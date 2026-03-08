---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_static_range_inversions_query.test.cpp
    title: test/yosupo_static_range_inversions_query.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    _deprecated_at_docs: _md/mo.md
    document_title: Mo's Algorithm
    links: []
  bundledCode: "#line 1 \"util/mo.cpp\"\nconst int B = 400;\n\nstruct Query {\n  \
    \  int l, r, no;\n    Query(int l, int r, int no) : l(l), r(r), no(no) {}\n  \
    \  Query() : l(0), r(0), no(0) {}\n    bool operator<(const Query &a) const {\n\
    \        int ablock = this->l / B, bblock = a.l / B;\n        if(ablock != bblock)\
    \ return ablock < bblock;\n        if(ablock & 1) return this->r < a.r;\n    \
    \    else return this->r > a.r;\n    }\n};\n/*\nfor (auto &&X : query) {\n   \
    \ while(X.l < l) g(--l);\n    while(r < X.r) f(r++);\n    while(l < X.l) g(l++);\n\
    \    while(X.r < r) f(--r);\n    ans[X.no] = ans;\n}\n*/\n\n/**\n * @brief Mo's\
    \ Algorithm\n * @docs _md/mo.md\n */\n"
  code: "const int B = 400;\n\nstruct Query {\n    int l, r, no;\n    Query(int l,\
    \ int r, int no) : l(l), r(r), no(no) {}\n    Query() : l(0), r(0), no(0) {}\n\
    \    bool operator<(const Query &a) const {\n        int ablock = this->l / B,\
    \ bblock = a.l / B;\n        if(ablock != bblock) return ablock < bblock;\n  \
    \      if(ablock & 1) return this->r < a.r;\n        else return this->r > a.r;\n\
    \    }\n};\n/*\nfor (auto &&X : query) {\n    while(X.l < l) g(--l);\n    while(r\
    \ < X.r) f(r++);\n    while(l < X.l) g(l++);\n    while(X.r < r) f(--r);\n   \
    \ ans[X.no] = ans;\n}\n*/\n\n/**\n * @brief Mo's Algorithm\n * @docs _md/mo.md\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: util/mo.cpp
  requiredBy: []
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_static_range_inversions_query.test.cpp
documentation_of: util/mo.cpp
layout: document
redirect_from:
- /library/util/mo.cpp
- /library/util/mo.cpp.html
title: Mo's Algorithm
---
---
layout: post
title: Mo's algorithm
date: 2020-02-17
category: クエリ
tags: クエリ
---

## 説明
区間のマージは高速に出来ないが、区間を1つ広げる/縮めることが$O(p(N))$でできれば、$Q$個のクエリを$O(N \sqrt{Q p(N)})$ で処理できる。(ブロックサイズ$B$を適切に設定すれば)
