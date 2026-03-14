---
category: "\u6570\u5B66"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_convolution_mod_1000000007_fft.test.cpp
    title: test/yosupo_convolution_mod_1000000007_fft.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4EFB\u610FMOD\u7573\u307F\u8FBC\u307F(3 NTT + Garner)"
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
    MOD)\n */\n\n\n#line 2 \"math/fft.cpp\"\n\nnamespace ArbitraryConvolution {\n\
    \    template<uint M>\n    struct StaticModInt {\n        uint val;\n        StaticModInt()\
    \ : val(0) {}\n        template<class T>\n        StaticModInt(T v) {\n      \
    \      long long x = (long long)(v % (long long)M);\n            if (x < 0) x\
    \ += M;\n            val = (uint)x;\n        }\n        static StaticModInt raw(uint\
    \ v) {\n            StaticModInt x;\n            x.val = v;\n            return\
    \ x;\n        }\n        StaticModInt& operator+=(const StaticModInt& rhs) {\n\
    \            val += rhs.val;\n            if (val >= M) val -= M;\n          \
    \  return *this;\n        }\n        StaticModInt& operator-=(const StaticModInt&\
    \ rhs) {\n            val -= rhs.val;\n            if (val >= M) val += M;\n \
    \           return *this;\n        }\n        StaticModInt& operator*=(const StaticModInt&\
    \ rhs) {\n            val = (uint)((unsigned long long)val * rhs.val % M);\n \
    \           return *this;\n        }\n        StaticModInt pow(long long n) const\
    \ {\n            StaticModInt x = *this, r = 1;\n            while (n) {\n   \
    \             if (n & 1) r *= x;\n                x *= x;\n                n >>=\
    \ 1;\n            }\n            return r;\n        }\n        StaticModInt inv()\
    \ const { return pow(M - 2); }\n        friend StaticModInt operator+(StaticModInt\
    \ lhs, const StaticModInt& rhs) { return lhs += rhs; }\n        friend StaticModInt\
    \ operator-(StaticModInt lhs, const StaticModInt& rhs) { return lhs -= rhs; }\n\
    \        friend StaticModInt operator*(StaticModInt lhs, const StaticModInt& rhs)\
    \ { return lhs *= rhs; }\n        friend bool operator==(const StaticModInt& lhs,\
    \ const StaticModInt& rhs) { return lhs.val == rhs.val; }\n        friend bool\
    \ operator!=(const StaticModInt& lhs, const StaticModInt& rhs) { return lhs.val\
    \ != rhs.val; }\n    };\n\n    template<uint MOD_, uint PRIMITIVE_ROOT_>\n   \
    \ struct NTT {\n        using mint = StaticModInt<MOD_>;\n        static constexpr\
    \ uint MODV = MOD_;\n        static constexpr uint G = PRIMITIVE_ROOT_;\n\n  \
    \      void ntt(vector<mint> &a, bool invert) const {\n            int n = (int)a.size();\n\
    \            for (int i = 1, j = 0; i < n; ++i) {\n                int bit = n\
    \ >> 1;\n                for (; j & bit; bit >>= 1) j ^= bit;\n              \
    \  j ^= bit;\n                if (i < j) swap(a[i], a[j]);\n            }\n  \
    \          for (int len = 2; len <= n; len <<= 1) {\n                mint wlen\
    \ = mint(G).pow((MODV - 1) / len);\n                if (invert) wlen = wlen.inv();\n\
    \                for (int i = 0; i < n; i += len) {\n                    mint\
    \ w = 1;\n                    for (int j = 0; j < len / 2; ++j) {\n          \
    \              mint u = a[i + j];\n                        mint v = a[i + j +\
    \ len / 2] * w;\n                        a[i + j] = u + v;\n                 \
    \       a[i + j + len / 2] = u - v;\n                        w *= wlen;\n    \
    \                }\n                }\n            }\n            if (invert)\
    \ {\n                mint inv_n = mint(n).inv();\n                for (auto &x\
    \ : a) x *= inv_n;\n            }\n        }\n\n        vector<uint> convolution(const\
    \ vector<uint> &a, const vector<uint> &b) const {\n            if (a.empty() ||\
    \ b.empty()) return {};\n            int need = (int)a.size() + (int)b.size()\
    \ - 1;\n            int n = 1;\n            while (n < need) n <<= 1;\n      \
    \      vector<mint> fa(n), fb(n);\n            for (int i = 0; i < (int)a.size();\
    \ ++i) fa[i] = a[i];\n            for (int i = 0; i < (int)b.size(); ++i) fb[i]\
    \ = b[i];\n            ntt(fa, false);\n            ntt(fb, false);\n        \
    \    for (int i = 0; i < n; ++i) fa[i] *= fb[i];\n            ntt(fa, true);\n\
    \            vector<uint> res(need);\n            for (int i = 0; i < need; ++i)\
    \ res[i] = fa[i].val;\n            return res;\n        }\n    };\n\n    using\
    \ NTT1 = NTT<167772161, 3>;\n    using NTT2 = NTT<469762049, 3>;\n    using NTT3\
    \ = NTT<1224736769, 3>;\n\n    vector<uint> convolution_mod(const vector<uint>\
    \ &a, const vector<uint> &b) {\n        if (a.empty() || b.empty()) return {};\n\
    \        static const NTT1 ntt1;\n        static const NTT2 ntt2;\n        static\
    \ const NTT3 ntt3;\n        static const long long m1 = 167772161LL;\n       \
    \ static const long long m2 = 469762049LL;\n        static const long long m3\
    \ = 1224736769LL;\n        static const long long m1_inv_m2 = StaticModInt<469762049>(m1).inv().val;\n\
    \        static const long long m12_mod_m3 = (m1 % m3) * (m2 % m3) % m3;\n   \
    \     static const long long m12_inv_m3 = StaticModInt<1224736769>((long long)m12_mod_m3).inv().val;\n\
    \        static const unsigned long long m12 = (unsigned long long)m1 * (unsigned\
    \ long long)m2;\n        static const long long m1_mod = m1 % MOD;\n        static\
    \ const long long m12_mod = m12 % MOD;\n\n        auto c1 = ntt1.convolution(a,\
    \ b);\n        auto c2 = ntt2.convolution(a, b);\n        auto c3 = ntt3.convolution(a,\
    \ b);\n        vector<uint> res(c1.size());\n        for (int i = 0; i < (int)res.size();\
    \ ++i) {\n            long long x1 = c1[i];\n            long long x2 = c2[i];\n\
    \            long long x3 = c3[i];\n            long long t = (x2 - x1) % m2;\n\
    \            if (t < 0) t += m2;\n            t = t * m1_inv_m2 % m2;\n      \
    \      long long x12 = (long long)(((__int128)x1 + (__int128)m1 * t) % m3);\n\
    \            long long u = (x3 - x12) % m3;\n            if (u < 0) u += m3;\n\
    \            u = u * m12_inv_m3 % m3;\n            __int128 value = x1 % MOD;\n\
    \            value += (__int128)m1_mod * t;\n            value += (__int128)m12_mod\
    \ * u;\n            res[i] = (uint)(value % MOD);\n        }\n        return res;\n\
    \    }\n}\n\nstruct poly {\n    vector<mint> v;\n    poly() = default;\n    explicit\
    \ poly(int n) : v(n) {}\n    explicit poly(vector<mint> vv) : v(std::move(vv))\
    \ {}\n    int size() const { return (int)v.size(); }\n    poly cut(int len) {\n\
    \        if (len < (int)v.size()) v.resize((size_t)len);\n        return *this;\n\
    \    }\n    mint& operator[](int i) { return v[i]; }\n    const mint& operator[](int\
    \ i) const { return v[i]; }\n    poly& operator+=(const poly &a) {\n        v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) v[i] += a.v[i];\n  \
    \      return *this;\n    }\n    poly& operator-=(const poly &a) {\n        v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) v[i] -= a.v[i];\n  \
    \      return *this;\n    }\n    poly& operator*=(const poly &a) {\n        if\
    \ (size() == 0 || a.size() == 0) {\n            v.clear();\n            return\
    \ *this;\n        }\n        vector<uint> x(size()), y(a.size());\n        for\
    \ (int i = 0; i < size(); ++i) x[i] = v[i].val;\n        for (int i = 0; i < a.size();\
    \ ++i) y[i] = a.v[i].val;\n        auto z = ArbitraryConvolution::convolution_mod(x,\
    \ y);\n        v.resize(z.size());\n        for (int i = 0; i < (int)z.size();\
    \ ++i) v[i] = z[i];\n        return *this;\n    }\n    poly& operator/=(const\
    \ poly &a) { return (*this) *= a.inv(); }\n    poly operator+(const poly &a) const\
    \ { return poly(*this) += a; }\n    poly operator-(const poly &a) const { return\
    \ poly(*this) -= a; }\n    poly operator*(const poly &a) const { return poly(*this)\
    \ *= a; }\n\n    poly inv() const {\n        int n = size();\n        poly r(1);\n\
    \        r[0] = v[0].inv();\n        int k = 1;\n        while (k < n) {\n   \
    \         k <<= 1;\n            poly f(k);\n            for (int i = 0; i < min(k,\
    \ n); ++i) f[i] = v[i];\n            poly nr = (r * r * f).cut(k);\n         \
    \   for (int i = 0; i < k / 2; ++i) {\n                nr[i] = r[i] + r[i] - nr[i];\n\
    \                nr[i + k / 2] = -nr[i + k / 2];\n            }\n            r\
    \ = nr;\n        }\n        r.v.resize(n);\n        return r;\n    }\n};\n\n/**\n\
    \ * @brief \u4EFB\u610FMOD\u7573\u307F\u8FBC\u307F(3 NTT + Garner)\n */\n"
  code: "#include \"../util/modint.cpp\"\n\nnamespace ArbitraryConvolution {\n   \
    \ template<uint M>\n    struct StaticModInt {\n        uint val;\n        StaticModInt()\
    \ : val(0) {}\n        template<class T>\n        StaticModInt(T v) {\n      \
    \      long long x = (long long)(v % (long long)M);\n            if (x < 0) x\
    \ += M;\n            val = (uint)x;\n        }\n        static StaticModInt raw(uint\
    \ v) {\n            StaticModInt x;\n            x.val = v;\n            return\
    \ x;\n        }\n        StaticModInt& operator+=(const StaticModInt& rhs) {\n\
    \            val += rhs.val;\n            if (val >= M) val -= M;\n          \
    \  return *this;\n        }\n        StaticModInt& operator-=(const StaticModInt&\
    \ rhs) {\n            val -= rhs.val;\n            if (val >= M) val += M;\n \
    \           return *this;\n        }\n        StaticModInt& operator*=(const StaticModInt&\
    \ rhs) {\n            val = (uint)((unsigned long long)val * rhs.val % M);\n \
    \           return *this;\n        }\n        StaticModInt pow(long long n) const\
    \ {\n            StaticModInt x = *this, r = 1;\n            while (n) {\n   \
    \             if (n & 1) r *= x;\n                x *= x;\n                n >>=\
    \ 1;\n            }\n            return r;\n        }\n        StaticModInt inv()\
    \ const { return pow(M - 2); }\n        friend StaticModInt operator+(StaticModInt\
    \ lhs, const StaticModInt& rhs) { return lhs += rhs; }\n        friend StaticModInt\
    \ operator-(StaticModInt lhs, const StaticModInt& rhs) { return lhs -= rhs; }\n\
    \        friend StaticModInt operator*(StaticModInt lhs, const StaticModInt& rhs)\
    \ { return lhs *= rhs; }\n        friend bool operator==(const StaticModInt& lhs,\
    \ const StaticModInt& rhs) { return lhs.val == rhs.val; }\n        friend bool\
    \ operator!=(const StaticModInt& lhs, const StaticModInt& rhs) { return lhs.val\
    \ != rhs.val; }\n    };\n\n    template<uint MOD_, uint PRIMITIVE_ROOT_>\n   \
    \ struct NTT {\n        using mint = StaticModInt<MOD_>;\n        static constexpr\
    \ uint MODV = MOD_;\n        static constexpr uint G = PRIMITIVE_ROOT_;\n\n  \
    \      void ntt(vector<mint> &a, bool invert) const {\n            int n = (int)a.size();\n\
    \            for (int i = 1, j = 0; i < n; ++i) {\n                int bit = n\
    \ >> 1;\n                for (; j & bit; bit >>= 1) j ^= bit;\n              \
    \  j ^= bit;\n                if (i < j) swap(a[i], a[j]);\n            }\n  \
    \          for (int len = 2; len <= n; len <<= 1) {\n                mint wlen\
    \ = mint(G).pow((MODV - 1) / len);\n                if (invert) wlen = wlen.inv();\n\
    \                for (int i = 0; i < n; i += len) {\n                    mint\
    \ w = 1;\n                    for (int j = 0; j < len / 2; ++j) {\n          \
    \              mint u = a[i + j];\n                        mint v = a[i + j +\
    \ len / 2] * w;\n                        a[i + j] = u + v;\n                 \
    \       a[i + j + len / 2] = u - v;\n                        w *= wlen;\n    \
    \                }\n                }\n            }\n            if (invert)\
    \ {\n                mint inv_n = mint(n).inv();\n                for (auto &x\
    \ : a) x *= inv_n;\n            }\n        }\n\n        vector<uint> convolution(const\
    \ vector<uint> &a, const vector<uint> &b) const {\n            if (a.empty() ||\
    \ b.empty()) return {};\n            int need = (int)a.size() + (int)b.size()\
    \ - 1;\n            int n = 1;\n            while (n < need) n <<= 1;\n      \
    \      vector<mint> fa(n), fb(n);\n            for (int i = 0; i < (int)a.size();\
    \ ++i) fa[i] = a[i];\n            for (int i = 0; i < (int)b.size(); ++i) fb[i]\
    \ = b[i];\n            ntt(fa, false);\n            ntt(fb, false);\n        \
    \    for (int i = 0; i < n; ++i) fa[i] *= fb[i];\n            ntt(fa, true);\n\
    \            vector<uint> res(need);\n            for (int i = 0; i < need; ++i)\
    \ res[i] = fa[i].val;\n            return res;\n        }\n    };\n\n    using\
    \ NTT1 = NTT<167772161, 3>;\n    using NTT2 = NTT<469762049, 3>;\n    using NTT3\
    \ = NTT<1224736769, 3>;\n\n    vector<uint> convolution_mod(const vector<uint>\
    \ &a, const vector<uint> &b) {\n        if (a.empty() || b.empty()) return {};\n\
    \        static const NTT1 ntt1;\n        static const NTT2 ntt2;\n        static\
    \ const NTT3 ntt3;\n        static const long long m1 = 167772161LL;\n       \
    \ static const long long m2 = 469762049LL;\n        static const long long m3\
    \ = 1224736769LL;\n        static const long long m1_inv_m2 = StaticModInt<469762049>(m1).inv().val;\n\
    \        static const long long m12_mod_m3 = (m1 % m3) * (m2 % m3) % m3;\n   \
    \     static const long long m12_inv_m3 = StaticModInt<1224736769>((long long)m12_mod_m3).inv().val;\n\
    \        static const unsigned long long m12 = (unsigned long long)m1 * (unsigned\
    \ long long)m2;\n        static const long long m1_mod = m1 % MOD;\n        static\
    \ const long long m12_mod = m12 % MOD;\n\n        auto c1 = ntt1.convolution(a,\
    \ b);\n        auto c2 = ntt2.convolution(a, b);\n        auto c3 = ntt3.convolution(a,\
    \ b);\n        vector<uint> res(c1.size());\n        for (int i = 0; i < (int)res.size();\
    \ ++i) {\n            long long x1 = c1[i];\n            long long x2 = c2[i];\n\
    \            long long x3 = c3[i];\n            long long t = (x2 - x1) % m2;\n\
    \            if (t < 0) t += m2;\n            t = t * m1_inv_m2 % m2;\n      \
    \      long long x12 = (long long)(((__int128)x1 + (__int128)m1 * t) % m3);\n\
    \            long long u = (x3 - x12) % m3;\n            if (u < 0) u += m3;\n\
    \            u = u * m12_inv_m3 % m3;\n            __int128 value = x1 % MOD;\n\
    \            value += (__int128)m1_mod * t;\n            value += (__int128)m12_mod\
    \ * u;\n            res[i] = (uint)(value % MOD);\n        }\n        return res;\n\
    \    }\n}\n\nstruct poly {\n    vector<mint> v;\n    poly() = default;\n    explicit\
    \ poly(int n) : v(n) {}\n    explicit poly(vector<mint> vv) : v(std::move(vv))\
    \ {}\n    int size() const { return (int)v.size(); }\n    poly cut(int len) {\n\
    \        if (len < (int)v.size()) v.resize((size_t)len);\n        return *this;\n\
    \    }\n    mint& operator[](int i) { return v[i]; }\n    const mint& operator[](int\
    \ i) const { return v[i]; }\n    poly& operator+=(const poly &a) {\n        v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) v[i] += a.v[i];\n  \
    \      return *this;\n    }\n    poly& operator-=(const poly &a) {\n        v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) v[i] -= a.v[i];\n  \
    \      return *this;\n    }\n    poly& operator*=(const poly &a) {\n        if\
    \ (size() == 0 || a.size() == 0) {\n            v.clear();\n            return\
    \ *this;\n        }\n        vector<uint> x(size()), y(a.size());\n        for\
    \ (int i = 0; i < size(); ++i) x[i] = v[i].val;\n        for (int i = 0; i < a.size();\
    \ ++i) y[i] = a.v[i].val;\n        auto z = ArbitraryConvolution::convolution_mod(x,\
    \ y);\n        v.resize(z.size());\n        for (int i = 0; i < (int)z.size();\
    \ ++i) v[i] = z[i];\n        return *this;\n    }\n    poly& operator/=(const\
    \ poly &a) { return (*this) *= a.inv(); }\n    poly operator+(const poly &a) const\
    \ { return poly(*this) += a; }\n    poly operator-(const poly &a) const { return\
    \ poly(*this) -= a; }\n    poly operator*(const poly &a) const { return poly(*this)\
    \ *= a; }\n\n    poly inv() const {\n        int n = size();\n        poly r(1);\n\
    \        r[0] = v[0].inv();\n        int k = 1;\n        while (k < n) {\n   \
    \         k <<= 1;\n            poly f(k);\n            for (int i = 0; i < min(k,\
    \ n); ++i) f[i] = v[i];\n            poly nr = (r * r * f).cut(k);\n         \
    \   for (int i = 0; i < k / 2; ++i) {\n                nr[i] = r[i] + r[i] - nr[i];\n\
    \                nr[i + k / 2] = -nr[i + k / 2];\n            }\n            r\
    \ = nr;\n        }\n        r.v.resize(n);\n        return r;\n    }\n};\n\n/**\n\
    \ * @brief \u4EFB\u610FMOD\u7573\u307F\u8FBC\u307F(3 NTT + Garner)\n */\n"
  dependsOn:
  - util/modint.cpp
  isVerificationFile: false
  path: math/fft.cpp
  requiredBy: []
  timestamp: '2026-03-14 20:56:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_convolution_mod_1000000007_fft.test.cpp
date: 2026-03-10
documentation_of: math/fft.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u4EFB\u610FMOD\u7573\u307F\u8FBC\u307F(3 NTT + Garner)"
---

## 説明
3 つの NTT 友好素数で畳み込み、Garner で任意 MOD に復元する。
複素 FFT を使わないので誤差がなく、計算量は $O(N log N)$。

## できること
- `poly operator*(const poly& a, const poly& b)`
  多項式の積を返す
- `poly inv() const`
  定数項が 0 でない多項式の逆数を返す

## 使い方
`MOD` を先に定義してから読み込む。
`poly` に係数を入れて `a * b` を呼べばよい。

## 実装上の補足
3 素数は `167772161`, `469762049`, `1224736769` を使う。
Library Checker の `convolution_mod_1000000007` は verify 済み。
