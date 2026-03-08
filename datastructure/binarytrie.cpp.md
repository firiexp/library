---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_set_xor_min_binarytrie.test.cpp
    title: test/yosupo_set_xor_min_binarytrie.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/binarytrie.md
    document_title: Binary Trie
    links: []
  bundledCode: "#line 1 \"datastructure/binarytrie.cpp\"\ntemplate<class T, size_t\
    \ X>\nstruct Binarytrie {\n    struct Node {\n        int cnt;\n        Node *nxt[2];\n\
    \        Node() : cnt(0), nxt{nullptr, nullptr} {}\n    };\n\n    Node *root;\n\
    \n    Binarytrie() : root(new Node) {}\n\n    int size() const {\n        return\
    \ root->cnt;\n    }\n\n    bool empty() const {\n        return root->cnt == 0;\n\
    \    }\n\n    int count(const T &x) const {\n        Node *p = root;\n       \
    \ for (int i = int(X) - 1; i >= 0; --i) {\n            int f = (x >> i) & 1;\n\
    \            if (!p->nxt[f]) return 0;\n            p = p->nxt[f];\n        }\n\
    \        return p->cnt;\n    }\n\n    bool contains(const T &x) const {\n    \
    \    return count(x) > 0;\n    }\n\n    void add(const T &x, int k = 1) {\n  \
    \      Node *p = root;\n        p->cnt += k;\n        for (int i = int(X) - 1;\
    \ i >= 0; --i) {\n            int f = (x >> i) & 1;\n            if (!p->nxt[f])\
    \ p->nxt[f] = new Node;\n            p = p->nxt[f];\n            p->cnt += k;\n\
    \        }\n    }\n\n    bool erase(const T &x, int k = 1) {\n        if (count(x)\
    \ < k) return false;\n        Node *p = root;\n        p->cnt -= k;\n        for\
    \ (int i = int(X) - 1; i >= 0; --i) {\n            int f = (x >> i) & 1;\n   \
    \         p = p->nxt[f];\n            p->cnt -= k;\n        }\n        return\
    \ true;\n    }\n\n    T xor_min(const T &x) const {\n        Node *p = root;\n\
    \        T ret = 0;\n        for (int i = int(X) - 1; i >= 0; --i) {\n       \
    \     int f = (x >> i) & 1;\n            if (!p->nxt[f] || p->nxt[f]->cnt == 0)\
    \ {\n                f ^= 1;\n                ret |= T(1) << i;\n            }\n\
    \            p = p->nxt[f];\n        }\n        return ret;\n    }\n\n    T min_element(T\
    \ x = 0) const {\n        return xor_min(x) ^ x;\n    }\n\n    T max_element(T\
    \ x = 0) const {\n        return xor_min(~x) ^ x;\n    }\n};\n\n/**\n * @brief\
    \ Binary Trie\n * @docs _md/binarytrie.md\n */\n"
  code: "template<class T, size_t X>\nstruct Binarytrie {\n    struct Node {\n   \
    \     int cnt;\n        Node *nxt[2];\n        Node() : cnt(0), nxt{nullptr, nullptr}\
    \ {}\n    };\n\n    Node *root;\n\n    Binarytrie() : root(new Node) {}\n\n  \
    \  int size() const {\n        return root->cnt;\n    }\n\n    bool empty() const\
    \ {\n        return root->cnt == 0;\n    }\n\n    int count(const T &x) const\
    \ {\n        Node *p = root;\n        for (int i = int(X) - 1; i >= 0; --i) {\n\
    \            int f = (x >> i) & 1;\n            if (!p->nxt[f]) return 0;\n  \
    \          p = p->nxt[f];\n        }\n        return p->cnt;\n    }\n\n    bool\
    \ contains(const T &x) const {\n        return count(x) > 0;\n    }\n\n    void\
    \ add(const T &x, int k = 1) {\n        Node *p = root;\n        p->cnt += k;\n\
    \        for (int i = int(X) - 1; i >= 0; --i) {\n            int f = (x >> i)\
    \ & 1;\n            if (!p->nxt[f]) p->nxt[f] = new Node;\n            p = p->nxt[f];\n\
    \            p->cnt += k;\n        }\n    }\n\n    bool erase(const T &x, int\
    \ k = 1) {\n        if (count(x) < k) return false;\n        Node *p = root;\n\
    \        p->cnt -= k;\n        for (int i = int(X) - 1; i >= 0; --i) {\n     \
    \       int f = (x >> i) & 1;\n            p = p->nxt[f];\n            p->cnt\
    \ -= k;\n        }\n        return true;\n    }\n\n    T xor_min(const T &x) const\
    \ {\n        Node *p = root;\n        T ret = 0;\n        for (int i = int(X)\
    \ - 1; i >= 0; --i) {\n            int f = (x >> i) & 1;\n            if (!p->nxt[f]\
    \ || p->nxt[f]->cnt == 0) {\n                f ^= 1;\n                ret |= T(1)\
    \ << i;\n            }\n            p = p->nxt[f];\n        }\n        return\
    \ ret;\n    }\n\n    T min_element(T x = 0) const {\n        return xor_min(x)\
    \ ^ x;\n    }\n\n    T max_element(T x = 0) const {\n        return xor_min(~x)\
    \ ^ x;\n    }\n};\n\n/**\n * @brief Binary Trie\n * @docs _md/binarytrie.md\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/binarytrie.cpp
  requiredBy: []
  timestamp: '2026-03-08 15:26:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_set_xor_min_binarytrie.test.cpp
documentation_of: datastructure/binarytrie.cpp
layout: document
redirect_from:
- /library/datastructure/binarytrie.cpp
- /library/datastructure/binarytrie.cpp.html
title: Binary Trie
---
## 説明
非負整数集合に対する binary trie である。
挿入、削除、存在判定、`xor` をかけたあとの最小値取得を `O(X)` で扱う。

## できること
- `Binarytrie<T, X> trie`
  `X` bit の整数を扱う trie を作る
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
Binarytrie<unsigned int, 30> trie;
if (!trie.contains(x)) trie.add(x);
unsigned int ans = trie.min_element(q);
```

## 実装上の補足
`xor_min(x)` は値そのものではなく最小 `xor` 値を返す。
この実装は multiset としても使える。
