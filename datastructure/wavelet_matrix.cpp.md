---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_wavelet_matrix_top_k_freq.test.cpp
    title: test/yosupo_aplusb_wavelet_matrix_top_k_freq.test.cpp
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
  bundledCode: "#line 1 \"datastructure/wavelet_matrix.cpp\"\n#if defined(__GNUC__)\
    \ && defined(__x86_64__)\n#include <immintrin.h>\n#endif\n\ntemplate <class T>\n\
    struct WaveletMatrix {\n    int n, lg, blocks;\n    vector<int> mid;\n    vector<unsigned\
    \ long long> bit;\n    vector<int> pref;\n    vector<T> vals;\n\n    WaveletMatrix()\
    \ : n(0), lg(0), blocks(0) {}\n    explicit WaveletMatrix(const vector<T> &v)\
    \ { build(v); }\n\n    static inline void rank1_pair(const unsigned long long\
    \ *row, const int *row_pref, int l, int r, int &l1, int &r1) {\n        int l_block\
    \ = l >> 6;\n        l1 = row_pref[l_block];\n        int l_rem = l & 63;\n  \
    \      if (l_rem) l1 += __builtin_popcountll(row[l_block] & ((1ULL << l_rem) -\
    \ 1));\n\n        int r_block = r >> 6;\n        r1 = row_pref[r_block];\n   \
    \     int r_rem = r & 63;\n        if (r_rem) r1 += __builtin_popcountll(row[r_block]\
    \ & ((1ULL << r_rem) - 1));\n    }\n\n#if defined(__GNUC__) && defined(__x86_64__)\n\
    \    __attribute__((target(\"popcnt,bmi2\")))\n    static inline void rank1_pair_bmi2(const\
    \ unsigned long long *row, const int *row_pref, int l, int r,\n              \
    \                         int &l1, int &r1) {\n        int l_block = l >> 6;\n\
    \        l1 = row_pref[l_block] + __builtin_popcountll(__builtin_ia32_bzhi_di(row[l_block],\
    \ l & 63));\n\n        int r_block = r >> 6;\n        r1 = row_pref[r_block] +\
    \ __builtin_popcountll(__builtin_ia32_bzhi_di(row[r_block], r & 63));\n    }\n\
    #endif\n\n    static int build_bit_row(const int *cur, int n, int blocks, int\
    \ shift,\n                             unsigned long long *row, int *row_pref)\
    \ {\n        int one_cnt = 0;\n        for (int block = 0; block < blocks; ++block)\
    \ {\n            int begin = block << 6;\n            int end = min(begin + 64,\
    \ n);\n            unsigned long long word = 0;\n            for (int i = begin;\
    \ i < end; ++i) {\n                word |= (unsigned long long)((cur[i] >> shift)\
    \ & 1) << (i - begin);\n            }\n            row[block] = word;\n      \
    \      one_cnt += __builtin_popcountll(word);\n            row_pref[block + 1]\
    \ = one_cnt;\n        }\n        return one_cnt;\n    }\n\n#if defined(__GNUC__)\
    \ && defined(__x86_64__)\n    __attribute__((target(\"avx2,popcnt\")))\n    static\
    \ int build_bit_row_avx2(const int *cur, int n, int blocks, int shift,\n     \
    \                             unsigned long long *row, int *row_pref) {\n    \
    \    int one_cnt = 0;\n        __m128i shift_count = _mm_cvtsi32_si128(31 - shift);\n\
    \        for (int block = 0; block < blocks; ++block) {\n            int begin\
    \ = block << 6;\n            int end = min(begin + 64, n);\n            unsigned\
    \ long long word = 0;\n            int i = begin;\n            for (; i + 8 <=\
    \ end; i += 8) {\n                __m256i x = _mm256_loadu_si256((const __m256i\
    \ *)(cur + i));\n                __m256i shifted = _mm256_sll_epi32(x, shift_count);\n\
    \                unsigned int mask = _mm256_movemask_ps(_mm256_castsi256_ps(shifted));\n\
    \                word |= (unsigned long long)mask << (i - begin);\n          \
    \  }\n            for (; i < end; ++i) {\n                word |= (unsigned long\
    \ long)((cur[i] >> shift) & 1) << (i - begin);\n            }\n            row[block]\
    \ = word;\n            one_cnt += __builtin_popcountll(word);\n            row_pref[block\
    \ + 1] = one_cnt;\n        }\n        return one_cnt;\n    }\n\n    struct PartitionTable8\
    \ {\n        alignas(32) int perm[256][8];\n        alignas(32) int rotate[9][8];\n\
    \        alignas(32) int store[9][8];\n\n        PartitionTable8() {\n       \
    \     for (int mask = 0; mask < 256; ++mask) {\n                int pos = 0;\n\
    \                for (int i = 0; i < 8; ++i) {\n                    if (!((mask\
    \ >> i) & 1)) perm[mask][pos++] = i;\n                }\n                for (int\
    \ i = 0; i < 8; ++i) {\n                    if ((mask >> i) & 1) perm[mask][pos++]\
    \ = i;\n                }\n            }\n            for (int zero_count = 0;\
    \ zero_count <= 8; ++zero_count) {\n                for (int i = 0; i < 8; ++i)\
    \ {\n                    rotate[zero_count][i] = zero_count + i < 8 ? zero_count\
    \ + i : 0;\n                    store[zero_count][i] = i < zero_count ? -1 : 0;\n\
    \                }\n            }\n        }\n    };\n\n    __attribute__((target(\"\
    avx2,popcnt\")))\n    static void stable_partition_avx2(const int *cur, int n,\
    \ int shift, int zero_cnt,\n                                      const unsigned\
    \ long long *row, int *nxt) {\n        static const PartitionTable8 table;\n \
    \       int zi = 0, oi = zero_cnt;\n        int i = 0;\n        for (; i + 8 <=\
    \ n; i += 8) {\n            __m256i x = _mm256_loadu_si256((const __m256i *)(cur\
    \ + i));\n            unsigned int ones = (row[i >> 6] >> (i & 63)) & 0xffU;\n\
    \            int one_count = __builtin_popcount(ones);\n            int zero_count\
    \ = 8 - one_count;\n            __m256i perm = _mm256_load_si256((const __m256i\
    \ *)table.perm[ones]);\n            __m256i packed = _mm256_permutevar8x32_epi32(x,\
    \ perm);\n            __m256i one_perm = _mm256_load_si256((const __m256i *)table.rotate[zero_count]);\n\
    \            __m256i one_values = _mm256_permutevar8x32_epi32(packed, one_perm);\n\
    \            __m256i zero_store = _mm256_load_si256((const __m256i *)table.store[zero_count]);\n\
    \            __m256i one_store = _mm256_load_si256((const __m256i *)table.store[one_count]);\n\
    \            _mm256_maskstore_epi32(nxt + zi, zero_store, packed);\n         \
    \   _mm256_maskstore_epi32(nxt + oi, one_store, one_values);\n            zi +=\
    \ zero_count;\n            oi += one_count;\n        }\n        for (; i < n;\
    \ ++i) {\n            int x = cur[i];\n            int b = (x >> shift) & 1;\n\
    \            int dst = b ? oi : zi;\n            nxt[dst] = x;\n            zi\
    \ += b ^ 1;\n            oi += b;\n        }\n    }\n\n    __attribute__((target(\"\
    avx512f,popcnt\")))\n    static void stable_partition_avx512(const int *cur, int\
    \ n, int shift, int zero_cnt,\n                                        const unsigned\
    \ long long *row, int *nxt) {\n        int zi = 0, oi = zero_cnt;\n        int\
    \ i = 0;\n        for (; i + 16 <= n; i += 16) {\n            __m512i x = _mm512_loadu_si512((const\
    \ void *)(cur + i));\n            unsigned int ones = (row[i >> 6] >> (i & 63))\
    \ & 0xffffU;\n            __mmask16 one_mask = (__mmask16)ones;\n            __mmask16\
    \ zero_mask = (__mmask16)~one_mask;\n            _mm512_mask_compressstoreu_epi32(nxt\
    \ + zi, zero_mask, x);\n            _mm512_mask_compressstoreu_epi32(nxt + oi,\
    \ one_mask, x);\n            int one_count = __builtin_popcount(ones);\n     \
    \       zi += 16 - one_count;\n            oi += one_count;\n        }\n     \
    \   for (; i < n; ++i) {\n            int x = cur[i];\n            int b = (x\
    \ >> shift) & 1;\n            int dst = b ? oi : zi;\n            nxt[dst] = x;\n\
    \            zi += b ^ 1;\n            oi += b;\n        }\n    }\n\n#endif\n\n\
    \    template <class U>\n    static auto encode_key(U x) -> typename make_unsigned<U>::type\
    \ {\n        using Key = typename make_unsigned<U>::type;\n        Key key = static_cast<Key>(x);\n\
    \        if constexpr (is_signed<U>::value) key ^= (Key(1) << (sizeof(U) * 8 -\
    \ 1));\n        return key;\n    }\n\n    void compress_generic(const vector<T>\
    \ &v, vector<int> &cur) {\n        vector<pair<T, int>> ord(n);\n        for (int\
    \ i = 0; i < n; ++i) ord[i] = {v[i], i};\n        sort(ord.begin(), ord.end(),\
    \ [](const pair<T, int> &a, const pair<T, int> &b) {\n            return a.first\
    \ < b.first;\n        });\n        vals.clear();\n        vals.reserve(n);\n \
    \       for (int i = 0; i < n; ++i) {\n            if (vals.empty() || vals.back()\
    \ < ord[i].first || ord[i].first < vals.back()) {\n                vals.push_back(ord[i].first);\n\
    \            }\n            cur[ord[i].second] = (int)vals.size() - 1;\n     \
    \   }\n    }\n\n    void compress_integral(const vector<T> &v, vector<int> &cur)\
    \ {\n        using Key = typename make_unsigned<T>::type;\n        vector<Key>\
    \ keys(n);\n        vector<int> ord(n), buf(n);\n        Key min_key = encode_key(v[0]);\n\
    \        Key max_key = min_key;\n        for (int i = 0; i < n; ++i) {\n     \
    \       keys[i] = encode_key(v[i]);\n            ord[i] = i;\n            min_key\
    \ = min(min_key, keys[i]);\n            max_key = max(max_key, keys[i]);\n   \
    \     }\n\n        const int B = 16;\n        const int MASK = (1 << B) - 1;\n\
    \        const int bucket_count = 1 << B;\n        auto pass_count = [&](Key x)\
    \ {\n            int passes = 0;\n            while (x) {\n                ++passes;\n\
    \                x >>= B;\n            }\n            return passes;\n       \
    \ };\n        int passes = pass_count(min_key ^ max_key);\n        int normalized_passes\
    \ = pass_count(max_key - min_key);\n        if (normalized_passes < passes) {\n\
    \            for (int i = 0; i < n; ++i) keys[i] -= min_key;\n            passes\
    \ = normalized_passes;\n        }\n\n        vector<int> cnt(bucket_count);\n\
    \        for (int pass = 0; pass < passes; ++pass) {\n            fill(cnt.begin(),\
    \ cnt.end(), 0);\n            int shift = pass * B;\n            for (int i =\
    \ 0; i < n; ++i) ++cnt[(keys[ord[i]] >> shift) & MASK];\n            int sum =\
    \ 0;\n            for (int i = 0; i < bucket_count; ++i) {\n                int\
    \ count = cnt[i];\n                cnt[i] = sum;\n                sum += count;\n\
    \            }\n            for (int i = 0; i < n; ++i) {\n                int\
    \ id = ord[i];\n                buf[cnt[(keys[id] >> shift) & MASK]++] = id;\n\
    \            }\n            ord.swap(buf);\n        }\n\n        vals.clear();\n\
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
    \ 0);\n        bit.assign(lg * blocks + 1, 0);\n        pref.assign(lg * (blocks\
    \ + 1), 0);\n        vector<int> nxt(n);\n\n#if defined(__GNUC__) && defined(__x86_64__)\n\
    \        bool use_avx2 = __builtin_cpu_supports(\"avx2\") && __builtin_cpu_supports(\"\
    popcnt\");\n        bool use_avx512 = __builtin_cpu_supports(\"avx512f\") && __builtin_cpu_supports(\"\
    popcnt\");\n#endif\n\n        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift)\
    \ {\n            auto *row = bit.data() + d * blocks;\n            auto *row_pref\
    \ = pref.data() + d * (blocks + 1);\n            int one_cnt;\n#if defined(__GNUC__)\
    \ && defined(__x86_64__)\n            if (use_avx2) one_cnt = build_bit_row_avx2(cur.data(),\
    \ n, blocks, shift, row, row_pref);\n            else one_cnt = build_bit_row(cur.data(),\
    \ n, blocks, shift, row, row_pref);\n#else\n            one_cnt = build_bit_row(cur.data(),\
    \ n, blocks, shift, row, row_pref);\n#endif\n            int zero_cnt = n - one_cnt;\n\
    \            mid[d] = zero_cnt;\n\n#if defined(__GNUC__) && defined(__x86_64__)\n\
    \            if (use_avx512) stable_partition_avx512(cur.data(), n, shift, zero_cnt,\
    \ row, nxt.data());\n            else if (use_avx2) stable_partition_avx2(cur.data(),\
    \ n, shift, zero_cnt, row, nxt.data());\n            else\n#endif\n          \
    \  {\n                int zi = 0, oi = zero_cnt;\n                for (int i =\
    \ 0; i < n; ++i) {\n                    int x = cur[i];\n                    int\
    \ b = (x >> shift) & 1;\n                    int dst = b ? oi : zi;\n        \
    \            nxt[dst] = x;\n                    zi += b ^ 1;\n               \
    \     oi += b;\n                }\n            }\n            cur.swap(nxt);\n\
    \        }\n    }\n\n    void build(const vector<T> &v) {\n        n = (int)v.size();\n\
    \        if (n == 0) {\n            lg = 0;\n            blocks = 0;\n       \
    \     vals.clear();\n            mid.clear();\n            bit.clear();\n    \
    \        pref.clear();\n            return;\n        }\n\n        vector<int>\
    \ cur(n);\n        compress_values(v, cur);\n        build_from_index_internal(move(cur));\n\
    \    }\n\n    void build_from_index(const vector<int> &idx, const vector<T> &sorted_vals)\
    \ {\n        vals = sorted_vals;\n        build_from_index_internal(idx);\n  \
    \  }\n\nprivate:\n    int count_less_index_fallback(int l, int r, int xi) const\
    \ {\n        const int *mid_data = mid.data();\n        const auto *bit_data =\
    \ bit.data();\n        const int *pref_data = pref.data();\n        int res =\
    \ 0;\n        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n      \
    \      int l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n\
    \            int l0 = l - l1, r0 = r - r1;\n            if ((xi >> shift) & 1)\
    \ {\n                res += r0 - l0;\n                l = mid_data[d] + l1;\n\
    \                r = mid_data[d] + r1;\n            }\n            else {\n  \
    \              l = l0;\n                r = r0;\n            }\n            if\
    \ (l == r) break;\n            bit_data += blocks;\n            pref_data += blocks\
    \ + 1;\n        }\n        return res;\n    }\n\n#if defined(__GNUC__) && defined(__x86_64__)\n\
    \    __attribute__((target(\"popcnt,bmi2\")))\n    int count_less_index_bmi2(int\
    \ l, int r, int xi) const {\n        const int *mid_data = mid.data();\n     \
    \   const auto *bit_data = bit.data();\n        const int *pref_data = pref.data();\n\
    \        int res = 0;\n        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift)\
    \ {\n            int l1, r1;\n            rank1_pair_bmi2(bit_data, pref_data,\
    \ l, r, l1, r1);\n            int l0 = l - l1, r0 = r - r1;\n            if ((xi\
    \ >> shift) & 1) {\n                res += r0 - l0;\n                l = mid_data[d]\
    \ + l1;\n                r = mid_data[d] + r1;\n            }\n            else\
    \ {\n                l = l0;\n                r = r0;\n            }\n       \
    \     if (l == r) break;\n            bit_data += blocks;\n            pref_data\
    \ += blocks + 1;\n        }\n        return res;\n    }\n#endif\n\n    int count_equal_index_fallback(int\
    \ l, int r, int xi) const {\n        const int *mid_data = mid.data();\n     \
    \   const auto *bit_data = bit.data();\n        const int *pref_data = pref.data();\n\
    \        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n           \
    \ int l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n  \
    \          int l0 = l - l1, r0 = r - r1;\n            if ((xi >> shift) & 1) {\n\
    \                l = mid_data[d] + l1;\n                r = mid_data[d] + r1;\n\
    \            }\n            else {\n                l = l0;\n                r\
    \ = r0;\n            }\n            if (l == r) return 0;\n            bit_data\
    \ += blocks;\n            pref_data += blocks + 1;\n        }\n        return\
    \ r - l;\n    }\n\n#if defined(__GNUC__) && defined(__x86_64__)\n    __attribute__((target(\"\
    popcnt,bmi2\")))\n    int count_equal_index_bmi2(int l, int r, int xi) const {\n\
    \        const int *mid_data = mid.data();\n        const auto *bit_data = bit.data();\n\
    \        const int *pref_data = pref.data();\n        for (int d = 0, shift =\
    \ lg - 1; d < lg; ++d, --shift) {\n            int l1, r1;\n            rank1_pair_bmi2(bit_data,\
    \ pref_data, l, r, l1, r1);\n            int l0 = l - l1, r0 = r - r1;\n     \
    \       if ((xi >> shift) & 1) {\n                l = mid_data[d] + l1;\n    \
    \            r = mid_data[d] + r1;\n            }\n            else {\n      \
    \          l = l0;\n                r = r0;\n            }\n            if (l\
    \ == r) return 0;\n            bit_data += blocks;\n            pref_data += blocks\
    \ + 1;\n        }\n        return r - l;\n    }\n#endif\n\n    int kth_smallest_index_fallback(int\
    \ l, int r, int k) const {\n        const int *mid_data = mid.data();\n      \
    \  const auto *bit_data = bit.data();\n        const int *pref_data = pref.data();\n\
    \        int idx = 0;\n        for (int d = 0; d < lg; ++d) {\n            int\
    \ l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n      \
    \      int l0 = l - l1, r0 = r - r1;\n            int z = r0 - l0;\n         \
    \   idx <<= 1;\n            if (k < z) {\n                l = l0;\n          \
    \      r = r0;\n            }\n            else {\n                k -= z;\n \
    \               idx |= 1;\n                l = mid_data[d] + l1;\n           \
    \     r = mid_data[d] + r1;\n            }\n            bit_data += blocks;\n\
    \            pref_data += blocks + 1;\n        }\n        return idx;\n    }\n\
    \n#if defined(__GNUC__) && defined(__x86_64__)\n    __attribute__((target(\"popcnt,bmi2\"\
    )))\n    int kth_smallest_index_bmi2(int l, int r, int k) const {\n        const\
    \ int *mid_data = mid.data();\n        const auto *bit_data = bit.data();\n  \
    \      const int *pref_data = pref.data();\n        int idx = 0;\n        for\
    \ (int d = 0; d < lg; ++d) {\n            int l1, r1;\n            rank1_pair_bmi2(bit_data,\
    \ pref_data, l, r, l1, r1);\n            int l0 = l - l1, r0 = r - r1;\n     \
    \       int z = r0 - l0;\n            idx <<= 1;\n            if (k < z) {\n \
    \               l = l0;\n                r = r0;\n            }\n            else\
    \ {\n                k -= z;\n                idx |= 1;\n                l = mid_data[d]\
    \ + l1;\n                r = mid_data[d] + r1;\n            }\n            bit_data\
    \ += blocks;\n            pref_data += blocks + 1;\n        }\n        return\
    \ idx;\n    }\n#endif\n\n    template <bool Prev, bool UseBmi2>\n    __attribute__((always_inline))\n\
    \    bool neighbor_index_impl(int l, int r, int xi, int &res) const {\n      \
    \  int prefix = 0;\n        int candidate_l = 0, candidate_r = 0, candidate_d\
    \ = -1, candidate_idx = 0;\n        int d = 0;\n        for (; d < lg && l < r;\
    \ ++d) {\n            const auto *row = bit.data() + d * blocks;\n           \
    \ const int *row_pref = pref.data() + d * (blocks + 1);\n            int l1, r1;\n\
    #if defined(__GNUC__) && defined(__x86_64__)\n            if constexpr (UseBmi2)\
    \ rank1_pair_bmi2(row, row_pref, l, r, l1, r1);\n            else rank1_pair(row,\
    \ row_pref, l, r, l1, r1);\n#else\n            rank1_pair(row, row_pref, l, r,\
    \ l1, r1);\n#endif\n            int l0 = l - l1, r0 = r - r1;\n            int\
    \ bit_value = (xi >> (lg - d - 1)) & 1;\n            if constexpr (Prev) {\n \
    \               if (bit_value) {\n                    if (l0 < r0) {\n       \
    \                 candidate_l = l0;\n                        candidate_r = r0;\n\
    \                        candidate_d = d + 1;\n                        candidate_idx\
    \ = prefix << 1;\n                    }\n                    l = mid[d] + l1;\n\
    \                    r = mid[d] + r1;\n                    prefix = prefix <<\
    \ 1 | 1;\n                }\n                else {\n                    l = l0;\n\
    \                    r = r0;\n                    prefix <<= 1;\n            \
    \    }\n            }\n            else {\n                if (bit_value) {\n\
    \                    l = mid[d] + l1;\n                    r = mid[d] + r1;\n\
    \                    prefix = prefix << 1 | 1;\n                }\n          \
    \      else {\n                    if (l1 < r1) {\n                        candidate_l\
    \ = mid[d] + l1;\n                        candidate_r = mid[d] + r1;\n       \
    \                 candidate_d = d + 1;\n                        candidate_idx\
    \ = prefix << 1 | 1;\n                    }\n                    l = l0;\n   \
    \                 r = r0;\n                    prefix <<= 1;\n               \
    \ }\n            }\n        }\n\n        if constexpr (!Prev) {\n            if\
    \ (d == lg && l < r) {\n                res = prefix;\n                return\
    \ true;\n            }\n        }\n        if (candidate_d < 0) return false;\n\
    \n        l = candidate_l;\n        r = candidate_r;\n        prefix = candidate_idx;\n\
    \        for (d = candidate_d; d < lg; ++d) {\n            const auto *row = bit.data()\
    \ + d * blocks;\n            const int *row_pref = pref.data() + d * (blocks +\
    \ 1);\n            int l1, r1;\n#if defined(__GNUC__) && defined(__x86_64__)\n\
    \            if constexpr (UseBmi2) rank1_pair_bmi2(row, row_pref, l, r, l1, r1);\n\
    \            else rank1_pair(row, row_pref, l, r, l1, r1);\n#else\n          \
    \  rank1_pair(row, row_pref, l, r, l1, r1);\n#endif\n            int l0 = l -\
    \ l1, r0 = r - r1;\n            prefix <<= 1;\n            if constexpr (Prev)\
    \ {\n                if (l1 < r1) {\n                    prefix |= 1;\n      \
    \              l = mid[d] + l1;\n                    r = mid[d] + r1;\n      \
    \          }\n                else {\n                    l = l0;\n          \
    \          r = r0;\n                }\n            }\n            else {\n   \
    \             if (l0 < r0) {\n                    l = l0;\n                  \
    \  r = r0;\n                }\n                else {\n                    prefix\
    \ |= 1;\n                    l = mid[d] + l1;\n                    r = mid[d]\
    \ + r1;\n                }\n            }\n        }\n        res = prefix;\n\
    \        return true;\n    }\n\n    template <bool Prev>\n    bool neighbor_index_fallback(int\
    \ l, int r, int xi, int &res) const {\n        return neighbor_index_impl<Prev,\
    \ false>(l, r, xi, res);\n    }\n\n#if defined(__GNUC__) && defined(__x86_64__)\n\
    \    template <bool Prev>\n    __attribute__((target(\"popcnt,bmi2\")))\n    bool\
    \ neighbor_index_bmi2(int l, int r, int xi, int &res) const {\n        return\
    \ neighbor_index_impl<Prev, true>(l, r, xi, res);\n    }\n#endif\n\npublic:\n\
    \    int count_less_index(int l, int r, int xi) const {\n        if (xi <= 0 ||\
    \ l >= r || n == 0) return 0;\n        if (xi >= (int)vals.size()) return r -\
    \ l;\n#if defined(__GNUC__) && defined(__x86_64__)\n        if (__builtin_cpu_supports(\"\
    popcnt\") && __builtin_cpu_supports(\"bmi2\")) {\n            return count_less_index_bmi2(l,\
    \ r, xi);\n        }\n#endif\n        return count_less_index_fallback(l, r, xi);\n\
    \    }\n\n    int count_less(int l, int r, const T &x) const {\n        int xi\
    \ = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());\n        return\
    \ count_less_index(l, r, xi);\n    }\n\n    int count_equal_index(int l, int r,\
    \ int xi) const {\n        if (l >= r || n == 0 || xi < 0 || xi >= (int)vals.size())\
    \ return 0;\n#if defined(__GNUC__) && defined(__x86_64__)\n        if (__builtin_cpu_supports(\"\
    popcnt\") && __builtin_cpu_supports(\"bmi2\")) {\n            return count_equal_index_bmi2(l,\
    \ r, xi);\n        }\n#endif\n        return count_equal_index_fallback(l, r,\
    \ xi);\n    }\n\n    vector<pair<int, int>> top_k_freq_index(int l, int r, int\
    \ k) const {\n        if (k <= 0 || l >= r || n == 0) return {};\n\n#if defined(__GNUC__)\
    \ && defined(__x86_64__)\n        bool use_bmi2 = __builtin_cpu_supports(\"popcnt\"\
    ) && __builtin_cpu_supports(\"bmi2\");\n#endif\n\n        struct Node {\n    \
    \        int l, r, d, idx;\n            long long lower;\n        };\n       \
    \ struct Item {\n            int freq, idx;\n        };\n\n        auto item_better\
    \ = [](const Item &a, const Item &b) {\n            if (a.freq != b.freq) return\
    \ a.freq > b.freq;\n            return a.idx < b.idx;\n        };\n        auto\
    \ node_worse = [](const Node &a, const Node &b) {\n            int ca = a.r -\
    \ a.l;\n            int cb = b.r - b.l;\n            if (ca != cb) return ca <\
    \ cb;\n            if (a.lower != b.lower) return a.lower > b.lower;\n       \
    \     return a.d < b.d;\n        };\n\n        vector<Node> heap;\n        heap.push_back({l,\
    \ r, 0, 0, 0});\n        vector<Item> best;\n        best.reserve(min(k, r - l));\n\
    \n        while (!heap.empty()) {\n            if ((int)best.size() == k) {\n\
    \                const Node &cur = heap.front();\n                const Item &cut\
    \ = best.front();\n                int freq = cur.r - cur.l;\n               \
    \ if (freq < cut.freq) break;\n                if (freq == cut.freq && cur.lower\
    \ >= cut.idx) break;\n            }\n\n            pop_heap(heap.begin(), heap.end(),\
    \ node_worse);\n            Node cur = heap.back();\n            heap.pop_back();\n\
    \n            if (cur.d == lg) {\n                Item item{cur.r - cur.l, cur.idx};\n\
    \                if ((int)best.size() < k) {\n                    best.push_back(item);\n\
    \                    push_heap(best.begin(), best.end(), item_better);\n     \
    \           }\n                else if (item_better(item, best.front())) {\n \
    \                   pop_heap(best.begin(), best.end(), item_better);\n       \
    \             best.back() = item;\n                    push_heap(best.begin(),\
    \ best.end(), item_better);\n                }\n                continue;\n  \
    \          }\n\n            const auto *row = bit.data() + cur.d * blocks;\n \
    \           const int *row_pref = pref.data() + cur.d * (blocks + 1);\n      \
    \      int l1, r1;\n#if defined(__GNUC__) && defined(__x86_64__)\n           \
    \ if (use_bmi2) rank1_pair_bmi2(row, row_pref, cur.l, cur.r, l1, r1);\n      \
    \      else rank1_pair(row, row_pref, cur.l, cur.r, l1, r1);\n#else\n        \
    \    rank1_pair(row, row_pref, cur.l, cur.r, l1, r1);\n#endif\n            int\
    \ l0 = cur.l - l1, r0 = cur.r - r1;\n            int shift = lg - cur.d - 1;\n\
    \            if (l0 < r0) {\n                heap.push_back({l0, r0, cur.d + 1,\
    \ cur.idx << 1, cur.lower});\n                push_heap(heap.begin(), heap.end(),\
    \ node_worse);\n            }\n            if (l1 < r1) {\n                heap.push_back({\n\
    \                    mid[cur.d] + l1,\n                    mid[cur.d] + r1,\n\
    \                    cur.d + 1,\n                    cur.idx << 1 | 1,\n     \
    \               cur.lower + (1LL << shift)\n                });\n            \
    \    push_heap(heap.begin(), heap.end(), node_worse);\n            }\n       \
    \ }\n\n        sort(best.begin(), best.end(), item_better);\n        vector<pair<int,\
    \ int>> res;\n        res.reserve(best.size());\n        for (const auto &item\
    \ : best) res.push_back({item.freq, item.idx});\n        return res;\n    }\n\n\
    \    vector<pair<int, T>> top_k_freq(int l, int r, int k) const {\n        auto\
    \ idx_res = top_k_freq_index(l, r, k);\n        vector<pair<int, T>> res;\n  \
    \      res.reserve(idx_res.size());\n        for (const auto &p : idx_res) res.push_back({p.first,\
    \ vals[p.second]});\n        return res;\n    }\n\n    int range_freq(int l, int\
    \ r, const T &lower, const T &upper) const {\n        if (lower >= upper || l\
    \ >= r) return 0;\n        return count_less(l, r, upper) - count_less(l, r, lower);\n\
    \    }\n\n    int freq(int l, int r, const T &x) const {\n        int xi = (int)(lower_bound(vals.begin(),\
    \ vals.end(), x) - vals.begin());\n        if (xi == (int)vals.size() || vals[xi]\
    \ != x) return 0;\n        return count_equal_index(l, r, xi);\n    }\n\n    T\
    \ kth_smallest(int l, int r, int k) const {\n#if defined(__GNUC__) && defined(__x86_64__)\n\
    \        if (__builtin_cpu_supports(\"popcnt\") && __builtin_cpu_supports(\"bmi2\"\
    )) {\n            return vals[kth_smallest_index_bmi2(l, r, k)];\n        }\n\
    #endif\n        return vals[kth_smallest_index_fallback(l, r, k)];\n    }\n\n\
    \    T kth_largest(int l, int r, int k) const {\n        return kth_smallest(l,\
    \ r, r - l - 1 - k);\n    }\n\n    bool prev_value(int l, int r, const T &upper,\
    \ T &res) const {\n        if (l >= r || n == 0) return false;\n        int xi\
    \ = (int)(lower_bound(vals.begin(), vals.end(), upper) - vals.begin());\n    \
    \    if (xi <= 0) return false;\n        if (xi >= (int)vals.size()) {\n     \
    \       res = kth_largest(l, r, 0);\n            return true;\n        }\n#if\
    \ defined(__GNUC__) && defined(__x86_64__)\n        if (__builtin_cpu_supports(\"\
    popcnt\") && __builtin_cpu_supports(\"bmi2\")) {\n            int idx;\n     \
    \       if (!neighbor_index_bmi2<true>(l, r, xi, idx)) return false;\n       \
    \     res = vals[idx];\n            return true;\n        }\n#endif\n        int\
    \ idx;\n        if (!neighbor_index_fallback<true>(l, r, xi, idx)) return false;\n\
    \        res = vals[idx];\n        return true;\n    }\n\n    bool next_value(int\
    \ l, int r, const T &lower, T &res) const {\n        if (l >= r || n == 0) return\
    \ false;\n        int xi = (int)(lower_bound(vals.begin(), vals.end(), lower)\
    \ - vals.begin());\n        if (xi >= (int)vals.size()) return false;\n#if defined(__GNUC__)\
    \ && defined(__x86_64__)\n        if (__builtin_cpu_supports(\"popcnt\") && __builtin_cpu_supports(\"\
    bmi2\")) {\n            int idx;\n            if (!neighbor_index_bmi2<false>(l,\
    \ r, xi, idx)) return false;\n            res = vals[idx];\n            return\
    \ true;\n        }\n#endif\n        int idx;\n        if (!neighbor_index_fallback<false>(l,\
    \ r, xi, idx)) return false;\n        res = vals[idx];\n        return true;\n\
    \    }\n};\n\n/**\n * @brief Wavelet Matrix\n */\n"
  code: "#if defined(__GNUC__) && defined(__x86_64__)\n#include <immintrin.h>\n#endif\n\
    \ntemplate <class T>\nstruct WaveletMatrix {\n    int n, lg, blocks;\n    vector<int>\
    \ mid;\n    vector<unsigned long long> bit;\n    vector<int> pref;\n    vector<T>\
    \ vals;\n\n    WaveletMatrix() : n(0), lg(0), blocks(0) {}\n    explicit WaveletMatrix(const\
    \ vector<T> &v) { build(v); }\n\n    static inline void rank1_pair(const unsigned\
    \ long long *row, const int *row_pref, int l, int r, int &l1, int &r1) {\n   \
    \     int l_block = l >> 6;\n        l1 = row_pref[l_block];\n        int l_rem\
    \ = l & 63;\n        if (l_rem) l1 += __builtin_popcountll(row[l_block] & ((1ULL\
    \ << l_rem) - 1));\n\n        int r_block = r >> 6;\n        r1 = row_pref[r_block];\n\
    \        int r_rem = r & 63;\n        if (r_rem) r1 += __builtin_popcountll(row[r_block]\
    \ & ((1ULL << r_rem) - 1));\n    }\n\n#if defined(__GNUC__) && defined(__x86_64__)\n\
    \    __attribute__((target(\"popcnt,bmi2\")))\n    static inline void rank1_pair_bmi2(const\
    \ unsigned long long *row, const int *row_pref, int l, int r,\n              \
    \                         int &l1, int &r1) {\n        int l_block = l >> 6;\n\
    \        l1 = row_pref[l_block] + __builtin_popcountll(__builtin_ia32_bzhi_di(row[l_block],\
    \ l & 63));\n\n        int r_block = r >> 6;\n        r1 = row_pref[r_block] +\
    \ __builtin_popcountll(__builtin_ia32_bzhi_di(row[r_block], r & 63));\n    }\n\
    #endif\n\n    static int build_bit_row(const int *cur, int n, int blocks, int\
    \ shift,\n                             unsigned long long *row, int *row_pref)\
    \ {\n        int one_cnt = 0;\n        for (int block = 0; block < blocks; ++block)\
    \ {\n            int begin = block << 6;\n            int end = min(begin + 64,\
    \ n);\n            unsigned long long word = 0;\n            for (int i = begin;\
    \ i < end; ++i) {\n                word |= (unsigned long long)((cur[i] >> shift)\
    \ & 1) << (i - begin);\n            }\n            row[block] = word;\n      \
    \      one_cnt += __builtin_popcountll(word);\n            row_pref[block + 1]\
    \ = one_cnt;\n        }\n        return one_cnt;\n    }\n\n#if defined(__GNUC__)\
    \ && defined(__x86_64__)\n    __attribute__((target(\"avx2,popcnt\")))\n    static\
    \ int build_bit_row_avx2(const int *cur, int n, int blocks, int shift,\n     \
    \                             unsigned long long *row, int *row_pref) {\n    \
    \    int one_cnt = 0;\n        __m128i shift_count = _mm_cvtsi32_si128(31 - shift);\n\
    \        for (int block = 0; block < blocks; ++block) {\n            int begin\
    \ = block << 6;\n            int end = min(begin + 64, n);\n            unsigned\
    \ long long word = 0;\n            int i = begin;\n            for (; i + 8 <=\
    \ end; i += 8) {\n                __m256i x = _mm256_loadu_si256((const __m256i\
    \ *)(cur + i));\n                __m256i shifted = _mm256_sll_epi32(x, shift_count);\n\
    \                unsigned int mask = _mm256_movemask_ps(_mm256_castsi256_ps(shifted));\n\
    \                word |= (unsigned long long)mask << (i - begin);\n          \
    \  }\n            for (; i < end; ++i) {\n                word |= (unsigned long\
    \ long)((cur[i] >> shift) & 1) << (i - begin);\n            }\n            row[block]\
    \ = word;\n            one_cnt += __builtin_popcountll(word);\n            row_pref[block\
    \ + 1] = one_cnt;\n        }\n        return one_cnt;\n    }\n\n    struct PartitionTable8\
    \ {\n        alignas(32) int perm[256][8];\n        alignas(32) int rotate[9][8];\n\
    \        alignas(32) int store[9][8];\n\n        PartitionTable8() {\n       \
    \     for (int mask = 0; mask < 256; ++mask) {\n                int pos = 0;\n\
    \                for (int i = 0; i < 8; ++i) {\n                    if (!((mask\
    \ >> i) & 1)) perm[mask][pos++] = i;\n                }\n                for (int\
    \ i = 0; i < 8; ++i) {\n                    if ((mask >> i) & 1) perm[mask][pos++]\
    \ = i;\n                }\n            }\n            for (int zero_count = 0;\
    \ zero_count <= 8; ++zero_count) {\n                for (int i = 0; i < 8; ++i)\
    \ {\n                    rotate[zero_count][i] = zero_count + i < 8 ? zero_count\
    \ + i : 0;\n                    store[zero_count][i] = i < zero_count ? -1 : 0;\n\
    \                }\n            }\n        }\n    };\n\n    __attribute__((target(\"\
    avx2,popcnt\")))\n    static void stable_partition_avx2(const int *cur, int n,\
    \ int shift, int zero_cnt,\n                                      const unsigned\
    \ long long *row, int *nxt) {\n        static const PartitionTable8 table;\n \
    \       int zi = 0, oi = zero_cnt;\n        int i = 0;\n        for (; i + 8 <=\
    \ n; i += 8) {\n            __m256i x = _mm256_loadu_si256((const __m256i *)(cur\
    \ + i));\n            unsigned int ones = (row[i >> 6] >> (i & 63)) & 0xffU;\n\
    \            int one_count = __builtin_popcount(ones);\n            int zero_count\
    \ = 8 - one_count;\n            __m256i perm = _mm256_load_si256((const __m256i\
    \ *)table.perm[ones]);\n            __m256i packed = _mm256_permutevar8x32_epi32(x,\
    \ perm);\n            __m256i one_perm = _mm256_load_si256((const __m256i *)table.rotate[zero_count]);\n\
    \            __m256i one_values = _mm256_permutevar8x32_epi32(packed, one_perm);\n\
    \            __m256i zero_store = _mm256_load_si256((const __m256i *)table.store[zero_count]);\n\
    \            __m256i one_store = _mm256_load_si256((const __m256i *)table.store[one_count]);\n\
    \            _mm256_maskstore_epi32(nxt + zi, zero_store, packed);\n         \
    \   _mm256_maskstore_epi32(nxt + oi, one_store, one_values);\n            zi +=\
    \ zero_count;\n            oi += one_count;\n        }\n        for (; i < n;\
    \ ++i) {\n            int x = cur[i];\n            int b = (x >> shift) & 1;\n\
    \            int dst = b ? oi : zi;\n            nxt[dst] = x;\n            zi\
    \ += b ^ 1;\n            oi += b;\n        }\n    }\n\n    __attribute__((target(\"\
    avx512f,popcnt\")))\n    static void stable_partition_avx512(const int *cur, int\
    \ n, int shift, int zero_cnt,\n                                        const unsigned\
    \ long long *row, int *nxt) {\n        int zi = 0, oi = zero_cnt;\n        int\
    \ i = 0;\n        for (; i + 16 <= n; i += 16) {\n            __m512i x = _mm512_loadu_si512((const\
    \ void *)(cur + i));\n            unsigned int ones = (row[i >> 6] >> (i & 63))\
    \ & 0xffffU;\n            __mmask16 one_mask = (__mmask16)ones;\n            __mmask16\
    \ zero_mask = (__mmask16)~one_mask;\n            _mm512_mask_compressstoreu_epi32(nxt\
    \ + zi, zero_mask, x);\n            _mm512_mask_compressstoreu_epi32(nxt + oi,\
    \ one_mask, x);\n            int one_count = __builtin_popcount(ones);\n     \
    \       zi += 16 - one_count;\n            oi += one_count;\n        }\n     \
    \   for (; i < n; ++i) {\n            int x = cur[i];\n            int b = (x\
    \ >> shift) & 1;\n            int dst = b ? oi : zi;\n            nxt[dst] = x;\n\
    \            zi += b ^ 1;\n            oi += b;\n        }\n    }\n\n#endif\n\n\
    \    template <class U>\n    static auto encode_key(U x) -> typename make_unsigned<U>::type\
    \ {\n        using Key = typename make_unsigned<U>::type;\n        Key key = static_cast<Key>(x);\n\
    \        if constexpr (is_signed<U>::value) key ^= (Key(1) << (sizeof(U) * 8 -\
    \ 1));\n        return key;\n    }\n\n    void compress_generic(const vector<T>\
    \ &v, vector<int> &cur) {\n        vector<pair<T, int>> ord(n);\n        for (int\
    \ i = 0; i < n; ++i) ord[i] = {v[i], i};\n        sort(ord.begin(), ord.end(),\
    \ [](const pair<T, int> &a, const pair<T, int> &b) {\n            return a.first\
    \ < b.first;\n        });\n        vals.clear();\n        vals.reserve(n);\n \
    \       for (int i = 0; i < n; ++i) {\n            if (vals.empty() || vals.back()\
    \ < ord[i].first || ord[i].first < vals.back()) {\n                vals.push_back(ord[i].first);\n\
    \            }\n            cur[ord[i].second] = (int)vals.size() - 1;\n     \
    \   }\n    }\n\n    void compress_integral(const vector<T> &v, vector<int> &cur)\
    \ {\n        using Key = typename make_unsigned<T>::type;\n        vector<Key>\
    \ keys(n);\n        vector<int> ord(n), buf(n);\n        Key min_key = encode_key(v[0]);\n\
    \        Key max_key = min_key;\n        for (int i = 0; i < n; ++i) {\n     \
    \       keys[i] = encode_key(v[i]);\n            ord[i] = i;\n            min_key\
    \ = min(min_key, keys[i]);\n            max_key = max(max_key, keys[i]);\n   \
    \     }\n\n        const int B = 16;\n        const int MASK = (1 << B) - 1;\n\
    \        const int bucket_count = 1 << B;\n        auto pass_count = [&](Key x)\
    \ {\n            int passes = 0;\n            while (x) {\n                ++passes;\n\
    \                x >>= B;\n            }\n            return passes;\n       \
    \ };\n        int passes = pass_count(min_key ^ max_key);\n        int normalized_passes\
    \ = pass_count(max_key - min_key);\n        if (normalized_passes < passes) {\n\
    \            for (int i = 0; i < n; ++i) keys[i] -= min_key;\n            passes\
    \ = normalized_passes;\n        }\n\n        vector<int> cnt(bucket_count);\n\
    \        for (int pass = 0; pass < passes; ++pass) {\n            fill(cnt.begin(),\
    \ cnt.end(), 0);\n            int shift = pass * B;\n            for (int i =\
    \ 0; i < n; ++i) ++cnt[(keys[ord[i]] >> shift) & MASK];\n            int sum =\
    \ 0;\n            for (int i = 0; i < bucket_count; ++i) {\n                int\
    \ count = cnt[i];\n                cnt[i] = sum;\n                sum += count;\n\
    \            }\n            for (int i = 0; i < n; ++i) {\n                int\
    \ id = ord[i];\n                buf[cnt[(keys[id] >> shift) & MASK]++] = id;\n\
    \            }\n            ord.swap(buf);\n        }\n\n        vals.clear();\n\
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
    \ 0);\n        bit.assign(lg * blocks + 1, 0);\n        pref.assign(lg * (blocks\
    \ + 1), 0);\n        vector<int> nxt(n);\n\n#if defined(__GNUC__) && defined(__x86_64__)\n\
    \        bool use_avx2 = __builtin_cpu_supports(\"avx2\") && __builtin_cpu_supports(\"\
    popcnt\");\n        bool use_avx512 = __builtin_cpu_supports(\"avx512f\") && __builtin_cpu_supports(\"\
    popcnt\");\n#endif\n\n        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift)\
    \ {\n            auto *row = bit.data() + d * blocks;\n            auto *row_pref\
    \ = pref.data() + d * (blocks + 1);\n            int one_cnt;\n#if defined(__GNUC__)\
    \ && defined(__x86_64__)\n            if (use_avx2) one_cnt = build_bit_row_avx2(cur.data(),\
    \ n, blocks, shift, row, row_pref);\n            else one_cnt = build_bit_row(cur.data(),\
    \ n, blocks, shift, row, row_pref);\n#else\n            one_cnt = build_bit_row(cur.data(),\
    \ n, blocks, shift, row, row_pref);\n#endif\n            int zero_cnt = n - one_cnt;\n\
    \            mid[d] = zero_cnt;\n\n#if defined(__GNUC__) && defined(__x86_64__)\n\
    \            if (use_avx512) stable_partition_avx512(cur.data(), n, shift, zero_cnt,\
    \ row, nxt.data());\n            else if (use_avx2) stable_partition_avx2(cur.data(),\
    \ n, shift, zero_cnt, row, nxt.data());\n            else\n#endif\n          \
    \  {\n                int zi = 0, oi = zero_cnt;\n                for (int i =\
    \ 0; i < n; ++i) {\n                    int x = cur[i];\n                    int\
    \ b = (x >> shift) & 1;\n                    int dst = b ? oi : zi;\n        \
    \            nxt[dst] = x;\n                    zi += b ^ 1;\n               \
    \     oi += b;\n                }\n            }\n            cur.swap(nxt);\n\
    \        }\n    }\n\n    void build(const vector<T> &v) {\n        n = (int)v.size();\n\
    \        if (n == 0) {\n            lg = 0;\n            blocks = 0;\n       \
    \     vals.clear();\n            mid.clear();\n            bit.clear();\n    \
    \        pref.clear();\n            return;\n        }\n\n        vector<int>\
    \ cur(n);\n        compress_values(v, cur);\n        build_from_index_internal(move(cur));\n\
    \    }\n\n    void build_from_index(const vector<int> &idx, const vector<T> &sorted_vals)\
    \ {\n        vals = sorted_vals;\n        build_from_index_internal(idx);\n  \
    \  }\n\nprivate:\n    int count_less_index_fallback(int l, int r, int xi) const\
    \ {\n        const int *mid_data = mid.data();\n        const auto *bit_data =\
    \ bit.data();\n        const int *pref_data = pref.data();\n        int res =\
    \ 0;\n        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n      \
    \      int l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n\
    \            int l0 = l - l1, r0 = r - r1;\n            if ((xi >> shift) & 1)\
    \ {\n                res += r0 - l0;\n                l = mid_data[d] + l1;\n\
    \                r = mid_data[d] + r1;\n            }\n            else {\n  \
    \              l = l0;\n                r = r0;\n            }\n            if\
    \ (l == r) break;\n            bit_data += blocks;\n            pref_data += blocks\
    \ + 1;\n        }\n        return res;\n    }\n\n#if defined(__GNUC__) && defined(__x86_64__)\n\
    \    __attribute__((target(\"popcnt,bmi2\")))\n    int count_less_index_bmi2(int\
    \ l, int r, int xi) const {\n        const int *mid_data = mid.data();\n     \
    \   const auto *bit_data = bit.data();\n        const int *pref_data = pref.data();\n\
    \        int res = 0;\n        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift)\
    \ {\n            int l1, r1;\n            rank1_pair_bmi2(bit_data, pref_data,\
    \ l, r, l1, r1);\n            int l0 = l - l1, r0 = r - r1;\n            if ((xi\
    \ >> shift) & 1) {\n                res += r0 - l0;\n                l = mid_data[d]\
    \ + l1;\n                r = mid_data[d] + r1;\n            }\n            else\
    \ {\n                l = l0;\n                r = r0;\n            }\n       \
    \     if (l == r) break;\n            bit_data += blocks;\n            pref_data\
    \ += blocks + 1;\n        }\n        return res;\n    }\n#endif\n\n    int count_equal_index_fallback(int\
    \ l, int r, int xi) const {\n        const int *mid_data = mid.data();\n     \
    \   const auto *bit_data = bit.data();\n        const int *pref_data = pref.data();\n\
    \        for (int d = 0, shift = lg - 1; d < lg; ++d, --shift) {\n           \
    \ int l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n  \
    \          int l0 = l - l1, r0 = r - r1;\n            if ((xi >> shift) & 1) {\n\
    \                l = mid_data[d] + l1;\n                r = mid_data[d] + r1;\n\
    \            }\n            else {\n                l = l0;\n                r\
    \ = r0;\n            }\n            if (l == r) return 0;\n            bit_data\
    \ += blocks;\n            pref_data += blocks + 1;\n        }\n        return\
    \ r - l;\n    }\n\n#if defined(__GNUC__) && defined(__x86_64__)\n    __attribute__((target(\"\
    popcnt,bmi2\")))\n    int count_equal_index_bmi2(int l, int r, int xi) const {\n\
    \        const int *mid_data = mid.data();\n        const auto *bit_data = bit.data();\n\
    \        const int *pref_data = pref.data();\n        for (int d = 0, shift =\
    \ lg - 1; d < lg; ++d, --shift) {\n            int l1, r1;\n            rank1_pair_bmi2(bit_data,\
    \ pref_data, l, r, l1, r1);\n            int l0 = l - l1, r0 = r - r1;\n     \
    \       if ((xi >> shift) & 1) {\n                l = mid_data[d] + l1;\n    \
    \            r = mid_data[d] + r1;\n            }\n            else {\n      \
    \          l = l0;\n                r = r0;\n            }\n            if (l\
    \ == r) return 0;\n            bit_data += blocks;\n            pref_data += blocks\
    \ + 1;\n        }\n        return r - l;\n    }\n#endif\n\n    int kth_smallest_index_fallback(int\
    \ l, int r, int k) const {\n        const int *mid_data = mid.data();\n      \
    \  const auto *bit_data = bit.data();\n        const int *pref_data = pref.data();\n\
    \        int idx = 0;\n        for (int d = 0; d < lg; ++d) {\n            int\
    \ l1, r1;\n            rank1_pair(bit_data, pref_data, l, r, l1, r1);\n      \
    \      int l0 = l - l1, r0 = r - r1;\n            int z = r0 - l0;\n         \
    \   idx <<= 1;\n            if (k < z) {\n                l = l0;\n          \
    \      r = r0;\n            }\n            else {\n                k -= z;\n \
    \               idx |= 1;\n                l = mid_data[d] + l1;\n           \
    \     r = mid_data[d] + r1;\n            }\n            bit_data += blocks;\n\
    \            pref_data += blocks + 1;\n        }\n        return idx;\n    }\n\
    \n#if defined(__GNUC__) && defined(__x86_64__)\n    __attribute__((target(\"popcnt,bmi2\"\
    )))\n    int kth_smallest_index_bmi2(int l, int r, int k) const {\n        const\
    \ int *mid_data = mid.data();\n        const auto *bit_data = bit.data();\n  \
    \      const int *pref_data = pref.data();\n        int idx = 0;\n        for\
    \ (int d = 0; d < lg; ++d) {\n            int l1, r1;\n            rank1_pair_bmi2(bit_data,\
    \ pref_data, l, r, l1, r1);\n            int l0 = l - l1, r0 = r - r1;\n     \
    \       int z = r0 - l0;\n            idx <<= 1;\n            if (k < z) {\n \
    \               l = l0;\n                r = r0;\n            }\n            else\
    \ {\n                k -= z;\n                idx |= 1;\n                l = mid_data[d]\
    \ + l1;\n                r = mid_data[d] + r1;\n            }\n            bit_data\
    \ += blocks;\n            pref_data += blocks + 1;\n        }\n        return\
    \ idx;\n    }\n#endif\n\n    template <bool Prev, bool UseBmi2>\n    __attribute__((always_inline))\n\
    \    bool neighbor_index_impl(int l, int r, int xi, int &res) const {\n      \
    \  int prefix = 0;\n        int candidate_l = 0, candidate_r = 0, candidate_d\
    \ = -1, candidate_idx = 0;\n        int d = 0;\n        for (; d < lg && l < r;\
    \ ++d) {\n            const auto *row = bit.data() + d * blocks;\n           \
    \ const int *row_pref = pref.data() + d * (blocks + 1);\n            int l1, r1;\n\
    #if defined(__GNUC__) && defined(__x86_64__)\n            if constexpr (UseBmi2)\
    \ rank1_pair_bmi2(row, row_pref, l, r, l1, r1);\n            else rank1_pair(row,\
    \ row_pref, l, r, l1, r1);\n#else\n            rank1_pair(row, row_pref, l, r,\
    \ l1, r1);\n#endif\n            int l0 = l - l1, r0 = r - r1;\n            int\
    \ bit_value = (xi >> (lg - d - 1)) & 1;\n            if constexpr (Prev) {\n \
    \               if (bit_value) {\n                    if (l0 < r0) {\n       \
    \                 candidate_l = l0;\n                        candidate_r = r0;\n\
    \                        candidate_d = d + 1;\n                        candidate_idx\
    \ = prefix << 1;\n                    }\n                    l = mid[d] + l1;\n\
    \                    r = mid[d] + r1;\n                    prefix = prefix <<\
    \ 1 | 1;\n                }\n                else {\n                    l = l0;\n\
    \                    r = r0;\n                    prefix <<= 1;\n            \
    \    }\n            }\n            else {\n                if (bit_value) {\n\
    \                    l = mid[d] + l1;\n                    r = mid[d] + r1;\n\
    \                    prefix = prefix << 1 | 1;\n                }\n          \
    \      else {\n                    if (l1 < r1) {\n                        candidate_l\
    \ = mid[d] + l1;\n                        candidate_r = mid[d] + r1;\n       \
    \                 candidate_d = d + 1;\n                        candidate_idx\
    \ = prefix << 1 | 1;\n                    }\n                    l = l0;\n   \
    \                 r = r0;\n                    prefix <<= 1;\n               \
    \ }\n            }\n        }\n\n        if constexpr (!Prev) {\n            if\
    \ (d == lg && l < r) {\n                res = prefix;\n                return\
    \ true;\n            }\n        }\n        if (candidate_d < 0) return false;\n\
    \n        l = candidate_l;\n        r = candidate_r;\n        prefix = candidate_idx;\n\
    \        for (d = candidate_d; d < lg; ++d) {\n            const auto *row = bit.data()\
    \ + d * blocks;\n            const int *row_pref = pref.data() + d * (blocks +\
    \ 1);\n            int l1, r1;\n#if defined(__GNUC__) && defined(__x86_64__)\n\
    \            if constexpr (UseBmi2) rank1_pair_bmi2(row, row_pref, l, r, l1, r1);\n\
    \            else rank1_pair(row, row_pref, l, r, l1, r1);\n#else\n          \
    \  rank1_pair(row, row_pref, l, r, l1, r1);\n#endif\n            int l0 = l -\
    \ l1, r0 = r - r1;\n            prefix <<= 1;\n            if constexpr (Prev)\
    \ {\n                if (l1 < r1) {\n                    prefix |= 1;\n      \
    \              l = mid[d] + l1;\n                    r = mid[d] + r1;\n      \
    \          }\n                else {\n                    l = l0;\n          \
    \          r = r0;\n                }\n            }\n            else {\n   \
    \             if (l0 < r0) {\n                    l = l0;\n                  \
    \  r = r0;\n                }\n                else {\n                    prefix\
    \ |= 1;\n                    l = mid[d] + l1;\n                    r = mid[d]\
    \ + r1;\n                }\n            }\n        }\n        res = prefix;\n\
    \        return true;\n    }\n\n    template <bool Prev>\n    bool neighbor_index_fallback(int\
    \ l, int r, int xi, int &res) const {\n        return neighbor_index_impl<Prev,\
    \ false>(l, r, xi, res);\n    }\n\n#if defined(__GNUC__) && defined(__x86_64__)\n\
    \    template <bool Prev>\n    __attribute__((target(\"popcnt,bmi2\")))\n    bool\
    \ neighbor_index_bmi2(int l, int r, int xi, int &res) const {\n        return\
    \ neighbor_index_impl<Prev, true>(l, r, xi, res);\n    }\n#endif\n\npublic:\n\
    \    int count_less_index(int l, int r, int xi) const {\n        if (xi <= 0 ||\
    \ l >= r || n == 0) return 0;\n        if (xi >= (int)vals.size()) return r -\
    \ l;\n#if defined(__GNUC__) && defined(__x86_64__)\n        if (__builtin_cpu_supports(\"\
    popcnt\") && __builtin_cpu_supports(\"bmi2\")) {\n            return count_less_index_bmi2(l,\
    \ r, xi);\n        }\n#endif\n        return count_less_index_fallback(l, r, xi);\n\
    \    }\n\n    int count_less(int l, int r, const T &x) const {\n        int xi\
    \ = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());\n        return\
    \ count_less_index(l, r, xi);\n    }\n\n    int count_equal_index(int l, int r,\
    \ int xi) const {\n        if (l >= r || n == 0 || xi < 0 || xi >= (int)vals.size())\
    \ return 0;\n#if defined(__GNUC__) && defined(__x86_64__)\n        if (__builtin_cpu_supports(\"\
    popcnt\") && __builtin_cpu_supports(\"bmi2\")) {\n            return count_equal_index_bmi2(l,\
    \ r, xi);\n        }\n#endif\n        return count_equal_index_fallback(l, r,\
    \ xi);\n    }\n\n    vector<pair<int, int>> top_k_freq_index(int l, int r, int\
    \ k) const {\n        if (k <= 0 || l >= r || n == 0) return {};\n\n#if defined(__GNUC__)\
    \ && defined(__x86_64__)\n        bool use_bmi2 = __builtin_cpu_supports(\"popcnt\"\
    ) && __builtin_cpu_supports(\"bmi2\");\n#endif\n\n        struct Node {\n    \
    \        int l, r, d, idx;\n            long long lower;\n        };\n       \
    \ struct Item {\n            int freq, idx;\n        };\n\n        auto item_better\
    \ = [](const Item &a, const Item &b) {\n            if (a.freq != b.freq) return\
    \ a.freq > b.freq;\n            return a.idx < b.idx;\n        };\n        auto\
    \ node_worse = [](const Node &a, const Node &b) {\n            int ca = a.r -\
    \ a.l;\n            int cb = b.r - b.l;\n            if (ca != cb) return ca <\
    \ cb;\n            if (a.lower != b.lower) return a.lower > b.lower;\n       \
    \     return a.d < b.d;\n        };\n\n        vector<Node> heap;\n        heap.push_back({l,\
    \ r, 0, 0, 0});\n        vector<Item> best;\n        best.reserve(min(k, r - l));\n\
    \n        while (!heap.empty()) {\n            if ((int)best.size() == k) {\n\
    \                const Node &cur = heap.front();\n                const Item &cut\
    \ = best.front();\n                int freq = cur.r - cur.l;\n               \
    \ if (freq < cut.freq) break;\n                if (freq == cut.freq && cur.lower\
    \ >= cut.idx) break;\n            }\n\n            pop_heap(heap.begin(), heap.end(),\
    \ node_worse);\n            Node cur = heap.back();\n            heap.pop_back();\n\
    \n            if (cur.d == lg) {\n                Item item{cur.r - cur.l, cur.idx};\n\
    \                if ((int)best.size() < k) {\n                    best.push_back(item);\n\
    \                    push_heap(best.begin(), best.end(), item_better);\n     \
    \           }\n                else if (item_better(item, best.front())) {\n \
    \                   pop_heap(best.begin(), best.end(), item_better);\n       \
    \             best.back() = item;\n                    push_heap(best.begin(),\
    \ best.end(), item_better);\n                }\n                continue;\n  \
    \          }\n\n            const auto *row = bit.data() + cur.d * blocks;\n \
    \           const int *row_pref = pref.data() + cur.d * (blocks + 1);\n      \
    \      int l1, r1;\n#if defined(__GNUC__) && defined(__x86_64__)\n           \
    \ if (use_bmi2) rank1_pair_bmi2(row, row_pref, cur.l, cur.r, l1, r1);\n      \
    \      else rank1_pair(row, row_pref, cur.l, cur.r, l1, r1);\n#else\n        \
    \    rank1_pair(row, row_pref, cur.l, cur.r, l1, r1);\n#endif\n            int\
    \ l0 = cur.l - l1, r0 = cur.r - r1;\n            int shift = lg - cur.d - 1;\n\
    \            if (l0 < r0) {\n                heap.push_back({l0, r0, cur.d + 1,\
    \ cur.idx << 1, cur.lower});\n                push_heap(heap.begin(), heap.end(),\
    \ node_worse);\n            }\n            if (l1 < r1) {\n                heap.push_back({\n\
    \                    mid[cur.d] + l1,\n                    mid[cur.d] + r1,\n\
    \                    cur.d + 1,\n                    cur.idx << 1 | 1,\n     \
    \               cur.lower + (1LL << shift)\n                });\n            \
    \    push_heap(heap.begin(), heap.end(), node_worse);\n            }\n       \
    \ }\n\n        sort(best.begin(), best.end(), item_better);\n        vector<pair<int,\
    \ int>> res;\n        res.reserve(best.size());\n        for (const auto &item\
    \ : best) res.push_back({item.freq, item.idx});\n        return res;\n    }\n\n\
    \    vector<pair<int, T>> top_k_freq(int l, int r, int k) const {\n        auto\
    \ idx_res = top_k_freq_index(l, r, k);\n        vector<pair<int, T>> res;\n  \
    \      res.reserve(idx_res.size());\n        for (const auto &p : idx_res) res.push_back({p.first,\
    \ vals[p.second]});\n        return res;\n    }\n\n    int range_freq(int l, int\
    \ r, const T &lower, const T &upper) const {\n        if (lower >= upper || l\
    \ >= r) return 0;\n        return count_less(l, r, upper) - count_less(l, r, lower);\n\
    \    }\n\n    int freq(int l, int r, const T &x) const {\n        int xi = (int)(lower_bound(vals.begin(),\
    \ vals.end(), x) - vals.begin());\n        if (xi == (int)vals.size() || vals[xi]\
    \ != x) return 0;\n        return count_equal_index(l, r, xi);\n    }\n\n    T\
    \ kth_smallest(int l, int r, int k) const {\n#if defined(__GNUC__) && defined(__x86_64__)\n\
    \        if (__builtin_cpu_supports(\"popcnt\") && __builtin_cpu_supports(\"bmi2\"\
    )) {\n            return vals[kth_smallest_index_bmi2(l, r, k)];\n        }\n\
    #endif\n        return vals[kth_smallest_index_fallback(l, r, k)];\n    }\n\n\
    \    T kth_largest(int l, int r, int k) const {\n        return kth_smallest(l,\
    \ r, r - l - 1 - k);\n    }\n\n    bool prev_value(int l, int r, const T &upper,\
    \ T &res) const {\n        if (l >= r || n == 0) return false;\n        int xi\
    \ = (int)(lower_bound(vals.begin(), vals.end(), upper) - vals.begin());\n    \
    \    if (xi <= 0) return false;\n        if (xi >= (int)vals.size()) {\n     \
    \       res = kth_largest(l, r, 0);\n            return true;\n        }\n#if\
    \ defined(__GNUC__) && defined(__x86_64__)\n        if (__builtin_cpu_supports(\"\
    popcnt\") && __builtin_cpu_supports(\"bmi2\")) {\n            int idx;\n     \
    \       if (!neighbor_index_bmi2<true>(l, r, xi, idx)) return false;\n       \
    \     res = vals[idx];\n            return true;\n        }\n#endif\n        int\
    \ idx;\n        if (!neighbor_index_fallback<true>(l, r, xi, idx)) return false;\n\
    \        res = vals[idx];\n        return true;\n    }\n\n    bool next_value(int\
    \ l, int r, const T &lower, T &res) const {\n        if (l >= r || n == 0) return\
    \ false;\n        int xi = (int)(lower_bound(vals.begin(), vals.end(), lower)\
    \ - vals.begin());\n        if (xi >= (int)vals.size()) return false;\n#if defined(__GNUC__)\
    \ && defined(__x86_64__)\n        if (__builtin_cpu_supports(\"popcnt\") && __builtin_cpu_supports(\"\
    bmi2\")) {\n            int idx;\n            if (!neighbor_index_bmi2<false>(l,\
    \ r, xi, idx)) return false;\n            res = vals[idx];\n            return\
    \ true;\n        }\n#endif\n        int idx;\n        if (!neighbor_index_fallback<false>(l,\
    \ r, xi, idx)) return false;\n        res = vals[idx];\n        return true;\n\
    \    }\n};\n\n/**\n * @brief Wavelet Matrix\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/wavelet_matrix.cpp
  requiredBy: []
  timestamp: '2026-07-26 12:56:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_wavelet_matrix_top_k_freq.test.cpp
  - test/yosupo_range_kth_smallest.test.cpp
  - test/yosupo_static_range_frequency.test.cpp
date: 2026-07-26
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
- `top_k_freq(l, r, k)` : 区間 $[l, r)$ で頻度上位 `k` 個の `(頻度, 値)` を返す。同頻度なら値昇順
- `kth_smallest(l, r, k)` : 区間 $[l, r)$ の `k` 番目 (0-indexed) に小さい値を返す
- `kth_largest(l, r, k)` : 区間 $[l, r)$ の `k` 番目 (0-indexed) に大きい値を返す
- `prev_value(l, r, upper, res)` : 区間 $[l, r)$ にある `upper` 未満の最大値を `res` に返す。存在しない場合 `false`
- `next_value(l, r, lower, res)` : 区間 $[l, r)$ にある `lower` 以上の最小値を `res` に返す。存在しない場合 `false`

## 実装上の補足
- 値は内部で座標圧縮して扱う。
- 圧縮済みで使うときは query 側も index API を使うと二分探索を省ける。
- 整数値の座標圧縮は値域に必要な桁だけ radix sort する。
- GCC の x86-64 環境では実行時に CPU 機能を判定し、構築に AVX2 / AVX-512、rank に POPCNT / BMI2 を使う。コンパイルオプションの追加は不要で、非対応 CPU では通常実装へ戻る。
- クエリはすべて静的配列前提。
