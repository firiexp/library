const NEW_BATCH_OPTION = "__new__";
const ACTIVE_STATUSES = new Set(["doc_review", "ready", "changes_requested", "approved"]);

const state = {
  overview: null,
  activeTab: "review",
  statusFilter: "active",
  selectedBranch: null,
  selectedBatch: null,
  diffMode: localStorage.getItem("local_review_diff_mode") || "unified",
  diffRange: "base",
  diffData: null,
  diffError: "",
  reviewDrafts: new Map(),
  openComposer: null,
  viewedFiles: {},
  collapsedFiles: {},
  showResolved: true,
  batchDraft: null,
  batchTargetMode: "auto",
  batchTargetExisting: "",
  batchTargetNew: "",
  batchTargetNewEdited: false,
  deleteBranchOnIntegrate: true,
  reopenReviewForm: false,
  activeEditor: null,
  editCheckResults: new Map(),
};

function el(tag, attrs = {}, ...children) {
  const node = document.createElement(tag);
  for (const [key, val] of Object.entries(attrs)) {
    if (key === "className") {
      node.className = val;
    } else if (key === "dataset") {
      Object.assign(node.dataset, val);
    } else if (key.startsWith("on") && typeof val === "function") {
      node.addEventListener(key.slice(2).toLowerCase(), val);
    } else if (val !== undefined && val !== null) {
      node.setAttribute(key, String(val));
    }
  }
  for (const child of children) {
    if (child === null || child === undefined || child === false) continue;
    if (typeof child === "string" || typeof child === "number") {
      node.appendChild(document.createTextNode(String(child)));
    } else {
      node.appendChild(child);
    }
  }
  return node;
}

let toastTimer = null;
function showToast(message, isError = false) {
  const toast = document.getElementById("toast");
  toast.textContent = message;
  toast.classList.toggle("error", isError);
  toast.classList.remove("hidden");
  if (toastTimer) clearTimeout(toastTimer);
  toastTimer = setTimeout(() => toast.classList.add("hidden"), 3200);
}

async function apiGet(url) {
  const resp = await fetch(url);
  const data = await resp.json();
  if (!resp.ok) {
    throw new Error(data.error || `HTTP ${resp.status}`);
  }
  return data;
}

async function apiPost(url, payload) {
  const resp = await fetch(url, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(payload),
  });
  const data = await resp.json();
  if (!resp.ok) {
    throw new Error(data.error || `HTTP ${resp.status}`);
  }
  return data;
}

function getSelectedItem() {
  if (!state.overview || !state.selectedBranch) return null;
  return state.overview.items.find((item) => item.branch === state.selectedBranch) || null;
}

function viewedKey(item, path) {
  return JSON.stringify([item.branch, state.diffData?.old_sha, state.diffData?.new_sha, path]);
}

function isFileViewed(item, path) {
  return Boolean(state.viewedFiles[viewedKey(item, path)]);
}

function setFileViewed(item, path, value) {
  state.viewedFiles[viewedKey(item, path)] = value;
  state.collapsedFiles[viewedKey(item, path)] = value;
}

function issueUrl(issueNumber) {
  if (!issueNumber || !state.overview || !state.overview.github_slug) return null;
  return `https://github.com/${state.overview.github_slug}/issues/${issueNumber}`;
}

function extractSuggestionBlocks(text) {
  const regex = /```suggestion\r?\n([\s\S]*?)```/g;
  const blocks = [];
  let match;
  while ((match = regex.exec(text)) !== null) {
    blocks.push(match[1]);
  }
  return blocks;
}

function canEditItem(item) {
  return Boolean(
    item &&
    item.branch_exists &&
    item.status !== "integrated" &&
    item.status !== "merged" &&
    state.diffData &&
    state.diffData.new_sha === item.live_head_sha
  );
}

function canApplyThreadSuggestion(item, thread) {
  return Boolean(canEditItem(item) && thread && thread.side === "new" && !thread.is_resolved);
}

function recordEditResult(branch, res) {
  state.editCheckResults.set(branch, {
    path: res.path,
    shortSha: res.short_sha,
    selfCheck: res.self_check,
    isCppEdit: Boolean(res.is_cpp_edit),
  });
}

function showCommitResultToast(res, label) {
  const selfCheck = res.self_check;
  if (selfCheck && !selfCheck.ok) {
    showToast(`${label} (${res.short_sha}) — ${selfCheck.summary}`, true);
  } else {
    const suffix = selfCheck && selfCheck.ran ? ` (${selfCheck.summary})` : "";
    showToast(`${label} (${res.short_sha})${suffix}`);
  }
}

function renderEditCheckBanner(item) {
  const banner = document.getElementById("edit-check-banner");
  if (!banner) return;
  const result = item ? state.editCheckResults.get(item.branch) : null;
  if (!result) {
    banner.className = "edit-check-banner hidden";
    banner.innerHTML = "";
    return;
  }
  const { path, shortSha, selfCheck, isCppEdit } = result;
  const statusClass = selfCheck && !selfCheck.ok
    ? "edit-check-fail"
    : selfCheck && selfCheck.ran
      ? "edit-check-ok"
      : "edit-check-info";
  banner.className = `edit-check-banner ${statusClass}`;
  banner.innerHTML = "";

  const summaryText = selfCheck ? selfCheck.summary : "committed";
  const hintParts = [path];
  if (isCppEdit) {
    hintParts.push("C++ ファイルを直接編集しました。必要に応じて verify を実行してください。");
  }

  const actions = [];
  if (selfCheck && !selfCheck.ok && canEditItem(item)) {
    actions.push(
      el(
        "button",
        {
          className: "btn btn-secondary btn-sm",
          type: "button",
          onClick: () => openFileEditor(item, path),
        },
        "ファイルを再編集"
      )
    );
  }
  actions.push(
    el(
      "button",
      {
        className: "btn btn-ghost btn-sm",
        type: "button",
        onClick: () => {
          state.editCheckResults.delete(item.branch);
          renderEditCheckBanner(item);
        },
      },
      "閉じる"
    )
  );

  banner.appendChild(
    el(
      "div",
      { className: "edit-check-head" },
      el(
        "div",
        { className: "edit-check-info-group" },
        el("strong", {}, `コミットしました (${shortSha}): ${summaryText}`),
        el("span", { className: "integrate-bar-hint" }, hintParts.join(" · "))
      ),
      el("div", { className: "form-actions-right" }, ...actions)
    )
  );
  if (selfCheck && !selfCheck.ok && selfCheck.output) {
    banner.appendChild(el("pre", { className: "edit-check-output" }, selfCheck.output));
  }
}

async function applyThreadSuggestion(item, thread, comment, suggestionIndex, buttonEl) {
  if (buttonEl) buttonEl.disabled = true;
  try {
    const res = await apiPost("/api/edit/suggestion", {
      branch: item.branch,
      thread_id: thread.id,
      comment_id: comment.id,
      suggestion_index: suggestionIndex,
      expected_head: item.live_head_sha,
      resolve: true,
      run_self_check: true,
    });
    recordEditResult(item.branch, res);
    showCommitResultToast(res, `Suggestion を適用しました`);
    await refreshAll(item.branch);
  } catch (err) {
    showToast(err.message, true);
  } finally {
    if (buttonEl && buttonEl.isConnected) buttonEl.disabled = false;
  }
}

