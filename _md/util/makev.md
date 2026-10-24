---
title: make_v, chmin, chmax
documentation_of: //util/makev.cpp
---
## 説明
各次元の長さと初期値を指定して、多次元 `vector` を作る。
最小値・最大値への更新も扱う。

## できること
- `make_v(n, m, ..., init)`
  指定した各次元長の `vector` を作り、各要素を `init` で初期化する。次元数を定数として $O(nm\cdots)$
- `void chmin(T& x, const T& y)`
  `x` を `min(x, y)` で更新する。$O(1)$
- `void chmax(T& x, const T& y)`
  `x` を `max(x, y)` で更新する。$O(1)$

## 使い方
要素型は初期値の型になる。

```cpp
auto dp = make_v(3, 4, 1000000000LL);
chmin(dp[0][0], 0LL);
```

この例では `vector<vector<long long>>` 型の3行4列の配列を作る。
