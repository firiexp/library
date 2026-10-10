---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/lowlink.cpp
    title: LowLink
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B
  bundledCode: "#line 1 \"test/aoj_grl_3_b.test.cpp\"\n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B\"\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing\
    \ uint = unsigned;\nusing ull = unsigned long long;\nusing namespace std;\n\n\
    template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n\
    #line 1 \"graph/lowlink.cpp\"\nclass LowLink {\n    struct CSR {\n        vector<int>\
    \ start, elist;\n\n        CSR() = default;\n\n        CSR(int n, const vector<pair<int,\
    \ int>> &edges) : start(n + 1), elist(edges.size() * 2) {\n            for (auto\
    \ &&[u, v] : edges) {\n                ++start[u + 1];\n                ++start[v\
    \ + 1];\n            }\n            for (int i = 0; i < n; ++i) start[i + 1] +=\
    \ start[i];\n            auto counter = start;\n            for (int id = 0; id\
    \ < (int)edges.size(); ++id) {\n                auto &&[u, v] = edges[id];\n \
    \               elist[counter[u]++] = id;\n                elist[counter[v]++]\
    \ = id;\n            }\n        }\n    };\n\n    int n = 0;\n    int other(int\
    \ id, int v) const {\n        return edges[id].first ^ edges[id].second ^ v;\n\
    \    }\n\n    void dfs(int i, int pe, const CSR &G, int &pos){\n        ord[i]\
    \ = low[i] = pos++;\n        int ch = 0;\n        bool is_art = false;\n     \
    \   for (int ei = G.start[i]; ei < G.start[i + 1]; ++ei) {\n            int id\
    \ = G.elist[ei];\n            if(id == pe) continue;\n            int j = other(id,\
    \ i);\n            if(~ord[j]){\n                low[i] = min(low[i], ord[j]);\n\
    \                continue;\n            }\n            par[j] = i;\n         \
    \   ch++;\n            dfs(j, id, G, pos);\n            low[i] = min(low[i], low[j]);\n\
    \            if(pe != -1 && ord[i] <= low[j]) is_art = true;\n            if(ord[i]\
    \ < low[j]) bridge.emplace_back(min(i, j), max(i, j));\n        }\n        if(pe\
    \ == -1 && ch > 1) is_art = true;\n        cut[i] = is_art;\n    }\n\n    void\
    \ sort_bridges(CSR &G) {\n        int b = (int)bridge.size();\n        if (b <=\
    \ 1) return;\n        int lg = 32 - __builtin_clz((unsigned)(b - 1));\n      \
    \  if (1LL * b * lg <= n) {\n            sort(bridge.begin(), bridge.end());\n\
    \            return;\n        }\n        fill(G.start.begin(), G.start.end(),\
    \ 0);\n        for (auto [u, v] : bridge) ++G.start[v + 1];\n        for (int\
    \ i = 0; i < n; ++i) G.start[i + 1] += G.start[i];\n        for (auto [u, v] :\
    \ bridge) {\n            int p = G.start[v]++;\n            G.elist[2 * p] = u;\n\
    \            G.elist[2 * p + 1] = v;\n        }\n        fill(G.start.begin(),\
    \ G.start.end(), 0);\n        for (int i = 0; i < b; ++i) ++G.start[G.elist[2\
    \ * i] + 1];\n        for (int i = 0; i < n; ++i) G.start[i + 1] += G.start[i];\n\
    \        for (int i = 0; i < b; ++i) {\n            int u = G.elist[2 * i], v\
    \ = G.elist[2 * i + 1];\n            bridge[G.start[u]++] = {u, v};\n        }\n\
    \    }\npublic:\n    vector<int> ord, low, par, articulation;\n    vector<pair<int,\
    \ int>> bridge;\n    vector<pair<int, int>> edges;\n    vector<char> cut;\n  \
    \  LowLink() = default;\n    explicit LowLink(int n): n(n), ord(n, -1), low(n),\
    \ par(n, -1), cut(n){}\n\n    void add_edge(int u, int v){\n        if(u == v)\
    \ return;\n        edges.emplace_back(u, v);\n    }\n\n    void build(){\n   \
    \     CSR G(n, edges);\n        int pos = 0;\n        fill(ord.begin(), ord.end(),\
    \ -1);\n        fill(par.begin(), par.end(), -1);\n        fill(cut.begin(), cut.end(),\
    \ 0);\n        articulation.clear();\n        bridge.clear();\n        for (int\
    \ i = 0; i < n; ++i) {\n            if(!~ord[i]) dfs(i, -1, G, pos);\n       \
    \ }\n        for (int i = 0; i < n; ++i) {\n            if(cut[i]) articulation.emplace_back(i);\n\
    \        }\n        sort_bridges(G);\n    }\n\n    inline bool is_bridge(int i,\
    \ int j){\n        if(ord[i] > ord[j]) swap(i, j);\n        return ord[i] < low[j];\n\
    \    }\n};\n\n/**\n * @brief LowLink\n */\n#line 21 \"test/aoj_grl_3_b.test.cpp\"\
    \n\nint main() {\n    int n, m;\n    cin >> n >> m;\n    LowLink G(n);\n    for\
    \ (int i = 0; i < m; ++i) {\n        int s, t;\n        scanf(\"%d %d\", &s, &t);\n\
    \        G.add_edge(s, t);\n    }\n    G.build();\n    for (auto &&e : G.bridge)\
    \ {\n        printf(\"%d %d\\n\", e.first, e.second);\n    }\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B\"\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing\
    \ uint = unsigned;\nusing ull = unsigned long long;\nusing namespace std;\n\n\
    template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n\
    #include \"../graph/lowlink.cpp\"\n\nint main() {\n    int n, m;\n    cin >> n\
    \ >> m;\n    LowLink G(n);\n    for (int i = 0; i < m; ++i) {\n        int s,\
    \ t;\n        scanf(\"%d %d\", &s, &t);\n        G.add_edge(s, t);\n    }\n  \
    \  G.build();\n    for (auto &&e : G.bridge) {\n        printf(\"%d %d\\n\", e.first,\
    \ e.second);\n    }\n    return 0;\n}\n"
  dependsOn:
  - graph/lowlink.cpp
  isVerificationFile: true
  path: test/aoj_grl_3_b.test.cpp
  requiredBy: []
  timestamp: '2026-10-10 16:25:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj_grl_3_b.test.cpp
layout: document
redirect_from:
- /verify/test/aoj_grl_3_b.test.cpp
- /verify/test/aoj_grl_3_b.test.cpp.html
title: test/aoj_grl_3_b.test.cpp
---
