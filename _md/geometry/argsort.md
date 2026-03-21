---
title: Arg Sort
documentation_of: //geometry/argsort.cpp
date: 2026-03-08
category: 幾何
tags: 幾何
---

## 説明
整数ベクトルを偏角順に並べる。
下半平面から始めて反時計回りになる順で sort する。
計算量は $O(N log N)$。

## できること
- `void argsort(vector<array<int, 2>>& v)`
  `v` を偏角順にその場で並べ替える

## 使い方
原点ベクトル `(0, 0)` を含むと順序の意味が弱いので基本は入れない。
同一直線上のベクトルの順序は長さでなく外積比較に従う。
