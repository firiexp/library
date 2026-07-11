---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/binaryindexedtree.cpp
    title: Binary Indexed Tree(BIT)
  - icon: ':heavy_check_mark:'
    path: datastructure/point_add_rectangle_sum.cpp
    title: "\u70B9\u52A0\u7B97\u9577\u65B9\u5F62\u548C(Point Add Rectangle Sum)"
  - icon: ':heavy_check_mark:'
    path: datastructure/sparsetable.cpp
    title: Sparse Table
  - icon: ':heavy_check_mark:'
    path: datastructure/static_rectangle_sum.cpp
    title: "\u9759\u7684\u9577\u65B9\u5F62\u548C(Static Rectangle Sum)"
  - icon: ':heavy_check_mark:'
    path: geometry/dualgraph.cpp
    title: "\u53CC\u5BFE\u30B0\u30E9\u30D5(Dual Graph)"
  - icon: ':heavy_check_mark:'
    path: geometry/geometry.cpp
    title: "\u5E7E\u4F55\u30E9\u30A4\u30D6\u30E9\u30EA(Geometry)"
  - icon: ':heavy_check_mark:'
    path: geometry/half_plane_intersection.cpp
    title: "\u534A\u5E73\u9762\u5171\u901A\u90E8\u5206(Half-Plane Intersection)"
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.cpp
    title: "Dijkstra\u6CD5"
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra_common.cpp
    title: graph/dijkstra_common.cpp
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra_restore.cpp
    title: "\u7D4C\u8DEF\u5FA9\u5143\u4ED8\u304DDijkstra\u6CD5"
  - icon: ':heavy_check_mark:'
    path: math/ntt.cpp
    title: "NTT\u30FB\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570(NTT/FPS)"
  - icon: ':heavy_check_mark:'
    path: math/prime/get_min_factor.cpp
    title: "\u6700\u5C0F\u7D20\u56E0\u6570\u30C6\u30FC\u30D6\u30EB(Min Factor Table)"
  - icon: ':heavy_check_mark:'
    path: math/prime/get_prime.cpp
    title: "\u7D20\u6570\u5217\u6319"
  - icon: ':heavy_check_mark:'
    path: math/prime/linear_sieve.cpp
    title: "\u7DDA\u5F62\u7BE9(Linear Sieve)"
  - icon: ':heavy_check_mark:'
    path: tree/LCA.cpp
    title: "\u6700\u8FD1\u5171\u901A\u7956\u5148(LCA)"
  - icon: ':heavy_check_mark:'
    path: tree/auxtree.cpp
    title: "\u88DC\u52A9\u6728(Aux Tree)"
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  - icon: ':heavy_check_mark:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  - icon: ':heavy_check_mark:'
    path: util/modint_base.cpp
    title: util/modint_base.cpp
  - icon: ':heavy_check_mark:'
    path: util/modint_base.cpp
    title: util/modint_base.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"test/yosupo_aplusb_library_composition.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\nstatic const int MOD = 998244353;\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\nusing ll = long long;\n\
    using uint = unsigned;\nusing ull = unsigned long long;\n\n#line 1 \"util/fastio.cpp\"\
    \nusing namespace std;\n\nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\
    \ntemplate<class T, class = void>\nstruct is_fastio_range : false_type {};\n\n\
    template<class T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()),\
    \ decltype(declval<T &>().end())>> : true_type {};\n\ntemplate<class T, class\
    \ = void>\nstruct has_fastio_value : false_type {};\n\ntemplate<class T>\nstruct\
    \ has_fastio_value<T, void_t<decltype(declval<const T &>().value())>> : true_type\
    \ {};\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr FastIoDigitTable()\
    \ : num() {\n        for (int i = 0; i < 10000; ++i) {\n            int x = i;\n\
    \            for (int j = 3; j >= 0; --j) {\n                num[i * 4 + j] =\
    \ char('0' + x % 10);\n                x /= 10;\n            }\n        }\n  \
    \  }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE = 1 << 17;\n  \
    \  static constexpr int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n    int idx,\
    \ size;\n    bool interactive;\n\n    Scanner() : idx(0), size(0), interactive(isatty(fileno(stdin)))\
    \ {}\n\n    inline void load() {\n        int len = size - idx;\n        memmove(buf,\
    \ buf + idx, len);\n        if (interactive) {\n            if (fgets(buf + len,\
    \ BUFSIZE + 1 - len, stdin)) size = len + (int)strlen(buf + len);\n          \
    \  else size = len;\n        } else {\n            size = len + (int)fread(buf\
    \ + len, 1, BUFSIZE - len, stdin);\n        }\n        idx = 0;\n        buf[size]\
    \ = 0;\n    }\n\n    inline void ensure() {\n        if (idx + OFFSET > size)\
    \ load();\n    }\n\n    inline void ensure_interactive() {\n        if (idx ==\
    \ size) load();\n    }\n\n    inline char skip() {\n        if (interactive) {\n\
    \            ensure_interactive();\n            while (buf[idx] && buf[idx] <=\
    \ ' ') {\n                ++idx;\n                ensure_interactive();\n    \
    \        }\n            return buf[idx++];\n        }\n        ensure();\n   \
    \     while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n            ensure();\n\
    \        }\n        return buf[idx++];\n    }\n\n    template<class T, typename\
    \ enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T &x) {\n  \
    \      if (interactive) {\n            char c = skip();\n            bool neg\
    \ = false;\n            if constexpr (is_signed<T>::value) {\n               \
    \ if (c == '-') {\n                    neg = true;\n                    ensure_interactive();\n\
    \                    c = buf[idx++];\n                }\n            }\n     \
    \       x = 0;\n            while (c >= '0') {\n                x = x * 10 + (c\
    \ & 15);\n                ensure_interactive();\n                c = buf[idx++];\n\
    \            }\n            if constexpr (is_signed<T>::value) {\n           \
    \     if (neg) x = -x;\n            }\n            return;\n        }\n      \
    \  char c = skip();\n        bool neg = false;\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (c == '-') {\n                neg = true;\n              \
    \  c = buf[idx++];\n            }\n        }\n        x = 0;\n        while (c\
    \ >= '0') {\n            x = x * 10 + (c & 15);\n            c = buf[idx++];\n\
    \        }\n        if constexpr (is_signed<T>::value) {\n            if (neg)\
    \ x = -x;\n        }\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && has_fastio_value<T>::value, int>::type = 0>\n    void read(T &x) {\n    \
    \    long long v;\n        read(v);\n        x = T(v);\n    }\n\n    template<class\
    \ Head, class Next, class... Tail>\n    void read(Head &head, Next &next, Tail\
    \ &...tail) {\n        read(head);\n        read(next, tail...);\n    }\n\n  \
    \  template<class T, class U>\n    void read(pair<T, U> &p) {\n        read(p.first,\
    \ p.second);\n    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value\
    \ && !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
    \ read(T &a) {\n        for (auto &x : a) read(x);\n    }\n\n    void read(char\
    \ &c) {\n        c = skip();\n    }\n\n    void read(string &s) {\n        s.clear();\n\
    \        if (interactive) {\n            ensure_interactive();\n            while\
    \ (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n                ensure_interactive();\n\
    \            }\n            while (true) {\n                int start = idx;\n\
    \                while (idx < size && buf[idx] > ' ') ++idx;\n               \
    \ s.append(buf + start, idx - start);\n                if (idx < size) break;\n\
    \                load();\n                if (size == 0) break;\n            }\n\
    \            if (idx < size) ++idx;\n            return;\n        }\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (idx < size && buf[idx] > ' ') ++idx;\n            s.append(buf\
    \ + start, idx - start);\n            if (idx < size) break;\n            load();\n\
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    char buf[BUFSIZE];\n    int idx;\n    bool interactive;\n    inline\
    \ static constexpr FastIoDigitTable table{};\n\n    Printer() : idx(0), interactive(isatty(fileno(stdout)))\
    \ {}\n    ~Printer() { flush(); }\n\n    inline void flush() {\n        if (idx)\
    \ {\n            fwrite(buf, 1, idx, stdout);\n            idx = 0;\n        }\n\
    \    }\n\n    inline void pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n\
    \        buf[idx++] = c;\n        if (interactive && c == '\\n') flush();\n  \
    \  }\n\n    inline void print_range(const char *s, size_t n) {\n        size_t\
    \ pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n\
    \            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n         \
    \   memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n     \
    \       pos += chunk;\n        }\n    }\n\n    void print(const char *s) {\n \
    \       print_range(s, strlen(s));\n    }\n\n    void print(const string &s) {\n\
    \        print_range(s.data(), s.size());\n    }\n\n    void print(char c) {\n\
    \        pc(c);\n    }\n\n    void print(bool b) {\n        pc(char('0' + (b ?\
    \ 1 : 0)));\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value\
    \ && !is_same<T, bool>::value, int>::type = 0>\n    void print(T x) {\n      \
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
    \ T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value && has_fastio_value<T>::value,\
    \ int>::type = 0>\n    void print(const T &x) {\n        print(x.value());\n \
    \   }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
    \ print(const T &a) {\n        bool first = true;\n        for (auto &&x : a)\
    \ {\n            if (!first) pc(' ');\n            first = false;\n          \
    \  print(x);\n        }\n    }\n\n    template<class T>\n    void println(const\
    \ T &x) {\n        print(x);\n        pc('\\n');\n    }\n\n    template<class\
    \ Head, class... Tail>\n    void println(const Head &head, const Tail &...tail)\
    \ {\n        print(head);\n        ((pc(' '), print(tail)), ...);\n        pc('\\\
    n');\n    }\n\n    void println() {\n        pc('\\n');\n    }\n};\n\ntemplate<class\
    \ T>\nScanner &operator>>(Scanner &in, T &x) {\n    in.read(x);\n    return in;\n\
    }\n\ntemplate<class T>\nPrinter &operator<<(Printer &out, const T &x) {\n    out.print(x);\n\
    \    return out;\n}\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n\
    \ */\n#line 13 \"test/yosupo_aplusb_library_composition.test.cpp\"\n\n#line 1\
    \ \"util/modint.cpp\"\n\n\n\n#line 1 \"util/modint_base.cpp\"\n\n\n\ntemplate\
    \ <uint Mod>\nstruct modint {\n    uint val;\npublic:\n    static modint raw(int\
    \ v) { modint x; x.val = v; return x; }\n    static constexpr uint get_mod() {\
    \ return Mod; }\n    static constexpr uint M() { return Mod; }\n    modint() :\
    \ val(0) {}\n    template <class T>\n    modint(T v) { ll x = (ll)(v % (ll)(Mod));\
    \ if (x < 0) x += Mod; val = uint(x); }\n    modint(bool v) { val = ((unsigned\
    \ int)(v) % Mod); }\n    uint &value() noexcept { return val; }\n    const uint\
    \ &value() const noexcept { return val; }\n    modint& operator++() { val++; if\
    \ (val == Mod) val = 0; return *this; }\n    modint& operator--() { if (val ==\
    \ 0) val = Mod; val--; return *this; }\n    modint operator++(int) { modint result\
    \ = *this; ++*this; return result; }\n    modint operator--(int) { modint result\
    \ = *this; --*this; return result; }\n    modint& operator+=(const modint& b)\
    \ { val += b.val; if (val >= Mod) val -= Mod; return *this; }\n    modint& operator-=(const\
    \ modint& b) { val -= b.val; if (val >= Mod) val += Mod; return *this; }\n   \
    \ modint& operator*=(const modint& b) { ull z = val; z *= b.val; val = (uint)(z\
    \ % Mod); return *this; }\n    modint& operator/=(const modint& b) { return *this\
    \ = *this * b.inv(); }\n    modint operator+() const { return *this; }\n    modint\
    \ operator-() const { return modint() - *this; }\n    modint pow(long long n)\
    \ const { modint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>=\
    \ 1; } return r; }\n    modint inv() const { return pow(Mod - 2); }\n    friend\
    \ modint operator+(const modint& a, const modint& b) { return modint(a) += b;\
    \ }\n    friend modint operator-(const modint& a, const modint& b) { return modint(a)\
    \ -= b; }\n    friend modint operator*(const modint& a, const modint& b) { return\
    \ modint(a) *= b; }\n    friend modint operator/(const modint& a, const modint&\
    \ b) { return modint(a) /= b; }\n    friend bool operator==(const modint& a, const\
    \ modint& b) { return a.val == b.val; }\n    friend bool operator!=(const modint&\
    \ a, const modint& b) { return a.val != b.val; }\n};\n\n\n#line 5 \"util/modint.cpp\"\
    \n\n#ifndef FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\nusing mint = modint<MOD>;\n#define\
    \ FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n#else\nstatic_assert(mint::get_mod() ==\
    \ MOD, \"mint is already defined with a different modulus\");\n#endif\n\n/**\n\
    \ * @brief modint(\u56FA\u5B9AMOD)\n */\n\n\n#line 1 \"math/ntt.cpp\"\n\n\n\n\
    #line 5 \"math/ntt.cpp\"\n\nconstexpr int ntt_mod = 998244353, ntt_root = 3;\n\
    #ifndef NTT_NAIVE_MUL_THRESHOLD\n#define NTT_NAIVE_MUL_THRESHOLD 3072\n#endif\n\
    #ifndef NTT_NAIVE_MUL_MIN_DIM\n#define NTT_NAIVE_MUL_MIN_DIM 48\n#endif\n#ifndef\
    \ FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\nusing mint = modint<ntt_mod>;\n#define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\
    #else\nstatic_assert(mint::get_mod() == ntt_mod, \"NTT requires mint with MOD\
    \ = 998244353\");\n#endif\n\n// 1012924417 -> 5, 924844033 -> 5\n// 998244353\
    \  -> 3, 897581057 -> 3\n// 645922817  -> 3;\n\nclass NTT {\n    static constexpr\
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
    \n/**\n * @brief NTT\u30FB\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570(NTT/FPS)\n */\n\
    \n\n#line 16 \"test/yosupo_aplusb_library_composition.test.cpp\"\n\n#line 1 \"\
    datastructure/point_add_rectangle_sum.cpp\"\nusing namespace std;\n\n#line 1 \"\
    datastructure/binaryindexedtree.cpp\"\n\n\n\ntemplate<class T>\nclass BIT {\n\
    \    vector<T> bit;\n    int m, n;\npublic:\n    BIT(int n): bit(n), m(1), n(n)\
    \ {\n        while (m < n) m <<= 1;\n    }\n\n    T sum(int k){\n        T ret\
    \ = 0;\n        for (; k > 0; k -= (k & -k)) ret += bit[k - 1];\n        return\
    \ ret;\n    }\n\n    void add(int k, T x){\n        for (k++; k <= n; k += (k\
    \ & -k)) bit[k - 1] += x;\n    }\n\n    int lower_bound(T x) {\n        if (x\
    \ <= 0) return 0;\n        int i = 0;\n        for (int j = m; j; j >>= 1) {\n\
    \            if (i + j <= n && bit[i + j - 1] < x) x -= bit[i + j - 1], i += j;\n\
    \        }\n        return min(i + 1, n);\n    }\n};\n\n/**\n * @brief Binary\
    \ Indexed Tree(BIT)\n */\n\n\n#line 4 \"datastructure/point_add_rectangle_sum.cpp\"\
    \n\ntemplate<class T>\nstruct PointAddRectangleSum {\n    struct Operation {\n\
    \        int type;\n        int x, y, z;\n        T w;\n    };\n\n    vector<Operation>\
    \ ops;\n    vector<int> xs;\n\n    void add_point(int x, int y, T w) {\n     \
    \   ops.push_back({0, x, y, 0, w});\n        xs.push_back(x);\n    }\n\n    void\
    \ add_query(int l, int d, int r, int u) {\n        ops.push_back({1, l, d, r,\
    \ u});\n    }\n\n    vector<T> solve() const {\n        vector<int> ord_x = xs;\n\
    \        sort(ord_x.begin(), ord_x.end());\n        ord_x.erase(unique(ord_x.begin(),\
    \ ord_x.end()), ord_x.end());\n\n        int m = (int)ord_x.size();\n        vector<vector<int>>\
    \ ys(m + 1);\n        for (auto op : ops) {\n            if (op.type != 0) continue;\n\
    \            int xi = (int)(lower_bound(ord_x.begin(), ord_x.end(), op.x) - ord_x.begin())\
    \ + 1;\n            for (int x = xi; x <= m; x += x & -x) ys[x].push_back(op.y);\n\
    \        }\n        for (int i = 1; i <= m; ++i) {\n            sort(ys[i].begin(),\
    \ ys[i].end());\n            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());\n\
    \        }\n\n        vector<BIT<T>> bit;\n        bit.reserve(m + 1);\n     \
    \   bit.emplace_back(0);\n        for (int i = 1; i <= m; ++i) bit.emplace_back((int)ys[i].size());\n\
    \n        auto add = [&](int x, int y, T w) {\n            int xi = (int)(lower_bound(ord_x.begin(),\
    \ ord_x.end(), x) - ord_x.begin()) + 1;\n            for (int i = xi; i <= m;\
    \ i += i & -i) {\n                int yi = (int)(lower_bound(ys[i].begin(), ys[i].end(),\
    \ y) - ys[i].begin());\n                bit[i].add(yi, w);\n            }\n  \
    \      };\n        auto sum = [&](int x, int y) {\n            T ret = 0;\n  \
    \          int xi = (int)(lower_bound(ord_x.begin(), ord_x.end(), x) - ord_x.begin());\n\
    \            for (int i = xi; i > 0; i -= i & -i) {\n                int yi =\
    \ (int)(lower_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin());\n       \
    \         ret += bit[i].sum(yi);\n            }\n            return ret;\n   \
    \     };\n\n        vector<T> ans;\n        for (auto op : ops) {\n          \
    \  if (op.type == 0) {\n                add(op.x, op.y, (T)op.w);\n          \
    \  } else {\n                ans.push_back(sum(op.z, op.w) - sum(op.z, op.y) -\
    \ sum(op.x, op.w) + sum(op.x, op.y));\n            }\n        }\n        return\
    \ ans;\n    }\n};\n\n/**\n * @brief \u70B9\u52A0\u7B97\u9577\u65B9\u5F62\u548C\
    (Point Add Rectangle Sum)\n */\n#line 1 \"datastructure/static_rectangle_sum.cpp\"\
    \nusing namespace std;\n\n#line 4 \"datastructure/static_rectangle_sum.cpp\"\n\
    \ntemplate<class T>\nstruct StaticRectangleSum {\n    struct Point {\n       \
    \ int x, y;\n        T w;\n    };\n\n    struct Event {\n        int x, d, u,\
    \ id, sign;\n\n        bool operator<(const Event& other) const {\n          \
    \  return x < other.x;\n        }\n    };\n\n    vector<Point> points;\n    vector<Event>\
    \ events;\n    vector<int> ys;\n\n    void add_point(int x, int y, T w) {\n  \
    \      points.push_back({x, y, w});\n        ys.push_back(y);\n    }\n\n    void\
    \ add_query(int l, int d, int r, int u) {\n        int id = (int)events.size()\
    \ / 2;\n        events.push_back({r, d, u, id, 1});\n        events.push_back({l,\
    \ d, u, id, -1});\n        ys.push_back(d);\n        ys.push_back(u);\n    }\n\
    \n    vector<T> solve() {\n        vector<int> ord_y = ys;\n        sort(ord_y.begin(),\
    \ ord_y.end());\n        ord_y.erase(unique(ord_y.begin(), ord_y.end()), ord_y.end());\n\
    \n        auto get_y = [&](int y) {\n            return (int)(lower_bound(ord_y.begin(),\
    \ ord_y.end(), y) - ord_y.begin());\n        };\n\n        vector<Point> ps =\
    \ points;\n        for (auto& p : ps) p.y = get_y(p.y);\n        for (auto& e\
    \ : events) {\n            e.d = get_y(e.d);\n            e.u = get_y(e.u);\n\
    \        }\n\n        sort(ps.begin(), ps.end(), [](const Point& a, const Point&\
    \ b) {\n            return a.x < b.x;\n        });\n        sort(events.begin(),\
    \ events.end());\n\n        int q = (int)events.size() / 2;\n        vector<T>\
    \ ans(q, 0);\n        BIT<T> bit((int)ord_y.size());\n        int i = 0;\n   \
    \     for (auto e : events) {\n            while (i < (int)ps.size() && ps[i].x\
    \ < e.x) {\n                bit.add(ps[i].y, ps[i].w);\n                ++i;\n\
    \            }\n            ans[e.id] += (bit.sum(e.u) - bit.sum(e.d)) * e.sign;\n\
    \        }\n        return ans;\n    }\n};\n\n/**\n * @brief \u9759\u7684\u9577\
    \u65B9\u5F62\u548C(Static Rectangle Sum)\n */\n#line 19 \"test/yosupo_aplusb_library_composition.test.cpp\"\
    \n\n#line 1 \"graph/dijkstra_common.cpp\"\n\n\n\ntemplate <typename T>\nstruct\
    \ edge {\n    int from, to;\n    T cost;\n\n    edge(int to, T cost) : from(-1),\
    \ to(to), cost(cost) {}\n    edge(int from, int to, T cost) : from(from), to(to),\
    \ cost(cost) {}\n};\n\ntemplate <typename T>\nstruct DijkstraPriorityQueue {\n\
    \    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;\n\n    bool\
    \ empty() const { return q.empty(); }\n\n    void push(T cost, int v) {\n    \
    \    q.emplace(cost, v);\n    }\n\n    pair<T, int> pop() {\n        auto res\
    \ = q.top();\n        q.pop();\n        return res;\n    }\n};\n\ntemplate <typename\
    \ T, class Queue, class OnRelax>\nvector<T> dijkstra_internal(int s, const vector<vector<edge<T>>>\
    \ &G, Queue &Q, OnRelax on_relax) {\n    int n = (int)G.size();\n    vector<T>\
    \ dist(n, INF<T>);\n    dist[s] = 0;\n    Q.push(T(0), s);\n    while (!Q.empty())\
    \ {\n        auto [cost, v] = Q.pop();\n        if (dist[v] < cost) continue;\n\
    \        for (auto &&e : G[v]) {\n            T nxt = cost + e.cost;\n       \
    \     if (dist[e.to] <= nxt) continue;\n            dist[e.to] = nxt;\n      \
    \      on_relax(v, e);\n            Q.push(nxt, e.to);\n        }\n    }\n   \
    \ return dist;\n}\n\ntemplate <typename T, class Queue>\nvector<T> dijkstra_internal(int\
    \ s, const vector<vector<edge<T>>> &G, Queue &Q) {\n    return dijkstra_internal(s,\
    \ G, Q, [](int, const edge<T> &) {});\n}\n\n\n#line 2 \"graph/dijkstra.cpp\"\n\
    \ntemplate <typename T>\nvector<T> dijkstra(int s, const vector<vector<edge<T>>>\
    \ &G) {\n    DijkstraPriorityQueue<T> Q;\n    return dijkstra_internal(s, G, Q);\n\
    }\n\n/**\n * @brief Dijkstra\u6CD5\n */\n#line 2 \"graph/dijkstra_restore.cpp\"\
    \n\ntemplate <typename T>\nstruct DijkstraRestoreResult {\n    vector<T> dist;\n\
    \    vector<int> parent;\n};\n\ntemplate <typename T>\nDijkstraRestoreResult<T>\
    \ dijkstra_restore(int s, const vector<vector<edge<T>>> &G) {\n    vector<int>\
    \ parent((int)G.size(), -1);\n    DijkstraPriorityQueue<T> Q;\n    auto dist =\
    \ dijkstra_internal(s, G, Q, [&](int v, const edge<T> &e) {\n        parent[e.to]\
    \ = v;\n    });\n    return {dist, parent};\n}\n\nvector<int> restore_path(int\
    \ s, int t, const vector<int> &parent) {\n    vector<int> path;\n    if (t < 0\
    \ || t >= (int)parent.size()) return path;\n    int v = t;\n    while (v != -1)\
    \ {\n        path.push_back(v);\n        if (v == s) {\n            reverse(path.begin(),\
    \ path.end());\n            return path;\n        }\n        v = parent[v];\n\
    \    }\n    path.clear();\n    return path;\n}\n\n/**\n * @brief \u7D4C\u8DEF\u5FA9\
    \u5143\u4ED8\u304DDijkstra\u6CD5\n */\n#line 22 \"test/yosupo_aplusb_library_composition.test.cpp\"\
    \n\n#line 1 \"math/prime/linear_sieve.cpp\"\n\n\n\nstruct LinearSieve {\n    int\
    \ n;\n    vector<int> primes;\n    vector<int> min_factor;\n    vector<int> phi;\n\
    \    vector<int> mobius;\n    vector<bool> prime_table;\n\n    explicit LinearSieve(int\
    \ n, bool need_min_factor = false, bool need_phi = false, bool need_mobius = false)\n\
    \        : n(n < 0 ? 0 : n),\n          min_factor(need_min_factor ? this->n +\
    \ 1 : 0),\n          phi(need_phi ? this->n + 1 : 0),\n          mobius(need_mobius\
    \ ? this->n + 1 : 0),\n          prime_table(need_min_factor ? 0 : this->n + 1,\
    \ true) {\n        if (!prime_table.empty()) {\n            prime_table[0] = false;\n\
    \            if (this->n >= 1) prime_table[1] = false;\n        }\n        if\
    \ (!min_factor.empty() && this->n >= 1) min_factor[1] = 1;\n        if (!phi.empty())\
    \ {\n            phi[0] = 0;\n            if (this->n >= 1) phi[1] = 1;\n    \
    \    }\n        if (!mobius.empty()) {\n            mobius[0] = 0;\n         \
    \   if (this->n >= 1) mobius[1] = 1;\n        }\n        for (int i = 2; i <=\
    \ this->n; ++i) {\n            bool prime = min_factor.empty() ? prime_table[i]\
    \ : min_factor[i] == 0;\n            if (prime) {\n                if (!min_factor.empty())\
    \ min_factor[i] = i;\n                if (!phi.empty()) phi[i] = i - 1;\n    \
    \            if (!mobius.empty()) mobius[i] = -1;\n                primes.emplace_back(i);\n\
    \            }\n            for (auto &&p : primes) {\n                long long\
    \ x = 1LL * i * p;\n                if (x > this->n) break;\n                if\
    \ (!prime_table.empty()) prime_table[x] = false;\n                if (!min_factor.empty())\
    \ min_factor[x] = p;\n                bool same = i % p == 0;\n              \
    \  if (!phi.empty()) phi[x] = same ? phi[i] * p : phi[i] * (p - 1);\n        \
    \        if (!mobius.empty()) mobius[x] = same ? 0 : -mobius[i];\n           \
    \     if (same) break;\n            }\n        }\n    }\n\n    bool is_prime(int\
    \ x) const {\n        if (x < 2 || x > n) return false;\n        if (!min_factor.empty())\
    \ return min_factor[x] == x;\n        return prime_table[x];\n    }\n};\n\n/**\n\
    \ * @brief \u7DDA\u5F62\u7BE9(Linear Sieve)\n */\n\n\n#line 2 \"math/prime/get_min_factor.cpp\"\
    \n\nvector<int> get_min_factor(int n) {\n    return LinearSieve(n, true).min_factor;\n\
    }\n\n/**\n * @brief \u6700\u5C0F\u7D20\u56E0\u6570\u30C6\u30FC\u30D6\u30EB(Min\
    \ Factor Table)\n */\n#line 2 \"math/prime/get_prime.cpp\"\n\nvector<int> get_prime(int\
    \ n) {\n    return LinearSieve(n).primes;\n}\n#line 25 \"test/yosupo_aplusb_library_composition.test.cpp\"\
    \n\n#line 1 \"geometry/geometry.cpp\"\n\n\n\n// \u51F8\u5305\u306F\u540C\u3058\
    \u9802\u70B9\u304C\u542B\u307E\u308C\u3066\u3044\u308B\u3068\u30D0\u30B0\u308B\
    \nusing geometry_real = double;\nusing real = geometry_real;\nstatic constexpr\
    \ geometry_real EPS = 1e-10;\nconst geometry_real pi = acos(-1);\n\nstruct Point\
    \ {\n    geometry_real x, y;\n    Point& operator+=(const Point a) { x += a.x;\
    \ y += a.y;  return *this; }\n    Point& operator-=(const Point a) { x -= a.x;\
    \ y -= a.y;  return *this; }\n    Point& operator*=(const geometry_real k) { x\
    \ *= k; y *= k;  return *this; }\n    Point& operator/=(const geometry_real k)\
    \ { x /= k; y /= k;  return *this; }\n    Point operator+(const Point a) const\
    \ {return Point(*this) += a; }\n    Point operator-(const Point a) const {return\
    \ Point(*this) -= a; }\n    Point operator*(const geometry_real k) const {return\
    \ Point(*this) *= k; }\n    Point operator/(const geometry_real k) const {return\
    \ Point(*this) /= k; }\n    bool operator<(const Point &a) const { return (x !=\
    \ a.x ? x < a.x : y < a.y); }\n    explicit Point(geometry_real a = 0, geometry_real\
    \ b = 0) : x(a), y(b) {};\n};\n\nbool sorty(Point a, Point b) {\n    return (a.y\
    \ != b.y ? a.y < b.y : a.x < b.x);\n}\n\nistream &operator>>(istream &s, Point\
    \ &P) {\n    s >> P.x >> P.y;\n    return s;\n}\n\ninline geometry_real dot(Point\
    \ a, Point b) { return a.x * b.x + a.y * b.y; }\n\ninline geometry_real cross(Point\
    \ a, Point b) { return a.x * b.y - a.y * b.x; }\n\ninline geometry_real abs(Point\
    \ a) { return sqrt(dot(a, a)); }\n\ngeometry_real angle(Point A, Point B) {\n\
    \    return acos(dot(A, B) / abs(A) / abs(B));\n}\n\nstatic constexpr int COUNTER_CLOCKWISE\
    \ = 1;\nstatic constexpr int CLOCKWISE = -1;\nstatic constexpr int ONLINE_BACK\
    \ = 2;\nstatic constexpr int ONLINE_FRONT = -2;\nstatic constexpr int ON_SEGMENT\
    \ = 0;\n\nint ccw(Point a, Point b, Point c) {\n    b -= a;\n    c -= a;\n   \
    \ if (cross(b, c) > EPS)\n        return COUNTER_CLOCKWISE;\n    if (cross(b,\
    \ c) < -EPS)\n        return CLOCKWISE;\n    if (dot(b, c) < 0)\n        return\
    \ ONLINE_BACK;\n    if (abs(b) < abs(c))\n        return ONLINE_FRONT;\n    return\
    \ ON_SEGMENT;\n}\n\nstruct Segment {\n    Point a, b;\n\n    Segment(Point x,\
    \ Point y) : a(x), b(y) {};\n};\n\nstruct Line {\n    Point a, b;\n\n    Line(Point\
    \ x, Point y) : a(x), b(y) {};\n};\n\nstruct Circle {\n    Point c;\n    geometry_real\
    \ r;\n\n    Circle(Point c, geometry_real r) : c(c), r(r) {};\n};\n\nusing Polygon\
    \ = vector<Point>;\n\nbool intersect(Segment s, Segment t) {\n    return (ccw(s.a,\
    \ s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 &&\n            ccw(t.a, t.b, s.a) * ccw(t.a,\
    \ t.b, s.b) <= 0);\n}\n\nbool intersect(Segment s, Line t) {\n    int a = ccw(t.a,\
    \ t.b, s.a), b = ccw(t.a, t.b, s.b);\n    return (!(a & 1) || !(b & 1) || a !=\
    \ b);\n}\n\nPoint polar(double r, double t) {\n    return Point(r * cos(t), r\
    \ * sin(t));\n}\n\ndouble arg(Point p) {\n    return atan2(p.y, p.x);\n}\n\nstatic\
    \ constexpr int CONTAIN = 0;\nstatic constexpr int INSCRIBE = 1;\nstatic constexpr\
    \ int INTERSECT = 2;\nstatic constexpr int CIRCUMSCRIBED = 3;\nstatic constexpr\
    \ int SEPARATE = 4;\n\nint intersect(Circle c1, Circle c2) {\n    if (c1.r < c2.r)\n\
    \        swap(c1, c2);\n    geometry_real d = abs(c1.c - c2.c);\n    geometry_real\
    \ r = c1.r + c2.r;\n    if (fabs(d - r) < EPS)\n        return CIRCUMSCRIBED;\n\
    \    if (d > r)\n        return SEPARATE;\n    if (fabs(d + c2.r - c1.r) < EPS)\n\
    \        return INSCRIBE;\n    if (d + c2.r < c1.r)\n        return CONTAIN;\n\
    \    return INTERSECT;\n}\n\ngeometry_real distance(Line l, Point c) {\n    return\
    \ abs(cross(l.b - l.a, c - l.a) / abs(l.b - l.a));\n}\n\ngeometry_real distance(Segment\
    \ s, Point c) {\n    if (dot(s.b - s.a, c - s.a) < EPS)\n        return abs(c\
    \ - s.a);\n    if (dot(s.a - s.b, c - s.b) < EPS)\n        return abs(c - s.b);\n\
    \    return abs(cross(s.b - s.a, c - s.a)) / abs(s.a - s.b);\n}\n\ngeometry_real\
    \ distance(Segment s, Segment t) {\n    if (intersect(s, t))\n        return 0.0;\n\
    \    return min({distance(s, t.a), distance(s, t.b),\n                distance(t,\
    \ s.a), distance(t, s.b)});\n}\n\nPoint project(Line l, Point p) {\n    Point\
    \ Q = l.b - l.a;\n    return l.a + Q * (dot(p - l.a, Q) / dot(Q, Q));\n}\n\nPoint\
    \ project(Segment s, Point p) {\n    Point Q = s.b - s.a;\n    return s.a + Q\
    \ * (dot(p - s.a, Q) / dot(Q, Q));\n}\n\nPoint refrect(Segment s, Point p) {\n\
    \    Point Q = project(s, p);\n    return Q * 2 - p;\n}\n\nbool isOrthogonal(Segment\
    \ s, Segment t) {\n    return fabs(dot(s.b - s.a, t.b - t.a)) < EPS;\n}\n\nbool\
    \ isparallel(Segment s, Segment t) {\n    return fabs(cross(s.b - s.a, t.b - t.a))\
    \ < EPS;\n}\n\nPoint crossPoint(Segment s, Segment t) {\n    geometry_real d1\
    \ = cross(s.b - s.a, t.b - t.a);\n    geometry_real d2 = cross(s.b - s.a, s.b\
    \ - t.a);\n    if (fabs(d1) < EPS && fabs(d2) < EPS)\n        return t.a;\n  \
    \  return t.a + (t.b - t.a) * d2 / d1;\n}\n\nPoint crossPoint(Line s, Line t)\
    \ {\n    geometry_real d1 = cross(s.b - s.a, t.b - t.a);\n    geometry_real d2\
    \ = cross(s.b - s.a, s.b - t.a);\n    if (fabs(d1) < EPS && fabs(d2) < EPS)\n\
    \        return t.a;\n    return t.a + (t.b - t.a) * d2 / d1;\n}\n\nPolygon crossPoint(Circle\
    \ c, Line l) {\n    Point p = project(l, c.c), q = (l.b - l.a) / abs(l.b - l.a);\n\
    \    if (abs(distance(l, c.c) - c.r) < EPS) {\n        return {p};\n    }\n  \
    \  double k = sqrt(c.r * c.r - dot(p - c.c, p - c.c));\n    return {p - q * k,\
    \ p + q * k};\n}\n\nPolygon crossPoint(Circle c, Segment s) {\n    auto tmp =\
    \ crossPoint(c, Line(s.a, s.b));\n    Polygon ret;\n    for (auto &&i: tmp) {\n\
    \        if (distance(s, i) < EPS)\n            ret.emplace_back(i);\n    }\n\
    \    return ret;\n}\n\nPolygon crossPoint(Circle c1, Circle c2) {\n    double\
    \ d = abs(c1.c - c2.c);\n    double a = acos((c1.r * c1.r + d * d - c2.r * c2.r)\
    \ / (2 * c1.r * d));\n    double t = arg(c2.c - c1.c);\n    return {c1.c + polar(c1.r,\
    \ t + a), c1.c + polar(c1.r, t - a)};\n}\n\nPolygon tangent(Circle c1, Point p)\
    \ {\n    Circle c2 = Circle(p, sqrt(dot(c1.c - p, c1.c - p) - c1.r * c1.r));\n\
    \    return crossPoint(c1, c2);\n}\n\nvector<Line> tangent(Circle c1, Circle c2)\
    \ {\n    vector<Line> ret;\n    if (c1.r < c2.r)\n        swap(c1, c2);\n    double\
    \ k = dot(c1.c - c2.c, c1.c - c2.c);\n    if (abs(k) < EPS)\n        return {};\n\
    \    Point u = (c2.c - c1.c) / sqrt(k);\n    Point v(-u.y, u.x);\n    for (auto\
    \ &&i: {-1, 1}) {\n        double h = (c1.r + i * c2.r) / sqrt(k);\n        if\
    \ (abs(h * h - 1) < EPS) {\n            ret.emplace_back(c1.c + u * c1.r, c1.c\
    \ + (u + v) * c1.r);\n        } else if (h * h < 1) {\n            Point u2 =\
    \ u * h, v2 = v * sqrt(1 - h * h);\n            ret.emplace_back(c1.c + (u2 +\
    \ v2) * c1.r, c2.c - (u2 + v2) * c2.r * i);\n            ret.emplace_back(c1.c\
    \ + (u2 - v2) * c1.r, c2.c - (u2 - v2) * c2.r * i);\n        }\n    }\n    return\
    \ ret;\n}\n\ngeometry_real area(Polygon v) {\n    if (v.size() < 3)\n        return\
    \ 0.0;\n    geometry_real ans = 0.0;\n    for (int i = 0; i < v.size(); ++i) {\n\
    \        ans += cross(v[i], v[(i + 1) % v.size()]);\n    }\n    return ans / 2;\n\
    }\n\ngeometry_real area(Circle c, Polygon &v) {\n    int n = v.size();\n    geometry_real\
    \ ans = 0.0;\n    Polygon u;\n    for (int i = 0; i < n; ++i) {\n        u.emplace_back(v[i]);\n\
    \        auto q = crossPoint(c, Segment(v[i], v[(i + 1) % n]));\n        for (auto\
    \ &&j: q) {\n            u.emplace_back(j);\n        }\n    }\n    for (int i\
    \ = 0; i < u.size(); ++i) {\n        Point A = u[i] - c.c, B = u[(i + 1) % u.size()]\
    \ - c.c;\n        if (abs(A) >= c.r + EPS || abs(B) >= c.r + EPS) {\n        \
    \    Point C = polar(1, arg(B) - arg(A));\n            ans += c.r * c.r * arg(C)\
    \ / 2;\n        } else {\n            ans += cross(A, B) / 2;\n        }\n   \
    \ }\n    return ans;\n}\n\ngeometry_real area(Circle a, Circle b) {\n    auto\
    \ d = abs(a.c - b.c);\n    if (a.r + b.r <= d + EPS)\n        return 0;\n    else\
    \ if (d <= abs(a.r - b.r))\n        return pi * min(a.r, b.r) * min(a.r, b.r);\n\
    \    geometry_real p = 2 * acos((a.r * a.r + d * d - b.r * b.r) / (2 * a.r * d));\n\
    \    geometry_real q = 2 * acos((b.r * b.r + d * d - a.r * a.r) / (2 * b.r * d));\n\
    \    return a.r * a.r * (p - sin(p)) / 2 + b.r * b.r * (q - sin(q)) / 2;\n}\n\n\
    Polygon convex_hull(Polygon v) {\n    int n = v.size();\n    sort(v.begin(), v.end(),\
    \ sorty);\n    int k = 0;\n    Polygon ret(n * 2);\n    for (int i = 0; i < n;\
    \ ++i) {\n        while (k > 1 && cross(ret[k - 1] - ret[k - 2], v[i] - ret[k\
    \ - 1]) < 0)\n            k--;\n        ret[k++] = v[i];\n    }\n    for (int\
    \ i = n - 2, t = k; i >= 0; i--) {\n        while (k > t && cross(ret[k - 1] -\
    \ ret[k - 2], v[i] - ret[k - 1]) < 0)\n            k--;\n        ret[k++] = v[i];\n\
    \    }\n    ret.resize(k - 1);\n    return ret;\n}\n\nbool isconvex(Polygon v)\
    \ {\n    int n = v.size();\n    for (int i = 0; i < n; ++i) {\n        if (ccw(v[(i\
    \ + n - 1) % n], v[i], v[(i + 1) % n]) == CLOCKWISE)\n            return false;\n\
    \    }\n    return true;\n}\n\nint contains(Polygon v, Point p) {\n    int n =\
    \ v.size();\n    bool x = false;\n    static constexpr int IN = 2, ON = 1, OUT\
    \ = 0;\n    for (int i = 0; i < n; ++i) {\n        Point a = v[i] - p, b = v[(i\
    \ + 1) % n] - p;\n        if (fabs(cross(a, b)) < EPS && dot(a, b) < EPS)\n  \
    \          return ON;\n        if (a.y > b.y)\n            swap(a, b);\n     \
    \   if (a.y < EPS && EPS < b.y && cross(a, b) > EPS)\n            x = !x;\n  \
    \  }\n    return (x ? IN : OUT);\n}\n\nint contains_convex(Polygon &v, Point p)\
    \ {\n    int a = 1, b = v.size() - 1;\n    static constexpr int IN = 2, ON = 1,\
    \ OUT = 0;\n    if (v.size() < 3)\n        return (ccw(v.front(), v.back(), p)\
    \ & 1) == 0 ? ON : OUT;\n    if (ccw(v[0], v[a], v[b]) > 0)\n        swap(a, b);\n\
    \    int la = ccw(v[0], v[a], p), lb = ccw(v[0], v[b], p);\n    if ((la & 1) ==\
    \ 0 || (lb & 1) == 0)\n        return ON;\n    if (la > 0 || lb < 0)\n       \
    \ return OUT;\n    while (abs(a - b) > 1) {\n        int c = (a + b) / 2;\n  \
    \      int val = ccw(v[0], v[c], p);\n        (val > 0 ? b : a) = c;\n    }\n\
    \    int res = ccw(v[a], v[b], p);\n    if ((res & 1) == 0)\n        return ON;\n\
    \    return res < 0 ? IN : OUT;\n}\n\ngeometry_real diameter(Polygon v) {\n  \
    \  int n = v.size();\n    if (n == 2)\n        return abs(v[0] - v[1]);\n    int\
    \ i = 0, j = 0;\n    for (int k = 0; k < n; ++k) {\n        if (v[i] < v[k])\n\
    \            i = k;\n        if (!(v[j] < v[k]))\n            j = k;\n    }\n\
    \    geometry_real ret = 0;\n    int si = i, sj = j;\n    while (i != sj || j\
    \ != si) {\n        ret = max(ret, abs(v[i] - v[j]));\n        if (cross(v[(i\
    \ + 1) % n] - v[i], v[(j + 1) % n] - v[j]) < 0.0)\n            i = (i + 1) % n;\n\
    \        else\n            j = (j + 1) % n;\n    }\n    return ret;\n}\n\nPolygon\
    \ convexCut(Polygon v, Line l) {\n    Polygon q;\n    int n = v.size();\n    for\
    \ (int i = 0; i < n; ++i) {\n        Point a = v[i], b = v[(i + 1) % n];\n   \
    \     if (ccw(l.a, l.b, a) != -1)\n            q.push_back(a);\n        if (ccw(l.a,\
    \ l.b, a) * ccw(l.a, l.b, b) < 0) {\n            q.push_back(crossPoint(Line(a,\
    \ b), l));\n        }\n    }\n    return q;\n}\n\ngeometry_real closest_pair(Polygon\
    \ &v, int l = 0, int r = -1) {\n    if (!(~r)) {\n        r = v.size();\n    \
    \    sort(v.begin(), v.end());\n    }\n    if (r - l < 2) {\n        return abs(v.front()\
    \ - v.back());\n    }\n    int mid = (l + r) / 2;\n    geometry_real p = v[mid].x;\n\
    \    geometry_real d = min(closest_pair(v, l, mid), closest_pair(v, mid, r));\n\
    \    inplace_merge(v.begin() + l, v.begin() + mid, v.begin() + r, sorty);\n  \
    \  Polygon u;\n    for (int i = l; i < r; ++i) {\n        if (fabs(v[i].x - p)\
    \ >= d)\n            continue;\n        for (int j = 0; j < u.size(); ++j) {\n\
    \            geometry_real dy = v[i].y - next(u.rbegin(), j)->y;\n           \
    \ if (dy >= d)\n                break;\n            d = min(d, abs(v[i] - *next(u.rbegin(),\
    \ j)));\n        }\n        u.emplace_back(v[i]);\n    }\n    return d;\n}\n\n\
    /**\n * @brief \u5E7E\u4F55\u30E9\u30A4\u30D6\u30E9\u30EA(Geometry)\n */\n\n\n\
    #line 2 \"geometry/dualgraph.cpp\"\n\nclass DualGraph {\n    struct P {\n    \
    \    int to, nxt, id, id2, rev;\n        P(int to = 0, int nxt = 0, int id = 0,\
    \ int rev = 0) : to(to), nxt(nxt), id(id), rev(rev), id2(0) {};\n        bool\
    \ operator!=(P x){ return to != x.to || nxt != x.nxt || id != x.id || rev != x.rev;\
    \ }\n    };\npublic:\n    int n, m;\n    Polygon v;\n    vector<vector<P>> G_;\n\
    \    vector<vector<int>> G;\n    vector<vector<Point>> A;\n    DualGraph(Polygon\
    \ v) : v(v), n(v.size()), G_(n), m(0) {}\n\n    void add_point(Point P){ v.emplace_back(P);\
    \ n++; G_.emplace_back(); }\n    void add_edge(int a, int b){\n        G_[a].emplace_back(b,\
    \ 0, m, 0);\n        G_[b].emplace_back(a, 0, m++, 0);\n    }\n\n    void build(){\n\
    \        vector<int> l(m), r(m);\n        for (int i = 0; i < n; ++i) {\n    \
    \        sort(G_[i].begin(), G_[i].end(), [&](P &a, P &b){ return arg(v[a.to]-v[i])\
    \ < arg(v[b.to]-v[i]); });\n            for (int j = 0; j < G_[i].size(); ++j)\
    \ {\n                G_[i][j].nxt = (j + 1) % G_[i].size();\n                if(i\
    \ < G_[i][j].to) l[G_[i][j].id] = j;\n                else r[G_[i][j].id] = j;\n\
    \            }\n        }\n        for (int i = 0; i < n; ++i) {\n           \
    \ for (auto &&e : G_[i]) {\n                e.rev = (i < e.to ? r[e.id] : l[e.id]);\n\
    \            }\n        }\n        int cur = 1;\n        A = move(vector<vector<Point>>());\n\
    \        for (int i = 0; i < n; ++i) {\n            for (auto &&x : G_[i]) {\n\
    \                if(x.id2) continue;\n                x.id2 = cur;\n         \
    \       A.emplace_back();\n                A.back().emplace_back(v[i]);\n    \
    \            auto e = &x;\n                while(e->to != i){\n              \
    \      A.back().emplace_back(v[e->to]);\n                    e = &G_[e->to][G_[e->to][e->rev].nxt];\n\
    \                    e->id2 = cur;\n                }\n                cur++;\n\
    \            }\n        }\n        for (int i = 0; i < n; ++i) {\n           \
    \ for (auto &&e : G_[i]) {\n                (i < e.to ? l[e.id] : r[e.id]) = e.id2-1;\n\
    \            }\n        }\n        G = move(vector<vector<int>>(A.size()));\n\
    \        for (int i = 0; i < m; ++i) {\n            G[l[i]].emplace_back(r[i]);\n\
    \            G[r[i]].emplace_back(l[i]);\n        }\n    }\n};\n\n/**\n * @brief\
    \ \u53CC\u5BFE\u30B0\u30E9\u30D5(Dual Graph)\n */\n#line 2 \"geometry/half_plane_intersection.cpp\"\
    \n\nnamespace internal_half_plane_intersection {\n\nstruct HalfPlane {\n    Point\
    \ p, pq;\n    geometry_real angle;\n\n    HalfPlane() = default;\n\n    explicit\
    \ HalfPlane(const Line &l)\n        : p(l.a), pq(l.b - l.a), angle(atan2(pq.y,\
    \ pq.x)) {}\n\n    bool operator<(const HalfPlane &other) const {\n        if\
    \ (fabs(angle - other.angle) > EPS) return angle < other.angle;\n        return\
    \ cross(pq, other.p - p) < 0;\n    }\n\n    bool outside(Point r) const {\n  \
    \      return cross(pq, r - p) < -EPS;\n    }\n};\n\nPoint intersection(const\
    \ HalfPlane &s, const HalfPlane &t) {\n    geometry_real a = cross(t.p - s.p,\
    \ t.pq) / cross(s.pq, t.pq);\n    return s.p + s.pq * a;\n}\n\nbool same_point(Point\
    \ a, Point b) {\n    return abs(a - b) < EPS;\n}\n\n}  // namespace internal_half_plane_intersection\n\
    \nPolygon half_plane_intersection(vector<Line> ls) {\n    using namespace internal_half_plane_intersection;\n\
    \n    static constexpr geometry_real INF = 1e9;\n    vector<HalfPlane> hs;\n \
    \   hs.reserve(ls.size() + 4);\n    for (const Line &l : ls) hs.emplace_back(l);\n\
    \n    Polygon box = {\n        Point(-INF, -INF),\n        Point(INF, -INF),\n\
    \        Point(INF, INF),\n        Point(-INF, INF),\n    };\n    for (int i =\
    \ 0; i < 4; ++i) {\n        hs.emplace_back(Line(box[i], box[(i + 1) % 4]));\n\
    \    }\n\n    sort(hs.begin(), hs.end());\n\n    deque<HalfPlane> deq;\n    for\
    \ (const HalfPlane &h : hs) {\n        while (deq.size() > 1 &&\n            \
    \   h.outside(intersection(deq.back(), deq[deq.size() - 2]))) {\n            deq.pop_back();\n\
    \        }\n        while (deq.size() > 1 &&\n               h.outside(intersection(deq[0],\
    \ deq[1]))) {\n            deq.pop_front();\n        }\n        if (!deq.empty()\
    \ && fabs(cross(deq.back().pq, h.pq)) < EPS) {\n            if (dot(deq.back().pq,\
    \ h.pq) < 0) return {};\n            if (h.outside(deq.back().p)) deq.pop_back();\n\
    \            else continue;\n        }\n        deq.push_back(h);\n    }\n\n \
    \   while (deq.size() > 2 &&\n           deq.front().outside(intersection(deq.back(),\
    \ deq[deq.size() - 2]))) {\n        deq.pop_back();\n    }\n    while (deq.size()\
    \ > 2 &&\n           deq.back().outside(intersection(deq[0], deq[1]))) {\n   \
    \     deq.pop_front();\n    }\n    if (deq.size() < 3) return {};\n\n    Polygon\
    \ res;\n    res.reserve(deq.size());\n    for (int i = 0; i < (int)deq.size();\
    \ ++i) {\n        Point p = intersection(deq[i], deq[(i + 1) % deq.size()]);\n\
    \        if (res.empty() || !same_point(res.back(), p)) res.push_back(p);\n  \
    \  }\n    if (res.size() >= 2 && same_point(res.front(), res.back())) res.pop_back();\n\
    \    if (res.size() < 3 || fabs(area(res)) < EPS) return {};\n    return res;\n\
    }\n\n/**\n * @brief \u534A\u5E73\u9762\u5171\u901A\u90E8\u5206(Half-Plane Intersection)\n\
    \ */\n#line 28 \"test/yosupo_aplusb_library_composition.test.cpp\"\n\n#line 1\
    \ \"datastructure/sparsetable.cpp\"\n\n\n\ntemplate <class F>\nstruct SparseTable\
    \ {\n    using T = typename F::T;\n    vector<vector<T>> table;\n    vector<int>\
    \ u;\n    SparseTable() = default;\n    explicit SparseTable(const vector<T> &v){\
    \ build(v); }\n \n    void build(const vector<T> &v){\n        int n = v.size(),\
    \ m = 1;\n        while((1<<m) <= n) m++;\n        table.assign(m, vector<T>(n));\n\
    \        u.assign(n+1, 0);\n        for (int i = 2; i <= n; ++i) {\n         \
    \   u[i] = u[i>>1] + 1;\n        }\n        for (int i = 0; i < n; ++i) {\n  \
    \          table[0][i] = v[i];\n        }\n        for (int i = 1; i < m; ++i)\
    \ {\n            int x = (1<<(i-1));\n            for (int j = 0; j < n; ++j)\
    \ {\n                table[i][j] = F::f(table[i-1][j], table[i-1][min(j+x, n-1)]);\n\
    \            }\n        }\n    }\n \n    T query(int a, int b){\n        int l\
    \ = b-a;\n        return F::f(table[u[l]][a], table[u[l]][b-(1<<u[l])]);\n   \
    \ }\n};\n\n/**\n * @brief Sparse Table\n */\n\n\n#line 2 \"tree/LCA.cpp\"\n\n\
    struct LCA_MinDepth {\n    using T = pair<int, int>;\n    static T f(T a, T b)\
    \ { return min(a, b); }\n    static T e() { return T{INF<int>, -1}; }\n};\n\n\
    class LCA {\n    SparseTable<LCA_MinDepth> table;\n\n    void dfs_euler(int v,\
    \ int p, int d, int &k) {\n        id[v] = k;\n        vs[k] = v;\n        depth[k++]\
    \ = d;\n        for (auto &&u : G[v]) {\n            if (u == p) continue;\n \
    \           dfs_euler(u, v, d + 1, k);\n            vs[k] = v;\n            depth[k++]\
    \ = d;\n        }\n    }\n\npublic:\n    int n;\n    vector<vector<int>> G;\n\
    \    vector<int> vs, depth, id;\n\n    explicit LCA(int n) : table(), n(n), G(n),\
    \ vs(2 * n - 1), depth(2 * n - 1), id(n) {}\n\n    void add_edge(int a, int b)\
    \ {\n        G[a].emplace_back(b);\n        G[b].emplace_back(a);\n    }\n\n \
    \   void eulertour(int root = 0) {\n        int k = 0;\n        dfs_euler(root,\
    \ -1, 0, k);\n    }\n\n    void build(int root = 0) {\n        eulertour(root);\n\
    \        vector<pair<int, int>> v(2 * n - 1);\n        for (int i = 0; i < 2 *\
    \ n - 1; ++i) {\n            v[i] = make_pair(depth[i], i);\n        }\n     \
    \   table.build(v);\n    }\n\n    void buildLCA(int root = 0) {\n        build(root);\n\
    \    }\n\n    int lca(int u, int v) {\n        if (id[u] > id[v]) swap(u, v);\n\
    \        return vs[table.query(id[u], id[v] + 1).second];\n    }\n};\n\n/**\n\
    \ * @brief \u6700\u8FD1\u5171\u901A\u7956\u5148(LCA)\n */\n#line 2 \"tree/auxtree.cpp\"\
    \n\nstruct F {\n    using T = pair<int, int>;\n    static T f(T a, T b) { return\
    \ min(a, b); }\n    static T e() { return T{INF<int>, -1}; }\n};\n\nclass AuxTree\
    \ {\n    SparseTable<F> table;\n    void dfs_euler(int v, int p, int d, int &k,\
    \ int &l){\n        id[v] = k;\n        vs[k] = v;\n        depth[k++] = d;\n\
    \        dep[v] = d;\n        fi[v] = l++;\n        for (auto &&u : G[v]) {\n\
    \            if(u != p){\n                dfs_euler(u, v, d+1, k, l);\n      \
    \          vs[k] = v;\n                depth[k++] = d;\n            }\n      \
    \  }\n    }\npublic:\n    int n;\n    vector<vector<int>> G, out;\n    vector<int>\
    \ vs, depth, dep, id, fi;\n    explicit AuxTree(int n) : table(), n(n), G(n),\
    \ out(n), vs(2*n-1), depth(2*n-1), dep(n), id(n), fi(n) {};\n    void add_edge(int\
    \ a, int b){\n        G[a].emplace_back(b);\n        G[b].emplace_back(a);\n \
    \   }\n\n    void eulertour(int root) {\n        int k = 0, l = 0;\n        dfs_euler(root,\
    \ -1, 0, k, l);\n    }\n\n    void buildLCA(int root = 0){\n        eulertour(root);\n\
    \        vector<pair<int, int>> v(2*n-1);\n        for (int i = 0; i < 2*n-1;\
    \ ++i) {\n            v[i] = make_pair(depth[i], vs[i]);\n        }\n        table.build(v);\n\
    \    }\n\n    void make(vector<int> &v){\n        sort(v.begin(),v.end(), [&](int\
    \ a, int b){ return fi[a] < fi[b]; });\n        v.erase(unique(v.begin(), v.end()),\
    \ v.end());\n        int k = v.size();\n        stack<int> s;\n        s.emplace(v.front());\n\
    \        for (int i = 0; i+1 < k; ++i) {\n            int w = LCA(v[i], v[i+1]);\n\
    \            if(w != v[i]){\n                int u = s.top(); s.pop();\n     \
    \           while(!s.empty() && dep[w] < dep[s.top()]){\n                    out[s.top()].emplace_back(u);\n\
    \                    out[u].emplace_back(s.top());\n                    u = s.top();\
    \ s.pop();\n                }\n                if(s.empty() || s.top() != w){\n\
    \                    s.emplace(w);\n                    v.emplace_back(w);\n \
    \               }\n                out[w].emplace_back(u);\n                out[u].emplace_back(w);\n\
    \            }\n            s.emplace(v[i+1]);\n        }\n        while(s.size()\
    \ > 1){\n            int u = s.top(); s.pop();\n            out[s.top()].emplace_back(u);\n\
    \            out[u].emplace_back(s.top());\n        }\n    }\n\n    void clear(vector<int>\
    \ &v){\n        for (auto &&i : v) {\n            out[i].clear();\n          \
    \  out[i].shrink_to_fit();\n        }\n    }\n\n    int LCA(int u, int v){\n \
    \       if(id[u] > id[v]) swap(u, v);\n        return table.query(id[u], id[v]+1).second;\n\
    \    }\n\n    int distance(int u, int v){\n        return dep[u]+dep[v]-2*dep[LCA(u,\
    \ v)];\n    }\n};\n\n/**\n * @brief \u88DC\u52A9\u6728(Aux Tree)\n */\n#line 31\
    \ \"test/yosupo_aplusb_library_composition.test.cpp\"\n\nint main() {\n    Scanner\
    \ sc;\n    Printer pr;\n    ll a, b;\n    sc.read(a, b);\n    pr.println(a + b);\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\nstatic const int MOD = 998244353;\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\nusing ll = long long;\n\
    using uint = unsigned;\nusing ull = unsigned long long;\n\n#include \"../util/fastio.cpp\"\
    \n\n#include \"../util/modint.cpp\"\n#include \"../math/ntt.cpp\"\n\n#include\
    \ \"../datastructure/point_add_rectangle_sum.cpp\"\n#include \"../datastructure/static_rectangle_sum.cpp\"\
    \n\n#include \"../graph/dijkstra.cpp\"\n#include \"../graph/dijkstra_restore.cpp\"\
    \n\n#include \"../math/prime/get_min_factor.cpp\"\n#include \"../math/prime/get_prime.cpp\"\
    \n\n#include \"../geometry/dualgraph.cpp\"\n#include \"../geometry/half_plane_intersection.cpp\"\
    \n\n#include \"../tree/LCA.cpp\"\n#include \"../tree/auxtree.cpp\"\n\nint main()\
    \ {\n    Scanner sc;\n    Printer pr;\n    ll a, b;\n    sc.read(a, b);\n    pr.println(a\
    \ + b);\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - util/modint.cpp
  - util/modint_base.cpp
  - math/ntt.cpp
  - util/modint_base.cpp
  - datastructure/point_add_rectangle_sum.cpp
  - datastructure/binaryindexedtree.cpp
  - datastructure/static_rectangle_sum.cpp
  - graph/dijkstra.cpp
  - graph/dijkstra_common.cpp
  - graph/dijkstra_restore.cpp
  - math/prime/get_min_factor.cpp
  - math/prime/linear_sieve.cpp
  - math/prime/get_prime.cpp
  - geometry/dualgraph.cpp
  - geometry/geometry.cpp
  - geometry/half_plane_intersection.cpp
  - tree/LCA.cpp
  - datastructure/sparsetable.cpp
  - tree/auxtree.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_library_composition.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 20:39:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_library_composition.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_library_composition.test.cpp
- /verify/test/yosupo_aplusb_library_composition.test.cpp.html
title: test/yosupo_aplusb_library_composition.test.cpp
---
