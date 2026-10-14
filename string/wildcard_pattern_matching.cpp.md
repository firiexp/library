---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/integer_convolution.cpp
    title: "\u6574\u6570\u7573\u307F\u8FBC\u307F(2/3 NTT)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_wildcard_pattern_matching.test.cpp
    title: test/yosupo_aplusb_wildcard_pattern_matching.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_wildcard_pattern_matching.test.cpp
    title: test/yosupo_wildcard_pattern_matching.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30EF\u30A4\u30EB\u30C9\u30AB\u30FC\u30C9\u4ED8\u304D\u30D1\u30BF\
      \u30FC\u30F3\u7167\u5408"
    links: []
  bundledCode: "#line 1 \"string/wildcard_pattern_matching.cpp\"\n\n\n\n#line 1 \"\
    math/integer_convolution.cpp\"\n\n\n\n#ifndef FIRIEXP_LIBRARY_ARBITRARY_CONVOLUTION_U64_NAIVE_THRESHOLD\n\
    #define FIRIEXP_LIBRARY_ARBITRARY_CONVOLUTION_U64_NAIVE_THRESHOLD 8192\n#endif\n\
    \n#ifndef FIRIEXP_LIBRARY_ARBITRARY_SQUARE_U64_NAIVE_THRESHOLD\n#define FIRIEXP_LIBRARY_ARBITRARY_SQUARE_U64_NAIVE_THRESHOLD\
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
    \u7573\u307F\u8FBC\u307F(2/3 NTT)\n */\n\n\n#line 5 \"string/wildcard_pattern_matching.cpp\"\
    \n\nnamespace wildcard_pattern_matching_detail {\ntemplate<class Transform>\n\
    void filter_matches(const string &text, const string &pattern, char wildcard,\n\
    \                    const Transform &transform, vector<int> &result) {\n    using\
    \ mint = typename Transform::mint;\n    int n = (int)text.size(), m = (int)pattern.size(),\
    \ size = 1;\n    while (size < n + m - 1) size <<= 1;\n    vector<mint> a(size),\
    \ b(size), score(size);\n    for (int power = 1; power <= 3; ++power) {\n    \
    \    fill(a.begin() + n, a.end(), mint(0));\n        fill(b.begin() + m, b.end(),\
    \ mint(0));\n        for (int i = 0; i < n; ++i) {\n            unsigned int value\
    \ = text[i] == wildcard ? 0 : (unsigned char)text[i] + 1;\n            unsigned\
    \ int x = value;\n            for (int k = 1; k < power; ++k) x *= value;\n  \
    \          a[i] = mint::raw(x);\n        }\n        for (int i = 0; i < m; ++i)\
    \ {\n            unsigned int value = pattern[i] == wildcard ? 0 : (unsigned char)pattern[i]\
    \ + 1;\n            unsigned int x = value;\n            for (int k = 1; k < 4\
    \ - power; ++k) x *= value;\n            b[m - 1 - i] = mint::raw(x);\n      \
    \  }\n        transform.ntt(a, false);\n        transform.ntt(b, false);\n   \
    \     for (int i = 0; i < size; ++i) {\n            mint product = a[i] * b[i];\n\
    \            if (power == 2) score[i] -= product + product;\n            else\
    \ score[i] += product;\n        }\n    }\n    transform.ntt(score, true);\n  \
    \  for (int i = 0; i <= n - m; ++i) result[i] &= score[i + m - 1].val == 0;\n\
    }\n}\n\nvector<int> wildcard_pattern_matching(const string& text, const string&\
    \ pattern, char wildcard = '*') {\n    int n = (int)text.size(), m = (int)pattern.size();\n\
    \    if (m > n) return {};\n    if (m == 0) return vector<int>(n + 1, 1);\n  \
    \  assert((long long)n + m - 1 <= (1 << 21));\n    if (n + m - 1 >= 128) {\n \
    \       vector<int> result(n - m + 1, 1);\n        wildcard_pattern_matching_detail::filter_matches(text,\
    \ pattern, wildcard, BoundedConvolution::internal::ntt1(), result);\n        wildcard_pattern_matching_detail::filter_matches(text,\
    \ pattern, wildcard, BoundedConvolution::internal::ntt2(), result);\n        return\
    \ result;\n    }\n    vector<unsigned int> a(n), b(m), ap(n), bp(m);\n    for\
    \ (int i = 0; i < n; ++i)\n        a[i] = text[i] == wildcard ? 0 : (unsigned\
    \ char)text[i] + 1;\n    for (int i = 0; i < m; ++i)\n        b[m - 1 - i] = pattern[i]\
    \ == wildcard ? 0 : (unsigned char)pattern[i] + 1;\n    vector<long long> score(n\
    \ - m + 1);\n    for (int power = 1; power <= 3; ++power) {\n        for (int\
    \ i = 0; i < n; ++i) {\n            ap[i] = a[i];\n            for (int k = 1;\
    \ k < power; ++k) ap[i] *= a[i];\n        }\n        for (int i = 0; i < m; ++i)\
    \ {\n            bp[i] = b[i];\n            for (int k = 1; k < 4 - power; ++k)\
    \ bp[i] *= b[i];\n        }\n        auto c = BoundedConvolution::convolution_u64(ap,\
    \ bp);\n        int sign = power == 2 ? -2 : 1;\n        for (int i = 0; i <=\
    \ n - m; ++i) score[i] += sign * (long long)c[i + m - 1];\n    }\n    vector<int>\
    \ result(n - m + 1);\n    for (int i = 0; i <= n - m; ++i) result[i] = score[i]\
    \ == 0;\n    return result;\n}\n\n\n\n/**\n * @brief \u30EF\u30A4\u30EB\u30C9\u30AB\
    \u30FC\u30C9\u4ED8\u304D\u30D1\u30BF\u30FC\u30F3\u7167\u5408\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_STRING_WILDCARD_PATTERN_MATCHING_CPP\n#define FIRIEXP_LIBRARY_STRING_WILDCARD_PATTERN_MATCHING_CPP\n\
    \n#include \"../math/integer_convolution.cpp\"\n\nnamespace wildcard_pattern_matching_detail\
    \ {\ntemplate<class Transform>\nvoid filter_matches(const string &text, const\
    \ string &pattern, char wildcard,\n                    const Transform &transform,\
    \ vector<int> &result) {\n    using mint = typename Transform::mint;\n    int\
    \ n = (int)text.size(), m = (int)pattern.size(), size = 1;\n    while (size <\
    \ n + m - 1) size <<= 1;\n    vector<mint> a(size), b(size), score(size);\n  \
    \  for (int power = 1; power <= 3; ++power) {\n        fill(a.begin() + n, a.end(),\
    \ mint(0));\n        fill(b.begin() + m, b.end(), mint(0));\n        for (int\
    \ i = 0; i < n; ++i) {\n            unsigned int value = text[i] == wildcard ?\
    \ 0 : (unsigned char)text[i] + 1;\n            unsigned int x = value;\n     \
    \       for (int k = 1; k < power; ++k) x *= value;\n            a[i] = mint::raw(x);\n\
    \        }\n        for (int i = 0; i < m; ++i) {\n            unsigned int value\
    \ = pattern[i] == wildcard ? 0 : (unsigned char)pattern[i] + 1;\n            unsigned\
    \ int x = value;\n            for (int k = 1; k < 4 - power; ++k) x *= value;\n\
    \            b[m - 1 - i] = mint::raw(x);\n        }\n        transform.ntt(a,\
    \ false);\n        transform.ntt(b, false);\n        for (int i = 0; i < size;\
    \ ++i) {\n            mint product = a[i] * b[i];\n            if (power == 2)\
    \ score[i] -= product + product;\n            else score[i] += product;\n    \
    \    }\n    }\n    transform.ntt(score, true);\n    for (int i = 0; i <= n - m;\
    \ ++i) result[i] &= score[i + m - 1].val == 0;\n}\n}\n\nvector<int> wildcard_pattern_matching(const\
    \ string& text, const string& pattern, char wildcard = '*') {\n    int n = (int)text.size(),\
    \ m = (int)pattern.size();\n    if (m > n) return {};\n    if (m == 0) return\
    \ vector<int>(n + 1, 1);\n    assert((long long)n + m - 1 <= (1 << 21));\n   \
    \ if (n + m - 1 >= 128) {\n        vector<int> result(n - m + 1, 1);\n       \
    \ wildcard_pattern_matching_detail::filter_matches(text, pattern, wildcard, BoundedConvolution::internal::ntt1(),\
    \ result);\n        wildcard_pattern_matching_detail::filter_matches(text, pattern,\
    \ wildcard, BoundedConvolution::internal::ntt2(), result);\n        return result;\n\
    \    }\n    vector<unsigned int> a(n), b(m), ap(n), bp(m);\n    for (int i = 0;\
    \ i < n; ++i)\n        a[i] = text[i] == wildcard ? 0 : (unsigned char)text[i]\
    \ + 1;\n    for (int i = 0; i < m; ++i)\n        b[m - 1 - i] = pattern[i] ==\
    \ wildcard ? 0 : (unsigned char)pattern[i] + 1;\n    vector<long long> score(n\
    \ - m + 1);\n    for (int power = 1; power <= 3; ++power) {\n        for (int\
    \ i = 0; i < n; ++i) {\n            ap[i] = a[i];\n            for (int k = 1;\
    \ k < power; ++k) ap[i] *= a[i];\n        }\n        for (int i = 0; i < m; ++i)\
    \ {\n            bp[i] = b[i];\n            for (int k = 1; k < 4 - power; ++k)\
    \ bp[i] *= b[i];\n        }\n        auto c = BoundedConvolution::convolution_u64(ap,\
    \ bp);\n        int sign = power == 2 ? -2 : 1;\n        for (int i = 0; i <=\
    \ n - m; ++i) score[i] += sign * (long long)c[i + m - 1];\n    }\n    vector<int>\
    \ result(n - m + 1);\n    for (int i = 0; i <= n - m; ++i) result[i] = score[i]\
    \ == 0;\n    return result;\n}\n\n#endif\n\n/**\n * @brief \u30EF\u30A4\u30EB\u30C9\
    \u30AB\u30FC\u30C9\u4ED8\u304D\u30D1\u30BF\u30FC\u30F3\u7167\u5408\n */\n"
  dependsOn:
  - math/integer_convolution.cpp
  isVerificationFile: false
  path: string/wildcard_pattern_matching.cpp
  requiredBy: []
  timestamp: '2026-10-14 20:38:29+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_wildcard_pattern_matching.test.cpp
  - test/yosupo_aplusb_wildcard_pattern_matching.test.cpp
