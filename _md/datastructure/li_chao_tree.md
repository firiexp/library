---
title: Li Chao Tree
documentation_of: //datastructure/li_chao_tree.cpp
date: 2026-03-07
category: データ構造
tags: データ構造
---

## 説明
直線集合に対して、1点での最小値(または最大値)クエリを処理する。
最適な直線の ID も取得できる。同じ評価値なら、先に追加した直線を選ぶ。

登録座標数を $N$、オンライン版の整数区間長を $C$ とする。
直線追加・クエリはオフライン版で $O(\log N)$、オンライン版で $O(\log C)$。
区間直線追加はそれぞれ $O(\log^2 N)$、$O(\log^2 C)$。

## できること
- `LiChaoTree<T, false>(xs)` : オフライン版（`xs` に含まれる座標でのみクエリ可能）
- `OnlineLiChaoTree<T, false>(low, high)` : オンライン版（区間 `[low, high)`）
- `int add_line(a, b)` : 直線 `y = ax + b` を追加し、その ID を返す
- `int add_segment(a, b, l, r)` : 区間 `[l, r)` のみ有効な直線 `y = ax + b` を追加し、その ID を返す
- `query(x)` : 座標 `x` での最小値を返す。有効な直線がない場合は `numeric_limits<T>::max() / 4`、最大値版ではその符号を反転した値を返す
- `optional<pair<T, int>> query_with_id(x)` : 最適な「評価値, ID」を返す。有効な直線がない場合は `nullopt`。同値なら小さい ID を返す

`LiChaoTree<T, true>` / `OnlineLiChaoTree<T, true>` を使うと最大値クエリになる。
ID は両方の追加操作を通して 0 から順に発行する。空区間や登録座標を含まない区間への追加でも ID を発行する。
オフライン版の未登録座標では `query_with_id` は `nullopt`、`query` は空集合の番兵を返す。

## 使い方
追加時に返る ID と遷移元の状態を対応付けると、最適値とともに遷移元を復元できる。

```cpp
LiChaoTree<long long> tree({0, 2, 5});
vector<int> source;
int id = tree.add_line(3, 1);
source.resize(id + 1);
source[id] = 7;
auto result = tree.query_with_id(2);
if (result) {
    auto [value, line_id] = *result;
    int parent = source[line_id];
}
```

## 実装上の補足
直線の評価に必要な乗算・加算と、最大値版の係数・評価値の符号反転は `T` に収まる必要がある。
オンライン版は整数区間を扱い、`low < high`、`high - low` が `T` に収まることを前提とする。クエリは `[low, high)` 内で行う。
有効な直線の評価値には、空集合を表す番兵による上限・下限はない。
各直線に `int` の ID を持つ。`T` のアラインメントにより、ID のサイズ以上に保持領域が増える場合がある。
