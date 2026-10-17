---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/binaryindexedtree.cpp
    title: Binary Indexed Tree(BIT)
  - icon: ':heavy_check_mark:'
    path: datastructure/fenwick_tree_2d.cpp
    title: "2\u6B21\u5143Fenwick Tree(2D BIT)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_library_composition.test.cpp
    title: test/yosupo_aplusb_library_composition.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_rectangle_sum_weights.test.cpp
    title: test/yosupo_aplusb_rectangle_sum_weights.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_add_rectangle_sum.test.cpp
    title: test/yosupo_point_add_rectangle_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u70B9\u52A0\u7B97\u9577\u65B9\u5F62\u548C(Point Add Rectangle\
      \ Sum)"
    links: []
  bundledCode: "#line 1 \"datastructure/point_add_rectangle_sum.cpp\"\nusing namespace\
    \ std;\n\n#line 1 \"datastructure/fenwick_tree_2d.cpp\"\n\n\n\nusing namespace\
    \ std;\n\n#line 1 \"datastructure/binaryindexedtree.cpp\"\n\n\n\ntemplate<class\
    \ T>\nclass BIT {\n    vector<T> bit;\n    int m, n;\npublic:\n    BIT(int n):\
    \ bit(n), m(1), n(n) {\n        while (m < n) m <<= 1;\n    }\n\n    explicit\
    \ BIT(const vector<T> &values): bit(values), m(1), n(values.size()) {\n      \
    \  while (m < n) m <<= 1;\n        for (int i = 1; i <= n; ++i) {\n          \
    \  int parent = i + (i & -i);\n            if (parent <= n) bit[parent - 1] +=\
    \ bit[i - 1];\n        }\n    }\n\n    T sum(int k){\n        T ret = 0;\n   \
    \     for (; k > 0; k -= (k & -k)) ret += bit[k - 1];\n        return ret;\n \
    \   }\n\n    void add(int k, T x){\n        for (k++; k <= n; k += (k & -k)) bit[k\
    \ - 1] += x;\n    }\n\n    int lower_bound(T x) {\n        if (x <= 0) return\
    \ 0;\n        int i = 0;\n        for (int j = m; j; j >>= 1) {\n            if\
    \ (i + j <= n && bit[i + j - 1] < x) x -= bit[i + j - 1], i += j;\n        }\n\
    \        return min(i + 1, n);\n    }\n};\n\n/**\n * @brief Binary Indexed Tree(BIT)\n\
    \ */\n\n\n#line 7 \"datastructure/fenwick_tree_2d.cpp\"\n\ntemplate<class T>\n\
    struct FenwickTree2D {\n    vector<pair<int, int>> points;\n    vector<int> xs;\n\
    \    vector<vector<int>> ys;\n    vector<BIT<T>> bit;\n    bool built = false;\n\
    \n    void add_point(int x, int y) {\n        assert(!built);\n        points.push_back({x,\
    \ y});\n        xs.push_back(x);\n    }\n\n    void build() {\n        assert(!built);\n\
    \        built = true;\n\n        sort(xs.begin(), xs.end());\n        xs.erase(unique(xs.begin(),\
    \ xs.end()), xs.end());\n\n        vector<pair<int, int>> ord = points;\n    \
    \    sort(ord.begin(), ord.end());\n        ord.erase(unique(ord.begin(), ord.end()),\
    \ ord.end());\n\n        int m = (int)xs.size();\n        ys.assign(m + 1, {});\n\
    \        {\n            vector<int> counts(m + 1);\n            int xi = 1;\n\
    \            for (auto &[x, y] : ord) {\n                while (xs[xi - 1] < x)\
    \ ++xi;\n                x = xi;\n                for (int i = xi; i <= m; i +=\
    \ i & -i) ++counts[i];\n            }\n            for (int i = 1; i <= m; ++i)\
    \ ys[i].reserve(counts[i]);\n        }\n        sort(ord.begin(), ord.end(), [](const\
    \ auto &a, const auto &b) {\n            return a.second < b.second;\n       \
    \ });\n        for (auto [xi, y] : ord) {\n            for (int i = xi; i <= m;\
    \ i += i & -i) ys[i].push_back(y);\n        }\n        bit.clear();\n        bit.reserve(m\
    \ + 1);\n        bit.emplace_back(0);\n        for (int i = 1; i <= m; ++i) {\n\
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
    /**\n * @brief 2\u6B21\u5143Fenwick Tree(2D BIT)\n */\n\n\n#line 4 \"datastructure/point_add_rectangle_sum.cpp\"\
    \n\ntemplate<class T>\nstruct PointAddRectangleSum {\n    struct Operation {\n\
    \        int type;\n        int x, y, z, u;\n        T w;\n    };\n\n    vector<Operation>\
    \ ops;\n\n    void add_point(int x, int y, T w) {\n        ops.push_back({0, x,\
    \ y, 0, 0, w});\n    }\n\n    void add_query(int l, int d, int r, int u) {\n \
    \       ops.push_back({1, l, d, r, u, T(0)});\n    }\n\n    vector<T> solve()\
    \ const {\n        FenwickTree2D<T> bit;\n        for (const auto &op : ops) {\n\
    \            if (op.type == 0) bit.add_point(op.x, op.y);\n        }\n       \
    \ bit.build();\n\n        vector<T> ans;\n        for (const auto &op : ops) {\n\
    \            if (op.type == 0) {\n                bit.add(op.x, op.y, op.w);\n\
    \            } else {\n                ans.push_back(bit.sum(op.x, op.y, op.z,\
    \ op.u));\n            }\n        }\n        return ans;\n    }\n};\n\n/**\n *\
    \ @brief \u70B9\u52A0\u7B97\u9577\u65B9\u5F62\u548C(Point Add Rectangle Sum)\n\
    \ */\n"
  code: "using namespace std;\n\n#include \"fenwick_tree_2d.cpp\"\n\ntemplate<class\
    \ T>\nstruct PointAddRectangleSum {\n    struct Operation {\n        int type;\n\
    \        int x, y, z, u;\n        T w;\n    };\n\n    vector<Operation> ops;\n\
    \n    void add_point(int x, int y, T w) {\n        ops.push_back({0, x, y, 0,\
    \ 0, w});\n    }\n\n    void add_query(int l, int d, int r, int u) {\n       \
    \ ops.push_back({1, l, d, r, u, T(0)});\n    }\n\n    vector<T> solve() const\
    \ {\n        FenwickTree2D<T> bit;\n        for (const auto &op : ops) {\n   \
    \         if (op.type == 0) bit.add_point(op.x, op.y);\n        }\n        bit.build();\n\
    \n        vector<T> ans;\n        for (const auto &op : ops) {\n            if\
    \ (op.type == 0) {\n                bit.add(op.x, op.y, op.w);\n            }\
    \ else {\n                ans.push_back(bit.sum(op.x, op.y, op.z, op.u));\n  \
    \          }\n        }\n        return ans;\n    }\n};\n\n/**\n * @brief \u70B9\
    \u52A0\u7B97\u9577\u65B9\u5F62\u548C(Point Add Rectangle Sum)\n */\n"
  dependsOn:
  - datastructure/fenwick_tree_2d.cpp
  - datastructure/binaryindexedtree.cpp
  isVerificationFile: false
  path: datastructure/point_add_rectangle_sum.cpp
  requiredBy: []
  timestamp: '2026-10-18 01:00:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_library_composition.test.cpp
  - test/yosupo_point_add_rectangle_sum.test.cpp
  - test/yosupo_aplusb_rectangle_sum_weights.test.cpp
