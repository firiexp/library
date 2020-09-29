---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tree/treedfs.cpp\"\ndeque<int> Q;\nstack<int> s;\nint cnt\
    \ = 0;\nvector<int> visited(n, 0), num(n);\ns.emplace(0);\nwhile(!s.empty()){\n\
    \    int a = s.top(); s.pop();\n    visited[a]++;\n    num[a] = cnt++;\n    Q.emplace_front(a);\n\
    \    for (auto &&i : v[a]) {\n        if(!visited[i]) s.emplace(i);\n    }\n}\n"
  code: "deque<int> Q;\nstack<int> s;\nint cnt = 0;\nvector<int> visited(n, 0), num(n);\n\
    s.emplace(0);\nwhile(!s.empty()){\n    int a = s.top(); s.pop();\n    visited[a]++;\n\
    \    num[a] = cnt++;\n    Q.emplace_front(a);\n    for (auto &&i : v[a]) {\n \
    \       if(!visited[i]) s.emplace(i);\n    }\n}"
  dependsOn: []
  isVerificationFile: false
  path: tree/treedfs.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tree/treedfs.cpp
layout: document
redirect_from:
- /library/tree/treedfs.cpp
- /library/tree/treedfs.cpp.html
title: tree/treedfs.cpp
---
