## 説明
必要な頂点集合だけを含む virtual tree を構築する。
LCA を自動で補い、元の木上での親子関係を保ったまま補助木 `out` に辺を張る。

## できること
- `AuxTree tr(n)`
  頂点数 `n` の木を作る
- `void add_edge(int a, int b)`
  木辺を張る
- `void buildLCA()`
  LCA と距離計算の前処理をする
- `void make(vector<int>& v)`
  頂点集合 `v` から補助木を作る。必要なら LCA 頂点も `v` に追加される
- `void clear(vector<int>& v)`
  `make` で使った頂点の `out` を消す
- `int LCA(int u, int v)`
  最近共通祖先を返す
- `int distance(int u, int v)`
  木上距離を返す

## 使い方
`buildLCA()` を先に呼び、その後でクエリごとに対象頂点を `v` に入れて `make(v)` を呼ぶ。
補助木の辺は `out` に無向辺として入る。

```cpp
AuxTree tr(n);
tr.add_edge(u, v);
tr.buildLCA();

vector<int> vs = query_vertices;
tr.make(vs);
for (int x : vs) {
    for (int y : tr.out[x]) {
        // virtual tree 上の辺
    }
}
tr.clear(vs);
```

## 実装上の補足
`make(v)` は引数 `v` を破壊的に変更し、LCA 頂点を追加する。
`clear(v)` は `make` 後の `v` をそのまま渡す前提である。
