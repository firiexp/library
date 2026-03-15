#include "../util/modint.cpp"
#if defined(__x86_64__) || defined(_M_X64)
#include <immintrin.h>
#endif

namespace squarematrix_mint_detail {
constexpr ull mul_max_term = (ull)(MOD - 1) * (MOD - 1);
constexpr size_t mul_block_size = mul_max_term == 0 ? 1 : size_t(~0ULL / mul_max_term);
constexpr size_t mul_unroll_size = mul_block_size < 16 ? mul_block_size : 16;

struct DotProductPair {
    uint first;
    uint second;
};

#if defined(__x86_64__) || defined(_M_X64)
__attribute__((target("avx2"))) inline ull avx2_hsum_u64x4(__m256i v) {
    alignas(32) ull buf[4];
    _mm256_store_si256((__m256i *)buf, v);
    return buf[0] + buf[1] + buf[2] + buf[3];
}

__attribute__((target("avx2"))) ull dot_product_raw_avx2(const uint *row, const uint *col, size_t n, uint mod) {
    ull sum = 0;
    size_t k = 0;
    for (; k + mul_block_size - 1 < n; k += mul_block_size) {
        ull acc = 0;
        size_t t = 0;
        __m256i acc_even = _mm256_setzero_si256();
        __m256i acc_odd = _mm256_setzero_si256();
        for (; t + 8 <= mul_block_size; t += 8) {
            const __m256i rowv = _mm256_loadu_si256((const __m256i *)(row + k + t));
            const __m256i colv = _mm256_loadu_si256((const __m256i *)(col + k + t));
            acc_even = _mm256_add_epi64(acc_even, _mm256_mul_epu32(rowv, colv));
            const __m256i row_hi = _mm256_srli_epi64(rowv, 32);
            const __m256i col_hi = _mm256_srli_epi64(colv, 32);
            acc_odd = _mm256_add_epi64(acc_odd, _mm256_mul_epu32(row_hi, col_hi));
        }
        acc += avx2_hsum_u64x4(acc_even) + avx2_hsum_u64x4(acc_odd);
        for (; t < mul_block_size; ++t) acc += (ull)row[k + t] * col[k + t];
        sum += acc % mod;
        if (sum >= mod) sum -= mod;
    }
    ull acc = 0;
    for (; k < n; ++k) acc += (ull)row[k] * col[k];
    sum += acc % mod;
    if (sum >= mod) sum -= mod;
    return uint(sum);
}

__attribute__((target("avx2"))) DotProductPair dot_product_raw2_avx2(const uint *row, const uint *col0, const uint *col1, size_t n, uint mod) {
    ull sum0 = 0, sum1 = 0;
    size_t k = 0;
    for (; k + mul_block_size - 1 < n; k += mul_block_size) {
        ull acc0 = 0, acc1 = 0;
        size_t t = 0;
        __m256i acc0_even = _mm256_setzero_si256();
        __m256i acc0_odd = _mm256_setzero_si256();
        __m256i acc1_even = _mm256_setzero_si256();
        __m256i acc1_odd = _mm256_setzero_si256();
        for (; t + 8 <= mul_block_size; t += 8) {
            const __m256i rowv = _mm256_loadu_si256((const __m256i *)(row + k + t));
            const __m256i col0v = _mm256_loadu_si256((const __m256i *)(col0 + k + t));
            const __m256i col1v = _mm256_loadu_si256((const __m256i *)(col1 + k + t));
            acc0_even = _mm256_add_epi64(acc0_even, _mm256_mul_epu32(rowv, col0v));
            acc1_even = _mm256_add_epi64(acc1_even, _mm256_mul_epu32(rowv, col1v));
            const __m256i row_hi = _mm256_srli_epi64(rowv, 32);
            const __m256i col0_hi = _mm256_srli_epi64(col0v, 32);
            const __m256i col1_hi = _mm256_srli_epi64(col1v, 32);
            acc0_odd = _mm256_add_epi64(acc0_odd, _mm256_mul_epu32(row_hi, col0_hi));
            acc1_odd = _mm256_add_epi64(acc1_odd, _mm256_mul_epu32(row_hi, col1_hi));
        }
        acc0 += avx2_hsum_u64x4(acc0_even) + avx2_hsum_u64x4(acc0_odd);
        acc1 += avx2_hsum_u64x4(acc1_even) + avx2_hsum_u64x4(acc1_odd);
        for (; t < mul_block_size; ++t) {
            const ull x = row[k + t];
            acc0 += x * col0[k + t];
            acc1 += x * col1[k + t];
        }
        sum0 += acc0 % mod;
        if (sum0 >= mod) sum0 -= mod;
        sum1 += acc1 % mod;
        if (sum1 >= mod) sum1 -= mod;
    }
    ull acc0 = 0, acc1 = 0;
    for (; k < n; ++k) {
        const ull x = row[k];
        acc0 += x * col0[k];
        acc1 += x * col1[k];
    }
    sum0 += acc0 % mod;
    if (sum0 >= mod) sum0 -= mod;
    sum1 += acc1 % mod;
    if (sum1 >= mod) sum1 -= mod;
    return {uint(sum0), uint(sum1)};
}

inline bool has_avx2() {
    static const bool cached = __builtin_cpu_supports("avx2");
    return cached;
}
#endif

uint dot_product_raw(const uint *row, const uint *col, size_t n, uint mod) {
#if defined(__x86_64__) || defined(_M_X64)
    if (mul_block_size >= 8 && has_avx2()) return dot_product_raw_avx2(row, col, n, mod);
#endif
    ull sum = 0;
    size_t k = 0;
    for (; k + mul_block_size - 1 < n; k += mul_block_size) {
        ull acc = 0;
        if constexpr (mul_unroll_size >= 1) acc += (ull)row[k + 0] * col[k + 0];
        if constexpr (mul_unroll_size >= 2) acc += (ull)row[k + 1] * col[k + 1];
        if constexpr (mul_unroll_size >= 3) acc += (ull)row[k + 2] * col[k + 2];
        if constexpr (mul_unroll_size >= 4) acc += (ull)row[k + 3] * col[k + 3];
        if constexpr (mul_unroll_size >= 5) acc += (ull)row[k + 4] * col[k + 4];
        if constexpr (mul_unroll_size >= 6) acc += (ull)row[k + 5] * col[k + 5];
        if constexpr (mul_unroll_size >= 7) acc += (ull)row[k + 6] * col[k + 6];
        if constexpr (mul_unroll_size >= 8) acc += (ull)row[k + 7] * col[k + 7];
        if constexpr (mul_unroll_size >= 9) acc += (ull)row[k + 8] * col[k + 8];
        if constexpr (mul_unroll_size >= 10) acc += (ull)row[k + 9] * col[k + 9];
        if constexpr (mul_unroll_size >= 11) acc += (ull)row[k + 10] * col[k + 10];
        if constexpr (mul_unroll_size >= 12) acc += (ull)row[k + 11] * col[k + 11];
        if constexpr (mul_unroll_size >= 13) acc += (ull)row[k + 12] * col[k + 12];
        if constexpr (mul_unroll_size >= 14) acc += (ull)row[k + 13] * col[k + 13];
        if constexpr (mul_unroll_size >= 15) acc += (ull)row[k + 14] * col[k + 14];
        if constexpr (mul_unroll_size >= 16) acc += (ull)row[k + 15] * col[k + 15];
        for (size_t t = mul_unroll_size; t < mul_block_size; ++t) {
            acc += (ull)row[k + t] * col[k + t];
        }
        sum += acc % mod;
        if (sum >= mod) sum -= mod;
    }
    ull acc = 0;
    for (; k < n; ++k) acc += (ull)row[k] * col[k];
    sum += acc % mod;
    if (sum >= mod) sum -= mod;
    return uint(sum);
}

DotProductPair dot_product_raw2(const uint *row, const uint *col0, const uint *col1, size_t n, uint mod) {
#if defined(__x86_64__) || defined(_M_X64)
    if (mul_block_size >= 8 && has_avx2()) return dot_product_raw2_avx2(row, col0, col1, n, mod);
#endif
    ull sum0 = 0, sum1 = 0;
    size_t k = 0;
    for (; k + mul_block_size - 1 < n; k += mul_block_size) {
        ull acc0 = 0, acc1 = 0;
        if constexpr (mul_unroll_size >= 1) {
            const ull x = row[k + 0];
            acc0 += x * col0[k + 0];
            acc1 += x * col1[k + 0];
        }
        if constexpr (mul_unroll_size >= 2) {
            const ull x = row[k + 1];
            acc0 += x * col0[k + 1];
            acc1 += x * col1[k + 1];
        }
        if constexpr (mul_unroll_size >= 3) {
            const ull x = row[k + 2];
            acc0 += x * col0[k + 2];
            acc1 += x * col1[k + 2];
        }
        if constexpr (mul_unroll_size >= 4) {
            const ull x = row[k + 3];
            acc0 += x * col0[k + 3];
            acc1 += x * col1[k + 3];
        }
        if constexpr (mul_unroll_size >= 5) {
            const ull x = row[k + 4];
            acc0 += x * col0[k + 4];
            acc1 += x * col1[k + 4];
        }
        if constexpr (mul_unroll_size >= 6) {
            const ull x = row[k + 5];
            acc0 += x * col0[k + 5];
            acc1 += x * col1[k + 5];
        }
        if constexpr (mul_unroll_size >= 7) {
            const ull x = row[k + 6];
            acc0 += x * col0[k + 6];
            acc1 += x * col1[k + 6];
        }
        if constexpr (mul_unroll_size >= 8) {
            const ull x = row[k + 7];
            acc0 += x * col0[k + 7];
            acc1 += x * col1[k + 7];
        }
        if constexpr (mul_unroll_size >= 9) {
            const ull x = row[k + 8];
            acc0 += x * col0[k + 8];
            acc1 += x * col1[k + 8];
        }
        if constexpr (mul_unroll_size >= 10) {
            const ull x = row[k + 9];
            acc0 += x * col0[k + 9];
            acc1 += x * col1[k + 9];
        }
        if constexpr (mul_unroll_size >= 11) {
            const ull x = row[k + 10];
            acc0 += x * col0[k + 10];
            acc1 += x * col1[k + 10];
        }
        if constexpr (mul_unroll_size >= 12) {
            const ull x = row[k + 11];
            acc0 += x * col0[k + 11];
            acc1 += x * col1[k + 11];
        }
        if constexpr (mul_unroll_size >= 13) {
            const ull x = row[k + 12];
            acc0 += x * col0[k + 12];
            acc1 += x * col1[k + 12];
        }
        if constexpr (mul_unroll_size >= 14) {
            const ull x = row[k + 13];
            acc0 += x * col0[k + 13];
            acc1 += x * col1[k + 13];
        }
        if constexpr (mul_unroll_size >= 15) {
            const ull x = row[k + 14];
            acc0 += x * col0[k + 14];
            acc1 += x * col1[k + 14];
        }
        if constexpr (mul_unroll_size >= 16) {
            const ull x = row[k + 15];
            acc0 += x * col0[k + 15];
            acc1 += x * col1[k + 15];
        }
        for (size_t t = mul_unroll_size; t < mul_block_size; ++t) {
            const ull x = row[k + t];
            acc0 += x * col0[k + t];
            acc1 += x * col1[k + t];
        }
        sum0 += acc0 % mod;
        if (sum0 >= mod) sum0 -= mod;
        sum1 += acc1 % mod;
        if (sum1 >= mod) sum1 -= mod;
    }
    ull acc0 = 0, acc1 = 0;
    for (; k < n; ++k) {
        const ull x = row[k];
        acc0 += x * col0[k];
        acc1 += x * col1[k];
    }
    sum0 += acc0 % mod;
    if (sum0 >= mod) sum0 -= mod;
    sum1 += acc1 % mod;
    if (sum1 >= mod) sum1 -= mod;
    return {uint(sum0), uint(sum1)};
}

template<class Rows>
void transpose_raw(const Rows &rows, uint *dst, size_t row_count, size_t col_count, size_t stride) {
    for (size_t k = 0; k < row_count; ++k) {
        const auto *row = rows[k].data();
        uint *col = dst + k;
        for (size_t j = 0; j < col_count; ++j) {
            *col = row[j].value();
            col += stride;
        }
    }
}
} // namespace squarematrix_mint_detail

