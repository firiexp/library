---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_pow_of_matrix.test.cpp
    title: test/yosupo_pow_of_matrix.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u56FA\u5B9A\u9577\u6B63\u65B9\u884C\u5217(mint\u5C02\u7528)"
    links: []
  bundledCode: "#line 1 \"util/modint.cpp\"\n\n\n\ntemplate <uint Mod>\nstruct modint\
    \ {\n    uint val;\npublic:\n    static modint raw(int v) { modint x; x.val =\
    \ v; return x; }\n    static constexpr uint get_mod() { return Mod; }\n    static\
    \ constexpr uint M() { return Mod; }\n    modint() : val(0) {}\n    template <class\
    \ T>\n    modint(T v) { ll x = (ll)(v % (ll)(Mod)); if (x < 0) x += Mod; val =\
    \ uint(x); }\n    modint(bool v) { val = ((unsigned int)(v) % Mod); }\n    uint\
    \ &value() noexcept { return val; }\n    const uint &value() const noexcept {\
    \ return val; }\n    modint& operator++() { val++; if (val == Mod) val = 0; return\
    \ *this; }\n    modint& operator--() { if (val == 0) val = Mod; val--; return\
    \ *this; }\n    modint operator++(int) { modint result = *this; ++*this; return\
    \ result; }\n    modint operator--(int) { modint result = *this; --*this; return\
    \ result; }\n    modint& operator+=(const modint& b) { val += b.val; if (val >=\
    \ Mod) val -= Mod; return *this; }\n    modint& operator-=(const modint& b) {\
    \ val -= b.val; if (val >= Mod) val += Mod; return *this; }\n    modint& operator*=(const\
    \ modint& b) { ull z = val; z *= b.val; val = (uint)(z % Mod); return *this; }\n\
    \    modint& operator/=(const modint& b) { return *this = *this * b.inv(); }\n\
    \    modint operator+() const { return *this; }\n    modint operator-() const\
    \ { return modint() - *this; }\n    modint pow(long long n) const { modint x =\
    \ *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n\
    \    modint inv() const { return pow(Mod - 2); }\n    friend modint operator+(const\
    \ modint& a, const modint& b) { return modint(a) += b; }\n    friend modint operator-(const\
    \ modint& a, const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    #define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\n/**\n * @brief modint(\u56FA\u5B9A\
    MOD)\n */\n\n\n#line 2 \"math/squarematrix_mint.cpp\"\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n#include <immintrin.h>\n#endif\n\nnamespace squarematrix_mint_detail\
    \ {\nconstexpr ull mul_max_term = (ull)(MOD - 1) * (MOD - 1);\nconstexpr size_t\
    \ mul_block_size = mul_max_term == 0 ? 1 : size_t(~0ULL / mul_max_term);\nconstexpr\
    \ size_t mul_unroll_size = mul_block_size < 16 ? mul_block_size : 16;\n\nstruct\
    \ DotProductPair {\n    uint first;\n    uint second;\n};\n\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n__attribute__((target(\"avx2\"))) inline ull avx2_hsum_u64x4(__m256i\
    \ v) {\n    alignas(32) ull buf[4];\n    _mm256_store_si256((__m256i *)buf, v);\n\
    \    return buf[0] + buf[1] + buf[2] + buf[3];\n}\n\n__attribute__((target(\"\
    avx2\"))) ull dot_product_raw_avx2(const uint *row, const uint *col, size_t n,\
    \ uint mod) {\n    ull sum = 0;\n    size_t k = 0;\n    for (; k + mul_block_size\
    \ - 1 < n; k += mul_block_size) {\n        ull acc = 0;\n        size_t t = 0;\n\
    \        __m256i acc_even = _mm256_setzero_si256();\n        __m256i acc_odd =\
    \ _mm256_setzero_si256();\n        for (; t + 8 <= mul_block_size; t += 8) {\n\
    \            const __m256i rowv = _mm256_loadu_si256((const __m256i *)(row + k\
    \ + t));\n            const __m256i colv = _mm256_loadu_si256((const __m256i *)(col\
    \ + k + t));\n            acc_even = _mm256_add_epi64(acc_even, _mm256_mul_epu32(rowv,\
    \ colv));\n            const __m256i row_hi = _mm256_srli_epi64(rowv, 32);\n \
    \           const __m256i col_hi = _mm256_srli_epi64(colv, 32);\n            acc_odd\
    \ = _mm256_add_epi64(acc_odd, _mm256_mul_epu32(row_hi, col_hi));\n        }\n\
    \        acc += avx2_hsum_u64x4(acc_even) + avx2_hsum_u64x4(acc_odd);\n      \
    \  for (; t < mul_block_size; ++t) acc += (ull)row[k + t] * col[k + t];\n    \
    \    sum += acc % mod;\n        if (sum >= mod) sum -= mod;\n    }\n    ull acc\
    \ = 0;\n    for (; k < n; ++k) acc += (ull)row[k] * col[k];\n    sum += acc %\
    \ mod;\n    if (sum >= mod) sum -= mod;\n    return uint(sum);\n}\n\n__attribute__((target(\"\
    avx2\"))) DotProductPair dot_product_raw2_avx2(const uint *row, const uint *col0,\
    \ const uint *col1, size_t n, uint mod) {\n    ull sum0 = 0, sum1 = 0;\n    size_t\
    \ k = 0;\n    for (; k + mul_block_size - 1 < n; k += mul_block_size) {\n    \
    \    ull acc0 = 0, acc1 = 0;\n        size_t t = 0;\n        __m256i acc0_even\
    \ = _mm256_setzero_si256();\n        __m256i acc0_odd = _mm256_setzero_si256();\n\
    \        __m256i acc1_even = _mm256_setzero_si256();\n        __m256i acc1_odd\
    \ = _mm256_setzero_si256();\n        for (; t + 8 <= mul_block_size; t += 8) {\n\
    \            const __m256i rowv = _mm256_loadu_si256((const __m256i *)(row + k\
    \ + t));\n            const __m256i col0v = _mm256_loadu_si256((const __m256i\
    \ *)(col0 + k + t));\n            const __m256i col1v = _mm256_loadu_si256((const\
    \ __m256i *)(col1 + k + t));\n            acc0_even = _mm256_add_epi64(acc0_even,\
    \ _mm256_mul_epu32(rowv, col0v));\n            acc1_even = _mm256_add_epi64(acc1_even,\
    \ _mm256_mul_epu32(rowv, col1v));\n            const __m256i row_hi = _mm256_srli_epi64(rowv,\
    \ 32);\n            const __m256i col0_hi = _mm256_srli_epi64(col0v, 32);\n  \
    \          const __m256i col1_hi = _mm256_srli_epi64(col1v, 32);\n           \
    \ acc0_odd = _mm256_add_epi64(acc0_odd, _mm256_mul_epu32(row_hi, col0_hi));\n\
    \            acc1_odd = _mm256_add_epi64(acc1_odd, _mm256_mul_epu32(row_hi, col1_hi));\n\
    \        }\n        acc0 += avx2_hsum_u64x4(acc0_even) + avx2_hsum_u64x4(acc0_odd);\n\
    \        acc1 += avx2_hsum_u64x4(acc1_even) + avx2_hsum_u64x4(acc1_odd);\n   \
    \     for (; t < mul_block_size; ++t) {\n            const ull x = row[k + t];\n\
    \            acc0 += x * col0[k + t];\n            acc1 += x * col1[k + t];\n\
    \        }\n        sum0 += acc0 % mod;\n        if (sum0 >= mod) sum0 -= mod;\n\
    \        sum1 += acc1 % mod;\n        if (sum1 >= mod) sum1 -= mod;\n    }\n \
    \   ull acc0 = 0, acc1 = 0;\n    for (; k < n; ++k) {\n        const ull x = row[k];\n\
    \        acc0 += x * col0[k];\n        acc1 += x * col1[k];\n    }\n    sum0 +=\
    \ acc0 % mod;\n    if (sum0 >= mod) sum0 -= mod;\n    sum1 += acc1 % mod;\n  \
    \  if (sum1 >= mod) sum1 -= mod;\n    return {uint(sum0), uint(sum1)};\n}\n\n\
    inline bool has_avx2() {\n    static const bool cached = __builtin_cpu_supports(\"\
    avx2\");\n    return cached;\n}\n#endif\n\nuint dot_product_raw(const uint *row,\
    \ const uint *col, size_t n, uint mod) {\n#if defined(__x86_64__) || defined(_M_X64)\n\
    \    if (mul_block_size >= 8 && has_avx2()) return dot_product_raw_avx2(row, col,\
    \ n, mod);\n#endif\n    ull sum = 0;\n    size_t k = 0;\n    for (; k + mul_block_size\
    \ - 1 < n; k += mul_block_size) {\n        ull acc = 0;\n        if constexpr\
    \ (mul_unroll_size >= 1) acc += (ull)row[k + 0] * col[k + 0];\n        if constexpr\
    \ (mul_unroll_size >= 2) acc += (ull)row[k + 1] * col[k + 1];\n        if constexpr\
    \ (mul_unroll_size >= 3) acc += (ull)row[k + 2] * col[k + 2];\n        if constexpr\
    \ (mul_unroll_size >= 4) acc += (ull)row[k + 3] * col[k + 3];\n        if constexpr\
    \ (mul_unroll_size >= 5) acc += (ull)row[k + 4] * col[k + 4];\n        if constexpr\
    \ (mul_unroll_size >= 6) acc += (ull)row[k + 5] * col[k + 5];\n        if constexpr\
    \ (mul_unroll_size >= 7) acc += (ull)row[k + 6] * col[k + 6];\n        if constexpr\
    \ (mul_unroll_size >= 8) acc += (ull)row[k + 7] * col[k + 7];\n        if constexpr\
    \ (mul_unroll_size >= 9) acc += (ull)row[k + 8] * col[k + 8];\n        if constexpr\
    \ (mul_unroll_size >= 10) acc += (ull)row[k + 9] * col[k + 9];\n        if constexpr\
    \ (mul_unroll_size >= 11) acc += (ull)row[k + 10] * col[k + 10];\n        if constexpr\
    \ (mul_unroll_size >= 12) acc += (ull)row[k + 11] * col[k + 11];\n        if constexpr\
    \ (mul_unroll_size >= 13) acc += (ull)row[k + 12] * col[k + 12];\n        if constexpr\
    \ (mul_unroll_size >= 14) acc += (ull)row[k + 13] * col[k + 13];\n        if constexpr\
    \ (mul_unroll_size >= 15) acc += (ull)row[k + 14] * col[k + 14];\n        if constexpr\
    \ (mul_unroll_size >= 16) acc += (ull)row[k + 15] * col[k + 15];\n        for\
    \ (size_t t = mul_unroll_size; t < mul_block_size; ++t) {\n            acc +=\
    \ (ull)row[k + t] * col[k + t];\n        }\n        sum += acc % mod;\n      \
    \  if (sum >= mod) sum -= mod;\n    }\n    ull acc = 0;\n    for (; k < n; ++k)\
    \ acc += (ull)row[k] * col[k];\n    sum += acc % mod;\n    if (sum >= mod) sum\
    \ -= mod;\n    return uint(sum);\n}\n\nDotProductPair dot_product_raw2(const uint\
    \ *row, const uint *col0, const uint *col1, size_t n, uint mod) {\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n    if (mul_block_size >= 8 && has_avx2()) return dot_product_raw2_avx2(row,\
    \ col0, col1, n, mod);\n#endif\n    ull sum0 = 0, sum1 = 0;\n    size_t k = 0;\n\
    \    for (; k + mul_block_size - 1 < n; k += mul_block_size) {\n        ull acc0\
    \ = 0, acc1 = 0;\n        if constexpr (mul_unroll_size >= 1) {\n            const\
    \ ull x = row[k + 0];\n            acc0 += x * col0[k + 0];\n            acc1\
    \ += x * col1[k + 0];\n        }\n        if constexpr (mul_unroll_size >= 2)\
    \ {\n            const ull x = row[k + 1];\n            acc0 += x * col0[k + 1];\n\
    \            acc1 += x * col1[k + 1];\n        }\n        if constexpr (mul_unroll_size\
    \ >= 3) {\n            const ull x = row[k + 2];\n            acc0 += x * col0[k\
    \ + 2];\n            acc1 += x * col1[k + 2];\n        }\n        if constexpr\
    \ (mul_unroll_size >= 4) {\n            const ull x = row[k + 3];\n          \
    \  acc0 += x * col0[k + 3];\n            acc1 += x * col1[k + 3];\n        }\n\
    \        if constexpr (mul_unroll_size >= 5) {\n            const ull x = row[k\
    \ + 4];\n            acc0 += x * col0[k + 4];\n            acc1 += x * col1[k\
    \ + 4];\n        }\n        if constexpr (mul_unroll_size >= 6) {\n          \
    \  const ull x = row[k + 5];\n            acc0 += x * col0[k + 5];\n         \
    \   acc1 += x * col1[k + 5];\n        }\n        if constexpr (mul_unroll_size\
    \ >= 7) {\n            const ull x = row[k + 6];\n            acc0 += x * col0[k\
    \ + 6];\n            acc1 += x * col1[k + 6];\n        }\n        if constexpr\
    \ (mul_unroll_size >= 8) {\n            const ull x = row[k + 7];\n          \
    \  acc0 += x * col0[k + 7];\n            acc1 += x * col1[k + 7];\n        }\n\
    \        if constexpr (mul_unroll_size >= 9) {\n            const ull x = row[k\
    \ + 8];\n            acc0 += x * col0[k + 8];\n            acc1 += x * col1[k\
    \ + 8];\n        }\n        if constexpr (mul_unroll_size >= 10) {\n         \
    \   const ull x = row[k + 9];\n            acc0 += x * col0[k + 9];\n        \
    \    acc1 += x * col1[k + 9];\n        }\n        if constexpr (mul_unroll_size\
    \ >= 11) {\n            const ull x = row[k + 10];\n            acc0 += x * col0[k\
    \ + 10];\n            acc1 += x * col1[k + 10];\n        }\n        if constexpr\
    \ (mul_unroll_size >= 12) {\n            const ull x = row[k + 11];\n        \
    \    acc0 += x * col0[k + 11];\n            acc1 += x * col1[k + 11];\n      \
    \  }\n        if constexpr (mul_unroll_size >= 13) {\n            const ull x\
    \ = row[k + 12];\n            acc0 += x * col0[k + 12];\n            acc1 += x\
    \ * col1[k + 12];\n        }\n        if constexpr (mul_unroll_size >= 14) {\n\
    \            const ull x = row[k + 13];\n            acc0 += x * col0[k + 13];\n\
    \            acc1 += x * col1[k + 13];\n        }\n        if constexpr (mul_unroll_size\
    \ >= 15) {\n            const ull x = row[k + 14];\n            acc0 += x * col0[k\
    \ + 14];\n            acc1 += x * col1[k + 14];\n        }\n        if constexpr\
    \ (mul_unroll_size >= 16) {\n            const ull x = row[k + 15];\n        \
    \    acc0 += x * col0[k + 15];\n            acc1 += x * col1[k + 15];\n      \
    \  }\n        for (size_t t = mul_unroll_size; t < mul_block_size; ++t) {\n  \
    \          const ull x = row[k + t];\n            acc0 += x * col0[k + t];\n \
    \           acc1 += x * col1[k + t];\n        }\n        sum0 += acc0 % mod;\n\
    \        if (sum0 >= mod) sum0 -= mod;\n        sum1 += acc1 % mod;\n        if\
    \ (sum1 >= mod) sum1 -= mod;\n    }\n    ull acc0 = 0, acc1 = 0;\n    for (; k\
    \ < n; ++k) {\n        const ull x = row[k];\n        acc0 += x * col0[k];\n \
    \       acc1 += x * col1[k];\n    }\n    sum0 += acc0 % mod;\n    if (sum0 >=\
    \ mod) sum0 -= mod;\n    sum1 += acc1 % mod;\n    if (sum1 >= mod) sum1 -= mod;\n\
    \    return {uint(sum0), uint(sum1)};\n}\n\ntemplate<class Rows>\nvoid transpose_raw(const\
    \ Rows &rows, uint *dst, size_t row_count, size_t col_count, size_t stride) {\n\
    \    for (size_t k = 0; k < row_count; ++k) {\n        const auto *row = rows[k].data();\n\
    \        uint *col = dst + k;\n        for (size_t j = 0; j < col_count; ++j)\
    \ {\n            *col = row[j].value();\n            col += stride;\n        }\n\
    \    }\n}\n} // namespace squarematrix_mint_detail\n\ntemplate<size_t SIZE>\n\
    struct SquareMatrixMint {\n    using T = mint;\n    using ar = array<T, SIZE>;\n\
    \    using mat = array<ar, SIZE>;\n    struct PreparedMul {\n        array<uint,\
    \ SIZE * SIZE> BT;\n    };\n\n    struct MatrixMulScratch : PreparedMul {\n  \
    \      array<uint, SIZE> row;\n    };\n\n    struct VecMulScratch : PreparedMul\
    \ {\n        array<uint, SIZE> res;\n    };\n\n    mat A;\nprivate:\n    void\
    \ mul_assign_prepared_impl(const PreparedMul &prepared, MatrixMulScratch &scratch,\
    \ size_t n, bool clear_unused) {\n        const uint mod = mint::get_mod();\n\
    \        for (size_t i = 0; i < n; ++i) {\n            T *row = A[i].data();\n\
    \            for (size_t j = 0; j < n; ++j) scratch.row[j] = row[j].value();\n\
    \            const uint *col = prepared.BT.data();\n            size_t j = 0;\n\
    \            for (; j + 1 < n; j += 2) {\n                auto dots = squarematrix_mint_detail::dot_product_raw2(scratch.row.data(),\
    \ col, col + SIZE, n, mod);\n                row[j].value() = dots.first;\n  \
    \              row[j + 1].value() = dots.second;\n                col += SIZE\
    \ * 2;\n            }\n            if (j < n) {\n                row[j].value()\
    \ = squarematrix_mint_detail::dot_product_raw(scratch.row.data(), col, n, mod);\n\
    \            }\n            if (clear_unused) {\n                for (size_t j\
    \ = n; j < SIZE; ++j) row[j].value() = 0;\n            }\n        }\n        if\
    \ (clear_unused) {\n            for (size_t i = n; i < SIZE; ++i) {\n        \
    \        for (size_t j = 0; j < SIZE; ++j) A[i][j].value() = 0;\n            }\n\
    \        }\n    }\n\npublic:\n    SquareMatrixMint() {\n        for (size_t i\
    \ = 0; i < SIZE; ++i) {\n            for (size_t j = 0; j < SIZE; ++j) {\n   \
    \             A[i][j] = 0;\n            }\n        }\n    }\n    static SquareMatrixMint\
    \ I(size_t n = SIZE) {\n        SquareMatrixMint X;\n        for (size_t i = 0;\
    \ i < n; ++i) X[i][i] = 1;\n        return X;\n    }\n\n    friend ar &operator*=(ar\
    \ &x, const SquareMatrixMint &Y) {\n        return Y.mul_vec_assign(x);\n    }\n\
    \    friend ar operator*(ar x, const SquareMatrixMint &Y) { return x *= Y; }\n\
    \n    void prepare_mul(PreparedMul &prepared, size_t n = SIZE) const {\n     \
    \   squarematrix_mint_detail::transpose_raw(A, prepared.BT.data(), n, n, SIZE);\n\
    \    }\n\n    void prepare_vec_mul(PreparedMul &prepared, size_t n = SIZE) const\
    \ {\n        prepare_mul(prepared, n);\n    }\n\n    ar &mul_vec_assign(ar &x,\
    \ size_t n = SIZE) const {\n        VecMulScratch scratch;\n        prepare_vec_mul(scratch,\
    \ n);\n        return mul_vec_assign_prepared_impl(x, scratch, n, scratch);\n\
    \    }\n    ar mul_vec(ar x, size_t n = SIZE) const { return mul_vec_assign(x,\
    \ n); }\n    ar &mul_vec_assign(ar &x, VecMulScratch &scratch, size_t n) const\
    \ {\n        prepare_vec_mul(scratch, n);\n        return mul_vec_assign_prepared_impl(x,\
    \ scratch, n, scratch);\n    }\n    ar mul_vec(ar x, VecMulScratch &scratch, size_t\
    \ n) const { return mul_vec_assign(x, scratch, n); }\n    ar &mul_vec_assign_prepared(ar\
    \ &x, VecMulScratch &scratch, size_t n) const {\n        return mul_vec_assign_prepared(x,\
    \ static_cast<const PreparedMul &>(scratch), scratch, n);\n    }\n    ar mul_vec_prepared(ar\
    \ x, VecMulScratch &scratch, size_t n) const {\n        return mul_vec_assign_prepared(x,\
    \ scratch, n);\n    }\n    ar &mul_vec_assign_prepared(ar &x, const PreparedMul\
    \ &prepared, VecMulScratch &scratch, size_t n) const {\n        return mul_vec_assign_prepared_impl(x,\
    \ prepared, n, scratch);\n    }\n    ar mul_vec_prepared(ar x, const PreparedMul\
    \ &prepared, VecMulScratch &scratch, size_t n) const {\n        return mul_vec_assign_prepared(x,\
    \ prepared, scratch, n);\n    }\n\nprivate:\n    ar &mul_vec_assign_prepared_impl(ar\
    \ &x, const PreparedMul &prepared, size_t n, VecMulScratch &scratch) const {\n\
    \        const uint mod = mint::get_mod();\n        for (size_t j = 0; j < n;\
    \ ++j) scratch.res[j] = x[j].value();\n        const uint *col = prepared.BT.data();\n\
    \        size_t j = 0;\n        for (; j + 1 < n; j += 2) {\n            auto\
    \ dots = squarematrix_mint_detail::dot_product_raw2(scratch.res.data(), col, col\
    \ + SIZE, n, mod);\n            x[j].value() = dots.first;\n            x[j +\
    \ 1].value() = dots.second;\n            col += SIZE * 2;\n        }\n       \
    \ if (j < n) {\n            x[j].value() = squarematrix_mint_detail::dot_product_raw(scratch.res.data(),\
    \ col, n, mod);\n        }\n        for (size_t j = n; j < SIZE; ++j) x[j].value()\
    \ = 0;\n        return x;\n    }\n\npublic:\n\n    inline const ar &operator[](int\
    \ k) const { return A.at(k); }\n    inline ar &operator[](int k) { return A.at(k);\
    \ }\n\n    SquareMatrixMint &operator+=(const SquareMatrixMint &B) {\n       \
    \ for (size_t i = 0; i < SIZE; ++i) {\n            for (size_t j = 0; j < SIZE;\
    \ ++j) {\n                A[i][j] += B.A[i][j];\n            }\n        }\n  \
    \      return *this;\n    }\n\n    SquareMatrixMint &operator-=(const SquareMatrixMint\
    \ &B) {\n        for (size_t i = 0; i < SIZE; ++i) {\n            for (size_t\
    \ j = 0; j < SIZE; ++j) {\n                A[i][j] -= B.A[i][j];\n           \
    \ }\n        }\n        return *this;\n    }\n\n    SquareMatrixMint &mul_assign(const\
    \ SquareMatrixMint &B, size_t n = SIZE) {\n        MatrixMulScratch scratch;\n\
    \        return mul_assign(B, scratch, n);\n    }\n    SquareMatrixMint &mul_assign(const\
    \ SquareMatrixMint &B, MatrixMulScratch &scratch, size_t n) {\n        B.prepare_mul(scratch,\
    \ n);\n        return mul_assign_prepared(scratch, n);\n    }\n    SquareMatrixMint\
    \ &mul_assign_prepared(MatrixMulScratch &scratch, size_t n, bool clear_unused\
    \ = true) {\n        return mul_assign_prepared(static_cast<const PreparedMul\
    \ &>(scratch), scratch, n, clear_unused);\n    }\n    SquareMatrixMint &mul_assign_prepared(const\
    \ PreparedMul &prepared, MatrixMulScratch &scratch, size_t n, bool clear_unused\
    \ = true) {\n        mul_assign_prepared_impl(prepared, scratch, n, clear_unused);\n\
    \        return *this;\n    }\n    SquareMatrixMint &operator*=(const SquareMatrixMint\
    \ &B) { return mul_assign(B); }\n\n    SquareMatrixMint pow(ll n, size_t dim =\
    \ SIZE) const {\n        if (n == 0) return I(dim);\n        const ull exp = (ull)n;\n\
    \        MatrixMulScratch scratch;\n        auto binary_pow = [&](ull m) {\n \
    \           SquareMatrixMint a = *this, res = I(dim);\n            while (m >\
    \ 1) {\n                a.prepare_mul(scratch, dim);\n                if (m &\
    \ 1) res.mul_assign_prepared(scratch, dim, false);\n                a.mul_assign_prepared(scratch,\
    \ dim, false);\n                m >>= 1;\n            }\n            a.prepare_mul(scratch,\
    \ dim);\n            res.mul_assign_prepared(scratch, dim, false);\n         \
    \   return res;\n        };\n        if (exp < 8) return binary_pow(exp);\n\n\
    \        constexpr int window_bits = 3;\n        constexpr size_t window_size\
    \ = size_t(1) << (window_bits - 1);\n        struct PowEntry {\n            SquareMatrixMint\
    \ mat;\n            PreparedMul prepared;\n        };\n        array<PowEntry,\
    \ window_size> odd;\n        odd[0].mat = *this;\n        odd[0].mat.prepare_mul(odd[0].prepared,\
    \ dim);\n        if constexpr (window_size > 1) {\n            SquareMatrixMint\
    \ base2 = *this;\n            base2.mul_assign(*this, scratch, dim);\n       \
    \     base2.prepare_mul(scratch, dim);\n            for (size_t i = 1; i < window_size;\
    \ ++i) {\n                odd[i].mat = odd[i - 1].mat;\n                odd[i].mat.mul_assign_prepared(scratch,\
    \ dim, false);\n                odd[i].mat.prepare_mul(odd[i].prepared, dim);\n\
    \            }\n        }\n\n        SquareMatrixMint res;\n        bool started\
    \ = false;\n        for (int bit = 63 - __builtin_clzll(exp); bit >= 0;) {\n \
    \           if (((exp >> bit) & 1ULL) == 0) {\n                if (started) {\n\
    \                    res.prepare_mul(scratch, dim);\n                    res.mul_assign_prepared(scratch,\
    \ dim, false);\n                }\n                --bit;\n                continue;\n\
    \            }\n            int low = bit - (window_bits - 1);\n            if\
    \ (low < 0) low = 0;\n            while (((exp >> low) & 1ULL) == 0) ++low;\n\
    \            uint value = 0;\n            for (int k = bit; k >= low; --k) value\
    \ = (value << 1) | uint((exp >> k) & 1ULL);\n            const uint idx = value\
    \ >> 1;\n            if (!started) {\n                res = odd[idx].mat;\n  \
    \              started = true;\n            } else {\n                for (int\
    \ k = low; k <= bit; ++k) {\n                    res.prepare_mul(scratch, dim);\n\
    \                    res.mul_assign_prepared(scratch, dim, false);\n         \
    \       }\n                res.mul_assign_prepared(odd[idx].prepared, scratch,\
    \ dim, false);\n            }\n            bit = low - 1;\n        }\n       \
    \ return res;\n    }\n    SquareMatrixMint operator+(const SquareMatrixMint &B)\
    \ const { return SquareMatrixMint(*this) += B; }\n    SquareMatrixMint operator-(const\
    \ SquareMatrixMint &B) const { return SquareMatrixMint(*this) -= B; }\n    SquareMatrixMint\
    \ operator*(const SquareMatrixMint &B) const { return SquareMatrixMint(*this)\
    \ *= B; }\n};\n\n/**\n * @brief \u56FA\u5B9A\u9577\u6B63\u65B9\u884C\u5217(mint\u5C02\
    \u7528)\n */\n"
  code: "#include \"../util/modint.cpp\"\n#if defined(__x86_64__) || defined(_M_X64)\n\
    #include <immintrin.h>\n#endif\n\nnamespace squarematrix_mint_detail {\nconstexpr\
    \ ull mul_max_term = (ull)(MOD - 1) * (MOD - 1);\nconstexpr size_t mul_block_size\
    \ = mul_max_term == 0 ? 1 : size_t(~0ULL / mul_max_term);\nconstexpr size_t mul_unroll_size\
    \ = mul_block_size < 16 ? mul_block_size : 16;\n\nstruct DotProductPair {\n  \
    \  uint first;\n    uint second;\n};\n\n#if defined(__x86_64__) || defined(_M_X64)\n\
    __attribute__((target(\"avx2\"))) inline ull avx2_hsum_u64x4(__m256i v) {\n  \
    \  alignas(32) ull buf[4];\n    _mm256_store_si256((__m256i *)buf, v);\n    return\
    \ buf[0] + buf[1] + buf[2] + buf[3];\n}\n\n__attribute__((target(\"avx2\"))) ull\
    \ dot_product_raw_avx2(const uint *row, const uint *col, size_t n, uint mod) {\n\
    \    ull sum = 0;\n    size_t k = 0;\n    for (; k + mul_block_size - 1 < n; k\
    \ += mul_block_size) {\n        ull acc = 0;\n        size_t t = 0;\n        __m256i\
    \ acc_even = _mm256_setzero_si256();\n        __m256i acc_odd = _mm256_setzero_si256();\n\
    \        for (; t + 8 <= mul_block_size; t += 8) {\n            const __m256i\
    \ rowv = _mm256_loadu_si256((const __m256i *)(row + k + t));\n            const\
    \ __m256i colv = _mm256_loadu_si256((const __m256i *)(col + k + t));\n       \
    \     acc_even = _mm256_add_epi64(acc_even, _mm256_mul_epu32(rowv, colv));\n \
    \           const __m256i row_hi = _mm256_srli_epi64(rowv, 32);\n            const\
    \ __m256i col_hi = _mm256_srli_epi64(colv, 32);\n            acc_odd = _mm256_add_epi64(acc_odd,\
    \ _mm256_mul_epu32(row_hi, col_hi));\n        }\n        acc += avx2_hsum_u64x4(acc_even)\
    \ + avx2_hsum_u64x4(acc_odd);\n        for (; t < mul_block_size; ++t) acc +=\
    \ (ull)row[k + t] * col[k + t];\n        sum += acc % mod;\n        if (sum >=\
    \ mod) sum -= mod;\n    }\n    ull acc = 0;\n    for (; k < n; ++k) acc += (ull)row[k]\
    \ * col[k];\n    sum += acc % mod;\n    if (sum >= mod) sum -= mod;\n    return\
    \ uint(sum);\n}\n\n__attribute__((target(\"avx2\"))) DotProductPair dot_product_raw2_avx2(const\
    \ uint *row, const uint *col0, const uint *col1, size_t n, uint mod) {\n    ull\
    \ sum0 = 0, sum1 = 0;\n    size_t k = 0;\n    for (; k + mul_block_size - 1 <\
    \ n; k += mul_block_size) {\n        ull acc0 = 0, acc1 = 0;\n        size_t t\
    \ = 0;\n        __m256i acc0_even = _mm256_setzero_si256();\n        __m256i acc0_odd\
    \ = _mm256_setzero_si256();\n        __m256i acc1_even = _mm256_setzero_si256();\n\
    \        __m256i acc1_odd = _mm256_setzero_si256();\n        for (; t + 8 <= mul_block_size;\
    \ t += 8) {\n            const __m256i rowv = _mm256_loadu_si256((const __m256i\
    \ *)(row + k + t));\n            const __m256i col0v = _mm256_loadu_si256((const\
    \ __m256i *)(col0 + k + t));\n            const __m256i col1v = _mm256_loadu_si256((const\
    \ __m256i *)(col1 + k + t));\n            acc0_even = _mm256_add_epi64(acc0_even,\
    \ _mm256_mul_epu32(rowv, col0v));\n            acc1_even = _mm256_add_epi64(acc1_even,\
    \ _mm256_mul_epu32(rowv, col1v));\n            const __m256i row_hi = _mm256_srli_epi64(rowv,\
    \ 32);\n            const __m256i col0_hi = _mm256_srli_epi64(col0v, 32);\n  \
    \          const __m256i col1_hi = _mm256_srli_epi64(col1v, 32);\n           \
    \ acc0_odd = _mm256_add_epi64(acc0_odd, _mm256_mul_epu32(row_hi, col0_hi));\n\
    \            acc1_odd = _mm256_add_epi64(acc1_odd, _mm256_mul_epu32(row_hi, col1_hi));\n\
    \        }\n        acc0 += avx2_hsum_u64x4(acc0_even) + avx2_hsum_u64x4(acc0_odd);\n\
    \        acc1 += avx2_hsum_u64x4(acc1_even) + avx2_hsum_u64x4(acc1_odd);\n   \
    \     for (; t < mul_block_size; ++t) {\n            const ull x = row[k + t];\n\
    \            acc0 += x * col0[k + t];\n            acc1 += x * col1[k + t];\n\
    \        }\n        sum0 += acc0 % mod;\n        if (sum0 >= mod) sum0 -= mod;\n\
    \        sum1 += acc1 % mod;\n        if (sum1 >= mod) sum1 -= mod;\n    }\n \
    \   ull acc0 = 0, acc1 = 0;\n    for (; k < n; ++k) {\n        const ull x = row[k];\n\
    \        acc0 += x * col0[k];\n        acc1 += x * col1[k];\n    }\n    sum0 +=\
    \ acc0 % mod;\n    if (sum0 >= mod) sum0 -= mod;\n    sum1 += acc1 % mod;\n  \
    \  if (sum1 >= mod) sum1 -= mod;\n    return {uint(sum0), uint(sum1)};\n}\n\n\
    inline bool has_avx2() {\n    static const bool cached = __builtin_cpu_supports(\"\
    avx2\");\n    return cached;\n}\n#endif\n\nuint dot_product_raw(const uint *row,\
    \ const uint *col, size_t n, uint mod) {\n#if defined(__x86_64__) || defined(_M_X64)\n\
    \    if (mul_block_size >= 8 && has_avx2()) return dot_product_raw_avx2(row, col,\
    \ n, mod);\n#endif\n    ull sum = 0;\n    size_t k = 0;\n    for (; k + mul_block_size\
    \ - 1 < n; k += mul_block_size) {\n        ull acc = 0;\n        if constexpr\
    \ (mul_unroll_size >= 1) acc += (ull)row[k + 0] * col[k + 0];\n        if constexpr\
    \ (mul_unroll_size >= 2) acc += (ull)row[k + 1] * col[k + 1];\n        if constexpr\
    \ (mul_unroll_size >= 3) acc += (ull)row[k + 2] * col[k + 2];\n        if constexpr\
    \ (mul_unroll_size >= 4) acc += (ull)row[k + 3] * col[k + 3];\n        if constexpr\
    \ (mul_unroll_size >= 5) acc += (ull)row[k + 4] * col[k + 4];\n        if constexpr\
    \ (mul_unroll_size >= 6) acc += (ull)row[k + 5] * col[k + 5];\n        if constexpr\
    \ (mul_unroll_size >= 7) acc += (ull)row[k + 6] * col[k + 6];\n        if constexpr\
    \ (mul_unroll_size >= 8) acc += (ull)row[k + 7] * col[k + 7];\n        if constexpr\
    \ (mul_unroll_size >= 9) acc += (ull)row[k + 8] * col[k + 8];\n        if constexpr\
    \ (mul_unroll_size >= 10) acc += (ull)row[k + 9] * col[k + 9];\n        if constexpr\
    \ (mul_unroll_size >= 11) acc += (ull)row[k + 10] * col[k + 10];\n        if constexpr\
    \ (mul_unroll_size >= 12) acc += (ull)row[k + 11] * col[k + 11];\n        if constexpr\
    \ (mul_unroll_size >= 13) acc += (ull)row[k + 12] * col[k + 12];\n        if constexpr\
    \ (mul_unroll_size >= 14) acc += (ull)row[k + 13] * col[k + 13];\n        if constexpr\
    \ (mul_unroll_size >= 15) acc += (ull)row[k + 14] * col[k + 14];\n        if constexpr\
    \ (mul_unroll_size >= 16) acc += (ull)row[k + 15] * col[k + 15];\n        for\
    \ (size_t t = mul_unroll_size; t < mul_block_size; ++t) {\n            acc +=\
    \ (ull)row[k + t] * col[k + t];\n        }\n        sum += acc % mod;\n      \
    \  if (sum >= mod) sum -= mod;\n    }\n    ull acc = 0;\n    for (; k < n; ++k)\
    \ acc += (ull)row[k] * col[k];\n    sum += acc % mod;\n    if (sum >= mod) sum\
    \ -= mod;\n    return uint(sum);\n}\n\nDotProductPair dot_product_raw2(const uint\
    \ *row, const uint *col0, const uint *col1, size_t n, uint mod) {\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n    if (mul_block_size >= 8 && has_avx2()) return dot_product_raw2_avx2(row,\
    \ col0, col1, n, mod);\n#endif\n    ull sum0 = 0, sum1 = 0;\n    size_t k = 0;\n\
    \    for (; k + mul_block_size - 1 < n; k += mul_block_size) {\n        ull acc0\
    \ = 0, acc1 = 0;\n        if constexpr (mul_unroll_size >= 1) {\n            const\
    \ ull x = row[k + 0];\n            acc0 += x * col0[k + 0];\n            acc1\
    \ += x * col1[k + 0];\n        }\n        if constexpr (mul_unroll_size >= 2)\
    \ {\n            const ull x = row[k + 1];\n            acc0 += x * col0[k + 1];\n\
    \            acc1 += x * col1[k + 1];\n        }\n        if constexpr (mul_unroll_size\
    \ >= 3) {\n            const ull x = row[k + 2];\n            acc0 += x * col0[k\
    \ + 2];\n            acc1 += x * col1[k + 2];\n        }\n        if constexpr\
    \ (mul_unroll_size >= 4) {\n            const ull x = row[k + 3];\n          \
    \  acc0 += x * col0[k + 3];\n            acc1 += x * col1[k + 3];\n        }\n\
    \        if constexpr (mul_unroll_size >= 5) {\n            const ull x = row[k\
    \ + 4];\n            acc0 += x * col0[k + 4];\n            acc1 += x * col1[k\
    \ + 4];\n        }\n        if constexpr (mul_unroll_size >= 6) {\n          \
    \  const ull x = row[k + 5];\n            acc0 += x * col0[k + 5];\n         \
    \   acc1 += x * col1[k + 5];\n        }\n        if constexpr (mul_unroll_size\
    \ >= 7) {\n            const ull x = row[k + 6];\n            acc0 += x * col0[k\
    \ + 6];\n            acc1 += x * col1[k + 6];\n        }\n        if constexpr\
    \ (mul_unroll_size >= 8) {\n            const ull x = row[k + 7];\n          \
    \  acc0 += x * col0[k + 7];\n            acc1 += x * col1[k + 7];\n        }\n\
    \        if constexpr (mul_unroll_size >= 9) {\n            const ull x = row[k\
    \ + 8];\n            acc0 += x * col0[k + 8];\n            acc1 += x * col1[k\
    \ + 8];\n        }\n        if constexpr (mul_unroll_size >= 10) {\n         \
    \   const ull x = row[k + 9];\n            acc0 += x * col0[k + 9];\n        \
    \    acc1 += x * col1[k + 9];\n        }\n        if constexpr (mul_unroll_size\
    \ >= 11) {\n            const ull x = row[k + 10];\n            acc0 += x * col0[k\
    \ + 10];\n            acc1 += x * col1[k + 10];\n        }\n        if constexpr\
    \ (mul_unroll_size >= 12) {\n            const ull x = row[k + 11];\n        \
    \    acc0 += x * col0[k + 11];\n            acc1 += x * col1[k + 11];\n      \
    \  }\n        if constexpr (mul_unroll_size >= 13) {\n            const ull x\
    \ = row[k + 12];\n            acc0 += x * col0[k + 12];\n            acc1 += x\
    \ * col1[k + 12];\n        }\n        if constexpr (mul_unroll_size >= 14) {\n\
    \            const ull x = row[k + 13];\n            acc0 += x * col0[k + 13];\n\
    \            acc1 += x * col1[k + 13];\n        }\n        if constexpr (mul_unroll_size\
    \ >= 15) {\n            const ull x = row[k + 14];\n            acc0 += x * col0[k\
    \ + 14];\n            acc1 += x * col1[k + 14];\n        }\n        if constexpr\
    \ (mul_unroll_size >= 16) {\n            const ull x = row[k + 15];\n        \
    \    acc0 += x * col0[k + 15];\n            acc1 += x * col1[k + 15];\n      \
    \  }\n        for (size_t t = mul_unroll_size; t < mul_block_size; ++t) {\n  \
    \          const ull x = row[k + t];\n            acc0 += x * col0[k + t];\n \
    \           acc1 += x * col1[k + t];\n        }\n        sum0 += acc0 % mod;\n\
    \        if (sum0 >= mod) sum0 -= mod;\n        sum1 += acc1 % mod;\n        if\
    \ (sum1 >= mod) sum1 -= mod;\n    }\n    ull acc0 = 0, acc1 = 0;\n    for (; k\
    \ < n; ++k) {\n        const ull x = row[k];\n        acc0 += x * col0[k];\n \
    \       acc1 += x * col1[k];\n    }\n    sum0 += acc0 % mod;\n    if (sum0 >=\
    \ mod) sum0 -= mod;\n    sum1 += acc1 % mod;\n    if (sum1 >= mod) sum1 -= mod;\n\
    \    return {uint(sum0), uint(sum1)};\n}\n\ntemplate<class Rows>\nvoid transpose_raw(const\
    \ Rows &rows, uint *dst, size_t row_count, size_t col_count, size_t stride) {\n\
    \    for (size_t k = 0; k < row_count; ++k) {\n        const auto *row = rows[k].data();\n\
    \        uint *col = dst + k;\n        for (size_t j = 0; j < col_count; ++j)\
    \ {\n            *col = row[j].value();\n            col += stride;\n        }\n\
    \    }\n}\n} // namespace squarematrix_mint_detail\n\ntemplate<size_t SIZE>\n\
    struct SquareMatrixMint {\n    using T = mint;\n    using ar = array<T, SIZE>;\n\
    \    using mat = array<ar, SIZE>;\n    struct PreparedMul {\n        array<uint,\
    \ SIZE * SIZE> BT;\n    };\n\n    struct MatrixMulScratch : PreparedMul {\n  \
    \      array<uint, SIZE> row;\n    };\n\n    struct VecMulScratch : PreparedMul\
    \ {\n        array<uint, SIZE> res;\n    };\n\n    mat A;\nprivate:\n    void\
    \ mul_assign_prepared_impl(const PreparedMul &prepared, MatrixMulScratch &scratch,\
    \ size_t n, bool clear_unused) {\n        const uint mod = mint::get_mod();\n\
    \        for (size_t i = 0; i < n; ++i) {\n            T *row = A[i].data();\n\
    \            for (size_t j = 0; j < n; ++j) scratch.row[j] = row[j].value();\n\
    \            const uint *col = prepared.BT.data();\n            size_t j = 0;\n\
    \            for (; j + 1 < n; j += 2) {\n                auto dots = squarematrix_mint_detail::dot_product_raw2(scratch.row.data(),\
    \ col, col + SIZE, n, mod);\n                row[j].value() = dots.first;\n  \
    \              row[j + 1].value() = dots.second;\n                col += SIZE\
    \ * 2;\n            }\n            if (j < n) {\n                row[j].value()\
    \ = squarematrix_mint_detail::dot_product_raw(scratch.row.data(), col, n, mod);\n\
    \            }\n            if (clear_unused) {\n                for (size_t j\
    \ = n; j < SIZE; ++j) row[j].value() = 0;\n            }\n        }\n        if\
    \ (clear_unused) {\n            for (size_t i = n; i < SIZE; ++i) {\n        \
    \        for (size_t j = 0; j < SIZE; ++j) A[i][j].value() = 0;\n            }\n\
    \        }\n    }\n\npublic:\n    SquareMatrixMint() {\n        for (size_t i\
    \ = 0; i < SIZE; ++i) {\n            for (size_t j = 0; j < SIZE; ++j) {\n   \
    \             A[i][j] = 0;\n            }\n        }\n    }\n    static SquareMatrixMint\
    \ I(size_t n = SIZE) {\n        SquareMatrixMint X;\n        for (size_t i = 0;\
    \ i < n; ++i) X[i][i] = 1;\n        return X;\n    }\n\n    friend ar &operator*=(ar\
    \ &x, const SquareMatrixMint &Y) {\n        return Y.mul_vec_assign(x);\n    }\n\
    \    friend ar operator*(ar x, const SquareMatrixMint &Y) { return x *= Y; }\n\
    \n    void prepare_mul(PreparedMul &prepared, size_t n = SIZE) const {\n     \
    \   squarematrix_mint_detail::transpose_raw(A, prepared.BT.data(), n, n, SIZE);\n\
    \    }\n\n    void prepare_vec_mul(PreparedMul &prepared, size_t n = SIZE) const\
    \ {\n        prepare_mul(prepared, n);\n    }\n\n    ar &mul_vec_assign(ar &x,\
    \ size_t n = SIZE) const {\n        VecMulScratch scratch;\n        prepare_vec_mul(scratch,\
    \ n);\n        return mul_vec_assign_prepared_impl(x, scratch, n, scratch);\n\
    \    }\n    ar mul_vec(ar x, size_t n = SIZE) const { return mul_vec_assign(x,\
    \ n); }\n    ar &mul_vec_assign(ar &x, VecMulScratch &scratch, size_t n) const\
    \ {\n        prepare_vec_mul(scratch, n);\n        return mul_vec_assign_prepared_impl(x,\
    \ scratch, n, scratch);\n    }\n    ar mul_vec(ar x, VecMulScratch &scratch, size_t\
    \ n) const { return mul_vec_assign(x, scratch, n); }\n    ar &mul_vec_assign_prepared(ar\
    \ &x, VecMulScratch &scratch, size_t n) const {\n        return mul_vec_assign_prepared(x,\
    \ static_cast<const PreparedMul &>(scratch), scratch, n);\n    }\n    ar mul_vec_prepared(ar\
    \ x, VecMulScratch &scratch, size_t n) const {\n        return mul_vec_assign_prepared(x,\
    \ scratch, n);\n    }\n    ar &mul_vec_assign_prepared(ar &x, const PreparedMul\
    \ &prepared, VecMulScratch &scratch, size_t n) const {\n        return mul_vec_assign_prepared_impl(x,\
    \ prepared, n, scratch);\n    }\n    ar mul_vec_prepared(ar x, const PreparedMul\
    \ &prepared, VecMulScratch &scratch, size_t n) const {\n        return mul_vec_assign_prepared(x,\
    \ prepared, scratch, n);\n    }\n\nprivate:\n    ar &mul_vec_assign_prepared_impl(ar\
    \ &x, const PreparedMul &prepared, size_t n, VecMulScratch &scratch) const {\n\
    \        const uint mod = mint::get_mod();\n        for (size_t j = 0; j < n;\
    \ ++j) scratch.res[j] = x[j].value();\n        const uint *col = prepared.BT.data();\n\
    \        size_t j = 0;\n        for (; j + 1 < n; j += 2) {\n            auto\
    \ dots = squarematrix_mint_detail::dot_product_raw2(scratch.res.data(), col, col\
    \ + SIZE, n, mod);\n            x[j].value() = dots.first;\n            x[j +\
    \ 1].value() = dots.second;\n            col += SIZE * 2;\n        }\n       \
    \ if (j < n) {\n            x[j].value() = squarematrix_mint_detail::dot_product_raw(scratch.res.data(),\
    \ col, n, mod);\n        }\n        for (size_t j = n; j < SIZE; ++j) x[j].value()\
    \ = 0;\n        return x;\n    }\n\npublic:\n\n    inline const ar &operator[](int\
    \ k) const { return A.at(k); }\n    inline ar &operator[](int k) { return A.at(k);\
    \ }\n\n    SquareMatrixMint &operator+=(const SquareMatrixMint &B) {\n       \
    \ for (size_t i = 0; i < SIZE; ++i) {\n            for (size_t j = 0; j < SIZE;\
    \ ++j) {\n                A[i][j] += B.A[i][j];\n            }\n        }\n  \
    \      return *this;\n    }\n\n    SquareMatrixMint &operator-=(const SquareMatrixMint\
    \ &B) {\n        for (size_t i = 0; i < SIZE; ++i) {\n            for (size_t\
    \ j = 0; j < SIZE; ++j) {\n                A[i][j] -= B.A[i][j];\n           \
    \ }\n        }\n        return *this;\n    }\n\n    SquareMatrixMint &mul_assign(const\
    \ SquareMatrixMint &B, size_t n = SIZE) {\n        MatrixMulScratch scratch;\n\
    \        return mul_assign(B, scratch, n);\n    }\n    SquareMatrixMint &mul_assign(const\
    \ SquareMatrixMint &B, MatrixMulScratch &scratch, size_t n) {\n        B.prepare_mul(scratch,\
    \ n);\n        return mul_assign_prepared(scratch, n);\n    }\n    SquareMatrixMint\
    \ &mul_assign_prepared(MatrixMulScratch &scratch, size_t n, bool clear_unused\
    \ = true) {\n        return mul_assign_prepared(static_cast<const PreparedMul\
    \ &>(scratch), scratch, n, clear_unused);\n    }\n    SquareMatrixMint &mul_assign_prepared(const\
    \ PreparedMul &prepared, MatrixMulScratch &scratch, size_t n, bool clear_unused\
    \ = true) {\n        mul_assign_prepared_impl(prepared, scratch, n, clear_unused);\n\
    \        return *this;\n    }\n    SquareMatrixMint &operator*=(const SquareMatrixMint\
    \ &B) { return mul_assign(B); }\n\n    SquareMatrixMint pow(ll n, size_t dim =\
    \ SIZE) const {\n        if (n == 0) return I(dim);\n        const ull exp = (ull)n;\n\
    \        MatrixMulScratch scratch;\n        auto binary_pow = [&](ull m) {\n \
    \           SquareMatrixMint a = *this, res = I(dim);\n            while (m >\
    \ 1) {\n                a.prepare_mul(scratch, dim);\n                if (m &\
    \ 1) res.mul_assign_prepared(scratch, dim, false);\n                a.mul_assign_prepared(scratch,\
    \ dim, false);\n                m >>= 1;\n            }\n            a.prepare_mul(scratch,\
    \ dim);\n            res.mul_assign_prepared(scratch, dim, false);\n         \
    \   return res;\n        };\n        if (exp < 8) return binary_pow(exp);\n\n\
    \        constexpr int window_bits = 3;\n        constexpr size_t window_size\
    \ = size_t(1) << (window_bits - 1);\n        struct PowEntry {\n            SquareMatrixMint\
    \ mat;\n            PreparedMul prepared;\n        };\n        array<PowEntry,\
    \ window_size> odd;\n        odd[0].mat = *this;\n        odd[0].mat.prepare_mul(odd[0].prepared,\
    \ dim);\n        if constexpr (window_size > 1) {\n            SquareMatrixMint\
    \ base2 = *this;\n            base2.mul_assign(*this, scratch, dim);\n       \
    \     base2.prepare_mul(scratch, dim);\n            for (size_t i = 1; i < window_size;\
    \ ++i) {\n                odd[i].mat = odd[i - 1].mat;\n                odd[i].mat.mul_assign_prepared(scratch,\
    \ dim, false);\n                odd[i].mat.prepare_mul(odd[i].prepared, dim);\n\
    \            }\n        }\n\n        SquareMatrixMint res;\n        bool started\
    \ = false;\n        for (int bit = 63 - __builtin_clzll(exp); bit >= 0;) {\n \
    \           if (((exp >> bit) & 1ULL) == 0) {\n                if (started) {\n\
    \                    res.prepare_mul(scratch, dim);\n                    res.mul_assign_prepared(scratch,\
    \ dim, false);\n                }\n                --bit;\n                continue;\n\
    \            }\n            int low = bit - (window_bits - 1);\n            if\
    \ (low < 0) low = 0;\n            while (((exp >> low) & 1ULL) == 0) ++low;\n\
    \            uint value = 0;\n            for (int k = bit; k >= low; --k) value\
    \ = (value << 1) | uint((exp >> k) & 1ULL);\n            const uint idx = value\
    \ >> 1;\n            if (!started) {\n                res = odd[idx].mat;\n  \
    \              started = true;\n            } else {\n                for (int\
    \ k = low; k <= bit; ++k) {\n                    res.prepare_mul(scratch, dim);\n\
    \                    res.mul_assign_prepared(scratch, dim, false);\n         \
    \       }\n                res.mul_assign_prepared(odd[idx].prepared, scratch,\
    \ dim, false);\n            }\n            bit = low - 1;\n        }\n       \
    \ return res;\n    }\n    SquareMatrixMint operator+(const SquareMatrixMint &B)\
    \ const { return SquareMatrixMint(*this) += B; }\n    SquareMatrixMint operator-(const\
    \ SquareMatrixMint &B) const { return SquareMatrixMint(*this) -= B; }\n    SquareMatrixMint\
    \ operator*(const SquareMatrixMint &B) const { return SquareMatrixMint(*this)\
    \ *= B; }\n};\n\n/**\n * @brief \u56FA\u5B9A\u9577\u6B63\u65B9\u884C\u5217(mint\u5C02\
    \u7528)\n */\n"
  dependsOn:
  - util/modint.cpp
  isVerificationFile: false
  path: math/squarematrix_mint.cpp
  requiredBy: []
  timestamp: '2026-03-15 18:15:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_pow_of_matrix.test.cpp
