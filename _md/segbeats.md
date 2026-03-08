## 説明
`range chmin`、`range chmax`、`range add`、`range sum` をまとめて処理する Segment Tree Beats である。
各操作は償却 `O(log N)`。

## できること
- `SegmentTreeBeats<T> seg(v)`
  配列 `v` から構築する
- `void chmin(int l, int r, T x)`
  半開区間 `[l, r)` の各値を `min(a_i, x)` にする
- `void chmax(int l, int r, T x)`
  半開区間 `[l, r)` の各値を `max(a_i, x)` にする
- `void add(int l, int r, T x)`
  半開区間 `[l, r)` に `x` を加える
- `T sum(int l, int r)`
  半開区間 `[l, r)` の総和を返す

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
