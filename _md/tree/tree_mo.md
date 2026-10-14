---
title: 木上パスのMo
documentation_of: //tree/tree_mo.cpp
date: 2026-10-14
category: 木
tags: 木
---

## 説明
静的な連結木のパスに対するクエリを Mo でまとめて処理する。
頂点1個の追加・削除で答えを更新できる、順序に依存しない集計を扱う。色の種類数などに使える。

## できること
- `tree_mo_solve(g, paths, add, erase, output, root=0)`
  `paths` の各 `(u,v)` について、パス上の全頂点を1回ずつ有効にして `output(id)` を呼ぶ。`id` は入力クエリ番号
- `add(v)` / `erase(v)`
  元の頂点番号 `v` を追加・削除する。状態は空集合から始め、終了時も空集合に戻る

## 使い方
`g` は `vector<vector<int>>` の無向木、`paths` は `vector<pair<int,int>>` とする。
root と各端点は有効な頂点番号を指定する。入力の木とクエリ列は変更しない。
Euler Tour とバケット幅は内部で管理する。
同一端点や祖先関係のあるパスもそのまま渡せる。空クエリ列では callback を呼ばず、空グラフでもよい。

```cpp
tree_mo_solve(g, paths,
    [&](int v) { if (frequency[color[v]]++ == 0) ++distinct; },
    [&](int v) { if (--frequency[color[v]] == 0) --distinct; },
    [&](int id) { answer[id] = distinct; });
```

`output` は現在の集計状態を変更しない。呼び出し順はクエリ順とは限らない。

## 実装上の補足
辺を往復する長さ $2N-1$ の Euler Tour を作り、パスの両端を隣接頂点へ動かす。
移動先が現在のパス内なら元の端点を削除し、パス外なら移動先を追加する。
これによりパス上の頂点集合を保てる。木の走査は反復処理なので、深い木でも stack 設定の変更は不要。

準備は $O(N+Q)$、ソートは $O(Q\log Q)$、領域は $O(N+Q)$。
バケット幅は $B=\max(1,\lfloor (2N-1)/\sqrt Q\rfloor)$ を内部で選ぶ。
頂点の追加・削除は合計 $O(QB+N^2/B+N)$ 回、`output` は $Q$ 回呼ぶ。
パスの向きに沿った順序付き集約には使えない。
