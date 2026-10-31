---
title: Dynamic Graph Vertex Add Component Sum
documentation_of: //graph/connectivity/dynamic_graph_vertex_add_component_sum.cpp
date: 2026-03-11
category: グラフ
tags: グラフ
---

## 説明
辺の追加・削除、頂点加算、連結成分和取得を offline で処理する。
時間区間セグメント木と rollback Union-Find を使う。

## できること
頂点数を $N$、クエリ数を $Q$ とする。

- `DynamicGraphVertexAddComponentSum(const vector<long long>& a, int q)`
  初期頂点値 `a` とクエリ数 `q` を受け取って初期化する。$O(N+Q)$
- `void add_edge(int u, int v)`
  辺追加クエリを登録する。償却 $O(1)$
- `void erase_edge(int u, int v)`
  辺削除クエリを登録する。償却 $O(1)$
- `void add_vertex(int v, long long x)`
  頂点 `v` に `x` を足すクエリを登録する。償却 $O(1)$
- `void add_component_query(int v)`
  頂点 `v` が属する連結成分の総和クエリを登録する。償却 $O(1)$
- `vector<long long> solve()`
  クエリ順に各総和クエリの答えを返す。時間 $O(N+Q\log Q\log N)$、領域 $O(N+Q\log Q)$

## 使い方
クエリを時系列順に積み、最後に `solve()` を呼ぶ。
登録数はコンストラクタに渡した `q` と一致させる。存在しない辺だけを追加し、存在する辺だけを削除する。
rollback のため経路圧縮は使わず、union-by-size により根探索を $O(\log(N))$ に抑える。

## 実装上の補足
時間木の各ノードには辺と頂点加算の開始位置を持ち、イベント本体はそれぞれ連続配列に格納する。
区間を2回分解し、個数の集計後に必要数だけ確保する。開始位置には `size_t` を使う。
`q == 0` も扱い、同じ登録内容で `solve()` を再度呼んでも同じ答えを返す。
