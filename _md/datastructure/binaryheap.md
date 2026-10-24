---
title: 二分ヒープ(Binary Heap)
documentation_of: //datastructure/binaryheap.cpp
---
## 説明
最大値を取り出す二分ヒープである。
要素和も同時に管理する。

## できること
要素数を $N$ とする。

- `binary_heap<T> pq`
  空の最大ヒープを作る。$O(1)$
- `void emplace(T x)`
  `x` を追加する。償却 $O(\log N)$
- `T top() const`
  最大値を返す。空のときは未定義。$O(1)$
- `void pop()`
  最大値を 1 つ削除する。空のときは未定義。$O(\log N)$
- `size_t size() const`
  要素数を返す。$O(1)$
- `bool empty()`
  空なら `true` を返す。$O(1)$
- `ll sum() const`
  全要素の総和を返す。$O(1)$

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
