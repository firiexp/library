---
title: 木の同型判定と頂点対応
documentation_of: //tree/tree_isomorphism.cpp
date: 2026-10-18
category: 木
tags: 木
---

## 説明
2本の木が同型かを判定し、同型なら頂点の対応を返す。
子部分木の同型類を共有辞書で分類するため、ハッシュ衝突による誤判定はない。
同じ頂点数 $N$ の木に対し、時間 $O(N\log N)$、追加領域 $O(N)$。

## できること
- `TreeIsomorphismResult tree_isomorphism(g, h)`
  根を指定せずに同型性を判定する
- `TreeIsomorphismResult rooted_tree_isomorphism(g, h, root_g, root_h)`
  指定した根同士を対応させる同型写像を求める
- `result.exists`
  同型なら `true`。頂点数が異なる場合や非同型なら `false`
- `result.mapping[v]`
  1本目の頂点 `v` に対応する2本目の頂点番号。失敗時は配列全体が空

## 使い方
単純な無向木の隣接リストを `vector<vector<int>>` で渡す。入力は変更しない。
非空の木では根を有効な頂点番号で指定する。空の木同士は根の指定を使わず、`exists = true` と空の対応を返す。

```cpp
auto result = tree_isomorphism(g, h);
if (result.exists) {
    int matched_vertex = result.mapping[v];
}
```

対応は全単射で、すべての辺を保つ。複数の対応がある場合はそのうち1つを返し、辞書順最小性は保証しない。
頂点・辺のラベルは扱わない。

## 実装上の補足
2本で共有した辞書に、ソート済みの子の同型類を登録する。
根の同型類が一致したら、同じ同型類の子同士を対応させる。
根なし版は `tree_center` で中心を求め、1本目の中心を1つ固定して2本目の中心を高々2通り試す。
構築・復元ともに再帰を使わない。既存の `TreeHash` の id は別々の `build` 間で比較できないため、2本の比較にはこの関数を使う。
