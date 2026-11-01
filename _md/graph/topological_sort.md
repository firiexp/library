---
title: トポロジカルソート(Topological Sort)
documentation_of: //graph/topological_sort.cpp
date: 2026-03-08
category: グラフ
tags: グラフ
---

## 説明
有向グラフのトポロジカル順序を求める。
閉路があるときは空配列を返す。

## できること
頂点数を $N$、辺数を $M$ とする。

- `vector<int> topological_sort(const vector<vector<int>>& g)`
  `g` のトポロジカル順序を返す。DAG でなければ空配列を返す。$O(N+M)$
- `vector<int> topological_sort_lexmin(const vector<vector<int>>& g)`
  頂点番号列が辞書順最小となるトポロジカル順序を返す。DAG でなければ空配列を返す。
  時間 $O(M+N\log N)$、返却値を含む追加領域 $O(N)$。

## 使い方
`g[v]` に `v -> to` を入れて使う。
`topological_sort` の順序は DFS の帰りがけ順を反転したものになる。
辞書順最小の順序が必要なら `topological_sort_lexmin(g)` を使う。
入次数が 0 の頂点を min-heap で管理し、その時点で選べる最小の頂点を順に取り出す。
平行辺を扱え、自己ループは閉路として判定する。空グラフの返り値も空配列となる。
