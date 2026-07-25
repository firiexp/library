---
category: "\u6570\u5B66"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/integer_convolution.cpp
    title: "\u6574\u6570\u7573\u307F\u8FBC\u307F(2/3 NTT)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_addition_of_big_integers.test.cpp
    title: test/yosupo_addition_of_big_integers.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_addition_of_hex_big_integers.test.cpp
    title: test/yosupo_addition_of_hex_big_integers.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_division_of_big_integers.test.cpp
    title: test/yosupo_division_of_big_integers.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_division_of_hex_big_integers.test.cpp
    title: test/yosupo_division_of_hex_big_integers.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_multiplication_of_big_integers.test.cpp
    title: test/yosupo_multiplication_of_big_integers.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_multiplication_of_hex_big_integers.test.cpp
    title: test/yosupo_multiplication_of_hex_big_integers.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u591A\u500D\u9577\u6574\u6570(BigInteger)"
    links: []
  bundledCode: "#line 1 \"util/biginteger.cpp\"\n\n\n\n#line 1 \"math/integer_convolution.cpp\"\
    \n\n\n\n#ifndef FIRIEXP_LIBRARY_ARBITRARY_CONVOLUTION_U64_NAIVE_THRESHOLD\n#define\
    \ FIRIEXP_LIBRARY_ARBITRARY_CONVOLUTION_U64_NAIVE_THRESHOLD 8192\n#endif\n\n#ifndef\
    \ FIRIEXP_LIBRARY_ARBITRARY_SQUARE_U64_NAIVE_THRESHOLD\n#define FIRIEXP_LIBRARY_ARBITRARY_SQUARE_U64_NAIVE_THRESHOLD\
    \ 32768\n#endif\n\nnamespace ArbitraryConvolution {\n    template<unsigned int\
    \ M>\n    struct StaticModInt {\n        unsigned int val;\n        StaticModInt()\
    \ : val(0) {}\n        template<class T>\n        StaticModInt(T v) {\n      \
    \      long long x = (long long)(v % (long long)M);\n            if (x < 0) x\
    \ += M;\n            val = (unsigned int)x;\n        }\n        static StaticModInt\
    \ raw(unsigned int v) {\n            StaticModInt x;\n            x.val = v;\n\
    \            return x;\n        }\n        StaticModInt& operator+=(const StaticModInt&\
    \ rhs) {\n            val += rhs.val;\n            if (val >= M) val -= M;\n \
    \           return *this;\n        }\n        StaticModInt& operator-=(const StaticModInt&\
    \ rhs) {\n            val -= rhs.val;\n            if (val >= M) val += M;\n \
    \           return *this;\n        }\n        StaticModInt& operator*=(const StaticModInt&\
    \ rhs) {\n            val = (unsigned int)((unsigned long long)val * rhs.val %\
    \ M);\n            return *this;\n        }\n        StaticModInt pow(long long\
    \ n) const {\n            StaticModInt x = *this, r = 1;\n            while (n)\
    \ {\n                if (n & 1) r *= x;\n                x *= x;\n           \
    \     n >>= 1;\n            }\n            return r;\n        }\n        StaticModInt\
    \ inv() const { return pow(M - 2); }\n        friend StaticModInt operator+(StaticModInt\
    \ lhs, const StaticModInt& rhs) { return lhs += rhs; }\n        friend StaticModInt\
    \ operator-(StaticModInt lhs, const StaticModInt& rhs) { return lhs -= rhs; }\n\
    \        friend StaticModInt operator*(StaticModInt lhs, const StaticModInt& rhs)\
    \ { return lhs *= rhs; }\n        friend bool operator==(const StaticModInt& lhs,\
    \ const StaticModInt& rhs) { return lhs.val == rhs.val; }\n        friend bool\
    \ operator!=(const StaticModInt& lhs, const StaticModInt& rhs) { return lhs.val\
    \ != rhs.val; }\n    };\n\n    template<unsigned int MOD_, unsigned int PRIMITIVE_ROOT_>\n\
    \    struct NTT {\n        using mint = StaticModInt<MOD_>;\n        static constexpr\
    \ unsigned int MODV = MOD_;\n        static constexpr unsigned int G = PRIMITIVE_ROOT_;\n\
    \        mint root[30], iroot[30], rate2[30], irate2[30], rate3[30], irate3[30],\
    \ inv_pow2[30];\n        int max_base;\n\n        NTT() : max_base(__builtin_ctz(MODV\
    \ - 1)) {\n            mint e = mint(G).pow((MODV - 1) >> max_base), ie = e.inv();\n\
    \            for (int i = max_base; i >= 0; --i) {\n                root[i] =\
    \ e;\n                iroot[i] = ie;\n                e *= e;\n              \
    \  ie *= ie;\n            }\n            mint prod = 1, iprod = 1;\n         \
    \   for (int i = 0; i <= max_base - 2; ++i) {\n                rate2[i] = root[i\
    \ + 2] * prod;\n                irate2[i] = iroot[i + 2] * iprod;\n          \
    \      prod *= iroot[i + 2];\n                iprod *= root[i + 2];\n        \
    \    }\n            prod = 1;\n            iprod = 1;\n            for (int i\
    \ = 0; i <= max_base - 3; ++i) {\n                rate3[i] = root[i + 3] * prod;\n\
    \                irate3[i] = iroot[i + 3] * iprod;\n                prod *= iroot[i\
    \ + 3];\n                iprod *= root[i + 3];\n            }\n            inv_pow2[0]\
    \ = 1;\n            mint inv2 = mint(2).inv();\n            for (int i = 1; i\
    \ < 30; ++i) inv_pow2[i] = inv_pow2[i - 1] * inv2;\n        }\n\n        mint\
    \ inv_size(int n) const {\n            return inv_pow2[__builtin_ctz((unsigned\
    \ int)n)];\n        }\n\n        void ntt(vector<mint> &a, bool invert) const\
    \ {\n            int n = (int)a.size();\n            assert(n > 0);\n        \
    \    assert((n & (n - 1)) == 0);\n            assert(__builtin_ctz((unsigned int)n)\
    \ <= max_base);\n            int h = __builtin_ctz((unsigned int)n);\n       \
    \     if (!invert) {\n                int len = 0;\n                while (len\
    \ < h) {\n                    if (h - len == 1) {\n                        int\
    \ p = 1 << (h - len - 1);\n                        mint rot = 1;\n           \
    \             for (int s = 0; s < (1 << len); ++s) {\n                       \
    \     int offset = s << (h - len);\n                            for (int i = 0;\
    \ i < p; ++i) {\n                                mint l = a[i + offset];\n   \
    \                             mint r = a[i + offset + p] * rot;\n            \
    \                    a[i + offset] = l + r;\n                                a[i\
    \ + offset + p] = l - r;\n                            }\n                    \
    \        if (s + 1 != (1 << len)) {\n                                rot *= rate2[__builtin_ctz(~(unsigned\
    \ int)s)];\n                            }\n                        }\n       \
    \                 ++len;\n                    } else {\n                     \
    \   int p = 1 << (h - len - 2);\n                        mint rot = 1, imag =\
    \ root[2];\n                        for (int s = 0; s < (1 << len); ++s) {\n \
    \                           mint rot2 = rot * rot;\n                         \
    \   mint rot3 = rot2 * rot;\n                            int offset = s << (h\
    \ - len);\n                            unsigned long long mod2 = 1ULL * MODV *\
    \ MODV;\n                            for (int i = 0; i < p; ++i) {\n         \
    \                       unsigned long long a0 = a[i + offset].val;\n         \
    \                       unsigned long long a1 = 1ULL * a[i + offset + p].val *\
    \ rot.val;\n                                unsigned long long a2 = 1ULL * a[i\
    \ + offset + 2 * p].val * rot2.val;\n                                unsigned\
    \ long long a3 = 1ULL * a[i + offset + 3 * p].val * rot3.val;\n              \
    \                  unsigned long long a1na3imag = 1ULL * mint(a1 + mod2 - a3).val\
    \ * imag.val;\n                                unsigned long long na2 = mod2 -\
    \ a2;\n                                a[i + offset] = mint(a0 + a2 + a1 + a3);\n\
    \                                a[i + offset + p] = mint(a0 + a2 + (2 * mod2\
    \ - (a1 + a3)));\n                                a[i + offset + 2 * p] = mint(a0\
    \ + na2 + a1na3imag);\n                                a[i + offset + 3 * p] =\
    \ mint(a0 + na2 + (mod2 - a1na3imag));\n                            }\n      \
    \                      if (s + 1 != (1 << len)) {\n                          \
    \      rot *= rate3[__builtin_ctz(~(unsigned int)s)];\n                      \
    \      }\n                        }\n                        len += 2;\n     \
    \               }\n                }\n            } else {\n                int\
    \ len = h;\n                while (len) {\n                    if (len == 1) {\n\
    \                        int p = 1 << (h - len);\n                        mint\
    \ irot = 1;\n                        for (int s = 0; s < (1 << (len - 1)); ++s)\
    \ {\n                            int offset = s << (h - len + 1);\n          \
    \                  for (int i = 0; i < p; ++i) {\n                           \
    \     mint l = a[i + offset];\n                                mint r = a[i +\
    \ offset + p];\n                                a[i + offset] = l + r;\n     \
    \                           a[i + offset + p] = mint(1ULL * (MODV + l.val - r.val)\
    \ * irot.val);\n                            }\n                            if\
    \ (s + 1 != (1 << (len - 1))) {\n                                irot *= irate2[__builtin_ctz(~(unsigned\
    \ int)s)];\n                            }\n                        }\n       \
    \                 --len;\n                    } else {\n                     \
    \   int p = 1 << (h - len);\n                        mint irot = 1, iimag = iroot[2];\n\
    \                        for (int s = 0; s < (1 << (len - 2)); ++s) {\n      \
    \                      mint irot2 = irot * irot;\n                           \
    \ mint irot3 = irot2 * irot;\n                            int offset = s << (h\
    \ - len + 2);\n                            for (int i = 0; i < p; ++i) {\n   \
    \                             unsigned long long a0 = a[i + offset].val;\n   \
    \                             unsigned long long a1 = a[i + offset + p].val;\n\
    \                                unsigned long long a2 = a[i + offset + 2 * p].val;\n\
    \                                unsigned long long a3 = a[i + offset + 3 * p].val;\n\
    \                                unsigned long long a2na3iimag = 1ULL * mint(1ULL\
    \ * (MODV + a2 - a3) * iimag.val).val;\n                                a[i +\
    \ offset] = mint(a0 + a1 + a2 + a3);\n                                a[i + offset\
    \ + p] = mint(a0 + (MODV - a1) + a2na3iimag) * irot;\n                       \
    \         a[i + offset + 2 * p] = mint(a0 + a1 + (MODV - a2) + (MODV - a3)) *\
    \ irot2;\n                                a[i + offset + 3 * p] = mint(a0 + (MODV\
    \ - a1) + (MODV - a2na3iimag)) * irot3;\n                            }\n     \
    \                       if (s + 1 != (1 << (len - 2))) {\n                   \
    \             irot *= irate3[__builtin_ctz(~(unsigned int)s)];\n             \
    \               }\n                        }\n                        len -= 2;\n\
    \                    }\n                }\n            }\n        }\n\n      \
    \  vector<unsigned int> convolution(const vector<unsigned int> &a, const vector<unsigned\
    \ int> &b) const {\n            if (a.empty() || b.empty()) return {};\n     \
    \       int need = (int)a.size() + (int)b.size() - 1;\n            int n = 1;\n\
    \            while (n < need) n <<= 1;\n            vector<mint> fa(n), fb(n);\n\
    \            for (int i = 0; i < (int)a.size(); ++i) fa[i] = a[i];\n         \
    \   for (int i = 0; i < (int)b.size(); ++i) fb[i] = b[i];\n            ntt(fa,\
    \ false);\n            ntt(fb, false);\n            for (int i = 0; i < n; ++i)\
    \ fa[i] *= fb[i];\n            ntt(fa, true);\n            mint iz = inv_size(n);\n\
    \            vector<unsigned int> res(need);\n            for (int i = 0; i <\
    \ need; ++i) res[i] = (fa[i] * iz).val;\n            return res;\n        }\n\n\
    \        vector<unsigned int> square(const vector<unsigned int> &a) const {\n\
    \            if (a.empty()) return {};\n            int need = (int)a.size() *\
    \ 2 - 1;\n            int n = 1;\n            while (n < need) n <<= 1;\n    \
    \        vector<mint> fa(n);\n            for (int i = 0; i < (int)a.size(); ++i)\
    \ fa[i] = a[i];\n            ntt(fa, false);\n            for (int i = 0; i <\
    \ n; ++i) fa[i] *= fa[i];\n            ntt(fa, true);\n            mint iz = inv_size(n);\n\
    \            vector<unsigned int> res(need);\n            for (int i = 0; i <\
    \ need; ++i) res[i] = (fa[i] * iz).val;\n            return res;\n        }\n\
    \    };\n\n    using NTT1 = NTT<167772161, 3>;\n    using NTT2 = NTT<469762049,\
    \ 3>;\n    using NTT3 = NTT<1224736769, 3>;\n\n    namespace internal {\n    \
    \    static constexpr int CONVOLUTION_U64_NAIVE_THRESHOLD = FIRIEXP_LIBRARY_ARBITRARY_CONVOLUTION_U64_NAIVE_THRESHOLD;\n\
    \        static constexpr int SQUARE_U64_NAIVE_THRESHOLD = FIRIEXP_LIBRARY_ARBITRARY_SQUARE_U64_NAIVE_THRESHOLD;\n\
    \n        inline const NTT1& ntt1() {\n            static const NTT1 value;\n\
    \            return value;\n        }\n\n        inline const NTT2& ntt2() {\n\
    \            static const NTT2 value;\n            return value;\n        }\n\n\
    \        inline const NTT3& ntt3() {\n            static const NTT3 value;\n \
    \           return value;\n        }\n\n        inline unsigned long long combine_u64(unsigned\
    \ int x1, unsigned int x2, unsigned int x3) {\n            static const unsigned\
    \ long long m1 = 167772161ULL;\n            static const unsigned long long m2\
    \ = 469762049ULL;\n            static const unsigned long long m3 = 1224736769ULL;\n\
    \            static const unsigned long long m1_inv_m2 = StaticModInt<469762049>(m1).inv().val;\n\
    \            static const unsigned long long m12_mod_m3 = (m1 % m3) * (m2 % m3)\
    \ % m3;\n            static const unsigned long long m12_inv_m3 = StaticModInt<1224736769>(m12_mod_m3).inv().val;\n\
    \            static const unsigned long long m12 = m1 * m2;\n\n            unsigned\
    \ long long t = (x2 + m2 - x1 % m2) % m2;\n            t = t * m1_inv_m2 % m2;\n\
    \            unsigned long long x12 = (x1 + (__uint128_t)m1 * t) % m3;\n     \
    \       unsigned long long u = (x3 + m3 - x12) % m3;\n            u = u * m12_inv_m3\
    \ % m3;\n            return (unsigned long long)((__uint128_t)x1 + (__uint128_t)m1\
    \ * t + (__uint128_t)m12 * u);\n        }\n\n        template<unsigned int TARGET_MOD>\n\
    \        inline unsigned int combine_mod(unsigned int x1, unsigned int x2, unsigned\
    \ int x3) {\n            static const long long m1 = 167772161LL;\n          \
    \  static const long long m2 = 469762049LL;\n            static const long long\
    \ m3 = 1224736769LL;\n            static const long long m1_inv_m2 = StaticModInt<469762049>(m1).inv().val;\n\
    \            static const long long m12_mod_m3 = (m1 % m3) * (m2 % m3) % m3;\n\
    \            static const long long m12_inv_m3 = StaticModInt<1224736769>(m12_mod_m3).inv().val;\n\
    \            static const unsigned long long m12 = (unsigned long long)m1 * (unsigned\
    \ long long)m2;\n            static const long long m1_mod = m1 % TARGET_MOD;\n\
    \            static const long long m12_mod = m12 % TARGET_MOD;\n\n          \
    \  long long t = ((long long)x2 - (long long)x1) % m2;\n            if (t < 0)\
    \ t += m2;\n            t = t * m1_inv_m2 % m2;\n            long long x12 = (long\
    \ long)(((__int128)x1 + (__int128)m1 * t) % m3);\n            long long u = ((long\
    \ long)x3 - x12) % m3;\n            if (u < 0) u += m3;\n            u = u * m12_inv_m3\
    \ % m3;\n            __int128 value = x1 % TARGET_MOD;\n            value += (__int128)m1_mod\
    \ * t;\n            value += (__int128)m12_mod * u;\n            return (unsigned\
    \ int)(value % TARGET_MOD);\n        }\n    }  // namespace internal\n\n    vector<unsigned\
    \ long long> convolution_u64(const vector<unsigned int> &a, const vector<unsigned\
    \ int> &b) {\n        if (a.empty() || b.empty()) return {};\n        if (1LL\
    \ * (int)a.size() * (int)b.size() <= internal::CONVOLUTION_U64_NAIVE_THRESHOLD)\
    \ {\n            vector<unsigned long long> res(a.size() + b.size() - 1);\n  \
    \          for (int i = 0; i < (int)a.size(); ++i) {\n                for (int\
    \ j = 0; j < (int)b.size(); ++j) {\n                    res[i + j] += (unsigned\
    \ long long)a[i] * b[j];\n                }\n            }\n            return\
    \ res;\n        }\n\n        auto c1 = internal::ntt1().convolution(a, b);\n \
    \       auto c2 = internal::ntt2().convolution(a, b);\n        auto c3 = internal::ntt3().convolution(a,\
    \ b);\n        vector<unsigned long long> res(c1.size());\n        for (int i\
    \ = 0; i < (int)res.size(); ++i) {\n            res[i] = internal::combine_u64(c1[i],\
    \ c2[i], c3[i]);\n        }\n        return res;\n    }\n\n    vector<unsigned\
    \ long long> square_u64(const vector<unsigned int> &a) {\n        if (a.empty())\
    \ return {};\n        if (1LL * (int)a.size() * (int)a.size() <= internal::SQUARE_U64_NAIVE_THRESHOLD)\
    \ {\n            vector<unsigned long long> res(a.size() * 2 - 1);\n         \
    \   for (int i = 0; i < (int)a.size(); ++i) {\n                res[i + i] += (unsigned\
    \ long long)a[i] * a[i];\n                for (int j = i + 1; j < (int)a.size();\
    \ ++j) {\n                    res[i + j] += 2ULL * (unsigned long long)a[i] *\
    \ a[j];\n                }\n            }\n            return res;\n        }\n\
    \n        auto c1 = internal::ntt1().square(a);\n        auto c2 = internal::ntt2().square(a);\n\
    \        auto c3 = internal::ntt3().square(a);\n        vector<unsigned long long>\
    \ res(c1.size());\n        for (int i = 0; i < (int)res.size(); ++i) {\n     \
    \       res[i] = internal::combine_u64(c1[i], c2[i], c3[i]);\n        }\n    \
    \    return res;\n    }\n}\n\nnamespace BoundedConvolution {\n    using NTT1 =\
    \ ArbitraryConvolution::NTT<998244353, 3>;\n    using NTT2 = ArbitraryConvolution::NTT<1004535809,\
    \ 3>;\n\n    namespace internal {\n        inline const NTT1& ntt1() {\n     \
    \       static const NTT1 value;\n            return value;\n        }\n\n   \
    \     inline const NTT2& ntt2() {\n            static const NTT2 value;\n    \
    \        return value;\n        }\n\n        inline unsigned long long combine_u64(unsigned\
    \ int x1, unsigned int x2) {\n            static constexpr unsigned long long\
    \ m1 = 998244353ULL;\n            static constexpr unsigned long long m2 = 1004535809ULL;\n\
    \            static const unsigned long long m1_inv_m2 =\n                ArbitraryConvolution::StaticModInt<1004535809>(m1).inv().val;\n\
    \            unsigned long long delta = (x2 + m2 - x1 % m2) % m2;\n          \
    \  unsigned long long multiplier = delta * m1_inv_m2 % m2;\n            return\
    \ x1 + m1 * multiplier;\n        }\n    }\n\n    vector<unsigned long long> convolution_u64(const\
    \ vector<unsigned int> &a,\n                                                const\
    \ vector<unsigned int> &b) {\n        if (a.empty() || b.empty()) return {};\n\
    \        auto c1 = internal::ntt1().convolution(a, b);\n        auto c2 = internal::ntt2().convolution(a,\
    \ b);\n        vector<unsigned long long> res(c1.size());\n        for (int i\
    \ = 0; i < (int)res.size(); ++i) {\n            res[i] = internal::combine_u64(c1[i],\
    \ c2[i]);\n        }\n        return res;\n    }\n\n    vector<unsigned long long>\
    \ square_u64(const vector<unsigned int> &a) {\n        if (a.empty()) return {};\n\
    \        auto c1 = internal::ntt1().square(a);\n        auto c2 = internal::ntt2().square(a);\n\
    \        vector<unsigned long long> res(c1.size());\n        for (int i = 0; i\
    \ < (int)res.size(); ++i) {\n            res[i] = internal::combine_u64(c1[i],\
    \ c2[i]);\n        }\n        return res;\n    }\n}\n\n/**\n * @brief \u6574\u6570\
    \u7573\u307F\u8FBC\u307F(2/3 NTT)\n */\n\n\n#line 5 \"util/biginteger.cpp\"\n\n\
    namespace BigIntegerDetail {\n    using u32 = unsigned int;\n    using u64 = unsigned\
    \ long long;\n    using u128 = __uint128_t;\n\n    struct DecimalRadix {\n   \
    \     static constexpr u64 BASE = 10000000000000000ULL;\n        static constexpr\
    \ int IO_BASE = 10;\n        static constexpr int BLOCK_DIGITS = 16;\n       \
    \ static constexpr u32 META_BASE = 10000u;\n        static constexpr int META_DIGITS\
    \ = 4;\n    };\n\n    struct HexRadix {\n        static constexpr u64 BASE = 1ULL\
    \ << 60;\n        static constexpr int IO_BASE = 16;\n        static constexpr\
    \ int BLOCK_DIGITS = 15;\n        static constexpr u32 META_BASE = 1u << 15;\n\
    \        static constexpr int META_DIGITS = 4;\n    };\n}\n\ntemplate<class Radix>\n\
    class BasicBigInteger {\n    using u32 = BigIntegerDetail::u32;\n    using u64\
    \ = BigIntegerDetail::u64;\n    using u128 = BigIntegerDetail::u128;\n\n    static\
    \ constexpr u64 BASE = Radix::BASE;\n    static constexpr int IO_BASE = Radix::IO_BASE;\n\
    \    static constexpr int BLOCK_DIGITS = Radix::BLOCK_DIGITS;\n    static constexpr\
    \ u32 META_BASE = Radix::META_BASE;\n    static constexpr int META_DIGITS = Radix::META_DIGITS;\n\
    \    static constexpr int SCHOOLBOOK_MIN_THRESHOLD = 32;\n    static constexpr\
    \ long long SCHOOLBOOK_AREA_THRESHOLD = 4096;\n\n    vector<u64> digits;\n   \
    \ bool negative;\n\n    static int digit_value(char c) {\n        if ('0' <= c\
    \ && c <= '9') return c - '0';\n        if ('a' <= c && c <= 'z') return c - 'a'\
    \ + 10;\n        if ('A' <= c && c <= 'Z') return c - 'A' + 10;\n        return\
    \ -1;\n    }\n\n    static char digit_char(int x) {\n        return x < 10 ? char('0'\
    \ + x) : char('a' + x - 10);\n    }\n\n    void normalize() {\n        while (!digits.empty()\
    \ && digits.back() == 0) digits.pop_back();\n        if (digits.empty()) negative\
    \ = false;\n    }\n\n    static int compare_abs(const BasicBigInteger &a, const\
    \ BasicBigInteger &b) {\n        if (a.digits.size() != b.digits.size()) {\n \
    \           return a.digits.size() < b.digits.size() ? -1 : 1;\n        }\n  \
    \      for (int i = (int)a.digits.size() - 1; i >= 0; --i) {\n            if (a.digits[i]\
    \ != b.digits[i]) return a.digits[i] < b.digits[i] ? -1 : 1;\n        }\n    \
    \    return 0;\n    }\n\n    static int compare(const BasicBigInteger &a, const\
    \ BasicBigInteger &b) {\n        if (a.negative != b.negative) return a.negative\
    \ ? -1 : 1;\n        int cmp = compare_abs(a, b);\n        return a.negative ?\
    \ -cmp : cmp;\n    }\n\n    void add_abs(const BasicBigInteger &other) {\n   \
    \     if (digits.size() < other.digits.size()) digits.resize(other.digits.size(),\
    \ 0);\n        u64 carry = 0;\n        size_t i = 0;\n        for (; i < other.digits.size();\
    \ ++i) {\n            u128 cur = u128(digits[i]) + other.digits[i] + carry;\n\
    \            if (cur >= BASE) {\n                digits[i] = u64(cur - BASE);\n\
    \                carry = 1;\n            } else {\n                digits[i] =\
    \ u64(cur);\n                carry = 0;\n            }\n        }\n        for\
    \ (; i < digits.size() && carry; ++i) {\n            if (++digits[i] == BASE)\
    \ digits[i] = 0;\n            else carry = 0;\n        }\n        if (carry) digits.push_back(1);\n\
    \    }\n\n    void sub_abs(const BasicBigInteger &other) {\n        u64 borrow\
    \ = 0;\n        for (size_t i = 0; i < digits.size(); ++i) {\n            u128\
    \ rhs = borrow;\n            if (i < other.digits.size()) rhs += other.digits[i];\n\
    \            if (u128(digits[i]) < rhs) {\n                digits[i] = u64(u128(digits[i])\
    \ + BASE - rhs);\n                borrow = 1;\n            } else {\n        \
    \        digits[i] = u64(u128(digits[i]) - rhs);\n                borrow = 0;\n\
    \            }\n        }\n        normalize();\n    }\n\n    void add_small_abs(u64\
    \ value) {\n        assert(value < BASE);\n        if (value == 0) return;\n \
    \       if (digits.empty()) {\n            digits.push_back(value);\n        \
    \    return;\n        }\n        u128 cur = u128(digits[0]) + value;\n       \
    \ digits[0] = u64(cur % BASE);\n        u64 carry = u64(cur / BASE);\n       \
    \ for (size_t i = 1; i < digits.size() && carry; ++i) {\n            if (++digits[i]\
    \ == BASE) digits[i] = 0;\n            else carry = 0;\n        }\n        if\
    \ (carry) digits.push_back(carry);\n    }\n\n    void mul_small_abs(u64 value)\
    \ {\n        assert(value < BASE);\n        if (digits.empty() || value == 1)\
    \ return;\n        if (value == 0) {\n            digits.clear();\n          \
    \  negative = false;\n            return;\n        }\n        u64 carry = 0;\n\
    \        for (u64 &digit : digits) {\n            u128 cur = u128(digit) * value\
    \ + carry;\n            digit = u64(cur % BASE);\n            carry = u64(cur\
    \ / BASE);\n        }\n        if (carry) digits.push_back(carry);\n    }\n\n\
    \    u64 div_small_abs(u64 value) {\n        assert(value != 0 && value < BASE);\n\
    \        u64 remainder = 0;\n        for (int i = (int)digits.size() - 1; i >=\
    \ 0; --i) {\n            u128 cur = u128(remainder) * BASE + digits[i];\n    \
    \        digits[i] = u64(cur / value);\n            remainder = u64(cur % value);\n\
    \        }\n        normalize();\n        return remainder;\n    }\n\n    static\
    \ vector<u64> mul_small_digits(const vector<u64> &src, u64 value) {\n        if\
    \ (src.empty() || value == 0) return {};\n        vector<u64> res;\n        res.reserve(src.size()\
    \ + 1);\n        u64 carry = 0;\n        for (u64 digit : src) {\n           \
    \ u128 cur = u128(digit) * value + carry;\n            res.push_back(u64(cur %\
    \ BASE));\n            carry = u64(cur / BASE);\n        }\n        if (carry)\
    \ res.push_back(carry);\n        return res;\n    }\n\n    static u64 div_small_digits(vector<u64>\
    \ &src, u64 value) {\n        u64 remainder = 0;\n        for (int i = (int)src.size()\
    \ - 1; i >= 0; --i) {\n            u128 cur = u128(remainder) * BASE + src[i];\n\
    \            src[i] = u64(cur / value);\n            remainder = u64(cur % value);\n\
    \        }\n        while (!src.empty() && src.back() == 0) src.pop_back();\n\
    \        return remainder;\n    }\n\n    static vector<u64> mul_schoolbook_digits(const\
    \ vector<u64> &a, const vector<u64> &b) {\n        if (a.empty() || b.empty())\
    \ return {};\n        vector<u64> res(a.size() + b.size(), 0);\n        for (size_t\
    \ i = 0; i < a.size(); ++i) {\n            u64 carry = 0;\n            for (size_t\
    \ j = 0; j < b.size(); ++j) {\n                u128 cur = u128(a[i]) * b[j] +\
    \ res[i + j] + carry;\n                res[i + j] = u64(cur % BASE);\n       \
    \         carry = u64(cur / BASE);\n            }\n            size_t pos = i\
    \ + b.size();\n            while (carry) {\n                u128 cur = u128(res[pos])\
    \ + carry;\n                res[pos] = u64(cur % BASE);\n                carry\
    \ = u64(cur / BASE);\n                ++pos;\n            }\n        }\n     \
    \   while (!res.empty() && res.back() == 0) res.pop_back();\n        return res;\n\
    \    }\n\n    static vector<u32> to_meta_digits(const vector<u64> &src) {\n  \
    \      vector<u32> res(src.size() * META_DIGITS);\n        for (size_t i = 0;\
    \ i < src.size(); ++i) {\n            u64 value = src[i];\n            for (int\
    \ j = 0; j < META_DIGITS; ++j) {\n                res[i * META_DIGITS + j] = u32(value\
    \ % META_BASE);\n                value /= META_BASE;\n            }\n        }\n\
    \        while (!res.empty() && res.back() == 0) res.pop_back();\n        return\
    \ res;\n    }\n\n    static vector<u64> from_meta_digits(const vector<u32> &src)\
    \ {\n        vector<u64> res;\n        res.reserve((src.size() + META_DIGITS -\
    \ 1) / META_DIGITS);\n        for (size_t i = 0; i < src.size(); i += META_DIGITS)\
    \ {\n            u128 value = 0;\n            for (int j = META_DIGITS - 1; j\
    \ >= 0; --j) {\n                value *= META_BASE;\n                size_t index\
    \ = i + (size_t)j;\n                if (index < src.size()) value += src[index];\n\
    \            }\n            res.push_back(u64(value));\n        }\n        while\
    \ (!res.empty() && res.back() == 0) res.pop_back();\n        return res;\n   \
    \ }\n\n    static vector<u64> mul_convolution_digits(const vector<u64> &a, const\
    \ vector<u64> &b) {\n        vector<u32> x = to_meta_digits(a);\n        vector<u32>\
    \ y = to_meta_digits(b);\n        vector<u64> convolution;\n        if (a == b)\
    \ convolution = BoundedConvolution::square_u64(x);\n        else convolution =\
    \ BoundedConvolution::convolution_u64(x, y);\n\n        vector<u32> meta;\n  \
    \      meta.reserve(convolution.size() + 4);\n        u128 carry = 0;\n      \
    \  for (u64 value : convolution) {\n            u128 cur = value + carry;\n  \
    \          meta.push_back(u32(cur % META_BASE));\n            carry = cur / META_BASE;\n\
    \        }\n        while (carry) {\n            meta.push_back(u32(carry % META_BASE));\n\
    \            carry /= META_BASE;\n        }\n        while (!meta.empty() && meta.back()\
    \ == 0) meta.pop_back();\n        return from_meta_digits(meta);\n    }\n\n  \
    \  static BasicBigInteger multiply_abs(const BasicBigInteger &a, const BasicBigInteger\
    \ &b) {\n        BasicBigInteger res;\n        if (a.is_zero() || b.is_zero())\
    \ return res;\n        if (a.digits.size() == 1) {\n            res = b.abs();\n\
    \            res.mul_small_abs(a.digits[0]);\n            return res;\n      \
    \  }\n        if (b.digits.size() == 1) {\n            res = a.abs();\n      \
    \      res.mul_small_abs(b.digits[0]);\n            return res;\n        }\n \
    \       long long area = (long long)a.digits.size() * (long long)b.digits.size();\n\
    \        if ((int)min(a.digits.size(), b.digits.size()) <= SCHOOLBOOK_MIN_THRESHOLD\
    \ ||\n            area <= SCHOOLBOOK_AREA_THRESHOLD) {\n            res.digits\
    \ = mul_schoolbook_digits(a.digits, b.digits);\n        } else {\n           \
    \ res.digits = mul_convolution_digits(a.digits, b.digits);\n        }\n      \
    \  return res;\n    }\n\n    void pad_inplace(size_t count) {\n        if (!digits.empty()\
    \ && count) digits.insert(digits.begin(), count, 0);\n    }\n\n    BasicBigInteger\
    \ pad(size_t count) const {\n        BasicBigInteger res = *this;\n        res.pad_inplace(count);\n\
    \        return res;\n    }\n\n    void drop_inplace(size_t count) {\n       \
    \ if (count >= digits.size()) {\n            digits.clear();\n            negative\
    \ = false;\n            return;\n        }\n        digits.erase(digits.begin(),\
    \ digits.begin() + (int)count);\n        normalize();\n    }\n\n    BasicBigInteger\
    \ top(size_t count) const {\n        BasicBigInteger res = *this;\n        if\
    \ (count >= res.digits.size()) res.pad_inplace(count - res.digits.size());\n \
    \       else res.drop_inplace(res.digits.size() - count);\n        return res;\n\
    \    }\n\n    static BasicBigInteger divmod_knuth_abs(const BasicBigInteger &a,\n\
    \                                             const BasicBigInteger &b,\n    \
    \                                         BasicBigInteger &remainder) {\n    \
    \    assert(!b.is_zero());\n        if (compare_abs(a, b) < 0) {\n           \
    \ remainder = a;\n            return BasicBigInteger();\n        }\n        if\
    \ (b.digits.size() == 1) {\n            BasicBigInteger quotient = a;\n      \
    \      u64 rem = quotient.div_small_abs(b.digits[0]);\n            remainder =\
    \ BasicBigInteger((long long)rem);\n            return quotient;\n        }\n\n\
    \        u64 norm = BASE / (b.digits.back() + 1);\n        vector<u64> un = norm\
    \ == 1 ? a.digits : mul_small_digits(a.digits, norm);\n        vector<u64> vn\
    \ = norm == 1 ? b.digits : mul_small_digits(b.digits, norm);\n        size_t n\
    \ = vn.size();\n        size_t m = un.size() - n;\n        un.push_back(0);\n\n\
    \        BasicBigInteger quotient;\n        quotient.digits.assign(m + 1, 0);\n\
    \        for (size_t jj = m + 1; jj-- > 0;) {\n            size_t j = jj;\n  \
    \          u128 numerator = u128(un[j + n]) * BASE + un[j + n - 1];\n        \
    \    u128 qhat = numerator / vn[n - 1];\n            u128 rhat = numerator % vn[n\
    \ - 1];\n            if (qhat == BASE) {\n                --qhat;\n          \
    \      rhat += vn[n - 1];\n            }\n            if (n >= 2) {\n        \
    \        while (rhat < BASE &&\n                       qhat * vn[n - 2] > rhat\
    \ * BASE + un[j + n - 2]) {\n                    --qhat;\n                   \
    \ rhat += vn[n - 1];\n                }\n            }\n\n            u64 carry\
    \ = 0;\n            u64 borrow = 0;\n            for (size_t i = 0; i < n; ++i)\
    \ {\n                u128 product = qhat * vn[i] + carry;\n                carry\
    \ = u64(product / BASE);\n                u128 sub = product % BASE + borrow;\n\
    \                if (u128(un[j + i]) < sub) {\n                    un[j + i] =\
    \ u64(u128(un[j + i]) + BASE - sub);\n                    borrow = 1;\n      \
    \          } else {\n                    un[j + i] = u64(u128(un[j + i]) - sub);\n\
    \                    borrow = 0;\n                }\n            }\n\n       \
    \     u128 sub = u128(carry) + borrow;\n            bool underflow = u128(un[j\
    \ + n]) < sub;\n            if (underflow) un[j + n] = u64(u128(un[j + n]) + BASE\
    \ - sub);\n            else un[j + n] = u64(u128(un[j + n]) - sub);\n\n      \
    \      if (underflow) {\n                --qhat;\n                u64 add_carry\
    \ = 0;\n                for (size_t i = 0; i < n; ++i) {\n                   \
    \ u128 cur = u128(un[j + i]) + vn[i] + add_carry;\n                    if (cur\
    \ >= BASE) {\n                        un[j + i] = u64(cur - BASE);\n         \
    \               add_carry = 1;\n                    } else {\n               \
    \         un[j + i] = u64(cur);\n                        add_carry = 0;\n    \
    \                }\n                }\n                un[j + n] = u64(u128(un[j\
    \ + n]) + add_carry);\n            }\n            quotient.digits[j] = u64(qhat);\n\
    \        }\n\n        quotient.normalize();\n        remainder.digits.assign(un.begin(),\
    \ un.begin() + n);\n        if (norm != 1) div_small_digits(remainder.digits,\
    \ norm);\n        remainder.normalize();\n        return quotient;\n    }\n\n\
    \    struct Scaled {\n        BasicBigInteger value;\n        long long scale;\n\
    \n        Scaled(long long value_ = 0, long long scale_ = 0) : value(value_),\
    \ scale(scale_) {}\n        Scaled(BasicBigInteger value_, long long scale_ =\
    \ 0)\n            : value(std::move(value_)), scale(scale_) {}\n\n        Scaled\
    \ &operator*=(const Scaled &other) {\n            value *= other.value;\n    \
    \        scale += other.scale;\n            return *this;\n        }\n\n     \
    \   Scaled &operator+=(const Scaled &other) {\n            if (scale < other.scale)\
    \ {\n                value += other.value.pad((size_t)(other.scale - scale));\n\
    \            } else {\n                value.pad_inplace((size_t)(scale - other.scale));\n\
    \                value += other.value;\n                scale = other.scale;\n\
    \            }\n            return *this;\n        }\n\n        Scaled &operator-=(const\
    \ Scaled &other) {\n            if (scale < other.scale) {\n                value\
    \ -= other.value.pad((size_t)(other.scale - scale));\n            } else {\n \
    \               value.pad_inplace((size_t)(scale - other.scale));\n          \
    \      value -= other.value;\n                scale = other.scale;\n         \
    \   }\n            return *this;\n        }\n\n        friend Scaled operator*(Scaled\
    \ lhs, const Scaled &rhs) { return lhs *= rhs; }\n        friend Scaled operator+(Scaled\
    \ lhs, const Scaled &rhs) { return lhs += rhs; }\n        friend Scaled operator-(Scaled\
    \ lhs, const Scaled &rhs) { return lhs -= rhs; }\n\n        BasicBigInteger round()\
    \ const {\n            if (scale >= 0) return value.pad((size_t)scale);\n    \
    \        if (-scale > (long long)value.digits.size()) return BasicBigInteger();\n\
    \            BasicBigInteger res = value.top(value.digits.size() - (size_t)(-scale));\n\
    \            if (value.digits[(size_t)(-scale - 1)] * 2 >= BASE) res += 1;\n \
    \           return res;\n        }\n\n        Scaled trunc(size_t count) const\
    \ {\n            count = min(count, value.digits.size());\n            return\
    \ Scaled(value.top(count), scale + (long long)value.digits.size() - (long long)count);\n\
    \        }\n\n        long long magnitude() const {\n            static constexpr\
    \ long long NEG_INF = -(1LL << 60);\n            if (value.is_zero()) return NEG_INF;\n\
    \            return (long long)value.digits.size() + scale;\n        }\n\n   \
    \     Scaled inv(long long precision) const {\n            assert(precision >=\
    \ 0 && !value.is_zero());\n            long double estimate = (long double)BASE\
    \ / (long double)value.digits.back();\n            long long lead = (long long)(estimate\
    \ + 0.5L);\n            Scaled result(BasicBigInteger(lead), -(long long)value.digits.size());\n\
    \            size_t current = 2;\n            Scaled amend = Scaled(1) - trunc(current)\
    \ * result;\n            while (-amend.magnitude() < precision) {\n          \
    \      result += result * amend;\n                current = 2 * (size_t)(1 - amend.magnitude());\n\
    \                result = result.trunc(current);\n                amend = Scaled(1)\
    \ - trunc(current) * result;\n            }\n            return result;\n    \
    \    }\n    };\n\n    static bool divmod_reciprocal_abs(const BasicBigInteger\
    \ &a,\n                                       const BasicBigInteger &b,\n    \
    \                                   BasicBigInteger &quotient,\n             \
    \                          BasicBigInteger &remainder) {\n        Scaled A(a);\n\
    \        Scaled B(b);\n        long long precision = A.magnitude() - B.magnitude()\
    \ + 1;\n        if (precision < 0) precision = 0;\n        quotient = (A * B.inv(precision)).round();\n\
    \        remainder = a - quotient * b;\n\n        int correction = 0;\n      \
    \  while (remainder.is_negative()) {\n            if (++correction > 8) return\
    \ false;\n            quotient -= 1;\n            remainder += b;\n        }\n\
    \        while (remainder >= b) {\n            if (++correction > 8) return false;\n\
    \            quotient += 1;\n            remainder -= b;\n        }\n        return\
    \ !quotient.is_negative() && !remainder.is_negative() && remainder < b;\n    }\n\
    \n    static pair<BasicBigInteger, BasicBigInteger> divmod_abs(const BasicBigInteger\
    \ &a,\n                                                              const BasicBigInteger\
    \ &b) {\n        assert(!b.is_zero());\n        if (compare_abs(a, b) < 0) return\
    \ {BasicBigInteger(), a};\n        if (b.digits.size() == 1) {\n            BasicBigInteger\
    \ quotient = a;\n            u64 remainder = quotient.div_small_abs(b.digits[0]);\n\
    \            return {quotient, BasicBigInteger((long long)remainder)};\n     \
    \   }\n\n        size_t quotient_size = a.digits.size() - b.digits.size() + 1;\n\
    \        if (b.digits.size() >= 4 && quotient_size >= 3) {\n            BasicBigInteger\
    \ quotient, remainder;\n            if (divmod_reciprocal_abs(a, b, quotient,\
    \ remainder)) {\n                return {std::move(quotient), std::move(remainder)};\n\
    \            }\n        }\n        BasicBigInteger remainder;\n        BasicBigInteger\
    \ quotient = divmod_knuth_abs(a, b, remainder);\n        return {std::move(quotient),\
    \ std::move(remainder)};\n    }\n\n    static pair<int, u64> shift_chunk() {\n\
    \        int bits = 0;\n        u64 value = 1;\n        while (bits < 62 && value\
    \ <= (BASE - 1) / 2) {\n            value *= 2;\n            ++bits;\n       \
    \ }\n        return {bits, value};\n    }\n\n    static void append_in_base(string\
    \ &out, u64 value, int base, int width) {\n        char buffer[70];\n        int\
    \ pos = 70;\n        do {\n            buffer[--pos] = digit_char((int)(value\
    \ % (u64)base));\n            value /= (u64)base;\n        } while (value);\n\
    \        int length = 70 - pos;\n        while (length < width) {\n          \
    \  out.push_back('0');\n            ++length;\n        }\n        out.append(buffer\
    \ + pos, buffer + 70);\n    }\n\npublic:\n    BasicBigInteger() : digits(), negative(false)\
    \ {}\n\n    BasicBigInteger(long long value) : digits(), negative(false) {\n \
    \       *this = value;\n    }\n\n    BasicBigInteger(const string &value, int\
    \ base = IO_BASE) : digits(), negative(false) {\n        bool ok = assign(value,\
    \ base);\n        assert(ok);\n        (void)ok;\n    }\n\n    BasicBigInteger\
    \ &operator=(long long value) {\n        digits.clear();\n        negative = value\
    \ < 0;\n        u64 magnitude = value < 0 ? u64(-(value + 1)) + 1 : u64(value);\n\
    \        while (magnitude) {\n            digits.push_back(magnitude % BASE);\n\
    \            magnitude /= BASE;\n        }\n        normalize();\n        return\
    \ *this;\n    }\n\n    bool assign(const string &value, int base = IO_BASE) {\n\
    \        digits.clear();\n        negative = false;\n        if (base < 2 || base\
    \ > 36 || value.empty()) return false;\n\n        int begin = 0;\n        bool\
    \ is_negative = false;\n        if (value[begin] == '+' || value[begin] == '-')\
    \ {\n            is_negative = value[begin] == '-';\n            if (++begin ==\
    \ (int)value.size()) return false;\n        }\n        for (int i = begin; i <\
    \ (int)value.size(); ++i) {\n            int digit = digit_value(value[i]);\n\
    \            if (digit < 0 || digit >= base) {\n                digits.clear();\n\
    \                negative = false;\n                return false;\n          \
    \  }\n        }\n        while (begin < (int)value.size() && value[begin] == '0')\
    \ ++begin;\n        if (begin == (int)value.size()) return true;\n\n        if\
    \ (base == IO_BASE) {\n            for (int right = (int)value.size(); right >\
    \ begin; right -= BLOCK_DIGITS) {\n                int left = max(begin, right\
    \ - BLOCK_DIGITS);\n                u64 block = 0;\n                for (int i\
    \ = left; i < right; ++i) {\n                    block = block * (u64)base + (u64)digit_value(value[i]);\n\
    \                }\n                digits.push_back(block);\n            }\n\
    \        } else {\n            u64 chunk_base = 1;\n            int chunk_digits\
    \ = 0;\n            while (chunk_base <= (BASE - 1) / (u64)base) {\n         \
    \       chunk_base *= (u64)base;\n                ++chunk_digits;\n          \
    \  }\n            int first = ((int)value.size() - begin) % chunk_digits;\n  \
    \          if (first == 0) first = chunk_digits;\n            for (int pos = begin;\
    \ pos < (int)value.size();) {\n                int width = pos == begin ? first\
    \ : chunk_digits;\n                u64 block = 0;\n                u64 power =\
    \ 1;\n                for (int i = 0; i < width; ++i) {\n                    block\
    \ = block * (u64)base + (u64)digit_value(value[pos + i]);\n                  \
    \  power *= (u64)base;\n                }\n                mul_small_abs(power);\n\
    \                add_small_abs(block);\n                pos += width;\n      \
    \      }\n        }\n        negative = is_negative;\n        normalize();\n \
    \       return true;\n    }\n\n    string to_string(int base = IO_BASE) const\
    \ {\n        assert(2 <= base && base <= 36);\n        if (is_zero()) return \"\
    0\";\n        string out;\n        if (negative) out.push_back('-');\n\n     \
    \   if (base == IO_BASE) {\n            append_in_base(out, digits.back(), base,\
    \ 0);\n            for (int i = (int)digits.size() - 2; i >= 0; --i) {\n     \
    \           append_in_base(out, digits[i], base, BLOCK_DIGITS);\n            }\n\
    \            return out;\n        }\n\n        u64 chunk_base = 1;\n        int\
    \ chunk_digits = 0;\n        while (chunk_base <= (BASE - 1) / (u64)base) {\n\
    \            chunk_base *= (u64)base;\n            ++chunk_digits;\n        }\n\
    \        BasicBigInteger value = abs();\n        vector<u64> parts;\n        while\
    \ (!value.is_zero()) parts.push_back(value.div_small_abs(chunk_base));\n     \
    \   append_in_base(out, parts.back(), base, 0);\n        for (int i = (int)parts.size()\
    \ - 2; i >= 0; --i) {\n            append_in_base(out, parts[i], base, chunk_digits);\n\
    \        }\n        return out;\n    }\n\n    bool is_zero() const { return digits.empty();\
    \ }\n    bool is_negative() const { return negative; }\n\n    BasicBigInteger\
    \ abs() const {\n        BasicBigInteger res = *this;\n        res.negative =\
    \ false;\n        return res;\n    }\n\n    BasicBigInteger operator+() const\
    \ { return *this; }\n\n    BasicBigInteger operator-() const {\n        BasicBigInteger\
    \ res = *this;\n        if (!res.is_zero()) res.negative = !res.negative;\n  \
    \      return res;\n    }\n\n    BasicBigInteger &operator+=(const BasicBigInteger\
    \ &other) {\n        if (other.is_zero()) return *this;\n        if (is_zero())\
    \ {\n            *this = other;\n            return *this;\n        }\n      \
    \  if (negative == other.negative) {\n            add_abs(other);\n          \
    \  return *this;\n        }\n        int cmp = compare_abs(*this, other);\n  \
    \      if (cmp == 0) {\n            digits.clear();\n            negative = false;\n\
    \        } else if (cmp > 0) {\n            sub_abs(other);\n        } else {\n\
    \            BasicBigInteger res = other;\n            res.sub_abs(*this);\n \
    \           *this = std::move(res);\n        }\n        return *this;\n    }\n\
    \n    BasicBigInteger &operator-=(const BasicBigInteger &other) {\n        return\
    \ *this += -other;\n    }\n\n    BasicBigInteger &operator*=(const BasicBigInteger\
    \ &other) {\n        if (is_zero() || other.is_zero()) {\n            digits.clear();\n\
    \            negative = false;\n            return *this;\n        }\n       \
    \ bool result_negative = negative != other.negative;\n        BasicBigInteger\
    \ result = multiply_abs(*this, other);\n        result.negative = result_negative;\n\
    \        *this = std::move(result);\n        return *this;\n    }\n\n    friend\
    \ BasicBigInteger operator+(BasicBigInteger lhs, const BasicBigInteger &rhs) {\
    \ return lhs += rhs; }\n    friend BasicBigInteger operator-(BasicBigInteger lhs,\
    \ const BasicBigInteger &rhs) { return lhs -= rhs; }\n    friend BasicBigInteger\
    \ operator*(BasicBigInteger lhs, const BasicBigInteger &rhs) { return lhs *= rhs;\
    \ }\n\n    friend bool operator==(const BasicBigInteger &a, const BasicBigInteger\
    \ &b) { return compare(a, b) == 0; }\n    friend bool operator!=(const BasicBigInteger\
    \ &a, const BasicBigInteger &b) { return compare(a, b) != 0; }\n    friend bool\
    \ operator<(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a,\
    \ b) < 0; }\n    friend bool operator<=(const BasicBigInteger &a, const BasicBigInteger\
    \ &b) { return compare(a, b) <= 0; }\n    friend bool operator>(const BasicBigInteger\
    \ &a, const BasicBigInteger &b) { return compare(a, b) > 0; }\n    friend bool\
    \ operator>=(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a,\
    \ b) >= 0; }\n\n    static pair<BasicBigInteger, BasicBigInteger> divmod(const\
    \ BasicBigInteger &a,\n                                                      \
    \   const BasicBigInteger &b) {\n        assert(!b.is_zero());\n        auto result\
    \ = divmod_abs(a.abs(), b.abs());\n        if (!result.first.is_zero()) result.first.negative\
    \ = a.negative != b.negative;\n        if (!result.second.is_zero()) result.second.negative\
    \ = a.negative;\n        return result;\n    }\n\n    static pair<BasicBigInteger,\
    \ BasicBigInteger> floor_divmod(const BasicBigInteger &a,\n                  \
    \                                             const BasicBigInteger &b) {\n  \
    \      auto result = divmod(a, b);\n        if (!result.second.is_zero() && a.negative\
    \ != b.negative) {\n            result.first -= 1;\n            result.second\
    \ += b;\n        }\n        return result;\n    }\n\n    friend pair<BasicBigInteger,\
    \ BasicBigInteger> divmod(const BasicBigInteger &a,\n                        \
    \                                 const BasicBigInteger &b) {\n        return\
    \ BasicBigInteger::divmod(a, b);\n    }\n\n    friend pair<BasicBigInteger, BasicBigInteger>\
    \ floor_divmod(const BasicBigInteger &a,\n                                   \
    \                            const BasicBigInteger &b) {\n        return BasicBigInteger::floor_divmod(a,\
    \ b);\n    }\n\n    BasicBigInteger &operator/=(const BasicBigInteger &other)\
    \ {\n        *this = divmod(*this, other).first;\n        return *this;\n    }\n\
    \n    BasicBigInteger &operator%=(const BasicBigInteger &other) {\n        *this\
    \ = divmod(*this, other).second;\n        return *this;\n    }\n\n    BasicBigInteger\
    \ &operator<<=(int bits) {\n        assert(bits >= 0);\n        if (is_zero()\
    \ || bits == 0) return *this;\n        auto chunk = shift_chunk();\n        while\
    \ (bits) {\n            int take = min(bits, chunk.first);\n            mul_small_abs(1ULL\
    \ << take);\n            bits -= take;\n        }\n        return *this;\n   \
    \ }\n\n    BasicBigInteger &operator>>=(int bits) {\n        assert(bits >= 0);\n\
    \        if (is_zero() || bits == 0) return *this;\n        bool was_negative\
    \ = negative;\n        bool discarded = false;\n        auto chunk = shift_chunk();\n\
    \        while (bits && !is_zero()) {\n            int take = min(bits, chunk.first);\n\
    \            discarded |= div_small_abs(1ULL << take) != 0;\n            bits\
    \ -= take;\n        }\n        if (was_negative && discarded) {\n            add_small_abs(1);\n\
    \            negative = true;\n        }\n        normalize();\n        return\
    \ *this;\n    }\n\n    friend BasicBigInteger operator/(BasicBigInteger lhs, const\
    \ BasicBigInteger &rhs) { return lhs /= rhs; }\n    friend BasicBigInteger operator%(BasicBigInteger\
    \ lhs, const BasicBigInteger &rhs) { return lhs %= rhs; }\n    friend BasicBigInteger\
    \ operator<<(BasicBigInteger lhs, int bits) { return lhs <<= bits; }\n    friend\
    \ BasicBigInteger operator>>(BasicBigInteger lhs, int bits) { return lhs >>= bits;\
    \ }\n};\n\nusing BigInteger = BasicBigInteger<BigIntegerDetail::DecimalRadix>;\n\
    using HexBigInteger = BasicBigInteger<BigIntegerDetail::HexRadix>;\n\n\n\n/**\n\
    \ * @brief \u591A\u500D\u9577\u6574\u6570(BigInteger)\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_UTIL_BIGINTEGER_CPP\n#define FIRIEXP_LIBRARY_UTIL_BIGINTEGER_CPP\n\
    \n#include \"../math/integer_convolution.cpp\"\n\nnamespace BigIntegerDetail {\n\
    \    using u32 = unsigned int;\n    using u64 = unsigned long long;\n    using\
    \ u128 = __uint128_t;\n\n    struct DecimalRadix {\n        static constexpr u64\
    \ BASE = 10000000000000000ULL;\n        static constexpr int IO_BASE = 10;\n \
    \       static constexpr int BLOCK_DIGITS = 16;\n        static constexpr u32\
    \ META_BASE = 10000u;\n        static constexpr int META_DIGITS = 4;\n    };\n\
    \n    struct HexRadix {\n        static constexpr u64 BASE = 1ULL << 60;\n   \
    \     static constexpr int IO_BASE = 16;\n        static constexpr int BLOCK_DIGITS\
    \ = 15;\n        static constexpr u32 META_BASE = 1u << 15;\n        static constexpr\
    \ int META_DIGITS = 4;\n    };\n}\n\ntemplate<class Radix>\nclass BasicBigInteger\
    \ {\n    using u32 = BigIntegerDetail::u32;\n    using u64 = BigIntegerDetail::u64;\n\
    \    using u128 = BigIntegerDetail::u128;\n\n    static constexpr u64 BASE = Radix::BASE;\n\
    \    static constexpr int IO_BASE = Radix::IO_BASE;\n    static constexpr int\
    \ BLOCK_DIGITS = Radix::BLOCK_DIGITS;\n    static constexpr u32 META_BASE = Radix::META_BASE;\n\
    \    static constexpr int META_DIGITS = Radix::META_DIGITS;\n    static constexpr\
    \ int SCHOOLBOOK_MIN_THRESHOLD = 32;\n    static constexpr long long SCHOOLBOOK_AREA_THRESHOLD\
    \ = 4096;\n\n    vector<u64> digits;\n    bool negative;\n\n    static int digit_value(char\
    \ c) {\n        if ('0' <= c && c <= '9') return c - '0';\n        if ('a' <=\
    \ c && c <= 'z') return c - 'a' + 10;\n        if ('A' <= c && c <= 'Z') return\
    \ c - 'A' + 10;\n        return -1;\n    }\n\n    static char digit_char(int x)\
    \ {\n        return x < 10 ? char('0' + x) : char('a' + x - 10);\n    }\n\n  \
    \  void normalize() {\n        while (!digits.empty() && digits.back() == 0) digits.pop_back();\n\
    \        if (digits.empty()) negative = false;\n    }\n\n    static int compare_abs(const\
    \ BasicBigInteger &a, const BasicBigInteger &b) {\n        if (a.digits.size()\
    \ != b.digits.size()) {\n            return a.digits.size() < b.digits.size()\
    \ ? -1 : 1;\n        }\n        for (int i = (int)a.digits.size() - 1; i >= 0;\
    \ --i) {\n            if (a.digits[i] != b.digits[i]) return a.digits[i] < b.digits[i]\
    \ ? -1 : 1;\n        }\n        return 0;\n    }\n\n    static int compare(const\
    \ BasicBigInteger &a, const BasicBigInteger &b) {\n        if (a.negative != b.negative)\
    \ return a.negative ? -1 : 1;\n        int cmp = compare_abs(a, b);\n        return\
    \ a.negative ? -cmp : cmp;\n    }\n\n    void add_abs(const BasicBigInteger &other)\
    \ {\n        if (digits.size() < other.digits.size()) digits.resize(other.digits.size(),\
    \ 0);\n        u64 carry = 0;\n        size_t i = 0;\n        for (; i < other.digits.size();\
    \ ++i) {\n            u128 cur = u128(digits[i]) + other.digits[i] + carry;\n\
    \            if (cur >= BASE) {\n                digits[i] = u64(cur - BASE);\n\
    \                carry = 1;\n            } else {\n                digits[i] =\
    \ u64(cur);\n                carry = 0;\n            }\n        }\n        for\
    \ (; i < digits.size() && carry; ++i) {\n            if (++digits[i] == BASE)\
    \ digits[i] = 0;\n            else carry = 0;\n        }\n        if (carry) digits.push_back(1);\n\
    \    }\n\n    void sub_abs(const BasicBigInteger &other) {\n        u64 borrow\
    \ = 0;\n        for (size_t i = 0; i < digits.size(); ++i) {\n            u128\
    \ rhs = borrow;\n            if (i < other.digits.size()) rhs += other.digits[i];\n\
    \            if (u128(digits[i]) < rhs) {\n                digits[i] = u64(u128(digits[i])\
    \ + BASE - rhs);\n                borrow = 1;\n            } else {\n        \
    \        digits[i] = u64(u128(digits[i]) - rhs);\n                borrow = 0;\n\
    \            }\n        }\n        normalize();\n    }\n\n    void add_small_abs(u64\
    \ value) {\n        assert(value < BASE);\n        if (value == 0) return;\n \
    \       if (digits.empty()) {\n            digits.push_back(value);\n        \
    \    return;\n        }\n        u128 cur = u128(digits[0]) + value;\n       \
    \ digits[0] = u64(cur % BASE);\n        u64 carry = u64(cur / BASE);\n       \
    \ for (size_t i = 1; i < digits.size() && carry; ++i) {\n            if (++digits[i]\
    \ == BASE) digits[i] = 0;\n            else carry = 0;\n        }\n        if\
    \ (carry) digits.push_back(carry);\n    }\n\n    void mul_small_abs(u64 value)\
    \ {\n        assert(value < BASE);\n        if (digits.empty() || value == 1)\
    \ return;\n        if (value == 0) {\n            digits.clear();\n          \
    \  negative = false;\n            return;\n        }\n        u64 carry = 0;\n\
    \        for (u64 &digit : digits) {\n            u128 cur = u128(digit) * value\
    \ + carry;\n            digit = u64(cur % BASE);\n            carry = u64(cur\
    \ / BASE);\n        }\n        if (carry) digits.push_back(carry);\n    }\n\n\
    \    u64 div_small_abs(u64 value) {\n        assert(value != 0 && value < BASE);\n\
    \        u64 remainder = 0;\n        for (int i = (int)digits.size() - 1; i >=\
    \ 0; --i) {\n            u128 cur = u128(remainder) * BASE + digits[i];\n    \
    \        digits[i] = u64(cur / value);\n            remainder = u64(cur % value);\n\
    \        }\n        normalize();\n        return remainder;\n    }\n\n    static\
    \ vector<u64> mul_small_digits(const vector<u64> &src, u64 value) {\n        if\
    \ (src.empty() || value == 0) return {};\n        vector<u64> res;\n        res.reserve(src.size()\
    \ + 1);\n        u64 carry = 0;\n        for (u64 digit : src) {\n           \
    \ u128 cur = u128(digit) * value + carry;\n            res.push_back(u64(cur %\
    \ BASE));\n            carry = u64(cur / BASE);\n        }\n        if (carry)\
    \ res.push_back(carry);\n        return res;\n    }\n\n    static u64 div_small_digits(vector<u64>\
    \ &src, u64 value) {\n        u64 remainder = 0;\n        for (int i = (int)src.size()\
    \ - 1; i >= 0; --i) {\n            u128 cur = u128(remainder) * BASE + src[i];\n\
    \            src[i] = u64(cur / value);\n            remainder = u64(cur % value);\n\
    \        }\n        while (!src.empty() && src.back() == 0) src.pop_back();\n\
    \        return remainder;\n    }\n\n    static vector<u64> mul_schoolbook_digits(const\
    \ vector<u64> &a, const vector<u64> &b) {\n        if (a.empty() || b.empty())\
    \ return {};\n        vector<u64> res(a.size() + b.size(), 0);\n        for (size_t\
    \ i = 0; i < a.size(); ++i) {\n            u64 carry = 0;\n            for (size_t\
    \ j = 0; j < b.size(); ++j) {\n                u128 cur = u128(a[i]) * b[j] +\
    \ res[i + j] + carry;\n                res[i + j] = u64(cur % BASE);\n       \
    \         carry = u64(cur / BASE);\n            }\n            size_t pos = i\
    \ + b.size();\n            while (carry) {\n                u128 cur = u128(res[pos])\
    \ + carry;\n                res[pos] = u64(cur % BASE);\n                carry\
    \ = u64(cur / BASE);\n                ++pos;\n            }\n        }\n     \
    \   while (!res.empty() && res.back() == 0) res.pop_back();\n        return res;\n\
    \    }\n\n    static vector<u32> to_meta_digits(const vector<u64> &src) {\n  \
    \      vector<u32> res(src.size() * META_DIGITS);\n        for (size_t i = 0;\
    \ i < src.size(); ++i) {\n            u64 value = src[i];\n            for (int\
    \ j = 0; j < META_DIGITS; ++j) {\n                res[i * META_DIGITS + j] = u32(value\
    \ % META_BASE);\n                value /= META_BASE;\n            }\n        }\n\
    \        while (!res.empty() && res.back() == 0) res.pop_back();\n        return\
    \ res;\n    }\n\n    static vector<u64> from_meta_digits(const vector<u32> &src)\
    \ {\n        vector<u64> res;\n        res.reserve((src.size() + META_DIGITS -\
    \ 1) / META_DIGITS);\n        for (size_t i = 0; i < src.size(); i += META_DIGITS)\
    \ {\n            u128 value = 0;\n            for (int j = META_DIGITS - 1; j\
    \ >= 0; --j) {\n                value *= META_BASE;\n                size_t index\
    \ = i + (size_t)j;\n                if (index < src.size()) value += src[index];\n\
    \            }\n            res.push_back(u64(value));\n        }\n        while\
    \ (!res.empty() && res.back() == 0) res.pop_back();\n        return res;\n   \
    \ }\n\n    static vector<u64> mul_convolution_digits(const vector<u64> &a, const\
    \ vector<u64> &b) {\n        vector<u32> x = to_meta_digits(a);\n        vector<u32>\
    \ y = to_meta_digits(b);\n        vector<u64> convolution;\n        if (a == b)\
    \ convolution = BoundedConvolution::square_u64(x);\n        else convolution =\
    \ BoundedConvolution::convolution_u64(x, y);\n\n        vector<u32> meta;\n  \
    \      meta.reserve(convolution.size() + 4);\n        u128 carry = 0;\n      \
    \  for (u64 value : convolution) {\n            u128 cur = value + carry;\n  \
    \          meta.push_back(u32(cur % META_BASE));\n            carry = cur / META_BASE;\n\
    \        }\n        while (carry) {\n            meta.push_back(u32(carry % META_BASE));\n\
    \            carry /= META_BASE;\n        }\n        while (!meta.empty() && meta.back()\
    \ == 0) meta.pop_back();\n        return from_meta_digits(meta);\n    }\n\n  \
    \  static BasicBigInteger multiply_abs(const BasicBigInteger &a, const BasicBigInteger\
    \ &b) {\n        BasicBigInteger res;\n        if (a.is_zero() || b.is_zero())\
    \ return res;\n        if (a.digits.size() == 1) {\n            res = b.abs();\n\
    \            res.mul_small_abs(a.digits[0]);\n            return res;\n      \
    \  }\n        if (b.digits.size() == 1) {\n            res = a.abs();\n      \
    \      res.mul_small_abs(b.digits[0]);\n            return res;\n        }\n \
    \       long long area = (long long)a.digits.size() * (long long)b.digits.size();\n\
    \        if ((int)min(a.digits.size(), b.digits.size()) <= SCHOOLBOOK_MIN_THRESHOLD\
    \ ||\n            area <= SCHOOLBOOK_AREA_THRESHOLD) {\n            res.digits\
    \ = mul_schoolbook_digits(a.digits, b.digits);\n        } else {\n           \
    \ res.digits = mul_convolution_digits(a.digits, b.digits);\n        }\n      \
    \  return res;\n    }\n\n    void pad_inplace(size_t count) {\n        if (!digits.empty()\
    \ && count) digits.insert(digits.begin(), count, 0);\n    }\n\n    BasicBigInteger\
    \ pad(size_t count) const {\n        BasicBigInteger res = *this;\n        res.pad_inplace(count);\n\
    \        return res;\n    }\n\n    void drop_inplace(size_t count) {\n       \
    \ if (count >= digits.size()) {\n            digits.clear();\n            negative\
    \ = false;\n            return;\n        }\n        digits.erase(digits.begin(),\
    \ digits.begin() + (int)count);\n        normalize();\n    }\n\n    BasicBigInteger\
    \ top(size_t count) const {\n        BasicBigInteger res = *this;\n        if\
    \ (count >= res.digits.size()) res.pad_inplace(count - res.digits.size());\n \
    \       else res.drop_inplace(res.digits.size() - count);\n        return res;\n\
    \    }\n\n    static BasicBigInteger divmod_knuth_abs(const BasicBigInteger &a,\n\
    \                                             const BasicBigInteger &b,\n    \
    \                                         BasicBigInteger &remainder) {\n    \
    \    assert(!b.is_zero());\n        if (compare_abs(a, b) < 0) {\n           \
    \ remainder = a;\n            return BasicBigInteger();\n        }\n        if\
    \ (b.digits.size() == 1) {\n            BasicBigInteger quotient = a;\n      \
    \      u64 rem = quotient.div_small_abs(b.digits[0]);\n            remainder =\
    \ BasicBigInteger((long long)rem);\n            return quotient;\n        }\n\n\
    \        u64 norm = BASE / (b.digits.back() + 1);\n        vector<u64> un = norm\
    \ == 1 ? a.digits : mul_small_digits(a.digits, norm);\n        vector<u64> vn\
    \ = norm == 1 ? b.digits : mul_small_digits(b.digits, norm);\n        size_t n\
    \ = vn.size();\n        size_t m = un.size() - n;\n        un.push_back(0);\n\n\
    \        BasicBigInteger quotient;\n        quotient.digits.assign(m + 1, 0);\n\
    \        for (size_t jj = m + 1; jj-- > 0;) {\n            size_t j = jj;\n  \
    \          u128 numerator = u128(un[j + n]) * BASE + un[j + n - 1];\n        \
    \    u128 qhat = numerator / vn[n - 1];\n            u128 rhat = numerator % vn[n\
    \ - 1];\n            if (qhat == BASE) {\n                --qhat;\n          \
    \      rhat += vn[n - 1];\n            }\n            if (n >= 2) {\n        \
    \        while (rhat < BASE &&\n                       qhat * vn[n - 2] > rhat\
    \ * BASE + un[j + n - 2]) {\n                    --qhat;\n                   \
    \ rhat += vn[n - 1];\n                }\n            }\n\n            u64 carry\
    \ = 0;\n            u64 borrow = 0;\n            for (size_t i = 0; i < n; ++i)\
    \ {\n                u128 product = qhat * vn[i] + carry;\n                carry\
    \ = u64(product / BASE);\n                u128 sub = product % BASE + borrow;\n\
    \                if (u128(un[j + i]) < sub) {\n                    un[j + i] =\
    \ u64(u128(un[j + i]) + BASE - sub);\n                    borrow = 1;\n      \
    \          } else {\n                    un[j + i] = u64(u128(un[j + i]) - sub);\n\
    \                    borrow = 0;\n                }\n            }\n\n       \
    \     u128 sub = u128(carry) + borrow;\n            bool underflow = u128(un[j\
    \ + n]) < sub;\n            if (underflow) un[j + n] = u64(u128(un[j + n]) + BASE\
    \ - sub);\n            else un[j + n] = u64(u128(un[j + n]) - sub);\n\n      \
    \      if (underflow) {\n                --qhat;\n                u64 add_carry\
    \ = 0;\n                for (size_t i = 0; i < n; ++i) {\n                   \
    \ u128 cur = u128(un[j + i]) + vn[i] + add_carry;\n                    if (cur\
    \ >= BASE) {\n                        un[j + i] = u64(cur - BASE);\n         \
    \               add_carry = 1;\n                    } else {\n               \
    \         un[j + i] = u64(cur);\n                        add_carry = 0;\n    \
    \                }\n                }\n                un[j + n] = u64(u128(un[j\
    \ + n]) + add_carry);\n            }\n            quotient.digits[j] = u64(qhat);\n\
    \        }\n\n        quotient.normalize();\n        remainder.digits.assign(un.begin(),\
    \ un.begin() + n);\n        if (norm != 1) div_small_digits(remainder.digits,\
    \ norm);\n        remainder.normalize();\n        return quotient;\n    }\n\n\
    \    struct Scaled {\n        BasicBigInteger value;\n        long long scale;\n\
    \n        Scaled(long long value_ = 0, long long scale_ = 0) : value(value_),\
    \ scale(scale_) {}\n        Scaled(BasicBigInteger value_, long long scale_ =\
    \ 0)\n            : value(std::move(value_)), scale(scale_) {}\n\n        Scaled\
    \ &operator*=(const Scaled &other) {\n            value *= other.value;\n    \
    \        scale += other.scale;\n            return *this;\n        }\n\n     \
    \   Scaled &operator+=(const Scaled &other) {\n            if (scale < other.scale)\
    \ {\n                value += other.value.pad((size_t)(other.scale - scale));\n\
    \            } else {\n                value.pad_inplace((size_t)(scale - other.scale));\n\
    \                value += other.value;\n                scale = other.scale;\n\
    \            }\n            return *this;\n        }\n\n        Scaled &operator-=(const\
    \ Scaled &other) {\n            if (scale < other.scale) {\n                value\
    \ -= other.value.pad((size_t)(other.scale - scale));\n            } else {\n \
    \               value.pad_inplace((size_t)(scale - other.scale));\n          \
    \      value -= other.value;\n                scale = other.scale;\n         \
    \   }\n            return *this;\n        }\n\n        friend Scaled operator*(Scaled\
    \ lhs, const Scaled &rhs) { return lhs *= rhs; }\n        friend Scaled operator+(Scaled\
    \ lhs, const Scaled &rhs) { return lhs += rhs; }\n        friend Scaled operator-(Scaled\
    \ lhs, const Scaled &rhs) { return lhs -= rhs; }\n\n        BasicBigInteger round()\
    \ const {\n            if (scale >= 0) return value.pad((size_t)scale);\n    \
    \        if (-scale > (long long)value.digits.size()) return BasicBigInteger();\n\
    \            BasicBigInteger res = value.top(value.digits.size() - (size_t)(-scale));\n\
    \            if (value.digits[(size_t)(-scale - 1)] * 2 >= BASE) res += 1;\n \
    \           return res;\n        }\n\n        Scaled trunc(size_t count) const\
    \ {\n            count = min(count, value.digits.size());\n            return\
    \ Scaled(value.top(count), scale + (long long)value.digits.size() - (long long)count);\n\
    \        }\n\n        long long magnitude() const {\n            static constexpr\
    \ long long NEG_INF = -(1LL << 60);\n            if (value.is_zero()) return NEG_INF;\n\
    \            return (long long)value.digits.size() + scale;\n        }\n\n   \
    \     Scaled inv(long long precision) const {\n            assert(precision >=\
    \ 0 && !value.is_zero());\n            long double estimate = (long double)BASE\
    \ / (long double)value.digits.back();\n            long long lead = (long long)(estimate\
    \ + 0.5L);\n            Scaled result(BasicBigInteger(lead), -(long long)value.digits.size());\n\
    \            size_t current = 2;\n            Scaled amend = Scaled(1) - trunc(current)\
    \ * result;\n            while (-amend.magnitude() < precision) {\n          \
    \      result += result * amend;\n                current = 2 * (size_t)(1 - amend.magnitude());\n\
    \                result = result.trunc(current);\n                amend = Scaled(1)\
    \ - trunc(current) * result;\n            }\n            return result;\n    \
    \    }\n    };\n\n    static bool divmod_reciprocal_abs(const BasicBigInteger\
    \ &a,\n                                       const BasicBigInteger &b,\n    \
    \                                   BasicBigInteger &quotient,\n             \
    \                          BasicBigInteger &remainder) {\n        Scaled A(a);\n\
    \        Scaled B(b);\n        long long precision = A.magnitude() - B.magnitude()\
    \ + 1;\n        if (precision < 0) precision = 0;\n        quotient = (A * B.inv(precision)).round();\n\
    \        remainder = a - quotient * b;\n\n        int correction = 0;\n      \
    \  while (remainder.is_negative()) {\n            if (++correction > 8) return\
    \ false;\n            quotient -= 1;\n            remainder += b;\n        }\n\
    \        while (remainder >= b) {\n            if (++correction > 8) return false;\n\
    \            quotient += 1;\n            remainder -= b;\n        }\n        return\
    \ !quotient.is_negative() && !remainder.is_negative() && remainder < b;\n    }\n\
    \n    static pair<BasicBigInteger, BasicBigInteger> divmod_abs(const BasicBigInteger\
    \ &a,\n                                                              const BasicBigInteger\
    \ &b) {\n        assert(!b.is_zero());\n        if (compare_abs(a, b) < 0) return\
    \ {BasicBigInteger(), a};\n        if (b.digits.size() == 1) {\n            BasicBigInteger\
    \ quotient = a;\n            u64 remainder = quotient.div_small_abs(b.digits[0]);\n\
    \            return {quotient, BasicBigInteger((long long)remainder)};\n     \
    \   }\n\n        size_t quotient_size = a.digits.size() - b.digits.size() + 1;\n\
    \        if (b.digits.size() >= 4 && quotient_size >= 3) {\n            BasicBigInteger\
    \ quotient, remainder;\n            if (divmod_reciprocal_abs(a, b, quotient,\
    \ remainder)) {\n                return {std::move(quotient), std::move(remainder)};\n\
    \            }\n        }\n        BasicBigInteger remainder;\n        BasicBigInteger\
    \ quotient = divmod_knuth_abs(a, b, remainder);\n        return {std::move(quotient),\
    \ std::move(remainder)};\n    }\n\n    static pair<int, u64> shift_chunk() {\n\
    \        int bits = 0;\n        u64 value = 1;\n        while (bits < 62 && value\
    \ <= (BASE - 1) / 2) {\n            value *= 2;\n            ++bits;\n       \
    \ }\n        return {bits, value};\n    }\n\n    static void append_in_base(string\
    \ &out, u64 value, int base, int width) {\n        char buffer[70];\n        int\
    \ pos = 70;\n        do {\n            buffer[--pos] = digit_char((int)(value\
    \ % (u64)base));\n            value /= (u64)base;\n        } while (value);\n\
    \        int length = 70 - pos;\n        while (length < width) {\n          \
    \  out.push_back('0');\n            ++length;\n        }\n        out.append(buffer\
    \ + pos, buffer + 70);\n    }\n\npublic:\n    BasicBigInteger() : digits(), negative(false)\
    \ {}\n\n    BasicBigInteger(long long value) : digits(), negative(false) {\n \
    \       *this = value;\n    }\n\n    BasicBigInteger(const string &value, int\
    \ base = IO_BASE) : digits(), negative(false) {\n        bool ok = assign(value,\
    \ base);\n        assert(ok);\n        (void)ok;\n    }\n\n    BasicBigInteger\
    \ &operator=(long long value) {\n        digits.clear();\n        negative = value\
    \ < 0;\n        u64 magnitude = value < 0 ? u64(-(value + 1)) + 1 : u64(value);\n\
    \        while (magnitude) {\n            digits.push_back(magnitude % BASE);\n\
    \            magnitude /= BASE;\n        }\n        normalize();\n        return\
    \ *this;\n    }\n\n    bool assign(const string &value, int base = IO_BASE) {\n\
    \        digits.clear();\n        negative = false;\n        if (base < 2 || base\
    \ > 36 || value.empty()) return false;\n\n        int begin = 0;\n        bool\
    \ is_negative = false;\n        if (value[begin] == '+' || value[begin] == '-')\
    \ {\n            is_negative = value[begin] == '-';\n            if (++begin ==\
    \ (int)value.size()) return false;\n        }\n        for (int i = begin; i <\
    \ (int)value.size(); ++i) {\n            int digit = digit_value(value[i]);\n\
    \            if (digit < 0 || digit >= base) {\n                digits.clear();\n\
    \                negative = false;\n                return false;\n          \
    \  }\n        }\n        while (begin < (int)value.size() && value[begin] == '0')\
    \ ++begin;\n        if (begin == (int)value.size()) return true;\n\n        if\
    \ (base == IO_BASE) {\n            for (int right = (int)value.size(); right >\
    \ begin; right -= BLOCK_DIGITS) {\n                int left = max(begin, right\
    \ - BLOCK_DIGITS);\n                u64 block = 0;\n                for (int i\
    \ = left; i < right; ++i) {\n                    block = block * (u64)base + (u64)digit_value(value[i]);\n\
    \                }\n                digits.push_back(block);\n            }\n\
    \        } else {\n            u64 chunk_base = 1;\n            int chunk_digits\
    \ = 0;\n            while (chunk_base <= (BASE - 1) / (u64)base) {\n         \
    \       chunk_base *= (u64)base;\n                ++chunk_digits;\n          \
    \  }\n            int first = ((int)value.size() - begin) % chunk_digits;\n  \
    \          if (first == 0) first = chunk_digits;\n            for (int pos = begin;\
    \ pos < (int)value.size();) {\n                int width = pos == begin ? first\
    \ : chunk_digits;\n                u64 block = 0;\n                u64 power =\
    \ 1;\n                for (int i = 0; i < width; ++i) {\n                    block\
    \ = block * (u64)base + (u64)digit_value(value[pos + i]);\n                  \
    \  power *= (u64)base;\n                }\n                mul_small_abs(power);\n\
    \                add_small_abs(block);\n                pos += width;\n      \
    \      }\n        }\n        negative = is_negative;\n        normalize();\n \
    \       return true;\n    }\n\n    string to_string(int base = IO_BASE) const\
    \ {\n        assert(2 <= base && base <= 36);\n        if (is_zero()) return \"\
    0\";\n        string out;\n        if (negative) out.push_back('-');\n\n     \
    \   if (base == IO_BASE) {\n            append_in_base(out, digits.back(), base,\
    \ 0);\n            for (int i = (int)digits.size() - 2; i >= 0; --i) {\n     \
    \           append_in_base(out, digits[i], base, BLOCK_DIGITS);\n            }\n\
    \            return out;\n        }\n\n        u64 chunk_base = 1;\n        int\
    \ chunk_digits = 0;\n        while (chunk_base <= (BASE - 1) / (u64)base) {\n\
    \            chunk_base *= (u64)base;\n            ++chunk_digits;\n        }\n\
    \        BasicBigInteger value = abs();\n        vector<u64> parts;\n        while\
    \ (!value.is_zero()) parts.push_back(value.div_small_abs(chunk_base));\n     \
    \   append_in_base(out, parts.back(), base, 0);\n        for (int i = (int)parts.size()\
    \ - 2; i >= 0; --i) {\n            append_in_base(out, parts[i], base, chunk_digits);\n\
    \        }\n        return out;\n    }\n\n    bool is_zero() const { return digits.empty();\
    \ }\n    bool is_negative() const { return negative; }\n\n    BasicBigInteger\
    \ abs() const {\n        BasicBigInteger res = *this;\n        res.negative =\
    \ false;\n        return res;\n    }\n\n    BasicBigInteger operator+() const\
    \ { return *this; }\n\n    BasicBigInteger operator-() const {\n        BasicBigInteger\
    \ res = *this;\n        if (!res.is_zero()) res.negative = !res.negative;\n  \
    \      return res;\n    }\n\n    BasicBigInteger &operator+=(const BasicBigInteger\
    \ &other) {\n        if (other.is_zero()) return *this;\n        if (is_zero())\
    \ {\n            *this = other;\n            return *this;\n        }\n      \
    \  if (negative == other.negative) {\n            add_abs(other);\n          \
    \  return *this;\n        }\n        int cmp = compare_abs(*this, other);\n  \
    \      if (cmp == 0) {\n            digits.clear();\n            negative = false;\n\
    \        } else if (cmp > 0) {\n            sub_abs(other);\n        } else {\n\
    \            BasicBigInteger res = other;\n            res.sub_abs(*this);\n \
    \           *this = std::move(res);\n        }\n        return *this;\n    }\n\
    \n    BasicBigInteger &operator-=(const BasicBigInteger &other) {\n        return\
    \ *this += -other;\n    }\n\n    BasicBigInteger &operator*=(const BasicBigInteger\
    \ &other) {\n        if (is_zero() || other.is_zero()) {\n            digits.clear();\n\
    \            negative = false;\n            return *this;\n        }\n       \
    \ bool result_negative = negative != other.negative;\n        BasicBigInteger\
    \ result = multiply_abs(*this, other);\n        result.negative = result_negative;\n\
    \        *this = std::move(result);\n        return *this;\n    }\n\n    friend\
    \ BasicBigInteger operator+(BasicBigInteger lhs, const BasicBigInteger &rhs) {\
    \ return lhs += rhs; }\n    friend BasicBigInteger operator-(BasicBigInteger lhs,\
    \ const BasicBigInteger &rhs) { return lhs -= rhs; }\n    friend BasicBigInteger\
    \ operator*(BasicBigInteger lhs, const BasicBigInteger &rhs) { return lhs *= rhs;\
    \ }\n\n    friend bool operator==(const BasicBigInteger &a, const BasicBigInteger\
    \ &b) { return compare(a, b) == 0; }\n    friend bool operator!=(const BasicBigInteger\
    \ &a, const BasicBigInteger &b) { return compare(a, b) != 0; }\n    friend bool\
    \ operator<(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a,\
    \ b) < 0; }\n    friend bool operator<=(const BasicBigInteger &a, const BasicBigInteger\
    \ &b) { return compare(a, b) <= 0; }\n    friend bool operator>(const BasicBigInteger\
    \ &a, const BasicBigInteger &b) { return compare(a, b) > 0; }\n    friend bool\
    \ operator>=(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a,\
    \ b) >= 0; }\n\n    static pair<BasicBigInteger, BasicBigInteger> divmod(const\
    \ BasicBigInteger &a,\n                                                      \
    \   const BasicBigInteger &b) {\n        assert(!b.is_zero());\n        auto result\
    \ = divmod_abs(a.abs(), b.abs());\n        if (!result.first.is_zero()) result.first.negative\
    \ = a.negative != b.negative;\n        if (!result.second.is_zero()) result.second.negative\
    \ = a.negative;\n        return result;\n    }\n\n    static pair<BasicBigInteger,\
    \ BasicBigInteger> floor_divmod(const BasicBigInteger &a,\n                  \
    \                                             const BasicBigInteger &b) {\n  \
    \      auto result = divmod(a, b);\n        if (!result.second.is_zero() && a.negative\
    \ != b.negative) {\n            result.first -= 1;\n            result.second\
    \ += b;\n        }\n        return result;\n    }\n\n    friend pair<BasicBigInteger,\
    \ BasicBigInteger> divmod(const BasicBigInteger &a,\n                        \
    \                                 const BasicBigInteger &b) {\n        return\
    \ BasicBigInteger::divmod(a, b);\n    }\n\n    friend pair<BasicBigInteger, BasicBigInteger>\
    \ floor_divmod(const BasicBigInteger &a,\n                                   \
    \                            const BasicBigInteger &b) {\n        return BasicBigInteger::floor_divmod(a,\
    \ b);\n    }\n\n    BasicBigInteger &operator/=(const BasicBigInteger &other)\
    \ {\n        *this = divmod(*this, other).first;\n        return *this;\n    }\n\
    \n    BasicBigInteger &operator%=(const BasicBigInteger &other) {\n        *this\
    \ = divmod(*this, other).second;\n        return *this;\n    }\n\n    BasicBigInteger\
    \ &operator<<=(int bits) {\n        assert(bits >= 0);\n        if (is_zero()\
    \ || bits == 0) return *this;\n        auto chunk = shift_chunk();\n        while\
    \ (bits) {\n            int take = min(bits, chunk.first);\n            mul_small_abs(1ULL\
    \ << take);\n            bits -= take;\n        }\n        return *this;\n   \
    \ }\n\n    BasicBigInteger &operator>>=(int bits) {\n        assert(bits >= 0);\n\
    \        if (is_zero() || bits == 0) return *this;\n        bool was_negative\
    \ = negative;\n        bool discarded = false;\n        auto chunk = shift_chunk();\n\
    \        while (bits && !is_zero()) {\n            int take = min(bits, chunk.first);\n\
    \            discarded |= div_small_abs(1ULL << take) != 0;\n            bits\
    \ -= take;\n        }\n        if (was_negative && discarded) {\n            add_small_abs(1);\n\
    \            negative = true;\n        }\n        normalize();\n        return\
    \ *this;\n    }\n\n    friend BasicBigInteger operator/(BasicBigInteger lhs, const\
    \ BasicBigInteger &rhs) { return lhs /= rhs; }\n    friend BasicBigInteger operator%(BasicBigInteger\
    \ lhs, const BasicBigInteger &rhs) { return lhs %= rhs; }\n    friend BasicBigInteger\
    \ operator<<(BasicBigInteger lhs, int bits) { return lhs <<= bits; }\n    friend\
    \ BasicBigInteger operator>>(BasicBigInteger lhs, int bits) { return lhs >>= bits;\
    \ }\n};\n\nusing BigInteger = BasicBigInteger<BigIntegerDetail::DecimalRadix>;\n\
    using HexBigInteger = BasicBigInteger<BigIntegerDetail::HexRadix>;\n\n#endif\n\
    \n/**\n * @brief \u591A\u500D\u9577\u6574\u6570(BigInteger)\n */\n"
  dependsOn:
  - math/integer_convolution.cpp
  isVerificationFile: false
  path: util/biginteger.cpp
  requiredBy: []
  timestamp: '2026-07-18 15:59:16+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_multiplication_of_big_integers.test.cpp
  - test/yosupo_multiplication_of_hex_big_integers.test.cpp
  - test/yosupo_addition_of_big_integers.test.cpp
  - test/yosupo_addition_of_hex_big_integers.test.cpp
  - test/yosupo_division_of_big_integers.test.cpp
  - test/yosupo_division_of_hex_big_integers.test.cpp