function renderEditorPreview(preview) {
  const pane = document.getElementById("editor-preview-pane");
  pane.innerHTML = "";
  if (!preview.has_changes || !(preview.hunks || []).length) {
    pane.appendChild(el("div", { className: "empty-state" }, "変更はありません。"));
    return;
  }
  const tbody = el("tbody");
  for (const hunk of preview.hunks) {
    tbody.appendChild(
      el("tr", { className: "diff-hunk-row" }, el("td", { colspan: "4" }, hunk.header))
    );
    for (const line of hunk.lines) {
      const prefix = line.type === "add" ? "+" : line.type === "del" ? "-" : line.type === "meta" ? "" : " ";
      const rowClass = line.type === "add" ? "line-add" : line.type === "del" ? "line-del" : "";
      tbody.appendChild(
        el(
          "tr",
          { className: rowClass },
          el("td", { className: "line-num" }, line.old_line ?? ""),
          el("td", { className: "line-num" }, line.new_line ?? ""),
          el("td", { className: "line-action" }),
          el(
            "td",
            { className: "code-cell" },
            el("span", { className: "line-prefix" }, prefix),
            line.content
          )
        )
      );
    }
  }
  pane.appendChild(diffTable(preview, "unified", tbody));
}

async function switchEditorMode(mode) {
  const editor = state.activeEditor;
  if (!editor) return;
  editor.mode = mode;
  document.getElementById("editor-tab-edit").classList.toggle("active", mode === "edit");
  document.getElementById("editor-tab-preview").classList.toggle("active", mode === "preview");
  const textarea = document.getElementById("editor-textarea");
  const previewPane = document.getElementById("editor-preview-pane");
  textarea.classList.toggle("hidden", mode !== "edit");
  previewPane.classList.toggle("hidden", mode !== "preview");
  if (mode !== "preview") return;

  previewPane.innerHTML = "";
  previewPane.appendChild(el("div", { className: "empty-state" }, "プレビューを生成中..."));
  try {
    const preview = await apiPost("/api/edit/preview", {
      branch: editor.branch,
      path: editor.path,
      content: editor.draft,
      expected_head: editor.headSha,
    });
    if (state.activeEditor !== editor || editor.mode !== "preview") return;
    renderEditorPreview(preview);
  } catch (err) {
    if (state.activeEditor !== editor || editor.mode !== "preview") return;
    previewPane.innerHTML = "";
    previewPane.appendChild(el("div", { className: "empty-state" }, err.message));
  }
}

async function openFileEditor(item, path) {
  if (!item) return;
  try {
    const data = await apiGet(
      `/api/file?branch=${encodeURIComponent(item.branch)}&path=${encodeURIComponent(path)}&ref=${encodeURIComponent(item.live_head_sha)}`
    );
    document.getElementById("editor-file-path").textContent = path;
    document.getElementById("editor-head-sha").textContent = data.short_sha || data.head_sha.slice(0, 7);
    const textarea = document.getElementById("editor-textarea");
    textarea.value = data.content;
    const editor = {
      branch: item.branch,
      path,
      headSha: data.head_sha,
      original: textarea.value,
      draft: textarea.value,
      mode: "edit",
      saving: false,
    };
    state.activeEditor = editor;
    document.getElementById("editor-commit-msg").value = `Edit ${path}`;
    document.getElementById("editor-commit-btn").disabled = false;
    document.getElementById("file-editor-modal").classList.remove("hidden");
    await switchEditorMode("edit");
    textarea.focus();
  } catch (err) {
    showToast(err.message, true);
  }
}

function closeFileEditor(force = false) {
  if (!state.activeEditor) return;
  if (!force && state.activeEditor.draft !== state.activeEditor.original) {
    if (!window.confirm("未保存の編集があります。破棄しますか？")) return;
  }
  state.activeEditor = null;
  document.getElementById("file-editor-modal").classList.add("hidden");
}

async function commitFileEditor() {
  const editor = state.activeEditor;
  if (!editor || editor.saving) return;
  const commitBtn = document.getElementById("editor-commit-btn");
  editor.saving = true;
  commitBtn.disabled = true;
  try {
    const message = document.getElementById("editor-commit-msg").value.trim();
    const res = await apiPost("/api/edit/file", {
      branch: editor.branch,
      path: editor.path,
      content: editor.draft,
      expected_head: editor.headSha,
      message,
      run_self_check: true,
    });
    recordEditResult(editor.branch, res);
    closeFileEditor(true);
    showCommitResultToast(res, `${res.path} をコミットしました`);
    await refreshAll(res.branch);
  } catch (err) {
    showToast(err.message, true);
  } finally {
    if (state.activeEditor === editor) editor.saving = false;
    commitBtn.disabled = false;
  }
}

function renderCommentBody(bodyText, suggestionCtx = null) {
  const container = el("div", { className: "comment-body" });
  const regex = /```suggestion\r?\n([\s\S]*?)```/g;
  let lastIndex = 0;
  let suggestionIdx = 0;
  let match;
  while ((match = regex.exec(bodyText)) !== null) {
    if (match.index > lastIndex) {
      container.appendChild(document.createTextNode(bodyText.slice(lastIndex, match.index)));
    }
    const idx = suggestionIdx;
    suggestionIdx += 1;
    const suggestionCode = match[1].replace(/\r?\n$/, "");
    let applyBtn = null;
    if (suggestionCtx && canApplyThreadSuggestion(suggestionCtx.item, suggestionCtx.thread)) {
      applyBtn = el(
        "button",
        {
          className: "btn btn-primary btn-sm apply-suggestion-btn",
          type: "button",
          onClick: () =>
            applyThreadSuggestion(
              suggestionCtx.item,
              suggestionCtx.thread,
              suggestionCtx.comment,
              idx,
              applyBtn
            ),
        },
        "Apply & commit"
      );
    }
    container.appendChild(
      el(
        "div",
        { className: "suggestion-box" },
        el(
          "div",
          { className: "suggestion-head" },
          el("span", {}, "Suggested change"),
          applyBtn
        ),
        el("pre", { className: "suggestion-code" }, suggestionCode)
      )
    );
    lastIndex = regex.lastIndex;
  }
  if (lastIndex < bodyText.length) {
    container.appendChild(document.createTextNode(bodyText.slice(lastIndex)));
  }
  return container;
}

function renderStatusBadge(status) {
  return el("span", { className: `status-badge status-${status}` }, status.replace("_", " "));
}

function renderDiffstat(stats) {
  return el(
    "span",
    { className: "diffstat-chip" },
    el("span", { className: "add" }, `+${stats.additions || 0}`),
    " ",
    el("span", { className: "del" }, `-${stats.deletions || 0}`)
  );
}

function getExistingBatches() {
  return state.overview?.existing_batch_branches || [];
}

function formatBatchOptionLabel(batch) {
  const tags = [];
  if (batch.tracked) tags.push(`${batch.entry_count || 0}件`);
  if (batch.pr_url) tags.push("PR作成済");
  return tags.length > 0 ? `${batch.branch} (${tags.join("・")})` : batch.branch;
}

function syncBatchTargetState() {
  if (!state.overview) return;
  const existing = getExistingBatches();
  const suggested = state.overview.suggested_new_batch || state.overview.default_batch || "";
  if (!state.batchTargetNewEdited) {
    state.batchTargetNew = suggested;
  }
  if (existing.length > 0) {
    if (
      state.batchTargetMode === "auto" ||
      (state.batchTargetMode === "existing" &&
        !existing.some((entry) => entry.branch === state.batchTargetExisting))
    ) {
      state.batchTargetExisting = existing[0].branch;
    }
  } else {
    state.batchTargetExisting = "";
  }
}

function renderSingleBatchTargetControl(labelId, selectId, inputId, checkboxId, buttonId, isAll) {
  const existing = getExistingBatches();
  const hasExisting = existing.length > 0;
  const isNewMode = !hasExisting || state.batchTargetMode === "new";
  const labelEl = document.getElementById(labelId);
  const selectEl = document.getElementById(selectId);
  const inputEl = document.getElementById(inputId);
  const checkboxEl = document.getElementById(checkboxId);
  const buttonEl = document.getElementById(buttonId);

  labelEl.textContent = hasExisting ? "統合先" : "統合先（新規作成）";
  selectEl.classList.toggle("hidden", !hasExisting);
  if (hasExisting) {
    selectEl.innerHTML = "";
    for (const entry of existing) {
      selectEl.appendChild(el("option", { value: entry.branch }, formatBatchOptionLabel(entry)));
    }
    selectEl.appendChild(el("option", { value: NEW_BATCH_OPTION }, "+ 新しいバッチを作成..."));
    selectEl.value = isNewMode ? NEW_BATCH_OPTION : state.batchTargetExisting;
  }

  inputEl.classList.toggle("hidden", !isNewMode);
  if (inputEl.value !== state.batchTargetNew) {
    inputEl.value = state.batchTargetNew;
  }
  checkboxEl.checked = state.deleteBranchOnIntegrate;
  if (isAll) {
    buttonEl.textContent = isNewMode ? "新規バッチを作成してすべて統合" : "すべてバッチへ統合";
  } else {
    buttonEl.textContent = isNewMode ? "バッチを作成して統合" : "バッチへ統合";
  }
}

