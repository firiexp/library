---
title: Bellman-Ford法
documentation_of: //graph/shortest_path/bellman_ford.cpp
---

## 説明
Bellman-Ford 法で単一始点最短路や、始点から到達可能な負閉路を求める。
負辺があっても使える。

## できること
頂点数を $V$、辺数を $E$ とする。

- `vector<T> bellman_ford(int s, int n, vector<edge<T>> &es)`
  始点 `s` から各頂点への最短距離を返す。始点から到達可能な負閉路があるときは空配列。$O(VE)$。
- `vector<int> bellman_ford_negative_cycle(int s, int n, const vector<edge<T>> &es)`
  始点から到達可能な負閉路を1つ、辺の向きに沿った入力辺ID列で返す。辺IDは `es` の添字で、平行辺も区別する。負閉路がなければ空配列。時間 $O(VE+V)$、追加領域 $O(V)$。

## 使い方
辺を `edge<T>(from, to, cost)` で列挙する。
距離が必要なら `bellman_ford`、負閉路の辺列が必要なら `bellman_ford_negative_cycle` を呼ぶ。

```cpp
vector<edge<long long>> es;
es.emplace_back(u, v, w);

auto dist = bellman_ford(0, n, es);
auto cycle = bellman_ford_negative_cycle(0, n, es);
for (int id : cycle) use(es[id]);
```

`0 <= s < n` とし、緩和中のすべての距離加算が `T` の範囲に収まる必要がある。
グラフ全体の負閉路を調べるには、全頂点への重み0の辺を持つ超始点を加える。
超始点へ戻る辺はないため、返る閉路は元の辺だけからなる。
負閉路の影響を受ける頂点も知りたい場合は `bellman_ford_negative_loop.cpp` を使う。

## 実装上の補足
`bellman_ford` では未到達頂点の距離が `numeric_limits<T>::max()` のまま残る。
負閉路の復元では距離を飽和させず、未到達かどうかを別に保持する。
負閉路を通るたびに距離が減るため、単純路の長さだけで型の範囲を見積もらない。
返す閉路は任意の1つで、先頭辺や長さは保証しない。
