---
category: "\u6587\u5B57\u5217"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_alds1_14_b.test.cpp
    title: test/aoj_alds1_14_b.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_kmp.test.cpp
    title: test/yosupo_aplusb_kmp.test.cpp
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
    \            j = table[j];\n        }\n    }\n    return res;\n}\n\nclass KMPMatcher\
    \ {\n    string pattern;\n    vector<int> table;\n    int matched = 0;\n    long\
    \ long position = 0;\n    bool announced = false;\n\npublic:\n    explicit KMPMatcher(const\
    \ string &pattern): pattern(pattern), table(kmp_table(pattern)) {}\n\n    void\
    \ reset() {\n        matched = 0;\n        position = 0;\n        announced =\
    \ false;\n    }\n\n    template<class Emit>\n    void scan(string_view chunk,\
    \ Emit &&emit) {\n        if (pattern.empty()) {\n            if (!announced)\
    \ {\n                announced = true;\n                emit(position);\n    \
    \        }\n            for (size_t i = 0; i < chunk.size(); ++i) emit(++position);\n\
    \            return;\n        }\n        for (char c : chunk) {\n            while\
    \ (matched >= 0 && c != pattern[matched]) matched = table[matched];\n        \
    \    ++matched;\n            ++position;\n            if (matched == (int)pattern.size())\
    \ {\n                matched = table[matched];\n                emit(position\
    \ - (long long)pattern.size());\n            }\n        }\n    }\n};\n\n/**\n\
    \ * @brief KMP\u6CD5\n */\n"
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
    \      }\n    }\n    return res;\n}\n\nclass KMPMatcher {\n    string pattern;\n\
    \    vector<int> table;\n    int matched = 0;\n    long long position = 0;\n \
    \   bool announced = false;\n\npublic:\n    explicit KMPMatcher(const string &pattern):\
    \ pattern(pattern), table(kmp_table(pattern)) {}\n\n    void reset() {\n     \
    \   matched = 0;\n        position = 0;\n        announced = false;\n    }\n\n\
    \    template<class Emit>\n    void scan(string_view chunk, Emit &&emit) {\n \
    \       if (pattern.empty()) {\n            if (!announced) {\n              \
    \  announced = true;\n                emit(position);\n            }\n       \
    \     for (size_t i = 0; i < chunk.size(); ++i) emit(++position);\n          \
    \  return;\n        }\n        for (char c : chunk) {\n            while (matched\
    \ >= 0 && c != pattern[matched]) matched = table[matched];\n            ++matched;\n\
    \            ++position;\n            if (matched == (int)pattern.size()) {\n\
    \                matched = table[matched];\n                emit(position - (long\
    \ long)pattern.size());\n            }\n        }\n    }\n};\n\n/**\n * @brief\
    \ KMP\u6CD5\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: string/kmp.cpp
  requiredBy: []
  timestamp: '2026-10-17 18:43:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_kmp.test.cpp
  - test/aoj_alds1_14_b.test.cpp
date: 2026-03-08
documentation_of: string/kmp.cpp
layout: document
tags: "\u6587\u5B57\u5217"
title: "KMP\u6CD5"
---

## 説明

Knuth-Morris-Pratt 法で、テキスト中のパターンの出現開始位置を列挙する。
一度だけ検索するなら `kmp_search` を使う。
同じパターンで複数のテキストを検索するときや、テキストを分割して読み込むときは `KMPMatcher` で前処理を再利用できる。

## できること

### 単発検索

- `vector<int> kmp_table(s)` : 失敗関数テーブルを $O(|s|)$ で返す
- `vector<int> kmp_search(text, pattern)` : 一致開始位置を昇順で返す。位置は0-indexed。$O(|text| + |pattern|)$

### KMPMatcher

- `KMPMatcher matcher(pattern)` : `pattern` からテーブルを構築する。時間・保持領域は $O(|pattern|)$
- `void scan(chunk, emit)` : `string_view` の `chunk` を前回の入力の続きとして検索する。一致ごとに `emit(long long pos)` を呼び、連結したテキスト上の0-indexed開始位置を渡す。コールバックの処理を除き、償却 $O(|chunk|+1)$
- `void reset()` : 照合状態と通算位置を初期化し、次のテキストを検索できる状態に戻す。テーブルは再利用する。$O(1)$

通算文字数は `long long`、パターン長は `int` に収まる前提とする。

## 使い方

単発検索は `auto pos = kmp_search(text, pattern);` でよい。

### KMPMatcher

テキストを分割して渡す場合は、同じ matcher の `scan` を順に呼ぶ。

```cpp
KMPMatcher matcher("aba");
vector<long long> positions;
auto emit = [&](long long pos) { positions.push_back(pos); };
matcher.scan("ab", emit);
matcher.scan("aba", emit);
```

連結した `"ababa"` の位置 `0, 2` が `positions` に入る。
入力の切れ目をまたぐ一致や、互いに重なる一致も列挙する。

別のテキストを検索するときは `matcher.reset()` を呼んでから `scan` に渡す。
例えば `reset()` 後に `"aba"` を渡すと、新しいテキストの位置 `0` を通知する。
`reset()` が初期化するのは matcher の状態だけなので、保存先の `positions` は必要に応じて呼出し側で空にする。
コールバック内で一致数だけを数えれば、一致位置を保存する領域は不要。

## 実装上の補足

- 空パターンの `kmp_search` は文字間と両端の境界 `0..|text|` をすべて返す。
- 空パターンの `scan` は初回の位置 `0` と各文字後の境界を1回ずつ通知する。空の `chunk` を繰り返しても重複通知しない。`reset()` 後は位置 `0` から通知し直す。
- 入力はバイト列として比較し、埋め込まれた NUL も扱う。
- コールバックから同じ matcher の `scan` / `reset` を呼ばない。
