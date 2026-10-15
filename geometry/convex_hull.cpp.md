---
category: "\u5E7E\u4F55"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/int_point.cpp
    title: "\u6574\u6570\u5EA7\u6A19\u70B9"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/furthest_pair.cpp
    title: "\u6700\u9060\u70B9\u5BFE"
  - icon: ':heavy_check_mark:'
    path: geometry/minkowski_sum.cpp
    title: "\u6574\u6570\u51F8\u591A\u89D2\u5F62\u306E\u30DF\u30F3\u30B3\u30D5\u30B9\
      \u30AD\u30FC\u548C"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_convex_hull.test.cpp
    title: test/yosupo_aplusb_convex_hull.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_furthest_pair.test.cpp
    title: test/yosupo_aplusb_furthest_pair.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_furthest_pair.test.cpp
    title: test/yosupo_aplusb_furthest_pair.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_minkowski_sum.test.cpp
    title: test/yosupo_aplusb_minkowski_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_minkowski_sum.test.cpp
    title: test/yosupo_aplusb_minkowski_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_furthest_pair.test.cpp
    title: test/yosupo_furthest_pair.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_static_convex_hull.test.cpp
    title: test/yosupo_static_convex_hull.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u51F8\u5305(Convex Hull)"
    links: []
  bundledCode: "#line 1 \"geometry/convex_hull.cpp\"\n\n\n\n#line 1 \"geometry/int_point.cpp\"\
    \n\n\n\nstruct IntPoint {\n    long long x = 0, y = 0;\n\n    IntPoint() = default;\n\
    \    IntPoint(long long x, long long y) : x(x), y(y) {}\n\n    bool operator<(const\
    \ IntPoint &p) const { return x < p.x || (!(p.x < x) && y < p.y); }\n    bool\
    \ operator==(const IntPoint &p) const { return x == p.x && y == p.y; }\n    bool\
    \ operator!=(const IntPoint &p) const { return !(*this == p); }\n    IntPoint\
    \ &operator+=(const IntPoint &p) { x += p.x; y += p.y; return *this; }\n    IntPoint\
    \ &operator-=(const IntPoint &p) { x -= p.x; y -= p.y; return *this; }\n    IntPoint\
    \ operator+(const IntPoint &p) const { return IntPoint(*this) += p; }\n    IntPoint\
    \ operator-(const IntPoint &p) const { return IntPoint(*this) -= p; }\n};\n\n\n\
    \n/**\n * @brief \u6574\u6570\u5EA7\u6A19\u70B9\n */\n#line 5 \"geometry/convex_hull.cpp\"\
    \n\n__int128 cross(IntPoint a, IntPoint b, IntPoint c) {\n    __int128 bx = static_cast<__int128>(b.x)\
    \ - a.x;\n    __int128 by = static_cast<__int128>(b.y) - a.y;\n    __int128 cx\
    \ = static_cast<__int128>(c.x) - a.x;\n    __int128 cy = static_cast<__int128>(c.y)\
    \ - a.y;\n    return bx * cy - by * cx;\n}\n\nvector<IntPoint> convex_hull(vector<IntPoint>\
    \ ps) {\n    sort(ps.begin(), ps.end());\n    ps.erase(unique(ps.begin(), ps.end()),\
    \ ps.end());\n    int n = ps.size();\n    if (n <= 2) return ps;\n\n    vector<IntPoint>\
    \ ch(2 * n);\n    int k = 0;\n    for (int i = 0; i < n; ++i) {\n        while\
    \ (k >= 2 && cross(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;\n        ch[k++] =\
    \ ps[i];\n    }\n    for (int i = n - 2, t = k + 1; i >= 0; --i) {\n        while\
    \ (k >= t && cross(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;\n        ch[k++] =\
    \ ps[i];\n    }\n    ch.resize(k - 1);\n    return ch;\n}\n\n\n\n/**\n * @brief\
    \ \u51F8\u5305(Convex Hull)\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_GEOMETRY_CONVEX_HULL_CPP\n#define FIRIEXP_LIBRARY_GEOMETRY_CONVEX_HULL_CPP\n\
    \n#include \"int_point.cpp\"\n\n__int128 cross(IntPoint a, IntPoint b, IntPoint\
    \ c) {\n    __int128 bx = static_cast<__int128>(b.x) - a.x;\n    __int128 by =\
    \ static_cast<__int128>(b.y) - a.y;\n    __int128 cx = static_cast<__int128>(c.x)\
    \ - a.x;\n    __int128 cy = static_cast<__int128>(c.y) - a.y;\n    return bx *\
    \ cy - by * cx;\n}\n\nvector<IntPoint> convex_hull(vector<IntPoint> ps) {\n  \
    \  sort(ps.begin(), ps.end());\n    ps.erase(unique(ps.begin(), ps.end()), ps.end());\n\
    \    int n = ps.size();\n    if (n <= 2) return ps;\n\n    vector<IntPoint> ch(2\
    \ * n);\n    int k = 0;\n    for (int i = 0; i < n; ++i) {\n        while (k >=\
    \ 2 && cross(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;\n        ch[k++] = ps[i];\n\
    \    }\n    for (int i = n - 2, t = k + 1; i >= 0; --i) {\n        while (k >=\
    \ t && cross(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;\n        ch[k++] = ps[i];\n\
    \    }\n    ch.resize(k - 1);\n    return ch;\n}\n\n#endif\n\n/**\n * @brief \u51F8\
    \u5305(Convex Hull)\n */\n"
  dependsOn:
  - geometry/int_point.cpp
  isVerificationFile: false
  path: geometry/convex_hull.cpp
  requiredBy:
  - geometry/minkowski_sum.cpp
  - geometry/furthest_pair.cpp
  timestamp: '2026-10-16 00:52:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_static_convex_hull.test.cpp
  - test/yosupo_furthest_pair.test.cpp
  - test/yosupo_aplusb_furthest_pair.test.cpp
  - test/yosupo_aplusb_furthest_pair.test.cpp
  - test/yosupo_aplusb_convex_hull.test.cpp
  - test/yosupo_aplusb_minkowski_sum.test.cpp
  - test/yosupo_aplusb_minkowski_sum.test.cpp
date: 2026-03-08
documentation_of: geometry/convex_hull.cpp
layout: document
tags: "\u5E7E\u4F55"
title: "\u51F8\u5305(Convex Hull)"
---

## 説明
整数座標点集合の凸包を Andrew's monotone chain で求める。
計算量は $O(N log N)$。

## できること
- `vector<IntPoint> convex_hull(vector<IntPoint> ps)`
  点集合の凸包の頂点を反時計回り順で返す。辺上の中間点と重複点は除く

## 使い方
点列を `vector<IntPoint>` で渡して使う。
各座標は $|x|, |y| \le 10^{18}$ とする。

## 実装上の補足
返り値は辞書順最小の点から始まる反時計回り順になる。
点数が `0`, `1`, `2` のときは重複を除いた結果をそのまま返す。
外積は差分を取る前に `__int128` へ変換して計算する。
