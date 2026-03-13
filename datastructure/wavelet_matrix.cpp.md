---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_static_range_frequency.test.cpp
    title: test/yosupo_static_range_frequency.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Wavelet Matrix
    links: []
  bundledCode: "#line 1 \"datastructure/wavelet_matrix.cpp\"\ntemplate <class T>\n\
    struct WaveletMatrix {\n    int n, lg, blocks;\n    vector<int> mid;\n    vector<unsigned\
    \ long long> bit;\n    vector<int> pref;\n    vector<T> vals;\n\n    WaveletMatrix()\
    \ : n(0), lg(0), blocks(0) {}\n    explicit WaveletMatrix(const vector<T> &v)\
    \ { build(v); }\n\n    void build(const vector<T> &v) {\n        n = (int)v.size();\n\
    \        vals = v;\n        sort(vals.begin(), vals.end());\n        vals.erase(unique(vals.begin(),\
    \ vals.end()), vals.end());\n\n        if (vals.empty()) {\n            lg = 0;\n\
    \            blocks = 0;\n            mid.clear();\n            bit.clear();\n\
    \            pref.clear();\n            return;\n        }\n\n        int m =\
    \ (int)vals.size();\n        lg = 0;\n        while ((1 << lg) < m) lg++;\n  \
    \      if (lg == 0) lg = 1;\n        blocks = (n + 63) >> 6;\n\n        vector<int>\
    \ cur(n);\n        for (int i = 0; i < n; ++i) {\n            cur[i] = (int)(lower_bound(vals.begin(),\
    \ vals.end(), v[i]) - vals.begin());\n        }\n\n        mid.assign(lg, 0);\n\
    \        bit.assign(lg * blocks, 0);\n        pref.assign(lg * (blocks + 1), 0);\n\
    \        vector<int> nxt(n);\n\n        for (int d = 0; d < lg; ++d) {\n     \
    \       int shift = lg - 1 - d;\n            auto *row = bit.data() + d * blocks;\n\
    \            auto *row_pref = pref.data() + d * (blocks + 1);\n            int\
    \ zero_cnt = 0;\n            for (int i = 0; i < n; ++i) {\n                int\
    \ b = (cur[i] >> shift) & 1;\n                if (b) row[i >> 6] |= 1ULL << (i\
    \ & 63);\n                else ++zero_cnt;\n            }\n            mid[d]\
    \ = zero_cnt;\n            for (int i = 0; i < blocks; ++i) row_pref[i + 1] =\
    \ row_pref[i] + __builtin_popcountll(row[i]);\n\n            int zi = 0, oi =\
    \ zero_cnt;\n            for (int i = 0; i < n; ++i) {\n                int x\
    \ = cur[i];\n                if ((x >> shift) & 1) nxt[oi++] = x;\n          \
    \      else nxt[zi++] = x;\n            }\n            cur.swap(nxt);\n      \
    \  }\n    }\n\n    int rank1(int d, int r) const {\n        int base = d * blocks;\n\
    \        int pref_base = d * (blocks + 1);\n        int block = r >> 6;\n    \
    \    int ret = pref[pref_base + block];\n        int rem = r & 63;\n        if\
    \ (rem) ret += __builtin_popcountll(bit[base + block] & ((1ULL << rem) - 1));\n\
    \        return ret;\n    }\n\n    int rank0(int d, int r) const {\n        return\
    \ r - rank1(d, r);\n    }\n\n    int count_less_index(int l, int r, int xi) const\
    \ {\n        if (xi <= 0 || l >= r || n == 0) return 0;\n        if (xi >= (int)vals.size())\
    \ return r - l;\n\n        int res = 0;\n        for (int d = 0; d < lg; ++d)\
    \ {\n            int shift = lg - 1 - d;\n            int b = (xi >> shift) &\
    \ 1;\n            int l0 = rank0(d, l), r0 = rank0(d, r);\n            if (b)\
    \ {\n                res += r0 - l0;\n                l = mid[d] + rank1(d, l);\n\
    \                r = mid[d] + rank1(d, r);\n            }\n            else {\n\
    \                l = l0;\n                r = r0;\n            }\n        }\n\
    \        return res;\n    }\n\n    int count_less(int l, int r, const T &x) const\
    \ {\n        int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \        return count_less_index(l, r, xi);\n    }\n\n    int range_freq(int l,\
    \ int r, const T &lower, const T &upper) const {\n        if (lower >= upper ||\
    \ l >= r) return 0;\n        return count_less(l, r, upper) - count_less(l, r,\
    \ lower);\n    }\n\n    int freq(int l, int r, const T &x) const {\n        int\
    \ li = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());\n     \
    \   int ri = (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \        return count_less_index(l, r, ri) - count_less_index(l, r, li);\n   \
    \ }\n\n    T kth_smallest(int l, int r, int k) const {\n        int idx = 0;\n\
    \        for (int d = 0; d < lg; ++d) {\n            int l0 = rank0(d, l), r0\
    \ = rank0(d, r);\n            int z = r0 - l0;\n            idx <<= 1;\n     \
    \       if (k < z) {\n                l = l0;\n                r = r0;\n     \
    \       }\n            else {\n                k -= z;\n                idx |=\
    \ 1;\n                l = mid[d] + rank1(d, l);\n                r = mid[d] +\
    \ rank1(d, r);\n            }\n        }\n        return vals[idx];\n    }\n\n\
    \    T kth_largest(int l, int r, int k) const {\n        return kth_smallest(l,\
    \ r, r - l - 1 - k);\n    }\n\n    bool prev_value(int l, int r, const T &upper,\
    \ T &res) const {\n        int cnt = count_less(l, r, upper);\n        if (cnt\
    \ == 0) return false;\n        res = kth_smallest(l, r, cnt - 1);\n        return\
    \ true;\n    }\n\n    bool next_value(int l, int r, const T &lower, T &res) const\
    \ {\n        int cnt = count_less(l, r, lower);\n        if (cnt == r - l) return\
    \ false;\n        res = kth_smallest(l, r, cnt);\n        return true;\n    }\n\
    };\n\n/**\n * @brief Wavelet Matrix\n */\n"
  code: "template <class T>\nstruct WaveletMatrix {\n    int n, lg, blocks;\n    vector<int>\
    \ mid;\n    vector<unsigned long long> bit;\n    vector<int> pref;\n    vector<T>\
    \ vals;\n\n    WaveletMatrix() : n(0), lg(0), blocks(0) {}\n    explicit WaveletMatrix(const\
    \ vector<T> &v) { build(v); }\n\n    void build(const vector<T> &v) {\n      \
    \  n = (int)v.size();\n        vals = v;\n        sort(vals.begin(), vals.end());\n\
    \        vals.erase(unique(vals.begin(), vals.end()), vals.end());\n\n       \
    \ if (vals.empty()) {\n            lg = 0;\n            blocks = 0;\n        \
    \    mid.clear();\n            bit.clear();\n            pref.clear();\n     \
    \       return;\n        }\n\n        int m = (int)vals.size();\n        lg =\
    \ 0;\n        while ((1 << lg) < m) lg++;\n        if (lg == 0) lg = 1;\n    \
    \    blocks = (n + 63) >> 6;\n\n        vector<int> cur(n);\n        for (int\
    \ i = 0; i < n; ++i) {\n            cur[i] = (int)(lower_bound(vals.begin(), vals.end(),\
    \ v[i]) - vals.begin());\n        }\n\n        mid.assign(lg, 0);\n        bit.assign(lg\
    \ * blocks, 0);\n        pref.assign(lg * (blocks + 1), 0);\n        vector<int>\
    \ nxt(n);\n\n        for (int d = 0; d < lg; ++d) {\n            int shift = lg\
    \ - 1 - d;\n            auto *row = bit.data() + d * blocks;\n            auto\
    \ *row_pref = pref.data() + d * (blocks + 1);\n            int zero_cnt = 0;\n\
    \            for (int i = 0; i < n; ++i) {\n                int b = (cur[i] >>\
    \ shift) & 1;\n                if (b) row[i >> 6] |= 1ULL << (i & 63);\n     \
    \           else ++zero_cnt;\n            }\n            mid[d] = zero_cnt;\n\
    \            for (int i = 0; i < blocks; ++i) row_pref[i + 1] = row_pref[i] +\
    \ __builtin_popcountll(row[i]);\n\n            int zi = 0, oi = zero_cnt;\n  \
    \          for (int i = 0; i < n; ++i) {\n                int x = cur[i];\n  \
    \              if ((x >> shift) & 1) nxt[oi++] = x;\n                else nxt[zi++]\
    \ = x;\n            }\n            cur.swap(nxt);\n        }\n    }\n\n    int\
    \ rank1(int d, int r) const {\n        int base = d * blocks;\n        int pref_base\
    \ = d * (blocks + 1);\n        int block = r >> 6;\n        int ret = pref[pref_base\
    \ + block];\n        int rem = r & 63;\n        if (rem) ret += __builtin_popcountll(bit[base\
    \ + block] & ((1ULL << rem) - 1));\n        return ret;\n    }\n\n    int rank0(int\
    \ d, int r) const {\n        return r - rank1(d, r);\n    }\n\n    int count_less_index(int\
    \ l, int r, int xi) const {\n        if (xi <= 0 || l >= r || n == 0) return 0;\n\
    \        if (xi >= (int)vals.size()) return r - l;\n\n        int res = 0;\n \
    \       for (int d = 0; d < lg; ++d) {\n            int shift = lg - 1 - d;\n\
    \            int b = (xi >> shift) & 1;\n            int l0 = rank0(d, l), r0\
    \ = rank0(d, r);\n            if (b) {\n                res += r0 - l0;\n    \
    \            l = mid[d] + rank1(d, l);\n                r = mid[d] + rank1(d,\
    \ r);\n            }\n            else {\n                l = l0;\n          \
    \      r = r0;\n            }\n        }\n        return res;\n    }\n\n    int\
    \ count_less(int l, int r, const T &x) const {\n        int xi = (int)(lower_bound(vals.begin(),\
    \ vals.end(), x) - vals.begin());\n        return count_less_index(l, r, xi);\n\
    \    }\n\n    int range_freq(int l, int r, const T &lower, const T &upper) const\
    \ {\n        if (lower >= upper || l >= r) return 0;\n        return count_less(l,\
    \ r, upper) - count_less(l, r, lower);\n    }\n\n    int freq(int l, int r, const\
    \ T &x) const {\n        int li = (int)(lower_bound(vals.begin(), vals.end(),\
    \ x) - vals.begin());\n        int ri = (int)(upper_bound(vals.begin(), vals.end(),\
    \ x) - vals.begin());\n        return count_less_index(l, r, ri) - count_less_index(l,\
    \ r, li);\n    }\n\n    T kth_smallest(int l, int r, int k) const {\n        int\
    \ idx = 0;\n        for (int d = 0; d < lg; ++d) {\n            int l0 = rank0(d,\
    \ l), r0 = rank0(d, r);\n            int z = r0 - l0;\n            idx <<= 1;\n\
    \            if (k < z) {\n                l = l0;\n                r = r0;\n\
    \            }\n            else {\n                k -= z;\n                idx\
    \ |= 1;\n                l = mid[d] + rank1(d, l);\n                r = mid[d]\
    \ + rank1(d, r);\n            }\n        }\n        return vals[idx];\n    }\n\
    \n    T kth_largest(int l, int r, int k) const {\n        return kth_smallest(l,\
    \ r, r - l - 1 - k);\n    }\n\n    bool prev_value(int l, int r, const T &upper,\
    \ T &res) const {\n        int cnt = count_less(l, r, upper);\n        if (cnt\
    \ == 0) return false;\n        res = kth_smallest(l, r, cnt - 1);\n        return\
    \ true;\n    }\n\n    bool next_value(int l, int r, const T &lower, T &res) const\
    \ {\n        int cnt = count_less(l, r, lower);\n        if (cnt == r - l) return\
    \ false;\n        res = kth_smallest(l, r, cnt);\n        return true;\n    }\n\
    };\n\n/**\n * @brief Wavelet Matrix\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/wavelet_matrix.cpp
  requiredBy: []
  timestamp: '2026-03-13 22:39:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_static_range_frequency.test.cpp
