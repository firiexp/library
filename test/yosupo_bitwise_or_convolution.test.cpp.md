---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/or_convolution.cpp
    title: Bitwise OR Convolution
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
    PROBLEM: https://judge.yosupo.jp/problem/bitwise_and_convolution
    links:
    - https://judge.yosupo.jp/problem/bitwise_and_convolution
  bundledCode: "#line 1 \"test/yosupo_bitwise_or_convolution.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\n\n#include <bits/stdc++.h>\n\
    \nstatic const int MOD = 998244353;\nusing ll = long long;\nusing uint = unsigned;\n\
    using ull = unsigned long long;\nusing namespace std;\n\n#line 14 \"test/yosupo_bitwise_or_convolution.test.cpp\"\
    \n#include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\
    \nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\ntemplate<class\
    \ T, class = void>\nstruct is_fastio_range : false_type {};\n\ntemplate<class\
    \ T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()), decltype(declval<T\
    \ &>().end())>> : true_type {};\n\ntemplate<class T, class = void>\nstruct has_fastio_value\
    \ : false_type {};\n\ntemplate<class T>\nstruct has_fastio_value<T, void_t<decltype(declval<const\
    \ T &>().value())>> : true_type {};\n\nstruct FastIoDigitTable {\n    char num[40000];\n\
    \n    constexpr FastIoDigitTable() : num() {\n        for (int i = 0; i < 10000;\
    \ ++i) {\n            int x = i;\n            for (int j = 3; j >= 0; --j) {\n\
    \                num[i * 4 + j] = char('0' + x % 10);\n                x /= 10;\n\
    \            }\n        }\n    }\n};\n\nstruct Scanner {\n    static constexpr\
    \ int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE\
    \ + 1];\n    int idx, size;\n    bool interactive;\n\n    Scanner() : idx(0),\
    \ size(0), interactive(isatty(fileno(stdin))) {}\n\n    inline void load() {\n\
    \        int len = size - idx;\n        memmove(buf, buf + idx, len);\n      \
    \  if (interactive) {\n            if (fgets(buf + len, BUFSIZE + 1 - len, stdin))\
    \ size = len + (int)strlen(buf + len);\n            else size = len;\n       \
    \ } else {\n            size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n\
    \        }\n        idx = 0;\n        buf[size] = 0;\n    }\n\n    inline void\
    \ ensure() {\n        if (idx + OFFSET > size) load();\n    }\n\n    inline void\
    \ ensure_interactive() {\n        if (idx == size) load();\n    }\n\n    inline\
    \ char skip() {\n        if (interactive) {\n            ensure_interactive();\n\
    \            while (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n \
    \               ensure_interactive();\n            }\n            return buf[idx++];\n\
    \        }\n        ensure();\n        while (buf[idx] && buf[idx] <= ' ') {\n\
    \            ++idx;\n            ensure();\n        }\n        return buf[idx++];\n\
    \    }\n\n    template<class T, typename enable_if<is_integral<T>::value, int>::type\
    \ = 0>\n    void read(T &x) {\n        if (interactive) {\n            char c\
    \ = skip();\n            bool neg = false;\n            if constexpr (is_signed<T>::value)\
    \ {\n                if (c == '-') {\n                    neg = true;\n      \
    \              ensure_interactive();\n                    c = buf[idx++];\n  \
    \              }\n            }\n            x = 0;\n            while (c >= '0')\
    \ {\n                x = x * 10 + (c & 15);\n                ensure_interactive();\n\
    \                c = buf[idx++];\n            }\n            if constexpr (is_signed<T>::value)\
    \ {\n                if (neg) x = -x;\n            }\n            return;\n  \
    \      }\n        char c = skip();\n        bool neg = false;\n        if constexpr\
    \ (is_signed<T>::value) {\n            if (c == '-') {\n                neg =\
    \ true;\n                c = buf[idx++];\n            }\n        }\n        x\
    \ = 0;\n        while (c >= '0') {\n            x = x * 10 + (c & 15);\n     \
    \       c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class T, typename\
    \ enable_if<!is_integral<T>::value && !is_fastio_range<T>::value && !is_same<typename\
    \ decay<T>::type, string>::value && has_fastio_value<T>::value, int>::type = 0>\n\
    \    void read(T &x) {\n        long long v;\n        read(v);\n        x = T(v);\n\
    \    }\n\n    template<class Head, class Next, class... Tail>\n    void read(Head\
    \ &head, Next &next, Tail &...tail) {\n        read(head);\n        read(next,\
    \ tail...);\n    }\n\n    template<class T, class U>\n    void read(pair<T, U>\
    \ &p) {\n        read(p.first, p.second);\n    }\n\n    template<class T, typename\
    \ enable_if<is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value,\
    \ int>::type = 0>\n    void read(T &a) {\n        for (auto &x : a) read(x);\n\
    \    }\n\n    void read(char &c) {\n        c = skip();\n    }\n\n    void read(string\
    \ &s) {\n        s.clear();\n        if (interactive) {\n            ensure_interactive();\n\
    \            while (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n \
    \               ensure_interactive();\n            }\n            while (true)\
    \ {\n                int start = idx;\n                while (idx < size && buf[idx]\
    \ > ' ') ++idx;\n                s.append(buf + start, idx - start);\n       \
    \         if (idx < size) break;\n                load();\n                if\
    \ (size == 0) break;\n            }\n            if (idx < size) ++idx;\n    \
    \        return;\n        }\n        ensure();\n        while (buf[idx] && buf[idx]\
    \ <= ' ') {\n            ++idx;\n            ensure();\n        }\n        while\
    \ (true) {\n            int start = idx;\n            while (idx < size && buf[idx]\
    \ > ' ') ++idx;\n            s.append(buf + start, idx - start);\n           \
    \ if (idx < size) break;\n            load();\n        }\n        if (idx < size)\
    \ ++idx;\n    }\n};\n\nstruct Printer {\n    static constexpr int BUFSIZE = 1\
    \ << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE];\n    int\
    \ idx;\n    bool interactive;\n    inline static constexpr FastIoDigitTable table{};\n\
    \n    Printer() : idx(0), interactive(isatty(fileno(stdout))) {}\n    ~Printer()\
    \ { flush(); }\n\n    inline void flush() {\n        if (idx) {\n            fwrite(buf,\
    \ 1, idx, stdout);\n            idx = 0;\n        }\n    }\n\n    inline void\
    \ pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++]\
    \ = c;\n        if (interactive && c == '\\n') flush();\n    }\n\n    inline void\
    \ print_range(const char *s, size_t n) {\n        size_t pos = 0;\n        while\
    \ (pos < n) {\n            if (idx == BUFSIZE) flush();\n            size_t chunk\
    \ = min(n - pos, (size_t)(BUFSIZE - idx));\n            memcpy(buf + idx, s +\
    \ pos, chunk);\n            idx += (int)chunk;\n            pos += chunk;\n  \
    \      }\n    }\n\n    void print(const char *s) {\n        print_range(s, strlen(s));\n\
    \    }\n\n    void print(const string &s) {\n        print_range(s.data(), s.size());\n\
    \    }\n\n    void print(char c) {\n        pc(c);\n    }\n\n    void print(bool\
    \ b) {\n        pc(char('0' + (b ? 1 : 0)));\n    }\n\n    template<class T, typename\
    \ enable_if<is_integral<T>::value && !is_same<T, bool>::value, int>::type = 0>\n\
    \    void print(T x) {\n        if (idx > BUFSIZE - 100) flush();\n        using\
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
    \ += TMP_SIZE - pos;\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && has_fastio_value<T>::value, int>::type = 0>\n    void print(const T &x) {\n\
    \        print(x.value());\n    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value\
    \ && !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
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
    \ */\n#line 1 \"util/modint.cpp\"\n\n\n\ntemplate <uint Mod>\nstruct modint {\n\
    \    uint val;\npublic:\n    static modint raw(int v) { modint x; x.val = v; return\
    \ x; }\n    static constexpr uint get_mod() { return Mod; }\n    static constexpr\
    \ uint M() { return Mod; }\n    modint() : val(0) {}\n    template <class T>\n\
    \    modint(T v) { ll x = (ll)(v % (ll)(Mod)); if (x < 0) x += Mod; val = uint(x);\
    \ }\n    modint(bool v) { val = ((unsigned int)(v) % Mod); }\n    uint &value()\
    \ noexcept { return val; }\n    const uint &value() const noexcept { return val;\
    \ }\n    modint& operator++() { val++; if (val == Mod) val = 0; return *this;\
    \ }\n    modint& operator--() { if (val == 0) val = Mod; val--; return *this;\
    \ }\n    modint operator++(int) { modint result = *this; ++*this; return result;\
    \ }\n    modint operator--(int) { modint result = *this; --*this; return result;\
    \ }\n    modint& operator+=(const modint& b) { val += b.val; if (val >= Mod) val\
    \ -= Mod; return *this; }\n    modint& operator-=(const modint& b) { val -= b.val;\
    \ if (val >= Mod) val += Mod; return *this; }\n    modint& operator*=(const modint&\
    \ b) { ull z = val; z *= b.val; val = (uint)(z % Mod); return *this; }\n    modint&\
    \ operator/=(const modint& b) { return *this = *this * b.inv(); }\n    modint\
    \ operator+() const { return *this; }\n    modint operator-() const { return modint()\
    \ - *this; }\n    modint pow(long long n) const { modint x = *this, r = 1; while\
    \ (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n    modint inv() const\
    \ { return pow(Mod - 2); }\n    friend modint operator+(const modint& a, const\
    \ modint& b) { return modint(a) += b; }\n    friend modint operator-(const modint&\
    \ a, const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    #define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\n/**\n * @brief modint(\u56FA\u5B9A\
    MOD)\n */\n\n\n#line 1 \"math/or_convolution.cpp\"\ntemplate<class T>\nvoid subset_zeta_transform(vector<T>\
    \ &v){\n    int n = 1;\n    while (n < (int)v.size()) n <<= 1;\n    v.resize(n);\n\
    \    for (int i = 1; i < n; i <<= 1) {\n        for (int s = 0; s < n; ++s) {\n\
    \            if ((s & i) == 0) v[s | i] += v[s];\n        }\n    }\n}\n\ntemplate<class\
    \ T>\nvoid subset_mobius_transform(vector<T> &v){\n    int n = 1;\n    while (n\
    \ < (int)v.size()) n <<= 1;\n    v.resize(n);\n    for (int i = 1; i < n; i <<=\
    \ 1) {\n        for (int s = 0; s < n; ++s) {\n            if ((s & i) == 0) v[s\
    \ | i] -= v[s];\n        }\n    }\n}\n\ntemplate<class T>\nvector<T> or_convolution(vector<T>\
    \ a, vector<T> b){\n    int n = 1;\n    while (n < (int)a.size() || n < (int)b.size())\
    \ n <<= 1;\n    a.resize(n);\n    b.resize(n);\n    subset_zeta_transform(a);\n\
    \    subset_zeta_transform(b);\n    for (int i = 0; i < n; ++i) a[i] *= b[i];\n\
    \    subset_mobius_transform(a);\n    return a;\n}\n\n/**\n * @brief OR\u7573\u307F\
    \u8FBC\u307F(Bitwise OR Convolution)\n */\n#line 19 \"test/yosupo_bitwise_or_convolution.test.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int n;\n    sc.read(n);\n\
    \    int m = 1 << n;\n    int full = m - 1;\n    vector<mint> a(m), b(m);\n  \
    \  for (int i = 0; i < m; ++i) {\n        int x;\n        sc.read(x);\n      \
    \  a[full ^ i] = x;\n    }\n    for (int i = 0; i < m; ++i) {\n        int x;\n\
    \        sc.read(x);\n        b[full ^ i] = x;\n    }\n    auto c = or_convolution(a,\
    \ b);\n    for (int i = 0; i < m; ++i) {\n        if (i) pr.print(' ');\n    \
    \    pr.print(c[full ^ i].val);\n    }\n    pr.println();\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\
    \n\n#include <bits/stdc++.h>\n\nstatic const int MOD = 998244353;\nusing ll =\
    \ long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\nusing namespace\
    \ std;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\
    \n#include \"../util/fastio.cpp\"\n#include \"../util/modint.cpp\"\n#include \"\
    ../math/or_convolution.cpp\"\n\nint main() {\n    Scanner sc;\n    Printer pr;\n\
    \n    int n;\n    sc.read(n);\n    int m = 1 << n;\n    int full = m - 1;\n  \
    \  vector<mint> a(m), b(m);\n    for (int i = 0; i < m; ++i) {\n        int x;\n\
    \        sc.read(x);\n        a[full ^ i] = x;\n    }\n    for (int i = 0; i <\
    \ m; ++i) {\n        int x;\n        sc.read(x);\n        b[full ^ i] = x;\n \
    \   }\n    auto c = or_convolution(a, b);\n    for (int i = 0; i < m; ++i) {\n\
    \        if (i) pr.print(' ');\n        pr.print(c[full ^ i].val);\n    }\n  \
    \  pr.println();\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - util/modint.cpp
  - math/or_convolution.cpp
  isVerificationFile: true
  path: test/yosupo_bitwise_or_convolution.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 13:47:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_bitwise_or_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_bitwise_or_convolution.test.cpp
- /verify/test/yosupo_bitwise_or_convolution.test.cpp.html
title: test/yosupo_bitwise_or_convolution.test.cpp
---
