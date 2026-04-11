---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/twosat.cpp
    title: 2-SAT
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/two_sat
    links:
    - https://judge.yosupo.jp/problem/two_sat
  bundledCode: "#line 1 \"test/yosupo_twosat.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/two_sat\"\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing\
    \ uint = unsigned;\nusing ull = unsigned long long;\nusing namespace std;\n\n\
    template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;\n\n\
    #line 1 \"graph/twosat.cpp\"\nstruct SCC {\n    struct CSR {\n        vector<int>\
    \ start, elist;\n\n        CSR() = default;\n\n        CSR(int n, const vector<pair<int,\
    \ int>> &edges, bool rev) : start(n + 1), elist(edges.size()) {\n            for\
    \ (auto &&[a, b] : edges) {\n                ++start[(rev ? b : a) + 1];\n   \
    \         }\n            for (int i = 0; i < n; ++i) start[i + 1] += start[i];\n\
    \            auto counter = start;\n            for (auto &&[a, b] : edges) {\n\
    \                int from = rev ? b : a;\n                int to = rev ? a : b;\n\
    \                elist[counter[from]++] = to;\n            }\n        }\n    };\n\
    \n    int n = 0;\n    vector<pair<int, int>> edges;\n    vector<int> vs, used,\
    \ cmp;\n    SCC() = default;\n    explicit SCC(int n) : n(n), used(n), cmp(n)\
    \ {}\n\n    void add_edge(int a, int b){\n        edges.emplace_back(a, b);\n\
    \    }\n\n    int build() {\n        CSR G(n, edges, false), G_r(n, edges, true);\n\
    \        vs.clear();\n        vs.reserve(n);\n        fill(used.begin(), used.end(),\
    \ 0);\n        auto dfs = [&](auto &&self, int v) -> void {\n            used[v]\
    \ = 1;\n            for (int ei = G.start[v]; ei < G.start[v + 1]; ++ei) {\n \
    \               int u = G.elist[ei];\n                if(!used[u]) self(self,\
    \ u);\n            }\n            vs.emplace_back(v);\n        };\n        for\
    \ (int i = 0; i < n; ++i) {\n            if(!used[i]) dfs(dfs, i);\n        }\n\
    \        fill(used.begin(),used.end(), 0);\n        int k = 0;\n        auto dfs_r\
    \ = [&](auto &&self, int v, int c) -> void {\n            used[v] = 1;\n     \
    \       cmp[v] = c;\n            for (int ei = G_r.start[v]; ei < G_r.start[v\
    \ + 1]; ++ei) {\n                int u = G_r.elist[ei];\n                if(!used[u])\
    \ self(self, u, c);\n            }\n        };\n        for (int i = n - 1; i\
    \ >= 0; --i) {\n            if(!used[vs[i]]){\n                dfs_r(dfs_r, vs[i],\
    \ k++);\n            }\n        }\n        return k;\n    }\n\n    int operator[](int\
    \ k) const { return cmp[k]; }\n};\n\nstruct TwoSAT {\n    int n;\n    SCC scc;\n\
    \    explicit TwoSAT(int n) : n(n), scc(n*2) {};\n    int negate(int v){\n   \
    \     int ret = n+v;\n        if(ret >= n*2) ret -= n*2;\n        return ret;\n\
    \    }\n\n    vector<int> build() {\n        scc.build();\n        vector<int>\
    \ res(n);\n        for (int i = 0; i < n; ++i) {\n            if(scc[i] == scc[n+i])\
    \ return {};\n            res[i] = scc[i] > scc[n+i];\n        }\n        return\
    \ res;\n    }\n\n    void add_if(int u, int v){ // u -> v\n        scc.add_edge(u,\
    \ v);\n        scc.add_edge(negate(v), negate(u));\n    }\n\n    void add_or(int\
    \ u, int v){ // u || v\n        add_if(negate(u), v);\n    }\n};\n\n/**\n * @brief\
    \ 2-SAT\n */\n#line 21 \"test/yosupo_twosat.test.cpp\"\n\nint main() {\n    string\
    \ s, t;\n    int n, m;\n    cin >> s >> t >> n >> m;\n    TwoSAT G(n);\n    for\
    \ (int i = 0; i < m; ++i) {\n        int a, b; char x;\n        scanf(\" %d %d\
    \ %c\", &a, &b, &x);\n        if(a < 0) a = n-a;\n        if(b < 0) b = n-b;\n\
    \        G.add_or(a-1, b-1);\n    }\n    auto ans = G.build();\n    if(ans.empty()){\n\
    \        puts(\"s UNSATISFIABLE\");\n    }else {\n        puts(\"s SATISFIABLE\"\
    );\n        printf(\"v \");\n        for (int i = 0; i < ans.size(); ++i) {\n\
    \            if(ans[i]) printf(\"%d \", i+1);\n            else printf(\"%d \"\
    , -(i+1));\n        }\n        puts(\"0\");\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/two_sat\"\n#include <iostream>\n\
    #include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n#include\
    \ <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\nstatic const\
    \ int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\nusing\
    \ ull = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#include \"../graph/twosat.cpp\"\
    \n\nint main() {\n    string s, t;\n    int n, m;\n    cin >> s >> t >> n >> m;\n\
    \    TwoSAT G(n);\n    for (int i = 0; i < m; ++i) {\n        int a, b; char x;\n\
    \        scanf(\" %d %d %c\", &a, &b, &x);\n        if(a < 0) a = n-a;\n     \
    \   if(b < 0) b = n-b;\n        G.add_or(a-1, b-1);\n    }\n    auto ans = G.build();\n\
    \    if(ans.empty()){\n        puts(\"s UNSATISFIABLE\");\n    }else {\n     \
    \   puts(\"s SATISFIABLE\");\n        printf(\"v \");\n        for (int i = 0;\
    \ i < ans.size(); ++i) {\n            if(ans[i]) printf(\"%d \", i+1);\n     \
    \       else printf(\"%d \", -(i+1));\n        }\n        puts(\"0\");\n    }\n\
    \    return 0;\n}"
  dependsOn:
  - graph/twosat.cpp
  isVerificationFile: true
  path: test/yosupo_twosat.test.cpp
  requiredBy: []
  timestamp: '2026-04-11 14:28:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_twosat.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_twosat.test.cpp
- /verify/test/yosupo_twosat.test.cpp.html
title: test/yosupo_twosat.test.cpp
---
