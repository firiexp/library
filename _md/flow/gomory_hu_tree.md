---
title: 全頂点対最小カット(Gomory–Hu木)
documentation_of: //flow/gomory_hu_tree.cpp
---

## 説明
無向容量グラフの全頂点対の最小カット値を、元の頂点番号を持つ重み付き木にまとめる。
木上の2頂点間のパスにある最小の辺重みが、元のグラフでの最小カット値となる。
同じグラフで多数の頂点対を問い合わせる場合に使う。

## できること
元のグラフの頂点数を $N$、辺数を $M$ とする。

- `GomoryHuTree<T>::Edge{u, v, capacity}`
  頂点 `u`, `v` を結ぶ無向辺と非負の整数容量。
- `GomoryHuTree<T> tree(n, edges)`
  $N-1$ 回の最大流で木を構築する。最大流以外の時間は $O(N(N+M))$。
- `const vector<Edge>& edges() const`
  木の $N-1$ 本の辺を返す。`capacity` が木の辺重み。$O(1)$。
- `T min_cut(int u, int v) const`
  異なる2頂点間の最小カット値を返す。非連結な成分間では0。$O(\log N)$。

構築後の保持領域は $O(N\log N)$。1頂点の木は構築でき、`edges()` は空になる。

## 使い方

```cpp
using CutTree = GomoryHuTree<ll>;
vector<CutTree::Edge> input{ {0, 1, 3}, {1, 2, 4}, {0, 2, 2}};
CutTree tree(3, input);
ll value = tree.min_cut(0, 2);
const auto& weighted_tree = tree.edges();
```

この例の `value` は5となる。元のグラフを変更した場合はオブジェクトを作り直す。

## 実装上の補足
各最大流の前に `reset_flow()` で残余容量を初期状態へ戻す。
最小カットの始点側に従って親を付け替え、親子を反転する場合は既存のカット値も引き継ぐ。
問い合わせは木上の二分累乗でパスの最小値を求める。カットを構成する元の辺集合を返す API は持たない。
最大流には無向版 `Dinic` を使い、1回あたりの最悪時間は $O(MN^2)$。内部の DFS は再帰なので、大きく深いグラフではスタック容量に注意する。
