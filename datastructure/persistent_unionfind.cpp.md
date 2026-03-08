---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_persistent_unionfind_persistent_unionfind.test.cpp
    title: test/yosupo_persistent_unionfind_persistent_unionfind.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "\u5B8C\u5168\u6C38\u7D9AUnionFind(Fully Persistent Union Find)"
    links: []
  bundledCode: "#line 1 \"datastructure/persistent_unionfind.cpp\"\nclass PersistentUnionFind\
    \ {\n    struct Node {\n        int val;\n        int l;\n        int r;\n   \
    \ };\n\n    int n;\n    vector<Node> node;\n    vector<pair<int, int>> roots;\n\
    \npublic:\n    explicit PersistentUnionFind(int sz) : n(sz) {\n        if (n ==\
    \ 0) {\n            node.push_back({-1, -1, -1});\n            roots.push_back({0,\
    \ 0});\n        } else {\n            roots.push_back({build(0, n), n});\n   \
    \     }\n    }\n\n    int versions() const { return roots.size(); }\n    int latest_version()\
    \ const { return versions() - 1; }\n    int count() const { return roots[latest_version()].second;\
    \ }\n    int count(int t) const { return roots[t].second; }\n\n    int root(int\
    \ t, int a) const {\n        int p = get(roots[t].first, a, 0, n);\n        if\
    \ (p < 0) return a;\n        return root(t, p);\n    }\n    int root(int a) const\
    \ { return root(latest_version(), a); }\n\n    bool same(int t, int a, int b)\
    \ const {\n        return root(t, a) == root(t, b);\n    }\n    bool same(int\
    \ a, int b) const { return same(latest_version(), a, b); }\n\n    int size(int\
    \ t, int a) const {\n        return -get(roots[t].first, root(t, a), 0, n);\n\
    \    }\n    int size(int a) const { return size(latest_version(), a); }\n\n  \
    \  int copy_version(int t) {\n        roots.push_back(roots[t]);\n        return\
    \ latest_version();\n    }\n\n    int unite(int t, int a, int b) {\n        if\
    \ (n == 0) {\n            return copy_version(t);\n        }\n        int rt =\
    \ roots[t].first;\n        int ra = root(t, a);\n        int rb = root(t, b);\n\
    \        if (ra == rb) return copy_version(t);\n        int sa = get(rt, ra, 0,\
    \ n);\n        int sb = get(rt, rb, 0, n);\n        if (sa > sb) {\n         \
    \   swap(ra, rb);\n            swap(sa, sb);\n        }\n        int nr = set(rt,\
    \ ra, sa + sb, 0, n);\n        nr = set(nr, rb, ra, 0, n);\n        roots.push_back({nr,\
    \ roots[t].second - 1});\n        return latest_version();\n    }\n    int unite(int\
    \ a, int b) { return unite(latest_version(), a, b); }\n\nprivate:\n    int make_node(int\
    \ val, int l, int r) {\n        node.push_back({val, l, r});\n        return node.size()\
    \ - 1;\n    }\n\n    int build(int l, int r) {\n        if (l + 1 == r) return\
    \ make_node(-1, -1, -1);\n        int m = (l + r) >> 1;\n        return make_node(0,\
    \ build(l, m), build(m, r));\n    }\n\n    int get(int id, int k, int l, int r)\
    \ const {\n        if (l + 1 == r) return node[id].val;\n        int m = (l +\
    \ r) >> 1;\n        if (k < m) return get(node[id].l, k, l, m);\n        return\
    \ get(node[id].r, k, m, r);\n    }\n\n    int set(int id, int k, int val, int\
    \ l, int r) {\n        if (l + 1 == r) return make_node(val, -1, -1);\n      \
    \  int m = (l + r) >> 1;\n        int nl = node[id].l;\n        int nr = node[id].r;\n\
    \        if (k < m) nl = set(nl, k, val, l, m);\n        else nr = set(nr, k,\
    \ val, m, r);\n        return make_node(0, nl, nr);\n    }\n};\n\n/**\n * @brief\
    \ \u5B8C\u5168\u6C38\u7D9AUnionFind(Fully Persistent Union Find)\n */\n"
  code: "class PersistentUnionFind {\n    struct Node {\n        int val;\n      \
    \  int l;\n        int r;\n    };\n\n    int n;\n    vector<Node> node;\n    vector<pair<int,\
    \ int>> roots;\n\npublic:\n    explicit PersistentUnionFind(int sz) : n(sz) {\n\
    \        if (n == 0) {\n            node.push_back({-1, -1, -1});\n          \
    \  roots.push_back({0, 0});\n        } else {\n            roots.push_back({build(0,\
    \ n), n});\n        }\n    }\n\n    int versions() const { return roots.size();\
    \ }\n    int latest_version() const { return versions() - 1; }\n    int count()\
    \ const { return roots[latest_version()].second; }\n    int count(int t) const\
    \ { return roots[t].second; }\n\n    int root(int t, int a) const {\n        int\
    \ p = get(roots[t].first, a, 0, n);\n        if (p < 0) return a;\n        return\
    \ root(t, p);\n    }\n    int root(int a) const { return root(latest_version(),\
    \ a); }\n\n    bool same(int t, int a, int b) const {\n        return root(t,\
    \ a) == root(t, b);\n    }\n    bool same(int a, int b) const { return same(latest_version(),\
    \ a, b); }\n\n    int size(int t, int a) const {\n        return -get(roots[t].first,\
    \ root(t, a), 0, n);\n    }\n    int size(int a) const { return size(latest_version(),\
    \ a); }\n\n    int copy_version(int t) {\n        roots.push_back(roots[t]);\n\
    \        return latest_version();\n    }\n\n    int unite(int t, int a, int b)\
    \ {\n        if (n == 0) {\n            return copy_version(t);\n        }\n \
    \       int rt = roots[t].first;\n        int ra = root(t, a);\n        int rb\
    \ = root(t, b);\n        if (ra == rb) return copy_version(t);\n        int sa\
    \ = get(rt, ra, 0, n);\n        int sb = get(rt, rb, 0, n);\n        if (sa >\
    \ sb) {\n            swap(ra, rb);\n            swap(sa, sb);\n        }\n   \
    \     int nr = set(rt, ra, sa + sb, 0, n);\n        nr = set(nr, rb, ra, 0, n);\n\
    \        roots.push_back({nr, roots[t].second - 1});\n        return latest_version();\n\
    \    }\n    int unite(int a, int b) { return unite(latest_version(), a, b); }\n\
    \nprivate:\n    int make_node(int val, int l, int r) {\n        node.push_back({val,\
    \ l, r});\n        return node.size() - 1;\n    }\n\n    int build(int l, int\
    \ r) {\n        if (l + 1 == r) return make_node(-1, -1, -1);\n        int m =\
    \ (l + r) >> 1;\n        return make_node(0, build(l, m), build(m, r));\n    }\n\
    \n    int get(int id, int k, int l, int r) const {\n        if (l + 1 == r) return\
    \ node[id].val;\n        int m = (l + r) >> 1;\n        if (k < m) return get(node[id].l,\
    \ k, l, m);\n        return get(node[id].r, k, m, r);\n    }\n\n    int set(int\
    \ id, int k, int val, int l, int r) {\n        if (l + 1 == r) return make_node(val,\
    \ -1, -1);\n        int m = (l + r) >> 1;\n        int nl = node[id].l;\n    \
    \    int nr = node[id].r;\n        if (k < m) nl = set(nl, k, val, l, m);\n  \
    \      else nr = set(nr, k, val, m, r);\n        return make_node(0, nl, nr);\n\
    \    }\n};\n\n/**\n * @brief \u5B8C\u5168\u6C38\u7D9AUnionFind(Fully Persistent\
    \ Union Find)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/persistent_unionfind.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_persistent_unionfind_persistent_unionfind.test.cpp
