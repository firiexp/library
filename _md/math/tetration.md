---
title: Tetration
documentation_of: //math/tetration.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
`a ↑↑ n mod M` をオイラーのトーシェント関数を使って計算する。
`a, n, M` が `long long` に収まる範囲を想定する。

## できること
- `ll totient(ll n)`
  `n` のオイラー関数 `phi(n)` を返す
- `ll tetration(ll a, ll n, ll M)`
  `a ↑↑ n mod M` を返す。`M = 1` なら `0`
- `ll tetration(ll a, ll n, ll M, bool& yojo)`
  内部用。指数の縮約で法をまたいだかを `yojo` に反映しつつ、必要なら `M` を足した値を返す

## 使い方
`tetration(a, n, M)` を呼ぶだけでよい。
`a ↑↑ 0 = 1` として扱う。

`a = 0` では `0 ↑↑ n` を `n >= 1` に対して `0, 1, 0, 1, ...` と解釈する。
再帰で `phi(M)` を辿る実装なので、`M` が小さくなっていく前提に乗る問題で使う。
