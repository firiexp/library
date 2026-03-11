---
title: Binary Indexed Tree(BIT)
documentation_of: //datastructure/binaryindexedtree.cpp
---
## 説明
可換群(逆元が存在する群)について、区間和を $O(\log N)$ で求め、更新を $O(\log N)$ で行う。<br>
可換でなくても $[0, x)$ について演算した結果だけを求めたいなら使える。(例: LIS)

## 操作
- $\operatorname{add}(k, x)$ : $k$ 番目の要素に $x$ を加算する
- $\operatorname{sum}(k)$ : 半開区間 $[0, k)$ の和を求める
- $\operatorname{lower\_bound}(x)$ : $\operatorname{sum}(k)$ が $x$ 以上になる最小の $k$ を求める。存在しなければ $N$ を返す

## 使い方
`lower_bound` は累積和が単調になる状況で使う。
典型的には各要素が非負のときに使える。
