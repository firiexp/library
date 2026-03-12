const jsonUrl = __JSON_URL__;
const sortColumns = __SORT_COLUMNS_JSON__;
let report = __BOOTSTRAP_JSON__;
const rows = document.getElementById("rows");
const filterInput = document.getElementById("filter");
const statusFilter = document.getElementById("status-filter");
const sortKey = document.getElementById("sort-key");
const sortDirection = document.getElementById("sort-direction");
const summaryLive = document.getElementById("summary-live");
const summaryGenerated = document.getElementById("summary-generated");
const summaryTotal = document.getElementById("summary-total");
const summaryProgress = document.getElementById("summary-progress");
const summaryFailed = document.getElementById("summary-failed");
const summaryVisible = document.getElementById("summary-visible");
const resultCount = document.getElementById("result-count");
const sortSummary = document.getElementById("sort-summary");
const controls = document.getElementById("controls");
const tableScroll = document.getElementById("table-scroll");
const tableHeaderWrap = document.getElementById("table-header-wrap");
let currentSort = "slowestSec";
let currentSortDirection = "desc";
let selectedPath = null;
let currentDetailTab = "case";
let currentCaseFilter = "all";
let currentCaseSort = "timeDesc";
let pendingReport = null;
const skeletonRows = 6;

function syncStickyHeaderOffset() {
    if (!controls) return;
    const controlsStyle = window.getComputedStyle(controls);
    const top = Number.parseFloat(controlsStyle.top) || 0;
    const gap = 8;
    const offset = Math.ceil(top + controls.getBoundingClientRect().height + gap);
    document.documentElement.style.setProperty("--dashboard-header-top", `${offset}px`);
}

function syncHeaderScroll() {
    if (!tableScroll || !tableHeaderWrap) return;
    tableHeaderWrap.scrollLeft = tableScroll.scrollLeft;
}

function fmtDurationMs(value) {
    if (value == null) return "-";
    return `${Math.round(value * 1000)} ms`;
}

function fmtMb(value) {
    if (value == null) return "-";
    return `${Math.round(value)} MB`;
}

function esc(value) {
    return String(value)
        .replaceAll("&", "&amp;")
        .replaceAll("<", "&lt;")
        .replaceAll(">", "&gt;")
        .replaceAll('"', "&quot;");
}

function compactProblemLabel(problem) {
    try {
        const url = new URL(problem);
        const segments = url.pathname.split("/").filter(Boolean);
        const tail = segments.slice(-2).join(" / ");
        return tail ? `${url.hostname} / ${tail}` : url.hostname;
    } catch (_error) {
        return problem;
    }
}

function renderProblem(problem, { compact = true, muted = true } = {}) {
    if (!problem) return `<span class="muted">problem url is unavailable</span>`;
    const url = esc(problem);
    const label = esc(compact ? compactProblemLabel(problem) : problem);
    const className = muted ? "problem-link muted" : "problem-link";
    return `<a class="${className}" href="${url}" title="${url}" target="_blank" rel="noreferrer noopener">${label}</a>`;
}

function statusClass(entry) {
    if (entry.phase === "running" || entry.phase === "pending") return "status-warn";
    if (entry.phase === "error") return "status-bad";
    if (entry.run.ok) return "status-ok";
    if (entry.run.parsed.caseCount > 0) return "status-bad";
    return "status-bad";
}

function statusLabel(entry) {
    if (entry.phase === "pending") return "PENDING";
    if (entry.phase === "running") return "RUNNING";
    if (entry.phase === "error") return "ERROR";
    if (entry.run.ok) return "OK";
    if (entry.run.parsed.caseCount > 0) return "FAILED";
    return "ERROR";
}

function isFailedEntry(entry) {
    return entry.phase === "error" || (entry.phase === "done" && !entry.run.ok);
}

function normalized(entry, key) {
    if (key === "path") return entry.path;
    if (key === "status") return statusLabel(entry);
    if (key === "compileWallSec") return entry.compiler.wallSec ?? -1;
    if (key === "slowestSec") return entry.run.parsed.slowestSec ?? -1;
    if (key === "averageSec") return entry.run.parsed.averageSec ?? -1;
    if (key === "maxMemoryMb") return entry.run.parsed.maxMemoryMb ?? -1;
    return -1;
}

function defaultSortDirection(key) {
    return sortColumns.find((column) => column.key === key)?.defaultDirection ?? "desc";
}

