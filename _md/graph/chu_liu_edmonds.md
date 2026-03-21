---
title: Chu-Liu Edmonds
documentation_of: //graph/chu_liu_edmonds.cpp
date: 2026-03-08
category: グラフ
tags: グラフ
---

## 説明
根付き有向グラフの最小全域有向木を求める。
各頂点へ入る辺から 1 本ずつ選び、根 `root` から全頂点へ到達できる最小コストの親配列を返す。

## できること
- `ChuLiuEdmonds<T> dmst(n, root)`
  頂点数 `n`、根 `root` のインスタンスを作る
- `int add_edge(int from, int to, T cost)`
  有向辺を追加し、その辺番号を返す
- `Result solve()`
  最小全域有向木を求める。存在しないとき `exists == false`

`Result` は次を持つ。

- `bool exists`
  最小全域有向木が存在するか
- `T cost`
  最小コスト。存在しないときは未定義
- `vector<int> parent`
  各頂点の親。根は `parent[root] = root`。存在しないときは空
- `vector<int> edge_id`
  採用した辺番号。根は `-1`

## 使い方
`add_edge` で全辺を追加してから `solve()` を呼ぶ。
戻り値の `parent[v]` が `v` の親、`edge_id[v]` が対応する採用辺番号になる。

## 実装上の補足
Skew heap + Union-Find による Chu-Liu/Edmonds 法。
計算量は償却 $O(M log N)$。
