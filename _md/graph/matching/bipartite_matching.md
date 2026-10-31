---
title: 二部グラフ最大マッチング(Bipartite Matching)
documentation_of: //graph/matching/bipartite_matching.cpp
---
## 説明
二部グラフの最大マッチングを単純 DFS で求める。

## できること
左頂点数を $L$、右頂点数を $R$、辺数を $M$ とする。

- `Bipartite_Matching bm(l, r)`
  左 `l` 頂点、右 `r` 頂点の二部グラフを作る。$O(L+R)$
- `void add_edge(int a, int b)`
  左 `a` と右 `b` の間に辺を追加する。償却 $O(1)$
- `int matching()`
  現在のマッチングを最大まで増やし、今回増やした本数を返す。1回の計算は $O(L(L+M))$
- `vector<pair<int, int>> get_pairs() const`
  現在のマッチングを `(左, 右)` の列で返す。$O(L)$

## 使い方
辺を追加してから `matching()` を呼ぶ。
マッチ先は `match` に入り、左 `i` の相手は `match[i] - l` で取れる。未マッチのときは `match[i] == -1`。

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
