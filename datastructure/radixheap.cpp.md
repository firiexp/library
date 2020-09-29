---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra_radix_heap.cpp
    title: "Dijkstra\u6CD5(Radix Heap)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_shortest_path_radix_heap.test.cpp
    title: test/yosupo_shortest_path_radix_heap.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/radixheap.cpp\"\ntemplate <class K, class\
    \ V>\nclass RadixHeap {\n    static constexpr int bit_length = sizeof(K)*8;\n\
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
    \ !sz; }\n};\n"
  code: "template <class K, class V>\nclass RadixHeap {\n    static constexpr int\
    \ bit_length = sizeof(K)*8;\n    K last;\n    size_t sz, cnt;\n    \n    array<vector<pair<K,\
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
    \ !sz; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/radixheap.cpp
  requiredBy:
  - graph/dijkstra_radix_heap.cpp
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_shortest_path_radix_heap.test.cpp
documentation_of: datastructure/radixheap.cpp
layout: document
redirect_from:
- /library/datastructure/radixheap.cpp
- /library/datastructure/radixheap.cpp.html
title: datastructure/radixheap.cpp
---
