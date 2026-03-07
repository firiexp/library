---
category: "\u30B0\u30E9\u30D5"
date: 2026-03-07
layout: post
tags: "\u30B0\u30E9\u30D5"
title: LowLink
---

## 説明

無向グラフの LowLink。
DFS 木の順序 `ord` と到達可能な最小順序 `low` を用いて、次を列挙する。

- 関節点 (articulation points)
- 橋 (bridges)

連結でないグラフにも対応する。

## 計算量

- `build()` : `O(V + E)`

## 使い方

1. `LowLink g(n);`
2. `add_edge(u, v)` で無向辺を追加
3. `build()` を呼ぶ
4. 結果を `articulation`, `bridge` などから参照

## 公開メンバ

- `vector<int> ord` : DFS 訪問順（未訪問は `-1`）
- `vector<int> low` : `lowlink` 値
- `vector<int> par` : DFS 木での親（根は `-1`）
- `vector<int> articulation` : 関節点の頂点番号一覧
- `vector<pair<int, int>> bridge` : 橋の一覧（`(min(u,v), max(u,v))` 形式、昇順ソート済み）

## 補足

- 多重辺を考慮している。
- 自己ループは `add_edge` で無視する実装。
- `is_bridge(i, j)` は `build()` 後に使用する。
{% include a.html code="lowlink.cpp" %}
