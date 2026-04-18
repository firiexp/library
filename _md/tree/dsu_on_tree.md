---
title: DSU on Tree
documentation_of: //tree/dsu_on_tree.cpp
---
## 説明
各頂点を根とする部分木について、追加・削除可能なデータ構造を使って部分木クエリを処理する。

`update` と `clear` を 1 頂点ごとに呼び、各頂点が $O(\log N)$ 回だけ追加・削除されることを使って計算する。
`update` が 1 回 $T_{\mathrm{add}}$、`clear` が 1 回 $T_{\mathrm{del}}$ なら、全体計算量は
$$
O(N \log N \cdot (T_{\mathrm{add}} + T_{\mathrm{del}}))
$$
になる。
特に `update` と `clear` が $O(1)$ なら $O(N \log N)$。

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
- `void run(update, query, clear, reset)`
  `update(v)` で頂点を追加し、`query(v)` で部分木 `v` の答えを確定する
  `keep == false` の片付け時には、部分木内の各頂点に `clear(v)` を呼んだあと `reset()` を呼ぶ

## 使い方
`update` は頂点 1 個を現在のデータ構造へ反映する。
`query` は「現在のデータ構造がちょうど頂点 `v` の部分木を表している」タイミングで呼ばれる。
通常は `clear(v)` で頂点ごとに削除する。

辺を自分で張る場合は次のように使う。

```cpp
DSUonTree dsu(n);
for (auto &&[u, v] : edges) dsu.add_edge(u, v);
dsu.build(0);
```

削除が重い場合は `clear` を空にして、`reset` でデータ構造全体を捨ててもよい。
この場合は touch した位置だけを戻すか、世代管理でまとめて無効化する形にする。
この実装なら `reset` で消す総量も各頂点あたり高々 $O(\log N)$ 回分に抑えられ、全体は償却 $O(N \log N)$ になる。

```cpp
vector<int> ans(n);
auto update = [&](int v) {
    // 頂点 v を追加
};
auto query = [&](int v) {
    // 部分木 v の答えを記録
};
auto clear = [&](int v) {
    // 頂点 v を削除
};
auto reset = [&]() {
    // 全体を初期状態へ戻す
};

DSUonTree dsu(g, 0);
dsu.run(update, query, clear, reset);
```

## 実装上の補足
内部では CSR を使って前処理と走査を行う。
`DSUonTree(g, root)` に渡した `g` は破壊しない。
