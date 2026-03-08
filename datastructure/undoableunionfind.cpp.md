---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_persistent_unionfind_undoableunionfind.test.cpp
    title: test/yosupo_persistent_unionfind_undoableunionfind.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Undoable Union Find
    links: []
  bundledCode: "#line 1 \"datastructure/undoableunionfind.cpp\"\nclass UndoableUnionFind\
    \ {\n    stack<pair<int, int>> hist;\n    int forest_size;\n    int snap;\n\n\
    public:\n    vector<int> uni;\n\n    explicit UndoableUnionFind(int sz) : forest_size(sz),\
    \ snap(0), uni(sz, -1) {}\n\n    int root(int a) {\n        if (uni[a] < 0) return\
    \ a;\n        return root(uni[a]);\n    }\n\n    bool same(int a, int b) {\n \
    \       return root(a) == root(b);\n    }\n\n    bool unite(int a, int b) {\n\
    \        a = root(a);\n        b = root(b);\n        hist.emplace(a, uni[a]);\n\
    \        hist.emplace(b, uni[b]);\n        if (a == b) return false;\n       \
    \ if (uni[a] > uni[b]) swap(a, b);\n        uni[a] += uni[b];\n        uni[b]\
    \ = a;\n        forest_size--;\n        return true;\n    }\n\n    int size()\
    \ { return forest_size; }\n    int size(int i) { return -uni[root(i)]; }\n\n \
    \   int get_state() const {\n        return int(hist.size() >> 1);\n    }\n\n\
    \    void undo() {\n        int a = hist.top().first;\n        int ua = hist.top().second;\n\
    \        hist.pop();\n        int b = hist.top().first;\n        int ub = hist.top().second;\n\
    \        hist.pop();\n        if (a != b) forest_size++;\n        uni[a] = ua;\n\
    \        uni[b] = ub;\n    }\n\n    void snapshot() {\n        snap = get_state();\n\
    \    }\n\n    void rollback(int state = -1) {\n        if (state == -1) state\
    \ = snap;\n        while (get_state() > state) undo();\n    }\n};\n\n/**\n * @brief\
    \ Undoable Union Find\n */\n"
  code: "class UndoableUnionFind {\n    stack<pair<int, int>> hist;\n    int forest_size;\n\
    \    int snap;\n\npublic:\n    vector<int> uni;\n\n    explicit UndoableUnionFind(int\
    \ sz) : forest_size(sz), snap(0), uni(sz, -1) {}\n\n    int root(int a) {\n  \
    \      if (uni[a] < 0) return a;\n        return root(uni[a]);\n    }\n\n    bool\
    \ same(int a, int b) {\n        return root(a) == root(b);\n    }\n\n    bool\
    \ unite(int a, int b) {\n        a = root(a);\n        b = root(b);\n        hist.emplace(a,\
    \ uni[a]);\n        hist.emplace(b, uni[b]);\n        if (a == b) return false;\n\
    \        if (uni[a] > uni[b]) swap(a, b);\n        uni[a] += uni[b];\n       \
    \ uni[b] = a;\n        forest_size--;\n        return true;\n    }\n\n    int\
    \ size() { return forest_size; }\n    int size(int i) { return -uni[root(i)];\
    \ }\n\n    int get_state() const {\n        return int(hist.size() >> 1);\n  \
    \  }\n\n    void undo() {\n        int a = hist.top().first;\n        int ua =\
    \ hist.top().second;\n        hist.pop();\n        int b = hist.top().first;\n\
    \        int ub = hist.top().second;\n        hist.pop();\n        if (a != b)\
    \ forest_size++;\n        uni[a] = ua;\n        uni[b] = ub;\n    }\n\n    void\
    \ snapshot() {\n        snap = get_state();\n    }\n\n    void rollback(int state\
    \ = -1) {\n        if (state == -1) state = snap;\n        while (get_state()\
    \ > state) undo();\n    }\n};\n\n/**\n * @brief Undoable Union Find\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/undoableunionfind.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_persistent_unionfind_undoableunionfind.test.cpp
documentation_of: datastructure/undoableunionfind.cpp
layout: document
title: Undoable Union Find
---
## 説明
undo / rollback ができる Union-Find である。
併合 1 回あたりの変更点を保存し、`undo()` を `O(1)` で行う。

## できること
- `UndoableUnionFind uf(n)`
  頂点数 `n` の Union-Find を作る
- `int root(int v)`
  頂点 `v` の代表元を返す
- `bool same(int u, int v)`
  `u` と `v` が同じ集合かを返す
- `bool unite(int u, int v)`
  `u` と `v` を併合する。すでに同じ集合なら `false`
- `int size()`
  連結成分数を返す
- `int size(int v)`
  `v` が属する集合サイズを返す
- `void undo()`
  直前の `unite` 1 回を取り消す
- `void snapshot()`
  現在状態を保存する
- `int get_state()`
  現在の履歴深さを返す
- `void rollback(int state = -1)`
  指定状態まで巻き戻す。`-1` なら直前の `snapshot()` に戻す

## 使い方
分岐探索や offline dynamic connectivity の DFS で、辺を追加して潜ってから `rollback(state)` で戻す形で使う。

```cpp
UndoableUnionFind uf(n);
int state = uf.get_state();
uf.unite(u, v);
bool ok = uf.same(a, b);
uf.rollback(state);
```

## 実装上の補足
経路圧縮をしない Union-Find にしているので、`unite` 1 回で変わる配列要素は高々 2 か所である。
`rollback()` は `undo()` を必要回数だけ繰り返す。
