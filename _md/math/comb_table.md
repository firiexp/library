---
category: "\u6570\u5B66"
date: 2026-03-08
tags: "\u6570\u5B66"
title: comb_table
---

## 説明
パスカルの三角形で二項係数表を作る。
`0 <= i <= n`, `0 <= j <= min(i, m)` の範囲で `res[i][j] = C(i, j)` を持つ。
計算量は $O(n * min(n, m))$、返り値のサイズは $O(nm)$。

## できること
- `vector<vector<mint>> comb_table(int n, int m)`
  `n` 行 `m` 列までの二項係数表を返す。`j > i` の要素は `0`

## 使い方
`mint` を四則演算可能な modint として用意してから呼ぶ。
`res[i][j]` をそのまま参照すれば `C(i, j)` が取れる。

## 実装上の補足
`res[i][0] = 1` を起点に
`res[i][j] = res[i - 1][j - 1] + res[i - 1][j]`
で埋める。
