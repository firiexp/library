---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_dsl_1_b_weightedunionfind.test.cpp
    title: test/aoj_dsl_1_b_weightedunionfind.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u91CD\u307F\u4ED8\u304DUnionFind(Weighted Union Find)"
    links: []
  bundledCode: "#line 1 \"datastructure/weightedunionfind.cpp\"\ntemplate <class T>\n\
    class WeightedUnionFind {\n    vector<int> uni;\n    vector<T> weights;\n\npublic:\n\
    \    explicit WeightedUnionFind(int n, T sum_unity = 0) : uni(n, -1), weights(n,\
    \ sum_unity) {}\n\n    int root(int a) {\n        if (uni[a] < 0) return a;\n\
    \        int p = uni[a];\n        int r = root(p);\n        weights[a] += weights[p];\n\
    \        return uni[a] = r;\n    }\n\n    T weight(int a) {\n        root(a);\n\
    \        return weights[a];\n    }\n\n    bool same(int a, int b) {\n        return\
    \ root(a) == root(b);\n    }\n\n    bool unite(int a, int b, T w) {\n        w\
    \ += weight(a);\n        w -= weight(b);\n        a = root(a);\n        b = root(b);\n\
    \        if (a == b) return false;\n        if (uni[a] > uni[b]) {\n         \
    \   swap(a, b);\n            w = -w;\n        }\n        uni[a] += uni[b];\n \
    \       uni[b] = a;\n        weights[b] = w;\n        return true;\n    }\n\n\
    \    int size(int a) {\n        return -uni[root(a)];\n    }\n\n    T diff(int\
    \ x, int y) {\n        return weight(y) - weight(x);\n    }\n};\n\n/**\n * @brief\
    \ \u91CD\u307F\u4ED8\u304DUnionFind(Weighted Union Find)\n */\n"
  code: "template <class T>\nclass WeightedUnionFind {\n    vector<int> uni;\n   \
    \ vector<T> weights;\n\npublic:\n    explicit WeightedUnionFind(int n, T sum_unity\
    \ = 0) : uni(n, -1), weights(n, sum_unity) {}\n\n    int root(int a) {\n     \
    \   if (uni[a] < 0) return a;\n        int p = uni[a];\n        int r = root(p);\n\
    \        weights[a] += weights[p];\n        return uni[a] = r;\n    }\n\n    T\
    \ weight(int a) {\n        root(a);\n        return weights[a];\n    }\n\n   \
    \ bool same(int a, int b) {\n        return root(a) == root(b);\n    }\n\n   \
    \ bool unite(int a, int b, T w) {\n        w += weight(a);\n        w -= weight(b);\n\
    \        a = root(a);\n        b = root(b);\n        if (a == b) return false;\n\
    \        if (uni[a] > uni[b]) {\n            swap(a, b);\n            w = -w;\n\
    \        }\n        uni[a] += uni[b];\n        uni[b] = a;\n        weights[b]\
    \ = w;\n        return true;\n    }\n\n    int size(int a) {\n        return -uni[root(a)];\n\
    \    }\n\n    T diff(int x, int y) {\n        return weight(y) - weight(x);\n\
    \    }\n};\n\n/**\n * @brief \u91CD\u307F\u4ED8\u304DUnionFind(Weighted Union\
    \ Find)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/weightedunionfind.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj_dsl_1_b_weightedunionfind.test.cpp
documentation_of: datastructure/weightedunionfind.cpp
layout: document
title: "\u91CD\u307F\u4ED8\u304DUnionFind(Weighted Union Find)"
---
## 説明
各頂点にポテンシャルを持たせた Union-Find である。
併合と差分取得をほぼ償却 $O(alpha(N))$ で扱う。

## できること
- `WeightedUnionFind<T> uf(n)`
  頂点数 `n` の構造体を作る
- `int root(int v)`
  頂点 `v` の代表元を返す
- `bool same(int u, int v)`
  `u` と `v` が同じ集合かを返す
- `bool unite(int u, int v, T w)`
  `weight(v) - weight(u) = w` となるように併合する。すでに同じ集合なら `false`
- `T weight(int v)`
  代表元から見た `v` のポテンシャルを返す
- `T diff(int u, int v)`
  `weight(v) - weight(u)` を返す。非連結では使わない
- `int size(int v)`
  `v` が属する集合サイズを返す

## 使い方
差分制約 `weight(y) - weight(x) = w` を追加したいときに `unite(x, y, w)` を呼ぶ。
差分を取りたいときは、先に `same(x, y)` を確認してから `diff(x, y)` を使う。

```cpp
WeightedUnionFind<long long> uf(n);
uf.unite(x, y, w);
if (uf.same(x, y)) {
    long long d = uf.diff(x, y);
}
```

## 実装上の補足
`weights[v]` は親とのポテンシャル差を持ち、経路圧縮時に代表元基準へ畳み込む。
`unite(x, y, w)` の `w` は `y - x` の向きで渡す。
