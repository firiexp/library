---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0294.test.cpp
    title: test/aoj0294.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_dominator_tree.test.cpp
    title: test/yosupo_dominator_tree.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/dominatortree.md
    document_title: Dominator Tree
    links: []
  bundledCode: "#line 1 \"graph/dominatortree.cpp\"\nclass DominatorTree {\n    int\
    \ n;\n    void unite(int x, int y){\n        uf_par[y] = x;\n    }\n\n    int\
    \ compress(int x){\n        if(uf_par[x] == x) return x;\n        int r = compress(uf_par[x]);\n\
    \        if(semi[m[x]] > semi[m[uf_par[x]]]) m[x] = m[uf_par[x]];\n        return\
    \ uf_par[x] = r;\n    }\n\n    int eval(int x){\n        compress(x);\n      \
    \  return m[x];\n    }\n\n\n    void dfs(int x, int &cur){\n        semi[x] =\
    \ cur;\n        ord[cur++] = x;\n        for (auto &&i : G[x]) {\n           \
    \ if(!~semi[i]){\n                par[i] = x;\n                dfs(i, cur);\n\
    \            }\n        }\n    }\npublic:\n    DominatorTree(int n) : n(n), G(n),\
    \ Grev(n), idom(n), semi(n), ord(n), par(n), uf_par(n), m(n), tmp(n), U(n) {}\n\
    \n    vector<vector<int>> G, Grev, tmp;\n    vector<int> semi, ord, par, uf_par,\
    \ m, U, idom;\n\n    void add_edge(int a, int b){\n        G[a].emplace_back(b);\n\
    \        Grev[b].emplace_back(a);\n    }\n    void build(int root){\n        for\
    \ (int i = 0; i < n; ++i) uf_par[i] = i, m[i] = i, semi[i] = -1, idom[i] = -1;\n\
    \        int cur = 0;\n        dfs(root, cur);\n        for (int i = cur-1; i\
    \ >= 0; --i) {\n            int a = ord[i];\n            for (auto &&b : Grev[a])\
    \ {\n                if(~semi[b]){\n                    int c = eval(b);\n   \
    \                 semi[a] = min(semi[a], semi[c]);\n                }\n      \
    \      }\n            tmp[ord[semi[a]]].emplace_back(a);\n            for (auto\
    \ &&b : tmp[par[a]]) U[b] = eval(b);\n            tmp[par[a]].clear();\n     \
    \       unite(par[a], a);\n        }\n        for (int i = 1; i < cur; ++i) {\n\
    \            int a = ord[i], b = U[a];\n            if(semi[a] == semi[b]) idom[a]\
    \ = semi[a];\n            else idom[a] = idom[b];\n        }\n        for (int\
    \ i = 1; i < cur; ++i) {\n            int a = ord[i];\n            idom[a] = ord[idom[a]];\n\
    \        }\n        idom[root] = -1;\n    }\n\n};\n\n\n/**\n * @brief Dominator\
    \ Tree\n * @docs _md/dominatortree.md\n */\n"
  code: "class DominatorTree {\n    int n;\n    void unite(int x, int y){\n      \
    \  uf_par[y] = x;\n    }\n\n    int compress(int x){\n        if(uf_par[x] ==\
    \ x) return x;\n        int r = compress(uf_par[x]);\n        if(semi[m[x]] >\
    \ semi[m[uf_par[x]]]) m[x] = m[uf_par[x]];\n        return uf_par[x] = r;\n  \
    \  }\n\n    int eval(int x){\n        compress(x);\n        return m[x];\n   \
    \ }\n\n\n    void dfs(int x, int &cur){\n        semi[x] = cur;\n        ord[cur++]\
    \ = x;\n        for (auto &&i : G[x]) {\n            if(!~semi[i]){\n        \
    \        par[i] = x;\n                dfs(i, cur);\n            }\n        }\n\
    \    }\npublic:\n    DominatorTree(int n) : n(n), G(n), Grev(n), idom(n), semi(n),\
    \ ord(n), par(n), uf_par(n), m(n), tmp(n), U(n) {}\n\n    vector<vector<int>>\
    \ G, Grev, tmp;\n    vector<int> semi, ord, par, uf_par, m, U, idom;\n\n    void\
    \ add_edge(int a, int b){\n        G[a].emplace_back(b);\n        Grev[b].emplace_back(a);\n\
    \    }\n    void build(int root){\n        for (int i = 0; i < n; ++i) uf_par[i]\
    \ = i, m[i] = i, semi[i] = -1, idom[i] = -1;\n        int cur = 0;\n        dfs(root,\
    \ cur);\n        for (int i = cur-1; i >= 0; --i) {\n            int a = ord[i];\n\
    \            for (auto &&b : Grev[a]) {\n                if(~semi[b]){\n     \
    \               int c = eval(b);\n                    semi[a] = min(semi[a], semi[c]);\n\
    \                }\n            }\n            tmp[ord[semi[a]]].emplace_back(a);\n\
    \            for (auto &&b : tmp[par[a]]) U[b] = eval(b);\n            tmp[par[a]].clear();\n\
    \            unite(par[a], a);\n        }\n        for (int i = 1; i < cur; ++i)\
    \ {\n            int a = ord[i], b = U[a];\n            if(semi[a] == semi[b])\
    \ idom[a] = semi[a];\n            else idom[a] = idom[b];\n        }\n       \
    \ for (int i = 1; i < cur; ++i) {\n            int a = ord[i];\n            idom[a]\
    \ = ord[idom[a]];\n        }\n        idom[root] = -1;\n    }\n\n};\n\n\n/**\n\
    \ * @brief Dominator Tree\n * @docs _md/dominatortree.md\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/dominatortree.cpp
  requiredBy: []
  timestamp: '2020-06-10 18:46:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0294.test.cpp
  - test/yosupo_dominator_tree.test.cpp
documentation_of: graph/dominatortree.cpp
layout: document
redirect_from:
- /library/graph/dominatortree.cpp
- /library/graph/dominatortree.cpp.html
title: Dominator Tree
---
## 説明
頂点$r$から任意の頂点に到達可能であるとき、$r$を始点としたDominator Treeを構築する。
