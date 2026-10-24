---
title: 並列二分探索
documentation_of: //util/parallel_binary_search.cpp
date: 2026-10-14
category: クエリ
tags: クエリ
---

## 説明
更新列の先頭から何個を適用すれば条件が初めて成立するかを、複数のクエリについてまとめて求める。
各条件は更新数 $t=0,\ldots,M$ に対して false から true へ単調に変わるものとする。

## できること
更新数を $M$、クエリ数を $Q$ とする。

- `parallel_binary_search(m, q, reset, apply, check)`
  各クエリの最初の成立時刻を `vector<int>` で返す。初期状態で成立すれば `0`、最後まで不成立なら `m+1`。callback を除いて時間 $O((M+Q)\log M)$、補助領域 $O(M+Q)$

## 使い方
状態を扱う3つの callback を渡す。

- `reset()`
  更新を適用していない初期状態を作る
- `apply(i)`
  0-based の更新 `i` を適用する。各ラウンドで `0` から順に呼ぶ
- `check(id)`
  現在の状態でクエリ `id` が成立するかを返す

`check` は更新 prefix の意味を変えてはならないが、UnionFind の経路圧縮など内部表現の変更はよい。
`0 <= m < INT_MAX`、`q >= 0` とする。
終了後の状態は最後に判定した prefix のままとなる。

```cpp
auto answer = parallel_binary_search(m, q,
    [&] { uf = UnionFind(n); },
    [&](int i) { uf.unite(edges[i].first, edges[i].second); },
    [&](int id) { return uf.same(queries[id].first, queries[id].second); });
```

## 実装上の補足
$O(\log M)$ ラウンドの二分探索を行い、各ラウンドで `reset` を1回、`apply` を高々 $M$ 回、`check` を高々 $Q$ 回呼ぶ。
`q=0` では callback を呼ばない。`m=0` では1回だけ初期化し、各条件を初期状態で判定する。
