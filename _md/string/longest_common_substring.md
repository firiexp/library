---
title: 複数文字列の最長共通部分文字列
documentation_of: //string/longest_common_substring.cpp
---

## 説明
複数の文字列すべてに現れる最長の連続部分文字列を求める。
最短の入力に Suffix Automaton を構築し、各入力での一致長を状態ごとに集計する。

## できること

- `longest_common_substring<W, start = 'a'>(strings)` : `vector<string>` を受け、最長共通部分文字列を `optional<string>` で返す。入力なしは `nullopt`、共通の非空部分文字列がなければ空文字列

1入力ならその文字列を返す。同じ長さの最長解が複数あれば任意の1つを返す。

入力数を $K$、最短長を $L$、総入力長を $T$ とする。
時間は $O(K+WL+T+KL)=O(K+WL+T)$、追加領域は $O(WL)$。空文字列があれば、最短入力を選んで終了する。

## 使い方

```cpp
vector<string> strings = {"xabcy", "zabc", "abcp"};
auto common = longest_common_substring<26>(strings);
```

この例では `*common` は `"abc"` になる。
文字種は既存の SAM と同じく `start <= c < start + W` とする。入力数・各文字列長・SAM の状態数は `int` に収まる前提。

## 実装上の補足
各文字列を走査した後、一致長を suffix link の先へ最大長で切り詰めながら伝播する。
状態ごとに全入力での最小値を取り、最大のものを代表位置から復元する。
2文字列の最長解を順に絞ると別の候補を失うため、その方法は使わない。
固定テキストに対する2文字列の照会を繰り返す場合は、`SuffixAutomaton::longest_common_substring` を使うと構築を再利用できる。
