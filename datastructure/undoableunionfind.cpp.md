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
  bundledCode: "#line 1 \"datastructure/undoableunionfind.cpp\"\nclass UndoableUnionFind\
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
    \ }\n    void rollback(){ while(!hist.empty()) undo(); }\n};\n"
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
    \ }\n    void rollback(){ while(!hist.empty()) undo(); }\n};"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/undoableunionfind.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: datastructure/undoableunionfind.cpp
layout: document
redirect_from:
- /library/datastructure/undoableunionfind.cpp
- /library/datastructure/undoableunionfind.cpp.html
title: datastructure/undoableunionfind.cpp
---
