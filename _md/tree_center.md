---
category: "\u6728"
date: 2026-03-08
layout: post
tags: "\u6728"
title: Tree Center
---

## 説明
重みなし木の中心と半径を `O(N)` で求める。
中心は 1 頂点または隣接する 2 頂点になる。

## できること
- `pair<int, vector<int>> tree_center(const vector<vector<int>>& g)`
  木の半径と中心頂点列を返す
- 戻り値の `first`
  半径
- 戻り値の `second`
  中心頂点を 1 個または 2 個持つ

## 使い方
隣接リストを `vector<vector<int>>` で持って `tree_center(g)` を呼ぶ。

```cpp
auto [radius, centers] = tree_center(g);
```

## 実装上の補足
直径の両端点を BFS 2 回で求め、直径パスの中央を中心とする。
直径長が偶数なら中心は 1 個、奇数なら中心は 2 個になる。
