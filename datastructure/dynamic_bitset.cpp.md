---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_many_aplusb_dynamic_bitset.test.cpp
    title: test/yosupo_many_aplusb_dynamic_bitset.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/dynamic_bitset.md
    document_title: DynamicBitset
    links: []
  bundledCode: "#line 1 \"datastructure/dynamic_bitset.cpp\"\nclass DynamicBitset\
    \ {\n    using ull = unsigned long long;\n    static constexpr int B = 64;\n\n\
    \    int n;\n    vector<ull> a;\n\n    static int popcount(ull x) {\n        return\
    \ __builtin_popcountll(x);\n    }\n    static int ctz(ull x) {\n        return\
    \ __builtin_ctzll(x);\n    }\n\n    ull tail_mask() const {\n        int rem =\
    \ n & (B - 1);\n        return rem ? ((1ULL << rem) - 1) : ~0ULL;\n    }\n\n \
    \   void normalize() {\n        if (!a.empty()) a.back() &= tail_mask();\n   \
    \ }\n\npublic:\n    DynamicBitset() : n(0) {}\n    explicit DynamicBitset(int\
    \ n, bool x = false) : n(n), a((n + B - 1) >> 6, x ? ~0ULL : 0ULL) {\n       \
    \ normalize();\n    }\n\n    int size() const { return n; }\n    bool empty()\
    \ const { return n == 0; }\n\n    void reset() {\n        fill(a.begin(), a.end(),\
    \ 0);\n    }\n    void set() {\n        fill(a.begin(), a.end(), ~0ULL);\n   \
    \     normalize();\n    }\n    void flip() {\n        for (auto &x : a) x = ~x;\n\
    \        normalize();\n    }\n\n    bool test(int k) const {\n        return (a[k\
    \ >> 6] >> (k & 63)) & 1ULL;\n    }\n    void set(int k) {\n        a[k >> 6]\
    \ |= 1ULL << (k & 63);\n    }\n    void reset(int k) {\n        a[k >> 6] &= ~(1ULL\
    \ << (k & 63));\n    }\n    void flip(int k) {\n        a[k >> 6] ^= 1ULL << (k\
    \ & 63);\n    }\n    void assign(int k, bool x) {\n        if (x) set(k);\n  \
    \      else reset(k);\n    }\n\n    bool any() const {\n        for (auto x :\
    \ a) if (x) return true;\n        return false;\n    }\n    bool none() const\
    \ { return !any(); }\n    bool all() const {\n        if (a.empty()) return true;\n\
    \        for (int i = 0; i + 1 < (int)a.size(); ++i) {\n            if (a[i] !=\
    \ ~0ULL) return false;\n        }\n        return a.back() == tail_mask();\n \
    \   }\n    int count() const {\n        int res = 0;\n        for (auto x : a)\
    \ res += popcount(x);\n        return res;\n    }\n\n    int find_first() const\
    \ {\n        for (int i = 0; i < (int)a.size(); ++i) {\n            if (a[i])\
    \ return (i << 6) + ctz(a[i]);\n        }\n        return -1;\n    }\n    int\
    \ find_next(int k) const {\n        ++k;\n        if (k >= n) return -1;\n   \
    \     int i = k >> 6;\n        ull x = a[i] & (~0ULL << (k & 63));\n        if\
    \ (x) return (i << 6) + ctz(x);\n        for (++i; i < (int)a.size(); ++i) {\n\
    \            if (a[i]) return (i << 6) + ctz(a[i]);\n        }\n        return\
    \ -1;\n    }\n\n    DynamicBitset& operator&=(const DynamicBitset &r) {\n    \
    \    for (int i = 0; i < (int)a.size(); ++i) a[i] &= r.a[i];\n        return *this;\n\
    \    }\n    DynamicBitset& operator|=(const DynamicBitset &r) {\n        for (int\
    \ i = 0; i < (int)a.size(); ++i) a[i] |= r.a[i];\n        return *this;\n    }\n\
    \    DynamicBitset& operator^=(const DynamicBitset &r) {\n        for (int i =\
    \ 0; i < (int)a.size(); ++i) a[i] ^= r.a[i];\n        normalize();\n        return\
    \ *this;\n    }\n\n    friend DynamicBitset operator&(DynamicBitset l, const DynamicBitset\
    \ &r) { return l &= r; }\n    friend DynamicBitset operator|(DynamicBitset l,\
    \ const DynamicBitset &r) { return l |= r; }\n    friend DynamicBitset operator^(DynamicBitset\
    \ l, const DynamicBitset &r) { return l ^= r; }\n\n    DynamicBitset& operator<<=(int\
    \ s) {\n        if (s <= 0) return *this;\n        if (s >= n) {\n           \
    \ reset();\n            return *this;\n        }\n        int block = s >> 6,\
    \ rem = s & 63;\n        vector<ull> b(a.size(), 0);\n        for (int i = (int)a.size()\
    \ - 1; i >= block; --i) {\n            b[i] |= a[i - block] << rem;\n        \
    \    if (rem && i - block - 1 >= 0) b[i] |= a[i - block - 1] >> (B - rem);\n \
    \       }\n        a.swap(b);\n        normalize();\n        return *this;\n \
    \   }\n    DynamicBitset& operator>>=(int s) {\n        if (s <= 0) return *this;\n\
    \        if (s >= n) {\n            reset();\n            return *this;\n    \
    \    }\n        int block = s >> 6, rem = s & 63;\n        vector<ull> b(a.size(),\
    \ 0);\n        for (int i = 0; i + block < (int)a.size(); ++i) {\n           \
    \ b[i] |= a[i + block] >> rem;\n            if (rem && i + block + 1 < (int)a.size())\
    \ b[i] |= a[i + block + 1] << (B - rem);\n        }\n        a.swap(b);\n    \
    \    normalize();\n        return *this;\n    }\n\n    friend DynamicBitset operator<<(DynamicBitset\
    \ l, int s) { return l <<= s; }\n    friend DynamicBitset operator>>(DynamicBitset\
    \ l, int s) { return l >>= s; }\n};\n\n/**\n * @brief DynamicBitset\n * @docs\
    \ _md/dynamic_bitset.md\n */\n"
  code: "class DynamicBitset {\n    using ull = unsigned long long;\n    static constexpr\
    \ int B = 64;\n\n    int n;\n    vector<ull> a;\n\n    static int popcount(ull\
    \ x) {\n        return __builtin_popcountll(x);\n    }\n    static int ctz(ull\
    \ x) {\n        return __builtin_ctzll(x);\n    }\n\n    ull tail_mask() const\
    \ {\n        int rem = n & (B - 1);\n        return rem ? ((1ULL << rem) - 1)\
    \ : ~0ULL;\n    }\n\n    void normalize() {\n        if (!a.empty()) a.back()\
    \ &= tail_mask();\n    }\n\npublic:\n    DynamicBitset() : n(0) {}\n    explicit\
    \ DynamicBitset(int n, bool x = false) : n(n), a((n + B - 1) >> 6, x ? ~0ULL :\
    \ 0ULL) {\n        normalize();\n    }\n\n    int size() const { return n; }\n\
    \    bool empty() const { return n == 0; }\n\n    void reset() {\n        fill(a.begin(),\
    \ a.end(), 0);\n    }\n    void set() {\n        fill(a.begin(), a.end(), ~0ULL);\n\
    \        normalize();\n    }\n    void flip() {\n        for (auto &x : a) x =\
    \ ~x;\n        normalize();\n    }\n\n    bool test(int k) const {\n        return\
    \ (a[k >> 6] >> (k & 63)) & 1ULL;\n    }\n    void set(int k) {\n        a[k >>\
    \ 6] |= 1ULL << (k & 63);\n    }\n    void reset(int k) {\n        a[k >> 6] &=\
    \ ~(1ULL << (k & 63));\n    }\n    void flip(int k) {\n        a[k >> 6] ^= 1ULL\
    \ << (k & 63);\n    }\n    void assign(int k, bool x) {\n        if (x) set(k);\n\
    \        else reset(k);\n    }\n\n    bool any() const {\n        for (auto x\
    \ : a) if (x) return true;\n        return false;\n    }\n    bool none() const\
    \ { return !any(); }\n    bool all() const {\n        if (a.empty()) return true;\n\
    \        for (int i = 0; i + 1 < (int)a.size(); ++i) {\n            if (a[i] !=\
    \ ~0ULL) return false;\n        }\n        return a.back() == tail_mask();\n \
    \   }\n    int count() const {\n        int res = 0;\n        for (auto x : a)\
    \ res += popcount(x);\n        return res;\n    }\n\n    int find_first() const\
    \ {\n        for (int i = 0; i < (int)a.size(); ++i) {\n            if (a[i])\
    \ return (i << 6) + ctz(a[i]);\n        }\n        return -1;\n    }\n    int\
    \ find_next(int k) const {\n        ++k;\n        if (k >= n) return -1;\n   \
    \     int i = k >> 6;\n        ull x = a[i] & (~0ULL << (k & 63));\n        if\
    \ (x) return (i << 6) + ctz(x);\n        for (++i; i < (int)a.size(); ++i) {\n\
    \            if (a[i]) return (i << 6) + ctz(a[i]);\n        }\n        return\
    \ -1;\n    }\n\n    DynamicBitset& operator&=(const DynamicBitset &r) {\n    \
    \    for (int i = 0; i < (int)a.size(); ++i) a[i] &= r.a[i];\n        return *this;\n\
    \    }\n    DynamicBitset& operator|=(const DynamicBitset &r) {\n        for (int\
    \ i = 0; i < (int)a.size(); ++i) a[i] |= r.a[i];\n        return *this;\n    }\n\
    \    DynamicBitset& operator^=(const DynamicBitset &r) {\n        for (int i =\
    \ 0; i < (int)a.size(); ++i) a[i] ^= r.a[i];\n        normalize();\n        return\
    \ *this;\n    }\n\n    friend DynamicBitset operator&(DynamicBitset l, const DynamicBitset\
    \ &r) { return l &= r; }\n    friend DynamicBitset operator|(DynamicBitset l,\
    \ const DynamicBitset &r) { return l |= r; }\n    friend DynamicBitset operator^(DynamicBitset\
    \ l, const DynamicBitset &r) { return l ^= r; }\n\n    DynamicBitset& operator<<=(int\
    \ s) {\n        if (s <= 0) return *this;\n        if (s >= n) {\n           \
    \ reset();\n            return *this;\n        }\n        int block = s >> 6,\
    \ rem = s & 63;\n        vector<ull> b(a.size(), 0);\n        for (int i = (int)a.size()\
    \ - 1; i >= block; --i) {\n            b[i] |= a[i - block] << rem;\n        \
    \    if (rem && i - block - 1 >= 0) b[i] |= a[i - block - 1] >> (B - rem);\n \
    \       }\n        a.swap(b);\n        normalize();\n        return *this;\n \
    \   }\n    DynamicBitset& operator>>=(int s) {\n        if (s <= 0) return *this;\n\
    \        if (s >= n) {\n            reset();\n            return *this;\n    \
    \    }\n        int block = s >> 6, rem = s & 63;\n        vector<ull> b(a.size(),\
    \ 0);\n        for (int i = 0; i + block < (int)a.size(); ++i) {\n           \
    \ b[i] |= a[i + block] >> rem;\n            if (rem && i + block + 1 < (int)a.size())\
    \ b[i] |= a[i + block + 1] << (B - rem);\n        }\n        a.swap(b);\n    \
    \    normalize();\n        return *this;\n    }\n\n    friend DynamicBitset operator<<(DynamicBitset\
    \ l, int s) { return l <<= s; }\n    friend DynamicBitset operator>>(DynamicBitset\
    \ l, int s) { return l >>= s; }\n};\n\n/**\n * @brief DynamicBitset\n * @docs\
    \ _md/dynamic_bitset.md\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/dynamic_bitset.cpp
  requiredBy: []
  timestamp: '2026-03-08 16:57:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_many_aplusb_dynamic_bitset.test.cpp
