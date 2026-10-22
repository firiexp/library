---
title: 動的な木の部分木加算・部分木和（Euler Tour Tree）
documentation_of: //tree/euler_tour_tree.cpp
---

## 説明
辺の追加・削除で形が変わる森に対し、部分木への加算と部分木の頂点数・頂点値の和を求める。
部分木は辺 `(v, p)` の `p` を親としたときの `v` 側とする。

## できること
- `EulerTourTree tree(values)`
  `vector<long long>` の初期頂点値から、辺のない森を作る
- `bool link(u, v)`
  異なる連結成分の頂点 `u, v` を辺で結ぶ。同じ連結成分なら追加せず false を返す
- `bool cut(u, v)`
  辺 `(u, v)` を削除する。辺がなければ false を返す
- `void subtree_add(v, p, x)`
  `p` を親とした `v` の部分木の各頂点に `x` を足す
- `long long subtree_sum(v, p)`
  `p` を親とした `v` の部分木の頂点値の和を返す
- `SubtreeInfo subtree_info(v, p)`
  同じ部分木の頂点数 `int size` と頂点値の和 `long long sum` をまとめて返す。孤立点の `size` は1
- `void vertex_add(v, x)` / `long long get(v)`
  頂点 `v` に `x` を足す / 頂点 `v` の値を返す
- `bool connected(u, v)`
  頂点 `u, v` が同じ連結成分かを返す

## 使い方
頂点番号は `0..values.size()-1` とする。初期の辺も `link` で追加する。
`subtree_add`・`subtree_sum`・`subtree_info` の親 `p` は、現在 `v` と辺でつながっている頂点を指定する。
`p=-1` を指定すると `v` の連結成分全体を扱い、孤立点にも使える。
頂点値・和・加算の中間計算は long long に収まるものとする。負の値・加算量も扱う。

```cpp
EulerTourTree tree(values);
for (auto [u, v] : edges) tree.link(u, v);
tree.subtree_add(v, p, x);
auto sum = tree.subtree_sum(v, p);
auto info = tree.subtree_info(v, p);
auto component = tree.subtree_info(v, -1);
tree.cut(u, v);
tree.link(w, z);
```

## 実装上の補足
頂点数を $N$ とすると、構築は $O(N)$ 時間・領域、各操作は償却 $O(\log N)$ 時間。
Euler tour を splay 木で保持する。各頂点の値を持つノードは1個、各辺を表すノードは2個とし、辺のノードは加算対象の個数に含めない。
削除した辺のノードを再利用するため、保持領域は操作数によらず $O(N)$。
再帰は使わず、問い合わせでも内部の splay 木の形を変更する。
`subtree_info` は区間の分離・復元を1回だけ行い、既存の頂点数と和を読み出す。保持配列は増やさず、追加の局所領域は $O(1)$。
祖先列の遅延伝播には既存の作業配列を再利用し、その長さは最悪 $O(N)$ になる。
