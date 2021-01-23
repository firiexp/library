---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/radixheap.cpp
    title: datastructure/radixheap.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_shortest_path_radix_heap.test.cpp
    title: test/yosupo_shortest_path_radix_heap.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/dijkstra.md
    document_title: "Dijkstra\u6CD5(Radix Heap)"
    links: []
  bundledCode: "#line 1 \"graph/dijkstra_radix_heap.cpp\"\ntemplate <typename T>\n\
    struct edge {\n    int from, to; T cost;\n    edge(int to, T cost) : from(-1),\
    \ to(to), cost(cost) {}\n    edge(int from, int to, T cost) : from(from), to(to),\
    \ cost(cost) {}\n};\n\n#line 1 \"datastructure/radixheap.cpp\"\ntemplate <class\
    \ K, class V>\nclass RadixHeap {\n    static constexpr int bit_length = sizeof(K)*8;\n\
    \    K last;\n    size_t sz, cnt;\n    \n    array<vector<pair<K, V>>, bit_length>\
    \ v;\n    static inline int bsr(int x){\n        return x ? bit_length-__builtin_clz(x)\
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
    (Radix Heap)\n * @docs _md/dijkstra.md\n */\n"
  code: "template <typename T>\nstruct edge {\n    int from, to; T cost;\n    edge(int\
    \ to, T cost) : from(-1), to(to), cost(cost) {}\n    edge(int from, int to, T\
    \ cost) : from(from), to(to), cost(cost) {}\n};\n\n#include \"../datastructure/radixheap.cpp\"\
    \n\ntemplate <typename T>\nvector<T> dijkstra(int s,vector<vector<edge<T>>> &G){\n\
    \    auto n = G.size();\n    vector<T> d(n, INF<T>);\n    RadixHeap<ll, int> Q;\n\
    \    d[s] = 0;\n    Q.emplace(0, s);\n    while(!Q.empty()){\n        T cost;\
    \ int i;\n        tie(cost, i) = Q.top(); Q.pop();\n        if(d[i] < cost) continue;\n\
    \        for (auto &&e : G[i]) {\n            auto cost2 = cost + e.cost;\n  \
    \          if(d[e.to] <= cost2) continue;\n            d[e.to] = cost2;\n    \
    \        Q.emplace(d[e.to], e.to);\n        }\n    }\n    return d;\n}\n\n/**\n\
    \ * @brief Dijkstra\u6CD5(Radix Heap)\n * @docs _md/dijkstra.md\n */"
  dependsOn:
  - datastructure/radixheap.cpp
  isVerificationFile: false
  path: graph/dijkstra_radix_heap.cpp
  requiredBy: []
  timestamp: '2020-05-02 12:50:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_shortest_path_radix_heap.test.cpp
documentation_of: graph/dijkstra_radix_heap.cpp
layout: document
redirect_from:
- /library/graph/dijkstra_radix_heap.cpp
- /library/graph/dijkstra_radix_heap.cpp.html
title: "Dijkstra\u6CD5(Radix Heap)"
---
## 説明
単一始点最短路を求める。負辺があると正しく動作しない。
$O(V \log E)$