---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: math/mod_sqrt.cpp
    title: Mod Sqrt
  - icon: ':question:'
    path: util/fastio.cpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sqrt_mod
    links:
    - https://judge.yosupo.jp/problem/sqrt_mod
  bundledCode: "#line 1 \"test/yosupo_sqrt_mod.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/sqrt_mod\"\
    \n\n#line 1 \"util/fastio.cpp\"\n#include <cstdio>\n#include <cstring>\n#include\
    \ <string>\n#include <type_traits>\nusing namespace std;\n\nstruct FastIoDigitTable\
    \ {\n    char num[40000];\n\n    constexpr FastIoDigitTable() : num() {\n    \
    \    for (int i = 0; i < 10000; ++i) {\n            int x = i;\n            for\
    \ (int j = 3; j >= 0; --j) {\n                num[i * 4 + j] = char('0' + x %\
    \ 10);\n                x /= 10;\n            }\n        }\n    }\n};\n\nstruct\
    \ Scanner {\n    static constexpr int BUFSIZE = 1 << 17;\n    static constexpr\
    \ int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n    int idx, size;\n\n    Scanner()\
    \ : idx(0), size(0) {}\n\n    inline void load() {\n        int len = size - idx;\n\
    \        memmove(buf, buf + idx, len);\n        size = len + (int)fread(buf +\
    \ len, 1, BUFSIZE - len, stdin);\n        idx = 0;\n        buf[size] = 0;\n \
    \   }\n\n    inline void ensure() {\n        if (idx + OFFSET > size) load();\n\
    \    }\n\n    inline char skip() {\n        ensure();\n        while (buf[idx]\
    \ && buf[idx] <= ' ') {\n            ++idx;\n            ensure();\n        }\n\
    \        return buf[idx++];\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value,\
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
    \ @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"math/mod_sqrt.cpp\"\
    \nlong long mod_pow(long long a, long long n, long long mod) {\n    long long\
    \ r = 1;\n    while (n) {\n        if (n & 1) r = (unsigned long long)r * a %\
    \ mod;\n        a = (unsigned long long)a * a % mod;\n        n >>= 1;\n    }\n\
    \    return r;\n}\n\nlong long mod_sqrt(long long a, long long p) {\n    a %=\
    \ p;\n    if (a < 0) a += p;\n    if (a == 0 || p == 2) return a;\n    if (mod_pow(a,\
    \ (p - 1) >> 1, p) != 1) return -1;\n    if (p % 4 == 3) return mod_pow(a, (p\
    \ + 1) >> 2, p);\n\n    long long q = p - 1;\n    int s = 0;\n    while ((q &\
    \ 1) == 0) {\n        ++s;\n        q >>= 1;\n    }\n    long long z = 2;\n  \
    \  while (mod_pow(z, (p - 1) >> 1, p) == 1) ++z;\n    long long c = mod_pow(z,\
    \ q, p);\n    long long t = mod_pow(a, q, p);\n    long long r = mod_pow(a, (q\
    \ + 1) >> 1, p);\n    int m = s;\n    while (t != 1) {\n        int i = 1;\n \
    \       long long tt = (unsigned long long)t * t % p;\n        while (i < m &&\
    \ tt != 1) {\n            tt = (unsigned long long)tt * tt % p;\n            ++i;\n\
    \        }\n        long long b = mod_pow(c, 1LL << (m - i - 1), p);\n       \
    \ r = (unsigned long long)r * b % p;\n        c = (unsigned long long)b * b %\
    \ p;\n        t = (unsigned long long)t * c % p;\n        m = i;\n    }\n    return\
    \ r;\n}\n\n/**\n * @brief \u5E73\u65B9\u6839(mod p)(Modular Square Root)\n */\n\
    #line 5 \"test/yosupo_sqrt_mod.test.cpp\"\n\nint main() {\n    Scanner sc;\n \
    \   Printer pr;\n    int t;\n    sc.read(t);\n    while (t--) {\n        long\
    \ long y, p;\n        sc.read(y, p);\n        pr.writeln(mod_sqrt(y, p));\n  \
    \  }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sqrt_mod\"\n\n#include\
    \ \"../util/fastio.cpp\"\n#include \"../math/mod_sqrt.cpp\"\n\nint main() {\n\
    \    Scanner sc;\n    Printer pr;\n    int t;\n    sc.read(t);\n    while (t--)\
    \ {\n        long long y, p;\n        sc.read(y, p);\n        pr.writeln(mod_sqrt(y,\
    \ p));\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - math/mod_sqrt.cpp
  isVerificationFile: true
  path: test/yosupo_sqrt_mod.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yosupo_sqrt_mod.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_sqrt_mod.test.cpp
- /verify/test/yosupo_sqrt_mod.test.cpp.html
title: test/yosupo_sqrt_mod.test.cpp
---
