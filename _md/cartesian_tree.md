---
title: Cartesian Tree
documentation_of: //tree/cartesian_tree.cpp
---
## 説明
数列から Cartesian tree を `O(N)` で構築する。
各区間の最小値の位置を根にした木で、同じ値があるときは左にある添字を優先する。

## できること
- `auto [g, root] = CartesianTree(a)`
  配列 `a` から木の子リスト `g` と根 `root` を返す

## 使い方
`g[v]` には頂点 `v` の子が入る。
親配列が欲しいときは `g` をなめて復元する。

```cpp
vector<int> a = {3, 1, 4, 1, 5};
auto [g, root] = CartesianTree(a);

vector<int> parent(a.size(), -1);
parent[root] = root;
for (int v = 0; v < (int)a.size(); ++v) {
    for (auto &&u : g[v]) parent[u] = v;
}
```

## 実装上の補足
スタックを使って最小 Cartesian tree を構築する。
`a[i] < a[j]` のときだけ pop するので、`a[i] == a[j]` なら小さい添字が祖先側に残る。
