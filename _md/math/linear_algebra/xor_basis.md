---
title: XOR基底(Linear Basis)
documentation_of: //math/linear_algebra/xor_basis.cpp
date: 2026-03-12
category: 数学
tags: 数学
---

## 説明
整数列から xor 基底を構築する。
基底の本数を $k$ とすると、表現できる相異なる値の個数は $2^k$。

## できること
$B$ を整数型 `T` のビット数、`U` を `make_unsigned_t<T>` とする。

- `XorBasis<T> xb`
  空の xor 基底を作る。$O(B)$
- `int size()`
  基底の本数を返す。$O(1)$
- `bool empty()`
  基底が空なら `true`。$O(1)$
- `bool add(T x)`
  `x` を基底に追加する。独立なら `true`、追加されなければ `false`。$O(B)$
- `bool contains(T x)`
  `x` を基底で表せるなら `true`、表せなければ `false`。$O(B)$
- `T get_min(T x = 0)`
  基底で表せる `y` に対する `x xor y` の最小値を返す。$O(B)$
- `T get_max(T x = 0)`
  基底で表せる `y` に対する `x xor y` の最大値を返す。$O(B)$
- `optional<T> kth(U k) const`
  表現できる相異なる値のうち、小さい順で `k` 番目を返す。0-indexed で、範囲外なら `nullopt`。$O(B)$
- `U order_of_key(T x) const`
  表現できる相異なる値のうち、`x` 未満の個数を返す。$O(B)$
- `void merge(const XorBasis<T>& other)`
  `other` の基底を併合する。$O(B^2)$
- `XorBasis<T> intersection(const XorBasis<T>& other) const`
  両方の生成空間に属する値全体の基底を返す。片方が空なら空の基底を返す。時間 $O(B^2)$、返却値を含む追加領域 $O(B)$

## 使い方
`XorBasis<unsigned long long> xb;` を作り、`add` で値を順に入れて使う。
追加した値の集合を $S$ とし、$\langle S\rangle$ をその値を xor して作れる値全体とする。
空の基底が表す集合は `{0}` であり、`kth(0)` は `0` を返す。
`contains(x)` で表現可能性を判定でき、`get_min(x)` と `get_max(x)` で
$$
\min_{y \in \langle S \rangle} (x \oplus y), \quad \max_{y \in \langle S \rangle} (x \oplus y)
$$
を求められる。
`{1, 2}` と `{3, 4}` が生成する空間の共通部分は `{0, 3}` であり、`intersection` はこれを生成する基底を返す。

## 実装上の補足
- `T` は `bool` 以外の整数型を使う。値は `make_unsigned_t<T>` の bit 列として扱い、大小は符号なしで比較する

## 入力ID集合の復元

`XorBasisWithIds<T>` は、指定した値を作る元入力のID集合を返す。
`T` は `bool` 以外の64bit以下の整数型とし、符号付き型もビット列として扱う。

- `XorBasisWithIds<T> xb`
  空の基底を作る。時間・保持領域ともに $O(B)$。
- `bool add(T value, int id)`
  値と入力IDを追加する。独立なら `true`、従属または0なら `false`。IDは呼び出しごとに異なる `int` を渡す。$O(B)$。
- `optional<vector<int>> representation(T value) const`
  xor が `value` になる入力ID列を返す。表せなければ `nullopt`、0なら空列。$O(B)$。
- `size()` / `empty()`
  基底の本数 / 空かどうかを返す。$O(1)$。

```cpp
XorBasisWithIds<unsigned long long> xb;
for (int i = 0; i < (int)a.size(); ++i) xb.add(a[i], i);
auto ids = xb.representation(target);
if (ids) for (int id : *ids) use(a[id]);
```

独立な元入力を高々 $B$ 個保持し、その組合せを係数マスクで管理する。
復元結果の個数・辞書順などは最適化しない。併合や共通部分の由来の合成は扱わない。
値だけを扱う既存の `XorBasis<T>` にはIDや係数マスクの保持費用はかからない。
