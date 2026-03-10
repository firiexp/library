---
title: 動的グラフ連結成分和(Dynamic Graph Vertex Add Component Sum)
documentation_of: //graph/dynamic_graph_vertex_add_component_sum.cpp
date: 2026-03-11
category: グラフ
tags: グラフ
---

## 説明
辺の追加・削除、頂点加算、連結成分和取得を offline で処理する。
時間区間セグメント木と rollback Union-Find を使う。

## できること
- `DynamicGraphVertexAddComponentSum(const vector<long long>& a, int q)`
  初期頂点値 `a` とクエリ数 `q` を受け取って solver を作る
- `void add_edge(int u, int v)`
  辺追加クエリを積む
- `void erase_edge(int u, int v)`
  辺削除クエリを積む
- `void add_vertex(int v, long long x)`
  頂点 `v` に `x` を足すクエリを積む
- `void add_component_query(int v)`
  頂点 `v` が属する連結成分の総和クエリを積む
- `vector<long long> solve()`
  クエリ順に各総和クエリの答えを返す

## 使い方
クエリを時系列順に積み、最後に `solve()` を呼ぶ。
計算量は `O((N + Q) log Q log^* N)` 相当で、rollback により経路圧縮は使わない。
