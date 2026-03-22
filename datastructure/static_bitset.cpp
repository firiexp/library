#if defined(__x86_64__) || defined(_M_X64)
#include <immintrin.h>
#endif

using namespace std;

namespace static_bitset_detail {
using Word = unsigned long long;
constexpr int avx2_threshold_words = 8;

#if defined(__x86_64__) || defined(_M_X64)
__attribute__((target("avx2"))) inline void and_assign_avx2(Word *dst, const Word *src, int m) {
    int i = 0;
    for (; i + 4 <= m; i += 4) {
        __m256i x = _mm256_loadu_si256((const __m256i *)(dst + i));
        __m256i y = _mm256_loadu_si256((const __m256i *)(src + i));
        _mm256_storeu_si256((__m256i *)(dst + i), _mm256_and_si256(x, y));
    }
    for (; i < m; ++i) dst[i] &= src[i];
}

__attribute__((target("avx2"))) inline void or_assign_avx2(Word *dst, const Word *src, int m) {
    int i = 0;
    for (; i + 4 <= m; i += 4) {
        __m256i x = _mm256_loadu_si256((const __m256i *)(dst + i));
        __m256i y = _mm256_loadu_si256((const __m256i *)(src + i));
        _mm256_storeu_si256((__m256i *)(dst + i), _mm256_or_si256(x, y));
    }
    for (; i < m; ++i) dst[i] |= src[i];
}

__attribute__((target("avx2"))) inline void xor_assign_avx2(Word *dst, const Word *src, int m) {
    int i = 0;
    for (; i + 4 <= m; i += 4) {
        __m256i x = _mm256_loadu_si256((const __m256i *)(dst + i));
        __m256i y = _mm256_loadu_si256((const __m256i *)(src + i));
        _mm256_storeu_si256((__m256i *)(dst + i), _mm256_xor_si256(x, y));
    }
    for (; i < m; ++i) dst[i] ^= src[i];
}

__attribute__((target("avx2"))) inline bool any_avx2(const Word *src, int m) {
    __m256i acc = _mm256_setzero_si256();
    int i = 0;
    for (; i + 4 <= m; i += 4) {
        acc = _mm256_or_si256(acc, _mm256_loadu_si256((const __m256i *)(src + i)));
    }
    if (!_mm256_testz_si256(acc, acc)) return true;
    for (; i < m; ++i) {
        if (src[i]) return true;
    }
    return false;
}

__attribute__((target("avx2"))) inline bool all_full_words_avx2(const Word *src, int m) {
    const __m256i ones = _mm256_set1_epi64x(-1);
    int i = 0;
    for (; i + 4 <= m; i += 4) {
        __m256i x = _mm256_loadu_si256((const __m256i *)(src + i));
        __m256i eq = _mm256_cmpeq_epi64(x, ones);
        if (_mm256_movemask_epi8(eq) != -1) return false;
    }
    for (; i < m; ++i) {
        if (src[i] != ~0ULL) return false;
    }
    return true;
}

inline bool has_avx2() {
    static const bool cached = __builtin_cpu_supports("avx2");
    return cached;
}
#endif
}  // namespace static_bitset_detail

template<int N>
class StaticBitset {
    static_assert(N >= 0);
    static constexpr int B = 64;
    static constexpr int M = (N + B - 1) >> 6;
    using Word = unsigned long long;

    Word a[M > 0 ? M : 1];

    static int popcount(Word x) {
        return __builtin_popcountll(x);
    }
    static int ctz(Word x) {
        return __builtin_ctzll(x);
    }
    static int clz(Word x) {
        return __builtin_clzll(x);
    }
    static constexpr Word tail_mask() {
        return N % B ? ((1ULL << (N % B)) - 1) : ~0ULL;
    }
    void normalize() {
        if constexpr (M > 0) a[M - 1] &= tail_mask();
    }

public:
    explicit StaticBitset(bool x = false) : a{} {
        if (x) set();
    }

    int size() const { return N; }
    bool empty() const { return N == 0; }

    void reset() {
        fill(a, a + M, 0);
    }
    void set() {
        fill(a, a + M, ~0ULL);
        normalize();
    }
    void flip() {
        for (Word &x : a) x = ~x;
        normalize();
    }

    bool test(int k) const {
        return (a[k >> 6] >> (k & 63)) & 1ULL;
    }
    void set(int k) {
        a[k >> 6] |= 1ULL << (k & 63);
    }
    void reset(int k) {
        a[k >> 6] &= ~(1ULL << (k & 63));
    }
    void flip(int k) {
        a[k >> 6] ^= 1ULL << (k & 63);
    }
    void assign(int k, bool x) {
        if (x) set(k);
        else reset(k);
    }

    bool any() const {
        const Word *p = a;
#if defined(__x86_64__) || defined(_M_X64)
        if constexpr (M >= static_bitset_detail::avx2_threshold_words) {
            if (static_bitset_detail::has_avx2()) return static_bitset_detail::any_avx2(p, M);
        }
#endif
        for (int i = 0; i < M; ++i) {
            if (p[i]) return true;
        }
        return false;
    }
    bool none() const { return !any(); }
    bool all() const {
        if constexpr (M == 0) return true;
        const Word *p = a;
#if defined(__x86_64__) || defined(_M_X64)
        if constexpr (M > 1 + static_bitset_detail::avx2_threshold_words) {
            if (static_bitset_detail::has_avx2()) {
                if (!static_bitset_detail::all_full_words_avx2(p, M - 1)) return false;
                return p[M - 1] == tail_mask();
            }
        }
#endif
        for (int i = 0; i + 1 < M; ++i) {
            if (p[i] != ~0ULL) return false;
        }
        return p[M - 1] == tail_mask();
    }
    int count() const {
        const Word *p = a;
        int res = 0;
        int i = 0;
        for (; i + 4 <= M; i += 4) {
            res += popcount(p[i + 0]) + popcount(p[i + 1]) + popcount(p[i + 2]) + popcount(p[i + 3]);
        }
        for (; i < M; ++i) res += popcount(p[i]);
        return res;
    }

