---
title: 関数グラフ(Functional Graph)
documentation_of: //graph/functional_graph.cpp
date: 2026-03-12
category: グラフ
tags: グラフ
---

## 説明
各頂点の出次数が 1 の有向グラフを扱う。
cycle 分解と doubling を前計算し、`k` 個先の頂点と各頂点が属する閉路情報を取る。
前処理 $O(N \log K)$、`jump` は $O(\log K)$、それ以外は $O(1)$。

## できること
- `FunctionalGraph fg(n)`
  `n` 頂点の関数グラフを作る
- `FunctionalGraph fg(to)`
  遷移先配列 `to` から作ってそのまま `build` する
- `void set_edge(int v, int nxt)`
  `v -> nxt` を設定する
- `void build()`
  閉路分解と doubling を前計算する
- `int jump(int v, long long k)`
  `v` から `k` 回遷移した先を返す
- `bool in_cycle(int v)`
  `v` が閉路上なら `true`
- `int cycle_id(int v)`
  `v` が属する連結成分の閉路 id を返す
- `int cycle_size(int v)`
  `v` が流れ込む閉路の長さを返す
- `int steps_to_cycle(int v)`
  `v` から閉路に入るまでの遷移回数を返す
- `int cycle_vertex(int v)`
  `v` から進んで最初に到達する閉路頂点を返す
- `int cycle_index(int v)`
  `cycle_vertex(v)` の閉路内 index を返す
- `const vector<int> &cycle(int id)`
  閉路 `id` の頂点列を返す。辺の向き順に並ぶ

## 使い方
各頂点の遷移先を `set_edge` で入れてから `build()` を呼ぶ。
`jump(v, k)` で `k` 個先を求め、`steps_to_cycle(v)` や `cycle_size(v)` で構造情報を使う。

```cpp
FunctionalGraph fg(n);
for (int v = 0; v < n; ++v) {
    fg.set_edge(v, to[v]);
}
fg.build();

int x = fg.jump(v, k);
int len = fg.cycle_size(v);
```

## 実装上の補足
- `cycle(id)` の先頭は実装依存だが、並び順は常に遷移先方向にそろう
- `cycle_index(v)` は非閉路頂点でも使え、`cycle_vertex(v)` の位置を返す
