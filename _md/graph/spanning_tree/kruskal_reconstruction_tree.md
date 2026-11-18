---
title: 2頂点が初めて連結になる辺重み（Kruskal 再構成木）
documentation_of: //graph/spanning_tree/kruskal_reconstruction_tree.cpp
---

## 説明
重み付き無向グラフで、重みが $w$ 以下の辺だけを使って2頂点を結べる最小の $w$ を求める。同じグラフで頂点対を変えて繰り返し調べるときに使う。

## できること
頂点数を $N$、辺数を $M$ とする。辺の重みは負でもよい。

- `KruskalReconstructionTree<T> tree(n, edges)`
  頂点番号を $0$ から $N-1$ とし、`vector<KruskalEdge<T>>` の各辺から再構成木を作る。構築時間は $O(N+M\log M)$、構築中の領域は $O(N+M)$、構築後の領域は $O(N)$。
- `T connection_threshold(int u, int v) const`
  異なる2頂点 `u`、`v` が初めて連結になる辺重みを返す。元のグラフで非連結なら `INF<T>` を返す。時間は $O(\log N)$。

## 使い方
ライブラリをインクルードする前に、辺重みと異なる値を `INF<T>` として定義する。

```cpp
vector<KruskalEdge<int>> edges = { {0, 1, -4}, {1, 2, -2}, {0, 2, 5} };
KruskalReconstructionTree<int> tree(4, edges);
int w = tree.connection_threshold(0, 2);  // -2
int x = tree.connection_threshold(0, 3);  // INF<int>
```

## 実装上の補足
辺を重みの昇順に処理し、異なる連結成分を併合するたびに、その重みを持つ親を両成分の根の上に作る。同じ重みの辺はどの順に処理しても、2頂点が初めて連結になる重みは変わらない。各成分の木を HL 分解し、クエリでは2頂点の最近共通祖先に記録した重みを返す。
