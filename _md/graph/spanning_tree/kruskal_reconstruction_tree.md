---
title: 2頂点が初めて連結になる辺重み(Kruskal 再構成木)
documentation_of: //graph/spanning_tree/kruskal_reconstruction_tree.cpp
---

## 説明
重み付き無向グラフで、重みが $w$ 以下の辺だけを使って2頂点を結べる最小の $w$ を求める。辺重みの上限を指定して、ある頂点から到達できる頂点の集合を葉の連続区間として取り出せる。

## できること
頂点数を $N$、辺数を $M$ とする。辺の重みは負でもよい。

- `KruskalReconstructionTree<T> tree(n, edges)`
  頂点番号を $0$ から $N-1$ とし、`vector<KruskalEdge<T>>` の各辺から再構成木を作る。構築時間は $O(N+M\log M)$、構築中の領域は $O(N+M)$、構築後の領域は $O(N)$。
- `T connection_threshold(int u, int v) const`
  異なる2頂点 `u`、`v` が初めて連結になる辺重みを返す。元のグラフで非連結なら `INF<T>` を返す。時間は $O(\log N)$。
- `leaf_order[i]`、`leaf_pos[v]`
  `leaf_order[i]` は再構成木の葉を深さ優先順に並べたときの $i$ 番目の元頂点、`leaf_pos[v]` は元頂点 $v$ の位置を表す。どちらも長さ $N$ の配列で、添字は $0$ から始まる。
- `pair<int, int> component_range(int v, const T &limit) const`
  重みが `limit` 以下の辺だけを使って `v` から到達できる頂点を、`leaf_order` 上の半開区間 $[l,r)$ で返す。孤立した頂点の区間には `v` だけが入る。時間は $O(\log N)$。
- `int component_size(int v, const T &limit) const`
  同じ条件で `v` から到達できる頂点数 $r-l$ を返す。時間は $O(\log N)$。

## 使い方
ライブラリをインクルードする前に、辺重みと異なる値を `INF<T>` として定義する。成分を調べる頂点には $0 \le v < N$ を指定する。

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
辺を重みの昇順に処理し、異なる連結成分を併合するたびに、その重みを持つ親を両成分の根の上に作る。同じ重みの辺はどの順に処理しても、2頂点が初めて連結になる重みは変わらない。各成分の木を HL 分解し、`connection_threshold` では2頂点の最近共通祖先に記録した重みを返す。

併合時の重みは葉から根に向かって単調非減少なので、`component_range` は鎖の先頭の親の重みが `limit` 以下なら、その親まで一度に上る。鎖の乗り換えは $O(\log N)$ 回で、最後の鎖だけを二分探索して条件を満たす最も高い頂点を求める。深さ優先順の先頭 $i$ 頂点に含まれる葉の個数を $P_i$ として記録する。部分木の区間が $[a,b)$ なら、葉の区間は $[P_a,P_b)$ となる。
