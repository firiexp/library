---
title: 無向グラフの st-numbering
documentation_of: //graph/connectivity/st_numbering.cpp
---

## 説明
無向グラフの全頂点を、`s` を先頭、`t` を末尾とする順序に並べる。
`s` 以外の各頂点には自分より前に隣接頂点が少なくとも1つあり、`t` 以外の各頂点には自分より後ろに隣接頂点が少なくとも1つある。

## できること
頂点数を $V$、辺数を $E$ とする。

- `vector<int> st_numbering(const vector<vector<int>>& g, int s, int t)`
  隣接リスト `g` と異なる2頂点 `s, t` を受け取り、条件を満たす頂点列を返す。そのような順序がなければ空列を返す。`s` と `t` の間に辺がなくてもよい。時間 $O(V+E)$、追加領域 $O(V)$

## 使い方
```cpp
vector<vector<int>> g = { {2, 3}, {3}, {0}, {0, 1} };
auto order = st_numbering(g, 2, 1);  // {2, 0, 3, 1}
```
