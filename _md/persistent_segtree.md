---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
date: 2026-03-08
layout: post
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Persistent Segment Tree
---

## 概要

永続セグメント木。
各更新は新しいバージョンを生成し、過去バージョンへのクエリも可能。

## 計算量

- 構築 : `O(n)`
- `update/add` (1点更新) : `O(log n)`
- `query` (区間積) : `O(log n)`

## 使い方

1. `PersistentSegmentTree<Monoid> seg(n)` または `seg(v)` で初期化
2. `update(version, k, x)` または `add(version, k, x)` で新バージョンを生成
3. `query(version, l, r)` で任意バージョンの区間クエリ

## 提供された機能

- `latest_version()` : 最新バージョン番号
- `versions()` : 保持中バージョン数
- `update(...)` : 点代入で新バージョン作成
- `add(...)` : 点加算（`f(old, x)`）で新バージョン作成
- `query(...)` : 区間クエリ
- `get(t, k)` : バージョン `t` の `k` 番目の値

