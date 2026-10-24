---
title: Functional Graph
documentation_of: //graph/functional_graph.cpp
date: 2026-03-12
category: グラフ
tags: グラフ
---

## 説明
各頂点の出次数が 1 の有向グラフを扱う。
cycle 分解と doubling を前計算し、`k` 個先の頂点、二頂点間の最小遷移回数、同時に進む二頂点の最初の合流時刻、各頂点が属する閉路情報を取る。

## できること
頂点数を $N$ とする。

- `FunctionalGraph fg(n)`
  `n` 頂点の関数グラフを作る。$O(N)$
- `FunctionalGraph fg(to)`
  遷移先配列 `to` から作ってそのまま `build` する。$O(N \log N)$
- `void set_edge(int v, int nxt)`
  `v -> nxt` を設定する。$O(1)$
- `void build()`
  閉路分解と doubling を前計算する。時間・領域 $O(N \log N)$
- `int jump(int v, long long k)`
  `v` から `k` 回遷移した先を返す。$0 \le k \le 2^{63}-1$。最悪 $O(\log N)$
- `int distance(int s, int t) const`
  `s` から `t` への最小遷移回数を返す。到達不能なら `-1`。$O(\log N)$、`t` が閉路上なら $O(1)$。追加領域 $O(1)$
- `int meeting_time(int u, int v) const`
  `u, v` から同時に1辺ずつ進み、初めて同じ頂点に到達する時刻を返す。合流しなければ `-1`。$O(\log N)$ 時間・追加領域 $O(1)$
- `bool in_cycle(int v)`
  `v` が閉路上なら `true`。$O(1)$
- `int cycle_id(int v)`
  `v` が属する連結成分の閉路 id を返す。$O(1)$
- `int cycle_size(int v)`
  `v` が流れ込む閉路の長さを返す。$O(1)$
- `int steps_to_cycle(int v)`
  `v` から閉路に入るまでの遷移回数を返す。$O(1)$
- `int cycle_vertex(int v)`
  `v` から進んで最初に到達する閉路頂点を返す。$O(1)$
- `int cycle_index(int v)`
  `cycle_vertex(v)` の閉路内 index を返す。$O(1)$
- `const vector<int> &cycle(int id)`
  閉路 `id` の頂点列を返す。辺の向き順に並ぶ。$O(1)$

## 使い方
各頂点の遷移先を `set_edge` で入れてから `build()` を呼ぶ。
辺を変更した後は再び `build()` を呼ぶ。
`jump(v, k)` で `k` 個先を求め、`steps_to_cycle(v)` や `cycle_size(v)` で構造情報を使う。
`distance(s, t)` と `meeting_time(u, v)` は同じ `build()` の結果で使え、追加の前処理は不要。

```cpp
FunctionalGraph fg(n);
for (int v = 0; v < n; ++v) {
    fg.set_edge(v, to[v]);
}
fg.build();

int x = fg.jump(v, k);
int len = fg.cycle_size(v);
int t = fg.meeting_time(u, v);
if (t != -1) {
    int meeting_vertex = fg.jump(u, t);
}
```

## 実装上の補足
- 閉路までの距離の最大値を $D$ とする。`up` は閉路到達前の遷移だけに使う。段数は $D=0$ なら1、$D>0$ なら $\lfloor\log_2 D\rfloor+1$。各段は `N` 要素で、再 `build` 時に最大距離に合わせて作り直す
- `cycle(id)` の先頭は実装依存だが、並び順は常に遷移先方向にそろう
- `cycle_index(v)` は非閉路頂点でも使え、`cycle_vertex(v)` の位置を返す
- `meeting_time` は成分、閉路上の位相、閉路までの距離を比較する。別成分・位相不一致・距離不一致なら $O(1)$、同じ深さの流入木では doubling を1回降りる。合流時刻は存在すれば $N-1$ 以下
