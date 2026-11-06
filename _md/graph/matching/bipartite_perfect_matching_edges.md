---
title: 二部グラフの完全マッチングの辺分類
documentation_of: //graph/matching/bipartite_perfect_matching_edges.cpp
---
## 説明
左右同数の二部グラフについて、各入力辺が完全マッチングに必須か、選択可能か、使用不能かを分類する。
多重辺は入力位置ごとに別の辺として扱う。

## できること
左右それぞれの頂点数を $N$、入力辺数を $M$ とする。

- `vector<int> bipartite_perfect_matching_edges(int n, const vector<pair<int, int>>& edges)`
  完全マッチングがあれば、入力順に各辺の分類を返す。存在しなければ空配列。
  時間 $O((N+M)\sqrt N)$、返却値を含む追加領域 $O(N+M)$。

各要素は次の値を取る。

- `0` : 使用不能。どの完全マッチングにも含まれない。
- `1` : 選択可能。一部の完全マッチングに含まれる。
- `2` : 必須。すべての完全マッチングに含まれる。

## 使い方
`edges[i] = {u, v}` は左側の頂点 `u` と右側の頂点 `v` を結ぶ。左右とも頂点番号は $[0,N)$ とする。

```cpp
vector<pair<int, int>> edges{ {0, 0}, {0, 1}, {1, 1}};
auto types = bipartite_perfect_matching_edges(2, edges);
if (!types.empty()) {
    bool required = types[0] == 2;
}
```

## 実装上の補足
Hopcroft-Karp 法で完全マッチングを1つ求め、採用した左右の頂点対を縮約する。
非採用辺 `(u, v)` を `u -> match_right[v]` に置き換え、$N$ 頂点で強連結成分分解する。後処理は時間・領域 $O(N+M)$。
非採用辺は縮約後の両端が同じ強連結成分なら選択可能となる。
採用辺は成分が2頂点以上、または同じ端点を結ぶ非採用の平行辺があれば選択可能で、それ以外は必須となる。
平行辺は縮約後に自己ループとなるため、強連結成分の大きさとは別に記録して辺 ID ごとに分類する。
内部の Hopcroft-Karp 法と強連結成分分解は再帰 DFS を使う。大入力では十分なスタック容量が必要となる。
