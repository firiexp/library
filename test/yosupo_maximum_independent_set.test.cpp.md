---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/independentset.cpp
    title: "\u6700\u5927\u72EC\u7ACB\u96C6\u5408(Maximum Independent Set)"
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
    \nclass IndependentSet {\n    int n;\n    vector<ull> G;\n    ull full_mask()\
    \ const { return n == 64 ? ~0ull : (1ull << n) - 1; }\n    int color_bound(ull\
    \ vertices) const {\n        int colors = 0;\n        while (vertices) {\n   \
    \         ++colors;\n            ull available = vertices;\n            while\
    \ (available) {\n                int v = 63 - __builtin_clzll(available);\n  \
    \              ull bit = 1ull << v;\n                vertices &= ~bit;\n     \
    \           available &= ~bit & ~G[v];\n            }\n        }\n        return\
    \ colors;\n    }\n    void dfs(ull R, ull P, ull X, pair<int, ull> &best) {\n\
    \        if (!P && !X) {\n            best = max(best, pair<int, ull>{__builtin_popcountll(R),\
    \ R});\n            return;\n        }\n        if (!P) return;\n        int bound\
    \ = __builtin_popcountll(R) + color_bound(P);\n        if (bound < best.first\
    \ || (bound == best.first && (R | P) <= best.second)) return;\n        int pivot\
    \ = -1, max_neighbors = -1;\n        for (ull vertices = P | X; vertices; vertices\
    \ &= vertices - 1) {\n            int u = __builtin_ctzll(vertices);\n       \
    \     int neighbors = __builtin_popcountll(P & G[u]);\n            if (neighbors\
    \ >= max_neighbors) {\n                pivot = u;\n                max_neighbors\
    \ = neighbors;\n            }\n        }\n        ull z = P & ~G[pivot];\n   \
    \     while (z) {\n            int i = 63 - __builtin_clzll(z);\n            z\
    \ &= ~(1ull << i);\n            dfs(R | (1ull << i), P & G[i], X & G[i], best);\n\
    \            P ^= 1ull << i;\n            X |= 1ull << i;\n        }\n    }\n\n\
    \npublic:\n    explicit IndependentSet(int n): n(n), G(n) {\n        for (int\
    \ i = 0; i < n; ++i) {\n            G[i] = full_mask() ^ (1ull << i);\n      \
    \  }\n    }\n    void add_edge(int u, int v){\n        G[u] &= ~(1ull << v);\n\
    \        G[v] &= ~(1ull << u);\n    }\n    pair<int, ull> maximum_independent_set()\
    \ {\n        pair<int, ull> best = {-1, 0};\n        dfs(0, full_mask(), 0, best);\n\
    \        return best;\n    }\n};\n\n/**\n * @brief \u6700\u5927\u72EC\u7ACB\u96C6\
    \u5408(Maximum Independent Set)\n */\n#line 21 \"test/yosupo_maximum_independent_set.test.cpp\"\
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
  timestamp: '2026-10-14 20:34:24+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_maximum_independent_set.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_maximum_independent_set.test.cpp
- /verify/test/yosupo_maximum_independent_set.test.cpp.html
title: test/yosupo_maximum_independent_set.test.cpp
---
