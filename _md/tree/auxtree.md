---
title: 補助木(Aux Tree)
documentation_of: //tree/auxtree.cpp
---
## 説明
必要な頂点集合だけを含む virtual tree を構築する。
LCA を自動で補い、元の木上での親子関係を保ったまま補助木 `out` に辺を張る。

## できること
元の木の頂点数を $N$、`make` に渡す頂点数を $K$ とする。

- `AuxTree tr(n)`
  頂点数 `n` の木を作る。$O(N)$
- `void add_edge(int a, int b)`
  木辺を張る。償却 $O(1)$
- `void buildLCA(int root = 0)`
  根 `root` に対して LCA と距離計算の前処理をする。$O(N\log N)$
- `void make(vector<int>& v)`
  頂点集合 `v` から補助木を作る。`v` を訪問順に並べて重複を除き、必要な LCA 頂点を追加する。$O(K\log K)$
- `void clear(vector<int>& v)`
  `make` 後の `v` に含まれる頂点の `out` を空にする。$O(K)$
- `int LCA(int u, int v)`
  最近共通祖先を返す。$O(1)$
- `int distance(int u, int v)`
  木上距離を返す。$O(1)$

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
`clear(v)` は `make` 後の `v` をそのまま渡す前提である。
