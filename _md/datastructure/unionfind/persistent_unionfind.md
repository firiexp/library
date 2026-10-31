---
title: 完全永続UnionFind(Fully Persistent Union Find)
documentation_of: //datastructure/unionfind/persistent_unionfind.cpp
---
## 説明
併合ごとに新しいバージョンを作る fully persistent な Union-Find である。
任意の過去のバージョンに対して `same` や `size` を呼べて、過去のバージョンからさらに `unite` して別の分岐を作れる。
経路圧縮は使わず、親配列を永続セグ木で持つ。

## できること
頂点数を $N$ とする。

- `PersistentUnionFind uf(n)`
  `0..n-1` をそれぞれ別集合として初期化する。時間・領域ともに $O(1)$
- `int versions()`
  保持しているバージョン数を返す。$O(1)$
- `int latest_version()`
  最新のバージョンの番号を返す。$O(1)$
- `int count()`
  最新のバージョンの連結成分数を返す。$O(1)$
- `int count(int t)`
  バージョン `t` の連結成分数を返す。$O(1)$
- `int root(int t, int v)`
  バージョン `t` での `v` の代表元を返す。$O(\log^2 N)$
- `bool same(int t, int u, int v)`
  バージョン `t` で `u` と `v` が同じ集合なら `true` を返す。$O(\log^2 N)$
- `int size(int t, int v)`
  バージョン `t` で `v` が属する集合サイズを返す。$O(\log^2 N)$
- `int copy_version(int t)`
  バージョン `t` と同じ状態の新しいバージョンを末尾に追加し、そのバージョン番号を返す。償却 $O(1)$
- `int unite(int t, int u, int v)`
  バージョン `t` を基準に `u` と `v` を併合した新しいバージョンを末尾に追加し、そのバージョン番号を返す。同じ集合でも失敗せず、同じ状態のバージョンを返す。償却 $O(\log^2 N)$

## 使い方
過去のバージョン番号を持っておき、そこから `unite` して分岐を作る。
Library Checker の `persistent_unionfind` のように、各クエリが「どのバージョンから派生するか」を指定する問題にそのまま使える。

```cpp
PersistentUnionFind uf(n);
int v1 = uf.unite(0, 0, 1);
int v2 = uf.unite(v1, 1, 2);
bool ok = uf.same(v1, 0, 2);
int sz = uf.size(v2, 0);
```

## 実装上の補足
- 未更新部分は値 `-1` の不変な1ノードを共有し、更新時だけ経路をコピーする
- 併合は union by size のみで、経路圧縮はしない
- `size` と `unite` は代表元の探索で読んだサイズを再利用し、同じ葉を再取得しない
- 親を高々 $O(\log N)$ 回辿り、各親参照に $O(\log N)$ かかる
- `unite` は葉2か所を同時に更新し、共通経路を1回だけコピーする。追加ノードは2本の根から葉への経路の和集合で、個数は $O(\log N)$。過去のバージョンのノードは変更しない
- 共有ノードの子は自分自身を指す。区間境界と組み合わせる内部表現であり、子リンクだけで辿る通常の木ではない
