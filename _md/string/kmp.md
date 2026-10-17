---
title: KMP法
documentation_of: //string/kmp.cpp
date: 2026-03-08
category: 文字列
tags: 文字列
---

## 説明

Knuth-Morris-Pratt 法で、テキスト中のパターンの出現開始位置を列挙する。
一度だけ検索するなら `kmp_search` を使う。
同じパターンで複数のテキストを検索するときや、テキストを分割して読み込むときは `KMPMatcher` で前処理を再利用できる。

## できること

- `kmp_table(s)` : 失敗関数テーブルを $O(|s|)$ で返す
- `kmp_search(text, pattern)` : 一致開始位置を昇順の `vector<int>` で返す。位置は0-indexed。$O(|text| + |pattern|)$
- `KMPMatcher matcher(pattern)` : パターンをコピーして保持し、テーブルを $O(|pattern|)$ で構築する
- `matcher.scan(chunk, emit)` : `string_view` の `chunk` を前回の入力の続きとして検索する。一致ごとに `emit(long long pos)` を呼び、連結したテキスト上の0-indexed開始位置を渡す
- `matcher.reset()` : 照合状態と通算位置を初期化し、次のテキストを検索できる状態に戻す。パターンとテーブルは再利用する。$O(1)$

パターン長 $M$、総テキスト長 $N$、`scan` の呼出し回数 $Q$、一致数 $Z$ に対し、逐次照合は合計 $O(N+Q+Z)$、保持領域は $O(M)$。
通算文字数は `long long`、パターン長は `int` に収まる前提とする。

## 使い方

単発検索は `auto pos = kmp_search(text, pattern);` でよい。
テキストを分割して渡す場合は、同じ matcher の `scan` を順に呼ぶ。

```cpp
KMPMatcher matcher("aba");
vector<long long> positions;
auto emit = [&](long long pos) { positions.push_back(pos); };
matcher.scan("ab", emit);
matcher.scan("aba", emit);
```

連結した `"ababa"` の位置 `0, 2` が `positions` に入る。
入力の切れ目をまたぐ一致や、互いに重なる一致も列挙する。

別のテキストを検索するときは `matcher.reset()` を呼んでから `scan` に渡す。
例えば `reset()` 後に `"aba"` を渡すと、新しいテキストの位置 `0` を通知する。
`reset()` が初期化するのは matcher の状態だけなので、保存先の `positions` は必要に応じて呼出し側で空にする。
コールバック内で一致数だけを数えれば、一致位置を保存する領域は不要。

## 実装上の補足

- 空パターンの `kmp_search` は文字間と両端の境界 `0..|text|` をすべて返す。
- 空パターンの `scan` は初回の位置 `0` と各文字後の境界を1回ずつ通知する。空の `chunk` を繰り返しても重複通知しない。`reset()` 後は位置 `0` から通知し直す。
- 入力はバイト列として比較し、埋め込まれた NUL も扱う。
- コールバックから同じ matcher の `scan` / `reset` を呼ばない。
