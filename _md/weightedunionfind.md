## 説明
各頂点にポテンシャルを持たせた Union-Find である。
併合と差分取得をほぼ償却 `O(alpha(N))` で扱う。

## できること
- `WeightedUnionFind<T> uf(n)`
  頂点数 `n` の構造体を作る
- `int root(int v)`
  頂点 `v` の代表元を返す
- `bool same(int u, int v)`
  `u` と `v` が同じ集合かを返す
- `bool unite(int u, int v, T w)`
  `weight(v) - weight(u) = w` となるように併合する。すでに同じ集合なら `false`
- `T weight(int v)`
  代表元から見た `v` のポテンシャルを返す
- `T diff(int u, int v)`
  `weight(v) - weight(u)` を返す。非連結では使わない
- `int size(int v)`
  `v` が属する集合サイズを返す

## 使い方
差分制約 `weight(y) - weight(x) = w` を追加したいときに `unite(x, y, w)` を呼ぶ。
差分を取りたいときは、先に `same(x, y)` を確認してから `diff(x, y)` を使う。

```cpp
WeightedUnionFind<long long> uf(n);
uf.unite(x, y, w);
if (uf.same(x, y)) {
    long long d = uf.diff(x, y);
}
```

## 実装上の補足
`weights[v]` は親とのポテンシャル差を持ち、経路圧縮時に代表元基準へ畳み込む。
`unite(x, y, w)` の `w` は `y - x` の向きで渡す。
