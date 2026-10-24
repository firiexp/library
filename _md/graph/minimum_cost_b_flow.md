---
title: 最小費用b-flow(Min-Cost b-Flow)
documentation_of: //graph/minimum_cost_b_flow.cpp
date: 2026-03-08
category: グラフ
tags: 最小費用流
---

## 説明
各頂点に収支 `b[v]`、各有向辺に下限 `lower`・上限 `upper`・単位費用 `cost` を持つ最小費用 `b-flow` を解く。
各頂点で「流出量 − 流入量 = `b[v]`」を満たす流れのうち、総費用が最小のものを求める。
`b[v]` が正なら供給、負なら需要を表す。

## できること
頂点数を $N$、辺数を $M$ とする。

- `MinimumCostBFlow<Flow, Cost> g(n)`
  頂点数 `n` のインスタンスを作る。$O(N)$
- `void add_supply(int v, Flow x)`
  頂点 `v` に供給 `x` を足す。$O(1)$
- `void add_demand(int v, Flow x)`
  頂点 `v` に需要 `x` を足す。$O(1)$
- `int add_edge(int from, int to, Flow lower, Flow upper, Cost cost)`
  下限・上限・費用付き有向辺を追加し、辺番号を返す。償却 $O(1)$
- `pair<bool, __int128_t> solve()`
  実行可能なら `{true, 最小費用}`、不可能なら `{false, 計算された費用}` を返す。保持している流量・需給・ポテンシャルを更新する
- `vector<Flow> get_flows() const`
  追加順の各辺の流量を返す。$O(M)$
- `vector<Cost> get_potential() const`
  最適解に対応するポテンシャルの一例を返す。`solve()` 成功後、辺や需給を変更する前に呼ぶ。計算量は $O(N)$

## 使い方
1. `MinimumCostBFlow<long long, long long> g(n);` を作る
2. 各頂点の収支を `add_supply` / `add_demand` で入れる
3. 各辺を `add_edge(from, to, lower, upper, cost)` で追加する
4. `auto [ok, cost] = g.solve();` を呼ぶ
5. `ok == true` なら `get_flows()` で各辺流量を取得する

## 実装上の補足
容量スケーリングとポテンシャルを使い、余剰のある頂点から不足のある頂点へ流量を送る。
負費用辺と下限制約をそのまま扱える。