function renderBatchTargetControls() {
  if (!state.overview) return;
  renderSingleBatchTargetControl(
    "integrate-batch-label",
    "integrate-batch-select",
    "integrate-batch-input",
    "integrate-delete-branch",
    "btn-integrate-now",
    false
  );
  renderSingleBatchTargetControl(
    "batch-target-label",
    "batch-target-select",
    "batch-target-input",
    "batch-delete-branches",
    "btn-integrate-all",
    true
  );
}

function resolveTargetBatchName() {
  const existing = getExistingBatches();
  const isNewMode = existing.length === 0 || state.batchTargetMode === "new";
  if (isNewMode) {
    const name = state.batchTargetNew.trim();
    if (!name) {
      showToast("作成するバッチブランチ名を入力してください", true);
      return null;
    }
    return name;
  }
  return state.batchTargetExisting || existing[0]?.branch || null;
}

function updateTopbar() {
  if (!state.overview) return;
  document.getElementById("repo-name").textContent = state.overview.repo_name;
  document.getElementById("base-info").textContent = `${state.overview.base} @ ${state.overview.base_short_sha}`;
  const approvedCount = state.overview.items.filter((i) => i.status === "approved").length;
  const integratedCount = state.overview.batches
    .filter((b) => !b.is_merged)
    .reduce((acc, b) => acc + (b.entries ? b.entries.length : 0), 0);
  document.getElementById("batch-badge").textContent = `${approvedCount}/${integratedCount}`;

  syncBatchTargetState();
  renderBatchTargetControls();
}

function renderSidebar() {
  const items = state.overview.items;
  const counts = {
    active: 0,
    doc_review: 0,
    ready: 0,
    changes_requested: 0,
    approved: 0,
    integrated: 0,
    merged: 0,
  };
  for (const item of items) {
    if (ACTIVE_STATUSES.has(item.status)) counts.active += 1;
    if (counts[item.status] !== undefined) counts[item.status] += 1;
  }

  document.querySelectorAll("#status-filters .filter-pill").forEach((btn) => {
    const key = btn.dataset.status;
    btn.classList.toggle("active", key === state.statusFilter);
    const pill = btn.querySelector(".pill-count");
    if (pill) pill.textContent = String(counts[key] ?? 0);
  });

  const filtered =
    state.statusFilter === "active"
      ? items.filter((item) => ACTIVE_STATUSES.has(item.status))
      : items.filter((item) => item.status === state.statusFilter);

  const queueList = document.getElementById("queue-list");
  queueList.innerHTML = "";
  if (filtered.length === 0) {
    queueList.appendChild(el("div", { className: "muted" }, "該当するレビュー項目はありません。"));
  } else {
    for (const item of filtered) {
      const card = el(
        "div",
        {
          className: `queue-card${item.branch === state.selectedBranch ? " selected" : ""}`,
          onClick: () => selectBranch(item.branch),
        },
        el(
          "div",
          { className: "queue-card-top" },
          renderStatusBadge(item.status),
          item.issue !== null && item.issue !== undefined
            ? el("span", { className: "sha-chip" }, `#${item.issue}`)
            : el("span", { className: "sha-chip" }, item.live_short_sha)
        ),
        el("div", { className: "queue-card-title" }, item.title || item.branch),
        el("div", { className: "queue-card-branch" }, item.branch),
        el(
          "div",
          { className: "queue-card-meta" },
          renderDiffstat(item.stats || {}),
          item.unresolved_count > 0
            ? el("span", { className: "unresolved-chip" }, `${item.unresolved_count} open`)
            : null,
          item.has_updates_since_review
            ? el("span", { className: "updated-chip" }, "new commits")
            : null
        )
      );
      queueList.appendChild(card);
    }
  }

  const untracked = state.overview.untracked_branches || [];
  document.getElementById("untracked-count").textContent = String(untracked.length);
  const untrackedList = document.getElementById("untracked-list");
  untrackedList.innerHTML = "";
  for (const cand of untracked) {
    const row = el(
      "div",
      { className: "untracked-row" },
      el(
        "div",
        { className: "untracked-info" },
        el("div", { className: "untracked-branch" }, cand.branch),
        el("div", { className: "untracked-subject" }, `${cand.ahead} commit(s): ${cand.subject}`)
      ),
      el(
        "button",
        {
          className: "btn btn-secondary btn-sm",
          onClick: async () => {
            try {
              await apiPost("/api/submit", { branch: cand.branch, base: state.overview.base });
              showToast(`Registered ${cand.branch}`);
              await refreshAll(cand.branch);
            } catch (err) {
              showToast(err.message, true);
            }
          },
        },
        "Register"
      )
    );
    untrackedList.appendChild(row);
  }
}

