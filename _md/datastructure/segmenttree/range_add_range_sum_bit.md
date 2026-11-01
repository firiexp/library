---
title: 一次関数加算・区間和BIT
documentation_of: //datastructure/segmenttree/range_add_range_sum_bit.cpp
---

## 説明
3本の BIT で、区間の各要素への一次関数 $ai+b$ の加算と区間和を扱う。
添字は 0-indexed、区間は半開区間とする。

遅延セグメント木で同じ操作を行うときに必要な、要素数・添字和を持つ集約型や作用の定義を省ける。
保持する配列は合計 $3N$ 個の `T` となる。定数加算と等差数列の加算を簡単に使いたいときに向く。

## できること
配列長を $N$ とする。保持領域は $O(N)$。

- `RangeAddRangeSumBIT<T> bit(n)`
  長さ `n` の零配列を作る。$O(N)$。
- `RangeAddRangeSumBIT<T> bit(values)`
  `vector<T>` の初期値から構築する。$O(N)$。
- `void add(int l, int r, T x)`
  $[l,r)$ に `x` を加える。$O(\log N)$。
- `void add(int l, int r, T a, T b)`
  各 $i\in[l,r)$ に $ai+b$ を加える。$O(\log N)$。
- `T sum(int r)`
  $[0,r)$ の和を返す。$O(\log N)$。
- `T sum(int l, int r)`
  $[l,r)$ の和を返す。$O(\log N)$。

## 使い方
$N \ge 0$、$0 \le l \le r \le N$ とする。
`T` は零初期化、加減算、`+=`、`long long` との積を扱える型とし、`long long` や `modint` を使える。
`T` の除算は使わないため、偶数を法とする `modint` でも使える。
整数型では、初期値の差分・係数と添字や添字和との積・BIT 内の累積値・問い合わせの中間値と答えがすべて `T` に収まることを前提とする。

```cpp
RangeAddRangeSumBIT<long long> bit(5);
bit.add(1, 4, 2, 1);
long long total = bit.sum(1, 4);
```

この例では添字 1, 2, 3 にそれぞれ 3, 5, 7 が加わり、`total` は 15 となる。
係数の `i` は配列全体の添字を指す。
左端 `l` から初項 `first`、公差 `d` の等差数列を加えるなら、`bit.add(l, r, d, first - d * l)` とする。

## 実装上の補足
$S(k)=k(k-1)/2$ とする。$[l,r)$ への一次関数加算による累積和の増分は、$l\le k\le r$ で $aS(k)+bk-aS(l)-bl$ となる。
この3係数の変化を区間の両端で BIT に加え、$k\ge r$ では増分が一定になるようにする。
配列からの構築には既存 BIT の線形構築を使う。
