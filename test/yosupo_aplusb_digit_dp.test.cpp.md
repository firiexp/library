---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/ahocorasick.cpp
    title: "Aho-Corasick\u6CD5"
  - icon: ':heavy_check_mark:'
    path: math/digit_dfa.cpp
    title: "\u6570\u5B57\u5217\u306E\u6761\u4EF6\u3092\u8868\u3059\u6709\u9650\u30AA\
      \u30FC\u30C8\u30DE\u30C8\u30F3"
  - icon: ':heavy_check_mark:'
    path: math/digit_dp.cpp
    title: "\u4E0A\u4E0B\u9650\u4ED8\u304D\u6841DP\u306E\u500B\u6570\u3068\u7DCF\u548C"
  - icon: ':heavy_check_mark:'
    path: string/avoid_patterns.cpp
    title: "\u7981\u6B62\u90E8\u5206\u6587\u5B57\u5217\u3092\u907F\u3051\u308B\u6709\
      \u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3"
  - icon: ':heavy_check_mark:'
    path: string/dfa.cpp
    title: "\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u3068\u6761\u4EF6\u306E\
      \u5408\u6210"
  - icon: ':heavy_check_mark:'
    path: string/dfa.cpp
    title: "\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u3068\u6761\u4EF6\u306E\
      \u5408\u6210"
  - icon: ':heavy_check_mark:'
    path: string/dfa_minimize.cpp
    title: "\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u306E\u6700\u5C0F\u5316"
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_digit_dp.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n#include <bits/stdc++.h>\nusing\
    \ namespace std;\nusing ll = long long;\nusing uint = unsigned;\nusing ull = unsigned\
    \ long long;\n\n#line 1 \"util/modint_base.cpp\"\n\n\n\ntemplate <uint Mod>\n\
    struct modint {\n    uint val;\npublic:\n    static modint raw(int v) { modint\
    \ x; x.val = v; return x; }\n    static constexpr uint get_mod() { return Mod;\
    \ }\n    static constexpr uint M() { return Mod; }\n    modint() : val(0) {}\n\
    \    template <class T>\n    modint(T v) { ll x = (ll)(v % (ll)(Mod)); if (x <\
    \ 0) x += Mod; val = uint(x); }\n    modint(bool v) { val = ((unsigned int)(v)\
    \ % Mod); }\n    uint &value() noexcept { return val; }\n    const uint &value()\
    \ const noexcept { return val; }\n    modint& operator++() { val++; if (val ==\
    \ Mod) val = 0; return *this; }\n    modint& operator--() { if (val == 0) val\
    \ = Mod; val--; return *this; }\n    modint operator++(int) { modint result =\
    \ *this; ++*this; return result; }\n    modint operator--(int) { modint result\
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
    \ a, const modint& b) { return a.val != b.val; }\n};\n\n\n#line 1 \"util/fastio.cpp\"\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"math/digit_dp.cpp\"\
    \n\n\n\n#line 1 \"string/dfa.cpp\"\n\n\n\ntemplate<int W>\nstruct DFA {\n    vector<array<int,\
    \ W>> next;\n    vector<char> accept;\n    int initial = -1;\n};\n\ntemplate<int\
    \ W>\nDFA<W> intersect(const DFA<W>& a, const DFA<W>& b) {\n    if (a.initial\
    \ == -1 || b.initial == -1) return {};\n    size_t width = b.next.size();\n  \
    \  assert(a.next.size() <= vector<int>().max_size() / width);\n    vector<int>\
    \ id(a.next.size() * width, -1);\n    vector<pair<int, int>> states;\n    DFA<W>\
    \ result;\n    auto add = [&](int x, int y) {\n        int& index = id[size_t(x)\
    \ * width + y];\n        if (index == -1) {\n            index = (int)states.size();\n\
    \            states.emplace_back(x, y);\n            result.next.emplace_back();\n\
    \            result.accept.push_back(a.accept[x] && b.accept[y]);\n        }\n\
    \        return index;\n    };\n    result.initial = add(a.initial, b.initial);\n\
    \    for (int i = 0; i < (int)states.size(); ++i) {\n        auto [x, y] = states[i];\n\
    \        for (int c = 0; c < W; ++c) {\n            int nx = a.next[x][c], ny\
    \ = b.next[y][c];\n            int to = nx == -1 || ny == -1 ? -1 : add(nx, ny);\n\
    \            result.next[i][c] = to;\n        }\n    }\n    return result;\n}\n\
    \ntemplate<int W>\nDFA<W> unite(const DFA<W>& a, const DFA<W>& b) {\n    if (a.initial\
    \ == -1 && b.initial == -1) return {};\n    size_t width = b.next.size() + 1;\n\
    \    assert(a.next.size() + 1 <= vector<int>().max_size() / width);\n    vector<int>\
    \ id((a.next.size() + 1) * width, -1);\n    vector<pair<int, int>> states;\n \
    \   DFA<W> result;\n    auto add = [&](int x, int y) {\n        if (x == -1 &&\
    \ y == -1) return -1;\n        int& index = id[size_t(x + 1) * width + (y + 1)];\n\
    \        if (index == -1) {\n            index = (int)states.size();\n       \
    \     states.emplace_back(x, y);\n            result.next.emplace_back();\n  \
    \          result.accept.push_back((x != -1 && a.accept[x]) || (y != -1 && b.accept[y]));\n\
    \        }\n        return index;\n    };\n    result.initial = add(a.initial,\
    \ b.initial);\n    for (int i = 0; i < (int)states.size(); ++i) {\n        auto\
    \ [x, y] = states[i];\n        for (int c = 0; c < W; ++c) {\n            int\
    \ nx = x == -1 ? -1 : a.next[x][c];\n            int ny = y == -1 ? -1 : b.next[y][c];\n\
    \            int to = add(nx, ny);\n            result.next[i][c] = to;\n    \
    \    }\n    }\n    return result;\n}\n\ntemplate<int W>\nDFA<W> complement(const\
    \ DFA<W>& a) {\n    if (a.initial == -1) {\n        DFA<W> result{vector<array<int,\
    \ W>>(1), {true}, 0};\n        result.next[0].fill(0);\n        return result;\n\
    \    }\n    DFA<W> result = a;\n    for (auto& accept : result.accept) accept\
    \ = !accept;\n    int sink = (int)result.next.size();\n    bool needed = false;\n\
    \    for (auto& row : result.next) {\n        for (int& to : row) if (to == -1)\
    \ {\n            to = sink;\n            needed = true;\n        }\n    }\n  \
    \  if (needed) {\n        result.next.emplace_back();\n        result.next.back().fill(sink);\n\
    \        result.accept.push_back(true);\n    }\n    return result;\n}\n\n\n\n\
    /**\n * @brief \u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u3068\u6761\u4EF6\
    \u306E\u5408\u6210\n */\n#line 5 \"math/digit_dp.cpp\"\n\nnamespace digit_dp_detail\
    \ {\n\ntemplate<class T, bool Sum>\nauto run(const string& lower, const string&\
    \ upper, const DFA<10>& a) {\n    using Value = conditional_t<Sum, pair<T, T>,\
    \ T>;\n    const Value zero = []() -> Value {\n        if constexpr (Sum) return\
    \ {T(0), T(0)};\n        else return T(0);\n    }();\n    auto count = [](Value&\
    \ x) -> T& {\n        if constexpr (Sum) return x.first;\n        else return\
    \ x;\n    };\n    auto empty = [](const Value& x) {\n        if constexpr (Sum)\
    \ return x.first == T(0) && x.second == T(0);\n        else return x == T(0);\n\
    \    };\n    assert(!lower.empty() && !upper.empty());\n    if (a.initial == -1)\
    \ return zero;\n    if (none_of(a.accept.begin(), a.accept.end(), [](char x) {\
    \ return x; })) return zero;\n    string_view l(lower), r(upper);\n    while (l.size()\
    \ > 1 && l.front() == '0') l.remove_prefix(1);\n    while (r.size() > 1 && r.front()\
    \ == '0') r.remove_prefix(1);\n    if (l.size() > r.size() || (l.size() == r.size()\
    \ && l > r)) return zero;\n    int s = (int)a.next.size();\n    vector<Value>\
    \ dp(s, zero), next(s, zero);\n    array<Value, 4> border{zero, zero, zero, zero};\n\
    \    array<int, 4> path{-1, -1, -1, s};\n    count(border[3]) = T(1);\n    bool\
    \ loose = false;\n    vector<int> last;\n    if constexpr (Sum) {\n        last.assign(s,\
    \ -1);\n        for (int v = 0; v < s; ++v) {\n            for (int d = 0; d <\
    \ 10; ++d) if (a.next[v][d] != -1) last[v] = d;\n        }\n    }\n    for (size_t\
    \ i = 0; i < r.size(); ++i) {\n        int ld = i < r.size() - l.size() ? 0 :\
    \ l[i - (r.size() - l.size())] - '0';\n        int rd = r[i] - '0';\n        if\
    \ (loose) fill(next.begin(), next.end(), zero);\n        for (int v = 0; loose\
    \ && v < s; ++v) {\n            const auto& from = dp[v];\n            if (empty(from))\
    \ continue;\n            if constexpr (Sum) {\n                if (last[v] ==\
    \ -1) continue;\n                T sum = from.second * T(10);\n              \
    \  for (int d = 0; d <= last[v]; ++d) {\n                    int to = a.next[v][d];\n\
    \                    if (to != -1) {\n                        next[to].first +=\
    \ from.first;\n                        next[to].second += sum;\n             \
    \       }\n                    if (d != last[v]) sum += from.first;\n        \
    \        }\n            } else {\n                for (int to : a.next[v]) if\
    \ (to != -1) next[to] += from;\n            }\n        }\n        array<Value,\
    \ 4> next_border{zero, zero, zero, zero};\n        array<int, 4> next_path{-1,\
    \ -1, -1, -1};\n        for (int tight = 1; tight < 4; ++tight) {\n          \
    \  int v = path[tight];\n            if (v == -1) continue;\n            int low\
    \ = tight & 1 ? ld : 0;\n            int high = tight & 2 ? rd : 9;\n        \
    \    for (int d = low; d <= high; ++d) {\n                int to = v == s && d\
    \ == 0 ? s : a.next[v == s ? a.initial : v][d];\n                if (to == -1)\
    \ continue;\n                int flags = ((tight & 1) && d == ld) | (((tight &\
    \ 2) && d == rd) << 1);\n                Value value = border[tight];\n      \
    \          if constexpr (Sum) value.second = value.second * T(10) + T(d);\n  \
    \              if (flags) {\n                    next_path[flags] = to;\n    \
    \                next_border[flags] = value;\n                } else {\n     \
    \               assert(to != s);\n                    loose = true;\n        \
    \            count(next[to]) += count(value);\n                    if constexpr\
    \ (Sum) next[to].second += value.second;\n                }\n            }\n \
    \       }\n        dp.swap(next);\n        path = next_path;\n        border =\
    \ next_border;\n    }\n    Value result = zero;\n    int zero_state = a.next[a.initial][0];\n\
    \    for (int v = 0; v < s; ++v) if (a.accept[v]) {\n        count(result) +=\
    \ count(dp[v]);\n        if constexpr (Sum) result.second += dp[v].second;\n \
    \   }\n    for (int tight = 1; tight < 4; ++tight) {\n        int v = path[tight];\n\
    \        if (v == s) v = zero_state;\n        if (v == -1 || !a.accept[v]) continue;\n\
    \        count(result) += count(border[tight]);\n        if constexpr (Sum) result.second\
    \ += border[tight].second;\n    }\n    return result;\n}\n\n}\n\ntemplate<class\
    \ T>\nT digit_count(const string& lower, const string& upper, const DFA<10>& a)\
    \ {\n    return digit_dp_detail::run<T, false>(lower, upper, a);\n}\n\ntemplate<class\
    \ T>\npair<T, T> digit_count_sum(const string& lower, const string& upper, const\
    \ DFA<10>& a) {\n    return digit_dp_detail::run<T, true>(lower, upper, a);\n\
    }\n\n\n\n/**\n * @brief \u4E0A\u4E0B\u9650\u4ED8\u304D\u6841DP\u306E\u500B\u6570\
    \u3068\u7DCF\u548C\n */\n#line 1 \"math/digit_dfa.cpp\"\n\n\n\n#line 5 \"math/digit_dfa.cpp\"\
    \n\nDFA<10> digit_value_mod(int m, int r = 0) {\n    assert(m > 0 && 0 <= r &&\
    \ r < m);\n    DFA<10> a{vector<array<int, 10>>(m), vector<char>(m), 0};\n   \
    \ a.accept[r] = true;\n    for (int v = 0; v < m; ++v) {\n        for (int d =\
    \ 0; d < 10; ++d) a.next[v][d] = (10LL * v + d) % m;\n    }\n    return a;\n}\n\
    \nDFA<10> digit_sum_mod(int m, int r = 0) {\n    assert(m > 0 && 0 <= r && r <\
    \ m);\n    DFA<10> a{vector<array<int, 10>>(m), vector<char>(m), 0};\n    a.accept[r]\
    \ = true;\n    for (int v = 0; v < m; ++v) {\n        for (int d = 0; d < 10;\
    \ ++d) a.next[v][d] = (v + (long long)d) % m;\n    }\n    return a;\n}\n\nDFA<10>\
    \ digit_sum_exact(int k) {\n    assert(0 <= k && k < numeric_limits<int>::max());\n\
    \    DFA<10> a{vector<array<int, 10>>(k + 1), vector<char>(k + 1), 0};\n    a.accept[k]\
    \ = true;\n    for (int v = 0; v <= k; ++v) {\n        for (int d = 0; d < 10;\
    \ ++d) a.next[v][d] = d <= k - v ? v + d : -1;\n    }\n    return a;\n}\n\nDFA<10>\
    \ no_equal_adjacent() {\n    DFA<10> a{vector<array<int, 10>>(11), vector<char>(11,\
    \ true), 10};\n    for (int v = 0; v <= 10; ++v) {\n        for (int d = 0; d\
    \ < 10; ++d) a.next[v][d] = v == d ? -1 : d;\n    }\n    return a;\n}\n\nDFA<10>\
    \ required_digits(int mask) {\n    assert(0 <= mask && mask < (1 << 10));\n  \
    \  array<int, 10> bit{};\n    int n = 1;\n    for (int d = 0; d < 10; ++d) {\n\
    \        if (mask >> d & 1) bit[d] = n, n *= 2;\n    }\n    DFA<10> a{vector<array<int,\
    \ 10>>(n), vector<char>(n), 0};\n    a.accept[n - 1] = true;\n    for (int v =\
    \ 0; v < n; ++v) {\n        for (int d = 0; d < 10; ++d) a.next[v][d] = v | bit[d];\n\
    \    }\n    return a;\n}\n\n\n\n/**\n * @brief \u6570\u5B57\u5217\u306E\u6761\u4EF6\
    \u3092\u8868\u3059\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\n */\n#line\
    \ 1 \"string/avoid_patterns.cpp\"\n\n\n\n#line 1 \"datastructure/ahocorasick.cpp\"\
    \n\n\n\ntemplate<int W, int start>\nclass AhoCorasick {\npublic:\n    struct Node\
    \ {\n        array<int, W> to;\n        int fail;\n        int val;\n    };\n\
    \    explicit AhoCorasick() : v(1) {}\n    vector<Node> v;\n    vector<int> ord;\n\
    \    int add(const string &s, int cur = 0){\n        for (auto &&i : s) {\n  \
    \          if(!v[cur].to[i-start]) v[cur].to[i-start] = v.size(), v.emplace_back();\n\
    \            cur = v[cur].to[i-start];\n        }\n        return cur;\n    }\n\
    \n    void build() {\n        v[0].fail = -1;\n        int l = 0, r = 1;\n   \
    \     ord.clear();\n        ord.reserve(v.size());\n        ord.emplace_back(0);\n\
    \        while(l < r){\n            int i = ord[l]; l++;\n            for (int\
    \ c = 0; c < W; ++c) {\n                if(!v[i].to[c]) continue;\n          \
    \      int to = v[i].to[c];\n                v[to].fail = (v[i].fail == -1 ? 0\
    \ : v[v[i].fail].to[c]);\n                ord.emplace_back(to);\n            \
    \    r++;\n            }\n            if(i != 0){\n                for (int c\
    \ = 0; c < W; ++c) {\n                    if(!v[i].to[c]) v[i].to[c] = v[v[i].fail].to[c];\n\
    \                }\n            }\n        }\n    }\n    inline int next(int x,\
    \ char c){ return v[x].to[c-start]; }\n\n    vector<long long> occurrence_counts(const\
    \ string &text) const {\n        vector<long long> counts(v.size());\n       \
    \ counts[0] = 1;\n        int state = 0;\n        for (char c : text) {\n    \
    \        state = v[state].to[c - start];\n            ++counts[state];\n     \
    \   }\n        for (int i = (int)ord.size() - 1; i > 0; --i) {\n            int\
    \ state = ord[i];\n            counts[v[state].fail] += counts[state];\n     \
    \   }\n        return counts;\n    }\n};\n\n\n\n/**\n * @brief Aho-Corasick\u6CD5\
    \n */\n#line 6 \"string/avoid_patterns.cpp\"\n\ntemplate<int W, int start>\nDFA<W>\
    \ avoid_patterns(const vector<string>& patterns) {\n    AhoCorasick<W, start>\
    \ ac;\n    for (const string& s : patterns) {\n        if (s.empty()) return {};\n\
    \        int v = ac.add(s);\n        ac.v[v].val = 1;\n    }\n    ac.build();\n\
    \    for (int v : ac.ord) {\n        if (v != 0) ac.v[v].val |= ac.v[ac.v[v].fail].val;\n\
    \    }\n    vector<int> id(ac.v.size(), -1), states{0};\n    id[0] = 0;\n    DFA<W>\
    \ result{vector<array<int, W>>(1), vector<char>(1, true), 0};\n    for (int i\
    \ = 0; i < (int)states.size(); ++i) {\n        int v = states[i];\n        for\
    \ (int c = 0; c < W; ++c) {\n            int to = ac.v[v].to[c];\n           \
    \ if (ac.v[to].val) {\n                result.next[i][c] = -1;\n             \
    \   continue;\n            }\n            if (id[to] == -1) {\n              \
    \  id[to] = (int)states.size();\n                states.push_back(to);\n     \
    \           result.next.emplace_back();\n                result.accept.push_back(true);\n\
    \            }\n            result.next[i][c] = id[to];\n        }\n    }\n  \
    \  return result;\n}\n\n\n\n/**\n * @brief \u7981\u6B62\u90E8\u5206\u6587\u5B57\
    \u5217\u3092\u907F\u3051\u308B\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\
    \n */\n#line 1 \"string/dfa_minimize.cpp\"\n\n\n\n#line 5 \"string/dfa_minimize.cpp\"\
    \n\ntemplate<int W>\nDFA<W> minimize(const DFA<W>& a) {\n    if (a.initial ==\
    \ -1) return {};\n    vector<int> index(a.next.size(), -1), states{a.initial};\n\
    \    index[a.initial] = 0;\n    for (size_t i = 0; i < states.size(); ++i) {\n\
    \        for (int to : a.next[states[i]]) {\n            if (to != -1 && index[to]\
    \ == -1) {\n                index[to] = (int)states.size();\n                states.push_back(to);\n\
    \            }\n        }\n    }\n    int sink = (int)states.size();\n    assert(sink\
    \ < numeric_limits<int>::max());\n    int n = sink + 1;\n    vector<int> order;\n\
    \    order.reserve(n);\n    for (int v = 0; v < sink; ++v) if (a.accept[states[v]])\
    \ order.push_back(v);\n    int accepted = (int)order.size();\n    if (accepted\
    \ == 0) return {};\n    for (int v = 0; v < sink; ++v) if (!a.accept[states[v]])\
    \ order.push_back(v);\n    order.push_back(sink);\n    vector<array<int, W>> head(n),\
    \ link(n);\n    for (auto& row : head) row.fill(-1);\n    for (int v = 0; v <\
    \ n; ++v) {\n        for (int c = 0; c < W; ++c) {\n            int to = v ==\
    \ sink ? -1 : a.next[states[v]][c];\n            to = to == -1 ? sink : index[to];\n\
    \            link[v][c] = head[to][c];\n            head[to][c] = v;\n       \
    \ }\n    }\n    vector<int> group(n), position(n), begin{0, accepted}, end{accepted,\
    \ n}, marked{0, accepted};\n    for (int i = 0; i < n; ++i) group[order[i]] =\
    \ i >= accepted, position[order[i]] = i;\n    vector<int> pending{accepted <=\
    \ n - accepted ? 0 : 1}, splitter, touched;\n    while (!pending.empty()) {\n\
    \        int block = pending.back();\n        pending.pop_back();\n        splitter.assign(order.begin()\
    \ + begin[block], order.begin() + end[block]);\n        for (int c = 0; c < W;\
    \ ++c) {\n            touched.clear();\n            for (int to : splitter) {\n\
    \                for (int v = head[to][c]; v != -1; v = link[v][c]) {\n      \
    \              int b = group[v];\n                    if (marked[b] == begin[b])\
    \ touched.push_back(b);\n                    int i = position[v], j = marked[b]++;\n\
    \                    swap(order[i], order[j]);\n                    position[order[i]]\
    \ = i;\n                    position[order[j]] = j;\n                }\n     \
    \       }\n            for (int b : touched) {\n                int mid = marked[b],\
    \ l = begin[b], r = end[b];\n                if (mid != r) {\n               \
    \     int id = (int)begin.size();\n                    if (mid - l <= r - mid)\
    \ {\n                        begin.push_back(l);\n                        end.push_back(mid);\n\
    \                        begin[b] = mid;\n                    } else {\n     \
    \                   begin.push_back(mid);\n                        end.push_back(r);\n\
    \                        end[b] = mid;\n                    }\n              \
    \      marked.push_back(begin[id]);\n                    for (int i = begin[id];\
    \ i < end[id]; ++i) group[order[i]] = id;\n                    pending.push_back(id);\n\
    \                }\n                marked[b] = begin[b];\n            }\n   \
    \     }\n    }\n    int dead = group[sink];\n    if (group[0] == dead) return\
    \ {};\n    vector<int> id(begin.size(), -1), queue{group[0]};\n    id[group[0]]\
    \ = 0;\n    DFA<W> result;\n    result.initial = 0;\n    for (size_t i = 0; i\
    \ < queue.size(); ++i) {\n        int v = states[order[begin[queue[i]]]];\n  \
    \      array<int, W> row;\n        for (int c = 0; c < W; ++c) {\n           \
    \ int to = a.next[v][c];\n            int b = to == -1 ? dead : group[index[to]];\n\
    \            if (b == dead) row[c] = -1;\n            else {\n               \
    \ if (id[b] == -1) {\n                    id[b] = (int)queue.size();\n       \
    \             queue.push_back(b);\n                }\n                row[c] =\
    \ id[b];\n            }\n        }\n        result.next.push_back(row);\n    \
    \    result.accept.push_back(bool(a.accept[v]));\n    }\n    return result;\n\
    }\n\n\n\n/**\n * @brief \u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u306E\
    \u6700\u5C0F\u5316\n */\n#line 14 \"test/yosupo_aplusb_digit_dp.test.cpp\"\n\n\
    struct AddOnly {\n    long long value;\n    explicit AddOnly(long long x) : value(x)\
    \ {}\n    AddOnly& operator+=(AddOnly x) { value += x.value; return *this; }\n\
    \    bool operator==(AddOnly x) const { return value == x.value; }\n};\n\nbool\
    \ accepts(const DFA<10>& a, int x) {\n    int v = a.initial;\n    for (char c\
    \ : to_string(x)) if (v != -1) v = a.next[v][c - '0'];\n    return v != -1 &&\
    \ a.accept[v];\n}\n\nvoid check(const DFA<10>& a, mt19937& rng) {\n    vector<long\
    \ long> counts(2002), sums(2002);\n    for (int x = 0; x <= 2000; ++x) {\n   \
    \     bool ok = accepts(a, x);\n        counts[x + 1] = counts[x] + ok;\n    \
    \    sums[x + 1] = sums[x] + (ok ? x : 0);\n    }\n    vector<pair<int, int>>\
    \ intervals{\n        {0, 0}, {0, 9}, {0, 99}, {0, 999}, {0, 2000}, {1, 2000},\n\
    \        {9, 10}, {99, 100}, {999, 1000}, {1000, 999}, {2000, 2000}\n    };\n\
    \    for (int tc = 0; tc < 50; ++tc) intervals.emplace_back(rng() % 2001, rng()\
    \ % 2001);\n    for (auto [l, r] : intervals) {\n        long long count = l <=\
    \ r ? counts[r + 1] - counts[l] : 0;\n        long long sum = l <= r ? sums[r\
    \ + 1] - sums[l] : 0;\n        string lower = string(rng() % 4, '0') + to_string(l);\n\
    \        string upper = string(rng() % 4, '0') + to_string(r);\n        auto answer\
    \ = digit_count_sum<long long>(lower, upper, a);\n        assert(answer == make_pair(count,\
    \ sum));\n        assert(digit_count<long long>(lower, upper, a) == count);\n\
    \        auto modular = digit_count_sum<modint<7>>(lower, upper, a);\n       \
    \ assert(modular.first == modint<7>(count) && modular.second == modint<7>(sum));\n\
    \        assert(digit_count<modint<7>>(lower, upper, a) == modint<7>(count));\n\
    \    }\n}\n\nvoid self_check() {\n    mt19937 rng(148);\n    check(DFA<10>{},\
    \ rng);\n    check(no_equal_adjacent(), rng);\n    check(minimize(digit_value_mod(100)),\
    \ rng);\n    check(minimize(intersect(digit_sum_exact(12), digit_value_mod(12))),\
    \ rng);\n    auto either = unite(digit_value_mod(3), digit_value_mod(5));\n  \
    \  check(either, rng);\n    check(complement(either), rng);\n    check(minimize(either),\
    \ rng);\n    auto repeated = complement(no_equal_adjacent());\n    check(repeated,\
    \ rng);\n    long long divisible = 0, adjacent = 0;\n    for (int x = 0; x <=\
    \ 2000; ++x) {\n        divisible += x % 3 == 0 || x % 5 == 0;\n        string\
    \ s = to_string(x);\n        adjacent += adjacent_find(s.begin(), s.end()) !=\
    \ s.end();\n        assert(digit_count<long long>(\"0\", s, either) == divisible);\n\
    \        assert(digit_count<long long>(\"0\", s, complement(either)) == x + 1\
    \ - divisible);\n        assert(digit_count<long long>(\"0\", s, repeated) ==\
    \ adjacent);\n    }\n    assert(digit_count<long long>(\"1\", \"100\", either)\
    \ == 47);\n    for (int mask : {0, 1, 2, 3, 6, 17, 513, 1023}) check(required_digits(mask),\
    \ rng);\n    for (int m = 1; m <= 12; ++m) {\n        check(digit_value_mod(m,\
    \ m - 1), rng);\n        check(digit_sum_mod(m, m - 1), rng);\n    }\n    for\
    \ (int k = 0; k <= 30; ++k) {\n        check(digit_sum_exact(k), rng);\n     \
    \   if (k) check(intersect(digit_sum_exact(k), digit_value_mod(k)), rng);\n  \
    \  }\n    for (const vector<string>& patterns : vector<vector<string>>{\n    \
    \    {}, {\"\"}, {\"0\"}, {\"00\"}, {\"01\"}, {\"4\", \"9\"}, {\"404\"}, {\"10\"\
    , \"101\"}\n    }) check(avoid_patterns<10, '0'>(patterns), rng);\n    for (int\
    \ tc = 0; tc < 100; ++tc) {\n        int n = 1 + rng() % 8;\n        DFA<10> a{vector<array<int,\
    \ 10>>(n), vector<char>(n), int(rng() % n)};\n        for (int v = 0; v < n; ++v)\
    \ {\n            a.accept[v] = rng() % 2;\n            for (int& to : a.next[v])\
    \ to = int(rng() % (n + 1)) - 1;\n        }\n        check(a, rng);\n    }\n \
    \   DFA<10> empty_only{vector<array<int, 10>>(1), {true}, 0};\n    empty_only.next[0].fill(-1);\n\
    \    assert(digit_count<int>(\"0\", \"0\", empty_only) == 0);\n    assert(digit_count<int>(\"\
    0\", \"0\", required_digits(1)) == 1);\n    assert(digit_count<int>(\"1\", \"\
    9\", required_digits(1)) == 0);\n    assert(digit_count<int>(\"0\", \"100\", required_digits(1))\
    \ == 11);\n    auto all = required_digits(0);\n    assert(digit_count<AddOnly>(\"\
    0\", \"1000\", all).value == 1001);\n    string limit = to_string(numeric_limits<long\
    \ long>::max());\n    assert(digit_count<long long>(\"1\", limit, all) == numeric_limits<long\
    \ long>::max());\n    assert(digit_count_sum<long long>(limit, limit, all).second\
    \ == numeric_limits<long long>::max());\n    for (int x : {0, 1, 9, 10, 99, 100,\
    \ 1000}) {\n        string bound = string(500, '0') + to_string(x);\n        assert(digit_count<AddOnly>(bound,\
    \ bound, all).value == 1);\n        assert(digit_count_sum<long long>(bound, bound,\
    \ all) == make_pair(1LL, (long long)x));\n    }\n    auto rejecting = all;\n \
    \   rejecting.accept[0] = false;\n    assert(digit_count_sum<long long>(\"0\"\
    , string(1000, '9'), rejecting) == make_pair(0LL, 0LL));\n    using Mint = modint<998244353>;\n\
    \    string upper(1000, '9');\n    auto answer = digit_count_sum<Mint>(\"0\",\
    \ upper, all);\n    Mint power = Mint(10).pow(1000);\n    assert(answer.first\
    \ == power && answer.second == power * (power - 1) / 2);\n    auto forbidden =\
    \ avoid_patterns<10, '0'>({\"404\"});\n    assert(digit_count<Mint>(\"1\", \"\
    1000\", forbidden) == Mint(999));\n    assert(digit_count<Mint>(\"1\", \"98765432109876543210\"\
    , forbidden) == Mint(848152577));\n}\n\nint main() {\n    self_check();\n    Scanner\
    \ sc;\n    Printer pr;\n    int a, b;\n    sc.read(a, b);\n    pr.println(a +\
    \ b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing ll = long long;\nusing uint = unsigned;\nusing ull\
    \ = unsigned long long;\n\n#include \"../util/modint_base.cpp\"\n#include \"../util/fastio.cpp\"\
    \n#include \"../math/digit_dp.cpp\"\n#include \"../math/digit_dfa.cpp\"\n#include\
    \ \"../string/avoid_patterns.cpp\"\n#include \"../string/dfa_minimize.cpp\"\n\n\
    struct AddOnly {\n    long long value;\n    explicit AddOnly(long long x) : value(x)\
    \ {}\n    AddOnly& operator+=(AddOnly x) { value += x.value; return *this; }\n\
    \    bool operator==(AddOnly x) const { return value == x.value; }\n};\n\nbool\
    \ accepts(const DFA<10>& a, int x) {\n    int v = a.initial;\n    for (char c\
    \ : to_string(x)) if (v != -1) v = a.next[v][c - '0'];\n    return v != -1 &&\
    \ a.accept[v];\n}\n\nvoid check(const DFA<10>& a, mt19937& rng) {\n    vector<long\
    \ long> counts(2002), sums(2002);\n    for (int x = 0; x <= 2000; ++x) {\n   \
    \     bool ok = accepts(a, x);\n        counts[x + 1] = counts[x] + ok;\n    \
    \    sums[x + 1] = sums[x] + (ok ? x : 0);\n    }\n    vector<pair<int, int>>\
    \ intervals{\n        {0, 0}, {0, 9}, {0, 99}, {0, 999}, {0, 2000}, {1, 2000},\n\
    \        {9, 10}, {99, 100}, {999, 1000}, {1000, 999}, {2000, 2000}\n    };\n\
    \    for (int tc = 0; tc < 50; ++tc) intervals.emplace_back(rng() % 2001, rng()\
    \ % 2001);\n    for (auto [l, r] : intervals) {\n        long long count = l <=\
    \ r ? counts[r + 1] - counts[l] : 0;\n        long long sum = l <= r ? sums[r\
    \ + 1] - sums[l] : 0;\n        string lower = string(rng() % 4, '0') + to_string(l);\n\
    \        string upper = string(rng() % 4, '0') + to_string(r);\n        auto answer\
    \ = digit_count_sum<long long>(lower, upper, a);\n        assert(answer == make_pair(count,\
    \ sum));\n        assert(digit_count<long long>(lower, upper, a) == count);\n\
    \        auto modular = digit_count_sum<modint<7>>(lower, upper, a);\n       \
    \ assert(modular.first == modint<7>(count) && modular.second == modint<7>(sum));\n\
    \        assert(digit_count<modint<7>>(lower, upper, a) == modint<7>(count));\n\
    \    }\n}\n\nvoid self_check() {\n    mt19937 rng(148);\n    check(DFA<10>{},\
    \ rng);\n    check(no_equal_adjacent(), rng);\n    check(minimize(digit_value_mod(100)),\
    \ rng);\n    check(minimize(intersect(digit_sum_exact(12), digit_value_mod(12))),\
    \ rng);\n    auto either = unite(digit_value_mod(3), digit_value_mod(5));\n  \
    \  check(either, rng);\n    check(complement(either), rng);\n    check(minimize(either),\
    \ rng);\n    auto repeated = complement(no_equal_adjacent());\n    check(repeated,\
    \ rng);\n    long long divisible = 0, adjacent = 0;\n    for (int x = 0; x <=\
    \ 2000; ++x) {\n        divisible += x % 3 == 0 || x % 5 == 0;\n        string\
    \ s = to_string(x);\n        adjacent += adjacent_find(s.begin(), s.end()) !=\
    \ s.end();\n        assert(digit_count<long long>(\"0\", s, either) == divisible);\n\
    \        assert(digit_count<long long>(\"0\", s, complement(either)) == x + 1\
    \ - divisible);\n        assert(digit_count<long long>(\"0\", s, repeated) ==\
    \ adjacent);\n    }\n    assert(digit_count<long long>(\"1\", \"100\", either)\
    \ == 47);\n    for (int mask : {0, 1, 2, 3, 6, 17, 513, 1023}) check(required_digits(mask),\
    \ rng);\n    for (int m = 1; m <= 12; ++m) {\n        check(digit_value_mod(m,\
    \ m - 1), rng);\n        check(digit_sum_mod(m, m - 1), rng);\n    }\n    for\
    \ (int k = 0; k <= 30; ++k) {\n        check(digit_sum_exact(k), rng);\n     \
    \   if (k) check(intersect(digit_sum_exact(k), digit_value_mod(k)), rng);\n  \
    \  }\n    for (const vector<string>& patterns : vector<vector<string>>{\n    \
    \    {}, {\"\"}, {\"0\"}, {\"00\"}, {\"01\"}, {\"4\", \"9\"}, {\"404\"}, {\"10\"\
    , \"101\"}\n    }) check(avoid_patterns<10, '0'>(patterns), rng);\n    for (int\
    \ tc = 0; tc < 100; ++tc) {\n        int n = 1 + rng() % 8;\n        DFA<10> a{vector<array<int,\
    \ 10>>(n), vector<char>(n), int(rng() % n)};\n        for (int v = 0; v < n; ++v)\
    \ {\n            a.accept[v] = rng() % 2;\n            for (int& to : a.next[v])\
    \ to = int(rng() % (n + 1)) - 1;\n        }\n        check(a, rng);\n    }\n \
    \   DFA<10> empty_only{vector<array<int, 10>>(1), {true}, 0};\n    empty_only.next[0].fill(-1);\n\
    \    assert(digit_count<int>(\"0\", \"0\", empty_only) == 0);\n    assert(digit_count<int>(\"\
    0\", \"0\", required_digits(1)) == 1);\n    assert(digit_count<int>(\"1\", \"\
    9\", required_digits(1)) == 0);\n    assert(digit_count<int>(\"0\", \"100\", required_digits(1))\
    \ == 11);\n    auto all = required_digits(0);\n    assert(digit_count<AddOnly>(\"\
    0\", \"1000\", all).value == 1001);\n    string limit = to_string(numeric_limits<long\
    \ long>::max());\n    assert(digit_count<long long>(\"1\", limit, all) == numeric_limits<long\
    \ long>::max());\n    assert(digit_count_sum<long long>(limit, limit, all).second\
    \ == numeric_limits<long long>::max());\n    for (int x : {0, 1, 9, 10, 99, 100,\
    \ 1000}) {\n        string bound = string(500, '0') + to_string(x);\n        assert(digit_count<AddOnly>(bound,\
    \ bound, all).value == 1);\n        assert(digit_count_sum<long long>(bound, bound,\
    \ all) == make_pair(1LL, (long long)x));\n    }\n    auto rejecting = all;\n \
    \   rejecting.accept[0] = false;\n    assert(digit_count_sum<long long>(\"0\"\
    , string(1000, '9'), rejecting) == make_pair(0LL, 0LL));\n    using Mint = modint<998244353>;\n\
    \    string upper(1000, '9');\n    auto answer = digit_count_sum<Mint>(\"0\",\
    \ upper, all);\n    Mint power = Mint(10).pow(1000);\n    assert(answer.first\
    \ == power && answer.second == power * (power - 1) / 2);\n    auto forbidden =\
    \ avoid_patterns<10, '0'>({\"404\"});\n    assert(digit_count<Mint>(\"1\", \"\
    1000\", forbidden) == Mint(999));\n    assert(digit_count<Mint>(\"1\", \"98765432109876543210\"\
    , forbidden) == Mint(848152577));\n}\n\nint main() {\n    self_check();\n    Scanner\
    \ sc;\n    Printer pr;\n    int a, b;\n    sc.read(a, b);\n    pr.println(a +\
    \ b);\n}\n"
  dependsOn:
  - util/modint_base.cpp
  - util/fastio.cpp
  - math/digit_dp.cpp
  - string/dfa.cpp
  - math/digit_dfa.cpp
  - string/avoid_patterns.cpp
  - string/dfa.cpp
  - datastructure/ahocorasick.cpp
  - string/dfa_minimize.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_digit_dp.test.cpp
  requiredBy: []
  timestamp: '2026-10-17 19:15:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_digit_dp.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_digit_dp.test.cpp
- /verify/test/yosupo_aplusb_digit_dp.test.cpp.html
title: test/yosupo_aplusb_digit_dp.test.cpp
---
