---
title: 木の直径(重み付き)
documentation_of: //tree/diameter_weighted.cpp
---
## 説明
重み付き木の直径長とその両端点を `O(N)` で求める。

## できること
- `pair<T, pair<int, int>> tree_diameter_weighted(const vector<vector<pair<int, T>>> &g)`
  直径を返す。戻り値の `first` は重み和としての直径長、`second.first` と `second.second` は両端点

## 使い方
隣接リストを `vector<vector<pair<int, T>>>` で持ち、`tree_diameter_weighted(g)` を呼ぶ。

```cpp
vector<vector<pair<int, long long>>> g(n);
g[u].push_back({v, w});
g[v].push_back({u, w});

auto [dist, ends] = tree_diameter_weighted(g);
int s = ends.first;
int t = ends.second;
```

重みなし木には `diameter.cpp` の `tree_diameter` を使う。

## 実装上の補足
任意の頂点から最遠点 `s` を取り、さらに `s` から最遠点を取る 2 回 DFS で求める。
木を仮定しているので、連結で閉路のないグラフに対して使う。
