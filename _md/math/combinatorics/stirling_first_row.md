---
title: 第一種Stirling数の列
documentation_of: //math/combinatorics/stirling_first_row.cpp
---

## 説明
固定した $N$ に対し、第一種 Stirling 数を $k=0,\ldots,N$ の順に求める。符号付きの数 $s(N,k)$ は下降階乗 $\prod_{i=0}^{N-1}(x-i)$ の $x^k$ の係数である。符号なしの数 $c(N,k)$ は上昇階乗 $\prod_{i=0}^{N-1}(x+i)$ の $x^k$ の係数である。これは、$N$ 個の要素の順列のうち、巡回分解でちょうど $k$ 個の巡回を持つ順列の個数に等しい。

## できること
どちらの関数も $0\leq N<2^{23}$ で使える。返り値は長さ $N+1$ の列で、添字 $k$ の要素は $x^k$ の係数を $998244353$ で割った余りである。$N=0$ のときは空積に対応する `{1}` を返す。

- `vector<mint> stirling_first_row(int n)` は符号付きの列 $s(N,k)=(-1)^{N-k}c(N,k)$ を返す。時間 $O(N\log N)$、領域 $O(N)$。
- `vector<mint> stirling_first_row_unsigned(int n)` は符号なしの列 $c(N,k)$ を返す。時間 $O(N\log N)$、領域 $O(N)$。

## 使い方
```cpp
auto signed_row = stirling_first_row(3);            // {0, 2, 998244350, 1}
auto unsigned_row = stirling_first_row_unsigned(3); // {0, 2, 3, 1}
```

## 実装上の補足
上昇階乗を $P_N(x)$ とおく。$m=\lfloor N/2\rfloor$ とし、$P_m(x)$ から `taylor_shift` で $P_m(x+m)$ を求める。これらを掛け合わせると $P_{2m}(x)$ が得られる。$N$ が奇数なら、さらに $x+2m$ を掛ける。

次数を倍にする各段階で Taylor shift と多項式の積に $O(m\log m)$ 時間かかる。最大の畳み込みでも係数は $2\lfloor N/2\rfloor+1$ 個なので、NTT の変換長は $2^{23}$ 以下に収まる。
