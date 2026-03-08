---
layout: post
title: Link-Cut Tree
date: 2026-03-08
category: 木
tags: 木
---

## 概要
動的森に対して、辺の `link` / `cut`、根の付け替え、パス集約を償却 `O(log N)` で処理するデータ構造です。

## 計算量
各操作は償却 `O(log N)` です。

## 使い方手順
`LinkCutTree<M> lct(n);` を作り、`M` に `using T`、`static T f(T, T)`、`static T e()` を定義します。
頂点値は `set(v, x)` で更新し、`fold(u, v)` で `u` から `v` への順序付きパス集約を取得します。
辺操作は `link(u, v)`、`cut(u, v)`、根の付け替えは `evert(v)` を使います。

## 実装上の補足
各ノードで順方向集約 `sum` と逆方向集約 `rsum` の両方を持つため、非可換モノイドでもパス順序を保ったまま扱えます。
連結判定は `connected(u, v)`、LCA は `lca(u, v)`、距離は `dist(u, v)` で取得できます。
