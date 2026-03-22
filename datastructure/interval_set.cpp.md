---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_predecessor_problem_interval_set.test.cpp
    title: test/yosupo_predecessor_problem_interval_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u533A\u9593\u96C6\u5408(Interval Set)"
    links: []
  bundledCode: "#line 1 \"datastructure/interval_set.cpp\"\ntemplate<class T, class\
    \ SumT = long long>\nclass IntervalSet {\npublic:\n    struct Interval {\n   \
    \     T l, r;\n    };\n\nprivate:\n    struct Compare {\n        using is_transparent\
    \ = void;\n\n        bool operator()(const Interval& a, const Interval& b) const\
    \ {\n            return a.l < b.l;\n        }\n        bool operator()(const Interval&\
    \ a, const T& x) const {\n            return a.l < x;\n        }\n        bool\
    \ operator()(const T& x, const Interval& a) const {\n            return x < a.l;\n\
    \        }\n    };\n\n    set<Interval, Compare> st_;\n    SumT total_ = 0;\n\n\
    \    static SumT seg_len(const Interval& seg) {\n        return static_cast<SumT>(seg.r)\
    \ - static_cast<SumT>(seg.l);\n    }\n\n    typename set<Interval, Compare>::const_iterator\
    \ find_interval_it(T x) const {\n        auto it = st_.upper_bound(x);\n     \
    \   if (it == st_.begin()) return st_.end();\n        --it;\n        if (it->l\
    \ <= x && x < it->r) return it;\n        return st_.end();\n    }\n\npublic:\n\
    \    using const_iterator = typename set<Interval, Compare>::const_iterator;\n\
    \n    IntervalSet() = default;\n\n    bool empty() const {\n        return st_.empty();\n\
    \    }\n\n    int size() const {\n        return (int)st_.size();\n    }\n\n \
    \   SumT total_length() const {\n        return total_;\n    }\n\n    const_iterator\
    \ begin() const {\n        return st_.begin();\n    }\n\n    const_iterator end()\
    \ const {\n        return st_.end();\n    }\n\n    vector<Interval> intervals()\
    \ const {\n        return vector<Interval>(st_.begin(), st_.end());\n    }\n\n\
    \    bool contains(T x) const {\n        return find_interval_it(x) != st_.end();\n\
    \    }\n\n    Interval find_interval(T x) const {\n        auto it = find_interval_it(x);\n\
    \        if (it == st_.end()) return {-1, -1};\n        return *it;\n    }\n\n\
    \    Interval insert(T l, T r) {\n        if (!(l < r)) return {l, l};\n\n   \
    \     auto it = st_.lower_bound(l);\n\n        if (it != st_.begin()) {\n    \
    \        auto pit = prev(it);\n            if (pit->r >= l) {\n              \
    \  l = min(l, pit->l);\n                r = max(r, pit->r);\n                total_\
    \ -= seg_len(*pit);\n                it = st_.erase(pit);\n            }\n   \
    \     }\n\n        while (it != st_.end() && it->l <= r) {\n            r = max(r,\
    \ it->r);\n            total_ -= seg_len(*it);\n            it = st_.erase(it);\n\
    \        }\n\n        auto new_it = st_.insert(it, {l, r});\n        total_ +=\
    \ static_cast<SumT>(r) - static_cast<SumT>(l);\n        return *new_it;\n    }\n\
    \n    SumT erase(T l, T r) {\n        if (!(l < r)) return 0;\n\n        SumT\
    \ removed = 0;\n        vector<Interval> add_back;\n\n        auto it = st_.lower_bound(l);\n\
    \        if (it != st_.begin()) --it;\n\n        while (it != st_.end() && it->l\
    \ < r) {\n            if (it->r <= l) {\n                ++it;\n             \
    \   continue;\n            }\n\n            Interval cur = *it;\n            it\
    \ = st_.erase(it);\n            total_ -= seg_len(cur);\n\n            T a = max(cur.l,\
    \ l);\n            T b = min(cur.r, r);\n            removed += static_cast<SumT>(b)\
    \ - static_cast<SumT>(a);\n\n            if (cur.l < l) add_back.push_back({cur.l,\
    \ l});\n            if (r < cur.r) add_back.push_back({r, cur.r});\n        }\n\
    \n        for (const auto& seg : add_back) {\n            st_.insert(seg);\n \
    \           total_ += seg_len(seg);\n        }\n\n        return removed;\n  \
    \  }\n\n    SumT covered_length(T l, T r) const {\n        if (!(l < r)) return\
    \ 0;\n\n        SumT res = 0;\n        auto it = st_.lower_bound(l);\n       \
    \ if (it != st_.begin()) --it;\n\n        while (it != st_.end() && it->l < r)\
    \ {\n            if (l < it->r) {\n                T a = max(l, it->l);\n    \
    \            T b = min(r, it->r);\n                if (a < b) {\n            \
    \        res += static_cast<SumT>(b) - static_cast<SumT>(a);\n               \
    \ }\n            }\n            ++it;\n        }\n        return res;\n    }\n\
    \n    T mex(T x) const {\n        auto it = find_interval_it(x);\n        if (it\
    \ == st_.end()) return x;\n        return it->r;\n    }\n\n    void clear() {\n\
    \        st_.clear();\n        total_ = 0;\n    }\n\n    Interval prev_interval(T\
    \ x) const {\n        auto it = st_.upper_bound(x);\n        if (it == st_.begin())\
    \ return {-1, -1};\n        --it;\n        return *it;\n    }\n\n    Interval\
    \ next_interval(T x) const {\n        auto fit = find_interval_it(x);\n      \
    \  if (fit != st_.end()) return *fit;\n\n        auto it = st_.lower_bound(x);\n\
    \        if (it == st_.end()) return {-1, -1};\n        return *it;\n    }\n};\n\
    \n/**\n * @brief \u533A\u9593\u96C6\u5408(Interval Set)\n */\n"
  code: "template<class T, class SumT = long long>\nclass IntervalSet {\npublic:\n\
    \    struct Interval {\n        T l, r;\n    };\n\nprivate:\n    struct Compare\
    \ {\n        using is_transparent = void;\n\n        bool operator()(const Interval&\
    \ a, const Interval& b) const {\n            return a.l < b.l;\n        }\n  \
    \      bool operator()(const Interval& a, const T& x) const {\n            return\
    \ a.l < x;\n        }\n        bool operator()(const T& x, const Interval& a)\
    \ const {\n            return x < a.l;\n        }\n    };\n\n    set<Interval,\
    \ Compare> st_;\n    SumT total_ = 0;\n\n    static SumT seg_len(const Interval&\
    \ seg) {\n        return static_cast<SumT>(seg.r) - static_cast<SumT>(seg.l);\n\
    \    }\n\n    typename set<Interval, Compare>::const_iterator find_interval_it(T\
    \ x) const {\n        auto it = st_.upper_bound(x);\n        if (it == st_.begin())\
    \ return st_.end();\n        --it;\n        if (it->l <= x && x < it->r) return\
    \ it;\n        return st_.end();\n    }\n\npublic:\n    using const_iterator =\
    \ typename set<Interval, Compare>::const_iterator;\n\n    IntervalSet() = default;\n\
    \n    bool empty() const {\n        return st_.empty();\n    }\n\n    int size()\
    \ const {\n        return (int)st_.size();\n    }\n\n    SumT total_length() const\
    \ {\n        return total_;\n    }\n\n    const_iterator begin() const {\n   \
    \     return st_.begin();\n    }\n\n    const_iterator end() const {\n       \
    \ return st_.end();\n    }\n\n    vector<Interval> intervals() const {\n     \
    \   return vector<Interval>(st_.begin(), st_.end());\n    }\n\n    bool contains(T\
    \ x) const {\n        return find_interval_it(x) != st_.end();\n    }\n\n    Interval\
    \ find_interval(T x) const {\n        auto it = find_interval_it(x);\n       \
    \ if (it == st_.end()) return {-1, -1};\n        return *it;\n    }\n\n    Interval\
    \ insert(T l, T r) {\n        if (!(l < r)) return {l, l};\n\n        auto it\
    \ = st_.lower_bound(l);\n\n        if (it != st_.begin()) {\n            auto\
    \ pit = prev(it);\n            if (pit->r >= l) {\n                l = min(l,\
    \ pit->l);\n                r = max(r, pit->r);\n                total_ -= seg_len(*pit);\n\
    \                it = st_.erase(pit);\n            }\n        }\n\n        while\
    \ (it != st_.end() && it->l <= r) {\n            r = max(r, it->r);\n        \
    \    total_ -= seg_len(*it);\n            it = st_.erase(it);\n        }\n\n \
    \       auto new_it = st_.insert(it, {l, r});\n        total_ += static_cast<SumT>(r)\
    \ - static_cast<SumT>(l);\n        return *new_it;\n    }\n\n    SumT erase(T\
    \ l, T r) {\n        if (!(l < r)) return 0;\n\n        SumT removed = 0;\n  \
    \      vector<Interval> add_back;\n\n        auto it = st_.lower_bound(l);\n \
    \       if (it != st_.begin()) --it;\n\n        while (it != st_.end() && it->l\
    \ < r) {\n            if (it->r <= l) {\n                ++it;\n             \
    \   continue;\n            }\n\n            Interval cur = *it;\n            it\
    \ = st_.erase(it);\n            total_ -= seg_len(cur);\n\n            T a = max(cur.l,\
    \ l);\n            T b = min(cur.r, r);\n            removed += static_cast<SumT>(b)\
    \ - static_cast<SumT>(a);\n\n            if (cur.l < l) add_back.push_back({cur.l,\
    \ l});\n            if (r < cur.r) add_back.push_back({r, cur.r});\n        }\n\
    \n        for (const auto& seg : add_back) {\n            st_.insert(seg);\n \
    \           total_ += seg_len(seg);\n        }\n\n        return removed;\n  \
    \  }\n\n    SumT covered_length(T l, T r) const {\n        if (!(l < r)) return\
    \ 0;\n\n        SumT res = 0;\n        auto it = st_.lower_bound(l);\n       \
    \ if (it != st_.begin()) --it;\n\n        while (it != st_.end() && it->l < r)\
    \ {\n            if (l < it->r) {\n                T a = max(l, it->l);\n    \
    \            T b = min(r, it->r);\n                if (a < b) {\n            \
    \        res += static_cast<SumT>(b) - static_cast<SumT>(a);\n               \
    \ }\n            }\n            ++it;\n        }\n        return res;\n    }\n\
    \n    T mex(T x) const {\n        auto it = find_interval_it(x);\n        if (it\
    \ == st_.end()) return x;\n        return it->r;\n    }\n\n    void clear() {\n\
    \        st_.clear();\n        total_ = 0;\n    }\n\n    Interval prev_interval(T\
    \ x) const {\n        auto it = st_.upper_bound(x);\n        if (it == st_.begin())\
    \ return {-1, -1};\n        --it;\n        return *it;\n    }\n\n    Interval\
    \ next_interval(T x) const {\n        auto fit = find_interval_it(x);\n      \
    \  if (fit != st_.end()) return *fit;\n\n        auto it = st_.lower_bound(x);\n\
    \        if (it == st_.end()) return {-1, -1};\n        return *it;\n    }\n};\n\
    \n/**\n * @brief \u533A\u9593\u96C6\u5408(Interval Set)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/interval_set.cpp
  requiredBy: []
  timestamp: '2026-03-22 12:10:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_predecessor_problem_interval_set.test.cpp