date: 2026-03-07
documentation_of: datastructure/wavelet_matrix.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Wavelet Matrix
---

## 説明
静的配列に対して、区間内の順序統計量・値の出現回数・前駆/後継検索を扱うデータ構造。

## 計算量
- 構築: $O(N \log \sigma)$
- `count_less` / `range_freq` / `freq`: $O(\log \sigma)$
- `kth_smallest` / `kth_largest`: $O(\log \sigma)$

$N$ は配列長、$\sigma$ は異なる値の個数。

## 使い方
1. `WaveletMatrix<T> wm(v);` で配列 `v` から構築する。
2. 区間 `[l, r)` に対して以下を呼ぶ。

## できること
- `count_less(l, r, x)` : 区間 $[l, r)$ のうち `x` 未満の個数を返す
- `range_freq(l, r, lower, upper)` : 区間 $[l, r)$ のうち $lower \le a_i < upper$ の個数を返す
- `freq(l, r, x)` : 区間 $[l, r)$ における `x` の出現回数を返す
- `kth_smallest(l, r, k)` : 区間 $[l, r)$ の `k` 番目 (0-indexed) に小さい値を返す
- `kth_largest(l, r, k)` : 区間 $[l, r)$ の `k` 番目 (0-indexed) に大きい値を返す
- `prev_value(l, r, upper, res)` : 区間 $[l, r)$ にある `upper` 未満の最大値を `res` に返す。存在しない場合 `false`
- `next_value(l, r, lower, res)` : 区間 $[l, r)$ にある `lower` 以上の最小値を `res` に返す。存在しない場合 `false`

## 実装上の補足
- 値は内部で座標圧縮して扱う。
- クエリはすべて静的配列前提。
