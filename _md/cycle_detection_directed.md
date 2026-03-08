---
layout: post
title: Cycle Detection Directed
date: 2026-03-08
category: グラフ
tags: グラフ
---

## 説明
有向グラフから 1 つサイクルを見つける。
見つからなければ空配列を返す。
計算量は `O(N + M)`。

## できること
- `vector<int> cycle_detection_directed(const vector<vector<pair<int, int>>>& g)`
  辺番号列としてサイクルを返す。存在しなければ空配列を返す

## 使い方
`g[v]` に `(to, edge_id)` を入れて使う。
返る辺番号列は順に辿ると有向サイクルになる。
