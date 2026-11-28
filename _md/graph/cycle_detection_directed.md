---
title: 有向閉路検出(Directed Cycle Detection)
documentation_of: //graph/cycle_detection_directed.cpp
---

## 説明
有向グラフの閉路を 1 つ求める。

## できること
頂点数を $N$、辺数を $M$ とする。閉路がなければ、すべて空の列を返す。

- `vector<int> cycle_detection_directed_vertices(const vector<vector<int>>& g)`
  隣接リストから、閉路をたどる順に頂点を返す。$O(N+M)$
- `CycleDetectionDirectedResult cycle_detection_directed_with_edges(const vector<vector<pair<int, int>>>& g)`
  各辺を `(行き先, 辺番号)` で表した隣接リスト $g$ を引数にする。閉路をたどる順に頂点列 `vertices` と辺番号列 `edge_ids` を返す。$O(N+M)$
- `vector<int> cycle_detection_directed(const vector<vector<pair<int, int>>>& g)`
  辺番号付きの隣接リストを引数にする。閉路をたどる順に辺番号を返す。$O(N+M)$

## 使い方
頂点列だけが必要なら `g[u]` に行き先 `v` を入れて `cycle_detection_directed_vertices(g)` を呼ぶ。
辺番号も使う場合は `g[u]` に `(v, edge_id)` を入れて `cycle_detection_directed(g)` または `cycle_detection_directed_with_edges(g)` を呼ぶ。
`cycle_detection_directed_with_edges(g)` の返り値では、`edge_ids[i]` が `vertices[i]` から次の頂点へ向かう辺の番号を表し、最後の辺は `vertices[0]` へ戻る。
