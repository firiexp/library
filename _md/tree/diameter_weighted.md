---
title: 木の直径(重み付き)
documentation_of: //tree/diameter_weighted.cpp
---
## 説明
辺重みが非負の木で、2頂点間の距離の最大値（直径長）と、その距離を取る経路を求める。距離は経路上の辺重みの和とする。

## できること
頂点数を $N$ とする。

- `pair<T, pair<int, int>> tree_diameter_weighted(g)`
  直径長と両端点を返す。空の木では長さは0、両端点はともに `-1`。時間・領域は $O(N)$。
- `pair<T, vector<int>> tree_diameter_weighted_path(g)`
  直径長と、一方の端点からもう一方まで順に並べた頂点列を返す。最長経路が複数あればそのうち1本を返す。空の木では長さは0で頂点列は空、1頂点の木では頂点列は `{0}`。時間・領域は $O(N)$。

## 使い方
各無向辺を両方向に登録し、隣接リスト `g` を作る。

```cpp
vector<vector<pair<int, long long>>> g(n);
g[u].push_back({v, w});
g[v].push_back({u, w});

auto [dist, path] = tree_diameter_weighted_path(g);
```

重みなし木には `diameter.cpp` の `tree_diameter` を使う。

## 実装上の補足
任意の頂点から最遠点 `s` を求め、次に `s` から最遠点 `t` を求める。頂点列を返す場合だけ2回目の探索で親を記録し、`t` から親をたどって経路を復元する。
