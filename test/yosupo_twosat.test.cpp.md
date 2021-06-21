---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/twosat.cpp
    title: graph/twosat.cpp
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
    #line 1 \"graph/twosat.cpp\"\nstruct SCC {\n    vector<vector<int>> G, G_r, G_out;\n\
    \    vector<int> vs, used, cmp;\n    SCC() = default;\n    explicit SCC(int n)\
    \ : G(n), G_r(n), used(n), cmp(n) {}\n\n    void add_edge(int a, int b){\n   \
    \     G[a].emplace_back(b);\n        G_r[b].emplace_back(a);\n    }\n\n    void\
    \ dfs(int v){\n        used[v] = 1;\n        for (auto &&u : G[v]) if(!used[u])\
    \ dfs(u);\n        vs.emplace_back(v);\n    }\n\n    void dfs_r(int v, int k){\n\
    \        used[v] = 1;\n        cmp[v] = k;\n        for (auto &&u : G_r[v]) if(!used[u])\
    \ dfs_r(u, k);\n    }\n\n    int build() {\n        int n = G.size();\n      \
    \  for (int i = 0; i < n; ++i) if(!used[i]) dfs(i);\n        fill(used.begin(),used.end(),\
    \ 0);\n        int k = 0;\n        for (int i = n - 1; i >= 0; --i) {\n      \
    \      if(!used[vs[i]]){\n                dfs_r(vs[i], k++);\n            }\n\
    \        }\n        return k;\n    }\n\n    int operator[](int k) const { return\
    \ cmp[k]; }\n};\n\nstruct TwoSAT {\n    int n;\n    SCC scc;\n    explicit TwoSAT(int\
    \ n) : n(n), scc(n*2) {};\n    int negate(int v){\n        int ret = n+v;\n  \
    \      if(ret >= n*2) ret -= n*2;\n        return ret;\n    }\n\n    vector<int>\
    \ build() {\n        scc.build();\n        vector<int> res(n);\n        for (int\
    \ i = 0; i < n; ++i) {\n            if(scc[i] == scc[n+i]) return {};\n      \
    \      res[i] = scc[i] > scc[n+i];\n        }\n        return res;\n    }\n\n\
    \    void add_if(int u, int v){ // u -> v\n        scc.add_edge(u, v);\n     \
    \   scc.add_edge(negate(v), negate(u));\n    }\n\n    void add_or(int u, int v){\
    \ // u || v\n        add_if(negate(u), v);\n    }\n};\n#line 21 \"test/yosupo_twosat.test.cpp\"\
    \n\nint main() {\n    string s, t;\n    int n, m;\n    cin >> s >> t >> n >> m;\n\
    \    TwoSAT G(n);\n    for (int i = 0; i < m; ++i) {\n        int a, b; char x;\n\
    \        scanf(\" %d %d %c\", &a, &b, &x);\n        if(a < 0) a = n-a;\n     \
    \   if(b < 0) b = n-b;\n        G.add_or(a-1, b-1);\n    }\n    auto ans = G.build();\n\
    \    if(ans.empty()){\n        puts(\"s UNSATISFIABLE\");\n    }else {\n     \
    \   puts(\"s SATISFIABLE\");\n        printf(\"v \");\n        for (int i = 0;\
    \ i < ans.size(); ++i) {\n            if(ans[i]) printf(\"%d \", i+1);\n     \
    \       else printf(\"%d \", -(i+1));\n        }\n        puts(\"0\");\n    }\n\
    \    return 0;\n}\n"
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
  timestamp: '2021-06-21 15:24:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_twosat.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_twosat.test.cpp
- /verify/test/yosupo_twosat.test.cpp.html
title: test/yosupo_twosat.test.cpp
---