function sortLabel(key) {
    return sortColumns.find((column) => column.key === key)?.label ?? "slowest";
}

function applyChipState(element, ...states) {
    element.className = ["chip", ...states.filter(Boolean)].join(" ");
}

function isLoadingInitialReport(totalTests) {
    return report.tests.length === 0 && totalTests > 0;
}

function buildLoadingSkeleton() {
    return Array.from({ length: skeletonRows }, () => `
        <tr class="skeleton-row" aria-hidden="true">
            <td>
                <div class="skeleton-stack">
                    <span class="skeleton-line"></span>
                    <span class="skeleton-line mid"></span>
                </div>
            </td>
            <td><span class="skeleton-line short"></span></td>
            <td><span class="skeleton-line short"></span></td>
            <td>
                <div class="skeleton-stack">
                    <span class="skeleton-line short"></span>
                    <span class="skeleton-line mid"></span>
                </div>
            </td>
            <td><span class="skeleton-line short"></span></td>
            <td><span class="skeleton-line short"></span></td>
        </tr>
    `).join("");
}

function syncSortUi() {
    if (sortKey) sortKey.value = currentSort;
    if (sortDirection) sortDirection.value = currentSortDirection;
    document.querySelectorAll("[data-sort]").forEach((button) => {
        const active = button.dataset.sort === currentSort;
        const indicator = button.querySelector(".sort-indicator");
        const header = button.closest("th");
        if (header) {
            header.classList.toggle("is-active", active);
            header.setAttribute("aria-sort", active ? (currentSortDirection === "asc" ? "ascending" : "descending") : "none");
        }
        button.setAttribute("aria-pressed", active ? "true" : "false");
        button.title = active
            ? `${button.dataset.label} (${currentSortDirection === "asc" ? "ascending" : "descending"})`
            : `sort by ${button.dataset.label}`;
        if (indicator) indicator.textContent = active ? (currentSortDirection === "asc" ? "↑" : "↓") : "";
    });
    if (sortSummary) {
        sortSummary.textContent = `sort: ${sortLabel(currentSort)} / ${currentSortDirection}`;
    }
}

function buildCaseTable(entry) {
    const cases = entry.run.parsed.cases.map((testcase) => {
        const isSlowest = testcase.name === entry.run.parsed.slowestCase;
        const isMaxMemory = testcase.name === entry.run.parsed.maxMemoryCase;
        const isFailed = testcase.status != null && testcase.status !== "AC";
        return {
            ...testcase,
            isSlowest,
            isMaxMemory,
            isFailed,
            isHot: isSlowest || isMaxMemory || isFailed,
        };
    });
    if (!cases.length) return "<div class=\"muted\">case detail is unavailable</div>";
    const filteredCases = cases
        .filter((testcase) => {
            if (currentCaseFilter === "failed") return testcase.isFailed;
            if (currentCaseFilter === "hot") return testcase.isHot;
            return true;
        })
        .sort((lhs, rhs) => {
            if (currentCaseSort === "timeAsc") return (lhs.timeSec ?? Number.POSITIVE_INFINITY) - (rhs.timeSec ?? Number.POSITIVE_INFINITY);
            if (currentCaseSort === "nameAsc") return lhs.name.localeCompare(rhs.name);
            return (rhs.timeSec ?? -1) - (lhs.timeSec ?? -1);
        });
    return `
        <h3 class="detail-block-title">case detail</h3>
        <div class="detail-toolbar">
            <select data-case-filter>
                <option value="all"${currentCaseFilter === "all" ? " selected" : ""}>cases: all</option>
                <option value="hot"${currentCaseFilter === "hot" ? " selected" : ""}>cases: hot only</option>
                <option value="failed"${currentCaseFilter === "failed" ? " selected" : ""}>cases: failed only</option>
            </select>
            <select data-case-sort>
                <option value="timeDesc"${currentCaseSort === "timeDesc" ? " selected" : ""}>sort: time desc</option>
                <option value="timeAsc"${currentCaseSort === "timeAsc" ? " selected" : ""}>sort: time asc</option>
                <option value="nameAsc"${currentCaseSort === "nameAsc" ? " selected" : ""}>sort: case name</option>
            </select>
            <div class="muted">showing ${filteredCases.length} / ${cases.length} cases</div>
        </div>
        <table class="case-table">
            <thead>
                <tr><th>case</th><th class="num">time</th><th>status</th></tr>
            </thead>
            <tbody>
                ${filteredCases.length ? filteredCases.map((testcase) => `
                    <tr class="case-row${testcase.isHot ? " is-hot" : ""}${testcase.isFailed ? " is-failed" : ""}">
                        <td>
                            <div class="case-name">
                                <div class="path">${esc(testcase.name)}</div>
                                <div class="case-tags">
                                    ${testcase.isSlowest ? '<span class="case-tag is-hot">slowest</span>' : ""}
                                    ${testcase.isMaxMemory ? '<span class="case-tag is-hot">max memory</span>' : ""}
                                    ${testcase.isFailed ? '<span class="case-tag is-failed">failed</span>' : ""}
                                </div>
                            </div>
                        </td>
                        <td class="num" title="${fmtDurationMs(testcase.timeSec ?? null)}">${fmtDurationMs(testcase.timeSec ?? null)}</td>
                        <td>${esc(testcase.status ?? "-")}</td>
                    </tr>
                `).join("") : '<tr><td colspan="3"><div class="empty-state">current case filter に一致する case はない</div></td></tr>'}
            </tbody>
        </table>
    `;
}

