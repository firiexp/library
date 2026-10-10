#if defined(__x86_64__) || defined(_M_X64)
#include <immintrin.h>
#endif

using namespace std;

namespace dynamic_bitset_detail {
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
}  // namespace dynamic_bitset_detail

class DynamicBitset {
    static constexpr int B = 64;
    using Word = unsigned long long;

    int n;
    vector<Word> a;

    static int popcount(Word x) {
        return __builtin_popcountll(x);
    }
    static int ctz(Word x) {
        return __builtin_ctzll(x);
    }
    static int clz(Word x) {
        return __builtin_clzll(x);
    }

    Word tail_mask() const {
        int rem = n & (B - 1);
        return rem ? ((1ULL << rem) - 1) : ~0ULL;
    }

    void normalize() {
        if (!a.empty()) a.back() &= tail_mask();
    }

public:
    DynamicBitset() : n(0) {}
    explicit DynamicBitset(int n, bool x = false) : n(n), a((n + B - 1) >> 6, x ? ~0ULL : 0ULL) {
        normalize();
    }

    int size() const { return n; }
    bool empty() const { return n == 0; }

    void reset() {
        fill(a.begin(), a.end(), 0);
    }
    void set() {
        fill(a.begin(), a.end(), ~0ULL);
        normalize();
    }
    void flip() {
        Word *p = a.data();
        int m = (int)a.size();
        for (int i = 0; i < m; ++i) p[i] = ~p[i];
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
        int m = (int)a.size();
        const Word *p = a.data();
#if defined(__x86_64__) || defined(_M_X64)
        if (m >= dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2()) {
            return dynamic_bitset_detail::any_avx2(p, m);
        }
#endif
        for (int i = 0; i < m; ++i) {
            if (p[i]) return true;
        }
        return false;
    }
    bool none() const { return !any(); }
    bool all() const {
        int m = (int)a.size();
        if (m == 0) return true;
        const Word *p = a.data();
#if defined(__x86_64__) || defined(_M_X64)
        if (m > 1 + dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2()) {
            if (!dynamic_bitset_detail::all_full_words_avx2(p, m - 1)) return false;
        } else
#endif
        {
            for (int i = 0; i + 1 < m; ++i) {
                if (p[i] != ~0ULL) return false;
            }
        }
        return p[m - 1] == tail_mask();
    }
    int count() const {
        const Word *p = a.data();
        int m = (int)a.size();
        int res = 0;
        int i = 0;
        for (; i + 4 <= m; i += 4) {
            res += popcount(p[i + 0]) + popcount(p[i + 1]) + popcount(p[i + 2]) + popcount(p[i + 3]);
        }
        for (; i < m; ++i) res += popcount(p[i]);
        return res;
    }

