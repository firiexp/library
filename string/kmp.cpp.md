---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_alds1_14_b.test.cpp
    title: test/aoj_alds1_14_b.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/kmp.cpp\"\nvector<int> kmp_table(const string &s){\n\
    \    int n = s.size();\n    vector<int> table(n + 1);\n    table[0] = -1;\n  \
    \  for (int i = 0, j = -1; i < n;) {\n        while(j >= 0 && s[i] != s[j]) j\
    \ = table[j];\n        i++, j++;\n        table[i] = j;\n    }\n    return table;\n\
    }\n\nvector<int> kmp_search(const string &text, const string &pattern){\n    int\
    \ n = text.size(), m = pattern.size();\n    vector<int> res;\n    if(pattern.empty()){\n\
    \        res.resize(n + 1);\n        iota(res.begin(), res.end(), 0);\n      \
    \  return res;\n    }\n    auto table = kmp_table(pattern);\n    for (int i =\
    \ 0, j = 0; i < n;) {\n        while(j >= 0 && text[i] != pattern[j]) j = table[j];\n\
    \        i++, j++;\n        if(j == m){\n            res.emplace_back(i - j);\n\
    \            j = table[j];\n        }\n    }\n    return res;\n}\n"
  code: "vector<int> kmp_table(const string &s){\n    int n = s.size();\n    vector<int>\
    \ table(n + 1);\n    table[0] = -1;\n    for (int i = 0, j = -1; i < n;) {\n \
    \       while(j >= 0 && s[i] != s[j]) j = table[j];\n        i++, j++;\n     \
    \   table[i] = j;\n    }\n    return table;\n}\n\nvector<int> kmp_search(const\
    \ string &text, const string &pattern){\n    int n = text.size(), m = pattern.size();\n\
    \    vector<int> res;\n    if(pattern.empty()){\n        res.resize(n + 1);\n\
    \        iota(res.begin(), res.end(), 0);\n        return res;\n    }\n    auto\
    \ table = kmp_table(pattern);\n    for (int i = 0, j = 0; i < n;) {\n        while(j\
    \ >= 0 && text[i] != pattern[j]) j = table[j];\n        i++, j++;\n        if(j\
    \ == m){\n            res.emplace_back(i - j);\n            j = table[j];\n  \
    \      }\n    }\n    return res;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: string/kmp.cpp
  requiredBy: []
  timestamp: '2026-03-08 01:01:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj_alds1_14_b.test.cpp
documentation_of: string/kmp.cpp
layout: document
redirect_from:
- /library/string/kmp.cpp
- /library/string/kmp.cpp.html
title: string/kmp.cpp
---
