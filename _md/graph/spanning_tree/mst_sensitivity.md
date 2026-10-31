---
title: 最小全域木の辺別制約コスト
documentation_of: //graph/spanning_tree/mst_sensitivity.cpp
date: 2026-10-14
category: グラフ
tags: グラフ
---

## 説明
無向重み付きグラフの各辺について、その辺を必ず採用する場合・使用禁止にする場合の最小全域木コストをまとめて求める。
負重み、同重み、多重辺、自己ループを扱う。

## できること
頂点数を $N$、辺数を $M$ とする。

- `mst_sensitivity(n, edges)`
  `MSTSensitivityResult` を返す。`edges` は Kruskal の `vector<KruskalEdge<long long>>` とする。時間 $O(M\log M+(N+M)\log N)$、入力・出力を含む領域 $O(M+N\log N)$
- `result.exists` / `result.cost`
  元グラフの全域木の存在と最小コスト。非連結なら `false` と `0`
- `result.forced[i]` / `result.forbidden[i]`
  入力順 `i` 番目の辺を必須／禁止にした最小コスト。実現不能なら `nullopt`

## 使い方
`n >= 1`、端点は `0..n-1` とする。返却配列の番号は `edge.idx` に依存しない。
元グラフが非連結なら、両配列は辺数個の `nullopt` となる。
自己ループの `forced` は `nullopt`、`forbidden` は元のコスト。1頂点の空の全域木はコスト0となる。

```cpp
auto result = mst_sensitivity(n, edges);
if (result.forced[i]) {
    bool can_belong_to_mst = *result.forced[i] == result.cost;
}
```

重みの加減算は中間値も含めて `long long` に収まる範囲で使う。
Kruskal 内の逐次加算と、交換式 `cost + added - removed` がこの条件を満たす必要がある。
条件ごとの木の復元は行わない。別途 LCA 構築や build は不要。

## 実装上の補足
Kruskal で木を1つ作り、非木辺の強制採用は木上パスの最大重みの辺との交換で求める。
辺は重み・元の入力順で1回だけソートする。Kruskal で不採用にした非自己ループ辺の ID をその順序で残し、後半でも使う。
ソート用の辺配列は木の構築後に解放し、非木辺の再ソートは行わない。
非木辺を重み順に処理し、パス上のまだ代替辺が決まっていない木辺へ最初の代替重みを設定する。
確定済みの辺は union-by-size と経路圧縮を持つ UnionFind で飛ばし、代表とは別に最上位頂点を保持する。
自己ループを除く非木辺の使用禁止は元のコストで、木辺の禁止はその代替辺との交換となる。

各木辺への代替設定は高々1回で、skip の総処理は $O((N+M)\alpha(N))$。
前処理の走査は反復処理とし、木の深さに依存する再帰は使わない。
