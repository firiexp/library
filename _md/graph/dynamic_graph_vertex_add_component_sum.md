---
title: Dynamic Graph Vertex Add Component Sum
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
登録数はコンストラクタに渡した `q` と一致させる。存在しない辺だけを追加し、存在する辺だけを削除する。
時間は $O(N+Q\log(Q+1)\log(N+1))$、領域は $O(N+Q\log(Q+1))$。
rollback のため経路圧縮は使わず、union-by-size により根探索を $O(\log(N+1))$ に抑える。

## 実装上の補足
時間木の各ノードには辺と頂点加算の開始位置を持ち、イベント本体はそれぞれ連続配列に格納する。
区間を2回分解し、個数の集計後に必要数だけ確保する。開始位置には `size_t` を使う。
`q == 0` も扱い、同じ登録内容で `solve()` を再度呼んでも同じ答えを返す。
