---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/radixheap.cpp
    title: datastructure/radixheap.cpp
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra_common.cpp
    title: graph/dijkstra_common.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_shortest_path_radix_heap.test.cpp
    title: test/yosupo_shortest_path_radix_heap.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Dijkstra\u6CD5(Radix Heap)"
    links: []
  bundledCode: "#line 1 \"graph/dijkstra_common.cpp\"\n\n\n\ntemplate <typename T>\n\
    struct edge {\n    int from, to;\n    T cost;\n\n    edge(int to, T cost) : from(-1),\
    \ to(to), cost(cost) {}\n    edge(int from, int to, T cost) : from(from), to(to),\
    \ cost(cost) {}\n};\n\ntemplate <typename T>\nstruct DijkstraPriorityQueue {\n\
    \    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;\n\n    bool\
    \ empty() const { return q.empty(); }\n\n    void push(T cost, int v) {\n    \
    \    q.emplace(cost, v);\n    }\n\n    pair<T, int> pop() {\n        auto res\
    \ = q.top();\n        q.pop();\n        return res;\n    }\n};\n\ntemplate <typename\
    \ T, class Queue, class OnRelax>\nvector<T> dijkstra_internal(int s, const vector<vector<edge<T>>>\
    \ &G, Queue &Q, OnRelax on_relax) {\n    int n = (int)G.size();\n    vector<T>\
    \ dist(n, INF<T>);\n    dist[s] = 0;\n    Q.push(T(0), s);\n    while (!Q.empty())\
    \ {\n        auto [cost, v] = Q.pop();\n        if (dist[v] < cost) continue;\n\
    \        for (auto &&e : G[v]) {\n            T nxt = cost + e.cost;\n       \
    \     if (dist[e.to] <= nxt) continue;\n            dist[e.to] = nxt;\n      \
    \      on_relax(v, e);\n            Q.push(nxt, e.to);\n        }\n    }\n   \
    \ return dist;\n}\n\ntemplate <typename T, class Queue>\nvector<T> dijkstra_internal(int\
    \ s, const vector<vector<edge<T>>> &G, Queue &Q) {\n    return dijkstra_internal(s,\
    \ G, Q, [](int, const edge<T> &) {});\n}\n\n\n#line 1 \"datastructure/radixheap.cpp\"\
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
    \ !sz; }\n};\n#line 3 \"graph/dijkstra_radix_heap.cpp\"\n\ntemplate <typename\
    \ T>\nstruct DijkstraRadixHeapQueue {\n    static_assert(numeric_limits<T>::is_integer,\
    \ \"dijkstra_radix_heap requires integer costs\");\n    static_assert(numeric_limits<T>::is_signed,\
    \ \"dijkstra_radix_heap requires signed integer costs\");\n    static_assert(sizeof(T)\
    \ <= sizeof(ll), \"dijkstra_radix_heap requires costs that fit in long long\"\
    );\n\n    RadixHeap<ll, int> Q;\n\n    bool empty() const { return Q.empty();\
    \ }\n\n    void push(T cost, int v) {\n        Q.emplace((ll)cost, v);\n    }\n\
    \n    pair<T, int> pop() {\n        auto [cost, v] = Q.top();\n        Q.pop();\n\
    \        return {static_cast<T>(cost), v};\n    }\n};\n\ntemplate <typename T>\n\
    vector<T> dijkstra_radix_heap(int s, const vector<vector<edge<T>>> &G) {\n   \
    \ DijkstraRadixHeapQueue<T> Q;\n    return dijkstra_internal(s, G, Q);\n}\n\n\
    /**\n * @brief Dijkstra\u6CD5(Radix Heap)\n */\n"
  code: "#include \"dijkstra_common.cpp\"\n#include \"../datastructure/radixheap.cpp\"\
    \n\ntemplate <typename T>\nstruct DijkstraRadixHeapQueue {\n    static_assert(numeric_limits<T>::is_integer,\
    \ \"dijkstra_radix_heap requires integer costs\");\n    static_assert(numeric_limits<T>::is_signed,\
    \ \"dijkstra_radix_heap requires signed integer costs\");\n    static_assert(sizeof(T)\
    \ <= sizeof(ll), \"dijkstra_radix_heap requires costs that fit in long long\"\
    );\n\n    RadixHeap<ll, int> Q;\n\n    bool empty() const { return Q.empty();\
    \ }\n\n    void push(T cost, int v) {\n        Q.emplace((ll)cost, v);\n    }\n\
    \n    pair<T, int> pop() {\n        auto [cost, v] = Q.top();\n        Q.pop();\n\
    \        return {static_cast<T>(cost), v};\n    }\n};\n\ntemplate <typename T>\n\
    vector<T> dijkstra_radix_heap(int s, const vector<vector<edge<T>>> &G) {\n   \
    \ DijkstraRadixHeapQueue<T> Q;\n    return dijkstra_internal(s, G, Q);\n}\n\n\
    /**\n * @brief Dijkstra\u6CD5(Radix Heap)\n */\n"
  dependsOn:
  - graph/dijkstra_common.cpp
  - datastructure/radixheap.cpp
  isVerificationFile: false
  path: graph/dijkstra_radix_heap.cpp
  requiredBy: []
  timestamp: '2026-03-12 14:17:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_shortest_path_radix_heap.test.cpp
documentation_of: graph/dijkstra_radix_heap.cpp
layout: document
title: "Dijkstra\u6CD5(Radix Heap)"
---
## 説明
Radix Heap を使った Dijkstra 法である。
非負整数重みの単一始点最短路を高速に求める。

## できること
- `vector<T> dijkstra_radix_heap(int s, const vector<vector<edge<T>>>& g)`
  始点 `s` から各頂点への最短距離を返す。未到達は `INF<T>`

## 使い方
辺重みは非負である必要がある。
`T` は `long long` に収まる符号付き整数型を想定する。
`edge<T>` の隣接リストを作って呼ぶ。

```cpp
vector<vector<edge<long long>>> g(n);
g[u].emplace_back(v, w);
auto dist = dijkstra_radix_heap(0, g);
```

## 実装上の補足
内部で `RadixHeap<ll, int>` を使う。
通常の priority queue 版 Dijkstra より、距離が整数で増加する性質を利用して定数倍を削る。
