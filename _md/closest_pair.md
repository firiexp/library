---
title: Closest Pair
documentation_of: //geometry/closest_pair.cpp
---
## 説明
平面上の整数点集合から、距離が最小の 2 点の元の添字を返す。
分割統治で解き、計算量は `O(N log N)`。

## できること
- `pair<int, int> closest_pair(const vector<pair<long long, long long>>& points)`
  最短距離を持つ 2 点の添字を返す。`points.size() < 2` は想定しない

## 使い方
入力順を保ったまま点列を渡すと、返り値はその元の添字になる。
同じ座標の点が複数あってもよい。

## 実装上の補足
- 距離比較は二乗距離で行うので平方根は使わない
- 差の二乗が 64 bit を超える可能性があるため、内部計算は `__int128_t` を使う
- 複数の最短対があるとき、どれを返すかは規定しない
