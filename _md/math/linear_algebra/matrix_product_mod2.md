---
title: mod 2の行列積
documentation_of: //math/linear_algebra/matrix_product_mod2.cpp
---

## 説明

各行を `DynamicBitset` で表した行列の積を mod 2 で求める。左の行列の各行について、値が1の列に対応する右の行列の行を XOR する。

## できること

- `vector<DynamicBitset> matrix_product_mod2(const vector<DynamicBitset>& a, const vector<DynamicBitset>& b, int columns = -1)` は $N\times M$ 行列 $A$ と $M\times K$ 行列 $B$ の積を $N\times K$ 行列として返す。各次元が正なら時間は $O(NM\lceil K/64\rceil)$。いずれかの次元が0なら $O(N+M+N\lceil K/64\rceil)$。返り値を除く作業領域は $O(1)$。

## 使い方

各行のビット `j` が列 `j` に対応する。`a` の各行の長さは `b` の行数にそろえる。`b` の各行の長さは $K$ にそろえる。

`columns` が既定値の `-1` なら `b` の最初の行から $K$ を求める。`b` が空なら既定の列数は0である。$N\times 0$ と $0\times K$ の積には第3引数で $K$ を渡す。`b` に行があるときに列数を指定する場合は、実際の行の長さに合わせる。

```cpp
vector<DynamicBitset> a(2, DynamicBitset(0));
auto c = matrix_product_mod2(a, {}, 5);  // 2 行 5 列の零行列
```