template<size_t SIZE>
struct SquareMatrixMint {
    using T = mint;
    using ar = array<T, SIZE>;
    using mat = array<ar, SIZE>;
    struct PreparedMul {
        array<uint, SIZE * SIZE> BT;
    };

    struct MatrixMulScratch : PreparedMul {
        array<uint, SIZE> row;
    };

    struct VecMulScratch : PreparedMul {
        array<uint, SIZE> res;
    };

    mat A;
private:
    void mul_assign_prepared_impl(const PreparedMul &prepared, MatrixMulScratch &scratch, size_t n, bool clear_unused) {
        const uint mod = mint::get_mod();
        for (size_t i = 0; i < n; ++i) {
            T *row = A[i].data();
            for (size_t j = 0; j < n; ++j) scratch.row[j] = row[j].value();
            const uint *col = prepared.BT.data();
            size_t j = 0;
            for (; j + 1 < n; j += 2) {
                auto dots = squarematrix_mint_detail::dot_product_raw2(scratch.row.data(), col, col + SIZE, n, mod);
                row[j].value() = dots.first;
                row[j + 1].value() = dots.second;
                col += SIZE * 2;
            }
            if (j < n) {
                row[j].value() = squarematrix_mint_detail::dot_product_raw(scratch.row.data(), col, n, mod);
            }
            if (clear_unused) {
                for (size_t j = n; j < SIZE; ++j) row[j].value() = 0;
            }
        }
        if (clear_unused) {
            for (size_t i = n; i < SIZE; ++i) {
                for (size_t j = 0; j < SIZE; ++j) A[i][j].value() = 0;
            }
        }
    }

public:
    SquareMatrixMint() {
        for (size_t i = 0; i < SIZE; ++i) {
            for (size_t j = 0; j < SIZE; ++j) {
                A[i][j] = 0;
            }
        }
    }
    static SquareMatrixMint I(size_t n = SIZE) {
        SquareMatrixMint X;
        for (size_t i = 0; i < n; ++i) X[i][i] = 1;
        return X;
    }

