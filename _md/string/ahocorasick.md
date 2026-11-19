---
title: Aho-Corasick法
documentation_of: //string/ahocorasick.cpp
---

## 説明
Trie 木に対応するパターンマッチングオートマトンを構築する。

## できること
ノード数を $V$、文字種数を $W$ とする。

- `AhoCorasick<W, start> ac`
  文字種数 `W`、最小文字 `start` の空のオートマトンを作る。$O(W)$
- `int add(const string& s, int cur = 0)`
  Trie 木の位置 `cur` に文字列 `s` を追加し、終端ノードの番号を返す。償却 $O(W|s|)$
- `void build()`
  パターンマッチングオートマトンを構築する。$O(WV)$
- `int next(int x, char c)`
  位置 `x` に文字 `c` を与えたときの行き先を返す。$O(1)$
- `vector<long long> occurrence_counts(const string& text) const`
  ノード順の出現回数を返す。時間 $O(|text|+V)$、追加領域 $O(V)$

## 使い方
`W` に文字種数、`start` に最小文字を指定してインスタンスを作る。
先に `add` でパターンを追加し、その後 `build()` を呼ぶ。
`next` は構築後の遷移を返す。
`add(pattern)` の返す終端 ID を保存しておき、`occurrence_counts(text)[id]` で重なりを含む出現回数を得る。
重複パターンは同じノードを共有する。空パターンの終端は root で、回数は `text.size()+1`。
パターン・テキストの文字は `start <= c < start + W` を満たす前提。

```cpp
AhoCorasick<26, 'a'> ac;
int id0 = ac.add("ab");
int id1 = ac.add("bc");
ac.build();
auto counts = ac.occurrence_counts("abcbc");
long long ans = counts[id0] + counts[id1];
```
