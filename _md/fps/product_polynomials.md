---
title: 多項式列の積
documentation_of: //fps/product_polynomials.cpp
date: 2026-10-30
category: FPS
tags: FPS
---

## 説明
複数の多項式の積を求める。
係数数が小さい2個を順に掛け合わせ、長い中間結果へ短い多項式を繰り返し掛ける処理を避ける。

## できること
多項式の個数を $F$、入力係数数の合計を $L$ とする。

- `poly product_polynomials(vector<poly> factors)`
  全ての多項式の積を返す。`factors` が空なら定数1、零多項式を含む場合は零多項式（係数列は空）を返す。時間 $O(F+L\log^2 L)$、領域 $O(F+L)$

空多項式がなければ $F\leq L$ なので、時間 $O(L\log^2 L)$、領域 $O(L)$ となる。

## 使い方
`poly` の列を渡す。
法は `998244353` に固定する。最高次側の0を取り除いた各多項式の次数の合計は $2^{23}$ 未満とする。

```cpp
vector<poly> factors;
factors.emplace_back(vector<mint>{1, 2});
factors.emplace_back(vector<mint>{3, 4});
auto product = product_polynomials(move(factors));
```

返り値の係数列は `{3, 10, 8}`。
引数は値で受ける。入力を残す場合はそのまま渡し、不要なら `move` でコピーを省ける。
空の係数列と、全係数が0の列はどちらも零多項式として扱う。

## 実装上の補足
定数多項式は先にまとめて掛け、残りを係数数の min-heap で管理する。
2個を取り出して既存の `poly::operator*=` で併合し、消費した多項式の領域は解放する。
併合後の次数は併合前の2個の次数の和になる。小さい次数から併合するため、各多項式が通る併合段数は $O(\log L)$。
全段の中間多項式を保持せず、存続する多項式と畳み込み用の一時領域だけを使う。
