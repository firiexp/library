---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_top_k_sum.test.cpp
    title: test/yosupo_aplusb_top_k_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E0A\u4F4DK\u548C\u7BA1\u7406"
    links: []
  bundledCode: "#line 1 \"datastructure/top_k_sum.cpp\"\ntemplate<class T, class SumT\
    \ = long long, bool Largest = true>\nclass TopKSum {\nprivate:\n    multiset<T>\
    \ selected_;\n    multiset<T> other_;\n    int K_ = 0;\n    int total_size_ =\
    \ 0;\n    SumT total_sum_ = 0;\n    SumT selected_sum_ = 0;\n\n    static bool\
    \ selected_before(const T& a, const T& b) {\n        if constexpr (Largest) return\
    \ a > b;\n        else return a < b;\n    }\n\n    typename multiset<T>::iterator\
    \ selected_boundary() {\n        assert(!selected_.empty());\n        if constexpr\
    \ (Largest) return selected_.begin();\n        else return prev(selected_.end());\n\
    \    }\n\n    typename multiset<T>::const_iterator selected_boundary() const {\n\
    \        assert(!selected_.empty());\n        if constexpr (Largest) return selected_.begin();\n\
    \        else return prev(selected_.end());\n    }\n\n    typename multiset<T>::iterator\
    \ other_best() {\n        assert(!other_.empty());\n        if constexpr (Largest)\
    \ return prev(other_.end());\n        else return other_.begin();\n    }\n\n \
    \   void move_selected_to_other() {\n        auto it = selected_boundary();\n\
    \        T x = *it;\n        selected_.erase(it);\n        selected_sum_ -= (SumT)x;\n\
    \        other_.insert(x);\n    }\n\n    void move_other_to_selected() {\n   \
    \     auto it = other_best();\n        T x = *it;\n        other_.erase(it);\n\
    \        selected_.insert(x);\n        selected_sum_ += (SumT)x;\n    }\n\n  \
    \  void rebalance() {\n        int target = min(K_, total_size_);\n        while\
    \ ((int)selected_.size() > target) move_selected_to_other();\n        while ((int)selected_.size()\
    \ < target) move_other_to_selected();\n        while (!selected_.empty() && !other_.empty())\
    \ {\n            auto sit = selected_boundary();\n            auto oit = other_best();\n\
    \            T s = *sit;\n            T o = *oit;\n            if (!selected_before(o,\
    \ s)) break;\n            selected_.erase(sit);\n            other_.erase(oit);\n\
    \            selected_.insert(o);\n            other_.insert(s);\n           \
    \ selected_sum_ += (SumT)o - (SumT)s;\n        }\n    }\n\npublic:\n    explicit\
    \ TopKSum(int K = 0) : K_(K) {\n        assert(K >= 0);\n    }\n\n    TopKSum(const\
    \ TopKSum&) = delete;\n    TopKSum& operator=(const TopKSum&) = delete;\n\n  \
    \  int k() const {\n        return K_;\n    }\n\n    void set_k(int new_k) {\n\
    \        assert(new_k >= 0);\n        K_ = new_k;\n        rebalance();\n    }\n\
    \n    int size() const {\n        return total_size_;\n    }\n\n    bool empty()\
    \ const {\n        return total_size_ == 0;\n    }\n\n    SumT total_sum() const\
    \ {\n        return total_sum_;\n    }\n\n    void insert(const T& x) {\n    \
    \    ++total_size_;\n        total_sum_ += (SumT)x;\n        if ((int)selected_.size()\
    \ < K_) {\n            selected_.insert(x);\n            selected_sum_ += (SumT)x;\n\
    \        } else if (selected_.empty()) {\n            other_.insert(x);\n    \
    \    } else {\n            T s = *selected_boundary();\n            if (selected_before(x,\
    \ s)) {\n                selected_.insert(x);\n                selected_sum_ +=\
    \ (SumT)x;\n            } else {\n                other_.insert(x);\n        \
    \    }\n        }\n        rebalance();\n    }\n\n    bool erase_one(const T&\
    \ x) {\n        auto it = selected_.find(x);\n        if (it != selected_.end())\
    \ {\n            selected_sum_ -= (SumT)x;\n            selected_.erase(it);\n\
    \        } else {\n            it = other_.find(x);\n            if (it == other_.end())\
    \ return false;\n            other_.erase(it);\n        }\n        --total_size_;\n\
    \        total_sum_ -= (SumT)x;\n        rebalance();\n        return true;\n\
    \    }\n\n    bool has_kth() const {\n        return 1 <= K_ && K_ <= total_size_;\n\
    \    }\n\n    T kth() const {\n        assert(has_kth());\n        return *selected_boundary();\n\
    \    }\n\n    SumT sum_topk() const {\n        return selected_sum_;\n    }\n\
    };\n\n/**\n * @brief \u4E0A\u4F4DK\u548C\u7BA1\u7406\n */\n"
  code: "template<class T, class SumT = long long, bool Largest = true>\nclass TopKSum\
    \ {\nprivate:\n    multiset<T> selected_;\n    multiset<T> other_;\n    int K_\
    \ = 0;\n    int total_size_ = 0;\n    SumT total_sum_ = 0;\n    SumT selected_sum_\
    \ = 0;\n\n    static bool selected_before(const T& a, const T& b) {\n        if\
    \ constexpr (Largest) return a > b;\n        else return a < b;\n    }\n\n   \
    \ typename multiset<T>::iterator selected_boundary() {\n        assert(!selected_.empty());\n\
    \        if constexpr (Largest) return selected_.begin();\n        else return\
    \ prev(selected_.end());\n    }\n\n    typename multiset<T>::const_iterator selected_boundary()\
    \ const {\n        assert(!selected_.empty());\n        if constexpr (Largest)\
    \ return selected_.begin();\n        else return prev(selected_.end());\n    }\n\
    \n    typename multiset<T>::iterator other_best() {\n        assert(!other_.empty());\n\
    \        if constexpr (Largest) return prev(other_.end());\n        else return\
    \ other_.begin();\n    }\n\n    void move_selected_to_other() {\n        auto\
    \ it = selected_boundary();\n        T x = *it;\n        selected_.erase(it);\n\
    \        selected_sum_ -= (SumT)x;\n        other_.insert(x);\n    }\n\n    void\
    \ move_other_to_selected() {\n        auto it = other_best();\n        T x = *it;\n\
    \        other_.erase(it);\n        selected_.insert(x);\n        selected_sum_\
    \ += (SumT)x;\n    }\n\n    void rebalance() {\n        int target = min(K_, total_size_);\n\
    \        while ((int)selected_.size() > target) move_selected_to_other();\n  \
    \      while ((int)selected_.size() < target) move_other_to_selected();\n    \
    \    while (!selected_.empty() && !other_.empty()) {\n            auto sit = selected_boundary();\n\
    \            auto oit = other_best();\n            T s = *sit;\n            T\
    \ o = *oit;\n            if (!selected_before(o, s)) break;\n            selected_.erase(sit);\n\
    \            other_.erase(oit);\n            selected_.insert(o);\n          \
    \  other_.insert(s);\n            selected_sum_ += (SumT)o - (SumT)s;\n      \
    \  }\n    }\n\npublic:\n    explicit TopKSum(int K = 0) : K_(K) {\n        assert(K\
    \ >= 0);\n    }\n\n    TopKSum(const TopKSum&) = delete;\n    TopKSum& operator=(const\
    \ TopKSum&) = delete;\n\n    int k() const {\n        return K_;\n    }\n\n  \
    \  void set_k(int new_k) {\n        assert(new_k >= 0);\n        K_ = new_k;\n\
    \        rebalance();\n    }\n\n    int size() const {\n        return total_size_;\n\
    \    }\n\n    bool empty() const {\n        return total_size_ == 0;\n    }\n\n\
    \    SumT total_sum() const {\n        return total_sum_;\n    }\n\n    void insert(const\
    \ T& x) {\n        ++total_size_;\n        total_sum_ += (SumT)x;\n        if\
    \ ((int)selected_.size() < K_) {\n            selected_.insert(x);\n         \
    \   selected_sum_ += (SumT)x;\n        } else if (selected_.empty()) {\n     \
    \       other_.insert(x);\n        } else {\n            T s = *selected_boundary();\n\
    \            if (selected_before(x, s)) {\n                selected_.insert(x);\n\
    \                selected_sum_ += (SumT)x;\n            } else {\n           \
    \     other_.insert(x);\n            }\n        }\n        rebalance();\n    }\n\
    \n    bool erase_one(const T& x) {\n        auto it = selected_.find(x);\n   \
    \     if (it != selected_.end()) {\n            selected_sum_ -= (SumT)x;\n  \
    \          selected_.erase(it);\n        } else {\n            it = other_.find(x);\n\
    \            if (it == other_.end()) return false;\n            other_.erase(it);\n\
    \        }\n        --total_size_;\n        total_sum_ -= (SumT)x;\n        rebalance();\n\
    \        return true;\n    }\n\n    bool has_kth() const {\n        return 1 <=\
    \ K_ && K_ <= total_size_;\n    }\n\n    T kth() const {\n        assert(has_kth());\n\
    \        return *selected_boundary();\n    }\n\n    SumT sum_topk() const {\n\
    \        return selected_sum_;\n    }\n};\n\n/**\n * @brief \u4E0A\u4F4DK\u548C\
    \u7BA1\u7406\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/top_k_sum.cpp
  requiredBy: []
  timestamp: '2026-03-21 14:23:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_top_k_sum.test.cpp
