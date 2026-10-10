---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_alds1_9_c_leftist_heap.test.cpp
    title: test/aoj_alds1_9_c_leftist_heap.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_leftist_heap.test.cpp
    title: test/yosupo_aplusb_leftist_heap.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4F75\u5408\u30FB\u4E00\u62EC\u52A0\u7B97\u4ED8\u304D\u30D2\u30FC\
      \u30D7(Leftist Heap)"
    links: []
  bundledCode: "#line 1 \"datastructure/leftist_heap.cpp\"\ntemplate<class T>\nclass\
    \ LeftistHeap {\n    struct Node {\n        T value, lazy;\n        int left,\
    \ right, rank;\n    };\n\n    vector<Node> nodes;\n    vector<int> roots, counts;\n\
    \    int free_head = -1;\n\n    int rank(int v) const { return v == -1 ? 0 : nodes[v].rank;\
    \ }\n\n    void apply(int v, const T &delta) {\n        if (v == -1) return;\n\
    \        nodes[v].value += delta;\n        nodes[v].lazy += delta;\n    }\n\n\
    \    void push_lazy(int v) {\n        apply(nodes[v].left, nodes[v].lazy);\n \
    \       apply(nodes[v].right, nodes[v].lazy);\n        nodes[v].lazy = T{};\n\
    \    }\n\n    int merge(int a, int b) {\n        if (a == -1) return b;\n    \
    \    if (b == -1) return a;\n        if (nodes[b].value < nodes[a].value) swap(a,\
    \ b);\n        push_lazy(a);\n        nodes[a].right = merge(nodes[a].right, b);\n\
    \        if (rank(nodes[a].left) < rank(nodes[a].right)) swap(nodes[a].left, nodes[a].right);\n\
    \        nodes[a].rank = rank(nodes[a].right) + 1;\n        return a;\n    }\n\
    \npublic:\n    explicit LeftistHeap(int m) : roots(m, -1), counts(m, 0) {}\n\n\
    \    bool empty(int i) const { return counts[i] == 0; }\n    int size(int i) const\
    \ { return counts[i]; }\n\n    T top(int i) const {\n        assert(!empty(i));\n\
    \        return nodes[roots[i]].value;\n    }\n\n    void push(int i, const T\
    \ &value) {\n        int v;\n        if (free_head == -1) {\n            v = (int)nodes.size();\n\
    \            nodes.push_back({value, T{}, -1, -1, 1});\n        } else {\n   \
    \         v = free_head;\n            free_head = nodes[v].left;\n           \
    \ nodes[v] = {value, T{}, -1, -1, 1};\n        }\n        roots[i] = merge(roots[i],\
    \ v);\n        ++counts[i];\n    }\n\n    void pop(int i) {\n        assert(!empty(i));\n\
    \        int v = roots[i];\n        push_lazy(v);\n        roots[i] = merge(nodes[v].left,\
    \ nodes[v].right);\n        nodes[v].left = free_head;\n        free_head = v;\n\
    \        --counts[i];\n    }\n\n    void meld(int i, int j) {\n        if (i ==\
    \ j) return;\n        roots[i] = merge(roots[i], roots[j]);\n        counts[i]\
    \ += counts[j];\n        roots[j] = -1;\n        counts[j] = 0;\n    }\n\n   \
    \ void add_all(int i, const T &delta) { apply(roots[i], delta); }\n};\n\n/**\n\
    \ * @brief \u4F75\u5408\u30FB\u4E00\u62EC\u52A0\u7B97\u4ED8\u304D\u30D2\u30FC\u30D7\
    (Leftist Heap)\n */\n"
  code: "template<class T>\nclass LeftistHeap {\n    struct Node {\n        T value,\
    \ lazy;\n        int left, right, rank;\n    };\n\n    vector<Node> nodes;\n \
    \   vector<int> roots, counts;\n    int free_head = -1;\n\n    int rank(int v)\
    \ const { return v == -1 ? 0 : nodes[v].rank; }\n\n    void apply(int v, const\
    \ T &delta) {\n        if (v == -1) return;\n        nodes[v].value += delta;\n\
    \        nodes[v].lazy += delta;\n    }\n\n    void push_lazy(int v) {\n     \
    \   apply(nodes[v].left, nodes[v].lazy);\n        apply(nodes[v].right, nodes[v].lazy);\n\
    \        nodes[v].lazy = T{};\n    }\n\n    int merge(int a, int b) {\n      \
    \  if (a == -1) return b;\n        if (b == -1) return a;\n        if (nodes[b].value\
    \ < nodes[a].value) swap(a, b);\n        push_lazy(a);\n        nodes[a].right\
    \ = merge(nodes[a].right, b);\n        if (rank(nodes[a].left) < rank(nodes[a].right))\
    \ swap(nodes[a].left, nodes[a].right);\n        nodes[a].rank = rank(nodes[a].right)\
    \ + 1;\n        return a;\n    }\n\npublic:\n    explicit LeftistHeap(int m) :\
    \ roots(m, -1), counts(m, 0) {}\n\n    bool empty(int i) const { return counts[i]\
    \ == 0; }\n    int size(int i) const { return counts[i]; }\n\n    T top(int i)\
    \ const {\n        assert(!empty(i));\n        return nodes[roots[i]].value;\n\
    \    }\n\n    void push(int i, const T &value) {\n        int v;\n        if (free_head\
    \ == -1) {\n            v = (int)nodes.size();\n            nodes.push_back({value,\
    \ T{}, -1, -1, 1});\n        } else {\n            v = free_head;\n          \
    \  free_head = nodes[v].left;\n            nodes[v] = {value, T{}, -1, -1, 1};\n\
    \        }\n        roots[i] = merge(roots[i], v);\n        ++counts[i];\n   \
    \ }\n\n    void pop(int i) {\n        assert(!empty(i));\n        int v = roots[i];\n\
    \        push_lazy(v);\n        roots[i] = merge(nodes[v].left, nodes[v].right);\n\
    \        nodes[v].left = free_head;\n        free_head = v;\n        --counts[i];\n\
    \    }\n\n    void meld(int i, int j) {\n        if (i == j) return;\n       \
    \ roots[i] = merge(roots[i], roots[j]);\n        counts[i] += counts[j];\n   \
    \     roots[j] = -1;\n        counts[j] = 0;\n    }\n\n    void add_all(int i,\
    \ const T &delta) { apply(roots[i], delta); }\n};\n\n/**\n * @brief \u4F75\u5408\
    \u30FB\u4E00\u62EC\u52A0\u7B97\u4ED8\u304D\u30D2\u30FC\u30D7(Leftist Heap)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/leftist_heap.cpp
  requiredBy: []
  timestamp: '2026-10-10 18:56:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_leftist_heap.test.cpp
  - test/aoj_alds1_9_c_leftist_heap.test.cpp
