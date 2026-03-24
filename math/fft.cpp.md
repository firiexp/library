---
category: "\u6570\u5B66"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: tree/frequency_table_of_tree_distance.cpp
    title: Frequency Table of Tree Distance
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_convolution_mod_1000000007_fft.test.cpp
    title: test/yosupo_convolution_mod_1000000007_fft.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_frequency_table_of_tree_distance.test.cpp
    title: test/yosupo_frequency_table_of_tree_distance.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4EFB\u610FMOD\u7573\u307F\u8FBC\u307F(3 NTT + Garner)"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.20/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.20/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.20/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 355, in update\n    raise BundleErrorAt(path, i + 1, \"found codes out\
    \ of include guard\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fft.cpp: line 346: found codes out of include guard\n"
  code: "#ifndef FIRIEXP_LIBRARY_MATH_FFT_CORE_CPP\n#define FIRIEXP_LIBRARY_MATH_FFT_CORE_CPP\n\
    \n#ifndef FIRIEXP_LIBRARY_ARBITRARY_CONVOLUTION_U64_NAIVE_THRESHOLD\n#define FIRIEXP_LIBRARY_ARBITRARY_CONVOLUTION_U64_NAIVE_THRESHOLD\
    \ 8192\n#endif\n\n#ifndef FIRIEXP_LIBRARY_ARBITRARY_SQUARE_U64_NAIVE_THRESHOLD\n\
    #define FIRIEXP_LIBRARY_ARBITRARY_SQUARE_U64_NAIVE_THRESHOLD 32768\n#endif\n\n\
    namespace ArbitraryConvolution {\n    template<unsigned int M>\n    struct StaticModInt\
    \ {\n        unsigned int val;\n        StaticModInt() : val(0) {}\n        template<class\
    \ T>\n        StaticModInt(T v) {\n            long long x = (long long)(v % (long\
    \ long)M);\n            if (x < 0) x += M;\n            val = (unsigned int)x;\n\
    \        }\n        static StaticModInt raw(unsigned int v) {\n            StaticModInt\
    \ x;\n            x.val = v;\n            return x;\n        }\n        StaticModInt&\
    \ operator+=(const StaticModInt& rhs) {\n            val += rhs.val;\n       \
    \     if (val >= M) val -= M;\n            return *this;\n        }\n        StaticModInt&\
    \ operator-=(const StaticModInt& rhs) {\n            val -= rhs.val;\n       \
    \     if (val >= M) val += M;\n            return *this;\n        }\n        StaticModInt&\
    \ operator*=(const StaticModInt& rhs) {\n            val = (unsigned int)((unsigned\
    \ long long)val * rhs.val % M);\n            return *this;\n        }\n      \
    \  StaticModInt pow(long long n) const {\n            StaticModInt x = *this,\
    \ r = 1;\n            while (n) {\n                if (n & 1) r *= x;\n      \
    \          x *= x;\n                n >>= 1;\n            }\n            return\
    \ r;\n        }\n        StaticModInt inv() const { return pow(M - 2); }\n   \
    \     friend StaticModInt operator+(StaticModInt lhs, const StaticModInt& rhs)\
    \ { return lhs += rhs; }\n        friend StaticModInt operator-(StaticModInt lhs,\
    \ const StaticModInt& rhs) { return lhs -= rhs; }\n        friend StaticModInt\
    \ operator*(StaticModInt lhs, const StaticModInt& rhs) { return lhs *= rhs; }\n\
    \        friend bool operator==(const StaticModInt& lhs, const StaticModInt& rhs)\
    \ { return lhs.val == rhs.val; }\n        friend bool operator!=(const StaticModInt&\
    \ lhs, const StaticModInt& rhs) { return lhs.val != rhs.val; }\n    };\n\n   \
    \ template<unsigned int MOD_, unsigned int PRIMITIVE_ROOT_>\n    struct NTT {\n\
    \        using mint = StaticModInt<MOD_>;\n        static constexpr unsigned int\
    \ MODV = MOD_;\n        static constexpr unsigned int G = PRIMITIVE_ROOT_;\n \
    \       mint root[30], iroot[30], rate2[30], irate2[30], rate3[30], irate3[30],\
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
    \    return res;\n    }\n}\n\n#endif\n\n#ifndef FIRIEXP_LIBRARY_FFT_EXACT_ONLY\n\
    #ifndef FIRIEXP_LIBRARY_MATH_FFT_POLY_CPP\n#define FIRIEXP_LIBRARY_MATH_FFT_POLY_CPP\n\
    \n#include \"../util/modint.cpp\"\n\nnamespace ArbitraryConvolution {\n    vector<unsigned\
    \ int> convolution_mod(const vector<unsigned int> &a, const vector<unsigned int>\
    \ &b) {\n        if (a.empty() || b.empty()) return {};\n        static const\
    \ NTT1 ntt1;\n        static const NTT2 ntt2;\n        static const NTT3 ntt3;\n\
    \        auto c1 = ntt1.convolution(a, b);\n        auto c2 = ntt2.convolution(a,\
    \ b);\n        auto c3 = ntt3.convolution(a, b);\n        vector<unsigned int>\
    \ res(c1.size());\n        for (int i = 0; i < (int)res.size(); ++i) {\n     \
    \       res[i] = internal::combine_mod<MOD>(c1[i], c2[i], c3[i]);\n        }\n\
    \        return res;\n    }\n}\n\nstruct poly {\n    vector<mint> v;\n    poly()\
    \ = default;\n    explicit poly(int n) : v(n) {}\n    explicit poly(vector<mint>\
    \ vv) : v(std::move(vv)) {}\n    int size() const { return (int)v.size(); }\n\
    \    poly cut(int len) {\n        if (len < (int)v.size()) v.resize((size_t)len);\n\
    \        return *this;\n    }\n    mint& operator[](int i) { return v[i]; }\n\
    \    const mint& operator[](int i) const { return v[i]; }\n    poly& operator+=(const\
    \ poly &a) {\n        v.resize(max(size(), a.size()));\n        for (int i = 0;\
    \ i < a.size(); ++i) v[i] += a.v[i];\n        return *this;\n    }\n    poly&\
    \ operator-=(const poly &a) {\n        v.resize(max(size(), a.size()));\n    \
    \    for (int i = 0; i < a.size(); ++i) v[i] -= a.v[i];\n        return *this;\n\
    \    }\n    poly& operator*=(const poly &a) {\n        if (size() == 0 || a.size()\
    \ == 0) {\n            v.clear();\n            return *this;\n        }\n    \
    \    vector<unsigned int> x(size()), y(a.size());\n        for (int i = 0; i <\
    \ size(); ++i) x[i] = v[i].val;\n        for (int i = 0; i < a.size(); ++i) y[i]\
    \ = a.v[i].val;\n        auto z = ArbitraryConvolution::convolution_mod(x, y);\n\
    \        v.resize(z.size());\n        for (int i = 0; i < (int)z.size(); ++i)\
    \ v[i] = z[i];\n        return *this;\n    }\n    poly& operator/=(const poly\
    \ &a) { return (*this) *= a.inv(); }\n    poly operator+(const poly &a) const\
    \ { return poly(*this) += a; }\n    poly operator-(const poly &a) const { return\
    \ poly(*this) -= a; }\n    poly operator*(const poly &a) const { return poly(*this)\
    \ *= a; }\n\n    poly inv() const {\n        int n = size();\n        poly r(1);\n\
    \        r[0] = v[0].inv();\n        int k = 1;\n        while (k < n) {\n   \
    \         k <<= 1;\n            poly f(k);\n            for (int i = 0; i < min(k,\
    \ n); ++i) f[i] = v[i];\n            poly nr = (r * r * f).cut(k);\n         \
    \   for (int i = 0; i < k / 2; ++i) {\n                nr[i] = r[i] + r[i] - nr[i];\n\
    \                nr[i + k / 2] = -nr[i + k / 2];\n            }\n            r\
    \ = nr;\n        }\n        r.v.resize(n);\n        return r;\n    }\n};\n\n/**\n\
    \ * @brief \u4EFB\u610FMOD\u7573\u307F\u8FBC\u307F(3 NTT + Garner)\n */\n\n#endif\n\
    #endif\n"
  dependsOn:
  - util/modint.cpp
  isVerificationFile: false
  path: math/fft.cpp
  requiredBy:
  - tree/frequency_table_of_tree_distance.cpp
  timestamp: '2026-03-15 11:18:22+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_frequency_table_of_tree_distance.test.cpp
  - test/yosupo_convolution_mod_1000000007_fft.test.cpp
