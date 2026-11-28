---
title: Tetration Mod
documentation_of: //math/modular/tetration.cpp
---

## 説明
テトレーション $a \uparrow\uparrow n$ を $M$ で割った余りを求める。$a,n \ge 0$、$M \ge 1$ とする。

## できること
- `ll totient(ll n)`
  `n` のオイラー関数 $\varphi(n)$ を返す。$O(\sqrt{n})$
- `ll tetration(ll a, ll n, ll M)`
  $a \uparrow\uparrow n \bmod M$ を返す。$O(\sqrt{M}+\log a)$
- `ull tetration(ll a, ll n, ll M, bool& large)`
  $a \uparrow\uparrow n \ge M$ なら `large` に `true` を入れて $(a \uparrow\uparrow n \bmod M) + M$ を返し、$M$ 未満なら `large` に `false` を入れて $a \uparrow\uparrow n$ をそのまま返す。オイラーの定理による指数縮約で使う。$O(\sqrt{M}+\log a)$

## 使い方
```cpp
ll r = tetration(3, 3, 100);  // 3^(3^3) mod 100 = 87
```
