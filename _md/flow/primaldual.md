---
title: 最小費用流(Primal-Dual)
documentation_of: //flow/primaldual.cpp
date: 2026-03-12
category: フロー
tags: フロー
---
## 説明
`s` から `t` へ指定した流量を流すときの最小費用を求める。
流量ごとの最小費用を、折れ点の列としてまとめて求めることもできる。

## できること
- `PrimalDual<F, C> mf(n)`
  頂点数 `n` のネットワークを作る
- `void add_edge(int u, int v, F cap, C cost)`
  容量 `cap`、費用 `cost` の有向辺を張る
- `C flow(int s, int t, F fl, int& ok)`
  流せた分の最小費用を返す。`ok` に `fl` を流し切れたかを代入する（流し切れれば `1`、そうでなければ `0`）
- `vector<pair<F, C>> slope(int s, int t, F limit = INF<F>)`
  流量と最小費用の折れ点を返す。先頭は `(0, 0)`、末尾は `limit` 以下で流せた最大流量とその費用。同じ傾きが続く区間はまとめる

頂点数を $N$、辺数を $M$、流量の上限（`fl` または `limit`）を $f$ として、`flow` / `slope` は最悪 $O(N+f(N+M)\log(N+M))$ 時間。
`slope` の返却値は $O(f+1)$ 領域。

## 使い方
辺を張ってから `flow` または `slope` を1回呼ぶ。
容量と指定する流量は非負整数、初期辺費用は非負、`s != t` とする。

```cpp
PrimalDual<long long, long long> mf(2);
mf.add_edge(0, 1, 2, 3);
mf.add_edge(0, 1, 1, 5);
auto curve = mf.slope(0, 1);
```

この例では `{(0, 0), (2, 6), (3, 11)}` を返す。
折れ点の間の整数流量に対する費用は線形補間で求められる。流量の上限が $0$ の場合や、流せる経路がない場合は `{(0, 0)}` を返す。

## 実装上の補足
各増加路は Dijkstra で求める。
整数容量では1回の増加で1以上流せるため、増加回数は流量の上限 $f$ 以下となる。
ポテンシャルを使って残余逆辺の負費用を扱う。実行後の残余グラフに対する `flow` / `slope` の再実行は扱わない。
総流量は `F`、総費用・被約費用・ポテンシャル・途中の加算と乗算は `C` に収まることが必要。Dijkstra の有限距離は `INF<C>` 未満とする。