date: 2026-03-15
documentation_of: math/squarematrix_mint.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "\u56FA\u5B9A\u9577\u6B63\u65B9\u884C\u5217(mint\u5C02\u7528)"
---

## 説明
`mint` 専用の固定長正方行列。
積で `mint.value()` を使う整数演算に寄せ、`MOD` と accumulator 幅に応じたチャンク分割で行列累乗の定数倍を削る。
汎用版と分け、性能重視の特殊版として置いている。

## できること
- `SquareMatrixMint<SIZE> A`
  `SIZE × SIZE` 行列を 0 初期化で作る
- `SquareMatrixMint<SIZE>::I()`
  単位行列を返す
- `SquareMatrixMint<SIZE>::I(n)`
  左上 `n × n` だけを使う単位行列を返す
- `SquareMatrixMint<SIZE>::PreparedMul prepared`
  転置済み右辺を保持する
- `A += B`, `A -= B`, `A *= B`
  加減算、行列積を行う
- `A.pow(k)`
  $A^k$ を返す
- `A.pow(k, n)`
  左上 `n × n` だけを使って $A^k$ を返す
- `x * A`
  長さ `SIZE` の行ベクトルに右から掛ける
- `A.mul_vec(x, n)`, `A.mul_vec_assign(x, n)`
  左上 `n × n` だけを使って行ベクトル積を行う
- `A.prepare_mul(prepared, n)`
  左上 `n × n` の転置済み右辺を作る
- `A.mul_assign_prepared(prepared, scratch, n)`
  転置済み右辺を再利用して行列積を行う
- `A.mul_vec_prepared(x, prepared, scratch, n)`
  行列積と同じ転置済み右辺を再利用して行ベクトル積を行う

## 使い方
要素が `mint` に固定でよいときに使う。
`Pow of Matrix` のようにサイズ固定で累乗回数が多いケースを想定している。
実際に使うサイズが `SIZE` 未満で、行ベクトル積も合わせて回したいときは `mul_vec(x, n)` を使う。
同じ行列を右辺に何度も使うなら `PreparedMul` を 1 つ作って `prepare_mul` し、行列積と行ベクトル積の両方で共有すると無駄が少ない。

汎用の半環版が必要なら `SquareMatrix<H, SIZE>` を使う。
