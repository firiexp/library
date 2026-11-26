---
title: 強連結成分分解(SCC)
documentation_of: //graph/connectivity/SCC.cpp
---

## 説明
有向グラフを強連結成分分解する。
Kosaraju 法で成分番号を求め、必要なら縮約 DAG も作る。

## できること
頂点数を $N$、辺数を $M$ とする。

- `SCC scc(n)`
  頂点数 `n` のグラフを作る。$O(N)$
- `void add_edge(int u, int v)`
  辺 `u -> v` を張る。償却 $O(1)$
- `int build(bool build_dag = true)`
  強連結成分分解を実行して成分数を返す。`false` なら縮約 DAG を作らず、`G_out` を空にする。時間・領域 $O(N+M)$
- `int operator[](int v) const`
  頂点 `v` の属する成分番号を返す。$O(1)$
- `vector<vector<int>> groups() const`
  成分ごとの頂点列を成分番号順（トポロジカル順）に返す。各成分の頂点番号は昇順に並ぶ。$O(N)$
- `vector<int> cmp`
  各頂点の成分番号を持つ
- `vector<int> sz`
  各成分の頂点数を持つ
- `vector<vector<int>> G_out`
  `G_out[c]` に成分 `c` から出る辺の行き先の成分番号を昇順で持つ。多重辺・自己ループは除かれる

## 使い方
縮約 DAG が不要なら、辺を張ってから `scc.build(false)` を呼ぶ。成分ごとの頂点列は `scc.groups()`、各頂点の成分番号は `scc[v]` で取得できる。
縮約 DAG も使う場合は `scc.build()` で分解し、`G_out` を参照する。

## 実装上の補足
成分番号はトポロジカル順で、小さい番号から大きい番号へ辺が向かう。
縮約辺は到着先の成分番号順に逆辺を走査して列挙する。既存の逆辺 CSR と $O(N)$ の作業領域を使う。
`build(false)` は縮約辺の列挙を省き、その作業配列や成分ごとの隣接リストを確保しない。
