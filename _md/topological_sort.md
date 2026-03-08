---
title: Topological Sort
documentation_of: //graph/topological_sort.cpp
date: 2026-03-08
category: グラフ
tags: グラフ
---

## 説明
有向グラフのトポロジカル順序を求める。
閉路があるときは空配列を返す。
計算量は `O(N + M)`。

## できること
- `vector<int> topological_sort(const vector<vector<int>>& g)`
  `g` のトポロジカル順序を返す。DAG でなければ空配列を返す

## 使い方
`g[v]` に `v -> to` を入れて使う。
順序は DFS の帰りがけ順を反転したものになる。
