---
title: 二重連結成分分解(Biconnected Components)
documentation_of: //graph/connectivity/biconnected_components.cpp
---

## 説明
無向グラフを二重頂点連結成分に分解する。
関節点は複数の成分に含まれることがある。孤立頂点は1頂点だけの成分とする。

## できること
頂点数を $V$、辺数を $E$ とする。

- `BiconnectedComponents g(n)`
  `n` 頂点のグラフを作る。$O(V)$
- `void add_edge(int u, int v)`
  無向辺を追加する。多重辺を扱い、自己ループは無視する。償却 $O(1)$
- `int build(bool build_edges = true)`
  全連結成分を分解し、二重頂点連結成分の数を返す。`build_edges` が `false` のときは頂点列だけを作り、`bcc_edges` は空になる。時間・領域 $O(V+E)$
- `bcc_edges[i]`
  成分 `i` に含まれる辺の列。各辺は `(min(u, v), max(u, v))` で表す。孤立頂点の成分では空
- `bcc_vertices[i]`
  成分 `i` の頂点を重複なく並べた列

## 使い方
辺を追加して `build()` を呼び、`bcc_edges` と `bcc_vertices` を参照する。
頂点列だけが必要なら `build(false)` を呼ぶ。

```cpp
BiconnectedComponents g(n);
for (auto [u, v] : edges) g.add_edge(u, v);
g.build();
auto &vertices = g.bcc_vertices;
auto &component_edges = g.bcc_edges;
```

## 実装上の補足
DFS は明示的なスタックで行い、グラフの深さに比例する再帰を使わない。
