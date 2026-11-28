---
title: 動的bitset(Dynamic Bitset)
documentation_of: //datastructure/bitset/dynamic_bitset.cpp
---

## 説明
可変長の bitset。
`uint64_t` 単位で持ち、集合演算、shift、立っている bit の走査を扱う。

## できること
$N$ は bitset の長さとする。

- `DynamicBitset bs(int n, bool x = false)`
  長さ `n` の bitset を作る。`x = true` なら全 bit を 1 で初期化する。$O(\lceil N/64 \rceil)$
- `int size() const`
  長さを返す。$O(1)$
- `bool empty() const`
  長さが 0 のときだけ `true` を返す。$O(1)$
- `bool test(int k) const`
  `k` bit 目を返す。$O(1)$
- `void set(int k)`, `void reset(int k)`, `void flip(int k)`, `void assign(int k, bool x)`
  `k` bit 目を更新する。$O(1)$
- `void set()`, `void reset()`, `void flip()`
  全体を更新する。$O(\lceil N/64 \rceil)$
- `void set(int l, int r)`, `void reset(int l, int r)`, `void flip(int l, int r)`
  半開区間 `[l, r)` をそれぞれ1、0、反転で更新する。時間 $O(1+\lceil(r-l)/64\rceil)$、追加領域 $O(1)$
- `bool any() const`, `bool none() const`, `bool all() const`
  1 があるか、全て 0 か、全て 1 かを返す。$O(\lceil N/64 \rceil)$
- `int count() const`
  1 の個数を返す。時間 $O(\lceil N/64 \rceil)$、追加領域 $O(1)$
- `int count_and(const DynamicBitset &other) const`
  両方で 1 の bit 数を返す。空なら `0`。時間 $O(\lceil N/64 \rceil)$、追加領域 $O(1)$
- `int count_xor(const DynamicBitset &other) const`
  bit が異なる位置の数（Hamming 距離）を返す。時間 $O(\lceil N/64 \rceil)$、追加領域 $O(1)$
- `bool intersects(const DynamicBitset &other) const`
  両方で 1 の bit があれば `true`。なければ空も含めて `false`。時間 $O(\lceil N/64 \rceil)$、追加領域 $O(1)$
- `int find_first() const`
  最初に立っている bit の位置を返す。なければ `-1`。$O(\lceil N/64 \rceil)$
- `int find_last() const`
  最後に立っている bit の位置を返す。なければ `-1`。$O(\lceil N/64 \rceil)$
- `int find_next(int k) const`
  $-1 \le k < N$。位置 $k+1$（$k=-1$ なら先頭）から昇順に探し、最初に立っている bit の位置を返す。なければ `-1`。$O(\lceil N/64 \rceil)$
- `int find_prev(int k) const`
  $0 \le k \le N$。位置 $k-1$（$k=N$ なら末尾）から降順に探し、最初に立っている bit の位置を返す。なければ `-1`。$O(\lceil N/64 \rceil)$
- `bs &= other`, `bs |= other`, `bs ^= other`
  bitset 同士の演算をその場で行う。$O(\lceil N/64 \rceil)$
- `bs << s`, `bs >> s`, `bs <<= s`, `bs >>= s`
  shift する。$O(\lceil N/64 \rceil)$
- `DynamicBitset &or_shift_left(int s)`
  `bs |= bs << s` と同じ更新を行い、自身への参照を返す。時間 $O(\lceil N/64 \rceil)$、追加領域 $O(1)$
- `DynamicBitset &or_shift_right(int s)`
  `bs |= bs >> s` と同じ更新を行い、自身への参照を返す。時間 $O(\lceil N/64 \rceil)$、追加領域 $O(1)$

## 使い方
例えば `bs.reset(limit, bs.size())` で `limit` 以上の候補をまとめて消せる。
長さが同じ bitset 同士で演算する。
`find_first`, `find_next` を使うと立っている bit だけを前から走査できる。
`find_last`, `find_prev` を使うと後ろからも走査できる。
部分和 DP は `reachable.set(0)` で初期化し、各重み `w` に対して `reachable.or_shift_left(w)` で更新できる。

## 実装上の補足
`count()`、`count_and()`、`count_xor()` は短い配列では scalar、長い配列では対応 CPU に応じた SIMD 集計を使う。
`StaticBitset` と集計処理を共有し、両方を同時に include できる。
`intersects` は共通 bit を見つけた時点で返る。
`or_shift_left` と `or_shift_right` は、`s <= 0`、`s >= size()`、空 bitset の場合は変更しない。

### 内部用の補助関数

`solve_linear_system_mod2` はピボット列を含む word から行を消去するために `xor_from_word` を使う。
`operator^=` も開始位置に 0 を指定してこの関数を使う。

- `DynamicBitset &xor_from_word(const DynamicBitset &other, int k)`
  64 bit を 1 word とし、word 数を $W=\lceil N/64\rceil$ とする。$0\le k\le W$ に対し、区間 $[k,W)$ の各 word を `other` の同じ位置の word と XOR し、自身への参照を返す。時間 $O(1+W-k)$、追加領域 $O(1)$
