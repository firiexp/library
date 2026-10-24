---
title: Trie 木
documentation_of: //datastructure/trie.cpp
date: 2018-04-28
category: 文字列
tags: 文字列
---

## 説明
文字列を prefix ごとにまとめ、挿入、完全一致検索、prefix からの遷移を扱う。
固定文字種 `W` と文字変換関数 `F` を前提にした実装である。

## できること
文字種数を $W$、文字変換を $O(1)$ とする。

- `Trie<W, F> trie(f, c = '$')`
  文字変換関数 `f` を使って Trie を作る。`c` は根ノードの表示用文字。$O(W)$
- `add(s, x)`
  文字列 `s` を id `x` で挿入する。終端ノードに `x` を記録する。償却 $O(W|s|)$
- `find(s)`
  文字列 `s` の終端ノード番号を返す。見つからなければ `-1`。$O(|s|)$
- `find(cur, c)`
  ノード `cur` から文字 `c` で遷移した先を返す。なければ `-1`。$O(1)$
- `id(cur)`
  ノード `cur` に対応する終端 id を返す。終端でなければ `-1`。$O(1)$
- `const vector<int>& idxs(int cur) const`
  ノード `cur` の終端ID一覧を挿入順の読み取り専用参照で返す。未登録の終端や `cur < 0` では空。取得は $O(1)$、列挙はID数に比例する
- `PrefixIntervals prefix_intervals() const`
  単語IDの列 `order` と、各ノードに対応する半開区間 `range` を返す。ノード数を $V$、登録した単語数を $K$ として $O(WV+K)$ 時間、$O(V+K)$ 領域

## 使い方
`F` は文字を `0` 以上 `W-1` 以下に写す関数として用意する。
`find` で prefix の終端ノードを取り、そのノードの `id` や `idxs` を参照する。

```cpp
auto f = [](char c) { return c - 'a'; };
Trie<26, decltype(f)> trie(f);
trie.add("apple", 0);
int node = trie.find("app");
auto index = trie.prefix_intervals();
auto [l, r] = index.range[node];
```

`index.order[l..r)` は、`"app"` を prefix に持つ登録単語のID列となる。
`find` が `-1` を返した場合、その prefix を持つ単語はない。
`order` は文字変換関数 `f` の順に並び、同じ終端のIDは挿入順を保つ。
空文字や同じIDの複数登録も含まれる。単語を追加した後は `prefix_intervals()` を呼び直す。

同じ単語に登録したIDだけを列挙する場合は `idxs` を使う。

```cpp
trie.add("apple", 1);
int terminal = trie.find("apple");
for (int id : trie.idxs(terminal)) {
    use(id);
}
```

## 実装上の補足
- 同じ文字列を複数回挿入すると `idxs(cur)` に id が追加される。`id(cur)` は最後に入れた値になる
- `idxs` が返す参照や iterator は、`add` や Trie の破棄で無効になることがある。追加後も保持するなら明示的にコピーする。`prefix_intervals()` の返り値は独立した snapshot である
- `find(cur, c)` は `cur < 0` を自動では防がないので、呼び出し側で確認する