function buildRawLog(entry) {
    if (!entry.run.output) return "<div class=\"muted\">raw log is unavailable</div>";
    const lines = entry.run.output.split("\n");
    const failureIndex = lines.findIndex((line) => line.startsWith("[FAILURE]") || line.startsWith("[ERROR]"));
    const excerpt = failureIndex >= 0
        ? lines.slice(Math.max(0, failureIndex - 2), Math.min(lines.length, failureIndex + 12)).join("\n").trim()
        : "";
    const summary = entry.run.parsed.summary ?? (entry.run.ok ? "test success" : statusLabel(entry));
    return `
        <h3 class="detail-block-title">raw log</h3>
        <div class="detail-toolbar">
            <div class="chip ${statusClass(entry)}">summary: ${esc(summary ?? "-")}</div>
            <div class="muted">${failureIndex >= 0 ? "first failure excerpt を先に表示する" : "full log のみ利用できる"}</div>
        </div>
        ${excerpt ? `
            <details class="log-block" open>
                <summary>first failure excerpt</summary>
                <pre>${esc(excerpt)}</pre>
            </details>
        ` : ""}
        <details class="log-block"${excerpt ? "" : " open"}>
            <summary>full log</summary>
            <pre>${esc(entry.run.output)}</pre>
        </details>
    `;
}

function findEntry(path) {
    return report.tests.find((entry) => entry.path === path) ?? null;
}

function ensureSelection(filtered) {
    if (!filtered.length || selectedPath == null) return null;
    if (filtered.some((entry) => entry.path === selectedPath)) return findEntry(selectedPath);
    selectedPath = null;
    return null;
}

function bindSelection() {
    rows.querySelectorAll("[data-expand-path]").forEach((button) => {
        const select = () => {
            selectedPath = selectedPath === button.dataset.expandPath ? null : button.dataset.expandPath;
            render();
        };
        button.addEventListener("click", select);
    });
}

function buildDetailPanel(entry) {
    const chips = [
        `<div class="chip ${statusClass(entry)}">status: ${statusLabel(entry)}</div>`,
        `<div class="chip">compile: ${fmtDurationMs(entry.compiler.wallSec)}</div>`,
        `<div class="chip">slowest: ${fmtDurationMs(entry.run.parsed.slowestSec)}</div>`,
        `<div class="chip">average: ${fmtDurationMs(entry.run.parsed.averageSec)}</div>`,
        `<div class="chip">memory: ${fmtMb(entry.run.parsed.maxMemoryMb)}</div>`,
        `<div class="chip">cases: ${entry.run.parsed.caseCount} / cached ${entry.testcases.cachedCaseCount}</div>`,
    ].join("");
    const content = currentDetailTab === "raw" ? buildRawLog(entry) : buildCaseTable(entry);
    return `
        <div class="detail-panel">
            <div class="detail-head">
                <div class="detail-head-main">
                    <div>
                        <div class="eyebrow">expanded test</div>
                        <h2 class="detail-title">${esc(entry.path)}</h2>
                        <div>${renderProblem(entry.problem, { compact: true, muted: false })}</div>
                        <div class="detail-problem-full muted">${renderProblem(entry.problem, { compact: false })}</div>
                    </div>
                </div>
                <div class="detail-head-side">
                    <div class="detail-chips">${chips}</div>
                </div>
            </div>
            <div class="detail-tabs">
                <button class="detail-tab${currentDetailTab === "case" ? " is-active" : ""}" type="button" data-detail-tab="case">case detail</button>
                <button class="detail-tab${currentDetailTab === "raw" ? " is-active" : ""}" type="button" data-detail-tab="raw">raw log</button>
            </div>
            <div class="detail-content">${content}</div>
        </div>
    `;
}

