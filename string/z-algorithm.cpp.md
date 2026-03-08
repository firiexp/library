---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_many_aplusb_z_algorithm.test.cpp
    title: test/yosupo_many_aplusb_z_algorithm.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/z-algorithm.cpp\"\nvector<int> Z_algorithm(const\
    \ string &s){\n    int n = (int)s.size();\n    vector<int> res(n);\n    if (n\
    \ == 0) return res;\n    res[0] = n;\n    for (int i = 1, j = 0; i < n; ++i) {\n\
    \        int &k = res[i];\n        if (j + res[j] > i) k = min(res[i - j], j +\
    \ res[j] - i);\n        while (i + k < n && s[k] == s[i + k]) ++k;\n        if\
    \ (i + k > j + res[j]) j = i;\n    }\n    return res;\n}\n"
  code: "vector<int> Z_algorithm(const string &s){\n    int n = (int)s.size();\n \
    \   vector<int> res(n);\n    if (n == 0) return res;\n    res[0] = n;\n    for\
    \ (int i = 1, j = 0; i < n; ++i) {\n        int &k = res[i];\n        if (j +\
    \ res[j] > i) k = min(res[i - j], j + res[j] - i);\n        while (i + k < n &&\
    \ s[k] == s[i + k]) ++k;\n        if (i + k > j + res[j]) j = i;\n    }\n    return\
    \ res;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: string/z-algorithm.cpp
  requiredBy: []
  timestamp: '2026-03-08 18:06:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_many_aplusb_z_algorithm.test.cpp
documentation_of: string/z-algorithm.cpp
layout: document
redirect_from:
- /library/string/z-algorithm.cpp
- /library/string/z-algorithm.cpp.html
title: string/z-algorithm.cpp
---
