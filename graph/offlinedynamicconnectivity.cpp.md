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
  bundledCode: "#line 1 \"graph/offlinedynamicconnectivity.cpp\"\nclass UndoableUnionFind\
    \ {\n    stack<pair<int, int>> hist;\n    int forest_size;\npublic:\n    vector<int>\
    \ uni;\n    explicit UndoableUnionFind(int sz) : uni(sz, -1), forest_size(sz)\
    \ {}\n\n    int root(int a){\n        if(uni[a] < 0) return a;\n        return\
    \ root(uni[a]);\n    }\n\n    bool unite(int a, int b){\n        a = root(a),\
    \ b = root(b);\n        hist.emplace(a, uni[a]);\n        hist.emplace(b, uni[b]);\n\
    \        if(a == b) return false;\n        if(uni[a] > uni[b]) swap(a, b);\n \
    \       uni[a] += uni[b];\n        uni[b] = a;\n        forest_size--;\n     \
    \   return true;\n    }\n\n    int size(){ return forest_size; }\n    int size(int\
    \ i){ return -uni[root(i)]; }\n\n    void undo(){\n        uni[hist.top().first]\
    \ = hist.top().second;\n        hist.pop();\n        uni[hist.top().first] = hist.top().second;\n\
    \        hist.pop();\n    }\n\n    void snapshot(){ while(!hist.empty()) hist.pop();\
    \ }\n    void rollback(){ while(!hist.empty()) undo(); }\n};\n\nclass OfflineDynamicConnectivity\
    \ {\n    UndoableUnionFind uf;\n    int n;\n    vector<vector<pair<int, int>>>\
    \ seg;\n    vector<pair<pair<int, int>, pair<int, int>>> pend;\n    map<pair<int,\
    \ int>, int> cnt, appear;\n    void add(int a, int b, const pair<int ,int> &e){\n\
    \        for (int l = a+sz, r = b+sz; l < r; l >>= 1, r >>= 1) {\n           \
    \ if(l&1) seg[l++].emplace_back(e);\n            if(r&1) seg[--r].emplace_back(e);\n\
    \        }\n    }\npublic:\n    int sz;\n    OfflineDynamicConnectivity(int n,\
    \ int q) : uf(n), n(n){\n        sz = 1;\n        while(sz < q) sz <<= 1;\n  \
    \      seg.resize(2*sz);\n    }\n\n    void insert(int t, int a, int b){\n   \
    \     auto e = minmax(a, b);\n        if(cnt[e]++ == 0) appear[e] = t;\n    }\n\
    \n    void erase(int t, int a, int b){\n        auto e = minmax(a, b);\n     \
    \   if(--cnt[e] == 0) pend.emplace_back(make_pair(appear[e], t), e)\n    }\n\n\
    \    void build(){\n        for (auto &&i : cnt) {\n            if(!i.second)\
    \ continue;\n            pend.emplace_back(make_pair(appear[i.first], q), i.first);\n\
    \        }\n        for (auto &&i : pend) {\n            add(i.first.first, i.first.second,\
    \ i.second);\n        }\n    }\n\n    template<typename F>\n    void run(const\
    \ F &f, int k = 1){\n        for (auto &&i : seg[k]) uf.unite(i.first, i.second);\n\
    \        if(k < sz){\n            run(f, (k << 1) | 0);\n            run(f, (k\
    \ << 1) | 1);\n        }else f(k-sz);\n        for (auto &&i : seg[k]) uf.undo();\n\
    \    }\n};\n"
  code: "class UndoableUnionFind {\n    stack<pair<int, int>> hist;\n    int forest_size;\n\
    public:\n    vector<int> uni;\n    explicit UndoableUnionFind(int sz) : uni(sz,\
    \ -1), forest_size(sz) {}\n\n    int root(int a){\n        if(uni[a] < 0) return\
    \ a;\n        return root(uni[a]);\n    }\n\n    bool unite(int a, int b){\n \
    \       a = root(a), b = root(b);\n        hist.emplace(a, uni[a]);\n        hist.emplace(b,\
    \ uni[b]);\n        if(a == b) return false;\n        if(uni[a] > uni[b]) swap(a,\
    \ b);\n        uni[a] += uni[b];\n        uni[b] = a;\n        forest_size--;\n\
    \        return true;\n    }\n\n    int size(){ return forest_size; }\n    int\
    \ size(int i){ return -uni[root(i)]; }\n\n    void undo(){\n        uni[hist.top().first]\
    \ = hist.top().second;\n        hist.pop();\n        uni[hist.top().first] = hist.top().second;\n\
    \        hist.pop();\n    }\n\n    void snapshot(){ while(!hist.empty()) hist.pop();\
    \ }\n    void rollback(){ while(!hist.empty()) undo(); }\n};\n\nclass OfflineDynamicConnectivity\
    \ {\n    UndoableUnionFind uf;\n    int n;\n    vector<vector<pair<int, int>>>\
    \ seg;\n    vector<pair<pair<int, int>, pair<int, int>>> pend;\n    map<pair<int,\
    \ int>, int> cnt, appear;\n    void add(int a, int b, const pair<int ,int> &e){\n\
    \        for (int l = a+sz, r = b+sz; l < r; l >>= 1, r >>= 1) {\n           \
    \ if(l&1) seg[l++].emplace_back(e);\n            if(r&1) seg[--r].emplace_back(e);\n\
    \        }\n    }\npublic:\n    int sz;\n    OfflineDynamicConnectivity(int n,\
    \ int q) : uf(n), n(n){\n        sz = 1;\n        while(sz < q) sz <<= 1;\n  \
    \      seg.resize(2*sz);\n    }\n\n    void insert(int t, int a, int b){\n   \
    \     auto e = minmax(a, b);\n        if(cnt[e]++ == 0) appear[e] = t;\n    }\n\
    \n    void erase(int t, int a, int b){\n        auto e = minmax(a, b);\n     \
    \   if(--cnt[e] == 0) pend.emplace_back(make_pair(appear[e], t), e)\n    }\n\n\
    \    void build(){\n        for (auto &&i : cnt) {\n            if(!i.second)\
    \ continue;\n            pend.emplace_back(make_pair(appear[i.first], q), i.first);\n\
    \        }\n        for (auto &&i : pend) {\n            add(i.first.first, i.first.second,\
    \ i.second);\n        }\n    }\n\n    template<typename F>\n    void run(const\
    \ F &f, int k = 1){\n        for (auto &&i : seg[k]) uf.unite(i.first, i.second);\n\
    \        if(k < sz){\n            run(f, (k << 1) | 0);\n            run(f, (k\
    \ << 1) | 1);\n        }else f(k-sz);\n        for (auto &&i : seg[k]) uf.undo();\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/offlinedynamicconnectivity.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/offlinedynamicconnectivity.cpp
layout: document
redirect_from:
- /library/graph/offlinedynamicconnectivity.cpp
- /library/graph/offlinedynamicconnectivity.cpp.html
title: graph/offlinedynamicconnectivity.cpp
---
