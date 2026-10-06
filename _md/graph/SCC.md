---
title: 強連結成分分解(SCC)
documentation_of: //graph/SCC.cpp
date: 2019-12-03
category: グラフ
tags: 有向グラフ
---

## 説明
有向グラフを強連結成分分解する。
Kosaraju 法で成分番号と縮約 DAG を作る。計算量は $O(N + M)$。

## できること
- `SCC scc(n)`
  頂点数 `n` のグラフを作る
- `void add_edge(int u, int v)`
  辺 `u -> v` を張る
- `int build()`
  強連結成分分解を実行して成分数を返す
- `int operator[](int v)`
  頂点 `v` の属する成分番号を返す
- `vector<int> cmp`
  各頂点の成分番号を持つ
- `vector<int> sz`
  各成分の頂点数を持つ
- `vector<vector<int>> G_out`
  `G_out[c]` に成分 `c` から出る辺の行き先の成分番号を昇順で持つ。多重辺・自己ループは除かれる

## 使い方
辺を張ってから `build()` を呼ぶ。
以後は `cmp[v]` や `scc[v]` で成分番号を見て、`G_out` を縮約 DAG として使う。

## 実装上の補足
成分番号はトポロジカル順で、小さい番号から大きい番号へ辺が向かう。
縮約辺は到着先の成分番号順に逆辺を走査して列挙する。既存の逆辺 CSR と $O(N)$ の作業領域を使う。
