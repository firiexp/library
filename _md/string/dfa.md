---
title: 有限オートマトンと条件の合成
documentation_of: //string/dfa.cpp
---

## 説明
文字を `0` から `W-1` で表す決定性有限オートマトン。条件を AND 合成できる。

## できること
- `DFA<W>{next, accept, initial}` : 遷移表、受理フラグ、初期状態から直接作る
- `intersect(a, b)` : 両方が受理する列を受理する DFA を返す。初期状態対から到達できる状態だけを持つ

## 使い方
`next` は `vector<array<int, W>>`、`accept` は状態数と同じ長さの `vector<char>`。
状態番号は `int` に収まる非負整数とし、`next[v][c] == -1` は拒否遷移を表す。
拒否した列は以後も拒否する。`initial == -1` は空列も含めた全拒否で、既定構築はこの形になる。
それ以外の遷移先と初期状態は有効な状態番号とする。
空列の受理は初期状態のフラグで決まる。受理しない状態から受理状態へ遷移してもよい。

```cpp
auto a = intersect(digit_sum_exact(12), digit_value_mod(12));
```

数字の条件には `math/digit_dfa.cpp` を include する。表は固定長の文字列 DP にも使える。
先頭 0 や数値の上下限はこの表では扱わない。

## 実装上の補足
入力状態数を $S_1,S_2$、到達状態対数を $R$ とすると、合成は最悪 $O(S_1S_2+WR)$ 時間。
状態対の ID 配列に $O(S_1S_2)$、返却表に $O(WR)$ の領域を使う。
状態数の積が確保可能で、返却状態数が `int` に収まる範囲で使う。
`intersect` は最小化を行わない。必要なら `string/dfa_minimize.cpp` の `minimize(a)` を使う。
