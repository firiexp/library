---
title: modと底を固定した離散対数
documentation_of: //math/modular/discrete_logarithm_table.cpp
date: 2026-11-05
category: 数学
tags: 数学
---

## 説明
底 $x$ とmod $m$ を固定し、$x^e\equiv y\pmod m$ を満たす最小の非負整数 $e$ を求める。
BSGS の表をクエリ間で再利用する。$m\geq1$、$\gcd(x,m)=1$ とする。

## できること

- `DiscreteLogarithmTable(x, mod)`
  底と法を固定して表を作る。前処理は期待時間 $O(\sqrt m)$、保持領域 $O(\sqrt m)$。
- `ll log(ll y) const`
  最小の非負指数を返す。解がなければ `-1`。期待時間 $O(\sqrt m)$、追加領域 $O(1)$。

## 使い方

```cpp
DiscreteLogarithmTable table(2, 7);
ll a = table.log(4);
ll b = table.log(3);
```

`a` は `2`、`b` は `-1` となる。

## 実装上の補足
$B=\lfloor\sqrt m\rfloor+1$ とし、$x^q$ と指数 $0\leq q<B$ の表を構築する。
クエリは $y,x^{-B}y,x^{-2B}y,\ldots$ の順に調べる。表には各剰余の最小指数を保持するため、最初に一致した組が最小の指数になる。
前処理中に冪が1へ戻った場合は周期全体を保持できているため、クエリは1回の表引きで終わる。
積と逆元計算の中間値には128 bit整数を使う。
