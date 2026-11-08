---
title: 有向グラフの全域木数
documentation_of: //graph/spanning_tree/count_directed_spanning_trees.cpp
---

## 説明
指定した根から全頂点へ到達できる有向全域木について、含まれる辺の重みの積を足し合わせる。
すべての重みを1にすると、そのような全域木の個数になる。

## できること
- `DirectedSpanningTreeEdge{from, to, weight}`
  `from` から `to` への有向辺。重みを省略すると1
- `mint count_directed_spanning_trees(n, root, edges)`
  根を `root` とする有向全域木の重み積の総和を返す。到達不能な頂点があれば0、1頂点なら1。$N$ 頂点・$M$ 辺で時間 $O(N^3+M)$、入力を除く作業領域 $O(N^2)$

## 使い方
行列式の計算で非零要素の逆元を使うため、`MOD` には素数を指定する。
多重辺はそれぞれ別の選択肢として数え、自己ループは無視する。
重みに0や負数を指定した場合も、`MOD` で剰余を取って計算する。

```cpp
vector<DirectedSpanningTreeEdge> edges{ {0, 1, 2}, {0, 2, 3}, {1, 2, 5} };
mint answer = count_directed_spanning_trees(3, 0, edges);
```

この例の結果は $2\cdot3+2\cdot5=16$ になる。
全頂点から根へ到達する内向きの木を数える場合は、すべての辺の `from` と `to` を交換して渡す。

## 実装上の補足
辺 $u\to v$ の重みを Laplacian の $(v,v)$ に加え、$(v,u)$ から引く。
根の行・列を除いた行列だけを構築し、既存の `matrix_determinant` で行列式を求める。
