---
category: "\u6587\u5B57\u5217"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_number_of_substrings_suffix_automaton.test.cpp
    title: test/yosupo_number_of_substrings_suffix_automaton.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Suffix Automaton
    links: []
  bundledCode: "#line 1 \"string/suffix_automaton.cpp\"\ntemplate<int W, char start\
    \ = 'a'>\nstruct SuffixAutomaton {\n    struct Node {\n        int link;\n   \
    \     int len;\n        int occ;\n        int next[W];\n        Node(int link\
    \ = -1, int len = 0, int occ = 0): link(link), len(len), occ(occ) {\n        \
    \    fill(next, next + W, -1);\n        }\n    };\n\n    vector<Node> nodes;\n\
    \    int last;\n\n    SuffixAutomaton(): nodes(1), last(0) {}\n\n    template<class\
    \ Container>\n    explicit SuffixAutomaton(const Container &s): SuffixAutomaton()\
    \ {\n        reserve(s.size());\n        for (auto &&c : s) add(c);\n    }\n\n\
    \    void reserve(int n) {\n        nodes.reserve(2 * n + 1);\n    }\n\n    static\
    \ int ord(char c) {\n        return c - start;\n    }\n\n    int add(char c) {\n\
    \        int k = ord(c);\n        int cur = nodes.size();\n        nodes.emplace_back(0,\
    \ nodes[last].len + 1, 1);\n        int p = last;\n        while (p != -1 && nodes[p].next[k]\
    \ == -1) {\n            nodes[p].next[k] = cur;\n            p = nodes[p].link;\n\
    \        }\n        if (p == -1) {\n            nodes[cur].link = 0;\n       \
    \     last = cur;\n            return cur;\n        }\n        int q = nodes[p].next[k];\n\
    \        if (nodes[p].len + 1 == nodes[q].len) {\n            nodes[cur].link\
    \ = q;\n            last = cur;\n            return cur;\n        }\n        int\
    \ clone = nodes.size();\n        nodes.push_back(nodes[q]);\n        nodes[clone].len\
    \ = nodes[p].len + 1;\n        nodes[clone].occ = 0;\n        while (p != -1 &&\
    \ nodes[p].next[k] == q) {\n            nodes[p].next[k] = clone;\n          \
    \  p = nodes[p].link;\n        }\n        nodes[q].link = nodes[cur].link = clone;\n\
    \        last = cur;\n        return cur;\n    }\n\n    template<class Container>\n\
    \    void build(const Container &s) {\n        reserve(s.size());\n        for\
    \ (auto &&c : s) add(c);\n    }\n\n    long long count_distinct_substrings() const\
    \ {\n        long long res = 0;\n        for (int i = 1; i < (int)nodes.size();\
    \ ++i) {\n            res += nodes[i].len - nodes[nodes[i].link].len;\n      \
    \  }\n        return res;\n    }\n\n    vector<int> order_by_length() const {\n\
    \        int max_len = 0;\n        for (auto &&node : nodes) max_len = max(max_len,\
    \ node.len);\n        vector<int> cnt(max_len + 1);\n        for (auto &&node\
    \ : nodes) cnt[node.len]++;\n        for (int i = 1; i <= max_len; ++i) cnt[i]\
    \ += cnt[i - 1];\n        vector<int> ord(nodes.size());\n        for (int i =\
    \ (int)nodes.size() - 1; i >= 0; --i) {\n            ord[--cnt[nodes[i].len]]\
    \ = i;\n        }\n        return ord;\n    }\n\n    vector<int> substring_occurrences()\
    \ const {\n        auto cnt = nodes;\n        auto ord = order_by_length();\n\
    \        for (int i = (int)ord.size() - 1; i >= 1; --i) {\n            int v =\
    \ ord[i];\n            cnt[cnt[v].link].occ += cnt[v].occ;\n        }\n      \
    \  vector<int> res(nodes.size());\n        for (int i = 0; i < (int)nodes.size();\
    \ ++i) res[i] = cnt[i].occ;\n        return res;\n    }\n};\n/**\n * @brief Suffix\
    \ Automaton\n */\n"
  code: "template<int W, char start = 'a'>\nstruct SuffixAutomaton {\n    struct Node\
    \ {\n        int link;\n        int len;\n        int occ;\n        int next[W];\n\
    \        Node(int link = -1, int len = 0, int occ = 0): link(link), len(len),\
    \ occ(occ) {\n            fill(next, next + W, -1);\n        }\n    };\n\n   \
    \ vector<Node> nodes;\n    int last;\n\n    SuffixAutomaton(): nodes(1), last(0)\
    \ {}\n\n    template<class Container>\n    explicit SuffixAutomaton(const Container\
    \ &s): SuffixAutomaton() {\n        reserve(s.size());\n        for (auto &&c\
    \ : s) add(c);\n    }\n\n    void reserve(int n) {\n        nodes.reserve(2 *\
    \ n + 1);\n    }\n\n    static int ord(char c) {\n        return c - start;\n\
    \    }\n\n    int add(char c) {\n        int k = ord(c);\n        int cur = nodes.size();\n\
    \        nodes.emplace_back(0, nodes[last].len + 1, 1);\n        int p = last;\n\
    \        while (p != -1 && nodes[p].next[k] == -1) {\n            nodes[p].next[k]\
    \ = cur;\n            p = nodes[p].link;\n        }\n        if (p == -1) {\n\
    \            nodes[cur].link = 0;\n            last = cur;\n            return\
    \ cur;\n        }\n        int q = nodes[p].next[k];\n        if (nodes[p].len\
    \ + 1 == nodes[q].len) {\n            nodes[cur].link = q;\n            last =\
    \ cur;\n            return cur;\n        }\n        int clone = nodes.size();\n\
    \        nodes.push_back(nodes[q]);\n        nodes[clone].len = nodes[p].len +\
    \ 1;\n        nodes[clone].occ = 0;\n        while (p != -1 && nodes[p].next[k]\
    \ == q) {\n            nodes[p].next[k] = clone;\n            p = nodes[p].link;\n\
    \        }\n        nodes[q].link = nodes[cur].link = clone;\n        last = cur;\n\
    \        return cur;\n    }\n\n    template<class Container>\n    void build(const\
    \ Container &s) {\n        reserve(s.size());\n        for (auto &&c : s) add(c);\n\
    \    }\n\n    long long count_distinct_substrings() const {\n        long long\
    \ res = 0;\n        for (int i = 1; i < (int)nodes.size(); ++i) {\n          \
    \  res += nodes[i].len - nodes[nodes[i].link].len;\n        }\n        return\
    \ res;\n    }\n\n    vector<int> order_by_length() const {\n        int max_len\
    \ = 0;\n        for (auto &&node : nodes) max_len = max(max_len, node.len);\n\
    \        vector<int> cnt(max_len + 1);\n        for (auto &&node : nodes) cnt[node.len]++;\n\
    \        for (int i = 1; i <= max_len; ++i) cnt[i] += cnt[i - 1];\n        vector<int>\
    \ ord(nodes.size());\n        for (int i = (int)nodes.size() - 1; i >= 0; --i)\
    \ {\n            ord[--cnt[nodes[i].len]] = i;\n        }\n        return ord;\n\
    \    }\n\n    vector<int> substring_occurrences() const {\n        auto cnt =\
    \ nodes;\n        auto ord = order_by_length();\n        for (int i = (int)ord.size()\
    \ - 1; i >= 1; --i) {\n            int v = ord[i];\n            cnt[cnt[v].link].occ\
    \ += cnt[v].occ;\n        }\n        vector<int> res(nodes.size());\n        for\
    \ (int i = 0; i < (int)nodes.size(); ++i) res[i] = cnt[i].occ;\n        return\
    \ res;\n    }\n};\n/**\n * @brief Suffix Automaton\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: string/suffix_automaton.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_number_of_substrings_suffix_automaton.test.cpp
