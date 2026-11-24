---
title: Cartesian Tree
documentation_of: //tree/cartesian_tree.cpp
---

## 説明
配列から最小 Cartesian tree を構築する。各区間で最小値をとる最も左の添字を根にする。
中順走査で頂点をたどると、元の配列の添字順になる。

## できること
配列の長さを $N$ とする。

- `CartesianTree cartesian_tree(const vector<T>& a)`
  配列 `a` から最小 Cartesian tree を構築して返す。$O(N)$
- `CartesianTree::root`
  根の添字（`int`）。空配列なら `-1`。
- `CartesianTree::parent`、`CartesianTree::left`、`CartesianTree::right`
  長さ $N$ の `vector<int>`。各頂点 `v` の親・左の子・右の子の添字を表し、根の親と存在しない子は `-1`。

## 使い方
`<` で比較できる要素型の `vector<T>` を `cartesian_tree(a)` に渡し、返り値の `root`・`parent`・`left`・`right` を参照する。

```cpp
vector<int> a = {3, 1, 4, 1, 5};
auto tree = cartesian_tree(a);
int root = tree.root;          // 1
int left = tree.left[root];    // 0
int right = tree.right[root];  // 3
int parent = tree.parent[2];   // 3
```

## 実装上の補足
頂点 `i` の挿入位置を `i - 1` から `parent` をたどって探すため、補助スタックを使わずに構築する。
