---
title: 個数制限付きナップサック
documentation_of: //math/bounded_knapsack.cpp
---

## 説明
重さ・価値・個数制限が指定された品物について、重さごとの最大価値を求める。
品物の種類数を $N$、容量を $W$ として、時間 $O(NW)$、補助領域 $O(W)$。

## できること
- `BoundedKnapsackItem { int weight; long long value, count; }`
  品物1個の重さ・価値と、使える個数を指定する
- `vector<long long> bounded_knapsack(const vector<BoundedKnapsackItem>& items, int capacity)`
  重さが $0,1,\ldots,\mathrm{capacity}$ になる品物の選び方について、最大価値を返す。作れない重さの値は `-INF<ll>`

## 使い方
重さは正、個数と容量は非負とする。価値には負の値も使える。
容量以下の最大価値は、返された配列の最大値で求める。

```cpp
vector<BoundedKnapsackItem> items = { {3, 4, 2}, {1, 2, 1} };
auto dp = bounded_knapsack(items, 7);
long long best = *max_element(dp.begin(), dp.end());
```

テンプレートの `-INF<ll>` は、各段階の到達可能な DP 値より小さく設定する。
個数と価値の積や、単調キュー内で使う `dp[r + j * weight] - j * value` を含め、途中の計算も `long long` に収まる必要がある。

## 実装上の補足
重さの剰余ごとに単調キューで最大値を管理する。
実効個数が少ない品物には二進分割を使い、容量内で個数制限に達しない品物には無制限ナップサックの更新を使う。
単調キューの作業配列は初めて必要になったときに確保し、品物間で再利用する。書き込んだ範囲だけを参照するため、作業配列の初期値は設定しない。