date: 2026-03-22
documentation_of: datastructure/interval_set.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "\u533A\u9593\u96C6\u5408(Interval Set)"
---

## 説明
半開区間 `[l, r)` の和集合を互いに素な区間列として管理する。
区間の追加・削除、被覆長、点を含む区間、mex、前後の区間取得を扱う。

## できること
- `IntervalSet<T, SumT> st`
  空の区間集合を作る
- `bool empty()`
  区間が 1 つもなければ `true`。$O(1)$
- `int size()`
  現在の区間数を返す。$O(1)$
- `SumT total_length()`
  和集合の全長を返す。$O(1)$
- `vector<Interval> intervals()`
  現在の区間列を左端昇順で返す。$O(N)$
- `bool contains(T x)`
  `x` を含むなら `true`。$O(\log N)$
- `Interval find_interval(T x)`
  `x` を含む区間を返す。無ければ `{-1, -1}`。$O(\log N)$
- `Interval insert(T l, T r)`
  `[l, r)` を追加して重なる区間も併合した結果の区間を返す。空区間なら `{l, l}`。触った区間数を $k$ として $O(k \log N)$
- `SumT erase(T l, T r)`
  `[l, r)` を削除し、実際に消えた長さを返す。空区間なら `0`。触った区間数を $k$ として $O(k \log N)$
