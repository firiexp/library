---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_top_kth.test.cpp
    title: test/yosupo_aplusb_top_kth.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E0A\u4F4DK\u500B\u3092\u7BA1\u7406\u3059\u308BTreap"
    links: []
  bundledCode: "#line 1 \"datastructure/top_kth.cpp\"\ntemplate<class T, class SumT\
    \ = long long, bool Largest = true>\nclass TopKTreap {\nprivate:\n    struct Node\
    \ {\n        T key;\n        int cnt;\n        int sz;\n        uint32_t pri;\n\
    \        SumT sum;\n        int l;\n        int r;\n\n        Node(const T& key_,\
    \ uint32_t pri_)\n            : key(key_), cnt(1), sz(1), pri(pri_), sum((SumT)key_),\
    \ l(-1), r(-1) {}\n    };\n\n    int root_ = -1;\n    int K_ = 0;\n    uint32_t\
    \ rng_ = 2463534242u;\n    vector<Node> nodes_;\n    vector<int> free_nodes_;\n\
    \n    static bool goes_left(const T& x, const T& key) {\n        if constexpr\
    \ (Largest) return x < key;\n        else return x > key;\n    }\n\n    int size(int\
    \ t) const {\n        return t == -1 ? 0 : nodes_[t].sz;\n    }\n\n    SumT subtree_sum(int\
    \ t) const {\n        return t == -1 ? SumT(0) : nodes_[t].sum;\n    }\n\n   \
    \ void pull(int t) {\n        if (t == -1) return;\n        Node& node = nodes_[t];\n\
    \        node.sz = node.cnt + size(node.l) + size(node.r);\n        node.sum =\
    \ subtree_sum(node.l) + subtree_sum(node.r) + (SumT)node.key * node.cnt;\n   \
    \ }\n\n    uint32_t next_rand() {\n        uint32_t x = rng_;\n        x ^= x\
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
    \        }\n\n        if (x == nodes_[t].key) {\n            ++nodes_[t].cnt;\n\
    \            pull(t);\n            return;\n        }\n\n        if (goes_left(x,\
    \ nodes_[t].key)) {\n            int child = nodes_[t].l;\n            insert(child,\
    \ x);\n            nodes_[t].l = child;\n            if (nodes_[nodes_[t].l].pri\
    \ > nodes_[t].pri) rotate_right(t);\n        } else {\n            int child =\
    \ nodes_[t].r;\n            insert(child, x);\n            nodes_[t].r = child;\n\
    \            if (nodes_[nodes_[t].r].pri > nodes_[t].pri) rotate_left(t);\n  \
    \      }\n        pull(t);\n    }\n\n    bool erase_one(int& t, const T& x) {\n\
    \        if (t == -1) return false;\n        bool ok = false;\n        if (goes_left(x,\
    \ nodes_[t].key)) {\n            int child = nodes_[t].l;\n            ok = erase_one(child,\
    \ x);\n            nodes_[t].l = child;\n        } else if (goes_left(nodes_[t].key,\
    \ x)) {\n            int child = nodes_[t].r;\n            ok = erase_one(child,\
    \ x);\n            nodes_[t].r = child;\n        } else {\n            ok = true;\n\
    \            if (nodes_[t].cnt > 1) {\n                --nodes_[t].cnt;\n    \
    \            pull(t);\n                return true;\n            }\n         \
    \   if (nodes_[t].l == -1 || nodes_[t].r == -1) {\n                int old = t;\n\
    \                t = (nodes_[old].l != -1 ? nodes_[old].l : nodes_[old].r);\n\
    \                recycle_node(old);\n                return true;\n          \
    \  }\n            if (nodes_[nodes_[t].l].pri > nodes_[nodes_[t].r].pri) {\n \
    \               rotate_right(t);\n                int child = nodes_[t].r;\n \
    \               ok = erase_one(child, x);\n                nodes_[t].r = child;\n\
    \            } else {\n                rotate_left(t);\n                int child\
    \ = nodes_[t].l;\n                ok = erase_one(child, x);\n                nodes_[t].l\
    \ = child;\n            }\n        }\n\n        if (t != -1) pull(t);\n      \
    \  return ok;\n    }\n\npublic:\n    explicit TopKTreap(int K = 0, uint32_t seed\
    \ = 2463534242u)\n        : root_(-1), K_(K), rng_(seed) {\n        assert(K >=\
    \ 0);\n        if (rng_ == 0) rng_ = 2463534242u;\n    }\n\n    TopKTreap(const\
    \ TopKTreap&) = delete;\n    TopKTreap& operator=(const TopKTreap&) = delete;\n\
    \n    void reserve(int capacity) {\n        assert(capacity >= 0);\n        nodes_.reserve(capacity);\n\
    \        free_nodes_.reserve(capacity);\n    }\n\n    int k() const {\n      \
    \  return K_;\n    }\n\n    void set_k(int new_k) {\n        assert(new_k >= 0);\n\
    \        K_ = new_k;\n    }\n\n    int size() const {\n        return size(root_);\n\
    \    }\n\n    bool empty() const {\n        return root_ == -1;\n    }\n\n   \
    \ SumT total_sum() const {\n        return subtree_sum(root_);\n    }\n\n    void\
    \ insert(const T& x) {\n        insert(root_, x);\n    }\n\n    bool erase_one(const\
    \ T& x) {\n        return erase_one(root_, x);\n    }\n\n    int count(const T&\
    \ x) const {\n        int t = root_;\n        while (t != -1) {\n            const\
    \ Node& node = nodes_[t];\n            if (x == node.key) return node.cnt;\n \
    \           t = goes_left(x, node.key) ? node.l : node.r;\n        }\n       \
    \ return 0;\n    }\n\n    bool contains(const T& x) const {\n        return count(x)\
    \ > 0;\n    }\n\n    T kth(int kth) const {\n        assert(1 <= kth && kth <=\
    \ size());\n\n        int t = root_;\n        while (t != -1) {\n            const\
    \ Node& node = nodes_[t];\n            int preferred_sz = size(node.r);\n    \
    \        if (kth <= preferred_sz) {\n                t = node.r;\n           \
    \ } else if (kth <= preferred_sz + node.cnt) {\n                return node.key;\n\
    \            } else {\n                kth -= preferred_sz + node.cnt;\n     \
    \           t = node.l;\n            }\n        }\n\n        assert(false);\n\
    \        return T();\n    }\n\n    bool has_kth() const {\n        return 1 <=\
    \ K_ && K_ <= size();\n    }\n\n    T kth() const {\n        assert(has_kth());\n\
    \        return kth(K_);\n    }\n\n    SumT sum_k(int k) const {\n        if (k\
    \ <= 0 || root_ == -1) return SumT(0);\n        if (k >= size()) return total_sum();\n\
    \        SumT res = 0;\n        int t = root_;\n        while (t != -1 && k >\
    \ 0) {\n            const Node& node = nodes_[t];\n            int preferred =\
    \ node.r;\n            int other = node.l;\n            int preferred_sz = size(preferred);\n\
    \            if (k <= preferred_sz) {\n                t = preferred;\n      \
    \          continue;\n            }\n            res += subtree_sum(preferred);\n\
    \            k -= preferred_sz;\n            int take = std::min(k, node.cnt);\n\
    \            res += (SumT)node.key * take;\n            k -= take;\n         \
    \   if (k == 0) break;\n            t = other;\n        }\n        return res;\n\
    \    }\n\n    SumT sum_topk() const {\n        return sum_k(K_);\n    }\n};\n\n\
    /**\n * @brief \u4E0A\u4F4DK\u500B\u3092\u7BA1\u7406\u3059\u308BTreap\n */\n"
  code: "template<class T, class SumT = long long, bool Largest = true>\nclass TopKTreap\
    \ {\nprivate:\n    struct Node {\n        T key;\n        int cnt;\n        int\
    \ sz;\n        uint32_t pri;\n        SumT sum;\n        int l;\n        int r;\n\
    \n        Node(const T& key_, uint32_t pri_)\n            : key(key_), cnt(1),\
    \ sz(1), pri(pri_), sum((SumT)key_), l(-1), r(-1) {}\n    };\n\n    int root_\
    \ = -1;\n    int K_ = 0;\n    uint32_t rng_ = 2463534242u;\n    vector<Node> nodes_;\n\
    \    vector<int> free_nodes_;\n\n    static bool goes_left(const T& x, const T&\
    \ key) {\n        if constexpr (Largest) return x < key;\n        else return\
    \ x > key;\n    }\n\n    int size(int t) const {\n        return t == -1 ? 0 :\
    \ nodes_[t].sz;\n    }\n\n    SumT subtree_sum(int t) const {\n        return\
    \ t == -1 ? SumT(0) : nodes_[t].sum;\n    }\n\n    void pull(int t) {\n      \
    \  if (t == -1) return;\n        Node& node = nodes_[t];\n        node.sz = node.cnt\
    \ + size(node.l) + size(node.r);\n        node.sum = subtree_sum(node.l) + subtree_sum(node.r)\
    \ + (SumT)node.key * node.cnt;\n    }\n\n    uint32_t next_rand() {\n        uint32_t\
    \ x = rng_;\n        x ^= x << 13;\n        x ^= x >> 17;\n        x ^= x << 5;\n\
    \        rng_ = x;\n        return x;\n    }\n\n    int make_node(const T& x)\
    \ {\n        uint32_t pri = next_rand();\n        if (!free_nodes_.empty()) {\n\
    \            int idx = free_nodes_.back();\n            free_nodes_.pop_back();\n\
    \            nodes_[idx] = Node(x, pri);\n            return idx;\n        }\n\
    \        nodes_.emplace_back(x, pri);\n        return (int)nodes_.size() - 1;\n\
    \    }\n\n    void recycle_node(int t) {\n        if (t != -1) free_nodes_.push_back(t);\n\
    \    }\n\n    void rotate_left(int& t) {\n        int r = nodes_[t].r;\n     \
    \   nodes_[t].r = nodes_[r].l;\n        nodes_[r].l = t;\n        pull(t);\n \
    \       pull(r);\n        t = r;\n    }\n\n    void rotate_right(int& t) {\n \
    \       int l = nodes_[t].l;\n        nodes_[t].l = nodes_[l].r;\n        nodes_[l].r\
    \ = t;\n        pull(t);\n        pull(l);\n        t = l;\n    }\n\n    void\
    \ insert(int& t, const T& x) {\n        if (t == -1) {\n            t = make_node(x);\n\
    \            return;\n        }\n\n        if (x == nodes_[t].key) {\n       \
    \     ++nodes_[t].cnt;\n            pull(t);\n            return;\n        }\n\
    \n        if (goes_left(x, nodes_[t].key)) {\n            int child = nodes_[t].l;\n\
    \            insert(child, x);\n            nodes_[t].l = child;\n           \
    \ if (nodes_[nodes_[t].l].pri > nodes_[t].pri) rotate_right(t);\n        } else\
    \ {\n            int child = nodes_[t].r;\n            insert(child, x);\n   \
    \         nodes_[t].r = child;\n            if (nodes_[nodes_[t].r].pri > nodes_[t].pri)\
    \ rotate_left(t);\n        }\n        pull(t);\n    }\n\n    bool erase_one(int&\
    \ t, const T& x) {\n        if (t == -1) return false;\n        bool ok = false;\n\
    \        if (goes_left(x, nodes_[t].key)) {\n            int child = nodes_[t].l;\n\
    \            ok = erase_one(child, x);\n            nodes_[t].l = child;\n   \
    \     } else if (goes_left(nodes_[t].key, x)) {\n            int child = nodes_[t].r;\n\
    \            ok = erase_one(child, x);\n            nodes_[t].r = child;\n   \
    \     } else {\n            ok = true;\n            if (nodes_[t].cnt > 1) {\n\
    \                --nodes_[t].cnt;\n                pull(t);\n                return\
    \ true;\n            }\n            if (nodes_[t].l == -1 || nodes_[t].r == -1)\
    \ {\n                int old = t;\n                t = (nodes_[old].l != -1 ?\
    \ nodes_[old].l : nodes_[old].r);\n                recycle_node(old);\n      \
    \          return true;\n            }\n            if (nodes_[nodes_[t].l].pri\
    \ > nodes_[nodes_[t].r].pri) {\n                rotate_right(t);\n           \
    \     int child = nodes_[t].r;\n                ok = erase_one(child, x);\n  \
    \              nodes_[t].r = child;\n            } else {\n                rotate_left(t);\n\
    \                int child = nodes_[t].l;\n                ok = erase_one(child,\
    \ x);\n                nodes_[t].l = child;\n            }\n        }\n\n    \
    \    if (t != -1) pull(t);\n        return ok;\n    }\n\npublic:\n    explicit\
    \ TopKTreap(int K = 0, uint32_t seed = 2463534242u)\n        : root_(-1), K_(K),\
    \ rng_(seed) {\n        assert(K >= 0);\n        if (rng_ == 0) rng_ = 2463534242u;\n\
    \    }\n\n    TopKTreap(const TopKTreap&) = delete;\n    TopKTreap& operator=(const\
    \ TopKTreap&) = delete;\n\n    void reserve(int capacity) {\n        assert(capacity\
    \ >= 0);\n        nodes_.reserve(capacity);\n        free_nodes_.reserve(capacity);\n\
    \    }\n\n    int k() const {\n        return K_;\n    }\n\n    void set_k(int\
    \ new_k) {\n        assert(new_k >= 0);\n        K_ = new_k;\n    }\n\n    int\
    \ size() const {\n        return size(root_);\n    }\n\n    bool empty() const\
    \ {\n        return root_ == -1;\n    }\n\n    SumT total_sum() const {\n    \
    \    return subtree_sum(root_);\n    }\n\n    void insert(const T& x) {\n    \
    \    insert(root_, x);\n    }\n\n    bool erase_one(const T& x) {\n        return\
    \ erase_one(root_, x);\n    }\n\n    int count(const T& x) const {\n        int\
    \ t = root_;\n        while (t != -1) {\n            const Node& node = nodes_[t];\n\
    \            if (x == node.key) return node.cnt;\n            t = goes_left(x,\
    \ node.key) ? node.l : node.r;\n        }\n        return 0;\n    }\n\n    bool\
    \ contains(const T& x) const {\n        return count(x) > 0;\n    }\n\n    T kth(int\
    \ kth) const {\n        assert(1 <= kth && kth <= size());\n\n        int t =\
    \ root_;\n        while (t != -1) {\n            const Node& node = nodes_[t];\n\
    \            int preferred_sz = size(node.r);\n            if (kth <= preferred_sz)\
    \ {\n                t = node.r;\n            } else if (kth <= preferred_sz +\
    \ node.cnt) {\n                return node.key;\n            } else {\n      \
    \          kth -= preferred_sz + node.cnt;\n                t = node.l;\n    \
    \        }\n        }\n\n        assert(false);\n        return T();\n    }\n\n\
    \    bool has_kth() const {\n        return 1 <= K_ && K_ <= size();\n    }\n\n\
    \    T kth() const {\n        assert(has_kth());\n        return kth(K_);\n  \
    \  }\n\n    SumT sum_k(int k) const {\n        if (k <= 0 || root_ == -1) return\
    \ SumT(0);\n        if (k >= size()) return total_sum();\n        SumT res = 0;\n\
    \        int t = root_;\n        while (t != -1 && k > 0) {\n            const\
    \ Node& node = nodes_[t];\n            int preferred = node.r;\n            int\
    \ other = node.l;\n            int preferred_sz = size(preferred);\n         \
    \   if (k <= preferred_sz) {\n                t = preferred;\n               \
    \ continue;\n            }\n            res += subtree_sum(preferred);\n     \
    \       k -= preferred_sz;\n            int take = std::min(k, node.cnt);\n  \
    \          res += (SumT)node.key * take;\n            k -= take;\n           \
    \ if (k == 0) break;\n            t = other;\n        }\n        return res;\n\
    \    }\n\n    SumT sum_topk() const {\n        return sum_k(K_);\n    }\n};\n\n\
    /**\n * @brief \u4E0A\u4F4DK\u500B\u3092\u7BA1\u7406\u3059\u308BTreap\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/top_kth.cpp
  requiredBy: []
  timestamp: '2026-03-23 22:54:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_top_kth.test.cpp
