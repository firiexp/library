---
title: 第一種Stirling数の列
documentation_of: //math/combinatorics/stirling_first_row.cpp
---

## 説明
固定した $n$ に対し、第一種 Stirling 数を $k = 0, \ldots, n$ について求める。
符号付き第一種 Stirling 数 $s(n, k)$ は下降階乗 $\prod_{i=0}^{n-1}(x - i)$、符号なし第一種 Stirling 数 $c(n, k)$ は上昇階乗 $\prod_{i=0}^{n-1}(x + i)$ の $x^k$ の係数に対応する。

## できること
$0 \le n < 2^{23}$ とし、値はすべて `998244353` で割った余りで返す。

- `vector<mint> stirling_first_row(int n)`
  $s(n, 0), \ldots, s(n, n)$ を返す。$O(n \log n)$
- `vector<mint> stirling_first_row_unsigned(int n)`
  $c(n, 0), \ldots, c(n, n)$ を返す。$O(n \log n)$

## 使い方
$s(n, k)$ が必要なら `stirling_first_row(n)`、$c(n, k)$ が必要なら `stirling_first_row_unsigned(n)` に整数 `n` を渡す。
返り値は長さ $n + 1$ で、添字 $k$ が $x^k$ の係数に対応する。

```cpp
auto s = stirling_first_row(3);
auto c = stirling_first_row_unsigned(3);
```

`s` は `{0, 2, 998244350, 1}`、`c` は `{0, 2, 3, 1}` になる。

## 実装上の補足
上昇階乗 $P_n(x) = \prod_{i=0}^{n-1}(x + i)$ は、$m = \lfloor n / 2 \rfloor$ の結果から `taylor_shift` で $P_m(x + m)$ を求めて $P_m(x) P_m(x + m)$ を計算する。
$n$ が奇数なら、さらに $x + 2m$ を掛ける。
$s(n, k)$ は $c(n, k)$ を求め、$n - k$ が奇数の項の符号を反転して得る。
