---
title: Frequency Table of Tree Distance
documentation_of: //tree/frequency_table_of_tree_distance.cpp
date: 2026-03-15
category: 木
tags: 木
---

## 説明
木上の距離ごとの頂点対数を求める。
`res[d]` に距離 `d` の unordered pair 数を入れて返す。
計算量は $O(N \log^2 N)$。

## できること
- `vector<long long> frequency_table_of_tree_distance(const vector<vector<int>>& g)`
  距離頻度表を返す。`res[0] = 0`、`res[d]` は距離 `d` の頂点対数

## 使い方
隣接リストを渡して呼ぶ。

## 実装上の補足
- 重心分解で各重心を通る頂点対だけを数える
- 深さ頻度の畳み込みを使い、同一子部分木内の対を引いて重複を除く
