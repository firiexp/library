---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fft.cpp
    title: "\u4EFB\u610FMOD\u7573\u307F\u8FBC\u307F(3 NTT + Garner)"
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: Fast IO
  - icon: ':heavy_check_mark:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod_1000000007
    links:
    - https://judge.yosupo.jp/problem/convolution_mod_1000000007
  bundledCode: "#line 1 \"test/yosupo_convolution_mod_1000000007_fft.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod_1000000007\"\
    \n\n#include <bits/stdc++.h>\n\nstatic const int MOD = 1000000007;\nusing ll =\
    \ long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\nusing namespace\
    \ std;\n\n#line 4 \"util/fastio.cpp\"\n#include <type_traits>\nusing namespace\
    \ std;\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr FastIoDigitTable()\
    \ : num() {\n        for (int i = 0; i < 10000; ++i) {\n            int x = i;\n\
    \            for (int j = 3; j >= 0; --j) {\n                num[i * 4 + j] =\
    \ char('0' + x % 10);\n                x /= 10;\n            }\n        }\n  \
    \  }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE = 1 << 17;\n  \
    \  static constexpr int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n    int idx,\
    \ size;\n\n    Scanner() : idx(0), size(0) {}\n\n    inline void load() {\n  \
    \      int len = size - idx;\n        memmove(buf, buf + idx, len);\n        size\
    \ = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n        idx = 0;\n\
    \        buf[size] = 0;\n    }\n\n    inline void ensure() {\n        if (idx\
    \ + OFFSET > size) load();\n    }\n\n    inline char skip() {\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        return buf[idx++];\n    }\n\n    template<class\
    \ T, typename enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T\
    \ &x) {\n        char c = skip();\n        bool neg = false;\n        if constexpr\
    \ (is_signed<T>::value) {\n            if (c == '-') {\n                neg =\
    \ true;\n                c = buf[idx++];\n            }\n        }\n        x\
    \ = 0;\n        while (c >= '0') {\n            x = x * 10 + (c & 15);\n     \
    \       c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class Head,\
    \ class... Tail>\n    void read(Head &head, Tail &...tail) {\n        read(head);\n\
    \        (read(tail), ...);\n    }\n\n    void read(char &c) {\n        c = skip();\n\
    \    }\n\n    void read(string &s) {\n        s.clear();\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (idx < size && buf[idx] > ' ') ++idx;\n            s.append(buf\
    \ + start, idx - start);\n            if (idx < size) break;\n            load();\n\
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    char buf[BUFSIZE];\n    int idx;\n    inline static constexpr FastIoDigitTable\
    \ table{};\n\n    Printer() : idx(0) {}\n    ~Printer() { flush(); }\n\n    inline\
    \ void flush() {\n        if (idx) {\n            fwrite(buf, 1, idx, stdout);\n\
    \            idx = 0;\n        }\n    }\n\n    inline void pc(char c) {\n    \
    \    if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++] = c;\n    }\n\n\
    \    inline void write_range(const char *s, size_t n) {\n        size_t pos =\
    \ 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n  \
    \          size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n           \
    \ memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n       \
    \     pos += chunk;\n        }\n    }\n\n    void write(const char *s) {\n   \
    \     write_range(s, strlen(s));\n    }\n\n    void write(const string &s) {\n\
    \        write_range(s.data(), s.size());\n    }\n\n    void write(char c) {\n\
    \        pc(c);\n    }\n\n    void write(bool b) {\n        pc(char('0' + (b ?\
    \ 1 : 0)));\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value\
    \ && !is_same<T, bool>::value, int>::type = 0>\n    void write(T x) {\n      \
    \  if (idx > BUFSIZE - 100) flush();\n        using U = typename make_unsigned<T>::type;\n\
    \        U y;\n        if constexpr (is_signed<T>::value) {\n            if (x\
    \ < 0) {\n                buf[idx++] = '-';\n                y = U(0) - static_cast<U>(x);\n\
    \            } else {\n                y = static_cast<U>(x);\n            }\n\
    \        } else {\n            y = x;\n        }\n        if (y == 0) {\n    \
    \        buf[idx++] = '0';\n            return;\n        }\n        static constexpr\
    \ int TMP_SIZE = sizeof(U) * 10 / 4;\n        char tmp[TMP_SIZE];\n        int\
    \ pos = TMP_SIZE;\n        while (y >= 10000) {\n            pos -= 4;\n     \
    \       memcpy(tmp + pos, table.num + (y % 10000) * 4, 4);\n            y /= 10000;\n\
    \        }\n        if (y >= 1000) {\n            memcpy(buf + idx, table.num\
    \ + (y << 2), 4);\n            idx += 4;\n        } else if (y >= 100) {\n   \
    \         memcpy(buf + idx, table.num + (y << 2) + 1, 3);\n            idx +=\
    \ 3;\n        } else if (y >= 10) {\n            unsigned q = (unsigned(y) * 205)\
    \ >> 11;\n            buf[idx] = char('0' + q);\n            buf[idx + 1] = char('0'\
    \ + (unsigned(y) - q * 10));\n            idx += 2;\n        } else {\n      \
    \      buf[idx++] = char('0' + y);\n        }\n        memcpy(buf + idx, tmp +\
    \ pos, TMP_SIZE - pos);\n        idx += TMP_SIZE - pos;\n    }\n\n    template<class\
    \ T>\n    void writeln(const T &x) {\n        write(x);\n        pc('\\n');\n\
    \    }\n\n    template<class Head, class... Tail>\n    void writeln(const Head\
    \ &head, const Tail &...tail) {\n        write(head);\n        ((pc(' '), write(tail)),\
    \ ...);\n        pc('\\n');\n    }\n\n    void writeln() {\n        pc('\\n');\n\
    \    }\n};\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line\
    \ 1 \"util/modint.cpp\"\n\n\n\ntemplate <uint M>\nstruct modint {\n    uint val;\n\
    public:\n    static modint raw(int v) { modint x; x.val = v; return x; }\n   \
    \ modint() : val(0) {}\n    template <class T>\n    modint(T v) { ll x = (ll)(v%(ll)(M));\
    \ if (x < 0) x += M; val = uint(x); }\n    modint(bool v) { val = ((unsigned int)(v)\
    \ % M); }\n    modint& operator++() { val++; if (val == M) val = 0; return *this;\
    \ }\n    modint& operator--() { if (val == 0) val = M; val--; return *this; }\n\
    \    modint operator++(int) { modint result = *this; ++*this; return result; }\n\
    \    modint operator--(int) { modint result = *this; --*this; return result; }\n\
    \    modint& operator+=(const modint& b) { val += b.val; if (val >= M) val -=\
    \ M; return *this; }\n    modint& operator-=(const modint& b) { val -= b.val;\
    \ if (val >= M) val += M; return *this; }\n    modint& operator*=(const modint&\
    \ b) { ull z = val; z *= b.val; val = (uint)(z % M); return *this; }\n    modint&\
    \ operator/=(const modint& b) { return *this = *this * b.inv(); }\n    modint\
    \ operator+() const { return *this; }\n    modint operator-() const { return modint()\
    \ - *this; }\n    modint pow(long long n) const { modint x = *this, r = 1; while\
    \ (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n    modint inv() const\
    \ { return pow(M-2); }\n    friend modint operator+(const modint& a, const modint&\
    \ b) { return modint(a) += b; }\n    friend modint operator-(const modint& a,\
    \ const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    \n/**\n * @brief modint(\u56FA\u5B9AMOD)\n */\n\n\n#line 2 \"math/fft.cpp\"\n\n\
    #line 5 \"math/fft.cpp\"\n\nnamespace ArbitraryConvolution {\n    template<uint\
    \ M>\n    struct StaticModInt {\n        uint val;\n        StaticModInt() : val(0)\
    \ {}\n        template<class T>\n        StaticModInt(T v) {\n            long\
    \ long x = (long long)(v % (long long)M);\n            if (x < 0) x += M;\n  \
    \          val = (uint)x;\n        }\n        static StaticModInt raw(uint v)\
    \ {\n            StaticModInt x;\n            x.val = v;\n            return x;\n\
    \        }\n        StaticModInt& operator+=(const StaticModInt& rhs) {\n    \
    \        val += rhs.val;\n            if (val >= M) val -= M;\n            return\
    \ *this;\n        }\n        StaticModInt& operator-=(const StaticModInt& rhs)\
    \ {\n            val -= rhs.val;\n            if (val >= M) val += M;\n      \
    \      return *this;\n        }\n        StaticModInt& operator*=(const StaticModInt&\
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
    \ * @brief \u4EFB\u610FMOD\u7573\u307F\u8FBC\u307F(3 NTT + Garner)\n */\n#line\
    \ 13 \"test/yosupo_convolution_mod_1000000007_fft.test.cpp\"\n\nint main() {\n\
    \    Scanner sc;\n    Printer pr;\n\n    int n, m;\n    sc.read(n, m);\n    poly\
    \ a(n), b(m);\n    for (int i = 0; i < n; ++i) {\n        int x;\n        sc.read(x);\n\
    \        a[i] = x;\n    }\n    for (int i = 0; i < m; ++i) {\n        int x;\n\
    \        sc.read(x);\n        b[i] = x;\n    }\n    a *= b;\n    for (int i =\
    \ 0; i < n + m - 1; ++i) {\n        if (i) pr.write(' ');\n        pr.write(a[i].val);\n\
    \    }\n    pr.writeln();\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod_1000000007\"\
    \n\n#include <bits/stdc++.h>\n\nstatic const int MOD = 1000000007;\nusing ll =\
    \ long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\nusing namespace\
    \ std;\n\n#include \"../util/fastio.cpp\"\n#include \"../math/fft.cpp\"\n\nint\
    \ main() {\n    Scanner sc;\n    Printer pr;\n\n    int n, m;\n    sc.read(n,\
    \ m);\n    poly a(n), b(m);\n    for (int i = 0; i < n; ++i) {\n        int x;\n\
    \        sc.read(x);\n        a[i] = x;\n    }\n    for (int i = 0; i < m; ++i)\
    \ {\n        int x;\n        sc.read(x);\n        b[i] = x;\n    }\n    a *= b;\n\
    \    for (int i = 0; i < n + m - 1; ++i) {\n        if (i) pr.write(' ');\n  \
    \      pr.write(a[i].val);\n    }\n    pr.writeln();\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - math/fft.cpp
  - util/modint.cpp
  isVerificationFile: true
  path: test/yosupo_convolution_mod_1000000007_fft.test.cpp
  requiredBy: []
  timestamp: '2026-03-11 00:57:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_convolution_mod_1000000007_fft.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_convolution_mod_1000000007_fft.test.cpp
- /verify/test/yosupo_convolution_mod_1000000007_fft.test.cpp.html
title: test/yosupo_convolution_mod_1000000007_fft.test.cpp
---
