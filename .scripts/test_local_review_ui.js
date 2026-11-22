(async () => {
  function check(condition, message) {
    if (!condition) throw new Error(message);
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
    check(!find("#integrate-batch-select").classList.contains("hidden"),
      "existing batch select should show after a batch branch is created");
    check(find("#integrate-batch-select").value === batchName,
      "created batch should become selected existing batch");
    document.body.dataset.reviewTest = "passed";
  } catch (err) {
    document.body.dataset.reviewTest = String(err);
  }
})();
