---
title: メビウス関数テーブル(Mobius Table)
documentation_of: //math/mobius_all.cpp
date: 2026-03-12
category: 数学
tags: 数学
---

## 説明
`0..M-1` のメビウス関数を線形篩でまとめて求める。
計算量は $O(M)$。

## できること
- `vector<int> mobius_all(int M)`
  `mobius[i] = μ(i)` を満たす長さ `M` の配列を返す

## 使い方
`mobius[0] = 0`, `mobius[1] = 1` になる。
包除や約数和の反転でまとめて使う前計算向けである。
