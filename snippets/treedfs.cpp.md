---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"snippets/treedfs.cpp\"\ndeque<int> Q;\nstack<int> s;\nint\
    \ cnt = 0;\nvector<int> visited(n, 0), num(n);\ns.emplace(0);\nwhile (!s.empty())\
    \ {\n    int a = s.top();\n    s.pop();\n    visited[a]++;\n    num[a] = cnt++;\n\
    \    Q.emplace_front(a);\n    for (auto &&i : v[a]) {\n        if (!visited[i])\
    \ s.emplace(i);\n    }\n}\n"
  code: "deque<int> Q;\nstack<int> s;\nint cnt = 0;\nvector<int> visited(n, 0), num(n);\n\
    s.emplace(0);\nwhile (!s.empty()) {\n    int a = s.top();\n    s.pop();\n    visited[a]++;\n\
    \    num[a] = cnt++;\n    Q.emplace_front(a);\n    for (auto &&i : v[a]) {\n \
    \       if (!visited[i]) s.emplace(i);\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: snippets/treedfs.cpp
  requiredBy: []
  timestamp: '2026-03-12 00:17:10+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: snippets/treedfs.cpp
layout: document
redirect_from:
- /library/snippets/treedfs.cpp
- /library/snippets/treedfs.cpp.html
title: snippets/treedfs.cpp
---
