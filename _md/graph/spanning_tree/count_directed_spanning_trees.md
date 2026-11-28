---
title: 有向グラフの全域木数
documentation_of: //graph/spanning_tree/count_directed_spanning_trees.cpp
---

## 説明
指定した根から全頂点へ到達できる有向全域木について、含まれる辺の重みの積を足し合わせる。
すべての重みを1にすると、そのような全域木の個数になる。

## できること
頂点数を $N$、辺数を $M$ とする。辺の重みと返り値は素数 `MOD` で割った余りで表す。

- `DirectedSpanningTreeEdge{from, to, weight}`
  `from` から `to` への有向辺。重みを省略すると1
- `mint count_directed_spanning_trees(n, root, edges)`
  根を `root` とする有向全域木の重み積の総和を返す。各強連結成分の頂点数を $s_i$ とすると、時間 $O(N+M+\sum_i s_i^3)$、作業領域 $O(N+M+\sum_i s_i^2)$。特にグラフが DAG なら時間・領域ともに $O(N+M)$

## 使い方
多重辺はそれぞれ別の選択肢として数え、自己ループは無視する。

```cpp
vector<DirectedSpanningTreeEdge> edges{ {0, 1, 2}, {0, 2, 3}, {1, 2, 5} };
mint answer = count_directed_spanning_trees(3, 0, edges); // 2 * 3 + 2 * 5 = 16
```

全頂点から根へ到達する内向きの木を数える場合は、すべての辺の `from` と `to` を交換して渡す。

## 実装上の補足
入次数ラプラシアンから根の行と列を除き、強連結成分ごとの対角ブロックの行列式を掛け合わせる。
成分の外から頂点 $v$ に入る辺の重みも、$(v,v)$ の対角要素に加える。
