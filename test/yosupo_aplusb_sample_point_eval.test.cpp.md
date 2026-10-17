---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fps/sample_point_eval.cpp
    title: "\u9023\u7D9A\u6A19\u672C\u70B9\u304B\u3089\u306E1\u70B9\u8A55\u4FA1"
  - icon: ':heavy_check_mark:'
    path: math/factorial.cpp
    title: "\u968E\u4E57\u30FB\u4E8C\u9805\u4FC2\u6570(Factorial)"
  - icon: ':heavy_check_mark:'
    path: math/factorial.cpp
    title: "\u968E\u4E57\u30FB\u4E8C\u9805\u4FC2\u6570(Factorial)"
  - icon: ':question:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_sample_point_eval.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing ll = long long;\nusing uint = unsigned;\nusing ull\
    \ = unsigned long long;\nconst int MOD = 1000000007;\n#line 1 \"util/fastio.cpp\"\
    \nusing namespace std;\n\nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\
    \ntemplate<class T, class = void>\nstruct is_fastio_range : false_type {};\n\n\
    template<class T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()),\
    \ decltype(declval<T &>().end())>> : true_type {};\n\ntemplate<class T, class\
    \ = void>\nstruct has_fastio_value : false_type {};\n\ntemplate<class T>\nstruct\
    \ has_fastio_value<T, void_t<decltype(declval<const T &>().value())>> : true_type\
    \ {};\n\ntemplate<class T, class = void>\nstruct has_fastio_assign_string : false_type\
    \ {};\n\ntemplate<class T>\nstruct has_fastio_assign_string<T, void_t<decltype(declval<T\
    \ &>().assign(declval<const string &>()))>> : true_type {};\n\ntemplate<class\
    \ T, class = void>\nstruct has_fastio_to_string : false_type {};\n\ntemplate<class\
    \ T>\nstruct has_fastio_to_string<T, void_t<decltype(declval<const T &>().to_string())>>\
    \ : true_type {};\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr\
    \ FastIoDigitTable() : num() {\n        for (int i = 0; i < 10000; ++i) {\n  \
    \          int x = i;\n            for (int j = 3; j >= 0; --j) {\n          \
    \      num[i * 4 + j] = char('0' + x % 10);\n                x /= 10;\n      \
    \      }\n        }\n    }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE\
    \ = 1 << 17;\n    static constexpr int OFFSET = 64;\n    static constexpr int\
    \ LONG_TOKEN_SAMPLE_SIZE = 1024;\n    static constexpr int LONG_TOKEN_MIN_DIGITS\
    \ = 16;\n    char buf[BUFSIZE + 1];\n    int idx, size;\n    bool interactive,\
    \ long_tokens;\n    string number_token;\n\n    Scanner() : idx(0), size(0), interactive(isatty(fileno(stdin))),\
    \ long_tokens(false) {}\n\n    __attribute__((always_inline))\n    static inline\
    \ unsigned parse_eight_digits(const char *p) {\n        unsigned long long value;\n\
    \        memcpy(&value, p, 8);\n#if defined(__BYTE_ORDER__) && __BYTE_ORDER__\
    \ == __ORDER_BIG_ENDIAN__\n        value = __builtin_bswap64(value);\n#endif\n\
    \        value -= 0x3030303030303030ULL;\n        value = (value * 10 + (value\
    \ >> 8)) & 0x00ff00ff00ff00ffULL;\n        value = (value * 100 + (value >> 16))\
    \ & 0x0000ffff0000ffffULL;\n        value = (value * 10000 + (value >> 32)) &\
    \ 0x00000000ffffffffULL;\n        return (unsigned)value;\n    }\n\n    __attribute__((always_inline))\n\
    \    static inline bool are_eight_digits(const char *p) {\n        unsigned long\
    \ long value;\n        memcpy(&value, p, 8);\n        return (((value + 0x4646464646464646ULL)\
    \ | (value - 0x3030303030303030ULL)) & 0x8080808080808080ULL) == 0;\n    }\n\n\
    \    template<class U>\n    __attribute__((noinline))\n    U read_long_digits(char\
    \ c) {\n        const char *p = buf + idx - 1;\n        const char *end = buf\
    \ + size;\n        U value = 0;\n        if (c >= '0' && end - p >= 16 && p[15]\
    \ >= '0' && are_eight_digits(p) && are_eight_digits(p + 8)) {\n            value\
    \ = (U)parse_eight_digits(p) * 100000000 + parse_eight_digits(p + 8);\n      \
    \      p += 16;\n            while (*p >= '0') {\n                value = value\
    \ * 10 + (*p & 15);\n                ++p;\n            }\n            idx = (int)(p\
    \ - buf) + 1;\n            return value;\n        }\n        while (c >= '0')\
    \ {\n            value = value * 10 + (c & 15);\n            c = buf[idx++];\n\
    \        }\n        return value;\n    }\n\n    inline void load() {\n       \
    \ int len = size - idx;\n        memmove(buf, buf + idx, len);\n        if (interactive)\
    \ {\n            if (fgets(buf + len, BUFSIZE + 1 - len, stdin)) size = len +\
    \ (int)strlen(buf + len);\n            else size = len;\n        } else {\n  \
    \          size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n    \
    \        int sample_size = min(size, LONG_TOKEN_SAMPLE_SIZE);\n            int\
    \ separators = 0;\n            int minus_signs = 0;\n            for (int i =\
    \ 0; i < sample_size; ++i) {\n                separators += buf[i] <= ' ';\n \
    \               minus_signs += buf[i] == '-';\n            }\n            // Select\
    \ once per buffer so ordinary short integers avoid the\n            // checks\
    \ and call overhead of the 16-digit SWAR path.\n            long_tokens = separators\
    \ * LONG_TOKEN_MIN_DIGITS < sample_size - minus_signs;\n        }\n        idx\
    \ = 0;\n        buf[size] = 0;\n    }\n\n    inline void ensure() {\n        if\
    \ (idx + OFFSET > size) load();\n    }\n\n    inline void ensure_interactive()\
    \ {\n        if (idx == size) load();\n    }\n\n    inline char skip() {\n   \
    \     if (interactive) {\n            ensure_interactive();\n            while\
    \ (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n                ensure_interactive();\n\
    \            }\n            return buf[idx++];\n        }\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        return buf[idx++];\n    }\n\n    template<class\
    \ T, typename enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T\
    \ &x) {\n        using Base = typename conditional<is_same<T, bool>::value, unsigned,\
    \ T>::type;\n        using U = typename make_unsigned<Base>::type;\n        //\
    \ The unsigned magnitude and -(y - 1) - 1 below also cover min(T).\n        if\
    \ (interactive) {\n            char c = skip();\n            bool neg = false;\n\
    \            if constexpr (is_signed<T>::value) {\n                if (c == '-')\
    \ {\n                    neg = true;\n                    ensure_interactive();\n\
    \                    c = buf[idx++];\n                }\n            }\n     \
    \       U y = 0;\n            while (c >= '0') {\n                y = y * 10 +\
    \ (c & 15);\n                ensure_interactive();\n                c = buf[idx++];\n\
    \            }\n            if constexpr (is_signed<T>::value) {\n           \
    \     if (neg && y) {\n                    x = -static_cast<T>(y - 1);\n     \
    \               --x;\n                    return;\n                }\n       \
    \     }\n            x = static_cast<T>(y);\n            return;\n        }\n\
    \        char c = skip();\n        bool neg = false;\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (c == '-') {\n                neg = true;\n              \
    \  c = buf[idx++];\n            }\n        }\n        U y;\n        if (__builtin_expect(long_tokens,\
    \ false)) {\n            y = read_long_digits<U>(c);\n        } else {\n     \
    \       y = 0;\n            while (c >= '0') {\n                y = y * 10 + (c\
    \ & 15);\n                c = buf[idx++];\n            }\n        }\n        if\
    \ constexpr (is_signed<T>::value) {\n            if (neg && y) {\n           \
    \     x = -static_cast<T>(y - 1);\n                --x;\n                return;\n\
    \            }\n        }\n        x = static_cast<T>(y);\n    }\n\n    void read(double\
    \ &x) {\n        read(number_token);\n        const char *first = number_token.data();\n\
    \        const char *last = first + number_token.size();\n        auto result\
    \ = from_chars(first, last, x);\n        if (result.ec != errc{} || result.ptr\
    \ != last) __builtin_trap();\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && has_fastio_value<T>::value, int>::type = 0>\n    void read(T &x) {\n    \
    \    long long v;\n        read(v);\n        x = T(v);\n    }\n\n    template<class\
    \ T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value && !has_fastio_value<T>::value\
    \ && has_fastio_assign_string<T>::value, int>::type = 0>\n    void read(T &x)\
    \ {\n        string s;\n        read(s);\n        bool ok = x.assign(s);\n   \
    \     if (!ok) __builtin_trap();\n    }\n\n    template<class Head, class Next,\
    \ class... Tail>\n    void read(Head &head, Next &next, Tail &...tail) {\n   \
    \     read(head);\n        read(next, tail...);\n    }\n\n    template<class T,\
    \ class U>\n    void read(pair<T, U> &p) {\n        read(p.first, p.second);\n\
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
    \            if (size == 0) break;\n        }\n        if (idx < size) ++idx;\n\
    \    }\n};\n\nstruct Printer {\n    static constexpr int BUFSIZE = 1 << 17;\n\
    \    static constexpr int OFFSET = 64;\n    static constexpr int DEFAULT_DOUBLE_PRECISION\
    \ = 15;\n    char buf[BUFSIZE];\n    int idx;\n    bool interactive;\n    string\
    \ number_buf;\n    inline static constexpr FastIoDigitTable table{};\n\n    Printer()\
    \ : idx(0), interactive(isatty(fileno(stdout))) {}\n    ~Printer() { flush();\
    \ }\n\n    inline void flush() {\n        if (idx) {\n            fwrite(buf,\
    \ 1, idx, stdout);\n            idx = 0;\n        }\n    }\n\n    inline void\
    \ pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++]\
    \ = c;\n        if (interactive && c == '\\n') flush();\n    }\n\n    inline void\
    \ print_range(const char *s, size_t n) {\n        if (interactive) {\n       \
    \     for (size_t i = 0; i < n; ++i) pc(s[i]);\n            return;\n        }\n\
    \        size_t pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE)\
    \ flush();\n            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n\
    \            memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n\
    \            pos += chunk;\n        }\n    }\n\n    void print(const char *s)\
    \ {\n        print_range(s, strlen(s));\n    }\n\n    void print(const string\
    \ &s) {\n        print_range(s.data(), s.size());\n    }\n\n    void print(char\
    \ c) {\n        pc(c);\n    }\n\n    void print(bool b) {\n        pc(char('0'\
    \ + (b ? 1 : 0)));\n    }\n\n    inline char *write_top(char *out, unsigned x)\
    \ {\n        if (x >= 1000) {\n            memcpy(out, table.num + (x << 2), 4);\n\
    \            return out + 4;\n        }\n        if (x >= 100) {\n           \
    \ memcpy(out, table.num + (x << 2) + 1, 3);\n            return out + 3;\n   \
    \     }\n        if (x >= 10) {\n            unsigned q = (x * 205) >> 11;\n \
    \           out[0] = char('0' + q);\n            out[1] = char('0' + (x - q *\
    \ 10));\n            return out + 2;\n        }\n        *out = char('0' + x);\n\
    \        return out + 1;\n    }\n\n    inline void write_four(char *out, unsigned\
    \ x) {\n        memcpy(out, table.num + (x << 2), 4);\n    }\n\n    inline void\
    \ write_eight(char *out, unsigned x) {\n        unsigned hi = x / 10000;\n   \
    \     unsigned lo = x - hi * 10000;\n        write_four(out, hi);\n        write_four(out\
    \ + 4, lo);\n    }\n\n    inline char *write_u32(char *out, unsigned x) {\n  \
    \      if (x >= 100000000) {\n            unsigned hi = x / 100000000;\n     \
    \       unsigned lo = x - hi * 100000000;\n            out = write_top(out, hi);\n\
    \            write_eight(out, lo);\n            return out + 8;\n        }\n \
    \       if (x >= 10000) {\n            unsigned hi = x / 10000;\n            unsigned\
    \ lo = x - hi * 10000;\n            out = write_top(out, hi);\n            write_four(out,\
    \ lo);\n            return out + 4;\n        }\n        return write_top(out,\
    \ x);\n    }\n\n    __attribute__((noinline))\n    inline char *write_u64(char\
    \ *out, unsigned long long x) {\n        if (x <= 0xffffffffULL) return write_u32(out,\
    \ (unsigned)x);\n        unsigned long long hi = x / 100000000;\n        unsigned\
    \ lo = (unsigned)(x - hi * 100000000);\n        if (hi <= 0xffffffffULL) {\n \
    \           out = write_u32(out, (unsigned)hi);\n            write_eight(out,\
    \ lo);\n            return out + 8;\n        }\n        unsigned top = (unsigned)(hi\
    \ / 100000000);\n        unsigned mid = (unsigned)(hi - (unsigned long long)top\
    \ * 100000000);\n        out = write_u32(out, top);\n        write_eight(out,\
    \ mid);\n        write_eight(out + 8, lo);\n        return out + 16;\n    }\n\n\
    \    template<class T, typename enable_if<is_integral<T>::value && !is_same<T,\
    \ bool>::value, int>::type = 0>\n    void print(T x) {\n        if (idx > BUFSIZE\
    \ - 100) flush();\n        using U = typename make_unsigned<T>::type;\n      \
    \  U y;\n        if constexpr (is_signed<T>::value) {\n            if (x < 0)\
    \ {\n                buf[idx++] = '-';\n                y = U(0) - static_cast<U>(x);\n\
    \            } else {\n                y = static_cast<U>(x);\n            }\n\
    \        } else {\n            y = x;\n        }\n        if (y == 0) {\n    \
    \        buf[idx++] = '0';\n            return;\n        }\n        char *out;\n\
    \        if constexpr (sizeof(U) <= 4) {\n            out = write_u32(buf + idx,\
    \ (unsigned)y);\n        } else if constexpr (sizeof(U) <= 8) {\n            out\
    \ = write_u64(buf + idx, (unsigned long long)y);\n        } else {\n         \
    \   static constexpr int TMP_SIZE = sizeof(U) * 10 / 4;\n            char tmp[TMP_SIZE];\n\
    \            int pos = TMP_SIZE;\n            while (y >= 10000) {\n         \
    \       pos -= 4;\n                memcpy(tmp + pos, table.num + (y % 10000) *\
    \ 4, 4);\n                y /= 10000;\n            }\n            out = write_top(buf\
    \ + idx, (unsigned)y);\n            memcpy(out, tmp + pos, TMP_SIZE - pos);\n\
    \            out += TMP_SIZE - pos;\n        }\n        idx = (int)(out - buf);\n\
    \    }\n\n    void print_fixed(double x, int precision = DEFAULT_DOUBLE_PRECISION)\
    \ {\n        if (precision < 0) __builtin_trap();\n        size_t required = (size_t)precision\
    \ + 512;\n        if (number_buf.size() < required) number_buf.resize(required);\n\
    \        while (true) {\n            char *first = number_buf.data();\n      \
    \      char *last = first + number_buf.size();\n            auto result = to_chars(first,\
    \ last, x, chars_format::fixed, precision);\n            if (result.ec == errc{})\
    \ {\n                print_range(first, result.ptr - first);\n               \
    \ return;\n            }\n            if (result.ec != errc::value_too_large)\
    \ __builtin_trap();\n            size_t next_size = number_buf.size() * 2;\n \
    \           if (next_size <= number_buf.size()) __builtin_trap();\n          \
    \  number_buf.resize(next_size);\n        }\n    }\n\n    void print(double x)\
    \ {\n        print_fixed(x);\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && has_fastio_value<T>::value, int>::type = 0>\n    void print(const T &x) {\n\
    \        print(x.value());\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && !has_fastio_value<T>::value && has_fastio_to_string<T>::value, int>::type\
    \ = 0>\n    void print(const T &x) {\n        print(x.to_string());\n    }\n\n\
    \    template<class T, typename enable_if<is_fastio_range<T>::value && !is_same<typename\
    \ decay<T>::type, string>::value, int>::type = 0>\n    void print(const T &a)\
    \ {\n        bool first = true;\n        for (auto &&x : a) {\n            if\
    \ (!first) pc(' ');\n            first = false;\n            print(x);\n     \
    \   }\n    }\n\n    template<class T>\n    void println(const T &x) {\n      \
    \  print(x);\n        pc('\\n');\n    }\n\n    template<class Head, class... Tail>\n\
    \    void println(const Head &head, const Tail &...tail) {\n        print(head);\n\
    \        ((pc(' '), print(tail)), ...);\n        pc('\\n');\n    }\n\n    void\
    \ println_fixed(double x, int precision = DEFAULT_DOUBLE_PRECISION) {\n      \
    \  print_fixed(x, precision);\n        pc('\\n');\n    }\n\n    void println()\
    \ {\n        pc('\\n');\n    }\n};\n\ntemplate<class T>\nScanner &operator>>(Scanner\
    \ &in, T &x) {\n    in.read(x);\n    return in;\n}\n\ntemplate<class T>\nPrinter\
    \ &operator<<(Printer &out, const T &x) {\n    out.print(x);\n    return out;\n\
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"math/factorial.cpp\"\
    \n\n\n\n#line 1 \"util/modint_base.cpp\"\n\n\n\ntemplate <uint Mod>\nstruct modint\
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
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\n\n\n#line 5 \"math/factorial.cpp\"\
    \n\n#ifndef FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\nusing mint = modint<MOD>;\n#define\
    \ FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n#endif\n\ntemplate <class Mint = mint>\n\
    class Factorial {\n    inline static vector<Mint> facts, factinv, invs;\n\n  \
    \  static void init() {\n        if (!facts.empty()) return;\n        facts.push_back(Mint(1));\n\
    \        factinv.push_back(Mint(1));\n        invs.push_back(Mint(0));\n     \
    \   invs.push_back(Mint(1));\n    }\n\n    static void expand(int n) {\n     \
    \   init();\n        if (n < (int)facts.size()) return;\n        int old = facts.size();\n\
    \        int mod = Mint::get_mod();\n        facts.resize(n + 1);\n        factinv.resize(n\
    \ + 1);\n        invs.resize(n + 1);\n        for (int i = max(2, old); i <= n;\
    \ ++i) {\n            invs[i] = -Mint(mod / i) * invs[mod % i];\n        }\n \
    \       for (int i = old; i <= n; ++i) {\n            facts[i] = facts[i - 1]\
    \ * Mint(i);\n            factinv[i] = factinv[i - 1] * invs[i];\n        }\n\
    \    }\npublic:\n    explicit Factorial(int n = 0) {\n        expand(n);\n   \
    \ }\n    void ensure(int n) const {\n        if (n >= 0) expand(n);\n    }\n \
    \   int max_n() const {\n        init();\n        return (int)facts.size() - 1;\n\
    \    }\n    Mint fact(int k) const {\n        if (k < 0) return inv_fact(-k);\n\
    \        expand(k);\n        return facts[k];\n    }\n    Mint inv_fact(int k)\
    \ const {\n        if (k < 0) return 0;\n        expand(k);\n        return factinv[k];\n\
    \    }\n    Mint inv(int k) const {\n        if (k < 0) return 0;\n        expand(k);\n\
    \        return invs[k];\n    }\n    Mint operator[](int k) const {\n        return\
    \ k >= 0 ? fact(k) : inv_fact(-k);\n    }\n    Mint C(int n, int k) const {\n\
    \        if (n < 0 || k < 0 || n < k) return 0;\n        expand(n);\n        return\
    \ facts[n] * factinv[k] * factinv[n - k];\n    }\n    Mint P(int n, int k) const\
    \ {\n        if (n < 0 || k < 0 || n < k) return 0;\n        expand(n);\n    \
    \    return facts[n] * factinv[n - k];\n    }\n    Mint H(int n, int k) const\
    \ {\n        if (n < 0 || k < 0) return 0;\n        if (k == 0) return 1;\n  \
    \      if (n == 0) return 0;\n        return C(n + k - 1, k);\n    }\n};\n\n/**\n\
    \ * @brief \u968E\u4E57\u30FB\u4E8C\u9805\u4FC2\u6570(Factorial)\n */\n\n\n#line\
    \ 1 \"fps/sample_point_eval.cpp\"\n\n\n\n#line 5 \"fps/sample_point_eval.cpp\"\
    \n\ntemplate <class Mint>\nMint sample_point_eval(const vector<Mint>& ys, Mint\
    \ x) {\n    int n = ys.size();\n    if (n == 0) return Mint(0);\n    assert(ys.size()\
    \ <= Mint::get_mod());\n    if (x.val < ys.size()) return ys[x.val];\n    Factorial<Mint>\
    \ factorial(n - 1);\n    vector<Mint> prefix(n + 1, Mint(1));\n    for (int i\
    \ = 0; i < n; ++i) prefix[i + 1] = prefix[i] * (x - Mint(i));\n    Mint result\
    \ = 0, suffix = 1;\n    for (int i = n - 1; i >= 0; --i) {\n        Mint term\
    \ = ys[i] * prefix[i] * suffix * factorial.inv_fact(i) * factorial.inv_fact(n\
    \ - 1 - i);\n        if ((n - 1 - i) & 1) result -= term;\n        else result\
    \ += term;\n        suffix *= x - Mint(i);\n    }\n    return result;\n}\n\n\n\
    \n/**\n * @brief \u9023\u7D9A\u6A19\u672C\u70B9\u304B\u3089\u306E1\u70B9\u8A55\
    \u4FA1\n */\n#line 13 \"test/yosupo_aplusb_sample_point_eval.test.cpp\"\n\ntemplate\
    \ <class Mint>\nMint evaluate(const vector<Mint>& f, Mint x) {\n    Mint result\
    \ = 0;\n    for (int i = (int)f.size() - 1; i >= 0; --i) result = result * x +\
    \ f[i];\n    return result;\n}\n\ntemplate <unsigned P>\nvoid check_mod() {\n\
    \    using Mint = modint<P>;\n    mt19937 rng(P);\n    assert(sample_point_eval(vector<Mint>{},\
    \ Mint(P - 1)) == Mint(0));\n    for (int tc = 0; tc < 300; ++tc) {\n        int\
    \ n = tc == 0 ? min(P, 70U) : 1 + rng() % min(P, 70U);\n        vector<Mint> f(n),\
    \ ys(n);\n        for (auto& c : f) c = rng() % P;\n        if (tc == 1) fill(f.begin(),\
    \ f.end(), Mint(0));\n        for (int i = 0; i < n; ++i) ys[i] = evaluate(f,\
    \ Mint(i));\n        auto original = ys;\n        for (int i = 0; i < n; ++i)\
    \ assert(sample_point_eval(ys, Mint(i)) == ys[i]);\n        for (int i = 0; i\
    \ < 12; ++i) {\n            Mint x = i == 0 ? Mint(P - 1) : i == 1 ? Mint(n) :\
    \ Mint(rng() % P);\n            assert(sample_point_eval(ys, x) == evaluate(f,\
    \ x));\n        }\n        assert(ys == original);\n        Factorial<Mint> factorial(n\
    \ - 1);\n        assert(factorial.fact(n - 1) * factorial.inv_fact(n - 1) == Mint(1));\n\
    \    }\n}\n\nint main() {\n    check_mod<2>();\n    check_mod<3>();\n    check_mod<5>();\n\
    \    check_mod<17>();\n    check_mod<998244353>();\n    check_mod<1000000007>();\n\
    \    Scanner in;\n    Printer out;\n    int a, b;\n    in.read(a, b);\n    out.println(a\
    \ + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing ll = long long;\nusing uint = unsigned;\nusing ull\
    \ = unsigned long long;\nconst int MOD = 1000000007;\n#include \"../util/fastio.cpp\"\
    \n#include \"../math/factorial.cpp\"\n#include \"../fps/sample_point_eval.cpp\"\
    \n#include \"../math/factorial.cpp\"\n\ntemplate <class Mint>\nMint evaluate(const\
    \ vector<Mint>& f, Mint x) {\n    Mint result = 0;\n    for (int i = (int)f.size()\
    \ - 1; i >= 0; --i) result = result * x + f[i];\n    return result;\n}\n\ntemplate\
    \ <unsigned P>\nvoid check_mod() {\n    using Mint = modint<P>;\n    mt19937 rng(P);\n\
    \    assert(sample_point_eval(vector<Mint>{}, Mint(P - 1)) == Mint(0));\n    for\
    \ (int tc = 0; tc < 300; ++tc) {\n        int n = tc == 0 ? min(P, 70U) : 1 +\
    \ rng() % min(P, 70U);\n        vector<Mint> f(n), ys(n);\n        for (auto&\
    \ c : f) c = rng() % P;\n        if (tc == 1) fill(f.begin(), f.end(), Mint(0));\n\
    \        for (int i = 0; i < n; ++i) ys[i] = evaluate(f, Mint(i));\n        auto\
    \ original = ys;\n        for (int i = 0; i < n; ++i) assert(sample_point_eval(ys,\
    \ Mint(i)) == ys[i]);\n        for (int i = 0; i < 12; ++i) {\n            Mint\
    \ x = i == 0 ? Mint(P - 1) : i == 1 ? Mint(n) : Mint(rng() % P);\n           \
    \ assert(sample_point_eval(ys, x) == evaluate(f, x));\n        }\n        assert(ys\
    \ == original);\n        Factorial<Mint> factorial(n - 1);\n        assert(factorial.fact(n\
    \ - 1) * factorial.inv_fact(n - 1) == Mint(1));\n    }\n}\n\nint main() {\n  \
    \  check_mod<2>();\n    check_mod<3>();\n    check_mod<5>();\n    check_mod<17>();\n\
    \    check_mod<998244353>();\n    check_mod<1000000007>();\n    Scanner in;\n\
    \    Printer out;\n    int a, b;\n    in.read(a, b);\n    out.println(a + b);\n\
    }\n"
  dependsOn:
  - util/fastio.cpp
  - math/factorial.cpp
  - util/modint_base.cpp
  - fps/sample_point_eval.cpp
  - math/factorial.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_sample_point_eval.test.cpp
  requiredBy: []
  timestamp: '2026-10-11 14:34:56+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_sample_point_eval.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_sample_point_eval.test.cpp
- /verify/test/yosupo_aplusb_sample_point_eval.test.cpp.html
title: test/yosupo_aplusb_sample_point_eval.test.cpp
---
