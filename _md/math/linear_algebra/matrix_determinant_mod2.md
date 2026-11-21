---
title: mod 2の行列式
documentation_of: //math/linear_algebra/matrix_determinant_mod2.cpp
---

## 説明

各行を `DynamicBitset` で表した正方行列の行列式を mod 2 で求める。

## できること

- `int matrix_determinant_mod2(vector<DynamicBitset> a)` は正則なら1、特異なら0を返す。$0\times 0$ 行列の行列式は1。$N$ 行 $N$ 列なら時間は $O(N^2\lceil N/64\rceil)$、入力のコピーを含む領域は $O(N\lceil N/64\rceil)$。

## 使い方

各行の長さを行数にそろえる。入力を残す場合はそのまま渡し、不要なら `std::move(a)` で渡せる。

```cpp
vector<DynamicBitset> a(2, DynamicBitset(2));
a[0].set(1);
a[1].set(0);
int det = matrix_determinant_mod2(a);  // 1
```
