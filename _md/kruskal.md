---
title: Kruskal法
documentation_of: //graph/kruskal.cpp
---
## 説明
無向重み付きグラフの最小全域木を求める。
辺を重み順にソートし、閉路にならないものだけ採用する。計算量は `O(M log M)`。

## できること
- `edge<T>(int from, int to, T cost, int idx = -1)`
  無向辺を作る。`idx = -1` のときは入力順の番号を自動で振る
- `KruskalResult<T> kruskal(vector<edge<T>> edges, int n)`
  頂点数 `n` のグラフに対する最小全域木を求める。非連結なら `exists = false`

## 使い方
`edge_id` には採用した辺の番号が入る。Yosupo `minimum_spanning_tree` の出力にそのまま使える。

```cpp
vector<edge<long long>> edges;
for (int i = 0; i < m; ++i) {
    int u, v;
    long long w;
    edges.emplace_back(u, v, w, i);
}

auto res = kruskal(edges, n);
if (res.exists) {
    long long cost = res.cost;
    vector<int> ids = res.edge_id;
}
```

## 実装上の補足
`idx` を明示しない場合でも、`kruskal` 内で入力順の番号を付ける。
返る `edge_id` の順序は、辺を採用した順である。
