---
title: 両端優先度付きキュー
documentation_of: //datastructure/heap/double_ended_priority_queue.cpp
---

## 説明
重複を許す集合に要素を追加し、最小値または最大値を1つずつ取り出せる。

## できること
要素数を $N$ とする。区間ヒープを1本の配列に格納し、領域はこれまでの最大要素数と予約容量の大きい方に比例する。
`min`、`max`、`pop_min`、`pop_max` はキューが空でないときに使う。

- `DoubleEndedPriorityQueue<T> pq`
  空のキューを作る。$O(1)$
- `DoubleEndedPriorityQueue<T> pq(values)`
  `vector<T> values` からキューを構築する。$O(N)$
- `void push(T value)`
  `value` を1つ追加する。償却 $O(\log N)$。配列を再確保する回は $O(N)$、予約容量内での追加は最悪 $O(\log N)$
- `const_reference min() const`
  最小値を返す。$O(1)$
- `const_reference max() const`
  最大値を返す。$O(1)$
- `T pop_min()`
  最小値を1つ削除し、その値を返す。$O(\log N)$
- `T pop_max()`
  最大値を1つ削除し、その値を返す。$O(\log N)$
- `bool empty() const`
  空なら `true` を返す。$O(1)$
- `size_t size() const`
  要素数を返す。$O(1)$
- `void reserve(size_t capacity)`
  `capacity` 個の要素を格納できる容量を確保する。再確保する場合は $O(N)$、容量が足りていれば $O(1)$

## 使い方
値の大小は `operator<` で比較する。`min` と `max` の返り値の型は `vector<T>::const_reference`。

```cpp
DoubleEndedPriorityQueue<int> pq({4, 1, 4});
pq.push(2);
int lo = pq.pop_min(); // 1
int hi = pq.pop_max(); // 4
int remaining = pq.max(); // 4
```
