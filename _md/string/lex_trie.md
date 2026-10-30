---
title: 辞書順比較付きTrie
documentation_of: //string/lex_trie.cpp
date: 2026-10-25
category: 文字列
tags: 文字列
---

## 説明
文字列や整数列をノードで表し、末尾への追加と、ノード間の辞書順比較を行う。
ノード `0` は空文字列を表す。同じ文字列を追加すると同じノード番号を返し、追加前のノードも引き続き使える。

## できること
ノード数を $N$、最大文字列長を $L$、追加する文字列長を $M$、予約容量を $C$ とする。領域は $O(N + C)$。

- `LexTrie trie(cap = 0)`
  空文字列だけを持つ trie を作る。`cap` は根以外のノード数の予約容量。$O(C)$。
- `void reserve(int cap)`
  ノード配列とハッシュ表の容量を予約する。既存ノードの番号は変わらず、容量は縮小しない。期待 $O(N + C)$
- `int size() const`
  根を含むノード数を返す。$O(1)$
- `int length(int v) const`
  ノード `v` の文字列長を返す。$O(1)$
- `vector<int> restore(int v) const`
  ノード `v` の列を整数列として返す。根なら空列。時間・返却領域とも $O(\mathrm{length}(v))$
- `string restore_string(int v) const`
  ノード `v` の列を文字列として返す。根なら空文字列。各要素が $0$ 以上 $255$ 以下の列に使う。時間・返却領域とも $O(\mathrm{length}(v))$
- `int append(int p, int c)`
  `p` の末尾に整数 `c` を1個追加したノードを返す。`c` は `int` の全範囲を使える。期待償却 $O(1)$
- `int append(int p, char c)`
  `c` を符号なしバイトとして追加する。期待償却 $O(1)$
- `int append(int p, string_view s)`
  `p` の末尾に `s` の各文字を符号なしバイトとして追加したノードを返す。空なら `p` を返す。期待償却 $O(M)$
- `int insert(string_view s)`
  根から `s` を追加したノードを返す。空なら `0` を返す。期待償却 $O(M)$
- `int compare(int a, int b) const`
  辞書順で `a < b` なら `-1`、同じなら `0`、`a > b` なら `1` を返す。$O(\log L)$
- `bool less(int a, int b) const`
  辞書順で `a < b` なら `true` を返す。$O(\log L)$
- `int lca(int a, int b) const`
  最長共通接頭辞を表すノードを返す。$O(\log L)$
- `int lcp(int a, int b) const`
  最長共通接頭辞の長さを返す。$O(\log L)$
- `int jump(int v, int k) const`
  末尾を `k` 文字取り除いたノードを返す。`k < 0` または `k > length(v)` なら `-1`。$O(\log L)$

## 使い方
`insert` で文字列を追加し、返されたノード番号を `append` や `compare` に渡す。
ノード番号は有効な範囲、予約容量は非負とする。

```cpp
LexTrie trie;
int a = trie.insert("ab");
int b = trie.append(a, 'c');
int c = trie.append(a, "d");
bool smaller = trie.less(b, c);
int prefix = trie.lca(b, c);
int common = trie.lcp(b, c);
```

この例では `smaller` は `true`、`prefix` は `a`、`common` は `2` になる。
整数列は `append(p, c)` を繰り返して作り、符号付き整数の大小で比較する。

文字列の出力には `restore_string`、整数列の取得には `restore` を使う。

```cpp
Printer out;
out.println(trie.restore_string(b));
```

この例では `abc` を出力する。

1文字追加を最大 `q` 回行うなら `LexTrie trie(q);` とする。
指定を省略した場合や予約容量を超えた場合は自動拡張する。

## 実装上の補足
各ノードに親と1本のジャンプ先を持ち、葉の追加時に祖先情報を定数時間で更新する。
最初の子は直接参照し、2個目以降の子は開番地法のハッシュ表で探す。
最初の子をたどるパスの先頭も保持し、同じパス上の比較と、パスの先頭同士が兄弟である場合の比較を定数時間で処理する。
最大長や文字の種類数の事前指定は不要。
