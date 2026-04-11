---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/SCC.cpp
    title: "\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3(SCC)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/scc
    links:
    - https://judge.yosupo.jp/problem/scc
  bundledCode: "#line 1 \"test/yosupo_scc.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/scc\"\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing\
    \ uint = unsigned;\nusing ull = unsigned long long;\nusing namespace std;\n\n\
    template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n\
    #line 1 \"graph/SCC.cpp\"\nclass SCC {\n    struct CSR {\n        vector<int>\
    \ start, elist;\n\n        CSR() = default;\n\n        CSR(int n, const vector<pair<int,\
    \ int>> &edges, bool rev) : start(n + 1), elist(edges.size()) {\n            for\
    \ (auto &&[a, b] : edges) {\n                ++start[(rev ? b : a) + 1];\n   \
    \         }\n            for (int i = 0; i < n; ++i) start[i + 1] += start[i];\n\
    \            auto counter = start;\n            for (auto &&[a, b] : edges) {\n\
    \                int from = rev ? b : a;\n                int to = rev ? a : b;\n\
    \                elist[counter[from]++] = to;\n            }\n        }\n    };\n\
    \n    int n = 0;\n    vector<pair<int, int>> edges;\n\npublic:\n    vector<vector<int>>\
    \ G_out;\n    vector<int> vs, used, cmp, sz;\n    SCC() = default;\n    explicit\
    \ SCC(int n) : n(n), used(n), cmp(n), sz(n) {}\n\n    void add_edge(int a, int\
    \ b){\n        edges.emplace_back(a, b);\n    }\n\n    int build() {\n       \
    \ CSR G(n, edges, false), G_r(n, edges, true);\n        vs.clear();\n        vs.reserve(n);\n\
    \        fill(used.begin(), used.end(), 0);\n        auto dfs = [&](auto &&self,\
    \ int v) -> void {\n            used[v] = 1;\n            for (int ei = G.start[v];\
    \ ei < G.start[v + 1]; ++ei) {\n                int u = G.elist[ei];\n       \
    \         if(!used[u]) self(self, u);\n            }\n            vs.emplace_back(v);\n\
    \        };\n        for (int i = 0; i < n; ++i) {\n            if(!used[i]) dfs(dfs,\
    \ i);\n        }\n        fill(used.begin(), used.end(), 0);\n        sz.resize(n);\n\
    \        fill(sz.begin(), sz.end(), 0);\n        int k = 0;\n        auto dfs_r\
    \ = [&](auto &&self, int v, int c) -> void {\n            used[v] = 1;\n     \
    \       cmp[v] = c;\n            sz[c]++;\n            for (int ei = G_r.start[v];\
    \ ei < G_r.start[v + 1]; ++ei) {\n                int u = G_r.elist[ei];\n   \
    \             if(!used[u]) self(self, u, c);\n            }\n        };\n    \
    \    for (int i = n - 1; i >= 0; --i) {\n            if(!used[vs[i]]){\n     \
    \           dfs_r(dfs_r, vs[i], k++);\n            }\n        }\n        G_out.assign(k,\
    \ {});\n        sz.resize(k);\n        for (auto &&[a, b] : edges) {\n       \
    \     if(cmp[a] != cmp[b]){\n                G_out[cmp[a]].emplace_back(cmp[b]);\n\
    \            }\n        }\n        for (auto &&l : G_out) {\n            sort(l.begin(),\
    \ l.end());\n            l.erase(unique(l.begin(), l.end()), l.end());\n     \
    \   }\n        return k;\n    }\n\n    int operator[](int k) const { return cmp[k];\
    \ }\n};\n\n/**\n * @brief \u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3(SCC)\n */\n\
    #line 21 \"test/yosupo_scc.test.cpp\"\n\nint main() {\n    int n, m;\n    cin\
    \ >> n >> m;\n    SCC G(n);\n    for (int i = 0; i < m; ++i) {\n        int a,\
    \ b;\n        scanf(\"%d %d\", &a, &b);\n        G.add_edge(a, b);\n    }\n  \
    \  printf(\"%d\\n\", G.build());\n    vector<vector<int>> res(G.sz.size());\n\
    \    for (int i = 0; i < n; ++i) {\n        res[G[i]].emplace_back(i);\n    }\n\
    \    for (int i = 0; i < G.sz.size(); ++i) {\n        printf(\"%d\", G.sz[i]);\n\
    \        for (auto &&j : res[i]) {\n            printf(\" %d\", j);\n        }\n\
    \        puts(\"\");\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/scc\"\n#include <iostream>\n\
    #include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n#include\
    \ <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\nstatic const\
    \ int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\nusing\
    \ ull = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#include \"../graph/SCC.cpp\"\
    \n\nint main() {\n    int n, m;\n    cin >> n >> m;\n    SCC G(n);\n    for (int\
    \ i = 0; i < m; ++i) {\n        int a, b;\n        scanf(\"%d %d\", &a, &b);\n\
    \        G.add_edge(a, b);\n    }\n    printf(\"%d\\n\", G.build());\n    vector<vector<int>>\
    \ res(G.sz.size());\n    for (int i = 0; i < n; ++i) {\n        res[G[i]].emplace_back(i);\n\
    \    }\n    for (int i = 0; i < G.sz.size(); ++i) {\n        printf(\"%d\", G.sz[i]);\n\
    \        for (auto &&j : res[i]) {\n            printf(\" %d\", j);\n        }\n\
    \        puts(\"\");\n    }\n    return 0;\n}"
  dependsOn:
  - graph/SCC.cpp
  isVerificationFile: true
  path: test/yosupo_scc.test.cpp
  requiredBy: []
  timestamp: '2026-04-11 14:07:08+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_scc.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_scc.test.cpp
- /verify/test/yosupo_scc.test.cpp.html
title: test/yosupo_scc.test.cpp
---
