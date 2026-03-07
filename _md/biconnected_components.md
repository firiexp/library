---
layout: post
title: Biconnected Components
date: 2026-03-08
category: グラフ
tags: グラフ
---

## 概要

無向グラフを二重頂点連結成分 (biconnected components) に分解する。
`build()` 後に、各成分の辺集合 `bcc_edges` と頂点集合 `bcc_vertices` を参照できる。

## 計算量

- `build()` : `O(V + E)`

## 使い方

1. `BiconnectedComponents g(n);`
2. `add_edge(u, v)` で無向辺を追加
3. `build()` を呼ぶ
4. 結果を `bcc_vertices` / `bcc_edges` から参照

## 実装上の補足

- 多重辺を考慮している。
- 自己ループは `add_edge` で無視する。
- 孤立頂点は 1 頂点のみの成分として `bcc_vertices` に含める。
