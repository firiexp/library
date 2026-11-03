---
title: 連立一次方程式の分解再利用
documentation_of: //math/linear_algebra/linear_system_decomposition.cpp
---

## 説明
素数modの固定行列 $A$ に対し、右辺だけが異なる連立一次方程式 $Ax=b$ を繰り返し解く。
行基本変形を記録し、各右辺に適用する。長方形・階数不足の行列にも使える。
1回だけ解く場合は `solve_linear_system` も使える。

## できること
行数を $H$、変数数を $W$、階数を $R$ とする。`mint` の法は素数で、オブジェクトの使用中は変更しない。

- `LinearSystemDecomposition(a, variables = -1)`
  係数行列を分解し、零空間基底を作る。入力は変更しない。変数数は先頭行から推定し、行がなければ0とする。明示する場合は全行の長さと一致させる。時間 $O(HW(R+1)+H+W(W-R))$。
- `int rank() const`
  係数行列の階数を返す。$O(1)$。
- `const vector<vector<mint>>& basis() const`
  零空間の基底 $W-R$ 本を参照で返す。取得は $O(1)$ でコピーを作らない。参照の寿命はオブジェクトに従う。
- `optional<vector<mint>> solve(vector<mint> b) const`
  長さ $H$ の右辺に対し、自由変数を0にした特解を返す。不整合なら `nullopt`。入力と分解結果は変更しない。時間 $O(HR+H+W)$、追加領域 $O(H+W)$。

構築中は係数行列に $O(H(W+1))$、消去記録に $O(R(H+1))$、基底に $O(W(W-R))$ の領域を使う。
構築後は係数行列を保持せず、消去記録・基底と管理情報に $O(HR+W(W-R)+R)$ を使う。

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
制約式が0本で変数がある場合は `LinearSystemDecomposition({}, W)` とする。
変数が0個の場合は、右辺がすべて0なら空の特解を返し、それ以外は `nullopt` となる。
