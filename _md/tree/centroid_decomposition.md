---
title: 重心分解(Centroid Decomposition)
documentation_of: //tree/centroid_decomposition.cpp
---
## 説明
木を重心分解し、重心木を構築する。
各部分木を重心で再帰的に分割し、`out` に重心木の子を持つ。

## できること
- `CentroidDecomposition cd(n)`
  頂点数 `n` の木を作る
- `void add_edge(int u, int v)`
  木辺を張る
- `int get(int root)`
  `root` を含む連結成分を重心分解し、重心木の根を返す

## 使い方
木を張ったあと `get(0)` のように呼ぶと、`out` に重心木が構築される。

```cpp
CentroidDecomposition cd(n);
cd.add_edge(u, v);
int root = cd.get(0);
for (int to : cd.out[root]) {
    // 重心木の子
}
```

## 実装上の補足
`out` は有向木として張られ、親から子への辺だけを持つ。
`get` は内部で訪問印 `v` を使うが、処理後には元に戻す。
