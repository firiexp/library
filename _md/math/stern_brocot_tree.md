---
title: Stern-Brocot木
documentation_of: //math/stern_brocot_tree.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
Stern-Brocot 木上の有理数の位置を、連続した `L` / `R` 移動列として扱う。
分数と経路の相互変換、LCA、祖先、部分木の表す区間の取得に使える。

## できること
$L$ を圧縮後の経路長とする。2つの経路ではその長さの最大値を使う。

- `vector<Move> encode_path(ll a, ll b)`
  既約分数 `a / b` への経路を、同じ方向への連続した移動をまとめた列で返す。$O(\log\max(a,b))$
- `Node decode_path(const vector<Move>& path)`
  経路から節点を復元する。$O(L)$
- `Node apply(Node node, Move move)`
  節点から `move.dir` の方向へ `move.steps` 回下る。$O(1)$
- `vector<Move> lca_path(const vector<Move>& a, const vector<Move>& b)`
  2 つの経路の共通接頭辞を返す。$O(L)$
- `vector<Move> ancestor_path(const vector<Move>& path, ll k)`
  根から深さ `k` の祖先への経路を返す。深さが足りなければ空。$O(L)$
- `ll depth(const vector<Move>& path)`
  根からの移動回数の合計を返す。$O(L)$
- `Node range(ll a, ll b)`
  `a / b` を根とする部分木が表す開区間 `(p / q, r / s)` を返す。$O(\log\max(a,b))$
- `Node lca(ll a, ll b, ll c, ll d)`
  2 つの分数の LCA を返す。$O(\log\max(a,b,c,d))$

## 使い方
`Node` は部分木の境界 `(p / q, r / s)` を持ち、現在の節点は mediant `(p + r) / (q + s)` で取れる。
経路は `Move{Left, x}` や `Move{Right, x}` の列で扱い、`x` は同じ方向へ続けて下る回数を表す。
`SternBrocotTree` 名前空間の関数と型を使う。

`encode_path(a, b)` は既約分数を想定する。
`ancestor_path(path, k)` の `k` は根からの深さで、`depth(path)` を超えると空を返す。
