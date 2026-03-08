---
layout: post
title: Static Rectangle Sum
date: 2026-03-08
category: データ構造
tags: データ構造
---

## 説明
静的な重み付き点集合に対して、長方形内の重み和をまとめて処理する。
`x` 方向の sweep と `y` 上の BIT を使う。

## できること
- `StaticRectangleSum<T> solver`
  空の solver を作る
- `void add_point(int x, int y, T w)`
  点 `(x, y)` に重み `w` を追加する
- `void add_query(int l, int d, int r, int u)`
  半開長方形 `[l, r) x [d, u)` のクエリを追加する
- `vector<T> solve()`
  追加順に各クエリの重み和を返す

## 使い方
先に点とクエリを全部追加してから `solve()` を呼ぶ。
`y` 座標は内部で座圧し、各クエリを `x < r` と `x < l` の差に分解して処理する。
