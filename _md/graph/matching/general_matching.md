---
title: 一般グラフ最大マッチング(General Matching)
documentation_of: //graph/matching/general_matching.cpp
date: 2026-03-08
category: グラフ
tags: グラフ
---

## 説明
Edmonds blossom による一般グラフの最大マッチング。
自己ループ・多重辺のない無向グラフに対して、最大本数のマッチングを求める。

## できること
頂点数を $N$、辺数を $M$ とする。

- `GeneralMatching gm(n)`
  頂点数 `n` のグラフを作る。$O(N)$
- `void add_edge(int u, int v)`
  無向辺 `u - v` を追加する。償却 $O(1)$
- `int max_matching()`
  最大マッチング数を返す。$O(N^3)$
- `const vector<int>& get_match() const`
  各頂点の相手を持つ配列を参照する。未マッチの頂点の要素は `-1`。$O(1)$
- `vector<pair<int, int>> get_pairs() const`
  マッチした辺集合を返す。$O(N)$

## 使い方
辺を追加してから `max_matching()` を 1 回呼ぶ。
答えの組は `get_pairs()` で取れる。

## 実装上の補足
花の縮約を BFS 上で処理する典型実装。
最初に未マッチの頂点同士を貪欲に結び、残った未マッチ頂点から増加路を探す。初期処理は $O(N+M)$ で、完全マッチングが得られた場合はそのまま終了する。
貪欲な初期解が最大でない場合も、増加路で辺を組み替えて最大本数を求める。返す辺集合は一意とは限らない。
`get_pairs()` は各辺を 1 回だけ返す。
