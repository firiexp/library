---
title: 数字列の条件を表す有限オートマトン
documentation_of: //math/digit_dfa.cpp
---

## 説明
数字 `0` から `9` の列に対する条件を、構築済みの `DFA<10>` で返す。

## できること
- `digit_value_mod(m, r=0)` : 整数値の剰余が `r`。$m$ 状態、構築 $O(10m)$
- `digit_sum_mod(m, r=0)` : 桁和の剰余が `r`。$m$ 状態、構築 $O(10m)$
- `digit_sum_exact(k)` : 桁和が `k`。超過は拒否。$k+1$ 状態、構築 $O(10(k+1))$
- `no_equal_adjacent()` : 同じ数字が隣接しない。11 状態
- `required_digits(mask)` : bit が立つ数字をすべて含む。指定数字数を $k$ として $2^k$ 状態、構築 $O(10\cdot 2^k)$

## 使い方
`m > 0`、`0 <= r < m`、`0 <= k < INT_MAX`、`0 <= mask < 1024` とする。
状態数は `int` に収まり、遷移表を確保できる範囲で使う。
`intersect(a, b)` で複数の条件を合成できる。

```cpp
auto a = intersect(digit_value_mod(7), required_digits((1 << 0) | (1 << 3)));
```

与えた数字は先頭 0 も含めてすべて読む。数値の正規表記は桁 DP 側で扱う。
空列の値と桁和は 0 とする。空列に隣接違反はなく、指定数字を含む条件は `mask == 0` のときだけ満たす。
