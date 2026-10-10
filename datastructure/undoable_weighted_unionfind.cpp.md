---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_undoable_weighted_unionfind.test.cpp
    title: test/yosupo_aplusb_undoable_weighted_unionfind.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_unionfind_with_potential_undoable.test.cpp
    title: test/yosupo_unionfind_with_potential_undoable.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u5DEE\u5206\u30FB\u77DB\u76FE\u5224\u5B9A\u4ED8\u304Drollback\
      \ UnionFind"
    links: []
  bundledCode: "#line 1 \"datastructure/undoable_weighted_unionfind.cpp\"\ntemplate<class\
    \ G>\nclass UndoableWeightedUnionFind {\n    using T = typename G::T;\n    struct\
    \ Change {\n        int a, b, size_a, size_b, bad_a, bad_b, total_bad;\n     \
    \   T weight_b;\n    };\n\n    vector<int> parent, bad;\n    vector<T> weight;\n\
    \    vector<Change> history;\n    int total_bad = 0;\n\n    pair<int, T> root_weight(int\
    \ v) const {\n        T result = G::e();\n        while (parent[v] >= 0) {\n \
    \           result = G::op(weight[v], result);\n            v = parent[v];\n \
    \       }\n        return {v, result};\n    }\n\npublic:\n    explicit UndoableWeightedUnionFind(int\
    \ n) : parent(n, -1), bad(n), weight(n, G::e()) {}\n\n    int root(int v) const\
    \ {\n        while (parent[v] >= 0) v = parent[v];\n        return v;\n    }\n\
    \n    bool same(int a, int b) const { return root(a) == root(b); }\n    int size(int\
    \ v) const { return -parent[root(v)]; }\n    bool consistent() const { return\
    \ total_bad == 0; }\n    bool consistent(int v) const { return bad[root(v)] ==\
    \ 0; }\n\n    optional<T> diff(int a, int b) const {\n        auto [ra, wa] =\
    \ root_weight(a);\n        auto [rb, wb] = root_weight(b);\n        if (ra !=\
    \ rb || bad[ra]) return nullopt;\n        return G::op(G::inv(wa), wb);\n    }\n\
    \n    bool unite(int a, int b, const T &w) {\n        auto [ra, wa] = root_weight(a);\n\
    \        auto [rb, wb] = root_weight(b);\n        T delta = G::op(wa, G::op(w,\
    \ G::inv(wb)));\n        if (parent[ra] > parent[rb]) {\n            swap(ra,\
    \ rb);\n            delta = G::inv(delta);\n        }\n        history.push_back({ra,\
    \ rb, parent[ra], parent[rb], bad[ra], bad[rb], total_bad, weight[rb]});\n   \
    \     if (ra == rb) {\n            if (!(delta == G::e())) {\n               \
    \ ++bad[ra];\n                ++total_bad;\n            }\n            return\
    \ false;\n        }\n        parent[ra] += parent[rb];\n        parent[rb] = ra;\n\
    \        weight[rb] = delta;\n        bad[ra] += bad[rb];\n        return true;\n\
    \    }\n\n    int get_state() const { return (int)history.size(); }\n\n    void\
    \ undo() {\n        assert(!history.empty());\n        const auto &change = history.back();\n\
    \        parent[change.a] = change.size_a;\n        parent[change.b] = change.size_b;\n\
    \        bad[change.a] = change.bad_a;\n        bad[change.b] = change.bad_b;\n\
    \        weight[change.b] = change.weight_b;\n        total_bad = change.total_bad;\n\
    \        history.pop_back();\n    }\n\n    void rollback(int state) {\n      \
    \  assert(0 <= state && state <= get_state());\n        while (get_state() > state)\
    \ undo();\n    }\n};\n\n/**\n * @brief \u5DEE\u5206\u30FB\u77DB\u76FE\u5224\u5B9A\
    \u4ED8\u304Drollback UnionFind\n */\n"
  code: "template<class G>\nclass UndoableWeightedUnionFind {\n    using T = typename\
    \ G::T;\n    struct Change {\n        int a, b, size_a, size_b, bad_a, bad_b,\
    \ total_bad;\n        T weight_b;\n    };\n\n    vector<int> parent, bad;\n  \
    \  vector<T> weight;\n    vector<Change> history;\n    int total_bad = 0;\n\n\
    \    pair<int, T> root_weight(int v) const {\n        T result = G::e();\n   \
    \     while (parent[v] >= 0) {\n            result = G::op(weight[v], result);\n\
    \            v = parent[v];\n        }\n        return {v, result};\n    }\n\n\
    public:\n    explicit UndoableWeightedUnionFind(int n) : parent(n, -1), bad(n),\
    \ weight(n, G::e()) {}\n\n    int root(int v) const {\n        while (parent[v]\
    \ >= 0) v = parent[v];\n        return v;\n    }\n\n    bool same(int a, int b)\
    \ const { return root(a) == root(b); }\n    int size(int v) const { return -parent[root(v)];\
    \ }\n    bool consistent() const { return total_bad == 0; }\n    bool consistent(int\
    \ v) const { return bad[root(v)] == 0; }\n\n    optional<T> diff(int a, int b)\
    \ const {\n        auto [ra, wa] = root_weight(a);\n        auto [rb, wb] = root_weight(b);\n\
    \        if (ra != rb || bad[ra]) return nullopt;\n        return G::op(G::inv(wa),\
    \ wb);\n    }\n\n    bool unite(int a, int b, const T &w) {\n        auto [ra,\
    \ wa] = root_weight(a);\n        auto [rb, wb] = root_weight(b);\n        T delta\
    \ = G::op(wa, G::op(w, G::inv(wb)));\n        if (parent[ra] > parent[rb]) {\n\
    \            swap(ra, rb);\n            delta = G::inv(delta);\n        }\n  \
    \      history.push_back({ra, rb, parent[ra], parent[rb], bad[ra], bad[rb], total_bad,\
    \ weight[rb]});\n        if (ra == rb) {\n            if (!(delta == G::e()))\
    \ {\n                ++bad[ra];\n                ++total_bad;\n            }\n\
    \            return false;\n        }\n        parent[ra] += parent[rb];\n   \
    \     parent[rb] = ra;\n        weight[rb] = delta;\n        bad[ra] += bad[rb];\n\
    \        return true;\n    }\n\n    int get_state() const { return (int)history.size();\
    \ }\n\n    void undo() {\n        assert(!history.empty());\n        const auto\
    \ &change = history.back();\n        parent[change.a] = change.size_a;\n     \
    \   parent[change.b] = change.size_b;\n        bad[change.a] = change.bad_a;\n\
    \        bad[change.b] = change.bad_b;\n        weight[change.b] = change.weight_b;\n\
    \        total_bad = change.total_bad;\n        history.pop_back();\n    }\n\n\
    \    void rollback(int state) {\n        assert(0 <= state && state <= get_state());\n\
    \        while (get_state() > state) undo();\n    }\n};\n\n/**\n * @brief \u5DEE\
    \u5206\u30FB\u77DB\u76FE\u5224\u5B9A\u4ED8\u304Drollback UnionFind\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/undoable_weighted_unionfind.cpp
  requiredBy: []
  timestamp: '2026-10-10 18:59:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_unionfind_with_potential_undoable.test.cpp
  - test/yosupo_aplusb_undoable_weighted_unionfind.test.cpp
documentation_of: datastructure/undoable_weighted_unionfind.cpp
layout: document
title: "\u5DEE\u5206\u30FB\u77DB\u76FE\u5224\u5B9A\u4ED8\u304Drollback UnionFind"
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
