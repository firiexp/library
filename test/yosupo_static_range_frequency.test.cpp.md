---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/wavelet_matrix.cpp
    title: Wavelet Matrix
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_frequency
    links:
    - https://judge.yosupo.jp/problem/static_range_frequency
  bundledCode: "#line 1 \"test/yosupo_static_range_frequency.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/static_range_frequency\"\n\n#include <algorithm>\n\
    #include <type_traits>\n#include <vector>\nusing namespace std;\n\n#line 1 \"\
    datastructure/wavelet_matrix.cpp\"\n#if defined(__GNUC__) && defined(__x86_64__)\n\
    #include <immintrin.h>\n#endif\n\ntemplate <class T>\nstruct WaveletMatrix {\n\
    \    int n, lg, blocks;\n    vector<int> mid;\n    vector<unsigned long long>\
    \ bit;\n    vector<int> pref;\n    vector<T> vals;\n\n    WaveletMatrix() : n(0),\
    \ lg(0), blocks(0) {}\n    explicit WaveletMatrix(const vector<T> &v) { build(v);\
    \ }\n\n    static inline void rank1_pair(const unsigned long long *row, const\
    \ int *row_pref, int l, int r, int &l1, int &r1) {\n        int l_block = l >>\
    \ 6;\n        l1 = row_pref[l_block];\n        int l_rem = l & 63;\n        if\
    \ (l_rem) l1 += __builtin_popcountll(row[l_block] & ((1ULL << l_rem) - 1));\n\n\
    \        int r_block = r >> 6;\n        r1 = row_pref[r_block];\n        int r_rem\
    \ = r & 63;\n        if (r_rem) r1 += __builtin_popcountll(row[r_block] & ((1ULL\
    \ << r_rem) - 1));\n    }\n\n#if defined(__GNUC__) && defined(__x86_64__)\n  \
    \  __attribute__((target(\"popcnt,bmi2\")))\n    static inline void rank1_pair_bmi2(const\
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
    \    }\n};\n\n/**\n * @brief Wavelet Matrix\n */\n#line 9 \"test/yosupo_static_range_frequency.test.cpp\"\
    \n#include <cstdio>\n#include <cstring>\n#include <string>\n\n#include <charconv>\n\
    #line 1 \"util/fastio.cpp\"\nusing namespace std;\n\nextern \"C\" int fileno(FILE\
    \ *);\nextern \"C\" int isatty(int);\n\ntemplate<class T, class = void>\nstruct\
    \ is_fastio_range : false_type {};\n\ntemplate<class T>\nstruct is_fastio_range<T,\
    \ void_t<decltype(declval<T &>().begin()), decltype(declval<T &>().end())>> :\
    \ true_type {};\n\ntemplate<class T, class = void>\nstruct has_fastio_value :\
    \ false_type {};\n\ntemplate<class T>\nstruct has_fastio_value<T, void_t<decltype(declval<const\
    \ T &>().value())>> : true_type {};\n\ntemplate<class T, class = void>\nstruct\
    \ has_fastio_assign_string : false_type {};\n\ntemplate<class T>\nstruct has_fastio_assign_string<T,\
    \ void_t<decltype(declval<T &>().assign(declval<const string &>()))>> : true_type\
    \ {};\n\ntemplate<class T, class = void>\nstruct has_fastio_to_string : false_type\
    \ {};\n\ntemplate<class T>\nstruct has_fastio_to_string<T, void_t<decltype(declval<const\
    \ T &>().to_string())>> : true_type {};\n\nstruct FastIoDigitTable {\n    char\
    \ num[40000];\n\n    constexpr FastIoDigitTable() : num() {\n        for (int\
    \ i = 0; i < 10000; ++i) {\n            int x = i;\n            for (int j = 3;\
    \ j >= 0; --j) {\n                num[i * 4 + j] = char('0' + x % 10);\n     \
    \           x /= 10;\n            }\n        }\n    }\n};\n\nstruct Scanner {\n\
    \    static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET\
    \ = 64;\n    static constexpr int LONG_TOKEN_SAMPLE_SIZE = 1024;\n    static constexpr\
    \ int LONG_TOKEN_MIN_DIGITS = 16;\n    char buf[BUFSIZE + 1];\n    int idx, size;\n\
    \    bool interactive, long_tokens;\n    string number_token;\n\n    Scanner()\
    \ : idx(0), size(0), interactive(isatty(fileno(stdin))), long_tokens(false) {}\n\
    \n    __attribute__((always_inline))\n    static inline unsigned parse_eight_digits(const\
    \ char *p) {\n        unsigned long long value;\n        memcpy(&value, p, 8);\n\
    #if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__\n      \
    \  value = __builtin_bswap64(value);\n#endif\n        value -= 0x3030303030303030ULL;\n\
    \        value = (value * 10 + (value >> 8)) & 0x00ff00ff00ff00ffULL;\n      \
    \  value = (value * 100 + (value >> 16)) & 0x0000ffff0000ffffULL;\n        value\
    \ = (value * 10000 + (value >> 32)) & 0x00000000ffffffffULL;\n        return (unsigned)value;\n\
    \    }\n\n    __attribute__((always_inline))\n    static inline bool are_eight_digits(const\
    \ char *p) {\n        unsigned long long value;\n        memcpy(&value, p, 8);\n\
    \        return (((value + 0x4646464646464646ULL) | (value - 0x3030303030303030ULL))\
    \ & 0x8080808080808080ULL) == 0;\n    }\n\n    template<class U>\n    __attribute__((noinline))\n\
    \    U read_long_digits(char c) {\n        const char *p = buf + idx - 1;\n  \
    \      const char *end = buf + size;\n        U value = 0;\n        if (c >= '0'\
    \ && end - p >= 16 && p[15] >= '0' && are_eight_digits(p) && are_eight_digits(p\
    \ + 8)) {\n            value = (U)parse_eight_digits(p) * 100000000 + parse_eight_digits(p\
    \ + 8);\n            p += 16;\n            while (*p >= '0') {\n             \
    \   value = value * 10 + (*p & 15);\n                ++p;\n            }\n   \
    \         idx = (int)(p - buf) + 1;\n            return value;\n        }\n  \
    \      while (c >= '0') {\n            value = value * 10 + (c & 15);\n      \
    \      c = buf[idx++];\n        }\n        return value;\n    }\n\n    inline\
    \ void load() {\n        int len = size - idx;\n        memmove(buf, buf + idx,\
    \ len);\n        if (interactive) {\n            if (fgets(buf + len, BUFSIZE\
    \ + 1 - len, stdin)) size = len + (int)strlen(buf + len);\n            else size\
    \ = len;\n        } else {\n            size = len + (int)fread(buf + len, 1,\
    \ BUFSIZE - len, stdin);\n            int sample_size = min(size, LONG_TOKEN_SAMPLE_SIZE);\n\
    \            int separators = 0;\n            int minus_signs = 0;\n         \
    \   for (int i = 0; i < sample_size; ++i) {\n                separators += buf[i]\
    \ <= ' ';\n                minus_signs += buf[i] == '-';\n            }\n    \
    \        // Select once per buffer so ordinary short integers avoid the\n    \
    \        // checks and call overhead of the 16-digit SWAR path.\n            long_tokens\
    \ = separators * LONG_TOKEN_MIN_DIGITS < sample_size - minus_signs;\n        }\n\
    \        idx = 0;\n        buf[size] = 0;\n    }\n\n    inline void ensure() {\n\
    \        if (idx + OFFSET > size) load();\n    }\n\n    inline void ensure_interactive()\
    \ {\n        if (idx == size) load();\n    }\n\n    inline char skip() {\n   \
    \     if (interactive) {\n            ensure_interactive();\n            while\
    \ (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n                ensure_interactive();\n\
    \            }\n            return buf[idx++];\n        }\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        return buf[idx++];\n    }\n\n    template<class\
    \ T, typename enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T\
    \ &x) {\n        using Base = typename conditional<is_same<T, bool>::value, unsigned,\
    \ T>::type;\n        using U = typename make_unsigned<Base>::type;\n        //\
    \ The unsigned magnitude and -(y - 1) - 1 below also cover min(T).\n        if\
    \ (interactive) {\n            char c = skip();\n            bool neg = false;\n\
    \            if constexpr (is_signed<T>::value) {\n                if (c == '-')\
    \ {\n                    neg = true;\n                    ensure_interactive();\n\
    \                    c = buf[idx++];\n                }\n            }\n     \
    \       U y = 0;\n            while (c >= '0') {\n                y = y * 10 +\
    \ (c & 15);\n                ensure_interactive();\n                c = buf[idx++];\n\
    \            }\n            if constexpr (is_signed<T>::value) {\n           \
    \     if (neg && y) {\n                    x = -static_cast<T>(y - 1);\n     \
    \               --x;\n                    return;\n                }\n       \
    \     }\n            x = static_cast<T>(y);\n            return;\n        }\n\
    \        char c = skip();\n        bool neg = false;\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (c == '-') {\n                neg = true;\n              \
    \  c = buf[idx++];\n            }\n        }\n        U y;\n        if (__builtin_expect(long_tokens,\
    \ false)) {\n            y = read_long_digits<U>(c);\n        } else {\n     \
    \       y = 0;\n            while (c >= '0') {\n                y = y * 10 + (c\
    \ & 15);\n                c = buf[idx++];\n            }\n        }\n        if\
    \ constexpr (is_signed<T>::value) {\n            if (neg && y) {\n           \
    \     x = -static_cast<T>(y - 1);\n                --x;\n                return;\n\
    \            }\n        }\n        x = static_cast<T>(y);\n    }\n\n    void read(double\
    \ &x) {\n        read(number_token);\n        const char *first = number_token.data();\n\
    \        const char *last = first + number_token.size();\n        auto result\
    \ = from_chars(first, last, x);\n        if (result.ec != errc{} || result.ptr\
    \ != last) __builtin_trap();\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && has_fastio_value<T>::value, int>::type = 0>\n    void read(T &x) {\n    \
    \    long long v;\n        read(v);\n        x = T(v);\n    }\n\n    template<class\
    \ T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value && !has_fastio_value<T>::value\
    \ && has_fastio_assign_string<T>::value, int>::type = 0>\n    void read(T &x)\
    \ {\n        string s;\n        read(s);\n        bool ok = x.assign(s);\n   \
    \     if (!ok) __builtin_trap();\n    }\n\n    template<class Head, class Next,\
    \ class... Tail>\n    void read(Head &head, Next &next, Tail &...tail) {\n   \
    \     read(head);\n        read(next, tail...);\n    }\n\n    template<class T,\
    \ class U>\n    void read(pair<T, U> &p) {\n        read(p.first, p.second);\n\
    \    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
    \ read(T &a) {\n        for (auto &x : a) read(x);\n    }\n\n    void read(char\
    \ &c) {\n        c = skip();\n    }\n\n    void read(string &s) {\n        s.clear();\n\
    \        if (interactive) {\n            ensure_interactive();\n            while\
    \ (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n                ensure_interactive();\n\
    \            }\n            while (true) {\n                int start = idx;\n\
    \                while (idx < size && buf[idx] > ' ') ++idx;\n               \
    \ s.append(buf + start, idx - start);\n                if (idx < size) break;\n\
    \                load();\n                if (size == 0) break;\n            }\n\
    \            if (idx < size) ++idx;\n            return;\n        }\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (idx < size && buf[idx] > ' ') ++idx;\n            s.append(buf\
    \ + start, idx - start);\n            if (idx < size) break;\n            load();\n\
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    static constexpr int DEFAULT_DOUBLE_PRECISION = 15;\n    char buf[BUFSIZE];\n\
    \    int idx;\n    bool interactive;\n    string number_buf;\n    inline static\
    \ constexpr FastIoDigitTable table{};\n\n    Printer() : idx(0), interactive(isatty(fileno(stdout)))\
    \ {}\n    ~Printer() { flush(); }\n\n    inline void flush() {\n        if (idx)\
    \ {\n            fwrite(buf, 1, idx, stdout);\n            idx = 0;\n        }\n\
    \    }\n\n    inline void pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n\
    \        buf[idx++] = c;\n        if (interactive && c == '\\n') flush();\n  \
    \  }\n\n    inline void print_range(const char *s, size_t n) {\n        size_t\
    \ pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n\
    \            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n         \
    \   memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n     \
    \       pos += chunk;\n        }\n    }\n\n    void print(const char *s) {\n \
    \       print_range(s, strlen(s));\n    }\n\n    void print(const string &s) {\n\
    \        print_range(s.data(), s.size());\n    }\n\n    void print(char c) {\n\
    \        pc(c);\n    }\n\n    void print(bool b) {\n        pc(char('0' + (b ?\
    \ 1 : 0)));\n    }\n\n    inline char *write_top(char *out, unsigned x) {\n  \
    \      if (x >= 1000) {\n            memcpy(out, table.num + (x << 2), 4);\n \
    \           return out + 4;\n        }\n        if (x >= 100) {\n            memcpy(out,\
    \ table.num + (x << 2) + 1, 3);\n            return out + 3;\n        }\n    \
    \    if (x >= 10) {\n            unsigned q = (x * 205) >> 11;\n            out[0]\
    \ = char('0' + q);\n            out[1] = char('0' + (x - q * 10));\n         \
    \   return out + 2;\n        }\n        *out = char('0' + x);\n        return\
    \ out + 1;\n    }\n\n    inline void write_four(char *out, unsigned x) {\n   \
    \     memcpy(out, table.num + (x << 2), 4);\n    }\n\n    inline void write_eight(char\
    \ *out, unsigned x) {\n        unsigned hi = x / 10000;\n        unsigned lo =\
    \ x - hi * 10000;\n        write_four(out, hi);\n        write_four(out + 4, lo);\n\
    \    }\n\n    inline char *write_u32(char *out, unsigned x) {\n        if (x >=\
    \ 100000000) {\n            unsigned hi = x / 100000000;\n            unsigned\
    \ lo = x - hi * 100000000;\n            out = write_top(out, hi);\n          \
    \  write_eight(out, lo);\n            return out + 8;\n        }\n        if (x\
    \ >= 10000) {\n            unsigned hi = x / 10000;\n            unsigned lo =\
    \ x - hi * 10000;\n            out = write_top(out, hi);\n            write_four(out,\
    \ lo);\n            return out + 4;\n        }\n        return write_top(out,\
    \ x);\n    }\n\n    __attribute__((noinline))\n    inline char *write_u64(char\
    \ *out, unsigned long long x) {\n        if (x <= 0xffffffffULL) return write_u32(out,\
    \ (unsigned)x);\n        unsigned long long hi = x / 100000000;\n        unsigned\
    \ lo = (unsigned)(x - hi * 100000000);\n        if (hi <= 0xffffffffULL) {\n \
    \           out = write_u32(out, (unsigned)hi);\n            write_eight(out,\
    \ lo);\n            return out + 8;\n        }\n        unsigned top = (unsigned)(hi\
    \ / 100000000);\n        unsigned mid = (unsigned)(hi - (unsigned long long)top\
    \ * 100000000);\n        out = write_u32(out, top);\n        write_eight(out,\
    \ mid);\n        write_eight(out + 8, lo);\n        return out + 16;\n    }\n\n\
    \    template<class T, typename enable_if<is_integral<T>::value && !is_same<T,\
    \ bool>::value, int>::type = 0>\n    void print(T x) {\n        if (idx > BUFSIZE\
    \ - 100) flush();\n        using U = typename make_unsigned<T>::type;\n      \
    \  U y;\n        if constexpr (is_signed<T>::value) {\n            if (x < 0)\
    \ {\n                buf[idx++] = '-';\n                y = U(0) - static_cast<U>(x);\n\
    \            } else {\n                y = static_cast<U>(x);\n            }\n\
    \        } else {\n            y = x;\n        }\n        if (y == 0) {\n    \
    \        buf[idx++] = '0';\n            return;\n        }\n        char *out;\n\
    \        if constexpr (sizeof(U) <= 4) {\n            out = write_u32(buf + idx,\
    \ (unsigned)y);\n        } else if constexpr (sizeof(U) <= 8) {\n            out\
    \ = write_u64(buf + idx, (unsigned long long)y);\n        } else {\n         \
    \   static constexpr int TMP_SIZE = sizeof(U) * 10 / 4;\n            char tmp[TMP_SIZE];\n\
    \            int pos = TMP_SIZE;\n            while (y >= 10000) {\n         \
    \       pos -= 4;\n                memcpy(tmp + pos, table.num + (y % 10000) *\
    \ 4, 4);\n                y /= 10000;\n            }\n            out = write_top(buf\
    \ + idx, (unsigned)y);\n            memcpy(out, tmp + pos, TMP_SIZE - pos);\n\
    \            out += TMP_SIZE - pos;\n        }\n        idx = (int)(out - buf);\n\
    \    }\n\n    void print_fixed(double x, int precision = DEFAULT_DOUBLE_PRECISION)\
    \ {\n        if (precision < 0) __builtin_trap();\n        size_t required = (size_t)precision\
    \ + 512;\n        if (number_buf.size() < required) number_buf.resize(required);\n\
    \        while (true) {\n            char *first = number_buf.data();\n      \
    \      char *last = first + number_buf.size();\n            auto result = to_chars(first,\
    \ last, x, chars_format::fixed, precision);\n            if (result.ec == errc{})\
    \ {\n                print_range(first, result.ptr - first);\n               \
    \ return;\n            }\n            if (result.ec != errc::value_too_large)\
    \ __builtin_trap();\n            size_t next_size = number_buf.size() * 2;\n \
    \           if (next_size <= number_buf.size()) __builtin_trap();\n          \
    \  number_buf.resize(next_size);\n        }\n    }\n\n    void print(double x)\
    \ {\n        print_fixed(x);\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && has_fastio_value<T>::value, int>::type = 0>\n    void print(const T &x) {\n\
    \        print(x.value());\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && !has_fastio_value<T>::value && has_fastio_to_string<T>::value, int>::type\
    \ = 0>\n    void print(const T &x) {\n        print(x.to_string());\n    }\n\n\
    \    template<class T, typename enable_if<is_fastio_range<T>::value && !is_same<typename\
    \ decay<T>::type, string>::value, int>::type = 0>\n    void print(const T &a)\
    \ {\n        bool first = true;\n        for (auto &&x : a) {\n            if\
    \ (!first) pc(' ');\n            first = false;\n            print(x);\n     \
    \   }\n    }\n\n    template<class T>\n    void println(const T &x) {\n      \
    \  print(x);\n        pc('\\n');\n    }\n\n    template<class Head, class... Tail>\n\
    \    void println(const Head &head, const Tail &...tail) {\n        print(head);\n\
    \        ((pc(' '), print(tail)), ...);\n        pc('\\n');\n    }\n\n    void\
    \ println_fixed(double x, int precision = DEFAULT_DOUBLE_PRECISION) {\n      \
    \  print_fixed(x, precision);\n        pc('\\n');\n    }\n\n    void println()\
    \ {\n        pc('\\n');\n    }\n};\n\ntemplate<class T>\nScanner &operator>>(Scanner\
    \ &in, T &x) {\n    in.read(x);\n    return in;\n}\n\ntemplate<class T>\nPrinter\
    \ &operator<<(Printer &out, const T &x) {\n    out.print(x);\n    return out;\n\
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 15 \"\
    test/yosupo_static_range_frequency.test.cpp\"\n\nint main() {\n    Scanner in;\n\
    \    Printer out;\n    int n, q;\n    in.read(n);\n    in.read(q);\n    vector<int>\
    \ a(n);\n    for (int i = 0; i < n; ++i) in.read(a[i]);\n\n    vector<int> vals\
    \ = a;\n    sort(vals.begin(), vals.end());\n    vals.erase(unique(vals.begin(),\
    \ vals.end()), vals.end());\n    vector<int> idx(n);\n    for (int i = 0; i <\
    \ n; ++i) idx[i] = (int)(lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin());\n\
    \n    WaveletMatrix<int> wm;\n    wm.build_from_index(idx, vals);\n    while (q--)\
    \ {\n        int l, r, x;\n        in.read(l);\n        in.read(r);\n        in.read(x);\n\
    \        int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \        if (xi == (int)vals.size() || vals[xi] != x) out.println(0);\n      \
    \  else out.println(wm.count_equal_index(l, r, xi));\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_frequency\"\
    \n\n#include <algorithm>\n#include <type_traits>\n#include <vector>\nusing namespace\
    \ std;\n\n#include \"../datastructure/wavelet_matrix.cpp\"\n#include <cstdio>\n\
    #include <cstring>\n#include <string>\n\n#include <charconv>\n#include \"../util/fastio.cpp\"\
    \n\nint main() {\n    Scanner in;\n    Printer out;\n    int n, q;\n    in.read(n);\n\
    \    in.read(q);\n    vector<int> a(n);\n    for (int i = 0; i < n; ++i) in.read(a[i]);\n\
    \n    vector<int> vals = a;\n    sort(vals.begin(), vals.end());\n    vals.erase(unique(vals.begin(),\
    \ vals.end()), vals.end());\n    vector<int> idx(n);\n    for (int i = 0; i <\
    \ n; ++i) idx[i] = (int)(lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin());\n\
    \n    WaveletMatrix<int> wm;\n    wm.build_from_index(idx, vals);\n    while (q--)\
    \ {\n        int l, r, x;\n        in.read(l);\n        in.read(r);\n        in.read(x);\n\
    \        int xi = (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());\n\
    \        if (xi == (int)vals.size() || vals[xi] != x) out.println(0);\n      \
    \  else out.println(wm.count_equal_index(l, r, xi));\n    }\n    return 0;\n}\n"
  dependsOn:
  - datastructure/wavelet_matrix.cpp
  - util/fastio.cpp
  isVerificationFile: true
  path: test/yosupo_static_range_frequency.test.cpp
  requiredBy: []
  timestamp: '2026-08-02 21:15:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_static_range_frequency.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_static_range_frequency.test.cpp
- /verify/test/yosupo_static_range_frequency.test.cpp.html
title: test/yosupo_static_range_frequency.test.cpp
---
