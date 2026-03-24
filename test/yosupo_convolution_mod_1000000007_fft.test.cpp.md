---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fft.cpp
    title: "\u4EFB\u610FMOD\u7573\u307F\u8FBC\u307F(3 NTT + Garner)"
  - icon: ':question:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  - icon: ':heavy_check_mark:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod_1000000007
    links:
    - https://judge.yosupo.jp/problem/convolution_mod_1000000007
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.20/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.20/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.20/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.20/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fft.cpp: line 346: found codes out of include guard\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod_1000000007\"\
    \n\n#include <bits/stdc++.h>\n\nstatic const int MOD = 1000000007;\nusing ll =\
    \ long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\nusing namespace\
    \ std;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\
    \n#include \"../util/fastio.cpp\"\n#include \"../math/fft.cpp\"\n\nint main()\
    \ {\n    Scanner sc;\n    Printer pr;\n\n    int n, m;\n    sc.read(n, m);\n \
    \   poly a(n), b(m);\n    for (int i = 0; i < n; ++i) {\n        int x;\n    \
    \    sc.read(x);\n        a[i] = x;\n    }\n    for (int i = 0; i < m; ++i) {\n\
    \        int x;\n        sc.read(x);\n        b[i] = x;\n    }\n    a *= b;\n\
    \    for (int i = 0; i < n + m - 1; ++i) {\n        if (i) pr.print(' ');\n  \
    \      pr.print(a[i].val);\n    }\n    pr.println();\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - math/fft.cpp
  - util/modint.cpp
  isVerificationFile: true
  path: test/yosupo_convolution_mod_1000000007_fft.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 13:47:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_convolution_mod_1000000007_fft.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_convolution_mod_1000000007_fft.test.cpp
- /verify/test/yosupo_convolution_mod_1000000007_fft.test.cpp.html
title: test/yosupo_convolution_mod_1000000007_fft.test.cpp
---
