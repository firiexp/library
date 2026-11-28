---
title: 最近共通祖先(LCA)
documentation_of: //tree/LCA.cpp
---
## 説明
根付き木の2頂点の最近共通祖先を求める。

## できること
頂点数を $N$ とする。

- `LCA lca(n)`
  頂点数 `n` の木を作る。$O(N)$
- `void add_edge(int u, int v)`
  木辺を張る。償却 $O(1)$
- `void eulertour(int root = 0)`
  頂点 `root` を根とする Euler Tour の頂点列 `vs`、各位置での深さ `depth`、各頂点の初出位置 `id` を求める。$O(N)$
- `void build(int root = 0)`
  `頂点 `root` を根として、クエリに使う表を構築する。$O(N\log N)$
- `void buildLCA(int root = 0)`
  `build(root)` の別名。$O(N\log N)$
- `int lca(int u, int v)`
  `u` と `v` の最近共通祖先を返す。$O(1)$

## 使い方
```cpp
LCA tree(4);
tree.add_edge(0, 1);
tree.add_edge(1, 2);
tree.add_edge(1, 3);
tree.build();
int w = tree.lca(2, 3); // 1
```

## 実装上の補足
根を除く頂点を DFS の行きがけ順に並べ、各頂点の親の初出位置を Sparse Table に格納する。
