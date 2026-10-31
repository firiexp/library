---
documentation_of: //math/convolution/gcd_transform.cpp
title: gcd_transform
date: 2026-10-30
category: 数学
tags: 数学
---

## 説明
添字を約数半順序とみなした zeta 変換と mobius 反転を行う。
`v[i]` に対して、変換後は `sum_{k>=1} v[i*k]` になる。

## できること
$n$ を配列長とする。計算量には素数の列挙を含む。

- `void gcd_transform(vector<T>& v)`
  倍数側への総和を取る。`v[0]` は触らない。$O(n\log\log n)$
- `void gcd_itransform(vector<T>& v)`
  `gcd_transform` の逆変換を行う。`v[0]` は触らない。$O(n\log\log n)$
- `vector<T> gcd_convolution(vector<T> a, vector<T> b)`
  $c_k=\sum_{i,j\geq1,\ \gcd(i,j)=k}a_i b_j$ を返す。返却長は `n = max(a.size(), b.size())` で、不足する係数は0として扱う。時間 $O(n\log\log n)$、領域 $O(n)$

## 使い方
長さ `n` の配列を渡し、`1..n-1` を使う。
空配列も渡せる。負の整数係数や `modint` も扱えるが、途中の加減算は係数型の範囲に収める。
gcd 畳み込みや、`gcd = 1` 条件の包除に使う前処理としてそのまま呼べる。

畳み込みを求める場合は `gcd_convolution(a, b)` を使う。
入力の0番は値によらず無視し、出力が空でなければ0番は0とする。
両入力が空なら空配列、一方の長さが0または1なら返却長に合わせた零列を返す。
入力は変更しない。不要な入力は `move` で渡せる。
係数型には加算・減算・乗算を使い、途中の値も型の範囲に収める。

```cpp
auto c = gcd_convolution(vector<long long>{0, 2, 3}, vector<long long>{0, 5, 7, 11});
```

返り値は `{0, 94, 21, 0}`。

## 実装上の補足
最大添字までの素数を `get_prime` の wheel sieve で先に列挙する。
変換本体は各素数の倍数に対する加減算だけを行う。順変換は商の降順、逆変換は昇順で走査する。
素数列を保持するため、bit 篩だけの実装よりメモリ使用量が増える場合がある。
