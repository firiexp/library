---
title: Hopcroft-Karp法
documentation_of: //graph/hopcroft_karp.cpp
date: 2026-03-08
category: グラフ
tags: グラフ
---

## 説明
二部グラフの最大マッチングを Hopcroft-Karp 法で求める。
左頂点数を `L`、右頂点数を `R`、辺数を `M` とすると計算量は $O(M sqrt(L + R))$。

## できること
- `HopcroftKarp hk(l, r)`
  左 `l` 頂点、右 `r` 頂点の二部グラフを作る
- `void add_edge(int a, int b)`
  左 `a` と右 `b` の間に辺を追加する
- `int max_matching()`
  最大マッチング数を返す
- `vector<pair<int, int>> get_pairs()`
  現在のマッチングを `(左, 右)` の列で返す

## 使い方
辺をすべて追加してから `max_matching()` を呼ぶ。
マッチ先は `match_left` と `match_right` に入り、必要なら `get_pairs()` で列挙できる。

## 実装上の補足
左側だけに BFS/DFS の層グラフを持つ標準的な Hopcroft-Karp 法。
