---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_persistent_segtree.test.cpp
    title: test/yosupo_aplusb_persistent_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_add_range_sum_persistent.test.cpp
    title: test/yosupo_point_add_range_sum_persistent.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6C38\u7D9A\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Persistent Segment\
      \ Tree)"
    links: []
  bundledCode: "#line 1 \"datastructure/segmenttree/persistent_segtree.cpp\"\ntemplate\
    \ <class M>\nstruct PersistentSegmentTree{\n    using T = typename M::T;\n   \
    \ struct Node{\n        T val;\n        int l, r;\n    };\n\n    int n{};\n  \
    \  vector<Node> node;\n    vector<int> root;\n\n    explicit PersistentSegmentTree(int\
    \ n): n(n){\n        node.push_back({M::e(), 0, 0});\n        root.push_back(0);\n\
    \    }\n    explicit PersistentSegmentTree(const vector<T> &v): n(v.size()){\n\
    \        if(n == 0){\n            node.push_back({M::e(), -1, -1});\n        \
    \    root.push_back(0);\n        }else{\n            root.push_back(build(0, n,\
    \ v));\n        }\n    }\n\n    int latest_version() const { return root.size()-1;\
    \ }\n    int versions() const { return root.size(); }\n\n    int update(int t,\
    \ int k, const T &x){\n        if(n == 0){\n            root.push_back(root[t]);\n\
    \            return latest_version();\n        }\n        root.push_back(update_(root[t],\
    \ k, x, 0, n));\n        return latest_version();\n    }\n    int update(int k,\
    \ const T &x){ return update(latest_version(), k, x); }\n\n    int add(int t,\
    \ int k, const T &x){\n        if(n == 0){\n            root.push_back(root[t]);\n\
    \            return latest_version();\n        }\n        root.push_back(add_(root[t],\
    \ k, x, 0, n));\n        return latest_version();\n    }\n    int add(int k, const\
    \ T &x){ return add(latest_version(), k, x); }\n\n    T query(int t, int a, int\
    \ b) const {\n        if(n == 0 || b <= a) return M::e();\n        return query_(root[t],\
    \ a, b, 0, n);\n    }\n    T query(int a, int b) const { return query(latest_version(),\
    \ a, b); }\n\n    T get(int t, int k) const { return query(t, k, k+1); }\n   \
    \ T operator[](const int &k) const { return get(latest_version(), k); }\n\n  \
    \  template<class F>\n    int search_right(int t, int l, F cond) const {\n   \
    \     T acc = M::e();\n        return search_right_(root[t], l, 0, n, acc, cond);\n\
    \    }\n    template<class F>\n    int search_right(int l, F cond) const {\n \
    \       return search_right(latest_version(), l, move(cond));\n    }\n\n    template<class\
    \ F>\n    int search_left(int t, int r, F cond) const {\n        T acc = M::e();\n\
    \        return search_left_(root[t], r, 0, n, acc, cond);\n    }\n    template<class\
    \ F>\n    int search_left(int r, F cond) const {\n        return search_left(latest_version(),\
    \ r, move(cond));\n    }\n\nprivate:\n    template<class F>\n    int search_right_(int\
    \ id, int a, int l, int r, T &acc, F &cond) const {\n        if(r <= a) return\
    \ n;\n        if(a <= l){\n            T next = M::f(acc, node[id].val);\n   \
    \         if(cond(next)){\n                acc = move(next);\n               \
    \ return n;\n            }\n            if(r-l == 1) return l;\n        }\n  \
    \      int m = l + ((r-l)>>1);\n        int result = search_right_(node[id].l,\
    \ a, l, m, acc, cond);\n        if(result != n) return result;\n        return\
    \ search_right_(node[id].r, a, m, r, acc, cond);\n    }\n\n    template<class\
    \ F>\n    int search_left_(int id, int a, int l, int r, T &acc, F &cond) const\
    \ {\n        if(a <= l) return 0;\n        if(r <= a){\n            T next = M::f(node[id].val,\
    \ acc);\n            if(cond(next)){\n                acc = move(next);\n    \
    \            return 0;\n            }\n            if(r-l == 1) return r;\n  \
    \      }\n        int m = l + ((r-l)>>1);\n        int result = search_left_(node[id].r,\
    \ a, m, r, acc, cond);\n        if(result != 0) return result;\n        return\
    \ search_left_(node[id].l, a, l, m, acc, cond);\n    }\n\n    int make_node(const\
    \ T &v, int l, int r){\n        node.push_back({v, l, r});\n        return node.size()-1;\n\
    \    }\n\n    int build(int l, int r, const vector<T> &v){\n        if(l+1 ==\
    \ r) return make_node(v[l], -1, -1);\n        int m = (l+r)>>1;\n        int ll\
    \ = build(l, m, v), rr = build(m, r, v);\n        return make_node(M::f(node[ll].val,\
    \ node[rr].val), ll, rr);\n    }\n\n    int update_(int id, int k, const T &x,\
    \ int l, int r){\n        if(l+1 == r) return make_node(x, -1, -1);\n        int\
    \ m = (l+r)>>1;\n        int ll = node[id].l, rr = node[id].r;\n        if(k <\
    \ m) ll = update_(ll, k, x, l, m);\n        else rr = update_(rr, k, x, m, r);\n\
    \        return make_node(M::f(node[ll].val, node[rr].val), ll, rr);\n    }\n\n\
    \    int add_(int id, int k, const T &x, int l, int r){\n        if(l+1 == r)\
    \ return make_node(M::f(node[id].val, x), -1, -1);\n        int m = (l+r)>>1;\n\
    \        int ll = node[id].l, rr = node[id].r;\n        if(k < m) ll = add_(ll,\
    \ k, x, l, m);\n        else rr = add_(rr, k, x, m, r);\n        return make_node(M::f(node[ll].val,\
    \ node[rr].val), ll, rr);\n    }\n\n    T query_(int id, int a, int b, int l,\
    \ int r) const {\n        if(r <= a || b <= l) return M::e();\n        if(a <=\
    \ l && r <= b) return node[id].val;\n        int m = (l+r)>>1;\n        return\
    \ M::f(query_(node[id].l, a, b, l, m), query_(node[id].r, a, b, m, r));\n    }\n\
    };\n\n/*\nstruct Monoid{\n    using T = long long;\n    static T f(T a, T b) {\
    \ return a + b; }\n    static T e() { return 0; }\n};\n*/\n\n/**\n * @brief \u6C38\
    \u7D9A\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Persistent Segment Tree)\n */\n"
  code: "template <class M>\nstruct PersistentSegmentTree{\n    using T = typename\
    \ M::T;\n    struct Node{\n        T val;\n        int l, r;\n    };\n\n    int\
    \ n{};\n    vector<Node> node;\n    vector<int> root;\n\n    explicit PersistentSegmentTree(int\
    \ n): n(n){\n        node.push_back({M::e(), 0, 0});\n        root.push_back(0);\n\
    \    }\n    explicit PersistentSegmentTree(const vector<T> &v): n(v.size()){\n\
    \        if(n == 0){\n            node.push_back({M::e(), -1, -1});\n        \
    \    root.push_back(0);\n        }else{\n            root.push_back(build(0, n,\
    \ v));\n        }\n    }\n\n    int latest_version() const { return root.size()-1;\
    \ }\n    int versions() const { return root.size(); }\n\n    int update(int t,\
    \ int k, const T &x){\n        if(n == 0){\n            root.push_back(root[t]);\n\
    \            return latest_version();\n        }\n        root.push_back(update_(root[t],\
    \ k, x, 0, n));\n        return latest_version();\n    }\n    int update(int k,\
    \ const T &x){ return update(latest_version(), k, x); }\n\n    int add(int t,\
    \ int k, const T &x){\n        if(n == 0){\n            root.push_back(root[t]);\n\
    \            return latest_version();\n        }\n        root.push_back(add_(root[t],\
    \ k, x, 0, n));\n        return latest_version();\n    }\n    int add(int k, const\
    \ T &x){ return add(latest_version(), k, x); }\n\n    T query(int t, int a, int\
    \ b) const {\n        if(n == 0 || b <= a) return M::e();\n        return query_(root[t],\
    \ a, b, 0, n);\n    }\n    T query(int a, int b) const { return query(latest_version(),\
    \ a, b); }\n\n    T get(int t, int k) const { return query(t, k, k+1); }\n   \
    \ T operator[](const int &k) const { return get(latest_version(), k); }\n\n  \
    \  template<class F>\n    int search_right(int t, int l, F cond) const {\n   \
    \     T acc = M::e();\n        return search_right_(root[t], l, 0, n, acc, cond);\n\
    \    }\n    template<class F>\n    int search_right(int l, F cond) const {\n \
    \       return search_right(latest_version(), l, move(cond));\n    }\n\n    template<class\
    \ F>\n    int search_left(int t, int r, F cond) const {\n        T acc = M::e();\n\
    \        return search_left_(root[t], r, 0, n, acc, cond);\n    }\n    template<class\
    \ F>\n    int search_left(int r, F cond) const {\n        return search_left(latest_version(),\
    \ r, move(cond));\n    }\n\nprivate:\n    template<class F>\n    int search_right_(int\
    \ id, int a, int l, int r, T &acc, F &cond) const {\n        if(r <= a) return\
    \ n;\n        if(a <= l){\n            T next = M::f(acc, node[id].val);\n   \
    \         if(cond(next)){\n                acc = move(next);\n               \
    \ return n;\n            }\n            if(r-l == 1) return l;\n        }\n  \
    \      int m = l + ((r-l)>>1);\n        int result = search_right_(node[id].l,\
    \ a, l, m, acc, cond);\n        if(result != n) return result;\n        return\
    \ search_right_(node[id].r, a, m, r, acc, cond);\n    }\n\n    template<class\
    \ F>\n    int search_left_(int id, int a, int l, int r, T &acc, F &cond) const\
    \ {\n        if(a <= l) return 0;\n        if(r <= a){\n            T next = M::f(node[id].val,\
    \ acc);\n            if(cond(next)){\n                acc = move(next);\n    \
    \            return 0;\n            }\n            if(r-l == 1) return r;\n  \
    \      }\n        int m = l + ((r-l)>>1);\n        int result = search_left_(node[id].r,\
    \ a, m, r, acc, cond);\n        if(result != 0) return result;\n        return\
    \ search_left_(node[id].l, a, l, m, acc, cond);\n    }\n\n    int make_node(const\
    \ T &v, int l, int r){\n        node.push_back({v, l, r});\n        return node.size()-1;\n\
    \    }\n\n    int build(int l, int r, const vector<T> &v){\n        if(l+1 ==\
    \ r) return make_node(v[l], -1, -1);\n        int m = (l+r)>>1;\n        int ll\
    \ = build(l, m, v), rr = build(m, r, v);\n        return make_node(M::f(node[ll].val,\
    \ node[rr].val), ll, rr);\n    }\n\n    int update_(int id, int k, const T &x,\
    \ int l, int r){\n        if(l+1 == r) return make_node(x, -1, -1);\n        int\
    \ m = (l+r)>>1;\n        int ll = node[id].l, rr = node[id].r;\n        if(k <\
    \ m) ll = update_(ll, k, x, l, m);\n        else rr = update_(rr, k, x, m, r);\n\
    \        return make_node(M::f(node[ll].val, node[rr].val), ll, rr);\n    }\n\n\
    \    int add_(int id, int k, const T &x, int l, int r){\n        if(l+1 == r)\
    \ return make_node(M::f(node[id].val, x), -1, -1);\n        int m = (l+r)>>1;\n\
    \        int ll = node[id].l, rr = node[id].r;\n        if(k < m) ll = add_(ll,\
    \ k, x, l, m);\n        else rr = add_(rr, k, x, m, r);\n        return make_node(M::f(node[ll].val,\
    \ node[rr].val), ll, rr);\n    }\n\n    T query_(int id, int a, int b, int l,\
    \ int r) const {\n        if(r <= a || b <= l) return M::e();\n        if(a <=\
    \ l && r <= b) return node[id].val;\n        int m = (l+r)>>1;\n        return\
    \ M::f(query_(node[id].l, a, b, l, m), query_(node[id].r, a, b, m, r));\n    }\n\
    };\n\n/*\nstruct Monoid{\n    using T = long long;\n    static T f(T a, T b) {\
    \ return a + b; }\n    static T e() { return 0; }\n};\n*/\n\n/**\n * @brief \u6C38\
    \u7D9A\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Persistent Segment Tree)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/segmenttree/persistent_segtree.cpp
  requiredBy: []
  timestamp: '2026-10-18 00:37:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_persistent_segtree.test.cpp
  - test/yosupo_point_add_range_sum_persistent.test.cpp
