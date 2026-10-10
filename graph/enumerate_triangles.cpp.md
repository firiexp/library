---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_enumerate_triangles.test.cpp
    title: test/yosupo_aplusb_enumerate_triangles.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_enumerate_triangles.test.cpp
    title: test/yosupo_enumerate_triangles.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u7121\u5411\u30B0\u30E9\u30D5\u306E\u4E09\u89D2\u5F62\u5217\u6319"
    links: []
  bundledCode: "#line 1 \"graph/enumerate_triangles.cpp\"\ntemplate<class F>\nvoid\
    \ enumerate_triangles(int n, const vector<pair<int, int>> &edges, F &&callback)\
    \ {\n    vector<int> degree(n), start(n + 1);\n    for (auto [u, v] : edges) {\n\
    \        assert(0 <= u && u < n && 0 <= v && v < n && u != v);\n        ++degree[u];\n\
    \        ++degree[v];\n    }\n    auto reversed = [&](int u, int v) {\n      \
    \  return degree[u] > degree[v] || (degree[u] == degree[v] && u > v);\n    };\n\
    \    for (auto [u, v] : edges) {\n        if (reversed(u, v)) swap(u, v);\n  \
    \      ++start[u + 1];\n    }\n    for (int v = 0; v < n; ++v) start[v + 1] +=\
    \ start[v];\n    vector<int> to(edges.size()), cursor = start;\n    for (auto\
    \ [u, v] : edges) {\n        if (reversed(u, v)) swap(u, v);\n        to[cursor[u]++]\
    \ = v;\n    }\n    fill(cursor.begin(), cursor.end(), -1);\n    for (int u = 0;\
    \ u < n; ++u) {\n        for (int i = start[u]; i < start[u + 1]; ++i) cursor[to[i]]\
    \ = u;\n        for (int i = start[u]; i < start[u + 1]; ++i) {\n            int\
    \ v = to[i];\n            for (int j = start[v]; j < start[v + 1]; ++j) {\n  \
    \              int w = to[j];\n                if (cursor[w] != u) continue;\n\
    \                int a = u, b = v, c = w;\n                if (a > b) swap(a,\
    \ b);\n                if (b > c) swap(b, c);\n                if (a > b) swap(a,\
    \ b);\n                callback(a, b, c);\n            }\n        }\n    }\n}\n\
    \n/**\n * @brief \u7121\u5411\u30B0\u30E9\u30D5\u306E\u4E09\u89D2\u5F62\u5217\u6319\
    \n */\n"
  code: "template<class F>\nvoid enumerate_triangles(int n, const vector<pair<int,\
    \ int>> &edges, F &&callback) {\n    vector<int> degree(n), start(n + 1);\n  \
    \  for (auto [u, v] : edges) {\n        assert(0 <= u && u < n && 0 <= v && v\
    \ < n && u != v);\n        ++degree[u];\n        ++degree[v];\n    }\n    auto\
    \ reversed = [&](int u, int v) {\n        return degree[u] > degree[v] || (degree[u]\
    \ == degree[v] && u > v);\n    };\n    for (auto [u, v] : edges) {\n        if\
    \ (reversed(u, v)) swap(u, v);\n        ++start[u + 1];\n    }\n    for (int v\
    \ = 0; v < n; ++v) start[v + 1] += start[v];\n    vector<int> to(edges.size()),\
    \ cursor = start;\n    for (auto [u, v] : edges) {\n        if (reversed(u, v))\
    \ swap(u, v);\n        to[cursor[u]++] = v;\n    }\n    fill(cursor.begin(), cursor.end(),\
    \ -1);\n    for (int u = 0; u < n; ++u) {\n        for (int i = start[u]; i <\
    \ start[u + 1]; ++i) cursor[to[i]] = u;\n        for (int i = start[u]; i < start[u\
    \ + 1]; ++i) {\n            int v = to[i];\n            for (int j = start[v];\
    \ j < start[v + 1]; ++j) {\n                int w = to[j];\n                if\
    \ (cursor[w] != u) continue;\n                int a = u, b = v, c = w;\n     \
    \           if (a > b) swap(a, b);\n                if (b > c) swap(b, c);\n \
    \               if (a > b) swap(a, b);\n                callback(a, b, c);\n \
    \           }\n        }\n    }\n}\n\n/**\n * @brief \u7121\u5411\u30B0\u30E9\u30D5\
    \u306E\u4E09\u89D2\u5F62\u5217\u6319\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/enumerate_triangles.cpp
  requiredBy: []
  timestamp: '2026-10-10 19:01:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_enumerate_triangles.test.cpp
  - test/yosupo_aplusb_enumerate_triangles.test.cpp
documentation_of: graph/enumerate_triangles.cpp
layout: document
title: "\u7121\u5411\u30B0\u30E9\u30D5\u306E\u4E09\u89D2\u5F62\u5217\u6319"
---

## 説明
単純無向グラフの三角形を重複なく列挙する。
callbackを $O(1)$ とすると時間 $O(N+M\sqrt M)$、入力とcallbackの保持する結果を除く作業領域は $O(N+M)$。

## できること
- `enumerate_triangles(n, edges, callback)`：各三角形について `callback(a,b,c)` をちょうど1回呼ぶ。元の頂点番号で `a < b < c` を満たし、列挙全体の順序は不問

## 使い方
`edges` は `vector<pair<int,int>>` で、各無向辺を1回だけ渡す。
頂点番号は `0..n-1`、自己ループと多重辺はないことを前提とする。
辺の端点の向き・入力順は任意で、入力を書き換えない。空グラフ、孤立点、非連結グラフも扱う。

```cpp
long long count = 0;
enumerate_triangles(n, edges, [&](int a, int b, int c) {
    ++count;
});
```

callback内で頂点重みの積や頂点ごとの三角形数も集計できる。結果の全保存は不要である。

## 実装上の補足
辺を `(次数, 頂点番号)` の小さい端点から大きい端点へ向け、出次数を $O(\sqrt M)$ に抑える。
有向隣接列を連続領域に格納し、隣接先への印と長さ2のパスを照合する。
