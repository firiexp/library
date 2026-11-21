---
title: mod 2の行列積
documentation_of: //math/linear_algebra/matrix_product_mod2.cpp
---

## 説明
各行を `DynamicBitset` で表した行列の積を mod 2 で求める。

## できること
$A$ を $N\times M$ 行列、$B$ を $M\times K$ 行列とする。

- `vector<DynamicBitset> matrix_product_mod2(const vector<DynamicBitset> &a, const vector<DynamicBitset> &b, int columns = -1)`
  積 $AB$ を $N\times K$ 行列として返す。$O(NM\lceil K/64\rceil)$

## 使い方
第 $i$ 行・第 $j$ 列の値は `a[i].test(j)` に対応する。`a` の各行の長さは `b` の行数 $M$ に、`b` の各行の長さは $K$ にそろえる。
`b` が 0 行のときだけ、出力の列数 $K$ を `columns` で指定できる（省略時は 0）。

```cpp
vector<DynamicBitset> a(2, DynamicBitset(3));
a[0].set(0);
a[0].set(2);
a[1].set(1);

vector<DynamicBitset> b(3, DynamicBitset(2));
b[0].set(0);
b[1].set(1);
b[2].set(0);
b[2].set(1);

auto c = matrix_product_mod2(a, b);  // [[0, 1], [0, 1]]
```
