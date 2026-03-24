---
title: ハンガリアン法(Hungarian Algorithm)
documentation_of: //flow/hungarian.cpp
date: 2026-03-08
category: フロー
tags: フロー
---

## 説明
二部割当問題の最適解を $O(N^2 M)$ で求める。
`N <= M` の長方形行列に対応し、各行を異なる列へ 1 つずつ割り当てる。

## できること
- `hungarian<T, Minimize>(cost)`
  コスト行列 `cost` に対する最適値、各行の割当先列、行側双対変数、列側双対変数を返す
- `Minimize=true`
  最小コスト割当を求める
- `Minimize=false`
  最大コスト割当を求める

返り値は `tuple<T, vector<int>, vector<T>, vector<T>>` で、順に次を表す。
- 最適値
- `match[i]`: 行 `i` を割り当てた列番号
- `row[i]`: 行側双対変数
- `col[j]`: 列側双対変数

`Minimize=true` では `row[i] + col[j] <= cost[i][j]` を満たし、最適値は双対和と一致する。

## 使い方
行数が列数以下のコスト行列を渡す。

```cpp
vector<vector<long long>> cost = {
    {3, 5, 4},
    {6, 1, 9},
};
auto [ans, match, row, col] = hungarian<long long>(cost);
```

最大化したいなら `hungarian<long long, false>(cost)` を使う。

## 実装上の補足
空行列には `0` と空ベクトルを返す。
各行の長さが揃っていること、`N <= M` を `assert` する。
