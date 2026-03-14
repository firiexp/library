---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/miller_rabin.cpp
    title: "Miller-Rabin\u6CD5(\u78BA\u7387\u7684\u7D20\u6570\u5224\u5B9A)"
  - icon: ':question:'
    path: util/fastio.cpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/primality_test
    links:
    - https://judge.yosupo.jp/problem/primality_test
  bundledCode: "#line 1 \"test/yosupo_primality_test.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/primality_test\"\n\n#include <cstdint>\n#include\
    \ <vector>\n\nusing ull = unsigned long long;\nusing namespace std;\n\n#include\
    \ <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\n\
    #line 1 \"util/fastio.cpp\"\nusing namespace std;\n\nextern \"C\" int fileno(FILE\
    \ *);\nextern \"C\" int isatty(int);\n\ntemplate<class T, class = void>\nstruct\
    \ is_fastio_range : false_type {};\n\ntemplate<class T>\nstruct is_fastio_range<T,\
    \ void_t<decltype(declval<T &>().begin()), decltype(declval<T &>().end())>> :\
    \ true_type {};\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr\
    \ FastIoDigitTable() : num() {\n        for (int i = 0; i < 10000; ++i) {\n  \
    \          int x = i;\n            for (int j = 3; j >= 0; --j) {\n          \
    \      num[i * 4 + j] = char('0' + x % 10);\n                x /= 10;\n      \
    \      }\n        }\n    }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE\
    \ = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n\
    \    int idx, size;\n    bool interactive;\n\n    Scanner() : idx(0), size(0),\
    \ interactive(isatty(fileno(stdin))) {}\n\n    inline void load() {\n        int\
    \ len = size - idx;\n        memmove(buf, buf + idx, len);\n        if (interactive)\
    \ {\n            if (fgets(buf + len, BUFSIZE + 1 - len, stdin)) size = len +\
    \ (int)strlen(buf + len);\n            else size = len;\n        } else {\n  \
    \          size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n    \
    \    }\n        idx = 0;\n        buf[size] = 0;\n    }\n\n    inline void ensure()\
    \ {\n        if (idx + OFFSET > size) load();\n    }\n\n    inline void ensure_interactive()\
    \ {\n        if (idx == size) load();\n    }\n\n    inline char skip() {\n   \
    \     if (interactive) {\n            ensure_interactive();\n            while\
    \ (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n                ensure_interactive();\n\
    \            }\n            return buf[idx++];\n        }\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        return buf[idx++];\n    }\n\n    template<class\
    \ T, typename enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T\
    \ &x) {\n        if (interactive) {\n            char c = skip();\n          \
    \  bool neg = false;\n            if constexpr (is_signed<T>::value) {\n     \
    \           if (c == '-') {\n                    neg = true;\n               \
    \     ensure_interactive();\n                    c = buf[idx++];\n           \
    \     }\n            }\n            x = 0;\n            while (c >= '0') {\n \
    \               x = x * 10 + (c & 15);\n                ensure_interactive();\n\
    \                c = buf[idx++];\n            }\n            if constexpr (is_signed<T>::value)\
    \ {\n                if (neg) x = -x;\n            }\n            return;\n  \
    \      }\n        char c = skip();\n        bool neg = false;\n        if constexpr\
    \ (is_signed<T>::value) {\n            if (c == '-') {\n                neg =\
    \ true;\n                c = buf[idx++];\n            }\n        }\n        x\
    \ = 0;\n        while (c >= '0') {\n            x = x * 10 + (c & 15);\n     \
    \       c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class Head,\
    \ class Next, class... Tail>\n    void read(Head &head, Next &next, Tail &...tail)\
    \ {\n        read(head);\n        read(next, tail...);\n    }\n\n    template<class\
    \ T, class U>\n    void read(pair<T, U> &p) {\n        read(p.first, p.second);\n\
    \    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
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
    \  }\n\n    inline void write_range(const char *s, size_t n) {\n        size_t\
    \ pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n\
    \            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n         \
    \   memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n     \
    \       pos += chunk;\n        }\n    }\n\n    void write(const char *s) {\n \
    \       write_range(s, strlen(s));\n    }\n\n    void write(const string &s) {\n\
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
    \ T, typename enable_if<is_fastio_range<T>::value && !is_same<typename decay<T>::type,\
    \ string>::value, int>::type = 0>\n    void write(const T &a) {\n        bool\
    \ first = true;\n        for (auto &&x : a) {\n            if (!first) pc(' ');\n\
    \            first = false;\n            write(x);\n        }\n    }\n\n    template<class\
    \ T>\n    void writeln(const T &x) {\n        write(x);\n        pc('\\n');\n\
    \    }\n\n    template<class Head, class... Tail>\n    void writeln(const Head\
    \ &head, const Tail &...tail) {\n        write(head);\n        ((pc(' '), write(tail)),\
    \ ...);\n        pc('\\n');\n    }\n\n    void writeln() {\n        pc('\\n');\n\
    \    }\n};\n\ntemplate<class T>\nScanner &operator>>(Scanner &in, T &x) {\n  \
    \  in.read(x);\n    return in;\n}\n\ntemplate<class T>\nPrinter &operator<<(Printer\
    \ &out, const T &x) {\n    out.write(x);\n    return out;\n}\n\n/**\n * @brief\
    \ \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"math/miller_rabin.cpp\"\
    \nusing u128 = __uint128_t;\n\nstruct mod64 {\n    unsigned long long n;\n   \
    \ static unsigned long long mod, inv, r2;\n    mod64() : n(0) {}\n    mod64(unsigned\
    \ long long x) : n(init(x)) {}\n    static unsigned long long init(unsigned long\
    \ long w) {\n        return reduce(u128(w) * r2);\n    }\n    static void set_mod(unsigned\
    \ long long m) {\n        mod = inv = m;\n        for (int i = 0; i < 5; ++i)\
    \ inv *= 2 - inv * m;\n        r2 = -u128(m) % m;\n    }\n    static unsigned\
    \ long long reduce(u128 x) {\n        unsigned long long y =\n            static_cast<unsigned\
    \ long long>(x >> 64)\n            - static_cast<unsigned long long>((u128(static_cast<unsigned\
    \ long long>(x) * inv) * mod) >> 64);\n        return (long long)y < 0 ? y + mod\
    \ : y;\n    }\n    mod64& operator*=(mod64 x) {\n        n = reduce(u128(n) *\
    \ x.n);\n        return *this;\n    }\n    mod64 operator*(mod64 x) const {\n\
    \        return mod64(*this) *= x;\n    }\n    mod64& operator+=(mod64 x) {\n\
    \        n += x.n - mod;\n        if((long long)n < 0) n += mod;\n        return\
    \ *this;\n    }\n    mod64 operator+(mod64 x) const {\n        return mod64(*this)\
    \ += x;\n    }\n    unsigned long long val() const {\n        return reduce(n);\n\
    \    }\n};\n\nunsigned long long mod64::mod, mod64::inv, mod64::r2;\n\nbool suspect(unsigned\
    \ long long a, unsigned long long s, unsigned long long d, unsigned long long\
    \ n){\n    if(mod64::mod != n) mod64::set_mod(n);\n    mod64 x(1), xx(a), one(1),\
    \ minusone(n - 1);\n    while(d > 0){\n        if(d & 1) x *= xx;\n        xx\
    \ *= xx;\n        d >>= 1;\n    }\n    if (x.n == one.n) return true;\n    for\
    \ (unsigned long long r = 0; r < s; ++r) {\n        if(x.n == minusone.n) return\
    \ true;\n        x *= x;\n    }\n    return false;\n}\n\ntemplate<class T>\nbool\
    \ miller_rabin(T m){\n    unsigned long long n = m;\n    if (n <= 1 || (n > 2\
    \ && n % 2 == 0)) return false;\n    if (n == 2 || n == 3 || n == 5 || n == 7)\
    \ return true;\n    if (n % 3 == 0 || n % 5 == 0 || n % 7 == 0) return false;\n\
    \    unsigned long long d = n - 1, s = 0;\n    while (!(d & 1)) { ++s; d >>= 1;\
    \ }\n    static constexpr unsigned long long small[] = {2, 7, 61};\n    static\
    \ constexpr unsigned long long large[] = {2, 325, 9375, 28178, 450775, 9780504,\
    \ 1795265022};\n    if(n < 4759123141ULL) {\n        for (auto p : small) {\n\
    \            if(p >= n) break;\n            if(!suspect(p, s, d, n)) return false;\n\
    \        }\n    } else {\n        for (auto p : large) {\n            if(p >=\
    \ n) break;\n            if(!suspect(p, s, d, n)) return false;\n        }\n \
    \   }\n    return true;\n}\n\n/**\n * @brief Miller-Rabin\u7D20\u6570\u5224\u5B9A\
    \n */\n#line 16 \"test/yosupo_primality_test.test.cpp\"\n\nint main() {\n    Scanner\
    \ sc;\n    Printer pr;\n    int q;\n    sc.read(q);\n    while (q--) {\n     \
    \   ull n;\n        sc.read(n);\n        pr.writeln(miller_rabin(n) ? \"Yes\"\
    \ : \"No\");\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/primality_test\"\n\n#include\
    \ <cstdint>\n#include <vector>\n\nusing ull = unsigned long long;\nusing namespace\
    \ std;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\
    \n#include \"../util/fastio.cpp\"\n#include \"../math/miller_rabin.cpp\"\n\nint\
    \ main() {\n    Scanner sc;\n    Printer pr;\n    int q;\n    sc.read(q);\n  \
    \  while (q--) {\n        ull n;\n        sc.read(n);\n        pr.writeln(miller_rabin(n)\
    \ ? \"Yes\" : \"No\");\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - math/miller_rabin.cpp
  isVerificationFile: true
  path: test/yosupo_primality_test.test.cpp
  requiredBy: []
  timestamp: '2026-03-14 13:04:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_primality_test.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_primality_test.test.cpp
- /verify/test/yosupo_primality_test.test.cpp.html
title: test/yosupo_primality_test.test.cpp
---
