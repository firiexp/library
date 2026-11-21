---
title: 無向グラフの彩色数
documentation_of: //graph/chromatic_number.cpp
---

## 説明
無向グラフの隣り合う頂点が異なる色になるように塗るときの最小の色数（彩色数）を求める。

## できること
- `int chromatic_number(int n, const vector<pair<int, int>> &edges)`
  頂点数 $n$（$0 \le n \le 20$）の単純無向グラフの彩色数を返す。時間 $O(n 2^n)$、領域 $O(2^n)$

## 使い方
頂点番号は $0$ から $n - 1$ とし、`edges` に各辺の両端を渡す。

```cpp
vector<pair<int, int>> edges = { {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0} };
int colors = chromatic_number(5, edges);  // 3
```

## 実装上の補足
各頂点部分集合に含まれる独立集合の個数を部分集合 DP で求め、包除原理により $k$ 個の独立集合で全頂点を覆えるかを判定する。
オーバーフローを避けるため、積が $2^{nk}$ を超える複数の素数冪 mod で判定する。