date: 2026-03-08
documentation_of: string/suffix_automaton.cpp
layout: post
tags: "\u6587\u5B57\u5217"
title: suffix automaton
---

## 概要

Suffix Automaton を構築する。
文字列中の全ての部分文字列を状態として圧縮表現でき、異なる部分文字列数や各状態の出現回数集計に使える。
この実装は固定文字種向けの配列遷移で、速度を優先している。

## 計算量

- 構築 : `O(|S|)`
- `count_distinct_substrings()` : `O(|states|)`
- `substring_occurrences()` : `O(|states| + max_len)`

文字種数 `W` はテンプレート引数。各状態の遷移は固定長配列 `int next[W]` で保持する。

## 使い方

1. `SuffixAutomaton<26, 'a'> sam(s);` のように文字種数と開始文字を指定して構築する
2. `sam.add(c)` で 1 文字ずつ伸ばしてもよい
3. `sam.count_distinct_substrings()` で異なる部分文字列数を得る
4. `sam.substring_occurrences()` で各状態に対応する endpos サイズを得る

## 実装上の補足

- `nodes[v].len` は状態 `v` が表す文字列の最大長。
- `nodes[v].link` は suffix link。
- `nodes[v].next` は遷移。
- `add(c)` に渡す文字は `start <= c < start + W` を満たす前提。
- `substring_occurrences()` の戻り値は状態ごとの出現回数で、クローン状態は構築時 `0` から集約する。
