---
category: "\u30D5\u30ED\u30FC"
date: 2026-03-08
layout: post
tags: "\u30D5\u30ED\u30FC"
title: ProjectSelectionProblem
---

## 説明
二値変数 `x_i in {0, 1}` に対する project selection problem を最大流で解く。
扱えるのは次の形の利益の和の最大化。

- `x_i = 1` のとき得る利益
- `x_i = 0` のとき得る利益
- `x_u = 1, x_v = 0` のとき払う罰金

`x_u = 1 -> x_v = 1` の依存制約もこの特別ケースとして表せる。

## できること
- `ProjectSelectionProblem<T> psp(n)`
  変数数 `n` で初期化する
- `int add_vertex()`
  補助変数を 1 つ追加して番号を返す
- `void add_true_profit(int v, T x)`
  `x_v = 1` のとき利益 `x` を足す
- `void add_false_profit(int v, T x)`
  `x_v = 0` のとき利益 `x` を足す
- `void add_penalty(int x, int y, T cost)`
  `x_x = 1, x_y = 0` のとき罰金 `cost` を足す
- `void add_if_then(int x, int y)`
  `x_x = 1 -> x_y = 1` を課す
- `void force_true(int v)`
  `x_v = 1` を強制する
- `void force_false(int v)`
  `x_v = 0` を強制する
- `T solve()`
  最大利益を返す
- `const vector<int>& get_selected() const`
  最適解で `x_i = 1` なら `1`、そうでなければ `0`

## 使い方
各利益と制約を追加してから `solve()` を呼ぶ。
行や列、区間などのボーナスを表す補助頂点が必要なら `add_vertex()` で増やす。

## 実装上の補足
正の利益を始点側、負の利益を終点側に張り、`x=1, y=0` の罰金を `x -> y` の辺に乗せる最大重み閉包として解く。
`get_selected()` は最小カット後に始点側へ残った頂点集合を返す。
