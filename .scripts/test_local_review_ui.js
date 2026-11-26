(async () => {
  function check(condition, message) {
    if (!condition) throw new Error(message);
  }

  async function waitFor(predicate, message, timeoutMs = 3000) {
    const start = Date.now();
    while (Date.now() - start < timeoutMs) {
      const value = predicate();
      if (value) return value;
      await new Promise((resolve) => setTimeout(resolve, 20));
    }
    throw new Error(message);
  }

  try {
    const find = (selector) => document.querySelector(selector);
    find("#auto-refresh").checked = false;
    await refreshAll();
    for (const mode of ["unified", "split"]) {
      find(`[data-mode="${mode}"]`).click();
      const row = find(".diff-table tr:nth-child(2)");
      const cells = (selector) => Array.from(row.querySelectorAll(selector));
      const width = (node) => node.getBoundingClientRect().width;
      check(cells(".line-num").every((cell) => width(cell) < 50), mode + " line number too wide");
      check(cells(".line-action").every((cell) => width(cell) < 30), mode + " action too wide");
      check(cells(".code-cell").reduce((sum, td) => sum + width(td), 0) > 0.75 * width(row),
        mode + " gutter crowds out code");
    }

    find(".diff-table tr:nth-child(2) .add-comment-btn").click();
    check(find(".comment-form"), "missing composer on old context line");
    const input = find(".comment-form textarea");
    input.value = "old context comment";
    input.dispatchEvent(new Event("input"));
    find('[data-mode="unified"]').click();
    check(find(".comment-form textarea").value === input.value, "draft lost on mode switch");
    await apiPost("/api/threads", {
      branch: state.selectedBranch, path: "lib.cpp", side: "old", line: 1,
      anchor_sha: state.diffData.old_sha, body: input.value,
    });
    await refreshAll();
    check(find(".thread-row .comment-body").textContent === input.value, "missing old-side thread");

    const fetchDiff = apiGet;
    let release;
    apiGet = (url) => new Promise((resolve) => { release = () => resolve({ files: [] }); });
    const pending = loadDiffForSelected();
    apiGet = fetchDiff;
    await loadDiffForSelected();
    release();
    await pending;
    check(find(".diff-table .code-cell"), "late response replaced the selected diff");
    apiGet = async () => { throw new Error("diff unavailable"); };
    await loadDiffForSelected();
    check(!find(".diff-table") && find("#diff-container").textContent.includes("diff unavailable"),
      "failed diff left stale code on screen");
    check(find("#btn-approve").disabled, "review enabled for a failed diff");

    apiGet = fetchDiff;
    await loadDiffForSelected();
    check(find("#integrate-delete-branch").checked, "delete branch should default to checked");
    check(find("#batch-delete-branches").checked, "batch tab delete branch should default to checked");
    check(find("#integrate-batch-select").classList.contains("hidden"),
      "existing batch select should be hidden when no batch exists");
    check(!find("#integrate-batch-input").classList.contains("hidden"),
      "new batch input should be visible when no batch exists");

    find(".edit-file-btn").click();
    await waitFor(
      () => !find("#file-editor-modal").classList.contains("hidden"),
      "file editor modal did not open"
    );
    const editorInput = find("#editor-textarea");
    check(editorInput.value.includes("return a - b;"), "editor missing file content");
    editorInput.value = editorInput.value.replace("a - b", "a * b");
    editorInput.dispatchEvent(new Event("input"));
    find("#editor-tab-preview").click();
    await waitFor(
      () => find("#editor-preview-pane .diff-table"),
      "editor preview diff did not render"
    );
    check(find("#editor-preview-pane").textContent.includes("a * b"), "preview missing updated line");
    find("#editor-commit-btn").click();
    await waitFor(
      () => find("#file-editor-modal").classList.contains("hidden") &&
        find("#diff-container").textContent.includes("a * b"),
      "direct file edit did not commit and refresh diff"
    );
    check(!find("#edit-check-banner").classList.contains("hidden"), "self check banner should be visible");

    find(".diff-table .line-add .add-comment-btn").click();
    await waitFor(() => find(".comment-form"), "new-side composer did not open");
    check(find(".composer-apply-btn").classList.contains("hidden"), "apply button should stay hidden without suggestion");
    const insertBtn = Array.from(find(".comment-form").querySelectorAll("button"))
      .find((btn) => btn.textContent.includes("Insert suggestion"));
    insertBtn.click();
    check(!find(".composer-apply-btn").classList.contains("hidden"), "apply button should show with suggestion");
    const composerInput = find(".comment-form textarea");
    composerInput.value = composerInput.value.replace("a * b", "a + b + 1");
    composerInput.dispatchEvent(new Event("input"));
    find(".composer-apply-btn").click();
    await waitFor(
      () => !find(".comment-form") && find("#diff-container").textContent.includes("a + b + 1"),
      "composer suggestion apply did not update diff"
    );

    await apiPost("/api/threads", {
      branch: state.selectedBranch,
      path: "lib.cpp",
      side: "new",
      line: 2,
      anchor_sha: state.diffData.new_sha,
      body: "use + 2\n```suggestion\n    return a + b + 2;\n```",
    });
    await refreshAll();
    const applyThreadBtn = await waitFor(
      () => find(".apply-suggestion-btn"),
      "thread apply suggestion button did not render"
    );
    applyThreadBtn.click();
    await waitFor(
      () => find("#diff-container").textContent.includes("a + b + 2") && !find(".apply-suggestion-btn"),
      "thread suggestion apply did not commit and resolve thread"
    );

    await submitReviewAction("approve");
    check(!find("#integrate-bar").classList.contains("hidden"), "integrate bar should show after approve");
    check(find("#review-action-bar").classList.contains("hidden"),
      "review action bar should collapse after approve");
    find("#btn-reopen-review").click();
    check(!find("#review-action-bar").classList.contains("hidden"),
      "reopen review button should restore review action bar");

    const batchName = resolveTargetBatchName();
    await integrateSingle(state.selectedBranch, batchName, state.deleteBranchOnIntegrate);
    check(!find("#integrated-bar").classList.contains("hidden"), "integrated bar should show after integrate");
    check(find("#integrate-bar").classList.contains("hidden"), "integrate bar should hide after integrate");
    check(!find("#edit-file-btn") && !find(".edit-file-btn"), "edit button should hide after integrate");
    check(!find("#integrate-batch-select").classList.contains("hidden"),
      "existing batch select should show after a batch branch is created");
    check(find("#integrate-batch-select").value === batchName,
      "created batch should become selected existing batch");
    document.body.dataset.reviewTest = "passed";
  } catch (err) {
    document.body.dataset.reviewTest = String(err);
  }
})();
