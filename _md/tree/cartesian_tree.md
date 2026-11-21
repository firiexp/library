---
title: Cartesian Tree
documentation_of: //tree/cartesian_tree.cpp
---

## 説明
配列から最小 Cartesian tree を構築する。各区間で最小値をとる最も左の添字を根にする。
中順走査で頂点をたどると、元の配列の添字順になる。

## できること
- `CartesianTree cartesian_tree(const vector<T>& a)`
  長さ $N$ の配列から $O(N)$ 時間で木を作る。返り値に $O(N)$、そのほかに $O(1)$ の領域を使う。

`root` は根の添字で、空配列なら `-1`、1要素なら `0`。
`parent[v]`、`left[v]`、`right[v]` は頂点 `v` の親、左の子、右の子の添字を表す。各配列の長さは $N$ で、根の親と存在しない子は `-1` になる。

## 使い方
```cpp
vector<int> a = {3, 1, 4, 1, 5};
auto tree = cartesian_tree(a);
int root = tree.root;          // 1
int left = tree.left[root];    // 0
int right = tree.right[root];  // 3
int parent = tree.parent[2];   // 3
```
