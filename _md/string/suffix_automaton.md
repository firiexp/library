---
title: Suffix Automaton
documentation_of: //string/suffix_automaton.cpp
date: 2026-03-08
category: 文字列
tags: 文字列
---

## 説明

Suffix Automaton を構築する。
文字列中の全ての部分文字列を状態として圧縮表現でき、異なる部分文字列数や各状態の出現回数集計に使える。
この実装は固定文字種向けの配列遷移で、速度を優先している。

## できること

- `longest_common_substring(t)` : 元の文字列 `s` と `t` の最長共通部分文字列を、`CommonSubstring {s_l, s_r, t_l, t_r}` で返す
- 返す区間は0-indexedの半開区間で、長さが等しく内容も一致する。同じ最大長の答えは任意の1組
- 共通部分が空、またはどちらかが空文字列なら4つとも `0`
- 問い合わせは `const`。繰り返し呼び出せ、`add` 直後にも再構築せず使える

## 計算量

- 構築 : $O(|S|)$
- `count_distinct_substrings()` : $O(|states|)$
- `substring_occurrences()` : $O(|states| + max_len)$
- `longest_common_substring(t)` : 時間 $O(|t|)$、返却値以外の追加領域 $O(1)$

文字種数 `W` はテンプレート引数。各状態の遷移は固定長配列 `int next[W]` で保持する。

## 使い方

1. `SuffixAutomaton<26, 'a'> sam(s);` のように文字種数と開始文字を指定して構築する
2. `sam.add(c)` で 1 文字ずつ伸ばしてもよい
3. `sam.count_distinct_substrings()` で異なる部分文字列数を得る
4. `sam.substring_occurrences()` で各状態に対応する endpos サイズを得る

## 実装上の補足

- `nodes[v].len` は状態 `v` が表す文字列の最大長。
- `nodes[v].link` は suffix link。
- `nodes[v].next` は遷移。
- `nodes[v].first_pos` は代表となる出現の末尾位置。clone は複製元の位置を引き継ぐ。
- `add(c)` に渡す文字は `start <= c < start + W` を満たす前提。
- `longest_common_substring(t)` の `t` に範囲外の文字があれば、その文字で一致を打ち切る。
- `substring_occurrences()` の戻り値は状態ごとの出現回数で、クローン状態は構築時 `0` から集約する。
