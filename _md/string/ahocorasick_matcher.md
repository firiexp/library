---
title: 文字列のパターン一致位置列挙
documentation_of: //string/ahocorasick_matcher.cpp
category: 文字列
tags: 文字列
---

## 説明
文字列配列 `patterns` を Aho–Corasick 法で前処理し、各文字列がテキスト中に現れる位置を列挙する。
一致した文字列を `patterns` の添字 `id` で区別し、`id` と出現開始位置の組を取得する。
同じ文字列を複数登録した場合は、それぞれの添字について列挙する。重なる出現も含む。

## できること
総パターン長を $P$、パターン数を $K$、状態数を $V$、文字種数を $W$ とする。

- `AhoCorasickMatcher<W, start>(const vector<string> &patterns)`
  パターン配列から構築する。時間 $O(P+K+WV)$、領域 $O(WV+K)$。
- `scan(const string &text, f) const`
  一致ごとに関数 `f(int id, size_t position)` を呼ぶ。`position` は0始まりの出現開始位置。
  一致数を $Z$、関数 `f` の1回の計算量を $F$ として、$O(|text|+ZF)$。

## 使い方
パターンとテキストの各文字は `0 <= c - start < W` を満たすものとする。
空パターンはテキストの各境界 $0,\ldots,|text|$ に1回ずつ出現するものとして扱う。
同じ matcher を複数テキストに再利用できる。

```cpp
AhoCorasickMatcher<26, 'a'> matcher({"aba", "ba", "aba"});
vector<pair<int, size_t>> matches;
matcher.scan("ababa", [&](int id, size_t position) {
    matches.emplace_back(id, position);
});
```

scan は一致の終端位置が小さい順に関数 `f` を呼ぶ。同じ終端では長いパターンから順に、同一文字列では `id` の昇順に呼ぶ。
パターンの追加・変更には matcher を作り直す。

## 実装上の補足
各状態に、failure 連鎖上で次にパターンが終端となる状態へのリンクを持つ。
scan はこのリンクだけをたどるため、一致のない接尾辞を繰り返し走査しない。
