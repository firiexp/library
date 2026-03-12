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
const chipTemplate = document.getElementById("dashboard-chip-template");
const liveChipTemplate = document.getElementById("dashboard-live-chip-template");
const emptyRowTemplate = document.getElementById("dashboard-empty-row-template");
const skeletonRowTemplate = document.getElementById("dashboard-skeleton-row-template");
const dashboardRowTemplate = document.getElementById("dashboard-row-template");
const detailRowTemplate = document.getElementById("detail-row-template");
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

function describeProblem(problem, { compact = true } = {}) {
    if (!problem) {
        return {
            available: false,
            label: "problem url is unavailable",
            url: "",
        };
    }
    return {
        available: true,
        label: compact ? compactProblemLabel(problem) : problem,
        url: problem,
    };
}

function cloneTemplate(template) {
    return template.content.firstElementChild.cloneNode(true);
}

function cloneTemplateContent(template) {
    return template.content.cloneNode(true);
}

function buildProblemNode(problem, { compact = true, muted = true } = {}) {
    const view = describeProblem(problem, { compact });
    if (!view.available) {
        const missing = document.createElement("span");
        missing.className = "muted";
        missing.textContent = view.label;
        return missing;
    }
    const link = document.createElement("a");
    link.className = muted ? "problem-link muted" : "problem-link";
    link.href = view.url;
    link.title = view.url;
    link.target = "_blank";
    link.rel = "noreferrer noopener";
    link.textContent = view.label;
    return link;
}

function setMetricText(element, value) {
    element.textContent = value;
    element.title = value;
}

function buildChip(text, ...states) {
    const chip = cloneTemplate(chipTemplate);
    applyChipState(chip, ...states);
    chip.textContent = text;
    return chip;
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
    const fragment = document.createDocumentFragment();
    for (let i = 0; i < skeletonRows; i += 1) {
        fragment.append(cloneTemplate(skeletonRowTemplate));
    }
    return fragment;
}

