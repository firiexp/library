---
title: Radix Heap
documentation_of: //datastructure/heap/radixheap.cpp
---

## 説明
最後に取り出したキー以上の値だけを追加できる、非負整数キーの最小優先度付きキュー。

## できること
キーの最大値を $D$ とする。

- `RadixHeap<K, V> heap`
  空の Radix Heap を作る。$O(1)$
- `void emplace(K x, V val)`
  キー `x`、値 `val` の要素を追加する。`x` は最後に取り出したキー以上とする。償却 $O(1)$
- `pair<K, V> top()`
  最小キーの要素を返す。空なら未定義。償却 $O(\log D)$
- `void pop()`
  最小キーの要素を取り除く。空なら未定義。償却 $O(\log D)$
- `size_t size() const`
  要素数を返す。$O(1)$
- `bool empty() const`
  空なら `true` を返す。$O(1)$

## 使い方
キー型 `K` には `int` または `long long`（`ll`）を指定し、非負のキーを追加する。
最後に取り出したキー（初期値は `0`）未満のキーは追加できない。

```cpp
RadixHeap<long long, int> pq;
pq.emplace(0, 0);
auto [d, v] = pq.top();
pq.pop();
```

## 実装上の補足
- 取り出し済み要素は定期的に回収する。回収に伴う要素の移動は `pop` 1 回あたり償却 $O(1)$
- 各 bucket の確保容量は再利用するため、保持領域は現在の要素数だけでは決まらない
- `V` はコピー構築と比較が可能な型を使う。代入できない型も扱える