date: 2026-03-21
documentation_of: datastructure/top_kth.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "\u4E0A\u4F4DK\u500B\u3092\u7BA1\u7406\u3059\u308B\u30C7\u30FC\u30BF\u69CB\u9020\
  \ (Treap)"
---

## 説明
重複あり multiset を Treap で管理し、順序付きで先頭 `k` 個の値と総和を扱う。
`Largest = true` なら大きい順、`Largest = false` なら小さい順になる。
各操作は期待 $O(\log N)$。

## できること
- `TopKTreap<T, SumT, Largest> st(K = 0, seed = 2463534242u)`
  順序付き先頭 `K` 個を基準にする空 multiset を作る
- `void reserve(int capacity)`
  ノード領域を `capacity` 個ぶん事前確保する
- `int k() const`
  現在の基準 `K` を返す
- `void set_k(int new_k)`
  基準 `K` を `new_k` に変える
- `int size() const`
  要素数を返す。重複分も数える
- `bool empty() const`
  空なら `true`
- `SumT total_sum() const`
  全要素の総和を返す
- `void insert(const T& x)`
  `x` を 1 個追加する
- `bool erase_one(const T& x)`
  `x` を 1 個削除する。存在しなければ `false`
- `int count(const T& x) const`
  `x` の個数を返す
- `bool contains(const T& x) const`
  `x` を含むなら `true`
- `T kth(int kth) const`
  順序に従う `kth` 番目の値を返す。`1 <= kth <= size()` で使う
- `bool has_kth() const`
  事前に設定した `K` 番目の要素が存在するなら `true`
- `T kth() const`
  順序に従う `K` 番目の値を返す。`has_kth()` が `true` のときに使う
- `SumT sum_k(int k) const`
  順序に従う先頭 `k` 個の総和を返す。`k <= 0` なら `0`、`k >= size()` なら全要素和
- `SumT sum_topk() const`
  順序に従う先頭 `K` 個の総和を返す

## 使い方
`insert` / `erase_one` で multiset を更新し、`sum_topk()` や `kth()` を読む。
`K` を途中で変えたいときは `set_k(new_k)` を使う。

大きい方から `K` 個を使いたいときは `TopKTreap<long long, long long, true>`、小さい方から `K` 個を使いたいときは `TopKTreap<long long, long long, false>` のように作る。
