---
title: 一次式の剰余の区間個数
documentation_of: //math/count_mod_linear.cpp
---

## 説明
$0 \le i < n$ のうち、$(ai+b) \bmod m$ が半開区間 $[l,r)$ に入る添字の個数を求める。
剰余は $[0,m)$ に収まるように正規化する。

## できること
- `ll count_mod_linear(ll n, ll m, ll a, ll b, ll l, ll r)`
  条件を満たす添字の個数を返す。空区間や `n == 0` では `0`、剰余全域では `n` を返す。
  時間 $O(\log m)$、追加領域 $O(1)$。

## 使い方
$0 \le n < 2^{32}$、$1 \le m < 2^{32}$、$0 \le l \le r \le m$ とする。
`a` と `b` は `long long` の全範囲を受け付ける。負の係数もそのまま渡せる。

```cpp
ll count = count_mod_linear(10, 7, -2, 3, 1, 4);
```

## 実装上の補足
`a`, `b` を $[0,m)$ に正規化し、次の床和の差を取る。

$$
\sum_{i=0}^{n-1}\left\lfloor\frac{ai+b+m-l}{m}\right\rfloor
-\sum_{i=0}^{n-1}\left\lfloor\frac{ai+b+m-r}{m}\right\rfloor
$$

それぞれの床和は $n(n+1)/2$ 以下で、上記の範囲では `long long` に収まる。
ずらした定数項は $2m$ 未満であり、床和内部の積は既存の `floor_sum` が `__int128` で計算する。
