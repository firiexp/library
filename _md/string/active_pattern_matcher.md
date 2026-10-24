---
title: 重み更新付きパターン照合
documentation_of: //string/active_pattern_matcher.cpp
---

## 説明
パターン辞書を構築し、テキスト中の重み付き出現回数の総和を求める。
異なる位置の一致も数え、空パターンは `text.size()+1` 回とする。

## できること
総パターン長を $P$、パターン数を $K$、Aho-Corasick の 状態数を $V$とする。

- `ActivePatternMatcher<W, start> matcher(patterns)`
  `vector<string>` から辞書を構築する。初期重みはすべて0。時間 $O(P+V \sigma +K)$、領域 $O(V \sigma +K)$
- `set_weight(id, value)`
  入力順のパターン `id` の重みを `long long` の `value` に置き換える。負の重みも使える。$O(\log V)$
- `long long query(S)`
  各パターンの出現回数と現在の重みの積を合計する。$O((|text|\log V)$

## 使い方
パターン・テキストの各文字は `start <= c < start + W` を満たす前提。
`id` は `0..K-1`。同じ文字列を複数登録した場合も、重みは ID ごとに独立する。
辞書は空でもよい。構築後のパターン追加・削除は扱わない。

```cpp
ActivePatternMatcher<26, 'a'> matcher({"a", "aa", "a"});
matcher.set_weight(0, 2);
matcher.set_weight(1, -1);
long long answer = matcher.query("aaa");
```

この例の答えは $3\cdot2-2=4$ になる。
各重みと照会の最終結果は `long long` に収まるものとする。

## 実装上の補足
Aho-Corasick の failure 木の部分木を連続区間へ写し、Fenwick 木で区間加算・点取得する。
failure 木の部分木サイズと区間は構築順を用いて求め、再帰は使わない。
照会はテキストの先頭と各文字の直後の状態だけを読むため、照会ごとの全状態走査や一致の列挙は不要である。
