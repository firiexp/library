---
title: 辞書順最小二部マッチング(Lexicographically Minimum Bipartite Matching)
documentation_of: //graph/bipartite_matching_lexmin.cpp
---
## 説明
二部グラフの最大マッチングのうち、左側頂点の対応先列を辞書順最小にしたものを求める。
先に通常の最大マッチングを作り、その後に左側を小さい順に確定していく。
未マッチを `-1` とし、右頂点番号 `0, 1, ...` より小さいものとして比較する。
時間は $O(L(M+L+R))$、領域は $O(M+L+R)$。

## できること
- `Bipartite_Matching_LexMin bm(l, r)`
  左 `l` 頂点、右 `r` 頂点の二部グラフを作る
- `void add_edge(int a, int b)`
  左 `a` と右 `b` の間に辺を張る
- `int solve_LexMin()`
  辞書順最小の最大マッチングを構成して、そのサイズを返す
- `vector<int> match`
  `match[v]` に対応先頂点番号が入る。未マッチは `-1`

## 使い方
辺を `add_edge` してから `solve_LexMin()` を呼ぶ。辺の追加順は任意でよい。
完全マッチングがなくても、最大サイズを保って左側の対応先列を最小にする。

```cpp
Bipartite_Matching_LexMin bm(l, r);
for (int u = 0; u < l; ++u) {
    for (int v : candidates[u]) bm.add_edge(u, v);
}
int sz = bm.solve_LexMin();
```

## 実装上の補足
内部の右側頂点は `l` 個ぶんオフセットされた番号で管理する。
`match[u]` が右側頂点を指すとき、元の右頂点番号は `match[u] - l` で取り出せる。
