---
title: DSU on Tree
documentation_of: //tree/dsu_on_tree.cpp
---
## 説明
各頂点を根とする部分木について、DSU on Tree を使って部分木クエリを処理する。

用途ごとに `add-remove` 型と `add-reset` 型を分けている。

`run_add_remove` は `add` と `remove` を 1 頂点ごとに呼ぶ。
各頂点は高々 $O(\log N)$ 回だけ追加・削除されるので、`add` が 1 回 $T_{\mathrm{add}}$、`remove` が 1 回 $T_{\mathrm{del}}$ なら
$$
O(N \log N \cdot (T_{\mathrm{add}} + T_{\mathrm{del}}))
$$
になる。

`run_add_reset` は `remove` を持たず、不要になった状態を `reset()` でまとめて捨てる。
`add` が重いが `remove` を書きたくないときや、touch した場所だけを履歴から戻したいときに向く。

## できること
- `DSUonTree dsu(n)`
  頂点数 `n` の木を作る。`add_edge` のあと `build(root)` を呼ぶ
- `DSUonTree dsu(g, root)`
  根 `root` を持つ木 `g` を前処理する
- `void add_edge(int u, int v)`
  辺 `u` - `v` を追加する
- `void build(int root = 0)`
  追加した辺から根 `root` を持つ木を前処理する
- `int idx(int v)`
  Euler Tour での `v` の位置を返す
- `int begin(int v)`
  部分木 `v` の Euler Tour 区間の左端を返す
- `int end(int v)`
  部分木 `v` の Euler Tour 区間の右端を返す
- `void run_add_remove(add, query, remove)`
  `add(v)` で頂点を追加し、`query(v)` で部分木 `v` の答えを確定する
  片付け時は部分木内の各頂点に `remove(v)` を呼ぶ
- `void run_add_reset(add, query, reset)`
  `add(v)` で頂点を追加し、`query(v)` で部分木 `v` の答えを確定する
  不要になった状態は `reset()` でまとめて捨てる

## 使い方
`add` は頂点 1 個を現在のデータ構造へ反映する。
`query` は「現在のデータ構造がちょうど頂点 `v` の部分木を表している」タイミングで呼ばれる。

辺を自分で張る場合は次のように使う。

```cpp
DSUonTree dsu(n);
for (auto &&[u, v] : edges) dsu.add_edge(u, v);
dsu.build(0);
```

`add-remove` 型は次のように使う。

```cpp
vector<int> ans(n);
auto add = [&](int v) {
    // 頂点 v を追加
};
auto query = [&](int v) {
    // 部分木 v の答えを記録
};
auto remove = [&](int v) {
    // 頂点 v を削除
};
DSUonTree dsu(g, 0);
dsu.run_add_remove(add, query, remove);
```

`add-reset` 型は次のように使う。
`reset()` は現在のデータ構造全体を初期状態へ戻す。
touch した位置だけを戻すか、世代管理でまとめて無効化する形を想定している。

```cpp
vector<int> ans(n);
auto add = [&](int v) {
    // 頂点 v を追加
};
auto query = [&](int v) {
    // 部分木 v の答えを記録
};
auto reset = [&]() {
    // 全体を初期状態へ戻す
};

DSUonTree dsu(g, 0);
dsu.run_add_reset(add, query, reset);
```

## 実装上の補足
内部では heavy child を先に並べた preorder を持つ。
`run_add_reset` はその順序を逆からたどり、現在区間を伸ばすだけで重い部分木を使い回す。
`DSUonTree(g, root)` に渡した `g` は破壊しない。
