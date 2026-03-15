# Implementation Ideas

## implicit_treap

### 背景

- 現状の `datastructure/implicit_treap.cpp` は join-based treap
- `reverse(l, r)` / `apply(l, r, x)` / `fold(l, r)` はそれぞれ
  `split(root, l)` -> `split(rest, r - l)` -> 区間部分木を触る -> `merge` -> `merge`
  を踏む
- 単発 range 操作の定数倍を大きく削るのは難しい

### 案1: RangeHandle API

- `cut(l, r)` で `[l, r)` の部分木を切り出して handle を返す
- handle 上で `reverse` / `apply` / `fold` / `size` / `all_fold` をまとめて実行する
- 最後に `join()` で元に戻す

イメージ:

```cpp
auto seg = tr.cut(l, r);
seg.reverse();
seg.apply(x);
auto ans = seg.fold();
seg.join();
```

同じ区間に複数操作をまとめる用途では有効。
一方で、1 クエリ 1 操作の verify にはほぼ効かない。

### 案2: sequence splay を別実装で持つ

- sentinel 付き splay tree で列を持つ
- `kth(l)` と `kth(r + 1)` を使って区間 subtree を露出する
- 単発の range 操作は treap より定数倍で有利になりやすい

今の `ImplicitTreap` を無理に変えるより、
`datastructure/sequence_splay.cpp` のような別ライブラリで持つ方が自然。

### メモ

- `ImplicitTreap` 自体に入れるなら、既存 API の sugar として `RangeHandle` を足すのが現実的
- 単発 range 操作の高速化が主目的なら、API 追加ではなくデータ構造差し替えの話になる
