---
title: 二部グラフの最小辺被覆
documentation_of: //graph/matching/bipartite_minimum_edge_cover.cpp
---

## 説明
二部グラフの全頂点を、最小本数の辺で覆う。
全頂点が選んだ辺の端点に少なくとも1回現れるような、辺 ID の集合を返す。
最小頂点被覆は「全辺に接する頂点集合」を求める操作であり、最小辺被覆とは異なる。

## できること
左右の頂点数を $L,R$、入力辺数を $M$ とする。

- `vector<int> bipartite_minimum_edge_cover(int l, int r, const vector<pair<int, int>>& edges)`
  最小辺被覆の辺 ID 列を返す。孤立点があれば空配列。
  時間 $O((L+R+M)\sqrt{L+R})$、返却値を含む追加領域 $O(L+R+M)$。

## 使い方
`edges[i] = {u, v}` は左側の頂点 `u` と右側の頂点 `v` を結ぶ。
`l, r` は非負、頂点番号はそれぞれ $[0,L)$、$[0,R)$ とする。
多重辺は別の入力辺として扱う。返却 ID の順序は未規定。

```cpp
vector<pair<int, int>> edges{ {0, 0}, {0, 1}, {1, 1}};
auto cover = bipartite_minimum_edge_cover(2, 2, edges);
for (int id : cover) {
    auto [u, v] = edges[id];
}
```

## 実装上の補足
Hopcroft-Karp 法で最大マッチングを求め、その辺を1本ずつ選ぶ。
未マッチの各頂点にはそれに接する任意の辺を1本追加する。
未マッチの左右頂点間には辺が存在しないため、追加する辺は重複しない。
最大マッチングの本数を $K$ とすると、返却する辺数は $L+R-K$。復元は時間 $O(L+R+M)$。
内部の Hopcroft-Karp 法は再帰 DFS を使う。大入力では十分なスタック容量が必要となる。
