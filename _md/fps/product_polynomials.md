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
多項式の個数を $F$、入力係数数の合計を $L$、次数上限 `degree_limit` を $D$ とする。

- `poly product_polynomials(vector<poly> factors)`
  全ての多項式の積を返す。時間 $O(F+L\log^2 L)$、領域 $O(F+L)$

- `poly product_polynomials(vector<poly> factors, int degree_limit)`
  積を $x^D$ で割った余りを返す。$D\geq0$ とする。最高次側の0を除いた係数列を返す。時間 $O(F+L\log^2 L)$、領域 $O(F+L)$

## 使い方
`poly` の列を渡す。
法は `998244353` 固定。
次数無指定なら入力の次数合計を $2^{23}$ 未満、指定時は切り詰め前の各中間積の係数数を $2^{23}$ 以下とする。

```cpp
vector<poly> factors;
factors.emplace_back(vector<mint>{1, 2});
factors.emplace_back(vector<mint>{3, 4});
auto product = product_polynomials(factors); // {3, 10, 8}
auto low = product_polynomials(move(factors), 2); // {3, 10}
```

## 実装上の補足
各因子を $x^k g(x)$ に分け、最低次側の0を取り除いた $g(x)$ だけを掛け合わせる。
定数と単項式の係数は先にまとめて掛け、残りを係数数の min-heap で管理する。
2個を取り出して既存の `poly::operator*=` で併合し、消費した多項式の領域は解放する。
最後に $k$ の合計だけ係数列の先頭へ0を戻す。
次数を指定した場合は、$k$ の合計が $D$ 以上なら零多項式を返す。それ以外は残りの次数に合わせて各因子と各中間積を切り詰める。
次数を指定しない場合、併合後の次数は併合前の2個の次数の和になる。小さい次数から併合するため、各多項式が通る併合段数は $O(\log L)$。
全段の中間多項式を保持せず、存続する多項式と畳み込み用の一時領域だけを使う。
