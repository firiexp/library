---
title: 木の最近傍有効頂点
documentation_of: //tree/centroid/nearest_active_vertex.cpp
---
## 説明
固定された重みなし木で、頂点の有効・無効を切り替えながら、指定頂点から最も近い有効頂点を求める。
距離が同じなら頂点番号が最小のものを返す。

## できること
頂点数を $N$ とする。保持領域は最大 $O(N\log N)$。

- `NearestActiveVertex nearest(g)`
  隣接リスト `g` の木を前処理する。すべての頂点は初期状態で無効。時間 $O(N\log N)$。
- `void set_active(int v, bool enabled)`
  頂点 `v` を有効または無効にする。同じ状態の再指定は何もしない。最悪 $O(\log^2 N)$、状態が変わらなければ $O(1)$。
- `pair<int, int> nearest(int v) const`
  最近傍の有効頂点までの距離と、その元頂点番号を返す。有効頂点がなければ `{-1, -1}`。時間 $O(\log N)$。

## 使い方
入力は連結な無向木とし、各辺を両端の隣接リストに1回ずつ入れる。辺重みはすべて1、頂点番号は $[0,N)$ とする。
辺の変更や、重み付き木は扱わない。

```cpp
vector<vector<int>> g{ {1}, {0, 2}, {1}};
NearestActiveVertex active(g);
active.set_active(0, true);
active.set_active(2, true);
auto result = active.nearest(1);
active.set_active(0, false);
```

この例の `result` は距離1・頂点0となる。頂点0を無効にした後は、頂点1の最近傍は頂点2になる。
問い合わせ頂点自身が有効なら距離0でその頂点を返す。

## 実装上の補足
`CentroidDecompositionQueryHelper` で各頂点の重心祖先と距離を前計算する。
各重心に、有効頂点の `(距離, 頂点番号)` を削除可能な集合として保持する。
問い合わせでは重心祖先ごとの最小候補に、問い合わせ頂点から重心までの距離を足して比較する。
各候補は実際の距離以上となり、最近傍頂点へのパスを分ける重心では実際の距離に一致する。
