---
title: 木の直径(Tree Diameter)
documentation_of: //tree/diameter.cpp
---
## 説明
重みなし木の直径長とその両端点を求める。

## できること
頂点数を $N$ とする。

- `pair<int, pair<int, int>> tree_diameter(const vector<vector<int>> &g)`
  直径を返す。戻り値の `first` は辺数としての直径長、`second.first` と `second.second` は両端点。$O(N)$
- `int diameter(const vector<vector<int>> &g)`
  直径長だけを返す。$O(N)$

## 使い方
隣接リストを `vector<vector<int>>` で持ち、`tree_diameter(g)` を呼ぶ。

```cpp
vector<vector<int>> g(n);
g[u].push_back(v);
g[v].push_back(u);

auto [dist, ends] = tree_diameter(g);
int s = ends.first;
int t = ends.second;
```

直径長だけ欲しいなら `diameter(g)` を使えばよい。
重み付き木には `diameter_weighted.cpp` の `tree_diameter_weighted` を使う。

## 実装上の補足
任意の頂点から最遠点 `s` を取り、さらに `s` から最遠点を取る 2 回 DFS で求める。
木を仮定しているので、連結で閉路のないグラフに対して使う。
