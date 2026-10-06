---
title: 下限制約付きs-t最大流 (Max Flow with Lower Bounds)
documentation_of: //graph/maxflow_lower_bound.cpp
date: 2026-03-07
category: フロー
tags: 最大流
---

## 説明
有向グラフの各辺に下限・上限を持つ `s-t` 最大流を求める。
各辺の上下限と、`s`, `t` 以外の頂点の流量保存を満たす非負の `s-t` 流を対象とする。
時間は $O(V^2 E)$、各辺の流量復元は追加で $O(E)$、領域は $O(V+E)$。

## できること
- `MaxFlowLowerBound<T> g(n)`
  頂点数 `n` のグラフを作る
- `void add_edge(int from, int to, T lower, T upper)`
  下限・上限付き有向辺を追加する。自己ループ・平行辺も扱う
- `pair<bool, T> max_flow(int s, int t)`
  実行可能性と最大流量を返す。実行不能なら `{false, 0}`
- `Result max_flow_with_edges(int s, int t)`
  `exists`, `value`, `edge_flow` を返す。`edge_flow[i]` は追加順での各辺の流量
  実行不能なら `exists=false`, `value=0`、`edge_flow` は空

## 使い方
```cpp
MaxFlowLowerBound<long long> g(n);
g.add_edge(u, v, lower, upper);
auto result = g.max_flow_with_edges(s, t);
if (result.exists) {
    long long maximum = result.value;
    vector<long long> flows = result.edge_flow;
}
```

## 実装上の補足
`0 <= lower <= upper`、`s != t` が必要で、容量・需要の合計・中間計算は `T` と `INF<T>` の範囲に収める。
負の正味 `s-t` 流だけが存在する場合は実行不能とする。
下限を需要に変換し、超始点・超終点と `t -> s` の辺で実行可能性を調べる。
元の辺の流量は下限に逆辺の残余容量を足して復元する。
どちらの API も登録した辺を変更せず、再実行できる。
