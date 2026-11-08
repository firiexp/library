---
title: 連立一次方程式の分解再利用
documentation_of: //math/linear_algebra/linear_system_decomposition.cpp
---

## 説明
素数modの固定行列 $A$ に対し、右辺だけが異なる連立一次方程式 $Ax=b$ を繰り返し解く。
行基本変形を記録し、各右辺に適用する。長方形・階数不足の行列にも使える。
1回だけ解く場合は `solve_linear_system` も使える。

## できること
$H$ 行 $W$ 列の行列でランクを $R$ とする。`mint` は素数 mod とする。

- `LinearSystemDecomposition(a, variables = -1, bool build_basis = true)`
  係数行列を分解する。`build_basis = true` なら零空間基底も作る。時間 $O(HW(R+1)+W(W-R))$。
- `int rank() const`
  係数行列の階数を返す。$O(1)$。
- `const vector<vector<mint>>& basis() const`
  零空間の基底 $W-R$ 本を参照で返す。`build_basis = false` で構築した場合は空。$O(1)$。
- `optional<vector<mint>> solve(vector<mint> b) const`
  長さ $H$ の右辺に対し、自由変数を0にした特解を返す。不整合なら `nullopt`。時間 $O(HR+W)$、追加領域 $O(H+W)$。

構築時は $O(HW+W(W-R))$、構築後は $O(HR+W(W-R))$ の領域を使う。
`build_basis = false` なら、構築時間は $O(HW(R+1))$、構築時の領域は $O(HW)$、構築後の領域は $O(HR)$ となる。

## 使い方
```cpp
vector<vector<mint>> a{ {1, 2, 3}, {0, 1, 1}};
LinearSystemDecomposition system(a);
for (const auto &b : right_hand_sides) {
    auto x = system.solve(b);
    if (!x) continue;
    const auto &basis = system.basis();
}
```

すべての解は、特解に基底の任意の線形結合を加えて得られる。
特解だけを繰り返し求めるなら `LinearSystemDecomposition system(a, -1, false)` とする。
基底を確保・生成せず、`rank()` と `solve(b)` は通常と同じ結果を返す。
制約式が0本で変数がある場合は `LinearSystemDecomposition({}, W)` とする。
変数が0個の場合は、右辺がすべて0なら空の特解を返し、それ以外は `nullopt` となる。
