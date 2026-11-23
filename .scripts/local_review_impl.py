#!/usr/bin/env python3

from __future__ import annotations

import argparse
import ast
import contextlib
import datetime as dt
import fcntl
import http.server
import json
import os
import re
import socketserver
import subprocess
import sys
import tempfile
import urllib.parse
import uuid
import webbrowser
from pathlib import Path
from typing import Any


ROOT = Path(__file__).resolve().parents[1]
ASSETS_DIR = ROOT / "scripts" / "local_review_assets"
STATE_VERSION = 1
VALID_STATUSES = ("ready", "changes_requested", "approved", "integrated", "rejected")
VALID_REVIEW_ACTIONS = ("approve", "request_changes", "comment", "reject")
ISSUE_BRANCH_RE = re.compile(r"(?:^|/)issue/(\d+)(?:[-_/]|$)")
SAME_PATH_HEADER_RE = re.compile(r'^diff --git ("?)a/(.*)\1 \1b/\2\1$')
HUNK_HEADER_RE = re.compile(r"^@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@(.*)$")
GITHUB_REMOTE_RE = re.compile(
    r"(?:git@github\.com:|https?://github\.com/)([^/\s]+/[^/\s]+?)(?:\.git)?$"
)


class LocalReviewError(RuntimeError):
    pass


def now_iso() -> str:
    return dt.datetime.now().astimezone().isoformat(timespec="seconds")


def new_id(prefix: str) -> str:
    return f"{prefix}_{uuid.uuid4().hex[:10]}"


def default_batch_name() -> str:
    return f"batch/{dt.datetime.now().astimezone().strftime('%Y%m%d')}"


def run_git(
    args: list[str],
    cwd: Path | None = None,
    check: bool = True,
) -> subprocess.CompletedProcess[str]:
    raw = subprocess.run(
        ["git", *args],
        cwd=str(cwd or ROOT),
        capture_output=True,
    )
    proc = subprocess.CompletedProcess(
        raw.args, raw.returncode,
        raw.stdout.decode("utf-8", errors="replace"),
        raw.stderr.decode("utf-8", errors="replace"),
    )
    if check and proc.returncode != 0:
        detail = (proc.stderr or proc.stdout).strip()
        raise LocalReviewError(f"git {' '.join(args)} failed: {detail}")
    return proc


def git_common_dir(repo_dir: Path | None = None) -> Path:
    base = repo_dir or ROOT
    raw = run_git(["rev-parse", "--git-common-dir"], cwd=base).stdout.strip()
    path = Path(raw)
    if not path.is_absolute():
        path = (base / path).resolve()
    return path


def git_toplevel(repo_dir: Path | None = None) -> Path:
    base = repo_dir or ROOT
    return Path(run_git(["rev-parse", "--show-toplevel"], cwd=base).stdout.strip()).resolve()


def storage_dir(repo_dir: Path | None = None, create: bool = True) -> Path:
    override = os.environ.get("LOCAL_REVIEW_DIR", "").strip()
    if override:
        directory = Path(override).expanduser().resolve()
    else:
        directory = git_common_dir(repo_dir) / "local-review"
    if create:
        directory.mkdir(parents=True, exist_ok=True)
    return directory


def state_path(repo_dir: Path | None = None, create: bool = True) -> Path:
    return storage_dir(repo_dir, create=create) / "state.json"


def empty_state() -> dict[str, Any]:
    return {"version": STATE_VERSION, "items": {}, "batches": {}}


def load_state_unlocked(path: Path) -> dict[str, Any]:
    if not path.is_file():
        return empty_state()
    data = json.loads(path.read_text(encoding="utf-8"))
    if not isinstance(data, dict):
        return empty_state()
    data.setdefault("version", STATE_VERSION)
    data.setdefault("items", {})
    data.setdefault("batches", {})
    return data


