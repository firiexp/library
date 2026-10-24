---
title: Virtual Tree Helper
documentation_of: //tree/virtual_tree_helper.cpp
date: 2026-03-08
category: 木
tags: 木
---

## 説明
必要な頂点とその LCA だけを含む virtual tree を構築する。

## できること
元の木の頂点数を $N$、`make` に渡す頂点数を $K$ とする。

- `VirtualTreeHelper vt(n)`
  頂点数 `n` の木を作る。$O(N)$
- `void add_edge(int u, int v)`
  木辺を張る。償却 $O(1)$
- `void build(int root = 0)`
  LCA 前処理をする。$O(N\log N)$
- `int lca(int u, int v)`
  最近共通祖先を返す。$O(1)$
- `int distance(int u, int v)`
  木上距離を返す。$O(1)$
- `VirtualTree make(vector<int> vertices)`
  virtual tree を返す。空集合には `root=-1` と空の `vertices`, `parent` を返す。時間 $O(K\log K)$、追加領域 $O(K)$

## 使い方
返り値の `vertices[i]` は元の木の頂点番号、`parent[i]` はその親の元頂点番号を表す。
根の頂点番号は `root` に入り、その要素の `parent[i]` は `-1`。`vertices` では親が子より先に現れる。
部分木 DP は `vertices` を逆順に走査すればよい。

```cpp
auto tr = vt.make(query_vertices);
for (int i = (int)tr.vertices.size() - 1; i >= 0; --i) {
    int v = tr.vertices[i];
    int p = tr.parent[i];
    if (p != -1) {
        // v -> p に畳み込む
    }
}
```

## 実装上の補足
返り値の頂点列には元の query 頂点に加えて必要な LCA 頂点も入る。
LCA 補完後は、DFS 訪問順が最小の頂点を根にする。返却順は補助木の DFS で決まり、補完後の列を再ソートする必要はない。
内部では `AuxTree` を使い、各クエリ後の `clear` は helper 側で処理する。
