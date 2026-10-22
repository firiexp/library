---
title: 階乗・二項係数(Factorial)
documentation_of: //math/factorial.cpp
date: 2026-03-11
category: 数学
tags: 数学
---

## 説明
階乗 `n!`、逆元 `n^{-1}`、階乗逆元 `(n!)^{-1}` を必要になったところまで遅延計算する。
`C(n, k)`、`P(n, k)`、`H(n, k)` を $O(1)$ で返す。


## できること
- `Factorial<Mint = mint> f(int n = 0)`
  `0` から `n` まで前計算して作る
- `void ensure(int n)`
  `n` まで前計算を広げる
- `int max_n()`
  現在前計算済みの最大添字を返す
- `mint fact(int k)`
  `k >= 0` なら `k!`、`k < 0` なら `(-k)!^{-1}` を返す
- `mint inv(int k)`
  `k^{-1}` を返す。`k < 0` なら `0`
- `mint inv_fact(int k)`
  `(k!)^{-1}` を返す。`k < 0` なら `0`
- `mint operator[](int k)`
  `k >= 0` なら `k!`、`k < 0` なら `(-k)!^{-1}` を返す
- `mint C(int n, int k)`
  二項係数を返す。
- `Mint C_large(long long n, long long k)`
  大きい `n` の二項係数を $O(t)$、$t=\min(k,n-k)$ で返す。`n < 0`、`k < 0`、`k > n` なら `0`
- `mint P(int n, int k)`
  順列数を返す。
- `mint H(int n, int k)`
  重複組合せを返す。

## 使い方
`Factorial<Mint> f(n);` で必要な範囲を用意する。同じ `Mint` のインスタンスは静的な表を共有し、`ensure` は指定された上限までだけ広げる。
逆元・階乗逆元と `C/P/H` は素数の法と $0 \le n < MOD$ を前提とする。表の使用中は `Mint` の法を変更しない。

`C_large` は固定素数法 $P$ と $t<P$、$t<\mathrm{INT\_MAX}$ を前提とする。`n` は `long long` の非負範囲で扱え、`n >= P` でもよい。表は `t` までだけ拡張するため、追加で必要な領域は $O(t)$。実際に確保・走査できる大きさの `t` に使う。

```cpp
Factorial<modint<1000000007>> f;
auto a = f.C_large(1000000000000000000LL, 3);
auto b = f.C_large(1000000000000000000LL, 999999999999999997LL);
assert(a == b);
```

## 実装上の補足
`C_large` は短い分子の積と `inv_fact(t)` を掛ける。`t<P` なので分母は可逆で、`n % P < t` なら分子に法の倍数が含まれるため表を拡張せず `0` を返す。

増分 $\Delta$ が500万以上で、法が素数かつ新しい上限が `MOD` 未満なら、末尾の階乗逆元を1回求めて逆走査する。それ以外は整数除算を使う従来の漸化式で広げる。既存の表は書き換えず、法をまたいでも `MOD` 未満の階乗逆元を保持する。
素数判定は逆走査が初めて候補になるときに行い、`Mint` ごとに結果を保持する。逆走査の拡張は $O(\Delta+\log MOD)$、通常の拡張は $O(\Delta)$、前計算済みの参照は $O(1)$。3本の表の領域は $O(N)$。
