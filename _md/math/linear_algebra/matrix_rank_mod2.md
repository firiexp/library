---
title: mod 2の行列の階数
documentation_of: //math/linear_algebra/matrix_rank_mod2.cpp
---

## 説明

各行を `DynamicBitset` で表した行列の階数を mod 2 で求める。長方形の行列にも使える。

## できること

- `int matrix_rank_mod2(vector<DynamicBitset> a)` は $N$ 行 $M$ 列の行列の階数を返す。行数または列数が0なら階数は0。階数を $r$ とすると、時間は $O(N+NM+Nr\lceil M/64\rceil)$、入力のコピーを含む領域は $O(N(1+\lceil M/64\rceil))$。

## 使い方

各行の長さを列数にそろえる。入力を残す場合はそのまま渡し、不要なら `std::move(a)` で渡せる。

```cpp
vector<DynamicBitset> a(2, DynamicBitset(3));
a[0].set(0);
a[1].set(2);
int rank = matrix_rank_mod2(a);  // 2
```

## 実装上の補足

前進消去ではピボットより下の行だけを更新する。ピボット行ではピボット列より左の成分がすべて0なので、その列を含む64ビットのワードから行末までを XOR する。
