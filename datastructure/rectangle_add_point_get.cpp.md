---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_rectangle_add_point_get.test.cpp
    title: test/yosupo_rectangle_add_point_get.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u9577\u65B9\u5F62\u52A0\u7B97\u70B9\u53D6\u5F97(Rectangle Add\
      \ Point Get)"
    links: []
  bundledCode: "#line 1 \"datastructure/rectangle_add_point_get.cpp\"\nusing namespace\
    \ std;\n\ntemplate<class T>\nstruct RectangleAddPointGet {\n    struct Operation\
    \ {\n        int type;\n        int l, d, r, u;\n        T w;\n    };\n\n    vector<Operation>\
    \ ops;\n    vector<int> xs;\n\n    void add_rectangle(int l, int d, int r, int\
    \ u, T w) {\n        ops.push_back({0, l, d, r, u, w});\n        xs.push_back(l);\n\
    \        xs.push_back(r);\n    }\n\n    void add_query(int x, int y) {\n     \
    \   ops.push_back({1, x, y, 0, 0, 0});\n    }\n\n    vector<T> solve() const {\n\
    \        vector<int> ord_x = xs;\n        ord_x.reserve(ord_x.size() + ops.size());\n\
    \        for (auto &&op : ops) {\n            if (op.type == 1) ord_x.push_back(op.l);\n\
    \        }\n        sort(ord_x.begin(), ord_x.end());\n        ord_x.erase(unique(ord_x.begin(),\
    \ ord_x.end()), ord_x.end());\n\n        int m = (int)ord_x.size();\n        vector<int>\
    \ x_index_lower(ops.size());\n        vector<int> x_index_upper(ops.size());\n\
    \        for (int idx = 0; idx < (int)ops.size(); ++idx) {\n            x_index_lower[idx]\
    \ = (int)(lower_bound(ord_x.begin(), ord_x.end(), ops[idx].l) - ord_x.begin())\
    \ + 1;\n            if (ops[idx].type == 1) {\n                x_index_upper[idx]\
    \ = (int)(upper_bound(ord_x.begin(), ord_x.end(), ops[idx].l) - ord_x.begin());\n\
    \            } else {\n                x_index_upper[idx] = (int)(lower_bound(ord_x.begin(),\
    \ ord_x.end(), ops[idx].r) - ord_x.begin()) + 1;\n            }\n        }\n \
    \       vector<int> cnt(m + 1);\n        auto count_point = [&](int xi) {\n  \
    \          for (int i = xi; i <= m; i += i & -i) ++cnt[i];\n        };\n     \
    \   for (int idx = 0; idx < (int)ops.size(); ++idx) {\n            if (ops[idx].type\
    \ == 1) continue;\n            count_point(x_index_lower[idx]);\n            count_point(x_index_lower[idx]);\n\
    \            count_point(x_index_upper[idx]);\n            count_point(x_index_upper[idx]);\n\
    \        }\n        vector<vector<int>> ys(m + 1);\n        for (int i = 1; i\
    \ <= m; ++i) ys[i].reserve(cnt[i]);\n        auto reserve_point = [&](int xi,\
    \ int y) {\n            for (int i = xi; i <= m; i += i & -i) ys[i].push_back(y);\n\
    \        };\n        for (int idx = 0; idx < (int)ops.size(); ++idx) {\n     \
    \       auto &&op = ops[idx];\n            if (op.type == 0) {\n             \
    \   reserve_point(x_index_lower[idx], op.d);\n                reserve_point(x_index_lower[idx],\
    \ op.u);\n                reserve_point(x_index_upper[idx], op.d);\n         \
    \       reserve_point(x_index_upper[idx], op.u);\n            }\n        }\n \
    \       for (int i = 1; i <= m; ++i) {\n            sort(ys[i].begin(), ys[i].end());\n\
    \            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());\n \
    \       }\n\n        vector<int> offset(m + 2, 0);\n        for (int i = 1; i\
    \ <= m; ++i) offset[i + 1] = offset[i] + (int)ys[i].size();\n        vector<T>\
    \ bit(offset[m + 1], 0);\n\n        auto add_point = [&](int xi, int y, T w) {\n\
    \            for (int i = xi; i <= m; i += i & -i) {\n                int yi =\
    \ (int)(lower_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin());\n       \
    \         int sz = (int)ys[i].size();\n                int base = offset[i];\n\
    \                for (++yi; yi <= sz; yi += yi & -yi) bit[base + yi - 1] += w;\n\
    \            }\n        };\n        auto prefix_sum = [&](int xi, int y) {\n \
    \           T ret = 0;\n            for (int i = xi; i > 0; i -= i & -i) {\n \
    \               int yi = (int)(upper_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin());\n\
    \                int base = offset[i];\n                for (; yi > 0; yi -= yi\
    \ & -yi) ret += bit[base + yi - 1];\n            }\n            return ret;\n\
    \        };\n\n        vector<T> ans;\n        for (int idx = 0; idx < (int)ops.size();\
    \ ++idx) {\n            auto &&op = ops[idx];\n            if (op.type == 0) {\n\
    \                add_point(x_index_lower[idx], op.d, op.w);\n                add_point(x_index_lower[idx],\
    \ op.u, -op.w);\n                add_point(x_index_upper[idx], op.d, -op.w);\n\
    \                add_point(x_index_upper[idx], op.u, op.w);\n            } else\
    \ {\n                ans.push_back(prefix_sum(x_index_upper[idx], op.d));\n  \
    \          }\n        }\n        return ans;\n    }\n};\n\n/**\n * @brief \u9577\
    \u65B9\u5F62\u52A0\u7B97\u70B9\u53D6\u5F97(Rectangle Add Point Get)\n */\n"
  code: "using namespace std;\n\ntemplate<class T>\nstruct RectangleAddPointGet {\n\
    \    struct Operation {\n        int type;\n        int l, d, r, u;\n        T\
    \ w;\n    };\n\n    vector<Operation> ops;\n    vector<int> xs;\n\n    void add_rectangle(int\
    \ l, int d, int r, int u, T w) {\n        ops.push_back({0, l, d, r, u, w});\n\
    \        xs.push_back(l);\n        xs.push_back(r);\n    }\n\n    void add_query(int\
    \ x, int y) {\n        ops.push_back({1, x, y, 0, 0, 0});\n    }\n\n    vector<T>\
    \ solve() const {\n        vector<int> ord_x = xs;\n        ord_x.reserve(ord_x.size()\
    \ + ops.size());\n        for (auto &&op : ops) {\n            if (op.type ==\
    \ 1) ord_x.push_back(op.l);\n        }\n        sort(ord_x.begin(), ord_x.end());\n\
    \        ord_x.erase(unique(ord_x.begin(), ord_x.end()), ord_x.end());\n\n   \
    \     int m = (int)ord_x.size();\n        vector<int> x_index_lower(ops.size());\n\
    \        vector<int> x_index_upper(ops.size());\n        for (int idx = 0; idx\
    \ < (int)ops.size(); ++idx) {\n            x_index_lower[idx] = (int)(lower_bound(ord_x.begin(),\
    \ ord_x.end(), ops[idx].l) - ord_x.begin()) + 1;\n            if (ops[idx].type\
    \ == 1) {\n                x_index_upper[idx] = (int)(upper_bound(ord_x.begin(),\
    \ ord_x.end(), ops[idx].l) - ord_x.begin());\n            } else {\n         \
    \       x_index_upper[idx] = (int)(lower_bound(ord_x.begin(), ord_x.end(), ops[idx].r)\
    \ - ord_x.begin()) + 1;\n            }\n        }\n        vector<int> cnt(m +\
    \ 1);\n        auto count_point = [&](int xi) {\n            for (int i = xi;\
    \ i <= m; i += i & -i) ++cnt[i];\n        };\n        for (int idx = 0; idx <\
    \ (int)ops.size(); ++idx) {\n            if (ops[idx].type == 1) continue;\n \
    \           count_point(x_index_lower[idx]);\n            count_point(x_index_lower[idx]);\n\
    \            count_point(x_index_upper[idx]);\n            count_point(x_index_upper[idx]);\n\
    \        }\n        vector<vector<int>> ys(m + 1);\n        for (int i = 1; i\
    \ <= m; ++i) ys[i].reserve(cnt[i]);\n        auto reserve_point = [&](int xi,\
    \ int y) {\n            for (int i = xi; i <= m; i += i & -i) ys[i].push_back(y);\n\
    \        };\n        for (int idx = 0; idx < (int)ops.size(); ++idx) {\n     \
    \       auto &&op = ops[idx];\n            if (op.type == 0) {\n             \
    \   reserve_point(x_index_lower[idx], op.d);\n                reserve_point(x_index_lower[idx],\
    \ op.u);\n                reserve_point(x_index_upper[idx], op.d);\n         \
    \       reserve_point(x_index_upper[idx], op.u);\n            }\n        }\n \
    \       for (int i = 1; i <= m; ++i) {\n            sort(ys[i].begin(), ys[i].end());\n\
    \            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());\n \
    \       }\n\n        vector<int> offset(m + 2, 0);\n        for (int i = 1; i\
    \ <= m; ++i) offset[i + 1] = offset[i] + (int)ys[i].size();\n        vector<T>\
    \ bit(offset[m + 1], 0);\n\n        auto add_point = [&](int xi, int y, T w) {\n\
    \            for (int i = xi; i <= m; i += i & -i) {\n                int yi =\
    \ (int)(lower_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin());\n       \
    \         int sz = (int)ys[i].size();\n                int base = offset[i];\n\
    \                for (++yi; yi <= sz; yi += yi & -yi) bit[base + yi - 1] += w;\n\
    \            }\n        };\n        auto prefix_sum = [&](int xi, int y) {\n \
    \           T ret = 0;\n            for (int i = xi; i > 0; i -= i & -i) {\n \
    \               int yi = (int)(upper_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin());\n\
    \                int base = offset[i];\n                for (; yi > 0; yi -= yi\
    \ & -yi) ret += bit[base + yi - 1];\n            }\n            return ret;\n\
    \        };\n\n        vector<T> ans;\n        for (int idx = 0; idx < (int)ops.size();\
    \ ++idx) {\n            auto &&op = ops[idx];\n            if (op.type == 0) {\n\
    \                add_point(x_index_lower[idx], op.d, op.w);\n                add_point(x_index_lower[idx],\
    \ op.u, -op.w);\n                add_point(x_index_upper[idx], op.d, -op.w);\n\
    \                add_point(x_index_upper[idx], op.u, op.w);\n            } else\
    \ {\n                ans.push_back(prefix_sum(x_index_upper[idx], op.d));\n  \
    \          }\n        }\n        return ans;\n    }\n};\n\n/**\n * @brief \u9577\
    \u65B9\u5F62\u52A0\u7B97\u70B9\u53D6\u5F97(Rectangle Add Point Get)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/rectangle_add_point_get.cpp
  requiredBy: []
  timestamp: '2026-03-12 00:49:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_rectangle_add_point_get.test.cpp
date: 2026-03-11
documentation_of: datastructure/rectangle_add_point_get.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "\u9577\u65B9\u5F62\u52A0\u7B97\u70B9\u53D6\u5F97(Rectangle Add Point Get)"
---

## 説明
長方形加算と点取得をまとめて処理する。
`x` 方向に sweep し、`y` 方向の差分を 1 次元 BIT で管理する。

## できること
- `RectangleAddPointGet<T> solver`
  空の solver を作る
- `void add_rectangle(int l, int d, int r, int u, T w)`
  半開長方形 `[l, r) x [d, u)` に重み `w` を加える操作を積む
- `void add_query(int x, int y)`
  点 `(x, y)` の値を取るクエリを積む
- `vector<T> solve()`
  追加順に各クエリの答えを返す

## 使い方
初期長方形も更新も `add_rectangle` で積む。
`solve()` は全 `y` 座標を座圧して、操作列を offline で処理する。
