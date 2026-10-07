---
title: Aho-Corasick法
documentation_of: //datastructure/ahocorasick.cpp
---

## 説明
Trie 木に対応するパターンマッチングオートマトンを構築する。
ノード数を $V$、文字種数を $W$ とすると、構築は $O(WV)$。

## できること
- `add(s, cur)` : Trie 木の位置 `cur` に文字列 `s` を追加し、そのノードを返す
- `build()` : パターンマッチングオートマトンを構築する
- `next(x, c)` : 位置 `x` に文字 `c` を与えたときの行き先を返す
- `occurrence_counts(text)` : ノード順の出現回数を `vector<long long>` で返す。時間 $O(|text|+V)$、追加領域 $O(V)$

## 使い方
先に `add` でパターンを追加し、その後 `build()` を呼ぶ。
`next` は構築後の遷移を返す。
`add(pattern)` の返す終端 ID を保存しておき、`occurrence_counts(text)[id]` で重なりを含む出現回数を得る。
重複パターンは同じノードを共有する。空パターンの終端は root で、回数は `text.size()+1`。
空テキストにも対応し、構築済みオートマトンを変更せず繰り返し問い合わせられる。
パターン・テキストの文字は `start <= c < start + W` を満たす前提。
