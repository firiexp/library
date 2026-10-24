---
title: Floor/Ceil Division
documentation_of: //util/ifloor.cpp
date: 2026-03-08
category: util
tags: util
---

## 説明
符号付き整数に対する床除算と天井除算。
C++ の `/` は 0 方向丸めなので、その差を吸収する。

## できること
- `T ifloor(T x, T y)`
  $\lfloor x/y\rfloor$ を返す。$O(1)$
- `T iceil(T x, T y)`
  $\lceil x/y\rceil$ を返す。$O(1)$

## 使い方
`y != 0` を仮定する。
負数を含む除算境界の計算で使う。
