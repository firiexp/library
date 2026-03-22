---
title: 区間集合(Interval Set)
documentation_of: //datastructure/interval_set.cpp
date: 2026-03-22
category: データ構造
tags: データ構造
---

## 説明
半開区間 `[l, r)` の和集合を互いに素な区間列として管理する。
区間の追加・削除、被覆長、点を含む区間、mex、前後の区間取得を扱う。

## できること
- `IntervalSet<T, SumT> st`
  空の区間集合を作る
- `bool empty()`
  区間が 1 つもなければ `true`。$O(1)$
- `int size()`
  現在の区間数を返す。$O(1)$
- `SumT total_length()`
  和集合の全長を返す。$O(1)$
- `vector<Interval> intervals()`
  現在の区間列を左端昇順で返す。$O(N)$
- `bool contains(T x)`
  `x` を含むなら `true`。$O(\log N)$
- `Interval find_interval(T x)`
  `x` を含む区間を返す。無ければ `{-1, -1}`。$O(\log N)$
- `Interval insert(T l, T r)`
  `[l, r)` を追加して重なる区間も併合した結果の区間を返す。空区間なら `{l, l}`。触った区間数を $k$ として $O(k \log N)$
- `SumT erase(T l, T r)`
  `[l, r)` を削除し、実際に消えた長さを返す。空区間なら `0`。触った区間数を $k$ として $O(k \log N)$
- `SumT covered_length(T l, T r)`
  `[l, r)` と和集合の共通部分の長さを返す。空区間なら `0`。重なる区間数を $k$ として $O(k\log N)$
- `T mex(T x)`
  `x` 以上で和集合に含まれない最小値を返す。$O(\log N)$
- `Interval prev_interval(T x)`
  左端が `x` 以下で最大の区間を返す。無ければ `{-1, -1}`。$O(\log N)$
- `Interval next_interval(T x)`
  `x` を含む区間、無ければ左端が `x` 以上で最小の区間を返す。無ければ `{-1, -1}`。$O(\log N)$
- `void clear()`
  全区間を消す。$O(N)$

## 使い方
整数集合を連続部分ごとの区間に圧縮して持ちたいときに使う。
`insert` は隣接区間も併合するので、整数集合を `[x, x + 1)` の集まりとして表す用途にも向く。

```cpp
IntervalSet<int, long long> st;
st.insert(2, 5);
st.insert(7, 9);
st.erase(3, 8);
auto len = st.total_length();  // 3
auto mx = st.mex(2);           // 3
```

## 実装上の補足
- 内部では互いに素で左端昇順な区間を `set` で持つ
- `insert` は重なる区間と隣接区間をまとめて 1 区間にする
- `prev_interval` と `next_interval` の番兵に `{-1, -1}` を使うので、この 2 つは `T=-1` を表せる型で使う前提と考えるのが安全
