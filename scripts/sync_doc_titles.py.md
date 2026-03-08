---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.19/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.19/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 96, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "#!/usr/bin/env python3\n\nfrom __future__ import annotations\n\nimport argparse\n\
    import json\nimport re\nimport sys\nfrom pathlib import Path\n\n\nROOT = Path(__file__).resolve().parents[1]\n\
    TITLE_FILE = ROOT / \"meta\" / \"doc_titles.yml\"\nCORE_DIRS = (\n    \"datastructure\"\
    ,\n    \"graph\",\n    \"math\",\n    \"string\",\n    \"tree\",\n    \"geometry\"\
    ,\n    \"flow\",\n    \"fps\",\n    \"util\",\n)\n\n\nCOMMENT_BLOCK_RE = re.compile(r\"\
    /\\*\\*\\n(?: \\*.*\\n)*? \\*/\\n?\", re.MULTILINE)\nMANAGED_BLOCK_RE = re.compile(\n\
    \    r\"/\\*\\*\\n \\* @brief (?P<title>[^\\n]+)\\n \\* @docs (?P<docs>_md/[^\\\
    n]+)\\n \\*/\\n?\",\n    re.MULTILINE,\n)\n\n\ndef load_titles(path: Path) ->\
    \ dict[str, str]:\n    titles: dict[str, str] = {}\n    for lineno, raw in enumerate(path.read_text().splitlines(),\
    \ 1):\n        line = raw.strip()\n        if not line or line.startswith(\"#\"\
    ):\n            continue\n        if \": \" not in line:\n            raise ValueError(f\"\
    {path}:{lineno}: invalid line\")\n        key, value = line.split(\": \", 1)\n\
    \        try:\n            parsed = json.loads(value)\n        except json.JSONDecodeError\
    \ as exc:\n            raise ValueError(f\"{path}:{lineno}: invalid JSON string\"\
    ) from exc\n        if not isinstance(parsed, str):\n            raise ValueError(f\"\
    {path}:{lineno}: title must be a string\")\n        titles[key] = parsed\n   \
    \ return titles\n\n\ndef collect_doc_files() -> set[str]:\n    files: set[str]\
    \ = set()\n    for root in CORE_DIRS:\n        for path in (ROOT / root).glob(\"\
    *.cpp\"):\n            if (ROOT / \"_md\" / f\"{path.stem}.md\").exists():\n \
    \               files.add(path.relative_to(ROOT).as_posix())\n    return files\n\
    \n\ndef expected_docs_path(relpath: str) -> str:\n    return f\"_md/{Path(relpath).stem}.md\"\
    \n\n\ndef render_block(relpath: str, title: str) -> str:\n    return (\n     \
    \   \"/**\\n\"\n        f\" * @brief {title}\\n\"\n        f\" * @docs {expected_docs_path(relpath)}\\\
    n\"\n        \" */\\n\"\n    )\n\n\ndef replace_block(text: str, relpath: str,\
    \ title: str) -> tuple[str, bool]:\n    new_block = render_block(relpath, title)\n\
    \    matches = [m for m in COMMENT_BLOCK_RE.finditer(text) if \"@brief\" in m.group(0)\
    \ or \"@docs\" in m.group(0)]\n    if len(matches) > 1:\n        raise ValueError(f\"\
    {relpath}: multiple managed comment blocks found\")\n    if matches:\n       \
    \ match = matches[0]\n        old = match.group(0)\n        if old.endswith(\"\
    \\n\"):\n            replacement = new_block\n        else:\n            replacement\
    \ = new_block.rstrip(\"\\n\")\n        updated = text[: match.start()] + replacement\
    \ + text[match.end() :]\n        return updated, updated != text\n\n    stripped\
    \ = text.rstrip(\"\\n\")\n    suffix = \"\\n\\n\" if stripped else \"\"\n    updated\
    \ = stripped + suffix + new_block\n    return updated, True\n\n\ndef check_file(relpath:\
    \ str, title: str) -> list[str]:\n    problems: list[str] = []\n    path = ROOT\
    \ / relpath\n    if not path.exists():\n        return [f\"missing file: {relpath}\"\
    ]\n    doc_path = expected_docs_path(relpath)\n    if not (ROOT / doc_path).exists():\n\
    \        problems.append(f\"missing md: {doc_path}\")\n\n    text = path.read_text()\n\
    \    match = MANAGED_BLOCK_RE.search(text)\n    if not match:\n        problems.append(f\"\
    missing managed block: {relpath}\")\n        return problems\n\n    current_title\
    \ = match.group(\"title\")\n    current_docs = match.group(\"docs\")\n    if current_title\
    \ != title:\n        problems.append(f\"title mismatch: {relpath}\")\n    if current_docs\
    \ != doc_path:\n        problems.append(f\"docs mismatch: {relpath} -> {current_docs}\"\
    )\n    return problems\n\n\ndef main() -> int:\n    parser = argparse.ArgumentParser(description=\"\
    sync @brief/@docs comments from meta/doc_titles.yml\")\n    parser.add_argument(\"\
    --write\", action=\"store_true\", help=\"rewrite source files to match meta/doc_titles.yml\"\
    )\n    args = parser.parse_args()\n\n    titles = load_titles(TITLE_FILE)\n  \
    \  doc_files = collect_doc_files()\n\n    problems: list[str] = []\n    for relpath\
    \ in sorted(titles):\n        if relpath not in doc_files:\n            problems.append(f\"\
    title entry without matching md-backed file: {relpath}\")\n    for relpath in\
    \ sorted(doc_files):\n        text = (ROOT / relpath).read_text()\n        if\
    \ \"@docs\" in text and relpath not in titles:\n            problems.append(f\"\
    file has @docs but no title entry: {relpath}\")\n    for relpath, title in sorted(titles.items()):\n\
    \        problems.extend(check_file(relpath, title))\n\n    if args.write:\n \
    \       changed = 0\n        for relpath, title in sorted(titles.items()):\n \
    \           path = ROOT / relpath\n            if not path.exists():\n       \
    \         continue\n            updated, is_changed = replace_block(path.read_text(),\
    \ relpath, title)\n            if is_changed:\n                path.write_text(updated)\n\
    \                changed += 1\n        print(f\"updated {changed} files\")\n\n\
    \    if problems:\n        for problem in problems:\n            print(problem,\
    \ file=sys.stderr)\n        return 1\n\n    print(f\"ok: {len(titles)} title entries\"\
    )\n    return 0\n\n\nif __name__ == \"__main__\":\n    raise SystemExit(main())\n"
  dependsOn: []
  isVerificationFile: false
  path: scripts/sync_doc_titles.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: scripts/sync_doc_titles.py
layout: document
redirect_from:
- /library/scripts/sync_doc_titles.py
- /library/scripts/sync_doc_titles.py.html
title: scripts/sync_doc_titles.py
---
