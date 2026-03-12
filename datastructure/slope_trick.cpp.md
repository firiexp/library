---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Slope Trick
    links: []
  bundledCode: "#line 1 \"datastructure/slope_trick.cpp\"\ntemplate<class T>\nstruct\
    \ SlopeTrick {\n    static constexpr T INF = numeric_limits<T>::max() / 4;\n\n\
    \    T min_f = 0;\n    priority_queue<T> L;\n    priority_queue<T, vector<T>,\
    \ greater<T>> R;\n    T add_l = 0, add_r = 0;\n    mutable bool eval_cache_valid\
    \ = false;\n    mutable vector<T> eval_l, eval_r;\n    mutable vector<T> eval_l_sum,\
    \ eval_r_sum;\n\n    struct Query {\n        T lx, rx, min_f;\n    };\n\nprivate:\n\
    \    void push_L(T a) { L.push(a - add_l); }\n    void push_R(T a) { R.push(a\
    \ - add_r); }\n    T top_L() const { return L.empty() ? -INF : L.top() + add_l;\
    \ }\n    T top_R() const { return R.empty() ? INF : R.top() + add_r; }\n    T\
    \ pop_L() {\n        invalidate_eval_cache();\n        T x = top_L();\n      \
    \  if (!L.empty()) L.pop();\n        return x;\n    }\n    T pop_R() {\n     \
    \   invalidate_eval_cache();\n        T x = top_R();\n        if (!R.empty())\
    \ R.pop();\n        return x;\n    }\n    size_t size() const { return L.size()\
    \ + R.size(); }\n    void invalidate_eval_cache() {\n        eval_cache_valid\
    \ = false;\n    }\n    void build_eval_cache() const {\n        if (eval_cache_valid)\
    \ return;\n\n        auto lq = L;\n        auto rq = R;\n        eval_l.clear();\n\
    \        eval_r.clear();\n        eval_l.reserve(lq.size());\n        eval_r.reserve(rq.size());\n\
    \        while (!lq.empty()) {\n            eval_l.emplace_back(lq.top() + add_l);\n\
    \            lq.pop();\n        }\n        reverse(eval_l.begin(), eval_l.end());\n\
    \        while (!rq.empty()) {\n            eval_r.emplace_back(rq.top() + add_r);\n\
    \            rq.pop();\n        }\n\n        eval_l_sum.assign(eval_l.size() +\
    \ 1, 0);\n        for (int i = 0; i < (int)eval_l.size(); ++i) {\n           \
    \ eval_l_sum[i + 1] = eval_l_sum[i] + eval_l[i];\n        }\n        eval_r_sum.assign(eval_r.size()\
    \ + 1, 0);\n        for (int i = 0; i < (int)eval_r.size(); ++i) {\n         \
    \   eval_r_sum[i + 1] = eval_r_sum[i] + eval_r[i];\n        }\n        eval_cache_valid\
    \ = true;\n    }\n\npublic:\n    Query query() const {\n        return {top_L(),\
    \ top_R(), min_f};\n    }\n\n    void add_all(T a) {\n        min_f += a;\n  \
    \  }\n\n    void add_a_minus_x(T a) {\n        invalidate_eval_cache();\n    \
    \    min_f += max<T>(0, a - top_R());\n        push_R(a);\n        push_L(pop_R());\n\
    \    }\n\n    void add_x_minus_a(T a) {\n        invalidate_eval_cache();\n  \
    \      min_f += max<T>(0, top_L() - a);\n        push_L(a);\n        push_R(pop_L());\n\
    \    }\n\n    void add_abs(T a) {\n        add_a_minus_x(a);\n        add_x_minus_a(a);\n\
    \    }\n\n    void clear_right() {\n        decltype(R){}.swap(R);\n        invalidate_eval_cache();\n\
    \    }\n\n    void clear_left() {\n        decltype(L){}.swap(L);\n        invalidate_eval_cache();\n\
    \    }\n\n    void shift(T a, T b) {\n        assert(a <= b);\n        add_l +=\
    \ a;\n        add_r += b;\n        invalidate_eval_cache();\n    }\n\n    void\
    \ shift(T a) {\n        shift(a, a);\n    }\n\n    T eval(T x) const {\n     \
    \   build_eval_cache();\n        T res = min_f;\n        int li = upper_bound(eval_l.begin(),\
    \ eval_l.end(), x) - eval_l.begin();\n        res += eval_l_sum.back() - eval_l_sum[li]\
    \ - x * static_cast<T>(eval_l.size() - li);\n        int ri = lower_bound(eval_r.begin(),\
    \ eval_r.end(), x) - eval_r.begin();\n        res += x * static_cast<T>(ri) -\
    \ eval_r_sum[ri];\n        return res;\n    }\n\n    void merge(SlopeTrick &st)\
    \ {\n        if (st.size() > size()) swap(*this, st);\n        while (!st.L.empty())\
    \ add_a_minus_x(st.pop_L());\n        while (!st.R.empty()) add_x_minus_a(st.pop_R());\n\
    \        min_f += st.min_f;\n    }\n};\n\n/**\n * @brief Slope Trick\n */\n"
  code: "template<class T>\nstruct SlopeTrick {\n    static constexpr T INF = numeric_limits<T>::max()\
    \ / 4;\n\n    T min_f = 0;\n    priority_queue<T> L;\n    priority_queue<T, vector<T>,\
    \ greater<T>> R;\n    T add_l = 0, add_r = 0;\n    mutable bool eval_cache_valid\
    \ = false;\n    mutable vector<T> eval_l, eval_r;\n    mutable vector<T> eval_l_sum,\
    \ eval_r_sum;\n\n    struct Query {\n        T lx, rx, min_f;\n    };\n\nprivate:\n\
    \    void push_L(T a) { L.push(a - add_l); }\n    void push_R(T a) { R.push(a\
    \ - add_r); }\n    T top_L() const { return L.empty() ? -INF : L.top() + add_l;\
    \ }\n    T top_R() const { return R.empty() ? INF : R.top() + add_r; }\n    T\
    \ pop_L() {\n        invalidate_eval_cache();\n        T x = top_L();\n      \
    \  if (!L.empty()) L.pop();\n        return x;\n    }\n    T pop_R() {\n     \
    \   invalidate_eval_cache();\n        T x = top_R();\n        if (!R.empty())\
    \ R.pop();\n        return x;\n    }\n    size_t size() const { return L.size()\
    \ + R.size(); }\n    void invalidate_eval_cache() {\n        eval_cache_valid\
    \ = false;\n    }\n    void build_eval_cache() const {\n        if (eval_cache_valid)\
    \ return;\n\n        auto lq = L;\n        auto rq = R;\n        eval_l.clear();\n\
    \        eval_r.clear();\n        eval_l.reserve(lq.size());\n        eval_r.reserve(rq.size());\n\
    \        while (!lq.empty()) {\n            eval_l.emplace_back(lq.top() + add_l);\n\
    \            lq.pop();\n        }\n        reverse(eval_l.begin(), eval_l.end());\n\
    \        while (!rq.empty()) {\n            eval_r.emplace_back(rq.top() + add_r);\n\
    \            rq.pop();\n        }\n\n        eval_l_sum.assign(eval_l.size() +\
    \ 1, 0);\n        for (int i = 0; i < (int)eval_l.size(); ++i) {\n           \
    \ eval_l_sum[i + 1] = eval_l_sum[i] + eval_l[i];\n        }\n        eval_r_sum.assign(eval_r.size()\
    \ + 1, 0);\n        for (int i = 0; i < (int)eval_r.size(); ++i) {\n         \
    \   eval_r_sum[i + 1] = eval_r_sum[i] + eval_r[i];\n        }\n        eval_cache_valid\
    \ = true;\n    }\n\npublic:\n    Query query() const {\n        return {top_L(),\
    \ top_R(), min_f};\n    }\n\n    void add_all(T a) {\n        min_f += a;\n  \
    \  }\n\n    void add_a_minus_x(T a) {\n        invalidate_eval_cache();\n    \
    \    min_f += max<T>(0, a - top_R());\n        push_R(a);\n        push_L(pop_R());\n\
    \    }\n\n    void add_x_minus_a(T a) {\n        invalidate_eval_cache();\n  \
    \      min_f += max<T>(0, top_L() - a);\n        push_L(a);\n        push_R(pop_L());\n\
    \    }\n\n    void add_abs(T a) {\n        add_a_minus_x(a);\n        add_x_minus_a(a);\n\
    \    }\n\n    void clear_right() {\n        decltype(R){}.swap(R);\n        invalidate_eval_cache();\n\
    \    }\n\n    void clear_left() {\n        decltype(L){}.swap(L);\n        invalidate_eval_cache();\n\
    \    }\n\n    void shift(T a, T b) {\n        assert(a <= b);\n        add_l +=\
    \ a;\n        add_r += b;\n        invalidate_eval_cache();\n    }\n\n    void\
    \ shift(T a) {\n        shift(a, a);\n    }\n\n    T eval(T x) const {\n     \
    \   build_eval_cache();\n        T res = min_f;\n        int li = upper_bound(eval_l.begin(),\
    \ eval_l.end(), x) - eval_l.begin();\n        res += eval_l_sum.back() - eval_l_sum[li]\
    \ - x * static_cast<T>(eval_l.size() - li);\n        int ri = lower_bound(eval_r.begin(),\
    \ eval_r.end(), x) - eval_r.begin();\n        res += x * static_cast<T>(ri) -\
    \ eval_r_sum[ri];\n        return res;\n    }\n\n    void merge(SlopeTrick &st)\
    \ {\n        if (st.size() > size()) swap(*this, st);\n        while (!st.L.empty())\
    \ add_a_minus_x(st.pop_L());\n        while (!st.R.empty()) add_x_minus_a(st.pop_R());\n\
    \        min_f += st.min_f;\n    }\n};\n\n/**\n * @brief Slope Trick\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/slope_trick.cpp
  requiredBy: []
  timestamp: '2026-03-12 19:34:31+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