- `SumT covered_length(T l, T r)`
  `[l, r)` と和集合の共通部分の長さを返す。空区間なら `0`。重なる区間数を $k$ として $O(k\log N)$
- `T mex(T x)`
  `x` 以上で和集合に含まれない最小値を返す。$O(\log N)$
- `Interval prev_interval(T x)`
  左端が `x` 以下で最大の区間を返す。無ければ `{-1, -1}`。$O(\log N)$
- `Interval next_interval(T x)`
  `x` を含む区間、無ければ左端が `x` 以上で最小の区間を返す。無ければ `{-1, -1}`。$O(\log N)$
- `void clear()`
  全区間を消す。$O(N)$

## 使い方
整数集合を連続部分ごとの区間に圧縮して持ちたいときに使う。
`insert` は隣接区間も併合するので、整数集合を `[x, x + 1)` の集まりとして表す用途にも向く。

```cpp
IntervalSet<int, long long> st;
st.insert(2, 5);
st.insert(7, 9);
st.erase(3, 8);
auto len = st.total_length();  // 3
auto mx = st.mex(2);           // 3
```

## 実装上の補足
- 内部では互いに素で左端昇順な区間を `set` で持つ
- `insert` は重なる区間と隣接区間をまとめて 1 区間にする
- `prev_interval` と `next_interval` の番兵に `{-1, -1}` を使うので、この 2 つは `T=-1` を表せる型で使う前提と考えるのが安全
