---
title: Garnerのアルゴリズム
documentation_of: //math/modular/garner.cpp
---

## 説明
複数 mod での余りから連立合同式を解く。

## できること
合同式の数を $N$、入力の法の最大値を $B$ とする。

- `ll Garner(vector<pair<ll, ll>> equations, ll mod)`
  `equations` の各要素 $(r_i, m_i)$ について $x \equiv r_i \pmod{m_i}$ を満たす最小の非負整数 $x$ を求め、$x \bmod \mathrm{mod}$ を返す。$r_i$ は負でも $m_i$ 以上でもよい。
  各 $m_i$ は正でどの2つも互いに素とし、出力の法 `mod` は任意の正の `long long`（$m_i$ と共通の素因数があってもよい）とする。$O(N^2 + N \log B)$

## 使い方
```cpp
vector<pair<ll, ll>> equations = { {-3, 5}, {3, 7} };
ll r = Garner(equations, 10);  // 最小非負解は 17、返り値は 7
```
