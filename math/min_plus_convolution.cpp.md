---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_min_plus_convolution_arbitrary_convex.test.cpp
    title: test/yosupo_min_plus_convolution_arbitrary_convex.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_min_plus_convolution_convex_arbitrary.test.cpp
    title: test/yosupo_min_plus_convolution_convex_arbitrary.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_min_plus_convolution_convex_convex.test.cpp
    title: test/yosupo_min_plus_convolution_convex_convex.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "min-plus\u7573\u307F\u8FBC\u307F(Min-Plus Convolution)"
    links: []
  bundledCode: "#line 1 \"math/min_plus_convolution.cpp\"\n#include <algorithm>\n\
    #include <vector>\nusing namespace std;\n\ntemplate<class T, class F>\nvector<T>\
    \ min_plus_convolution_monotone(int n, int m, F f) {\n    vector<T> res(n + m\
    \ - 1);\n    auto dfs = [&](auto &&self, int left, int right, int opt_left, int\
    \ opt_right) -> void {\n        if (left > right) return;\n        int mid = (left\
    \ + right) >> 1;\n        int from = max(opt_left, max(0, mid - (m - 1)));\n \
    \       int to = min(opt_right, min(n - 1, mid));\n        int best = from;\n\
    \        T best_value = f(mid, from);\n        for (int i = from + 1; i <= to;\
    \ ++i) {\n            T value = f(mid, i);\n            if (value < best_value)\
    \ {\n                best = i;\n                best_value = value;\n        \
    \    }\n        }\n        res[mid] = best_value;\n        self(self, left, mid\
    \ - 1, opt_left, best);\n        self(self, mid + 1, right, best, opt_right);\n\
    \    };\n    dfs(dfs, 0, n + m - 2, 0, n - 1);\n    return res;\n}\n\ntemplate<class\
    \ T>\nvector<T> min_plus_convolution_arbitrary_convex(const vector<T> &a, const\
    \ vector<T> &b) {\n    if (a.empty() || b.empty()) return {};\n    int n = a.size(),\
    \ m = b.size();\n    return min_plus_convolution_monotone<T>(n, m, [&](int k,\
    \ int i) {\n        return a[i] + b[k - i];\n    });\n}\n\ntemplate<class T>\n\
    vector<T> min_plus_convolution_convex_arbitrary(const vector<T> &a, const vector<T>\
    \ &b) {\n    if (a.empty() || b.empty()) return {};\n    vector<T> ra(a.rbegin(),\
    \ a.rend());\n    vector<T> rb(b.rbegin(), b.rend());\n    auto res = min_plus_convolution_arbitrary_convex(rb,\
    \ ra);\n    reverse(res.begin(), res.end());\n    return res;\n}\n\ntemplate<class\
    \ T>\nvector<T> min_plus_convolution_convex_convex(const vector<T> &a, const vector<T>\
    \ &b) {\n    if (a.empty() || b.empty()) return {};\n    int n = a.size(), m =\
    \ b.size();\n    vector<T> res(n + m - 1);\n    int i = 0, j = 0;\n    res[0]\
    \ = a[0] + b[0];\n    for (int k = 1; k < n + m - 1; ++k) {\n        if (i ==\
    \ n - 1) {\n            ++j;\n        } else if (j == m - 1) {\n            ++i;\n\
    \        } else if (a[i + 1] + b[j] < a[i] + b[j + 1]) {\n            ++i;\n \
    \       } else {\n            ++j;\n        }\n        res[k] = a[i] + b[j];\n\
    \    }\n    return res;\n}\n\n/**\n * @brief min-plus\u7573\u307F\u8FBC\u307F\
    (Min-Plus Convolution)\n */\n"
  code: "#include <algorithm>\n#include <vector>\nusing namespace std;\n\ntemplate<class\
    \ T, class F>\nvector<T> min_plus_convolution_monotone(int n, int m, F f) {\n\
    \    vector<T> res(n + m - 1);\n    auto dfs = [&](auto &&self, int left, int\
    \ right, int opt_left, int opt_right) -> void {\n        if (left > right) return;\n\
    \        int mid = (left + right) >> 1;\n        int from = max(opt_left, max(0,\
    \ mid - (m - 1)));\n        int to = min(opt_right, min(n - 1, mid));\n      \
    \  int best = from;\n        T best_value = f(mid, from);\n        for (int i\
    \ = from + 1; i <= to; ++i) {\n            T value = f(mid, i);\n            if\
    \ (value < best_value) {\n                best = i;\n                best_value\
    \ = value;\n            }\n        }\n        res[mid] = best_value;\n       \
    \ self(self, left, mid - 1, opt_left, best);\n        self(self, mid + 1, right,\
    \ best, opt_right);\n    };\n    dfs(dfs, 0, n + m - 2, 0, n - 1);\n    return\
    \ res;\n}\n\ntemplate<class T>\nvector<T> min_plus_convolution_arbitrary_convex(const\
    \ vector<T> &a, const vector<T> &b) {\n    if (a.empty() || b.empty()) return\
    \ {};\n    int n = a.size(), m = b.size();\n    return min_plus_convolution_monotone<T>(n,\
    \ m, [&](int k, int i) {\n        return a[i] + b[k - i];\n    });\n}\n\ntemplate<class\
    \ T>\nvector<T> min_plus_convolution_convex_arbitrary(const vector<T> &a, const\
    \ vector<T> &b) {\n    if (a.empty() || b.empty()) return {};\n    vector<T> ra(a.rbegin(),\
    \ a.rend());\n    vector<T> rb(b.rbegin(), b.rend());\n    auto res = min_plus_convolution_arbitrary_convex(rb,\
    \ ra);\n    reverse(res.begin(), res.end());\n    return res;\n}\n\ntemplate<class\
    \ T>\nvector<T> min_plus_convolution_convex_convex(const vector<T> &a, const vector<T>\
    \ &b) {\n    if (a.empty() || b.empty()) return {};\n    int n = a.size(), m =\
    \ b.size();\n    vector<T> res(n + m - 1);\n    int i = 0, j = 0;\n    res[0]\
    \ = a[0] + b[0];\n    for (int k = 1; k < n + m - 1; ++k) {\n        if (i ==\
    \ n - 1) {\n            ++j;\n        } else if (j == m - 1) {\n            ++i;\n\
    \        } else if (a[i + 1] + b[j] < a[i] + b[j + 1]) {\n            ++i;\n \
    \       } else {\n            ++j;\n        }\n        res[k] = a[i] + b[j];\n\
    \    }\n    return res;\n}\n\n/**\n * @brief min-plus\u7573\u307F\u8FBC\u307F\
    (Min-Plus Convolution)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/min_plus_convolution.cpp
  requiredBy: []
  timestamp: '2026-03-11 00:57:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_min_plus_convolution_convex_convex.test.cpp
  - test/yosupo_min_plus_convolution_convex_arbitrary.test.cpp
  - test/yosupo_min_plus_convolution_arbitrary_convex.test.cpp