documentation_of: datastructure/dynamic_bitset.cpp
layout: document
redirect_from:
- /library/datastructure/dynamic_bitset.cpp
- /library/datastructure/dynamic_bitset.cpp.html
title: DynamicBitset
---
---
layout: post
title: Dynamic Bitset
date: 2026-03-08
category: データ構造
tags: データ構造
---

## 説明
可変長の bitset。
`uint64_t` 単位で持ち、集合演算、shift、立っている bit の走査を扱う。

## できること
- `DynamicBitset bs(int n, bool x = false)`
  長さ `n` の bitset を作る。`x = true` なら全 bit を 1 で初期化する
- `int size() const`
  長さを返す
- `bool test(int k) const`
  `k` bit 目を返す
- `void set(int k)`, `void reset(int k)`, `void flip(int k)`, `void assign(int k, bool x)`
  `k` bit 目を更新する
- `void set()`, `void reset()`, `void flip()`
  全体を更新する
- `bool any() const`, `bool none() const`, `bool all() const`
  1 があるか、全て 0 か、全て 1 かを返す
- `int count() const`
  1 の個数を返す
- `int find_first() const`
  最初に立っている bit の位置を返す。なければ `-1`
- `int find_next(int k) const`
  `k` より右で最初に立っている bit の位置を返す。なければ `-1`
- `bs &= other`, `bs |= other`, `bs ^= other`
  bitset 同士の演算をその場で行う
- `bs << s`, `bs >> s`, `bs <<= s`, `bs >>= s`
  shift する

## 使い方
長さが同じ bitset 同士で演算する。
`find_first`, `find_next` を使うと立っている bit だけを走査できる。
