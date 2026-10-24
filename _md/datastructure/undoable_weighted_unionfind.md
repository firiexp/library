---
title: 差分・矛盾判定付きrollback UnionFind
documentation_of: //datastructure/undoable_weighted_unionfind.cpp
---

## 説明
群上の差分制約 `inv(potential[a]) op potential[b] == w` を追加し、履歴の途中まで取り消せるUnionFind。
非可換な群にも対応し、成分ごと・全体の矛盾を管理する。

## できること
頂点数を $N$ とし、群演算と要素コピーを $O(1)$ とする。

- `UndoableWeightedUnionFind<G> uf(n)`：制約のない `n` 頂点を作る。$O(N)$
- `unite(a, b, w)`：制約を1本登録する。2成分を併合したときだけ `true` を返す。戻り値は整合性を意味しない。償却 $O(\log N)$
- `consistent()` / `consistent(v)`：全制約 / `v` の成分が整合するかを返す。全体は $O(1)$、成分指定は $O(\log N)$
- `same(a, b)`：同じ成分かを返す。$O(\log N)$
- `diff(a, b)`：同じ整合する成分なら差分を `optional<G::T>` で返す。それ以外は `nullopt`。$O(\log N)$
- `root(v)` / `size(v)`：成分の代表 / 頂点数を返す。$O(\log N)$
- `get_state()`：現在の制約数を返す。$O(1)$
- `undo()`：直前の1制約を取り消す。履歴が空でないことが前提。$O(1)$
- `rollback(s)`：履歴長 `s` まで戻す。現在の履歴のprefix `0 <= s <= get_state()` を指定する。戻す制約数を $k$ として $O(k)$

## 使い方
`G` に `using T`、結合演算 `op(a,b)`、逆元 `inv(a)`、単位元 `e()` を定義し、`T` を等値比較できるようにする。
整数の差分を扱う場合は、`T = long long` として次のように定義する。

```cpp
struct AddGroup {
    using T = long long;
    static T op(T a, T b) { return a + b; }
    static T inv(T a) { return -a; }
    static T e() { return 0; }
};

UndoableWeightedUnionFind<AddGroup> uf(3);
int state = uf.get_state();
uf.unite(0, 1, 5);
uf.unite(1, 2, 3);
auto delta = uf.diff(0, 2);
uf.rollback(state);
```

この例では `delta` は8を保持し、rollbackで2本の制約を取り消す。

整合する冗長制約と矛盾する制約も、それぞれ1操作として履歴に積む。
別成分が矛盾していても、整合する成分の差分は取得できる。
rollback後に捨てた履歴には戻れない。

## 実装上の補足
経路圧縮せず、サイズの小さい根を大きい根につなぐ。
同時に保持した制約数の最大値を $S_{\max}$ として、領域は $O(N+S_{\max})$。rollbackで履歴のcapacityは縮めない。
