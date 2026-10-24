---
title: 木の中心(Tree Center)
documentation_of: //tree/tree_center.cpp
date: 2026-03-08
category: 木
tags: 木
---

## 説明
重みなし木の中心と半径を求める。
中心は 1 頂点または隣接する 2 頂点になる。

## できること
頂点数を $N$ とする。

- `pair<int, vector<int>> tree_center(const vector<vector<int>>& g)`
  `first` に半径、`second` に1個または2個の中心頂点を入れて返す。$O(N)$

## 使い方
隣接リストを `vector<vector<int>>` で持って `tree_center(g)` を呼ぶ。

```cpp
auto [radius, centers] = tree_center(g);
```

## 実装上の補足
直径の両端点を BFS 2 回で求め、直径パスの中央を中心とする。
直径長が偶数なら中心は 1 個、奇数なら中心は 2 個になる。
