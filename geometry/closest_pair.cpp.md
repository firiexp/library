---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_closest_pair.test.cpp
    title: test/yosupo_closest_pair.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Closest Pair
    links: []
  bundledCode: "#line 1 \"geometry/closest_pair.cpp\"\npair<int, int> closest_pair(const\
    \ vector<pair<long long, long long>> &points) {\n    using Dist = __int128_t;\n\
    \    struct P {\n        long long x;\n        long long y;\n        int idx;\n\
    \    };\n\n    int n = points.size();\n    assert(n >= 2);\n    vector<P> ps(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        ps[i] = {points[i].first, points[i].second,\
    \ i};\n    }\n    sort(ps.begin(), ps.end(), [](const P &a, const P &b) {\n  \
    \      if (a.x != b.x) return a.x < b.x;\n        if (a.y != b.y) return a.y <\
    \ b.y;\n        return a.idx < b.idx;\n    });\n\n    Dist best = -1;\n    pair<int,\
    \ int> ans = {-1, -1};\n    auto update = [&](const P &a, const P &b) {\n    \
    \    Dist dx = Dist(a.x) - Dist(b.x);\n        Dist dy = Dist(a.y) - Dist(b.y);\n\
    \        Dist d = dx * dx + dy * dy;\n        pair<int, int> cand = {a.idx, b.idx};\n\
    \        if (best == -1 || d < best) {\n            best = d;\n            ans\
    \ = cand;\n        }\n    };\n    update(ps[0], ps[1]);\n\n    auto dfs = [&](auto\
    \ &&self, int l, int r) -> vector<int> {\n        if (r - l == 1) return {l};\n\
    \        int m = (l + r) >> 1;\n        long long mx = ps[m].x;\n        vector<int>\
    \ left = self(self, l, m);\n        vector<int> right = self(self, m, r);\n  \
    \      vector<int> ord;\n        vector<int> near;\n        ord.reserve(r - l);\n\
    \        near.reserve(r - l);\n        int i = 0, j = 0;\n        while (i < (int)left.size()\
    \ || j < (int)right.size()) {\n            int idx;\n            if (j == (int)right.size()\
    \ || (i < (int)left.size() && ps[left[i]].y < ps[right[j]].y)) {\n           \
    \     idx = left[i++];\n            } else {\n                idx = right[j++];\n\
    \            }\n            ord.push_back(idx);\n            Dist dx = Dist(ps[idx].x)\
    \ - Dist(mx);\n            if (dx * dx > best) continue;\n            for (int\
    \ k = (int)near.size() - 1; k >= 0; --k) {\n                int idy = near[k];\n\
    \                Dist dy = Dist(ps[idx].y) - Dist(ps[idy].y);\n              \
    \  if (best == 0 || dy * dy > best) break;\n                update(ps[idx], ps[idy]);\n\
    \            }\n            near.push_back(idx);\n        }\n        return ord;\n\
    \    };\n    dfs(dfs, 0, n);\n    return ans;\n}\n\n/**\n * @brief Closest Pair\n\
    \ */\n"
  code: "pair<int, int> closest_pair(const vector<pair<long long, long long>> &points)\
    \ {\n    using Dist = __int128_t;\n    struct P {\n        long long x;\n    \
    \    long long y;\n        int idx;\n    };\n\n    int n = points.size();\n  \
    \  assert(n >= 2);\n    vector<P> ps(n);\n    for (int i = 0; i < n; ++i) {\n\
    \        ps[i] = {points[i].first, points[i].second, i};\n    }\n    sort(ps.begin(),\
    \ ps.end(), [](const P &a, const P &b) {\n        if (a.x != b.x) return a.x <\
    \ b.x;\n        if (a.y != b.y) return a.y < b.y;\n        return a.idx < b.idx;\n\
    \    });\n\n    Dist best = -1;\n    pair<int, int> ans = {-1, -1};\n    auto\
    \ update = [&](const P &a, const P &b) {\n        Dist dx = Dist(a.x) - Dist(b.x);\n\
    \        Dist dy = Dist(a.y) - Dist(b.y);\n        Dist d = dx * dx + dy * dy;\n\
    \        pair<int, int> cand = {a.idx, b.idx};\n        if (best == -1 || d <\
    \ best) {\n            best = d;\n            ans = cand;\n        }\n    };\n\
    \    update(ps[0], ps[1]);\n\n    auto dfs = [&](auto &&self, int l, int r) ->\
    \ vector<int> {\n        if (r - l == 1) return {l};\n        int m = (l + r)\
    \ >> 1;\n        long long mx = ps[m].x;\n        vector<int> left = self(self,\
    \ l, m);\n        vector<int> right = self(self, m, r);\n        vector<int> ord;\n\
    \        vector<int> near;\n        ord.reserve(r - l);\n        near.reserve(r\
    \ - l);\n        int i = 0, j = 0;\n        while (i < (int)left.size() || j <\
    \ (int)right.size()) {\n            int idx;\n            if (j == (int)right.size()\
    \ || (i < (int)left.size() && ps[left[i]].y < ps[right[j]].y)) {\n           \
    \     idx = left[i++];\n            } else {\n                idx = right[j++];\n\
    \            }\n            ord.push_back(idx);\n            Dist dx = Dist(ps[idx].x)\
    \ - Dist(mx);\n            if (dx * dx > best) continue;\n            for (int\
    \ k = (int)near.size() - 1; k >= 0; --k) {\n                int idy = near[k];\n\
    \                Dist dy = Dist(ps[idx].y) - Dist(ps[idy].y);\n              \
    \  if (best == 0 || dy * dy > best) break;\n                update(ps[idx], ps[idy]);\n\
    \            }\n            near.push_back(idx);\n        }\n        return ord;\n\
    \    };\n    dfs(dfs, 0, n);\n    return ans;\n}\n\n/**\n * @brief Closest Pair\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: geometry/closest_pair.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_closest_pair.test.cpp
documentation_of: geometry/closest_pair.cpp
layout: document
title: Closest Pair
---
## 説明
平面上の整数点集合から、距離が最小の 2 点の元の添字を返す。
分割統治で解き、計算量は $O(N log N)$。

## できること
- `pair<int, int> closest_pair(const vector<pair<long long, long long>>& points)`
  最短距離を持つ 2 点の添字を返す。`points.size() < 2` は想定しない

## 使い方
入力順を保ったまま点列を渡すと、返り値はその元の添字になる。
同じ座標の点が複数あってもよい。

## 実装上の補足
- 距離比較は二乗距離で行うので平方根は使わない
- 差の二乗が 64 bit を超える可能性があるため、内部計算は `__int128_t` を使う
- 複数の最短対があるとき、どれを返すかは規定しない
