---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fft.cpp
    title: "\u4EFB\u610FMOD\u7573\u307F\u8FBC\u307F(3 NTT + Garner)"
  - icon: ':heavy_check_mark:'
    path: tree/frequency_table_of_tree_distance.cpp
    title: Frequency Table of Tree Distance
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
    links:
    - https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.20/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.20/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.20/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.20/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.20/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fft.cpp: line 346: found codes out of include guard\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\
    \n\n#include <bits/stdc++.h>\n\nusing namespace std;\n\n#include <cstdio>\n#include\
    \ <cstring>\n#include <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../tree/frequency_table_of_tree_distance.cpp\"\n\nint main() {\n\
    \    Scanner sc;\n    Printer pr;\n\n    int n;\n    sc.read(n);\n    vector<vector<int>>\
    \ g(n);\n    for (int i = 0; i < n - 1; ++i) {\n        int u, v;\n        sc.read(u,\
    \ v);\n        g[u].push_back(v);\n        g[v].push_back(u);\n    }\n\n    auto\
    \ ans = frequency_table_of_tree_distance(g);\n    for (int d = 1; d < n; ++d)\
    \ {\n        if (d != 1) pr.print(' ');\n        pr.print(ans[d]);\n    }\n  \
    \  pr.println();\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - tree/frequency_table_of_tree_distance.cpp
  - math/fft.cpp
  isVerificationFile: true
  path: test/yosupo_frequency_table_of_tree_distance.test.cpp
  requiredBy: []
  timestamp: '2026-03-23 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_frequency_table_of_tree_distance.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_frequency_table_of_tree_distance.test.cpp
- /verify/test/yosupo_frequency_table_of_tree_distance.test.cpp.html
title: test/yosupo_frequency_table_of_tree_distance.test.cpp
---
