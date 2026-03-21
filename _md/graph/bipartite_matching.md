---
title: 二部グラフ最大マッチング(Bipartite Matching)
documentation_of: //graph/bipartite_matching.cpp
---
## 説明
二部グラフの最大マッチングを単純 DFS で求める。
左頂点数を `L`、右頂点数を `R`、辺数を `M` とすると計算量は $O(LM)$。

## できること
- `Bipartite_Matching bm(l, r)`
  左 `l` 頂点、右 `r` 頂点の二部グラフを作る
- `void add_edge(int a, int b)`
  左 `a` と右 `b` の間に辺を追加する
- `int matching()`
  最大マッチング数を返す
- `vector<pair<int, int>> get_pairs()`
  現在のマッチングを `(左, 右)` の列で返す

## 使い方
辺を追加してから `matching()` を呼ぶ。
マッチ先は `match` に入り、左 `i` の相手は `match[i] - l` で取れる。

```cpp
Bipartite_Matching bm(l, r);
for (auto [a, b] : edges) bm.add_edge(a, b);

int sz = bm.matching();
auto pairs = bm.get_pairs();
```

## 実装上の補足
Hopcroft-Karp より遅いが、実装が短く拡張しやすい。
`Bipartite_Matching_LexMin` の基底クラスとしても使う。
最悪ケースが重いため、このリポでは現状 Library Checker の重い verify には載せていない。
