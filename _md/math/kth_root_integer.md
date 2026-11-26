---
title: 整数k乗根(K-th Root Integer)
documentation_of: //math/kth_root_integer.cpp
---

## 説明
符号なし64ビット整数の $k$ 乗根を小数点以下切り捨てで求める。

## できること
- `ull kth_root_integer(ull a, ull k)`
  $r^k \le a$ を満たす最大の整数 $r$ を返す。$a$ のビット数を $B$ として $O((B/k)\log k)$

## 使い方
```cpp
ull r = kth_root_integer(30, 3);  // 3
```
