---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj2257.test.cpp
    title: test/aoj2257.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/ahocorasick.md
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
    \    inline int next(int x, char c){ return v[x].to[c-start]; }\n};\n/**\n * @brief\
    \ Aho-Corasick\u6CD5\n * @docs _md/ahocorasick.md\n */\n"
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
    \ char c){ return v[x].to[c-start]; }\n};\n/**\n * @brief Aho-Corasick\u6CD5\n\
    \ * @docs _md/ahocorasick.md\n */"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/ahocorasick.cpp
  requiredBy: []
  timestamp: '2020-04-26 18:02:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj2257.test.cpp
documentation_of: datastructure/ahocorasick.cpp
layout: document
redirect_from:
- /library/datastructure/ahocorasick.cpp
- /library/datastructure/ahocorasick.cpp.html
title: "Aho-Corasick\u6CD5"
---
## 説明
Trie木に対応するパターンマッチングオートマトンを構築する。

## 操作
- $\mathrm{add}(s, cur))$ : Trie木の位置$cur$に文字列$s$を追加し、そのノードを返す。
- $\mathrm{build}()$ : パターンマッチングオートマトンを構築する。
- $\mathrm{next}(x, c)$ : 位置xに文字$c$を与えたときの行き先を返す。