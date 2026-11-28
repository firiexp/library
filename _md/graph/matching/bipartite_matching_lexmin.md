---
title: 辞書順最小二部マッチング(Lexicographically Minimum Bipartite Matching)
documentation_of: //graph/matching/bipartite_matching_lexmin.cpp
---
## 説明
二部グラフの最大マッチングのうち、左頂点の番号順に並べた対応先の列が辞書順最小になるものを求める。
未マッチを `-1` とし、右頂点番号 `0, 1, ...` より小さいものとして比較する。

## できること
左頂点数を $L$、右頂点数を $R$、辺数を $M$ とする。

- `Bipartite_Matching_LexMin bm(l, r)`
  左 `l` 頂点、右 `r` 頂点の二部グラフを作る。$O(L+R)$
- `void add_edge(int a, int b)`
  左 `a` と右 `b` の間に辺を張る。償却 $O(1)$
- `int solve_LexMin()`
  辞書順最小の最大マッチングを構成して、そのサイズを返す。時間 $O(L(M+L+R))$、領域 $O(M+L+R)$
- `vector<int> match`
  長さ `l + r` の配列。左頂点 `u` と右頂点 `v` がマッチすると、`match[u] == l + v`、`match[l + v] == u` となる。未マッチの頂点の値は `-1`。
- `vector<pair<int, int>> get_pairs() const`
  マッチした辺を `(左頂点番号, 右頂点番号)` の組として左頂点番号の昇順に返す。頂点番号は左右とも 0 始まり。$O(L)$

## 使い方
辺を `add_edge` で追加してから `solve_LexMin()` を呼び、`get_pairs()` や `match` で結果を取り出す。

```cpp
Bipartite_Matching_LexMin bm(3, 2);
bm.add_edge(0, 1);
bm.add_edge(1, 1);
bm.add_edge(2, 0);

int sz = bm.solve_LexMin();  // 2
auto pairs = bm.get_pairs();  // [(1, 1), (2, 0)]
```
