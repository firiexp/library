#ifndef FIRIEXP_LIBRARY_DATASTRUCTURE_BITSET_COUNT_CPP
#define FIRIEXP_LIBRARY_DATASTRUCTURE_BITSET_COUNT_CPP

#if defined(__x86_64__) || defined(_M_X64)
#include <immintrin.h>
#endif

namespace bitset_count_detail {
using Word = unsigned long long;
constexpr int count_threshold_words = 128;

#if defined(__x86_64__) || defined(_M_X64)
template<bool Intersect = false>
__attribute__((target("avx2,popcnt"))) inline int count_avx2(const Word *src, int m, const Word *other = nullptr) {
    const __m256i lookup = _mm256_setr_epi8(
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4);
    const __m256i mask = _mm256_set1_epi8(15);
    const __m256i zero = _mm256_setzero_si256();
    __m256i sum = zero;
    int i = 0;
    for (; i + 4 <= m; i += 4) {
        __m256i x = _mm256_loadu_si256((const __m256i *)(src + i));
        if constexpr (Intersect) x = _mm256_and_si256(x, _mm256_loadu_si256((const __m256i *)(other + i)));
        __m256i lo = _mm256_and_si256(x, mask);
        __m256i hi = _mm256_and_si256(_mm256_srli_epi16(x, 4), mask);
        __m256i counts = _mm256_add_epi8(_mm256_shuffle_epi8(lookup, lo), _mm256_shuffle_epi8(lookup, hi));
        sum = _mm256_add_epi64(sum, _mm256_sad_epu8(counts, zero));
    }
    alignas(32) Word lanes[4];
    _mm256_storeu_si256((__m256i *)lanes, sum);
    int result = lanes[0] + lanes[1] + lanes[2] + lanes[3];
    for (; i < m; ++i) result += __builtin_popcountll(Intersect ? src[i] & other[i] : src[i]);
    return result;
}

template<bool Intersect>
__attribute__((target("avx2,popcnt,avx512f,avx512vpopcntdq"))) inline __m512i count_block_avx512(const Word *src, const Word *other, int i) {
    __m512i x = _mm512_loadu_si512(src + i);
    if constexpr (Intersect) x = _mm512_and_si512(x, _mm512_loadu_si512(other + i));
    return _mm512_popcnt_epi64(x);
}

template<bool Intersect = false>
__attribute__((target("avx2,popcnt,avx512f,avx512vpopcntdq"))) inline int count_avx512(const Word *src, int m, const Word *other = nullptr) {
    __m512i sum0 = _mm512_setzero_si512(), sum1 = sum0, sum2 = sum0, sum3 = sum0;
    int i = 0;
    for (; i + 32 <= m; i += 32) {
        sum0 = _mm512_add_epi64(sum0, count_block_avx512<Intersect>(src, other, i));
        sum1 = _mm512_add_epi64(sum1, count_block_avx512<Intersect>(src, other, i + 8));
        sum2 = _mm512_add_epi64(sum2, count_block_avx512<Intersect>(src, other, i + 16));
        sum3 = _mm512_add_epi64(sum3, count_block_avx512<Intersect>(src, other, i + 24));
    }
    __m512i sum = _mm512_add_epi64(_mm512_add_epi64(sum0, sum1), _mm512_add_epi64(sum2, sum3));
    for (; i + 8 <= m; i += 8) {
        sum = _mm512_add_epi64(sum, count_block_avx512<Intersect>(src, other, i));
    }
    alignas(64) Word lanes[8];
    _mm512_storeu_si512(lanes, sum);
    int result = 0;
    for (Word lane : lanes) result += lane;
    for (; i < m; ++i) result += __builtin_popcountll(Intersect ? src[i] & other[i] : src[i]);
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

template<bool Intersect = false>
__attribute__((noinline)) inline int count_large(const Word *src, int m, const Word *other = nullptr) {
    int backend = count_backend();
    if (backend == 2) return count_avx512<Intersect>(src, m, other);
    if (backend == 1) return count_avx2<Intersect>(src, m, other);
    int result = 0;
    for (int i = 0; i < m; ++i) result += __builtin_popcountll(Intersect ? src[i] & other[i] : src[i]);
    return result;
}

__attribute__((target("avx2"))) inline bool intersects_avx2(const Word *src, const Word *other, int m) {
    int i = 0;
    for (; i + 4 <= m; i += 4) {
        __m256i x = _mm256_loadu_si256((const __m256i *)(src + i));
        __m256i y = _mm256_loadu_si256((const __m256i *)(other + i));
        if (!_mm256_testz_si256(x, y)) return true;
    }
    for (; i < m; ++i) {
        if (src[i] & other[i]) return true;
    }
    return false;
}

#endif
}

#endif

/**
 * @brief bitsetの共通集計処理
 */
