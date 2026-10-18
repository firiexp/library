#ifndef FIRIEXP_LIBRARY_DATASTRUCTURE_BITSET_COUNT_CPP
#define FIRIEXP_LIBRARY_DATASTRUCTURE_BITSET_COUNT_CPP

#if defined(__x86_64__) || defined(_M_X64)
#include <immintrin.h>
#endif

namespace bitset_count_detail {
using Word = unsigned long long;
constexpr int count_threshold_words = 128;

#if defined(__x86_64__) || defined(_M_X64)
__attribute__((target("avx2,popcnt"))) inline int count_avx2(const Word *src, int m) {
    const __m256i lookup = _mm256_setr_epi8(
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4);
    const __m256i mask = _mm256_set1_epi8(15);
    const __m256i zero = _mm256_setzero_si256();
    __m256i sum = zero;
    int i = 0;
    for (; i + 4 <= m; i += 4) {
        __m256i x = _mm256_loadu_si256((const __m256i *)(src + i));
        __m256i lo = _mm256_and_si256(x, mask);
        __m256i hi = _mm256_and_si256(_mm256_srli_epi16(x, 4), mask);
        __m256i counts = _mm256_add_epi8(_mm256_shuffle_epi8(lookup, lo), _mm256_shuffle_epi8(lookup, hi));
        sum = _mm256_add_epi64(sum, _mm256_sad_epu8(counts, zero));
    }
    alignas(32) Word lanes[4];
    _mm256_storeu_si256((__m256i *)lanes, sum);
    int result = lanes[0] + lanes[1] + lanes[2] + lanes[3];
    for (; i < m; ++i) result += __builtin_popcountll(src[i]);
    return result;
}

__attribute__((target("avx2,popcnt,avx512f,avx512vpopcntdq"))) inline int count_avx512(const Word *src, int m) {
    __m512i sum0 = _mm512_setzero_si512(), sum1 = sum0, sum2 = sum0, sum3 = sum0;
    int i = 0;
    for (; i + 32 <= m; i += 32) {
        sum0 = _mm512_add_epi64(sum0, _mm512_popcnt_epi64(_mm512_loadu_si512(src + i)));
        sum1 = _mm512_add_epi64(sum1, _mm512_popcnt_epi64(_mm512_loadu_si512(src + i + 8)));
        sum2 = _mm512_add_epi64(sum2, _mm512_popcnt_epi64(_mm512_loadu_si512(src + i + 16)));
        sum3 = _mm512_add_epi64(sum3, _mm512_popcnt_epi64(_mm512_loadu_si512(src + i + 24)));
    }
    __m512i sum = _mm512_add_epi64(_mm512_add_epi64(sum0, sum1), _mm512_add_epi64(sum2, sum3));
    for (; i + 8 <= m; i += 8) {
        __m512i x = _mm512_loadu_si512(src + i);
        sum = _mm512_add_epi64(sum, _mm512_popcnt_epi64(x));
    }
    alignas(64) Word lanes[8];
    _mm512_storeu_si512(lanes, sum);
    int result = 0;
    for (Word lane : lanes) result += lane;
    for (; i < m; ++i) result += __builtin_popcountll(src[i]);
    return result;
}

inline int count_backend() {
    static const int backend = [] {
        if (!__builtin_cpu_supports("avx2") || !__builtin_cpu_supports("popcnt")) return 0;
        if (__builtin_cpu_supports("avx512f") && __builtin_cpu_supports("avx512vpopcntdq")) return 2;
        return 1;
    }();
    return backend;
}

__attribute__((noinline)) inline int count_large(const Word *src, int m) {
    int backend = count_backend();
    if (backend == 2) return count_avx512(src, m);
    if (backend == 1) return count_avx2(src, m);
    int result = 0;
    for (int i = 0; i < m; ++i) result += __builtin_popcountll(src[i]);
    return result;
}

#endif
}

#endif

/**
 * @brief bitsetの共通集計処理
 */
