---
title: DAGの最小頂点素パス被覆
documentation_of: //graph/matching/dag_minimum_path_cover.cpp
---

## 説明
DAG の全頂点をちょうど1回ずつ含む、最少本数の有向パスを求める。
各パスは元のグラフにある辺で連続する。到達可能性だけを使う鎖分解とは異なる。

## できること
頂点数を $N$、辺数を $M$ とする。

- `vector<vector<int>> dag_minimum_path_cover(const vector<vector<int>>& g)`
  各パスの元頂点番号列を返す。返却配列の `size()` が最小パス本数となる。
  孤立頂点は長さ1のパス、空グラフは空配列を返す。
  時間 $O((N+M)\sqrt N)$、返却値を含む追加領域 $O(N+M)$。

## 使い方
`g[v]` に辺 `v -> to` の終点を入れる。頂点番号は $[0,N)$ とする。
入力は DAG であることを前提とし、閉路の検出は行わない。非連結なグラフと平行辺を扱える。
同じ最小本数を達成する被覆のうち、どれを返すかは保証しない。

```cpp
vector<vector<int>> g{ {1}, {2}, {}, {}};
auto paths = dag_minimum_path_cover(g);
int minimum_count = paths.size();
```

## 実装上の補足
各頂点を左右に複製し、元の辺を左から右への辺として Hopcroft-Karp 法で最大マッチングを求める。
マッチした辺をパスの後続として復元する。DAG なので閉路は生じず、最小本数は $N-\text{matching size}$ となる。
