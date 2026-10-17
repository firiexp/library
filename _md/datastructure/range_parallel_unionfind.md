---
title: Range Parallel UnionFind
documentation_of: //datastructure/range_parallel_unionfind.cpp
---

## 説明
長さ $k$ の2区間について、対応する頂点 $(a+i,b+i)$ をまとめて同じ集合にする。
階層ごとに併合済みの区間を記録し、同じ対応を繰り返し処理する手間を省く。

## できること
- `RangeParallelUnionFind uf(n)`
  頂点 $0,1,\ldots,n-1$ を、それぞれ独立した集合として構築する
- `int unite_range(int a, int b, int k)`
  $0\leq i<k$ のすべての頂点対 $(a+i,b+i)$ を併合し、新たに成立した成分の併合数を返す
- `int unite_range(int a, int b, int k, F on_merge)`
  異なる頂点成分を併合する直前に `on_merge(keep, absorbed)` を呼ぶ。引数は併合前の代表元で、`keep` が併合後の代表元になる
- `int root(int v)` / `bool same(int a, int b)`
  代表元の取得と、同じ集合に属するかの判定を行う
- `int size(int v)` / `int count() const`
  頂点 `v` の成分の頂点数と、全体の成分数を返す

## 使い方
$0\leq k\leq n$、$0\leq a,b\leq n-k$ とする。区間が重なっていてもよい。
callback で成分ごとの値を更新できる。callback 内では、この UnionFind の新たな併合は行わない。

```cpp
RangeParallelUnionFind uf(n);
vector<long long> component_sum = weights;
uf.unite_range(a, b, k, [&](int keep, int absorbed) {
    component_sum[keep] += component_sum[absorbed];
});
```

## 実装上の補足
構築と保持領域は $O(N\log(N))$。$Q$ 回の区間併合の合計は償却 $O((N\log(N)+Q)\alpha(N))$ 時間で、callback の実行時間は別途加わる。
callback の呼出総数は高々 $\max(0,N-1)$ 回。1回の区間併合が常に対数時間で終わるという保証ではない。
`root`・`same`・`size` は償却 $O(\alpha(N))$、`count` は $O(1)$ 時間。
