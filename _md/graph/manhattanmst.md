---
title: マンハッタンMST(Manhattan MST)
documentation_of: //graph/manhattanmst.cpp
---
## 説明
マンハッタン距離に対する最小全域木の候補辺集合を $O(N log N)$ で列挙する。
返る辺だけに Kruskal をかければ、元の完全グラフの最小全域木が求まる。

## できること
- `vector<pair<int, int>> manhattanMST(vector<T> xs, vector<T> ys)`
  点列 `(xs[i], ys[i])` に対する候補辺集合を返す

## 使い方
返り値は頂点番号の組 `(u, v)` の列で、辺重みは自分でマンハッタン距離を計算して使う。
`T` には加減算と比較が必要である。

```cpp
vector<long long> xs(n), ys(n);
auto es = manhattanMST(xs, ys);

vector<edge<long long>> g;
for (auto [u, v] : es) {
    long long w = abs(xs[u] - xs[v]) + abs(ys[u] - ys[v]);
    g.emplace_back(u, v, w);
}
long long ans = kruskal(g, n).cost;
```

## 実装上の補足
返る辺数は $O(N)$ 本で、重複辺を含むことがある。
最小全域木そのものは返さないので、別に MST を構成する処理が必要である。
