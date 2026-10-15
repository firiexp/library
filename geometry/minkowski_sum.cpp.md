---
category: "\u5E7E\u4F55"
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
    path: test/yosupo_aplusb_minkowski_sum.test.cpp
    title: test/yosupo_aplusb_minkowski_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6574\u6570\u51F8\u591A\u89D2\u5F62\u306E\u30DF\u30F3\u30B3\u30D5\
      \u30B9\u30AD\u30FC\u548C"
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
    \ \u51F8\u5305(Convex Hull)\n */\n#line 2 \"geometry/minkowski_sum.cpp\"\n\nvector<IntPoint>\
    \ minkowski_sum(const vector<IntPoint> &a, const vector<IntPoint> &b) {\n    if\
    \ (a.empty() || b.empty()) return {};\n    int n = a.size(), m = b.size();\n \
    \   int p = min_element(a.begin(), a.end()) - a.begin();\n    int q = min_element(b.begin(),\
    \ b.end()) - b.begin();\n    vector<IntPoint> result;\n    result.reserve(n +\
    \ m);\n    if (n == 1 || m == 1) {\n        for (int k = 0; k < max(n, m); ++k)\
    \ {\n            const auto &u = a[(p + k) % n];\n            const auto &v =\
    \ b[(q + k) % m];\n            result.emplace_back(u.x + v.x, u.y + v.y);\n  \
    \      }\n        return result;\n    }\n    for (int i = 0, j = 0; i < n || j\
    \ < m;) {\n        result.emplace_back(a[p].x + b[q].x, a[p].y + b[q].y);\n  \
    \      int next_p = (p + 1) % n, next_q = (q + 1) % m;\n        int order;\n \
    \       if (i == n) order = 1;\n        else if (j == m) order = -1;\n       \
    \ else {\n            __int128 ax = static_cast<__int128>(a[next_p].x) - a[p].x;\n\
    \            __int128 ay = static_cast<__int128>(a[next_p].y) - a[p].y;\n    \
    \        __int128 bx = static_cast<__int128>(b[next_q].x) - b[q].x;\n        \
    \    __int128 by = static_cast<__int128>(b[next_q].y) - b[q].y;\n            bool\
    \ half_a = ax < 0 || (ax == 0 && ay < 0);\n            bool half_b = bx < 0 ||\
    \ (bx == 0 && by < 0);\n            __int128 turn = ax * by - ay * bx;\n     \
    \       order = half_a != half_b ? (half_a ? 1 : -1) : turn > 0 ? -1 : turn <\
    \ 0 ? 1 : 0;\n        }\n        if (order <= 0) {\n            p = next_p;\n\
    \            ++i;\n        }\n        if (order >= 0) {\n            q = next_q;\n\
    \            ++j;\n        }\n    }\n    return result;\n}\n\n/**\n * @brief \u6574\
    \u6570\u51F8\u591A\u89D2\u5F62\u306E\u30DF\u30F3\u30B3\u30D5\u30B9\u30AD\u30FC\
    \u548C\n */\n"
  code: "#include \"convex_hull.cpp\"\n\nvector<IntPoint> minkowski_sum(const vector<IntPoint>\
    \ &a, const vector<IntPoint> &b) {\n    if (a.empty() || b.empty()) return {};\n\
    \    int n = a.size(), m = b.size();\n    int p = min_element(a.begin(), a.end())\
    \ - a.begin();\n    int q = min_element(b.begin(), b.end()) - b.begin();\n   \
    \ vector<IntPoint> result;\n    result.reserve(n + m);\n    if (n == 1 || m ==\
    \ 1) {\n        for (int k = 0; k < max(n, m); ++k) {\n            const auto\
    \ &u = a[(p + k) % n];\n            const auto &v = b[(q + k) % m];\n        \
    \    result.emplace_back(u.x + v.x, u.y + v.y);\n        }\n        return result;\n\
    \    }\n    for (int i = 0, j = 0; i < n || j < m;) {\n        result.emplace_back(a[p].x\
    \ + b[q].x, a[p].y + b[q].y);\n        int next_p = (p + 1) % n, next_q = (q +\
    \ 1) % m;\n        int order;\n        if (i == n) order = 1;\n        else if\
    \ (j == m) order = -1;\n        else {\n            __int128 ax = static_cast<__int128>(a[next_p].x)\
    \ - a[p].x;\n            __int128 ay = static_cast<__int128>(a[next_p].y) - a[p].y;\n\
    \            __int128 bx = static_cast<__int128>(b[next_q].x) - b[q].x;\n    \
    \        __int128 by = static_cast<__int128>(b[next_q].y) - b[q].y;\n        \
    \    bool half_a = ax < 0 || (ax == 0 && ay < 0);\n            bool half_b = bx\
    \ < 0 || (bx == 0 && by < 0);\n            __int128 turn = ax * by - ay * bx;\n\
    \            order = half_a != half_b ? (half_a ? 1 : -1) : turn > 0 ? -1 : turn\
    \ < 0 ? 1 : 0;\n        }\n        if (order <= 0) {\n            p = next_p;\n\
    \            ++i;\n        }\n        if (order >= 0) {\n            q = next_q;\n\
    \            ++j;\n        }\n    }\n    return result;\n}\n\n/**\n * @brief \u6574\
    \u6570\u51F8\u591A\u89D2\u5F62\u306E\u30DF\u30F3\u30B3\u30D5\u30B9\u30AD\u30FC\
    \u548C\n */\n"
  dependsOn:
  - geometry/convex_hull.cpp
  - geometry/int_point.cpp
  isVerificationFile: false
  path: geometry/minkowski_sum.cpp
  requiredBy: []
  timestamp: '2026-10-16 00:52:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_minkowski_sum.test.cpp
date: 2026-10-16
documentation_of: geometry/minkowski_sum.cpp
layout: document
tags: "\u5E7E\u4F55"
title: "\u6574\u6570\u51F8\u591A\u89D2\u5F62\u306E\u30DF\u30F3\u30B3\u30D5\u30B9\u30AD\
  \u30FC\u548C"
---

## 説明
整数凸多角形 $A, B$ のミンコフスキー和 $A+B = \{a+b \mid a \in A, b \in B\}$ を求める。

## できること
- `vector<IntPoint> minkowski_sum(const vector<IntPoint>& a, const vector<IntPoint>& b)`
  和の凸包を辞書順最小の点から反時計回りで返す。重複点と辺上の中間点は除く。どちらかが空なら空配列。最悪 $O(|A|+|B|)$ 時間、返却領域 $O(|A|+|B|)$、入力と出力を除く追加領域 $O(1)$

## 使い方
各入力は反時計回りの凸包の頂点列とし、重複点・辺上の中間点・末尾の閉点を含めない。開始位置は任意で、`convex_hull` の結果をそのまま渡せる。
1点は点、2点は線分として扱う。入力は変更しない。
各呼び出しの入力座標は $|x|, |y| \le 10^{18}$ とする。出力座標の絶対値は $2\times10^{18}$ 以下になる。

```cpp
vector<IntPoint> a = convex_hull(points_a);
vector<IntPoint> b = convex_hull(points_b);
auto sum = minkowski_sum(a, b);
```

## 実装上の補足
辺を偏角順に併合し、同方向の平行辺をまとめる。差分を取る前に `__int128` へ変換し、浮動小数点数は使わない。
