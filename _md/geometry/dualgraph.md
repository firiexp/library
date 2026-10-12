---
title: 双対グラフ(Dual Graph)
documentation_of: //geometry/dualgraph.cpp
---
## 説明
与えられた連結な平面グラフ(頂点が座標で表される)の双対グラフを構築する。

## できること
- `DualGraph dual(points)`
  座標列から頂点を作る
- `void add_point(Point p)` / `void add_edge(int u, int v)`
  頂点 / 無向辺を追加する
- `void build()`
  面境界を `A`、双対隣接リストを `G` に構築する。再実行できる。橋の両側は同じ面になる

## 実装上の補足
頂点数を $V$、辺数を $E$、各頂点の次数を $d_v$、最大次数を $\Delta$ とする。
構築時間は $O(V+E+\sum_v d_v \log d_v)$。
次数16以上の頂点では半辺ごとに偏角を1回だけ計算し、ソートで再利用する。偏角計算の総回数は $O(E)$。
角度の作業配列は必要なときだけ確保し、頂点間で再利用する。従来の $O(V+E)$ の領域に加え、作業配列は $O(\Delta)$。
