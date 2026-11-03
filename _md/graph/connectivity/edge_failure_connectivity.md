---
title: 辺除去後の連結判定
documentation_of: //graph/connectivity/edge_failure_connectivity.cpp
---

## 説明
静的な無向グラフで、指定した辺1本を除いた後の2頂点の連結性を問い合わせる。
頂点番号と入力順の辺IDで指定でき、平行辺・自己ループ・非連結グラフも扱う。

## できること
頂点数を $V$、辺数を $E$ とする。保持領域は $O(V+E)$。

- `EdgeFailureConnectivity g(n)`
  `n` 頂点のグラフを作る。空グラフも構築できる。$O(V)$。
- `int add_edge(u, v)`
  無向辺を追加し、0から始まる追加順の辺IDを返す。自己ループにもIDを割り当てる。償却 $O(1)$。
- `void build()`
  全連結成分を前処理する。時間・追加領域 $O(V+E)$。再帰を使わず、長い道でもスタックサイズの変更は不要。
- `bool connected_without_edge(u, v, edge_id) const`
  その辺1本だけを除いたとき、`u` と `v` が連結なら `true` を返す。最悪 $O(1)$。状態は変更しない。

## 使い方
頂点番号は $[0,V)$、辺IDは `add_edge` の返り値を使う。
問い合わせ前に `build()` を呼ぶ。辺を追加した後は再構築が必要で、既存の辺IDは変わらない。

```cpp
EdgeFailureConnectivity g(3);
int e = g.add_edge(0, 1);
g.add_edge(1, 2);
g.build();
bool connected = g.connected_without_edge(0, 2, e);
```

この例の `connected` は `false` となる。
`u == v` は常に `true`。元から別の連結成分なら `false`。
別成分の辺や自己ループを除いても結果は変わらず、平行辺は指定した1本だけを除く。

## 実装上の補足
`TwoEdgeConnectedComponents` のDFS順・部分木サイズ・橋判定を利用する。
元から連結な頂点対について、除去辺が橋でなければ連結性は変わらない。
橋なら、DFS木の子側の部分木に片方の頂点だけが含まれる場合に分断される。
