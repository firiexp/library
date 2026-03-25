---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0275_dynamic_bitset.test.cpp
    title: test/aoj0275_dynamic_bitset.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj_alds1_14_b_dynamic_bitset.test.cpp
    title: test/aoj_alds1_14_b_dynamic_bitset.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_dynamic_bitset.test.cpp
    title: test/yosupo_aplusb_dynamic_bitset.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u52D5\u7684bitset(Dynamic Bitset)"
    links: []
  bundledCode: "#line 1 \"datastructure/dynamic_bitset.cpp\"\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n#include <immintrin.h>\n#endif\n\nusing namespace std;\n\
    \nnamespace dynamic_bitset_detail {\nusing Word = unsigned long long;\nconstexpr\
    \ int avx2_threshold_words = 8;\n\n#if defined(__x86_64__) || defined(_M_X64)\n\
    __attribute__((target(\"avx2\"))) inline void and_assign_avx2(Word *dst, const\
    \ Word *src, int m) {\n    int i = 0;\n    for (; i + 4 <= m; i += 4) {\n    \
    \    __m256i x = _mm256_loadu_si256((const __m256i *)(dst + i));\n        __m256i\
    \ y = _mm256_loadu_si256((const __m256i *)(src + i));\n        _mm256_storeu_si256((__m256i\
    \ *)(dst + i), _mm256_and_si256(x, y));\n    }\n    for (; i < m; ++i) dst[i]\
    \ &= src[i];\n}\n\n__attribute__((target(\"avx2\"))) inline void or_assign_avx2(Word\
    \ *dst, const Word *src, int m) {\n    int i = 0;\n    for (; i + 4 <= m; i +=\
    \ 4) {\n        __m256i x = _mm256_loadu_si256((const __m256i *)(dst + i));\n\
    \        __m256i y = _mm256_loadu_si256((const __m256i *)(src + i));\n       \
    \ _mm256_storeu_si256((__m256i *)(dst + i), _mm256_or_si256(x, y));\n    }\n \
    \   for (; i < m; ++i) dst[i] |= src[i];\n}\n\n__attribute__((target(\"avx2\"\
    ))) inline void xor_assign_avx2(Word *dst, const Word *src, int m) {\n    int\
    \ i = 0;\n    for (; i + 4 <= m; i += 4) {\n        __m256i x = _mm256_loadu_si256((const\
    \ __m256i *)(dst + i));\n        __m256i y = _mm256_loadu_si256((const __m256i\
    \ *)(src + i));\n        _mm256_storeu_si256((__m256i *)(dst + i), _mm256_xor_si256(x,\
    \ y));\n    }\n    for (; i < m; ++i) dst[i] ^= src[i];\n}\n\n__attribute__((target(\"\
    avx2\"))) inline bool any_avx2(const Word *src, int m) {\n    __m256i acc = _mm256_setzero_si256();\n\
    \    int i = 0;\n    for (; i + 4 <= m; i += 4) {\n        acc = _mm256_or_si256(acc,\
    \ _mm256_loadu_si256((const __m256i *)(src + i)));\n    }\n    if (!_mm256_testz_si256(acc,\
    \ acc)) return true;\n    for (; i < m; ++i) {\n        if (src[i]) return true;\n\
    \    }\n    return false;\n}\n\n__attribute__((target(\"avx2\"))) inline bool\
    \ all_full_words_avx2(const Word *src, int m) {\n    const __m256i ones = _mm256_set1_epi64x(-1);\n\
    \    int i = 0;\n    for (; i + 4 <= m; i += 4) {\n        __m256i x = _mm256_loadu_si256((const\
    \ __m256i *)(src + i));\n        __m256i eq = _mm256_cmpeq_epi64(x, ones);\n \
    \       if (_mm256_movemask_epi8(eq) != -1) return false;\n    }\n    for (; i\
    \ < m; ++i) {\n        if (src[i] != ~0ULL) return false;\n    }\n    return true;\n\
    }\n\ninline bool has_avx2() {\n    static const bool cached = __builtin_cpu_supports(\"\
    avx2\");\n    return cached;\n}\n#endif\n}  // namespace dynamic_bitset_detail\n\
    \nclass DynamicBitset {\n    static constexpr int B = 64;\n    using Word = unsigned\
    \ long long;\n\n    int n;\n    vector<Word> a;\n\n    static int popcount(Word\
    \ x) {\n        return __builtin_popcountll(x);\n    }\n    static int ctz(Word\
    \ x) {\n        return __builtin_ctzll(x);\n    }\n    static int clz(Word x)\
    \ {\n        return __builtin_clzll(x);\n    }\n\n    Word tail_mask() const {\n\
    \        int rem = n & (B - 1);\n        return rem ? ((1ULL << rem) - 1) : ~0ULL;\n\
    \    }\n\n    void normalize() {\n        if (!a.empty()) a.back() &= tail_mask();\n\
    \    }\n\npublic:\n    DynamicBitset() : n(0) {}\n    explicit DynamicBitset(int\
    \ n, bool x = false) : n(n), a((n + B - 1) >> 6, x ? ~0ULL : 0ULL) {\n       \
    \ normalize();\n    }\n\n    int size() const { return n; }\n    bool empty()\
    \ const { return n == 0; }\n\n    void reset() {\n        fill(a.begin(), a.end(),\
    \ 0);\n    }\n    void set() {\n        fill(a.begin(), a.end(), ~0ULL);\n   \
    \     normalize();\n    }\n    void flip() {\n        Word *p = a.data();\n  \
    \      int m = (int)a.size();\n        for (int i = 0; i < m; ++i) p[i] = ~p[i];\n\
    \        normalize();\n    }\n\n    bool test(int k) const {\n        return (a[k\
    \ >> 6] >> (k & 63)) & 1ULL;\n    }\n    void set(int k) {\n        a[k >> 6]\
    \ |= 1ULL << (k & 63);\n    }\n    void reset(int k) {\n        a[k >> 6] &= ~(1ULL\
    \ << (k & 63));\n    }\n    void flip(int k) {\n        a[k >> 6] ^= 1ULL << (k\
    \ & 63);\n    }\n    void assign(int k, bool x) {\n        if (x) set(k);\n  \
    \      else reset(k);\n    }\n\n    bool any() const {\n        int m = (int)a.size();\n\
    \        const Word *p = a.data();\n#if defined(__x86_64__) || defined(_M_X64)\n\
    \        if (m >= dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2())\
    \ {\n            return dynamic_bitset_detail::any_avx2(p, m);\n        }\n#endif\n\
    \        for (int i = 0; i < m; ++i) {\n            if (p[i]) return true;\n \
    \       }\n        return false;\n    }\n    bool none() const { return !any();\
    \ }\n    bool all() const {\n        int m = (int)a.size();\n        if (m ==\
    \ 0) return true;\n        const Word *p = a.data();\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n        if (m > 1 + dynamic_bitset_detail::avx2_threshold_words\
    \ && dynamic_bitset_detail::has_avx2()) {\n            if (!dynamic_bitset_detail::all_full_words_avx2(p,\
    \ m - 1)) return false;\n        } else\n#endif\n        {\n            for (int\
    \ i = 0; i + 1 < m; ++i) {\n                if (p[i] != ~0ULL) return false;\n\
    \            }\n        }\n        return p[m - 1] == tail_mask();\n    }\n  \
    \  int count() const {\n        const Word *p = a.data();\n        int m = (int)a.size();\n\
    \        int res = 0;\n        int i = 0;\n        for (; i + 4 <= m; i += 4)\
    \ {\n            res += popcount(p[i + 0]) + popcount(p[i + 1]) + popcount(p[i\
    \ + 2]) + popcount(p[i + 3]);\n        }\n        for (; i < m; ++i) res += popcount(p[i]);\n\
    \        return res;\n    }\n\n    int find_first() const {\n        int m = (int)a.size();\n\
    \        const Word *p = a.data();\n        for (int i = 0; i < m; ++i) {\n  \
    \          if (p[i]) return (i << 6) + ctz(p[i]);\n        }\n        return -1;\n\
    \    }\n    int find_last() const {\n        const Word *p = a.data();\n     \
    \   for (int i = (int)a.size() - 1; i >= 0; --i) {\n            if (p[i]) return\
    \ (i << 6) + (B - 1 - clz(p[i]));\n        }\n        return -1;\n    }\n    int\
    \ find_next(int k) const {\n        ++k;\n        if (k >= n) return -1;\n   \
    \     const Word *p = a.data();\n        int i = k >> 6;\n        Word x = p[i]\
    \ & (~0ULL << (k & 63));\n        if (x) return (i << 6) + ctz(x);\n        int\
    \ m = (int)a.size();\n        for (++i; i < m; ++i) {\n            if (p[i]) return\
    \ (i << 6) + ctz(p[i]);\n        }\n        return -1;\n    }\n    int find_prev(int\
    \ k) const {\n        --k;\n        if (k < 0) return -1;\n        const Word\
    \ *p = a.data();\n        int i = k >> 6;\n        int rem = k & 63;\n       \
    \ Word mask = rem == B - 1 ? ~0ULL : ((1ULL << (rem + 1)) - 1);\n        Word\
    \ x = p[i] & mask;\n        if (x) return (i << 6) + (B - 1 - clz(x));\n     \
    \   for (--i; i >= 0; --i) {\n            if (p[i]) return (i << 6) + (B - 1 -\
    \ clz(p[i]));\n        }\n        return -1;\n    }\n\n    DynamicBitset &operator&=(const\
    \ DynamicBitset &r) {\n        Word *p = a.data();\n        const Word *q = r.a.data();\n\
    \        int m = (int)a.size();\n#if defined(__x86_64__) || defined(_M_X64)\n\
    \        if (m >= dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2())\
    \ {\n            dynamic_bitset_detail::and_assign_avx2(p, q, m);\n          \
    \  return *this;\n        }\n#endif\n        for (int i = 0; i < m; ++i) p[i]\
    \ &= q[i];\n        return *this;\n    }\n    DynamicBitset &operator|=(const\
    \ DynamicBitset &r) {\n        Word *p = a.data();\n        const Word *q = r.a.data();\n\
    \        int m = (int)a.size();\n#if defined(__x86_64__) || defined(_M_X64)\n\
    \        if (m >= dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2())\
    \ {\n            dynamic_bitset_detail::or_assign_avx2(p, q, m);\n           \
    \ return *this;\n        }\n#endif\n        for (int i = 0; i < m; ++i) p[i] |=\
    \ q[i];\n        return *this;\n    }\n    DynamicBitset &operator^=(const DynamicBitset\
    \ &r) {\n        Word *p = a.data();\n        const Word *q = r.a.data();\n  \
    \      int m = (int)a.size();\n#if defined(__x86_64__) || defined(_M_X64)\n  \
    \      if (m >= dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2())\
    \ {\n            dynamic_bitset_detail::xor_assign_avx2(p, q, m);\n          \
    \  normalize();\n            return *this;\n        }\n#endif\n        for (int\
    \ i = 0; i < m; ++i) p[i] ^= q[i];\n        normalize();\n        return *this;\n\
    \    }\n\n    friend DynamicBitset operator&(DynamicBitset l, const DynamicBitset\
    \ &r) { return l &= r; }\n    friend DynamicBitset operator|(DynamicBitset l,\
    \ const DynamicBitset &r) { return l |= r; }\n    friend DynamicBitset operator^(DynamicBitset\
    \ l, const DynamicBitset &r) { return l ^= r; }\n\n    DynamicBitset &operator<<=(int\
    \ s) {\n        if (s <= 0 || n == 0) return *this;\n        if (s >= n) {\n \
    \           reset();\n            return *this;\n        }\n        if (s == 1)\
    \ {\n            Word carry = 0;\n            for (int i = 0; i < (int)a.size();\
    \ ++i) {\n                Word next = a[i] >> (B - 1);\n                a[i] =\
    \ (a[i] << 1) | carry;\n                carry = next;\n            }\n       \
    \     normalize();\n            return *this;\n        }\n        int m = (int)a.size();\n\
    \        int block = s >> 6;\n        int rem = s & 63;\n        if (rem == 0)\
    \ {\n            memmove(a.data() + block, a.data(), sizeof(Word) * (m - block));\n\
    \        } else {\n            for (int i = m - 1; i > block; --i) {\n       \
    \         a[i] = (a[i - block] << rem) | (a[i - block - 1] >> (B - rem));\n  \
    \          }\n            a[block] = a[0] << rem;\n        }\n        fill(a.begin(),\
    \ a.begin() + block, 0);\n        normalize();\n        return *this;\n    }\n\
    \    DynamicBitset &operator>>=(int s) {\n        if (s <= 0 || n == 0) return\
    \ *this;\n        if (s >= n) {\n            reset();\n            return *this;\n\
    \        }\n        if (s == 1) {\n            int m = (int)a.size();\n      \
    \      for (int i = 0; i < m; ++i) {\n                Word next = i + 1 < m ?\
    \ (a[i + 1] << (B - 1)) : 0;\n                a[i] = (a[i] >> 1) | next;\n   \
    \         }\n            normalize();\n            return *this;\n        }\n\
    \        int m = (int)a.size();\n        int block = s >> 6;\n        int rem\
    \ = s & 63;\n        if (rem == 0) {\n            memmove(a.data(), a.data() +\
    \ block, sizeof(Word) * (m - block));\n        } else {\n            int last\
    \ = m - block - 1;\n            for (int i = 0; i < last; ++i) {\n           \
    \     a[i] = (a[i + block] >> rem) | (a[i + block + 1] << (B - rem));\n      \
    \      }\n            a[last] = a[m - 1] >> rem;\n        }\n        fill(a.begin()\
    \ + (m - block), a.end(), 0);\n        normalize();\n        return *this;\n \
    \   }\n\n    friend DynamicBitset operator<<(DynamicBitset l, int s) { return\
    \ l <<= s; }\n    friend DynamicBitset operator>>(DynamicBitset l, int s) { return\
    \ l >>= s; }\n};\n\n/**\n * @brief \u52D5\u7684bitset(Dynamic Bitset)\n */\n"
  code: "#if defined(__x86_64__) || defined(_M_X64)\n#include <immintrin.h>\n#endif\n\
    \nusing namespace std;\n\nnamespace dynamic_bitset_detail {\nusing Word = unsigned\
    \ long long;\nconstexpr int avx2_threshold_words = 8;\n\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n__attribute__((target(\"avx2\"))) inline void and_assign_avx2(Word\
    \ *dst, const Word *src, int m) {\n    int i = 0;\n    for (; i + 4 <= m; i +=\
    \ 4) {\n        __m256i x = _mm256_loadu_si256((const __m256i *)(dst + i));\n\
    \        __m256i y = _mm256_loadu_si256((const __m256i *)(src + i));\n       \
    \ _mm256_storeu_si256((__m256i *)(dst + i), _mm256_and_si256(x, y));\n    }\n\
    \    for (; i < m; ++i) dst[i] &= src[i];\n}\n\n__attribute__((target(\"avx2\"\
    ))) inline void or_assign_avx2(Word *dst, const Word *src, int m) {\n    int i\
    \ = 0;\n    for (; i + 4 <= m; i += 4) {\n        __m256i x = _mm256_loadu_si256((const\
    \ __m256i *)(dst + i));\n        __m256i y = _mm256_loadu_si256((const __m256i\
    \ *)(src + i));\n        _mm256_storeu_si256((__m256i *)(dst + i), _mm256_or_si256(x,\
    \ y));\n    }\n    for (; i < m; ++i) dst[i] |= src[i];\n}\n\n__attribute__((target(\"\
    avx2\"))) inline void xor_assign_avx2(Word *dst, const Word *src, int m) {\n \
    \   int i = 0;\n    for (; i + 4 <= m; i += 4) {\n        __m256i x = _mm256_loadu_si256((const\
    \ __m256i *)(dst + i));\n        __m256i y = _mm256_loadu_si256((const __m256i\
    \ *)(src + i));\n        _mm256_storeu_si256((__m256i *)(dst + i), _mm256_xor_si256(x,\
    \ y));\n    }\n    for (; i < m; ++i) dst[i] ^= src[i];\n}\n\n__attribute__((target(\"\
    avx2\"))) inline bool any_avx2(const Word *src, int m) {\n    __m256i acc = _mm256_setzero_si256();\n\
    \    int i = 0;\n    for (; i + 4 <= m; i += 4) {\n        acc = _mm256_or_si256(acc,\
    \ _mm256_loadu_si256((const __m256i *)(src + i)));\n    }\n    if (!_mm256_testz_si256(acc,\
    \ acc)) return true;\n    for (; i < m; ++i) {\n        if (src[i]) return true;\n\
    \    }\n    return false;\n}\n\n__attribute__((target(\"avx2\"))) inline bool\
    \ all_full_words_avx2(const Word *src, int m) {\n    const __m256i ones = _mm256_set1_epi64x(-1);\n\
    \    int i = 0;\n    for (; i + 4 <= m; i += 4) {\n        __m256i x = _mm256_loadu_si256((const\
    \ __m256i *)(src + i));\n        __m256i eq = _mm256_cmpeq_epi64(x, ones);\n \
    \       if (_mm256_movemask_epi8(eq) != -1) return false;\n    }\n    for (; i\
    \ < m; ++i) {\n        if (src[i] != ~0ULL) return false;\n    }\n    return true;\n\
    }\n\ninline bool has_avx2() {\n    static const bool cached = __builtin_cpu_supports(\"\
    avx2\");\n    return cached;\n}\n#endif\n}  // namespace dynamic_bitset_detail\n\
    \nclass DynamicBitset {\n    static constexpr int B = 64;\n    using Word = unsigned\
    \ long long;\n\n    int n;\n    vector<Word> a;\n\n    static int popcount(Word\
    \ x) {\n        return __builtin_popcountll(x);\n    }\n    static int ctz(Word\
    \ x) {\n        return __builtin_ctzll(x);\n    }\n    static int clz(Word x)\
    \ {\n        return __builtin_clzll(x);\n    }\n\n    Word tail_mask() const {\n\
    \        int rem = n & (B - 1);\n        return rem ? ((1ULL << rem) - 1) : ~0ULL;\n\
    \    }\n\n    void normalize() {\n        if (!a.empty()) a.back() &= tail_mask();\n\
    \    }\n\npublic:\n    DynamicBitset() : n(0) {}\n    explicit DynamicBitset(int\
    \ n, bool x = false) : n(n), a((n + B - 1) >> 6, x ? ~0ULL : 0ULL) {\n       \
    \ normalize();\n    }\n\n    int size() const { return n; }\n    bool empty()\
    \ const { return n == 0; }\n\n    void reset() {\n        fill(a.begin(), a.end(),\
    \ 0);\n    }\n    void set() {\n        fill(a.begin(), a.end(), ~0ULL);\n   \
    \     normalize();\n    }\n    void flip() {\n        Word *p = a.data();\n  \
    \      int m = (int)a.size();\n        for (int i = 0; i < m; ++i) p[i] = ~p[i];\n\
    \        normalize();\n    }\n\n    bool test(int k) const {\n        return (a[k\
    \ >> 6] >> (k & 63)) & 1ULL;\n    }\n    void set(int k) {\n        a[k >> 6]\
    \ |= 1ULL << (k & 63);\n    }\n    void reset(int k) {\n        a[k >> 6] &= ~(1ULL\
    \ << (k & 63));\n    }\n    void flip(int k) {\n        a[k >> 6] ^= 1ULL << (k\
    \ & 63);\n    }\n    void assign(int k, bool x) {\n        if (x) set(k);\n  \
    \      else reset(k);\n    }\n\n    bool any() const {\n        int m = (int)a.size();\n\
    \        const Word *p = a.data();\n#if defined(__x86_64__) || defined(_M_X64)\n\
    \        if (m >= dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2())\
    \ {\n            return dynamic_bitset_detail::any_avx2(p, m);\n        }\n#endif\n\
    \        for (int i = 0; i < m; ++i) {\n            if (p[i]) return true;\n \
    \       }\n        return false;\n    }\n    bool none() const { return !any();\
    \ }\n    bool all() const {\n        int m = (int)a.size();\n        if (m ==\
    \ 0) return true;\n        const Word *p = a.data();\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n        if (m > 1 + dynamic_bitset_detail::avx2_threshold_words\
    \ && dynamic_bitset_detail::has_avx2()) {\n            if (!dynamic_bitset_detail::all_full_words_avx2(p,\
    \ m - 1)) return false;\n        } else\n#endif\n        {\n            for (int\
    \ i = 0; i + 1 < m; ++i) {\n                if (p[i] != ~0ULL) return false;\n\
    \            }\n        }\n        return p[m - 1] == tail_mask();\n    }\n  \
    \  int count() const {\n        const Word *p = a.data();\n        int m = (int)a.size();\n\
    \        int res = 0;\n        int i = 0;\n        for (; i + 4 <= m; i += 4)\
    \ {\n            res += popcount(p[i + 0]) + popcount(p[i + 1]) + popcount(p[i\
    \ + 2]) + popcount(p[i + 3]);\n        }\n        for (; i < m; ++i) res += popcount(p[i]);\n\
    \        return res;\n    }\n\n    int find_first() const {\n        int m = (int)a.size();\n\
    \        const Word *p = a.data();\n        for (int i = 0; i < m; ++i) {\n  \
    \          if (p[i]) return (i << 6) + ctz(p[i]);\n        }\n        return -1;\n\
    \    }\n    int find_last() const {\n        const Word *p = a.data();\n     \
    \   for (int i = (int)a.size() - 1; i >= 0; --i) {\n            if (p[i]) return\
    \ (i << 6) + (B - 1 - clz(p[i]));\n        }\n        return -1;\n    }\n    int\
    \ find_next(int k) const {\n        ++k;\n        if (k >= n) return -1;\n   \
    \     const Word *p = a.data();\n        int i = k >> 6;\n        Word x = p[i]\
    \ & (~0ULL << (k & 63));\n        if (x) return (i << 6) + ctz(x);\n        int\
    \ m = (int)a.size();\n        for (++i; i < m; ++i) {\n            if (p[i]) return\
    \ (i << 6) + ctz(p[i]);\n        }\n        return -1;\n    }\n    int find_prev(int\
    \ k) const {\n        --k;\n        if (k < 0) return -1;\n        const Word\
    \ *p = a.data();\n        int i = k >> 6;\n        int rem = k & 63;\n       \
    \ Word mask = rem == B - 1 ? ~0ULL : ((1ULL << (rem + 1)) - 1);\n        Word\
    \ x = p[i] & mask;\n        if (x) return (i << 6) + (B - 1 - clz(x));\n     \
    \   for (--i; i >= 0; --i) {\n            if (p[i]) return (i << 6) + (B - 1 -\
    \ clz(p[i]));\n        }\n        return -1;\n    }\n\n    DynamicBitset &operator&=(const\
    \ DynamicBitset &r) {\n        Word *p = a.data();\n        const Word *q = r.a.data();\n\
    \        int m = (int)a.size();\n#if defined(__x86_64__) || defined(_M_X64)\n\
    \        if (m >= dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2())\
    \ {\n            dynamic_bitset_detail::and_assign_avx2(p, q, m);\n          \
    \  return *this;\n        }\n#endif\n        for (int i = 0; i < m; ++i) p[i]\
    \ &= q[i];\n        return *this;\n    }\n    DynamicBitset &operator|=(const\
    \ DynamicBitset &r) {\n        Word *p = a.data();\n        const Word *q = r.a.data();\n\
    \        int m = (int)a.size();\n#if defined(__x86_64__) || defined(_M_X64)\n\
    \        if (m >= dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2())\
    \ {\n            dynamic_bitset_detail::or_assign_avx2(p, q, m);\n           \
    \ return *this;\n        }\n#endif\n        for (int i = 0; i < m; ++i) p[i] |=\
    \ q[i];\n        return *this;\n    }\n    DynamicBitset &operator^=(const DynamicBitset\
    \ &r) {\n        Word *p = a.data();\n        const Word *q = r.a.data();\n  \
    \      int m = (int)a.size();\n#if defined(__x86_64__) || defined(_M_X64)\n  \
    \      if (m >= dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2())\
    \ {\n            dynamic_bitset_detail::xor_assign_avx2(p, q, m);\n          \
    \  normalize();\n            return *this;\n        }\n#endif\n        for (int\
    \ i = 0; i < m; ++i) p[i] ^= q[i];\n        normalize();\n        return *this;\n\
    \    }\n\n    friend DynamicBitset operator&(DynamicBitset l, const DynamicBitset\
    \ &r) { return l &= r; }\n    friend DynamicBitset operator|(DynamicBitset l,\
    \ const DynamicBitset &r) { return l |= r; }\n    friend DynamicBitset operator^(DynamicBitset\
    \ l, const DynamicBitset &r) { return l ^= r; }\n\n    DynamicBitset &operator<<=(int\
    \ s) {\n        if (s <= 0 || n == 0) return *this;\n        if (s >= n) {\n \
    \           reset();\n            return *this;\n        }\n        if (s == 1)\
    \ {\n            Word carry = 0;\n            for (int i = 0; i < (int)a.size();\
    \ ++i) {\n                Word next = a[i] >> (B - 1);\n                a[i] =\
    \ (a[i] << 1) | carry;\n                carry = next;\n            }\n       \
    \     normalize();\n            return *this;\n        }\n        int m = (int)a.size();\n\
    \        int block = s >> 6;\n        int rem = s & 63;\n        if (rem == 0)\
    \ {\n            memmove(a.data() + block, a.data(), sizeof(Word) * (m - block));\n\
    \        } else {\n            for (int i = m - 1; i > block; --i) {\n       \
    \         a[i] = (a[i - block] << rem) | (a[i - block - 1] >> (B - rem));\n  \
    \          }\n            a[block] = a[0] << rem;\n        }\n        fill(a.begin(),\
    \ a.begin() + block, 0);\n        normalize();\n        return *this;\n    }\n\
    \    DynamicBitset &operator>>=(int s) {\n        if (s <= 0 || n == 0) return\
    \ *this;\n        if (s >= n) {\n            reset();\n            return *this;\n\
    \        }\n        if (s == 1) {\n            int m = (int)a.size();\n      \
    \      for (int i = 0; i < m; ++i) {\n                Word next = i + 1 < m ?\
    \ (a[i + 1] << (B - 1)) : 0;\n                a[i] = (a[i] >> 1) | next;\n   \
    \         }\n            normalize();\n            return *this;\n        }\n\
    \        int m = (int)a.size();\n        int block = s >> 6;\n        int rem\
    \ = s & 63;\n        if (rem == 0) {\n            memmove(a.data(), a.data() +\
    \ block, sizeof(Word) * (m - block));\n        } else {\n            int last\
    \ = m - block - 1;\n            for (int i = 0; i < last; ++i) {\n           \
    \     a[i] = (a[i + block] >> rem) | (a[i + block + 1] << (B - rem));\n      \
    \      }\n            a[last] = a[m - 1] >> rem;\n        }\n        fill(a.begin()\
    \ + (m - block), a.end(), 0);\n        normalize();\n        return *this;\n \
    \   }\n\n    friend DynamicBitset operator<<(DynamicBitset l, int s) { return\
    \ l <<= s; }\n    friend DynamicBitset operator>>(DynamicBitset l, int s) { return\
    \ l >>= s; }\n};\n\n/**\n * @brief \u52D5\u7684bitset(Dynamic Bitset)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/dynamic_bitset.cpp
  requiredBy: []
  timestamp: '2026-03-22 13:44:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0275_dynamic_bitset.test.cpp
  - test/aoj_alds1_14_b_dynamic_bitset.test.cpp
  - test/yosupo_aplusb_dynamic_bitset.test.cpp
date: 2026-03-22
documentation_of: datastructure/dynamic_bitset.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "\u52D5\u7684bitset(Dynamic Bitset)"
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
- `int find_last() const`
  最後に立っている bit の位置を返す。なければ `-1`
- `int find_next(int k) const`
  `k` より右で最初に立っている bit の位置を返す。なければ `-1`
- `int find_prev(int k) const`
  `k` より左で最初に立っている bit の位置を返す。なければ `-1`
- `bs &= other`, `bs |= other`, `bs ^= other`
  bitset 同士の演算をその場で行う
- `bs << s`, `bs >> s`, `bs <<= s`, `bs >>= s`
  shift する

## 使い方
長さが同じ bitset 同士で演算する。
`find_first`, `find_next` を使うと立っている bit だけを前から走査できる。
`find_last`, `find_prev` を使うと後ろからも走査できる。

