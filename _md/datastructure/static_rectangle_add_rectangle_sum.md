---
title: 静的な長方形加算・長方形和
documentation_of: //datastructure/static_rectangle_add_rectangle_sum.cpp
---

## 説明
長方形ごとの重みを加算した後、指定した長方形内の総和をまとめて求める。
各更新の重みに、問い合わせの長方形との共通部分の面積を掛けて足し合わせる。
整数座標では単位セルごとの重みの和と一致する。

## できること
- `StaticRectangleAddRectangleSum<T> solver`
  重みと結果の型を `T` とする計算器を作る
- `void add_rectangle(int l, int d, int r, int u, T w)`
  半開長方形 $[l,r)\times[d,u)$ に重み `w` を加える
- `void add_query(int l, int d, int r, int u)`
  半開長方形 $[l,r)\times[d,u)$ の総和を問い合わせる
- `vector<T> solve() const`
  登録されたすべての更新を反映し、問い合わせの登録順に答えを返す。更新数 $N$、問い合わせ数 $Q$ として時間 $O((N+Q)\log(N+Q+1))$、補助領域 $O(N+Q)$

## 使い方
`l <= r`、`d <= u` とする。座標と重みは負でもよい。
更新と問い合わせを登録してから `solve()` を呼ぶ。面積が $0$ の更新は影響せず、面積が $0$ の問い合わせの答えは `0` になる。

```cpp
StaticRectangleAddRectangleSum<long long> solver;
solver.add_rectangle(0, 0, 2, 3, 5);
solver.add_query(0, 0, 2, 3);
solver.add_query(1, 1, 3, 4);
auto ans = solver.solve();
```

この例の答えは `30, 10` となる。
`T` には `long long`、`__int128`、`modint` などを使える。座標の積と重みの積や総和を含め、途中の計算も表現できる型を選ぶ。

## 実装上の補足
更新の4隅を符号付きの点に分解し、$x$ 座標の順に走査する。
各点 $(a,b,w)$ の係数 $(w,wa,wb,wab)$ を BIT にまとめて持ち、長方形の総和を求める。
