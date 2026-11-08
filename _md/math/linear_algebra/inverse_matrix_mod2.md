---
title: mod 2の逆行列
documentation_of: //math/linear_algebra/inverse_matrix_mod2.cpp
---

## 説明
mod 2 の正方行列の逆行列を求める。
各行を `DynamicBitset` で持ち、係数行列と単位行列に同じ行交換・XORを適用する。

## できること
- `optional<vector<DynamicBitset>> inverse_matrix_mod2(vector<DynamicBitset> a)`
  可逆なら逆行列、特異なら `nullopt` を返す。空行列には空の逆行列を返して成功とする。
  $N$ 行 $N$ 列に対し、時間 $O(N^2\lceil N/64\rceil+N^2)$、入力コピーと返却値を含む領域 $O(N\lceil N/64\rceil+N)$。

## 使い方
`a` の各行の長さを行数と一致させる。第 $i$ 行・第 $j$ 列の値は `a[i].test(j)` に対応する。
入力を残す場合はそのまま渡し、不要なら `std::move(a)` で渡せる。

```cpp
vector<DynamicBitset> a(2, DynamicBitset(2));
a[0].set(0);
a[0].set(1);
a[1].set(1);
auto inverse = inverse_matrix_mod2(a);
if (inverse) {
    bool value = (*inverse)[0].test(1);
}
```

返された行列を $B$ とすると、mod 2 上で $AB=BA=I$ を満たす。
`inverse->empty()` では可逆性を判断せず、`inverse.has_value()` で成功を判定する。