    friend ar &operator*=(ar &x, const SquareMatrixMint &Y) {
        return Y.mul_vec_assign(x);
    }
    friend ar operator*(ar x, const SquareMatrixMint &Y) { return x *= Y; }

    void prepare_mul(PreparedMul &prepared, size_t n = SIZE) const {
        squarematrix_mint_detail::transpose_raw(A, prepared.BT.data(), n, n, SIZE);
    }

    void prepare_vec_mul(PreparedMul &prepared, size_t n = SIZE) const {
        prepare_mul(prepared, n);
    }

    ar &mul_vec_assign(ar &x, size_t n = SIZE) const {
        VecMulScratch scratch;
        prepare_vec_mul(scratch, n);
        return mul_vec_assign_prepared_impl(x, scratch, n, scratch);
    }
    ar mul_vec(ar x, size_t n = SIZE) const { return mul_vec_assign(x, n); }
    ar &mul_vec_assign(ar &x, VecMulScratch &scratch, size_t n) const {
        prepare_vec_mul(scratch, n);
        return mul_vec_assign_prepared_impl(x, scratch, n, scratch);
    }
    ar mul_vec(ar x, VecMulScratch &scratch, size_t n) const { return mul_vec_assign(x, scratch, n); }
    ar &mul_vec_assign_prepared(ar &x, VecMulScratch &scratch, size_t n) const {
        return mul_vec_assign_prepared(x, static_cast<const PreparedMul &>(scratch), scratch, n);
    }
    ar mul_vec_prepared(ar x, VecMulScratch &scratch, size_t n) const {
        return mul_vec_assign_prepared(x, scratch, n);
    }
    ar &mul_vec_assign_prepared(ar &x, const PreparedMul &prepared, VecMulScratch &scratch, size_t n) const {
        return mul_vec_assign_prepared_impl(x, prepared, n, scratch);
    }
    ar mul_vec_prepared(ar x, const PreparedMul &prepared, VecMulScratch &scratch, size_t n) const {
        return mul_vec_assign_prepared(x, prepared, scratch, n);
    }

private:
    ar &mul_vec_assign_prepared_impl(ar &x, const PreparedMul &prepared, size_t n, VecMulScratch &scratch) const {
        const uint mod = mint::get_mod();
        for (size_t j = 0; j < n; ++j) scratch.res[j] = x[j].value();
        const uint *col = prepared.BT.data();
        size_t j = 0;
        for (; j + 1 < n; j += 2) {
            auto dots = squarematrix_mint_detail::dot_product_raw2(scratch.res.data(), col, col + SIZE, n, mod);
            x[j].value() = dots.first;
            x[j + 1].value() = dots.second;
            col += SIZE * 2;
        }
        if (j < n) {
            x[j].value() = squarematrix_mint_detail::dot_product_raw(scratch.res.data(), col, n, mod);
        }
        for (size_t j = n; j < SIZE; ++j) x[j].value() = 0;
        return x;
    }

public:

    inline const ar &operator[](int k) const { return A.at(k); }
    inline ar &operator[](int k) { return A.at(k); }

    SquareMatrixMint &operator+=(const SquareMatrixMint &B) {
        for (size_t i = 0; i < SIZE; ++i) {
            for (size_t j = 0; j < SIZE; ++j) {
                A[i][j] += B.A[i][j];
            }
        }
        return *this;
    }

    SquareMatrixMint &operator-=(const SquareMatrixMint &B) {
        for (size_t i = 0; i < SIZE; ++i) {
            for (size_t j = 0; j < SIZE; ++j) {
                A[i][j] -= B.A[i][j];
            }
        }
        return *this;
    }

    SquareMatrixMint &mul_assign(const SquareMatrixMint &B, size_t n = SIZE) {
        MatrixMulScratch scratch;
        return mul_assign(B, scratch, n);
    }
    SquareMatrixMint &mul_assign(const SquareMatrixMint &B, MatrixMulScratch &scratch, size_t n) {
        B.prepare_mul(scratch, n);
        return mul_assign_prepared(scratch, n);
    }
    SquareMatrixMint &mul_assign_prepared(MatrixMulScratch &scratch, size_t n, bool clear_unused = true) {
        return mul_assign_prepared(static_cast<const PreparedMul &>(scratch), scratch, n, clear_unused);
    }
    SquareMatrixMint &mul_assign_prepared(const PreparedMul &prepared, MatrixMulScratch &scratch, size_t n, bool clear_unused = true) {
        mul_assign_prepared_impl(prepared, scratch, n, clear_unused);
        return *this;
    }
    SquareMatrixMint &operator*=(const SquareMatrixMint &B) { return mul_assign(B); }

