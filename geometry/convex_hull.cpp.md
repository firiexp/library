---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_static_convex_hull.test.cpp
    title: test/yosupo_static_convex_hull.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    _deprecated_at_docs: _md/convex_hull.md
    document_title: "\u51F8\u5305(Convex Hull)"
    links: []
  bundledCode: "#line 1 \"geometry/convex_hull.cpp\"\nusing IntPoint = pair<ll, ll>;\n\
    \nll cross(IntPoint a, IntPoint b, IntPoint c) {\n    b.first -= a.first;\n  \
    \  b.second -= a.second;\n    c.first -= a.first;\n    c.second -= a.second;\n\
    \    return b.first * c.second - b.second * c.first;\n}\n\nvector<IntPoint> convex_hull(vector<IntPoint>\
    \ ps) {\n    sort(ps.begin(), ps.end());\n    ps.erase(unique(ps.begin(), ps.end()),\
    \ ps.end());\n    int n = ps.size();\n    if (n <= 2) return ps;\n\n    vector<IntPoint>\
    \ ch(2 * n);\n    int k = 0;\n    for (int i = 0; i < n; ++i) {\n        while\
    \ (k >= 2 && cross(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;\n        ch[k++] =\
    \ ps[i];\n    }\n    for (int i = n - 2, t = k + 1; i >= 0; --i) {\n        while\
    \ (k >= t && cross(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;\n        ch[k++] =\
    \ ps[i];\n    }\n    ch.resize(k - 1);\n    return ch;\n}\n\n/**\n * @brief \u51F8\
    \u5305(Convex Hull)\n * @docs _md/convex_hull.md\n */\n"
  code: "using IntPoint = pair<ll, ll>;\n\nll cross(IntPoint a, IntPoint b, IntPoint\
    \ c) {\n    b.first -= a.first;\n    b.second -= a.second;\n    c.first -= a.first;\n\
    \    c.second -= a.second;\n    return b.first * c.second - b.second * c.first;\n\
    }\n\nvector<IntPoint> convex_hull(vector<IntPoint> ps) {\n    sort(ps.begin(),\
    \ ps.end());\n    ps.erase(unique(ps.begin(), ps.end()), ps.end());\n    int n\
    \ = ps.size();\n    if (n <= 2) return ps;\n\n    vector<IntPoint> ch(2 * n);\n\
    \    int k = 0;\n    for (int i = 0; i < n; ++i) {\n        while (k >= 2 && cross(ch[k\
    \ - 2], ch[k - 1], ps[i]) <= 0) --k;\n        ch[k++] = ps[i];\n    }\n    for\
    \ (int i = n - 2, t = k + 1; i >= 0; --i) {\n        while (k >= t && cross(ch[k\
    \ - 2], ch[k - 1], ps[i]) <= 0) --k;\n        ch[k++] = ps[i];\n    }\n    ch.resize(k\
    \ - 1);\n    return ch;\n}\n\n/**\n * @brief \u51F8\u5305(Convex Hull)\n * @docs\
    \ _md/convex_hull.md\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: geometry/convex_hull.cpp
  requiredBy: []
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_static_convex_hull.test.cpp
documentation_of: geometry/convex_hull.cpp
layout: document
redirect_from:
- /library/geometry/convex_hull.cpp
- /library/geometry/convex_hull.cpp.html
title: "\u51F8\u5305(Convex Hull)"
---
---
layout: post
title: Convex Hull
date: 2026-03-08
category: 幾何
tags: 幾何
---

## 説明
整数座標点集合の凸包を Andrew's monotone chain で求める。
計算量は `O(N log N)`。

## できること
- `vector<pair<ll, ll>> convex_hull(vector<pair<ll, ll>> ps)`
  点集合の凸包の頂点を反時計回り順で返す。辺上の中間点と重複点は除く

## 使い方
点列を `vector<pair<ll, ll>>` で渡して使う。


## 実装上の補足
返り値は辞書順最小の点から始まる反時計回り順になる。
点数が `0`, `1`, `2` のときは重複を除いた結果をそのまま返す。
