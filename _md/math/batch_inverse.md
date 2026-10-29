---
title: 配列内の全ての要素の逆元
documentation_of: //math/batch_inverse.cpp
date: 2026-10-30
category: 数学
tags: 数学
---

## 説明
modint の配列について、全要素の逆元をまとめて求める。
逆元の計算を1回にまとめ、残りを乗算で求める。

## できること
- `vector<modint<p>> batch_inverse(const vector<modint<p>>& a)`
  `a[i].inv()` を入力と同じ順序で返す。長さを $N$、法を $p$ として時間 $O(N+\log p)$、出力を含む領域 $O(N)$

## 使い方
素数を法とする `modint<p>` の配列を渡す。
全要素が非零であることを前提とする。0を含む場合は assert で検出する。

```cpp
vector<modint<17>> a = {2, 3, 4};
auto inverse = batch_inverse(a);
```

返り値は `{9, 6, 13}`。各要素について `a[i] * inverse[i] == 1` となる。

## 実装上の補足
各位置より前の累積積を出力用の配列に保持する。
全積の逆元を1回だけ求め、後ろから走査して各要素の逆元に置き換える。