function bindDetailTabs() {
    rows.querySelectorAll("[data-detail-tab]").forEach((button) => {
        button.addEventListener("click", (event) => {
            event.stopPropagation();
            currentDetailTab = button.dataset.detailTab;
            render();
        });
    });
    rows.querySelectorAll("[data-case-filter]").forEach((select) => {
        select.addEventListener("change", () => {
            currentCaseFilter = select.value;
            render();
        });
    });
    rows.querySelectorAll("[data-case-sort]").forEach((select) => {
        select.addEventListener("change", () => {
            currentCaseSort = select.value;
            render();
        });
    });
}

function updateLiveChip() {
    const meta = pendingReport != null ? "update pending" : "auto";
    summaryLive.innerHTML = `<span class="live-dot" aria-hidden="true"></span><span class="chip-label">live</span><span class="chip-meta">${meta}</span>`;
    applyChipState(summaryLive, "chip-action", pendingReport != null ? "is-active" : "is-ok");
    summaryLive.disabled = false;
    summaryLive.title = pendingReport != null
        ? "apply pending update now"
        : (refreshLock ? "refresh in progress" : "refresh now");
}

function render() {
    if (selectedPath == null && pendingReport != null) {
        report = pendingReport;
        pendingReport = null;
    }
    const query = filterInput.value.trim().toLowerCase();
    const totalTests = report.testCount ?? report.tests.length;
    const loadingInitial = isLoadingInitialReport(totalTests);
    const filtered = report.tests
        .filter((entry) => {
            const haystack = `${entry.path} ${entry.problem}`.toLowerCase();
            if (query && !haystack.includes(query)) return false;
            if (statusFilter.value === "ok" && !entry.run.ok) return false;
            if (statusFilter.value === "failed" && !isFailedEntry(entry)) return false;
            return true;
        })
        .sort((lhs, rhs) => {
            const a = normalized(lhs, currentSort);
            const b = normalized(rhs, currentSort);
            const direction = currentSortDirection === "asc" ? 1 : -1;
            if (typeof a === "string" || typeof b === "string") {
                return direction * String(a).localeCompare(String(b));
            }
            return direction * (a - b);
        });
    ensureSelection(filtered);
    syncSortUi();

    if (!filtered.length) {
        if (loadingInitial) {
            rows.innerHTML = buildLoadingSkeleton();
        } else {
            rows.innerHTML = `<tr><td colspan="6"><div class="empty-state">current filter に一致する test はない</div></td></tr>`;
        }
    } else {
        rows.innerHTML = filtered.map((entry) => {
            const slowest = entry.run.parsed.slowestSec;
            const isSelected = selectedPath === entry.path;
            const detailRow = isSelected
                ? `
                <tr class="detail-row">
                    <td colspan="6">${buildDetailPanel(entry)}</td>
                </tr>
                `
                : "";
            return `
                <tr class="dashboard-row${isSelected ? " is-selected" : ""}" data-entry-path="${esc(entry.path)}" aria-selected="${isSelected ? "true" : "false"}">
                    <td>
                        <div class="test-main">
                            <div class="test-head">
                                <button class="expander${isSelected ? " is-open" : ""}" type="button" data-expand-path="${esc(entry.path)}" aria-expanded="${isSelected ? "true" : "false"}">${isSelected ? "−" : "+"}</button>
                                <div class="path test-path" title="${esc(entry.path)}">${esc(entry.path)}</div>
                            </div>
                            <div class="test-problem">${renderProblem(entry.problem)}</div>
                        </div>
                    </td>
                    <td data-label="status"><span class="status-badge ${statusClass(entry)}">${statusLabel(entry)}</span></td>
                    <td class="num" data-label="compile" title="${fmtDurationMs(entry.compiler.wallSec)}">${fmtDurationMs(entry.compiler.wallSec)}</td>
                    <td class="num" data-label="slowest" title="${fmtDurationMs(slowest)}">
                        <div>${fmtDurationMs(slowest)}</div>
                        <div class="muted metric-sub" title="${esc(entry.run.parsed.slowestCase ?? "-")}">${esc(entry.run.parsed.slowestCase ?? "-")}</div>
                    </td>
                    <td class="num" data-label="average" title="${fmtDurationMs(entry.run.parsed.averageSec)}">${fmtDurationMs(entry.run.parsed.averageSec)}</td>
                    <td class="num" data-label="memory" title="${fmtMb(entry.run.parsed.maxMemoryMb)}">${fmtMb(entry.run.parsed.maxMemoryMb)}</td>
                </tr>
                ${detailRow}
            `;
        }).join("");
    }

    const summary = report.summary ?? {};
    const pending = summary.pending ?? 0;
    const running = summary.running ?? 0;
    const done = summary.done ?? 0;
    const failed = summary.failed ?? report.tests.filter((entry) => isFailedEntry(entry)).length;
    summaryGenerated.textContent = `generated: ${report.generatedAt}`;
    summaryTotal.textContent = `tests: ${totalTests}`;
    summaryProgress.textContent = `done: ${done} / running: ${running} / pending: ${pending}`;
    summaryFailed.textContent = statusFilter.value === "failed" ? `failed: ${failed} (filtered)` : `failed: ${failed}`;
    summaryVisible.textContent = loadingInitial ? "visible: loading" : `visible: ${filtered.length}`;
    updateLiveChip();
    applyChipState(summaryTotal);
    applyChipState(summaryProgress, running > 0 || pending > 0 ? "is-warn" : "is-ok");
    applyChipState(summaryFailed, "chip-action", failed > 0 ? "is-bad" : "is-ok", statusFilter.value === "failed" ? "is-active" : "");
    applyChipState(summaryVisible, loadingInitial || query || statusFilter.value !== "all" ? "is-active" : "");
    summaryFailed.disabled = failed === 0 && statusFilter.value !== "failed";
    summaryFailed.title = statusFilter.value === "failed" ? "clear failed filter" : "show failed tests only";
    resultCount.textContent = filtered.length
        ? `displaying ${filtered.length} / ${totalTests} tests`
        : (loadingInitial ? `loading dashboard... ${totalTests} tests queued` : "displaying 0 tests");
    bindSelection();
    bindDetailTabs();
}

