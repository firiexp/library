---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/convex_hull.cpp
    title: "\u51F8\u5305(Convex Hull)"
  - icon: ':heavy_check_mark:'
    path: geometry/int_point.cpp
    title: "\u6574\u6570\u5EA7\u6A19\u70B9"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_furthest_pair.test.cpp
    title: test/yosupo_aplusb_furthest_pair.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_furthest_pair.test.cpp
    title: test/yosupo_furthest_pair.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u9060\u70B9\u5BFE"
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
    \ \u51F8\u5305(Convex Hull)\n */\n#line 2 \"geometry/furthest_pair.cpp\"\n\npair<int,\
    \ int> furthest_pair(const vector<IntPoint> &points) {\n    assert(points.size()\
    \ >= 2);\n    auto hull = convex_hull(points);\n    int n = hull.size();\n   \
    \ if (n == 1) return {0, 1};\n    auto distance_squared = [&](int i, int j) {\n\
    \        __int128 dx = static_cast<__int128>(hull[i].x) - hull[j].x;\n       \
    \ __int128 dy = static_cast<__int128>(hull[i].y) - hull[j].y;\n        return\
    \ dx * dx + dy * dy;\n    };\n    pair<int, int> best = {0, 1};\n    __int128\
    \ best_distance = distance_squared(0, 1);\n    auto update = [&](int i, int j)\
    \ {\n        __int128 d = distance_squared(i, j);\n        if (d > best_distance)\
    \ {\n            best_distance = d;\n            best = {i, j};\n        }\n \
    \   };\n    if (n > 2) {\n        int j = 1;\n        for (int i = 0; i < n; ++i)\
    \ {\n            int next_i = (i + 1) % n;\n            auto height = [&](int\
    \ v) { return cross(hull[i], hull[next_i], hull[v]); };\n            while (height((j\
    \ + 1) % n) > height(j)) j = (j + 1) % n;\n            update(i, j);\n       \
    \     update(next_i, j);\n            int next_j = (j + 1) % n;\n            if\
    \ (height(next_j) == height(j)) {\n                update(i, next_j);\n      \
    \          update(next_i, next_j);\n            }\n        }\n    }\n    pair<int,\
    \ int> result = {-1, -1};\n    for (int i = 0; i < int(points.size()); ++i) {\n\
    \        if (points[i] == hull[best.first]) result.first = i;\n        if (points[i]\
    \ == hull[best.second]) result.second = i;\n        if (result.first != -1 &&\
    \ result.second != -1) break;\n    }\n    return result;\n}\n\n/**\n * @brief\
    \ \u6700\u9060\u70B9\u5BFE\n */\n"
  code: "#include \"convex_hull.cpp\"\n\npair<int, int> furthest_pair(const vector<IntPoint>\
    \ &points) {\n    assert(points.size() >= 2);\n    auto hull = convex_hull(points);\n\
    \    int n = hull.size();\n    if (n == 1) return {0, 1};\n    auto distance_squared\
    \ = [&](int i, int j) {\n        __int128 dx = static_cast<__int128>(hull[i].x)\
    \ - hull[j].x;\n        __int128 dy = static_cast<__int128>(hull[i].y) - hull[j].y;\n\
    \        return dx * dx + dy * dy;\n    };\n    pair<int, int> best = {0, 1};\n\
    \    __int128 best_distance = distance_squared(0, 1);\n    auto update = [&](int\
    \ i, int j) {\n        __int128 d = distance_squared(i, j);\n        if (d > best_distance)\
    \ {\n            best_distance = d;\n            best = {i, j};\n        }\n \
    \   };\n    if (n > 2) {\n        int j = 1;\n        for (int i = 0; i < n; ++i)\
    \ {\n            int next_i = (i + 1) % n;\n            auto height = [&](int\
    \ v) { return cross(hull[i], hull[next_i], hull[v]); };\n            while (height((j\
    \ + 1) % n) > height(j)) j = (j + 1) % n;\n            update(i, j);\n       \
    \     update(next_i, j);\n            int next_j = (j + 1) % n;\n            if\
    \ (height(next_j) == height(j)) {\n                update(i, next_j);\n      \
    \          update(next_i, next_j);\n            }\n        }\n    }\n    pair<int,\
    \ int> result = {-1, -1};\n    for (int i = 0; i < int(points.size()); ++i) {\n\
    \        if (points[i] == hull[best.first]) result.first = i;\n        if (points[i]\
    \ == hull[best.second]) result.second = i;\n        if (result.first != -1 &&\
    \ result.second != -1) break;\n    }\n    return result;\n}\n\n/**\n * @brief\
    \ \u6700\u9060\u70B9\u5BFE\n */\n"
  dependsOn:
  - geometry/convex_hull.cpp
  - geometry/int_point.cpp
  isVerificationFile: false
  path: geometry/furthest_pair.cpp
  requiredBy: []
  timestamp: '2026-10-16 00:52:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_furthest_pair.test.cpp
  - test/yosupo_aplusb_furthest_pair.test.cpp
documentation_of: geometry/furthest_pair.cpp
layout: document
title: "\u6700\u9060\u70B9\u5BFE"
---

## 説明
整数点集合から、距離が最大の2点の元の添字を返す。
時間計算量は $O(N\log N)$、追加領域は $O(N)$。

## できること
- `pair<int, int> furthest_pair(const vector<IntPoint>& points)`
  最遠点対の異なる2つの添字を返す。`points.size() >= 2` を前提とする。同距離の組が複数ある場合は任意の1組を返す

## 使い方
点列は未整列のまま渡せる。入力は変更しない。
重複点や全点が共線の場合も扱う。全点が一致する場合は `{0, 1}` を返す。

```cpp
vector<IntPoint> points = { {1, 2}, {3, 6}, {2, 1}};
auto [i, j] = furthest_pair(points);
```

## 実装上の補足
各座標は $|x|, |y| \le 10^{18}$ とする。
差分を取る前に `__int128` へ変換し、外積・距離二乗を整数で比較する。
この範囲では外積の絶対値・距離二乗は $8\times10^{36}$ 以下となり、符号付き `__int128` に収まる。
