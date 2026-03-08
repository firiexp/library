---
category: util
date: 2026-03-08
layout: post
tags: util
title: IFloor
---

## 説明
符号付き整数に対する床除算と天井除算。
C++ の `/` は 0 方向丸めなので、その差を吸収する。

## できること
- `T ifloor(T x, T y)`
  `floor(x / y)` を返す
- `T iceil(T x, T y)`
  `ceil(x / y)` を返す

## 使い方
`y != 0` を仮定する。
負数を含む除算境界の計算で使う。
