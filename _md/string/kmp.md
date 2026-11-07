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

### 単発検索

- `vector<int> kmp_table(s)` : 失敗関数テーブルを $O(|s|)$ で返す
- `vector<int> kmp_search(text, pattern)` : 一致開始位置を昇順で返す。位置は0-indexed。$O(|text| + |pattern|)$

### KMPMatcher

同じ matcher に渡した各 chunk を、呼び出し順に連結した列として検索する。

- `KMPMatcher matcher(pattern)` : `pattern` のテーブルを構築する。時間・保持領域は $O(|pattern|)$
- `void scan(chunk, emit)` : `chunk` を読み、一致するたびに `emit(long long pos)` を呼ぶ。`pos` は連結した列上の0-indexed開始位置
- `void scan(first, last, emit)` : iterator 区間 `[first,last)` を chunk として渡す
- `void reset()` : 照合状態と通算位置を初期化する。テーブルは再利用する。$O(1)$

読み込んだ要素数を $N$、一致数を $Z$ として、`scan` 全体で $O(N+Z)$。
`emit` の呼び出し回数は $Z$ 回。

通算要素数は `long long`、パターン長と単発検索のテキスト長は `int` に収まる前提とする。

## 使い方

単発検索は `auto pos = kmp_search(text, pattern);` でよい。

### KMPMatcher

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

整数列も同じ手順で検索する。

```cpp
KMPMatcher matcher(vector<long long>{-1, 1000, -1});
vector<long long> a = {-1, 1000}, b = {-1, 1000, -1};
vector<long long> positions;
auto emit = [&](long long pos) { positions.push_back(pos); };
matcher.scan(a, emit);
matcher.scan(b.begin(), b.end(), emit);
```

位置 `0, 2` が通知される。

## 実装上の補足

- 空パターンの `kmp_search` は文字間と両端の境界 `0..|text|` をすべて返す。
- 空パターンの `scan` は初回の位置 `0` と各文字後の境界を1回ずつ `emit` に渡す。空の `chunk` を繰り返しても同じ境界を重複して渡さない。`reset()` 後は位置 `0` から渡し直す。
- 文字列はバイト列として比較する。`string` / `string_view` は埋め込まれた NUL も扱う。
- コールバックから同じ matcher の `scan` / `reset` を呼ばない。
