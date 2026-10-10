---
title: 静的長方形和(Static Rectangle Sum)
documentation_of: //datastructure/static_rectangle_sum.cpp
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
- `vector<T> solve() const`
  追加順に各クエリの重み和を返す。登録内容を変更せず、同じ入力なら何度呼んでも同じ答えを返す

## 使い方
先に点とクエリを全部追加してから `solve()` を呼ぶ。
`y` 座標は内部で座圧し、各クエリを `x < r` と `x < l` の差に分解して処理する。

## 実装上の補足
点数を $N$、クエリ数を $Q$ とすると、時間は $O((N+Q)\log(N+Q))$、作業領域は $O(N+Q)$。
登録された点・イベント・座標列は保持し、座圧とソートには作業用コピーを使う。イベントのコピーに $2Q$ 個ぶんの領域を使う。
呼び出しごとに全登録内容を再計算するため、点やクエリの追加後も呼べるが、差分だけを処理するものではない。
