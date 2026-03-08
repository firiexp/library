---
category: "\u30B0\u30E9\u30D5"
date: 2026-03-08
layout: post
tags: "\u30B0\u30E9\u30D5"
title: general_matching
---

## 説明
Edmonds blossom による一般グラフの最大マッチング。
多重辺なし無向グラフに対して、最大本数のマッチングを `O(N^3)` で求める。

## できること
- `GeneralMatching gm(n)`
  頂点数 `n` のグラフを作る
- `void add_edge(int u, int v)`
  無向辺 `u - v` を追加する
- `int max_matching()`
  最大マッチング数を返す
- `const vector<int>& get_match() const`
  `match[v]` を返す。未マッチなら `-1`
- `vector<pair<int, int>> get_pairs() const`
  マッチした辺集合を返す

## 使い方
辺を追加してから `max_matching()` を 1 回呼ぶ。
答えの組は `get_pairs()` で取れる。

## 実装上の補足
花の縮約を BFS 上で処理する典型実装。
`get_pairs()` は各辺を 1 回だけ返す。
