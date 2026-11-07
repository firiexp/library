---
title: Interval Map
documentation_of: //datastructure/interval_map.cpp
category: データ構造
tags: データ構造
---

## 説明
半開区間 `[0,n)` の値を、同じ値が続く区間に分けて管理する。
区間代入の前に、変更される各区間と旧値を引数として関数を呼べる。色別の個数などの更新に使う。
値を変更せず、指定範囲の区間を列挙することもできる。

## できること
長さを $N=n$、保持区間数を $K$、指定範囲と交わる区間数を $C$ とする。
値のコピー・比較は定数時間とする。

- `IntervalMap<T>(ll n, const T &value)`
  `[0,n)` を `value` で初期化する。$n\ge 0$ とする。時間・領域 $O(1)$。
- `IntervalMap<T>(const vector<T> &values)`
  配列から構築し、隣接する同値要素をまとめる。空配列なら $n=0$。時間 $O(N)$、保持領域 $O(K)$。
- `T get(ll position) const`
  `position` の値を返す。$O(\log K)$。
- `for_each_interval(ll l, ll r, f) const`
  各保持区間と `[l,r)` の共通部分について、左から順に `f(ll begin, ll end, const T &value)` を呼ぶ。
  値や区間境界を変更しない。関数 `f` の実行を除き $O(\log K+C)$ 時間、追加領域 $O(1)$。
- `assign(ll l, ll r, T value, f)`
  `[l,r)` を `value` にする。代入前に、各区間と `[l,r)` の共通部分について、左から順に `f(ll begin, ll end, const T &old_value)` を呼ぶ。
  関数 `f` の1回の計算量を $f(N)$ として、$O(\log K+C f(N))$。
- `assign(ll l, ll r, T value)`
  `[l,r)` を `value` にする。$O(\log K+C)$。

## 使い方
`0 <= position < n`、`0 <= l <= r <= n` とする。空区間の代入・列挙は何もしない。
同じ値を代入する場合も関数 `f` を呼ぶ。`f` に渡す区間は `[l,r)` を重複なく覆う。
構築・代入後は隣接する同値区間を統合する。`T` にはコピーと `==` が必要で、デフォルトコンストラクタは不要。
配列構築では値をコピーして保持するため、構築元の配列を変更・破棄しても影響しない。

```cpp
IntervalMap<int> colors(n, 0);
vector<ll> count(color_count);
count[0] = n;
colors.assign(l, r, color, [&](ll begin, ll end, int old_color) {
    count[old_color] -= end - begin;
});
count[color] += r - l;
```

全区間の列挙には `for_each_interval(0, n, f)` を使う。
代入・列挙の関数 `f` の中から同じ IntervalMap を変更しない。渡された値への参照は `f` の実行中だけ使う。

## 実装上の補足
配列構築では隣接要素を1回ずつ比較し、各区間の左端を `map` の末尾へ hint 付きで挿入する。
区間の左端を `map` で管理し、代入の両端で分割してから対象区間を削除する。
定数初期化後の $Q$ 回の区間代入で作る境界は $O(Q)$ 個なので、関数 `f` を呼ぶ回数と削除する区間数の総和も $O(Q)$。
区間代入列の総時間は $O(Q\log Q+Qf(N))$、保持領域は $O(K)$ となる。
