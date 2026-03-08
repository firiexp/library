---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/biconnected_components.cpp
    title: "\u4E8C\u91CD\u9023\u7D50\u6210\u5206\u5206\u89E3(Biconnected Components)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/biconnected_components
    links:
    - https://judge.yosupo.jp/problem/biconnected_components
  bundledCode: "#line 1 \"test/yosupo_biconnected_components.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/biconnected_components\"\n#include <iostream>\n\
    #include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n#include\
    \ <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\nstatic const\
    \ int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\nusing\
    \ ull = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#line 1 \"graph/biconnected_components.cpp\"\
    \nclass BiconnectedComponents {\n    vector<int> st;\n    void dfs(int i, int\
    \ pe, int &pos){\n        ord[i] = low[i] = pos++;\n        for (auto &&e : G[i])\
    \ {\n            int j = e.first, id = e.second;\n            if(id == pe) continue;\n\
    \            if(ord[j] < ord[i]) st.emplace_back(id);\n            if(~ord[j]){\n\
    \                low[i] = min(low[i], ord[j]);\n                continue;\n  \
    \          }\n            par[j] = i;\n            dfs(j, id, pos);\n        \
    \    low[i] = min(low[i], low[j]);\n            if(ord[i] <= low[j]){\n      \
    \          bcc_edges.emplace_back();\n                while(true){\n         \
    \           int k = st.back();\n                    st.pop_back();\n         \
    \           bcc_edges.back().emplace_back(min(edges[k].first, edges[k].second),\
    \ max(edges[k].first, edges[k].second));\n                    if(k == id) break;\n\
    \                }\n            }\n        }\n    }\npublic:\n    vector<int>\
    \ ord, low, par;\n    vector<pair<int, int>> edges;\n    vector<vector<pair<int,\
    \ int>>> G;\n    vector<vector<pair<int, int>>> bcc_edges;\n    vector<vector<int>>\
    \ bcc_vertices;\n    explicit BiconnectedComponents(int n): ord(n, -1), low(n),\
    \ par(n, -1), G(n){}\n\n    void add_edge(int u, int v){\n        if(u != v){\n\
    \            int id = edges.size();\n            edges.emplace_back(u, v);\n \
    \           G[u].emplace_back(v, id);\n            G[v].emplace_back(u, id);\n\
    \        }\n    }\n\n    int build(){\n        int n = G.size(), pos = 0;\n  \
    \      fill(ord.begin(), ord.end(), -1);\n        fill(par.begin(), par.end(),\
    \ -1);\n        bcc_edges.clear();\n        bcc_vertices.clear();\n        st.clear();\n\
    \        for (int i = 0; i < n; ++i) {\n            if(ord[i] < 0) dfs(i, -1,\
    \ pos);\n        }\n        vector<int> seen(n, -1);\n        bcc_vertices.reserve(bcc_edges.size());\n\
    \        for (int i = 0; i < (int)bcc_edges.size(); ++i) {\n            vector<int>\
    \ now;\n            for (auto &&e : bcc_edges[i]) {\n                if(seen[e.first]\
    \ != i){\n                    seen[e.first] = i;\n                    now.emplace_back(e.first);\n\
    \                }\n                if(seen[e.second] != i){\n               \
    \     seen[e.second] = i;\n                    now.emplace_back(e.second);\n \
    \               }\n            }\n            bcc_vertices.emplace_back(now);\n\
    \        }\n        for (int i = 0; i < n; ++i) {\n            if(G[i].empty()){\n\
    \                bcc_edges.emplace_back();\n                bcc_vertices.push_back({i});\n\
    \            }\n        }\n        return bcc_vertices.size();\n    }\n};\n\n\
    /**\n * @brief \u4E8C\u91CD\u9023\u7D50\u6210\u5206\u5206\u89E3(Biconnected Components)\n\
    \ * @docs _md/biconnected_components.md\n */\n#line 21 \"test/yosupo_biconnected_components.test.cpp\"\
    \n\nint main() {\n    int n, m;\n    cin >> n >> m;\n    BiconnectedComponents\
    \ G(n);\n    for (int i = 0; i < m; ++i) {\n        int a, b;\n        scanf(\"\
    %d %d\", &a, &b);\n        G.add_edge(a, b);\n    }\n    G.build();\n    auto\
    \ res = G.bcc_vertices;\n    for (auto &&v : res) sort(v.begin(), v.end());\n\
    \    sort(res.begin(), res.end());\n    cout << res.size() << \"\\n\";\n    for\
    \ (auto &&v : res) {\n        cout << v.size();\n        for (auto &&x : v) cout\
    \ << \" \" << x;\n        cout << \"\\n\";\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/biconnected_components\"\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing\
    \ uint = unsigned;\nusing ull = unsigned long long;\nusing namespace std;\n\n\
    template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n\
    #include \"../graph/biconnected_components.cpp\"\n\nint main() {\n    int n, m;\n\
    \    cin >> n >> m;\n    BiconnectedComponents G(n);\n    for (int i = 0; i <\
    \ m; ++i) {\n        int a, b;\n        scanf(\"%d %d\", &a, &b);\n        G.add_edge(a,\
    \ b);\n    }\n    G.build();\n    auto res = G.bcc_vertices;\n    for (auto &&v\
    \ : res) sort(v.begin(), v.end());\n    sort(res.begin(), res.end());\n    cout\
    \ << res.size() << \"\\n\";\n    for (auto &&v : res) {\n        cout << v.size();\n\
    \        for (auto &&x : v) cout << \" \" << x;\n        cout << \"\\n\";\n  \
    \  }\n    return 0;\n}\n"
  dependsOn:
  - graph/biconnected_components.cpp
  isVerificationFile: true
  path: test/yosupo_biconnected_components.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_biconnected_components.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_biconnected_components.test.cpp
- /verify/test/yosupo_biconnected_components.test.cpp.html
title: test/yosupo_biconnected_components.test.cpp
---
