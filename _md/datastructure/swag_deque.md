---
title: SWAG Deque
documentation_of: //datastructure/swag_deque.cpp
---
## 説明
両端キューに対する sliding window aggregation である。
結合則を満たす演算で、両端への追加・削除と全体積の取得を扱う。

## できること
モノイド演算を $O(1)$ とする。

- `TwoStackDeque<G> deq`
  空の deque を作る。$O(1)$
- `size_t size() const`
  要素数を返す。$O(1)$
- `bool empty() const`
  空なら `true` を返す。$O(1)$
- `void push_front(const T& v)`
  先頭に `v` を追加する。償却 $O(1)$
- `void push_back(const T& v)`
  末尾に `v` を追加する。償却 $O(1)$
- `void pop_front()`
  先頭を 1 つ削除する。空なら何もしない。償却 $O(1)$
- `void pop_back()`
  末尾を 1 つ削除する。空なら何もしない。償却 $O(1)$
- `T fold()`
  deque 全体の積を返す。空なら `G::e()`。$O(1)$

## 使い方
`G` に `using T`、`static T f(T, T)`、`static T e()` を定義して使う。
`f(a, b)` は左から右へ並べたときの積を返すようにする。

```cpp
struct Monoid {
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

TwoStackDeque<Monoid> deq;
deq.push_front(3);
deq.push_back(5);
long long x = deq.fold();
while (!deq.empty()) deq.pop_front();
```

## 実装上の補足
片側が空で削除できないときは、反対側の要素を半分ずつ持ち替える。
非可換な演算にも使える。
