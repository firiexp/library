---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"util/mo.cpp\"\nconst int B = 400;\n\nstruct Query {\n  \
    \  int l, r, no;\n    Query(int l, int r, int no) : l(l), r(r), no(no) {}\n  \
    \  Query() : l(0), r(0), no(0) {}\n    bool operator<(const Query &a) const {\n\
    \        int ablock = this->l / B, bblock = a.l / B;\n        if(ablock != bblock)\
    \ return ablock < bblock;\n        if(ablock & 1) return this->r < a.r;\n    \
    \    else return this->r > a.r;\n    }\n};\n"
  code: "const int B = 400;\n\nstruct Query {\n    int l, r, no;\n    Query(int l,\
    \ int r, int no) : l(l), r(r), no(no) {}\n    Query() : l(0), r(0), no(0) {}\n\
    \    bool operator<(const Query &a) const {\n        int ablock = this->l / B,\
    \ bblock = a.l / B;\n        if(ablock != bblock) return ablock < bblock;\n  \
    \      if(ablock & 1) return this->r < a.r;\n        else return this->r > a.r;\n\
    \    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: util/mo.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: util/mo.cpp
layout: document
redirect_from:
- /library/util/mo.cpp
- /library/util/mo.cpp.html
title: util/mo.cpp
---