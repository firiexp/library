---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_fast_set.test.cpp
    title: test/yosupo_aplusb_fast_set.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_predecessor_problem_fast_set.test.cpp
    title: test/yosupo_predecessor_problem_fast_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6574\u6570\u96C6\u5408\u306E\u524D\u5F8C\u691C\u7D22(FastSet)"
    links: []
  bundledCode: "#line 1 \"datastructure/fast_set.cpp\"\nclass FastSet {\n    int n;\n\
    \    vector<vector<unsigned long long>> layers;\n\npublic:\n    explicit FastSet(int\
    \ n) : n(n) {\n        assert(n >= 0);\n        while (n > 0) {\n            n\
    \ = (n + 63LL) / 64;\n            layers.emplace_back(n, 0);\n            if (n\
    \ == 1) break;\n        }\n    }\n\n    explicit FastSet(const vector<bool> &present)\
    \ : FastSet((int)present.size()) {\n        for (int i = 0; i < n; ++i)\n    \
    \        if (present[i]) layers[0][i >> 6] |= 1ULL << (i & 63);\n        for (int\
    \ h = 1; h < (int)layers.size(); ++h)\n            for (int i = 0; i < (int)layers[h\
    \ - 1].size(); ++i)\n                if (layers[h - 1][i]) layers[h][i >> 6] |=\
    \ 1ULL << (i & 63);\n    }\n\n    bool contains(int x) const {\n        assert(0\
    \ <= x && x < n);\n        return (layers[0][x >> 6] >> (x & 63)) & 1;\n    }\n\
    \n    void insert(int x) {\n        assert(0 <= x && x < n);\n        for (auto\
    \ &layer : layers) {\n            auto &word = layer[x >> 6];\n            bool\
    \ nonempty = word != 0;\n            word |= 1ULL << (x & 63);\n            if\
    \ (nonempty) break;\n            x >>= 6;\n        }\n    }\n\n    void erase(int\
    \ x) {\n        assert(0 <= x && x < n);\n        for (auto &layer : layers) {\n\
    \            auto &word = layer[x >> 6];\n            word &= ~(1ULL << (x & 63));\n\
    \            if (word) break;\n            x >>= 6;\n        }\n    }\n\n    int\
    \ next(int x) const {\n        assert(0 <= x && x <= n);\n        if (x == n)\
    \ return -1;\n        for (int h = 0; h < (int)layers.size(); ++h) {\n       \
    \     if ((x >> 6) >= (int)layers[h].size()) return -1;\n            auto word\
    \ = layers[h][x >> 6] >> (x & 63);\n            if (!word) {\n               \
    \ x = (x >> 6) + 1;\n                continue;\n            }\n            x +=\
    \ __builtin_ctzll(word);\n            for (int j = h - 1; j >= 0; --j)\n     \
    \           x = x * 64 + __builtin_ctzll(layers[j][x]);\n            return x;\n\
    \        }\n        return -1;\n    }\n\n    int prev(int x) const {\n       \
    \ assert(-1 <= x && x < n);\n        if (x == -1) return -1;\n        for (int\
    \ h = 0; h < (int)layers.size(); ++h) {\n            auto word = layers[h][x >>\
    \ 6] << (63 - (x & 63));\n            if (!word) {\n                x = (x >>\
    \ 6) - 1;\n                if (x < 0) return -1;\n                continue;\n\
    \            }\n            x -= __builtin_clzll(word);\n            for (int\
    \ j = h - 1; j >= 0; --j)\n                x = x * 64 + 63 - __builtin_clzll(layers[j][x]);\n\
    \            return x;\n        }\n        return -1;\n    }\n};\n\n/**\n * @brief\
    \ \u6574\u6570\u96C6\u5408\u306E\u524D\u5F8C\u691C\u7D22(FastSet)\n */\n"
  code: "class FastSet {\n    int n;\n    vector<vector<unsigned long long>> layers;\n\
    \npublic:\n    explicit FastSet(int n) : n(n) {\n        assert(n >= 0);\n   \
    \     while (n > 0) {\n            n = (n + 63LL) / 64;\n            layers.emplace_back(n,\
    \ 0);\n            if (n == 1) break;\n        }\n    }\n\n    explicit FastSet(const\
    \ vector<bool> &present) : FastSet((int)present.size()) {\n        for (int i\
    \ = 0; i < n; ++i)\n            if (present[i]) layers[0][i >> 6] |= 1ULL << (i\
    \ & 63);\n        for (int h = 1; h < (int)layers.size(); ++h)\n            for\
    \ (int i = 0; i < (int)layers[h - 1].size(); ++i)\n                if (layers[h\
    \ - 1][i]) layers[h][i >> 6] |= 1ULL << (i & 63);\n    }\n\n    bool contains(int\
    \ x) const {\n        assert(0 <= x && x < n);\n        return (layers[0][x >>\
    \ 6] >> (x & 63)) & 1;\n    }\n\n    void insert(int x) {\n        assert(0 <=\
    \ x && x < n);\n        for (auto &layer : layers) {\n            auto &word =\
    \ layer[x >> 6];\n            bool nonempty = word != 0;\n            word |=\
    \ 1ULL << (x & 63);\n            if (nonempty) break;\n            x >>= 6;\n\
    \        }\n    }\n\n    void erase(int x) {\n        assert(0 <= x && x < n);\n\
    \        for (auto &layer : layers) {\n            auto &word = layer[x >> 6];\n\
    \            word &= ~(1ULL << (x & 63));\n            if (word) break;\n    \
    \        x >>= 6;\n        }\n    }\n\n    int next(int x) const {\n        assert(0\
    \ <= x && x <= n);\n        if (x == n) return -1;\n        for (int h = 0; h\
    \ < (int)layers.size(); ++h) {\n            if ((x >> 6) >= (int)layers[h].size())\
    \ return -1;\n            auto word = layers[h][x >> 6] >> (x & 63);\n       \
    \     if (!word) {\n                x = (x >> 6) + 1;\n                continue;\n\
    \            }\n            x += __builtin_ctzll(word);\n            for (int\
    \ j = h - 1; j >= 0; --j)\n                x = x * 64 + __builtin_ctzll(layers[j][x]);\n\
    \            return x;\n        }\n        return -1;\n    }\n\n    int prev(int\
    \ x) const {\n        assert(-1 <= x && x < n);\n        if (x == -1) return -1;\n\
    \        for (int h = 0; h < (int)layers.size(); ++h) {\n            auto word\
    \ = layers[h][x >> 6] << (63 - (x & 63));\n            if (!word) {\n        \
    \        x = (x >> 6) - 1;\n                if (x < 0) return -1;\n          \
    \      continue;\n            }\n            x -= __builtin_clzll(word);\n   \
    \         for (int j = h - 1; j >= 0; --j)\n                x = x * 64 + 63 -\
    \ __builtin_clzll(layers[j][x]);\n            return x;\n        }\n        return\
    \ -1;\n    }\n};\n\n/**\n * @brief \u6574\u6570\u96C6\u5408\u306E\u524D\u5F8C\u691C\
    \u7D22(FastSet)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/fast_set.cpp
  requiredBy: []
  timestamp: '2026-10-10 18:51:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_predecessor_problem_fast_set.test.cpp
  - test/yosupo_aplusb_fast_set.test.cpp
