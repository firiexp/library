---
title: Lyndon分解(Lyndon Factorization)
documentation_of: //string/lyndon_factorization.cpp
date: 2026-03-11
category: 文字列
tags: 文字列
---

## 説明
文字列を Lyndon word の非増加列に一意に分解する。

## できること
- `vector<pair<int, int>> lyndon_factorization(const string& s)`
  各因子の半開区間 `[l, r)` を順に返す。$O(|s|)$

## 使い方
返り値の各区間を `s.substr(l, r - l)` として取り出せる。

```cpp
auto segs = lyndon_factorization(s);
for (auto &&[l, r] : segs) {
    string t = s.substr(l, r - l);
}
```

## 実装上の補足
Duval algorithm を使う。
