---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/bellman_ford.cpp
    title: "Bellman-Ford\u6CD5"
  - icon: ':heavy_check_mark:'
    path: graph/bfs01.cpp
    title: 01-BFS
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.cpp
    title: "Dijkstra\u6CD5"
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra_common.cpp
    title: graph/dijkstra_common.cpp
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra_radix_heap.cpp
    title: "Dijkstra\u6CD5(Radix Heap)"
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra_restore.cpp
    title: "\u7D4C\u8DEF\u5FA9\u5143\u4ED8\u304DDijkstra\u6CD5"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0275_dynamic_bitset.test.cpp
    title: test/aoj0275_dynamic_bitset.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj0275_static_bitset.test.cpp
    title: test/aoj0275_static_bitset.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj2945_bfs01.test.cpp
    title: test/aoj2945_bfs01.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj_grl_1_a_dijkstra.test.cpp
    title: test/aoj_grl_1_a_dijkstra.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj_grl_1_b_bellman_ford.test.cpp
    title: test/aoj_grl_1_b_bellman_ford.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_bellman_ford.test.cpp
    title: test/yosupo_aplusb_bellman_ford.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_library_composition.test.cpp
    title: test/yosupo_aplusb_library_composition.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_library_composition_reverse.test.cpp
    title: test/yosupo_aplusb_library_composition_reverse.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_shortest_path.test.cpp
    title: test/yosupo_shortest_path.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_shortest_path_radix_heap.test.cpp
    title: test/yosupo_shortest_path_radix_heap.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/edge.cpp\"\n\n\n\ntemplate <typename T>\nstruct edge\
    \ {\n    int from, to;\n    T cost;\n\n    edge(int to, T cost) : from(-1), to(to),\
    \ cost(cost) {}\n    edge(int from, int to, T cost) : from(from), to(to), cost(cost)\
    \ {}\n\n    explicit operator int() const { return to; }\n};\n\n\n"
  code: "#ifndef FIRIEXP_LIBRARY_GRAPH_EDGE_CPP\n#define FIRIEXP_LIBRARY_GRAPH_EDGE_CPP\n\
    \ntemplate <typename T>\nstruct edge {\n    int from, to;\n    T cost;\n\n   \
    \ edge(int to, T cost) : from(-1), to(to), cost(cost) {}\n    edge(int from, int\
    \ to, T cost) : from(from), to(to), cost(cost) {}\n\n    explicit operator int()\
    \ const { return to; }\n};\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/edge.cpp
  requiredBy:
  - graph/dijkstra_common.cpp
  - graph/dijkstra_restore.cpp
  - graph/dijkstra.cpp
  - graph/dijkstra_radix_heap.cpp
  - graph/bfs01.cpp
  - graph/bellman_ford.cpp
  timestamp: '2026-10-05 23:03:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_shortest_path.test.cpp
  - test/aoj_grl_1_b_bellman_ford.test.cpp
  - test/aoj_grl_1_a_dijkstra.test.cpp
  - test/yosupo_aplusb_bellman_ford.test.cpp
  - test/aoj0275_static_bitset.test.cpp
  - test/yosupo_aplusb_library_composition.test.cpp
  - test/aoj2945_bfs01.test.cpp
  - test/aoj0275_dynamic_bitset.test.cpp
  - test/yosupo_shortest_path_radix_heap.test.cpp
  - test/yosupo_aplusb_library_composition_reverse.test.cpp
documentation_of: graph/edge.cpp
layout: document
redirect_from:
- /library/graph/edge.cpp
- /library/graph/edge.cpp.html
title: graph/edge.cpp
---
