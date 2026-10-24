---
title: Segment Tree Beats!
documentation_of: //datastructure/segmenttree/segbeats.cpp
---
## 説明
`range chmin`、`range chmax`、`range add`、`range sum` をまとめて処理する Segment Tree Beats である。

## できること
配列長を $N$ とする。

- `SegmentTreeBeats<T> seg(v)`
  配列 `v` から構築する。$O(N)$
- `void chmin(int l, int r, T x)`
  半開区間 `[l, r)` の各値を `min(a_i, x)` にする。償却 $O(\log^2 N)$
- `void chmax(int l, int r, T x)`
  半開区間 `[l, r)` の各値を `max(a_i, x)` にする。償却 $O(\log^2 N)$
- `void add(int l, int r, T x)`
  半開区間 `[l, r)` に `x` を加える。$O(\log N)$
- `T sum(int l, int r)`
  半開区間 `[l, r)` の総和を返す。$O(\log N)$

## 使い方
```cpp
vector<long long> a(n);
SegmentTreeBeats<long long> seg(a);

seg.chmin(l, r, x);
seg.chmax(l, r, x);
seg.add(l, r, x);
long long ans = seg.sum(l, r);
```

## 実装上の補足
最小値・次小値・最大値・次大値とその個数を持つ典型的な Segment Tree Beats 実装である。
`INF<T>` を使うので、利用側で `template<class T> constexpr T INF = ...;` を定義しておく必要がある。

計算量の分析は[原著資料](https://ruogu-alter.github.io/2020/04/07/segment-tree-beats/segment_tree_beats.pdf)と[著者による補足](https://jiry-2.blog.uoj.ac/blog/1404)を参照。
