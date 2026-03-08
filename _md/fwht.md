---
layout: post
title: FWHT
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
XOR 畳み込みで使う Walsh-Hadamard 変換。
長さを 2 冪に拡張してその場変換する。
計算量は `O(N log N)`。

## できること
- `void fwht(vector<T>& v)`
  `v` を FWHT でその場変換する
- `void ifwht(vector<T>& v)`
  `v` を逆 FWHT でその場変換する。`T` に `+`, `-`, `>> 1` が必要

## 使い方
どちらも長さが 2 冪でなくてもよく、不足分は `0` で埋めてから処理する。
XOR 畳み込みは `fwht(a)`, `fwht(b)` のあと各点積を取り、`ifwht` で戻す。