function renderPrHeader(item) {
  const badge = document.getElementById("pr-status-badge");
  badge.className = `status-badge status-${item.status}`;
  badge.textContent = item.status.replace("_", " ");
  document.getElementById("pr-title").textContent = item.title || item.branch;

  const link = document.getElementById("pr-issue-link");
  if (item.issue !== null && item.issue !== undefined) {
    link.textContent = `#${item.issue}`;
    const url = issueUrl(item.issue);
    if (url) {
      link.href = url;
    } else {
      link.removeAttribute("href");
    }
    link.classList.remove("hidden");
  } else {
    link.classList.add("hidden");
  }

  document.getElementById("pr-branch-name").textContent = item.branch;
  document.getElementById("pr-base-name").textContent = item.base;
  document.getElementById("pr-head-sha").textContent = item.live_short_sha || "";
  const statHost = document.getElementById("pr-diffstat");
  statHost.innerHTML = "";
  statHost.appendChild(renderDiffstat(item.stats || {}));

  const grid = document.getElementById("pr-details-grid");
  grid.innerHTML = "";
  if (item.summary) {
    grid.appendChild(
      el("div", { className: "detail-card" }, el("h4", {}, "変更概要"), el("p", {}, item.summary))
    );
  }
  if (item.verification && item.verification.length > 0) {
    grid.appendChild(
      el(
        "div",
        { className: "detail-card" },
        el("h4", {}, "検証"),
        el(
          "ul",
          {},
          ...item.verification.map((line) => el("li", {}, line))
        )
      )
    );
  }
  if (item.performance) {
    grid.appendChild(
      el("div", { className: "detail-card" }, el("h4", {}, "性能"), el("p", {}, item.performance))
    );
  }
  if (item.review_notes) {
    grid.appendChild(
      el("div", { className: "detail-card" }, el("h4", {}, "レビュー観点"), el("p", {}, item.review_notes))
    );
  }
  if (item.batch) {
    grid.appendChild(
      el(
        "div",
        { className: "detail-card" },
        el("h4", {}, "統合先"),
        el("p", {}, `${item.batch} (${(item.integrated_sha || "").slice(0, 7)})`)
      )
    );
  }

  const reviewsBox = document.getElementById("pr-reviews-box");
  const reviewsList = document.getElementById("pr-reviews-list");
  reviewsList.innerHTML = "";
  if (item.reviews && item.reviews.length > 0) {
    reviewsBox.classList.remove("hidden");
    for (const rev of item.reviews) {
      reviewsList.appendChild(
        el(
          "div",
          { className: "review-entry" },
          el("strong", {}, `[${rev.action}] `),
          el("span", { className: "muted" }, `${rev.author} @ ${(rev.head_sha || "").slice(0, 7)}`),
          rev.body ? el("div", {}, rev.body) : null
        )
      );
    }
  } else {
    reviewsBox.classList.add("hidden");
  }

  const docReviewBar = document.getElementById("doc-review-bar");
  const integrateBar = document.getElementById("integrate-bar");
  const integratedBar = document.getElementById("integrated-bar");
  const reviewActionBar = document.getElementById("review-action-bar");
  const reopenBtn = document.getElementById("btn-reopen-review");
  const isDocReview = item.status === "doc_review" && item.branch_exists;
  const isApprovedActive = item.status === "approved" && item.branch_exists;
  const isIntegrated = item.status === "integrated";
  const isMerged = item.status === "merged";
  const isTerminal = isIntegrated || isMerged;

  docReviewBar.classList.toggle("hidden", !isDocReview);
  integrateBar.classList.toggle("hidden", !isApprovedActive);
  integratedBar.classList.toggle("hidden", !isTerminal);
  integratedBar.classList.toggle("merged-bar", isMerged);
  reviewActionBar.classList.toggle("hidden", isTerminal || (isApprovedActive && !state.reopenReviewForm));
  reopenBtn.textContent = state.reopenReviewForm ? "レビュー変更を閉じる" : "レビューを変更";

  if (isTerminal) {
    const sha = (item.integrated_sha || "").slice(0, 7);
    document.getElementById("integrated-bar-title").textContent = isMerged ? "マージ済み" : "統合済み";
    const detail = isMerged
      ? item.batch
        ? `${item.batch}${sha ? ` (${sha})` : ""} 経由で ${item.base} にマージされました`
        : `${item.base} にマージされました`
      : item.batch
        ? `${item.batch}${sha ? ` (${sha})` : ""} に統合しました`
        : "バッチブランチに統合しました";
    document.getElementById("integrated-bar-detail").textContent = detail;
    const readyItems = (state.overview?.items || []).filter((entry) => entry.status === "ready");
    const nextBtn = document.getElementById("btn-next-ready");
    nextBtn.classList.toggle("hidden", readyItems.length === 0);
    if (readyItems.length > 0) {
      nextBtn.textContent = `次のレビューへ（残り ${readyItems.length} 件）`;
    }
    document.getElementById("btn-go-batch-ship").classList.toggle("hidden", isMerged || !item.batch);
  }

  const rangeSelect = document.getElementById("diff-range-select");
  rangeSelect.innerHTML = "";
  rangeSelect.appendChild(el("option", { value: "base" }, `All changes (${item.base}...HEAD)`));
  if (item.has_updates_since_review) {
    rangeSelect.appendChild(
      el(
        "option",
        { value: "since_review" },
        `Since last review (${item.last_reviewed_sha.slice(0, 7)}..${item.live_short_sha})`
      )
    );
  }
  for (const commit of item.commits || []) {
    rangeSelect.appendChild(
      el("option", { value: `commit:${commit.sha}` }, `Commit ${commit.short_sha}: ${commit.subject}`)
    );
  }
  if ([...rangeSelect.options].some((o) => o.value === state.diffRange)) {
    rangeSelect.value = state.diffRange;
  } else {
    state.diffRange = "base";
    rangeSelect.value = "base";
  }
  renderEditCheckBanner(item);
}

function groupThreads(item, files) {
  const map = new Map();
  const outside = [];
  const byPath = new Map(files.map((file) => [file.path, file]));
  const diff = state.diffData;
  for (const thread of item.threads || []) {
    if (!state.showResolved && thread.is_resolved) continue;
    const { path, side, line } = thread;
    const sha = side === "old" ? diff.old_sha : diff.new_sha;
    const sameRevision = thread.anchor_sha ? thread.anchor_sha === sha :
      thread.head_sha === diff.new_sha && (side === "new" || state.diffRange === "base");
    if (!sameRevision || !byPath.get(path)?.hunks.some((h) =>
      line >= h[side + "_start"] && line < h[side + "_start"] + h[side + "_count"]
    )) {
      outside.push(thread);
      continue;
    }
    const key = `${path}|${side}|${line}`;
    if (!map.has(key)) map.set(key, []);
    map.get(key).push(thread);
  }
  return { map, outside };
}

function buildThreadElement(item, thread) {
  const replyInput = el("textarea", { rows: "2", placeholder: "返信を入力..." });
  const form = el(
    "div",
    { className: "thread-reply-form hidden" },
    replyInput,
    el(
      "div",
      { className: "form-actions" },
      el("span", { className: "muted" }, `Thread ${thread.id}`),
      el(
        "div",
        { className: "form-actions-right" },
        el(
          "button",
          {
            className: "btn btn-ghost btn-sm",
            onClick: () => form.classList.add("hidden"),
          },
          "Cancel"
        ),
        el(
          "button",
          {
            className: "btn btn-primary btn-sm",
            onClick: async () => {
              const text = replyInput.value.trim();
              if (!text) return;
              try {
                await apiPost("/api/threads/reply", {
                  branch: item.branch,
                  thread_id: thread.id,
                  body: text,
                  author: "human",
                });
                showToast("Reply posted");
                await refreshAll(item.branch);
              } catch (err) {
                showToast(err.message, true);
              }
            },
          },
          "Reply"
        )
      )
    )
  );

  const head = el(
    "div",
    { className: "thread-head" },
    el(
      "span",
      {},
      `${thread.path}:${thread.line} (${thread.side}) @ ${(thread.anchor_sha || thread.head_sha || "").slice(0, 7)}`,
      thread.is_resolved ? " — Resolved" : ""
    ),
    el(
      "div",
      { className: "form-actions-right" },
      el(
        "button",
        {
          className: "btn btn-ghost btn-sm",
          onClick: () => {
            form.classList.toggle("hidden");
            if (!form.classList.contains("hidden")) replyInput.focus();
          },
        },
        "Reply"
      ),
      el(
        "button",
        {
          className: "btn btn-secondary btn-sm",
          onClick: async () => {
            try {
              await apiPost("/api/threads/resolve", {
                branch: item.branch,
                thread_id: thread.id,
                resolved: !thread.is_resolved,
              });
              await refreshAll(item.branch);
            } catch (err) {
              showToast(err.message, true);
            }
          },
        },
        thread.is_resolved ? "Unresolve" : "Resolve"
      )
    )
  );

  const comments = (thread.comments || []).map((c) =>
    el(
      "div",
      { className: "thread-comment" },
      el(
        "div",
        { className: "comment-meta" },
        el("span", { className: "comment-author" }, c.author),
        c.commit ? el("code", {}, c.commit) : null,
        el("span", {}, (c.created_at || "").replace("T", " ").slice(0, 16))
      ),
      renderCommentBody(c.body || "", { item, thread, comment: c })
    )
  );

  return el(
    "div",
    { className: `thread-card${thread.is_resolved ? " resolved" : ""}` },
    head,
    ...comments,
    form
  );
}

