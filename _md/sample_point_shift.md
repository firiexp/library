---
title: Sample Point Shift
documentation_of: //fps/sample_point_shift.cpp
date: 2026-03-08
category: FPS
tags: FPS
---

## 説明
多項式 `f` の値 `f(0), f(1), ..., f(n-1)` から、連続する別区間 `f(c), f(c+1), ..., f(c+m-1)` をまとめて計算する。
`998244353` 上で動き、計算量は $O((n + m) log (n + m))$。

## できること
- `vector<mint> sample_point_shift(const vector<mint>& ys, mint c, int m = -1)`
  `ys[i] = f(i)` とみなして `f(c + i)` を `i = 0..m-1` について返す
- `m = -1`
  `m = ys.size()` とみなす

## 使い方
`#include "../fps/sample_point_shift.cpp"` を読み込む。
値列 `ys` と開始点 `c`、必要個数 `m` を渡す。

```cpp
vector<mint> ys = {1, 4, 9, 16};
auto shifted = sample_point_shift(ys, mint(2), 3);
```

## 実装上の補足
`c` が既知の標本点範囲に入る場合は、その部分を直接使って残りだけ再帰的に補う。
一般部分は Lagrange 補間の係数を作って 1 回の畳み込みへ落とす。
