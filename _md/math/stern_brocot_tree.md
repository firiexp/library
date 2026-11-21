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
  深さ `k` の祖先への経路を返す。`k == 0` なら根への空の経路を返す。`k < 0` または `k > depth(path)` なら `nullopt` を返す。$O(L)$
- `optional<Node> ancestor(ll a, ll b, ll k)`
  分数 $a/b$ の深さ `k` の祖先を返す。指定した深さに祖先がなければ `nullopt` を返す。$O(\log\max(a,b))$
- `ll depth(const vector<Move>& path)`
  根からの移動回数の合計を返す。$O(L)$
- `Node range(ll a, ll b)`
  `a / b` を根とする部分木が表す開区間 `(p / q, r / s)` を返す。$O(\log\max(a,b))$
- `Node lca(ll a, ll b, ll c, ll d)`
  2 つの分数の LCA を返す。$O(\log\max(a,b,c,d))$
- `pair<pair<ll, ll>, pair<ll, ll>> binary_search(ll max_num, ll max_den, Pred pred)`
  分子が `max_num` 以下、分母が `max_den` 以下の正の既約分数を対象とする。`pred(p, q)` が真になる最大の $p/q$ と、偽になる最小の $p/q$ をこの順に返す。各分数は `{分子, 分母}` で表す。2つの上限の大きい方を $N$ として、述語の呼び出しは $O(\log N)$ 回、述語を除く計算時間は $O(\log N)$、追加領域は $O(1)$。

## 使い方
`Node` は部分木の境界 `(p / q, r / s)` を持ち、現在の節点は mediant `(p + r) / (q + s)` で取れる。
経路は `Move{Left, x}` や `Move{Right, x}` の列で扱い、`x` は同じ方向へ続けて下る回数を表す。
`SternBrocotTree` 名前空間の関数と型を使う。

`encode_path(a, b)` は既約分数を想定する。

探索の上限にはそれぞれ $0$ 以上の `ll` を指定する。分数を小さい順に並べたとき、`pred(p, q)` は真から偽に高々1回だけ切り替わるものとする。真の分数がなければ左端は $0/1$、偽の分数がなければ右端は $1/0$ とする。上限のどちらかが $0$ なら $0/1$ と $1/0$ を返す。述語を呼ぶのは分子・分母がともに正で上限内にあるときだけである。

```cpp
auto [left, right] = SternBrocotTree::binary_search(5, 5, [](ll p, ll q) {
    return 5 * p <= 7 * q;
}); // left = 4/3, right = 3/2
```

条件を $p/q\leq x/y$ とすると、$x/y$ 自身が範囲内にあるときは左端が $x/y$ になる。交差積 $py$ と $qx$ が `ll` に収まらない場合は、述語の乗算を `__int128` で行う。

## 実装上の補足
同じ方向に進める歩数を倍々に試してから二分探索する。まとめて $t$ 歩進む区間の述語呼び出しは $O(1+\log t)$ 回。各区間で更新する端点の分子と分母の和は、直前に更新した端点の和の $t$ 倍以上になる。この和は $2N$ 以下なので、全区間の $t$ の積も $2N$ 以下である。さらに、更新が2回進むと和は少なくとも2倍になるため、区間数も $O(\log N)$ に収まる。
