import json
import os
import shutil
import subprocess
import tempfile
import threading
import unittest
import urllib.request
from pathlib import Path
from unittest.mock import patch

import local_review_impl as lr


def git(cwd: Path, *args: str) -> str:
    proc = subprocess.run(
        ["git", *args],
        cwd=str(cwd),
        capture_output=True,
        text=True,
        check=True,
    )
    return proc.stdout.strip()


class LocalReviewWorkflowTest(unittest.TestCase):
    def setUp(self) -> None:
        self.tmp = tempfile.TemporaryDirectory()
        self.root = Path(self.tmp.name) / "repo"
        self.root.mkdir()
        git(self.root, "init", "-b", "master")
        self.enterContext(patch.dict(os.environ))
        os.environ.pop("LOCAL_REVIEW_DIR", None)
        git(self.root, "config", "user.name", "Tester")
        git(self.root, "config", "user.email", "tester@example.com")
        (self.root / "lib.cpp").write_text("int add(int a, int b) {\n    return a + b;\n}\n", encoding="utf-8")
        git(self.root, "add", "lib.cpp")
        git(self.root, "commit", "-m", "Initial commit")

    def tearDown(self) -> None:
        self.tmp.cleanup()

    def test_end_to_end_worktree_review_and_batch_integration(self) -> None:
        wt_a = Path(self.tmp.name) / "wt_a"
        wt_b = Path(self.tmp.name) / "wt_b"
        git(self.root, "worktree", "add", "-b", "issue/101-mul", str(wt_a), "master")
        git(self.root, "worktree", "add", "-b", "issue/102-sub", str(wt_b), "master")

        (wt_a / "mul.cpp").write_text("int mul(int a, int b) {\n    return a * b;\n}\n", encoding="utf-8")
        git(wt_a, "add", "mul.cpp")
        git(wt_a, "commit", "-m", "Add mul helper")

        submitted_a = lr.submit_branch(
            branch="issue/101-mul",
            base="master",
            summary="乗算ヘルパを追加",
            verification=["python3 scripts/codex_self_check.py: pass"],
            repo_dir=wt_a,
        )
        self.assertEqual(submitted_a["issue"], 101)
        self.assertEqual(submitted_a["status"], "ready")

        (wt_b / "sub.cpp").write_text("int sub(int a, int b) {\n    return a - b;\n}\n", encoding="utf-8")
        git(wt_b, "add", "sub.cpp")
        git(wt_b, "commit", "-m", "Add sub helper")
        submitted_b = lr.submit_branch(
            branch="issue/102-sub",
            base="master",
            summary="減算ヘルパを追加",
            repo_dir=wt_b,
        )
        self.assertEqual(submitted_b["issue"], 102)

        overview = lr.overview_payload(base="master", repo_dir=self.root)
        self.assertEqual({item["branch"] for item in overview["items"]}, {"issue/101-mul", "issue/102-sub"})

        thread = lr.add_inline_comment(
            branch="issue/101-mul",
            path="mul.cpp",
            line=2,
            side="new",
            body="long long にしてください\n```suggestion\n    return 1LL * a * b;\n```",
            repo_dir=self.root,
        )
        lr.record_review(
            branch="issue/101-mul",
            action="request_changes",
            body="オーバーフロー対策をお願いします",
            repo_dir=self.root,
        )

        report = lr.get_comments_report("issue/101-mul", unresolved_only=True, repo_dir=wt_a)
        self.assertEqual(report["status"], "changes_requested")
        self.assertEqual(len(report["threads"]), 1)
        self.assertEqual(report["threads"][0]["id"], thread["id"])

        (wt_a / "mul.cpp").write_text("long long mul(int a, int b) {\n    return 1LL * a * b;\n}\n", encoding="utf-8")
        git(wt_a, "add", "mul.cpp")
        git(wt_a, "commit", "-m", "Use long long in mul")
        fix_sha = lr.short_sha(lr.resolve_commit("issue/101-mul", wt_a))

        lr.reply_to_thread(
            branch="issue/101-mul",
            thread_id=thread["id"],
            body="long long に変更しました",
            commit=fix_sha,
            repo_dir=wt_a,
        )
        resubmitted = lr.submit_branch(branch="issue/101-mul", base="master", repo_dir=wt_a)
        self.assertEqual(resubmitted["status"], "ready")
        self.assertTrue(resubmitted["has_updates_since_review"])

        since_diff = lr.get_diff_payload(
            branch="issue/101-mul",
            base="master",
            mode="range",
            from_sha=resubmitted["last_reviewed_sha"],
            to_sha=resubmitted["live_head_sha"],
            repo_dir=self.root,
        )
        self.assertEqual(len(since_diff["files"]), 1)
        self.assertEqual(since_diff["files"][0]["path"], "mul.cpp")

        lr.set_thread_resolved("issue/101-mul", thread["id"], True, repo_dir=self.root)
        lr.record_review("issue/101-mul", action="approve", repo_dir=self.root)
        lr.record_review("issue/102-sub", action="approve", repo_dir=self.root)

        res_a = lr.integrate_branch("issue/101-mul", batch_branch="batch/test", repo_dir=self.root)
        res_b = lr.integrate_branch("issue/102-sub", batch_branch="batch/test", repo_dir=self.root)
        self.assertEqual(res_a["batch"], "batch/test")
        self.assertEqual(res_b["batch"], "batch/test")

        batch_commits = lr.branch_commits("master", "batch/test", self.root)
        self.assertEqual(len(batch_commits), 2)
        msg_first = git(self.root, "log", "-1", "--format=%B", batch_commits[0]["sha"])
        self.assertIn("Closes #101", msg_first)

        draft = lr.build_batch_pr_draft("batch/test", repo_dir=self.root)
        self.assertIn("Closes #101", draft["body"])
        self.assertIn("Closes #102", draft["body"])
        self.assertIn("Rebase and merge", draft["body"])

        git(self.root, "worktree", "remove", "--force", str(wt_a))
        git(self.root, "worktree", "remove", "--force", str(wt_b))

    def test_integrate_rejects_unapproved_and_conflict(self) -> None:
        git(self.root, "checkout", "-b", "issue/201-a")
        (self.root / "lib.cpp").write_text("int add(int a, int b) {\n    return a + b + 1;\n}\n", encoding="utf-8")
        git(self.root, "add", "lib.cpp")
        git(self.root, "commit", "-m", "Change add +1")
        lr.submit_branch("issue/201-a", base="master", repo_dir=self.root)

        with self.assertRaises(lr.LocalReviewError):
            lr.integrate_branch("issue/201-a", batch_branch="batch/conflict", repo_dir=self.root)

        lr.record_review("issue/201-a", action="approve", repo_dir=self.root)
        lr.integrate_branch("issue/201-a", batch_branch="batch/conflict", repo_dir=self.root)

        git(self.root, "checkout", "-b", "issue/202-b", "master")
        (self.root / "lib.cpp").write_text("int add(int a, int b) {\n    return a + b + 2;\n}\n", encoding="utf-8")
        git(self.root, "add", "lib.cpp")
        git(self.root, "commit", "-m", "Change add +2")
        lr.submit_branch("issue/202-b", base="master", repo_dir=self.root)
        lr.record_review("issue/202-b", action="approve", repo_dir=self.root)

        with self.assertRaises(lr.LocalReviewError) as ctx:
            lr.integrate_branch("issue/202-b", batch_branch="batch/conflict", repo_dir=self.root)
        self.assertIn("merge conflict", str(ctx.exception))

    def test_catalog_conflict_preserves_independent_entries(self) -> None:
        catalog = self.root / "meta/doc_titles.yml"
        catalog.parent.mkdir()
        catalog.write_text('lib.cpp: "library"\n')
        script = self.root / "scripts/sync_doc_titles.py"
        script.parent.mkdir()
        script.write_text("pass\n")
        git(self.root, "add", ".")
        git(self.root, "commit", "-m", "catalog")
        for number in [1, 2, 3]:
            branch = f"issue/{number}-title"
            git(self.root, "switch", "-c", branch, "master")
            key = "a.cpp" if number != 2 else "b.cpp"
            with catalog.open("a") as stream:
                stream.write(f'{key}: "title {number}"\n')
            git(self.root, "commit", "-am", "title")
            lr.submit_branch(branch, repo_dir=self.root)
            lr.record_review(branch, "approve", repo_dir=self.root)
            if number == 3:
                with self.assertRaisesRegex(lr.LocalReviewError, "merge conflict"):
                    lr.integrate_branch(branch, "batch/titles", repo_dir=self.root)
            else:
                lr.integrate_branch(branch, "batch/titles", repo_dir=self.root)
        self.assertEqual(git(self.root, "show", "batch/titles:meta/doc_titles.yml").splitlines(),
                         ['lib.cpp: "library"', 'a.cpp: "title 1"', 'b.cpp: "title 2"'])

    def test_resubmit_and_integration_keep_custom_base(self) -> None:
        git(self.root, "switch", "-c", "release")
        (self.root / "base-only").touch()
        git(self.root, "add", "base-only")
        git(self.root, "commit", "-m", "release base")
        git(self.root, "switch", "-c", "issue/400-release")
        (self.root / "feature").touch()
        git(self.root, "add", "feature")
        git(self.root, "commit", "-m", "feature")
        branch = "issue/400-release"
        lr.submit_branch(branch, base="release", repo_dir=self.root)
        self.assertEqual(lr.submit_branch(branch, repo_dir=self.root)["base"], "release")
        lr.record_review(branch, "approve", repo_dir=self.root)
        batch_wt = Path(self.tmp.name) / "checked-out-batch"
        git(self.root, "worktree", "add", "-b", "batch/release", str(batch_wt), "release")
        scratch = batch_wt / "local-note"
        scratch.write_text("keep me")
        with self.assertRaisesRegex(lr.LocalReviewError, "local changes"):
            lr.integrate_branch(branch, "batch/release", repo_dir=self.root)
        self.assertEqual(scratch.read_text(), "keep me")
        self.assertEqual(git(batch_wt, "rev-parse", "HEAD"), git(self.root, "rev-parse", "release"))
        scratch.unlink()
        lr.integrate_branch(branch, "batch/release", repo_dir=self.root)
        self.assertTrue((batch_wt / "feature").exists())
        self.assertEqual(lr.build_batch_pr_draft("batch/release", repo_dir=self.root)["base"], "release")
        self.assertEqual(git(self.root, "rev-parse", "batch/release^"), git(self.root, "rev-parse", "release"))

    def test_patch_keeps_paths_content_and_line_numbers(self) -> None:
        old = 'old "名前".txt'
        new = "sub dir/新しい名前.txt"
        prefix = "".join(f"line {i}\n" for i in range(1000))
        (self.root / old).write_text(prefix + "-- a/not-a-header\n")
        (self.root / "two words.bin").write_bytes(b"\x00bytes")
        git(self.root, "add", ".")
        git(self.root, "commit", "-m", "base files")
        git(self.root, "switch", "-c", "issue/401-patch")
        (self.root / "sub dir").mkdir()
        git(self.root, "mv", old, new)
        (self.root / new).write_text(prefix + "++ b/not-a-header\nparagraph\u2028still one line\n")
        (self.root / "two words.bin").unlink()
        (self.root / "empty name").touch()
        git(self.root, "add", "-A")
        git(self.root, "commit", "-m", "rename and edit")
        diff = lr.get_diff_payload("issue/401-patch", "master", repo_dir=self.root)
        files = {f["path"]: f for f in diff["files"]}
        self.assertEqual(set(files), {new, "two words.bin", "empty name"})
        self.assertTrue(files["two words.bin"]["is_binary"])
        self.assertEqual(files["two words.bin"]["status"], "deleted")
        self.assertEqual(files["empty name"]["status"], "added")
        self.assertEqual((files[new]["status"], files[new]["old_path"]), ("renamed", old))
        self.assertEqual(diff["stats"], {"files": 3, "additions": 2, "deletions": 1})
        lines = files[new]["hunks"][0]["lines"][-3:]
        self.assertEqual([(row["content"], row["old_line"], row["new_line"]) for row in lines], [
            ("-- a/not-a-header", 1001, None), ("++ b/not-a-header", None, 1001),
            ("paragraph\u2028still one line", None, 1002),
        ])

    def test_reviews_and_integration_use_the_reviewed_commit(self) -> None:
        branch = "issue/402-approval"
        git(self.root, "switch", "-c", branch)
        (self.root / "a").touch()
        git(self.root, "add", "a")
        git(self.root, "commit", "-m", "version 1")
        reviewed = lr.submit_branch(branch, repo_dir=self.root)["head_sha"]
        lr.record_review(branch, "approve", expected_head=reviewed, repo_dir=self.root)
        (self.root / "b").touch()
        git(self.root, "add", "b")
        git(self.root, "commit", "-m", "version 2")
        with self.assertRaisesRegex(lr.LocalReviewError, "since the diff"):
            lr.record_review(branch, "approve", expected_head=reviewed, repo_dir=self.root)
        with self.assertRaisesRegex(lr.LocalReviewError, "after approval"):
            lr.integrate_branch(branch, batch_branch="batch/reviewed", repo_dir=self.root)
        self.assertFalse(lr.branch_exists("batch/reviewed", self.root))
        self.assertEqual(lr.overview_payload(repo_dir=self.root)["items"][0]["status"], "ready")
        self.assertEqual(lr.get_diff_payload(branch, "master", to_sha=reviewed, repo_dir=self.root)["new_sha"], reviewed)

    def test_readonly_overview_does_not_create_state_dir(self) -> None:
        state_dir = lr.storage_dir(self.root, create=False)
        self.assertFalse(state_dir.exists())
        overview = lr.overview_payload(base="master", repo_dir=self.root)
        self.assertEqual(overview["items"], [])
        self.assertEqual(overview["existing_batch_branches"], [])
        self.assertEqual(overview["suggested_new_batch"], overview["default_batch"])
        self.assertFalse(state_dir.exists())

    def test_overview_existing_batch_branches_and_suggested_name(self) -> None:
        today_batch = lr.default_batch_name()
        git(self.root, "branch", "batch/manual-only", "master")

        git(self.root, "switch", "-c", "issue/501-a", "master")
        (self.root / "a.cpp").write_text("int a() { return 1; }\n", encoding="utf-8")
        git(self.root, "add", "a.cpp")
        git(self.root, "commit", "-m", "Add a")
        lr.submit_branch("issue/501-a", repo_dir=self.root)
        lr.record_review("issue/501-a", "approve", repo_dir=self.root)
        lr.integrate_branch("issue/501-a", batch_branch=today_batch, repo_dir=self.root)

        git(self.root, "switch", "-c", "issue/502-b", "master")
        (self.root / "b.cpp").write_text("int b() { return 2; }\n", encoding="utf-8")
        git(self.root, "add", "b.cpp")
        git(self.root, "commit", "-m", "Add b")
        lr.submit_branch("issue/502-b", repo_dir=self.root)
        lr.record_review("issue/502-b", "approve", repo_dir=self.root)
        lr.integrate_branch("issue/502-b", batch_branch="batch/shipped", repo_dir=self.root)

        git(self.root, "switch", "-c", "issue/503-c", "master")
        (self.root / "c.cpp").write_text("int c() { return 3; }\n", encoding="utf-8")
        git(self.root, "add", "c.cpp")
        git(self.root, "commit", "-m", "Add c")
        lr.submit_branch("issue/503-c", repo_dir=self.root)
        lr.record_review("issue/503-c", "approve", repo_dir=self.root)
        lr.integrate_branch("issue/503-c", batch_branch="batch/deleted", repo_dir=self.root)
        git(self.root, "branch", "-D", "batch/deleted")

        with lr.locked_state(self.root, write=True) as state:
            state["batches"]["batch/shipped"]["pr_url"] = "https://github.com/example/repo/pull/1"

        overview = lr.overview_payload(base="master", repo_dir=self.root)
        names = [entry["branch"] for entry in overview["existing_batch_branches"]]
        self.assertEqual(names, [today_batch, "batch/shipped", "batch/manual-only"])
        self.assertEqual(overview["suggested_new_batch"], f"{today_batch}-2")

    def test_browser_diff_layout_and_line_comments(self) -> None:
        chrome = next((shutil.which(name) for name in ("google-chrome", "chromium", "chromium-browser")
                       if shutil.which(name)), None)
        if not chrome:
            self.skipTest("Chrome or Chromium required to measure rendered columns")
        branch = "issue/403-layout"
        git(self.root, "switch", "-c", branch)
        path = self.root / "lib.cpp"
        path.write_text(path.read_text().replace("a + b", "a - b"))
        git(self.root, "commit", "-am", "Change operator")
        lr.submit_branch(branch, repo_dir=self.root)

        assets = Path(self.tmp.name) / "assets"
        shutil.copytree(lr.ASSETS_DIR, assets)
        page = assets / "app.html"
        checks = Path(__file__).with_name("test_local_review_ui.js").read_text()
        page.write_text(page.read_text().replace("</body>", f"<script>{checks}</script></body>"))
        with patch.object(lr, "ASSETS_DIR", assets):
            server = lr.create_server("127.0.0.1", 0, self.root)
            worker = threading.Thread(target=server.serve_forever, daemon=True)
            worker.start()
            try:
                result = subprocess.run(
                    [chrome, "--headless", "--no-sandbox", "--disable-dev-shm-usage",
                     "--disable-background-networking", "--no-first-run", "--dump-dom",
                     "--window-size=1440,1000", "--virtual-time-budget=10000",
                     f"--user-data-dir={self.tmp.name}/browser", f"http://127.0.0.1:{server.server_port}/"],
                    capture_output=True, text=True, timeout=45, check=False,
                )
            finally:
                server.shutdown()
                server.server_close()
                worker.join()
        if result.returncode != 0:
            detail = (result.stderr or result.stdout).strip()
            if (
                "requires the chromium snap" in detail
                or "snap-confine is packaged without necessary permissions" in detail
            ):
                self.skipTest(f"Chrome/Chromium unavailable in this environment: {detail.splitlines()[0]}")
            self.fail(f"browser test command failed ({result.returncode}): {detail[-1500:]}")
        marker = 'data-review-test="'
        status = result.stdout.partition(marker)[2].partition('"')[0]
        self.assertEqual(status, "passed", msg=status or result.stderr[-1500:])

    def test_http_api_and_static_assets(self) -> None:
        git(self.root, "checkout", "-b", "issue/301-http")
        (self.root / "extra.cpp").write_text("int one() { return 1; }\n", encoding="utf-8")
        git(self.root, "add", "extra.cpp")
        git(self.root, "commit", "-m", "Add extra")
        git(self.root, "checkout", "master")

        server = lr.create_server("127.0.0.1", 0, repo_dir=self.root, base="master")
        port = server.server_address[1]
        thread = threading.Thread(target=server.serve_forever, daemon=True)
        thread.start()
        try:
            base_url = f"http://127.0.0.1:{port}"
            with urllib.request.urlopen(f"{base_url}/") as resp:
                html = resp.read().decode("utf-8")
                self.assertIn("Local Review Queue", html)

            with urllib.request.urlopen(f"{base_url}/api/overview") as resp:
                queued = json.load(resp)["untracked_branches"]
                self.assertEqual([(c["branch"], c["ahead"]) for c in queued], [("issue/301-http", 1)])

            req = urllib.request.Request(
                f"{base_url}/api/submit",
                data=json.dumps({"branch": "issue/301-http", "summary": "HTTP test"}).encode("utf-8"),
                headers={"Content-Type": "application/json"},
                method="POST",
            )
            with urllib.request.urlopen(req) as resp:
                payload = json.loads(resp.read().decode("utf-8"))
                self.assertEqual(payload["item"]["issue"], 301)

            with urllib.request.urlopen(f"{base_url}/api/diff?branch=issue/301-http") as resp:
                diff = json.loads(resp.read().decode("utf-8"))
                self.assertEqual(diff["stats"]["files"], 1)
                self.assertEqual(diff["files"][0]["path"], "extra.cpp")
        finally:
            server.shutdown()
            server.server_close()
            thread.join(timeout=2)


if __name__ == "__main__":
    unittest.main()
