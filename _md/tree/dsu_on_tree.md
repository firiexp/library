---
title: DSU on Tree
documentation_of: //tree/dsu_on_tree.cpp
---

## 説明
各頂点を根とする部分木のクエリを DSU on Tree でまとめて処理する。
頂点を1個ずつ追加・削除する方法と、状態をまとめて初期化する方法を選べる。

## できること
頂点数を $N$ とする。

- `DSUonTree dsu(n)`
  `n` 頂点の木を作る。$O(N)$
- `DSUonTree dsu(g, root)`
  隣接リスト `g` と根 `root` から前処理する。$O(N)$
- `void add_edge(int u, int v)`
  木辺を追加する。償却 $O(1)$
- `void build(int root = 0)`
  根 `root` で前処理する。$O(N)$
- `int idx(int v)`
  Euler Tour での `v` の位置を返す。$O(1)$
- `int begin(int v)`
  `v` の部分木に対応する半開区間の左端を返す。$O(1)$
- `int end(int v)`
  `v` の部分木に対応する半開区間の右端を返す。$O(1)$
- `void run_add_remove(add, query, remove)`
  `add(v)` で追加し、`remove(v)` で削除する。現在の頂点集合が `v` の部分木と一致するときに `query(v)` を呼ぶ。追加・削除は合計 $O(N\log N)$ 回、クエリは $N$ 回
- `void run_add_reset(add, query, reset)`
  `add(v)` で追加し、`reset()` で全状態を初期化する。現在の頂点集合が `v` の部分木と一致するときに `query(v)` を呼ぶ。追加は合計 $O(N\log N)$ 回、初期化・クエリはそれぞれ $O(N)$ 回

## 使い方
辺を追加して `build(root)` を呼ぶか、隣接リストから構築する。
集計用の状態は空集合から始める。次は部分木の頂点値の和を求める例。

```cpp
DSUonTree dsu(g, 0);
vector<long long> answer(g.size());
long long sum = 0;
dsu.run_add_remove(
    [&](int v) { sum += value[v]; },
    [&](int v) { answer[v] = sum; },
    [&](int v) { sum -= value[v]; });
```

全状態をまとめて初期化できるなら `run_add_reset` を使う。
heavy path ごとに葉側から根側へ頂点を処理し、同じパス上では頂点を追加しながら `query(v)` を呼ぶ。
各 heavy path の処理を始める前と、すべての処理が終わった後に `reset()` を呼ぶ。

```cpp
sum = 0;
dsu.run_add_reset(
    [&](int v) { sum += value[v]; },
    [&](int v) { answer[v] = sum; },
    [&]() { sum = 0; });
```

`reset()` は現在の集計状態を空集合へ戻す。
配列で集計する場合は、変更した位置だけを戻すか、世代番号で無効化するとよい。
