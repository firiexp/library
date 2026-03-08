---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_unionfind_quickfind.test.cpp
    title: test/yosupo_unionfind_quickfind.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    _deprecated_at_docs: _md/quickfind.md
    document_title: Quick Find
    links: []
  bundledCode: "#line 1 \"datastructure/quickfind.cpp\"\nstruct QuickFind {\n    int\
    \ n;\n    vector<int> roots;\n    vector<vector<int>> v;\n    explicit QuickFind(int\
    \ n) : n(n) {\n        v.resize(n);\n        for (int i = 0; i < n; ++i) v[i].emplace_back(i);\n\
    \        roots.resize(n);\n        iota(roots.begin(),roots.end(), 0);\n    }\n\
    \ \n    int root(int a){ return roots[a]; }\n    size_t size(int a){ return v[a].size();\
    \ }\n    bool unite(int a, int b){\n        if(same(a, b)) return false;\n   \
    \     a = roots[a], b = roots[b];\n        if(size(a) < size(b)) swap(a, b);\n\
    \        for (auto &&i : v[b]) {\n            v[a].emplace_back(i);\n        \
    \    roots[i] = a;\n        }\n        v[b].clear();\n        v[b].shrink_to_fit();\n\
    \        return true;\n    }\n    bool same(int a, int b){ return roots[a] ==\
    \ roots[b]; }\n    const vector<int>& components(int x){ return v[roots[x]];}\n\
    };\n\n/**\n * @brief Quick Find\n * @docs _md/quickfind.md\n */\n"
  code: "struct QuickFind {\n    int n;\n    vector<int> roots;\n    vector<vector<int>>\
    \ v;\n    explicit QuickFind(int n) : n(n) {\n        v.resize(n);\n        for\
    \ (int i = 0; i < n; ++i) v[i].emplace_back(i);\n        roots.resize(n);\n  \
    \      iota(roots.begin(),roots.end(), 0);\n    }\n \n    int root(int a){ return\
    \ roots[a]; }\n    size_t size(int a){ return v[a].size(); }\n    bool unite(int\
    \ a, int b){\n        if(same(a, b)) return false;\n        a = roots[a], b =\
    \ roots[b];\n        if(size(a) < size(b)) swap(a, b);\n        for (auto &&i\
    \ : v[b]) {\n            v[a].emplace_back(i);\n            roots[i] = a;\n  \
    \      }\n        v[b].clear();\n        v[b].shrink_to_fit();\n        return\
    \ true;\n    }\n    bool same(int a, int b){ return roots[a] == roots[b]; }\n\
    \    const vector<int>& components(int x){ return v[roots[x]];}\n};\n\n/**\n *\
    \ @brief Quick Find\n * @docs _md/quickfind.md\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/quickfind.cpp
  requiredBy: []
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_unionfind_quickfind.test.cpp
documentation_of: datastructure/quickfind.cpp
layout: document
redirect_from:
- /library/datastructure/quickfind.cpp
- /library/datastructure/quickfind.cpp.html
title: Quick Find
---
---
layout: post
title: 素集合データ構造 (Quick-Find)
date: 2026-03-08
category: データ構造
tags: データ構造
---

## 説明
各連結成分の頂点一覧を持ちながら併合する素集合データ構造。
`same` や `root` は `O(1)`、`unite` は小さい集合を大きい集合へマージする実装で、各頂点は高々 `O(log N)` 回しか移動しない。
全体では `N` 回の併合を通して `O(N log N)` 程度で動く。

## できること
- `QuickFind(int n)`
  `0..n-1` をそれぞれ別集合として初期化する
- `int root(int a)`
  `a` が属する集合の代表元を返す
- `bool same(int a, int b)`
  `a` と `b` が同じ集合なら `true` を返す
- `bool unite(int a, int b)`
  `a` と `b` の集合を併合する。もともと同じなら `false`
- `size_t size(int a)`
  代表元 `a` が持つ集合のサイズを返す。非代表元を渡すと 0 になることがある
- `const vector<int>& components(int x)`
  `x` が属する連結成分の頂点一覧を返す

## 使い方
`QuickFind uf(n);` を作って `unite(a, b)` と `same(a, b)` を使う。
成分に含まれる頂点を直接ほしいときは `components(x)` が使える。

```cpp
QuickFind uf(n);
uf.unite(0, 1);
if (uf.same(0, 1)) {
    auto comp = uf.components(0);
}
```

## 実装上の補足
- `components(x)` は代表元ではなく任意の頂点 `x` を渡してよい
- `size(a)` は実装上 `v[a].size()` を返すので、確実に使うなら `size(root(x))` とする