date: 2026-03-08
documentation_of: datastructure/segmenttree/persistent_segtree.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "\u6C38\u7D9A\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Persistent Segment Tree)"
---

## 説明
点更新ごとに新しいバージョンを作り、任意の過去のバージョンの区間積を求める。
更新前のバージョンはそのまま残る。

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
  バージョン `t` に対して半開区間 `[l, r)` の積を問い合わせる。空区間なら単位元を返す。最悪 $O(\log N)$
- `T get(int t, int k)`
  バージョン `t` の位置 `k` の値を返す。最悪 $O(\log N)$
- `int search_right(int t, int l, F cond) const`
  バージョン `t` で `cond(query(t, l, r))` を満たす最大の `r` を返す。最悪 $O(\log N)$
- `int search_left(int t, int r, F cond) const`
  バージョン `t` で `cond(query(t, l, r))` を満たす最小の `l` を返す。最悪 $O(\log N)$
- `int latest_version()` / `int versions()`
  最新のバージョン番号 / 保持しているバージョン数を返す。$O(1)$

## 使い方
`M` に `T`、二項演算 `f`、単位元 `e` を定義する。非可換モノイドも使える。
`update`、`add`、`query`、`search_right`、`search_left` はバージョン番号を省略すると最新のバージョンを使う。`seg[k]` は最新のバージョンの値を返す。
境界探索の `cond` は単位元で `true` とし、区間を伸ばすと `true` から `false` への変化が高々1回になるものを使う。探索の計算量は述語が $O(1)$ の場合である。
要素数が0の場合、更新は空の新しいバージョンを作り、区間積は単位元を返す。

## 実装上の補足
サイズ指定の構築では、単位元を持つ1ノードを未更新の全区間で共有する。
更新時だけ経路をコピーし、過去のバージョンと共有ノードは変更しない。
共有ノードの子は自分自身を指す。`node` と `root` は区間境界と組み合わせる内部表現であり、子リンクだけで辿る通常の木ではない。
境界探索は部分木の積を使って走査し、追加ノードを作らない。再帰の作業領域は $O(\log N)$。
