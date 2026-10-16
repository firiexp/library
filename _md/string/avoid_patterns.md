---
title: 禁止部分文字列を避ける有限オートマトン
documentation_of: //string/avoid_patterns.cpp
---

## 説明
指定したパターンを部分文字列として含まない列を受理する `DFA<W>` を作る。
Aho-Corasick の failure 先から禁止判定を伝播し、禁止状態を通らず到達できる状態だけを返す。

## できること
- `avoid_patterns<W, start>(patterns)` : `const vector<string>&` から構築済みの遷移表を返す
- 空のパターン群は全列を受理する。空パターンを含むと空列も含めて全拒否となり、`initial == -1` を返す
- 重複パターンや、一方が他方を含むパターン群も扱う

## 使い方
```cpp
auto a = avoid_patterns<2, 'a'>({"aab", "bbab", "abab"});
auto b = avoid_patterns<10, '0'>({"4", "9"});
```

パターンの各文字 `c` は既存の Aho-Corasick と同じく `start <= c < start + W` を満たす前提。
返却表の文字番号は `c - start` となる。禁止語を完成させる遷移は `-1`、残る全状態は受理状態。
数値の先頭 0 は扱わず、桁 DP 側で制御する。

## 実装上の補足
パターン数を $K$、総長を $P$、Trie ノード数を $V$ とすると、構築は $O(K+P+WV)$ 時間、$O(WV)$ 領域。
空パターンがあればその場で終了する。パターン数分の終端 ID 配列は保持しない。
返却状態数を $R$ とすると返却表は $O(WR)$ 領域。状態数は `int` に収まる範囲で使う。
