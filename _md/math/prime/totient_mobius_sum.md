---
title: オイラーのφ関数とメビウス関数の総和
documentation_of: //math/prime/totient_mobius_sum.cpp
---

## 説明

オイラーの $\varphi$ 関数とメビウス関数 $\mu$ の累積和を求める。固定した $N$ で一度構築すると、$N$ 自身と各商 $\lfloor N/i \rfloor$ までの総和を取り出せる。

## できること

$B$ を篩の上限とする。両クエリは $x$ までの総和を $\varphi$、$\mu$ の順に返す。$x$ には $0$ から $B$ までの整数、または正の整数 $i$ に対する商 $\lfloor N/i\rfloor$ を指定する。$x=0$ では `{0, 0}` を返す。

- `TotientMobiusSum(long long n, int limit)`
  `n` に $N$、`limit` に $\lfloor\sqrt{N}\rfloor \le B \le N$ を満たす $B$ を指定して総和を前計算する。時間 $O(B + N/\sqrt{B})$、領域 $O(B + N/B)$。
- `pair<long long, long long> get(long long x) const`
  両方の総和を `long long` で返す。$\varphi$ の総和が `long long` に収まる場合に使う。$O(1)$。
- `pair<__int128, long long> get_big(long long x) const`
  $\varphi$ の総和を `__int128`、$\mu$ の総和を `long long` で返す。$O(1)$。

## 使い方

```cpp
long long n = 10000000000LL;
TotientMobiusSum sums(n, 1000000);
auto [phi, mu] = sums.get(10);        // 32, -1
auto [phi_n, mu_n] = sums.get_big(n); // 30396355092886216366, -33722
```

## 実装上の補足

$B$ 以下は線形篩で各値を求め、累積和を取る。$B$ を超える商は小さい順に処理する。$\sum_{d\mid k}\varphi(d)=k$ と $\sum_{d\mid k}\mu(d)=[k=1]$ より、$x \ge 1$ で $\varphi$ の総和 $\Phi(x)$ と $\mu$ の総和 $M(x)$ は次の式を満たす。

$$
\Phi(x)=\frac{x(x+1)}{2}-\sum_{j=2}^{x}\Phi(\lfloor x/j\rfloor),\qquad
M(x)=1-\sum_{j=2}^{x}M(\lfloor x/j\rfloor).
$$

商 $\lfloor x/j\rfloor$ が同じ値 $q$ を取る区間ごとに、$\Phi(q)$ と $M(q)$ に区間の長さを掛けて引く。$B$ を超える商 $x$ の総和は、添字 $\lfloor N/x\rfloor$ で配列に保存する。$B$ を $N^{2/3}$ 程度に取ると、構築時間と領域はともに $O(N^{2/3})$ になる。
