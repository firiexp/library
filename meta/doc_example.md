# Docs Style Example

このファイルは `_md/*.md` を書くときの参照用サンプル。
文体、見出し、箇条書き、MathJax の使い方をここに合わせる。

## Front Matter

```md
---
title: XOR基底(Linear Basis)
documentation_of: //math/linear_basis.cpp
date: 2026-03-11
category: 数学
tags: 数学
---
```

- `title` は短く保つ
- `documentation_of` は対応する `.cpp` を指す
- 日付は更新日に合わせる

## 本文テンプレート

```md
## 説明
整数列から xor 基底を構築する。
基底の本数を $k$ とすると、表現できる値の個数は $2^k$。

## できること
- `LinearBasis<T> lb`
  空の xor 基底を作る
- `bool add(T x)`
  `x` を基底に追加する。独立なら `true`、追加されなければ `false`
- `bool contains(T x)`
  `x` を基底で表せるなら `true`、表せなければ `false`
- `T get_max(T x = 0)`
  `x xor y` を最大にする `y` を基底から選んだ値を返す。空でも `x` は返る

## 使い方
要素を `add` で順に入れて使う。
典型的には
$$
\max_{y \in \langle S \rangle} (x \oplus y)
$$
のような形で使う。

## 実装上の補足
- 数式は MathJax を使い、インラインは `$...$`、別行は `$$...$$` を使う
- 説明は短く保ち、背景説明より使い方を先に見せる
```

## 書き方の要点

- 先頭は `## 説明`、次に `## できること`、`## 使い方` を置く
- API 説明は短い箇条書きにする
- 失敗時や返り値の意味を 1 行で読めるように書く
- インライン数式は `$O(N \log N)$` のように書く
- 別行数式は次の形にする

```md
$$
f(i) = \sum_{j=0}^{i-1} a_j
$$
```

- バックスラッシュを含む集合記法や総和記号もそのまま MathJax で書く
- 例コードは本当に必要なときだけ短く入れる
