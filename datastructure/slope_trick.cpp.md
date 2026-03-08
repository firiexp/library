---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_many_aplusb_slope_trick.test.cpp
    title: test/yosupo_many_aplusb_slope_trick.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Slope Trick
    links: []
  bundledCode: "#line 1 \"datastructure/slope_trick.cpp\"\ntemplate<class T>\nstruct\
    \ SlopeTrick {\n    static constexpr T INF = numeric_limits<T>::max() / 4;\n\n\
    \    T min_f = 0;\n    priority_queue<T> L;\n    priority_queue<T, vector<T>,\
    \ greater<T>> R;\n    T add_l = 0, add_r = 0;\n\n    struct Query {\n        T\
    \ lx, rx, min_f;\n    };\n\nprivate:\n    void push_L(T a) { L.push(a - add_l);\
    \ }\n    void push_R(T a) { R.push(a - add_r); }\n    T top_L() const { return\
    \ L.empty() ? -INF : L.top() + add_l; }\n    T top_R() const { return R.empty()\
    \ ? INF : R.top() + add_r; }\n    T pop_L() {\n        T x = top_L();\n      \
    \  if (!L.empty()) L.pop();\n        return x;\n    }\n    T pop_R() {\n     \
    \   T x = top_R();\n        if (!R.empty()) R.pop();\n        return x;\n    }\n\
    \    size_t size() const { return L.size() + R.size(); }\n\npublic:\n    Query\
    \ query() const {\n        return {top_L(), top_R(), min_f};\n    }\n\n    void\
    \ add_all(T a) {\n        min_f += a;\n    }\n\n    void add_a_minus_x(T a) {\n\
    \        min_f += max<T>(0, a - top_R());\n        push_R(a);\n        push_L(pop_R());\n\
    \    }\n\n    void add_x_minus_a(T a) {\n        min_f += max<T>(0, top_L() -\
    \ a);\n        push_L(a);\n        push_R(pop_L());\n    }\n\n    void add_abs(T\
    \ a) {\n        add_a_minus_x(a);\n        add_x_minus_a(a);\n    }\n\n    void\
    \ clear_right() {\n        decltype(R){}.swap(R);\n    }\n\n    void clear_left()\
    \ {\n        decltype(L){}.swap(L);\n    }\n\n    void shift(T a, T b) {\n   \
    \     assert(a <= b);\n        add_l += a;\n        add_r += b;\n    }\n\n   \
    \ void shift(T a) {\n        shift(a, a);\n    }\n\n    T eval(T x) const {\n\
    \        T res = min_f;\n        auto lq = L;\n        auto rq = R;\n        while\
    \ (!lq.empty()) {\n            res += max<T>(0, lq.top() + add_l - x);\n     \
    \       lq.pop();\n        }\n        while (!rq.empty()) {\n            res +=\
    \ max<T>(0, x - (rq.top() + add_r));\n            rq.pop();\n        }\n     \
    \   return res;\n    }\n\n    void merge(SlopeTrick &st) {\n        if (st.size()\
    \ > size()) swap(*this, st);\n        while (!st.L.empty()) add_a_minus_x(st.pop_L());\n\
    \        while (!st.R.empty()) add_x_minus_a(st.pop_R());\n        min_f += st.min_f;\n\
    \    }\n};\n\n/**\n * @brief Slope Trick\n */\n"
  code: "template<class T>\nstruct SlopeTrick {\n    static constexpr T INF = numeric_limits<T>::max()\
    \ / 4;\n\n    T min_f = 0;\n    priority_queue<T> L;\n    priority_queue<T, vector<T>,\
    \ greater<T>> R;\n    T add_l = 0, add_r = 0;\n\n    struct Query {\n        T\
    \ lx, rx, min_f;\n    };\n\nprivate:\n    void push_L(T a) { L.push(a - add_l);\
    \ }\n    void push_R(T a) { R.push(a - add_r); }\n    T top_L() const { return\
    \ L.empty() ? -INF : L.top() + add_l; }\n    T top_R() const { return R.empty()\
    \ ? INF : R.top() + add_r; }\n    T pop_L() {\n        T x = top_L();\n      \
    \  if (!L.empty()) L.pop();\n        return x;\n    }\n    T pop_R() {\n     \
    \   T x = top_R();\n        if (!R.empty()) R.pop();\n        return x;\n    }\n\
    \    size_t size() const { return L.size() + R.size(); }\n\npublic:\n    Query\
    \ query() const {\n        return {top_L(), top_R(), min_f};\n    }\n\n    void\
    \ add_all(T a) {\n        min_f += a;\n    }\n\n    void add_a_minus_x(T a) {\n\
    \        min_f += max<T>(0, a - top_R());\n        push_R(a);\n        push_L(pop_R());\n\
    \    }\n\n    void add_x_minus_a(T a) {\n        min_f += max<T>(0, top_L() -\
    \ a);\n        push_L(a);\n        push_R(pop_L());\n    }\n\n    void add_abs(T\
    \ a) {\n        add_a_minus_x(a);\n        add_x_minus_a(a);\n    }\n\n    void\
    \ clear_right() {\n        decltype(R){}.swap(R);\n    }\n\n    void clear_left()\
    \ {\n        decltype(L){}.swap(L);\n    }\n\n    void shift(T a, T b) {\n   \
    \     assert(a <= b);\n        add_l += a;\n        add_r += b;\n    }\n\n   \
    \ void shift(T a) {\n        shift(a, a);\n    }\n\n    T eval(T x) const {\n\
    \        T res = min_f;\n        auto lq = L;\n        auto rq = R;\n        while\
    \ (!lq.empty()) {\n            res += max<T>(0, lq.top() + add_l - x);\n     \
    \       lq.pop();\n        }\n        while (!rq.empty()) {\n            res +=\
    \ max<T>(0, x - (rq.top() + add_r));\n            rq.pop();\n        }\n     \
    \   return res;\n    }\n\n    void merge(SlopeTrick &st) {\n        if (st.size()\
    \ > size()) swap(*this, st);\n        while (!st.L.empty()) add_a_minus_x(st.pop_L());\n\
    \        while (!st.R.empty()) add_x_minus_a(st.pop_R());\n        min_f += st.min_f;\n\
    \    }\n};\n\n/**\n * @brief Slope Trick\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/slope_trick.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_many_aplusb_slope_trick.test.cpp
date: 2026-03-08
documentation_of: datastructure/slope_trick.cpp
layout: post
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Slope Trick
---

## 説明
下に凸な区分線形関数を保ちながら、`max(a - x, 0)` や `max(x - a, 0)` の加算、平行移動、片側累積 min を扱う。
各操作は償却 `O(log N)`。

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
