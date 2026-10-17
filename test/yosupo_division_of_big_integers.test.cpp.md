---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/integer_convolution.cpp
    title: "\u6574\u6570\u7573\u307F\u8FBC\u307F(2/3 NTT)"
  - icon: ':heavy_check_mark:'
    path: util/biginteger.cpp
    title: "\u591A\u500D\u9577\u6574\u6570(BigInteger)"
  - icon: ':question:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/division_of_big_integers
    links:
    - https://judge.yosupo.jp/problem/division_of_big_integers
  bundledCode: "#line 1 \"test/yosupo_division_of_big_integers.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/division_of_big_integers\"\n\n#include\
    \ <cassert>\n#include <algorithm>\n#include <cstdio>\n#include <cstring>\n#include\
    \ <string>\n#include <utility>\n#include <type_traits>\n#include <vector>\n\n\
    #include <charconv>\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\nextern\
    \ \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\ntemplate<class T,\
    \ class = void>\nstruct is_fastio_range : false_type {};\n\ntemplate<class T>\n\
    struct is_fastio_range<T, void_t<decltype(declval<T &>().begin()), decltype(declval<T\
    \ &>().end())>> : true_type {};\n\ntemplate<class T, class = void>\nstruct has_fastio_value\
    \ : false_type {};\n\ntemplate<class T>\nstruct has_fastio_value<T, void_t<decltype(declval<const\
    \ T &>().value())>> : true_type {};\n\ntemplate<class T, class = void>\nstruct\
    \ has_fastio_assign_string : false_type {};\n\ntemplate<class T>\nstruct has_fastio_assign_string<T,\
    \ void_t<decltype(declval<T &>().assign(declval<const string &>()))>> : true_type\
    \ {};\n\ntemplate<class T, class = void>\nstruct has_fastio_to_string : false_type\
    \ {};\n\ntemplate<class T>\nstruct has_fastio_to_string<T, void_t<decltype(declval<const\
    \ T &>().to_string())>> : true_type {};\n\nstruct FastIoDigitTable {\n    char\
    \ num[40000];\n\n    constexpr FastIoDigitTable() : num() {\n        for (int\
    \ i = 0; i < 10000; ++i) {\n            int x = i;\n            for (int j = 3;\
    \ j >= 0; --j) {\n                num[i * 4 + j] = char('0' + x % 10);\n     \
    \           x /= 10;\n            }\n        }\n    }\n};\n\nstruct Scanner {\n\
    \    static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET\
    \ = 64;\n    static constexpr int LONG_TOKEN_SAMPLE_SIZE = 1024;\n    static constexpr\
    \ int LONG_TOKEN_MIN_DIGITS = 16;\n    char buf[BUFSIZE + 1];\n    int idx, size;\n\
    \    bool interactive, long_tokens;\n    string number_token;\n\n    Scanner()\
    \ : idx(0), size(0), interactive(isatty(fileno(stdin))), long_tokens(false) {}\n\
    \n    __attribute__((always_inline))\n    static inline unsigned parse_eight_digits(const\
    \ char *p) {\n        unsigned long long value;\n        memcpy(&value, p, 8);\n\
    #if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__\n      \
    \  value = __builtin_bswap64(value);\n#endif\n        value -= 0x3030303030303030ULL;\n\
    \        value = (value * 10 + (value >> 8)) & 0x00ff00ff00ff00ffULL;\n      \
    \  value = (value * 100 + (value >> 16)) & 0x0000ffff0000ffffULL;\n        value\
    \ = (value * 10000 + (value >> 32)) & 0x00000000ffffffffULL;\n        return (unsigned)value;\n\
    \    }\n\n    __attribute__((always_inline))\n    static inline bool are_eight_digits(const\
    \ char *p) {\n        unsigned long long value;\n        memcpy(&value, p, 8);\n\
    \        return (((value + 0x4646464646464646ULL) | (value - 0x3030303030303030ULL))\
    \ & 0x8080808080808080ULL) == 0;\n    }\n\n    template<class U>\n    __attribute__((noinline))\n\
    \    U read_long_digits(char c) {\n        const char *p = buf + idx - 1;\n  \
    \      const char *end = buf + size;\n        U value = 0;\n        if (c >= '0'\
    \ && end - p >= 16 && p[15] >= '0' && are_eight_digits(p) && are_eight_digits(p\
    \ + 8)) {\n            value = (U)parse_eight_digits(p) * 100000000 + parse_eight_digits(p\
    \ + 8);\n            p += 16;\n            while (*p >= '0') {\n             \
    \   value = value * 10 + (*p & 15);\n                ++p;\n            }\n   \
    \         idx = (int)(p - buf) + 1;\n            return value;\n        }\n  \
    \      while (c >= '0') {\n            value = value * 10 + (c & 15);\n      \
    \      c = buf[idx++];\n        }\n        return value;\n    }\n\n    inline\
    \ void load() {\n        int len = size - idx;\n        memmove(buf, buf + idx,\
    \ len);\n        if (interactive) {\n            if (fgets(buf + len, BUFSIZE\
    \ + 1 - len, stdin)) size = len + (int)strlen(buf + len);\n            else size\
    \ = len;\n        } else {\n            size = len + (int)fread(buf + len, 1,\
    \ BUFSIZE - len, stdin);\n            int sample_size = min(size, LONG_TOKEN_SAMPLE_SIZE);\n\
    \            int separators = 0;\n            int minus_signs = 0;\n         \
    \   for (int i = 0; i < sample_size; ++i) {\n                separators += buf[i]\
    \ <= ' ';\n                minus_signs += buf[i] == '-';\n            }\n    \
    \        // Select once per buffer so ordinary short integers avoid the\n    \
    \        // checks and call overhead of the 16-digit SWAR path.\n            long_tokens\
    \ = separators * LONG_TOKEN_MIN_DIGITS < sample_size - minus_signs;\n        }\n\
    \        idx = 0;\n        buf[size] = 0;\n    }\n\n    inline void ensure() {\n\
    \        if (idx + OFFSET > size) load();\n    }\n\n    inline void ensure_interactive()\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"util/biginteger.cpp\"\
    \n\n\n\n#line 1 \"math/integer_convolution.cpp\"\n\n\n\n#ifndef FIRIEXP_LIBRARY_ARBITRARY_CONVOLUTION_U64_NAIVE_THRESHOLD\n\
    #define FIRIEXP_LIBRARY_ARBITRARY_CONVOLUTION_U64_NAIVE_THRESHOLD 8192\n#endif\n\
    \n#ifndef FIRIEXP_LIBRARY_ARBITRARY_SQUARE_U64_NAIVE_THRESHOLD\n#define FIRIEXP_LIBRARY_ARBITRARY_SQUARE_U64_NAIVE_THRESHOLD\
    \ 32768\n#endif\n\nnamespace ArbitraryConvolution {\n    template<unsigned int\
    \ M>\n    struct StaticModInt {\n        unsigned int val;\n        StaticModInt()\
    \ : val(0) {}\n        template<class T>\n        StaticModInt(T v) {\n      \
    \      long long x = (long long)(v % (long long)M);\n            if (x < 0) x\
    \ += M;\n            val = (unsigned int)x;\n        }\n        static StaticModInt\
    \ raw(unsigned int v) {\n            StaticModInt x;\n            x.val = v;\n\
    \            return x;\n        }\n        StaticModInt& operator+=(const StaticModInt&\
    \ rhs) {\n            val += rhs.val;\n            if (val >= M) val -= M;\n \
    \           return *this;\n        }\n        StaticModInt& operator-=(const StaticModInt&\
    \ rhs) {\n            val -= rhs.val;\n            if (val >= M) val += M;\n \
    \           return *this;\n        }\n        StaticModInt& operator*=(const StaticModInt&\
    \ rhs) {\n            val = (unsigned int)((unsigned long long)val * rhs.val %\
    \ M);\n            return *this;\n        }\n        StaticModInt pow(long long\
    \ n) const {\n            StaticModInt x = *this, r = 1;\n            while (n)\
    \ {\n                if (n & 1) r *= x;\n                x *= x;\n           \
    \     n >>= 1;\n            }\n            return r;\n        }\n        StaticModInt\
    \ inv() const { return pow(M - 2); }\n        friend StaticModInt operator+(StaticModInt\
    \ lhs, const StaticModInt& rhs) { return lhs += rhs; }\n        friend StaticModInt\
    \ operator-(StaticModInt lhs, const StaticModInt& rhs) { return lhs -= rhs; }\n\
    \        friend StaticModInt operator*(StaticModInt lhs, const StaticModInt& rhs)\
    \ { return lhs *= rhs; }\n        friend bool operator==(const StaticModInt& lhs,\
    \ const StaticModInt& rhs) { return lhs.val == rhs.val; }\n        friend bool\
    \ operator!=(const StaticModInt& lhs, const StaticModInt& rhs) { return lhs.val\
    \ != rhs.val; }\n    };\n\n    template<unsigned int MOD_, unsigned int PRIMITIVE_ROOT_>\n\
    \    struct NTT {\n        using mint = StaticModInt<MOD_>;\n        static constexpr\
    \ unsigned int MODV = MOD_;\n        static constexpr unsigned int G = PRIMITIVE_ROOT_;\n\
    \        mint root[30], iroot[30], rate2[30], irate2[30], rate3[30], irate3[30],\
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
    \    return res;\n    }\n}\n\nnamespace BoundedConvolution {\n    using NTT1 =\
    \ ArbitraryConvolution::NTT<998244353, 3>;\n    using NTT2 = ArbitraryConvolution::NTT<1004535809,\
    \ 3>;\n\n    namespace internal {\n        inline const NTT1& ntt1() {\n     \
    \       static const NTT1 value;\n            return value;\n        }\n\n   \
    \     inline const NTT2& ntt2() {\n            static const NTT2 value;\n    \
    \        return value;\n        }\n\n        inline unsigned long long combine_u64(unsigned\
    \ int x1, unsigned int x2) {\n            static constexpr unsigned long long\
    \ m1 = 998244353ULL;\n            static constexpr unsigned long long m2 = 1004535809ULL;\n\
    \            static const unsigned long long m1_inv_m2 =\n                ArbitraryConvolution::StaticModInt<1004535809>(m1).inv().val;\n\
    \            unsigned long long delta = (x2 + m2 - x1 % m2) % m2;\n          \
    \  unsigned long long multiplier = delta * m1_inv_m2 % m2;\n            return\
    \ x1 + m1 * multiplier;\n        }\n    }\n\n    vector<unsigned long long> convolution_u64(const\
    \ vector<unsigned int> &a,\n                                                const\
    \ vector<unsigned int> &b) {\n        if (a.empty() || b.empty()) return {};\n\
    \        auto c1 = internal::ntt1().convolution(a, b);\n        auto c2 = internal::ntt2().convolution(a,\
    \ b);\n        vector<unsigned long long> res(c1.size());\n        for (int i\
    \ = 0; i < (int)res.size(); ++i) {\n            res[i] = internal::combine_u64(c1[i],\
    \ c2[i]);\n        }\n        return res;\n    }\n\n    vector<unsigned long long>\
    \ square_u64(const vector<unsigned int> &a) {\n        if (a.empty()) return {};\n\
    \        auto c1 = internal::ntt1().square(a);\n        auto c2 = internal::ntt2().square(a);\n\
    \        vector<unsigned long long> res(c1.size());\n        for (int i = 0; i\
    \ < (int)res.size(); ++i) {\n            res[i] = internal::combine_u64(c1[i],\
    \ c2[i]);\n        }\n        return res;\n    }\n}\n\n/**\n * @brief \u6574\u6570\
    \u7573\u307F\u8FBC\u307F(2/3 NTT)\n */\n\n\n#line 5 \"util/biginteger.cpp\"\n\n\
    namespace BigIntegerDetail {\n    using u32 = unsigned int;\n    using u64 = unsigned\
    \ long long;\n\n    struct DecimalRadix {\n        static constexpr u64 BASE =\
    \ 100000000;\n        static constexpr u32 META_BASE = 10000;\n        static\
    \ constexpr int IO_BASE = 10;\n        static constexpr int BLOCK_DIGITS = 8;\n\
    \    };\n\n    struct HexRadix {\n        static constexpr u64 BASE = 1ULL <<\
    \ 32;\n        static constexpr u32 META_BASE = 1u << 16;\n        static constexpr\
    \ int IO_BASE = 16;\n        static constexpr int BLOCK_DIGITS = 8;\n    };\n\n\
    \    template<class Radix>\n    struct Magnitude {\n        using Digits = vector<u32>;\n\
    \        static constexpr u64 BASE = Radix::BASE;\n        static constexpr u32\
    \ META_BASE = Radix::META_BASE;\n        static constexpr size_t SCHOOLBOOK_MIN\
    \ = 32;\n        static constexpr u64 SCHOOLBOOK_AREA = 16384;\n        static\
    \ constexpr size_t KARATSUBA_LIMIT = Radix::IO_BASE == 10 ? 192 : 768;\n     \
    \   static constexpr size_t DIVISION_MIN = 64;\n        static constexpr u64 DIVISION_AREA\
    \ = 16384;\n        static constexpr size_t DIVIDE_CONQUER_MAX = 4096;\n     \
    \   static constexpr size_t CYCLIC_MIN = 4096;\n\n        static void trim(Digits\
    \ &a) {\n            while (!a.empty() && a.back() == 0) a.pop_back();\n     \
    \   }\n\n        static int compare(const Digits &a, const Digits &b) {\n    \
    \        if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;\n    \
    \        for (size_t i = a.size(); i-- > 0;) {\n                if (a[i] != b[i])\
    \ return a[i] < b[i] ? -1 : 1;\n            }\n            return 0;\n       \
    \ }\n\n        static void add(Digits &a, const Digits &b) {\n            if (a.size()\
    \ < b.size()) a.resize(b.size());\n            u64 carry = 0;\n            size_t\
    \ i = 0;\n            for (; i < b.size(); ++i) {\n                u64 value =\
    \ u64(a[i]) + b[i] + carry;\n                carry = value >= BASE;\n        \
    \        a[i] = u32(value - carry * BASE);\n            }\n            for (;\
    \ carry && i < a.size(); ++i) {\n                u64 value = u64(a[i]) + carry;\n\
    \                carry = value >= BASE;\n                a[i] = u32(value - carry\
    \ * BASE);\n            }\n            if (carry) a.push_back(1);\n        }\n\
    \n        static void subtract(Digits &a, const Digits &b) {\n            u64\
    \ borrow = 0;\n            size_t i = 0;\n            for (; i < b.size(); ++i)\
    \ {\n                u64 value = u64(b[i]) + borrow;\n                borrow =\
    \ a[i] < value;\n                a[i] = u32(u64(a[i]) + borrow * BASE - value);\n\
    \            }\n            for (; borrow && i < a.size(); ++i) {\n          \
    \      borrow = a[i] == 0;\n                a[i] = u32(u64(a[i]) + borrow * BASE\
    \ - 1);\n            }\n            assert(!borrow);\n            trim(a);\n \
    \       }\n\n        static void increment(Digits &a) {\n            size_t i\
    \ = 0;\n            while (i < a.size() && u64(a[i]) + 1 == BASE) a[i++] = 0;\n\
    \            if (i == a.size()) a.push_back(1);\n            else ++a[i];\n  \
    \      }\n\n        static void decrement(Digits &a) {\n            size_t i =\
    \ 0;\n            while (a[i] == 0) a[i++] = u32(BASE - 1);\n            --a[i];\n\
    \            trim(a);\n        }\n\n        static void multiply_small(Digits\
    \ &a, u32 b) {\n            if (b == 0) { a.clear(); return; }\n            if\
    \ (b == 1) return;\n            u64 carry = 0;\n            for (u32 &digit :\
    \ a) {\n                u64 value = u64(digit) * b + carry;\n                digit\
    \ = u32(value % BASE);\n                carry = value / BASE;\n            }\n\
    \            while (carry) {\n                a.push_back(u32(carry % BASE));\n\
    \                carry /= BASE;\n            }\n        }\n\n        static u32\
    \ divide_small(Digits &a, u32 b) {\n            assert(b);\n            u64 remainder\
    \ = 0;\n            for (size_t i = a.size(); i-- > 0;) {\n                u64\
    \ value = remainder * BASE + a[i];\n                a[i] = u32(value / b);\n \
    \               remainder = value % b;\n            }\n            trim(a);\n\
    \            return u32(remainder);\n        }\n\n        static Digits high(const\
    \ Digits &a, size_t drop) {\n            if (drop >= a.size()) return {};\n  \
    \          return Digits(a.begin() + drop, a.end());\n        }\n\n        static\
    \ Digits schoolbook(const Digits &a, const Digits &b) {\n            Digits result(a.size()\
    \ + b.size());\n            for (size_t i = 0; i < a.size(); ++i) {\n        \
    \        u64 carry = 0;\n                for (size_t j = 0; j < b.size(); ++j)\
    \ {\n                    u64 value = u64(a[i]) * b[j] + result[i + j] + carry;\n\
    \                    result[i + j] = u32(value % BASE);\n                    carry\
    \ = value / BASE;\n                }\n                result[i + b.size()] = u32(carry);\n\
    \            }\n            trim(result);\n            return result;\n      \
    \  }\n\n        static Digits split(const Digits &a) {\n            Digits result(2\
    \ * a.size());\n            for (size_t i = 0; i < a.size(); ++i) {\n        \
    \        result[2 * i] = a[i] % META_BASE;\n                result[2 * i + 1]\
    \ = a[i] / META_BASE;\n            }\n            trim(result);\n            return\
    \ result;\n        }\n\n        static void add_shifted(Digits &a, const Digits\
    \ &b, size_t shift) {\n            if (a.size() < b.size() + shift) a.resize(b.size()\
    \ + shift);\n            u64 carry = 0;\n            size_t i = 0;\n         \
    \   for (; i < b.size(); ++i) {\n                u64 value = u64(a[i + shift])\
    \ + b[i] + carry;\n                carry = value >= BASE;\n                a[i\
    \ + shift] = u32(value - carry * BASE);\n            }\n            for (; carry\
    \ && i + shift < a.size(); ++i) {\n                u64 value = u64(a[i + shift])\
    \ + carry;\n                carry = value >= BASE;\n                a[i + shift]\
    \ = u32(value - carry * BASE);\n            }\n            if (carry) a.push_back(1);\n\
    \        }\n\n        static Digits karatsuba(const Digits &a, const Digits &b)\
    \ {\n            size_t k = max(a.size(), b.size()) / 2;\n            Digits a0(a.begin(),\
    \ a.begin() + min(k, a.size()));\n            Digits b0(b.begin(), b.begin() +\
    \ min(k, b.size()));\n            Digits a1 = high(a, k), b1 = high(b, k);\n \
    \           trim(a0);\n            trim(b0);\n            Digits z0 = multiply(a0,\
    \ b0), z2 = multiply(a1, b1);\n            add(a0, a1);\n            add(b0, b1);\n\
    \            Digits z1 = multiply(a0, b0);\n            subtract(z1, z0);\n  \
    \          subtract(z1, z2);\n            add_shifted(z0, z1, k);\n          \
    \  add_shifted(z0, z2, 2 * k);\n            trim(z0);\n            return z0;\n\
    \        }\n\n        static Digits multiply(const Digits &a, const Digits &b)\
    \ {\n            if (a.empty() || b.empty()) return {};\n            if (min(a.size(),\
    \ b.size()) == 1) {\n                Digits result = a.size() == 1 ? b : a;\n\
    \                multiply_small(result, a.size() == 1 ? a[0] : b[0]);\n      \
    \          return result;\n            }\n            if (min(a.size(), b.size())\
    \ <= SCHOOLBOOK_MIN || u64(a.size()) * b.size() <= SCHOOLBOOK_AREA) {\n      \
    \          return a.size() < b.size() ? schoolbook(a, b) : schoolbook(b, a);\n\
    \            }\n            if (min(a.size(), b.size()) <= KARATSUBA_LIMIT &&\
    \ max(a.size(), b.size()) <= 2 * min(a.size(), b.size())) return karatsuba(a,\
    \ b);\n            Digits x = split(a);\n            vector<u64> product;\n  \
    \          if (&a == &b || a == b) product = BoundedConvolution::square_u64(x);\n\
    \            else product = BoundedConvolution::convolution_u64(x, split(b));\n\
    \            Digits result;\n            result.reserve(a.size() + b.size());\n\
    \            u64 carry = 0;\n            for (size_t i = 0; i < product.size();\
    \ i += 2) {\n                u64 value = product[i] + carry;\n               \
    \ u32 low = u32(value % META_BASE);\n                carry = value / META_BASE;\n\
    \                if (i + 1 < product.size()) carry += product[i + 1];\n      \
    \          result.push_back(low + u32(carry % META_BASE) * META_BASE);\n     \
    \           carry /= META_BASE;\n            }\n            while (carry) {\n\
    \                result.push_back(u32(carry % BASE));\n                carry /=\
    \ BASE;\n            }\n            trim(result);\n            return result;\n\
    \        }\n\n        static pair<Digits, Digits> knuth(Digits a, const Digits\
    \ &b) {\n            assert(b.size() >= 2 && b.back() >= BASE / 2);\n        \
    \    if (compare(a, b) < 0) return {{}, std::move(a)};\n            size_t n =\
    \ b.size(), count = a.size() - n + 1;\n            Digits quotient(count);\n \
    \           a.push_back(0);\n            for (size_t j = count; j-- > 0;) {\n\
    \                u64 numerator = u64(a[j + n]) * BASE + a[j + n - 1];\n      \
    \          u64 q = numerator / b.back(), r = numerator % b.back();\n         \
    \       if (q >= BASE) { q = BASE - 1; r = numerator - q * b.back(); }\n     \
    \           while (r < BASE && q * b[n - 2] > r * BASE + a[j + n - 2]) {\n   \
    \                 --q;\n                    r += b.back();\n                }\n\
    \                u64 carry = 0;\n                for (size_t i = 0; i < n; ++i)\
    \ {\n                    u64 product = q * b[i] + carry;\n                   \
    \ u64 low = product % BASE;\n                    carry = product / BASE;\n   \
    \                 if (a[j + i] < low) { a[j + i] = u32(u64(a[j + i]) + BASE -\
    \ low); ++carry; }\n                    else a[j + i] -= u32(low);\n         \
    \       }\n                bool underflow = a[j + n] < carry;\n              \
    \  a[j + n] = u32(u64(a[j + n]) + (underflow ? BASE : 0) - carry);\n         \
    \       if (underflow) {\n                    --q;\n                    u64 c\
    \ = 0;\n                    for (size_t i = 0; i < n; ++i) {\n               \
    \         u64 value = u64(a[j + i]) + b[i] + c;\n                        c = value\
    \ >= BASE;\n                        a[j + i] = u32(value - c * BASE);\n      \
    \              }\n                    a[j + n] = u32((u64(a[j + n]) + c) % BASE);\n\
    \                }\n                quotient[j] = u32(q);\n            }\n   \
    \         a.resize(n);\n            trim(a);\n            trim(quotient);\n  \
    \          return {std::move(quotient), std::move(a)};\n        }\n\n        template<class\
    \ Transform>\n        static vector<u32> cyclic_convolution(const Digits &a, const\
    \ Digits &b,\n                                               size_t size, const\
    \ Transform &transform) {\n            using mint = typename Transform::mint;\n\
    \            vector<mint> x(size), y(size);\n            for (size_t i = 0; i\
    \ < a.size(); ++i) x[i] = mint::raw(a[i]);\n            for (size_t i = 0; i <\
    \ b.size(); ++i) y[i] = mint::raw(b[i]);\n            transform.ntt(x, false);\n\
    \            transform.ntt(y, false);\n            for (size_t i = 0; i < size;\
    \ ++i) x[i] *= y[i];\n            transform.ntt(x, true);\n            mint scale\
    \ = transform.inv_size(size);\n            vector<u32> result(size);\n       \
    \     for (size_t i = 0; i < size; ++i) result[i] = (x[i] * scale).val;\n    \
    \        return result;\n        }\n\n        static void cyclic_normalize(Digits\
    \ &a, size_t size) {\n            if (a.size() > size) {\n                Digits\
    \ extra = high(a, size);\n                a.resize(size);\n                add(a,\
    \ extra);\n                if (a.size() > size) {\n                    a.resize(size);\n\
    \                    increment(a);\n                }\n            }\n       \
    \     if (a.size() == size && all_of(a.begin(), a.end(), [](u32 x) { return x\
    \ == BASE - 1; })) a.clear();\n            trim(a);\n        }\n\n        static\
    \ Digits cyclic_product(const Digits &a, const Digits &b, size_t size) {\n   \
    \         assert(a.size() <= size && b.size() <= size);\n            Digits x\
    \ = split(a), y = split(b);\n            auto c1 = cyclic_convolution(x, y, 2\
    \ * size, BoundedConvolution::internal::ntt1());\n            auto c2 = cyclic_convolution(x,\
    \ y, 2 * size, BoundedConvolution::internal::ntt2());\n            Digits result(size);\n\
    \            u64 carry = 0;\n            for (size_t i = 0; i < size; ++i) {\n\
    \                u64 value = BoundedConvolution::internal::combine_u64(c1[2 *\
    \ i], c2[2 * i]) + carry;\n                u32 low = u32(value % META_BASE);\n\
    \                carry = value / META_BASE + BoundedConvolution::internal::combine_u64(c1[2\
    \ * i + 1], c2[2 * i + 1]);\n                result[i] = low + u32(carry % META_BASE)\
    \ * META_BASE;\n                carry /= META_BASE;\n            }\n         \
    \   while (carry) {\n                result.push_back(u32(carry % BASE));\n  \
    \              carry /= BASE;\n            }\n            cyclic_normalize(result,\
    \ size);\n            return result;\n        }\n\n        static Digits cyclic_difference(Digits\
    \ a, const Digits &b, size_t size) {\n            if (a.size() > size) {\n   \
    \             Digits top = high(a, size);\n                a.resize(size);\n \
    \               add(a, top);\n            }\n            cyclic_normalize(a, size);\n\
    \            if (compare(a, b) >= 0) subtract(a, b);\n            else {\n   \
    \             Digits modulus(size, u32(BASE - 1));\n                subtract(modulus,\
    \ b);\n                add(a, modulus);\n            }\n            return a;\n\
    \        }\n\n        static pair<Digits, Digits> divide_three_two(const Digits\
    \ &a, const Digits &b, size_t k) {\n            Digits a12 = high(a, k), a2 =\
    \ high(a, 2 * k), b1 = high(b, k);\n            Digits quotient, remainder;\n\
    \            if (compare(a2, b1) < 0) {\n                auto qr = divide_two_one(a12,\
    \ b1);\n                quotient = std::move(qr.first);\n                remainder\
    \ = std::move(qr.second);\n            } else {\n                quotient.assign(k,\
    \ u32(BASE - 1));\n                remainder = a12;\n                subtract(remainder,\
    \ multiply(quotient, b1));\n            }\n            Digits low(a.begin(), a.begin()\
    \ + min(k, a.size()));\n            low.resize(k);\n            low.insert(low.end(),\
    \ remainder.begin(), remainder.end());\n            trim(low);\n            Digits\
    \ b0(b.begin(), b.begin() + k);\n            trim(b0);\n            Digits product\
    \ = multiply(quotient, b0);\n            for (int i = 0; i < 2 && compare(low,\
    \ product) < 0; ++i) {\n                decrement(quotient);\n               \
    \ add(low, b);\n            }\n            subtract(low, product);\n         \
    \   return {std::move(quotient), std::move(low)};\n        }\n\n        static\
    \ pair<Digits, Digits> divide_two_one(const Digits &a, const Digits &b) {\n  \
    \          size_t n = b.size();\n            if (n <= 64 || n % 2) return knuth(a,\
    \ b);\n            size_t k = n / 2;\n            auto top = divide_three_two(high(a,\
    \ k), b, k);\n            Digits low(a.begin(), a.begin() + min(k, a.size()));\n\
    \            low.resize(k);\n            low.insert(low.end(), top.second.begin(),\
    \ top.second.end());\n            trim(low);\n            auto bottom = divide_three_two(low,\
    \ b, k);\n            bottom.first.resize(k);\n            bottom.first.insert(bottom.first.end(),\
    \ top.first.begin(), top.first.end());\n            trim(bottom.first);\n    \
    \        return bottom;\n        }\n\n        static pair<Digits, Digits> burnikel(Digits\
    \ a, Digits b) {\n            size_t unit = 1;\n            while ((b.size() +\
    \ unit - 1) / unit > 64) unit *= 2;\n            size_t n = (b.size() + unit -\
    \ 1) / unit * unit;\n            size_t padding = n - b.size();\n            a.insert(a.begin(),\
    \ padding, 0);\n            b.insert(b.begin(), padding, 0);\n            size_t\
    \ end = a.size() - n;\n            Digits quotient(end + 1), remainder = high(a,\
    \ end);\n            if (compare(remainder, b) >= 0) {\n                quotient[end]\
    \ = 1;\n                subtract(remainder, b);\n            }\n            while\
    \ (end) {\n                size_t begin = end > n ? end - n : 0;\n           \
    \     Digits block(a.begin() + begin, a.begin() + end);\n                block.insert(block.end(),\
    \ remainder.begin(), remainder.end());\n                trim(block);\n       \
    \         auto qr = divide_two_one(block, b);\n                copy(qr.first.begin(),\
    \ qr.first.end(), quotient.begin() + begin);\n                remainder = std::move(qr.second);\n\
    \                end = begin;\n            }\n            trim(quotient);\n  \
    \          remainder = high(remainder, padding);\n            return {std::move(quotient),\
    \ std::move(remainder)};\n        }\n\n        static Digits reciprocal(const\
    \ Digits &b) {\n            assert(b.size() >= 2 && b.back() >= BASE / 2);\n \
    \           size_t n = b.size();\n            if (n <= 64) {\n               \
    \ Digits power(2 * n + 1);\n                power.back() = 1;\n              \
    \  return knuth(std::move(power), b).first;\n            }\n            size_t\
    \ h = (n + 1) / 2 + 1;\n            Digits x = reciprocal(high(b, n - h));\n \
    \           for (int i = 0; i < 4; ++i) decrement(x);\n            size_t size\
    \ = 1;\n            while (size <= n) size *= 2;\n            Digits error;\n\
    \            if (size >= CYCLIC_MIN && size < n + x.size() - 1) {\n          \
    \      error.resize((n + h) % size + 1);\n                error.back() = 1;\n\
    \                error = cyclic_difference(std::move(error), cyclic_product(b,\
    \ x, size), size);\n            } else {\n                error.resize(n + h +\
    \ 1);\n                error.back() = 1;\n                subtract(error, multiply(b,\
    \ x));\n            }\n            Digits correction = high(multiply(x, error),\
    \ 2 * h);\n            x.insert(x.begin(), n - h, 0);\n            add(x, correction);\n\
    \            return x;\n        }\n\n        static pair<Digits, Digits> divide_with_inverse(const\
    \ Digits &a, const Digits &b,\n                                              \
    \         const Digits &inverse, size_t precision) {\n            Digits top =\
    \ high(a, b.size() - precision);\n            Digits quotient = high(multiply(top,\
    \ inverse), 2 * precision);\n            size_t size = 1;\n            while (size\
    \ <= b.size()) size *= 2;\n            Digits remainder;\n            if (size\
    \ >= CYCLIC_MIN && quotient.size() > SCHOOLBOOK_MIN && size < quotient.size()\
    \ + b.size() - 1) {\n                remainder = cyclic_difference(a, cyclic_product(quotient,\
    \ b, size), size);\n                if (remainder.size() > b.size() + 1 ||\n \
    \                   (remainder.size() == b.size() + 1 && remainder.back() >= 3))\
    \ {\n                    decrement(quotient);\n                    add(remainder,\
    \ b);\n                    cyclic_normalize(remainder, size);\n              \
    \  }\n            } else {\n                Digits product = multiply(quotient,\
    \ b);\n                if (compare(product, a) > 0) {\n                    decrement(quotient);\n\
    \                    subtract(product, b);\n                }\n              \
    \  remainder = a;\n                subtract(remainder, product);\n           \
    \ }\n            for (int i = 0; i < 2 && compare(remainder, b) >= 0; ++i) {\n\
    \                increment(quotient);\n                subtract(remainder, b);\n\
    \            }\n            assert(compare(remainder, b) < 0);\n            return\
    \ {std::move(quotient), std::move(remainder)};\n        }\n\n        static pair<Digits,\
    \ Digits> divide(const Digits &a, const Digits &b) {\n            assert(!b.empty());\n\
    \            if (compare(a, b) < 0) return {{}, a};\n            if (b.size()\
    \ == 1) {\n                Digits quotient = a;\n                u32 r = divide_small(quotient,\
    \ b[0]);\n                return {std::move(quotient), r ? Digits{r} : Digits{}};\n\
    \            }\n            if (a.size() == 2) {\n                u64 dividend\
    \ = u64(a[1]) * BASE + a[0];\n                u64 divisor = u64(b[1]) * BASE +\
    \ b[0];\n                u64 q = dividend / divisor, r = dividend % divisor;\n\
    \                Digits remainder;\n                if (r) remainder.push_back(u32(r\
    \ % BASE));\n                if (r >= BASE) remainder.push_back(u32(r / BASE));\n\
    \                return {Digits{u32(q)}, std::move(remainder)};\n            }\n\
    \            u32 norm = u32(BASE / (u64(b.back()) + 1));\n            Digits dividend\
    \ = a, divisor = b;\n            multiply_small(dividend, norm);\n           \
    \ multiply_small(divisor, norm);\n            size_t m = divisor.size(), q = dividend.size()\
    \ - m + 1;\n            pair<Digits, Digits> result;\n            if (min(m, q)\
    \ <= DIVISION_MIN || u64(m) * q <= DIVISION_AREA) {\n                result =\
    \ knuth(std::move(dividend), divisor);\n            } else if (max(m, q) <= DIVIDE_CONQUER_MAX)\
    \ {\n                result = burnikel(std::move(dividend), std::move(divisor));\n\
    \            } else {\n                size_t precision = min(q, (m + 1) / 2 +\
    \ 1);\n                size_t step = precision - 1;\n                Digits inverse\
    \ = reciprocal(high(divisor, m - precision));\n                if (q <= precision)\
    \ {\n                    result = divide_with_inverse(dividend, divisor, inverse,\
    \ precision);\n                } else {\n                    Digits quotient(q);\n\
    \                    size_t end = dividend.size() - m;\n                    Digits\
    \ remainder = high(dividend, end);\n                    if (compare(remainder,\
    \ divisor) >= 0) {\n                        quotient[end] = 1;\n             \
    \           subtract(remainder, divisor);\n                    }\n           \
    \         while (end) {\n                        size_t begin = end > step ? end\
    \ - step : 0;\n                        Digits block(dividend.begin() + begin,\
    \ dividend.begin() + end);\n                        block.insert(block.end(),\
    \ remainder.begin(), remainder.end());\n                        trim(block);\n\
    \                        auto qr = divide_with_inverse(block, divisor, inverse,\
    \ precision);\n                        copy(qr.first.begin(), qr.first.end(),\
    \ quotient.begin() + begin);\n                        remainder = std::move(qr.second);\n\
    \                        end = begin;\n                    }\n               \
    \     trim(quotient);\n                    result = {std::move(quotient), std::move(remainder)};\n\
    \                }\n            }\n            if (norm != 1) divide_small(result.second,\
    \ norm);\n            return result;\n        }\n\n        static Digits power_of_two(int\
    \ bits) {\n            Digits result{1}, factor{2};\n            while (bits)\
    \ {\n                if (bits & 1) result = multiply(result, factor);\n      \
    \          bits >>= 1;\n                if (bits) factor = multiply(factor, factor);\n\
    \            }\n            return result;\n        }\n    };\n}\n\ntemplate<class\
    \ Radix>\nclass BasicBigInteger {\n    using u32 = BigIntegerDetail::u32;\n  \
    \  using u64 = BigIntegerDetail::u64;\n    using Ops = BigIntegerDetail::Magnitude<Radix>;\n\
    \    using Digits = typename Ops::Digits;\n    static constexpr u64 BASE = Radix::BASE;\n\
    \    static constexpr int IO_BASE = Radix::IO_BASE;\n    static constexpr int\
    \ BLOCK_DIGITS = Radix::BLOCK_DIGITS;\n\n    Digits digits;\n    bool negative\
    \ = false;\n\n    static int digit_value(char c) {\n        if ('0' <= c && c\
    \ <= '9') return c - '0';\n        if ('a' <= c && c <= 'z') return c - 'a' +\
    \ 10;\n        if ('A' <= c && c <= 'Z') return c - 'A' + 10;\n        return\
    \ -1;\n    }\n\n    static void append_digits(string &out, u32 value, int base,\
    \ int width) {\n        char buffer[32];\n        int pos = 32;\n        do {\n\
    \            int digit = value % base;\n            buffer[--pos] = char(digit\
    \ < 10 ? '0' + digit : 'a' + digit - 10);\n            value /= base;\n      \
    \  } while (value);\n        out.append(max(0, width - (32 - pos)), '0');\n  \
    \      out.append(buffer + pos, buffer + 32);\n    }\n\n    BasicBigInteger(Digits\
    \ value, bool sign) : digits(std::move(value)), negative(sign && !digits.empty())\
    \ {}\n\n    BasicBigInteger &add_signed(const BasicBigInteger &other, bool sign)\
    \ {\n        if (negative == sign) Ops::add(digits, other.digits);\n        else\
    \ {\n            int cmp = Ops::compare(digits, other.digits);\n            if\
    \ (cmp >= 0) Ops::subtract(digits, other.digits);\n            else {\n      \
    \          Digits result = other.digits;\n                Ops::subtract(result,\
    \ digits);\n                digits = std::move(result);\n                negative\
    \ = sign;\n            }\n        }\n        if (digits.empty()) negative = false;\n\
    \        return *this;\n    }\n\n    static int compare(const BasicBigInteger\
    \ &a, const BasicBigInteger &b) {\n        if (a.negative != b.negative) return\
    \ a.negative ? -1 : 1;\n        int cmp = Ops::compare(a.digits, b.digits);\n\
    \        return a.negative ? -cmp : cmp;\n    }\n\npublic:\n    BasicBigInteger()\
    \ = default;\n    BasicBigInteger(long long value) { *this = value; }\n    BasicBigInteger(const\
    \ string &value, int base = IO_BASE) {\n        bool ok = assign(value, base);\n\
    \        assert(ok);\n        (void)ok;\n    }\n\n    BasicBigInteger &operator=(long\
    \ long value) {\n        digits.clear();\n        negative = value < 0;\n    \
    \    u64 magnitude = negative ? u64(-(value + 1)) + 1 : u64(value);\n        while\
    \ (magnitude) {\n            digits.push_back(u32(magnitude % BASE));\n      \
    \      magnitude /= BASE;\n        }\n        return *this;\n    }\n\n    bool\
    \ assign(const string &value, int base = IO_BASE) {\n        digits.clear();\n\
    \        negative = false;\n        if (base < 2 || base > 36 || value.empty())\
    \ return false;\n        size_t begin = value[0] == '+' || value[0] == '-';\n\
    \        if (begin == value.size()) return false;\n        for (size_t i = begin;\
    \ i < value.size(); ++i) {\n            int digit = digit_value(value[i]);\n \
    \           if (digit < 0 || digit >= base) return false;\n        }\n       \
    \ while (begin < value.size() && value[begin] == '0') ++begin;\n        if (begin\
    \ == value.size()) return true;\n        if (base == IO_BASE) {\n            digits.reserve((value.size()\
    \ - begin + BLOCK_DIGITS - 1) / BLOCK_DIGITS);\n            for (size_t right\
    \ = value.size(); right > begin;) {\n                size_t left = right - min(size_t(BLOCK_DIGITS),\
    \ right - begin);\n                u32 block = 0;\n                for (size_t\
    \ i = left; i < right; ++i) block = block * base + digit_value(value[i]);\n  \
    \              digits.push_back(block);\n                right = left;\n     \
    \       }\n        } else {\n            u32 power = 1;\n            int count\
    \ = 0;\n            while (power <= (BASE - 1) / base) { power *= base; ++count;\
    \ }\n            size_t width = (value.size() - begin - 1) % count + 1;\n    \
    \        for (size_t pos = begin; pos < value.size(); width = count) {\n     \
    \           u32 block = 0, multiplier = 1;\n                for (size_t i = 0;\
    \ i < width; ++i) {\n                    block = block * base + digit_value(value[pos++]);\n\
    \                    multiplier *= base;\n                }\n                Ops::multiply_small(digits,\
    \ multiplier);\n                if (block) Ops::add(digits, Digits{block});\n\
    \            }\n        }\n        negative = value[0] == '-';\n        return\
    \ true;\n    }\n\n    string to_string(int base = IO_BASE) const {\n        assert(2\
    \ <= base && base <= 36);\n        if (is_zero()) return \"0\";\n        string\
    \ out;\n        out.reserve(digits.size() * BLOCK_DIGITS + 1);\n        if (negative)\
    \ out.push_back('-');\n        if (base == IO_BASE) {\n            append_digits(out,\
    \ digits.back(), base, 0);\n            for (size_t i = digits.size() - 1; i--\
    \ > 0;) append_digits(out, digits[i], base, BLOCK_DIGITS);\n        } else {\n\
    \            u32 power = 1;\n            int count = 0;\n            while (power\
    \ <= (BASE - 1) / base) { power *= base; ++count; }\n            Digits value\
    \ = digits, parts;\n            while (!value.empty()) parts.push_back(Ops::divide_small(value,\
    \ power));\n            append_digits(out, parts.back(), base, 0);\n         \
    \   for (size_t i = parts.size() - 1; i-- > 0;) append_digits(out, parts[i], base,\
    \ count);\n        }\n        return out;\n    }\n\n    bool is_zero() const {\
    \ return digits.empty(); }\n    bool is_negative() const { return negative; }\n\
    \    BasicBigInteger abs() const { return BasicBigInteger(digits, false); }\n\
    \    BasicBigInteger operator+() const { return *this; }\n    BasicBigInteger\
    \ operator-() const { return BasicBigInteger(digits, !negative); }\n\n    BasicBigInteger\
    \ &operator+=(const BasicBigInteger &other) { return add_signed(other, other.negative);\
    \ }\n    BasicBigInteger &operator-=(const BasicBigInteger &other) { return add_signed(other,\
    \ !other.negative); }\n    BasicBigInteger &operator*=(const BasicBigInteger &other)\
    \ {\n        bool sign = negative != other.negative;\n        digits = Ops::multiply(digits,\
    \ other.digits);\n        negative = sign && !digits.empty();\n        return\
    \ *this;\n    }\n\n    static pair<BasicBigInteger, BasicBigInteger> divmod(const\
    \ BasicBigInteger &a, const BasicBigInteger &b) {\n        auto result = Ops::divide(a.digits,\
    \ b.digits);\n        return {BasicBigInteger(std::move(result.first), a.negative\
    \ != b.negative),\n                BasicBigInteger(std::move(result.second), a.negative)};\n\
    \    }\n\n    static pair<BasicBigInteger, BasicBigInteger> floor_divmod(const\
    \ BasicBigInteger &a, const BasicBigInteger &b) {\n        auto result = divmod(a,\
    \ b);\n        if (!result.second.is_zero() && a.negative != b.negative) {\n \
    \           result.first -= 1;\n            result.second += b;\n        }\n \
    \       return result;\n    }\n\n    BasicBigInteger &operator/=(const BasicBigInteger\
    \ &other) { *this = divmod(*this, other).first; return *this; }\n    BasicBigInteger\
    \ &operator%=(const BasicBigInteger &other) { *this = divmod(*this, other).second;\
    \ return *this; }\n\n    BasicBigInteger &operator<<=(int bits) {\n        assert(bits\
    \ >= 0);\n        if (is_zero() || bits == 0) return *this;\n        if constexpr\
    \ (IO_BASE == 16) {\n            u32 carry = 0;\n            int shift = bits\
    \ % 32;\n            for (u32 &digit : digits) {\n                u64 value =\
    \ (u64(digit) << shift) | carry;\n                digit = u32(value);\n      \
    \          carry = u32(value >> 32);\n            }\n            if (carry) digits.push_back(carry);\n\
    \            digits.insert(digits.begin(), bits / 32, 0);\n        } else if (bits\
    \ < 32) Ops::multiply_small(digits, 1u << bits);\n        else digits = Ops::multiply(digits,\
    \ Ops::power_of_two(bits));\n        return *this;\n    }\n\n    BasicBigInteger\
    \ &operator>>=(int bits) {\n        assert(bits >= 0);\n        if (is_zero()\
    \ || bits == 0) return *this;\n        bool discarded = false;\n        if constexpr\
    \ (IO_BASE == 16) {\n            size_t drop = min(digits.size(), size_t(bits\
    \ / 32));\n            for (size_t i = 0; i < drop; ++i) discarded |= digits[i]\
    \ != 0;\n            digits.erase(digits.begin(), digits.begin() + drop);\n  \
    \          int shift = bits % 32;\n            if (shift) {\n                u32\
    \ carry = 0, mask = (1u << shift) - 1;\n                for (size_t i = digits.size();\
    \ i-- > 0;) {\n                    u32 next = digits[i] & mask;\n            \
    \        digits[i] = (digits[i] >> shift) | (carry << (32 - shift));\n       \
    \             carry = next;\n                }\n                discarded |= carry\
    \ != 0;\n            }\n            Ops::trim(digits);\n        } else if (bits\
    \ < 32) discarded = Ops::divide_small(digits, 1u << bits) != 0;\n        else\
    \ if (u64(bits) >= 27ULL * digits.size()) { digits.clear(); discarded = true;\
    \ }\n        else {\n            auto result = Ops::divide(digits, Ops::power_of_two(bits));\n\
    \            digits = std::move(result.first);\n            discarded = !result.second.empty();\n\
    \        }\n        if (negative && discarded) Ops::increment(digits);\n     \
    \   if (digits.empty()) negative = false;\n        return *this;\n    }\n\n  \
    \  friend BasicBigInteger operator+(BasicBigInteger a, const BasicBigInteger &b)\
    \ { a += b; return a; }\n    friend BasicBigInteger operator-(BasicBigInteger\
    \ a, const BasicBigInteger &b) { a -= b; return a; }\n    friend BasicBigInteger\
    \ operator*(const BasicBigInteger &a, const BasicBigInteger &b) {\n        return\
    \ BasicBigInteger(Ops::multiply(a.digits, b.digits), a.negative != b.negative);\n\
    \    }\n    friend BasicBigInteger operator/(const BasicBigInteger &a, const BasicBigInteger\
    \ &b) { return divmod(a, b).first; }\n    friend BasicBigInteger operator%(const\
    \ BasicBigInteger &a, const BasicBigInteger &b) { return divmod(a, b).second;\
    \ }\n    friend BasicBigInteger operator<<(BasicBigInteger a, int bits) { a <<=\
    \ bits; return a; }\n    friend BasicBigInteger operator>>(BasicBigInteger a,\
    \ int bits) { a >>= bits; return a; }\n    friend bool operator==(const BasicBigInteger\
    \ &a, const BasicBigInteger &b) { return compare(a, b) == 0; }\n    friend bool\
    \ operator!=(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a,\
    \ b) != 0; }\n    friend bool operator<(const BasicBigInteger &a, const BasicBigInteger\
    \ &b) { return compare(a, b) < 0; }\n    friend bool operator<=(const BasicBigInteger\
    \ &a, const BasicBigInteger &b) { return compare(a, b) <= 0; }\n    friend bool\
    \ operator>(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a,\
    \ b) > 0; }\n    friend bool operator>=(const BasicBigInteger &a, const BasicBigInteger\
    \ &b) { return compare(a, b) >= 0; }\n    friend pair<BasicBigInteger, BasicBigInteger>\
    \ divmod(const BasicBigInteger &a, const BasicBigInteger &b) {\n        return\
    \ BasicBigInteger::divmod(a, b);\n    }\n    friend pair<BasicBigInteger, BasicBigInteger>\
    \ floor_divmod(const BasicBigInteger &a, const BasicBigInteger &b) {\n       \
    \ return BasicBigInteger::floor_divmod(a, b);\n    }\n};\n\nusing BigInteger =\
    \ BasicBigInteger<BigIntegerDetail::DecimalRadix>;\nusing HexBigInteger = BasicBigInteger<BigIntegerDetail::HexRadix>;\n\
    \n\n\n/**\n * @brief \u591A\u500D\u9577\u6574\u6570(BigInteger)\n */\n#line 15\
    \ \"test/yosupo_division_of_big_integers.test.cpp\"\n\nint main() {\n    Scanner\
    \ sc;\n    Printer pr;\n    int t;\n    sc.read(t);\n    while (t--) {\n     \
    \   BigInteger x, y;\n        sc.read(x, y);\n        auto qr = divmod(x, y);\n\
    \        pr.println(qr.first, qr.second);\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/division_of_big_integers\"\
    \n\n#include <cassert>\n#include <algorithm>\n#include <cstdio>\n#include <cstring>\n\
    #include <string>\n#include <utility>\n#include <type_traits>\n#include <vector>\n\
    \n#include <charconv>\n#include \"../util/fastio.cpp\"\n#include \"../util/biginteger.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n    int t;\n    sc.read(t);\n\
    \    while (t--) {\n        BigInteger x, y;\n        sc.read(x, y);\n       \
    \ auto qr = divmod(x, y);\n        pr.println(qr.first, qr.second);\n    }\n \
    \   return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - util/biginteger.cpp
  - math/integer_convolution.cpp
  isVerificationFile: true
  path: test/yosupo_division_of_big_integers.test.cpp
  requiredBy: []
  timestamp: '2026-10-12 11:34:48+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_division_of_big_integers.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_division_of_big_integers.test.cpp
- /verify/test/yosupo_division_of_big_integers.test.cpp.html
title: test/yosupo_division_of_big_integers.test.cpp
---
