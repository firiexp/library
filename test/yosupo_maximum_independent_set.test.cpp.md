---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/independentset.cpp
    title: graph/independentset.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/maximum_independent_set
    links:
    - https://judge.yosupo.jp/problem/maximum_independent_set
  bundledCode: "#line 1 \"test/yosupo_maximum_independent_set.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/maximum_independent_set\"\n#include\
    \ <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n\
    #include <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\n\
    static const int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\n\
    using ull = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\n#line 1 \"graph/independentset.cpp\"\
    \nclass IndependentSet {\n    int n;\n    vector<ull> G;\n    pair<int, ull> dfs(ull\
    \ R, ull P, ull X){\n        if(!P && !X){\n            return {__builtin_popcountll(R),\
    \ R};\n        }\n        if(!P) return {-1, 0};\n        pair<int, ull> res =\
    \ {-1, 0};\n        int pivot = __builtin_ctzll(P|X);\n        ull z = P & ~G[pivot];\n\
    \        for (int i = 0; i < n; ++i) {\n            if(z & (1ull << i)){\n   \
    \             res = max(res, dfs(R|(1ull << i), P&G[i], X&G[i]));\n          \
    \      P ^= 1ull << i;\n                X |= 1ull << i;\n            }\n     \
    \   }\n        return res;\n    }\n\n\npublic:\n    explicit IndependentSet(int\
    \ n): n(n), G(n) {\n        for (int i = 0; i < n; ++i) {\n            G[i] =\
    \ ((1ull << n)-1)^(1ull << i);\n        }\n    }\n    void add_edge(int u, int\
    \ v){\n        G[u] &= ~(1ull << v);\n        G[v] &= ~(1ull << u);\n    }\n \
    \   pair<int, ull> maximum_independent_set() {\n        return dfs(0, (1ull <<\
    \ n)-1, 0);\n    }\n};\n#line 21 \"test/yosupo_maximum_independent_set.test.cpp\"\
    \n\nint main() {\n    int n, m;\n    cin >> n >> m;\n    IndependentSet G(n);\n\
    \    for (int i = 0; i < m; ++i) {\n        int l, r;\n        cin >> l >> r;\n\
    \        G.add_edge(l, r);\n    }\n    auto res = G.maximum_independent_set();\n\
    \    cout << res.first << \"\\n\";\n    int cur = 0;\n    for (int i = 0; i <\
    \ n; ++i) {\n        if(res.second & (1ull << i)){\n            if(cur++) printf(\"\
    \ \");\n            printf(\"%d\", i);\n        }\n    }\n    puts(\"\");\n  \
    \  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/maximum_independent_set\"\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing\
    \ uint = unsigned;\nusing ull = unsigned long long;\nusing namespace std;\n\n\
    template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\
    \n#include \"../graph/independentset.cpp\"\n\nint main() {\n    int n, m;\n  \
    \  cin >> n >> m;\n    IndependentSet G(n);\n    for (int i = 0; i < m; ++i) {\n\
    \        int l, r;\n        cin >> l >> r;\n        G.add_edge(l, r);\n    }\n\
    \    auto res = G.maximum_independent_set();\n    cout << res.first << \"\\n\"\
    ;\n    int cur = 0;\n    for (int i = 0; i < n; ++i) {\n        if(res.second\
    \ & (1ull << i)){\n            if(cur++) printf(\" \");\n            printf(\"\
    %d\", i);\n        }\n    }\n    puts(\"\");\n    return 0;\n}"
  dependsOn:
  - graph/independentset.cpp
  isVerificationFile: true
  path: test/yosupo_maximum_independent_set.test.cpp
  requiredBy: []
  timestamp: '2021-06-23 00:43:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_maximum_independent_set.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_maximum_independent_set.test.cpp
- /verify/test/yosupo_maximum_independent_set.test.cpp.html
title: test/yosupo_maximum_independent_set.test.cpp
---
