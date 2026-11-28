---
title: K番目の最短ウォーク
documentation_of: //graph/shortest_path/k_shortest_walk.cpp
---

## 説明
非負重みの有向グラフで、始点から終点へのウォークのコストを小さい順に最大 $K$ 個返す。
頂点・辺の繰り返しを許し、異なる辺列は同じコストでも別々に数える。
多重辺・自己ループ・重み0の閉路に対応する。

## できること
頂点数を $N$、辺数を $M$、列挙数の上限を $K$ とする。

- `vector<T> k_shortest_walk(int s, int t, int k, const vector<vector<edge<T>>>& g)`
  ウォークのコストを小さい順に最大 $K$ 個返す。時間 $O((N+M)\log(N+M)+K\log K)$、空間 $O(N+M+N\log M+K)$
- `vector<T> k_shortest_walk_reachable(int s, int t, int k, const vector<vector<edge<T>>>& g)`
  `s` から到達できる領域に絞って同じコスト列を返す。領域内の頂点数を $R$、辺数を $E$ とすると、時間 $O(N+(R+E)\log(R+E)+K\log K)$、空間 $O(N+E+R\log E+K)$

どちらの関数も `s` から `t` へのウォークが `k` 本に満たなければ存在する分だけ返し、到達不能なら空配列を返す。
`s == t` では長さ0の空ウォークも1本に数える。`t` を途中で通って再び戻るウォークも数える。

## 使い方
頂点は0-indexedとする。

```cpp
vector<vector<edge<long long>>> g(n);
g[u].emplace_back(v, w);
auto costs = k_shortest_walk(s, t, k, g);
```

## 実装上の補足
逆向きDijkstra法で終点への最短路木を作り、木以外の辺の追加コストをleftist heapで管理する。
`k_shortest_walk_reachable` は、始点からグラフの一部にだけ到達でき、その中に終点がある場合に誘導部分グラフを作る。
どちらも `k == 0` なら探索前に空配列を返し、`k == 1` なら列挙用のヒープを作らずに最短距離だけを返す。
