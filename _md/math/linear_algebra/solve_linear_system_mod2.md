---
title: mod 2の連立一次方程式(基底・特殊解)
documentation_of: //math/linear_algebra/solve_linear_system_mod2.cpp
---

## 説明
mod 2 の連立一次方程式について、同次方程式 $Av=0$ の解空間の基底を求める。
$Ax=b$ の特殊解も1つ求め、基底と合わせてすべての解を表せる。
係数行を `DynamicBitset` で持ち、64 bit ごとの XOR で消去する。

## できること
- `optional<LinearSystemSolutionMod2> solve_linear_system_mod2(vector<DynamicBitset> a, DynamicBitset b, int variables = -1)`
  基底と特殊解を返す。解がなければ `nullopt`。$N$ 行 $M$ 列に対し、時間 $O(NM\lceil M/64\rceil+M^2+N)$、入力コピーと返却値を含む領域 $O((N+M)\lceil M/64\rceil+N+M)$
- `LinearSystemSolutionMod2::rank`
  係数行列の階数
- `LinearSystemSolutionMod2::particular`
  $Ax=b$ を満たす長さ $M$ の `DynamicBitset`
- `LinearSystemSolutionMod2::basis`
  $Av=0$ を満たす、互いに一次独立な長さ $M$ の `DynamicBitset` を $M-\mathrm{rank}$ 本持つ

## 使い方
`a` は $N$ 行 $M$ 列、`b` は長さ $N$ とする。列 $j$ の値は各行の `test(j)` に対応する。
すべての解は`particular` と `basis` から任意に選んだベクトルの XOR で表せる。

```cpp
vector<DynamicBitset> a(1, DynamicBitset(2));
a[0].set(0);
a[0].set(1);
DynamicBitset b(1, true);
auto solution = solve_linear_system_mod2(a, b);
```

この例は $x_0+x_1=1\pmod 2$ を解く。
入力を保持する場合はそのまま渡し、不要な行列と右辺は `std::move` で渡せる。
行数が $0$ の場合、変数数は `variables` で指定する。省略時は $0$ とする。行数が正で第3引数を指定する場合は、列数と一致させる。
