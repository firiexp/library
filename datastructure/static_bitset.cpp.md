---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0275_static_bitset.test.cpp
    title: test/aoj0275_static_bitset.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_static_bitset.test.cpp
    title: test/yosupo_aplusb_static_bitset.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u56FA\u5B9A\u9577bitset(Static Bitset)"
    links: []
  bundledCode: "#line 1 \"datastructure/static_bitset.cpp\"\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n#include <immintrin.h>\n#endif\n\nusing namespace std;\n\
    \nnamespace static_bitset_detail {\nusing Word = unsigned long long;\nconstexpr\
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
    avx2\");\n    return cached;\n}\n#endif\n}  // namespace static_bitset_detail\n\
    \ntemplate<int N>\nclass StaticBitset {\n    static_assert(N >= 0);\n    static\
    \ constexpr int B = 64;\n    static constexpr int M = (N + B - 1) >> 6;\n    using\
    \ Word = unsigned long long;\n\n    Word a[M > 0 ? M : 1];\n\n    static int popcount(Word\
    \ x) {\n        return __builtin_popcountll(x);\n    }\n    static int ctz(Word\
    \ x) {\n        return __builtin_ctzll(x);\n    }\n    static int clz(Word x)\
    \ {\n        return __builtin_clzll(x);\n    }\n    static constexpr Word tail_mask()\
    \ {\n        return N % B ? ((1ULL << (N % B)) - 1) : ~0ULL;\n    }\n    void\
    \ normalize() {\n        if constexpr (M > 0) a[M - 1] &= tail_mask();\n    }\n\
    \npublic:\n    explicit StaticBitset(bool x = false) : a{} {\n        if (x) set();\n\
    \    }\n\n    int size() const { return N; }\n    bool empty() const { return\
    \ N == 0; }\n\n    void reset() {\n        fill(a, a + M, 0);\n    }\n    void\
    \ set() {\n        fill(a, a + M, ~0ULL);\n        normalize();\n    }\n    void\
    \ flip() {\n        for (Word &x : a) x = ~x;\n        normalize();\n    }\n\n\
    \    bool test(int k) const {\n        return (a[k >> 6] >> (k & 63)) & 1ULL;\n\
    \    }\n    void set(int k) {\n        a[k >> 6] |= 1ULL << (k & 63);\n    }\n\
    \    void reset(int k) {\n        a[k >> 6] &= ~(1ULL << (k & 63));\n    }\n \
    \   void flip(int k) {\n        a[k >> 6] ^= 1ULL << (k & 63);\n    }\n    void\
    \ assign(int k, bool x) {\n        if (x) set(k);\n        else reset(k);\n  \
    \  }\n\n    bool any() const {\n        const Word *p = a;\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n        if constexpr (M >= static_bitset_detail::avx2_threshold_words)\
    \ {\n            if (static_bitset_detail::has_avx2()) return static_bitset_detail::any_avx2(p,\
    \ M);\n        }\n#endif\n        for (int i = 0; i < M; ++i) {\n            if\
    \ (p[i]) return true;\n        }\n        return false;\n    }\n    bool none()\
    \ const { return !any(); }\n    bool all() const {\n        if constexpr (M ==\
    \ 0) return true;\n        const Word *p = a;\n#if defined(__x86_64__) || defined(_M_X64)\n\
    \        if constexpr (M > 1 + static_bitset_detail::avx2_threshold_words) {\n\
    \            if (static_bitset_detail::has_avx2()) {\n                if (!static_bitset_detail::all_full_words_avx2(p,\
    \ M - 1)) return false;\n                return p[M - 1] == tail_mask();\n   \
    \         }\n        }\n#endif\n        for (int i = 0; i + 1 < M; ++i) {\n  \
    \          if (p[i] != ~0ULL) return false;\n        }\n        return p[M - 1]\
    \ == tail_mask();\n    }\n    int count() const {\n        const Word *p = a;\n\
    \        int res = 0;\n        int i = 0;\n        for (; i + 4 <= M; i += 4)\
    \ {\n            res += popcount(p[i + 0]) + popcount(p[i + 1]) + popcount(p[i\
    \ + 2]) + popcount(p[i + 3]);\n        }\n        for (; i < M; ++i) res += popcount(p[i]);\n\
    \        return res;\n    }\n\n    int find_first() const {\n        const Word\
    \ *p = a;\n        for (int i = 0; i < M; ++i) {\n            if (p[i]) return\
    \ (i << 6) + ctz(p[i]);\n        }\n        return -1;\n    }\n    int find_last()\
    \ const {\n        const Word *p = a;\n        for (int i = M - 1; i >= 0; --i)\
    \ {\n            if (p[i]) return (i << 6) + (B - 1 - clz(p[i]));\n        }\n\
    \        return -1;\n    }\n    int find_next(int k) const {\n        ++k;\n \
    \       if (k >= N) return -1;\n        const Word *p = a;\n        int i = k\
    \ >> 6;\n        Word x = p[i] & (~0ULL << (k & 63));\n        if (x) return (i\
    \ << 6) + ctz(x);\n        for (++i; i < M; ++i) {\n            if (p[i]) return\
    \ (i << 6) + ctz(p[i]);\n        }\n        return -1;\n    }\n    int find_prev(int\
    \ k) const {\n        --k;\n        if (k < 0) return -1;\n        const Word\
    \ *p = a;\n        int i = k >> 6;\n        int rem = k & 63;\n        Word mask\
    \ = rem == B - 1 ? ~0ULL : ((1ULL << (rem + 1)) - 1);\n        Word x = p[i] &\
    \ mask;\n        if (x) return (i << 6) + (B - 1 - clz(x));\n        for (--i;\
    \ i >= 0; --i) {\n            if (p[i]) return (i << 6) + (B - 1 - clz(p[i]));\n\
    \        }\n        return -1;\n    }\n\n    StaticBitset &operator&=(const StaticBitset\
    \ &r) {\n        Word *p = a;\n        const Word *q = r.a;\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n        if constexpr (M >= static_bitset_detail::avx2_threshold_words)\
    \ {\n            if (static_bitset_detail::has_avx2()) {\n                static_bitset_detail::and_assign_avx2(p,\
    \ q, M);\n                return *this;\n            }\n        }\n#endif\n  \
    \      for (int i = 0; i < M; ++i) p[i] &= q[i];\n        return *this;\n    }\n\
    \    StaticBitset &operator|=(const StaticBitset &r) {\n        Word *p = a;\n\
    \        const Word *q = r.a;\n#if defined(__x86_64__) || defined(_M_X64)\n  \
    \      if constexpr (M >= static_bitset_detail::avx2_threshold_words) {\n    \
    \        if (static_bitset_detail::has_avx2()) {\n                static_bitset_detail::or_assign_avx2(p,\
    \ q, M);\n                return *this;\n            }\n        }\n#endif\n  \
    \      for (int i = 0; i < M; ++i) p[i] |= q[i];\n        return *this;\n    }\n\
    \    StaticBitset &operator^=(const StaticBitset &r) {\n        Word *p = a;\n\
    \        const Word *q = r.a;\n#if defined(__x86_64__) || defined(_M_X64)\n  \
    \      if constexpr (M >= static_bitset_detail::avx2_threshold_words) {\n    \
    \        if (static_bitset_detail::has_avx2()) {\n                static_bitset_detail::xor_assign_avx2(p,\
    \ q, M);\n                normalize();\n                return *this;\n      \
    \      }\n        }\n#endif\n        for (int i = 0; i < M; ++i) p[i] ^= q[i];\n\
    \        normalize();\n        return *this;\n    }\n\n    friend StaticBitset\
    \ operator&(StaticBitset l, const StaticBitset &r) { return l &= r; }\n    friend\
    \ StaticBitset operator|(StaticBitset l, const StaticBitset &r) { return l |=\
    \ r; }\n    friend StaticBitset operator^(StaticBitset l, const StaticBitset &r)\
    \ { return l ^= r; }\n\n    StaticBitset &operator<<=(int s) {\n        if (s\
    \ <= 0 || N == 0) return *this;\n        if (s >= N) {\n            reset();\n\
    \            return *this;\n        }\n        if (s == 1) {\n            Word\
    \ carry = 0;\n            for (int i = 0; i < M; ++i) {\n                Word\
    \ next = a[i] >> (B - 1);\n                a[i] = (a[i] << 1) | carry;\n     \
    \           carry = next;\n            }\n            normalize();\n         \
    \   return *this;\n        }\n        int block = s >> 6;\n        int rem = s\
    \ & 63;\n        if (rem == 0) {\n            memmove(a + block, a, sizeof(Word)\
    \ * (M - block));\n        } else {\n            for (int i = M - 1; i > block;\
    \ --i) {\n                a[i] = (a[i - block] << rem) | (a[i - block - 1] >>\
    \ (B - rem));\n            }\n            a[block] = a[0] << rem;\n        }\n\
    \        fill(a, a + block, 0);\n        normalize();\n        return *this;\n\
    \    }\n    StaticBitset &operator>>=(int s) {\n        if (s <= 0 || N == 0)\
    \ return *this;\n        if (s >= N) {\n            reset();\n            return\
    \ *this;\n        }\n        if (s == 1) {\n            for (int i = 0; i < M;\
    \ ++i) {\n                Word next = i + 1 < M ? (a[i + 1] << (B - 1)) : 0;\n\
    \                a[i] = (a[i] >> 1) | next;\n            }\n            normalize();\n\
    \            return *this;\n        }\n        int block = s >> 6;\n        int\
    \ rem = s & 63;\n        if (rem == 0) {\n            memmove(a, a + block, sizeof(Word)\
    \ * (M - block));\n        } else {\n            int last = M - block - 1;\n \
    \           for (int i = 0; i < last; ++i) {\n                a[i] = (a[i + block]\
    \ >> rem) | (a[i + block + 1] << (B - rem));\n            }\n            a[last]\
    \ = a[M - 1] >> rem;\n        }\n        fill(a + (M - block), a + M, 0);\n  \
    \      normalize();\n        return *this;\n    }\n\n    friend StaticBitset operator<<(StaticBitset\
    \ l, int s) { return l <<= s; }\n    friend StaticBitset operator>>(StaticBitset\
    \ l, int s) { return l >>= s; }\n};\n\n/**\n * @brief \u56FA\u5B9A\u9577bitset(Static\
    \ Bitset)\n */\n"
  code: "#if defined(__x86_64__) || defined(_M_X64)\n#include <immintrin.h>\n#endif\n\
    \nusing namespace std;\n\nnamespace static_bitset_detail {\nusing Word = unsigned\
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
    avx2\");\n    return cached;\n}\n#endif\n}  // namespace static_bitset_detail\n\
    \ntemplate<int N>\nclass StaticBitset {\n    static_assert(N >= 0);\n    static\
    \ constexpr int B = 64;\n    static constexpr int M = (N + B - 1) >> 6;\n    using\
    \ Word = unsigned long long;\n\n    Word a[M > 0 ? M : 1];\n\n    static int popcount(Word\
    \ x) {\n        return __builtin_popcountll(x);\n    }\n    static int ctz(Word\
    \ x) {\n        return __builtin_ctzll(x);\n    }\n    static int clz(Word x)\
    \ {\n        return __builtin_clzll(x);\n    }\n    static constexpr Word tail_mask()\
    \ {\n        return N % B ? ((1ULL << (N % B)) - 1) : ~0ULL;\n    }\n    void\
    \ normalize() {\n        if constexpr (M > 0) a[M - 1] &= tail_mask();\n    }\n\
    \npublic:\n    explicit StaticBitset(bool x = false) : a{} {\n        if (x) set();\n\
    \    }\n\n    int size() const { return N; }\n    bool empty() const { return\
    \ N == 0; }\n\n    void reset() {\n        fill(a, a + M, 0);\n    }\n    void\
    \ set() {\n        fill(a, a + M, ~0ULL);\n        normalize();\n    }\n    void\
    \ flip() {\n        for (Word &x : a) x = ~x;\n        normalize();\n    }\n\n\
    \    bool test(int k) const {\n        return (a[k >> 6] >> (k & 63)) & 1ULL;\n\
    \    }\n    void set(int k) {\n        a[k >> 6] |= 1ULL << (k & 63);\n    }\n\
    \    void reset(int k) {\n        a[k >> 6] &= ~(1ULL << (k & 63));\n    }\n \
    \   void flip(int k) {\n        a[k >> 6] ^= 1ULL << (k & 63);\n    }\n    void\
    \ assign(int k, bool x) {\n        if (x) set(k);\n        else reset(k);\n  \
    \  }\n\n    bool any() const {\n        const Word *p = a;\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n        if constexpr (M >= static_bitset_detail::avx2_threshold_words)\
    \ {\n            if (static_bitset_detail::has_avx2()) return static_bitset_detail::any_avx2(p,\
    \ M);\n        }\n#endif\n        for (int i = 0; i < M; ++i) {\n            if\
    \ (p[i]) return true;\n        }\n        return false;\n    }\n    bool none()\
    \ const { return !any(); }\n    bool all() const {\n        if constexpr (M ==\
    \ 0) return true;\n        const Word *p = a;\n#if defined(__x86_64__) || defined(_M_X64)\n\
    \        if constexpr (M > 1 + static_bitset_detail::avx2_threshold_words) {\n\
    \            if (static_bitset_detail::has_avx2()) {\n                if (!static_bitset_detail::all_full_words_avx2(p,\
    \ M - 1)) return false;\n                return p[M - 1] == tail_mask();\n   \
    \         }\n        }\n#endif\n        for (int i = 0; i + 1 < M; ++i) {\n  \
    \          if (p[i] != ~0ULL) return false;\n        }\n        return p[M - 1]\
    \ == tail_mask();\n    }\n    int count() const {\n        const Word *p = a;\n\
    \        int res = 0;\n        int i = 0;\n        for (; i + 4 <= M; i += 4)\
    \ {\n            res += popcount(p[i + 0]) + popcount(p[i + 1]) + popcount(p[i\
    \ + 2]) + popcount(p[i + 3]);\n        }\n        for (; i < M; ++i) res += popcount(p[i]);\n\
    \        return res;\n    }\n\n    int find_first() const {\n        const Word\
    \ *p = a;\n        for (int i = 0; i < M; ++i) {\n            if (p[i]) return\
    \ (i << 6) + ctz(p[i]);\n        }\n        return -1;\n    }\n    int find_last()\
    \ const {\n        const Word *p = a;\n        for (int i = M - 1; i >= 0; --i)\
    \ {\n            if (p[i]) return (i << 6) + (B - 1 - clz(p[i]));\n        }\n\
    \        return -1;\n    }\n    int find_next(int k) const {\n        ++k;\n \
    \       if (k >= N) return -1;\n        const Word *p = a;\n        int i = k\
    \ >> 6;\n        Word x = p[i] & (~0ULL << (k & 63));\n        if (x) return (i\
    \ << 6) + ctz(x);\n        for (++i; i < M; ++i) {\n            if (p[i]) return\
    \ (i << 6) + ctz(p[i]);\n        }\n        return -1;\n    }\n    int find_prev(int\
    \ k) const {\n        --k;\n        if (k < 0) return -1;\n        const Word\
    \ *p = a;\n        int i = k >> 6;\n        int rem = k & 63;\n        Word mask\
    \ = rem == B - 1 ? ~0ULL : ((1ULL << (rem + 1)) - 1);\n        Word x = p[i] &\
    \ mask;\n        if (x) return (i << 6) + (B - 1 - clz(x));\n        for (--i;\
    \ i >= 0; --i) {\n            if (p[i]) return (i << 6) + (B - 1 - clz(p[i]));\n\
    \        }\n        return -1;\n    }\n\n    StaticBitset &operator&=(const StaticBitset\
    \ &r) {\n        Word *p = a;\n        const Word *q = r.a;\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n        if constexpr (M >= static_bitset_detail::avx2_threshold_words)\
    \ {\n            if (static_bitset_detail::has_avx2()) {\n                static_bitset_detail::and_assign_avx2(p,\
    \ q, M);\n                return *this;\n            }\n        }\n#endif\n  \
    \      for (int i = 0; i < M; ++i) p[i] &= q[i];\n        return *this;\n    }\n\
    \    StaticBitset &operator|=(const StaticBitset &r) {\n        Word *p = a;\n\
    \        const Word *q = r.a;\n#if defined(__x86_64__) || defined(_M_X64)\n  \
    \      if constexpr (M >= static_bitset_detail::avx2_threshold_words) {\n    \
    \        if (static_bitset_detail::has_avx2()) {\n                static_bitset_detail::or_assign_avx2(p,\
    \ q, M);\n                return *this;\n            }\n        }\n#endif\n  \
    \      for (int i = 0; i < M; ++i) p[i] |= q[i];\n        return *this;\n    }\n\
    \    StaticBitset &operator^=(const StaticBitset &r) {\n        Word *p = a;\n\
    \        const Word *q = r.a;\n#if defined(__x86_64__) || defined(_M_X64)\n  \
    \      if constexpr (M >= static_bitset_detail::avx2_threshold_words) {\n    \
    \        if (static_bitset_detail::has_avx2()) {\n                static_bitset_detail::xor_assign_avx2(p,\
    \ q, M);\n                normalize();\n                return *this;\n      \
    \      }\n        }\n#endif\n        for (int i = 0; i < M; ++i) p[i] ^= q[i];\n\
    \        normalize();\n        return *this;\n    }\n\n    friend StaticBitset\
    \ operator&(StaticBitset l, const StaticBitset &r) { return l &= r; }\n    friend\
    \ StaticBitset operator|(StaticBitset l, const StaticBitset &r) { return l |=\
    \ r; }\n    friend StaticBitset operator^(StaticBitset l, const StaticBitset &r)\
    \ { return l ^= r; }\n\n    StaticBitset &operator<<=(int s) {\n        if (s\
    \ <= 0 || N == 0) return *this;\n        if (s >= N) {\n            reset();\n\
    \            return *this;\n        }\n        if (s == 1) {\n            Word\
    \ carry = 0;\n            for (int i = 0; i < M; ++i) {\n                Word\
    \ next = a[i] >> (B - 1);\n                a[i] = (a[i] << 1) | carry;\n     \
    \           carry = next;\n            }\n            normalize();\n         \
    \   return *this;\n        }\n        int block = s >> 6;\n        int rem = s\
    \ & 63;\n        if (rem == 0) {\n            memmove(a + block, a, sizeof(Word)\
    \ * (M - block));\n        } else {\n            for (int i = M - 1; i > block;\
    \ --i) {\n                a[i] = (a[i - block] << rem) | (a[i - block - 1] >>\
    \ (B - rem));\n            }\n            a[block] = a[0] << rem;\n        }\n\
    \        fill(a, a + block, 0);\n        normalize();\n        return *this;\n\
    \    }\n    StaticBitset &operator>>=(int s) {\n        if (s <= 0 || N == 0)\
    \ return *this;\n        if (s >= N) {\n            reset();\n            return\
    \ *this;\n        }\n        if (s == 1) {\n            for (int i = 0; i < M;\
    \ ++i) {\n                Word next = i + 1 < M ? (a[i + 1] << (B - 1)) : 0;\n\
    \                a[i] = (a[i] >> 1) | next;\n            }\n            normalize();\n\
    \            return *this;\n        }\n        int block = s >> 6;\n        int\
    \ rem = s & 63;\n        if (rem == 0) {\n            memmove(a, a + block, sizeof(Word)\
    \ * (M - block));\n        } else {\n            int last = M - block - 1;\n \
    \           for (int i = 0; i < last; ++i) {\n                a[i] = (a[i + block]\
    \ >> rem) | (a[i + block + 1] << (B - rem));\n            }\n            a[last]\
    \ = a[M - 1] >> rem;\n        }\n        fill(a + (M - block), a + M, 0);\n  \
    \      normalize();\n        return *this;\n    }\n\n    friend StaticBitset operator<<(StaticBitset\
    \ l, int s) { return l <<= s; }\n    friend StaticBitset operator>>(StaticBitset\
    \ l, int s) { return l >>= s; }\n};\n\n/**\n * @brief \u56FA\u5B9A\u9577bitset(Static\
    \ Bitset)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/static_bitset.cpp
  requiredBy: []
  timestamp: '2026-03-22 13:44:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0275_static_bitset.test.cpp
  - test/yosupo_aplusb_static_bitset.test.cpp
date: 2026-03-22
documentation_of: datastructure/static_bitset.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Static Bitset
---

## 説明
長さがコンパイル時定数の bitset。
`uint64_t` 単位で持ち、集合演算、shift、立っている bit の走査を扱う。

## できること
- `StaticBitset<N> bs(bool x = false)`
  長さ `N` の bitset を作る。`x = true` なら全 bit を 1 で初期化する
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
`StaticBitset<2048> bs;` のように長さをテンプレート引数で指定する。
