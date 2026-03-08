## 説明
Bellman-Ford 法で単一始点最短路を求める。
負辺があっても使え、計算量は `O(VE)`。

## できること
- `vector<T> bellman_ford(int s, int n, vector<edge<T>> &es)`
  始点 `s` から各頂点への最短距離を返す。始点から到達可能な負閉路があるときは空 vector を返す

## 使い方
辺を `edge<T>(from, to, cost)` で列挙し、`bellman_ford(s, n, es)` を呼ぶ。

```cpp
vector<edge<long long>> es;
es.emplace_back(u, v, w);

auto dist = bellman_ford(0, n, es);
if (dist.empty()) {
    // reachable negative cycle
}
```

## 実装上の補足
未到達頂点の距離は `numeric_limits<T>::max()` のまま残る。
負閉路が欲しい場合や `-INF` 伝播が必要な場合は `bellman_ford_negative_loop.cpp` を使う。