documentation_of: string/wildcard_pattern_matching.cpp
layout: document
title: "\u30EF\u30A4\u30EB\u30C9\u30AB\u30FC\u30C9\u4ED8\u304D\u30D1\u30BF\u30FC\u30F3\
  \u7167\u5408"
---

## 説明
文字列とパターンの両方にワイルドカードを含むパターン照合を行う。
ワイルドカードは任意の1文字に一致する。
文字列の長さを $N$、パターンの長さを $M$ として、時間は $O((N+M)\log(N+M+1))$、領域は $O(N+M)$。

## できること
- `vector<int> wildcard_pattern_matching(const string& text, const string& pattern, char wildcard = '*')`
  `text` の開始位置 $0,1,\ldots,N-M$ それぞれについて、`pattern` と一致すれば $1$、一致しなければ $0$ を返す

## 使い方
```cpp
auto matches = wildcard_pattern_matching("ab*aba", "a*");
```

この例では `{1, 0, 1, 1, 0}` を返す。
`pattern` が `text` より長い場合は空列を返す。空の `pattern` は全 $N+1$ 箇所で一致する。
任意の byte 列を扱えるが、`wildcard` に指定した文字は通常文字として使えない。

## 実装上の補足
$1\le M\le N$ の場合、$N+M-1\le 2^{21}$ が必要。
ワイルドカードを $0$、通常文字を byte 値 $+1$ に変換し、不一致の指標 $\sum ab(a-b)^2$ を求める。
$N+M-1\ge128$ では、各法で3項の積を周波数領域で合計し、逆 NTT を1回だけ行う。NTT は合計14回で、作業配列3本を使い回し、法ごとに順に処理する。
指標は非負で、$M\le2^{20}$ より $\mathrm{score}\le M\cdot256^4\le2^{52}<998244353\cdot1004535809$。
この2法でともに零なら整数としても零なので、剰余の衝突による誤一致はない。逆 NTT の長さ倍は各法で可逆なため、零判定には正規化も整数復元も不要。
短い入力では従来どおり3回の整数畳み込みで計算する。
