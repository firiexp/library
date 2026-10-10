---
title: 差分・矛盾判定付きrollback UnionFind
documentation_of: //datastructure/undoable_weighted_unionfind.cpp
---

## 説明
群上の差分制約 `inv(potential[a]) op potential[b] == w` を追加し、履歴の途中まで取り消せるUnionFind。
非可換な群にも対応し、成分ごと・全体の矛盾を管理する。

## できること
- `UndoableWeightedUnionFind<G> uf(n)`：制約のない `n` 頂点を作る
- `unite(a, b, w)`：制約を1本登録する。2成分を併合したときだけ `true` を返す。戻り値は整合性を意味しない
- `consistent()` / `consistent(v)`：全制約 / `v` の成分が整合するかを返す
- `same(a, b)`：同じ成分かを返す
- `diff(a, b)`：同じ整合する成分なら差分を `optional<G::T>` で返す。それ以外は `nullopt`
- `root(v)` / `size(v)`：成分の代表 / 頂点数を返す
- `get_state()`：現在の制約数を返す
- `undo()`：直前の1制約を取り消す。履歴が空でないことが前提
- `rollback(s)`：履歴長 `s` まで戻す。現在の履歴のprefix `0 <= s <= get_state()` を指定する

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
rollback後に捨てた履歴への移動はできず、永続versionのAPIではない。

## 実装上の補足
経路圧縮せず、サイズの小さい根を大きい根につなぐ。群演算と要素コピーを $O(1)$ とすると、`root/same/size/diff/consistent(v)` は最悪 $O(\log(N+1))$。
`consistent()/get_state()/undo()` は最悪 $O(1)$、$k$ 操作を戻すrollbackは $O(k)$。
`unite` の木操作は最悪 $O(\log(N+1))$、履歴配列の幾何拡張を含めると償却で同じ計算量となる。
同時に保持した制約数の最大値を $S_{\max}$ として、領域は $O(N+S_{\max})$。rollbackで履歴のcapacityは縮めない。
