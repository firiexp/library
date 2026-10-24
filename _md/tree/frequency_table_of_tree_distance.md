---
title: Frequency Table of Tree Distance
documentation_of: //tree/frequency_table_of_tree_distance.cpp
date: 2026-03-15
category: 木
tags: 木
---

## 説明
木上の距離ごとの頂点対数を求める。
頂点対は順序を区別せず、異なる2頂点だけを数える。

## できること
頂点数を $N$ とする。

- `vector<long long> frequency_table_of_tree_distance(const vector<vector<int>>& g)`
  長さ $N$ の距離頻度表を返す。`res[0] = 0`、`res[d]` は距離 `d` の頂点対数。$O(N\log^2 N)$

## 使い方
隣接リストを渡して呼ぶ。

## 実装上の補足
- 重心分解で各重心を通る頂点対だけを数える
- 深さ頻度の畳み込みを使い、同一子部分木内の対を引いて重複を除く
- 重心から距離 $d$ の個数を添字 $d-1$ に置き、二乗の結果を2つずらして加減する。重心自身との対は別に加算する
- 最大距離 $D$ が2冪なら、先頭の零を除いた長さ $D$ の二乗は変換長 $2D$ で足りる。葉だけの成分では畳み込みを行わない