date: 2026-03-15
documentation_of: math/fft.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u4EFB\u610FMOD\u7573\u307F\u8FBC\u307F(3 NTT + Garner)"
---

## 説明
3 つの NTT 友好素数で畳み込み、Garner で任意 MOD に復元する。
複素 FFT を使わないので誤差がなく、計算量は $O(N \log N)$。

## できること
- `vector<unsigned int> ArbitraryConvolution::convolution_mod(const vector<unsigned int>& a, const vector<unsigned int>& b)`
  `MOD` 上の畳み込みを返す。どちらかが空なら空配列
- `vector<unsigned long long> ArbitraryConvolution::convolution_u64(const vector<unsigned int>& a, const vector<unsigned int>& b)`
  整数値を保ったまま畳み込みを返す。どちらかが空なら空配列
- `vector<unsigned long long> ArbitraryConvolution::square_u64(const vector<unsigned int>& a)`
  整数値を保ったまま自己畳み込みを返す。空なら空配列
- `poly operator*(const poly& a, const poly& b)`
  多項式の積を返す
- `poly inv() const`
  定数項が 0 でない多項式の逆数を返す

## 使い方
`MOD` を先に定義してから読み込む。
`poly` に係数を入れて `a * b` を呼べばよい。
exact な整数値が必要なら `ArbitraryConvolution::convolution_u64` か `ArbitraryConvolution::square_u64` を使う。

## 実装上の補足
3 素数は `167772161`, `469762049`, `1224736769` を使う。
`square_u64` は self-convolution 専用に、各 mod で変換 1 回で済む経路を持つ。
Library Checker の `convolution_mod_1000000007` は verify 済み。
