---
title: 最小シュタイナー木
documentation_of: //graph/minimum_steiner_tree.cpp
---

## 説明
非負重みの無向グラフで、指定された頂点集合を連結にする最小コストと採用辺を求める。
`build(terminals)` で前計算し、`cost(v)` で `terminals` に `v` を加えた場合の最小コストを取得する。
非連結グラフ、多重辺、自己ループ、重み0の辺に対応する。

## できること
指定頂点数を $K$、頂点数を $N$、辺数を $M$ とする。

- `MinimumSteinerTree<T> st(n)`
  `n` 頂点のグラフを作る。`n >= 1`。$O(N)$
- `int add_edge(int u, int v, T weight)`
  無向辺を追加し、0から始まる入力順の辺IDを返す。最初の `build` より前に呼ぶ。償却 $O(1)$
- `void build(const vector<int>& terminals)`
  指定頂点集合について前計算する。再呼び出しで以前のDPと復元情報を置き換える
  時間 $O(3^K N + 2^K (N+M)\log(N+M))$、保持領域 $O(2^K N+M)$
- `T cost(int v) const`
  `terminals` と `v` を連結にする最小コストを返す。連結にできなければ `INF<T>`。時間 $O(1)$
- `vector<int> restore(int v) const`
  `cost(v)` を達成する木の辺IDを重複なく返す。連結にできなければ空。空解とは `cost(v)` で区別する
  時間 $O(KN\alpha(N))$、追加領域 $O(N+K)$

## 使い方
頂点は0-indexed、`terminals` は相異なる有効な頂点の非空列とする。
`T` は整数型（通常は `long long`）、辺重みは非負、有限の答えは `INF<T>` 未満とする。

```cpp
MinimumSteinerTree<long long> st(n);
for (auto [u, v, w] : edges) st.add_edge(u, v, w);
st.build(terminals);
auto answer = st.cost(terminals[0]);
auto ids = st.restore(terminals[0]);
for (int v = 0; v < n; ++v) {
    auto with_v = st.cost(v);
}
```

## 実装上の補足
部分集合DPの分割遷移と、各集合に対する多始点Dijkstra法を使う。
復元は再帰でグラフをたどらず、Union-Findで重複辺と重み0の閉路を除く。
最適解の一意性や辺IDの順序は保証しない。
