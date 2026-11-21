---
title: 静的配列の区間最頻値
documentation_of: //datastructure/static_range_mode.cpp
---

## 説明
静的配列の区間最頻値とその出現回数をオンラインで求める。

## できること
配列長を $N$ とする。

- `StaticRangeMode<T> mode(a)`
  配列 `a` から構築する。`T` は `<` で比較できる型とする。時間 $O(N\sqrt{N})$、領域 $O(N)$
- `pair<T, int> query(int l, int r) const`
  半開区間 `[l, r)`（$0 \le l < r \le N$）の最頻値とその出現回数を返す。$O(\sqrt{N})$

## 使い方
```cpp
StaticRangeMode<int> mode({4, 7, 4, 7, 7});
auto [value, freq] = mode.query(1, 5);  // value == 7, freq == 3
```

## 実装上の補足
配列を幅 $\sqrt{N}$ のブロックに分け、ブロック区間ごとの最頻値を前計算しておく。
クエリでは中央のブロック区間の最頻値を初期値とし、値ごとの出現位置配列を使って左右の端の要素が現在の最大頻度を上回るかを $O(1)$ ずつ確認する。
