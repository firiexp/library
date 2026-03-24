---
category: "\u30D5\u30ED\u30FC"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_assignment_hungarian.test.cpp
    title: test/yosupo_assignment_hungarian.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30CF\u30F3\u30AC\u30EA\u30A2\u30F3\u6CD5(Hungarian Algorithm)"
    links: []
  bundledCode: "#line 1 \"flow/hungarian.cpp\"\ntemplate<class T, bool Minimize =\
    \ true>\ntuple<T, vector<int>, vector<T>, vector<T>> hungarian(const vector<vector<T>>\
    \ &cost) {\n    int n = cost.size();\n    if (n == 0) return {T(0), {}, {}, {}};\n\
    \    int m = cost[0].size();\n    assert(n <= m);\n    for (int i = 0; i < n;\
    \ ++i) assert((int)cost[i].size() == m);\n\n    vector<vector<T>> a(n + 1, vector<T>(m\
    \ + 1));\n    for (int i = 0; i < n; ++i) {\n        for (int j = 0; j < m; ++j)\
    \ {\n            a[i + 1][j + 1] = Minimize ? cost[i][j] : -cost[i][j];\n    \
    \    }\n    }\n\n    vector<int> p(m + 1), way(m + 1);\n    vector<T> u(n + 1),\
    \ v(m + 1), minv(m + 1);\n    vector<char> used(m + 1);\n\n    for (int i = 1;\
    \ i <= n; ++i) {\n        p[0] = i;\n        fill(minv.begin(), minv.end(), numeric_limits<T>::max());\n\
    \        fill(used.begin(), used.end(), 0);\n        int j0 = 0;\n        while\
    \ (p[j0] != 0) {\n            used[j0] = 1;\n            int i0 = p[j0], j1 =\
    \ 0;\n            T delta = numeric_limits<T>::max();\n            for (int j\
    \ = 1; j <= m; ++j) {\n                if (used[j]) continue;\n              \
    \  T cur = a[i0][j] - u[i0] - v[j];\n                if (cur < minv[j]) {\n  \
    \                  minv[j] = cur;\n                    way[j] = j0;\n        \
    \        }\n                if (minv[j] < delta) {\n                    delta\
    \ = minv[j];\n                    j1 = j;\n                }\n            }\n\
    \            for (int j = 0; j <= m; ++j) {\n                if (used[j]) {\n\
    \                    u[p[j]] += delta;\n                    v[j] -= delta;\n \
    \               } else {\n                    minv[j] -= delta;\n            \
    \    }\n            }\n            j0 = j1;\n        }\n        while (j0 != 0)\
    \ {\n            int j1 = way[j0];\n            p[j0] = p[j1];\n            j0\
    \ = j1;\n        }\n    }\n\n    vector<int> match(n, -1);\n    for (int j = 1;\
    \ j <= m; ++j) {\n        if (p[j] != 0) match[p[j] - 1] = j - 1;\n    }\n\n \
    \   vector<T> row(n), col(m);\n    for (int i = 0; i < n; ++i) row[i] = u[i +\
    \ 1];\n    for (int j = 0; j < m; ++j) col[j] = v[j + 1];\n    T ans = -v[0];\n\
    \    if (!Minimize) {\n        ans = -ans;\n        for (int i = 0; i < n; ++i)\
    \ row[i] = -row[i];\n        for (int j = 0; j < m; ++j) col[j] = -col[j];\n \
    \   }\n    return {ans, match, row, col};\n}\n\n/**\n * @brief \u30CF\u30F3\u30AC\
    \u30EA\u30A2\u30F3\u6CD5(Hungarian Algorithm)\n */\n"
  code: "template<class T, bool Minimize = true>\ntuple<T, vector<int>, vector<T>,\
    \ vector<T>> hungarian(const vector<vector<T>> &cost) {\n    int n = cost.size();\n\
    \    if (n == 0) return {T(0), {}, {}, {}};\n    int m = cost[0].size();\n   \
    \ assert(n <= m);\n    for (int i = 0; i < n; ++i) assert((int)cost[i].size()\
    \ == m);\n\n    vector<vector<T>> a(n + 1, vector<T>(m + 1));\n    for (int i\
    \ = 0; i < n; ++i) {\n        for (int j = 0; j < m; ++j) {\n            a[i +\
    \ 1][j + 1] = Minimize ? cost[i][j] : -cost[i][j];\n        }\n    }\n\n    vector<int>\
    \ p(m + 1), way(m + 1);\n    vector<T> u(n + 1), v(m + 1), minv(m + 1);\n    vector<char>\
    \ used(m + 1);\n\n    for (int i = 1; i <= n; ++i) {\n        p[0] = i;\n    \
    \    fill(minv.begin(), minv.end(), numeric_limits<T>::max());\n        fill(used.begin(),\
    \ used.end(), 0);\n        int j0 = 0;\n        while (p[j0] != 0) {\n       \
    \     used[j0] = 1;\n            int i0 = p[j0], j1 = 0;\n            T delta\
    \ = numeric_limits<T>::max();\n            for (int j = 1; j <= m; ++j) {\n  \
    \              if (used[j]) continue;\n                T cur = a[i0][j] - u[i0]\
    \ - v[j];\n                if (cur < minv[j]) {\n                    minv[j] =\
    \ cur;\n                    way[j] = j0;\n                }\n                if\
    \ (minv[j] < delta) {\n                    delta = minv[j];\n                \
    \    j1 = j;\n                }\n            }\n            for (int j = 0; j\
    \ <= m; ++j) {\n                if (used[j]) {\n                    u[p[j]] +=\
    \ delta;\n                    v[j] -= delta;\n                } else {\n     \
    \               minv[j] -= delta;\n                }\n            }\n        \
    \    j0 = j1;\n        }\n        while (j0 != 0) {\n            int j1 = way[j0];\n\
    \            p[j0] = p[j1];\n            j0 = j1;\n        }\n    }\n\n    vector<int>\
    \ match(n, -1);\n    for (int j = 1; j <= m; ++j) {\n        if (p[j] != 0) match[p[j]\
    \ - 1] = j - 1;\n    }\n\n    vector<T> row(n), col(m);\n    for (int i = 0; i\
    \ < n; ++i) row[i] = u[i + 1];\n    for (int j = 0; j < m; ++j) col[j] = v[j +\
    \ 1];\n    T ans = -v[0];\n    if (!Minimize) {\n        ans = -ans;\n       \
    \ for (int i = 0; i < n; ++i) row[i] = -row[i];\n        for (int j = 0; j < m;\
    \ ++j) col[j] = -col[j];\n    }\n    return {ans, match, row, col};\n}\n\n/**\n\
    \ * @brief \u30CF\u30F3\u30AC\u30EA\u30A2\u30F3\u6CD5(Hungarian Algorithm)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: flow/hungarian.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_assignment_hungarian.test.cpp
