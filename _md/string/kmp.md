---
title: KMP法
documentation_of: //string/kmp.cpp
date: 2026-03-08
category: 文字列
tags: 文字列
---

## 説明

Knuth-Morris-Pratt 法。
文字列 `pattern` の失敗関数テーブルを `kmp_table` で構築し、
`kmp_search(text, pattern)` で `pattern` の出現開始位置を列挙する。
`KMPMatcher` は前処理を再利用し、分割されたテキストを逐次照合する。

## できること

- `kmp_table(s)` : 失敗関数テーブルを $O(|s|)$ で返す
- `kmp_search(text, pattern)` : 一致開始位置を昇順の `vector<int>` で返す。$O(|text| + |pattern|)$
- `KMPMatcher matcher(pattern)` : パターンを所有し、テーブルを $O(|pattern|)$ で構築する
- `matcher.scan(chunk, emit)` : `string_view` の `chunk` を直前の入力の続きとして走査し、一致ごとに `emit(long long pos)` を呼ぶ。位置は連結したテキスト上の0-indexed開始位置
- `matcher.reset()` : 照合状態と通算位置を初期化する。パターンとテーブルを再利用し、$O(1)$

パターン長 $M$、総テキスト長 $N$、走査回数 $Q$、一致数 $Z$ に対し、逐次照合は合計 $O(N+Q+Z)$、保持領域は $O(M)$。
通算文字数は `long long`、パターン長は `int` に収まる前提とする。

## 使い方

単発検索は `auto pos = kmp_search(text, pattern);` でよい。

```cpp
KMPMatcher matcher("aba");
vector<long long> positions;
auto emit = [&](long long pos) { positions.push_back(pos); };
matcher.scan("ab", emit);
matcher.scan("aba", emit);
matcher.reset();
matcher.scan("aba", emit);
```

最初の2回は連結した `"ababa"` の位置 `0, 2` を通知し、`reset()` 後は新しいテキストの位置 `0` を通知する。
コールバック内で一致数だけを数えれば、一致位置を保存する領域は不要。

## 実装上の補足

- `pattern` が空文字列のときは、`0..|text|` のすべてを返す。
- 空パターンの `scan` は初回の位置 `0` と各文字後の境界を1回ずつ通知する。空の `chunk` を繰り返しても重複通知しない。`reset()` 後は位置 `0` から通知し直す。
- 入力はバイト列として比較し、埋め込まれた NUL も扱う。コールバックから同じ matcher の `scan` / `reset` を呼ばない。
