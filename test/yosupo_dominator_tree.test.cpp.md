---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/dominatortree.cpp
    title: Dominator Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
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
    \ = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\nusing ull = unsigned\
    \ long long;\nusing namespace std;\n\ntemplate<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\
    \n#line 1 \"graph/dominatortree.cpp\"\nclass DominatorTree {\n    struct CSR {\n\
    \        vector<int> start, elist;\n\n        CSR() = default;\n\n        CSR(int\
    \ n, const vector<pair<int, int>> &edges, bool rev) : start(n + 1), elist(edges.size())\
    \ {\n            for (auto &&[a, b] : edges) {\n                ++start[(rev ?\
    \ b : a) + 1];\n            }\n            for (int i = 0; i < n; ++i) start[i\
    \ + 1] += start[i];\n            auto counter = start;\n            for (auto\
    \ &&[a, b] : edges) {\n                int from = rev ? b : a;\n             \
    \   int to = rev ? a : b;\n                elist[counter[from]++] = to;\n    \
    \        }\n        }\n    };\n\n    int n;\n    vector<pair<int, int>> edges;\n\
    \    void unite(int x, int y){\n        uf_par[y] = x;\n    }\n\n    int compress(int\
    \ x){\n        if(uf_par[x] == x) return x;\n        int r = compress(uf_par[x]);\n\
    \        if(semi[m[x]] > semi[m[uf_par[x]]]) m[x] = m[uf_par[x]];\n        return\
    \ uf_par[x] = r;\n    }\n\n    int eval(int x){\n        compress(x);\n      \
    \  return m[x];\n    }\npublic:\n    DominatorTree(int n) : n(n), semi(n), ord(n),\
    \ par(n), uf_par(n), m(n), U(n), idom(n), bucket_head(n), bucket_next(n) {}\n\n\
    \    vector<int> semi, ord, par, uf_par, m, U, idom;\n    vector<int> bucket_head,\
    \ bucket_next;\n\n    void add_edge(int a, int b){\n        edges.emplace_back(a,\
    \ b);\n    }\n    void build(int root){\n        CSR G(n, edges, false), Grev(n,\
    \ edges, true);\n        for (int i = 0; i < n; ++i) {\n            uf_par[i]\
    \ = i;\n            m[i] = i;\n            semi[i] = -1;\n            idom[i]\
    \ = -1;\n            par[i] = -1;\n            bucket_head[i] = -1;\n        \
    \    bucket_next[i] = -1;\n        }\n        int cur = 0;\n        auto dfs =\
    \ [&](auto &&self, int x) -> void {\n            semi[x] = cur;\n            ord[cur++]\
    \ = x;\n            for (int ei = G.start[x]; ei < G.start[x + 1]; ++ei) {\n \
    \               int to = G.elist[ei];\n                if(!~semi[to]){\n     \
    \               par[to] = x;\n                    self(self, to);\n          \
    \      }\n            }\n        };\n        par[root] = root;\n        dfs(dfs,\
    \ root);\n        for (int i = cur-1; i >= 0; --i) {\n            int a = ord[i];\n\
    \            for (int ei = Grev.start[a]; ei < Grev.start[a + 1]; ++ei) {\n  \
    \              int b = Grev.elist[ei];\n                if(~semi[b]){\n      \
    \              int c = eval(b);\n                    semi[a] = min(semi[a], semi[c]);\n\
    \                }\n            }\n            bucket_next[a] = bucket_head[ord[semi[a]]];\n\
    \            bucket_head[ord[semi[a]]] = a;\n            int p = par[a];\n   \
    \         for (int b = bucket_head[p]; b != -1; b = bucket_next[b]) {\n      \
    \          U[b] = eval(b);\n            }\n            bucket_head[p] = -1;\n\
    \            unite(p, a);\n        }\n        for (int i = 1; i < cur; ++i) {\n\
    \            int a = ord[i], b = U[a];\n            if(semi[a] == semi[b]) idom[a]\
    \ = semi[a];\n            else idom[a] = idom[b];\n        }\n        for (int\
    \ i = 1; i < cur; ++i) {\n            int a = ord[i];\n            idom[a] = ord[idom[a]];\n\
    \        }\n        idom[root] = -1;\n    }\n\n};\n\n\n/**\n * @brief Dominator\
    \ Tree\n */\n#line 22 \"test/yosupo_dominator_tree.test.cpp\"\n\nint main() {\n\
    \    int n, m, s;\n    scanf(\"%d %d %d\", &n, &m, &s);\n    DominatorTree G(n);\n\
    \    for (int i = 0; i < m; ++i) {\n        int a, b;\n        scanf(\"%d %d\"\
    , &a, &b);\n        G.add_edge(a, b);\n    }\n    G.build(s);\n    for (int i\
    \ = 0; i < n; ++i) {\n        if(i) printf(\" \");\n        printf(\"%d\", (i\
    \ == s ? s : G.idom[i]));\n    }\n    puts(\"\");\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dominatortree\"\n\n#include\
    \ <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n\
    #include <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\n\
    static const int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\n\
    using ull = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
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
  timestamp: '2026-04-11 14:28:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_dominator_tree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_dominator_tree.test.cpp
- /verify/test/yosupo_dominator_tree.test.cpp.html
title: test/yosupo_dominator_tree.test.cpp
---