documentation_of: datastructure/persistent_unionfind.cpp
layout: document
title: "\u5B8C\u5168\u6C38\u7D9AUnionFind(Fully Persistent Union Find)"
---
## 説明
各操作で新しい版を作る fully persistent な Union-Find である。
任意の過去版に対して `same` や `size` を呼べて、過去版からさらに `unite` して別の分岐を作れる。
経路圧縮は使わず、親配列を永続セグ木で持つ。

## できること
- `PersistentUnionFind uf(n)`
  `0..n-1` をそれぞれ別集合として初期化する
- `int versions()`
  保持している版数を返す
- `int latest_version()`
  最新版の番号を返す
- `int count()`
  最新版の連結成分数を返す
- `int count(int t)`
  版 `t` の連結成分数を返す
- `int root(int t, int v)`
  版 `t` での `v` の代表元を返す
- `bool same(int t, int u, int v)`
  版 `t` で `u` と `v` が同じ集合なら `true` を返す
- `int size(int t, int v)`
  版 `t` で `v` が属する集合サイズを返す
- `int copy_version(int t)`
  版 `t` と同じ状態の新しい版を末尾に追加し、その版番号を返す
- `int unite(int t, int u, int v)`
  版 `t` を基準に `u` と `v` を併合した新しい版を末尾に追加し、その版番号を返す。同じ集合でも失敗せず、同じ状態の版を返す

## 使い方
過去版番号を持っておき、そこから `unite` して分岐を作る。
Library Checker の `persistent_unionfind` のように、各クエリが「どの版から派生するか」を指定する問題にそのまま使える。

```cpp
PersistentUnionFind uf(n);
int v1 = uf.unite(0, 0, 1);
int v2 = uf.unite(v1, 1, 2);
bool ok = uf.same(v1, 0, 2);
int sz = uf.size(v2, 0);
```

## 実装上の補足
- 併合は union by size のみで、経路圧縮はしない
- `root` / `same` / `size(v)` は 1 回の親参照ごとに永続セグ木を 1 回辿るので、ならしで `O(log^2 N)` 程度になる
- `unite` は葉 2 か所だけを更新するので `O(log N)` 個のノード追加で済む
