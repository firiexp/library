---
title: SWAG Deque
documentation_of: //datastructure/swag_deque.cpp
---
## 説明
両端キューに対する sliding window aggregation である。
結合則を満たす演算なら、両端への追加・削除と全体積の取得を償却 `O(1)` で処理する。

## できること
- `TwoStackDeque<G> deq`
  空の deque を作る
- `void push_front(const T& v)`
  先頭に `v` を追加する
- `void push_back(const T& v)`
  末尾に `v` を追加する
- `void pop_front()`
  先頭を 1 つ削除する。空なら何もしない
- `void pop_back()`
  末尾を 1 つ削除する。空なら何もしない
- `T fold()`
  deque 全体の積を返す。空なら `G::e()`

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
```

## 実装上の補足
片側が空で削除できないときは、反対側の要素を半分ずつ持ち替える。
各操作は償却 `O(1)` で、非可換な演算にも使える。
