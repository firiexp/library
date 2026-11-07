---
title: 頂点除去後の連結判定
documentation_of: //graph/connectivity/vertex_failure_connectivity.cpp
---

## 説明
無向グラフで、指定した頂点を除いたときの連結性と連結成分の頂点数を調べる。
ブロックカット木と HL 分解を内部で構築する。

## できること
頂点数を $V$、辺数を $E$ とする。

- `VertexFailureConnectivity g(n)`
  `n` 頂点のグラフを作る。時間・領域は $O(V)$
- `void add_edge(int u, int v)`
  無向辺を追加する。自己ループと多重辺も受け付ける。時間は償却 $O(1)$
- `void build()`
  全連結成分を前処理する。辺の追加後は再度呼ぶ。時間・領域は $O(V+E)$
- `bool connected_without_vertex(int u, int v, int x)`
  頂点 `x` を除いたグラフで `u` と `v` が連結なら `true`。端点が `x` なら `false`。時間は $O(\log V)$
- `int component_size_without_vertex(int u, int x) const`
  頂点 `x` を除いたグラフで、`u` が属する連結成分の頂点数を返す。`u == x` なら `0`。
  時間は $O(\log V)$

## 使い方
元の頂点番号 `0, ..., n-1` で辺を追加し、`build()` 後にクエリを処理する。
`u == v` は `u != x` なら `true`。もともと非連結の2頂点は `false` となる。
孤立点や非連結グラフ、空グラフも構築できる。

```cpp
VertexFailureConnectivity g(4);
g.add_edge(0, 1);
g.add_edge(1, 2);
g.build();
int size = g.component_size_without_vertex(0, 1);
bool connected = g.connected_without_vertex(0, 2, 1);
```

この例では `size == 1`、`connected == false` となる。辺を追加した後は再度 `build()` を呼ぶ。

## 実装上の補足
除去頂点が関節点の場合だけ、ブロックカット木の端点間パスに含まれるかを調べる。
その部分木に片方の端点だけが含まれれば非連結、どちらも含まれなければ連結のままとなる。
両方が含まれる場合だけ LCA を1回求める。部分木の包含判定は $O(1)$。

成分サイズは元の各頂点を対応するブロックカット木のノードへ1回だけ加算し、HL 順の累積和で求める。
関節点を除く場合、子側なら該当する部分木の重み、親側なら元成分から除去頂点の部分木を引いた重みを返す。
非関節点を除く場合は元成分のサイズから1を引く。サイズ取得のための追加領域は $O(V)$。
再 `build()` 時は累積和と元成分のサイズも作り直す。
森の根は内部で選ぶ。前処理は再帰を使わず、長い道でもスタック設定の変更は不要。
