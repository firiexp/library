---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_range_kth_smallest.test.cpp
    title: test/yosupo_range_kth_smallest.test.cpp
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
    \ { build(v); }\n\n    static inline void rank1_pair(const unsigned long long\
    \ *row, const int *row_pref, int l, int r, int &l1, int &r1) {\n        int l_block\
    \ = l >> 6;\n        l1 = row_pref[l_block];\n        int l_rem = l & 63;\n  \
    \      if (l_rem) l1 += __builtin_popcountll(row[l_block] & ((1ULL << l_rem) -\
    \ 1));\n\n        int r_block = r >> 6;\n        r1 = row_pref[r_block];\n   \
    \     int r_rem = r & 63;\n        if (r_rem) r1 += __builtin_popcountll(row[r_block]\
    \ & ((1ULL << r_rem) - 1));\n    }\n\n    template <class U>\n    static auto\
    \ encode_key(U x) -> typename make_unsigned<U>::type {\n        using Key = typename\
    \ make_unsigned<U>::type;\n        Key key = static_cast<Key>(x);\n        if\
    \ constexpr (is_signed<U>::value) key ^= (Key(1) << (sizeof(U) * 8 - 1));\n  \
    \      return key;\n    }\n\n    void compress_generic(const vector<T> &v, vector<int>\
    \ &cur) {\n        vector<pair<T, int>> ord(n);\n        for (int i = 0; i < n;\
    \ ++i) ord[i] = {v[i], i};\n        sort(ord.begin(), ord.end(), [](const pair<T,\
    \ int> &a, const pair<T, int> &b) {\n            return a.first < b.first;\n \
    \       });\n        vals.clear();\n        vals.reserve(n);\n        for (int\
    \ i = 0; i < n; ++i) {\n            if (vals.empty() || vals.back() < ord[i].first\
    \ || ord[i].first < vals.back()) {\n                vals.push_back(ord[i].first);\n\
    \            }\n            cur[ord[i].second] = (int)vals.size() - 1;\n     \
    \   }\n    }\n\n    void compress_integral(const vector<T> &v, vector<int> &cur)\
    \ {\n        using Key = typename make_unsigned<T>::type;\n        vector<Key>\
    \ keys(n);\n        vector<int> ord(n), buf(n);\n        for (int i = 0; i < n;\
    \ ++i) {\n            keys[i] = encode_key(v[i]);\n            ord[i] = i;\n \
    \       }\n\n        const int B = 16;\n        const int MASK = (1 << B) - 1;\n\
    \        const int bucket_count = 1 << B;\n        const int passes = (int)(sizeof(Key)\
    \ * 8 + B - 1) / B;\n        vector<int> cnt(bucket_count), pos(bucket_count);\n\
    \        for (int pass = 0; pass < passes; ++pass) {\n            fill(cnt.begin(),\
    \ cnt.end(), 0);\n            int shift = pass * B;\n            for (int i =\
    \ 0; i < n; ++i) ++cnt[(keys[ord[i]] >> shift) & MASK];\n            pos[0] =\
    \ 0;\n            for (int i = 0; i + 1 < bucket_count; ++i) pos[i + 1] = pos[i]\
    \ + cnt[i];\n            for (int i = 0; i < n; ++i) {\n                int id\
    \ = ord[i];\n                buf[pos[(keys[id] >> shift) & MASK]++] = id;\n  \
    \          }\n            ord.swap(buf);\n        }\n\n        vals.clear();\n\
    \        vals.reserve(n);\n        bool has_prev = false;\n        Key prev =\
    \ 0;\n        for (int i = 0; i < n; ++i) {\n            int id = ord[i];\n  \
    \          if (!has_prev || keys[id] != prev) {\n                vals.push_back(v[id]);\n\
    \                prev = keys[id];\n                has_prev = true;\n        \
    \    }\n            cur[id] = (int)vals.size() - 1;\n        }\n    }\n\n    void\
    \ compress_values(const vector<T> &v, vector<int> &cur) {\n        if constexpr\
    \ (is_integral<T>::value && sizeof(T) <= 8) compress_integral(v, cur);\n     \
    \   else compress_generic(v, cur);\n    }\n\n    void build_from_index_internal(vector<int>\
    \ cur) {\n        n = (int)cur.size();\n        if (n == 0) {\n            lg\
    \ = 0;\n            blocks = 0;\n            mid.clear();\n            bit.clear();\n\
    \            pref.clear();\n            return;\n        }\n\n        int m =\
    \ (int)vals.size();\n        lg = 0;\n        while ((1LL << lg) < m) ++lg;\n\
    \        if (lg == 0) lg = 1;\n        blocks = (n + 63) >> 6;\n\n        mid.assign(lg,\
    \ 0);\n        bit.assign(lg * blocks, 0);\n        pref.assign(lg * (blocks +\
    \ 1), 0);\n        vector<int> nxt(n);\n\n        for (int d = 0, shift = lg -\
    \ 1; d < lg; ++d, --shift) {\n            auto *row = bit.data() + d * blocks;\n\
    \            auto *row_pref = pref.data() + d * (blocks + 1);\n            int\
    \ zero_cnt = 0;\n            for (int i = 0; i < n; ++i) {\n                int\
    \ x = cur[i];\n                int b = (x >> shift) & 1;\n                if (b)\
    \ row[i >> 6] |= 1ULL << (i & 63);\n                else ++zero_cnt;\n       \
    \     }\n            mid[d] = zero_cnt;\n            for (int i = 0; i < blocks;\
    \ ++i) row_pref[i + 1] = row_pref[i] + __builtin_popcountll(row[i]);\n\n     \
    \       int zi = 0, oi = zero_cnt;\n            for (int i = 0; i < n; ++i) {\n\
    \                int x = cur[i];\n                if ((x >> shift) & 1) nxt[oi++]\
    \ = x;\n                else nxt[zi++] = x;\n            }\n            cur.swap(nxt);\n\
    \        }\n    }\n\n    void build(const vector<T> &v) {\n        n = (int)v.size();\n\
    \        if (n == 0) {\n            lg = 0;\n            blocks = 0;\n       \
    \     vals.clear();\n            mid.clear();\n            bit.clear();\n    \
    \        pref.clear();\n            return;\n        }\n\n        vector<int>\
    \ cur(n);\n        compress_values(v, cur);\n        build_from_index_internal(move(cur));\n\
    \    }\n\n    void build_from_index(const vector<int> &idx, const vector<T> &sorted_vals)\
    \ {\n        vals = sorted_vals;\n        build_from_index_internal(idx);\n  \
    \  }\n\n    int count_less_index(int l, int r, int xi) const {\n        if (xi\
    \ <= 0 || l >= r || n == 0) return 0;\n        if (xi >= (int)vals.size()) return\
    \ r - l;\n\n        const int *mid_data = mid.data();\n        const auto *bit_data\
    \ = bit.data();\n        const int *pref_data = pref.data();\n        int res\
    \ = 0;\n        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n    \
    \        int l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n\
    \            int l0 = l - l1, r0 = r - r1;\n            if ((xi >> shift) & 1)\
    \ {\n                res += r0 - l0;\n                l = mid_data[d] + l1;\n\
    \                r = mid_data[d] + r1;\n            }\n            else {\n  \
    \              l = l0;\n                r = r0;\n            }\n            bit_data\
    \ += blocks;\n            pref_data += blocks + 1;\n        }\n        return\
    \ res;\n    }\n\n    int count_less(int l, int r, const T &x) const {\n      \
    \  int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \        return count_less_index(l, r, xi);\n    }\n\n    int count_equal_index(int\
    \ l, int r, int xi) const {\n        if (l >= r || n == 0 || xi < 0 || xi >= (int)vals.size())\
    \ return 0;\n\n        const int *mid_data = mid.data();\n        const auto *bit_data\
    \ = bit.data();\n        const int *pref_data = pref.data();\n        for (int\
    \ d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n            int l1, r1;\n  \
    \          rank1_pair(bit_data, pref_data, l, r, l1, r1);\n            int l0\
    \ = l - l1, r0 = r - r1;\n            if ((xi >> shift) & 1) {\n             \
    \   l = mid_data[d] + l1;\n                r = mid_data[d] + r1;\n           \
    \ }\n            else {\n                l = l0;\n                r = r0;\n  \
    \          }\n            bit_data += blocks;\n            pref_data += blocks\
    \ + 1;\n        }\n        return r - l;\n    }\n\n    int range_freq(int l, int\
    \ r, const T &lower, const T &upper) const {\n        if (lower >= upper || l\
    \ >= r) return 0;\n        return count_less(l, r, upper) - count_less(l, r, lower);\n\
    \    }\n\n    int freq(int l, int r, const T &x) const {\n        int xi = (int)(lower_bound(vals.begin(),\
    \ vals.end(), x) - vals.begin());\n        if (xi == (int)vals.size() || vals[xi]\
    \ != x) return 0;\n        return count_equal_index(l, r, xi);\n    }\n\n    T\
    \ kth_smallest(int l, int r, int k) const {\n        const int *mid_data = mid.data();\n\
    \        const auto *bit_data = bit.data();\n        const int *pref_data = pref.data();\n\
    \        int idx = 0;\n        for (int d = 0; d < lg; ++d) {\n            int\
    \ l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n      \
    \      int l0 = l - l1, r0 = r - r1;\n            int z = r0 - l0;\n         \
    \   idx <<= 1;\n            if (k < z) {\n                l = l0;\n          \
    \      r = r0;\n            }\n            else {\n                k -= z;\n \
    \               idx |= 1;\n                l = mid_data[d] + l1;\n           \
    \     r = mid_data[d] + r1;\n            }\n            bit_data += blocks;\n\
    \            pref_data += blocks + 1;\n        }\n        return vals[idx];\n\
    \    }\n\n    T kth_largest(int l, int r, int k) const {\n        return kth_smallest(l,\
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
    \ vector<T> &v) { build(v); }\n\n    static inline void rank1_pair(const unsigned\
    \ long long *row, const int *row_pref, int l, int r, int &l1, int &r1) {\n   \
    \     int l_block = l >> 6;\n        l1 = row_pref[l_block];\n        int l_rem\
    \ = l & 63;\n        if (l_rem) l1 += __builtin_popcountll(row[l_block] & ((1ULL\
    \ << l_rem) - 1));\n\n        int r_block = r >> 6;\n        r1 = row_pref[r_block];\n\
    \        int r_rem = r & 63;\n        if (r_rem) r1 += __builtin_popcountll(row[r_block]\
    \ & ((1ULL << r_rem) - 1));\n    }\n\n    template <class U>\n    static auto\
    \ encode_key(U x) -> typename make_unsigned<U>::type {\n        using Key = typename\
    \ make_unsigned<U>::type;\n        Key key = static_cast<Key>(x);\n        if\
    \ constexpr (is_signed<U>::value) key ^= (Key(1) << (sizeof(U) * 8 - 1));\n  \
    \      return key;\n    }\n\n    void compress_generic(const vector<T> &v, vector<int>\
    \ &cur) {\n        vector<pair<T, int>> ord(n);\n        for (int i = 0; i < n;\
    \ ++i) ord[i] = {v[i], i};\n        sort(ord.begin(), ord.end(), [](const pair<T,\
    \ int> &a, const pair<T, int> &b) {\n            return a.first < b.first;\n \
    \       });\n        vals.clear();\n        vals.reserve(n);\n        for (int\
    \ i = 0; i < n; ++i) {\n            if (vals.empty() || vals.back() < ord[i].first\
    \ || ord[i].first < vals.back()) {\n                vals.push_back(ord[i].first);\n\
    \            }\n            cur[ord[i].second] = (int)vals.size() - 1;\n     \
    \   }\n    }\n\n    void compress_integral(const vector<T> &v, vector<int> &cur)\
    \ {\n        using Key = typename make_unsigned<T>::type;\n        vector<Key>\
    \ keys(n);\n        vector<int> ord(n), buf(n);\n        for (int i = 0; i < n;\
    \ ++i) {\n            keys[i] = encode_key(v[i]);\n            ord[i] = i;\n \
    \       }\n\n        const int B = 16;\n        const int MASK = (1 << B) - 1;\n\
    \        const int bucket_count = 1 << B;\n        const int passes = (int)(sizeof(Key)\
    \ * 8 + B - 1) / B;\n        vector<int> cnt(bucket_count), pos(bucket_count);\n\
    \        for (int pass = 0; pass < passes; ++pass) {\n            fill(cnt.begin(),\
    \ cnt.end(), 0);\n            int shift = pass * B;\n            for (int i =\
    \ 0; i < n; ++i) ++cnt[(keys[ord[i]] >> shift) & MASK];\n            pos[0] =\
    \ 0;\n            for (int i = 0; i + 1 < bucket_count; ++i) pos[i + 1] = pos[i]\
    \ + cnt[i];\n            for (int i = 0; i < n; ++i) {\n                int id\
    \ = ord[i];\n                buf[pos[(keys[id] >> shift) & MASK]++] = id;\n  \
    \          }\n            ord.swap(buf);\n        }\n\n        vals.clear();\n\
    \        vals.reserve(n);\n        bool has_prev = false;\n        Key prev =\
    \ 0;\n        for (int i = 0; i < n; ++i) {\n            int id = ord[i];\n  \
    \          if (!has_prev || keys[id] != prev) {\n                vals.push_back(v[id]);\n\
    \                prev = keys[id];\n                has_prev = true;\n        \
    \    }\n            cur[id] = (int)vals.size() - 1;\n        }\n    }\n\n    void\
    \ compress_values(const vector<T> &v, vector<int> &cur) {\n        if constexpr\
    \ (is_integral<T>::value && sizeof(T) <= 8) compress_integral(v, cur);\n     \
    \   else compress_generic(v, cur);\n    }\n\n    void build_from_index_internal(vector<int>\
    \ cur) {\n        n = (int)cur.size();\n        if (n == 0) {\n            lg\
    \ = 0;\n            blocks = 0;\n            mid.clear();\n            bit.clear();\n\
    \            pref.clear();\n            return;\n        }\n\n        int m =\
    \ (int)vals.size();\n        lg = 0;\n        while ((1LL << lg) < m) ++lg;\n\
    \        if (lg == 0) lg = 1;\n        blocks = (n + 63) >> 6;\n\n        mid.assign(lg,\
    \ 0);\n        bit.assign(lg * blocks, 0);\n        pref.assign(lg * (blocks +\
    \ 1), 0);\n        vector<int> nxt(n);\n\n        for (int d = 0, shift = lg -\
    \ 1; d < lg; ++d, --shift) {\n            auto *row = bit.data() + d * blocks;\n\
    \            auto *row_pref = pref.data() + d * (blocks + 1);\n            int\
    \ zero_cnt = 0;\n            for (int i = 0; i < n; ++i) {\n                int\
    \ x = cur[i];\n                int b = (x >> shift) & 1;\n                if (b)\
    \ row[i >> 6] |= 1ULL << (i & 63);\n                else ++zero_cnt;\n       \
    \     }\n            mid[d] = zero_cnt;\n            for (int i = 0; i < blocks;\
    \ ++i) row_pref[i + 1] = row_pref[i] + __builtin_popcountll(row[i]);\n\n     \
    \       int zi = 0, oi = zero_cnt;\n            for (int i = 0; i < n; ++i) {\n\
    \                int x = cur[i];\n                if ((x >> shift) & 1) nxt[oi++]\
    \ = x;\n                else nxt[zi++] = x;\n            }\n            cur.swap(nxt);\n\
    \        }\n    }\n\n    void build(const vector<T> &v) {\n        n = (int)v.size();\n\
    \        if (n == 0) {\n            lg = 0;\n            blocks = 0;\n       \
    \     vals.clear();\n            mid.clear();\n            bit.clear();\n    \
    \        pref.clear();\n            return;\n        }\n\n        vector<int>\
    \ cur(n);\n        compress_values(v, cur);\n        build_from_index_internal(move(cur));\n\
    \    }\n\n    void build_from_index(const vector<int> &idx, const vector<T> &sorted_vals)\
    \ {\n        vals = sorted_vals;\n        build_from_index_internal(idx);\n  \
    \  }\n\n    int count_less_index(int l, int r, int xi) const {\n        if (xi\
    \ <= 0 || l >= r || n == 0) return 0;\n        if (xi >= (int)vals.size()) return\
    \ r - l;\n\n        const int *mid_data = mid.data();\n        const auto *bit_data\
    \ = bit.data();\n        const int *pref_data = pref.data();\n        int res\
    \ = 0;\n        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n    \
    \        int l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n\
    \            int l0 = l - l1, r0 = r - r1;\n            if ((xi >> shift) & 1)\
    \ {\n                res += r0 - l0;\n                l = mid_data[d] + l1;\n\
    \                r = mid_data[d] + r1;\n            }\n            else {\n  \
    \              l = l0;\n                r = r0;\n            }\n            bit_data\
    \ += blocks;\n            pref_data += blocks + 1;\n        }\n        return\
    \ res;\n    }\n\n    int count_less(int l, int r, const T &x) const {\n      \
    \  int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \        return count_less_index(l, r, xi);\n    }\n\n    int count_equal_index(int\
    \ l, int r, int xi) const {\n        if (l >= r || n == 0 || xi < 0 || xi >= (int)vals.size())\
    \ return 0;\n\n        const int *mid_data = mid.data();\n        const auto *bit_data\
    \ = bit.data();\n        const int *pref_data = pref.data();\n        for (int\
    \ d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n            int l1, r1;\n  \
    \          rank1_pair(bit_data, pref_data, l, r, l1, r1);\n            int l0\
    \ = l - l1, r0 = r - r1;\n            if ((xi >> shift) & 1) {\n             \
    \   l = mid_data[d] + l1;\n                r = mid_data[d] + r1;\n           \
    \ }\n            else {\n                l = l0;\n                r = r0;\n  \
    \          }\n            bit_data += blocks;\n            pref_data += blocks\
    \ + 1;\n        }\n        return r - l;\n    }\n\n    int range_freq(int l, int\
    \ r, const T &lower, const T &upper) const {\n        if (lower >= upper || l\
    \ >= r) return 0;\n        return count_less(l, r, upper) - count_less(l, r, lower);\n\
    \    }\n\n    int freq(int l, int r, const T &x) const {\n        int xi = (int)(lower_bound(vals.begin(),\
    \ vals.end(), x) - vals.begin());\n        if (xi == (int)vals.size() || vals[xi]\
    \ != x) return 0;\n        return count_equal_index(l, r, xi);\n    }\n\n    T\
    \ kth_smallest(int l, int r, int k) const {\n        const int *mid_data = mid.data();\n\
    \        const auto *bit_data = bit.data();\n        const int *pref_data = pref.data();\n\
    \        int idx = 0;\n        for (int d = 0; d < lg; ++d) {\n            int\
    \ l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n      \
    \      int l0 = l - l1, r0 = r - r1;\n            int z = r0 - l0;\n         \
    \   idx <<= 1;\n            if (k < z) {\n                l = l0;\n          \
    \      r = r0;\n            }\n            else {\n                k -= z;\n \
    \               idx |= 1;\n                l = mid_data[d] + l1;\n           \
    \     r = mid_data[d] + r1;\n            }\n            bit_data += blocks;\n\
    \            pref_data += blocks + 1;\n        }\n        return vals[idx];\n\
    \    }\n\n    T kth_largest(int l, int r, int k) const {\n        return kth_smallest(l,\
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
  timestamp: '2026-03-26 00:19:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_range_kth_smallest.test.cpp
  - test/yosupo_static_range_frequency.test.cpp
date: 2026-03-26
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
2. 事前に座標圧縮したなら `wm.build_from_index(idx, sorted_vals);` でも構築できる。
3. 区間 `[l, r)` に対して以下を呼ぶ。

## できること
- `build_from_index(idx, sorted_vals)` : 圧縮済み index 列 `idx` と昇順の値列 `sorted_vals` から構築する
- `count_less(l, r, x)` : 区間 $[l, r)$ のうち `x` 未満の個数を返す
- `count_less_index(l, r, xi)` : 区間 $[l, r)$ のうち圧縮 index `xi` 未満の個数を返す
- `range_freq(l, r, lower, upper)` : 区間 $[l, r)$ のうち $lower \le a_i < upper$ の個数を返す
- `freq(l, r, x)` : 区間 $[l, r)$ における `x` の出現回数を返す
- `count_equal_index(l, r, xi)` : 区間 $[l, r)$ における圧縮 index `xi` の出現回数を返す
- `kth_smallest(l, r, k)` : 区間 $[l, r)$ の `k` 番目 (0-indexed) に小さい値を返す
- `kth_largest(l, r, k)` : 区間 $[l, r)$ の `k` 番目 (0-indexed) に大きい値を返す
- `prev_value(l, r, upper, res)` : 区間 $[l, r)$ にある `upper` 未満の最大値を `res` に返す。存在しない場合 `false`
- `next_value(l, r, lower, res)` : 区間 $[l, r)$ にある `lower` 以上の最小値を `res` に返す。存在しない場合 `false`

## 実装上の補足
- 値は内部で座標圧縮して扱う。
- 圧縮済みで使うときは query 側も index API を使うと二分探索を省ける。
- クエリはすべて静的配列前提。
