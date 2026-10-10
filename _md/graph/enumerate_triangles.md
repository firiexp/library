---
title: 無向グラフの三角形列挙
documentation_of: //graph/enumerate_triangles.cpp
---

## 説明
単純無向グラフの三角形を重複なく列挙する。
callbackを $O(1)$ とすると時間 $O(N+M\sqrt M)$、入力とcallbackの保持する結果を除く作業領域は $O(N+M)$。

## できること
- `enumerate_triangles(n, edges, callback)`：各三角形について `callback(a,b,c)` をちょうど1回呼ぶ。元の頂点番号で `a < b < c` を満たし、列挙全体の順序は不問

## 使い方
`edges` は `vector<pair<int,int>>` で、各無向辺を1回だけ渡す。
頂点番号は `0..n-1`、自己ループと多重辺はないことを前提とする。
辺の端点の向き・入力順は任意で、入力を書き換えない。空グラフ、孤立点、非連結グラフも扱う。

```cpp
long long count = 0;
enumerate_triangles(n, edges, [&](int a, int b, int c) {
    ++count;
});
```

callback内で頂点重みの積や頂点ごとの三角形数も集計できる。結果の全保存は不要である。

## 実装上の補足
辺を `(次数, 頂点番号)` の小さい端点から大きい端点へ向け、出次数を $O(\sqrt M)$ に抑える。
有向隣接列を連続領域に格納し、隣接先への印と長さ2のパスを照合する。