function buildComposerElement(item, path, side, lineNumber, lineContent) {
  let applyBtn = null;
  const syncApplyButton = () => {
    if (!applyBtn) return;
    const blocks = extractSuggestionBlocks(textarea.value);
    applyBtn.classList.toggle("hidden", blocks.length !== 1);
  };

  const textarea = el("textarea", {
    rows: "3",
    placeholder: `${path}:${lineNumber} への指摘を入力...`,
    onInput: (ev) => {
      state.openComposer.draft = ev.target.value;
      syncApplyButton();
    },
  });
  textarea.value = state.openComposer.draft || "";

  if (side === "new" && canEditItem(item)) {
    applyBtn = el(
      "button",
      {
        className: "btn btn-approve btn-sm composer-apply-btn hidden",
        type: "button",
        onClick: async () => {
          const blocks = extractSuggestionBlocks(textarea.value);
          if (blocks.length !== 1) return;
          applyBtn.disabled = true;
          try {
            const res = await apiPost("/api/edit/suggestion", {
              branch: item.branch,
              path,
              line: lineNumber,
              start_line: lineNumber,
              replacement: blocks[0],
              expected_head: item.live_head_sha,
              run_self_check: true,
            });
            state.openComposer = null;
            recordEditResult(item.branch, res);
            showCommitResultToast(res, `${path}:${lineNumber} を更新しました`);
            await refreshAll(item.branch);
          } catch (err) {
            showToast(err.message, true);
          } finally {
            if (applyBtn.isConnected) applyBtn.disabled = false;
          }
        },
      },
      "Apply & commit"
    );
    syncApplyButton();
  }

  return el(
    "div",
    { className: "thread-card" },
    el(
      "div",
      { className: "thread-head" },
      el("strong", {}, `New comment on ${path}:${lineNumber} (${side})`)
    ),
    el(
      "div",
      { className: "comment-form" },
      textarea,
      el(
        "div",
        { className: "form-actions" },
        el(
          "button",
          {
            className: "btn btn-secondary btn-sm",
            onClick: () => {
              const block = `\`\`\`suggestion\n${lineContent}\n\`\`\`\n`;
              textarea.value = textarea.value ? `${textarea.value}\n${block}` : block;
              state.openComposer.draft = textarea.value;
              syncApplyButton();
              textarea.focus();
            },
          },
          "Insert suggestion"
        ),
        el(
          "div",
          { className: "form-actions-right" },
          el(
            "button",
            {
              className: "btn btn-ghost btn-sm",
              onClick: () => {
                state.openComposer = null;
                renderDiff(item);
              },
            },
            "Cancel"
          ),
          applyBtn,
          el(
            "button",
            {
              className: "btn btn-primary btn-sm",
              onClick: async () => {
                const body = textarea.value.trim();
                if (!body) return;
                try {
                  await apiPost("/api/threads", {
                    branch: item.branch,
                    path,
                    side,
                    anchor_sha: side === "old" ? state.diffData.old_sha : state.diffData.new_sha,
                    line: lineNumber,
                    body,
                    author: "human",
                  });
                  state.openComposer = null;
                  showToast("Comment added");
                  await refreshAll(item.branch);
                } catch (err) {
                  showToast(err.message, true);
                }
              },
            },
            "Add comment"
          )
        )
      )
    )
  );
}

function openComposerAt(item, path, side, lineNumber, content) {
  state.openComposer = { path, side, line: lineNumber, content };
  renderDiff(item);
}

function diffTable(file, mode, tbody) {
  let maxLine = 1;
  for (const hunk of file.hunks) {
    maxLine = Math.max(maxLine, hunk.old_start + hunk.old_count - 1, hunk.new_start + hunk.new_count - 1);
  }
  const columns = mode === "split"
    ? ["line-num", "line-action", "code", "line-num", "line-action", "code"]
    : ["line-num", "line-num", "line-action", "code"];
  const group = el("colgroup", {}, ...columns.map((name) => el("col", { className: name + "-col" })));
  const table = el("table", { className: "diff-table " + mode }, group, tbody);
  table.style.setProperty("--line-number-width", Math.max(2, String(maxLine).length) + "ch");
  return table;
}

function appendThreadRow(tbody, item, path, threadMap, anchors, colSpan) {
  const widgets = [];
  for (const [side, line] of anchors) {
    if (line == null) continue;
    for (const thread of threadMap.get(`${path}|${side}|${line}`) || []) {
      widgets.push(buildThreadElement(item, thread));
    }
    const composer = state.openComposer;
    if (composer && composer.path === path && composer.side === side && composer.line === line) {
      widgets.push(buildComposerElement(item, path, side, line, composer.content));
    }
  }
  if (widgets.length) {
    tbody.appendChild(el("tr", { className: "thread-row" }, el("td", { colspan: colSpan }, ...widgets)));
  }
}

function renderUnifiedTable(item, file, threadMap) {
  const tbody = el("tbody");
  for (const hunk of file.hunks || []) {
    tbody.appendChild(
      el("tr", { className: "diff-hunk-row" }, el("td", { colspan: "4" }, hunk.header))
    );
    for (const line of hunk.lines) {
      const side = line.type === "del" ? "old" : "new";
      const lineNumber = side === "old" ? line.old_line : line.new_line;
      const prefix = line.type === "add" ? "+" : line.type === "del" ? "-" : " ";
      const rowClass =
        line.type === "add" ? "line-add" : line.type === "del" ? "line-del" : "";
      const actionCell = el("td", { className: "line-action" });
      if (lineNumber !== null && line.type !== "meta") {
        actionCell.appendChild(
          el(
            "button",
            {
              className: "add-comment-btn",
              title: "Add inline comment",
              onClick: () => openComposerAt(item, file.path, side, lineNumber, line.content),
            },
            "+"
          )
        );
      }

      tbody.appendChild(
        el(
          "tr",
          { className: rowClass },
          el("td", { className: "line-num" }, line.old_line ?? ""),
          el("td", { className: "line-num" }, line.new_line ?? ""),
          actionCell,
          el(
            "td",
            { className: "code-cell" },
            el("span", { className: "line-prefix" }, prefix),
            line.content
          )
        )
      );

      appendThreadRow(tbody, item, file.path, threadMap, [["old", line.old_line], ["new", line.new_line]], 4);
    }
  }
  return diffTable(file, "unified", tbody);
}

function buildSplitRows(lines) {
  const rows = [];
  let i = 0;
  while (i < lines.length) {
    const cur = lines[i];
    if (cur.type === "context" || cur.type === "meta") {
      rows.push({ left: cur, right: cur });
      i += 1;
    } else {
      const dels = [];
      const adds = [];
      while (i < lines.length && lines[i].type === "del") {
        dels.push(lines[i]);
        i += 1;
      }
      while (i < lines.length && lines[i].type === "add") {
        adds.push(lines[i]);
        i += 1;
      }
      const n = Math.max(dels.length, adds.length);
      for (let k = 0; k < n; k += 1) {
        rows.push({ left: dels[k] || null, right: adds[k] || null });
      }
    }
  }
  return rows;
}

function renderSplitTable(item, file, threadMap) {
  const tbody = el("tbody");
  for (const hunk of file.hunks || []) {
    tbody.appendChild(
      el("tr", { className: "diff-hunk-row" }, el("td", { colspan: "6" }, hunk.header))
    );
    const pairs = buildSplitRows(hunk.lines);
    for (const pair of pairs) {
      const left = pair.left;
      const right = pair.right;

      const leftCells = left
        ? [
            el(
              "td",
              { className: `line-num ${left.type === "del" ? "line-del" : ""}` },
              left.old_line ?? ""
            ),
            el(
              "td",
              { className: `line-action ${left.type === "del" ? "line-del" : ""}` },
              left.old_line
                ? el(
                    "button",
                    {
                      className: "add-comment-btn",
                      onClick: () => openComposerAt(item, file.path, "old", left.old_line, left.content),
                    },
                    "+"
                  )
                : null
            ),
            el(
              "td",
              { className: `code-cell ${left.type === "del" ? "line-del" : ""}` },
              left.content
            ),
          ]
        : [
            el("td", { className: "line-num line-empty" }),
            el("td", { className: "line-action line-empty" }),
            el("td", { className: "code-cell line-empty" }),
          ];

      const rightCells = right
        ? [
            el(
              "td",
              { className: `line-num ${right.type === "add" ? "line-add" : ""}` },
              right.new_line ?? ""
            ),
            el(
              "td",
              { className: `line-action ${right.type === "add" ? "line-add" : ""}` },
              right.new_line
                ? el(
                    "button",
                    {
                      className: "add-comment-btn",
                      onClick: () => openComposerAt(item, file.path, "new", right.new_line, right.content),
                    },
                    "+"
                  )
                : null
            ),
            el(
              "td",
              { className: `code-cell ${right.type === "add" ? "line-add" : ""}` },
              right.content
            ),
          ]
        : [
            el("td", { className: "line-num line-empty" }),
            el("td", { className: "line-action line-empty" }),
            el("td", { className: "code-cell line-empty" }),
          ];

      tbody.appendChild(el("tr", {}, ...leftCells, ...rightCells));
      appendThreadRow(tbody, item, file.path, threadMap, [["old", left?.old_line], ["new", right?.new_line]], 6);
    }
  }
  return diffTable(file, "split", tbody);
}

