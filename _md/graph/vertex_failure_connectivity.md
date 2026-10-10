---
title: 頂点除去後の連結判定
documentation_of: //graph/vertex_failure_connectivity.cpp
---

## 説明
無向グラフで、指定した頂点を通らずに2頂点間を移動できるかを求める。
ブロックカット木と HL 分解を内部で構築する。前処理は $O(N+M)$、問い合わせは $O(\log(N+1))$、領域は $O(N+M)$。

## できること
- `VertexFailureConnectivity g(n)`
  `n` 頂点のグラフを作る
- `void add_edge(int u, int v)`
  無向辺を追加する。自己ループと平行辺も受け付ける
- `void build()`
  全連結成分を前処理する。辺の追加後は再度呼ぶ
- `bool connected_without_vertex(int u, int v, int x)`
  頂点 `x` を除いたグラフで `u` と `v` が連結なら `true`。端点が `x` なら `false`

## 使い方
元の頂点番号 `0, ..., n-1` で辺を追加し、`build()` 後に問い合わせる。
`u == v` は `u != x` なら `true`。もともと非連結の2頂点は `false` となる。
孤立点や非連結グラフ、空グラフも構築できる。問い合わせで実際のグラフは変更しない。

## 実装上の補足
除去頂点が関節点の場合だけ、ブロックカット木の端点間パスに含まれるかを調べる。
森の根は内部で選ぶ。前処理は再帰を使わず、長い道でもスタック設定の変更は不要。
