---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj2257.test.cpp
    title: test/aoj2257.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aho_corasick.test.cpp
    title: test/yosupo_aho_corasick.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_aho_occurrences.test.cpp
    title: test/yosupo_aplusb_aho_occurrences.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Aho-Corasick\u6CD5"
    links: []
  bundledCode: "#line 1 \"datastructure/ahocorasick.cpp\"\ntemplate<int W, int start>\n\
    class AhoCorasick {\npublic:\n    struct Node {\n        array<int, W> to;\n \
    \       int fail;\n        int val;\n    };\n    explicit AhoCorasick() : v(1)\
    \ {}\n    vector<Node> v;\n    vector<int> ord;\n    int add(string &s, int cur\
    \ = 0){\n        for (auto &&i : s) {\n            if(!v[cur].to[i-start]) v[cur].to[i-start]\
    \ = v.size(), v.emplace_back();\n            cur = v[cur].to[i-start];\n     \
    \   }\n        return cur;\n    }\n\n    void build() {\n        v[0].fail = -1;\n\
    \        int l = 0, r = 1;\n        ord.clear();\n        ord.reserve(v.size());\n\
    \        ord.emplace_back(0);\n        while(l < r){\n            int i = ord[l];\
    \ l++;\n            for (int c = 0; c < W; ++c) {\n                if(!v[i].to[c])\
    \ continue;\n                int to = v[i].to[c];\n                v[to].fail\
    \ = (v[i].fail == -1 ? 0 : v[v[i].fail].to[c]);\n                ord.emplace_back(to);\n\
    \                r++;\n            }\n            if(i != 0){\n              \
    \  for (int c = 0; c < W; ++c) {\n                    if(!v[i].to[c]) v[i].to[c]\
    \ = v[v[i].fail].to[c];\n                }\n            }\n        }\n    }\n\
    \    inline int next(int x, char c){ return v[x].to[c-start]; }\n\n    vector<long\
    \ long> occurrence_counts(const string &text) const {\n        vector<long long>\
    \ counts(v.size());\n        counts[0] = 1;\n        int state = 0;\n        for\
    \ (char c : text) {\n            state = v[state].to[c - start];\n           \
    \ ++counts[state];\n        }\n        for (int i = (int)ord.size() - 1; i > 0;\
    \ --i) {\n            int state = ord[i];\n            counts[v[state].fail] +=\
    \ counts[state];\n        }\n        return counts;\n    }\n};\n/**\n * @brief\
    \ Aho-Corasick\u6CD5\n */\n"
  code: "template<int W, int start>\nclass AhoCorasick {\npublic:\n    struct Node\
    \ {\n        array<int, W> to;\n        int fail;\n        int val;\n    };\n\
    \    explicit AhoCorasick() : v(1) {}\n    vector<Node> v;\n    vector<int> ord;\n\
    \    int add(string &s, int cur = 0){\n        for (auto &&i : s) {\n        \
    \    if(!v[cur].to[i-start]) v[cur].to[i-start] = v.size(), v.emplace_back();\n\
    \            cur = v[cur].to[i-start];\n        }\n        return cur;\n    }\n\
    \n    void build() {\n        v[0].fail = -1;\n        int l = 0, r = 1;\n   \
    \     ord.clear();\n        ord.reserve(v.size());\n        ord.emplace_back(0);\n\
    \        while(l < r){\n            int i = ord[l]; l++;\n            for (int\
    \ c = 0; c < W; ++c) {\n                if(!v[i].to[c]) continue;\n          \
    \      int to = v[i].to[c];\n                v[to].fail = (v[i].fail == -1 ? 0\
    \ : v[v[i].fail].to[c]);\n                ord.emplace_back(to);\n            \
    \    r++;\n            }\n            if(i != 0){\n                for (int c\
    \ = 0; c < W; ++c) {\n                    if(!v[i].to[c]) v[i].to[c] = v[v[i].fail].to[c];\n\
    \                }\n            }\n        }\n    }\n    inline int next(int x,\
    \ char c){ return v[x].to[c-start]; }\n\n    vector<long long> occurrence_counts(const\
    \ string &text) const {\n        vector<long long> counts(v.size());\n       \
    \ counts[0] = 1;\n        int state = 0;\n        for (char c : text) {\n    \
    \        state = v[state].to[c - start];\n            ++counts[state];\n     \
    \   }\n        for (int i = (int)ord.size() - 1; i > 0; --i) {\n            int\
    \ state = ord[i];\n            counts[v[state].fail] += counts[state];\n     \
    \   }\n        return counts;\n    }\n};\n/**\n * @brief Aho-Corasick\u6CD5\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/ahocorasick.cpp
  requiredBy: []
  timestamp: '2026-10-07 22:14:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_aho_occurrences.test.cpp
  - test/aoj2257.test.cpp
  - test/yosupo_aho_corasick.test.cpp
documentation_of: datastructure/ahocorasick.cpp
layout: document
title: "Aho-Corasick\u6CD5"
---

## 説明
Trie 木に対応するパターンマッチングオートマトンを構築する。

## できること
ノード数を $V$、文字種数を $W$ とする。

- `add(s, cur)` : Trie 木の位置 `cur` に文字列 `s` を追加し、そのノードを返す
- `build()` : パターンマッチングオートマトンを $O(WV)$ で構築する
- `next(x, c)` : 位置 `x` に文字 `c` を与えたときの行き先を返す
- `occurrence_counts(text)` : ノード順の出現回数を `vector<long long>` で返す。時間 $O(|text|+V)$、追加領域 $O(V)$

## 使い方
先に `add` でパターンを追加し、その後 `build()` を呼ぶ。
`next` は構築後の遷移を返す。
`add(pattern)` の返す終端 ID を保存しておき、`occurrence_counts(text)[id]` で重なりを含む出現回数を得る。
重複パターンは同じノードを共有する。空パターンの終端は root で、回数は `text.size()+1`。
空テキストにも対応し、構築済みオートマトンを変更せず繰り返し問い合わせられる。
パターン・テキストの文字は `start <= c < start + W` を満たす前提。
