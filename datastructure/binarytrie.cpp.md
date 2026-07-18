---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_binarytrie.test.cpp
    title: test/yosupo_aplusb_binarytrie.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_set_xor_min_binarytrie.test.cpp
    title: test/yosupo_set_xor_min_binarytrie.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Binary Trie
    links: []
  bundledCode: "#line 1 \"datastructure/binarytrie.cpp\"\ntemplate<class T, size_t\
    \ X>\nstruct Binarytrie {\n    struct Node {\n        int cnt;\n        int nxt[2];\n\
    \        Node() : cnt(0), nxt{-1, -1} {}\n    };\n\n    vector<Node> nodes;\n\n\
    \    Binarytrie() : nodes(1) {}\n\n    explicit Binarytrie(const vector<T> &v)\
    \ : Binarytrie() {\n        reserve((int)v.size());\n        for (const T &x :\
    \ v) add(x);\n    }\n\n    void reserve(int n) {\n        if (n <= 0) return;\n\
    \        nodes.reserve(nodes.size() + (size_t)n * X);\n    }\n\n    int size()\
    \ const {\n        return nodes[0].cnt;\n    }\n\n    bool empty() const {\n \
    \       return nodes[0].cnt == 0;\n    }\n\n    int count(const T &x) const {\n\
    \        int p = 0;\n        for (int i = int(X) - 1; i >= 0; --i) {\n       \
    \     int f = (x >> i) & 1;\n            p = nodes[p].nxt[f];\n            if\
    \ (p == -1) return 0;\n        }\n        return nodes[p].cnt;\n    }\n\n    bool\
    \ contains(const T &x) const {\n        return count(x) > 0;\n    }\n\n    void\
    \ add(const T &x, int k = 1) {\n        int p = 0;\n        nodes[p].cnt += k;\n\
    \        for (int i = int(X) - 1; i >= 0; --i) {\n            int f = (x >> i)\
    \ & 1;\n            int to = nodes[p].nxt[f];\n            if (to == -1) {\n \
    \               to = (int)nodes.size();\n                nodes[p].nxt[f] = to;\n\
    \                nodes.emplace_back();\n            }\n            p = to;\n \
    \           nodes[p].cnt += k;\n        }\n    }\n\n    bool erase(const T &x,\
    \ int k = 1) {\n        array<int, X + 1> path;\n        int p = 0;\n        path[0]\
    \ = p;\n        for (int i = int(X) - 1, d = 1; i >= 0; --i, ++d) {\n        \
    \    int f = (x >> i) & 1;\n            p = nodes[p].nxt[f];\n            if (p\
    \ == -1) return false;\n            path[d] = p;\n        }\n        if (nodes[p].cnt\
    \ < k) return false;\n        for (int v : path) nodes[v].cnt -= k;\n        return\
    \ true;\n    }\n\n    T xor_min(const T &x) const {\n        int p = 0;\n    \
    \    T ret = 0;\n        for (int i = int(X) - 1; i >= 0; --i) {\n           \
    \ int f = (x >> i) & 1;\n            int to = nodes[p].nxt[f];\n            if\
    \ (to == -1 || nodes[to].cnt == 0) {\n                f ^= 1;\n              \
    \  ret |= T(1) << i;\n            }\n            p = nodes[p].nxt[f];\n      \
    \  }\n        return ret;\n    }\n\n    T min_element(T x = 0) const {\n     \
    \   return xor_min(x) ^ x;\n    }\n\n    T max_element(T x = 0) const {\n    \
    \    T y = x ^ bit_mask();\n        return xor_min(y) ^ y;\n    }\n\nprivate:\n\
    \    static constexpr T bit_mask() {\n        if constexpr (X == sizeof(T) * 8)\
    \ return T(-1);\n        else return (T(1) << X) - 1;\n    }\n};\n\n/**\n * @brief\
    \ Binary Trie\n */\n"
  code: "template<class T, size_t X>\nstruct Binarytrie {\n    struct Node {\n   \
    \     int cnt;\n        int nxt[2];\n        Node() : cnt(0), nxt{-1, -1} {}\n\
    \    };\n\n    vector<Node> nodes;\n\n    Binarytrie() : nodes(1) {}\n\n    explicit\
    \ Binarytrie(const vector<T> &v) : Binarytrie() {\n        reserve((int)v.size());\n\
    \        for (const T &x : v) add(x);\n    }\n\n    void reserve(int n) {\n  \
    \      if (n <= 0) return;\n        nodes.reserve(nodes.size() + (size_t)n * X);\n\
    \    }\n\n    int size() const {\n        return nodes[0].cnt;\n    }\n\n    bool\
    \ empty() const {\n        return nodes[0].cnt == 0;\n    }\n\n    int count(const\
    \ T &x) const {\n        int p = 0;\n        for (int i = int(X) - 1; i >= 0;\
    \ --i) {\n            int f = (x >> i) & 1;\n            p = nodes[p].nxt[f];\n\
    \            if (p == -1) return 0;\n        }\n        return nodes[p].cnt;\n\
    \    }\n\n    bool contains(const T &x) const {\n        return count(x) > 0;\n\
    \    }\n\n    void add(const T &x, int k = 1) {\n        int p = 0;\n        nodes[p].cnt\
    \ += k;\n        for (int i = int(X) - 1; i >= 0; --i) {\n            int f =\
    \ (x >> i) & 1;\n            int to = nodes[p].nxt[f];\n            if (to ==\
    \ -1) {\n                to = (int)nodes.size();\n                nodes[p].nxt[f]\
    \ = to;\n                nodes.emplace_back();\n            }\n            p =\
    \ to;\n            nodes[p].cnt += k;\n        }\n    }\n\n    bool erase(const\
    \ T &x, int k = 1) {\n        array<int, X + 1> path;\n        int p = 0;\n  \
    \      path[0] = p;\n        for (int i = int(X) - 1, d = 1; i >= 0; --i, ++d)\
    \ {\n            int f = (x >> i) & 1;\n            p = nodes[p].nxt[f];\n   \
    \         if (p == -1) return false;\n            path[d] = p;\n        }\n  \
    \      if (nodes[p].cnt < k) return false;\n        for (int v : path) nodes[v].cnt\
    \ -= k;\n        return true;\n    }\n\n    T xor_min(const T &x) const {\n  \
    \      int p = 0;\n        T ret = 0;\n        for (int i = int(X) - 1; i >= 0;\
    \ --i) {\n            int f = (x >> i) & 1;\n            int to = nodes[p].nxt[f];\n\
    \            if (to == -1 || nodes[to].cnt == 0) {\n                f ^= 1;\n\
    \                ret |= T(1) << i;\n            }\n            p = nodes[p].nxt[f];\n\
    \        }\n        return ret;\n    }\n\n    T min_element(T x = 0) const {\n\
    \        return xor_min(x) ^ x;\n    }\n\n    T max_element(T x = 0) const {\n\
    \        T y = x ^ bit_mask();\n        return xor_min(y) ^ y;\n    }\n\nprivate:\n\
    \    static constexpr T bit_mask() {\n        if constexpr (X == sizeof(T) * 8)\
    \ return T(-1);\n        else return (T(1) << X) - 1;\n    }\n};\n\n/**\n * @brief\
    \ Binary Trie\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/binarytrie.cpp
  requiredBy: []
  timestamp: '2026-05-07 23:02:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_binarytrie.test.cpp
  - test/yosupo_set_xor_min_binarytrie.test.cpp
