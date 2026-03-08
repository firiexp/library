---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_deque_operate_all_composite.test.cpp
    title: test/yosupo_deque_operate_all_composite.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    _deprecated_at_docs: _md/swag_deque.md
    document_title: SWAG Deque
    links: []
  bundledCode: "#line 1 \"datastructure/swag_deque.cpp\"\ntemplate<class G>\nclass\
    \ TwoStackDeque {\n    using T = typename G::T;\n    vector<T> l, r, lsum, rsum;\n\
    \    void rebuild_left_sum() {\n        lsum.assign(1, G::e());\n        for (int\
    \ i = 0; i < (int)l.size(); ++i) {\n            lsum.push_back(G::f(l[i], lsum.back()));\n\
    \        }\n    }\n\n    void rebuild_right_sum() {\n        rsum.assign(1, G::e());\n\
    \        for (int i = 0; i < (int)r.size(); ++i) {\n            rsum.push_back(G::f(rsum.back(),\
    \ r[i]));\n        }\n    }\n\n    void rebalance_from_right() {\n        int\
    \ lsize = ((int)r.size() + 1) / 2;\n        int rsize = (int)r.size() - lsize;\n\
    \        l.resize(lsize);\n        for (int i = 0; i < lsize; ++i) l[i] = r[lsize\
    \ - i - 1];\n        for (int i = 0; i < rsize; ++i) r[i] = r[i + lsize];\n  \
    \      r.resize(rsize);\n        rebuild_left_sum();\n        rebuild_right_sum();\n\
    \    }\n\n    void rebalance_from_left() {\n        int rsize = ((int)l.size()\
    \ + 1) / 2;\n        int lsize = (int)l.size() - rsize;\n        r.resize(rsize);\n\
    \        for (int i = 0; i < rsize; ++i) r[i] = l[rsize - i - 1];\n        for\
    \ (int i = 0; i < lsize; ++i) l[i] = l[i + rsize];\n        l.resize(lsize);\n\
    \        rebuild_left_sum();\n        rebuild_right_sum();\n    }\npublic:\n \
    \   TwoStackDeque() : l(0), r(0), lsum(1, G::e()), rsum(1, G::e()) {}\n\n    void\
    \ push_front(const T& v){\n        lsum.push_back(G::f(v, lsum.back()));\n   \
    \     l.push_back(v);\n    }\n\n    void push_back(const T& v){\n        rsum.push_back(G::f(rsum.back(),\
    \ v));\n        r.push_back(v);\n    }\n\n    void pop_front(){\n        if(l.empty()){\n\
    \            if(r.empty()) return;\n            rebalance_from_right();\n    \
    \    }\n        l.pop_back(); lsum.pop_back();\n    }\n\n    void pop_back(){\n\
    \        if(r.empty()){\n            if(l.empty()) return;\n            rebalance_from_left();\n\
    \        }\n        r.pop_back(); rsum.pop_back();\n    }\n\n    T fold(){\n \
    \       return G::f(lsum.back(), rsum.back());\n    }\n};\n/*\nstruct Monoid {\n\
    \    using T = int;\n    static T f(T a, T b) { return a+b; }\n    static T e()\
    \ { return 0; }\n};\n*/\n\n/**\n * @brief SWAG Deque\n * @docs _md/swag_deque.md\n\
    \ */\n"
  code: "template<class G>\nclass TwoStackDeque {\n    using T = typename G::T;\n\
    \    vector<T> l, r, lsum, rsum;\n    void rebuild_left_sum() {\n        lsum.assign(1,\
    \ G::e());\n        for (int i = 0; i < (int)l.size(); ++i) {\n            lsum.push_back(G::f(l[i],\
    \ lsum.back()));\n        }\n    }\n\n    void rebuild_right_sum() {\n       \
    \ rsum.assign(1, G::e());\n        for (int i = 0; i < (int)r.size(); ++i) {\n\
    \            rsum.push_back(G::f(rsum.back(), r[i]));\n        }\n    }\n\n  \
    \  void rebalance_from_right() {\n        int lsize = ((int)r.size() + 1) / 2;\n\
    \        int rsize = (int)r.size() - lsize;\n        l.resize(lsize);\n      \
    \  for (int i = 0; i < lsize; ++i) l[i] = r[lsize - i - 1];\n        for (int\
    \ i = 0; i < rsize; ++i) r[i] = r[i + lsize];\n        r.resize(rsize);\n    \
    \    rebuild_left_sum();\n        rebuild_right_sum();\n    }\n\n    void rebalance_from_left()\
    \ {\n        int rsize = ((int)l.size() + 1) / 2;\n        int lsize = (int)l.size()\
    \ - rsize;\n        r.resize(rsize);\n        for (int i = 0; i < rsize; ++i)\
    \ r[i] = l[rsize - i - 1];\n        for (int i = 0; i < lsize; ++i) l[i] = l[i\
    \ + rsize];\n        l.resize(lsize);\n        rebuild_left_sum();\n        rebuild_right_sum();\n\
    \    }\npublic:\n    TwoStackDeque() : l(0), r(0), lsum(1, G::e()), rsum(1, G::e())\
    \ {}\n\n    void push_front(const T& v){\n        lsum.push_back(G::f(v, lsum.back()));\n\
    \        l.push_back(v);\n    }\n\n    void push_back(const T& v){\n        rsum.push_back(G::f(rsum.back(),\
    \ v));\n        r.push_back(v);\n    }\n\n    void pop_front(){\n        if(l.empty()){\n\
    \            if(r.empty()) return;\n            rebalance_from_right();\n    \
    \    }\n        l.pop_back(); lsum.pop_back();\n    }\n\n    void pop_back(){\n\
    \        if(r.empty()){\n            if(l.empty()) return;\n            rebalance_from_left();\n\
    \        }\n        r.pop_back(); rsum.pop_back();\n    }\n\n    T fold(){\n \
    \       return G::f(lsum.back(), rsum.back());\n    }\n};\n/*\nstruct Monoid {\n\
    \    using T = int;\n    static T f(T a, T b) { return a+b; }\n    static T e()\
    \ { return 0; }\n};\n*/\n\n/**\n * @brief SWAG Deque\n * @docs _md/swag_deque.md\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/swag_deque.cpp
  requiredBy: []
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_deque_operate_all_composite.test.cpp
documentation_of: datastructure/swag_deque.cpp
layout: document
redirect_from:
- /library/datastructure/swag_deque.cpp
- /library/datastructure/swag_deque.cpp.html
title: SWAG Deque
---
## 説明
両端キューに対する sliding window aggregation である。
結合則を満たす演算なら、両端への追加・削除と全体積の取得を償却 `O(1)` で処理する。

## できること
- `TwoStackDeque<G> deq`
  空の deque を作る
- `void push_front(const T& v)`
  先頭に `v` を追加する
- `void push_back(const T& v)`
  末尾に `v` を追加する
- `void pop_front()`
  先頭を 1 つ削除する。空なら何もしない
- `void pop_back()`
  末尾を 1 つ削除する。空なら何もしない
- `T fold()`
  deque 全体の積を返す。空なら `G::e()`

## 使い方
`G` に `using T`、`static T f(T, T)`、`static T e()` を定義して使う。
`f(a, b)` は左から右へ並べたときの積を返すようにする。

```cpp
struct Monoid {
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

TwoStackDeque<Monoid> deq;
deq.push_front(3);
deq.push_back(5);
long long x = deq.fold();
```

## 実装上の補足
片側が空で削除できないときは、反対側の要素を半分ずつ持ち替える。
各操作は償却 `O(1)` で、非可換な演算にも使える。
