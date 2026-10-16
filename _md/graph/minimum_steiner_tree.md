---
title: 最小シュタイナー木
documentation_of: //graph/minimum_steiner_tree.cpp
---

## 説明
非負重みの無向グラフで、少数の指定頂点をすべて連結にする最小コストと採用辺を求める。
指定頂点集合に各頂点を1つ加えた場合のコストを、同じ前計算から取得できる。
非連結グラフ、多重辺、自己ループ、重み0の辺に対応する。

## できること
- `MinimumSteinerTree<T> st(n)`
  `n` 頂点のグラフを作る。`n >= 1`
- `int add_edge(int u, int v, T weight)`
  無向辺を追加し、0から始まる入力順の辺IDを返す。最初の `build` より前に呼ぶ
- `void build(const vector<int>& terminals)`
  指定頂点集合について前計算する。再呼び出しで以前のDPと復元情報を置き換える
- `T cost(int v) const`
  `terminals` と `v` を連結にする最小コストを返す。連結にできなければ `INF<T>`
- `vector<int> restore(int v) const`
  `cost(v)` を達成する木の辺IDを重複なく返す。連結にできなければ空。空解とは `cost(v)` で区別する

## 使い方
頂点は0-indexed、`terminals` は相異なる有効な頂点の非空列とする。
`T` は整数型を使い、辺重みは非負、有限の答えは `INF<T>` 未満とする。
通常は `long long` を使い、利用側で `INF<T>` を定義する。

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
指定頂点数を $K$、頂点数を $N$、辺数を $M$ とする。
部分集合DPの分割遷移と、各集合に対する多始点Dijkstra法を使う。
`build` は時間 $O(3^K N + 2^K (N+M)\log(N+M+1))$、保持領域は $O(2^K N+M)$。
`1 << K` が正の `int` に収まる $K < 31$ に加え、指数的な配列確保と計算量が実行環境に収まることを前提とする。
`INF<T>` 以上の和を計算前に除外し、到達不能状態の加算や中間和のoverflowを避ける。

`cost` は $O(1)$。`restore` は時間 $O(KN\alpha(N))$、追加領域 $O(N+K)$。
復元は再帰でグラフをたどらず、Union-Findで重複辺と重み0の閉路を除く。
最適解の一意性や辺IDの順序は保証しない。
