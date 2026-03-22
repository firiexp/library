---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_dynamic_sequence_range_affine_range_sum.test.cpp
    title: test/yosupo_dynamic_sequence_range_affine_range_sum.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Implicit Treap
    links: []
  bundledCode: "#line 1 \"datastructure/implicit_treap.cpp\"\ntemplate <class M>\n\
    struct ImplicitTreap {\n    using T = typename M::T;\n    using L = typename M::L;\n\
    \n    struct Node {\n        int l, r, sz;\n        unsigned pri;\n        bool\
    \ rev, has_lazy;\n        T val, sum, rsum;\n        L lazy;\n\n        Node(unsigned\
    \ pri, const T &val)\n            : l(-1), r(-1), sz(1), pri(pri), rev(false),\
    \ has_lazy(false),\n              val(val), sum(val), rsum(val), lazy(M::l())\
    \ {}\n    };\n\n    int root;\n    vector<Node> nodes;\n    vector<int> free_nodes;\n\
    \    unsigned long long rng_state;\n\n    ImplicitTreap() : root(-1), rng_state(0x123456789abcdef0ull)\
    \ {}\n\n    explicit ImplicitTreap(const vector<T> &v) : ImplicitTreap() {\n \
    \       reserve((int)v.size());\n        build_linear(v);\n    }\n\n    int size()\
    \ const {\n        return root == -1 ? 0 : nodes[root].sz;\n    }\n\n    bool\
    \ empty() const {\n        return root == -1;\n    }\n\n    void reserve(int capacity)\
    \ {\n        nodes.reserve(capacity);\n        free_nodes.reserve(capacity);\n\
    \    }\n\n    T all_fold() const {\n        return root == -1 ? M::e() : nodes[root].sum;\n\
    \    }\n\n    void insert(int k, const T &x) {\n        auto [a, b] = split(root,\
    \ k);\n        root = merge(merge(a, new_node(x)), b);\n    }\n\n    void push_front(const\
    \ T &x) {\n        insert(0, x);\n    }\n\n    void push_back(const T &x) {\n\
    \        insert(size(), x);\n    }\n\n    T erase(int k) {\n        auto [a, bc]\
    \ = split(root, k);\n        auto [b, c] = split(bc, 1);\n        T res = nodes[b].val;\n\
    \        recycle_node(b);\n        root = merge(a, c);\n        return res;\n\
    \    }\n\n    T pop_front() {\n        return erase(0);\n    }\n\n    T pop_back()\
    \ {\n        return erase(size() - 1);\n    }\n\n    T get(int k) {\n        auto\
    \ [a, bc] = split(root, k);\n        auto [b, c] = split(bc, 1);\n        T res\
    \ = nodes[b].val;\n        root = merge(merge(a, b), c);\n        return res;\n\
    \    }\n\n    void set(int k, const T &x) {\n        auto [a, bc] = split(root,\
    \ k);\n        auto [b, c] = split(bc, 1);\n        Node &node = nodes[b];\n \
    \       node.val = x;\n        node.sum = x;\n        node.rsum = x;\n       \
    \ node.rev = false;\n        node.has_lazy = false;\n        pull(b);\n      \
    \  root = merge(merge(a, b), c);\n    }\n\n    void apply(int l, int r, const\
    \ L &x) {\n        auto [a, b, c] = split3(root, l, r);\n        apply_node(b,\
    \ x);\n        root = merge(merge(a, b), c);\n    }\n\n    void reverse(int l,\
    \ int r) {\n        auto [a, b, c] = split3(root, l, r);\n        toggle(b);\n\
    \        root = merge(merge(a, b), c);\n    }\n\n    T fold(int l, int r) {\n\
    \        auto [a, b, c] = split3(root, l, r);\n        T res = b == -1 ? M::e()\
    \ : nodes[b].sum;\n        root = merge(merge(a, b), c);\n        return res;\n\
    \    }\n\nprivate:\n    unsigned next_rand() {\n        rng_state ^= rng_state\
    \ << 7;\n        rng_state ^= rng_state >> 9;\n        return static_cast<unsigned>(rng_state);\n\
    \    }\n\n    int new_node(const T &x) {\n        unsigned pri = next_rand();\n\
    \        if (!free_nodes.empty()) {\n            int idx = free_nodes.back();\n\
    \            free_nodes.pop_back();\n            nodes[idx] = Node(pri, x);\n\
    \            return idx;\n        }\n        nodes.emplace_back(pri, x);\n   \
    \     return (int)nodes.size() - 1;\n    }\n\n    void recycle_node(int x) {\n\
    \        if (x != -1) free_nodes.push_back(x);\n    }\n\n    void build_linear(const\
    \ vector<T> &v) {\n        if (v.empty()) return;\n        vector<int> ids(v.size());\n\
    \        for (int i = 0; i < (int)v.size(); ++i) ids[i] = new_node(v[i]);\n\n\
    \        vector<int> st;\n        st.reserve(v.size());\n        for (int cur\
    \ : ids) {\n            int last = -1;\n            while (!st.empty() && nodes[st.back()].pri\
    \ > nodes[cur].pri) {\n                last = st.back();\n                st.pop_back();\n\
    \            }\n            nodes[cur].l = last;\n            if (!st.empty())\
    \ nodes[st.back()].r = cur;\n            st.push_back(cur);\n        }\n     \
    \   root = st.front();\n\n        vector<int> ord;\n        ord.reserve(v.size());\n\
    \        st.assign(1, root);\n        while (!st.empty()) {\n            int x\
    \ = st.back();\n            st.pop_back();\n            ord.push_back(x);\n  \
    \          if (nodes[x].l != -1) st.push_back(nodes[x].l);\n            if (nodes[x].r\
    \ != -1) st.push_back(nodes[x].r);\n        }\n        for (int i = (int)ord.size()\
    \ - 1; i >= 0; --i) pull(ord[i]);\n    }\n\n    void apply_node(int x, const L\
    \ &lazy) {\n        if (x == -1) return;\n        Node &node = nodes[x];\n   \
    \     node.val = M::g(node.val, lazy);\n        node.sum = M::g(node.sum, lazy);\n\
    \        node.rsum = M::g(node.rsum, lazy);\n        if (node.has_lazy) node.lazy\
    \ = M::h(node.lazy, lazy);\n        else {\n            node.lazy = lazy;\n  \
    \          node.has_lazy = true;\n        }\n    }\n\n    void toggle(int x) {\n\
    \        if (x == -1) return;\n        Node &node = nodes[x];\n        swap(node.l,\
    \ node.r);\n        swap(node.sum, node.rsum);\n        node.rev ^= 1;\n    }\n\
    \n    void push(int x) {\n        if (x == -1) return;\n        Node &node = nodes[x];\n\
    \        if (node.rev) {\n            toggle(node.l);\n            toggle(node.r);\n\
    \            node.rev = false;\n        }\n        if (node.has_lazy) {\n    \
    \        apply_node(node.l, node.lazy);\n            apply_node(node.r, node.lazy);\n\
    \            node.has_lazy = false;\n        }\n    }\n\n    void pull(int x)\
    \ {\n        Node &node = nodes[x];\n        node.sz = 1;\n        node.sum =\
    \ node.val;\n        node.rsum = node.val;\n        if (node.l != -1) {\n    \
    \        const Node &left = nodes[node.l];\n            node.sz += left.sz;\n\
    \            node.sum = M::f(left.sum, node.sum);\n            node.rsum = M::f(node.rsum,\
    \ left.rsum);\n        }\n        if (node.r != -1) {\n            const Node\
    \ &right = nodes[node.r];\n            node.sz += right.sz;\n            node.sum\
    \ = M::f(node.sum, right.sum);\n            node.rsum = M::f(right.rsum, node.rsum);\n\
    \        }\n    }\n\n    int merge(int a, int b) {\n        if (a == -1 || b ==\
    \ -1) return a == -1 ? b : a;\n        if (nodes[a].pri < nodes[b].pri) {\n  \
    \          push(a);\n            nodes[a].r = merge(nodes[a].r, b);\n        \
    \    pull(a);\n            return a;\n        }\n        push(b);\n        nodes[b].l\
    \ = merge(a, nodes[b].l);\n        pull(b);\n        return b;\n    }\n\n    pair<int,\
    \ int> split(int x, int k) {\n        if (x == -1) return {-1, -1};\n        push(x);\n\
    \        int left_size = nodes[x].l == -1 ? 0 : nodes[nodes[x].l].sz;\n      \
    \  if (k <= left_size) {\n            auto [a, b] = split(nodes[x].l, k);\n  \
    \          nodes[x].l = b;\n            pull(x);\n            return {a, x};\n\
    \        }\n        auto [a, b] = split(nodes[x].r, k - left_size - 1);\n    \
    \    nodes[x].r = a;\n        pull(x);\n        return {x, b};\n    }\n\n    tuple<int,\
    \ int, int> split3(int x, int l, int r) {\n        auto [a, bc] = split(x, l);\n\
    \        auto [b, c] = split(bc, r - l);\n        return {a, b, c};\n    }\n};\n\
    \n/**\n * @brief Implicit Treap\n */\n"
  code: "template <class M>\nstruct ImplicitTreap {\n    using T = typename M::T;\n\
    \    using L = typename M::L;\n\n    struct Node {\n        int l, r, sz;\n  \
    \      unsigned pri;\n        bool rev, has_lazy;\n        T val, sum, rsum;\n\
    \        L lazy;\n\n        Node(unsigned pri, const T &val)\n            : l(-1),\
    \ r(-1), sz(1), pri(pri), rev(false), has_lazy(false),\n              val(val),\
    \ sum(val), rsum(val), lazy(M::l()) {}\n    };\n\n    int root;\n    vector<Node>\
    \ nodes;\n    vector<int> free_nodes;\n    unsigned long long rng_state;\n\n \
    \   ImplicitTreap() : root(-1), rng_state(0x123456789abcdef0ull) {}\n\n    explicit\
    \ ImplicitTreap(const vector<T> &v) : ImplicitTreap() {\n        reserve((int)v.size());\n\
    \        build_linear(v);\n    }\n\n    int size() const {\n        return root\
    \ == -1 ? 0 : nodes[root].sz;\n    }\n\n    bool empty() const {\n        return\
    \ root == -1;\n    }\n\n    void reserve(int capacity) {\n        nodes.reserve(capacity);\n\
    \        free_nodes.reserve(capacity);\n    }\n\n    T all_fold() const {\n  \
    \      return root == -1 ? M::e() : nodes[root].sum;\n    }\n\n    void insert(int\
    \ k, const T &x) {\n        auto [a, b] = split(root, k);\n        root = merge(merge(a,\
    \ new_node(x)), b);\n    }\n\n    void push_front(const T &x) {\n        insert(0,\
    \ x);\n    }\n\n    void push_back(const T &x) {\n        insert(size(), x);\n\
    \    }\n\n    T erase(int k) {\n        auto [a, bc] = split(root, k);\n     \
    \   auto [b, c] = split(bc, 1);\n        T res = nodes[b].val;\n        recycle_node(b);\n\
    \        root = merge(a, c);\n        return res;\n    }\n\n    T pop_front()\
    \ {\n        return erase(0);\n    }\n\n    T pop_back() {\n        return erase(size()\
    \ - 1);\n    }\n\n    T get(int k) {\n        auto [a, bc] = split(root, k);\n\
    \        auto [b, c] = split(bc, 1);\n        T res = nodes[b].val;\n        root\
    \ = merge(merge(a, b), c);\n        return res;\n    }\n\n    void set(int k,\
    \ const T &x) {\n        auto [a, bc] = split(root, k);\n        auto [b, c] =\
    \ split(bc, 1);\n        Node &node = nodes[b];\n        node.val = x;\n     \
    \   node.sum = x;\n        node.rsum = x;\n        node.rev = false;\n       \
    \ node.has_lazy = false;\n        pull(b);\n        root = merge(merge(a, b),\
    \ c);\n    }\n\n    void apply(int l, int r, const L &x) {\n        auto [a, b,\
    \ c] = split3(root, l, r);\n        apply_node(b, x);\n        root = merge(merge(a,\
    \ b), c);\n    }\n\n    void reverse(int l, int r) {\n        auto [a, b, c] =\
    \ split3(root, l, r);\n        toggle(b);\n        root = merge(merge(a, b), c);\n\
    \    }\n\n    T fold(int l, int r) {\n        auto [a, b, c] = split3(root, l,\
    \ r);\n        T res = b == -1 ? M::e() : nodes[b].sum;\n        root = merge(merge(a,\
    \ b), c);\n        return res;\n    }\n\nprivate:\n    unsigned next_rand() {\n\
    \        rng_state ^= rng_state << 7;\n        rng_state ^= rng_state >> 9;\n\
    \        return static_cast<unsigned>(rng_state);\n    }\n\n    int new_node(const\
    \ T &x) {\n        unsigned pri = next_rand();\n        if (!free_nodes.empty())\
    \ {\n            int idx = free_nodes.back();\n            free_nodes.pop_back();\n\
    \            nodes[idx] = Node(pri, x);\n            return idx;\n        }\n\
    \        nodes.emplace_back(pri, x);\n        return (int)nodes.size() - 1;\n\
    \    }\n\n    void recycle_node(int x) {\n        if (x != -1) free_nodes.push_back(x);\n\
    \    }\n\n    void build_linear(const vector<T> &v) {\n        if (v.empty())\
    \ return;\n        vector<int> ids(v.size());\n        for (int i = 0; i < (int)v.size();\
    \ ++i) ids[i] = new_node(v[i]);\n\n        vector<int> st;\n        st.reserve(v.size());\n\
    \        for (int cur : ids) {\n            int last = -1;\n            while\
    \ (!st.empty() && nodes[st.back()].pri > nodes[cur].pri) {\n                last\
    \ = st.back();\n                st.pop_back();\n            }\n            nodes[cur].l\
    \ = last;\n            if (!st.empty()) nodes[st.back()].r = cur;\n          \
    \  st.push_back(cur);\n        }\n        root = st.front();\n\n        vector<int>\
    \ ord;\n        ord.reserve(v.size());\n        st.assign(1, root);\n        while\
    \ (!st.empty()) {\n            int x = st.back();\n            st.pop_back();\n\
    \            ord.push_back(x);\n            if (nodes[x].l != -1) st.push_back(nodes[x].l);\n\
    \            if (nodes[x].r != -1) st.push_back(nodes[x].r);\n        }\n    \
    \    for (int i = (int)ord.size() - 1; i >= 0; --i) pull(ord[i]);\n    }\n\n \
    \   void apply_node(int x, const L &lazy) {\n        if (x == -1) return;\n  \
    \      Node &node = nodes[x];\n        node.val = M::g(node.val, lazy);\n    \
    \    node.sum = M::g(node.sum, lazy);\n        node.rsum = M::g(node.rsum, lazy);\n\
    \        if (node.has_lazy) node.lazy = M::h(node.lazy, lazy);\n        else {\n\
    \            node.lazy = lazy;\n            node.has_lazy = true;\n        }\n\
    \    }\n\n    void toggle(int x) {\n        if (x == -1) return;\n        Node\
    \ &node = nodes[x];\n        swap(node.l, node.r);\n        swap(node.sum, node.rsum);\n\
    \        node.rev ^= 1;\n    }\n\n    void push(int x) {\n        if (x == -1)\
    \ return;\n        Node &node = nodes[x];\n        if (node.rev) {\n         \
    \   toggle(node.l);\n            toggle(node.r);\n            node.rev = false;\n\
    \        }\n        if (node.has_lazy) {\n            apply_node(node.l, node.lazy);\n\
    \            apply_node(node.r, node.lazy);\n            node.has_lazy = false;\n\
    \        }\n    }\n\n    void pull(int x) {\n        Node &node = nodes[x];\n\
    \        node.sz = 1;\n        node.sum = node.val;\n        node.rsum = node.val;\n\
    \        if (node.l != -1) {\n            const Node &left = nodes[node.l];\n\
    \            node.sz += left.sz;\n            node.sum = M::f(left.sum, node.sum);\n\
    \            node.rsum = M::f(node.rsum, left.rsum);\n        }\n        if (node.r\
    \ != -1) {\n            const Node &right = nodes[node.r];\n            node.sz\
    \ += right.sz;\n            node.sum = M::f(node.sum, right.sum);\n          \
    \  node.rsum = M::f(right.rsum, node.rsum);\n        }\n    }\n\n    int merge(int\
    \ a, int b) {\n        if (a == -1 || b == -1) return a == -1 ? b : a;\n     \
    \   if (nodes[a].pri < nodes[b].pri) {\n            push(a);\n            nodes[a].r\
    \ = merge(nodes[a].r, b);\n            pull(a);\n            return a;\n     \
    \   }\n        push(b);\n        nodes[b].l = merge(a, nodes[b].l);\n        pull(b);\n\
    \        return b;\n    }\n\n    pair<int, int> split(int x, int k) {\n      \
    \  if (x == -1) return {-1, -1};\n        push(x);\n        int left_size = nodes[x].l\
    \ == -1 ? 0 : nodes[nodes[x].l].sz;\n        if (k <= left_size) {\n         \
    \   auto [a, b] = split(nodes[x].l, k);\n            nodes[x].l = b;\n       \
    \     pull(x);\n            return {a, x};\n        }\n        auto [a, b] = split(nodes[x].r,\
    \ k - left_size - 1);\n        nodes[x].r = a;\n        pull(x);\n        return\
    \ {x, b};\n    }\n\n    tuple<int, int, int> split3(int x, int l, int r) {\n \
    \       auto [a, bc] = split(x, l);\n        auto [b, c] = split(bc, r - l);\n\
    \        return {a, b, c};\n    }\n};\n\n/**\n * @brief Implicit Treap\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/implicit_treap.cpp
  requiredBy: []
  timestamp: '2026-03-13 22:51:48+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_dynamic_sequence_range_affine_range_sum.test.cpp
