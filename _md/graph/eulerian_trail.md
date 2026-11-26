---
title: オイラー路(Eulerian Trail)
documentation_of: //graph/eulerian_trail.cpp
---

## 説明
有向グラフまたは無向グラフの Eulerian trail / circuit を 1 つ構成する。
辺をちょうど 1 回ずつ通る頂点列と辺番号列を返す。

## できること
頂点数を $N$、辺数を $M$ とする。

- `EulerianTrail<false> g(n)`
  頂点数 `n` の無向グラフを作る。$O(N)$
- `EulerianTrail<true> g(n)`
  頂点数 `n` の有向グラフを作る。$O(N)$
- `int add_edge(int from, int to)`
  辺を追加し、0 始まりの辺番号を返す。償却 $O(1)$
- `Result solve() const`
  Eulerian trail が存在すれば構成を返す。存在しないとき `exists == false`。時間・領域 $O(N+M)$
- `Result solve(int start) const`
  頂点 `start` から始まる Eulerian trail が存在すれば構成を返す。存在しないときや `start` が範囲外のとき `exists == false`。時間・領域 $O(N+M)$

返り値の `EulerianTrail::Result` は次のメンバを持つ。

- `bool exists`
  Eulerian trail が存在するか
- `vector<int> vertices`
  通る頂点列。存在する場合は長さ $M + 1$、存在しない場合は空
- `vector<int> edge_ids`
  通る辺番号列。存在する場合は長さ $M$、存在しない場合は空

## 使い方
全辺を `add_edge` で追加し、`solve()` または始点を指定して `solve(start)` を呼ぶ。
`vertices[i] -> vertices[i + 1]` に対応する辺番号が `edge_ids[i]` に入る。
頂点数は 1 以上とし、自己ループ・多重辺も扱う。辺がなければ頂点列は `solve()` で `{0}`、範囲内の `start` に対する `solve(start)` で `{start}`、辺番号列は空になる。

```cpp
EulerianTrail<true> g(3);
int e0 = g.add_edge(0, 1);
int e1 = g.add_edge(1, 2);
auto res = g.solve(0);
// res.exists == true, res.vertices == {0, 1, 2}, res.edge_ids == {e0, e1}
```

## 実装上の補足
Hierholzer 法で構成する。
有向辺は隣接表に 1 回だけ現れるため、走査位置だけで管理する。無向辺では使用済み配列も使う。
