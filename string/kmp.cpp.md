---
category: "\u6587\u5B57\u5217"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_alds1_14_b.test.cpp
    title: test/aoj_alds1_14_b.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "KMP\u6CD5"
    links: []
  bundledCode: "#line 1 \"string/kmp.cpp\"\nvector<int> kmp_table(const string &s){\n\
    \    int n = s.size();\n    vector<int> table(n + 1);\n    table[0] = -1;\n  \
    \  for (int i = 0, j = -1; i < n;) {\n        while(j >= 0 && s[i] != s[j]) j\
    \ = table[j];\n        i++, j++;\n        table[i] = j;\n    }\n    return table;\n\
    }\n\nvector<int> kmp_search(const string &text, const string &pattern){\n    int\
    \ n = text.size(), m = pattern.size();\n    vector<int> res;\n    if(pattern.empty()){\n\
    \        res.resize(n + 1);\n        iota(res.begin(), res.end(), 0);\n      \
    \  return res;\n    }\n    auto table = kmp_table(pattern);\n    for (int i =\
    \ 0, j = 0; i < n;) {\n        while(j >= 0 && text[i] != pattern[j]) j = table[j];\n\
    \        i++, j++;\n        if(j == m){\n            res.emplace_back(i - j);\n\
    \            j = table[j];\n        }\n    }\n    return res;\n}\n\n/**\n * @brief\
    \ KMP\u6CD5\n */\n"
  code: "vector<int> kmp_table(const string &s){\n    int n = s.size();\n    vector<int>\
    \ table(n + 1);\n    table[0] = -1;\n    for (int i = 0, j = -1; i < n;) {\n \
    \       while(j >= 0 && s[i] != s[j]) j = table[j];\n        i++, j++;\n     \
    \   table[i] = j;\n    }\n    return table;\n}\n\nvector<int> kmp_search(const\
    \ string &text, const string &pattern){\n    int n = text.size(), m = pattern.size();\n\
    \    vector<int> res;\n    if(pattern.empty()){\n        res.resize(n + 1);\n\
    \        iota(res.begin(), res.end(), 0);\n        return res;\n    }\n    auto\
    \ table = kmp_table(pattern);\n    for (int i = 0, j = 0; i < n;) {\n        while(j\
    \ >= 0 && text[i] != pattern[j]) j = table[j];\n        i++, j++;\n        if(j\
    \ == m){\n            res.emplace_back(i - j);\n            j = table[j];\n  \
    \      }\n    }\n    return res;\n}\n\n/**\n * @brief KMP\u6CD5\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: string/kmp.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj_alds1_14_b.test.cpp
date: 2026-03-08
documentation_of: string/kmp.cpp
layout: document
tags: "\u6587\u5B57\u5217"
title: KMP
---

## 概要

Knuth-Morris-Pratt 法。
文字列 `pattern` の失敗関数テーブルを `kmp_table` で構築し、
`kmp_search(text, pattern)` で `pattern` の出現開始位置を列挙する。

## 計算量

- `kmp_table(s)` : $O(|s|)$
- `kmp_search(text, pattern)` : $O(|text| + |pattern|)$

## 使い方

1. `auto pos = kmp_search(text, pattern);`
2. `pos` に一致開始位置（0-indexed）が昇順で入る

## 実装上の補足

- `pattern` が空文字列のときは、`0..|text|` のすべてを返す。
