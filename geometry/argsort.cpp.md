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
  bundledCode: "#line 1 \"geometry/argsort.cpp\"\nusing Ar2 = array<int, 2>;\nvoid\
    \ argsort(vector<Ar2> &v){\n    auto pos = [&](Ar2 &x) -> int { if(x[1]) return\
    \ x[1] < 0 ? -1 : 1; else return x[0] > 0; };\n    sort(v.begin(),v.end(), [&](Ar2\
    \ a, Ar2 b){\n        if(pos(a) != pos(b)) return pos(a) < pos(b);\n        return\
    \ (ll)a[0]*b[1] > (ll)a[1]*b[0];\n    });\n}\n"
  code: "using Ar2 = array<int, 2>;\nvoid argsort(vector<Ar2> &v){\n    auto pos =\
    \ [&](Ar2 &x) -> int { if(x[1]) return x[1] < 0 ? -1 : 1; else return x[0] > 0;\
    \ };\n    sort(v.begin(),v.end(), [&](Ar2 a, Ar2 b){\n        if(pos(a) != pos(b))\
    \ return pos(a) < pos(b);\n        return (ll)a[0]*b[1] > (ll)a[1]*b[0];\n   \
    \ });\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: geometry/argsort.cpp
  requiredBy: []
  timestamp: '2021-04-21 13:28:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: geometry/argsort.cpp
layout: document
redirect_from:
- /library/geometry/argsort.cpp
- /library/geometry/argsort.cpp.html
title: geometry/argsort.cpp
---