function buildEmptyRow(message) {
    const row = cloneTemplate(emptyRowTemplate);
    row.querySelector(".empty-state").textContent = message;
    return row;
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

function toggleSelection(path) {
    selectedPath = selectedPath === path ? null : path;
}

function buildDashboardRow(entry, isSelected) {
    const slowest = entry.run.parsed.slowestSec;
    const row = cloneTemplate(dashboardRowTemplate);
    const expander = row.querySelector("[data-expand-path]");
    const pathLabel = row.querySelector(".test-path");
    const statusBadge = row.querySelector(".status-badge");
    const compileCell = row.querySelector(".cell-compile");
    const slowestValue = row.querySelector(".cell-slowest-value");
    const slowestCase = row.querySelector(".cell-slowest-case");
    const averageCell = row.querySelector(".cell-average");
    const memoryCell = row.querySelector(".cell-memory");

    row.dataset.entryPath = entry.path;
    row.setAttribute("aria-selected", isSelected ? "true" : "false");
    row.classList.toggle("is-selected", isSelected);

    expander.dataset.expandPath = entry.path;
    expander.setAttribute("aria-expanded", isSelected ? "true" : "false");
    expander.classList.toggle("is-open", isSelected);
    expander.textContent = isSelected ? "−" : "+";

    pathLabel.textContent = entry.path;
    pathLabel.title = entry.path;
    row.querySelector(".test-problem").replaceChildren(buildProblemNode(entry.problem));

    statusBadge.className = `status-badge ${statusClass(entry)}`;
    statusBadge.textContent = statusLabel(entry);

    setMetricText(compileCell, fmtDurationMs(entry.compiler.wallSec));
    setMetricText(slowestValue, fmtDurationMs(slowest));
    slowestCase.textContent = entry.run.parsed.slowestCase ?? "-";
    slowestCase.title = entry.run.parsed.slowestCase ?? "-";
    setMetricText(averageCell, fmtDurationMs(entry.run.parsed.averageSec));
    setMetricText(memoryCell, fmtMb(entry.run.parsed.maxMemoryMb));

    return row;
}

function buildDetailRow(entry) {
    const detailRow = cloneTemplate(detailRowTemplate);
    const compactProblem = detailRow.querySelector(".detail-problem-compact");
    const fullProblem = detailRow.querySelector(".detail-problem-full");
    const chipContainer = detailRow.querySelector(".detail-chips");
    const detailContent = detailRow.querySelector(".detail-content");

    detailRow.querySelector(".detail-title").textContent = entry.path;
    compactProblem.replaceChildren(buildProblemNode(entry.problem, { compact: true, muted: false }));
    fullProblem.replaceChildren(buildProblemNode(entry.problem, { compact: false }));
    chipContainer.replaceChildren(
        buildChip(`status: ${statusLabel(entry)}`, statusClass(entry)),
        buildChip(`compile: ${fmtDurationMs(entry.compiler.wallSec)}`),
        buildChip(`slowest: ${fmtDurationMs(entry.run.parsed.slowestSec)}`),
        buildChip(`average: ${fmtDurationMs(entry.run.parsed.averageSec)}`),
        buildChip(`memory: ${fmtMb(entry.run.parsed.maxMemoryMb)}`),
        buildChip(`cases: ${entry.run.parsed.caseCount} / cached ${entry.testcases.cachedCaseCount}`),
    );
    detailRow.querySelectorAll("[data-detail-tab]").forEach((button) => {
        button.classList.toggle("is-active", button.dataset.detailTab === currentDetailTab);
    });
    detailContent.innerHTML = currentDetailTab === "raw" ? buildRawLog(entry) : buildCaseTable(entry);
    return detailRow;
}

function applyPendingReportIfIdle() {
    if (selectedPath == null && pendingReport != null) {
        report = pendingReport;
        pendingReport = null;
    }
}

function getVisibleEntries(query, statusValue) {
    return report.tests
        .filter((entry) => {
            const haystack = `${entry.path} ${entry.problem}`.toLowerCase();
            if (query && !haystack.includes(query)) return false;
            if (statusValue === "ok" && !entry.run.ok) return false;
            if (statusValue === "failed" && !isFailedEntry(entry)) return false;
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
}

function renderRows(filtered, { loadingInitial }) {
    if (!filtered.length) {
        if (loadingInitial) {
            rows.replaceChildren(buildLoadingSkeleton());
        } else {
            rows.replaceChildren(buildEmptyRow("current filter に一致する test はない"));
        }
        return;
    }

    const fragment = document.createDocumentFragment();
    filtered.forEach((entry) => {
        const isSelected = selectedPath === entry.path;
        fragment.append(buildDashboardRow(entry, isSelected));
        if (isSelected) fragment.append(buildDetailRow(entry));
    });
    rows.replaceChildren(fragment);
}

function getSummaryState(filtered, { totalTests, loadingInitial, query, statusValue }) {
    const summary = report.summary ?? {};
    const pending = summary.pending ?? 0;
    const running = summary.running ?? 0;
    const done = summary.done ?? 0;
    const failed = summary.failed ?? report.tests.filter((entry) => isFailedEntry(entry)).length;

    return {
        generatedText: `generated: ${report.generatedAt}`,
        totalText: `tests: ${totalTests}`,
        progressText: `done: ${done} / running: ${running} / pending: ${pending}`,
        failedText: statusValue === "failed" ? `failed: ${failed} (filtered)` : `failed: ${failed}`,
        visibleText: loadingInitial ? "visible: loading" : `visible: ${filtered.length}`,
        resultCountText: filtered.length
            ? `displaying ${filtered.length} / ${totalTests} tests`
            : (loadingInitial ? `loading dashboard... ${totalTests} tests queued` : "displaying 0 tests"),
        progressStates: [running > 0 || pending > 0 ? "is-warn" : "is-ok"],
        failedStates: ["chip-action", failed > 0 ? "is-bad" : "is-ok", statusValue === "failed" ? "is-active" : ""],
        visibleStates: [loadingInitial || query || statusValue !== "all" ? "is-active" : ""],
        failedDisabled: failed === 0 && statusValue !== "failed",
        failedTitle: statusValue === "failed" ? "clear failed filter" : "show failed tests only",
    };
}

function updateSummary(filtered, options) {
    const state = getSummaryState(filtered, options);
    summaryGenerated.textContent = state.generatedText;
    summaryTotal.textContent = state.totalText;
    summaryProgress.textContent = state.progressText;
    summaryFailed.textContent = state.failedText;
    summaryVisible.textContent = state.visibleText;
    resultCount.textContent = state.resultCountText;
    updateLiveChip();
    applyChipState(summaryTotal);
    applyChipState(summaryProgress, ...state.progressStates);
    applyChipState(summaryFailed, ...state.failedStates);
    applyChipState(summaryVisible, ...state.visibleStates);
    summaryFailed.disabled = state.failedDisabled;
    summaryFailed.title = state.failedTitle;
}

function updateLiveChip() {
    const meta = pendingReport != null ? "update pending" : "auto";
    summaryLive.replaceChildren(cloneTemplateContent(liveChipTemplate));
    summaryLive.querySelector(".chip-meta").textContent = meta;
    applyChipState(summaryLive, "chip-action", pendingReport != null ? "is-active" : "is-ok");
    summaryLive.disabled = false;
    summaryLive.title = pendingReport != null
        ? "apply pending update now"
        : (refreshLock ? "refresh in progress" : "refresh now");
}

function render() {
    applyPendingReportIfIdle();
    const query = filterInput.value.trim().toLowerCase();
    const totalTests = report.testCount ?? report.tests.length;
    const loadingInitial = isLoadingInitialReport(totalTests);
    const filtered = getVisibleEntries(query, statusFilter.value);
    ensureSelection(filtered);
    syncSortUi();
    renderRows(filtered, { loadingInitial });
    updateSummary(filtered, { totalTests, loadingInitial, query, statusValue: statusFilter.value });
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
rows.addEventListener("click", (event) => {
    if (!(event.target instanceof Element)) return;

    const detailTab = event.target.closest("[data-detail-tab]");
    if (detailTab && rows.contains(detailTab)) {
        currentDetailTab = detailTab.dataset.detailTab;
        render();
        return;
    }

    const expandButton = event.target.closest("[data-expand-path]");
    if (expandButton && rows.contains(expandButton)) {
        toggleSelection(expandButton.dataset.expandPath);
        render();
    }
});
rows.addEventListener("change", (event) => {
    if (!(event.target instanceof Element)) return;

    const caseFilter = event.target.closest("[data-case-filter]");
    if (caseFilter && rows.contains(caseFilter)) {
        currentCaseFilter = caseFilter.value;
        render();
        return;
    }

    const caseSort = event.target.closest("[data-case-sort]");
    if (caseSort && rows.contains(caseSort)) {
        currentCaseSort = caseSort.value;
        render();
    }
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
