---
title: 和ごとの部分集合数
documentation_of: //math/subset_sum_counts.cpp
date: 2026-10-11
category: 数学
tags: 数学
---

## 説明
非負の重み列から、和が $0,1,\ldots,T$ になる部分集合の個数を求める。
同じ重みでも添字が異なれば別の要素として数える。

## できること
- `vector<mint> subset_sum_counts(const vector<int>& weights, int max_sum)`
  `max_sum` を $T$ として、和が $0,1,\ldots,T$ になる部分集合の個数を順に返す。要素数を $N$ として時間 $O(N+T\log(T+1))$、入力を除く領域 $O(T+1)$

## 使い方
`math/subset_sum_counts.cpp` を読み込み、重み列と和の上限を渡す。
この実装の法は、依存先の `math/ntt.cpp` に合わせて `998244353` 固定。
重みは非負、$0\leq T<998244353$ かつ内部 NTT の対応長に収まる範囲を前提とする。
入力の重み列は変更しない。

```cpp
auto counts = subset_sum_counts({0, 1, 1, 3}, 4);
```

返り値は `{2, 4, 2, 2, 4}`。
重み0が $z$ 個ある場合は、全ての個数を $2^z$ 倍する。
上限を超える重みは無視する。

## 実装上の補足
重み $v>0$ の頻度を $c_v$ とすると、母関数は $F(x)=\prod_v(1+x^v)^{c_v}$。
$\log F(x)$ の $x^{jv}$ の係数へ $c_v(-1)^{j+1}/j$ を加え、形式的冪級数の指数関数で $F$ を得る。
実装では対数の導関数を集約してから積分し、既存の逆元キャッシュを使う。