date: 2026-03-20
documentation_of: util/biginteger.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u591A\u500D\u9577\u6574\u6570(BigInteger)"
---

## 説明
符号付き多倍長整数を扱う。
`BigInteger` は $10^{16}$ 基数の little endian limb 列を唯一の内部表現として持つ。
16 進入出力を中心に使う場合は、同じ API を $2^{60}$ 基数で実装した `HexBigInteger` を使う。

## できること
- `BigInteger()`
  `0` を作る
- `BigInteger(long long x)`
  `x` から作る
- `BigInteger(const string& s, int base = 10)`
  `s` から作る。`base` は $2$ 以上 $36$ 以下。不正な文字列なら assertion failure
- `x.assign(const string& s, int base = 10)`
  `s` を代入する。成功なら `true`、不正な文字列なら `false`
- `HexBigInteger(const string& s)`
  16 進文字列から作る
- `x.is_zero()`
  `x == 0` なら `true`
- `x.to_string(int base = 10)`
  `base` 表記の文字列にする。英字は小文字で返す
- `x += y`, `x -= y`, `x *= y`, `x /= y`, `x %= y`
  四則演算と余りを計算する。`/` は 0 方向に切り捨て、`%` は dividend と同符号の余りを返す。0 除算は assertion failure
- `x << k`, `x >> k`
  2 の冪でのシフトを行う
- `x < y`, `x <= y`, `x > y`, `x >= y`, `x == y`, `x != y`
  比較する
- `divmod(x, y)`
  `/` と `%` の結果を同時に返す。0 除算は assertion failure
- `floor_divmod(x, y)`
  商を負の無限大方向に丸め、divisor と同符号の余りを返す。0 除算は assertion failure

## 使い方
`Scanner` と `Printer` から直接入出力できる。

```cpp
BigInteger a, b;
sc.read(a, b);
auto [q, r] = divmod(a, b);
pr.println(q, r);
```

10 進中心なら `BigInteger`、16 進中心なら `HexBigInteger` を使う。
異なる基数の文字列も扱えるが、主基数以外の変換には追加コストがかかる。

## 実装上の補足

乗算は小さい入力で筆算、大きい入力で exact NTT を使う。
除算は商が短い入力で Knuth 法、それ以外の大きい入力で Newton 法による逆数計算を使う。
