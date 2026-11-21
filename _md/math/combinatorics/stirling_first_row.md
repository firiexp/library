---
title: 第一種Stirling数の列
documentation_of: //math/combinatorics/stirling_first_row.cpp
---

## 説明
固定した $n$ に対し、第一種 Stirling 数を $k = 0, \ldots, n$ について求める。
符号付き $s(n, k)$ は下降階乗 $\prod_{i=0}^{n-1}(x - i)$、符号なし $c(n, k)$ は上昇階乗 $\prod_{i=0}^{n-1}(x + i)$ の $x^k$ の係数に対応する。

## できること
- `vector<mint> stirling_first_row(int n)`
  符号付きの列 $s(n, 0), \ldots, s(n, n)$ を返す。時間 $O(n\log n)$、領域 $O(n)$
- `vector<mint> stirling_first_row_unsigned(int n)`
  符号なしの列 $c(n, 0), \ldots, c(n, n)$ を返す。時間 $O(n\log n)$、領域 $O(n)$

## 使い方
$0 \le n < 2^{23}$ で使う。返り値は長さ $n + 1$ で、添字 $k$ が $x^k$ の係数に対応する。

```cpp
auto signed_row = stirling_first_row(3);            // {0, 2, 998244350, 1}
auto unsigned_row = stirling_first_row_unsigned(3); // {0, 2, 3, 1}
```

## 実装上の補足
上昇階乗 $P_n(x)$ を $m = \lfloor n / 2 \rfloor$ として `taylor_shift` で $P_m(x) P_m(x + m)$ を計算する分割統治で求める。$n$ が奇数ならさらに $x + 2m$ を掛ける。
