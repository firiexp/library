---
title: 2頂点が初めて連結になる辺重み(Kruskal 再構成木)
documentation_of: //graph/spanning_tree/kruskal_reconstruction_tree.cpp
---

## 説明
重み付き無向グラフで、指定した重み以下の辺だけを使ったときの連結性を扱う。
2頂点が初めて連結になる最小の辺重みや、ある頂点から到達できる頂点集合の連続区間・頂点数を求められる。

## できること
頂点数を $N$、辺数を $M$ とする。辺の重みは負でもよい。

- `KruskalReconstructionTree<T> tree(n, edges)`
  頂点番号を $0$ から $N-1$ とし、`vector<KruskalEdge<T>>` の各辺から再構成木を作る。時間 $O(N + M \log M)$、構築後の領域 $O(N)$
- `T connection_threshold(int u, int v) const`
  異なる2頂点 `u`、`v` が初めて連結になる辺重みを返す。元のグラフで非連結なら `INF<T>` を返す。$O(\log N)$
- `vector<int> leaf_order`
  再構成木の葉を深さ優先順に並べた長さ $N$ の元頂点列。
- `vector<int> leaf_pos`
  `leaf_pos[v]` に、`leaf_order` 上での元頂点 `v` の添字を持つ。
- `pair<int, int> component_range(int v, const T &limit) const`
  重みが `limit` 以下の辺だけで `v` から到達できる頂点集合を、`leaf_order` 上の半開区間 $[l, r)$ で返す。$O(\log N)$
- `int component_size(int v, const T &limit) const`
  重みが `limit` 以下の辺だけで `v` から到達できる頂点数を返す。$O(\log N)$

## 使い方
ライブラリをインクルードする前に、辺重みと異なる値を `INF<T>` として定義する。
頂点ごとの値を `leaf_pos[v]` の位置に並べておけば、`component_range(v, limit)` が返す区間 $[l, r)$ に対してセグメント木などの区間クエリをそのまま適用できる。

```cpp
vector<KruskalEdge<int>> edges = { {0, 1, -4}, {1, 2, -2}, {0, 2, 5} };
KruskalReconstructionTree<int> tree(4, edges);
int w = tree.connection_threshold(0, 2);  // -2
int x = tree.connection_threshold(0, 3);  // INF<int>
auto [l, r] = tree.component_range(0, -2);  // 区間に含まれる頂点は 0, 1, 2
bool reachable = l <= tree.leaf_pos[2] && tree.leaf_pos[2] < r;  // true
int count = tree.component_size(0, -3);  // 2
```

## 実装上の補足
辺を重みの昇順に処理し、異なる連結成分を併合するたびに、その重みを持つ親を両成分の根の上に作る。各成分の木を HL 分解し、`connection_threshold` では2頂点の LCA に記録した重みを返す。
`component_range` は HL 分解の鎖をたどって重みが `limit` 以下の最も高い祖先を探し、葉の累積個数で部分木を `leaf_order` の区間へ変換する。