    SquareMatrixMint pow(ll n, size_t dim = SIZE) const {
        if (n == 0) return I(dim);
        const ull exp = (ull)n;
        MatrixMulScratch scratch;
        auto binary_pow = [&](ull m) {
            SquareMatrixMint a = *this, res = I(dim);
            while (m > 1) {
                a.prepare_mul(scratch, dim);
                if (m & 1) res.mul_assign_prepared(scratch, dim, false);
                a.mul_assign_prepared(scratch, dim, false);
                m >>= 1;
            }
            a.prepare_mul(scratch, dim);
            res.mul_assign_prepared(scratch, dim, false);
            return res;
        };
        if (exp < 8) return binary_pow(exp);

        constexpr int window_bits = 3;
        constexpr size_t window_size = size_t(1) << (window_bits - 1);
        struct PowEntry {
            SquareMatrixMint mat;
            PreparedMul prepared;
        };
        array<PowEntry, window_size> odd;
        odd[0].mat = *this;
        odd[0].mat.prepare_mul(odd[0].prepared, dim);
        if constexpr (window_size > 1) {
            SquareMatrixMint base2 = *this;
            base2.mul_assign(*this, scratch, dim);
            base2.prepare_mul(scratch, dim);
            for (size_t i = 1; i < window_size; ++i) {
                odd[i].mat = odd[i - 1].mat;
                odd[i].mat.mul_assign_prepared(scratch, dim, false);
                odd[i].mat.prepare_mul(odd[i].prepared, dim);
            }
        }

        SquareMatrixMint res;
        bool started = false;
        for (int bit = 63 - __builtin_clzll(exp); bit >= 0;) {
            if (((exp >> bit) & 1ULL) == 0) {
                if (started) {
                    res.prepare_mul(scratch, dim);
                    res.mul_assign_prepared(scratch, dim, false);
                }
                --bit;
                continue;
            }
            int low = bit - (window_bits - 1);
            if (low < 0) low = 0;
            while (((exp >> low) & 1ULL) == 0) ++low;
            uint value = 0;
            for (int k = bit; k >= low; --k) value = (value << 1) | uint((exp >> k) & 1ULL);
            const uint idx = value >> 1;
            if (!started) {
                res = odd[idx].mat;
                started = true;
            } else {
                for (int k = low; k <= bit; ++k) {
                    res.prepare_mul(scratch, dim);
                    res.mul_assign_prepared(scratch, dim, false);
                }
                res.mul_assign_prepared(odd[idx].prepared, scratch, dim, false);
            }
            bit = low - 1;
        }
        return res;
    }
    SquareMatrixMint operator+(const SquareMatrixMint &B) const { return SquareMatrixMint(*this) += B; }
    SquareMatrixMint operator-(const SquareMatrixMint &B) const { return SquareMatrixMint(*this) -= B; }
    SquareMatrixMint operator*(const SquareMatrixMint &B) const { return SquareMatrixMint(*this) *= B; }
};

/**
 * @brief 固定長正方行列(mint専用)
 */