date: 2026-03-08
documentation_of: datastructure/point_add_rectangle_sum.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "\u70B9\u52A0\u7B97\u9577\u65B9\u5F62\u548C(Point Add Rectangle Sum)"
---

## 説明
点追加と長方形和クエリをまとめて処理する。
全追加点を先に集めて、座圧済み 2 次元 BIT を offline 構築する。

## できること
- `PointAddRectangleSum<T> solver`
  空の solver を作る
- `void add_point(int x, int y, T w)`
  点 `(x, y)` に重み `w` を追加する操作を積む
- `void add_query(int l, int d, int r, int u)`
  半開長方形 `[l, r) x [d, u)` の和クエリを積む
- `vector<T> solve() const`
  追加順に各クエリの答えを返す。加算回数を $P$、クエリ数を $Q$ として時間 $O((P+Q)\log^2 P)$、追加領域 $O(P\log P+Q)$

## 使い方
初期点も更新点も `add_point` で順に積む。
`solve()` はそれまでに現れる全追加点の座標から 2 次元 BIT を構築し、操作列を先頭から再生する。
登録した操作は保持し、繰り返し呼べる。

## 実装上の補足
`FenwickTree2D` で登録座標を重複排除し、全体を $y$ 順に並べて各 BIT の行へ配る。構築は $O(P\log P)$。
