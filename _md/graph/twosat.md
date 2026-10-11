---
title: 2-SAT
documentation_of: //graph/twosat.cpp
date: 2019-12-03
category: グラフ
tags: 有向グラフ
---

## 説明
2-SAT を SCC で解く。
各変数 $x_i$ とその否定を 2 頂点に対応させ、含意グラフを作る。

## できること
- `TwoSAT sat(n)`
  変数数 `n` の 2-SAT を作る
- `int negate(int v)`
  リテラル `v` の否定を返す
- `void add_if(int u, int v)`
  含意 `u -> v` を加える
- `void add_or(int u, int v)`
  節 `u or v` を加える
- `void at_most_one(const vector<int>& literals)`
  与えたリテラルのうち真になるものを高々1つに制限する。候補数を $K$ として追加は償却 $O(K)$ 時間・領域
- `vector<int> build()`
  全ての制約を満たす代入を元の `n` 変数について返す。充足不能なら空配列。通常の節数を $M$、`at_most_one` に渡した候補数の総和を $S$ として $O(n+M+S)$ 時間・領域

## 使い方
正リテラルを `0..n-1`、負リテラルを `negate(i)` で表す。
制約を追加したあと `build()` を呼び、返り値 `res[i]` を変数 `i` の真偽として使う。

`sat.at_most_one({0, sat.negate(1), 2});` のように排他制約を追加できる。
補助変数は内部で確保され、追加前のリテラル番号は変わらない。
同じリテラルを複数回渡した場合は、それぞれの出現を数える。

## 実装上の補足
`build()` で $x_i$ と $\lnot x_i$ が同じ SCC に入ったら充足不能と判定する。
代入は SCC 番号の大小で決めている。
