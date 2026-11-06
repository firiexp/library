---
title: 2次元Fenwick Tree(2D BIT)
documentation_of: //datastructure/range_query_2d/fenwick_tree_2d.cpp
date: 2026-03-11
category: データ構造
tags: データ構造
---

## 説明
更新される点集合を先に登録してから構築する座圧 2 次元 BIT。
点加算と半開長方形和を扱う。

## できること
登録点数を $N$、異なる登録座標の個数を $P$ とする。

- `FenwickTree2D<T> fw`
  空の 2 次元 BIT を作る。$O(1)$
- `int add_point(int x, int y)`
  今後更新する可能性がある点 `(x, y)` を登録し、登録順の `0`-indexed ID を返す。重複登録にも別の ID を返す。償却 $O(1)$
- `void build()`
  登録済みの点から内部座圧を構築する。空集合・重複登録も扱える。呼び出しは1回に限る。$O(N\log N)$
- `void build(const vector<T>& initial_weights)`
  登録順に初期重みを与えて構築する。列の長さは登録点数以下とし、省略した末尾の重みは `0`。重複座標の重みは加算する。$O(N\log N)$
- `void add(int x, int y, T w)`
  登録済みの点 `(x, y)` に `w` を加える。未登録点は使えない。$O(\log^2 N)$
- `void prepare_updates()`
  構築後に ID ごとの更新先を前計算する。呼び出しは1回に限り、現在の重みは変えない。$O(N\log N)$、追加領域 $O(N+P\log P)$
- `void add(int id, T w)`
  `prepare_updates()` 後に、ID が指す点へ `w` を加える。同じ座標の ID は同じ点を更新する。$O(\log^2 P)$
- `T sum(int x, int y)`
  半開長方形 `(-inf, x) x (-inf, y)` の総和を返す。$O(\log^2 N)$
- `T sum(int l, int d, int r, int u)`
  半開長方形 `[l, r) x [d, u)` の総和を返す。`l <= r`、`d <= u` で使い、空長方形は `0` を返す。$O(\log^2 N)$

## 使い方
`T` は `0` が加算の単位元となり、`+=` と減算を使える可換群の型にする。
更新に使う全点を `add_point` で登録してから `build()` する。
`build()` 後は `add` と `sum` を任意順に呼べる。
初期点を先に登録し、その後に将来の更新点を登録すると、`build(initial_weights)` に初期点だけの重みを渡せる。初期値がない場合は `build()` を使う。

同じ登録点への更新が多い場合は、`prepare_updates()` で更新先を保存できる。座標による加算と併用でき、ID はそのインスタンス内で有効である。
更新が少ない場合は、前計算をせず座標による `add` を使う。

```cpp
FenwickTree2D<long long> fw;
int id = fw.add_point(2, 3);
fw.build(vector<long long>{5});
fw.prepare_updates();
fw.add(id, 7);
long long total = fw.sum(0, 0, 4, 4);
```

## 実装上の補足
登録点を重複排除して $x$ の順位と各外側 BIT ノードの必要容量を求め、$y$ 順に各外側 BIT ノードへ配る。
各外側 BIT ノードが持つ $y$ 座標列は既に整列済みなので、再ソートせず重複排除だけを行う。
登録順や重複除去を利用側で管理する必要はない。
初期重みを渡した場合は、各行で同じ $y$ の重みを集約し、配列から BIT を線形構築する。構築直後に全初期点へ `add` する必要はない。
初期重みの個数が登録点数に対して少ない場合は、通常構築後の個別加算を内部で選ぶ。個別加算は $O(N/\log N)$ 個以下に限るため、構築全体の $O(N\log N)$ は変わらない。

長方形和は外側・内側の BIT で共通の累積経路を省く。保持領域は $O(N\log N)$。
ID 更新の前計算では、登録点を座標ごとにまとめ、$y$ 順に走査して各行の更新位置を求める。同じ座標の更新位置列は共有する。
