---
title: Stern-Brocot木
documentation_of: //math/stern_brocot_tree.cpp
---

## 説明
Stern-Brocot 木上の有理数の位置を、連続した `L` / `R` 移動列として扱う。
分数と経路の相互変換、LCA、祖先、部分木の表す区間の取得、分子・分母に上限を設けた有理数の探索に使える。

## できること
$L$ を圧縮後の経路長とする。2つの経路ではその長さの最大値を使う。

- `vector<Move> encode_path(ll a, ll b)`
  既約分数 `a / b` への経路を、同じ方向への連続した移動をまとめた列で返す。$O(\log\max(a,b))$
- `Node decode_path(const vector<Move>& path)`
  経路から節点を復元する。$O(L)$
- `Node apply(Node node, Move move)`
  節点から `move.dir` の方向へ `move.steps` 回下る。$O(1)$
- `vector<Move> lca_path(const vector<Move>& a, const vector<Move>& b)`
  2 つの経路の共通接頭辞を返す。$O(L)$
- `optional<vector<Move>> ancestor_path(const vector<Move>& path, ll k)`
  深さ `k` の祖先への経路を返す。存在しなければ `nullopt`。$O(L)$
- `optional<Node> ancestor(ll a, ll b, ll k)`
  分数 $a/b$ の深さ `k` の祖先を返す。存在しなければ `nullopt`。$O(\log\max(a,b))$
- `ll depth(const vector<Move>& path)`
  根からの移動回数の合計を返す。$O(L)$
- `Node range(ll a, ll b)`
  `a / b` を根とする部分木が表す開区間 `(p / q, r / s)` を返す。$O(\log\max(a,b))$
- `Node lca(ll a, ll b, ll c, ll d)`
  2 つの分数の LCA を返す。$O(\log\max(a,b,c,d))$
- `pair<pair<ll, ll>, pair<ll, ll>> binary_search(ll max_num, ll max_den, Pred pred)`
  分子 `max_num` 以下・分母 `max_den` 以下の正の既約分数の中で、`pred(p, q)` が真になる最大の `{p, q}` と偽になる最小の `{p, q}` を返す。$N = \max(\text{max\_num}, \text{max\_den})$ として述語呼び出し $O(\log N)$ 回、述語を除き $O(\log N)$

## 使い方
`Node` は部分木の境界 `(p / q, r / s)` を持ち、現在の節点は mediant `(p + r) / (q + s)` で取れる。
経路は `Move{Left, x}` や `Move{Right, x}` の列で扱い、`x` は同じ方向へ続けて下る回数を表す。
`SternBrocotTree` 名前空間の関数と型を使う。

`encode_path(a, b)` は既約分数を想定する。

`binary_search` では、分数を昇順に並べたとき `pred(p, q)` が真から偽へ高々1回だけ切り替わるものとする。
真の分数がなければ左端は `{0, 1}`、偽の分数がなければ右端は `{1, 0}` となる。

```cpp
auto [left, right] = SternBrocotTree::binary_search(5, 5, [](ll p, ll q) {
    return 5 * p <= 7 * q;
}); // left = 4/3, right = 3/2
```

## 実装上の補足
`binary_search` は同じ方向に進める歩数を倍々に試してから二分探索することで、述語の呼び出し回数を $O(\log N)$ に抑える。