documentation_of: datastructure/leftist_heap.cpp
layout: document
title: "\u4F75\u5408\u30FB\u4E00\u62EC\u52A0\u7B97\u4ED8\u304D\u30D2\u30FC\u30D7(Leftist\
  \ Heap)"
---

## 説明
複数の最小ヒープを1つのpoolで管理し、ヒープの併合と全要素への加算を扱う。
重複値は別々の要素として保持する。

## できること
全ヒープに含まれる要素数を $H$ とする。

- `LeftistHeap<T> heap(m)`：空のヒープを `m` 個作る。$O(m)$
- `push(i, x)`：ヒープ `i` に `x` を追加する。償却 $O(\log H)$
- `top(i)`：最小値のコピーを返す。空でないことが前提。$O(1)$
- `pop(i)`：最小値を1個削除する。空でないことが前提。$O(\log H)$
- `meld(i, j)`：`j` の全要素を `i` に移し、`j` を空にする。`i == j` なら何もしない。$O(\log H)$
- `add_all(i, delta)`：全要素に `delta` を加算する。空なら何もしない。$O(1)$
- `size(i)` / `empty(i)`：要素数 / 空かを返す。$O(1)$

## 使い方
ヒープ番号は `0 <= i < m` とする。併合後の `j` は空のヒープとして再利用できる。
通常は `LeftistHeap<long long>` のように数値型を指定する。
独自型を使う場合は、比較 `<` と加算 `+=` が使え、`T{}` で初期化した値が加算の単位元になるようにする。`T` が `long long` なら、この初期値は0になる。
加算は値の大小関係を保ち、値・遅延値・中間値が `T` に収まることを前提とする。上記の計算量では値のコピー・比較・加算を $O(1)$ とする。

## 実装上の補足
左子のrank以上にならないよう右子のrankを保ち、短い右経路だけを辿って併合する。
削除したnodeは子の添字欄を使ったfree listへ戻すため、`pop` で追加確保しない。
同時に生存した要素数の最大値を $H_{\max}$ とすると、領域は $O(m+H_{\max})$。過去のpush総数には比例しない。