    int find_first() const {
        int m = (int)a.size();
        const Word *p = a.data();
        for (int i = 0; i < m; ++i) {
            if (p[i]) return (i << 6) + ctz(p[i]);
        }
        return -1;
    }
    int find_last() const {
        const Word *p = a.data();
        for (int i = (int)a.size() - 1; i >= 0; --i) {
            if (p[i]) return (i << 6) + (B - 1 - clz(p[i]));
        }
        return -1;
    }
    int find_next(int k) const {
        ++k;
        if (k >= n) return -1;
        const Word *p = a.data();
        int i = k >> 6;
        Word x = p[i] & (~0ULL << (k & 63));
        if (x) return (i << 6) + ctz(x);
        int m = (int)a.size();
        for (++i; i < m; ++i) {
            if (p[i]) return (i << 6) + ctz(p[i]);
        }
        return -1;
    }
    int find_prev(int k) const {
        --k;
        if (k < 0) return -1;
        const Word *p = a.data();
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

    DynamicBitset &operator&=(const DynamicBitset &r) {
        Word *p = a.data();
        const Word *q = r.a.data();
        int m = (int)a.size();
#if defined(__x86_64__) || defined(_M_X64)
        if (m >= dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2()) {
            dynamic_bitset_detail::and_assign_avx2(p, q, m);
            return *this;
        }
#endif
        for (int i = 0; i < m; ++i) p[i] &= q[i];
        return *this;
    }
    DynamicBitset &operator|=(const DynamicBitset &r) {
        Word *p = a.data();
        const Word *q = r.a.data();
        int m = (int)a.size();
#if defined(__x86_64__) || defined(_M_X64)
        if (m >= dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2()) {
            dynamic_bitset_detail::or_assign_avx2(p, q, m);
            return *this;
        }
#endif
        for (int i = 0; i < m; ++i) p[i] |= q[i];
        return *this;
    }
    DynamicBitset &operator^=(const DynamicBitset &r) {
        Word *p = a.data();
        const Word *q = r.a.data();
        int m = (int)a.size();
#if defined(__x86_64__) || defined(_M_X64)
        if (m >= dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2()) {
            dynamic_bitset_detail::xor_assign_avx2(p, q, m);
            normalize();
            return *this;
        }
#endif
        for (int i = 0; i < m; ++i) p[i] ^= q[i];
        normalize();
        return *this;
    }

    friend DynamicBitset operator&(DynamicBitset l, const DynamicBitset &r) { l &= r; return l; }
    friend DynamicBitset operator|(DynamicBitset l, const DynamicBitset &r) { l |= r; return l; }
    friend DynamicBitset operator^(DynamicBitset l, const DynamicBitset &r) { l ^= r; return l; }

    DynamicBitset &operator<<=(int s) {
        if (s <= 0 || n == 0) return *this;
        if (s >= n) {
            reset();
            return *this;
        }
        if (s == 1) {
            Word carry = 0;
            for (int i = 0; i < (int)a.size(); ++i) {
                Word next = a[i] >> (B - 1);
                a[i] = (a[i] << 1) | carry;
                carry = next;
            }
            normalize();
            return *this;
        }
        int m = (int)a.size();
        int block = s >> 6;
        int rem = s & 63;
        if (rem == 0) {
            memmove(a.data() + block, a.data(), sizeof(Word) * (m - block));
        } else {
            for (int i = m - 1; i > block; --i) {
                a[i] = (a[i - block] << rem) | (a[i - block - 1] >> (B - rem));
            }
            a[block] = a[0] << rem;
        }
        fill(a.begin(), a.begin() + block, 0);
        normalize();
        return *this;
    }
    DynamicBitset &operator>>=(int s) {
        if (s <= 0 || n == 0) return *this;
        if (s >= n) {
            reset();
            return *this;
        }
        if (s == 1) {
            int m = (int)a.size();
            for (int i = 0; i < m; ++i) {
                Word next = i + 1 < m ? (a[i + 1] << (B - 1)) : 0;
                a[i] = (a[i] >> 1) | next;
            }
            normalize();
            return *this;
        }
        int m = (int)a.size();
        int block = s >> 6;
        int rem = s & 63;
        if (rem == 0) {
            memmove(a.data(), a.data() + block, sizeof(Word) * (m - block));
        } else {
            int last = m - block - 1;
            for (int i = 0; i < last; ++i) {
                a[i] = (a[i + block] >> rem) | (a[i + block + 1] << (B - rem));
            }
            a[last] = a[m - 1] >> rem;
        }
        fill(a.begin() + (m - block), a.end(), 0);
        normalize();
        return *this;
    }

    DynamicBitset &or_shift_left(int s) {
        if (s <= 0 || s >= n) return *this;
        int m = (int)a.size();
        int block = s >> 6;
        int rem = s & 63;
        if (rem == 0) {
            for (int i = m - 1; i >= block; --i) a[i] |= a[i - block];
        } else {
            for (int i = m - 1; i > block; --i) {
                a[i] |= (a[i - block] << rem) | (a[i - block - 1] >> (B - rem));
            }
            a[block] |= a[0] << rem;
        }
        normalize();
        return *this;
    }

    DynamicBitset &or_shift_right(int s) {
        if (s <= 0 || s >= n) return *this;
        int m = (int)a.size();
        int block = s >> 6;
        int rem = s & 63;
        if (rem == 0) {
            for (int i = 0; i < m - block; ++i) a[i] |= a[i + block];
        } else {
            int last = m - block - 1;
            for (int i = 0; i < last; ++i) {
                a[i] |= (a[i + block] >> rem) | (a[i + block + 1] << (B - rem));
            }
            a[last] |= a[m - 1] >> rem;
        }
        return *this;
    }

    friend DynamicBitset operator<<(DynamicBitset l, int s) { l <<= s; return l; }
    friend DynamicBitset operator>>(DynamicBitset l, int s) { l >>= s; return l; }
};

/**
 * @brief 動的bitset(Dynamic Bitset)
 */
