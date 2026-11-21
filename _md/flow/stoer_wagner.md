---
title: 無向グラフの全域最小カット(Stoer–Wagner法)
documentation_of: //flow/stoer_wagner.cpp
---

## 説明
非負重み付き無向グラフの全域最小カットを Stoer–Wagner 法で求める。

## できること
頂点数を $V$ とする。

- `pair<T, vector<int>> stoer_wagner(vector<vector<T>> graph)`
  全域最小カットの重みと、カットの一方に属する頂点番号列を返す。$V < 2$ なら `{0, {}}`。時間 $O(V^3)$、領域 $O(V^2)$

## 使い方
$V \times V$ の対称な隣接行列を渡す。辺がない組は `0`、多重辺は重みの和を入れ、対角成分は使わない。

```cpp
vector<vector<long long>> graph{
    {0, 10, 0, 0},
    {10, 0, 3, 0},
    {0, 3, 0, 10},
    {0, 0, 10, 0}
};
auto [weight, side] = stoer_wagner(graph);  // weight == 3
```
