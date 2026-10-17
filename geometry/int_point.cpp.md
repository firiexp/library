---
category: "\u5E7E\u4F55"
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/argsort.cpp
    title: "\u504F\u89D2\u30BD\u30FC\u30C8(Argument Sort)"
  - icon: ':heavy_check_mark:'
    path: geometry/closest_pair.cpp
    title: Closest Pair
  - icon: ':heavy_check_mark:'
    path: geometry/convex_hull.cpp
    title: "\u51F8\u5305(Convex Hull)"
  - icon: ':heavy_check_mark:'
    path: geometry/furthest_pair.cpp
    title: "\u6700\u9060\u70B9\u5BFE"
  - icon: ':heavy_check_mark:'
    path: geometry/minkowski_sum.cpp
    title: "\u6574\u6570\u51F8\u591A\u89D2\u5F62\u306E\u30DF\u30F3\u30B3\u30D5\u30B9\
      \u30AD\u30FC\u548C"
  - icon: ':heavy_check_mark:'
    path: geometry/polygon_integral.cpp
    title: "\u591A\u89D2\u5F62\u306E\u533A\u9593\u9762\u7A4D\u3068\u91CD\u5FC3"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_argsort.test.cpp
    title: test/yosupo_aplusb_argsort.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_closest_pair.test.cpp
    title: test/yosupo_aplusb_closest_pair.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_convex_hull.test.cpp
    title: test/yosupo_aplusb_convex_hull.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_furthest_pair.test.cpp
    title: test/yosupo_aplusb_furthest_pair.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_minkowski_sum.test.cpp
    title: test/yosupo_aplusb_minkowski_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_polygon_integral.test.cpp
    title: test/yosupo_aplusb_polygon_integral.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_closest_pair.test.cpp
    title: test/yosupo_closest_pair.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_furthest_pair.test.cpp
    title: test/yosupo_furthest_pair.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_sort_points_by_argument.test.cpp
    title: test/yosupo_sort_points_by_argument.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_static_convex_hull.test.cpp
    title: test/yosupo_static_convex_hull.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6574\u6570\u5EA7\u6A19\u70B9"
    links: []
  bundledCode: "#line 1 \"geometry/int_point.cpp\"\n\n\n\nstruct IntPoint {\n    long\
    \ long x = 0, y = 0;\n\n    IntPoint() = default;\n    IntPoint(long long x, long\
    \ long y) : x(x), y(y) {}\n\n    bool operator<(const IntPoint &p) const { return\
    \ x < p.x || (!(p.x < x) && y < p.y); }\n    bool operator==(const IntPoint &p)\
    \ const { return x == p.x && y == p.y; }\n    bool operator!=(const IntPoint &p)\
    \ const { return !(*this == p); }\n    IntPoint &operator+=(const IntPoint &p)\
    \ { x += p.x; y += p.y; return *this; }\n    IntPoint &operator-=(const IntPoint\
    \ &p) { x -= p.x; y -= p.y; return *this; }\n    IntPoint operator+(const IntPoint\
    \ &p) const { return IntPoint(*this) += p; }\n    IntPoint operator-(const IntPoint\
    \ &p) const { return IntPoint(*this) -= p; }\n};\n\n\n\n/**\n * @brief \u6574\u6570\
    \u5EA7\u6A19\u70B9\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_GEOMETRY_INT_POINT_CPP\n#define FIRIEXP_LIBRARY_GEOMETRY_INT_POINT_CPP\n\
    \nstruct IntPoint {\n    long long x = 0, y = 0;\n\n    IntPoint() = default;\n\
    \    IntPoint(long long x, long long y) : x(x), y(y) {}\n\n    bool operator<(const\
    \ IntPoint &p) const { return x < p.x || (!(p.x < x) && y < p.y); }\n    bool\
    \ operator==(const IntPoint &p) const { return x == p.x && y == p.y; }\n    bool\
    \ operator!=(const IntPoint &p) const { return !(*this == p); }\n    IntPoint\
    \ &operator+=(const IntPoint &p) { x += p.x; y += p.y; return *this; }\n    IntPoint\
    \ &operator-=(const IntPoint &p) { x -= p.x; y -= p.y; return *this; }\n    IntPoint\
    \ operator+(const IntPoint &p) const { return IntPoint(*this) += p; }\n    IntPoint\
    \ operator-(const IntPoint &p) const { return IntPoint(*this) -= p; }\n};\n\n\
    #endif\n\n/**\n * @brief \u6574\u6570\u5EA7\u6A19\u70B9\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: geometry/int_point.cpp
  requiredBy:
  - geometry/minkowski_sum.cpp
  - geometry/closest_pair.cpp
  - geometry/polygon_integral.cpp
  - geometry/convex_hull.cpp
  - geometry/furthest_pair.cpp
  - geometry/argsort.cpp
  timestamp: '2026-10-16 00:52:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_static_convex_hull.test.cpp
  - test/yosupo_sort_points_by_argument.test.cpp
  - test/yosupo_furthest_pair.test.cpp
  - test/yosupo_aplusb_closest_pair.test.cpp
  - test/yosupo_aplusb_argsort.test.cpp
  - test/yosupo_closest_pair.test.cpp
  - test/yosupo_aplusb_furthest_pair.test.cpp
  - test/yosupo_aplusb_convex_hull.test.cpp
  - test/yosupo_aplusb_minkowski_sum.test.cpp
  - test/yosupo_aplusb_polygon_integral.test.cpp
date: 2026-10-16
documentation_of: geometry/int_point.cpp
layout: document
tags: "\u5E7E\u4F55"
title: "\u6574\u6570\u5EA7\u6A19\u70B9"
---

## 説明
整数幾何で共通に使う2次元の点を表す。

## できること
- `IntPoint(x, y)`：`long long` の座標 `x`, `y` を持つ点を作る。引数なしなら原点
- `p.x`, `p.y`：各座標を取得・変更する
- `p < q`：`x`, `y` の辞書順で比較する
- `p == q`, `p != q`：座標の一致・不一致を返す
- `p + q`, `p - q`, `p += q`, `p -= q`：座標ごとに加減算する。結果の各座標は `long long` に収まるものとする

## 使い方
整数凸包・最近点対・最遠点対・ミンコフスキー和には `vector<IntPoint>` を渡す。
座標範囲の制約は各アルゴリズムの説明に従う。

```cpp
IntPoint p{1, 2}, q{3, 4};
IntPoint sum = p + q;
auto [x, y] = sum;
```
