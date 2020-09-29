---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/trie.cpp\"\ntemplate<int W, class F> // W\
    \ -> word size\nstruct Trie {\n    struct Node {\n        char c;\n        array<int,\
    \ W> nxt;\n        vector<int> idxs;\n        int id;\n        explicit Node(char\
    \ c): c(c), id(-1){\n            fill(nxt.begin(),nxt.end(), -1);\n        }\n\
    \    };\n    vector<Node> v;\n    F f;\n    explicit Trie(F f, char c = '$') :\
    \ f(f) {\n        v.emplace_back(c);\n    }\n    void add(const string &s, int\
    \ x){\n        int cur = 0;\n        for (auto &&i : s) {\n            int k =\
    \ f(i);\n            if(~v[cur].nxt[k]){\n                cur = v[cur].nxt[k];\n\
    \                continue;\n            }\n            int npos = v.size();\n\
    \            v[cur].nxt[k] = npos;\n            v.emplace_back(i);\n         \
    \   cur = npos;\n        }\n        v[cur].id = x;\n        v[cur].idxs.emplace_back(x);\n\
    \    }\n\n    int find(const string &s){\n        int cur = 0;\n        for (auto\
    \ &&i : s) {\n            int k = f(i);\n            if(v[cur].nxt[k] < 0) return\
    \ -1;\n            cur = v[cur].nxt[k];\n        }\n        return cur;\n    }\n\
    \    int find(int cur, char c) {return v[cur].nxt[f(c)]; }\n    int id(int cur)\
    \ { return cur < 0 ? -1 : v[cur].id;}\n\n    vector<int> idxs(int cur) { return\
    \ cur < 0 ? vector<int>() : v[cur].idxs; }\n};\n"
  code: "template<int W, class F> // W -> word size\nstruct Trie {\n    struct Node\
    \ {\n        char c;\n        array<int, W> nxt;\n        vector<int> idxs;\n\
    \        int id;\n        explicit Node(char c): c(c), id(-1){\n            fill(nxt.begin(),nxt.end(),\
    \ -1);\n        }\n    };\n    vector<Node> v;\n    F f;\n    explicit Trie(F\
    \ f, char c = '$') : f(f) {\n        v.emplace_back(c);\n    }\n    void add(const\
    \ string &s, int x){\n        int cur = 0;\n        for (auto &&i : s) {\n   \
    \         int k = f(i);\n            if(~v[cur].nxt[k]){\n                cur\
    \ = v[cur].nxt[k];\n                continue;\n            }\n            int\
    \ npos = v.size();\n            v[cur].nxt[k] = npos;\n            v.emplace_back(i);\n\
    \            cur = npos;\n        }\n        v[cur].id = x;\n        v[cur].idxs.emplace_back(x);\n\
    \    }\n\n    int find(const string &s){\n        int cur = 0;\n        for (auto\
    \ &&i : s) {\n            int k = f(i);\n            if(v[cur].nxt[k] < 0) return\
    \ -1;\n            cur = v[cur].nxt[k];\n        }\n        return cur;\n    }\n\
    \    int find(int cur, char c) {return v[cur].nxt[f(c)]; }\n    int id(int cur)\
    \ { return cur < 0 ? -1 : v[cur].id;}\n\n    vector<int> idxs(int cur) { return\
    \ cur < 0 ? vector<int>() : v[cur].idxs; }\n};"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/trie.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: datastructure/trie.cpp
layout: document
redirect_from:
- /library/datastructure/trie.cpp
- /library/datastructure/trie.cpp.html
title: datastructure/trie.cpp
---
