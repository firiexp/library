---
layout: post
title: Eulerian Trail
documentation_of: //graph/eulerian_trail.cpp
date: 2026-03-08
category: グラフ
tags: グラフ
---

## 説明
有向グラフまたは無向グラフの Eulerian trail / circuit を 1 つ構成する。
辺をちょうど 1 回ずつ通る頂点列と辺番号列を返す。

## できること
- `EulerianTrail<false> g(n)`
  頂点数 `n` の無向グラフを作る
- `EulerianTrail<true> g(n)`
  頂点数 `n` の有向グラフを作る
- `int add_edge(int from, int to)`
  辺を追加し、辺番号を返す
- `Result solve()`
  Eulerian trail が存在すれば構成を返す。存在しないとき `exists == false`

`Result` は次を持つ。

- `bool exists`
  Eulerian trail が存在するか
- `vector<int> vertices`
  通る頂点列。長さは `M + 1`
- `vector<int> edge_ids`
  通る辺番号列。長さは `M`

## 使い方
全辺を `add_edge` で追加し、`solve()` を呼ぶ。
`vertices[i] -> vertices[i + 1]` に対応する辺番号が `edge_ids[i]` に入る。

## 実装上の補足
Hierholzer 法で構成する。
計算量は `O(N + M)`。