function renderDiff(item) {
  const jumpBar = document.getElementById("file-jump-bar");
  const container = document.getElementById("diff-container");
  jumpBar.innerHTML = "";
  container.innerHTML = "";
  renderEditCheckBanner(item);
  document.querySelectorAll(".review-action-bar button").forEach((button) => {
    button.disabled =
      !state.diffData || !item.branch_exists || item.status === "integrated" || item.status === "merged";
  });

  if (state.diffData && state.diffData.new_sha !== item.live_head_sha) {
    const approve = document.getElementById("btn-approve");
    approve.disabled = true;
    approve.title = "Select the current branch head in Range to approve.";
  } else {
    document.getElementById("btn-approve").removeAttribute("title");
  }
  if (!state.diffData) {
    document.getElementById("viewed-progress").textContent = "";
    container.appendChild(el("div", { className: "muted" }, state.diffError || "Diff を読み込み中..."));
    return;
  }

  const files = state.diffData.files || [];
  let viewedCount = 0;
  for (const file of files) {
    if (isFileViewed(item, file.path)) viewedCount += 1;
  }
  document.getElementById("viewed-progress").textContent = `${viewedCount} / ${files.length} viewed`;

  if (files.length === 0) {
    container.appendChild(el("div", { className: "card empty-state" }, "この範囲に差分はありません。"));
  }

  const { map: threadMap, outside } = groupThreads(item, files);

  files.forEach((file, index) => {
    const fileId = `diff-file-${index}`;
    const viewed = isFileViewed(item, file.path);
    jumpBar.appendChild(
      el(
        "a",
        {
          href: `#${fileId}`,
          className: `file-jump-chip${viewed ? " viewed" : ""}`,
        },
        file.path,
        renderDiffstat(file)
      )
    );

    const key = viewedKey(item, file.path);
    const collapsed = Boolean(state.collapsedFiles[key]);
    const toggleBtn = el(
      "button",
      {
        className: "btn btn-ghost btn-sm",
        onClick: () => {
          state.collapsedFiles[key] = !collapsed;
          renderDiff(item);
        },
      },
      collapsed ? "▸" : "▾"
    );

    const viewedCheckbox = el("input", {
      type: "checkbox",
      onChange: (ev) => {
        setFileViewed(item, file.path, ev.target.checked);
        renderDiff(item);
      },
    });
    viewedCheckbox.checked = viewed;

    let editBtn = null;
    if (
      !file.is_binary &&
      file.status !== "deleted" &&
      item.branch_exists &&
      item.status !== "integrated" &&
      item.status !== "merged"
    ) {
      const headMismatch = state.diffData.new_sha !== item.live_head_sha;
      editBtn = el(
        "button",
        {
          className: "btn btn-secondary btn-sm edit-file-btn",
          type: "button",
          title: headMismatch ? "Select the current branch head in Range to edit." : "Edit file directly",
          onClick: () => openFileEditor(item, file.path),
        },
        "Edit"
      );
      editBtn.disabled = headMismatch;
    }

    const header = el(
      "div",
      { className: "diff-file-header" },
      el(
        "div",
        { className: "diff-file-left" },
        toggleBtn,
        el("span", { className: `file-status file-status-${file.status}` }, file.status),
        el(
          "span",
          { className: "diff-file-path" },
          file.status === "renamed" ? `${file.old_path} → ${file.new_path}` : file.path
        )
      ),
      el(
        "div",
        { className: "diff-file-right" },
        editBtn,
        renderDiffstat(file),
        el("label", { className: "checkbox-inline" }, viewedCheckbox, "Viewed")
      )
    );

    let body = null;
    if (!collapsed) {
      if (file.is_binary) {
        body = el("div", { className: "empty-state" }, "Binary file");
      } else {
        const table =
          state.diffMode === "split"
            ? renderSplitTable(item, file, threadMap)
            : renderUnifiedTable(item, file, threadMap);
        body = el("div", { className: "diff-table-wrap" }, table);
      }
    }

    container.appendChild(el("article", { id: fileId, className: "diff-file" }, header, body));
  });
  if (outside.length) {
    container.appendChild(el("section", {}, el("h3", {}, "Threads outside this diff"),
      ...outside.map((thread) => buildThreadElement(item, thread))));
  }
}

let diffRequest = 0;
async function loadDiffForSelected() {
  const request = ++diffRequest;
  const item = getSelectedItem();
  state.diffData = null;
  state.diffError = "";
  state.openComposer = null;
  if (!item) return;
  renderDiff(item);

  const params = new URLSearchParams({ branch: item.branch, to: item.live_head_sha });
  if (state.diffRange === "since_review" && item.has_updates_since_review) {
    params.set("mode", "range");
    params.set("from", item.last_reviewed_sha);
  } else if (state.diffRange.startsWith("commit:")) {
    params.set("mode", "commit");
    params.set("to", state.diffRange.slice("commit:".length));
  } else {
    params.set("mode", "base");
  }

  try {
    const data = await apiGet(`/api/diff?${params.toString()}`);
    if (request !== diffRequest) return;
    state.diffData = data;
  } catch (err) {
    if (request !== diffRequest) return;
    state.diffError = err.message;
  }
  renderDiff(item);
}

async function selectBranch(branch) {
  const reviewBody = document.getElementById("review-body");
  if (branch !== state.selectedBranch) {
    if (state.activeEditor && state.activeEditor.branch !== branch) {
      closeFileEditor(true);
    }
    if (state.selectedBranch) state.reviewDrafts.set(state.selectedBranch, reviewBody.value);
    state.selectedBranch = branch;
    reviewBody.value = state.reviewDrafts.get(branch) || "";
    state.diffRange = "base";
    state.reopenReviewForm = false;
  }
  renderSidebar();
  const item = getSelectedItem();
  if (!item) {
    ++diffRequest;
    state.diffData = null;
    closeFileEditor(true);
    renderEditCheckBanner(null);
    document.getElementById("empty-state").classList.remove("hidden");
    document.getElementById("review-workspace").classList.add("hidden");
    return;
  }
  document.getElementById("empty-state").classList.add("hidden");
  document.getElementById("review-workspace").classList.remove("hidden");
  renderPrHeader(item);
  await loadDiffForSelected();
}

