---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_order_statistic_tree.test.cpp
    title: test/yosupo_aplusb_order_statistic_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_ordered_set.test.cpp
    title: test/yosupo_ordered_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u9806\u5E8F\u6728(Order Statistic Tree)"
    links: []
  bundledCode: "#line 1 \"datastructure/order_statistic_tree.cpp\"\ntemplate<class\
    \ T, class Compare = less<T>>\nclass OrderStatisticTree {\nprivate:\n    struct\
    \ Node {\n        T key;\n        int cnt;\n        int sz;\n        uint32_t\
    \ pri;\n        int l;\n        int r;\n\n        Node(const T& key_, uint32_t\
    \ pri_)\n            : key(key_), cnt(1), sz(1), pri(pri_), l(-1), r(-1) {}\n\
    \    };\n\n    int root_ = -1;\n    uint32_t rng_ = 2463534242u;\n    vector<Node>\
    \ nodes_;\n    vector<int> free_nodes_;\n    Compare comp_;\n\n    int size(int\
    \ t) const {\n        return t == -1 ? 0 : nodes_[t].sz;\n    }\n\n    bool equal_key(const\
    \ T& a, const T& b) const {\n        return !comp_(a, b) && !comp_(b, a);\n  \
    \  }\n\n    void pull(int t) {\n        if (t == -1) return;\n        Node& node\
    \ = nodes_[t];\n        node.sz = node.cnt + size(node.l) + size(node.r);\n  \
    \  }\n\n    uint32_t next_rand() {\n        uint32_t x = rng_;\n        x ^= x\
    \ << 13;\n        x ^= x >> 17;\n        x ^= x << 5;\n        rng_ = x;\n   \
    \     return x;\n    }\n\n    int make_node(const T& x) {\n        uint32_t pri\
    \ = next_rand();\n        if (!free_nodes_.empty()) {\n            int idx = free_nodes_.back();\n\
    \            free_nodes_.pop_back();\n            nodes_[idx] = Node(x, pri);\n\
    \            return idx;\n        }\n        nodes_.emplace_back(x, pri);\n  \
    \      return (int)nodes_.size() - 1;\n    }\n\n    void recycle_node(int t) {\n\
    \        if (t != -1) free_nodes_.push_back(t);\n    }\n\n    void rotate_left(int&\
    \ t) {\n        int r = nodes_[t].r;\n        nodes_[t].r = nodes_[r].l;\n   \
    \     nodes_[r].l = t;\n        pull(t);\n        pull(r);\n        t = r;\n \
    \   }\n\n    void rotate_right(int& t) {\n        int l = nodes_[t].l;\n     \
    \   nodes_[t].l = nodes_[l].r;\n        nodes_[l].r = t;\n        pull(t);\n \
    \       pull(l);\n        t = l;\n    }\n\n    void insert(int& t, const T& x)\
    \ {\n        if (t == -1) {\n            t = make_node(x);\n            return;\n\
    \        }\n\n        if (equal_key(x, nodes_[t].key)) {\n            ++nodes_[t].cnt;\n\
    \            pull(t);\n            return;\n        }\n\n        if (comp_(x,\
    \ nodes_[t].key)) {\n            int child = nodes_[t].l;\n            insert(child,\
    \ x);\n            nodes_[t].l = child;\n            if (nodes_[nodes_[t].l].pri\
    \ > nodes_[t].pri) rotate_right(t);\n        } else {\n            int child =\
    \ nodes_[t].r;\n            insert(child, x);\n            nodes_[t].r = child;\n\
    \            if (nodes_[nodes_[t].r].pri > nodes_[t].pri) rotate_left(t);\n  \
    \      }\n        pull(t);\n    }\n\n    bool erase_one(int& t, const T& x) {\n\
    \        if (t == -1) return false;\n\n        bool ok = false;\n        if (comp_(x,\
    \ nodes_[t].key)) {\n            int child = nodes_[t].l;\n            ok = erase_one(child,\
    \ x);\n            nodes_[t].l = child;\n        } else if (comp_(nodes_[t].key,\
    \ x)) {\n            int child = nodes_[t].r;\n            ok = erase_one(child,\
    \ x);\n            nodes_[t].r = child;\n        } else {\n            ok = true;\n\
    \            if (nodes_[t].cnt > 1) {\n                --nodes_[t].cnt;\n    \
    \            pull(t);\n                return true;\n            }\n         \
    \   if (nodes_[t].l == -1 || nodes_[t].r == -1) {\n                int old = t;\n\
    \                t = nodes_[old].l != -1 ? nodes_[old].l : nodes_[old].r;\n  \
    \              recycle_node(old);\n                return true;\n            }\n\
    \            if (nodes_[nodes_[t].l].pri > nodes_[nodes_[t].r].pri) {\n      \
    \          rotate_right(t);\n                int child = nodes_[t].r;\n      \
    \          ok = erase_one(child, x);\n                nodes_[t].r = child;\n \
    \           } else {\n                rotate_left(t);\n                int child\
    \ = nodes_[t].l;\n                ok = erase_one(child, x);\n                nodes_[t].l\
    \ = child;\n            }\n        }\n\n        if (t != -1) pull(t);\n      \
    \  return ok;\n    }\n\npublic:\n    explicit OrderStatisticTree(uint32_t seed\
    \ = 2463534242u, Compare comp = Compare())\n        : root_(-1), rng_(seed), comp_(comp)\
    \ {\n        if (rng_ == 0) rng_ = 2463534242u;\n    }\n\n    void reserve(int\
    \ capacity) {\n        assert(capacity >= 0);\n        nodes_.reserve(capacity);\n\
    \        free_nodes_.reserve(capacity);\n    }\n\n    int size() const {\n   \
    \     return size(root_);\n    }\n\n    bool empty() const {\n        return root_\
    \ == -1;\n    }\n\n    void insert(const T& x) {\n        insert(root_, x);\n\
    \    }\n\n    bool erase_one(const T& x) {\n        return erase_one(root_, x);\n\
    \    }\n\n    int count(const T& x) const {\n        int t = root_;\n        while\
    \ (t != -1) {\n            const Node& node = nodes_[t];\n            if (equal_key(x,\
    \ node.key)) return node.cnt;\n            t = comp_(x, node.key) ? node.l : node.r;\n\
    \        }\n        return 0;\n    }\n\n    bool contains(const T& x) const {\n\
    \        return count(x) > 0;\n    }\n\n    T find_by_order(int k) const {\n \
    \       assert(0 <= k && k < size());\n\n        int t = root_;\n        while\
    \ (true) {\n            const Node& node = nodes_[t];\n            int left_sz\
    \ = size(node.l);\n            if (k < left_sz) {\n                t = node.l;\n\
    \            } else if (k < left_sz + node.cnt) {\n                return node.key;\n\
    \            } else {\n                k -= left_sz + node.cnt;\n            \
    \    t = node.r;\n            }\n        }\n    }\n\n    int order_of_key(const\
    \ T& x) const {\n        int res = 0;\n        int t = root_;\n        while (t\
    \ != -1) {\n            const Node& node = nodes_[t];\n            if (comp_(node.key,\
    \ x)) {\n                res += size(node.l) + node.cnt;\n                t =\
    \ node.r;\n            } else {\n                t = node.l;\n            }\n\
    \        }\n        return res;\n    }\n};\n\n/**\n * @brief \u9806\u5E8F\u6728\
    (Order Statistic Tree)\n */\n"
  code: "template<class T, class Compare = less<T>>\nclass OrderStatisticTree {\n\
    private:\n    struct Node {\n        T key;\n        int cnt;\n        int sz;\n\
    \        uint32_t pri;\n        int l;\n        int r;\n\n        Node(const T&\
    \ key_, uint32_t pri_)\n            : key(key_), cnt(1), sz(1), pri(pri_), l(-1),\
    \ r(-1) {}\n    };\n\n    int root_ = -1;\n    uint32_t rng_ = 2463534242u;\n\
    \    vector<Node> nodes_;\n    vector<int> free_nodes_;\n    Compare comp_;\n\n\
    \    int size(int t) const {\n        return t == -1 ? 0 : nodes_[t].sz;\n   \
    \ }\n\n    bool equal_key(const T& a, const T& b) const {\n        return !comp_(a,\
    \ b) && !comp_(b, a);\n    }\n\n    void pull(int t) {\n        if (t == -1) return;\n\
    \        Node& node = nodes_[t];\n        node.sz = node.cnt + size(node.l) +\
    \ size(node.r);\n    }\n\n    uint32_t next_rand() {\n        uint32_t x = rng_;\n\
    \        x ^= x << 13;\n        x ^= x >> 17;\n        x ^= x << 5;\n        rng_\
    \ = x;\n        return x;\n    }\n\n    int make_node(const T& x) {\n        uint32_t\
    \ pri = next_rand();\n        if (!free_nodes_.empty()) {\n            int idx\
    \ = free_nodes_.back();\n            free_nodes_.pop_back();\n            nodes_[idx]\
    \ = Node(x, pri);\n            return idx;\n        }\n        nodes_.emplace_back(x,\
    \ pri);\n        return (int)nodes_.size() - 1;\n    }\n\n    void recycle_node(int\
    \ t) {\n        if (t != -1) free_nodes_.push_back(t);\n    }\n\n    void rotate_left(int&\
    \ t) {\n        int r = nodes_[t].r;\n        nodes_[t].r = nodes_[r].l;\n   \
    \     nodes_[r].l = t;\n        pull(t);\n        pull(r);\n        t = r;\n \
    \   }\n\n    void rotate_right(int& t) {\n        int l = nodes_[t].l;\n     \
    \   nodes_[t].l = nodes_[l].r;\n        nodes_[l].r = t;\n        pull(t);\n \
    \       pull(l);\n        t = l;\n    }\n\n    void insert(int& t, const T& x)\
    \ {\n        if (t == -1) {\n            t = make_node(x);\n            return;\n\
    \        }\n\n        if (equal_key(x, nodes_[t].key)) {\n            ++nodes_[t].cnt;\n\
    \            pull(t);\n            return;\n        }\n\n        if (comp_(x,\
    \ nodes_[t].key)) {\n            int child = nodes_[t].l;\n            insert(child,\
    \ x);\n            nodes_[t].l = child;\n            if (nodes_[nodes_[t].l].pri\
    \ > nodes_[t].pri) rotate_right(t);\n        } else {\n            int child =\
    \ nodes_[t].r;\n            insert(child, x);\n            nodes_[t].r = child;\n\
    \            if (nodes_[nodes_[t].r].pri > nodes_[t].pri) rotate_left(t);\n  \
    \      }\n        pull(t);\n    }\n\n    bool erase_one(int& t, const T& x) {\n\
    \        if (t == -1) return false;\n\n        bool ok = false;\n        if (comp_(x,\
    \ nodes_[t].key)) {\n            int child = nodes_[t].l;\n            ok = erase_one(child,\
    \ x);\n            nodes_[t].l = child;\n        } else if (comp_(nodes_[t].key,\
    \ x)) {\n            int child = nodes_[t].r;\n            ok = erase_one(child,\
    \ x);\n            nodes_[t].r = child;\n        } else {\n            ok = true;\n\
    \            if (nodes_[t].cnt > 1) {\n                --nodes_[t].cnt;\n    \
    \            pull(t);\n                return true;\n            }\n         \
    \   if (nodes_[t].l == -1 || nodes_[t].r == -1) {\n                int old = t;\n\
    \                t = nodes_[old].l != -1 ? nodes_[old].l : nodes_[old].r;\n  \
    \              recycle_node(old);\n                return true;\n            }\n\
    \            if (nodes_[nodes_[t].l].pri > nodes_[nodes_[t].r].pri) {\n      \
    \          rotate_right(t);\n                int child = nodes_[t].r;\n      \
    \          ok = erase_one(child, x);\n                nodes_[t].r = child;\n \
    \           } else {\n                rotate_left(t);\n                int child\
    \ = nodes_[t].l;\n                ok = erase_one(child, x);\n                nodes_[t].l\
    \ = child;\n            }\n        }\n\n        if (t != -1) pull(t);\n      \
    \  return ok;\n    }\n\npublic:\n    explicit OrderStatisticTree(uint32_t seed\
    \ = 2463534242u, Compare comp = Compare())\n        : root_(-1), rng_(seed), comp_(comp)\
    \ {\n        if (rng_ == 0) rng_ = 2463534242u;\n    }\n\n    void reserve(int\
    \ capacity) {\n        assert(capacity >= 0);\n        nodes_.reserve(capacity);\n\
    \        free_nodes_.reserve(capacity);\n    }\n\n    int size() const {\n   \
    \     return size(root_);\n    }\n\n    bool empty() const {\n        return root_\
    \ == -1;\n    }\n\n    void insert(const T& x) {\n        insert(root_, x);\n\
    \    }\n\n    bool erase_one(const T& x) {\n        return erase_one(root_, x);\n\
    \    }\n\n    int count(const T& x) const {\n        int t = root_;\n        while\
    \ (t != -1) {\n            const Node& node = nodes_[t];\n            if (equal_key(x,\
    \ node.key)) return node.cnt;\n            t = comp_(x, node.key) ? node.l : node.r;\n\
    \        }\n        return 0;\n    }\n\n    bool contains(const T& x) const {\n\
    \        return count(x) > 0;\n    }\n\n    T find_by_order(int k) const {\n \
    \       assert(0 <= k && k < size());\n\n        int t = root_;\n        while\
    \ (true) {\n            const Node& node = nodes_[t];\n            int left_sz\
    \ = size(node.l);\n            if (k < left_sz) {\n                t = node.l;\n\
    \            } else if (k < left_sz + node.cnt) {\n                return node.key;\n\
    \            } else {\n                k -= left_sz + node.cnt;\n            \
    \    t = node.r;\n            }\n        }\n    }\n\n    int order_of_key(const\
    \ T& x) const {\n        int res = 0;\n        int t = root_;\n        while (t\
    \ != -1) {\n            const Node& node = nodes_[t];\n            if (comp_(node.key,\
    \ x)) {\n                res += size(node.l) + node.cnt;\n                t =\
    \ node.r;\n            } else {\n                t = node.l;\n            }\n\
    \        }\n        return res;\n    }\n};\n\n/**\n * @brief \u9806\u5E8F\u6728\
    (Order Statistic Tree)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/order_statistic_tree.cpp
  requiredBy: []
  timestamp: '2026-07-11 20:39:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_ordered_set.test.cpp
  - test/yosupo_aplusb_order_statistic_tree.test.cpp