let refreshLock = false;
async function refreshReport() {
    if (refreshLock) return;
    refreshLock = true;
    updateLiveChip();
    try {
        const response = await fetch(`${jsonUrl}?t=${Date.now()}`, { cache: "no-store" });
        if (!response.ok) return;
        const nextReport = await response.json();
        if (selectedPath != null) {
            pendingReport = nextReport;
            updateLiveChip();
        } else {
            report = nextReport;
            pendingReport = null;
            render();
        }
    } catch (_error) {
    } finally {
        refreshLock = false;
        if (selectedPath != null || pendingReport != null) {
            updateLiveChip();
        } else if (!document.hidden) {
            updateLiveChip();
        }
    }
}

document.querySelectorAll("[data-sort]").forEach((button) => {
    button.addEventListener("click", () => {
        if (currentSort === button.dataset.sort) {
            currentSortDirection = currentSortDirection === "asc" ? "desc" : "asc";
        } else {
            currentSort = button.dataset.sort;
            currentSortDirection = defaultSortDirection(currentSort);
        }
        render();
    });
});
filterInput.addEventListener("input", render);
statusFilter.addEventListener("change", render);
summaryFailed.addEventListener("click", () => {
    statusFilter.value = statusFilter.value === "failed" ? "all" : "failed";
    render();
});
summaryLive.addEventListener("click", () => {
    if (pendingReport != null) {
        report = pendingReport;
        pendingReport = null;
        render();
        return;
    }
    refreshReport();
});
sortKey.addEventListener("change", () => {
    currentSort = sortKey.value;
    render();
});
sortDirection.addEventListener("change", () => {
    currentSortDirection = sortDirection.value;
    render();
});
render();
syncStickyHeaderOffset();
syncHeaderScroll();
refreshReport();
setInterval(refreshReport, 2000);
window.addEventListener("resize", syncStickyHeaderOffset);
window.addEventListener("load", syncStickyHeaderOffset);
if (tableScroll) {
    tableScroll.addEventListener("scroll", syncHeaderScroll, { passive: true });
}
if ("ResizeObserver" in window && controls) {
    new ResizeObserver(syncStickyHeaderOffset).observe(controls);
}
