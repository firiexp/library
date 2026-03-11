---
title: 最小費用流(Primal-Dual)
documentation_of: //flow/primaldual.cpp
date: 2026-03-12
category: フロー
tags: フロー
---
## 説明
負辺付き残余グラフに対してポテンシャル付き Dijkstra を回す最小費用流。
`s` から `t` へ流量 `fl` を流すときの最小費用を返す。

## できること
- `PrimalDual<F, C> mf(n)`
  頂点数 `n` のネットワークを作る
- `void add_edge(int u, int v, F cap, C cost)`
  容量 `cap`、費用 `cost` の有向辺を張る
- `C flow(int s, int t, F fl, int& ok)`
  `fl` 流したときの最小費用を返す。流し切れなければ `ok = 0`

## 使い方
辺を張ってから `flow(s, t, fl, ok)` を呼ぶ。
成功時は `ok = 1`、失敗時はその時点までに流せたぶんの費用を返して終了する。

## 実装上の補足
各増加路は Dijkstra で求める。
ポテンシャルは毎回 0 から初期化されるので、1 回の `flow` 呼び出しで使い切る前提。