date: 2026-05-25
documentation_of: datastructure/order_statistic_tree.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "\u9806\u5E8F\u6728(Order Statistic Tree)"
---

## 説明
Treap で順序付き multiset を管理する。
`find_by_order` と `order_of_key` を使って、順位から値、値から順位を求める。
各操作は期待 $O(\log N)$。

## できること
- `OrderStatisticTree<T, Compare> st(seed = 2463534242u, comp = Compare())`
  空の順序統計木を作る。順序は `Compare` に従う
- `void reserve(int capacity)`
  ノード領域を `capacity` 個ぶん事前確保する
- `int size() const`
  要素数を返す。重複分も数える
- `bool empty() const`
  空なら `true`
- `void insert(T x)`
  `x` を 1 個追加する
- `bool erase_one(T x)`
  `x` を 1 個削除する。存在しなければ `false`
- `int count(T x) const`
  `x` の個数を返す。存在しなければ `0`
- `bool contains(T x) const`
  `x` を含むなら `true`
- `T find_by_order(int k) const`
  `0`-indexed で `k` 番目の値を返す。`0 <= k < size()` で使う
- `int order_of_key(T x) const`
  `Compare` の順序で `x` より前にある要素数を返す

## 使い方
`insert` / `erase_one` で集合を更新し、`find_by_order(k)` と `order_of_key(x)` で順位クエリを処理する。
同じ値を複数個入れると multiset として扱う。

```cpp
OrderStatisticTree<long long> st;
st.insert(5);
st.insert(1);
st.insert(5);

long long x = st.find_by_order(1); // 5
int c = st.order_of_key(5);        // 1
```

## 実装上の補足
`__gnu_pbds::tree` と違い、`find_by_order` は iterator ではなく値を返す。
重複を区別したいときは `OrderStatisticTree<pair<T, int>>` のように ID を持たせる。
`Compare = greater<T>` にすると、大きい順で順位を数える。
