---
title: 区間ソートと区間積
documentation_of: //datastructure/segmenttree/sortable_segtree.cpp
---

## 説明
key と値を一緒に区間ソートし、現在の位置区間の積を求める。
非可換モノイドに対応し、積は列の左から右へ取る。

## できること
要素数を $N$、key の値域の上端を $U$、$W=\lceil\log_2 U\rceil)$ とする。

- `SortableSegmentTree<M> seg(keys, values, key_upper = uint64_t(1) << 31)`
  同じ長さの `vector<int>` と `vector<T>` から構築する。$O(NW)$ 時間、$O(NW)$ 領域。
  key は $[0,U)$ の相異なる整数とする。
- `void set(int i, int key, const T& value)`
  位置 `i` の key と値を置き換える。変更後も key は相異なるものとする。$O(\log N+W)$。
- `void sort_ascending(int l, int r)`
  `[l,r)` を key の昇順にソートする。
- `void sort_descending(int l, int r)`
  `[l,r)` を key の降順にソートする。
- `T fold(int l, int r)`
  現在の `[l,r)` の値を順番に合成する。$O(\log N+W)$。
- `pair<int,T> get(int i) const`
  位置 `i` の key と値を返す。$O(\log N+W)$。
- `int size() const`
  要素数を返す。$O(1)$。
- `NodeStats node_stats() const`
  ノードに関する情報を返す。$O(1)$。

sort を含む全 $Q$ 操作の時間は、構築と合わせて償却 $O((N+Q)(\log N+W))$。

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
string value = seg.fold(0, 3);
```

将来の更新 key の事前読み込みや座標圧縮は不要で、削除済み key は再利用できる。
同時に存在する同値 key の安定ソートは扱わない。

## 実装上の補足
列を昇順・降順のブロックに分け、各ブロックを要素数と正順・逆順の積を持つ値域木で表す。
操作の端点では順位で木を分割し、sort は範囲内の木を破壊的に併合する。
外側の SegmentTree に各ブロックの積を置く。`fold` も内部のブロック境界を分割する。

分割が作るノードは各操作 $O(W)$。併合で両側が非空の再帰は必ず片方のノードを回収する。
ブロック境界の追加も各操作で定数個なので、ノードの生成・回収と外側の木の更新を通算すると上記の償却計算量になる。
回収したノード枠は分割・点更新で再利用する。

外側の木・ブロック境界・debug 検査用の key 集合は別に必要。一般の `T` ではそのサイズにも比例する。
