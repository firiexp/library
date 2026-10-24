---
title: Dinic法(Dinic)
documentation_of: //flow/dinic.cpp
date: 2019-07-31
category: フロー
tags: 最大流
---

## 説明
Dinic による最大流。

## できること
頂点数を $V$、追加した辺数を $E$ とする。 保持領域は $O(V+E)$。

- `Dinic<T, directed> mf(n)` : 頂点数 `n` のグラフを作る。`directed=false` なら無向辺を扱う。$O(V)$
- `int add_edge(int from, int to, T cap)` : 容量 `cap` の辺を追加し、0からの追加順の ID を返す。償却 $O(1)$
- `T flow(int s, int t, T lim = INF<T>)` : 現在の残余グラフで最大 `lim` だけ流し、今回追加した流量を返す。$O(EV^2)$
- `Edge get_edge(int id) const` : `from, to, capacity, flow` を返す。`capacity` は登録時の容量、`flow` は登録方向への正味流量。$O(1)$
- `vector<Edge> edges() const` : 追加順で全辺の情報を返す。逆辺は含めない。時間・返却領域 $O(E)$
- `vector<char> min_cut(int s) const` : 現在の残余グラフで `s` から到達できる頂点を `true` で返す。時間 $O(V+E)$、追加領域 $O(V)$

## 使い方
```cpp
Dinic<long long, true> mf(n);
int id = mf.add_edge(u, v, capacity);
long long value = mf.flow(s, t);
auto e = mf.get_edge(id);
auto source_side = mf.min_cut(s);
```

## 実装上の補足
`G` を直接書き換えた場合、`get_edge` と `edges` の返却値は保証しない。
`s != t`、`cap >= 0`、`lim >= 0` とし、流量と計算中の残余容量は `T` に収める。
無向版の `T` は符号付き型を使う。流量は `-capacity` から `capacity` の範囲を取り、残余容量は元容量の2倍になる場合がある。
`min_cut(s)` は終点が到達不能になったとき最小カットの始点側を表す。流量上限による途中停止では、最小カットとは限らない。
BFS は終点の距離が決まった時点で終了する。この時点で終点の1つ前までの層はすべて距離が決まっており、同じ最短距離の増加路を続けて探せる。
流量上限 `lim` を使い切った場合は、次の BFS を行わずに終了する。再実行では前回の残余グラフを引き継ぐ。
