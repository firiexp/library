---
title: マンハッタンMST(Manhattan MST)
documentation_of: //graph/spanning_tree/manhattanmst.cpp
---
## 説明
マンハッタン距離に対する最小全域木の候補辺集合を列挙する。
最小全域木そのものは求めないため最小全域木ライブラリ(Kruskal 法など) と組み合わせる必要がある。

## できること
`xs` と `ys` は長さ $N$ の座標列とする。

- `vector<pair<int, int>> manhattanMST(vector<T> xs, vector<T> ys)`
  点列 `(xs[i], ys[i])` の候補辺を頂点番号の組 `(u, v)` で返す。$O(N\log N)$

## 使い方
候補辺の重み $|x_u-x_v|+|y_u-y_v|$ は呼び出し側で求める。
整数座標では、各点の $x_i+y_i$ と $x_i-y_i$ が整数昇格後の符号付き型に収まるように `T` を選ぶ。
例えば $|x_i|, |y_i| \le 10^9$ なら、各点の和と差の絶対値は最大 $2\times 10^9$ で、32 ビット符号付き整数に収まるが、辺重みは最大 $4\times 10^9$ になるため、下の例では座標に `long long` を使う。

```cpp
vector<long long> xs(n), ys(n);
auto es = manhattanMST(xs, ys);

vector<KruskalEdge<long long>> g;
for (auto [u, v] : es) {
    long long w = abs(xs[u] - xs[v]) + abs(ys[u] - ys[v]);
    g.emplace_back(u, v, w);
}
long long ans = kruskal(g, n).cost;
```

## 実装上の補足
返り値の辺数は $O(N)$ 本で、重複辺を含むことがある。
