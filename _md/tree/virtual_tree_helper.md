---
title: Virtual Tree Helper
documentation_of: //tree/virtual_tree_helper.cpp
date: 2026-03-08
category: 木
tags: 木
---

## 説明
`AuxTree` の `make / clear / out` 管理を隠して、DP しやすい形で virtual tree を返す補助ラッパ。
各クエリごとに、必要頂点と補われた LCA 頂点からなる根付き木を作る。
入力の頂点数を $K$ として、`make` は $O(K\log K)$ 時間、追加領域 $O(K)$。

## できること
- `VirtualTreeHelper vt(n)`
  頂点数 `n` の木を作る
- `void add_edge(int u, int v)`
  木辺を張る
- `void build(int root = 0)`
  LCA 前処理をする
- `int lca(int u, int v)`
  最近共通祖先を返す
- `int distance(int u, int v)`
  木上距離を返す
- `VirtualTree make(vector<int> vertices)`
  virtual tree を返す。空集合には `root=-1` と空の `vertices`, `parent` を返す

## 使い方
`make` の返り値は `vertices[i]` とその親 `parent[i]` を持つ。
`parent[i] = -1` の頂点が根で、`i` は親が子より先に出る。
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
根の選択は線形探索で行う。ただし補完後8頂点以下では、小さい集合での速度を保つためソートして先頭を取る。
内部では `AuxTree` を使い、各クエリ後の `clear` は helper 側で処理する。
補完後の列に同じ頂点が複数あっても、その隣接リストを繰り返し空にするだけなので次のクエリには影響しない。
