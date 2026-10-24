---
title: 最近共通祖先(LCA)
documentation_of: //tree/LCA.cpp
---
## 説明
Euler Tour + Sparse Table で木上の LCA を求める。

## できること
頂点数を $N$ とする。

- `LCA lca(n)`
  頂点数 `n` の木を作る。$O(N)$
- `void add_edge(int u, int v)`
  木辺を張る。償却 $O(1)$
- `void build(int root = 0)`
  根 `root` で前処理をする。$O(N\log N)$
- `void buildLCA(int root = 0)`
  `build(root)` の別名。$O(N\log N)$
- `int lca(int u, int v)`
  `u` と `v` の最近共通祖先を返す。$O(1)$

## 使い方
木を張ったあと `build(root)` を 1 回呼び、以降 `lca(u, v)` を使う。

```cpp
LCA lca(n);
for (auto [u, v] : edges) {
    lca.add_edge(u, v);
}
lca.build(0);

int w = lca.lca(u, v);
```

## 実装上の補足
`id[v]` は Euler Tour 上での最初の出現位置を持つ。
RMQ には `SparseTable` を使うので、`INF<T>` が見える位置で include する必要がある。
