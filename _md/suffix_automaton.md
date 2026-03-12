---
title: suffix automaton
documentation_of: //string/suffix_automaton.cpp
date: 2026-03-08
category: 文字列
tags: 文字列
---

## 概要

Suffix Automaton を構築する。
文字列中の全ての部分文字列を状態として圧縮表現でき、異なる部分文字列数や各状態の出現回数集計に使える。
この実装は固定文字種向けの配列遷移で、速度を優先している。

## 計算量

- 構築 : $O(|S|)$
- `count_distinct_substrings()` : $O(|states|)$
- `substring_occurrences()` : $O(|states| + max_len)$

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
- `add(c)` に渡す文字は `start <= c < start + W` を満たす前提。
- `substring_occurrences()` の戻り値は状態ごとの出現回数で、クローン状態は構築時 `0` から集約する。