    int find_first() const {
        const Word *p = a;
        for (int i = 0; i < M; ++i) {
            if (p[i]) return (i << 6) + ctz(p[i]);
        }
        return -1;
    }
    int find_last() const {
        const Word *p = a;
        for (int i = M - 1; i >= 0; --i) {
            if (p[i]) return (i << 6) + (B - 1 - clz(p[i]));
        }
        return -1;
    }
    int find_next(int k) const {
        ++k;
        if (k >= N) return -1;
        const Word *p = a;
        int i = k >> 6;
        Word x = p[i] & (~0ULL << (k & 63));
        if (x) return (i << 6) + ctz(x);
        for (++i; i < M; ++i) {
            if (p[i]) return (i << 6) + ctz(p[i]);
        }
        return -1;
    }
    int find_prev(int k) const {
        --k;
        if (k < 0) return -1;
        const Word *p = a;
        int i = k >> 6;
        int rem = k & 63;
        Word mask = rem == B - 1 ? ~0ULL : ((1ULL << (rem + 1)) - 1);
        Word x = p[i] & mask;
        if (x) return (i << 6) + (B - 1 - clz(x));
        for (--i; i >= 0; --i) {
            if (p[i]) return (i << 6) + (B - 1 - clz(p[i]));
        }
        return -1;
    }

    StaticBitset &operator&=(const StaticBitset &r) {
        Word *p = a;
        const Word *q = r.a;
#if defined(__x86_64__) || defined(_M_X64)
        if constexpr (M >= static_bitset_detail::avx2_threshold_words) {
            if (static_bitset_detail::has_avx2()) {
                static_bitset_detail::and_assign_avx2(p, q, M);
                return *this;
            }
        }
#endif
        for (int i = 0; i < M; ++i) p[i] &= q[i];
        return *this;
    }
    StaticBitset &operator|=(const StaticBitset &r) {
        Word *p = a;
        const Word *q = r.a;
#if defined(__x86_64__) || defined(_M_X64)
        if constexpr (M >= static_bitset_detail::avx2_threshold_words) {
            if (static_bitset_detail::has_avx2()) {
                static_bitset_detail::or_assign_avx2(p, q, M);
                return *this;
            }
        }
#endif
        for (int i = 0; i < M; ++i) p[i] |= q[i];
        return *this;
    }
    StaticBitset &operator^=(const StaticBitset &r) {
        Word *p = a;
        const Word *q = r.a;
#if defined(__x86_64__) || defined(_M_X64)
        if constexpr (M >= static_bitset_detail::avx2_threshold_words) {
            if (static_bitset_detail::has_avx2()) {
                static_bitset_detail::xor_assign_avx2(p, q, M);
                normalize();
                return *this;
            }
        }
#endif
        for (int i = 0; i < M; ++i) p[i] ^= q[i];
        normalize();
        return *this;
    }

    friend StaticBitset operator&(StaticBitset l, const StaticBitset &r) { return l &= r; }
    friend StaticBitset operator|(StaticBitset l, const StaticBitset &r) { return l |= r; }
    friend StaticBitset operator^(StaticBitset l, const StaticBitset &r) { return l ^= r; }

    StaticBitset &operator<<=(int s) {
        if (s <= 0 || N == 0) return *this;
        if (s >= N) {
            reset();
            return *this;
        }
        if (s == 1) {
            Word carry = 0;
            for (int i = 0; i < M; ++i) {
                Word next = a[i] >> (B - 1);
                a[i] = (a[i] << 1) | carry;
                carry = next;
            }
            normalize();
            return *this;
        }
        int block = s >> 6;
        int rem = s & 63;
        if (rem == 0) {
            memmove(a + block, a, sizeof(Word) * (M - block));
        } else {
            for (int i = M - 1; i > block; --i) {
                a[i] = (a[i - block] << rem) | (a[i - block - 1] >> (B - rem));
            }
            a[block] = a[0] << rem;
        }
        fill(a, a + block, 0);
        normalize();
        return *this;
    }
    StaticBitset &operator>>=(int s) {
        if (s <= 0 || N == 0) return *this;
        if (s >= N) {
            reset();
            return *this;
        }
        if (s == 1) {
            for (int i = 0; i < M; ++i) {
                Word next = i + 1 < M ? (a[i + 1] << (B - 1)) : 0;
                a[i] = (a[i] >> 1) | next;
            }
            normalize();
            return *this;
        }
        int block = s >> 6;
        int rem = s & 63;
        if (rem == 0) {
            memmove(a, a + block, sizeof(Word) * (M - block));
        } else {
            int last = M - block - 1;
            for (int i = 0; i < last; ++i) {
                a[i] = (a[i + block] >> rem) | (a[i + block + 1] << (B - rem));
            }
            a[last] = a[M - 1] >> rem;
        }
        fill(a + (M - block), a + M, 0);
        normalize();
        return *this;
    }

    friend StaticBitset operator<<(StaticBitset l, int s) { return l <<= s; }
    friend StaticBitset operator>>(StaticBitset l, int s) { return l >>= s; }
};

/**
 * @brief 固定長bitset(Static Bitset)
 */
