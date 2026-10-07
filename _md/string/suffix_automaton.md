---
title: Suffix Automaton
documentation_of: //string/suffix_automaton.cpp
date: 2026-03-08
category: 文字列
tags: 文字列
---

## 説明
Suffix Automaton を構築する。
異なる部分文字列数、各状態の出現回数、別文字列との最長共通部分文字列を求める。

## できること
元の文字列 `s` の長さを $N$、状態数を $V$ とする。文字種数 `W` は定数として扱う。

- `SuffixAutomaton<W, start> sam` : 空文字列から $O(1)$ で構築する
- `SuffixAutomaton<W, start> sam(s)` : 文字列 `s` から $O(N)$ で構築する
- `reserve(n)` : 長さ `n` を見込んで状態の領域を確保する。$O(n)$
- `add(c)` : 末尾に文字 `c` を追加し、追加後の文字列全体に対応する状態番号を返す。償却 $O(1)$
- `build(t)` : 末尾に文字列 `t` を追加する。償却 $O(|t|)$
- `count_distinct_substrings()` : 異なる部分文字列数を返す。$O(V)$
- `substring_occurrences()` : 各状態の出現回数を状態番号順の `vector<int>` で返す。$O(V+N)$
- `order_by_length()` : 各状態が表す最大長の昇順に状態番号を返す。$O(V+N)$
- `longest_common_substring(t)` : `s` と `t` の最長共通部分文字列の位置を `SubstringMatch` で返す。時間 $O(|t|)$、返却値以外の追加領域 $O(1)$

## 使い方
`SuffixAutomaton<26, 'a'> sam(s);` のように文字種数と開始文字を指定する。
構築時や `add(c)` で追加する文字は `start <= c < start + W` を満たす前提。

`auto match = sam.longest_common_substring(t);` とすると、
`[match.s_l, match.s_r)` が `s` 側、`[match.t_l, match.t_r)` が `t` 側の0-indexed半開区間を表す。
最長の答えが複数ある場合は任意の1組を返す。共通部分が空なら4つとも `0`。
集計・照合は構築済みオートマトンを変更せず、`add` の後も再構築せず繰り返せる。

## 実装上の補足
- `nodes[v].len` は状態 `v` が表す文字列の最大長。
- `nodes[v].link` は suffix link。
- `nodes[v].next` は遷移。
- `nodes[v].first_pos` は代表となる出現の末尾位置。clone は複製元の位置を引き継ぐ。
- `substring_occurrences()` の戻り値は状態ごとの出現回数で、クローン状態は構築時 `0` から集約する。
