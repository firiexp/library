---
category: "\u6587\u5B57\u5217"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_lyndon_factorization.test.cpp
    title: test/yosupo_lyndon_factorization.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Lyndon\u5206\u89E3(Lyndon Factorization)"
    links: []
  bundledCode: "#line 1 \"string/lyndon_factorization.cpp\"\nusing namespace std;\n\
    \nvector<pair<int, int>> lyndon_factorization(const string &s) {\n    int n =\
    \ (int)s.size();\n    vector<pair<int, int>> res;\n    for (int i = 0; i < n;)\
    \ {\n        int j = i + 1, k = i;\n        while (j < n && s[k] <= s[j]) {\n\
    \            if (s[k] < s[j]) k = i;\n            else ++k;\n            ++j;\n\
    \        }\n        int len = j - k;\n        while (i <= k) {\n            res.emplace_back(i,\
    \ i + len);\n            i += len;\n        }\n    }\n    return res;\n}\n\n/**\n\
    \ * @brief Lyndon\u5206\u89E3(Lyndon Factorization)\n */\n"
  code: "using namespace std;\n\nvector<pair<int, int>> lyndon_factorization(const\
    \ string &s) {\n    int n = (int)s.size();\n    vector<pair<int, int>> res;\n\
    \    for (int i = 0; i < n;) {\n        int j = i + 1, k = i;\n        while (j\
    \ < n && s[k] <= s[j]) {\n            if (s[k] < s[j]) k = i;\n            else\
    \ ++k;\n            ++j;\n        }\n        int len = j - k;\n        while (i\
    \ <= k) {\n            res.emplace_back(i, i + len);\n            i += len;\n\
    \        }\n    }\n    return res;\n}\n\n/**\n * @brief Lyndon\u5206\u89E3(Lyndon\
    \ Factorization)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: string/lyndon_factorization.cpp
  requiredBy: []
  timestamp: '2026-03-12 00:49:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_lyndon_factorization.test.cpp
date: 2026-03-11
documentation_of: string/lyndon_factorization.cpp
layout: document
tags: "\u6587\u5B57\u5217"
title: "Lyndon\u5206\u89E3(Lyndon Factorization)"
---

## 説明
文字列を Lyndon word の非増加列に一意に分解する。
Duval algorithm により $O(|s|)$。

## できること
- `vector<pair<int, int>> lyndon_factorization(const string& s)`
  各因子の半開区間 `[l, r)` を順に返す。空文字列なら空 vector を返す

## 使い方
返り値の各区間を `s.substr(l, r - l)` として取り出せる。

```cpp
auto segs = lyndon_factorization(s);
for (auto &&[l, r] : segs) {
    string t = s.substr(l, r - l);
}
```

## 実装上の補足
- 返る因子列は辞書順で単調非増加
- 区間で返すので、追加の文字列コピーなしで他の処理に渡せる
