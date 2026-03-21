---
title: Cycle Detection Undirected
documentation_of: //graph/cycle_detection_undirected.cpp
date: 2026-03-08
category: グラフ
tags: グラフ
---

## 説明
無向グラフから 1 つサイクルを見つける。
多重辺を含んでもよい。
計算量は $O(N + M)$。

## できること
- `CycleDetectionUndirectedResult cycle_detection_undirected(const vector<pair<int, int>>& edges, int n)`
  サイクルの頂点列と辺番号列を返す。存在しなければ両方空配列を返す

## 使い方
`edges[i] = {u, v}` を渡す。
返る `vertices` と `edge_ids` は同じ長さで、`edge_ids[i]` が `vertices[i]` と次の頂点を結ぶ。
