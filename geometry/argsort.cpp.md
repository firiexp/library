---
category: "\u5E7E\u4F55"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/int_point.cpp
    title: "\u6574\u6570\u5EA7\u6A19\u70B9"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_argsort.test.cpp
    title: test/yosupo_aplusb_argsort.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_sort_points_by_argument.test.cpp
    title: test/yosupo_sort_points_by_argument.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u504F\u89D2\u30BD\u30FC\u30C8(Argument Sort)"
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
    \u5EA7\u6A19\u70B9\n */\n#line 2 \"geometry/argsort.cpp\"\n\nnamespace geometry_argsort_detail\
    \ {\ntemplate <class Wide, class T>\nint compare(T ax, T ay, T bx, T by) {\n \
    \   auto half = [](T x, T y) { return y ? (y < 0 ? -1 : 1) : int(x < 0); };\n\
    \    int a = half(ax, ay), b = half(bx, by);\n    if (a != b) return a < b ? -1\
    \ : 1;\n    Wide lhs = Wide(ax) * by, rhs = Wide(ay) * bx;\n    return lhs > rhs\
    \ ? -1 : lhs < rhs ? 1 : 0;\n}\n}\n\nusing Ar2 = array<int, 2>;\n\nvoid argsort(vector<Ar2>\
    \ &v) {\n    sort(v.begin(), v.end(), [](const Ar2 &a, const Ar2 &b) {\n     \
    \   return geometry_argsort_detail::compare<long long>(a[0], a[1], b[0], b[1])\
    \ < 0;\n    });\n}\n\nvoid argsort(vector<IntPoint> &v) {\n    sort(v.begin(),\
    \ v.end(), [](const IntPoint &a, const IntPoint &b) {\n        return geometry_argsort_detail::compare<__int128>(a.x,\
    \ a.y, b.x, b.y) < 0;\n    });\n}\n\nvector<int> arg_sort_indices(const vector<IntPoint>\
    \ &v) {\n    vector<int> order(v.size());\n    iota(order.begin(), order.end(),\
    \ 0);\n    sort(order.begin(), order.end(), [&](int i, int j) {\n        int c\
    \ = geometry_argsort_detail::compare<__int128>(v[i].x, v[i].y, v[j].x, v[j].y);\n\
    \        return c < 0 || (c == 0 && i < j);\n    });\n    return order;\n}\n\n\
    /**\n * @brief \u504F\u89D2\u30BD\u30FC\u30C8(Argument Sort)\n */\n"
  code: "#include \"int_point.cpp\"\n\nnamespace geometry_argsort_detail {\ntemplate\
    \ <class Wide, class T>\nint compare(T ax, T ay, T bx, T by) {\n    auto half\
    \ = [](T x, T y) { return y ? (y < 0 ? -1 : 1) : int(x < 0); };\n    int a = half(ax,\
    \ ay), b = half(bx, by);\n    if (a != b) return a < b ? -1 : 1;\n    Wide lhs\
    \ = Wide(ax) * by, rhs = Wide(ay) * bx;\n    return lhs > rhs ? -1 : lhs < rhs\
    \ ? 1 : 0;\n}\n}\n\nusing Ar2 = array<int, 2>;\n\nvoid argsort(vector<Ar2> &v)\
    \ {\n    sort(v.begin(), v.end(), [](const Ar2 &a, const Ar2 &b) {\n        return\
    \ geometry_argsort_detail::compare<long long>(a[0], a[1], b[0], b[1]) < 0;\n \
    \   });\n}\n\nvoid argsort(vector<IntPoint> &v) {\n    sort(v.begin(), v.end(),\
    \ [](const IntPoint &a, const IntPoint &b) {\n        return geometry_argsort_detail::compare<__int128>(a.x,\
    \ a.y, b.x, b.y) < 0;\n    });\n}\n\nvector<int> arg_sort_indices(const vector<IntPoint>\
    \ &v) {\n    vector<int> order(v.size());\n    iota(order.begin(), order.end(),\
    \ 0);\n    sort(order.begin(), order.end(), [&](int i, int j) {\n        int c\
    \ = geometry_argsort_detail::compare<__int128>(v[i].x, v[i].y, v[j].x, v[j].y);\n\
    \        return c < 0 || (c == 0 && i < j);\n    });\n    return order;\n}\n\n\
    /**\n * @brief \u504F\u89D2\u30BD\u30FC\u30C8(Argument Sort)\n */\n"
  dependsOn:
  - geometry/int_point.cpp
  isVerificationFile: false
  path: geometry/argsort.cpp
  requiredBy: []
  timestamp: '2026-10-18 01:34:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_sort_points_by_argument.test.cpp
  - test/yosupo_aplusb_argsort.test.cpp
date: 2026-03-08
documentation_of: geometry/argsort.cpp
layout: document
tags: "\u5E7E\u4F55"
title: "\u504F\u89D2\u30BD\u30FC\u30C8(Argument Sort)"
---

## 説明
整数ベクトルを偏角 $(-\pi, \pi]$ の昇順に並べる。
下半平面、正の $x$ 軸、上半平面、負の $x$ 軸の順に反時計回りとなる。
原点は偏角 $0$ として正の $x$ 軸と同じ方向に扱う。
計算量は $O(N \log N)$。

## できること
- `void argsort(vector<array<int, 2>>& v)`
  `v` を偏角順にその場で並べ替える。同方向の順序は未指定
- `void argsort(vector<IntPoint>& v)`
  整数座標点をその場で並べ替える。同方向の順序は未指定
- `vector<int> arg_sort_indices(const vector<IntPoint>& v)`
  入力を変更せず、偏角順の元 index を返す。同方向は元 index の昇順。追加領域 $O(N)$

## 使い方
`IntPoint` はこのファイルから読み込まれる。空列も渡せる。
点に重みなどが対応している場合は、返された index で元の配列を参照する。

```cpp
vector<IntPoint> points{ {4000000000LL, 0}, {0, -5000000000LL}, {0, 0} };
auto order = arg_sort_indices(points);
for (int i : order) use(points[i], weight[i]);
```

この例の `order` は `{1, 0, 2}` となる。

## 実装上の補足
半平面と整数の積で比較し、浮動小数点は使わない。
`array<int, 2>` 版の積は `long long`、`IntPoint` 版は乗算前に `__int128` へ変換する。
積同士を比較し、外積の差を作らないので、それぞれ `int` / `long long` の座標全域を扱える。
他の幾何関数の座標制約は変わらない。