date: 2026-03-12
documentation_of: datastructure/implicit_treap.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Implicit Treap
---

## 説明
列を持つ implicit treap である。
挿入、削除、区間反転、区間作用、区間集約を期待 $O(\log N)$ で扱う。

## できること
- `ImplicitTreap<M> tr`
  空列を作る
- `ImplicitTreap<M> tr(v)`
  配列 `v` から列を作る
- `int size()`
  要素数を返す
- `bool empty()`
  空列なら `true`
- `void reserve(int capacity)`
  あらかじめノード領域を確保する
- `T all_fold()`
  列全体の集約値を返す。空なら `M::e()`
- `void insert(int k, T x)`
  `x` を位置 `k` の前に挿入する
- `void push_front(T x)`, `void push_back(T x)`
  先頭または末尾に挿入する
- `T erase(int k)`
  位置 `k` の要素を削除して返す
- `T pop_front()`, `T pop_back()`
  先頭または末尾を削除して返す
- `T get(int k)`
  位置 `k` の要素を返す
- `void set(int k, T x)`
  位置 `k` の要素を `x` に置き換える
- `void apply(int l, int r, L x)`
  半開区間 $[l, r)$ に作用素 `x` を適用する
- `void reverse(int l, int r)`
  半開区間 $[l, r)$ を反転する
- `T fold(int l, int r)`
  半開区間 $[l, r)$ の順序付き集約を返す

## 使い方
`M` は次を持てばよい。

```cpp
struct Monoid {
    using T = ...;
    using L = ...;
    static T f(T a, T b);
    static T g(T a, L x);
    static L h(L a, L b);
    static T e();
    static L l();
};
```

`f` は列順を保って畳み込まれる。
`reverse` を使うので、非可換モノイドでも `fold` の順序が壊れない。
`apply` を使うときは
$$
g(f(a, b), x) = f(g(a, x), g(b, x))
$$
を満たすように `T` を設計する。

## 実装上の補足
- 作用素の合成順は `h(古い作用, 新しい作用)` である
- 範囲和のように長さ依存の更新をしたいときは、`T` に長さを持たせて `g` で処理する
