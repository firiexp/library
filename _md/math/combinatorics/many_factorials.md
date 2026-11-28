---
title: Many Factorials
documentation_of: //math/combinatorics/many_factorials.cpp
---

## 説明
非負整数の列に対し、各要素の階乗を $P=998244353$ で割った余りを求める。

## できること
クエリ数を $Q$ とする。$P$ 未満の入力値のうち、最大値を $M$、異なる値の個数を $U$ とする。
ブロック幅は $B=512$、ブロック数は $K=(P-1)/B = 1949696$。

- `vector<mint> many_factorials(const vector<long long>& ns)`
  各 `ns[i]` の階乗を $P$ で割った余りを入力順に返す。`ns[i]` が $P$ 以上なら `0`。
  $M\le 2K$ なら通常の階乗表を引く。表を拡張する場合は $O(M+Q)$、構築済みの範囲なら $O(Q)$。
  $M>2K$ なら $P$ 未満の値をソートして重複を除き、ブロック境界の階乗表から求める。$O(Q\log Q+UB+\log P)$ 。初回だけ表の構築に $O(K\log B)$ かかる。

## 使い方
```cpp
vector<long long> ns = {3, 7, 5};
auto ans = many_factorials(ns);  // {6, 5040, 120}
```

## 実装上の補足
`sample_point_shift` でブロックごとの積をまとめて求め、その累積積をブロック境界の階乗表に保存する。どちらの階乗表も呼び出し間で再利用する。
各ブロックの前半は左端の階乗に残りの因子を掛け、後半は右端の階乗を余分な因子の積で割る。後半のクエリに使う分母の逆元は `batch_inverse` でまとめて求める。
