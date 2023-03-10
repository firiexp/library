---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0342.test.cpp
    title: test/aoj0342.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj0377.test.cpp
    title: test/aoj0377.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj0403.test.cpp
    title: test/aoj0403.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_unionfind.test.cpp
    title: test/yosupo_unionfind.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/unionfind.md
    document_title: "UnionFind(\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020)"
    links: []
  bundledCode: "#line 1 \"datastructure/unionfind.cpp\"\nclass UnionFind {\n    int\
    \ n;\n    vector<int> uni;\n    int forest_size;\npublic:\n    explicit UnionFind(int\
    \ n) : n(n), uni(static_cast<uint>(n), -1), forest_size(n) {};\n\n    int root(int\
    \ a){\n        if (uni[a] < 0) return a;\n        else return (uni[a] = root(uni[a]));\n\
    \    }\n\n    bool unite(int a, int b) {\n        a = root(a);\n        b = root(b);\n\
    \        if(a == b) return false;\n        if(uni[a] > uni[b]) swap(a, b);\n \
    \       uni[a] += uni[b];\n        uni[b] = a;\n        forest_size--;\n     \
    \   return true;\n    }\n    int size(){ return forest_size; }\n    int size(int\
    \ i){ return -uni[root(i)]; }\n    bool same(int a, int b) { return root(a) ==\
    \ root(b); }\n};\n\n/**\n * @brief UnionFind(\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\
    \u69CB\u9020)\n * @docs _md/unionfind.md\n */\n"
  code: "class UnionFind {\n    int n;\n    vector<int> uni;\n    int forest_size;\n\
    public:\n    explicit UnionFind(int n) : n(n), uni(static_cast<uint>(n), -1),\
    \ forest_size(n) {};\n\n    int root(int a){\n        if (uni[a] < 0) return a;\n\
    \        else return (uni[a] = root(uni[a]));\n    }\n\n    bool unite(int a,\
    \ int b) {\n        a = root(a);\n        b = root(b);\n        if(a == b) return\
    \ false;\n        if(uni[a] > uni[b]) swap(a, b);\n        uni[a] += uni[b];\n\
    \        uni[b] = a;\n        forest_size--;\n        return true;\n    }\n  \
    \  int size(){ return forest_size; }\n    int size(int i){ return -uni[root(i)];\
    \ }\n    bool same(int a, int b) { return root(a) == root(b); }\n};\n\n/**\n *\
    \ @brief UnionFind(\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020)\n * @docs\
    \ _md/unionfind.md\n */"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/unionfind.cpp
  requiredBy: []
  timestamp: '2021-06-21 15:24:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0377.test.cpp
  - test/yosupo_unionfind.test.cpp
  - test/aoj0342.test.cpp
  - test/aoj0403.test.cpp
documentation_of: datastructure/unionfind.cpp
layout: document
redirect_from:
- /library/datastructure/unionfind.cpp
- /library/datastructure/unionfind.cpp.html
title: "UnionFind(\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020)"
---
## 説明
頂点の併合、代表元の取得が$O(\alpha (n))$でできるデータ構造。

## 操作
- $\mathrm{root}(a)$ : 頂点$a$の代表元を取得。　
- $\mathrm{unite}(a, b)$ : 頂点$a$と$b$の属する集合を併合する。　
- $\mathrm{size}()$ : 集合の数を取得する。
- $\mathrm{size}(i)$ : $i$の属する集合の大きさを取得する。
- $\mathrm{same}(a, b)$ : $a$と$b$が同じ集合に属するかどうかを判定する。