function buildBatchCard(batch) {
  const isMerged = Boolean(batch.is_merged);
  const metaParts = [`${(batch.entries || []).length} issue(s)`];
  if (!isMerged) {
    metaParts.push(`${(batch.commits || []).length} commit(s)`);
  }
  if (batch.pr_url) metaParts.push("PR created");
  if (isMerged) metaParts.push("Merged");

  const actionRow = !isMerged
    ? el(
        "div",
        { className: "batch-card-actions" },
        el("span", { className: "muted" }, metaParts.join(" · ")),
        el(
          "button",
          {
            className: "btn btn-secondary btn-sm",
            onClick: async (ev) => {
              ev.stopPropagation();
              const deleteBranch = Boolean(document.getElementById("sync-delete-branches")?.checked);
              try {
                const res = await apiPost("/api/batches/mark-merged", {
                  batch: batch.branch,
                  delete_branch: deleteBranch,
                });
                const suffix = res.deleted_branch ? "（ローカルブランチ削除済み）" : "";
                showToast(`${batch.branch} をマージ済みにしました${suffix}`);
                await refreshAll();
              } catch (err) {
                showToast(err.message, true);
              }
            },
          },
          "マージ済みにする"
        )
      )
    : el("div", { className: "muted" }, metaParts.join(" · "));

  return el(
    "div",
    {
      className: `batch-card${batch.branch === state.selectedBatch ? " selected" : ""}${isMerged ? " merged" : ""}`,
      onClick: () => selectBatch(batch.branch),
    },
    el(
      "div",
      { className: "queue-card-top" },
      el("strong", {}, batch.branch),
      isMerged ? renderStatusBadge("merged") : renderDiffstat(batch.stats || {})
    ),
    actionRow,
    el(
      "ul",
      { className: "batch-entries" },
      ...(batch.entries || []).map((entry) =>
        el(
          "li",
          {},
          `${entry.short_sha || ""} ${entry.title}${entry.issue !== null && entry.issue !== undefined ? ` (#${entry.issue})` : ""}`
        )
      )
    )
  );
}

function renderBatchView() {
  if (!state.overview) return;
  const approved = state.overview.items.filter((i) => i.status === "approved" && i.branch_exists);
  const approvedList = document.getElementById("approved-list");
  approvedList.innerHTML = "";

  const integrateAllBtn = document.getElementById("btn-integrate-all");
  integrateAllBtn.disabled = approved.length === 0;

  if (approved.length === 0) {
    approvedList.appendChild(el("div", { className: "muted" }, "統合待ちの Approved ブランチはありません。"));
  } else {
    for (const item of approved) {
      approvedList.appendChild(
        el(
          "div",
          { className: "approved-row" },
          el(
            "div",
            {},
            el("strong", {}, item.title || item.branch),
            el(
              "div",
              { className: "queue-card-branch" },
              `${item.branch}${item.issue !== null && item.issue !== undefined ? ` (#${item.issue})` : ""}`
            )
          ),
          el(
            "button",
            {
              className: "btn btn-primary btn-sm",
              onClick: async () => {
                const batchName = resolveTargetBatchName();
                if (!batchName) return;
                await integrateSingle(
                  item.branch,
                  batchName,
                  state.deleteBranchOnIntegrate
                );
              },
            },
            "統合"
          )
        )
      );
    }
  }

  const batches = state.overview.batches || [];
  const openBatches = batches.filter((b) => !b.is_merged);
  const mergedBatches = batches.filter((b) => b.is_merged);

  const batchList = document.getElementById("batch-list");
  batchList.innerHTML = "";
  if (openBatches.length === 0) {
    batchList.appendChild(el("div", { className: "muted" }, "未マージのローカルバッチはありません。"));
  } else {
    for (const batch of openBatches) {
      batchList.appendChild(buildBatchCard(batch));
    }
  }

  const mergedSection = document.getElementById("merged-batches-section");
  const mergedList = document.getElementById("merged-batch-list");
  document.getElementById("merged-batches-count").textContent = String(mergedBatches.length);
  mergedList.innerHTML = "";
  mergedSection.classList.toggle("hidden", mergedBatches.length === 0);
  for (const batch of mergedBatches) {
    mergedList.appendChild(buildBatchCard(batch));
  }
}

async function selectBatch(batchBranch) {
  state.selectedBatch = batchBranch;
  state.batchDraft = null;
  document.getElementById("batch-draft-view").classList.add("hidden");
  document.getElementById("batch-draft-empty").classList.remove("hidden");
  renderBatchView();
  try {
    const draft = await apiGet(`/api/batch/draft?batch=${encodeURIComponent(batchBranch)}`);
    if (state.selectedBatch !== batchBranch) return;
    state.batchDraft = draft;
    document.getElementById("batch-draft-empty").classList.add("hidden");
    document.getElementById("batch-draft-view").classList.remove("hidden");
    document.getElementById("draft-title").textContent = draft.title;
    document.getElementById("draft-body").textContent = draft.body;
    document.getElementById("draft-cmd").textContent = [
      `python3 scripts/codex_self_check.py`,
      `python3 scripts/local_review.py prepare-pr --batch ${batchBranch} --create`,
    ].join("\n");
  } catch (err) {
    showToast(err.message, true);
  }
}

async function integrateSingle(branch, batchName, deleteBranch) {
  if (!batchName) return;
  try {
    const res = await apiPost("/api/integrate", {
      branch,
      batch: batchName,
      delete_branch: deleteBranch,
    });
    state.batchTargetMode = "existing";
    state.batchTargetExisting = res.batch;
    state.batchTargetNewEdited = false;
    const suffix = deleteBranch && !res.deleted_branch
      ? "（元ブランチは worktree 使用中のため残しました）"
      : res.deleted_branch
        ? "（元ブランチ削除済み）"
        : "";
    showToast(`${branch} を ${res.batch} (${res.short_sha}) へ統合しました${suffix}`);
    await refreshAll(branch);
    await selectBatch(res.batch);
  } catch (err) {
    showToast(err.message, true);
  }
}

async function submitReviewAction(action) {
  const item = getSelectedItem();
  if (!item) return;
  const bodyEl = document.getElementById("review-body");
  try {
    await apiPost("/api/review", {
      branch: item.branch,
      action,
      expected_head: item.live_head_sha,
      body: bodyEl.value,
      author: "human",
    });
    state.reviewDrafts.delete(item.branch);
    if (state.selectedBranch === item.branch) bodyEl.value = "";
    if (action === "approve") {
      state.reopenReviewForm = false;
      showToast(`${item.branch} を承認しました。統合先バッチを選んで統合できます`);
    } else {
      showToast(`Marked ${item.branch} as ${action}`);
    }
    await refreshAll(item.branch);
  } catch (err) {
    showToast(err.message, true);
  }
}

let overviewRequest = 0;
async function refreshAll(preferBranch = null, background = false) {
  const request = ++overviewRequest;
  const selection = state.selectedBranch;
  const overview = await apiGet("/api/overview");
  if (request !== overviewRequest || (background && editingReview())) return;
  if (background && state.diffData && JSON.stringify(state.overview) === JSON.stringify(overview)) return;
  state.overview = overview;
  updateTopbar();

  const preferred = selection === state.selectedBranch && preferBranch ? preferBranch : state.selectedBranch;
  const firstActive = overview.items.find((item) => ACTIVE_STATUSES.has(item.status));
  const branch = overview.items.some((item) => item.branch === preferred)
    ? preferred
    : (firstActive || overview.items[0])?.branch;
  await selectBranch(branch || null);
  renderBatchView();
  const openBatches = (state.overview.batches || []).filter((b) => !b.is_merged);
  if (state.selectedBatch && state.overview.batches.some((b) => b.branch === state.selectedBatch)) {
    await selectBatch(state.selectedBatch);
  } else if (openBatches.length > 0 && state.activeTab === "batch") {
    await selectBatch(openBatches[0].branch);
  }
}

function switchTab(tab) {
  state.activeTab = tab;
  document.getElementById("tab-review").classList.toggle("active", tab === "review");
  document.getElementById("tab-batch").classList.toggle("active", tab === "batch");
  document.getElementById("view-review").classList.toggle("hidden", tab !== "review");
  document.getElementById("view-batch").classList.toggle("hidden", tab !== "batch");
  if (tab === "batch" && state.overview && state.overview.batches.length > 0 && !state.selectedBatch) {
    selectBatch(state.overview.batches[0].branch);
  }
}

function editingReview() {
  return Boolean(
    state.activeEditor ||
    state.openComposer ||
    document.querySelector(".thread-reply-form:not(.hidden)") ||
    document.activeElement?.matches("textarea, select, input:not([type=checkbox])")
  );
}

function bindBatchTargetEvents(selectId, inputId, checkboxId) {
  document.getElementById(selectId).addEventListener("change", (ev) => {
    if (ev.target.value === NEW_BATCH_OPTION) {
      state.batchTargetMode = "new";
      renderBatchTargetControls();
      document.getElementById(inputId).focus();
    } else {
      state.batchTargetMode = "existing";
      state.batchTargetExisting = ev.target.value;
      renderBatchTargetControls();
    }
  });
  document.getElementById(inputId).addEventListener("input", (ev) => {
    state.batchTargetNew = ev.target.value;
    state.batchTargetNewEdited = true;
    const otherId = inputId === "integrate-batch-input" ? "batch-target-input" : "integrate-batch-input";
    const other = document.getElementById(otherId);
    if (other && other.value !== state.batchTargetNew) {
      other.value = state.batchTargetNew;
    }
  });
  document.getElementById(checkboxId).addEventListener("change", (ev) => {
    state.deleteBranchOnIntegrate = ev.target.checked;
    renderBatchTargetControls();
  });
}

function bindEvents() {
  document.getElementById("tab-review").addEventListener("click", () => switchTab("review"));
  document.getElementById("tab-batch").addEventListener("click", () => switchTab("batch"));
  document.getElementById("refresh-btn").addEventListener("click", () => refreshAll().catch((err) => showToast(err.message, true)));

  document.querySelectorAll("#status-filters .filter-pill").forEach((btn) => {
    btn.addEventListener("click", () => {
      state.statusFilter = btn.dataset.status;
      renderSidebar();
    });
  });

  document.querySelectorAll("#diff-mode-toggle .seg-btn").forEach((btn) => {
    btn.classList.toggle("active", btn.dataset.mode === state.diffMode);
    btn.addEventListener("click", () => {
      state.diffMode = btn.dataset.mode;
      localStorage.setItem("local_review_diff_mode", state.diffMode);
      document.querySelectorAll("#diff-mode-toggle .seg-btn").forEach((b) => {
        b.classList.toggle("active", b.dataset.mode === state.diffMode);
      });
      const item = getSelectedItem();
      if (item) renderDiff(item);
    });
  });

  document.getElementById("diff-range-select").addEventListener("change", async (ev) => {
    state.diffRange = ev.target.value;
    await loadDiffForSelected();
  });

  document.getElementById("show-resolved").addEventListener("change", (ev) => {
    state.showResolved = ev.target.checked;
    const item = getSelectedItem();
    if (item) renderDiff(item);
  });

  document.getElementById("btn-expand-all").addEventListener("click", () => {
    state.collapsedFiles = {};
    const item = getSelectedItem();
    if (item) renderDiff(item);
  });

  document.getElementById("btn-collapse-all").addEventListener("click", () => {
    const item = getSelectedItem();
    if (!item || !state.diffData) return;
    for (const file of state.diffData.files || []) {
      state.collapsedFiles[viewedKey(item, file.path)] = true;
    }
    renderDiff(item);
  });

  document.getElementById("btn-approve").addEventListener("click", () => submitReviewAction("approve"));
  document.getElementById("btn-request-changes").addEventListener("click", () => submitReviewAction("request_changes"));
  document.getElementById("btn-comment").addEventListener("click", () => submitReviewAction("comment"));
  document.getElementById("btn-reject").addEventListener("click", () => submitReviewAction("reject"));
  document.getElementById("btn-pass-doc-review").addEventListener("click", () => submitReviewAction("pass_doc_review"));

  document.getElementById("btn-sync-batches").addEventListener("click", async () => {
    const deleteBranches = Boolean(document.getElementById("sync-delete-branches")?.checked);
    try {
      const res = await apiPost("/api/batches/sync", { delete_branches: deleteBranches });
      const count = (res.synced_batches || []).length;
      if (count === 0) {
        showToast("新しくマージ済みになったバッチはありません");
      } else {
        showToast(`${count} 件のバッチをマージ済みに同期しました`);
      }
      await refreshAll();
    } catch (err) {
      showToast(err.message, true);
    }
  });

  bindBatchTargetEvents("integrate-batch-select", "integrate-batch-input", "integrate-delete-branch");
  bindBatchTargetEvents("batch-target-select", "batch-target-input", "batch-delete-branches");

  document.getElementById("btn-reopen-review").addEventListener("click", () => {
    state.reopenReviewForm = !state.reopenReviewForm;
    const item = getSelectedItem();
    if (item) renderPrHeader(item);
  });

  document.getElementById("btn-go-batch-ship").addEventListener("click", () => {
    const item = getSelectedItem();
    switchTab("batch");
    if (item?.batch) {
      selectBatch(item.batch);
    }
  });

  document.getElementById("btn-next-ready").addEventListener("click", () => {
    const next = (state.overview?.items || []).find((entry) => entry.status === "ready");
    if (!next) return;
    if (state.statusFilter !== "active" && state.statusFilter !== "ready") {
      state.statusFilter = "ready";
    }
    selectBranch(next.branch);
  });

  document.getElementById("btn-integrate-now").addEventListener("click", async () => {
    const item = getSelectedItem();
    if (!item) return;
    const batchName = resolveTargetBatchName();
    if (!batchName) return;
    await integrateSingle(item.branch, batchName, state.deleteBranchOnIntegrate);
  });

  document.getElementById("btn-integrate-all").addEventListener("click", async () => {
    if (!state.overview) return;
    const batchName = resolveTargetBatchName();
    if (!batchName) return;
    const deleteBranch = state.deleteBranchOnIntegrate;
    const approved = state.overview.items.filter((i) => i.status === "approved" && i.branch_exists);
    let lastBatch = batchName;
    let integratedCount = 0;
    for (const item of approved) {
      try {
        const res = await apiPost("/api/integrate", {
          branch: item.branch,
          batch: lastBatch,
          delete_branch: deleteBranch,
        });
        lastBatch = res.batch;
        integratedCount += 1;
      } catch (err) {
        showToast(`${item.branch}: ${err.message}`, true);
        break;
      }
    }
    if (integratedCount > 0 && lastBatch) {
      state.batchTargetMode = "existing";
      state.batchTargetExisting = lastBatch;
      state.batchTargetNewEdited = false;
      showToast(`${integratedCount} 件を ${lastBatch} へ統合しました`);
    }
    await refreshAll();
    if (lastBatch) await selectBatch(lastBatch);
  });

  document.getElementById("btn-copy-pr-body").addEventListener("click", async () => {
    if (!state.batchDraft) return;
    try {
      await navigator.clipboard.writeText(state.batchDraft.body);
      showToast("Copied PR body");
    } catch {
      showToast("Clipboard copy failed", true);
    }
  });

  document.getElementById("editor-close-btn").addEventListener("click", () => closeFileEditor(false));
  document.getElementById("editor-cancel-btn").addEventListener("click", () => closeFileEditor(false));
  document.getElementById("file-editor-modal").addEventListener("click", (ev) => {
    if (ev.target.id === "file-editor-modal") closeFileEditor(false);
  });
  document.getElementById("editor-tab-edit").addEventListener("click", () => switchEditorMode("edit"));
  document.getElementById("editor-tab-preview").addEventListener("click", () => switchEditorMode("preview"));
  document.getElementById("editor-textarea").addEventListener("input", (ev) => {
    if (state.activeEditor) state.activeEditor.draft = ev.target.value;
  });
  document.getElementById("editor-commit-btn").addEventListener("click", () => commitFileEditor());
  document.addEventListener("keydown", (ev) => {
    if (!state.activeEditor) return;
    if (ev.key === "Escape") {
      ev.preventDefault();
      closeFileEditor(false);
    } else if (
      (ev.ctrlKey || ev.metaKey) &&
      ev.key === "Enter" &&
      (ev.target?.id === "editor-textarea" || ev.target?.id === "editor-commit-msg")
    ) {
      ev.preventDefault();
      commitFileEditor();
    }
  });

  setInterval(() => {
    if (!document.getElementById("auto-refresh").checked) return;
    if (editingReview()) return;
    refreshAll(null, true).catch((err) => showToast(err.message, true));
  }, 5000);
}

bindEvents();
refreshAll().catch((err) => showToast(err.message, true));
