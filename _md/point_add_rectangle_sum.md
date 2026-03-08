---
layout: post
title: Point Add Rectangle Sum
date: 2026-03-08
category: データ構造
tags: データ構造
---

## 説明
点追加と長方形和クエリをまとめて処理する。
全追加点を先に集めて、座圧済み 2 次元 BIT を offline 構築する。

## できること
- `PointAddRectangleSum<T> solver`
  空の solver を作る
- `void add_point(int x, int y, T w)`
  点 `(x, y)` に重み `w` を追加する操作を積む
- `void add_query(int l, int d, int r, int u)`
  半開長方形 `[l, r) x [d, u)` の和クエリを積む
- `vector<T> solve()`
  追加順に各クエリの答えを返す

## 使い方
初期点も更新点も `add_point` で順に積む。
`solve()` はそれまでに現れる全追加点の座標から 2 次元 BIT を構築し、操作列を先頭から再生する。
