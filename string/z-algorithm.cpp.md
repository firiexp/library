---
category: "\u6587\u5B57\u5217"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_many_aplusb_z_algorithm.test.cpp
    title: test/yosupo_many_aplusb_z_algorithm.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Z-Algorithm
    links: []
  bundledCode: "#line 1 \"string/z-algorithm.cpp\"\nvector<int> Z_algorithm(const\
    \ string &s){\n    int n = (int)s.size();\n    vector<int> res(n);\n    if (n\
    \ == 0) return res;\n    res[0] = n;\n    for (int i = 1, j = 0; i < n; ++i) {\n\
    \        int &k = res[i];\n        if (j + res[j] > i) k = min(res[i - j], j +\
    \ res[j] - i);\n        while (i + k < n && s[k] == s[i + k]) ++k;\n        if\
    \ (i + k > j + res[j]) j = i;\n    }\n    return res;\n}\n\n/**\n * @brief Z-Algorithm\n\
    \ */\n"
  code: "vector<int> Z_algorithm(const string &s){\n    int n = (int)s.size();\n \
    \   vector<int> res(n);\n    if (n == 0) return res;\n    res[0] = n;\n    for\
    \ (int i = 1, j = 0; i < n; ++i) {\n        int &k = res[i];\n        if (j +\
    \ res[j] > i) k = min(res[i - j], j + res[j] - i);\n        while (i + k < n &&\
    \ s[k] == s[i + k]) ++k;\n        if (i + k > j + res[j]) j = i;\n    }\n    return\
    \ res;\n}\n\n/**\n * @brief Z-Algorithm\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: string/z-algorithm.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_many_aplusb_z_algorithm.test.cpp
date: 2026-03-08
documentation_of: string/z-algorithm.cpp
layout: post
tags: "\u6587\u5B57\u5217"
title: Z-algorithm
---

## 説明
文字列 `s` の各位置 `i` について、`s` と `s[i, |s|)` の最長共通接頭辞長を `O(|s|)` で求める。
`res[i]` は `s[0..)` と `s[i..)` の LCP 長になる。

## できること
- `vector<int> Z_algorithm(const string& s)`
  Z 配列を返す。`res[0] = |s|`。空文字列なら空 vector を返す

## 使い方
`auto z = Z_algorithm(s);` として使う。
部分文字列検索では `pattern + '$' + text` のように連結し、`z[i] == pattern.size()` になる位置を拾えばよい。

```cpp
string t = pattern + '$' + text;
auto z = Z_algorithm(t);
for (int i = 0; i < (int)t.size(); ++i) {
    if (z[i] == (int)pattern.size()) {
        // pattern が一致
    }
}
```

## 実装上の補足
- 一致判定だけでなく、各 suffix と先頭の一致長をまとめて取りたいときに向く
- 返る配列は 0-indexed
- `'$'` のような区切り文字を使うときは、元の文字列に現れない文字を選ぶ
