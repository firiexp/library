---
title: 多次元配列(NdVec)
documentation_of: //util/ndvec.cpp
date: 2026-04-11
category: ユーティリティ
tags: ユーティリティ
---

## 説明
多次元配列を 1 次元 `vector` に載せて管理する。
各要素アクセスは $O(N)$。

## できること
- `NdVec<T, N> a`
  空の `NdVec` を作る
- `NdVec<T, N> a(dim, init)`
  各次元長 `dim` の配列を作り、全要素を `init` で初期化する
- `long long a.size()`
  確保した総要素数を返す
- `long long a.index(i0, i1, ..., i{N-1})`
  多次元添字に対応する 1 次元 index を返す
- `a(i0, i1, ..., i{N-1})`
  その位置の要素を参照する
- `a.fill(x)`
  全要素を `x` にする

## 使い方
`dim[k]` を第 `k` 次元の長さとして `NdVec<T, N> a(dim, init);` を作る。
添字は `a(i, j, k)` のように関数呼び出し形式で渡す。

```cpp
NdVec<long long, 3> dp({n, m, k}, -1);
dp(0, 0, 0) = 0;
dp.fill(0);
```

内部では右端の次元を最下位として持つ。
つまり `dim = {a, b, c}` のとき、`index(i, j, k) = (i b + j) c + k` になる。
