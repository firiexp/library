---
title: 併合・一括加算付きヒープ(Leftist Heap)
documentation_of: //datastructure/heap/leftist_heap.cpp
---

## 説明
複数の最小ヒープを管理し、ヒープの併合と優先度への一括加算を扱う。
要素には復元用のIDを付けられる。同じ優先度では小さいIDを選ぶ。

## できること
全ヒープに含まれる要素数を $H$ とする。優先度のコピー・比較・加算は $O(1)$ とする。
ヒープ番号は `0 <= i < m` とし、`top`・`top_with_id`・`pop` は空でないヒープに対して呼ぶ。

- `LeftistHeap<T> heap(int m)`：空のヒープを `m` 個作る。$O(m)$
- `void push(int i, const T &value, int id = -1)`：優先度 `value`、ID `id` の要素を追加する。優先度・IDが同じ要素も別々に保持する。償却 $O(\log H)$
- `T top(int i) const`：最小の優先度を返す。$O(1)$
- `pair<T, int> top_with_id(int i) const`：最小要素の `{優先度, ID}` を返す。$O(1)$
- `void pop(int i)`：最小要素を1個削除する。$O(\log H)$
- `void meld(int i, int j)`：`j` の全要素を `i` に移し、`j` を空にする。`i == j` なら何もしない。$O(\log H)$
- `void add_all(int i, const T &delta)`：ヒープ `i` の全要素の優先度に `delta` を加算する。IDは変えない。空なら何もしない。$O(1)$
- `int size(int i) const`：要素数を返す。$O(1)$
- `bool empty(int i) const`：空かを返す。$O(1)$

## 使い方
通常は `LeftistHeap<long long>` のように数値型を指定する。
独自型を使う場合は、比較 `<` と加算 `+=` が使え、`T{}` が加算の単位元になるようにする。
加算は優先度の大小関係を保ち、優先度・遅延値・中間値が `T` に収まる必要がある。

```cpp
LeftistHeap<long long> heap(2);
heap.push(0, 8, 42);
heap.push(1, 5, 17);
heap.add_all(0, -3);
heap.meld(0, 1);
auto best = heap.top_with_id(0); // {5, 17}
heap.pop(0);
auto next = heap.top_with_id(0); // {5, 42}
```

IDは利用者が指定する識別子で、内部のノード番号とは独立している。
削除ノードを再利用しても、生存する要素のIDは変わらない。併合後の `j` は空のヒープとして再利用できる。

## 実装上の補足
左子のrank以上にならないよう右子のrankを保ち、短い右経路だけを辿って併合する。
削除したnodeは子の添字欄を使ったfree listへ戻すため、`pop` で追加確保しない。
同時に生存した要素数の最大値を $H_{\max}$ とすると、領域は $O(m+H_{\max})$。過去のpush総数には比例しない。
各ノードは優先度と遅延値の `T` を2個、子・rank・IDの `int` を4個持つ。
ID用の `int` が1個増えるが、GCC / x86-64では `T = long long` のノードはパディングを含めて従来と同じ32バイト、`T = int` では20バイトから24バイトになる。
