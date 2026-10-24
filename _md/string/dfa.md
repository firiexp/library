---
title: 有限オートマトンと条件の合成
documentation_of: //string/dfa.cpp
---

## 説明
文字を `0` から `W-1` で表す決定性有限オートマトン。条件を AND・OR・NOT で合成できる。

## できること
文字種数を $W$、入力 DFA の状態数を $S$、2つの DFA を合成する場合はそれぞれ $S_1,S_2$ とする。

- `DFA<W>{next, accept, initial}` : 遷移表、受理フラグ、初期状態から直接作る
- `DFA<W> intersect(a, b)` : 両方が受理する列を受理する DFA を返す。時間・領域は $O(WS_1S_2)$
- `DFA<W> unite(a, b)` : 少なくとも片方が受理する列を受理する DFA を返す。時間・領域は $O(WS_1S_2)$
- `DFA<W> complement(a)` : `0..W-1` 上の有限列全体に対する補集合を返す。空列を含め、元の DFA が拒否する列だけを受理する。時間・領域は $O(WS)$

## 使い方
`next` は `vector<array<int, W>>`、`accept` は状態数と同じ長さの `vector<char>`。
状態番号は `int` に収まる非負整数とし、`next[v][c] == -1` は拒否遷移を表す。
拒否した列は以後も拒否する。`initial == -1` は空列も含めた全拒否で、既定構築はこの形になる。
それ以外の遷移先と初期状態は有効な状態番号とする。
空列の受理は初期状態のフラグで決まる。受理しない状態から受理状態へ遷移してもよい。

```cpp
auto a = intersect(digit_sum_exact(12), digit_value_mod(12));
auto b = unite(digit_value_mod(3), digit_value_mod(5));
auto c = complement(b);
```

`b` は十進表記の値が3または5で割り切れる列、`c` はどちらでも割り切れない列を受理する。
数字の条件には `math/digit_dfa.cpp` を include する。表は固定長の文字列 DP にも使える。
先頭 0 や数値の上下限はこの表では扱わない。

```cpp
long long count = digit_count<long long>("1", "100", b);
```

`math/digit_dp.cpp` を include すれば、1以上100以下で3または5で割り切れる整数の個数 `47` が得られる。

## 実装上の補足
AND・OR の合成では初期状態対から到達できる状態対だけを返す。状態対の ID 配列は未到達の組も含めて確保する。
OR では片方が拒否遷移に入っても他方の遷移を続け、両方が拒否した遷移を `-1` にする。
NOT では拒否遷移がある場合、その行き先として全列を受理する状態を追加する。`initial == -1` の補集合は全列を受理する1状態となる。
最小化は行わない。必要なら `string/dfa_minimize.cpp` の `minimize(a)` を使う。
