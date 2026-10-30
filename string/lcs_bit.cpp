#if defined(__GNUC__) && defined(__x86_64__)
#include <immintrin.h>
#endif

namespace lcs_bit_detail {
using Word = unsigned long long;

inline void update_scalar(Word *dp, const Word *p, int size, Word shift = 1, Word borrow = 0) {
    for (int j = 0; j < size; ++j) {
        Word x = dp[j] | p[j], y = (dp[j] << 1) | shift;
        shift = dp[j] >> 63;
        Word z = x - y;
        Word next = (x < y) | (z < borrow);
        dp[j] = x & ~(z - borrow);
        borrow = next;
    }
}

#if defined(__GNUC__) && defined(__x86_64__)
__attribute__((target("avx2,popcnt"))) inline void update_avx2(Word *dp, const Word *p, int size) {
    const __m256i sign = _mm256_set1_epi64x(numeric_limits<long long>::min());
    const __m256i bits = _mm256_setr_epi64x(1, 2, 4, 8);
    Word shift = 1, borrow = 0;
    int j = 0;
    for (; j + 4 <= size; j += 4) {
        __m256i d = _mm256_loadu_si256((const __m256i *)(dp + j));
        __m256i high = _mm256_srli_epi64(d, 63);
        __m256i carry = _mm256_permute4x64_epi64(high, _MM_SHUFFLE(2, 1, 0, 3));
        carry = _mm256_blend_epi32(carry, _mm256_set1_epi64x(shift), 3);
        shift = dp[j + 3] >> 63;
        __m256i x = _mm256_or_si256(d, _mm256_loadu_si256((const __m256i *)(p + j)));
        __m256i y = _mm256_or_si256(_mm256_slli_epi64(d, 1), carry);
        unsigned g = _mm256_movemask_pd(_mm256_castsi256_pd(_mm256_cmpgt_epi64(
            _mm256_xor_si256(y, sign), _mm256_xor_si256(x, sign))));
        unsigned prop = _mm256_movemask_pd(_mm256_castsi256_pd(_mm256_cmpeq_epi64(x, y)));
        unsigned incoming = (prop + (g << 1) + borrow) ^ prop;
        borrow = incoming >> 4;
        __m256i mask = _mm256_cmpeq_epi64(_mm256_and_si256(_mm256_set1_epi64x(incoming), bits), bits);
        __m256i z = _mm256_add_epi64(_mm256_sub_epi64(x, y), mask);
        _mm256_storeu_si256((__m256i *)(dp + j), _mm256_andnot_si256(z, x));
    }
    update_scalar(dp + j, p + j, size - j, shift, borrow);
}

__attribute__((target("avx2,popcnt,avx512f"))) inline void update_avx512(Word *dp, const Word *p, int size) {
    const __m512i order = _mm512_setr_epi64(0, 0, 1, 2, 3, 4, 5, 6);
    const __m512i one = _mm512_set1_epi64(1);
    Word shift = 1, borrow = 0;
    int j = 0;
    for (; j + 8 <= size; j += 8) {
        __m512i d = _mm512_loadu_si512(dp + j);
        __m512i high = _mm512_maskz_srli_epi64(255, d, 63);
        __m512i carry = _mm512_maskz_permutexvar_epi64(255, order, high);
        carry = _mm512_mask_mov_epi64(carry, 1, _mm512_set1_epi64(shift));
        shift = dp[j + 7] >> 63;
        __m512i x = _mm512_or_si512(d, _mm512_loadu_si512(p + j));
        __m512i y = _mm512_or_si512(_mm512_maskz_slli_epi64(255, d, 1), carry);
        unsigned g = _mm512_cmp_epu64_mask(x, y, _MM_CMPINT_LT);
        unsigned prop = _mm512_cmp_epu64_mask(x, y, _MM_CMPINT_EQ);
        unsigned incoming = (prop + (g << 1) + borrow) ^ prop;
        borrow = incoming >> 8;
        __m512i z = _mm512_mask_sub_epi64(_mm512_sub_epi64(x, y), incoming, _mm512_sub_epi64(x, y), one);
        _mm512_storeu_si512(dp + j, _mm512_andnot_si512(z, x));
    }
    update_scalar(dp + j, p + j, size - j, shift, borrow);
}

inline int backend() {
    static const int result = [] {
        if (!__builtin_cpu_supports("avx2") || !__builtin_cpu_supports("popcnt")) return 0;
        return __builtin_cpu_supports("avx512f") ? 2 : 1;
    }();
    return result;
}
#endif

template<auto Update>
inline void run(const string &s, int m, const vector<vector<Word>> &p, vector<Word> &dp) {
    for (int i = 1; i < (int)s.size(); ++i) {
        Update(dp.data(), p[(unsigned char)s[i]].data(), (int)dp.size());
        if (m & 63) dp.back() &= (1ULL << (m & 63)) - 1;
    }
}
}

int LCS_bit(const string &a, const string &b) {
    const string &s = a.size() >= b.size() ? a : b;
    const string &t = a.size() >= b.size() ? b : a;
    const int n = s.size(), m = t.size(), bit_sz = (m+63)>>6;
    if(n == 0 || m == 0) return 0;
    vector<vector<ull>> p(256, vector<ull>(bit_sz, 0));
    for (int i = 0; i < m; ++i) {
        p[(unsigned char)t[i]][i>>6] |= (1ULL << (i&63));
    }
    vector<ull> dp(bit_sz);
    for (int i = 0; i < m; ++i) {
        if(s[0] == t[i]) {
            dp[i>>6] |= (1ULL << (i&63));
            break;
        }
    }
    using namespace lcs_bit_detail;
#if defined(__GNUC__) && defined(__x86_64__)
    if (bit_sz >= 4 && backend()) {
        if (bit_sz >= 8 && backend() == 2) {
            run<update_avx512>(s, m, p, dp);
        } else {
            run<update_avx2>(s, m, p, dp);
        }
    } else
#endif
    {
        for (int i = 1; i < n; ++i) {
            update_scalar(dp.data(), p[(unsigned char)s[i]].data(), bit_sz);
            if (m & 63) dp.back() &= (1ULL << (m & 63)) - 1;
        }
    }
    int ans = 0;
    for (int i = 0; i < bit_sz; ++i) {
        ans += __builtin_popcountll(dp[i]);
    }
    return ans;
}

/**
 * @brief LCS(bitset)
 */
