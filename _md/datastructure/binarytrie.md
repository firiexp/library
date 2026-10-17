---
title: Binary Trie
documentation_of: //datastructure/binarytrie.cpp
---
## 説明
非負整数集合に対する binary trie である。
挿入、削除、存在判定、`xor` をかけたあとの最小値・順位取得を $O(X)$ で扱う。
ノードは `vector` でまとめて管理する。

## できること
- `Binarytrie<T, X> trie`
  `X` bit の整数を扱う trie を作る
- `Binarytrie<T, X> trie(v)`
  `vector<T> v` の要素を入れた trie を作る。重複はそのまま個数として入る
- `void reserve(int n)`
  今後 `n` 個挿入する想定でノード領域を先に確保する
- `void add(T x, int k = 1)`
  `x` を `k` 個追加する。`k >= 0` を前提とし、`k = 0` は何もしない
- `bool erase(T x, int k = 1)`
  `x` を `k` 個削除する。個数が足りなければ `false`。`k >= 0` を前提とし、`k = 0` は何もせず `true`
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
- `T kth_element(int k, T xor_mask = 0) const`
  `a xor xor_mask` が小さい順で `k` 番目の元要素 `a` を返す。重複も数え、`0 <= k < size()` を前提とする
- `int count_less(T bound, T xor_mask = 0) const`
  `a xor xor_mask < bound` を満たす要素数を返す。時間 $O(X)$、追加領域 $O(1)$

## 使い方
値・xor の引数・`bound` は非負の `X` bit 整数とする。
集合として使うなら、挿入前に `contains(x)` を見て重複を避ける。

```cpp
vector<unsigned int> init = {1, 4, 7};
Binarytrie<unsigned int, 30> trie(init);
trie.reserve(q);
if (!trie.contains(x)) trie.add(x);
unsigned int ans = trie.min_element(q);
```

`{1, 4, 4, 7}` を入れた trie では、`kth_element(1, 3)` は `7`、`count_less(5, 3)` は `2` を返す。
`kth_element(0, mask)` は `min_element(mask)`、`kth_element(size() - 1, mask)` は `max_element(mask)` に一致する。

## 実装上の補足
`xor_min(x)` は値そのものではなく最小 `xor` 値を返す。
この実装は multiset としても使える。

削除で空になった枝は回収し、次の挿入で再利用する。
同時に保持した相異なる値の最大数を $D_{\max}$ とすると、`nodes.size()` は $O(1 + X D_{\max})$。
`reserve(n)` と vector コンストラクタの先行確保、過去の vector capacity はこのノード数の上限とは別であり、削除時には縮小しない。
公開 `nodes` の添字は再利用されるため、要素に対応する恒久的な識別子として保存しない。
