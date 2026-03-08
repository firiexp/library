---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj2945_bfs01.test.cpp
    title: test/aoj2945_bfs01.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/template.md
    document_title: "\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8(Template)"
    links: []
  bundledCode: "#line 1 \"util/template.cpp\"\n// Contest template helper pieces (no\
    \ main function).\n// Full submission template lives in snippets/template.cpp.\n\
    \n#include <algorithm>\n#include <array>\n#include <bitset>\n#include <cmath>\n\
    #include <iostream>\n#include <limits>\n#include <map>\n#include <numeric>\n#include\
    \ <queue>\n#include <set>\n#include <stack>\n#include <unordered_map>\n\nstatic\
    \ const int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\n\
    using ull = unsigned long long;\nusing namespace std;\n\ntemplate<class T>\nconstexpr\
    \ T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\ntemplate<class T>\nT\
    \ ifloor(T x, T y){\n    return x/y-(x%y ? (x < 0)^(y < 0) : 0);\n}\n\ntemplate<class\
    \ T>\ninline T iceil(T x, T y){\n    return x/y+(x%y ? (x >= 0)^(y < 0) : 0);\n\
    }\n\ntemplate<class T>\ninline bool chmax(T& a, T b) {\n    if (a < b) {\n   \
    \     a = b;\n        return true;\n    }\n    return false;\n}\n\ntemplate<class\
    \ T>\ninline bool chmin(T& a, T b) {\n    if (a > b) {\n        a = b;\n     \
    \   return true;\n    }\n    return false;\n}\n\ntemplate <typename T>\nusing\
    \ GPQ = priority_queue<T, vector<T>, greater<T>>;\n\ntemplate<class T>\nvector<pair<T,\
    \ int>> RLE(const vector<T> &a){\n    vector<pair<T, int>> p;\n    if(a.empty())\
    \ return p;\n    p.emplace_back(a[0], 1);\n    for (int j = 1; j < (int)a.size();\
    \ ++j) {\n        if(p.back().first == a[j]) p.back().second++;\n        else\
    \ p.emplace_back(a[j], 1);\n    }\n    return p;\n}\n\n/**\n * @brief \u30C6\u30F3\
    \u30D7\u30EC\u30FC\u30C8(Template)\n * @docs _md/template.md\n */\n"
  code: "// Contest template helper pieces (no main function).\n// Full submission\
    \ template lives in snippets/template.cpp.\n\n#include <algorithm>\n#include <array>\n\
    #include <bitset>\n#include <cmath>\n#include <iostream>\n#include <limits>\n\
    #include <map>\n#include <numeric>\n#include <queue>\n#include <set>\n#include\
    \ <stack>\n#include <unordered_map>\n\nstatic const int MOD = 1000000007;\nusing\
    \ ll = long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\nusing\
    \ namespace std;\n\ntemplate<class T>\nconstexpr T INF = ::numeric_limits<T>::max()\
    \ / 32 * 15 + 208;\n\ntemplate<class T>\nT ifloor(T x, T y){\n    return x/y-(x%y\
    \ ? (x < 0)^(y < 0) : 0);\n}\n\ntemplate<class T>\ninline T iceil(T x, T y){\n\
    \    return x/y+(x%y ? (x >= 0)^(y < 0) : 0);\n}\n\ntemplate<class T>\ninline\
    \ bool chmax(T& a, T b) {\n    if (a < b) {\n        a = b;\n        return true;\n\
    \    }\n    return false;\n}\n\ntemplate<class T>\ninline bool chmin(T& a, T b)\
    \ {\n    if (a > b) {\n        a = b;\n        return true;\n    }\n    return\
    \ false;\n}\n\ntemplate <typename T>\nusing GPQ = priority_queue<T, vector<T>,\
    \ greater<T>>;\n\ntemplate<class T>\nvector<pair<T, int>> RLE(const vector<T>\
    \ &a){\n    vector<pair<T, int>> p;\n    if(a.empty()) return p;\n    p.emplace_back(a[0],\
    \ 1);\n    for (int j = 1; j < (int)a.size(); ++j) {\n        if(p.back().first\
    \ == a[j]) p.back().second++;\n        else p.emplace_back(a[j], 1);\n    }\n\
    \    return p;\n}\n\n/**\n * @brief \u30C6\u30F3\u30D7\u30EC\u30FC\u30C8(Template)\n\
    \ * @docs _md/template.md\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: util/template.cpp
  requiredBy: []
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj2945_bfs01.test.cpp
documentation_of: util/template.cpp
layout: document
redirect_from:
- /library/util/template.cpp
- /library/util/template.cpp.html
title: "\u30C6\u30F3\u30D7\u30EC\u30FC\u30C8(Template)"
---
---
layout: post
title: テンプレート
date: 2018-04-29
category: テンプレート
tags: テンプレート
---

## 説明
テンプレート
`snippets/template.cpp` にコンテスト用テンプレートを置く。
