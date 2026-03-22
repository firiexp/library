---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: datastructure/binaryindexedtree.cpp
    title: Binary Indexed Tree(BIT)
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_point_add_rectangle_sum_fenwick_tree_2d.test.cpp
    title: test/yosupo_point_add_rectangle_sum_fenwick_tree_2d.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "2\u6B21\u5143Fenwick Tree(2D BIT)"
    links: []
  bundledCode: "#line 1 \"datastructure/fenwick_tree_2d.cpp\"\nusing namespace std;\n\
    \n#line 1 \"datastructure/binaryindexedtree.cpp\"\ntemplate<class T>\nclass BIT\
    \ {\n    vector<T> bit;\n    int m, n;\npublic:\n    BIT(int n): bit(n), m(1),\
    \ n(n) {\n        while (m < n) m <<= 1;\n    }\n\n    T sum(int k){\n       \
    \ T ret = 0;\n        for (; k > 0; k -= (k & -k)) ret += bit[k - 1];\n      \
    \  return ret;\n    }\n\n    void add(int k, T x){\n        for (k++; k <= n;\
    \ k += (k & -k)) bit[k - 1] += x;\n    }\n\n    int lower_bound(T x) {\n     \
    \   if (x <= 0) return 0;\n        int i = 0;\n        for (int j = m; j; j >>=\
    \ 1) {\n            if (i + j <= n && bit[i + j - 1] < x) x -= bit[i + j - 1],\
    \ i += j;\n        }\n        return min(i + 1, n);\n    }\n};\n\n/**\n * @brief\
    \ Binary Indexed Tree(BIT)\n */\n#line 4 \"datastructure/fenwick_tree_2d.cpp\"\
    \n\ntemplate<class T>\nstruct FenwickTree2D {\n    vector<pair<int, int>> points;\n\
    \    vector<int> xs;\n    vector<vector<int>> ys;\n    vector<BIT<T>> bit;\n \
    \   bool built = false;\n\n    void add_point(int x, int y) {\n        assert(!built);\n\
    \        points.push_back({x, y});\n        xs.push_back(x);\n    }\n\n    void\
    \ build() {\n        assert(!built);\n        built = true;\n\n        sort(xs.begin(),\
    \ xs.end());\n        xs.erase(unique(xs.begin(), xs.end()), xs.end());\n\n  \
    \      vector<pair<int, int>> ord = points;\n        sort(ord.begin(), ord.end());\n\
    \        ord.erase(unique(ord.begin(), ord.end()), ord.end());\n\n        int\
    \ m = (int)xs.size();\n        ys.assign(m + 1, {});\n        for (auto [x, y]\
    \ : ord) {\n            int xi = (int)(lower_bound(xs.begin(), xs.end(), x) -\
    \ xs.begin()) + 1;\n            for (int i = xi; i <= m; i += i & -i) ys[i].push_back(y);\n\
    \        }\n        bit.clear();\n        bit.reserve(m + 1);\n        bit.emplace_back(0);\n\
    \        for (int i = 1; i <= m; ++i) {\n            sort(ys[i].begin(), ys[i].end());\n\
    \            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());\n \
    \           bit.emplace_back((int)ys[i].size());\n        }\n    }\n\n    void\
    \ add(int x, int y, T w) {\n        assert(built);\n        int m = (int)xs.size();\n\
    \        int xi = (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin());\n\
    \        assert(xi < m && xs[xi] == x);\n        ++xi;\n        for (int i = xi;\
    \ i <= m; i += i & -i) {\n            int yi = (int)(lower_bound(ys[i].begin(),\
    \ ys[i].end(), y) - ys[i].begin());\n            assert(yi < (int)ys[i].size()\
    \ && ys[i][yi] == y);\n            bit[i].add(yi, w);\n        }\n    }\n\n  \
    \  T sum(int x, int y) {\n        assert(built);\n        T ret = 0;\n       \
    \ int xi = (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin());\n       \
    \ for (int i = xi; i > 0; i -= i & -i) {\n            int yi = (int)(lower_bound(ys[i].begin(),\
    \ ys[i].end(), y) - ys[i].begin());\n            ret += bit[i].sum(yi);\n    \
    \    }\n        return ret;\n    }\n\n    T sum(int l, int d, int r, int u) {\n\
    \        return sum(r, u) - sum(r, d) - sum(l, u) + sum(l, d);\n    }\n};\n\n\
    /**\n * @brief 2\u6B21\u5143Fenwick Tree(2D BIT)\n */\n"
  code: "using namespace std;\n\n#include \"binaryindexedtree.cpp\"\n\ntemplate<class\
    \ T>\nstruct FenwickTree2D {\n    vector<pair<int, int>> points;\n    vector<int>\
    \ xs;\n    vector<vector<int>> ys;\n    vector<BIT<T>> bit;\n    bool built =\
    \ false;\n\n    void add_point(int x, int y) {\n        assert(!built);\n    \
    \    points.push_back({x, y});\n        xs.push_back(x);\n    }\n\n    void build()\
    \ {\n        assert(!built);\n        built = true;\n\n        sort(xs.begin(),\
    \ xs.end());\n        xs.erase(unique(xs.begin(), xs.end()), xs.end());\n\n  \
    \      vector<pair<int, int>> ord = points;\n        sort(ord.begin(), ord.end());\n\
    \        ord.erase(unique(ord.begin(), ord.end()), ord.end());\n\n        int\
    \ m = (int)xs.size();\n        ys.assign(m + 1, {});\n        for (auto [x, y]\
    \ : ord) {\n            int xi = (int)(lower_bound(xs.begin(), xs.end(), x) -\
    \ xs.begin()) + 1;\n            for (int i = xi; i <= m; i += i & -i) ys[i].push_back(y);\n\
    \        }\n        bit.clear();\n        bit.reserve(m + 1);\n        bit.emplace_back(0);\n\
    \        for (int i = 1; i <= m; ++i) {\n            sort(ys[i].begin(), ys[i].end());\n\
    \            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());\n \
    \           bit.emplace_back((int)ys[i].size());\n        }\n    }\n\n    void\
    \ add(int x, int y, T w) {\n        assert(built);\n        int m = (int)xs.size();\n\
    \        int xi = (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin());\n\
    \        assert(xi < m && xs[xi] == x);\n        ++xi;\n        for (int i = xi;\
    \ i <= m; i += i & -i) {\n            int yi = (int)(lower_bound(ys[i].begin(),\
    \ ys[i].end(), y) - ys[i].begin());\n            assert(yi < (int)ys[i].size()\
    \ && ys[i][yi] == y);\n            bit[i].add(yi, w);\n        }\n    }\n\n  \
    \  T sum(int x, int y) {\n        assert(built);\n        T ret = 0;\n       \
    \ int xi = (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin());\n       \
    \ for (int i = xi; i > 0; i -= i & -i) {\n            int yi = (int)(lower_bound(ys[i].begin(),\
    \ ys[i].end(), y) - ys[i].begin());\n            ret += bit[i].sum(yi);\n    \
    \    }\n        return ret;\n    }\n\n    T sum(int l, int d, int r, int u) {\n\
    \        return sum(r, u) - sum(r, d) - sum(l, u) + sum(l, d);\n    }\n};\n\n\
    /**\n * @brief 2\u6B21\u5143Fenwick Tree(2D BIT)\n */\n"
  dependsOn:
  - datastructure/binaryindexedtree.cpp
  isVerificationFile: false
  path: datastructure/fenwick_tree_2d.cpp
  requiredBy: []
  timestamp: '2026-03-12 00:49:33+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_point_add_rectangle_sum_fenwick_tree_2d.test.cpp
date: 2026-03-11
documentation_of: datastructure/fenwick_tree_2d.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "2\u6B21\u5143Fenwick Tree(2D BIT)"
---

## 説明
更新される点集合を先に登録してから構築する座圧 2 次元 BIT。
点加算と半開長方形和を各 $O(log^2 N)$ で扱う。

## できること
- `FenwickTree2D<T> fw`
  空の 2 次元 BIT を作る
- `void add_point(int x, int y)`
  今後更新する可能性がある点 `(x, y)` を登録する
- `void build()`
  登録済みの点から内部座圧を構築する
- `void add(int x, int y, T w)`
  登録済みの点 `(x, y)` に `w` を加える。未登録点は使えない
- `T sum(int x, int y)`
  半開長方形 `(-inf, x) x (-inf, y)` の総和を返す
- `T sum(int l, int d, int r, int u)`
  半開長方形 `[l, r) x [d, u)` の総和を返す

## 使い方
更新に使う全点を `add_point` で登録してから `build()` する。
`build()` 後は `add` と `sum` を任意順に呼べる。
