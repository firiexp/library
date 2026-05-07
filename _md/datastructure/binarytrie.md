---
title: Binary Trie
documentation_of: //datastructure/binarytrie.cpp
---
## 説明
非負整数集合に対する binary trie である。
挿入、削除、存在判定、`xor` をかけたあとの最小値取得を $O(X)$ で扱う。
ノードは `vector` でまとめて管理する。

## できること
- `Binarytrie<T, X> trie`
  `X` bit の整数を扱う trie を作る
- `Binarytrie<T, X> trie(v)`
  `vector<T> v` の要素を入れた trie を作る。重複はそのまま個数として入る
- `void reserve(int n)`
  今後 `n` 個挿入する想定でノード領域を先に確保する
- `void add(T x, int k = 1)`
  `x` を `k` 個追加する
- `bool erase(T x, int k = 1)`
  `x` を `k` 個削除する。個数が足りなければ `false`
- `int count(T x)`
  `x` の個数を返す
- `bool contains(T x)`
  `x` が 1 個以上あるかを返す
- `bool empty()`
  空集合かを返す
- `int size()`
  要素数を返す
- `T xor_min(T x)`
  集合内の要素との `xor` の最小値を返す。空集合では使わない
- `T min_element(T x = 0)`
  `a xor x` が最小となる要素 `a` を返す。`x = 0` なら通常の最小値
- `T max_element(T x = 0)`
  `a xor x` が最大となる要素 `a` を返す。`x = 0` なら通常の最大値

## 使い方
集合として使うなら、挿入前に `contains(x)` を見て重複を避ける。

```cpp
vector<unsigned int> init = {1, 4, 7};
Binarytrie<unsigned int, 30> trie(init);
trie.reserve(q);
if (!trie.contains(x)) trie.add(x);
unsigned int ans = trie.min_element(q);
```

## 実装上の補足
`xor_min(x)` は値そのものではなく最小 `xor` 値を返す。
この実装は multiset としても使える。
