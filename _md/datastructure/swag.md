---
title: SWAG
documentation_of: //datastructure/swag.cpp
date: 2020-02-19
category: データ構造
tags: データ構造
---

## 説明
キューへの追加・削除と、キュー全体のモノイド積の取得を扱う。
非可換な演算でも先頭から末尾の順に集約する。

## できること
モノイド演算を $O(1)$ とする。

- `SWAG<G> q` : 空のキューを作る。`G::T`、結合演算 `G::f(a, b)`、単位元 `G::e()` を定義する。$O(1)$
- `push(v)` : 末尾に追加する。償却 $O(1)$
- `pop()` : 先頭を削除する。キューが空でないことが必要。償却 $O(1)$
- `fold()` : 全要素の積を返す。空なら単位元を返す。$O(1)$

## 使い方
整数の加算なら次のように定義する。

```cpp
struct Monoid {
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

SWAG<Monoid> q;
q.push(3);
q.push(5);
long long sum = q.fold();
q.pop();
```

## 実装上の補足
入力側には各要素と全体積1個、出力側には累積積だけを保持する。要素数を $N$ として領域は $O(N)$。
入力側を反転して出力側へ移す際も演算順序を保ち、逆元は使わない。
要素型はコピー構築可能であればよく、代入演算子は不要である。
