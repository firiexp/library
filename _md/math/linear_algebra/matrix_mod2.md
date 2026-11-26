---
title: mod 2の行列演算(積・階数・行列式)
documentation_of: //math/linear_algebra/matrix_mod2.cpp
---

## 説明
各行を `DynamicBitset` で表した行列について、mod 2 での積・階数・行列式を求める。

## できること
- `vector<DynamicBitset> matrix_product_mod2(const vector<DynamicBitset> &a, const vector<DynamicBitset> &b, int columns = -1)`
  $N \times M$ 行列 `a` と $M \times K$ 行列 `b` の積を $N \times K$ 行列として返す。$O(NM\lceil K/64\rceil)$
- `int matrix_rank_mod2(vector<DynamicBitset> a)`
  $N \times M$ 行列 `a` の階数を返す。$O(NM + N\min(N, M)\lceil M/64\rceil)$
- `int matrix_determinant_mod2(vector<DynamicBitset> a)`
  $N \times N$ 正方行列 `a` の行列式を mod 2 で返す（正則なら `1`、特異なら `0`）。$O(N^2\lceil N/64\rceil)$

## 使い方
第 $i$ 行・第 $j$ 列の値は `a[i].test(j)` に対応する。各行列の行の長さは列数にそろえる。
`matrix_product_mod2` で `b` が 0 行のときだけ、出力の列数 $K$ を `columns` で指定できる（省略時は 0）。
`matrix_rank_mod2` と `matrix_determinant_mod2` は入力を残す場合はそのまま渡し、不要なら `std::move(a)` で渡せる。

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

auto c = matrix_product_mod2(a, b);    // [[0, 1], [0, 1]]
int rank = matrix_rank_mod2(a);        // 2
int det = matrix_determinant_mod2(c);  // 0
```

## 実装上の補足
`matrix_rank_mod2` の前進消去ではピボットより下の行だけを更新し、ピボット列を含む 64 bit ワード以降だけを XOR する。