date: 2026-03-21
documentation_of: datastructure/top_k_sum.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "\u4E0A\u4F4DK\u500B\u306E\u548C\u3092\u7BA1\u7406\u3059\u308B\u30C7\u30FC\u30BF\
  \u69CB\u9020"
---

## 説明
重複あり multiset を 2 分割して管理し、順序に従う先頭 `K` 個の総和を扱う。
`Largest = true` なら大きい順、`Largest = false` なら小さい順になる。
`sum_topk()` は $O(1)$、`insert` / `erase_one` は $O(\log N)$。

## できること
- `TopKSum<T, SumT, Largest> ds(K = 0)`
  順序付き先頭 `K` 個を基準にする空 multiset を作る
- `int k() const`
  現在の基準 `K` を返す
- `void set_k(int new_k)`
  基準 `K` を `new_k` に変える。計算量は $O(|new\_k-K| \log N)$
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
- `bool has_kth() const`
  事前に設定した `K` 番目の要素が存在するなら `true`
- `T kth() const`
  順序に従う `K` 番目の値を返す。`has_kth()` が `true` のときに使う
- `SumT sum_topk() const`
  順序に従う先頭 `K` 個の総和を返す

## 使い方
`selected` に先頭 `K` 個、`other` に残りを入れる 2 分割を保って使う。
値の追加・削除をしながら `sum_topk()` を高頻度に読みたい用途に向く。

`TopKSum<long long, long long, false>` とすると小さい方から `K` 個の和、`TopKSum<long long, long long, true>` とすると大きい方から `K` 個の和を扱う。

## 実装上の補足
- `kth()` は `selected` 側の境界値を返す
- `kth(int)` や `sum_k(int)` のような汎用順位クエリは持たない
