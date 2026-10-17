---
title: 容量スケーリングDinic(Capacity Scaling Dinic)
documentation_of: //flow/costscalingdinic.cpp
---
## 説明
capacity scaling を入れた Dinic 法による最大流である。
大きい容量から順に流すことで、容量が大きいケースで定数倍を改善する。
辺 ID と登録時の容量の保持を含め、領域は $O(V+E)$。

## できること
- `CostScalingDinic<T, directed> mf(n)`
  頂点数 `n` のフローグラフを作る
- `int add_edge(int from, int to, T cap)`
  容量 `cap` の辺を追加し、0からの追加順の ID を返す。`directed=false` なら無向辺。償却 $O(1)$
- `T flow(int s, int t, T lim = INF<T>)`
  現在の残余グラフで `s` から `t` へ最大 `lim` だけ流し、今回追加した流量を返す
- `Edge get_edge(int id) const`
  `from, to, capacity, flow` を返す。`capacity` は登録時の容量、`flow` は登録方向への正味流量。$O(1)$
- `vector<Edge> edges() const`
  追加順で全辺の情報を返す。逆辺は含めない。時間・返却領域 $O(E)$
- `vector<char> min_cut(int s) const`
  現在の残余グラフで `s` から到達できる頂点を `true` で返す。時間 $O(V+E)$、追加領域 $O(V)$

## 使い方
容量型 `T` と有向・無向の別をテンプレート引数で与える。

```cpp
CostScalingDinic<long long, true> mf(n);
int id = mf.add_edge(u, v, c);
long long ans = mf.flow(s, t);
auto e = mf.get_edge(id);
auto source_side = mf.min_cut(s);
```

## 実装上の補足
容量は非負整数で、流量と計算中の残余容量は `T` に収まる必要がある。
無向版の `T` は符号付き整数型を使う。流量は `-capacity` から `capacity` の範囲を取り、残余容量は元容量の2倍になる場合がある。
辺情報の取得は、対象辺の登録容量と残余容量の対応が保たれていることを前提とする。
`min_cut(s)` は終点が到達不能になったとき最小カットの始点側を表す。流量上限による途中停止では、最小カットとは限らない。
`s != t`、`lim >= 0` とする。再実行では前回の残余グラフを引き継ぐ。
`flow` の開始時に全残余辺を $O(V+E)$ 時間で走査し、最大残余容量と `lim` の小さい方以下の最大2冪から scaling を始める。
正の残余容量がない場合は `0` を返す。容量が小さい入力では、使える辺がない高位の幅での BFS を省ける。
BFS は終点の距離が決まった時点で終了する。同じ最短距離の増加路に必要な層は保持する。
