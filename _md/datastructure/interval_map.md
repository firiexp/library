---
title: Interval Map
documentation_of: //datastructure/interval_map.cpp
category: データ構造
tags: データ構造
---

## 説明
半開区間 `[0,n)` の値を、同じ値が続く区間に分けて管理する。
区間代入の前に、変更される各区間と旧値を引数として関数を呼べる。色別の個数などの更新に使う。

## できること
長さを $N=n$、保持区間数を $K$、代入範囲と交わる変更前の区間数を $C$ とする。
値のコピー・比較は定数時間とする。

- `IntervalMap<T>(ll n, const T &value)`
  `[0,n)` を `value` で初期化する。$n\ge 0$ とする。時間・領域 $O(1)$。
- `T get(ll position) const`
  `position` の値を返す。$O(\log K)$。
- `assign(ll l, ll r, T value, f)`
  `[l,r)` を `value` にする。代入前に、各区間と `[l,r)` の共通部分について、左から順に `f(ll begin, ll end, const T &old_value)` を呼ぶ。
  関数 `f` の1回の計算量を $f(N)$ として、$O(\log K+C f(N))$。
- `assign(ll l, ll r, T value)`
  `[l,r)` を `value` にする。$O(\log K+C)$。

## 使い方
`0 <= position < n`、`0 <= l <= r <= n` とする。空区間への代入は何もしない。
同じ値を代入する場合も関数 `f` を呼ぶ。`f` に渡す区間は `[l,r)` を重複なく覆う。
代入後は隣接する同値区間を統合する。`T` にはコピーと `==` が必要。

```cpp
IntervalMap<int> colors(n, 0);
vector<ll> count(color_count);
count[0] = n;
colors.assign(l, r, color, [&](ll begin, ll end, int old_color) {
    count[old_color] -= end - begin;
});
count[color] += r - l;
```

関数 `f` の中から同じ IntervalMap を変更しない。旧値への参照は `f` の実行中だけ使う。

## 実装上の補足
区間の左端を `map` で管理し、代入の両端で分割してから対象区間を削除する。
定数初期化後の $Q$ 回の区間代入で作る境界は $O(Q)$ 個なので、関数 `f` を呼ぶ回数と削除する区間数の総和も $O(Q)$。
区間代入列の総時間は $O(Q\log Q+Qf(N))$、保持領域は $O(K)$ となる。
