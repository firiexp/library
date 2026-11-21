---
title: mod 2の行列式
documentation_of: //math/linear_algebra/matrix_determinant_mod2.cpp
---

## 説明
各行を `DynamicBitset` で表した正方行列の行列式を mod 2 で求める。

## できること
行列のサイズを $N\times N$ とする。

- `int matrix_determinant_mod2(vector<DynamicBitset> a)`
  行列式を mod 2 で返す（正則なら `1`、特異なら `0`）。$O(N^2\lceil N/64\rceil)$

## 使い方
第 $i$ 行・第 $j$ 列の値は `a[i].test(j)` に対応する。各行の長さは行数 $N$ にそろえる。
入力を残す場合はそのまま渡し、不要なら `std::move(a)` で渡せる。

```cpp
vector<DynamicBitset> a(2, DynamicBitset(2));
a[0].set(1);
a[1].set(0);
int det = matrix_determinant_mod2(a);  // 1
```
