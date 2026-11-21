---
title: オイラーのφ関数とメビウス関数の総和
documentation_of: //math/prime/totient_mobius_sum.cpp
---

## 説明

オイラーの $\varphi$ 関数とメビウス関数 $\mu$ の累積和を求める。固定した $N$ で一度構築すると、$N$ 自身と各商 $\lfloor N/i \rfloor$ までの総和を取り出せる。

## できること

- `TotientMobiusSum(long long n, int limit)`
  $N$ を `n`、篩の上限 $B$ を `limit` として総和を前計算する。$N \ge 0$、$\lfloor\sqrt{N}\rfloor \le B \le N$、`limit < INT_MAX` が必要。時間 $O(B + N/\sqrt{B})$、領域 $O(B + N/B)$。
- `pair<__int128, long long> get(long long x) const`
  $\bigl(\sum_{k=1}^{x}\varphi(k),\ \sum_{k=1}^{x}\mu(k)\bigr)$ を返す。$x$ には $0$ から $B$ までの整数、または正の整数 $i$ に対する商 $\lfloor N/i \rfloor$ を指定する。`get(0)` は `{0, 0}` を返す。$O(1)$。

## 使い方

```cpp
TotientMobiusSum sums(10, 4);
auto [phi, mu] = sums.get(10);               // 32, -1
auto [phi_half, mu_half] = sums.get(10 / 2); // 10, -2
```

## 実装上の補足

$B$ 以下は線形篩で各値を求め、累積和を取る。$B$ を超える商は小さい順に処理する。$\sum_{d\mid k}\varphi(d)=k$ と $\sum_{d\mid k}\mu(d)=[k=1]$ より、$x \ge 1$ で $\varphi$ の総和 $\Phi(x)$ と $\mu$ の総和 $M(x)$ は次の式を満たす。

$$
\Phi(x)=\frac{x(x+1)}{2}-\sum_{j=2}^{x}\Phi(\lfloor x/j\rfloor),\qquad
M(x)=1-\sum_{j=2}^{x}M(\lfloor x/j\rfloor).
$$

商 $\lfloor x/j\rfloor$ が同じ値 $q$ を取る区間ごとに、$\Phi(q)$ と $M(q)$ に区間の長さを掛けて引く。$B$ を超える商 $x$ の総和は、添字 $\lfloor N/x\rfloor$ で配列に保存する。$B$ を $N^{2/3}$ 程度に取ると、構築時間と領域はともに $O(N^{2/3})$ になる。

Ryzen 9 9900X、GCC 13.3、C++17、`-O2 -DNDEBUG` での計測例を示す。各条件を別プロセスで5回ずつ実行した。時間は構築から `get(n)` までの中央値、メモリはプロセスのピーク RSS の最大値。

| $N$ | $B$ | 保持する $B$ 超の商の個数 | 時間 (秒) | メモリ (MiB) |
| ---: | ---: | ---: | ---: | ---: |
| $10^8$ | 10,000 | 9,999 | 0.0060 | 4.2 |
| $10^8$ | 215,443 | 464 | 0.0032 | 6.8 |
| $10^9$ | 31,622 | 31,622 | 0.0472 | 5.3 |
| $10^9$ | 1,000,000 | 999 | 0.0365 | 19.2 |
| $10^{10}$ | 100,000 | 99,999 | 0.2237 | 8.2 |
| $10^{10}$ | 1,000,000 | 9,999 | 0.0699 | 19.5 |
| $10^{10}$ | 4,641,588 | 2,154 | 0.0905 | 76.2 |
