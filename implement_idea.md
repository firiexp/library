# Implementation Ideas

## implicit_treap

### 背景

- 現状の `datastructure/implicit_treap.cpp` は join-based treap
- `reverse(l, r)` / `apply(l, r, x)` / `fold(l, r)` はそれぞれ
  `split(root, l)` -> `split(rest, r - l)` -> 区間の部分木を操作する -> `merge` -> `merge`
  の順に処理する
- 単発 range 操作の定数倍を大きく削るのは難しい

### 案1: RangeHandle API

- `cut(l, r)` で `[l, r)` の部分木を切り出して handle を返す
- handle 上で `reverse` / `apply` / `fold` / `size` / `all_fold` をまとめて実行する
- 最後に `join()` で元に戻す

使用例は次のとおり。

```cpp
auto seg = tr.cut(l, r);
seg.reverse();
seg.apply(x);
auto ans = seg.fold();
seg.join();
```

同じ区間に複数操作をまとめる用途では有効。
一方で、1 クエリ 1 操作の verify にはほとんど効果がない。

### 案2: sequence splay を別実装で持つ

- sentinel 付き splay tree で列を持つ
- `kth(l)` と `kth(r + 1)` を使って対象区間を1つの部分木として取り出す
- 単発の range 操作は treap より定数倍で有利になりやすい

今の `ImplicitTreap` を無理に変えるより、
`datastructure/sequence_splay.cpp` のような別ライブラリで持つ方が自然。

### メモ

- `ImplicitTreap` 自体に入れるなら、既存 API をまとめて呼ぶ仕組みとして `RangeHandle` を足すのが現実的
- 単発 range 操作の高速化が主目的なら、API 追加ではなくデータ構造差し替えの話になる
