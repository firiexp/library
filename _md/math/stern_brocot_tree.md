---
title: Stern-Brocot木
documentation_of: //math/stern_brocot_tree.cpp
---

## 説明
Stern-Brocot 木上の正の有理数を、連続した `L` / `R` 移動列や部分木区間として扱う。
分数と経路の相互変換、LCA、祖先、部分木の表す区間の取得、分子・分母に上限を設けた有理数の探索に使える。

## できること
$L$ を圧縮後の経路長とする。2つの経路ではその長さの最大値を使う。

- `vector<Move> encode_path(ll a, ll b)`
  正の分数 `a / b` への経路を、同じ方向への連続した移動をまとめた列で返す。$O(\log\max(a,b))$
- `Node decode_path(const vector<Move>& path)`
  経路から節点を復元する。$O(L)$
- `Node apply(Node node, Move move)`
  節点から `move.dir` の方向へ `move.steps` 回下る。$O(1)$
- `vector<Move> lca_path(const vector<Move>& a, const vector<Move>& b)`
  2つの経路の共通接頭辞を返す。$O(L)$
- `vector<Move> ancestor_path(const vector<Move>& path, ll k)`
  根から深さ `k` の祖先への経路を返す。`k < 0` または `depth(path)` を超える場合は `{ {Left, -1} }`（`depth` は `-1`）。$O(L)$
- `Node ancestor(ll a, ll b, ll k)`
  正の分数 `a / b` の根から深さ `k` の祖先を返す。`k < 0` または分数の深さを超える場合は `Node(-1, -1, 0, 0)`（`num() == -1`、`den() == -1`）。$O(\log\max(a,b))$
- `ll depth(const vector<Move>& path)`
  根からの移動回数の合計を返す。$O(L)$
- `Node range(ll a, ll b)`
  正の分数 `a / b` を根とする部分木が表す開区間 `(p / q, r / s)` を返す。$O(\log\max(a,b))$
- `Node lca(ll a, ll b, ll c, ll d)`
  2つの正の分数 `a / b` と `c / d` の LCA を返す。$O(\log\max(a,b,c,d))$
- `pair<pair<ll, ll>, pair<ll, ll>> binary_search(ll max_num, ll max_den, Pred pred)`
  分子 `max_num` 以下・分母 `max_den` 以下の正の既約分数の中で、`pred(p, q)` が真になる最大の `{p, q}` と偽になる最小の `{p, q}` を返す。真の分数がなければ左端は `{0, 1}`、偽の分数がなければ右端は `{1, 0}`。$N = \max(\text{max\_num}, \text{max\_den})$ として述語呼び出し $O(\log N)$ 回、述語を除き $O(\log N)$

## 使い方
`SternBrocotTree` 名前空間の関数と型を使う。
`Node` は部分木の開区間 `(p / q, r / s)` を持ち、節点が表す分数は `num()` / `den()`（`(p + r) / (q + s)`）で取れる。
経路は `Move{Left, x}` や `Move{Right, x}` の列で扱い、`x` は同じ方向へ続けて下る回数を表す。根 `1 / 1` の深さは `0` とする。

`binary_search` では、`max_num, max_den >= 0` とし、上限内の正の既約分数を昇順に並べたとき `pred(p, q)` が真から偽へ高々1回だけ切り替わるものとする。
`pred` には上限内の正の既約分数 `(p, q)` のみが渡される。

```cpp
auto [left, right] = SternBrocotTree::binary_search(5, 5, [](ll p, ll q) {
    return 5 * p <= 7 * q;
}); // left = {4, 3}, right = {3, 2}
```

## 実装上の補足
`binary_search` は同じ方向へ進める歩数を指数探索と二分探索で求める。
