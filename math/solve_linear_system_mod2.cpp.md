---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/dynamic_bitset.cpp
    title: "\u52D5\u7684bitset(Dynamic Bitset)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_solve_linear_system_mod2.test.cpp
    title: test/yosupo_aplusb_solve_linear_system_mod2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_system_of_linear_equations_mod_2.test.cpp
    title: test/yosupo_system_of_linear_equations_mod_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "mod 2\u306E\u9023\u7ACB\u4E00\u6B21\u65B9\u7A0B\u5F0F(\u57FA\u5E95\
      \u30FB\u7279\u6B8A\u89E3)"
    links: []
  bundledCode: "#line 1 \"math/solve_linear_system_mod2.cpp\"\n\n\n\n#line 1 \"datastructure/dynamic_bitset.cpp\"\
    \n\n\n\n#if defined(__x86_64__) || defined(_M_X64)\n#include <immintrin.h>\n#endif\n\
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
    \ &r) { l &= r; return l; }\n    friend DynamicBitset operator|(DynamicBitset\
    \ l, const DynamicBitset &r) { l |= r; return l; }\n    friend DynamicBitset operator^(DynamicBitset\
    \ l, const DynamicBitset &r) { l ^= r; return l; }\n\n    DynamicBitset &operator<<=(int\
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
    \   }\n\n    DynamicBitset &or_shift_left(int s) {\n        if (s <= 0 || s >=\
    \ n) return *this;\n        int m = (int)a.size();\n        int block = s >> 6;\n\
    \        int rem = s & 63;\n        if (rem == 0) {\n            for (int i =\
    \ m - 1; i >= block; --i) a[i] |= a[i - block];\n        } else {\n          \
    \  for (int i = m - 1; i > block; --i) {\n                a[i] |= (a[i - block]\
    \ << rem) | (a[i - block - 1] >> (B - rem));\n            }\n            a[block]\
    \ |= a[0] << rem;\n        }\n        normalize();\n        return *this;\n  \
    \  }\n\n    DynamicBitset &or_shift_right(int s) {\n        if (s <= 0 || s >=\
    \ n) return *this;\n        int m = (int)a.size();\n        int block = s >> 6;\n\
    \        int rem = s & 63;\n        if (rem == 0) {\n            for (int i =\
    \ 0; i < m - block; ++i) a[i] |= a[i + block];\n        } else {\n           \
    \ int last = m - block - 1;\n            for (int i = 0; i < last; ++i) {\n  \
    \              a[i] |= (a[i + block] >> rem) | (a[i + block + 1] << (B - rem));\n\
    \            }\n            a[last] |= a[m - 1] >> rem;\n        }\n        return\
    \ *this;\n    }\n\n    friend DynamicBitset operator<<(DynamicBitset l, int s)\
    \ { l <<= s; return l; }\n    friend DynamicBitset operator>>(DynamicBitset l,\
    \ int s) { l >>= s; return l; }\n};\n\n/**\n * @brief \u52D5\u7684bitset(Dynamic\
    \ Bitset)\n */\n\n\n#line 5 \"math/solve_linear_system_mod2.cpp\"\n\nstruct LinearSystemSolutionMod2\
    \ {\n    int rank;\n    DynamicBitset particular;\n    vector<DynamicBitset> basis;\n\
    };\n\noptional<LinearSystemSolutionMod2> solve_linear_system_mod2(\n    vector<DynamicBitset>\
    \ a, DynamicBitset b, int variables = -1) {\n    int n = (int)a.size();\n    assert(variables\
    \ >= -1 && b.size() == n);\n    int m = variables < 0 ? (n ? a[0].size() : 0)\
    \ : variables;\n    for (const auto& row : a) assert(row.size() == m);\n    vector<int>\
    \ pivot, where(m, -1);\n    int rank = 0;\n    for (int col = 0; col < m && rank\
    \ < n; ++col) {\n        int row = rank;\n        while (row < n && !a[row].test(col))\
    \ ++row;\n        if (row == n) continue;\n        swap(a[row], a[rank]);\n  \
    \      bool value = b.test(row);\n        b.assign(row, b.test(rank));\n     \
    \   b.assign(rank, value);\n        for (int i = 0; i < n; ++i) {\n          \
    \  if (i == rank || !a[i].test(col)) continue;\n            a[i] ^= a[rank];\n\
    \            if (value) b.flip(i);\n        }\n        where[col] = rank++;\n\
    \        pivot.push_back(col);\n    }\n    for (int i = rank; i < n; ++i) if (b.test(i))\
    \ return nullopt;\n\n    LinearSystemSolutionMod2 result{rank, DynamicBitset(m),\
    \ {}};\n    for (int i = 0; i < rank; ++i) result.particular.assign(pivot[i],\
    \ b.test(i));\n    result.basis.reserve(m - rank);\n    for (int col = 0; col\
    \ < m; ++col) {\n        if (where[col] != -1) continue;\n        DynamicBitset\
    \ v(m);\n        v.set(col);\n        for (int i = 0; i < rank; ++i) v.assign(pivot[i],\
    \ a[i].test(col));\n        result.basis.push_back(std::move(v));\n    }\n   \
    \ return result;\n}\n\n\n\n/**\n * @brief mod 2\u306E\u9023\u7ACB\u4E00\u6B21\u65B9\
    \u7A0B\u5F0F(\u57FA\u5E95\u30FB\u7279\u6B8A\u89E3)\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_MATH_SOLVE_LINEAR_SYSTEM_MOD2_CPP\n#define FIRIEXP_LIBRARY_MATH_SOLVE_LINEAR_SYSTEM_MOD2_CPP\n\
    \n#include \"../datastructure/dynamic_bitset.cpp\"\n\nstruct LinearSystemSolutionMod2\
    \ {\n    int rank;\n    DynamicBitset particular;\n    vector<DynamicBitset> basis;\n\
    };\n\noptional<LinearSystemSolutionMod2> solve_linear_system_mod2(\n    vector<DynamicBitset>\
    \ a, DynamicBitset b, int variables = -1) {\n    int n = (int)a.size();\n    assert(variables\
    \ >= -1 && b.size() == n);\n    int m = variables < 0 ? (n ? a[0].size() : 0)\
    \ : variables;\n    for (const auto& row : a) assert(row.size() == m);\n    vector<int>\
    \ pivot, where(m, -1);\n    int rank = 0;\n    for (int col = 0; col < m && rank\
    \ < n; ++col) {\n        int row = rank;\n        while (row < n && !a[row].test(col))\
    \ ++row;\n        if (row == n) continue;\n        swap(a[row], a[rank]);\n  \
    \      bool value = b.test(row);\n        b.assign(row, b.test(rank));\n     \
    \   b.assign(rank, value);\n        for (int i = 0; i < n; ++i) {\n          \
    \  if (i == rank || !a[i].test(col)) continue;\n            a[i] ^= a[rank];\n\
    \            if (value) b.flip(i);\n        }\n        where[col] = rank++;\n\
    \        pivot.push_back(col);\n    }\n    for (int i = rank; i < n; ++i) if (b.test(i))\
    \ return nullopt;\n\n    LinearSystemSolutionMod2 result{rank, DynamicBitset(m),\
    \ {}};\n    for (int i = 0; i < rank; ++i) result.particular.assign(pivot[i],\
    \ b.test(i));\n    result.basis.reserve(m - rank);\n    for (int col = 0; col\
    \ < m; ++col) {\n        if (where[col] != -1) continue;\n        DynamicBitset\
    \ v(m);\n        v.set(col);\n        for (int i = 0; i < rank; ++i) v.assign(pivot[i],\
    \ a[i].test(col));\n        result.basis.push_back(std::move(v));\n    }\n   \
    \ return result;\n}\n\n#endif\n\n/**\n * @brief mod 2\u306E\u9023\u7ACB\u4E00\u6B21\
    \u65B9\u7A0B\u5F0F(\u57FA\u5E95\u30FB\u7279\u6B8A\u89E3)\n */\n"
  dependsOn:
  - datastructure/dynamic_bitset.cpp
  isVerificationFile: false
  path: math/solve_linear_system_mod2.cpp
  requiredBy: []
  timestamp: '2026-10-12 01:24:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_system_of_linear_equations_mod_2.test.cpp
  - test/yosupo_aplusb_solve_linear_system_mod2.test.cpp
