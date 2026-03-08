---
layout: post
title: Convex Hull
documentation_of: //geometry/convex_hull.cpp
date: 2026-03-08
category: 幾何
tags: 幾何
---

## 説明
整数座標点集合の凸包を Andrew's monotone chain で求める。
計算量は `O(N log N)`。

## できること
- `vector<pair<ll, ll>> convex_hull(vector<pair<ll, ll>> ps)`
  点集合の凸包の頂点を反時計回り順で返す。辺上の中間点と重複点は除く

## 使い方
点列を `vector<pair<ll, ll>>` で渡して使う。


## 実装上の補足
返り値は辞書順最小の点から始まる反時計回り順になる。
点数が `0`, `1`, `2` のときは重複を除いた結果をそのまま返す。
