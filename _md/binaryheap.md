---
title: 二分ヒープ(Binary Heap)
documentation_of: //datastructure/binaryheap.cpp
---
## 説明
最大値を取り出す二分ヒープである。
`push`、`pop`、`top` を `O(log N)` で扱い、要素和も同時に管理する。

## できること
- `binary_heap<T> pq`
  空の最大ヒープを作る
- `void emplace(T x)`
  `x` を追加する
- `T top() const`
  最大値を返す。空のときは未定義
- `void pop()`
  最大値を 1 つ削除する。空のときは未定義
- `size_t size() const`
  要素数を返す
- `bool empty()`
  空なら `true` を返す
- `ll sum() const`
  全要素の総和を返す

## 使い方
`T` は `operator<` と `ll` への加減算ができる型を想定している。

```cpp
binary_heap<int> pq;
pq.emplace(3);
pq.emplace(8);
int mx = pq.top();
ll s = pq.sum();
pq.pop();
```

## 実装上の補足
`std::push_heap` / `std::pop_heap` を使った最大ヒープである。
`sum()` は `ll` で保持するので、`T` が大きいときはオーバーフローに注意する。
