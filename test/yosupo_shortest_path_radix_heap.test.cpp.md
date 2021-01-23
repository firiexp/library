---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/radixheap.cpp
    title: datastructure/radixheap.cpp
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra_radix_heap.cpp
    title: "Dijkstra\u6CD5(Radix Heap)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/shortest_path
    links:
    - https://judge.yosupo.jp/problem/shortest_path
  bundledCode: "#line 1 \"test/yosupo_shortest_path_radix_heap.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\n\n#include <iostream>\n\
    #include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n#include\
    \ <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\nstatic const\
    \ int MOD = 1000000007;\nusing ll = long long;\nusing u32 = unsigned;\nusing u64\
    \ = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr T\
    \ INF = ::numeric_limits<T>::max()/32*15+208;\n\n#line 1 \"graph/dijkstra_radix_heap.cpp\"\
    \ntemplate <typename T>\nstruct edge {\n    int from, to; T cost;\n    edge(int\
    \ to, T cost) : from(-1), to(to), cost(cost) {}\n    edge(int from, int to, T\
    \ cost) : from(from), to(to), cost(cost) {}\n};\n\n#line 1 \"datastructure/radixheap.cpp\"\
    \ntemplate <class K, class V>\nclass RadixHeap {\n    static constexpr int bit_length\
    \ = sizeof(K)*8;\n    K last;\n    size_t sz, cnt;\n    \n    array<vector<pair<K,\
    \ V>>, bit_length> v;\n    static inline int bsr(int x){\n        return x ? bit_length-__builtin_clz(x)\
    \ : 0;\n    }\n    static inline int bsr(ll x){\n        return x ? bit_length-__builtin_clzll(x)\
    \ : 0;\n    }\n\n    void pull() {\n        if(cnt < v[0].size()) return;;\n \
    \       int i = 1;\n        while(v[i].empty()) i++;\n        last = min_element(v[i].begin(),v[i].end())->first;\n\
    \        for (auto &&x : v[i]) v[bsr(x.first ^ last)].push_back(x);\n        v[i].clear();\n\
    \    }\npublic:\n    RadixHeap() : last(0), sz(0), cnt(0) {}\n    void emplace(K\
    \ x, V val){\n        sz++;\n        v[bsr(x^last)].emplace_back(x, val);\n  \
    \  }\n\n    pair<K, V> top() {\n        pull();\n        return v[0][cnt];\n \
    \   }\n\n    void pop() {\n        pull();\n        sz--;\n        cnt++;\n  \
    \  }\n\n    size_t size() const { return sz; }\n    bool empty() const { return\
    \ !sz; }\n};\n#line 9 \"graph/dijkstra_radix_heap.cpp\"\n\ntemplate <typename\
    \ T>\nvector<T> dijkstra(int s,vector<vector<edge<T>>> &G){\n    auto n = G.size();\n\
    \    vector<T> d(n, INF<T>);\n    RadixHeap<ll, int> Q;\n    d[s] = 0;\n    Q.emplace(0,\
    \ s);\n    while(!Q.empty()){\n        T cost; int i;\n        tie(cost, i) =\
    \ Q.top(); Q.pop();\n        if(d[i] < cost) continue;\n        for (auto &&e\
    \ : G[i]) {\n            auto cost2 = cost + e.cost;\n            if(d[e.to] <=\
    \ cost2) continue;\n            d[e.to] = cost2;\n            Q.emplace(d[e.to],\
    \ e.to);\n        }\n    }\n    return d;\n}\n\n/**\n * @brief Dijkstra\u6CD5\
    (Radix Heap)\n * @docs _md/dijkstra.md\n */\n#line 22 \"test/yosupo_shortest_path_radix_heap.test.cpp\"\
    \n\nint main() {\n    int n, m, s, t;\n    cin >> n >> m >> s >> t;\n    vector<vector<edge<ll>>>\
    \ G(n), Ginv(n);\n    for (int i = 0; i < m; ++i) {\n        int a, b, c;\n  \
    \      scanf(\"%d %d %d\", &a, &b, &c);\n        G[a].emplace_back(b, c);\n  \
    \      Ginv[b].emplace_back(a, c);\n    }\n    auto d = dijkstra(s, G);\n    if(d[t]\
    \ == INF<ll>){\n        puts(\"-1\");\n        return 0;\n    }\n    vector<int>\
    \ ans{t};\n    vector<int> visited(n);\n    visited[t] = 1;\n    while(ans.back()\
    \ != s){\n        for (auto &&i : Ginv[ans.back()]) {\n            if(d[i.to]+i.cost\
    \ == d[ans.back()] && !visited[i.to]){\n                ans.emplace_back(i.to);\n\
    \                visited[i.to] = 1;\n                break;\n            }\n \
    \       }\n    }\n    printf(\"%lld %lu\\n\", d[t], ans.size()-1);\n    for (int\
    \ i = (int)ans.size()-1; i > 0; --i) {\n        printf(\"%d %d\\n\", ans[i], ans[i-1]);\n\
    \    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\n\n#include\
    \ <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n#include <queue>\n\
    #include <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\n\
    static const int MOD = 1000000007;\nusing ll = long long;\nusing u32 = unsigned;\n\
    using u64 = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max()/32*15+208;\n\n#include \"../graph/dijkstra_radix_heap.cpp\"\
    \n\nint main() {\n    int n, m, s, t;\n    cin >> n >> m >> s >> t;\n    vector<vector<edge<ll>>>\
    \ G(n), Ginv(n);\n    for (int i = 0; i < m; ++i) {\n        int a, b, c;\n  \
    \      scanf(\"%d %d %d\", &a, &b, &c);\n        G[a].emplace_back(b, c);\n  \
    \      Ginv[b].emplace_back(a, c);\n    }\n    auto d = dijkstra(s, G);\n    if(d[t]\
    \ == INF<ll>){\n        puts(\"-1\");\n        return 0;\n    }\n    vector<int>\
    \ ans{t};\n    vector<int> visited(n);\n    visited[t] = 1;\n    while(ans.back()\
    \ != s){\n        for (auto &&i : Ginv[ans.back()]) {\n            if(d[i.to]+i.cost\
    \ == d[ans.back()] && !visited[i.to]){\n                ans.emplace_back(i.to);\n\
    \                visited[i.to] = 1;\n                break;\n            }\n \
    \       }\n    }\n    printf(\"%lld %lu\\n\", d[t], ans.size()-1);\n    for (int\
    \ i = (int)ans.size()-1; i > 0; --i) {\n        printf(\"%d %d\\n\", ans[i], ans[i-1]);\n\
    \    }\n    return 0;\n}"
  dependsOn:
  - graph/dijkstra_radix_heap.cpp
  - datastructure/radixheap.cpp
  isVerificationFile: true
  path: test/yosupo_shortest_path_radix_heap.test.cpp
  requiredBy: []
  timestamp: '2020-05-02 12:50:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_shortest_path_radix_heap.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_shortest_path_radix_heap.test.cpp
- /verify/test/yosupo_shortest_path_radix_heap.test.cpp.html
title: test/yosupo_shortest_path_radix_heap.test.cpp
---
