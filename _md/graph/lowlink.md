---
title: LowLink
documentation_of: //graph/lowlink.cpp
date: 2026-03-07
category: グラフ
tags: グラフ
---

## 説明
無向グラフの関節点と橋を列挙する。
非連結グラフや多重辺も扱う。

## できること
頂点数を $V$、辺数を $E$ とする。

- `LowLink g(n)`
  `n` 頂点のグラフを作る。$O(V)$
- `void add_edge(int u, int v)`
  無向辺を追加する。自己ループは無視する。償却 $O(1)$
- `void build()`
  全連結成分の関節点と橋を求める。時間・領域 $O(V+E)$
- `bool is_bridge(int u, int v)`
  辺 `(u, v)` が橋なら `true`。指定する2頂点の間には辺がちょうど1本あるものとする。$O(1)$
- `articulation`
  関節点の頂点番号列
- `bridge`
  橋の列。各辺は `(min(u, v), max(u, v))` で表し、列全体は辞書順に並ぶ
- `ord[v]` / `low[v]`
  DFS の訪問順と、`v` の部分木から木辺を下り、後退辺を高々1本使って到達できる頂点の最小訪問順
- `par[v]`
  DFS 木の親。根なら `-1`

## 使い方
辺を追加して `build()` を呼び、結果の配列や `is_bridge` を使う。

```cpp
LowLink g(n);
for (auto [u, v] : edges) g.add_edge(u, v);
g.build();
auto articulation = g.articulation;
auto bridges = g.bridge;
```

## 実装上の補足
橋の整列も $O(V+E)$ で行う。橋が少なければ比較ソートを使い、それ以外では計数ソートを使う。
