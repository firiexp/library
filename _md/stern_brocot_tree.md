---
layout: post
title: Stern Brocot Tree
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
Stern-Brocot 木上の有理数の位置を、連続した `L` / `R` 移動列として扱う。
分数と経路の相互変換、LCA、祖先、担当区間の取得に使える。

## できること
- `vector<Move> encode_path(ll a, ll b)`
  既約分数 `a / b` への経路を run-length 圧縮して返す
- `Node decode_path(const vector<Move>& path)`
  経路から節点を復元する
- `Node apply(Node node, Move move)`
  節点から `move` 回だけ下る
- `vector<Move> lca_path(const vector<Move>& a, const vector<Move>& b)`
  2 つの経路の共通接頭辞を返す
- `vector<Move> ancestor_path(const vector<Move>& path, ll k)`
  根から深さ `k` の祖先への経路を返す。深さが足りなければ空
- `ll depth(const vector<Move>& path)`
  経路長を返す
- `Node range(ll a, ll b)`
  `a / b` を根とする部分木が表す開区間 `(p / q, r / s)` を返す
- `Node lca(ll a, ll b, ll c, ll d)`
  2 つの分数の LCA を返す

## 使い方
`Node` は部分木の境界 `(p / q, r / s)` を持ち、現在の節点は mediant `(p + r) / (q + s)` で取れる。
経路は `Move{Left, x}` や `Move{Right, x}` の列で扱う。

`encode_path(a, b)` は既約分数を想定する。
`ancestor_path(path, k)` の `k` は根からの深さで、`depth(path)` を超えると空を返す。
