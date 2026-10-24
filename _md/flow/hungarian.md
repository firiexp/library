---
title: ハンガリアン法(Hungarian Algorithm)
documentation_of: //flow/hungarian.cpp
date: 2026-03-08
category: フロー
tags: フロー
---

## 説明
二部割当問題の最適解を求める。
行数が列数以下の長方形行列に対応し、各行を異なる列へ1つずつ割り当てる。

## できること
行数を $N$、列数を $M$ とする。

- `hungarian<T, Minimize>(cost)`
  コスト行列 `cost` に対する最適値、各行の割当先列、行側双対変数、列側双対変数を返す。時間 $O(N^2M)$、入力行列を除く領域 $O(N+M)$

`Minimize=true` なら最小コスト割当、`false` なら最大コスト割当を求める。

返り値は `tuple<T, vector<int>, vector<T>, vector<T>>` で、順に次を表す。
- 最適値
- `match[i]`: 行 `i` を割り当てた列番号
- `row[i]`: 行側双対変数
- `col[j]`: 列側双対変数

`Minimize=true` では `row[i] + col[j] <= cost[i][j]` を満たす。
`Minimize=false` では `row[i] + col[j] >= cost[i][j]` を満たす。
最適値は双対和と一致する。割り当てた辺では等号が成り立つ。

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
各行の長さが揃っていること、行数が列数以下であることを `assert` する。
`T` は64 bit以下の符号付き整数型、または浮動小数点型を使う。
返す最適値と各双対変数は `T` に収まるものとする。
整数では費用の絶対値の上界を1回の走査で求め、`LLONG_MAX / (8*(N+1))` 以下なら中間計算を64 bitで行う。それ以外は符号反転・距離・双対更新をすべて `__int128` で計算する。
浮動小数点型では入力を有限値とし、計算誤差を許容する。

探索中は始点からの距離を保持し、未訪問列への一律の減算を省く。
増加路が確定した後、訪問した列に対応する双対変数だけを最終距離との差で更新する。