documentation_of: datastructure/fast_set.cpp
layout: document
title: "\u6574\u6570\u96C6\u5408\u306E\u524D\u5F8C\u691C\u7D22(FastSet)"
---

## 説明
$[0,N)$ の整数集合を64bit単位の階層bitsetで管理する。
更新と前後検索は $O(\log N)$、存在判定は $O(1)$。

## できること
- `FastSet s(n)`：空集合を作る
- `FastSet s(present)`：`vector<bool>` の真の位置を集合に入れる。構築 $O(N)$
- `insert(x)` / `erase(x)`：挿入 / 削除する。重複挿入・存在しない要素の削除は何もしない
- `contains(x)`：存在するかを返す
- `next(x)`：`x` 以上の最小要素を返す。存在しなければ `-1`
- `prev(x)`：`x` 以下の最大要素を返す。存在しなければ `-1`

## 使い方
更新と存在判定は `0 <= x < n`、`next` は `0 <= x <= n`、`prev` は `-1 <= x < n` を前提とする。
`next(n)` と `prev(-1)` は常に `-1`。範囲外の入力を自動で切り詰めることはしない。

## 実装上の補足
各階層は下位wordが非空かを保持する。疎な集合でも空wordを線形走査しない。
階層の配列は構築時に確保し、各操作では確保しない。
