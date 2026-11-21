---
title: mod 2の行列の階数
documentation_of: //math/linear_algebra/matrix_rank_mod2.cpp
---

## 説明
各行を `DynamicBitset` で表した行列の階数を mod 2 で求める。

## できること
行列のサイズを $N\times M$ とする。

- `int matrix_rank_mod2(vector<DynamicBitset> a)`
  行列の階数を返す。$O(NM + N\min(N, M)\lceil M/64\rceil)$

## 使い方
第 $i$ 行・第 $j$ 列の値は `a[i].test(j)` に対応する。各行の長さは列数 $M$ にそろえる。
入力を残す場合はそのまま渡し、不要なら `std::move(a)` で渡せる。

```cpp
vector<DynamicBitset> a(2, DynamicBitset(3));
a[0].set(0);
a[1].set(2);
int rank = matrix_rank_mod2(a);  // 2
```

## 実装上の補足
前進消去ではピボットより下の行だけを更新し、ピボット列を含む 64 bit ワード以降だけを XOR する。
