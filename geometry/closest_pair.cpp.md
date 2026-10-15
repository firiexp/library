---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/int_point.cpp
    title: "\u6574\u6570\u5EA7\u6A19\u70B9"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_closest_pair.test.cpp
    title: test/yosupo_aplusb_closest_pair.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_closest_pair.test.cpp
    title: test/yosupo_closest_pair.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Closest Pair
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
    \u5EA7\u6A19\u70B9\n */\n#line 2 \"geometry/closest_pair.cpp\"\n\npair<int, int>\
    \ closest_pair(const vector<IntPoint> &points) {\n    using Dist = __int128_t;\n\
    \    struct P {\n        long long x;\n        long long y;\n        int idx;\n\
    \    };\n\n    int n = points.size();\n    assert(n >= 2);\n    vector<P> ps(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        ps[i] = {points[i].x, points[i].y,\
    \ i};\n    }\n    sort(ps.begin(), ps.end(), [](const P &a, const P &b) {\n  \
    \      if (a.x != b.x) return a.x < b.x;\n        if (a.y != b.y) return a.y <\
    \ b.y;\n        return a.idx < b.idx;\n    });\n\n    Dist best = -1;\n    pair<int,\
    \ int> ans = {-1, -1};\n    auto update = [&](const P &a, const P &b) {\n    \
    \    Dist dx = Dist(a.x) - Dist(b.x);\n        Dist dy = Dist(a.y) - Dist(b.y);\n\
    \        Dist d = dx * dx + dy * dy;\n        pair<int, int> cand = {a.idx, b.idx};\n\
    \        if (best == -1 || d < best) {\n            best = d;\n            ans\
    \ = cand;\n        }\n    };\n    update(ps[0], ps[1]);\n\n    vector<int> ord(n),\
    \ scratch(n);\n    auto dfs = [&](auto &&self, int l, int r) -> void {\n     \
    \   if (r - l == 1) {\n            ord[l] = l;\n            return;\n        }\n\
    \        int m = (l + r) >> 1;\n        long long mx = ps[m].x;\n        self(self,\
    \ l, m);\n        self(self, m, r);\n        int i = l, j = m;\n        for (int\
    \ k = l; k < r; ++k) {\n            if (j == r || (i < m && ps[ord[i]].y < ps[ord[j]].y))\
    \ {\n                scratch[k] = ord[i++];\n            } else {\n          \
    \      scratch[k] = ord[j++];\n            }\n        }\n        copy(scratch.begin()\
    \ + l, scratch.begin() + r, ord.begin() + l);\n        int count = 0;\n      \
    \  for (int k = l; k < r; ++k) {\n            int idx = ord[k];\n            Dist\
    \ dx = Dist(ps[idx].x) - Dist(mx);\n            if (dx * dx > best) continue;\n\
    \            for (int t = count - 1; t >= 0; --t) {\n                int idy =\
    \ scratch[l + t];\n                Dist dy = Dist(ps[idx].y) - Dist(ps[idy].y);\n\
    \                if (best == 0 || dy * dy > best) break;\n                update(ps[idx],\
    \ ps[idy]);\n            }\n            scratch[l + count++] = idx;\n        }\n\
    \    };\n    dfs(dfs, 0, n);\n    return ans;\n}\n\n/**\n * @brief Closest Pair\n\
    \ */\n"
  code: "#include \"int_point.cpp\"\n\npair<int, int> closest_pair(const vector<IntPoint>\
    \ &points) {\n    using Dist = __int128_t;\n    struct P {\n        long long\
    \ x;\n        long long y;\n        int idx;\n    };\n\n    int n = points.size();\n\
    \    assert(n >= 2);\n    vector<P> ps(n);\n    for (int i = 0; i < n; ++i) {\n\
    \        ps[i] = {points[i].x, points[i].y, i};\n    }\n    sort(ps.begin(), ps.end(),\
    \ [](const P &a, const P &b) {\n        if (a.x != b.x) return a.x < b.x;\n  \
    \      if (a.y != b.y) return a.y < b.y;\n        return a.idx < b.idx;\n    });\n\
    \n    Dist best = -1;\n    pair<int, int> ans = {-1, -1};\n    auto update = [&](const\
    \ P &a, const P &b) {\n        Dist dx = Dist(a.x) - Dist(b.x);\n        Dist\
    \ dy = Dist(a.y) - Dist(b.y);\n        Dist d = dx * dx + dy * dy;\n        pair<int,\
    \ int> cand = {a.idx, b.idx};\n        if (best == -1 || d < best) {\n       \
    \     best = d;\n            ans = cand;\n        }\n    };\n    update(ps[0],\
    \ ps[1]);\n\n    vector<int> ord(n), scratch(n);\n    auto dfs = [&](auto &&self,\
    \ int l, int r) -> void {\n        if (r - l == 1) {\n            ord[l] = l;\n\
    \            return;\n        }\n        int m = (l + r) >> 1;\n        long long\
    \ mx = ps[m].x;\n        self(self, l, m);\n        self(self, m, r);\n      \
    \  int i = l, j = m;\n        for (int k = l; k < r; ++k) {\n            if (j\
    \ == r || (i < m && ps[ord[i]].y < ps[ord[j]].y)) {\n                scratch[k]\
    \ = ord[i++];\n            } else {\n                scratch[k] = ord[j++];\n\
    \            }\n        }\n        copy(scratch.begin() + l, scratch.begin() +\
    \ r, ord.begin() + l);\n        int count = 0;\n        for (int k = l; k < r;\
    \ ++k) {\n            int idx = ord[k];\n            Dist dx = Dist(ps[idx].x)\
    \ - Dist(mx);\n            if (dx * dx > best) continue;\n            for (int\
    \ t = count - 1; t >= 0; --t) {\n                int idy = scratch[l + t];\n \
    \               Dist dy = Dist(ps[idx].y) - Dist(ps[idy].y);\n               \
    \ if (best == 0 || dy * dy > best) break;\n                update(ps[idx], ps[idy]);\n\
    \            }\n            scratch[l + count++] = idx;\n        }\n    };\n \
    \   dfs(dfs, 0, n);\n    return ans;\n}\n\n/**\n * @brief Closest Pair\n */\n"
  dependsOn:
  - geometry/int_point.cpp
  isVerificationFile: false
  path: geometry/closest_pair.cpp
  requiredBy: []
  timestamp: '2026-10-16 00:52:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_closest_pair.test.cpp
  - test/yosupo_closest_pair.test.cpp
documentation_of: geometry/closest_pair.cpp
layout: document
title: Closest Pair
---
## 説明
平面上の整数点集合から、距離が最小の 2 点の元の添字を返す。
分割統治で解き、計算量は $O(N log N)$。

## できること
- `pair<int, int> closest_pair(const vector<IntPoint>& points)`
  最短距離を持つ 2 点の添字を返す。`points.size() < 2` は想定しない

## 使い方
`vector<IntPoint>` を入力順のまま渡すと、返り値はその元の添字になる。
同じ座標の点が複数あってもよい。

## 実装上の補足
- 距離比較は二乗距離で行うので平方根は使わない
- 差の二乗が 64 bit を超える可能性があるため、内部計算は `__int128_t` を使う
- 複数の最短対があるとき、どれを返すかは規定しない
