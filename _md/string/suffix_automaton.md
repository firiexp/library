---
title: Suffix Automaton
documentation_of: //string/suffix_automaton.cpp
date: 2026-03-08
category: 文字列
tags: 文字列
---

## 説明

文字列から Suffix Automaton を構築し、異なる部分文字列の個数や辞書順 k 番目を求める。
各状態の出現回数の集計や、別文字列との最長共通部分文字列の検索にも使える。

## できること

元の文字列 `s` の長さを $N$、状態数を $V$ とする。文字種数 `W` は定数として扱う。

- `SuffixAutomaton<W, start> sam` : 空文字列から $O(1)$ で構築する
- `SuffixAutomaton<W, start> sam(s)` : 文字列 `s` から $O(N)$ で構築する
- `reserve(n)` : 長さ `n` を見込んで状態の領域を確保する。$O(n)$
- `add(c)` : 末尾に文字 `c` を追加し、追加後の文字列全体に対応する状態番号を返す。償却 $O(1)$
- `build(t)` : 末尾に文字列 `t` を追加する。償却 $O(|t|)$
- `count_distinct_substrings()` : 異なる部分文字列数を返す。$O(V)$
- `kth_substring(k)` : 異なる非空部分文字列を辞書順に並べたときの `k` 番目を返す。`k` は0-indexed。返り値は元文字列上の半開区間 `[l,r)` を表す `optional<pair<int,int>>` で、負数・範囲外は `nullopt`
- `substring_occurrences()` : 各状態の出現回数を状態番号順の `vector<int>` で返す。$O(V+N)$
- `order_by_length()` : 各状態が表す最大長の昇順に状態番号を返す。$O(V+N)$
- `longest_common_substring(t)` : `s` と `t` の最長共通部分文字列の位置を `SubstringMatch` で返す。時間 $O(|t|)$、返却値以外の追加領域 $O(1)$

`kth_substring` は初回の準備に $O(WV)$、各クエリに最悪 $O(WN)$ かかる。追加領域は $O(V)$。
文字を追加すると、次のクエリで準備をやり直す。

## 使い方

`SuffixAutomaton<26, 'a'> sam(s);` のように文字種数と開始文字を指定する。
構築時や `add(c)` で追加する文字は `start <= c < start + W` を満たす前提。

辞書順 k 番目の部分文字列は返された区間を使って取り出す。

```cpp
string s = "ababa";
SuffixAutomaton<26> sam(s);
if (auto range = sam.kth_substring(2)) {
    auto [l, r] = *range;
    cout << s.substr(l, r - l) << '\n';
}
```

この例では `"aba"` を出力する。
同じ部分文字列が複数の位置に現れても1種類として数え、出現位置は任意の1つを返す。
辞書順は `start` からの文字の順とする。空文字列から構築した場合は全ての `k` に対して `nullopt` を返す。

最長共通部分文字列は `auto match = sam.longest_common_substring(t);` で求める。
`[match.s_l, match.s_r)` が `s` 側、`[match.t_l, match.t_r)` が `t` 側の0-indexed半開区間を表す。
最長の答えが複数ある場合は任意の1組を返す。共通部分が空なら4つとも `0`。
集計・照合は構築済みオートマトンを変更せず、`add` の後も再構築せず繰り返せる。

## 実装上の補足

- `nodes[v].len` は状態 `v` が表す文字列の最大長。
- `nodes[v].link` は suffix link。
- `nodes[v].next` は遷移。
- `nodes[v].first_pos` は代表となる出現の末尾位置。clone は複製元の位置を引き継ぐ。
- `substring_occurrences()` は状態ごとに出現回数を集計する。クローン状態の出現回数は構築時に `0` とし、集計時に加算する。
- `kth_substring` に必要な部分文字列数は `long long` で保持する。初回クエリで集計して再利用し、`add` / `build` で文字を追加したら次のクエリで再計算する。クエリを呼ばない用途ではこの集計を行わない。
- `nodes` / `last` は参照用とし、直接の書き換えには対応しない。直接書き換えた場合はキャッシュとの整合性も保証されない。
