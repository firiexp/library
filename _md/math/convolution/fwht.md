---
title: 高速Walsh-Hadamard変換(FWHT)
documentation_of: //math/convolution/fwht.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
整数・modint の Walsh-Hadamard 変換と XOR 畳み込みを扱う。

## できること
$L$ を2冪に拡張した後の配列長とする。

- `void fwht(vector<T>& v)`
  `v` を FWHT でその場変換する。$O(L\log L)$
- `void ifwht(vector<T>& v)`
  `v` を逆 FWHT でその場変換する。整数は段ごとに2で割り、modint は最後に長さの逆元を掛ける。$O(L\log L)$
- `vector<T> xor_convolution(vector<T> a, vector<T> b)`
  `c[k] = Σ_{i xor j = k} a[i] * b[j]` を返す。両方空なら長さ1の零列を返す。時間 $O(L\log L)$、追加領域 $O(L)$

## 使い方
長さが 2 冪でなくてもよく、不足分は零で埋める。
変換は入力を、畳み込みは両方の入力を収める最小の 2 冪長（最低1）を使う。
`xor_convolution(a, b)` だけで補完から逆変換まで行える。

`T` は零で初期化でき、`+`, `-` を持つこと。畳み込みには `*=` も必要。
`inv()` を持つ型は逆変換にその逆元 API と `*=` を使う。2が可逆で、`inv()` が正しい逆元を返すことを前提とする。
既存の `mint` は奇素数の法で使う。法2には対応しない。

整数の逆変換には `>> 1` を使う。各段の和・差が2で割り切れ、変換や各点積の途中計算が型の範囲内に収まることを前提とする。
順変換してから逆変換すると、零で補完した元の列に戻る。
