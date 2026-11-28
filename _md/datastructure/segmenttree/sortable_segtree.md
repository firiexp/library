---
title: 区間ソートと区間積
documentation_of: //datastructure/segmenttree/sortable_segtree.cpp
---

## 説明
key と値を一緒に区間ソートし、区間積を求める。
非可換モノイドに対応し、積は列の左から右へ取る。

## できること
要素数を $N$、`key_upper` を $U$ とする。

- `SortableSegmentTree<M> seg(keys, values, key_upper = uint64_t(1) << 31)`
  同じ長さの `vector<int>` と `vector<T>` から構築する。`key_upper` は `1` 以上、各 key は相異なる非負整数とする。$O(N \log U)$ 時間、$O(N \log U)$ 領域。
- `void set(int i, int key, const T& value)`
  位置 `i` の key と値を置き換える。新しい key は $[0,U)$ に収まる非負の `int` で、ほかの位置の key と異なるものとする。$O(\log N+W)$。
- `void sort_ascending(int l, int r)`
  `[l,r)` を key の昇順にソートする。$Q$ 回の操作通算で構築と合わせて償却 $O((N+Q)(\log N+\log U))$。
- `void sort_descending(int l, int r)`
  `[l,r)` を key の降順にソートする。$Q$ 回の操作通算で構築と合わせて償却 $O((N+Q)(\log N+\log U))$。
- `T fold(int l, int r)`
  現在の配列の半開区間 `[l,r)` の値を左から順に合成する。$O(\log N+\log U)$。
- `pair<int,T> get(int i) const`
  位置 `i` の key と値を返す。$O(\log N+\log U)$。
- `int size() const`
  要素数を返す。$O(1)$。
- `NodeStats node_stats() const`
  確保数・解放数・生存数・最大生存数・確保済みスロット数（`allocations`, `releases`, `live`, `peak_live`, `slots`）を返す。$O(1)$。

## 使い方
`M` に値型 `T`、結合的な合成 `f`、単位元 `e()` を定義する。
次は文字列を key 順に並べ替えて連結する例。文字列の合成時間は長さに依存する。

```cpp
struct Concat {
    using T = string;
    static T f(const T& a, const T& b) { return a + b; }
    static T e() { return ""; }
};
SortableSegmentTree<Concat> seg({3, 0, 2}, {"A", "B", "C"}, 4);
seg.sort_ascending(0, 3);
string value = seg.fold(0, 3);  // "BCA"
```

将来の更新 key の事前読み込みや座標圧縮は不要で、削除済み key は再利用できる。
同時に存在する同値 key の安定ソートは扱わない。

## 実装上の補足
各ブロックを正順・逆順の積を持つ値域木で表し、ブロックの開始位置を FastSet で管理する。
`fold` はブロックを分割せず、両端の部分区間の積を値域木から、その間のブロックの積を外側の SegmentTree から求める。
ソートで値域木を併合するときに回収したノードは、ブロックの分割や点更新で再利用する。
