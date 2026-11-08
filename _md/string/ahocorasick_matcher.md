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
- `scan(string_view chunk, f)`
  `chunk` をそれまでに `scan` へ渡した文字列の末尾に続けて検索し、一致ごとに `f(int id, long long position)` を呼ぶ。`position` はつなげたテキストでの0始まりの出現開始位置
- `reset()`
  `patterns` を再利用し、次の `scan` から別のテキストを先頭位置0で検索する。$O(1)$

`scan` の呼出し数を $C$、総入力長を $N$、一致数を $Z$、関数 `f` の1回の計算量を $F$ として、合計 $O(C+N+ZF)$。
`scan` の追加領域は $O(1)$。

## 使い方
パターンとテキストの各文字は `0 <= c - start < W` を満たすものとする。
空パターンは各文字の直前とテキスト末尾に一致する。例えば `"ab"` に対しては、位置0・1・2で `f` を呼ぶ。

`"ab"` と `"aba"` を順に渡すと、`"ababa"` を検索した場合と同じ結果になる。

```cpp
AhoCorasickMatcher<26, 'a'> matcher({"aba", "ba", "aba"});
vector<pair<int, long long>> matches;
auto emit = [&](int id, long long position) {
    matches.emplace_back(id, position);
};
matcher.scan("ab", emit);
matcher.scan("aba", emit);
```

scan は一致の終端位置が小さい順に関数 `f` を呼ぶ。同じ終端では長いパターンから順に、同一文字列では `id` の昇順に呼ぶ。
パターンの追加・変更には matcher を作り直す。
callback の実行中に同じ matcher の `scan`・`reset` を呼んだり、matcher 自体を変更したりしてはならない。

## 実装上の補足
各状態に、failure 連鎖上で次にパターンが終端となる状態へのリンクを持つ。
scan はこのリンクだけをたどるため、一致のない接尾辞を繰り返し走査しない。