def save_state_unlocked(path: Path, state: dict[str, Any]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp_path = path.with_suffix(".json.tmp")
    tmp_path.write_text(
        json.dumps(state, ensure_ascii=False, indent=2) + "\n",
        encoding="utf-8",
    )
    os.replace(tmp_path, path)


@contextlib.contextmanager
def locked_state(repo_dir: Path | None = None, write: bool = True):
    path = state_path(repo_dir, create=write)
    if not write and not path.is_file():
        yield empty_state()
        return
    lock_file = path.with_suffix(".lock")
    if write:
        lock_file.parent.mkdir(parents=True, exist_ok=True)
    elif not lock_file.exists():
        yield load_state_unlocked(path)
        return
    mode = "a+" if write else "r"
    with open(lock_file, mode, encoding="utf-8") as fh:
        fcntl.flock(fh.fileno(), fcntl.LOCK_EX if write else fcntl.LOCK_SH)
        try:
            state = load_state_unlocked(path)
            yield state
            if write:
                save_state_unlocked(path, state)
        finally:
            fcntl.flock(fh.fileno(), fcntl.LOCK_UN)


def current_branch(repo_dir: Path | None = None) -> str:
    branch = run_git(["rev-parse", "--abbrev-ref", "HEAD"], cwd=repo_dir).stdout.strip()
    if branch == "HEAD" or not branch:
        raise LocalReviewError("HEAD is detached; pass --branch explicitly")
    return branch


def branch_exists(branch: str, repo_dir: Path | None = None) -> bool:
    proc = run_git(["show-ref", "--verify", "--quiet", f"refs/heads/{branch}"], cwd=repo_dir, check=False)
    return proc.returncode == 0


def ref_exists(ref: str, repo_dir: Path | None = None) -> bool:
    proc = run_git(["rev-parse", "--verify", "--quiet", f"{ref}^{{commit}}"], cwd=repo_dir, check=False)
    return proc.returncode == 0


def resolve_commit(ref: str, repo_dir: Path | None = None) -> str:
    return run_git(["rev-parse", "--verify", "--end-of-options", f"{ref}^{{commit}}"], cwd=repo_dir).stdout.strip()


def short_sha(sha: str) -> str:
    return sha[:7] if sha else ""


def extract_issue_number(branch: str) -> int | None:
    match = ISSUE_BRANCH_RE.search(branch)
    return int(match.group(1)) if match else None


def github_repo_slug(repo_dir: Path | None = None) -> str:
    proc = run_git(["remote", "get-url", "origin"], cwd=repo_dir, check=False)
    if proc.returncode != 0:
        return ""
    match = GITHUB_REMOTE_RE.search(proc.stdout.strip())
    return match.group(1) if match else ""


def default_branch_title(base: str, branch: str, repo_dir: Path | None = None) -> str:
    proc = run_git(["log", "--reverse", "--format=%s", f"{base}..{branch}"], cwd=repo_dir, check=False)
    lines = [line.strip() for line in proc.stdout.splitlines() if line.strip()]
    if lines:
        return lines[0]
    fallback = run_git(["log", "-1", "--format=%s", branch], cwd=repo_dir, check=False).stdout.strip()
    return fallback or branch


def branch_commits(base: str, branch: str, repo_dir: Path | None = None) -> list[dict[str, str]]:
    if not ref_exists(base, repo_dir) or not ref_exists(branch, repo_dir):
        return []
    proc = run_git(
        ["log", "--reverse", "--format=%H%x1f%h%x1f%s%x1f%an%x1f%cI", f"{base}..{branch}"],
        cwd=repo_dir,
        check=False,
    )
    commits: list[dict[str, str]] = []
    for line in proc.stdout.splitlines():
        parts = line.split("\x1f")
        if len(parts) != 5:
            continue
        commits.append(
            {
                "sha": parts[0],
                "short_sha": parts[1],
                "subject": parts[2],
                "author": parts[3],
                "date": parts[4],
            }
        )
    return commits


def branch_diffstat(base: str, branch: str, repo_dir: Path | None = None) -> dict[str, int]:
    if not ref_exists(base, repo_dir) or not ref_exists(branch, repo_dir):
        return {"files": 0, "additions": 0, "deletions": 0}
    proc = run_git(["diff", "--numstat", f"{base}...{branch}"], cwd=repo_dir, check=False)
    files = 0
    additions = 0
    deletions = 0
    for line in proc.stdout.splitlines():
        parts = line.split("\t")
        if len(parts) < 3:
            continue
        files += 1
        if parts[0].isdigit():
            additions += int(parts[0])
        if parts[1].isdigit():
            deletions += int(parts[1])
    return {"files": files, "additions": additions, "deletions": deletions}


def list_worktrees(repo_dir: Path | None = None) -> list[dict[str, Any]]:
    proc = run_git(["worktree", "list", "--porcelain"], cwd=repo_dir)
    entries: list[dict[str, Any]] = []
    current: dict[str, Any] = {}
    for raw in proc.stdout.splitlines():
        line = raw.strip()
        if not line:
            if current:
                entries.append(current)
                current = {}
            continue
        if line.startswith("worktree "):
            current["path"] = Path(line[len("worktree "):]).resolve()
        elif line.startswith("HEAD "):
            current["head"] = line[len("HEAD "):]
        elif line.startswith("branch "):
            ref = line[len("branch "):]
            current["branch"] = ref[len("refs/heads/"):] if ref.startswith("refs/heads/") else ref
        elif line == "detached":
            current["detached"] = True
        elif line.startswith("prunable"):
            current["prunable"] = True
    if current:
        entries.append(current)
    return entries


def find_worktree_for_branch(branch: str, repo_dir: Path | None = None) -> Path | None:
    for entry in list_worktrees(repo_dir):
        if entry.get("branch") == branch and not entry.get("prunable"):
            path = entry.get("path")
            if isinstance(path, Path) and path.exists():
                return path
    return None


def is_worktree_clean(worktree_dir: Path) -> bool:
    proc = run_git(["status", "--porcelain"], cwd=worktree_dir)
    return proc.stdout.strip() == ""


def decode_git_path(path: str) -> str:
    if path.startswith('"'):
        return ast.literal_eval("b" + path).decode("utf-8", errors="replace")
    return path


def parse_unified_diff(diff_text: str) -> list[dict[str, Any]]:
    files: list[dict[str, Any]] = []
    current_file: dict[str, Any] | None = None
    current_hunk: dict[str, Any] | None = None
    old_line = 0
    new_line = 0

    for line in diff_text.split("\n"):
        line = line.removesuffix("\r")
        if line.startswith("diff --git "):
            if current_file is not None:
                files.append(current_file)
            match = SAME_PATH_HEADER_RE.fullmatch(line)
            path = decode_git_path(match[1] + match[2] + match[1]) if match else ""
            current_file = {
                "old_path": path,
                "new_path": path,
                "path": path,
                "status": "modified",
                "is_binary": False,
                "additions": 0,
                "deletions": 0,
                "hunks": [],
            }
            current_hunk = None
            continue

        if current_file is None:
            continue

        hunk_match = HUNK_HEADER_RE.match(line)
        if hunk_match:
            old_line = int(hunk_match.group(1))
            new_line = int(hunk_match.group(3))
            current_hunk = {
                "header": line,
                "old_start": old_line,
                "old_count": int(hunk_match.group(2) or "1"),
                "new_start": new_line,
                "new_count": int(hunk_match.group(4) or "1"),
                "lines": [],
            }
            current_file["hunks"].append(current_hunk)
            continue

        if current_hunk is None:
            if line.startswith("new file mode "):
                current_file["status"] = "added"
            elif line.startswith("deleted file mode "):
                current_file["status"] = "deleted"
            elif line.startswith("rename from "):
                current_file["status"] = "renamed"
                current_file["old_path"] = decode_git_path(line[len("rename from "):])
            elif line.startswith("rename to "):
                current_file["status"] = "renamed"
                current_file["new_path"] = decode_git_path(line[len("rename to "):])
                current_file["path"] = current_file["new_path"]
            elif line.startswith("Binary files ") or line == "GIT binary patch":
                current_file["is_binary"] = True
            continue

        if line.startswith("+"):
            current_hunk["lines"].append(
                {"type": "add", "old_line": None, "new_line": new_line, "content": line[1:]}
            )
            current_file["additions"] += 1
            new_line += 1
        elif line.startswith("-"):
            current_hunk["lines"].append(
                {"type": "del", "old_line": old_line, "new_line": None, "content": line[1:]}
            )
            current_file["deletions"] += 1
            old_line += 1
        elif line.startswith(" "):
            current_hunk["lines"].append(
                {"type": "context", "old_line": old_line, "new_line": new_line, "content": line[1:]}
            )
            old_line += 1
            new_line += 1
        elif line.startswith("\\ No newline at end of file"):
            current_hunk["lines"].append(
                {"type": "meta", "old_line": None, "new_line": None, "content": line}
            )

    if current_file is not None:
        files.append(current_file)
    return files


def get_diff_payload(
    branch: str,
    base: str,
    mode: str = "base",
    from_sha: str = "",
    to_sha: str = "",
    repo_dir: Path | None = None,
) -> dict[str, Any]:
    new_sha = resolve_commit(to_sha or branch, repo_dir)
    if mode == "range" and from_sha:
        old_sha = resolve_commit(from_sha, repo_dir)
    elif mode == "commit":
        old_sha = resolve_commit(f"{new_sha}^", repo_dir)
    elif mode == "base":
        old_sha = run_git(["merge-base", resolve_commit(base, repo_dir), new_sha], cwd=repo_dir).stdout.strip()
    else:
        raise LocalReviewError(f"invalid diff range: {mode}")

    diff_spec = f"{old_sha}..{new_sha}"
    proc = run_git(
        ["-c", "core.quotePath=true", "-c", "diff.suppressBlankEmpty=false", "diff",
         "--no-color", "--no-ext-diff", "--no-textconv", "--src-prefix=a/", "--dst-prefix=b/",
         "--submodule=short", "-M", "--unified=3", diff_spec, "--"],
        cwd=repo_dir,
    )
    files = parse_unified_diff(proc.stdout)
    total_add = sum(item["additions"] for item in files)
    total_del = sum(item["deletions"] for item in files)
    return {
        "spec": diff_spec,
        "old_sha": old_sha,
        "new_sha": new_sha,
        "files": files,
        "stats": {
            "files": len(files),
            "additions": total_add,
            "deletions": total_del,
        },
    }


def discover_untracked_branches(
    state: dict[str, Any],
    base: str = "master",
    repo_dir: Path | None = None,
) -> list[dict[str, Any]]:
    if not ref_exists(base, repo_dir):
        return []
    registered = set(state.get("items", {}).keys())
    batches = set(state.get("batches", {}).keys())
    fields = "%(refname:lstrip=2)%00%(objectname)%00%(subject)%00%(committerdate:iso-strict)"
    proc = run_git(
        ["for-each-ref", "--no-merged", base, "--sort=-committerdate", f"--format={fields}", "refs/heads"],
        cwd=repo_dir,
    )
    candidates: list[dict[str, Any]] = []
    for line in proc.stdout.split("\n"):
        parts = line.split("\x00", 3)
        if len(parts) != 4:
            continue
        name, sha, subject, committed_at = parts
        if name in {base, "master", "main"} or name in registered or name in batches or name.startswith("batch/"):
            continue
        ahead_raw = run_git(["rev-list", "--count", f"{base}..{name}"], cwd=repo_dir, check=False).stdout.strip()
        ahead = int(ahead_raw) if ahead_raw.isdigit() else 0
        if ahead == 0:
            continue
        candidates.append(
            {
                "branch": name,
                "head_sha": sha,
                "short_sha": short_sha(sha),
                "subject": subject,
                "committed_at": committed_at,
                "ahead": ahead,
                "issue": extract_issue_number(name),
            }
        )
    return candidates


def enrich_item(item: dict[str, Any], repo_dir: Path | None = None) -> dict[str, Any]:
    copy = dict(item)
    branch = copy["branch"]
    base = copy.get("base", "master")
    exists = branch_exists(branch, repo_dir)
    copy["branch_exists"] = exists
    if exists:
        live_sha = resolve_commit(branch, repo_dir)
        if copy.get("status") == "approved" and copy.get("last_reviewed_sha") != live_sha:
            copy["status"] = "ready"
        copy["live_head_sha"] = live_sha
        copy["live_short_sha"] = short_sha(live_sha)
        copy["commits"] = branch_commits(base, live_sha, repo_dir)
        copy["stats"] = branch_diffstat(base, live_sha, repo_dir)
    else:
        copy["live_head_sha"] = copy.get("head_sha", "")
        copy["live_short_sha"] = short_sha(copy.get("head_sha", ""))
        copy["commits"] = []
        copy["stats"] = {"files": 0, "additions": 0, "deletions": 0}
    threads = copy.get("threads", [])
    copy["unresolved_count"] = sum(1 for thread in threads if not thread.get("is_resolved"))
    copy["thread_count"] = len(threads)
    copy["has_updates_since_review"] = bool(
        copy.get("last_reviewed_sha")
        and copy["live_head_sha"]
        and copy.get("last_reviewed_sha") != copy["live_head_sha"]
    )
    return copy


def submit_branch(
    branch: str,
    base: str | None = None,
    issue: int | None = None,
    close_keyword: str | None = None,
    title: str | None = None,
    summary: str | None = None,
    verification: list[str] | None = None,
    performance: str | None = None,
    review_notes: str | None = None,
    repo_dir: Path | None = None,
) -> dict[str, Any]:
    if not branch_exists(branch, repo_dir):
        raise LocalReviewError(f"local branch not found: {branch}")

    timestamp = now_iso()

    with locked_state(repo_dir, write=True) as state:
        existing = state["items"].get(branch)
        base = base or (existing or {}).get("base", "master")
        if not ref_exists(base, repo_dir):
            raise LocalReviewError(f"base ref not found: {base}")
        head_sha = resolve_commit(f"refs/heads/{branch}", repo_dir)
        if existing is None:
            resolved_issue = issue if issue is not None else extract_issue_number(branch)
            resolved_title = title.strip() if title else default_branch_title(base, branch, repo_dir)
            item = {
                "branch": branch,
                "base": base,
                "issue": resolved_issue,
                "close_keyword": close_keyword or "Closes",
                "title": resolved_title,
                "summary": (summary or "").strip(),
                "verification": list(verification or []),
                "performance": (performance or "").strip(),
                "review_notes": (review_notes or "").strip(),
                "status": "ready",
                "head_sha": head_sha,
                "last_reviewed_sha": "",
                "batch": "",
                "integrated_sha": "",
                "created_at": timestamp,
                "updated_at": timestamp,
                "reviews": [],
                "threads": [],
            }
            state["items"][branch] = item
        else:
            existing["base"] = base
            if issue is not None:
                existing["issue"] = issue
            if close_keyword is not None:
                existing["close_keyword"] = close_keyword
            if title is not None:
                existing["title"] = title.strip()
            if summary is not None:
                existing["summary"] = summary.strip()
            if verification:
                existing["verification"] = list(verification)
            if performance is not None:
                existing["performance"] = performance.strip()
            if review_notes is not None:
                existing["review_notes"] = review_notes.strip()
            existing["head_sha"] = head_sha
            existing["status"] = "ready"
            existing["updated_at"] = timestamp
            item = existing

    return enrich_item(item, repo_dir)


def add_inline_comment(
    branch: str,
    path: str,
    line: int,
    body: str,
    side: str = "new",
    start_line: int | None = None,
    author: str = "human",
    repo_dir: Path | None = None,
    anchor_sha: str = "",
) -> dict[str, Any]:
    if not body.strip():
        raise LocalReviewError("comment body must not be empty")
    if side not in {"new", "old"}:
        raise LocalReviewError(f"invalid side: {side}")
    if line < 1:
        raise LocalReviewError(f"invalid line number: {line}")

    timestamp = now_iso()
    head_sha = resolve_commit(branch, repo_dir) if branch_exists(branch, repo_dir) else ""

    with locked_state(repo_dir, write=True) as state:
        item = state["items"].get(branch)
        if item is None:
            raise LocalReviewError(f"branch is not registered in local review: {branch}")
        thread = {
            "id": new_id("thr"),
            "path": path,
            "side": side,
            "line": int(line),
            "start_line": int(start_line) if start_line is not None else int(line),
            "is_resolved": False,
            "head_sha": head_sha or item.get("head_sha", ""),
            "created_at": timestamp,
            "updated_at": timestamp,
            "comments": [
                {
                    "id": new_id("cmt"),
                    "author": author,
                    "body": body.rstrip(),
                    "commit": "",
                    "created_at": timestamp,
                }
            ],
        }
        if anchor_sha:
            thread["anchor_sha"] = resolve_commit(anchor_sha, repo_dir)
        item.setdefault("threads", []).append(thread)
        item["updated_at"] = timestamp
        return thread


def reply_to_thread(
    branch: str,
    thread_id: str,
    body: str,
    author: str = "agent",
    commit: str = "",
    resolve: bool = False,
    repo_dir: Path | None = None,
) -> dict[str, Any]:
    if not body.strip():
        raise LocalReviewError("reply body must not be empty")
    timestamp = now_iso()

    with locked_state(repo_dir, write=True) as state:
        item = state["items"].get(branch)
        if item is None:
            raise LocalReviewError(f"branch is not registered in local review: {branch}")
        target = None
        for thread in item.get("threads", []):
            if thread.get("id") == thread_id:
                target = thread
                break
        if target is None:
            raise LocalReviewError(f"thread not found: {thread_id}")
        comment = {
            "id": new_id("cmt"),
            "author": author,
            "body": body.rstrip(),
            "commit": commit.strip(),
            "created_at": timestamp,
        }
        target.setdefault("comments", []).append(comment)
        target["updated_at"] = timestamp
        if resolve:
            target["is_resolved"] = True
        item["updated_at"] = timestamp
        return target


def set_thread_resolved(
    branch: str,
    thread_id: str,
    resolved: bool,
    repo_dir: Path | None = None,
) -> dict[str, Any]:
    timestamp = now_iso()
    with locked_state(repo_dir, write=True) as state:
        item = state["items"].get(branch)
        if item is None:
            raise LocalReviewError(f"branch is not registered in local review: {branch}")
        for thread in item.get("threads", []):
            if thread.get("id") == thread_id:
                thread["is_resolved"] = resolved
                thread["updated_at"] = timestamp
                item["updated_at"] = timestamp
                return thread
        raise LocalReviewError(f"thread not found: {thread_id}")


def record_review(
    branch: str,
    action: str,
    body: str = "",
    author: str = "human",
    repo_dir: Path | None = None,
    expected_head: str = "",
) -> dict[str, Any]:
    if action not in VALID_REVIEW_ACTIONS:
        raise LocalReviewError(f"invalid review action: {action}")
    timestamp = now_iso()

    with locked_state(repo_dir, write=True) as state:
        item = state["items"].get(branch)
        if item is None:
            raise LocalReviewError(f"branch is not registered in local review: {branch}")
        if item.get("status") == "integrated":
            raise LocalReviewError(f"branch is already integrated: {branch}")
        effective_sha = resolve_commit(f"refs/heads/{branch}", repo_dir)
        if expected_head and effective_sha != expected_head:
            raise LocalReviewError("branch changed since the diff was loaded; reload before reviewing")
        review = {
            "id": new_id("rev"),
            "action": action,
            "author": author,
            "body": body.rstrip(),
            "head_sha": effective_sha,
            "created_at": timestamp,
        }
        item.setdefault("reviews", []).append(review)
        item["head_sha"] = effective_sha
        if action in {"approve", "request_changes", "reject"}:
            item["last_reviewed_sha"] = effective_sha
        if action == "approve":
            item["status"] = "approved"
        elif action == "request_changes":
            item["status"] = "changes_requested"
        elif action == "reject":
            item["status"] = "rejected"
        item["updated_at"] = timestamp
        return enrich_item(item, repo_dir)


def get_comments_report(
    branch: str,
    unresolved_only: bool = True,
    repo_dir: Path | None = None,
) -> dict[str, Any]:
    with locked_state(repo_dir, write=False) as state:
        item = state["items"].get(branch)
        if item is None:
            raise LocalReviewError(f"branch is not registered in local review: {branch}")
        threads = item.get("threads", [])
        if unresolved_only:
            threads = [thread for thread in threads if not thread.get("is_resolved")]
        return {
            "branch": branch,
            "issue": item.get("issue"),
            "status": enrich_item(item, repo_dir)["status"],
            "head_sha": item.get("head_sha", ""),
            "last_reviewed_sha": item.get("last_reviewed_sha", ""),
            "reviews": item.get("reviews", []),
            "threads": threads,
        }


def build_squash_commit_message(item: dict[str, Any], custom_message: str | None = None) -> str:
    if custom_message and custom_message.strip():
        return custom_message.strip()
    title = item.get("title") or item["branch"]
    issue = item.get("issue")
    keyword = item.get("close_keyword") or "Closes"
    lines = [title]
    if item.get("summary"):
        lines.append("")
        lines.append(item["summary"].strip())
    if issue is not None:
        lines.append("")
        lines.append(f"{keyword} #{issue}")
    return "\n".join(lines)


def conflicted_files(worktree_dir: Path) -> list[str]:
    proc = run_git(["diff", "--name-only", "--diff-filter=U"], cwd=worktree_dir, check=False)
    return [line.strip() for line in proc.stdout.splitlines() if line.strip()]


def try_auto_resolve_doc_titles(worktree_dir: Path) -> bool:
    conflicts = conflicted_files(worktree_dir)
    if conflicts != ["meta/doc_titles.yml"]:
        return False
    sync_script = worktree_dir / "scripts" / "sync_doc_titles.py"
    if not sync_script.is_file():
        return False
    titles = worktree_dir / "meta/doc_titles.yml"
    run_git(["checkout", "--conflict=diff3", "--", "meta/doc_titles.yml"], cwd=worktree_dir)
    lines = titles.read_text(encoding="utf-8").splitlines(keepends=True)
    resolved = []
    keys = set()
    for i, line in enumerate(lines):
        if line.startswith("<<<<<<< ") or line.startswith(">>>>>>> "):
            continue
        if line.startswith("||||||| "):
            if i + 1 >= len(lines) or lines[i + 1].rstrip("\n") != "=======":
                return False
            continue
        if line.rstrip("\n") == "=======":
            continue
        if line.strip() and not line.lstrip().startswith("#"):
            key, separator, _ = line.partition(": ")
            if not separator or key in keys:
                return False
            keys.add(key)
        resolved.append(line)
    titles.write_text("".join(resolved), encoding="utf-8")
    proc = subprocess.run(
        [sys.executable, str(sync_script), "--write"],
        cwd=str(worktree_dir),
        capture_output=True,
        text=True,
    )
    if proc.returncode != 0:
        return False
    run_git(["add", "--update"], cwd=worktree_dir)
    return not conflicted_files(worktree_dir)


def integrate_branch(
    branch: str,
    batch_branch: str | None = None,
    base: str | None = None,
    message: str | None = None,
    delete_branch: bool = False,
    force: bool = False,
    auto_sync_titles: bool = True,
    repo_dir: Path | None = None,
) -> dict[str, Any]:
    repo = repo_dir or ROOT
    if not branch_exists(branch, repo):
        raise LocalReviewError(f"local branch not found: {branch}")

    with locked_state(repo, write=True) as state:
        item = state["items"].get(branch)
        if item is None:
            raise LocalReviewError(f"branch is not registered in local review: {branch}")
        if not force and item.get("status") != "approved":
            raise LocalReviewError(
                f"branch {branch} has status '{item.get('status')}' (expected 'approved'; pass --force to override)"
            )
        source_sha = resolve_commit(f"refs/heads/{branch}", repo)
        if not force and item.get("last_reviewed_sha") != source_sha:
            raise LocalReviewError(f"branch {branch} changed after approval; review the new head before integrating")
        target_batch = batch_branch or item.get("batch") or default_batch_name()
        target_base = base or item.get("base") or "master"
        commit_message = build_squash_commit_message(item, message)

        if not ref_exists(target_base, repo):
            raise LocalReviewError(f"base ref not found: {target_base}")

        batch_ref = f"refs/heads/{target_batch}"
        batch_exists = branch_exists(target_batch, repo)
        start_sha = resolve_commit(batch_ref if batch_exists else target_base, repo)
        with tempfile.TemporaryDirectory(prefix="local-review-merge-") as scratch:
            wt_dir = Path(scratch) / "worktree"
            run_git(["worktree", "add", "--detach", str(wt_dir), start_sha], cwd=repo)
            try:
                merge_proc = run_git(["merge", "--squash", source_sha], cwd=wt_dir, check=False)
                if merge_proc.returncode and not (auto_sync_titles and try_auto_resolve_doc_titles(wt_dir)):
                    conflicts = conflicted_files(wt_dir)
                    detail = ", ".join(conflicts) if conflicts else (merge_proc.stderr or merge_proc.stdout).strip()
                    raise LocalReviewError(f"merge conflict integrating {branch} into {target_batch}: {detail}")

                if not run_git(["diff", "--cached", "--name-only"], cwd=wt_dir).stdout:
                    raise LocalReviewError(f"no staged changes when integrating {branch} into {target_batch}")
                run_git(["commit", "-m", commit_message], cwd=wt_dir)
                new_sha = resolve_commit("HEAD", wt_dir)

                existing_wt = find_worktree_for_branch(target_batch, repo)
                if existing_wt is None:
                    expected_sha = start_sha if batch_exists else "0" * len(start_sha)
                    run_git(["update-ref", batch_ref, new_sha, expected_sha], cwd=repo)
                else:
                    if not is_worktree_clean(existing_wt) or resolve_commit("HEAD", existing_wt) != start_sha:
                        raise LocalReviewError(f"worktree for {target_batch} has local changes: {existing_wt}")
                    run_git(["merge", "--ff-only", new_sha], cwd=existing_wt)
            finally:
                run_git(["worktree", "remove", "--force", str(wt_dir)], cwd=repo)

        deleted_branch = False
        if delete_branch:
            branch_wt = find_worktree_for_branch(branch, repo)
            if branch_wt is None:
                proc = run_git(["update-ref", "-d", f"refs/heads/{branch}", source_sha], cwd=repo, check=False)
                deleted_branch = proc.returncode == 0

        timestamp = now_iso()
        item["status"] = "integrated"
        item["batch"] = target_batch
        item["integrated_sha"] = new_sha
        item["updated_at"] = timestamp

        batch = state["batches"].setdefault(
            target_batch,
            {
                "branch": target_batch,
                "base": target_base,
                "created_at": timestamp,
                "updated_at": timestamp,
                "pr_url": "",
                "entries": [],
            },
        )
        batch["updated_at"] = timestamp
        batch["entries"] = [
            entry for entry in batch.get("entries", []) if entry.get("branch") != branch
        ]
        batch["entries"].append(
            {
                "branch": branch,
                "issue": item.get("issue"),
                "close_keyword": item.get("close_keyword") or "Closes",
                "title": item.get("title") or branch,
                "summary": item.get("summary", ""),
                "verification": item.get("verification", []),
                "performance": item.get("performance", ""),
                "commit_sha": new_sha,
                "short_sha": short_sha(new_sha),
                "integrated_at": timestamp,
            }
        )

    return {
        "branch": branch,
        "batch": target_batch,
        "commit_sha": new_sha,
        "short_sha": short_sha(new_sha),
        "deleted_branch": deleted_branch,
    }


def build_batch_pr_draft(
    batch_branch: str,
    title: str | None = None,
    repo_dir: Path | None = None,
) -> dict[str, Any]:
    repo = repo_dir or ROOT
    with locked_state(repo, write=False) as state:
        batch = state["batches"].get(batch_branch)
        if batch is None:
            raise LocalReviewError(f"batch not found in local review state: {batch_branch}")
        entries = list(batch.get("entries", []))
        base = batch.get("base", "master")

    if not entries:
        raise LocalReviewError(f"batch {batch_branch} has no integrated entries")

    resolved_title = title.strip() if title else f"Batch update ({batch_branch}, {len(entries)} items)"
    issue_lines: list[str] = []
    seen_issues: set[tuple[str, int]] = set()
    for entry in entries:
        issue = entry.get("issue")
        keyword = entry.get("close_keyword") or "Closes"
        if issue is not None and (keyword, issue) not in seen_issues:
            seen_issues.add((keyword, issue))
            issue_lines.append(f"{keyword} #{issue}")

    body_parts: list[str] = []
    if issue_lines:
        body_parts.append("## 関連 issue\n\n" + "\n".join(issue_lines))

    change_lines: list[str] = []
    verify_lines: list[str] = []
    perf_lines: list[str] = []
    for entry in entries:
        issue_tag = f" (#{entry['issue']})" if entry.get("issue") is not None else ""
        sha_tag = f" `{entry['short_sha']}`" if entry.get("short_sha") else ""
        line = f"- **{entry['title']}**{issue_tag}{sha_tag}"
        if entry.get("summary"):
            line += f": {entry['summary']}"
        change_lines.append(line)
        for v in entry.get("verification") or []:
            verify_lines.append(f"- [{entry['title']}] {v}")
        if entry.get("performance"):
            perf_lines.append(f"- [{entry['title']}] {entry['performance']}")

    body_parts.append("## 変更概要\n\n" + "\n".join(change_lines))
    if verify_lines:
        body_parts.append("## 検証\n\n" + "\n".join(verify_lines))
    if perf_lines:
        body_parts.append("## 性能\n\n" + "\n".join(perf_lines))
    body_parts.append(
        "## マージ方針\n\n- 1 issue = 1 コミットを維持するため **Rebase and merge**（または Merge commit）でマージする。"
    )

    commits = branch_commits(base, batch_branch, repo) if branch_exists(batch_branch, repo) else []
    stats = branch_diffstat(base, batch_branch, repo) if branch_exists(batch_branch, repo) else {
        "files": 0,
        "additions": 0,
        "deletions": 0,
    }
    return {
        "batch": batch_branch,
        "base": base,
        "title": resolved_title,
        "body": "\n\n".join(body_parts),
        "entries": entries,
        "commits": commits,
        "stats": stats,
    }


def discover_local_batch_branches(
    batches: list[dict[str, Any]],
    repo_dir: Path | None = None,
) -> list[dict[str, Any]]:
    tracked: list[dict[str, Any]] = []
    seen: set[str] = set()
    for batch in batches:
        name = batch["branch"]
        if not batch.get("branch_exists"):
            continue
        seen.add(name)
        tracked.append(
            {
                "branch": name,
                "entry_count": len(batch.get("entries") or []),
                "commit_count": len(batch.get("commits") or []),
                "pr_url": batch.get("pr_url", ""),
                "updated_at": batch.get("updated_at", ""),
                "tracked": True,
            }
        )
    unshipped = [entry for entry in tracked if not entry["pr_url"]]
    shipped = [entry for entry in tracked if entry["pr_url"]]
    unshipped.sort(key=lambda entry: entry["updated_at"], reverse=True)
    shipped.sort(key=lambda entry: entry["updated_at"], reverse=True)
    result = unshipped + shipped

    proc = run_git(
        ["for-each-ref", "--sort=-committerdate", "--format=%(refname:lstrip=2)", "refs/heads/batch"],
        cwd=repo_dir,
        check=False,
    )
    if proc.returncode == 0:
        for raw in proc.stdout.splitlines():
            name = raw.strip()
            if not name or name in seen:
                continue
            seen.add(name)
            result.append(
                {
                    "branch": name,
                    "entry_count": 0,
                    "commit_count": 0,
                    "pr_url": "",
                    "updated_at": "",
                    "tracked": False,
                }
            )
    return result


def suggest_new_batch_name(existing_names: set[str], repo_dir: Path | None = None) -> str:
    base_name = default_batch_name()
    if base_name not in existing_names and not branch_exists(base_name, repo_dir):
        return base_name
    suffix = 2
    while True:
        candidate = f"{base_name}-{suffix}"
        if candidate not in existing_names and not branch_exists(candidate, repo_dir):
            return candidate
        suffix += 1


def overview_payload(base: str = "master", repo_dir: Path | None = None) -> dict[str, Any]:
    repo = repo_dir or ROOT
    with locked_state(repo, write=False) as state:
        items = [enrich_item(item, repo) for item in state.get("items", {}).values()]
        items.sort(key=lambda entry: entry.get("updated_at", ""), reverse=True)
        batches: list[dict[str, Any]] = []
        for batch in state.get("batches", {}).values():
            batch_copy = dict(batch)
            b_name = batch_copy["branch"]
            b_base = batch_copy.get("base", base)
            batch_copy["branch_exists"] = branch_exists(b_name, repo)
            if batch_copy["branch_exists"] and ref_exists(b_base, repo):
                batch_copy["commits"] = branch_commits(b_base, b_name, repo)
                batch_copy["stats"] = branch_diffstat(b_base, b_name, repo)
            else:
                batch_copy["commits"] = []
                batch_copy["stats"] = {"files": 0, "additions": 0, "deletions": 0}
            batches.append(batch_copy)
        batches.sort(key=lambda entry: entry.get("updated_at", ""), reverse=True)
        untracked = discover_untracked_branches(state, base=base, repo_dir=repo)

    existing_batches = discover_local_batch_branches(batches, repo_dir=repo)
    existing_names = {entry["branch"] for entry in existing_batches}
    suggested_new_batch = suggest_new_batch_name(existing_names, repo_dir=repo)
    master_sha = resolve_commit(base, repo) if ref_exists(base, repo) else ""
    return {
        "repo_name": git_toplevel(repo).name,
        "github_slug": github_repo_slug(repo),
        "base": base,
        "base_sha": master_sha,
        "base_short_sha": short_sha(master_sha),
        "default_batch": default_batch_name(),
        "suggested_new_batch": suggested_new_batch,
        "existing_batch_branches": existing_batches,
        "items": items,
        "batches": batches,
        "untracked_branches": untracked,
    }


def build_http_handler(repo_dir: Path, default_base: str = "master"):
    class LocalReviewHandler(http.server.BaseHTTPRequestHandler):
        def log_message(self, format: str, *args: Any) -> None:
            return

        def send_json(self, status: int, payload: Any) -> None:
            raw = json.dumps(payload, ensure_ascii=False).encode("utf-8")
            self.send_response(status)
            self.send_header("Content-Type", "application/json; charset=utf-8")
            self.send_header("Content-Length", str(len(raw)))
            self.send_header("Cache-Control", "no-store")
            self.end_headers()
            self.wfile.write(raw)

        def send_asset(self, filename: str, content_type: str) -> None:
            asset_path = ASSETS_DIR / filename
            if not asset_path.is_file():
                self.send_json(404, {"error": f"asset not found: {filename}"})
                return
            raw = asset_path.read_bytes()
            self.send_response(200)
            self.send_header("Content-Type", content_type)
            self.send_header("Content-Length", str(len(raw)))
            self.send_header("Cache-Control", "no-store")
            self.end_headers()
            self.wfile.write(raw)

        def read_json_body(self) -> dict[str, Any]:
            length = int(self.headers.get("Content-Length", "0") or "0")
            if length == 0:
                return {}
            raw = self.rfile.read(length)
            data = json.loads(raw.decode("utf-8"))
            if not isinstance(data, dict):
                raise LocalReviewError("JSON body must be an object")
            return data

        def do_GET(self) -> None:
            parsed = urllib.parse.urlparse(self.path)
            path = parsed.path
            query = urllib.parse.parse_qs(parsed.query)
            try:
                if path in {"/", "/index.html"}:
                    self.send_asset("app.html", "text/html; charset=utf-8")
                    return
                if path == "/app.css":
                    self.send_asset("app.css", "text/css; charset=utf-8")
                    return
                if path == "/app.js":
                    self.send_asset("app.js", "application/javascript; charset=utf-8")
                    return
                if path == "/api/overview":
                    base = query.get("base", [default_base])[0]
                    self.send_json(200, overview_payload(base=base, repo_dir=repo_dir))
                    return
                if path == "/api/diff":
                    branch = query.get("branch", [""])[0]
                    mode = query.get("mode", ["base"])[0]
                    from_sha = query.get("from", [""])[0]
                    to_sha = query.get("to", [""])[0]
                    if not branch:
                        raise LocalReviewError("branch parameter is required")
                    with locked_state(repo_dir, write=False) as state:
                        item = state["items"].get(branch)
                        base = item.get("base", default_base) if item else default_base
                    diff = get_diff_payload(
                        branch=branch,
                        base=base,
                        mode=mode,
                        from_sha=from_sha,
                        to_sha=to_sha,
                        repo_dir=repo_dir,
                    )
                    self.send_json(200, diff)
                    return
                if path == "/api/batch/draft":
                    batch = query.get("batch", [""])[0]
                    if not batch:
                        raise LocalReviewError("batch parameter is required")
                    self.send_json(200, build_batch_pr_draft(batch, repo_dir=repo_dir))
                    return
                self.send_json(404, {"error": f"not found: {path}"})
            except LocalReviewError as exc:
                self.send_json(400, {"error": str(exc)})
            except Exception as exc:
                self.send_json(500, {"error": str(exc)})

        def do_POST(self) -> None:
            parsed = urllib.parse.urlparse(self.path)
            path = parsed.path
            try:
                body = self.read_json_body()
                if path == "/api/submit":
                    branch = str(body.get("branch", "")).strip()
                    if not branch:
                        raise LocalReviewError("branch is required")
                    issue_val = body.get("issue")
                    issue = int(issue_val) if issue_val not in (None, "") else None
                    result = submit_branch(
                        branch=branch,
                        base=str(body.get("base") or default_base),
                        issue=issue,
                        close_keyword=body.get("close_keyword"),
                        title=body.get("title"),
                        summary=body.get("summary"),
                        verification=body.get("verification"),
                        performance=body.get("performance"),
                        review_notes=body.get("review_notes"),
                        repo_dir=repo_dir,
                    )
                    self.send_json(200, {"item": result})
                    return
                if path == "/api/threads":
                    thread = add_inline_comment(
                        branch=str(body.get("branch", "")),
                        path=str(body.get("path", "")),
                        line=int(body.get("line", 0)),
                        start_line=int(body["start_line"]) if body.get("start_line") else None,
                        side=str(body.get("side", "new")),
                        body=str(body.get("body", "")),
                        author=str(body.get("author", "human")),
                        anchor_sha=str(body.get("anchor_sha", "")),
                        repo_dir=repo_dir,
                    )
                    self.send_json(200, {"thread": thread})
                    return
                if path == "/api/threads/reply":
                    thread = reply_to_thread(
                        branch=str(body.get("branch", "")),
                        thread_id=str(body.get("thread_id", "")),
                        body=str(body.get("body", "")),
                        author=str(body.get("author", "human")),
                        commit=str(body.get("commit", "")),
                        resolve=bool(body.get("resolve", False)),
                        repo_dir=repo_dir,
                    )
                    self.send_json(200, {"thread": thread})
                    return
                if path == "/api/threads/resolve":
                    thread = set_thread_resolved(
                        branch=str(body.get("branch", "")),
                        thread_id=str(body.get("thread_id", "")),
                        resolved=bool(body.get("resolved", True)),
                        repo_dir=repo_dir,
                    )
                    self.send_json(200, {"thread": thread})
                    return
                if path == "/api/review":
                    item = record_review(
                        branch=str(body.get("branch", "")),
                        action=str(body.get("action", "")),
                        body=str(body.get("body", "")),
                        author=str(body.get("author", "human")),
                        expected_head=str(body.get("expected_head", "")),
                        repo_dir=repo_dir,
                    )
                    self.send_json(200, {"item": item})
                    return
                if path == "/api/integrate":
                    result = integrate_branch(
                        branch=str(body.get("branch", "")),
                        batch_branch=str(body.get("batch", "")).strip() or None,
                        base=body.get("base"),
                        message=body.get("message"),
                        delete_branch=bool(body.get("delete_branch", False)),
                        force=bool(body.get("force", False)),
                        repo_dir=repo_dir,
                    )
                    self.send_json(200, result)
                    return
                self.send_json(404, {"error": f"not found: {path}"})
            except LocalReviewError as exc:
                self.send_json(400, {"error": str(exc)})
            except Exception as exc:
                self.send_json(500, {"error": str(exc)})

    return LocalReviewHandler


class ReusableThreadingHTTPServer(socketserver.ThreadingMixIn, http.server.HTTPServer):
    allow_reuse_address = True
    daemon_threads = True


def create_server(host: str, port: int, repo_dir: Path | None = None, base: str = "master") -> ReusableThreadingHTTPServer:
    handler = build_http_handler(repo_dir or ROOT, default_base=base)
    return ReusableThreadingHTTPServer((host, port), handler)


def cmd_serve(args: argparse.Namespace) -> int:
    server = create_server(args.host, args.port, ROOT, base=args.base)
    host, port = server.server_address
    url = f"http://{host}:{port}/"
    print(f"Local Review UI running at {url}")
    print(f"State directory: {storage_dir(ROOT, create=False)}")
    if args.open:
        webbrowser.open(url)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nStopped.")
    finally:
        server.server_close()
    return 0


def cmd_submit(args: argparse.Namespace) -> int:
    branch = args.branch or current_branch(ROOT)
    close_keyword = "Refs" if args.refs else "Closes"
    item = submit_branch(
        branch=branch,
        base=args.base,
        issue=args.issue,
        close_keyword=close_keyword if (args.refs or args.issue is not None) else None,
        title=args.title,
        summary=args.summary,
        verification=args.verify,
        performance=args.perf,
        review_notes=args.notes,
        repo_dir=ROOT,
    )
    if args.json:
        print(json.dumps(item, ensure_ascii=False, indent=2))
    else:
        issue_tag = f" (#{item['issue']})" if item.get("issue") is not None else ""
        print(f"submitted: {item['branch']}{issue_tag} [{item['status']}] {item['live_short_sha']}")
    return 0


def cmd_list(args: argparse.Namespace) -> int:
    data = overview_payload(base=args.base, repo_dir=ROOT)
    items = data["items"]
    if args.status:
        items = [item for item in items if item.get("status") == args.status]
    if args.json:
        print(json.dumps({"items": items, "batches": data["batches"]}, ensure_ascii=False, indent=2))
        return 0
    if not items:
        print("(no items in local review queue)")
        return 0
    for item in items:
        issue_tag = f"#{item['issue']}" if item.get("issue") is not None else "-"
        stats = item.get("stats", {})
        print(
            f"[{item['status']:<17}] {item['branch']} ({issue_tag}) "
            f"{item['live_short_sha']} +{stats.get('additions', 0)}/-{stats.get('deletions', 0)} "
            f"unresolved={item.get('unresolved_count', 0)} | {item.get('title', '')}"
        )
    return 0


def cmd_comments(args: argparse.Namespace) -> int:
    branch = args.branch or current_branch(ROOT)
    report = get_comments_report(branch, unresolved_only=not args.all, repo_dir=ROOT)
    if args.json:
        print(json.dumps(report, ensure_ascii=False, indent=2))
        return 0
    issue_tag = f" (#{report['issue']})" if report.get("issue") is not None else ""
    print(f"Branch: {report['branch']}{issue_tag} [{report['status']}] head={short_sha(report['head_sha'])}")
    if report["reviews"]:
        print("\nReviews:")
        for rev in report["reviews"]:
            body = f": {rev['body']}" if rev.get("body") else ""
            print(f"  - [{rev['action']}] ({rev['author']} @ {short_sha(rev.get('head_sha', ''))}){body}")
    if not report["threads"]:
        print("\n(no matching threads)")
        return 0
    print("\nThreads:")
    for thread in report["threads"]:
        state_tag = "resolved" if thread.get("is_resolved") else "open"
        print(f"  [{thread['id']}] {thread['path']}:{thread['line']} ({thread['side']}, {state_tag})")
        for comment in thread.get("comments", []):
            commit_tag = f" ({comment['commit']})" if comment.get("commit") else ""
            indented = "\n      ".join(comment.get("body", "").splitlines())
            print(f"    - {comment['author']}{commit_tag}: {indented}")
    return 0


def cmd_reply(args: argparse.Namespace) -> int:
    branch = args.branch or current_branch(ROOT)
    commit = args.commit
    if args.with_head_commit and not commit and branch_exists(branch, ROOT):
        commit = short_sha(resolve_commit(branch, ROOT))
    thread = reply_to_thread(
        branch=branch,
        thread_id=args.thread,
        body=args.body,
        author=args.author,
        commit=commit,
        resolve=args.resolve,
        repo_dir=ROOT,
    )
    if args.json:
        print(json.dumps(thread, ensure_ascii=False, indent=2))
    else:
        print(f"replied: {branch} [{thread['id']}]")
    return 0


def cmd_add_comment(args: argparse.Namespace) -> int:
    branch = args.branch or current_branch(ROOT)
    thread = add_inline_comment(
        branch=branch,
        path=args.path,
        line=args.line,
        start_line=args.start_line,
        side=args.side,
        body=args.body,
        author=args.author,
        repo_dir=ROOT,
    )
    if args.json:
        print(json.dumps(thread, ensure_ascii=False, indent=2))
    else:
        print(f"comment added: {branch} [{thread['id']}] {thread['path']}:{thread['line']}")
    return 0


def cmd_resolve(args: argparse.Namespace) -> int:
    branch = args.branch or current_branch(ROOT)
    thread = set_thread_resolved(
        branch=branch,
        thread_id=args.thread,
        resolved=not args.unresolve,
        repo_dir=ROOT,
    )
    if args.json:
        print(json.dumps(thread, ensure_ascii=False, indent=2))
    else:
        verb = "unresolved" if args.unresolve else "resolved"
        print(f"{verb}: {branch} [{thread['id']}]")
    return 0


def cmd_review(args: argparse.Namespace) -> int:
    branch = args.branch or current_branch(ROOT)
    item = record_review(
        branch=branch,
        action=args.action,
        body=args.body,
        author=args.author,
        repo_dir=ROOT,
    )
    if args.json:
        print(json.dumps(item, ensure_ascii=False, indent=2))
    else:
        print(f"reviewed: {item['branch']} -> {item['status']} ({item['live_short_sha']})")
    return 0


def cmd_integrate(args: argparse.Namespace) -> int:
    result = integrate_branch(
        branch=args.branch,
        batch_branch=args.batch,
        base=args.base,
        message=args.message,
        delete_branch=args.delete_branch,
        force=args.force,
        auto_sync_titles=not args.no_auto_sync_titles,
        repo_dir=ROOT,
    )
    if args.json:
        print(json.dumps(result, ensure_ascii=False, indent=2))
    else:
        suffix = " (branch deleted)" if result["deleted_branch"] else ""
        print(
            f"integrated: {result['branch']} -> {result['batch']} "
            f"as {result['short_sha']}{suffix}"
        )
    return 0


def cmd_prepare_pr(args: argparse.Namespace) -> int:
    draft = build_batch_pr_draft(args.batch, title=args.title, repo_dir=ROOT)
    if args.push or args.create:
        run_git(["push", "-u", "origin", args.batch], cwd=ROOT)
    if args.create:
        proc = subprocess.run(
            [
                "gh",
                "pr",
                "create",
                "--base",
                draft["base"],
                "--head",
                args.batch,
                "--title",
                draft["title"],
                "--body",
                draft["body"],
            ],
            cwd=str(ROOT),
            capture_output=True,
            text=True,
        )
        if proc.returncode != 0:
            raise LocalReviewError(f"gh pr create failed: {(proc.stderr or proc.stdout).strip()}")
        pr_url = proc.stdout.strip()
        with locked_state(ROOT, write=True) as state:
            if args.batch in state["batches"]:
                state["batches"][args.batch]["pr_url"] = pr_url
                state["batches"][args.batch]["updated_at"] = now_iso()
        draft["pr_url"] = pr_url
    if args.json:
        print(json.dumps(draft, ensure_ascii=False, indent=2))
    else:
        print(f"# {draft['title']}\n")
        print(draft["body"])
        if draft.get("pr_url"):
            print(f"\nPR created: {draft['pr_url']}")
    return 0


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Local PR-style review queue UI and batch integration CLI."
    )
    sub = parser.add_subparsers(dest="command", required=True)

    p_serve = sub.add_parser("serve", help="Start the local GitHub PR-style review Web UI.")
    p_serve.add_argument("--host", default="127.0.0.1", help="Bind host (default: 127.0.0.1).")
    p_serve.add_argument("--port", type=int, default=8765, help="Bind port (default: 8765).")
    p_serve.add_argument("--base", default="master", help="Default base ref (default: master).")
    p_serve.add_argument("--open", action="store_true", help="Open browser automatically.")
    p_serve.set_defaults(func=cmd_serve)

    p_submit = sub.add_parser("submit", help="Register or resubmit a local branch for review.")
    p_submit.add_argument("--branch", help="Branch name (default: current HEAD branch).")
    p_submit.add_argument("--base", help="Base ref (default: existing review base, or master).")
    p_submit.add_argument("--issue", type=int, help="GitHub issue number.")
    p_submit.add_argument("--refs", action="store_true", help="Use Refs # instead of Closes #.")
    p_submit.add_argument("--title", help="Short review title.")
    p_submit.add_argument("--summary", help="Change summary.")
    p_submit.add_argument("--verify", action="append", help="Verification result line (repeatable).")
    p_submit.add_argument("--perf", help="Performance measurement note.")
    p_submit.add_argument("--notes", help="Review points or open questions.")
    p_submit.add_argument("--json", action="store_true", help="Output JSON.")
    p_submit.set_defaults(func=cmd_submit)

    p_list = sub.add_parser("list", help="List branches in the local review queue.")
    p_list.add_argument("--status", choices=VALID_STATUSES, help="Filter by status.")
    p_list.add_argument("--base", default="master", help="Base ref (default: master).")
    p_list.add_argument("--json", action="store_true", help="Output JSON.")
    p_list.set_defaults(func=cmd_list)

    p_comments = sub.add_parser("comments", help="Inspect reviews and inline threads for a branch.")
    p_comments.add_argument("branch", nargs="?", help="Branch name (default: current HEAD branch).")
    p_comments.add_argument("--all", action="store_true", help="Include resolved threads.")
    p_comments.add_argument("--json", action="store_true", help="Output JSON.")
    p_comments.set_defaults(func=cmd_comments)

    p_add = sub.add_parser("add-comment", help="Add an inline comment thread to a branch.")
    p_add.add_argument("branch", nargs="?", help="Branch name (default: current HEAD branch).")
    p_add.add_argument("--path", required=True, help="Repository-relative file path.")
    p_add.add_argument("--line", required=True, type=int, help="Line number.")
    p_add.add_argument("--start-line", type=int, help="Start line for multi-line comment.")
    p_add.add_argument("--side", choices=("new", "old"), default="new", help="Diff side (default: new).")
    p_add.add_argument("--body", required=True, help="Comment body.")
    p_add.add_argument("--author", default="human", help="Comment author.")
    p_add.add_argument("--json", action="store_true", help="Output JSON.")
    p_add.set_defaults(func=cmd_add_comment)

    p_reply = sub.add_parser("reply", help="Reply to an inline review thread.")
    p_reply.add_argument("branch", nargs="?", help="Branch name (default: current HEAD branch).")
    p_reply.add_argument("--thread", required=True, help="Thread ID.")
    p_reply.add_argument("--body", required=True, help="Reply body.")
    p_reply.add_argument("--commit", default="", help="Commit hash referencing the fix.")
    p_reply.add_argument("--with-head-commit", action="store_true", help="Attach current branch HEAD short SHA.")
    p_reply.add_argument("--author", default="agent", help="Reply author (default: agent).")
    p_reply.add_argument("--resolve", action="store_true", help="Also resolve the thread.")
    p_reply.add_argument("--json", action="store_true", help="Output JSON.")
    p_reply.set_defaults(func=cmd_reply)

    p_resolve = sub.add_parser("resolve", help="Resolve or unresolve an inline thread.")
    p_resolve.add_argument("branch", nargs="?", help="Branch name (default: current HEAD branch).")
    p_resolve.add_argument("--thread", required=True, help="Thread ID.")
    p_resolve.add_argument("--unresolve", action="store_true", help="Reopen the thread.")
    p_resolve.add_argument("--json", action="store_true", help="Output JSON.")
    p_resolve.set_defaults(func=cmd_resolve)

    p_review = sub.add_parser("review", help="Submit a review decision for a branch.")
    p_review.add_argument("branch", nargs="?", help="Branch name (default: current HEAD branch).")
    p_review.add_argument("--action", required=True, choices=VALID_REVIEW_ACTIONS, help="Review action.")
    p_review.add_argument("--body", default="", help="Review summary body.")
    p_review.add_argument("--author", default="human", help="Reviewer name.")
    p_review.add_argument("--json", action="store_true", help="Output JSON.")
    p_review.set_defaults(func=cmd_review)

    p_integrate = sub.add_parser(
        "integrate",
        help="Squash-integrate an approved branch into a batch branch as 1 commit.",
    )
    p_integrate.add_argument("branch", help="Approved issue branch to integrate.")
    p_integrate.add_argument("--batch", help="Target batch branch (default: batch/YYYYMMDD).")
    p_integrate.add_argument("--base", help="Base ref when creating a new batch branch (default: review base).")
    p_integrate.add_argument("--message", help="Custom squash commit message.")
    p_integrate.add_argument("--delete-branch", action="store_true", help="Delete source branch after integration.")
    p_integrate.add_argument("--force", action="store_true", help="Allow integrating non-approved branch.")
    p_integrate.add_argument(
        "--no-auto-sync-titles",
        action="store_true",
        help="Disable automatic meta/doc_titles.yml conflict resolution.",
    )
    p_integrate.add_argument("--json", action="store_true", help="Output JSON.")
    p_integrate.set_defaults(func=cmd_integrate)

    p_pr = sub.add_parser("prepare-pr", help="Generate batch PR description (and optionally push/create PR).")
    p_pr.add_argument("--batch", required=True, help="Batch branch name.")
    p_pr.add_argument("--title", help="Custom PR title.")
    p_pr.add_argument("--push", action="store_true", help="Push the batch branch to origin.")
    p_pr.add_argument("--create", action="store_true", help="Push and run gh pr create.")
    p_pr.add_argument("--json", action="store_true", help="Output JSON.")
    p_pr.set_defaults(func=cmd_prepare_pr)

    return parser


def main(argv: list[str] | None = None) -> int:
    parser = build_parser()
    args = parser.parse_args(argv)
    try:
        return args.func(args)
    except LocalReviewError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
