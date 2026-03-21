---
title: Trie 木
documentation_of: //datastructure/trie.cpp
date: 2018-04-28
category: 文字列
tags: 文字列
---

## 説明
文字列を prefix ごとにまとめる木。文字列挿入、完全一致検索、prefix からの遷移を $O(|S|)$ で扱う。
固定文字種 `W` と文字変換関数 `F` を前提にした実装である。

## できること
- `Trie<W, F> trie(f, c = '$')`
  文字変換関数 `f` を使って Trie を作る。`c` は根ノードの表示用文字
- `add(s, x)`
  文字列 `s` を id `x` で挿入する。終端ノードに `x` を記録する
- `find(s)`
  文字列 `s` の終端ノード番号を返す。見つからなければ `-1`
- `find(cur, c)`
  ノード `cur` から文字 `c` で遷移した先を返す。無ければ `-1`
- `id(cur)`
  ノード `cur` に対応する終端 id を返す。終端でなければ `-1`
- `idxs(cur)`
  ノード `cur` に対応する id 一覧を返す。無ければ空

## 使い方
`F` は文字を `0` 以上 `W-1` 以下に写す関数として用意する。
`find` で prefix の終端ノードを取り、そのノードの `id` や `idxs` を参照する。

```cpp
auto f = [](char c) { return c - 'a'; };
Trie<26, decltype(f)> trie(f);
trie.add("apple", 0);
int node = trie.find("app");
```

## 実装上の補足
- 同じ文字列を複数回挿入すると `idxs(cur)` に id が追加される。`id(cur)` は最後に入れた値になる
- `find(cur, c)` は `cur < 0` を自動では防がないので、呼び出し側で確認する
