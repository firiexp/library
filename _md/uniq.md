---
category: util
date: 2026-03-08
layout: post
tags: util
title: Uniq
---

## 説明
`vector` を sort して重複削除する短い定型。
座標圧縮の前処理などで使う。

## できること
- `sort(v.begin(), v.end());`
  昇順に並べる
- `v.erase(unique(v.begin(), v.end()), v.end());`
  重複を削除する

## 使い方
`vector<T> v;` に対してそのまま 2 行を実行する。
順序は失われるので、元の順序を保ちたい用途には使わない。
