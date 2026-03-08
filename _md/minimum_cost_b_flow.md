---
title: Minimum Cost B-Flow
documentation_of: //graph/minimum_cost_b_flow.cpp
date: 2026-03-08
category: グラフ
tags: 最小費用流
---

## 説明
各頂点に需要 `b[v]`、各有向辺に下限 `lower`・上限 `upper`・単位費用 `cost` を持つ最小費用 `b-flow` を解く。
頂点 `v` では

- `sum(outgoing flow) - sum(incoming flow) = b[v]`

を満たす流れを探し、その中で総費用を最小化する。

## できること
- `MinimumCostBFlow<Flow, Cost> g(n)`
  頂点数 `n` のインスタンスを作る
- `void add_supply(int v, Flow x)`
  頂点 `v` に供給 `x` を足す
- `void add_demand(int v, Flow x)`
  頂点 `v` に需要 `x` を足す
- `int add_edge(int from, int to, Flow lower, Flow upper, Cost cost)`
  下限・上限・費用付き有向辺を追加する
- `pair<bool, __int128_t> solve()`
  実行可能なら `{true, 最小費用}`、不可能なら `{false, 計算された費用}` を返す
- `vector<Flow> get_flows()`
  追加順の各辺の流量を返す
- `vector<Cost> get_potential()`
  最適解に対応するポテンシャルの一例を返す

## 使い方
1. `MinimumCostBFlow<long long, long long> g(n);` を作る
2. 各頂点の収支を `add_supply` / `add_demand` で入れる
3. 各辺を `add_edge(from, to, lower, upper, cost)` で追加する
4. `auto [ok, cost] = g.solve();` を呼ぶ
5. `ok == true` なら `get_flows()` で各辺流量を取得する

## 実装上の補足
cost scaling による最小費用 circulaton 法をベースにしている。
負費用辺と下限制約をそのまま扱える。
