## 説明
各頂点を根とする部分木について、追加・削除可能なデータ構造を使ってクエリを処理する。
全体計算量は、`update` と `clear` が `O(1)` なら `O(N log N)`。

## できること
- `DSUonTree<G> dsu(g, root)`
  根 `root` を持つ木 `g` を前処理する
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
削除が重い場合は `clear` を空にして、`reset` で全体を初期化してもよい。

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
`g[v][0]` が heavy child になるように隣接順を並べ替えるので、`g` は破壊的に変更される。
