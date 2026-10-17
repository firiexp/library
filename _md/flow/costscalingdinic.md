---
title: 容量スケーリングDinic(Capacity Scaling Dinic)
documentation_of: //flow/costscalingdinic.cpp
---
## 説明
capacity scaling を入れた Dinic 法による最大流である。
大きい容量から順に流すことで、容量が大きいケースで定数倍を改善する。

## できること
- `CostScalingDinic<T, directed> mf(n)`
  頂点数 `n` のフローグラフを作る
- `void add_edge(int from, int to, T cap)`
  容量 `cap` の辺を張る。`directed=false` なら無向辺
- `T flow(int s, int t, T lim = INF<T>)`
  現在の残余グラフで `s` から `t` へ最大 `lim` だけ流し、今回追加した流量を返す。`lim=0` なら何もしない

## 使い方
容量型 `T` と有向・無向の別をテンプレート引数で与える。

```cpp
CostScalingDinic<long long, true> mf(n);
mf.add_edge(u, v, c);
long long ans = mf.flow(s, t);
```

## 実装上の補足
辺容量 0 は追加しない。
容量は非負で、計算中の残余容量も `T` に収まる必要がある。
無向辺の逆向き残余容量は、元容量の 2 倍になる場合がある。
`s != t`、`lim >= 0` とする。再実行では前回の残余グラフを引き継ぐ。
`flow` の開始時に全残余辺を $O(V+E)$ 時間で走査し、最大残余容量と `lim` の小さい方以下の最大2冪から scaling を始める。
正の残余容量がない場合は `0` を返す。容量が小さい入力では、使える辺がない高位の幅での BFS を省ける。
BFS は終点の距離が決まった時点で終了する。同じ最短距離の増加路に必要な層は保持する。
