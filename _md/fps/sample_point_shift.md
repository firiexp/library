---
title: 標本点シフト(Sample Point Shift)
documentation_of: //fps/sample_point_shift.cpp
---

## 説明
多項式 `f` の値 `f(0), f(1), ..., f(n-1)` から、連続する別区間 `f(c), f(c+1), ..., f(c+m-1)` をまとめて計算する。
`998244353` 上で動く。

## できること
- `vector<mint> sample_point_shift(const vector<mint>& ys, mint c, int m = -1)`
  `ys[i] = f(i)` とみなして `f(c + i)` を `i = 0..m-1` について返す。`m = -1` なら `m = ys.size()` とみなす。$N=\mathrm{ys.size()}$ として $O((N+m)\log(N+m))$

## 使い方
値列 `ys` と開始点 `c`、必要個数 `m` を渡す。

```cpp
vector<mint> ys = {1, 4, 9, 16};
auto shifted = sample_point_shift(ys, mint(2), 3);
```

## 実装上の補足
`c` が既知の標本点範囲に入る場合は、その部分を直接使って残りだけ再帰的に補う。
法 $p=998244353$ をまたぐときは、$p-1$ で終わる区間と $0$ から始まる区間に分ける。
既知の標本点を含まない各区間では、Lagrange 補間に必要な係数を中間積で求める。区間内の点数を $k$ とすると、NTT を使う場合は $N+k-1\le 2^{23}$ が必要。
