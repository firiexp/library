---
title: NTT・形式的冪級数(NTT/FPS)
documentation_of: //math/ntt.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
`998244353` 上の NTT と、形式的冪級数 `poly` の基本演算をまとめた実装。
多項式積、逆数、対数、指数、冪、平方根を扱う。

## できること
$N$ を入力多項式の係数数の最大値、$D$ を要求する係数数 `deg` とする。

- `poly(vector<mint> a)`
  係数列から多項式を作る。$O(N)$
- `poly operator+(const poly& g)`
  和を返す。$O(N)$
- `poly operator-(const poly& g)`
  差を返す。$O(N)$
- `poly operator*(const poly& g)`
  積を返す。$O(N\log N)$
- `poly diff()`
  微分を返す。$O(N)$
- `poly integral()`
  定数項を0として積分した多項式を返す。$O(N)$
- `poly inv(int deg = -1)`
  逆数を `x^deg` 未満で返す。定数項が `0` なら使えない。時間 $O(D\log D)$、追加領域 $O(D)$
- `poly log(int deg = -1)`
  対数を `x^deg` 未満で返す。定数項が `1` である必要がある。時間 $O(D\log D)$、追加領域 $O(D)$
- `poly exp(int deg = -1)`
  指数を `x^deg` 未満で返す。定数項が `0` である必要がある。$O(D\log D)$
- `poly pow(long long k, int deg = -1)`
  非負整数 `k` 乗を `x^deg` 未満で返す。$O(D\log D+\log k)$
- `poly sqrt(int deg = -1)`
  平方根を `x^deg` 未満で返す。存在しなければ空多項式を返す。$O(N+D\log D)$
- `mint eval(mint x)`
  1 点での値を返す。$O(N)$
- `pair<poly, poly> divmod(const poly& g) const`
  商と剰余を返す。除数は零多項式であってはならない。剰余の末尾の零は除く。$O(N\log N)$
- `poly mod(const poly& g) const`
  剰余を返す。除数は零多項式であってはならない。剰余の末尾の零は除く。$O(N\log N)$

## 使い方
`#include "../math/ntt.cpp"` を読み込み、`poly` に係数列を入れて使う。
`poly` の `i` 番目は `x^i` の係数を表す。

畳み込みだけなら `f * g` を使う。
FPS 演算は必要な次数だけ `deg` を指定して切り詰める。
`inv` と `log` は `deg = 0` で空多項式を返す。この場合も定数項の条件は必要。
`deg = -1` は入力と同じ係数数を意味する。

## 実装上の補足
`transform` は長さが 2 冪であることを前提にする。
内部 mod は `998244353` 固定。
定数多項式との積はスカラー倍で計算する。
短い側が 16 係数以下の積と面積の小さい積は単純積を使い、それ以外は NTT を使う。
同一オブジェクトの `f * f` と `f *= f` はNTT 経路で順変換を 1 回にまとめる。
`pow` は $1\le k\le64$ で二分累乗を使う。先頭の零をシフトとして分離し、途中の係数列は必要な長さにだけ切り詰める。
`divmod` は末尾の零を除いた除数の係数数を $m$、商の係数数を $k$ として、
$\min(m,k)\le16$ または $mk\le4096$ なら $O(mk)$ の単純除算を使う。
それ以外は反転多項式の逆数と NTT による除算を使う。
`log(deg)` は微分前に必要な係数だけを取り出す。
