---
title: 下限制約付きs-t最大流 (Max Flow with Lower Bounds)
documentation_of: //graph/maxflow_lower_bound.cpp
date: 2026-03-07
category: フロー
tags: 最大流
---

## 説明

有向グラフの各辺に下限制約 `lower` と上限制約 `upper` を持つ
`s-t` 最大流を求める。

各辺 `e=(u,v)` の流量 `f_e` は

- `lower_e <= f_e <= upper_e`

を満たす。さらに（`s`,`t` 以外で）フロー保存を満たす中で、`s` から `t` への流量を最大化する。

## 計算量

- `max_flow(s, t)` : $O(V^2 E)$（Dinic ベース）

## 使い方

1. `MaxFlowLowerBound<long long> g(n);`
2. `add_edge(from, to, lower, upper)` で辺を追加
3. `auto [ok, ans] = g.max_flow(s, t);`
4. `ok == false` なら制約を満たす流れが存在しない

## 公開メンバ

- `int n` : 頂点数
- `void add_edge(int from, int to, T lower, T upper)` : 下限付き有向辺を追加
- `pair<bool, T> max_flow(int s, int t)` : 実行可能性判定と最大流量を返す

## 実装メモ

- 下限を需要に変換し、超始点 `ss`・超終点 `tt` と `t -> s` の無限辺を加えた可行循環で可否判定。
- 可行解が得られた後、`t -> s` 辺を消して残余グラフで `s -> t` の追加増加分を流し、最大流を得る。
