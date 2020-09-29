---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/SCC.cpp
    title: graph/SCC.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
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
    \ u32 = unsigned;\nusing u64 = unsigned long long;\nusing namespace std;\n\ntemplate<class\
    \ T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#line 1 \"graph/SCC.cpp\"\
    \nclass SCC {\n    void dfs(int v){\n        used[v] = 1;\n        for (auto &&u\
    \ : G[v]) if(!used[u]) dfs(u);\n        vs.emplace_back(v);\n    }\n\n    void\
    \ dfs_r(int v, int k){\n        used[v] = 1;\n        cmp[v] = k;\n        sz[k]++;\n\
    \        for (auto &&u : G_r[v]) if(!used[u]) dfs_r(u, k);\n    }\npublic:\n \
    \   vector<vector<int>> G, G_r, G_out;\n    vector<int> vs, used, cmp, sz;\n \
    \   SCC() = default;\n    explicit SCC(int n) : G(n), G_r(n), G_out(n), used(n),\
    \ cmp(n), sz(n) {}\n\n    void add_edge(int a, int b){\n        G[a].emplace_back(b);\n\
    \        G_r[b].emplace_back(a);\n    }\n\n    int build() {\n        int n =\
    \ G.size();\n        for (int i = 0; i < n; ++i) if(!used[i]) dfs(i);\n      \
    \  fill(used.begin(),used.end(), 0);\n        int k = 0;\n        for (int i =\
    \ n - 1; i >= 0; --i) {\n            if(!used[vs[i]]){\n                dfs_r(vs[i],\
    \ k++);\n            }\n        }\n        G_out.resize(k);\n        sz.resize(k);\n\
    \        for (int i = 0; i < n; ++i) {\n            for (auto &&j : G[i]) {\n\
    \                if(cmp[i] != cmp[j]){\n                    G_out[cmp[i]].emplace_back(cmp[j]);\n\
    \                }\n            }\n        }\n        for (auto &&l : G_out) {\n\
    \            sort(l.begin(), l.end());\n            l.erase(unique(l.begin(),\
    \ l.end()), l.end());\n        }\n        return k;\n    }\n\n    int operator[](int\
    \ k) const { return cmp[k]; }\n};\n#line 21 \"test/yosupo_scc.test.cpp\"\n\nint\
    \ main() {\n    int n, m;\n    cin >> n >> m;\n    SCC G(n);\n    for (int i =\
    \ 0; i < m; ++i) {\n        int a, b;\n        scanf(\"%d %d\", &a, &b);\n   \
    \     G.add_edge(a, b);\n    }\n    printf(\"%d\\n\", G.build());\n    vector<vector<int>>\
    \ res(G.sz.size());\n    for (int i = 0; i < n; ++i) {\n        res[G[i]].emplace_back(i);\n\
    \    }\n    for (int i = 0; i < G.sz.size(); ++i) {\n        printf(\"%d\", G.sz[i]);\n\
    \        for (auto &&j : res[i]) {\n            printf(\" %d\", j);\n        }\n\
    \        puts(\"\");\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/scc\"\n#include <iostream>\n\
    #include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n#include\
    \ <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\nstatic const\
    \ int MOD = 1000000007;\nusing ll = long long;\nusing u32 = unsigned;\nusing u64\
    \ = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr T\
    \ INF = ::numeric_limits<T>::max()/32*15+208;\n\n#include \"../graph/SCC.cpp\"\
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
  timestamp: '2020-09-13 16:56:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_scc.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_scc.test.cpp
- /verify/test/yosupo_scc.test.cpp.html
title: test/yosupo_scc.test.cpp
---
