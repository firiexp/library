---
title: 偏角ソート(Argument Sort)
documentation_of: //geometry/argsort.cpp
date: 2026-03-08
category: 幾何
tags: 幾何
---

## 説明
整数ベクトルを偏角 $(-\pi, \pi]$ の昇順に並べる。
下半平面、正の $x$ 軸、上半平面、負の $x$ 軸の順に反時計回りとなる。
原点は偏角 $0$ として正の $x$ 軸と同じ方向に扱う。

## できること
点数を $N$ とする。

- `void argsort(vector<array<int, 2>>& v)`
  `v` を偏角順にその場で並べ替える。同方向の順序は未指定。$O(N\log N)$
- `void argsort(vector<IntPoint>& v)`
  整数座標点をその場で並べ替える。同方向の順序は未指定。$O(N\log N)$
- `vector<int> arg_sort_indices(const vector<IntPoint>& v)`
  偏角順に元の添字を返す。同方向は元の添字の昇順。時間 $O(N\log N)$、追加領域 $O(N)$

## 使い方
`IntPoint` はこのファイルから読み込まれる。
点に重みなどが対応している場合は、返された添字で元の配列を参照する。

```cpp
vector<IntPoint> points{ {4000000000LL, 0}, {0, -5000000000LL}, {0, 0} };
auto order = arg_sort_indices(points);
for (int i : order) use(points[i], weight[i]);
```

この例の `order` は `{1, 0, 2}` となる。

## 実装上の補足
半平面と整数の積で比較し、浮動小数点数は使わない。
`array<int, 2>` 版の積は `long long`、`IntPoint` 版は乗算前に `__int128` へ変換する。
積同士を比較し、外積の差を作らないので、それぞれ `int` / `long long` の座標全域を扱える。