date: 2026-03-11
documentation_of: math/min_plus_convolution.cpp
layout: document
tags: "\u6570\u5B66"
title: "min-plus\u7573\u307F\u8FBC\u307F(Min-Plus Convolution)"
---

## 説明
`c[k] = min_i (a[i] + b[k - i])` を計算する。
配列の凸性に応じて 3 種類の関数を使い分ける。

ここで凸とは、隣接差分が単調非減少であることを指す。

## できること
- `vector<T> min_plus_convolution_arbitrary_convex(const vector<T>& a, const vector<T>& b)`
  `a` を任意列、`b` を凸列として min-plus 畳み込みを返す。計算量は `O((N + M) log(N + M))`
- `vector<T> min_plus_convolution_convex_arbitrary(const vector<T>& a, const vector<T>& b)`
  `a` を凸列、`b` を任意列として min-plus 畳み込みを返す。計算量は `O((N + M) log(N + M))`
- `vector<T> min_plus_convolution_convex_convex(const vector<T>& a, const vector<T>& b)`
  `a, b` を凸列として min-plus 畳み込みを返す。計算量は `O(N + M)`

## 使い方
凸性がある側に応じて関数を選ぶ。
返り値の長さは常に `a.size() + b.size() - 1`。

`T` は `+` と `<` が使える型を想定する。
空配列を渡したときは空配列を返す。
