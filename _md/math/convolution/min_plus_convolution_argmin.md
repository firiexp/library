---
title: 添字取得付きmin-plus畳み込み
documentation_of: //math/convolution/min_plus_convolution_argmin.cpp
---

## 説明
min-plus畳み込みの最小値と、その値を取る第1引数の添字を求める。
凸列とは、隣接差分が単調非減少の列を指す。

## できること
$N,M$ をそれぞれ `a`, `b` の長さとする。
返り値は `MinPlusArgmin<T>` で、最小値の列 `value` と添字列 `argmin` を持つ。
`argmin[k]` は `a[i] + b[k-i] == value[k]` となる `i`。同値なら任意の1つを返す。
片方が空なら `value`・`argmin` はともに空。

- `min_plus_argmin_arbitrary_convex(a, b)`
  `a` を任意列、`b` を凸列として計算する。$O((N+M)\log(N+M))$。
- `min_plus_argmin_convex_arbitrary(a, b)`
  `a` を凸列、`b` を任意列として計算する。$O((N+M)\log(N+M))$。
- `min_plus_argmin_convex_convex(a, b)`
  `a, b` を凸列として計算する。$O(N+M)$。

返却する2つの配列の領域は $O(N+M)$。

## 使い方
```cpp
auto res = min_plus_argmin_arbitrary_convex(a, b);
int i = res.argmin[k];
int j = k - i;
```

`T` は `+` と `<` が使える型とし、有限な要素を使う。
すべての加算が `T` に収まる必要がある。

## 実装上の補足
`min_plus_convolution.cpp` の計算部分を共用し、探索で選んだ添字を保存する。
内部で引数を交換する場合も、元の `a` の添字を返す。
