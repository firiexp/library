---
title: 約数の総和変換とLCM畳み込み
documentation_of: //math/convolution/lcm_transform.cpp
date: 2026-11-15
category: 数学
tags: 数学
---

## 説明
各添字の約数にある係数の総和を求める変換と、その逆変換を扱う。
加えて、変換後の各成分の積を逆変換する LCM 畳み込みを扱う。

## できること
変換では $N=v.size()-1$、畳み込みでは $N=\mathtt{limit}$ とする。
添字は1から使う。変換は0番を変更せず、畳み込みは入力の0番を無視して出力の0番を0にする。
以下の計算量は素数の列挙を含み、係数の演算を $O(1)$ とする。

- `void lcm_transform(vector<T>& v)`
  $v_k\gets\sum_{d\mid k}v_d$ に更新する。時間 $O(N\log\log N)$、追加領域 $O(N)$
- `void lcm_itransform(vector<T>& v)`
  `lcm_transform` の逆変換を行う。時間 $O(N\log\log N)$、追加領域 $O(N)$
- `vector<T> lcm_convolution(const vector<T>& a, const vector<T>& b, int limit)`
  $c_k=\sum_{i,j\geq1,\ \operatorname{lcm}(i,j)=k}a_i b_j$ を $1\leq k\leq N$ について求め、長さ $N+1$ の列を返す。時間 $O(N\log\log N)$、領域 $O(N)$

## 使い方
変換には加減算、畳み込みには加減算と乗算ができる係数型を使う。整数型では途中の値も型の範囲に収める必要がある。負の係数と `modint` にも対応する。

畳み込みの `limit` は0以上とする。不足する入力係数は0として扱う。
入力の長さによらず、最小公倍数が `limit` 以下の組を集計し、上限を超える組は含めない。

```cpp
vector<long long> a{0, 0, 2}, b{0, 0, 0, 3};
auto c = lcm_convolution(a, b, 6); // {0, 0, 0, 0, 0, 0, 6}
auto d = lcm_convolution(a, b, 5); // {0, 0, 0, 0, 0, 0}
```

## 実装上の補足
素数 $p$ ごとに $i$ の昇順で `v[i*p] += v[i]` を行う。逆変換では降順に減算する。
畳み込みの3回の変換では同じ素数列を使う。
