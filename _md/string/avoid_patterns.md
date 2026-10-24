---
title: 禁止部分文字列を避ける有限オートマトン
documentation_of: //string/avoid_patterns.cpp
---

## 説明
指定したパターンを部分文字列として含まない列を受理する `DFA<W>` を作る。

## できること
パターンの総長を $P$、文字種数を $W$ とする。

- `DFA<W> avoid_patterns<W, start>(const vector<string>& patterns)`
  `patterns` のどれも含まない列を受理する DFA を返す。時間・領域は $O(WP)$

## 使い方
```cpp
auto a = avoid_patterns<2, 'a'>({"aab", "bbab", "abab"});
auto b = avoid_patterns<10, '0'>({"4", "9"});
```

パターンの各文字 `c` は `start <= c < start + W` を満たす必要がある。
返却表の文字番号は `c - start` となる。禁止語を完成させる遷移は `-1`、残る全状態は受理状態。
数値の先頭 0 は扱わず、桁 DP 側で制御する。

## 実装上の補足
Aho-Corasick の failure link に沿って禁止判定を伝播し、禁止状態を通らず到達できる状態だけを残す。
空のパターン群なら全列を受理する。空文字列をパターンに含む場合は全列を拒否し、`initial == -1` となる。
