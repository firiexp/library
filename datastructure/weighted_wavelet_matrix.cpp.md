---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_static_range_sum_with_upper_bound.test.cpp
    title: test/yosupo_static_range_sum_with_upper_bound.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u91CD\u307F\u4ED8\u304DWavelet Matrix(Weighted Wavelet Matrix)"
    links: []
  bundledCode: "#line 1 \"datastructure/weighted_wavelet_matrix.cpp\"\ntemplate <class\
    \ T, class U>\nstruct WeightedWaveletMatrix {\n    struct CountSum {\n       \
    \ int count;\n        U sum;\n    };\n\n    int n, lg, blocks;\n    vector<int>\
    \ mid;\n    vector<unsigned long long> bit;\n    vector<int> pref;\n    vector<U>\
    \ zero_sum;\n    vector<U> base_sum;\n    vector<T> vals;\n\n    WeightedWaveletMatrix()\
    \ : n(0), lg(0), blocks(0) {}\n    WeightedWaveletMatrix(const vector<T> &v, const\
    \ vector<U> &w) { build(v, w); }\n\n    static inline void rank1_pair(const unsigned\
    \ long long *row, const int *row_pref, int l, int r, int &l1, int &r1) {\n   \
    \     int l_block = l >> 6;\n        l1 = row_pref[l_block];\n        int l_rem\
    \ = l & 63;\n        if (l_rem) l1 += __builtin_popcountll(row[l_block] & ((1ULL\
    \ << l_rem) - 1));\n\n        int r_block = r >> 6;\n        r1 = row_pref[r_block];\n\
    \        int r_rem = r & 63;\n        if (r_rem) r1 += __builtin_popcountll(row[r_block]\
    \ & ((1ULL << r_rem) - 1));\n    }\n\n    template <class X>\n    static auto\
    \ encode_key(X x) -> typename make_unsigned<X>::type {\n        using Key = typename\
    \ make_unsigned<X>::type;\n        Key key = static_cast<Key>(x);\n        if\
    \ constexpr (is_signed<X>::value) key ^= (Key(1) << (sizeof(X) * 8 - 1));\n  \
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
    \ cur, const vector<U> &w) {\n        n = (int)cur.size();\n        base_sum.assign(n\
    \ + 1, U());\n        for (int i = 0; i < n; ++i) base_sum[i + 1] = base_sum[i]\
    \ + w[i];\n\n        if (n == 0) {\n            lg = 0;\n            blocks =\
    \ 0;\n            mid.clear();\n            bit.clear();\n            pref.clear();\n\
    \            zero_sum.clear();\n            return;\n        }\n\n        int\
    \ m = (int)vals.size();\n        lg = 0;\n        while ((1LL << lg) < m) ++lg;\n\
    \        if (lg == 0) lg = 1;\n        blocks = (n + 63) >> 6;\n        vector<U>\
    \ cur_w = w;\n\n        mid.assign(lg, 0);\n        bit.assign(lg * blocks, 0);\n\
    \        pref.assign(lg * (blocks + 1), 0);\n        zero_sum.assign(lg * (n +\
    \ 1), U());\n        vector<int> nxt(n);\n        vector<U> nxt_w(n);\n\n    \
    \    for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n            auto\
    \ *row = bit.data() + d * blocks;\n            auto *row_pref = pref.data() +\
    \ d * (blocks + 1);\n            auto *row_zero_sum = zero_sum.data() + d * (n\
    \ + 1);\n            int zero_cnt = 0;\n            for (int i = 0; i < n; ++i)\
    \ {\n                int x = cur[i];\n                int b = (x >> shift) & 1;\n\
    \                if (b) row[i >> 6] |= 1ULL << (i & 63);\n                else\
    \ ++zero_cnt;\n                row_zero_sum[i + 1] = row_zero_sum[i] + (b ? U()\
    \ : cur_w[i]);\n            }\n            mid[d] = zero_cnt;\n            for\
    \ (int i = 0; i < blocks; ++i) row_pref[i + 1] = row_pref[i] + __builtin_popcountll(row[i]);\n\
    \n            int zi = 0, oi = zero_cnt;\n            for (int i = 0; i < n; ++i)\
    \ {\n                int x = cur[i];\n                if ((x >> shift) & 1) {\n\
    \                    nxt[oi] = x;\n                    nxt_w[oi++] = cur_w[i];\n\
    \                }\n                else {\n                    nxt[zi] = x;\n\
    \                    nxt_w[zi++] = cur_w[i];\n                }\n            }\n\
    \            cur.swap(nxt);\n            cur_w.swap(nxt_w);\n        }\n    }\n\
    \n    void build(const vector<T> &v, const vector<U> &w) {\n        n = (int)v.size();\n\
    \        if (n == 0) {\n            lg = 0;\n            blocks = 0;\n       \
    \     vals.clear();\n            mid.clear();\n            bit.clear();\n    \
    \        pref.clear();\n            zero_sum.clear();\n            base_sum.assign(1,\
    \ U());\n            return;\n        }\n\n        vector<int> cur(n);\n     \
    \   compress_values(v, cur);\n        build_from_index_internal(move(cur), w);\n\
    \    }\n\n    void build_from_index(const vector<int> &idx, const vector<T> &sorted_vals,\
    \ const vector<U> &w) {\n        vals = sorted_vals;\n        build_from_index_internal(idx,\
    \ w);\n    }\n\n    CountSum count_sum_less_index(int l, int r, int xi) const\
    \ {\n        if (xi <= 0 || l >= r || n == 0) return {0, U()};\n        if (xi\
    \ >= (int)vals.size()) return {r - l, base_sum[r] - base_sum[l]};\n\n        const\
    \ int *mid_data = mid.data();\n        const auto *bit_data = bit.data();\n  \
    \      const int *pref_data = pref.data();\n        const U *zero_sum_data = zero_sum.data();\n\
    \        CountSum res{0, U()};\n        for (int d = 0, shift = lg - 1; d < lg;\
    \ ++d, --shift) {\n            int l1, r1;\n            rank1_pair(bit_data, pref_data,\
    \ l, r, l1, r1);\n            int l0 = l - l1, r0 = r - r1;\n            if ((xi\
    \ >> shift) & 1) {\n                res.count += r0 - l0;\n                res.sum\
    \ += zero_sum_data[r] - zero_sum_data[l];\n                l = mid_data[d] + l1;\n\
    \                r = mid_data[d] + r1;\n            }\n            else {\n  \
    \              l = l0;\n                r = r0;\n            }\n            bit_data\
    \ += blocks;\n            pref_data += blocks + 1;\n            zero_sum_data\
    \ += n + 1;\n        }\n        return res;\n    }\n\n    CountSum count_sum_less(int\
    \ l, int r, const T &x) const {\n        int xi = (int)(lower_bound(vals.begin(),\
    \ vals.end(), x) - vals.begin());\n        return count_sum_less_index(l, r, xi);\n\
    \    }\n\n    CountSum count_sum_less_equal(int l, int r, const T &x) const {\n\
    \        int xi = (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \        return count_sum_less_index(l, r, xi);\n    }\n\n    int count_less(int\
    \ l, int r, const T &x) const {\n        return count_sum_less(l, r, x).count;\n\
    \    }\n\n    int count_less_equal(int l, int r, const T &x) const {\n       \
    \ return count_sum_less_equal(l, r, x).count;\n    }\n\n    U sum_less(int l,\
    \ int r, const T &x) const {\n        return count_sum_less(l, r, x).sum;\n  \
    \  }\n\n    U sum_less_equal(int l, int r, const T &x) const {\n        return\
    \ count_sum_less_equal(l, r, x).sum;\n    }\n};\n\n/**\n * @brief \u91CD\u307F\
    \u4ED8\u304DWavelet Matrix(Weighted Wavelet Matrix)\n */\n"
  code: "template <class T, class U>\nstruct WeightedWaveletMatrix {\n    struct CountSum\
    \ {\n        int count;\n        U sum;\n    };\n\n    int n, lg, blocks;\n  \
    \  vector<int> mid;\n    vector<unsigned long long> bit;\n    vector<int> pref;\n\
    \    vector<U> zero_sum;\n    vector<U> base_sum;\n    vector<T> vals;\n\n   \
    \ WeightedWaveletMatrix() : n(0), lg(0), blocks(0) {}\n    WeightedWaveletMatrix(const\
    \ vector<T> &v, const vector<U> &w) { build(v, w); }\n\n    static inline void\
    \ rank1_pair(const unsigned long long *row, const int *row_pref, int l, int r,\
    \ int &l1, int &r1) {\n        int l_block = l >> 6;\n        l1 = row_pref[l_block];\n\
    \        int l_rem = l & 63;\n        if (l_rem) l1 += __builtin_popcountll(row[l_block]\
    \ & ((1ULL << l_rem) - 1));\n\n        int r_block = r >> 6;\n        r1 = row_pref[r_block];\n\
    \        int r_rem = r & 63;\n        if (r_rem) r1 += __builtin_popcountll(row[r_block]\
    \ & ((1ULL << r_rem) - 1));\n    }\n\n    template <class X>\n    static auto\
    \ encode_key(X x) -> typename make_unsigned<X>::type {\n        using Key = typename\
    \ make_unsigned<X>::type;\n        Key key = static_cast<Key>(x);\n        if\
    \ constexpr (is_signed<X>::value) key ^= (Key(1) << (sizeof(X) * 8 - 1));\n  \
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
    \ cur, const vector<U> &w) {\n        n = (int)cur.size();\n        base_sum.assign(n\
    \ + 1, U());\n        for (int i = 0; i < n; ++i) base_sum[i + 1] = base_sum[i]\
    \ + w[i];\n\n        if (n == 0) {\n            lg = 0;\n            blocks =\
    \ 0;\n            mid.clear();\n            bit.clear();\n            pref.clear();\n\
    \            zero_sum.clear();\n            return;\n        }\n\n        int\
    \ m = (int)vals.size();\n        lg = 0;\n        while ((1LL << lg) < m) ++lg;\n\
    \        if (lg == 0) lg = 1;\n        blocks = (n + 63) >> 6;\n        vector<U>\
    \ cur_w = w;\n\n        mid.assign(lg, 0);\n        bit.assign(lg * blocks, 0);\n\
    \        pref.assign(lg * (blocks + 1), 0);\n        zero_sum.assign(lg * (n +\
    \ 1), U());\n        vector<int> nxt(n);\n        vector<U> nxt_w(n);\n\n    \
    \    for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n            auto\
    \ *row = bit.data() + d * blocks;\n            auto *row_pref = pref.data() +\
    \ d * (blocks + 1);\n            auto *row_zero_sum = zero_sum.data() + d * (n\
    \ + 1);\n            int zero_cnt = 0;\n            for (int i = 0; i < n; ++i)\
    \ {\n                int x = cur[i];\n                int b = (x >> shift) & 1;\n\
    \                if (b) row[i >> 6] |= 1ULL << (i & 63);\n                else\
    \ ++zero_cnt;\n                row_zero_sum[i + 1] = row_zero_sum[i] + (b ? U()\
    \ : cur_w[i]);\n            }\n            mid[d] = zero_cnt;\n            for\
    \ (int i = 0; i < blocks; ++i) row_pref[i + 1] = row_pref[i] + __builtin_popcountll(row[i]);\n\
    \n            int zi = 0, oi = zero_cnt;\n            for (int i = 0; i < n; ++i)\
    \ {\n                int x = cur[i];\n                if ((x >> shift) & 1) {\n\
    \                    nxt[oi] = x;\n                    nxt_w[oi++] = cur_w[i];\n\
    \                }\n                else {\n                    nxt[zi] = x;\n\
    \                    nxt_w[zi++] = cur_w[i];\n                }\n            }\n\
    \            cur.swap(nxt);\n            cur_w.swap(nxt_w);\n        }\n    }\n\
    \n    void build(const vector<T> &v, const vector<U> &w) {\n        n = (int)v.size();\n\
    \        if (n == 0) {\n            lg = 0;\n            blocks = 0;\n       \
    \     vals.clear();\n            mid.clear();\n            bit.clear();\n    \
    \        pref.clear();\n            zero_sum.clear();\n            base_sum.assign(1,\
    \ U());\n            return;\n        }\n\n        vector<int> cur(n);\n     \
    \   compress_values(v, cur);\n        build_from_index_internal(move(cur), w);\n\
    \    }\n\n    void build_from_index(const vector<int> &idx, const vector<T> &sorted_vals,\
    \ const vector<U> &w) {\n        vals = sorted_vals;\n        build_from_index_internal(idx,\
    \ w);\n    }\n\n    CountSum count_sum_less_index(int l, int r, int xi) const\
    \ {\n        if (xi <= 0 || l >= r || n == 0) return {0, U()};\n        if (xi\
    \ >= (int)vals.size()) return {r - l, base_sum[r] - base_sum[l]};\n\n        const\
    \ int *mid_data = mid.data();\n        const auto *bit_data = bit.data();\n  \
    \      const int *pref_data = pref.data();\n        const U *zero_sum_data = zero_sum.data();\n\
    \        CountSum res{0, U()};\n        for (int d = 0, shift = lg - 1; d < lg;\
    \ ++d, --shift) {\n            int l1, r1;\n            rank1_pair(bit_data, pref_data,\
    \ l, r, l1, r1);\n            int l0 = l - l1, r0 = r - r1;\n            if ((xi\
    \ >> shift) & 1) {\n                res.count += r0 - l0;\n                res.sum\
    \ += zero_sum_data[r] - zero_sum_data[l];\n                l = mid_data[d] + l1;\n\
    \                r = mid_data[d] + r1;\n            }\n            else {\n  \
    \              l = l0;\n                r = r0;\n            }\n            bit_data\
    \ += blocks;\n            pref_data += blocks + 1;\n            zero_sum_data\
    \ += n + 1;\n        }\n        return res;\n    }\n\n    CountSum count_sum_less(int\
    \ l, int r, const T &x) const {\n        int xi = (int)(lower_bound(vals.begin(),\
    \ vals.end(), x) - vals.begin());\n        return count_sum_less_index(l, r, xi);\n\
    \    }\n\n    CountSum count_sum_less_equal(int l, int r, const T &x) const {\n\
    \        int xi = (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \        return count_sum_less_index(l, r, xi);\n    }\n\n    int count_less(int\
    \ l, int r, const T &x) const {\n        return count_sum_less(l, r, x).count;\n\
    \    }\n\n    int count_less_equal(int l, int r, const T &x) const {\n       \
    \ return count_sum_less_equal(l, r, x).count;\n    }\n\n    U sum_less(int l,\
    \ int r, const T &x) const {\n        return count_sum_less(l, r, x).sum;\n  \
    \  }\n\n    U sum_less_equal(int l, int r, const T &x) const {\n        return\
    \ count_sum_less_equal(l, r, x).sum;\n    }\n};\n\n/**\n * @brief \u91CD\u307F\
    \u4ED8\u304DWavelet Matrix(Weighted Wavelet Matrix)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/weighted_wavelet_matrix.cpp
  requiredBy: []
  timestamp: '2026-03-26 00:19:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_static_range_sum_with_upper_bound.test.cpp
date: 2026-03-26
documentation_of: datastructure/weighted_wavelet_matrix.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "\u91CD\u307F\u4ED8\u304DWavelet Matrix(Weighted Wavelet Matrix)"
---

## 説明
静的配列に対して、区間内の `x` 未満 / 以下の個数と重みの総和を扱う。

## できること
- `WeightedWaveletMatrix<T, U> wm(v, w)`
  値配列 `v` と重み配列 `w` から構築する
- `build_from_index(idx, sorted_vals, w)`
  圧縮済み index 列 `idx` と昇順の値列 `sorted_vals`、重み列 `w` から構築する
- `count_sum_less(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満の要素数と重み和を返す
- `count_sum_less_equal(l, r, x)`
  区間 $[l, r)$ のうち `x` 以下の要素数と重み和を返す
- `count_sum_less_index(l, r, xi)`
  区間 $[l, r)$ のうち圧縮 index `xi` 未満の要素数と重み和を返す
- `count_less(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満の個数を返す
- `count_less_equal(l, r, x)`
  区間 $[l, r)$ のうち `x` 以下の個数を返す
- `sum_less(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満の重み和を返す
- `sum_less_equal(l, r, x)`
  区間 $[l, r)$ のうち `x` 以下の重み和を返す

## 使い方
`WeightedWaveletMatrix<T, U> wm(v, w);` を作る。
圧縮済みなら `build_from_index(idx, sorted_vals, w);` でも作れる。
値で区間を絞り、その中にある要素数と重み和を同時に取りたいときに使う。

## 実装上の補足
- 値は内部で座標圧縮して扱う。
- 圧縮済みで使うときは `count_sum_less_index` を使うと query 側の二分探索を省ける。
- クエリはすべて静的配列前提。
- 各クエリは $O(\log \sigma)$、構築は $O(N \log \sigma)$。
