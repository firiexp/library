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
  辺を追加し、辺番号を返す。償却 $O(1)$
- `Result solve() const`
  始点を自動で選び、オイラー路が存在すればその経路を返す。存在しないときは `exists == false`。時間・領域 $O(N+M)$
- `Result solve(int start) const`
  頂点 `start` から始まるオイラー路を返す。そのような経路がない場合や `start` が範囲外の場合は `exists == false`。時間・領域 $O(N+M)$

`Result` は次を持つ。

- `bool exists`
  Eulerian trail が存在するか
- `vector<int> vertices`
  通る頂点列。成功時の長さは `M + 1` で、閉路なら先頭と末尾が一致する
- `vector<int> edge_ids`
  通る辺番号列。成功時の長さは `M`

## 使い方
全辺を `add_edge` で追加し、始点を指定する場合は `solve(start)`、自動で選ぶ場合は `solve()` を呼ぶ。始点には `0 <= start < n` を満たす頂点番号を指定する。
`vertices[i] -> vertices[i + 1]` に対応する辺番号が `edge_ids[i]` に入る。
頂点数は1以上とし、自己ループ・多重辺も扱う。辺がなければ頂点列は `solve()` では `{0}`、有効な始点を指定した `solve(start)` では `{start}` となり、辺番号列は空になる。
存在しない場合は両方の列が空になる。

辺がある場合、閉路なら辺に接するどの頂点からでも始められる。始点と終点が異なるオイラー路の場合、有向グラフでは出次数が入次数より1大きい頂点、無向グラフでは奇数次数の2頂点のどちらかが始点になる。始点から全辺をたどれなければ失敗する。

## 実装上の補足
Hierholzer 法で構成する。
有向辺は隣接表に1回だけ現れるため、走査位置だけで管理する。無向辺では使用済み配列も使う。
