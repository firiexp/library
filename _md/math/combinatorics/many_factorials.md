---
title: Many Factorials
documentation_of: //math/combinatorics/many_factorials.cpp
date: 2026-03-15
category: 数学
tags: 数学
---

## 説明
複数の `n` に対して `n! mod 998244353` をまとめて計算する。
`n >= 998244353` なら `0` を返す。


## できること
- `vector<mint> many_factorials(const vector<long long>& ns)`
  各 `ns[i]` について `ns[i]! mod 998244353` を入力順に返す。`ns[i] >= 0` が必要。`ns[i] >= 998244353` なら `0`。空入力には空の配列を返す

## 使い方
`#include "../math/combinatorics/many_factorials.cpp"` を読み込む。

```cpp
vector<long long> ns = {3, 5, 998244352};
auto ans = many_factorials(ns);
```

## 実装上の補足
法未満の要求値の最大値を $M$、問い合わせ数を $Q$ とする。$M\le 10^6$ なら、通常の階乗表を必要な範囲まで拡張して直接参照する。
階乗表は既存の標本点シフト用の表と共有し、呼出し間で保持する。初回は $O(M+Q)$ 時間・$O(M)$ の表領域を使い、構築済みの範囲なら $O(Q)$ 時間。$M>10^6$ でも表の範囲内なら直接参照する。
空入力や全要素が法以上の場合は前計算しない。

大きい要求には次のブロック経路を使う。
同じ値をまとめ、`sample_point_shift` で幅512のブロックごとの積とその累積積を前計算する。
ブロック内の位置が前半なら左端から掛け足し、後半なら次のブロックの境界から割り戻す。
各クエリは高々256個の積で求める。