date: 2026-03-08
documentation_of: datastructure/slope_trick.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Slope Trick
---

## 説明
下に凸な区分線形関数を保ちながら、`max(a - x, 0)` や `max(x - a, 0)` の加算、平行移動、片側累積 min を扱う。
各操作は償却 $O(log N)$。

## できること
- `SlopeTrick<T> st`
  関数 `f(x) = 0` で初期化する
- `query()`
  最小値を取る区間 `[lx, rx]` と `min_f` を返す
- `add_all(a)`
  `f(x) += a`
- `add_a_minus_x(a)`
  `f(x) += max(a - x, 0)`
- `add_x_minus_a(a)`
  `f(x) += max(x - a, 0)`
- `add_abs(a)`
  `f(x) += |x - a|`
- `clear_right()`
  `f(x) = min_{y <= x} f(y)` にする
- `clear_left()`
  `f(x) = min_{y >= x} f(y)` にする
- `shift(a, b)`
  `f(x) = min_{x-b <= y <= x-a} f(y)` にする
- `shift(a)`
  `f(x) = f(x - a)` にする
- `eval(x)`
  現在の `f(x)` を返す
- `merge(other)`
  `f(x) += other(x)` を destructive にマージする

## 使い方
```cpp
SlopeTrick<long long> st;
st.add_abs(5);
st.add_x_minus_a(2);
auto q = st.query();
```

## 実装上の補足
左右の折れ点を priority queue で持つ典型実装である。
`merge` は `other` を破壊する。
`eval` は heap から実値列と prefix sum を遅延構築して使う。
更新直後の最初の `eval` は再構築が入るが、同じ状態への連続 `eval` は $O(\log N)$ で処理できる。
