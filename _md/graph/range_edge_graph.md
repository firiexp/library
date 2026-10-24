---
title: 区間への辺を圧縮するグラフ
documentation_of: //graph/range_edge_graph.cpp
date: 2026-10-14
category: グラフ
tags: グラフ
---

## 説明
頂点から区間、区間から頂点、区間から区間への有向辺を、補助頂点を使って圧縮する。
元の頂点番号 `0..n-1` を保ち、既存の最短路ライブラリに渡せる隣接リストを返す。

## できること
元の頂点数を $N$ とする。

- `RangeEdgeGraph<T> rg(n)`
  元頂点数 `n` のグラフを作る。$O(N)$
- `rg.add_edge(u, v, w)`
  重み `w` の有向辺 `u -> v` を追加する。償却 $O(1)$
- `rg.add_to_range(u, l, r, w)`
  `u` から区間 `[l, r)` の全頂点へ重み `w` の辺を追加する。償却 $O(\log N)$
- `rg.add_from_range(l, r, v, w)`
  区間 `[l, r)` の全頂点から `v` へ重み `w` の辺を追加する。償却 $O(\log N)$
- `rg.add_range_to_range(l1, r1, l2, r2, w)`
  2区間の直積の全有向辺を重み `w` で追加する。補助頂点を1個追加する。償却 $O(\log N)$
- `rg.graph()`
  `const vector<vector<edge<T>>>&` を返す。補助頂点も含む。$O(1)$

## 使い方
区間は `0 <= l <= r <= n` の半開区間とし、空区間の追加は何もしない。
`T` は重みと `T(0)` を表せる型を使う。重複辺、自己辺、重なる区間も扱う。
追加される全頂点の番号が `int` に収まり、グラフを確保できる範囲で使う。

```cpp
RangeEdgeGraph<long long> rg(n);
rg.add_to_range(0, l, r, 5);
rg.add_range_to_range(l1, r1, l2, r2, 7);
auto dist = dijkstra(0, rg.graph());
```

最短路計算の前提は選ぶアルゴリズムに従う。Dijkstra 法なら非負重みと、距離がその `INF<T>` 未満に収まることが必要となる。
結果の先頭 `n` 要素が元頂点への距離となる。別途 build や reserve は不要。

## 実装上の補足
上下2方向のセグメント木の葉を元頂点として共有する。区間から区間への追加には中継点を1個使う。
辺追加の回数を $Q$ とすると、生成するグラフは $O(N+Q)$ 頂点、$O(N+Q\log N)$ 辺となる。
最短路処理の計算量は生成されたグラフの頂点数・辺数と使うアルゴリズムによる。
