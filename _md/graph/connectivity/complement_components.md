---
title: 補グラフの連結成分
documentation_of: //graph/connectivity/complement_components.cpp
---

## 説明
単純無向グラフの補グラフについて、連結成分を列挙する。
補グラフの隣接リストを作らずに求める。

## できること
元グラフの頂点数を $N$、辺数を $M$ とする。

- `vector<vector<int>> complement_components(const vector<vector<int>>& g)`
  補グラフの各連結成分を頂点列として返す。空グラフなら空の配列。時間 $O(N+M)$、入力・出力を除く作業領域 $O(N)$

## 使い方
`g` は頂点番号 `0` から `n-1` の対称な隣接リストとし、自己ループ・平行辺を含めない。

```cpp
vector<vector<int>> g(n);
g[u].push_back(v);
g[v].push_back(u);
auto components = complement_components(g);
```

各頂点は結果にちょうど1回現れる。
成分の順序と、成分内の頂点の順序は保証しない。

## 実装上の補足
未訪問頂点を連結リストで管理し、元のグラフで隣接していない頂点を取り出して探索する。
取り出す処理は各頂点に1回だけで、取り出さずに通過する処理は元の辺に対応する。
