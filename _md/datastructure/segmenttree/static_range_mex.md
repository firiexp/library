---
title: 静的区間mex
documentation_of: //datastructure/segmenttree/static_range_mex.cpp
---

## 説明
静的な整数配列に対する複数の区間 mex をまとめて求める。mex は区間に現れない最小の非負整数を指す。

## できること
配列長を $N$、クエリ数を $Q$ とする。

- `vector<int> static_range_mex(a, queries)` : 各半開区間 `[l, r)` の mex を `queries` と同じ順序で返す。$O((N+Q)\log N+Q\log Q)$ 時間、$O(N+Q)$ 追加領域。

## 使い方
`a` は `int` や `long long` などの符号付き整数の `vector`、`queries` は `vector<pair<int, int>>` とする。区間は `0 <= l <= r <= N` を満たすこと。

値の座標圧縮は不要。負値や $N$ を超える値は答えに影響しないので、そのまま渡せる。

```cpp
vector<long long> a{0, 2, 1, -5, 1000000000000LL};
vector<pair<int, int>> queries{ {0, 3}, {1, 3}, {2, 2}};
auto answer = static_range_mex(a, queries);
```

この例の答えは `{3, 0, 0}` になる。

## 実装上の補足
空区間の答えは `0`。空のクエリ列には空配列を返す。

クエリを右端の昇順に処理し、値 $0,\ldots,N$ の最終出現位置を区間最小値のセグメント木に保持する。未出現の初期値は $-1$。右端未満の位置だけを反映し、最終出現位置が左端より小さい最初の値を境界探索で求める。
