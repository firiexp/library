## 説明
各操作で新しい版を作る fully persistent な Union-Find である。
任意の過去版に対して `same` や `size` を呼べて、過去版からさらに `unite` して別の分岐を作れる。
経路圧縮は使わず、親配列を永続セグ木で持つ。

## できること
- `PersistentUnionFind uf(n)`
  `0..n-1` をそれぞれ別集合として初期化する
- `int versions()`
  保持している版数を返す
- `int latest_version()`
  最新版の番号を返す
- `int count()`
  最新版の連結成分数を返す
- `int count(int t)`
  版 `t` の連結成分数を返す
- `int root(int t, int v)`
  版 `t` での `v` の代表元を返す
- `bool same(int t, int u, int v)`
  版 `t` で `u` と `v` が同じ集合なら `true` を返す
- `int size(int t, int v)`
  版 `t` で `v` が属する集合サイズを返す
- `int copy_version(int t)`
  版 `t` と同じ状態の新しい版を末尾に追加し、その版番号を返す
- `int unite(int t, int u, int v)`
  版 `t` を基準に `u` と `v` を併合した新しい版を末尾に追加し、その版番号を返す。同じ集合でも失敗せず、同じ状態の版を返す

## 使い方
過去版番号を持っておき、そこから `unite` して分岐を作る。
Library Checker の `persistent_unionfind` のように、各クエリが「どの版から派生するか」を指定する問題にそのまま使える。

```cpp
PersistentUnionFind uf(n);
int v1 = uf.unite(0, 0, 1);
int v2 = uf.unite(v1, 1, 2);
bool ok = uf.same(v1, 0, 2);
int sz = uf.size(v2, 0);
```

## 実装上の補足
- 併合は union by size のみで、経路圧縮はしない
- `root` / `same` / `size(v)` は 1 回の親参照ごとに永続セグ木を 1 回辿るので、ならしで `O(log^2 N)` 程度になる
- `unite` は葉 2 か所だけを更新するので `O(log N)` 個のノード追加で済む