documentation_of: math/solve_linear_system_mod2.cpp
layout: document
title: "mod 2\u306E\u9023\u7ACB\u4E00\u6B21\u65B9\u7A0B\u5F0F(\u57FA\u5E95\u30FB\u7279\
  \u6B8A\u89E3)"
---

## 説明
mod 2 の連立一次方程式について、同次方程式 $Av=0$ の解空間の基底を求める。
$Ax=b$ の特殊解も1つ求め、基底と合わせてすべての解を表せる。
係数行を `DynamicBitset` で持ち、64 bit ごとの XOR で消去する。

## できること
- `optional<LinearSystemSolutionMod2> solve_linear_system_mod2(vector<DynamicBitset> a, DynamicBitset b, int variables = -1)`
  基底と特殊解を返す。解がなければ `nullopt`
- `LinearSystemSolutionMod2::rank`
  係数行列の階数
- `LinearSystemSolutionMod2::particular`
  $Ax=b$ を満たす長さ $M$ の `DynamicBitset`
- `LinearSystemSolutionMod2::basis`
  $Av=0$ を満たす、互いに一次独立な長さ $M$ の `DynamicBitset` を $M-\mathrm{rank}$ 本持つ

## 使い方
`a` は $N$ 行 $M$ 列、`b` は長さ $N$ とする。列 $j$ の値は各行の `test(j)` に対応する。
すべての解は、`particular` と `basis` から任意に選んだベクトルの XOR で表せる。

```cpp
vector<DynamicBitset> a(1, DynamicBitset(2));
a[0].set(0);
a[0].set(1);
DynamicBitset b(1, true);
auto solution = solve_linear_system_mod2(a, b);
```

この例は $x_0+x_1=1\pmod 2$ を解く。
入力を保持する場合はそのまま渡し、不要な行列と右辺は `std::move` で渡せる。
行数が $0$ の場合、変数数は `variables` で指定する。省略時は $0$ とする。行数が正で第3引数を指定する場合は、列数と一致させる。

## 実装上の補足
$N$ 行 $M$ 列の最悪計算量は、時間 $O(NM\lceil M/64\rceil+M^2+N)$。
入力コピーと返却値を含む領域は $O((N+M)\lceil M/64\rceil+N+M)$。
