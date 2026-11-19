---
title: 重み付き辺構造体(edge)
documentation_of: //graph/edge.cpp
---

## 説明
最短路などのグラフアルゴリズムで共通に使う重み付き辺の構造体。

## できること
- `edge<T>(int to, T cost)`
  行き先 `to` と重み `cost` を持つ辺を作る。`from` は `-1`。$O(1)$
- `edge<T>(int from, int to, T cost)`
  始点 `from`、行き先 `to`、重み `cost` を持つ辺を作る。$O(1)$
- `explicit operator int() const`
  行き先頂点 `to` へ明示変換する。$O(1)$

## 使い方
隣接リスト `vector<vector<edge<long long>>>` や辺リスト `vector<edge<long long>>` の要素として使う。

```cpp
vector<vector<edge<long long>>> g(n);
g[u].emplace_back(v, w);
```
