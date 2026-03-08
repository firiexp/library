---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_many_aplusb_argsort.test.cpp
    title: test/yosupo_many_aplusb_argsort.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"geometry/argsort.cpp\"\nusing Ar2 = array<int, 2>;\nvoid\
    \ argsort(vector<Ar2> &v)\n{\n    auto pos = [&](Ar2 &x) -> int\n    { if(x[1])\
    \ return x[1] < 0 ? -1 : 1; else return x[0] < 0; };\n    sort(v.begin(), v.end(),\
    \ [&](Ar2 a, Ar2 b)\n         {\n        if(pos(a) != pos(b)) return pos(a) <\
    \ pos(b);\n        return (ll)a[0]*b[1] > (ll)a[1]*b[0]; });\n}\n"
  code: "using Ar2 = array<int, 2>;\nvoid argsort(vector<Ar2> &v)\n{\n    auto pos\
    \ = [&](Ar2 &x) -> int\n    { if(x[1]) return x[1] < 0 ? -1 : 1; else return x[0]\
    \ < 0; };\n    sort(v.begin(), v.end(), [&](Ar2 a, Ar2 b)\n         {\n      \
    \  if(pos(a) != pos(b)) return pos(a) < pos(b);\n        return (ll)a[0]*b[1]\
    \ > (ll)a[1]*b[0]; });\n}"
  dependsOn: []
  isVerificationFile: false
  path: geometry/argsort.cpp
  requiredBy: []
  timestamp: '2023-03-07 12:28:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_many_aplusb_argsort.test.cpp
documentation_of: geometry/argsort.cpp
layout: document
redirect_from:
- /library/geometry/argsort.cpp
- /library/geometry/argsort.cpp.html
title: geometry/argsort.cpp
---
