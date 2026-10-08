---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_slope_trick.test.cpp
    title: test/yosupo_aplusb_slope_trick.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Slope Trick
    links: []
  bundledCode: "#line 1 \"datastructure/slope_trick.cpp\"\ntemplate<class T>\nstruct\
    \ SlopeTrick {\n    static constexpr T INF = numeric_limits<T>::max() / 4;\n \
    \   static constexpr bool raw_eval_cache = is_integral<T>::value && sizeof(T)\
    \ <= 8;\n    using EvalSum = conditional_t<raw_eval_cache, __int128, T>;\n\n \
    \   T min_f = 0;\n    priority_queue<T> L;\n    priority_queue<T, vector<T>, greater<T>>\
    \ R;\n    T add_l = 0, add_r = 0;\n    mutable bool eval_cache_valid = false;\n\
    \    mutable vector<T> eval_l, eval_r;\n    mutable vector<EvalSum> eval_l_sum,\
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
    \        while (!lq.empty()) {\n            if constexpr (raw_eval_cache) eval_l.emplace_back(lq.top());\n\
    \            else eval_l.emplace_back(lq.top() + add_l);\n            lq.pop();\n\
    \        }\n        reverse(eval_l.begin(), eval_l.end());\n        while (!rq.empty())\
    \ {\n            if constexpr (raw_eval_cache) eval_r.emplace_back(rq.top());\n\
    \            else eval_r.emplace_back(rq.top() + add_r);\n            rq.pop();\n\
    \        }\n\n        eval_l_sum.assign(eval_l.size() + 1, 0);\n        for (int\
    \ i = 0; i < (int)eval_l.size(); ++i) {\n            eval_l_sum[i + 1] = eval_l_sum[i]\
    \ + eval_l[i];\n        }\n        eval_r_sum.assign(eval_r.size() + 1, 0);\n\
    \        for (int i = 0; i < (int)eval_r.size(); ++i) {\n            eval_r_sum[i\
    \ + 1] = eval_r_sum[i] + eval_r[i];\n        }\n        eval_cache_valid = true;\n\
    \    }\n\npublic:\n    Query query() const {\n        return {top_L(), top_R(),\
    \ min_f};\n    }\n\n    void add_all(T a) {\n        min_f += a;\n    }\n\n  \
    \  void add_a_minus_x(T a) {\n        invalidate_eval_cache();\n        min_f\
    \ += max<T>(0, a - top_R());\n        push_R(a);\n        push_L(pop_R());\n \
    \   }\n\n    void add_x_minus_a(T a) {\n        invalidate_eval_cache();\n   \
    \     min_f += max<T>(0, top_L() - a);\n        push_L(a);\n        push_R(pop_L());\n\
    \    }\n\n    void add_abs(T a) {\n        add_a_minus_x(a);\n        add_x_minus_a(a);\n\
    \    }\n\n    void clear_right() {\n        decltype(R){}.swap(R);\n        invalidate_eval_cache();\n\
    \    }\n\n    void clear_left() {\n        decltype(L){}.swap(L);\n        invalidate_eval_cache();\n\
    \    }\n\n    void shift(T a, T b) {\n        assert(a <= b);\n        add_l +=\
    \ a;\n        add_r += b;\n        if constexpr (!raw_eval_cache) invalidate_eval_cache();\n\
    \    }\n\n    void shift(T a) {\n        shift(a, a);\n    }\n\n    T eval(T x)\
    \ const {\n        build_eval_cache();\n        EvalSum lx = x, rx = x;\n    \
    \    if constexpr (raw_eval_cache) {\n            lx -= static_cast<EvalSum>(add_l);\n\
    \            rx -= static_cast<EvalSum>(add_r);\n        }\n        EvalSum res\
    \ = min_f;\n        int li = upper_bound(eval_l.begin(), eval_l.end(), lx) - eval_l.begin();\n\
    \        res += eval_l_sum.back() - eval_l_sum[li] - lx * static_cast<EvalSum>(eval_l.size()\
    \ - li);\n        int ri = lower_bound(eval_r.begin(), eval_r.end(), rx) - eval_r.begin();\n\
    \        res += rx * static_cast<EvalSum>(ri) - eval_r_sum[ri];\n        return\
    \ static_cast<T>(res);\n    }\n\n    void merge(SlopeTrick &st) {\n        if\
    \ (st.size() > size()) swap(*this, st);\n        while (!st.L.empty()) add_a_minus_x(st.pop_L());\n\
    \        while (!st.R.empty()) add_x_minus_a(st.pop_R());\n        min_f += st.min_f;\n\
    \    }\n};\n\n/**\n * @brief Slope Trick\n */\n"
  code: "template<class T>\nstruct SlopeTrick {\n    static constexpr T INF = numeric_limits<T>::max()\
    \ / 4;\n    static constexpr bool raw_eval_cache = is_integral<T>::value && sizeof(T)\
    \ <= 8;\n    using EvalSum = conditional_t<raw_eval_cache, __int128, T>;\n\n \
    \   T min_f = 0;\n    priority_queue<T> L;\n    priority_queue<T, vector<T>, greater<T>>\
    \ R;\n    T add_l = 0, add_r = 0;\n    mutable bool eval_cache_valid = false;\n\
    \    mutable vector<T> eval_l, eval_r;\n    mutable vector<EvalSum> eval_l_sum,\
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
    \        while (!lq.empty()) {\n            if constexpr (raw_eval_cache) eval_l.emplace_back(lq.top());\n\
    \            else eval_l.emplace_back(lq.top() + add_l);\n            lq.pop();\n\
    \        }\n        reverse(eval_l.begin(), eval_l.end());\n        while (!rq.empty())\
    \ {\n            if constexpr (raw_eval_cache) eval_r.emplace_back(rq.top());\n\
    \            else eval_r.emplace_back(rq.top() + add_r);\n            rq.pop();\n\
    \        }\n\n        eval_l_sum.assign(eval_l.size() + 1, 0);\n        for (int\
    \ i = 0; i < (int)eval_l.size(); ++i) {\n            eval_l_sum[i + 1] = eval_l_sum[i]\
    \ + eval_l[i];\n        }\n        eval_r_sum.assign(eval_r.size() + 1, 0);\n\
    \        for (int i = 0; i < (int)eval_r.size(); ++i) {\n            eval_r_sum[i\
    \ + 1] = eval_r_sum[i] + eval_r[i];\n        }\n        eval_cache_valid = true;\n\
    \    }\n\npublic:\n    Query query() const {\n        return {top_L(), top_R(),\
    \ min_f};\n    }\n\n    void add_all(T a) {\n        min_f += a;\n    }\n\n  \
    \  void add_a_minus_x(T a) {\n        invalidate_eval_cache();\n        min_f\
    \ += max<T>(0, a - top_R());\n        push_R(a);\n        push_L(pop_R());\n \
    \   }\n\n    void add_x_minus_a(T a) {\n        invalidate_eval_cache();\n   \
    \     min_f += max<T>(0, top_L() - a);\n        push_L(a);\n        push_R(pop_L());\n\
    \    }\n\n    void add_abs(T a) {\n        add_a_minus_x(a);\n        add_x_minus_a(a);\n\
    \    }\n\n    void clear_right() {\n        decltype(R){}.swap(R);\n        invalidate_eval_cache();\n\
    \    }\n\n    void clear_left() {\n        decltype(L){}.swap(L);\n        invalidate_eval_cache();\n\
    \    }\n\n    void shift(T a, T b) {\n        assert(a <= b);\n        add_l +=\
    \ a;\n        add_r += b;\n        if constexpr (!raw_eval_cache) invalidate_eval_cache();\n\
    \    }\n\n    void shift(T a) {\n        shift(a, a);\n    }\n\n    T eval(T x)\
    \ const {\n        build_eval_cache();\n        EvalSum lx = x, rx = x;\n    \
    \    if constexpr (raw_eval_cache) {\n            lx -= static_cast<EvalSum>(add_l);\n\
    \            rx -= static_cast<EvalSum>(add_r);\n        }\n        EvalSum res\
    \ = min_f;\n        int li = upper_bound(eval_l.begin(), eval_l.end(), lx) - eval_l.begin();\n\
    \        res += eval_l_sum.back() - eval_l_sum[li] - lx * static_cast<EvalSum>(eval_l.size()\
    \ - li);\n        int ri = lower_bound(eval_r.begin(), eval_r.end(), rx) - eval_r.begin();\n\
    \        res += rx * static_cast<EvalSum>(ri) - eval_r_sum[ri];\n        return\
    \ static_cast<T>(res);\n    }\n\n    void merge(SlopeTrick &st) {\n        if\
    \ (st.size() > size()) swap(*this, st);\n        while (!st.L.empty()) add_a_minus_x(st.pop_L());\n\
    \        while (!st.R.empty()) add_x_minus_a(st.pop_R());\n        min_f += st.min_f;\n\
    \    }\n};\n\n/**\n * @brief Slope Trick\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/slope_trick.cpp
  requiredBy: []
  timestamp: '2026-10-09 00:41:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_slope_trick.test.cpp
date: 2026-03-08
documentation_of: datastructure/slope_trick.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Slope Trick
---

## 説明
下に凸な区分線形関数を保ちながら、`max(a - x, 0)` や `max(x - a, 0)` の加算、平行移動、片側累積 min を扱う。
折れ点の追加は $O(\log K)$、平行移動と定数加算は $O(1)$。$K$ は保持する折れ点数とする。

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
`eval` は heap から整列列と累積和を遅延構築する。構築に $O(K\log K)$、領域に $O(K)$ を使い、構築後の評価は $O(\log K)$。

64bit以下の整数型では移動前のキーを保持するため、`shift(a)`、`shift(a, b)`、`add_all` の後もキャッシュを再利用する。
累積和・評価座標からオフセットを引いた値・評価中の集計には `__int128` を使う。64bit整数の場合、累積和1要素は16 bytesになる。
既存の更新演算と最終的な返却値が `T` に収まることを前提とし、移動前の累積和や変換座標が `T` に収まる必要はない。

それ以外の型では実座標を保持し、`shift` 後の最初の評価で再構築する。
折れ点の追加・削除、`clear_left`、`clear_right`、`merge` によって変更されたキャッシュも次の評価で再構築する。
