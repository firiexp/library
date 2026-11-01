---
title: 永続セグメント木(Persistent Segment Tree)
documentation_of: //datastructure/segmenttree/persistent_segtree.cpp
date: 2026-03-08
category: データ構造
tags: データ構造
---

## 説明
点更新ごとに新しいバージョンを作り、任意の過去のバージョンの区間積を求める。
更新前のバージョンはそのまま残る。

Cursor はあるバージョンのセグメント木で、現在見ているノードとその区間を表す。
その区間の積を読み取ったり、左右の子を指す Cursor を取得したりできる。
複数のバージョンを同時にたどり、区間積の差などを見て探索する用途に使う。

## できること
要素数を $N$、モノイドの演算を $O(1)$ とする。

- `PersistentSegmentTree<M> seg(n)`
  全要素が単位元の列を初期バージョン `0` として作る。時間・領域ともに $O(1)$
- `PersistentSegmentTree<M> seg(values)`
  配列から初期バージョン `0` を作る。時間・領域ともに $O(N)$
- `int update(int t, int k, const T &x)`
  バージョン `t` を元に、位置 `k` の値を `x` に置き換えた新しいバージョンを作り、その番号を返す。配列の拡張を含めて償却 $O(\log N)$、追加ノード数は $O(\log N)$
- `int add(int t, int k, const T &x)`
  バージョン `t` を元に、位置 `k` の値 `old` を `M::f(old, x)` に置き換えた新しいバージョンを作り、その番号を返す。配列の拡張を含めて償却 $O(\log N)$、追加ノード数は $O(\log N)$
- `T query(int t, int l, int r)`
  バージョン `t` に対して半開区間 `[l, r)` の積を返す。空区間なら単位元を返す。最悪 $O(\log N)$
- `T get(int t, int k)`
  バージョン `t` の位置 `k` の値を返す。最悪 $O(\log N)$
- `int search_right(int t, int l, F cond) const`
  バージョン `t` で `cond(query(t, l, r))` を満たす最大の `r` を返す。最悪 $O(\log N)$
- `int search_left(int t, int r, F cond) const`
  バージョン `t` で `cond(query(t, l, r))` を満たす最小の `l` を返す。最悪 $O(\log N)$
- `int latest_version()` / `int versions()`
  最新のバージョン番号 / 保持しているバージョン数を返す。$O(1)$
- `Cursor root_cursor(int t) const`
  バージョン `t` の全区間を表す読み取り専用 Cursor を返す。省略時は最新のバージョン。$O(1)$
- `Children split(const Cursor &cur) const`
  空でも葉でもない Cursor を、前半 `low` と後半 `high` に分ける。$O(1)$
- `T cur.fold()` / `pair<int, int> cur.range()`
  現在区間の積のコピー / 半開区間の両端を返す。$O(1)$
- `bool cur.empty()` / `bool cur.is_leaf()` / `int cur.index()`
  区間が空か / 長さ1か / 葉の位置を返す。`index()` は葉でのみ使う。$O(1)$

## 使い方
`M` に `T`、二項演算 `f`、単位元 `e` を定義する。非可換モノイドも使える。
`update`、`add`、`query`、`search_right`、`search_left` はバージョン番号を省略すると最新のバージョンを使う。`seg[k]` は最新のバージョンの値を返す。
境界探索の `cond` は単位元で `true` とし、区間を伸ばすと `true` から `false` への変化が高々1回になるものを使う。探索の計算量は述語が $O(1)$ の場合である。
要素数が0の場合、更新は空の新しいバージョンを作り、区間積は単位元を返す。

整数の加算なら次のように定義する。

```cpp
struct Monoid {
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

PersistentSegmentTree<Monoid> seg(3);
int t = seg.update(0, 1, 5);
long long sum = seg.query(t, 0, 3);
```

Cursor の応用例は[Cursorによる区間内順位検索](../../guides/persistent_segtree_cursor.html)を参照。

## 実装上の補足
サイズ指定の構築では単位元を持つ1ノードを未更新の全区間で共有する。
更新時だけ経路をコピーし、過去のバージョンと共有ノードは変更しない。
共有ノードの子は自分自身を指す。`node` と `root` は区間境界と組み合わせる内部表現であり、子リンクだけで辿る通常の木ではない。
境界探索は部分木の積を使って走査する。再帰の作業領域は $O(\log N)$。
`get` と `operator[]` は有効な位置 `0 <= k < n` の葉へ直接降下する。作業領域は $O(1)$。
Cursor はノード番号と区間境界を持つため、初期共有ノードも有限の区間として降下できる。
要素数0の根は空で、葉ではなく、積は単位元となる。
Cursor の作成・分割はノードやバージョンを追加しない。
$K$ 本のバージョンを同時にたどる順位探索は $O(K\log N)$ 時間、Cursor の保持領域は $O(K)$。
`update`・`add` に伴う内部配列の再確保後も、過去の Cursor は有効である。
参照先の木を破棄・move・代入・swap した場合は無効になる。Cursor の寿命内では同じ木オブジェクトを使う。