documentation_of: datastructure/binarytrie.cpp
layout: document
title: Binary Trie
---
## 説明
非負整数集合に対する binary trie である。
挿入、削除、存在判定、`xor` をかけたあとの最小値取得を $O(X)$ で扱う。
ノードは `vector` でまとめて管理する。

## できること
- `Binarytrie<T, X> trie`
  `X` bit の整数を扱う trie を作る
- `Binarytrie<T, X> trie(v)`
  `vector<T> v` の要素を入れた trie を作る。重複はそのまま個数として入る
- `void reserve(int n)`
  今後 `n` 個挿入する想定でノード領域を先に確保する
- `void add(T x, int k = 1)`
  `x` を `k` 個追加する
- `bool erase(T x, int k = 1)`
  `x` を `k` 個削除する。個数が足りなければ `false`
- `int count(T x)`
  `x` の個数を返す
- `bool contains(T x)`
  `x` が 1 個以上あるかを返す
- `bool empty()`
  空集合かを返す
- `int size()`
  要素数を返す
- `T xor_min(T x)`
  集合内の要素との `xor` の最小値を返す。空集合では使わない
- `T min_element(T x = 0)`
  `a xor x` が最小となる要素 `a` を返す。`x = 0` なら通常の最小値
- `T max_element(T x = 0)`
  `a xor x` が最大となる要素 `a` を返す。`x = 0` なら通常の最大値

## 使い方
集合として使うなら、挿入前に `contains(x)` を見て重複を避ける。

```cpp
vector<unsigned int> init = {1, 4, 7};
Binarytrie<unsigned int, 30> trie(init);
trie.reserve(q);
if (!trie.contains(x)) trie.add(x);
unsigned int ans = trie.min_element(q);
```

## 実装上の補足
`xor_min(x)` は値そのものではなく最小 `xor` 値を返す。
この実装は multiset としても使える。