date: 2026-03-08
documentation_of: flow/hungarian.cpp
layout: document
tags: "\u30D5\u30ED\u30FC"
title: "\u30CF\u30F3\u30AC\u30EA\u30A2\u30F3\u6CD5(Hungarian Algorithm)"
---

## 説明
二部割当問題の最適解を $O(N^2 M)$ で求める。
`N <= M` の長方形行列に対応し、各行を異なる列へ 1 つずつ割り当てる。

## できること
- `hungarian<T, Minimize>(cost)`
  コスト行列 `cost` に対する最適値、各行の割当先列、行側双対変数、列側双対変数を返す
- `Minimize=true`
  最小コスト割当を求める
- `Minimize=false`
  最大コスト割当を求める

返り値は `tuple<T, vector<int>, vector<T>, vector<T>>` で、順に次を表す。
- 最適値
- `match[i]`: 行 `i` を割り当てた列番号
- `row[i]`: 行側双対変数
- `col[j]`: 列側双対変数

`Minimize=true` では `row[i] + col[j] <= cost[i][j]` を満たし、最適値は双対和と一致する。

## 使い方
行数が列数以下のコスト行列を渡す。

```cpp
vector<vector<long long>> cost = {
    {3, 5, 4},
    {6, 1, 9},
};
auto [ans, match, row, col] = hungarian<long long>(cost);
```

最大化したいなら `hungarian<long long, false>(cost)` を使う。

## 実装上の補足
空行列には `0` と空ベクトルを返す。
各行の長さが揃っていること、`N <= M` を `assert` する。
