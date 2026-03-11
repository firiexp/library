---
title: Dynamic Connectivity (オフライン)
date: 2020-02-26
category: グラフ
tags: グラフ
---

## 説明

次の形のクエリをオフラインで $O(q \log^2 q)$ で処理する。
- 決まった辺を追加、削除する
- 連結成分についての情報を取得する

## 使い方
各辺の生存区間を時間セグメント木に乗せ、走査中に Undo 可能 Union-Find で状態を持つ。
