---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: fps/nth_term.cpp
    title: "\u6709\u7406\u578B\u6BCD\u95A2\u6570\u306En\u9805(N-th Term)"
  - icon: ':question:'
    path: math/ntt.cpp
    title: "NTT\u30FB\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570(NTT/FPS)"
  - icon: ':question:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
    links:
    - https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
  bundledCode: "#line 1 \"test/yosupo_kth_term_of_linearly_recurrent_sequence_nth_term.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence\"\
    \n\n#include <algorithm>\n#include <vector>\nusing namespace std;\n\nusing ll\
    \ = long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\n\n#line\
    \ 1 \"util/fastio.cpp\"\n#include <cstdio>\n#include <cstring>\n#include <string>\n\
    #include <type_traits>\nusing namespace std;\n\nstruct FastIoDigitTable {\n  \
    \  char num[40000];\n\n    constexpr FastIoDigitTable() : num() {\n        for\
    \ (int i = 0; i < 10000; ++i) {\n            int x = i;\n            for (int\
    \ j = 3; j >= 0; --j) {\n                num[i * 4 + j] = char('0' + x % 10);\n\
    \                x /= 10;\n            }\n        }\n    }\n};\n\nstruct Scanner\
    \ {\n    static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET\
    \ = 64;\n    char buf[BUFSIZE + 1];\n    int idx, size;\n\n    Scanner() : idx(0),\
    \ size(0) {}\n\n    inline void load() {\n        int len = size - idx;\n    \
    \    memmove(buf, buf + idx, len);\n        size = len + (int)fread(buf + len,\
    \ 1, BUFSIZE - len, stdin);\n        idx = 0;\n        buf[size] = 0;\n    }\n\
    \n    inline void ensure() {\n        if (idx + OFFSET > size) load();\n    }\n\
    \n    inline char skip() {\n        ensure();\n        while (buf[idx] && buf[idx]\
    \ <= ' ') {\n            ++idx;\n            ensure();\n        }\n        return\
    \ buf[idx++];\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value,\
    \ int>::type = 0>\n    void read(T &x) {\n        char c = skip();\n        bool\
    \ neg = false;\n        if constexpr (is_signed<T>::value) {\n            if (c\
    \ == '-') {\n                neg = true;\n                c = buf[idx++];\n  \
    \          }\n        }\n        x = 0;\n        while (c >= '0') {\n        \
    \    x = x * 10 + (c & 15);\n            c = buf[idx++];\n        }\n        if\
    \ constexpr (is_signed<T>::value) {\n            if (neg) x = -x;\n        }\n\
    \    }\n\n    template<class Head, class... Tail>\n    void read(Head &head, Tail\
    \ &...tail) {\n        read(head);\n        (read(tail), ...);\n    }\n\n    void\
    \ read(char &c) {\n        c = skip();\n    }\n\n    void read(string &s) {\n\
    \        s.clear();\n        ensure();\n        while (buf[idx] && buf[idx] <=\
    \ ' ') {\n            ++idx;\n            ensure();\n        }\n        while\
    \ (true) {\n            int start = idx;\n            while (idx < size && buf[idx]\
    \ > ' ') ++idx;\n            s.append(buf + start, idx - start);\n           \
    \ if (idx < size) break;\n            load();\n        }\n        if (idx < size)\
    \ ++idx;\n    }\n};\n\nstruct Printer {\n    static constexpr int BUFSIZE = 1\
    \ << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE];\n    int\
    \ idx;\n    inline static constexpr FastIoDigitTable table{};\n\n    Printer()\
    \ : idx(0) {}\n    ~Printer() { flush(); }\n\n    inline void flush() {\n    \
    \    if (idx) {\n            fwrite(buf, 1, idx, stdout);\n            idx = 0;\n\
    \        }\n    }\n\n    inline void pc(char c) {\n        if (idx > BUFSIZE -\
    \ OFFSET) flush();\n        buf[idx++] = c;\n    }\n\n    inline void write_range(const\
    \ char *s, size_t n) {\n        size_t pos = 0;\n        while (pos < n) {\n \
    \           if (idx == BUFSIZE) flush();\n            size_t chunk = min(n - pos,\
    \ (size_t)(BUFSIZE - idx));\n            memcpy(buf + idx, s + pos, chunk);\n\
    \            idx += (int)chunk;\n            pos += chunk;\n        }\n    }\n\
    \n    void write(const char *s) {\n        write_range(s, strlen(s));\n    }\n\
    \n    void write(const string &s) {\n        write_range(s.data(), s.size());\n\
    \    }\n\n    void write(char c) {\n        pc(c);\n    }\n\n    void write(bool\
    \ b) {\n        pc(char('0' + (b ? 1 : 0)));\n    }\n\n    template<class T, typename\
    \ enable_if<is_integral<T>::value && !is_same<T, bool>::value, int>::type = 0>\n\
    \    void write(T x) {\n        if (idx > BUFSIZE - 100) flush();\n        using\
    \ U = typename make_unsigned<T>::type;\n        U y;\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (x < 0) {\n                buf[idx++] = '-';\n           \
    \     y = U(0) - static_cast<U>(x);\n            } else {\n                y =\
    \ static_cast<U>(x);\n            }\n        } else {\n            y = x;\n  \
    \      }\n        if (y == 0) {\n            buf[idx++] = '0';\n            return;\n\
    \        }\n        static constexpr int TMP_SIZE = sizeof(U) * 10 / 4;\n    \
    \    char tmp[TMP_SIZE];\n        int pos = TMP_SIZE;\n        while (y >= 10000)\
    \ {\n            pos -= 4;\n            memcpy(tmp + pos, table.num + (y % 10000)\
    \ * 4, 4);\n            y /= 10000;\n        }\n        if (y >= 1000) {\n   \
    \         memcpy(buf + idx, table.num + (y << 2), 4);\n            idx += 4;\n\
    \        } else if (y >= 100) {\n            memcpy(buf + idx, table.num + (y\
    \ << 2) + 1, 3);\n            idx += 3;\n        } else if (y >= 10) {\n     \
    \       unsigned q = (unsigned(y) * 205) >> 11;\n            buf[idx] = char('0'\
    \ + q);\n            buf[idx + 1] = char('0' + (unsigned(y) - q * 10));\n    \
    \        idx += 2;\n        } else {\n            buf[idx++] = char('0' + y);\n\
    \        }\n        memcpy(buf + idx, tmp + pos, TMP_SIZE - pos);\n        idx\
    \ += TMP_SIZE - pos;\n    }\n\n    template<class T>\n    void writeln(const T\
    \ &x) {\n        write(x);\n        pc('\\n');\n    }\n\n    template<class Head,\
    \ class... Tail>\n    void writeln(const Head &head, const Tail &...tail) {\n\
    \        write(head);\n        ((pc(' '), write(tail)), ...);\n        pc('\\\
    n');\n    }\n\n    void writeln() {\n        pc('\\n');\n    }\n};\n\n/**\n *\
    \ @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n * @docs _md/fastio.md\n */\n\
    #line 2 \"math/ntt.cpp\"\n#include <cassert>\n\nconstexpr int ntt_mod = 998244353,\
    \ ntt_root = 3;\n#ifndef NTT_NAIVE_MUL_THRESHOLD\n#define NTT_NAIVE_MUL_THRESHOLD\
    \ 3072\n#endif\n#ifndef NTT_NAIVE_MUL_MIN_DIM\n#define NTT_NAIVE_MUL_MIN_DIM 48\n\
    #endif\n// 1012924417 -> 5, 924844033 -> 5\n// 998244353  -> 3, 897581057 -> 3\n\
    // 645922817  -> 3;\ntemplate <uint M>\nstruct modint {\n    uint val;\npublic:\n\
    \    static modint raw(int v) { modint x; x.val = v; return x; }\n    modint()\
    \ : val(0) {}\n    template <class T>\n    modint(T v) { ll x = (ll)(v%(ll)(M));\
    \ if (x < 0) x += M; val = uint(x); }\n    modint(bool v) { val = ((unsigned int)(v)\
    \ % M); }\n    modint& operator++() { val++; if (val == M) val = 0; return *this;\
    \ }\n    modint& operator--() { if (val == 0) val = M; val--; return *this; }\n\
    \    modint operator++(int) { modint result = *this; ++*this; return result; }\n\
    \    modint operator--(int) { modint result = *this; --*this; return result; }\n\
    \    modint& operator+=(const modint& rhs) { val += rhs.val; if (val >= M) val\
    \ -= M; return *this; }\n    modint& operator-=(const modint& rhs) { val -= rhs.val;\
    \ if (val >= M) val += M; return *this; }\n    modint& operator*=(const modint&\
    \ rhs) { ull z = val; z *= rhs.val; val = (uint)(z % M); return *this; }\n   \
    \ modint& operator/=(const modint& rhs) { return *this = *this * rhs.inv(); }\n\
    \    modint operator+() const { return *this; }\n    modint operator-() const\
    \ { return modint() - *this; }\n    modint pow(long long n) const { modint x =\
    \ *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n\
    \    modint inv() const { return pow(M-2); }\n    friend modint operator+(const\
    \ modint& lhs, const modint& rhs) { return modint(lhs) += rhs; }\n    friend modint\
    \ operator-(const modint& lhs, const modint& rhs) { return modint(lhs) -= rhs;\
    \ }\n    friend modint operator*(const modint& lhs, const modint& rhs) { return\
    \ modint(lhs) *= rhs; }\n    friend modint operator/(const modint& lhs, const\
    \ modint& rhs) { return modint(lhs) /= rhs; }\n    friend bool operator==(const\
    \ modint& lhs, const modint& rhs) { return lhs.val == rhs.val; }\n    friend bool\
    \ operator!=(const modint& lhs, const modint& rhs) { return lhs.val != rhs.val;\
    \ }\n};\nusing mint = modint<998244353>;\n\nclass NTT {\n    static constexpr\
    \ int max_base = 23, maxN = 1 << max_base; // 998244353 supports up to 2^23-th\
    \ roots\n    mint root[30], iroot[30], rate2[30], irate2[30], rate3[30], irate3[30];\n\
    public:\n    NTT() {\n        int cnt2 = __builtin_ctz(ntt_mod-1);\n        mint\
    \ e = mint(ntt_root).pow((ntt_mod-1) >> cnt2), ie = e.inv();\n        for (int\
    \ i = cnt2; i >= 0; i--){\n            root[i] = e;\n            iroot[i] = ie;\n\
    \            e *= e; ie *= ie;\n        }\n        mint prod = 1, iprod = 1;\n\
    \        for (int i = 0; i <= cnt2 - 2; i++) {\n            rate2[i] = root[i\
    \ + 2] * prod;\n            irate2[i] = iroot[i + 2] * iprod;\n            prod\
    \ *= iroot[i + 2];\n            iprod *= root[i + 2];\n        }\n        prod\
    \ = 1, iprod = 1;\n        for (int i = 0; i <= cnt2 - 3; i++) {\n           \
    \ rate3[i] = root[i + 3] * prod;\n            irate3[i] = iroot[i + 3] * iprod;\n\
    \            prod *= iroot[i + 3];\n            iprod *= root[i + 3];\n      \
    \  }\n    }\n\n    mint root_pow2(int k) const { return root[k]; }\n    mint iroot_pow2(int\
    \ k) const { return iroot[k]; }\n\n    void transform(vector<mint> &a, int sign){\n\
    \        const int n = a.size();\n        assert(n > 0);\n        assert((n &\
    \ (n - 1)) == 0);\n        assert(n <= maxN);\n        int h = 0;\n        while\
    \ ((1U << h) < (unsigned int)(n)) h++;\n        if(!sign){ // fft\n          \
    \  int len = 0;\n            while (len < h) {\n                if (h - len ==\
    \ 1) {\n                    int p = 1 << (h - len - 1);\n                    mint\
    \ rot = 1;\n                    for (int s = 0; s < (1 << len); s++) {\n     \
    \                   int offset = s << (h - len);\n                        for\
    \ (int i = 0; i < p; i++) {\n                            auto l = a[i + offset];\n\
    \                            auto r = a[i + offset + p] * rot;\n             \
    \               a[i + offset] = l + r;\n                            a[i + offset\
    \ + p] = l - r;\n                        }\n                        if (s + 1\
    \ != (1 << len)) {\n                            rot *= rate2[__builtin_ctz(~(unsigned\
    \ int)(s))];\n                        }\n                    }\n             \
    \       len++;\n                } else {\n                    int p = 1 << (h\
    \ - len - 2);\n                    mint rot = 1, imag = root[2];\n           \
    \         for (int s = 0; s < (1 << len); s++) {\n                        mint\
    \ rot2 = rot * rot;\n                        mint rot3 = rot2 * rot;\n       \
    \                 int offset = s << (h - len);\n                        for (int\
    \ i = 0; i < p; i++) {\n                            ull mod2 = 1ULL * ntt_mod\
    \ * ntt_mod;\n                            ull a0 = a[i + offset].val;\n      \
    \                      ull a1 = 1ULL * a[i + offset + p].val * rot.val;\n    \
    \                        ull a2 = 1ULL * a[i + offset + 2 * p].val * rot2.val;\n\
    \                            ull a3 = 1ULL * a[i + offset + 3 * p].val * rot3.val;\n\
    \                            ull a1na3imag = 1ULL * mint(a1 + mod2 - a3).val *\
    \ imag.val;\n                            ull na2 = mod2 - a2;\n              \
    \              a[i + offset] = mint(a0 + a2 + a1 + a3);\n                    \
    \        a[i + offset + p] = mint(a0 + a2 + (2 * mod2 - (a1 + a3)));\n       \
    \                     a[i + offset + 2 * p] = mint(a0 + na2 + a1na3imag);\n  \
    \                          a[i + offset + 3 * p] = mint(a0 + na2 + (mod2 - a1na3imag));\n\
    \                        }\n                        if (s + 1 != (1 << len)) {\n\
    \                            rot *= rate3[__builtin_ctz(~(unsigned int)(s))];\n\
    \                        }\n                    }\n                    len +=\
    \ 2;\n                }\n            }\n        }else { // ifft\n            int\
    \ len = h;\n            while (len) {\n                if (len == 1) {\n     \
    \               int p = 1 << (h - len);\n                    mint irot = 1;\n\
    \                    for (int s = 0; s < (1 << (len - 1)); s++) {\n          \
    \              int offset = s << (h - len + 1);\n                        for (int\
    \ i = 0; i < p; i++) {\n                            auto l = a[i + offset];\n\
    \                            auto r = a[i + offset + p];\n                   \
    \         a[i + offset] = l + r;\n                            a[i + offset + p]\
    \ = mint(1ULL * (ntt_mod + l.val - r.val) * irot.val);\n                     \
    \   }\n                        if (s + 1 != (1 << (len - 1))) {\n            \
    \                irot *= irate2[__builtin_ctz(~(unsigned int)(s))];\n        \
    \                }\n                    }\n                    len--;\n      \
    \          } else {\n                    int p = 1 << (h - len);\n           \
    \         mint irot = 1, iimag = iroot[2];\n                    for (int s = 0;\
    \ s < (1 << (len - 2)); s++) {\n                        mint irot2 = irot * irot;\n\
    \                        mint irot3 = irot2 * irot;\n                        int\
    \ offset = s << (h - len + 2);\n                        for (int i = 0; i < p;\
    \ i++) {\n                            ull a0 = a[i + offset].val;\n          \
    \                  ull a1 = a[i + offset + p].val;\n                         \
    \   ull a2 = a[i + offset + 2 * p].val;\n                            ull a3 =\
    \ a[i + offset + 3 * p].val;\n                            ull a2na3iimag = 1ULL\
    \ * mint(1ULL * (ntt_mod + a2 - a3) * iimag.val).val;\n                      \
    \      a[i + offset] = mint(a0 + a1 + a2 + a3);\n                            a[i\
    \ + offset + p] = mint(a0 + (ntt_mod - a1) + a2na3iimag) * irot;\n           \
    \                 a[i + offset + 2 * p] = mint(a0 + a1 + (ntt_mod - a2) + (ntt_mod\
    \ - a3)) * irot2;\n                            a[i + offset + 3 * p] = mint(a0\
    \ + (ntt_mod - a1) + (ntt_mod - a2na3iimag)) * irot3;\n                      \
    \  }\n                        if (s + 1 != (1 << (len - 2))) {\n             \
    \               irot *= irate3[__builtin_ctz(~(unsigned int)(s))];\n         \
    \               }\n                    }\n                    len -= 2;\n    \
    \            }\n            }\n        }\n    }\n};\n\nNTT ntt;\n\nvoid ntt_ifft(vector<mint>&\
    \ a) {\n    ntt.transform(a, 1);\n    static vector<mint> inv_pow2 = []() {\n\
    \        vector<mint> t(31, mint(1));\n        mint inv2 = mint(2).inv();\n  \
    \      for (int i = 1; i < (int)t.size(); ++i) t[i] = t[i - 1] * inv2;\n     \
    \   return t;\n    }();\n    mint iz = inv_pow2[__builtin_ctz((unsigned)a.size())];\n\
    \    for (auto& x : a) x *= iz;\n}\n\nmint ntt_inv_size(int n) {\n    static vector<mint>\
    \ inv_pow2 = []() {\n        vector<mint> t(31, mint(1));\n        mint inv2 =\
    \ mint(2).inv();\n        for (int i = 1; i < (int)t.size(); ++i) t[i] = t[i -\
    \ 1] * inv2;\n        return t;\n    }();\n    return inv_pow2[__builtin_ctz((unsigned)n)];\n\
    }\n\nbool mod_sqrt(mint a, mint &x) {\n    if (a == mint(0)) {\n        x = mint(0);\n\
    \        return true;\n    }\n    if (a.pow((ntt_mod - 1) >> 1) != mint(1)) return\
    \ false;\n    if (ntt_mod % 4 == 3) {\n        x = a.pow((ntt_mod + 1) >> 2);\n\
    \        return true;\n    }\n    int s = 0;\n    int q = ntt_mod - 1;\n    while\
    \ ((q & 1) == 0) {\n        ++s;\n        q >>= 1;\n    }\n    mint z = 2;\n \
    \   while (z.pow((ntt_mod - 1) >> 1) == mint(1)) ++z;\n    mint c = z.pow(q);\n\
    \    mint t = a.pow(q);\n    mint r = a.pow((q + 1) >> 1);\n    int m = s;\n \
    \   while (t != mint(1)) {\n        int i = 1;\n        mint tt = t * t;\n   \
    \     while (i < m && tt != mint(1)) {\n            tt *= tt;\n            ++i;\n\
    \        }\n        mint b = c.pow(1LL << (m - i - 1));\n        r *= b;\n   \
    \     c = b * b;\n        t *= c;\n        m = i;\n    }\n    x = r;\n    return\
    \ true;\n}\n\nstruct poly {\n    vector<mint> v;\n    poly() = default;\n    explicit\
    \ poly(int n) : v(n) {};\n    explicit poly(vector<mint> vv) : v(std::move(vv))\
    \ {};\n    int size() const {return (int)v.size(); }\n    void shrink() {\n  \
    \      while (!v.empty() && v.back() == mint(0)) v.pop_back();\n    }\n    poly\
    \ cut(int len){\n        if (len < (int)v.size()) v.resize(static_cast<unsigned\
    \ long>(len));\n        return *this;\n    }\n    inline mint& operator[] (int\
    \ i) {return v[i]; }\n    inline const mint& operator[] (int i) const {return\
    \ v[i]; }\n    poly& operator+=(const poly &a) {\n        this->v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) this->v[i] += a.v[i];\n\
    \        return *this;\n    }\n    poly &operator+=(const mint &r) {\n       \
    \ if (v.empty()) v.resize(1);\n        v[0] += r;\n        return *this;\n   \
    \ }\n    poly& operator-=(const poly &a) {\n        this->v.resize(max(size(),\
    \ a.size()));\n        for (int i = 0; i < a.size(); ++i) this->v[i] -= a.v[i];\n\
    \        return *this;\n    }\n    poly& operator*=(const poly &a) {\n       \
    \ const int n = size();\n        const int m = a.size();\n        if (n == 0 ||\
    \ m == 0) {\n            v.clear();\n            return *this;\n        }\n  \
    \      if (1LL * n * m <= NTT_NAIVE_MUL_THRESHOLD && min(n, m) <= NTT_NAIVE_MUL_MIN_DIM)\
    \ {\n            vector<mint> res(n + m - 1);\n            for (int i = 0; i <\
    \ n; ++i) {\n                for (int j = 0; j < m; ++j) {\n                 \
    \   res[i + j] += v[i] * a.v[j];\n                }\n            }\n         \
    \   v = std::move(res);\n            return *this;\n        }\n        int N =\
    \ n + m - 1;\n        int sz = 1;\n        while(sz < N) sz <<= 1;\n        this->v.resize(sz);\n\
    \        ntt.transform(this->v, 0);\n        if (this == &a) {\n            for\
    \ (int i = 0; i < sz; ++i) this->v[i] *= this->v[i];\n        } else {\n     \
    \       static thread_local vector<mint> b;\n            b.assign(a.v.begin(),\
    \ a.v.end());\n            b.resize(sz);\n            ntt.transform(b, 0);\n \
    \           for(int i = 0; i < sz; ++i) this->v[i] *= b[i];\n        }\n     \
    \   ntt.transform(this->v, 1);\n        this->v.resize(N);\n        mint iz =\
    \ ntt_inv_size(sz);\n        for (int i = 0; i < N; i++) this->v[i] *= iz;\n \
    \       return *this;\n    }\n    poly& operator/=(const poly &a){ return (*this\
    \ *= a.inv()); }\n    poly operator+(const poly &a) const { return poly(*this)\
    \ += a; }\n    poly operator+(const mint &v) const { return poly(*this) += v;\
    \ }\n    poly operator-(const poly &a) const { return poly(*this) -= a; }\n  \
    \  poly operator*(const poly &a) const { return poly(*this) *= a; }\n    poly\
    \ rev(int deg = -1) const {\n        poly ret(*this);\n        if (deg != -1)\
    \ ret.v.resize(deg);\n        reverse(ret.v.begin(), ret.v.end());\n        return\
    \ ret;\n    }\n\n    pair<poly, poly> divmod(const poly &a) const {\n        poly\
    \ f(*this), g(a);\n        f.shrink();\n        g.shrink();\n        assert(!g.v.empty());\n\
    \        if (f.size() < g.size()) return {poly(), f};\n        int need = f.size()\
    \ - g.size() + 1;\n        poly q = (f.rev().pre(need) * g.rev().inv(need)).pre(need).rev();\n\
    \        poly r = f - g * q;\n        r = r.pre(g.size() - 1);\n        r.shrink();\n\
    \        return {q, r};\n    }\n\n    poly mod(const poly &a) const {\n      \
    \  return divmod(a).second;\n    }\n\n    mint eval(mint x) const {\n        mint\
    \ y = 0;\n        for (int i = size() - 1; i >= 0; --i) y = y * x + v[i];\n  \
    \      return y;\n    }\n\n    poly pre(int sz) const {\n        poly ret(sz);\n\
    \        for (int i = 0; i < min<int>(sz, v.size()); ++i) {\n            ret[i]\
    \ = v[i];\n        }\n        return ret;\n    }\n\n    poly diff() const {\n\
    \        const int n = (int)this->size();\n        poly ret(max(0, n - 1));\n\
    \        mint one(1), coeff(1);\n        for (int i = 1; i < n; i++) {\n     \
    \       ret[i - 1] = v[i] * coeff;\n            coeff += one;\n        }\n   \
    \     return ret;\n    }\n\n    poly integral() const {\n        const int n =\
    \ (int)this->size();\n        poly ret(n + 1);\n        ret[0] = mint(0);\n  \
    \      static vector<mint> invs = {mint(0), mint(1)};\n        if ((int)invs.size()\
    \ <= n) {\n            int old = (int)invs.size();\n            invs.resize(n\
    \ + 1);\n            for (int i = old; i <= n; ++i) invs[i] = mint(ntt_mod - ntt_mod\
    \ / i) * invs[ntt_mod % i];\n        }\n        for (int i = 0; i < n; i++) ret[i\
    \ + 1] = v[i] * invs[i + 1];\n        return ret;\n    }\n\n    poly inv(int deg\
    \ = -1) const {\n        assert(!v.empty() && v[0] != mint(0));\n        if (deg\
    \ == -1) deg = size();\n        poly res(deg);\n        res[0] = v[0].inv();\n\
    \        for (int d = 1; d < deg; d <<= 1) {\n            vector<mint> f(2 * d),\
    \ g(2 * d);\n            for (int i = 0; i < min(size(), 2 * d); ++i) f[i] = v[i];\n\
    \            for (int i = 0; i < d; ++i) g[i] = res[i];\n            ntt.transform(f,\
    \ 0);\n            ntt.transform(g, 0);\n            for (int i = 0; i < 2 * d;\
    \ ++i) f[i] *= g[i];\n            ntt_ifft(f);\n            fill(f.begin(), f.begin()\
    \ + d, mint(0));\n            ntt.transform(f, 0);\n            for (int i = 0;\
    \ i < 2 * d; ++i) f[i] *= g[i];\n            ntt_ifft(f);\n            for (int\
    \ i = d; i < min(2 * d, deg); ++i) res[i] = -f[i];\n        }\n        return\
    \ res.pre(deg);\n    }\n\n    poly log(int deg = -1) const {\n        assert(!v.empty()\
    \ && v[0] == mint(1));\n        if (deg == -1) deg = (int)this->size();\n    \
    \    return (this->diff() * this->inv(deg)).pre(deg - 1).integral();\n    }\n\n\
    \    poly exp(int deg = -1) const {\n        assert(v.size() == 0 || v[0] == mint(0));\n\
    \        if (deg == -1) deg = v.size();\n        static vector<mint> invs = {mint(0),\
    \ mint(1)};\n        auto ensure_invs = [&](int n) {\n            if ((int)invs.size()\
    \ <= n) {\n                int old = (int)invs.size();\n                invs.resize(n\
    \ + 1);\n                for (int i = old; i <= n; ++i) invs[i] = mint(ntt_mod\
    \ - ntt_mod / i) * invs[ntt_mod % i];\n            }\n        };\n        auto\
    \ inplace_integral = [&](poly& f) {\n            int n = f.size();\n         \
    \   ensure_invs(n);\n            f.v.insert(f.v.begin(), mint(0));\n         \
    \   for (int i = 1; i <= n; ++i) f[i] *= invs[i];\n        };\n        poly b(vector<mint>{mint(1),\
    \ (1 < size() ? v[1] : mint(0))});\n        poly c(vector<mint>{mint(1)}), z1,\
    \ z2(vector<mint>{mint(1), mint(1)});\n        for (int m = 2; m < deg; m <<=\
    \ 1) {\n            poly y = b;\n            y.v.resize(2 * m);\n            ntt.transform(y.v,\
    \ 0);\n            z1 = z2;\n            poly z(m);\n            for (int i =\
    \ 0; i < m; ++i) z[i] = y[i] * z1[i];\n            ntt_ifft(z.v);\n          \
    \  fill(z.v.begin(), z.v.begin() + m / 2, mint(0));\n            ntt.transform(z.v,\
    \ 0);\n            for (int i = 0; i < m; ++i) z[i] *= -z1[i];\n            ntt_ifft(z.v);\n\
    \            c.v.insert(c.v.end(), z.v.begin() + m / 2, z.v.end());\n        \
    \    z2 = c;\n            z2.v.resize(2 * m);\n            ntt.transform(z2.v,\
    \ 0);\n\n            poly x(m);\n            for (int i = 0; i + 1 < m && i +\
    \ 1 < size(); ++i) x[i] = v[i + 1] * mint(i + 1);\n            x[m - 1] = mint(0);\n\
    \            ntt.transform(x.v, 0);\n            for (int i = 0; i < m; ++i) x[i]\
    \ *= y[i];\n            ntt_ifft(x.v);\n            for (int i = 0; i + 1 < m;\
    \ ++i) x[i] -= b[i + 1] * mint(i + 1);\n            x.v.resize(2 * m);\n     \
    \       for (int i = 0; i + 1 < m; ++i) {\n                x[m + i] = x[i];\n\
    \                x[i] = mint(0);\n            }\n            ntt.transform(x.v,\
    \ 0);\n            for (int i = 0; i < 2 * m; ++i) x[i] *= z2[i];\n          \
    \  ntt_ifft(x.v);\n            x.v.pop_back();\n            inplace_integral(x);\n\
    \            for (int i = m; i < min(size(), 2 * m); ++i) x[i] += v[i];\n    \
    \        fill(x.v.begin(), x.v.begin() + m, mint(0));\n            ntt.transform(x.v,\
    \ 0);\n            for (int i = 0; i < 2 * m; ++i) x[i] *= y[i];\n           \
    \ ntt_ifft(x.v);\n            b.v.insert(b.v.end(), x.v.begin() + m, x.v.end());\n\
    \        }\n        return b.pre(deg);\n    }\n\n    poly pow(long long k, int\
    \ deg = -1) const {\n        if (deg == -1) deg = size();\n        poly ret(max(0,\
    \ deg));\n        if (deg <= 0) return ret;\n        if (k == 0) {\n         \
    \   ret[0] = 1;\n            return ret;\n        }\n        if (0 < k && k <=\
    \ 64) {\n            poly base = pre(deg);\n            poly ans(1);\n       \
    \     ans[0] = 1;\n            long long e = k;\n            while (e > 0) {\n\
    \                if (e & 1) {\n                    ans *= base;\n            \
    \        ans = ans.pre(deg);\n                }\n                e >>= 1;\n  \
    \              if (e == 0) break;\n                base *= base;\n           \
    \     base = base.pre(deg);\n            }\n            ans = ans.pre(deg);\n\
    \            if (ans.size() < deg) ans.v.resize(deg);\n            return ans;\n\
    \        }\n        int lead = 0;\n        while (lead < size() && v[lead] ==\
    \ mint(0)) lead++;\n        if (lead == size()) return ret;\n        long long\
    \ shift_ll = 0;\n        if (lead > 0) {\n            if (k > (deg - 1) / lead)\
    \ return ret;\n            shift_ll = 1LL * lead * k;\n        }\n        poly\
    \ f(size() - lead);\n        mint inv_lead = v[lead].inv();\n        for (int\
    \ i = lead; i < size(); ++i) f[i - lead] = v[i] * inv_lead;\n        int shift\
    \ = static_cast<int>(shift_ll);\n        int rem_deg = deg - shift;\n        poly\
    \ g = f.log(rem_deg);\n        mint k_mint = mint(k);\n        for (int i = 0;\
    \ i < g.size(); ++i) g[i] *= k_mint;\n        g = g.exp(rem_deg);\n        mint\
    \ coeff = v[lead].pow(k);\n        for (int i = 0; i < g.size(); ++i) g[i] *=\
    \ coeff;\n        for (int i = 0; i < g.size(); ++i) ret[i + shift] = g[i];\n\
    \        return ret;\n    }\n\n    poly sqrt(int deg = -1) const {\n        if\
    \ (deg == -1) deg = size();\n        poly ret(max(0, deg));\n        if (deg <=\
    \ 0) return ret;\n        int lead = 0;\n        while (lead < size() && v[lead]\
    \ == mint(0)) lead++;\n        if (lead == size()) return ret;\n        if (lead\
    \ & 1) return poly();\n        mint sq0;\n        if (!mod_sqrt(v[lead], sq0))\
    \ return poly();\n        int shift = lead >> 1;\n        if (shift >= deg) return\
    \ ret;\n        int rem_deg = deg - shift;\n        poly f(size() - lead);\n \
    \       mint inv_lead = v[lead].inv();\n        for (int i = lead; i < size();\
    \ ++i) f[i - lead] = v[i] * inv_lead;\n        poly s(1);\n        s[0] = 1;\n\
    \        mint inv2 = mint(2).inv();\n        for (int k = 1; k < rem_deg; k <<=\
    \ 1) {\n            poly ns = (s + (f.pre(k << 1) * s.inv(k << 1)).pre(k << 1)).pre(k\
    \ << 1);\n            for (int i = 0; i < ns.size(); ++i) ns[i] *= inv2;\n   \
    \         s = ns;\n        }\n        s = s.pre(rem_deg);\n        for (int i\
    \ = 0; i < s.size(); ++i) ret[i + shift] = s[i] * sq0;\n        return ret;\n\
    \    }\n\n    vector<mint> multipoint_eval(const vector<mint> &xs) const;\n};\n\
    \n/**\n * @brief NTT\u30FB\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570(NTT/FPS)\n * @docs\
    \ _md/ntt.md\n */\n#line 2 \"fps/nth_term.cpp\"\nmint nth_term(poly p, poly q,\
    \ ll n){\n    if(!n) return p[0]/q[0];\n    int sz = 1, h = 0;\n    int k = max(p.size(),\
    \ q.size());\n    while(sz < 2*k-1) sz <<= 1, h++;\n    p.v.resize(sz); q.v.resize(sz);\n\
    \    mint x = mint(sz>>1).inv();\n    vector<mint> y(sz>>1, 0);\n    for (int\
    \ j = sz>>2, i = h; j; j >>= 1, i--) y[j] = ntt.iroot_pow2(i);\n    y[0] = 1;\n\
    \    for (int i = 2; i < sz>>1; i <<= 1) {\n        for (int j = i+1; j < 2*i;\
    \ ++j) {\n            y[j] = y[j-i]*y[i];\n        }\n    }\n    ntt.transform(p.v,\
    \ 0);\n    ntt.transform(q.v, 0);\n    poly tmp(sz>>1);\n    auto up = [&](poly\
    \ &A){\n        for (int i = 0; i < sz>>1; ++i) tmp[i] = A[i];\n        ntt.transform(tmp.v,\
    \ 1);\n        mint now = x;\n        for (int i = 0; i < sz>>1; ++i) tmp[i] *=\
    \ now, now *= ntt.root_pow2(h);\n        ntt.transform(tmp.v, 0);\n        for\
    \ (int i = 0; i < sz>>1; ++i) A[i|(sz>>1)] = tmp[i];\n    };\n    int ika = h;\n\
    \    while(n){\n        for (int i = 0; i < sz; ++i) p[i] *= q[i^1];\n       \
    \ if(n&1) for (int i = 0; i < sz>>1; ++i) p[i] = (p[i<<1]-p[(i<<1)|1])*y[i];\n\
    \        else for (int i = 0; i < sz>>1; ++i) p[i] = (p[i<<1]+p[(i<<1)|1]);\n\
    \        ika++;\n        if(n == 1) break;\n        up(p);\n        for (int i\
    \ = 0; i < sz>>1; ++i) q[i] = q[i<<1]*q[(i<<1)|1];\n        up(q);\n        n\
    \ >>= 1;\n    }\n    for (int i = 0; i < sz>>1; ++i) tmp[i] = p[i];\n    ntt.transform(tmp.v,\
    \ 1);\n    return mint(2).pow(ntt_mod-ika)*tmp[0];\n}\n\n/**\n * @brief \u6709\
    \u7406\u578B\u6BCD\u95A2\u6570\u306En\u9805(N-th Term)\n * @docs _md/nth_term.md\n\
    \ */\n#line 13 \"test/yosupo_kth_term_of_linearly_recurrent_sequence_nth_term.test.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int d;\n    ll n;\n\
    \    sc.read(d, n);\n    vector<mint> a(d), c(d);\n    for (int i = 0; i < d;\
    \ ++i) {\n        int x;\n        sc.read(x);\n        a[i] = x;\n    }\n    for\
    \ (int i = 0; i < d; ++i) {\n        int x;\n        sc.read(x);\n        c[i]\
    \ = x;\n    }\n\n    poly q(d + 1);\n    q[0] = 1;\n    for (int i = 0; i < d;\
    \ ++i) q[i + 1] = -c[i];\n    poly p = (poly(a) * q).cut(d);\n    pr.writeln(nth_term(p,\
    \ q, n).val);\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence\"\
    \n\n#include <algorithm>\n#include <vector>\nusing namespace std;\n\nusing ll\
    \ = long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\n\n#include\
    \ \"../util/fastio.cpp\"\n#include \"../fps/nth_term.cpp\"\n\nint main() {\n \
    \   Scanner sc;\n    Printer pr;\n\n    int d;\n    ll n;\n    sc.read(d, n);\n\
    \    vector<mint> a(d), c(d);\n    for (int i = 0; i < d; ++i) {\n        int\
    \ x;\n        sc.read(x);\n        a[i] = x;\n    }\n    for (int i = 0; i < d;\
    \ ++i) {\n        int x;\n        sc.read(x);\n        c[i] = x;\n    }\n\n  \
    \  poly q(d + 1);\n    q[0] = 1;\n    for (int i = 0; i < d; ++i) q[i + 1] = -c[i];\n\
    \    poly p = (poly(a) * q).cut(d);\n    pr.writeln(nth_term(p, q, n).val);\n\
    \    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - fps/nth_term.cpp
  - math/ntt.cpp
  isVerificationFile: true
  path: test/yosupo_kth_term_of_linearly_recurrent_sequence_nth_term.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 21:12:29+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yosupo_kth_term_of_linearly_recurrent_sequence_nth_term.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_kth_term_of_linearly_recurrent_sequence_nth_term.test.cpp
- /verify/test/yosupo_kth_term_of_linearly_recurrent_sequence_nth_term.test.cpp.html
title: test/yosupo_kth_term_of_linearly_recurrent_sequence_nth_term.test.cpp
---
