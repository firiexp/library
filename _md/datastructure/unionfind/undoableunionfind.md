---
title: Undoable Union Find
documentation_of: //datastructure/unionfind/undoableunionfind.cpp
---
## 説明
undo / rollback ができる Union-Find である。
併合1回あたりの変更点を保存し、直前の操作や保存した状態まで戻せる。

## できること
頂点数を $N$ とする。

- `UndoableUnionFind uf(n)`
  頂点数 `n` の Union-Find を作る。$O(N)$
- `int root(int v)`
  頂点 `v` の代表元を返す。$O(\log N)$
- `bool same(int u, int v)`
  `u` と `v` が同じ集合かを返す。$O(\log N)$
- `bool unite(int u, int v)`
  `u` と `v` を併合する。すでに同じ集合なら `false`。償却 $O(\log N)$
- `int size()`
  連結成分数を返す。$O(1)$
- `int size(int v)`
  `v` が属する集合サイズを返す。$O(\log N)$
- `void undo()`
  直前の `unite` 1 回を取り消す。履歴が空でないことを前提とする。$O(1)$
- `void snapshot()`
  現在状態を保存する。$O(1)$
- `int get_state()`
  現在の履歴深さを返す。$O(1)$
- `void rollback(int state = -1)`
  指定状態まで巻き戻す。`-1` なら直前の `snapshot()` に戻す。戻す `unite` の回数を $k$ として $O(k)$

## 使い方
分岐探索や offline dynamic connectivity の DFS で、辺を追加して潜ってから `rollback(state)` で戻す形で使う。

```cpp
UndoableUnionFind uf(n);
int state = uf.get_state();
uf.unite(u, v);
bool ok = uf.same(a, b);
uf.rollback(state);
```

## 実装上の補足
経路圧縮をしない Union-Find にしているので、`unite` 1 回で変わる配列要素は高々 2 か所である。
`rollback()` は `undo()` を必要回数だけ繰り返す。
