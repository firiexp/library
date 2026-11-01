---
layout: page
title: 永続セグメント木のCursorによる区間内順位検索
---

# 永続セグメント木のCursorによる区間内順位検索

## 説明
[永続セグメント木](../datastructure/segmenttree/persistent_segtree.cpp.html)の Cursor を使い、配列の区間内で小さい方から指定した順位の値を求める。
Cursor は各バージョンのセグメント木のノードとその区間を表す。
2つのバージョンを同じ方向へたどり、出現回数の差を使って探索する。

## 使い方
配列 `{3, 1, 4, 1, 2}` の区間 `[1, 5)` に含まれる値のうち、3番目に小さい値を求める。
対象の値を並べると `{1, 1, 2, 4}` なので、答えは `2` となる。同じ値も出現回数だけ数える。

元の配列の値 `x` をセグメント木の添字として使い、その位置に `x` の出現回数を保存する。
この例の値は0以上5未満なので、長さ5のセグメント木を作る。`Monoid` には整数の加算を定義する。
`version[i]` は元の配列の先頭 `i` 要素を数えたバージョンである。
`version[r]` と `version[l]` の頻度の差を取ると、元の配列の区間 `[l, r)` の各値の出現回数になる。

2つの Cursor を同じ方向へたどり、小さい値側の個数を比べて次に進む子を選ぶ。
順位 `k` は0始まりとし、`0 <= k < r - l` を満たす値を指定する。

```cpp
struct Monoid {
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

vector<int> values = {3, 1, 4, 1, 2};
PersistentSegmentTree<Monoid> freq(5);
vector<int> version{0};
for (int x : values) version.push_back(freq.add(x, 1));

int l = 1, r = 5, k = 2;
auto left = freq.root_cursor(version[l]);
auto right = freq.root_cursor(version[r]);
while (!left.is_leaf()) {
    auto x = freq.split(left), y = freq.split(right);
    long long low_count = y.low.fold() - x.low.fold();
    if (k < low_count) {
        left = x.low;
        right = y.low;
    } else {
        k -= low_count;
        left = x.high;
        right = y.high;
    }
}
int value = left.index();
```

`value` に答えの `2` が入る。各段で候補の値の範囲が半分になるため、セグメント木の長さを $N$ とすると探索は $O(\log N)$ 時間となる。
