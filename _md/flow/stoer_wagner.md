---
title: 無向グラフの全域最小カット(Stoer–Wagner法)
documentation_of: //flow/stoer_wagner.cpp
---

## 説明

非負の辺重みを持つ無向グラフを2つの空でない頂点集合に分け、両者を結ぶ辺の重みの総和を最小にする。密グラフ向けの Stoer–Wagner 法を使う。

## できること

- `pair<T, vector<int>> stoer_wagner(vector<vector<T>> graph)`
  最小カットの重みと、片側に属する元の頂点番号を返す。最小カットが複数あればその1つを返す。非連結グラフの最小カットの重みは $0$。頂点数 $V$ が $2$ 未満なら `{0, {}}` を返す。時間 $O(V^3)$、領域 $O(V^2)$。

## 使い方

$V \times V$ の対称な隣接行列を渡す。辺がない頂点対の成分は $0$ とし、多重辺は重みを合計して両方の成分に入れる。対角成分は使わない。どのカットの重みも型 `T` に収まる必要がある。

```cpp
vector<vector<long long>> graph{
    {0, 10, 0, 0},
    {10, 0, 3, 0},
    {0, 3, 0, 10},
    {0, 0, 10, 0}
};
auto [weight, side] = stoer_wagner(graph);  // weight == 3
```
