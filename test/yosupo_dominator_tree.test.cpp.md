---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/dominatortree.cpp
    title: Dominator Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dominatortree
    links:
    - https://judge.yosupo.jp/problem/dominatortree
  bundledCode: "#line 1 \"test/yosupo_dominator_tree.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/dominatortree\"\n\n#include <iostream>\n#include\
    \ <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n#include <stack>\n\
    #include <numeric>\n#include <bitset>\n#include <cmath>\n\nstatic const int MOD\
    \ = 1000000007;\nusing ll = long long;\nusing u32 = unsigned;\nusing u64 = unsigned\
    \ long long;\nusing namespace std;\n\ntemplate<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\
    \n#line 1 \"graph/dominatortree.cpp\"\nclass DominatorTree {\n    int n;\n   \
    \ void unite(int x, int y){\n        uf_par[y] = x;\n    }\n\n    int compress(int\
    \ x){\n        if(uf_par[x] == x) return x;\n        int r = compress(uf_par[x]);\n\
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
    \ Tree\n * @docs _md/dominatortree.md\n */\n#line 22 \"test/yosupo_dominator_tree.test.cpp\"\
    \n\nint main() {\n    int n, m, s;\n    scanf(\"%d %d %d\", &n, &m, &s);\n   \
    \ DominatorTree G(n);\n    for (int i = 0; i < m; ++i) {\n        int a, b;\n\
    \        scanf(\"%d %d\", &a, &b);\n        G.add_edge(a, b);\n    }\n    G.build(s);\n\
    \    for (int i = 0; i < n; ++i) {\n        if(i) printf(\" \");\n        printf(\"\
    %d\", (i == s ? s : G.idom[i]));\n    }\n    puts(\"\");\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dominatortree\"\n\n#include\
    \ <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n\
    #include <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\n\
    static const int MOD = 1000000007;\nusing ll = long long;\nusing u32 = unsigned;\n\
    using u64 = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#include \"../graph/dominatortree.cpp\"\
    \n\nint main() {\n    int n, m, s;\n    scanf(\"%d %d %d\", &n, &m, &s);\n   \
    \ DominatorTree G(n);\n    for (int i = 0; i < m; ++i) {\n        int a, b;\n\
    \        scanf(\"%d %d\", &a, &b);\n        G.add_edge(a, b);\n    }\n    G.build(s);\n\
    \    for (int i = 0; i < n; ++i) {\n        if(i) printf(\" \");\n        printf(\"\
    %d\", (i == s ? s : G.idom[i]));\n    }\n    puts(\"\");\n    return 0;\n}"
  dependsOn:
  - graph/dominatortree.cpp
  isVerificationFile: true
  path: test/yosupo_dominator_tree.test.cpp
  requiredBy: []
  timestamp: '2020-06-10 18:46:05+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_dominator_tree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_dominator_tree.test.cpp
- /verify/test/yosupo_dominator_tree.test.cpp.html
title: test/yosupo_dominator_tree.test.cpp
---
