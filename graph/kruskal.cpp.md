---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/kruskal.cpp\"\ntemplate <typename T>\nstruct edge\
    \ {\n    int from, to;\n    T cost;\n\n    edge(int to, T cost) : from(-1), to(to),\
    \ cost(cost) {}\n    edge(int from, int to, T cost) : from(from), to(to), cost(cost)\
    \ {}\n\n    explicit operator int() const {return to;}\n};\n\nclass UnionFind\
    \ {\n    vector<int> uni;\n    int n;\npublic:\n    explicit UnionFind(int n)\
    \ : uni(static_cast<uint>(n), -1) , n(n){};\n\n    int root(int a){\n        if\
    \ (uni[a] < 0) return a;\n        else return (uni[a] = root(uni[a]));\n    }\n\
    \n    bool unite(int a, int b) {\n        a = root(a);\n        b = root(b);\n\
    \        if(a == b) return false;\n        if(uni[a] > uni[b]) swap(a, b);\n \
    \       uni[a] += uni[b];\n        uni[b] = a;\n        return true;\n    }\n\
    };\n\ntemplate< typename T >\nT kruskal(vector<edge<T>> &G, int V)\n{\n    sort(begin(G),\
    \ end(G), [](const edge< T > &a, const edge< T > &b) { return (a.cost < b.cost);\
    \ });\n    UnionFind tree(V);\n    T ret = 0;\n    for(auto &e : G) {\n      \
    \  if(tree.unite(e.from, e.to)) ret += e.cost;\n    }\n    return (ret);\n}\n"
  code: "template <typename T>\nstruct edge {\n    int from, to;\n    T cost;\n\n\
    \    edge(int to, T cost) : from(-1), to(to), cost(cost) {}\n    edge(int from,\
    \ int to, T cost) : from(from), to(to), cost(cost) {}\n\n    explicit operator\
    \ int() const {return to;}\n};\n\nclass UnionFind {\n    vector<int> uni;\n  \
    \  int n;\npublic:\n    explicit UnionFind(int n) : uni(static_cast<uint>(n),\
    \ -1) , n(n){};\n\n    int root(int a){\n        if (uni[a] < 0) return a;\n \
    \       else return (uni[a] = root(uni[a]));\n    }\n\n    bool unite(int a, int\
    \ b) {\n        a = root(a);\n        b = root(b);\n        if(a == b) return\
    \ false;\n        if(uni[a] > uni[b]) swap(a, b);\n        uni[a] += uni[b];\n\
    \        uni[b] = a;\n        return true;\n    }\n};\n\ntemplate< typename T\
    \ >\nT kruskal(vector<edge<T>> &G, int V)\n{\n    sort(begin(G), end(G), [](const\
    \ edge< T > &a, const edge< T > &b) { return (a.cost < b.cost); });\n    UnionFind\
    \ tree(V);\n    T ret = 0;\n    for(auto &e : G) {\n        if(tree.unite(e.from,\
    \ e.to)) ret += e.cost;\n    }\n    return (ret);\n}"
  dependsOn: []
  isVerificationFile: false
  path: graph/kruskal.cpp
  requiredBy: []
  timestamp: '2021-06-21 15:24:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/kruskal.cpp
layout: document
redirect_from:
- /library/graph/kruskal.cpp
- /library/graph/kruskal.cpp.html
title: graph/kruskal.cpp
---
