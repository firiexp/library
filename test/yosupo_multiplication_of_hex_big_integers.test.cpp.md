---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/integer_convolution.cpp
    title: "\u6574\u6570\u7573\u307F\u8FBC\u307F(2/3 NTT)"
  - icon: ':heavy_check_mark:'
    path: util/biginteger.cpp
    title: "\u591A\u500D\u9577\u6574\u6570(BigInteger)"
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/multiplication_of_hex_big_integers
    links:
    - https://judge.yosupo.jp/problem/multiplication_of_hex_big_integers
  bundledCode: "#line 1 \"test/yosupo_multiplication_of_hex_big_integers.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/multiplication_of_hex_big_integers\"\
    \n\n#include <cassert>\n#include <algorithm>\n#include <cstdio>\n#include <cstring>\n\
    #include <string>\n#include <utility>\n#include <type_traits>\n#include <vector>\n\
    \n#include <charconv>\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\nextern\
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
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    static constexpr int DEFAULT_DOUBLE_PRECISION = 15;\n    char buf[BUFSIZE];\n\
    \    int idx;\n    bool interactive;\n    string number_buf;\n    inline static\
    \ constexpr FastIoDigitTable table{};\n\n    Printer() : idx(0), interactive(isatty(fileno(stdout)))\
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
    \ 1 : 0)));\n    }\n\n    inline char *write_top(char *out, unsigned x) {\n  \
    \      if (x >= 1000) {\n            memcpy(out, table.num + (x << 2), 4);\n \
    \           return out + 4;\n        }\n        if (x >= 100) {\n            memcpy(out,\
    \ table.num + (x << 2) + 1, 3);\n            return out + 3;\n        }\n    \
    \    if (x >= 10) {\n            unsigned q = (x * 205) >> 11;\n            out[0]\
    \ = char('0' + q);\n            out[1] = char('0' + (x - q * 10));\n         \
    \   return out + 2;\n        }\n        *out = char('0' + x);\n        return\
    \ out + 1;\n    }\n\n    inline void write_four(char *out, unsigned x) {\n   \
    \     memcpy(out, table.num + (x << 2), 4);\n    }\n\n    inline void write_eight(char\
    \ *out, unsigned x) {\n        unsigned hi = x / 10000;\n        unsigned lo =\
    \ x - hi * 10000;\n        write_four(out, hi);\n        write_four(out + 4, lo);\n\
    \    }\n\n    inline char *write_u32(char *out, unsigned x) {\n        if (x >=\
    \ 100000000) {\n            unsigned hi = x / 100000000;\n            unsigned\
    \ lo = x - hi * 100000000;\n            out = write_top(out, hi);\n          \
    \  write_eight(out, lo);\n            return out + 8;\n        }\n        if (x\
    \ >= 10000) {\n            unsigned hi = x / 10000;\n            unsigned lo =\
    \ x - hi * 10000;\n            out = write_top(out, hi);\n            write_four(out,\
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
    \ long long;\n    using u128 = __uint128_t;\n\n    struct DecimalRadix {\n   \
    \     static constexpr u64 BASE = 10000000000000000ULL;\n        static constexpr\
    \ int IO_BASE = 10;\n        static constexpr int BLOCK_DIGITS = 16;\n       \
    \ static constexpr u32 META_BASE = 10000u;\n        static constexpr int META_DIGITS\
    \ = 4;\n    };\n\n    struct HexRadix {\n        static constexpr u64 BASE = 1ULL\
    \ << 60;\n        static constexpr int IO_BASE = 16;\n        static constexpr\
    \ int BLOCK_DIGITS = 15;\n        static constexpr u32 META_BASE = 1u << 15;\n\
    \        static constexpr int META_DIGITS = 4;\n    };\n}\n\ntemplate<class Radix>\n\
    class BasicBigInteger {\n    using u32 = BigIntegerDetail::u32;\n    using u64\
    \ = BigIntegerDetail::u64;\n    using u128 = BigIntegerDetail::u128;\n\n    static\
    \ constexpr u64 BASE = Radix::BASE;\n    static constexpr int IO_BASE = Radix::IO_BASE;\n\
    \    static constexpr int BLOCK_DIGITS = Radix::BLOCK_DIGITS;\n    static constexpr\
    \ u32 META_BASE = Radix::META_BASE;\n    static constexpr int META_DIGITS = Radix::META_DIGITS;\n\
    \    static constexpr int SCHOOLBOOK_MIN_THRESHOLD = 32;\n    static constexpr\
    \ long long SCHOOLBOOK_AREA_THRESHOLD = 4096;\n\n    vector<u64> digits;\n   \
    \ bool negative;\n\n    static int digit_value(char c) {\n        if ('0' <= c\
    \ && c <= '9') return c - '0';\n        if ('a' <= c && c <= 'z') return c - 'a'\
    \ + 10;\n        if ('A' <= c && c <= 'Z') return c - 'A' + 10;\n        return\
    \ -1;\n    }\n\n    static char digit_char(int x) {\n        return x < 10 ? char('0'\
    \ + x) : char('a' + x - 10);\n    }\n\n    void normalize() {\n        while (!digits.empty()\
    \ && digits.back() == 0) digits.pop_back();\n        if (digits.empty()) negative\
    \ = false;\n    }\n\n    static int compare_abs(const BasicBigInteger &a, const\
    \ BasicBigInteger &b) {\n        if (a.digits.size() != b.digits.size()) {\n \
    \           return a.digits.size() < b.digits.size() ? -1 : 1;\n        }\n  \
    \      for (int i = (int)a.digits.size() - 1; i >= 0; --i) {\n            if (a.digits[i]\
    \ != b.digits[i]) return a.digits[i] < b.digits[i] ? -1 : 1;\n        }\n    \
    \    return 0;\n    }\n\n    static int compare(const BasicBigInteger &a, const\
    \ BasicBigInteger &b) {\n        if (a.negative != b.negative) return a.negative\
    \ ? -1 : 1;\n        int cmp = compare_abs(a, b);\n        return a.negative ?\
    \ -cmp : cmp;\n    }\n\n    void add_abs(const BasicBigInteger &other) {\n   \
    \     if (digits.size() < other.digits.size()) digits.resize(other.digits.size(),\
    \ 0);\n        u64 carry = 0;\n        size_t i = 0;\n        for (; i < other.digits.size();\
    \ ++i) {\n            u128 cur = u128(digits[i]) + other.digits[i] + carry;\n\
    \            if (cur >= BASE) {\n                digits[i] = u64(cur - BASE);\n\
    \                carry = 1;\n            } else {\n                digits[i] =\
    \ u64(cur);\n                carry = 0;\n            }\n        }\n        for\
    \ (; i < digits.size() && carry; ++i) {\n            if (++digits[i] == BASE)\
    \ digits[i] = 0;\n            else carry = 0;\n        }\n        if (carry) digits.push_back(1);\n\
    \    }\n\n    void sub_abs(const BasicBigInteger &other) {\n        u64 borrow\
    \ = 0;\n        for (size_t i = 0; i < digits.size(); ++i) {\n            u128\
    \ rhs = borrow;\n            if (i < other.digits.size()) rhs += other.digits[i];\n\
    \            if (u128(digits[i]) < rhs) {\n                digits[i] = u64(u128(digits[i])\
    \ + BASE - rhs);\n                borrow = 1;\n            } else {\n        \
    \        digits[i] = u64(u128(digits[i]) - rhs);\n                borrow = 0;\n\
    \            }\n        }\n        normalize();\n    }\n\n    void add_small_abs(u64\
    \ value) {\n        assert(value < BASE);\n        if (value == 0) return;\n \
    \       if (digits.empty()) {\n            digits.push_back(value);\n        \
    \    return;\n        }\n        u128 cur = u128(digits[0]) + value;\n       \
    \ digits[0] = u64(cur % BASE);\n        u64 carry = u64(cur / BASE);\n       \
    \ for (size_t i = 1; i < digits.size() && carry; ++i) {\n            if (++digits[i]\
    \ == BASE) digits[i] = 0;\n            else carry = 0;\n        }\n        if\
    \ (carry) digits.push_back(carry);\n    }\n\n    void mul_small_abs(u64 value)\
    \ {\n        assert(value < BASE);\n        if (digits.empty() || value == 1)\
    \ return;\n        if (value == 0) {\n            digits.clear();\n          \
    \  negative = false;\n            return;\n        }\n        u64 carry = 0;\n\
    \        for (u64 &digit : digits) {\n            u128 cur = u128(digit) * value\
    \ + carry;\n            digit = u64(cur % BASE);\n            carry = u64(cur\
    \ / BASE);\n        }\n        if (carry) digits.push_back(carry);\n    }\n\n\
    \    u64 div_small_abs(u64 value) {\n        assert(value != 0 && value < BASE);\n\
    \        u64 remainder = 0;\n        for (int i = (int)digits.size() - 1; i >=\
    \ 0; --i) {\n            u128 cur = u128(remainder) * BASE + digits[i];\n    \
    \        digits[i] = u64(cur / value);\n            remainder = u64(cur % value);\n\
    \        }\n        normalize();\n        return remainder;\n    }\n\n    static\
    \ vector<u64> mul_small_digits(const vector<u64> &src, u64 value) {\n        if\
    \ (src.empty() || value == 0) return {};\n        vector<u64> res;\n        res.reserve(src.size()\
    \ + 1);\n        u64 carry = 0;\n        for (u64 digit : src) {\n           \
    \ u128 cur = u128(digit) * value + carry;\n            res.push_back(u64(cur %\
    \ BASE));\n            carry = u64(cur / BASE);\n        }\n        if (carry)\
    \ res.push_back(carry);\n        return res;\n    }\n\n    static u64 div_small_digits(vector<u64>\
    \ &src, u64 value) {\n        u64 remainder = 0;\n        for (int i = (int)src.size()\
    \ - 1; i >= 0; --i) {\n            u128 cur = u128(remainder) * BASE + src[i];\n\
    \            src[i] = u64(cur / value);\n            remainder = u64(cur % value);\n\
    \        }\n        while (!src.empty() && src.back() == 0) src.pop_back();\n\
    \        return remainder;\n    }\n\n    static vector<u64> mul_schoolbook_digits(const\
    \ vector<u64> &a, const vector<u64> &b) {\n        if (a.empty() || b.empty())\
    \ return {};\n        vector<u64> res(a.size() + b.size(), 0);\n        for (size_t\
    \ i = 0; i < a.size(); ++i) {\n            u64 carry = 0;\n            for (size_t\
    \ j = 0; j < b.size(); ++j) {\n                u128 cur = u128(a[i]) * b[j] +\
    \ res[i + j] + carry;\n                res[i + j] = u64(cur % BASE);\n       \
    \         carry = u64(cur / BASE);\n            }\n            size_t pos = i\
    \ + b.size();\n            while (carry) {\n                u128 cur = u128(res[pos])\
    \ + carry;\n                res[pos] = u64(cur % BASE);\n                carry\
    \ = u64(cur / BASE);\n                ++pos;\n            }\n        }\n     \
    \   while (!res.empty() && res.back() == 0) res.pop_back();\n        return res;\n\
    \    }\n\n    static vector<u32> to_meta_digits(const vector<u64> &src) {\n  \
    \      vector<u32> res(src.size() * META_DIGITS);\n        for (size_t i = 0;\
    \ i < src.size(); ++i) {\n            u64 value = src[i];\n            for (int\
    \ j = 0; j < META_DIGITS; ++j) {\n                res[i * META_DIGITS + j] = u32(value\
    \ % META_BASE);\n                value /= META_BASE;\n            }\n        }\n\
    \        while (!res.empty() && res.back() == 0) res.pop_back();\n        return\
    \ res;\n    }\n\n    static vector<u64> from_meta_digits(const vector<u32> &src)\
    \ {\n        vector<u64> res;\n        res.reserve((src.size() + META_DIGITS -\
    \ 1) / META_DIGITS);\n        for (size_t i = 0; i < src.size(); i += META_DIGITS)\
    \ {\n            u128 value = 0;\n            for (int j = META_DIGITS - 1; j\
    \ >= 0; --j) {\n                value *= META_BASE;\n                size_t index\
    \ = i + (size_t)j;\n                if (index < src.size()) value += src[index];\n\
    \            }\n            res.push_back(u64(value));\n        }\n        while\
    \ (!res.empty() && res.back() == 0) res.pop_back();\n        return res;\n   \
    \ }\n\n    static vector<u64> mul_convolution_digits(const vector<u64> &a, const\
    \ vector<u64> &b) {\n        vector<u32> x = to_meta_digits(a);\n        vector<u32>\
    \ y = to_meta_digits(b);\n        vector<u64> convolution;\n        if (a == b)\
    \ convolution = BoundedConvolution::square_u64(x);\n        else convolution =\
    \ BoundedConvolution::convolution_u64(x, y);\n\n        vector<u32> meta;\n  \
    \      meta.reserve(convolution.size() + 4);\n        u128 carry = 0;\n      \
    \  for (u64 value : convolution) {\n            u128 cur = value + carry;\n  \
    \          meta.push_back(u32(cur % META_BASE));\n            carry = cur / META_BASE;\n\
    \        }\n        while (carry) {\n            meta.push_back(u32(carry % META_BASE));\n\
    \            carry /= META_BASE;\n        }\n        while (!meta.empty() && meta.back()\
    \ == 0) meta.pop_back();\n        return from_meta_digits(meta);\n    }\n\n  \
    \  static BasicBigInteger multiply_abs(const BasicBigInteger &a, const BasicBigInteger\
    \ &b) {\n        BasicBigInteger res;\n        if (a.is_zero() || b.is_zero())\
    \ return res;\n        if (a.digits.size() == 1) {\n            res = b.abs();\n\
    \            res.mul_small_abs(a.digits[0]);\n            return res;\n      \
    \  }\n        if (b.digits.size() == 1) {\n            res = a.abs();\n      \
    \      res.mul_small_abs(b.digits[0]);\n            return res;\n        }\n \
    \       long long area = (long long)a.digits.size() * (long long)b.digits.size();\n\
    \        if ((int)min(a.digits.size(), b.digits.size()) <= SCHOOLBOOK_MIN_THRESHOLD\
    \ ||\n            area <= SCHOOLBOOK_AREA_THRESHOLD) {\n            res.digits\
    \ = mul_schoolbook_digits(a.digits, b.digits);\n        } else {\n           \
    \ res.digits = mul_convolution_digits(a.digits, b.digits);\n        }\n      \
    \  return res;\n    }\n\n    void pad_inplace(size_t count) {\n        if (!digits.empty()\
    \ && count) digits.insert(digits.begin(), count, 0);\n    }\n\n    BasicBigInteger\
    \ pad(size_t count) const {\n        BasicBigInteger res = *this;\n        res.pad_inplace(count);\n\
    \        return res;\n    }\n\n    void drop_inplace(size_t count) {\n       \
    \ if (count >= digits.size()) {\n            digits.clear();\n            negative\
    \ = false;\n            return;\n        }\n        digits.erase(digits.begin(),\
    \ digits.begin() + (int)count);\n        normalize();\n    }\n\n    BasicBigInteger\
    \ top(size_t count) const {\n        BasicBigInteger res = *this;\n        if\
    \ (count >= res.digits.size()) res.pad_inplace(count - res.digits.size());\n \
    \       else res.drop_inplace(res.digits.size() - count);\n        return res;\n\
    \    }\n\n    static BasicBigInteger divmod_knuth_abs(const BasicBigInteger &a,\n\
    \                                             const BasicBigInteger &b,\n    \
    \                                         BasicBigInteger &remainder) {\n    \
    \    assert(!b.is_zero());\n        if (compare_abs(a, b) < 0) {\n           \
    \ remainder = a;\n            return BasicBigInteger();\n        }\n        if\
    \ (b.digits.size() == 1) {\n            BasicBigInteger quotient = a;\n      \
    \      u64 rem = quotient.div_small_abs(b.digits[0]);\n            remainder =\
    \ BasicBigInteger((long long)rem);\n            return quotient;\n        }\n\n\
    \        u64 norm = BASE / (b.digits.back() + 1);\n        vector<u64> un = norm\
    \ == 1 ? a.digits : mul_small_digits(a.digits, norm);\n        vector<u64> vn\
    \ = norm == 1 ? b.digits : mul_small_digits(b.digits, norm);\n        size_t n\
    \ = vn.size();\n        size_t m = un.size() - n;\n        un.push_back(0);\n\n\
    \        BasicBigInteger quotient;\n        quotient.digits.assign(m + 1, 0);\n\
    \        for (size_t jj = m + 1; jj-- > 0;) {\n            size_t j = jj;\n  \
    \          u128 numerator = u128(un[j + n]) * BASE + un[j + n - 1];\n        \
    \    u128 qhat = numerator / vn[n - 1];\n            u128 rhat = numerator % vn[n\
    \ - 1];\n            if (qhat == BASE) {\n                --qhat;\n          \
    \      rhat += vn[n - 1];\n            }\n            if (n >= 2) {\n        \
    \        while (rhat < BASE &&\n                       qhat * vn[n - 2] > rhat\
    \ * BASE + un[j + n - 2]) {\n                    --qhat;\n                   \
    \ rhat += vn[n - 1];\n                }\n            }\n\n            u64 carry\
    \ = 0;\n            u64 borrow = 0;\n            for (size_t i = 0; i < n; ++i)\
    \ {\n                u128 product = qhat * vn[i] + carry;\n                carry\
    \ = u64(product / BASE);\n                u128 sub = product % BASE + borrow;\n\
    \                if (u128(un[j + i]) < sub) {\n                    un[j + i] =\
    \ u64(u128(un[j + i]) + BASE - sub);\n                    borrow = 1;\n      \
    \          } else {\n                    un[j + i] = u64(u128(un[j + i]) - sub);\n\
    \                    borrow = 0;\n                }\n            }\n\n       \
    \     u128 sub = u128(carry) + borrow;\n            bool underflow = u128(un[j\
    \ + n]) < sub;\n            if (underflow) un[j + n] = u64(u128(un[j + n]) + BASE\
    \ - sub);\n            else un[j + n] = u64(u128(un[j + n]) - sub);\n\n      \
    \      if (underflow) {\n                --qhat;\n                u64 add_carry\
    \ = 0;\n                for (size_t i = 0; i < n; ++i) {\n                   \
    \ u128 cur = u128(un[j + i]) + vn[i] + add_carry;\n                    if (cur\
    \ >= BASE) {\n                        un[j + i] = u64(cur - BASE);\n         \
    \               add_carry = 1;\n                    } else {\n               \
    \         un[j + i] = u64(cur);\n                        add_carry = 0;\n    \
    \                }\n                }\n                un[j + n] = u64(u128(un[j\
    \ + n]) + add_carry);\n            }\n            quotient.digits[j] = u64(qhat);\n\
    \        }\n\n        quotient.normalize();\n        remainder.digits.assign(un.begin(),\
    \ un.begin() + n);\n        if (norm != 1) div_small_digits(remainder.digits,\
    \ norm);\n        remainder.normalize();\n        return quotient;\n    }\n\n\
    \    struct Scaled {\n        BasicBigInteger value;\n        long long scale;\n\
    \n        Scaled(long long value_ = 0, long long scale_ = 0) : value(value_),\
    \ scale(scale_) {}\n        Scaled(BasicBigInteger value_, long long scale_ =\
    \ 0)\n            : value(std::move(value_)), scale(scale_) {}\n\n        Scaled\
    \ &operator*=(const Scaled &other) {\n            value *= other.value;\n    \
    \        scale += other.scale;\n            return *this;\n        }\n\n     \
    \   Scaled &operator+=(const Scaled &other) {\n            if (scale < other.scale)\
    \ {\n                value += other.value.pad((size_t)(other.scale - scale));\n\
    \            } else {\n                value.pad_inplace((size_t)(scale - other.scale));\n\
    \                value += other.value;\n                scale = other.scale;\n\
    \            }\n            return *this;\n        }\n\n        Scaled &operator-=(const\
    \ Scaled &other) {\n            if (scale < other.scale) {\n                value\
    \ -= other.value.pad((size_t)(other.scale - scale));\n            } else {\n \
    \               value.pad_inplace((size_t)(scale - other.scale));\n          \
    \      value -= other.value;\n                scale = other.scale;\n         \
    \   }\n            return *this;\n        }\n\n        friend Scaled operator*(Scaled\
    \ lhs, const Scaled &rhs) { return lhs *= rhs; }\n        friend Scaled operator+(Scaled\
    \ lhs, const Scaled &rhs) { return lhs += rhs; }\n        friend Scaled operator-(Scaled\
    \ lhs, const Scaled &rhs) { return lhs -= rhs; }\n\n        BasicBigInteger round()\
    \ const {\n            if (scale >= 0) return value.pad((size_t)scale);\n    \
    \        if (-scale > (long long)value.digits.size()) return BasicBigInteger();\n\
    \            BasicBigInteger res = value.top(value.digits.size() - (size_t)(-scale));\n\
    \            if (value.digits[(size_t)(-scale - 1)] * 2 >= BASE) res += 1;\n \
    \           return res;\n        }\n\n        Scaled trunc(size_t count) const\
    \ {\n            count = min(count, value.digits.size());\n            return\
    \ Scaled(value.top(count), scale + (long long)value.digits.size() - (long long)count);\n\
    \        }\n\n        long long magnitude() const {\n            static constexpr\
    \ long long NEG_INF = -(1LL << 60);\n            if (value.is_zero()) return NEG_INF;\n\
    \            return (long long)value.digits.size() + scale;\n        }\n\n   \
    \     Scaled inv(long long precision) const {\n            assert(precision >=\
    \ 0 && !value.is_zero());\n            long double estimate = (long double)BASE\
    \ / (long double)value.digits.back();\n            long long lead = (long long)(estimate\
    \ + 0.5L);\n            Scaled result(BasicBigInteger(lead), -(long long)value.digits.size());\n\
    \            size_t current = 2;\n            Scaled amend = Scaled(1) - trunc(current)\
    \ * result;\n            while (-amend.magnitude() < precision) {\n          \
    \      result += result * amend;\n                current = 2 * (size_t)(1 - amend.magnitude());\n\
    \                result = result.trunc(current);\n                amend = Scaled(1)\
    \ - trunc(current) * result;\n            }\n            return result;\n    \
    \    }\n    };\n\n    static bool divmod_reciprocal_abs(const BasicBigInteger\
    \ &a,\n                                       const BasicBigInteger &b,\n    \
    \                                   BasicBigInteger &quotient,\n             \
    \                          BasicBigInteger &remainder) {\n        Scaled A(a);\n\
    \        Scaled B(b);\n        long long precision = A.magnitude() - B.magnitude()\
    \ + 1;\n        if (precision < 0) precision = 0;\n        quotient = (A * B.inv(precision)).round();\n\
    \        remainder = a - quotient * b;\n\n        int correction = 0;\n      \
    \  while (remainder.is_negative()) {\n            if (++correction > 8) return\
    \ false;\n            quotient -= 1;\n            remainder += b;\n        }\n\
    \        while (remainder >= b) {\n            if (++correction > 8) return false;\n\
    \            quotient += 1;\n            remainder -= b;\n        }\n        return\
    \ !quotient.is_negative() && !remainder.is_negative() && remainder < b;\n    }\n\
    \n    static pair<BasicBigInteger, BasicBigInteger> divmod_abs(const BasicBigInteger\
    \ &a,\n                                                              const BasicBigInteger\
    \ &b) {\n        assert(!b.is_zero());\n        if (compare_abs(a, b) < 0) return\
    \ {BasicBigInteger(), a};\n        if (b.digits.size() == 1) {\n            BasicBigInteger\
    \ quotient = a;\n            u64 remainder = quotient.div_small_abs(b.digits[0]);\n\
    \            return {quotient, BasicBigInteger((long long)remainder)};\n     \
    \   }\n\n        size_t quotient_size = a.digits.size() - b.digits.size() + 1;\n\
    \        if (b.digits.size() >= 4 && quotient_size >= 3) {\n            BasicBigInteger\
    \ quotient, remainder;\n            if (divmod_reciprocal_abs(a, b, quotient,\
    \ remainder)) {\n                return {std::move(quotient), std::move(remainder)};\n\
    \            }\n        }\n        BasicBigInteger remainder;\n        BasicBigInteger\
    \ quotient = divmod_knuth_abs(a, b, remainder);\n        return {std::move(quotient),\
    \ std::move(remainder)};\n    }\n\n    static pair<int, u64> shift_chunk() {\n\
    \        int bits = 0;\n        u64 value = 1;\n        while (bits < 62 && value\
    \ <= (BASE - 1) / 2) {\n            value *= 2;\n            ++bits;\n       \
    \ }\n        return {bits, value};\n    }\n\n    static void append_in_base(string\
    \ &out, u64 value, int base, int width) {\n        char buffer[70];\n        int\
    \ pos = 70;\n        do {\n            buffer[--pos] = digit_char((int)(value\
    \ % (u64)base));\n            value /= (u64)base;\n        } while (value);\n\
    \        int length = 70 - pos;\n        while (length < width) {\n          \
    \  out.push_back('0');\n            ++length;\n        }\n        out.append(buffer\
    \ + pos, buffer + 70);\n    }\n\npublic:\n    BasicBigInteger() : digits(), negative(false)\
    \ {}\n\n    BasicBigInteger(long long value) : digits(), negative(false) {\n \
    \       *this = value;\n    }\n\n    BasicBigInteger(const string &value, int\
    \ base = IO_BASE) : digits(), negative(false) {\n        bool ok = assign(value,\
    \ base);\n        assert(ok);\n        (void)ok;\n    }\n\n    BasicBigInteger\
    \ &operator=(long long value) {\n        digits.clear();\n        negative = value\
    \ < 0;\n        u64 magnitude = value < 0 ? u64(-(value + 1)) + 1 : u64(value);\n\
    \        while (magnitude) {\n            digits.push_back(magnitude % BASE);\n\
    \            magnitude /= BASE;\n        }\n        normalize();\n        return\
    \ *this;\n    }\n\n    bool assign(const string &value, int base = IO_BASE) {\n\
    \        digits.clear();\n        negative = false;\n        if (base < 2 || base\
    \ > 36 || value.empty()) return false;\n\n        int begin = 0;\n        bool\
    \ is_negative = false;\n        if (value[begin] == '+' || value[begin] == '-')\
    \ {\n            is_negative = value[begin] == '-';\n            if (++begin ==\
    \ (int)value.size()) return false;\n        }\n        for (int i = begin; i <\
    \ (int)value.size(); ++i) {\n            int digit = digit_value(value[i]);\n\
    \            if (digit < 0 || digit >= base) {\n                digits.clear();\n\
    \                negative = false;\n                return false;\n          \
    \  }\n        }\n        while (begin < (int)value.size() && value[begin] == '0')\
    \ ++begin;\n        if (begin == (int)value.size()) return true;\n\n        if\
    \ (base == IO_BASE) {\n            for (int right = (int)value.size(); right >\
    \ begin; right -= BLOCK_DIGITS) {\n                int left = max(begin, right\
    \ - BLOCK_DIGITS);\n                u64 block = 0;\n                for (int i\
    \ = left; i < right; ++i) {\n                    block = block * (u64)base + (u64)digit_value(value[i]);\n\
    \                }\n                digits.push_back(block);\n            }\n\
    \        } else {\n            u64 chunk_base = 1;\n            int chunk_digits\
    \ = 0;\n            while (chunk_base <= (BASE - 1) / (u64)base) {\n         \
    \       chunk_base *= (u64)base;\n                ++chunk_digits;\n          \
    \  }\n            int first = ((int)value.size() - begin) % chunk_digits;\n  \
    \          if (first == 0) first = chunk_digits;\n            for (int pos = begin;\
    \ pos < (int)value.size();) {\n                int width = pos == begin ? first\
    \ : chunk_digits;\n                u64 block = 0;\n                u64 power =\
    \ 1;\n                for (int i = 0; i < width; ++i) {\n                    block\
    \ = block * (u64)base + (u64)digit_value(value[pos + i]);\n                  \
    \  power *= (u64)base;\n                }\n                mul_small_abs(power);\n\
    \                add_small_abs(block);\n                pos += width;\n      \
    \      }\n        }\n        negative = is_negative;\n        normalize();\n \
    \       return true;\n    }\n\n    string to_string(int base = IO_BASE) const\
    \ {\n        assert(2 <= base && base <= 36);\n        if (is_zero()) return \"\
    0\";\n        string out;\n        if (negative) out.push_back('-');\n\n     \
    \   if (base == IO_BASE) {\n            append_in_base(out, digits.back(), base,\
    \ 0);\n            for (int i = (int)digits.size() - 2; i >= 0; --i) {\n     \
    \           append_in_base(out, digits[i], base, BLOCK_DIGITS);\n            }\n\
    \            return out;\n        }\n\n        u64 chunk_base = 1;\n        int\
    \ chunk_digits = 0;\n        while (chunk_base <= (BASE - 1) / (u64)base) {\n\
    \            chunk_base *= (u64)base;\n            ++chunk_digits;\n        }\n\
    \        BasicBigInteger value = abs();\n        vector<u64> parts;\n        while\
    \ (!value.is_zero()) parts.push_back(value.div_small_abs(chunk_base));\n     \
    \   append_in_base(out, parts.back(), base, 0);\n        for (int i = (int)parts.size()\
    \ - 2; i >= 0; --i) {\n            append_in_base(out, parts[i], base, chunk_digits);\n\
    \        }\n        return out;\n    }\n\n    bool is_zero() const { return digits.empty();\
    \ }\n    bool is_negative() const { return negative; }\n\n    BasicBigInteger\
    \ abs() const {\n        BasicBigInteger res = *this;\n        res.negative =\
    \ false;\n        return res;\n    }\n\n    BasicBigInteger operator+() const\
    \ { return *this; }\n\n    BasicBigInteger operator-() const {\n        BasicBigInteger\
    \ res = *this;\n        if (!res.is_zero()) res.negative = !res.negative;\n  \
    \      return res;\n    }\n\n    BasicBigInteger &operator+=(const BasicBigInteger\
    \ &other) {\n        if (other.is_zero()) return *this;\n        if (is_zero())\
    \ {\n            *this = other;\n            return *this;\n        }\n      \
    \  if (negative == other.negative) {\n            add_abs(other);\n          \
    \  return *this;\n        }\n        int cmp = compare_abs(*this, other);\n  \
    \      if (cmp == 0) {\n            digits.clear();\n            negative = false;\n\
    \        } else if (cmp > 0) {\n            sub_abs(other);\n        } else {\n\
    \            BasicBigInteger res = other;\n            res.sub_abs(*this);\n \
    \           *this = std::move(res);\n        }\n        return *this;\n    }\n\
    \n    BasicBigInteger &operator-=(const BasicBigInteger &other) {\n        return\
    \ *this += -other;\n    }\n\n    BasicBigInteger &operator*=(const BasicBigInteger\
    \ &other) {\n        if (is_zero() || other.is_zero()) {\n            digits.clear();\n\
    \            negative = false;\n            return *this;\n        }\n       \
    \ bool result_negative = negative != other.negative;\n        BasicBigInteger\
    \ result = multiply_abs(*this, other);\n        result.negative = result_negative;\n\
    \        *this = std::move(result);\n        return *this;\n    }\n\n    friend\
    \ BasicBigInteger operator+(BasicBigInteger lhs, const BasicBigInteger &rhs) {\
    \ return lhs += rhs; }\n    friend BasicBigInteger operator-(BasicBigInteger lhs,\
    \ const BasicBigInteger &rhs) { return lhs -= rhs; }\n    friend BasicBigInteger\
    \ operator*(BasicBigInteger lhs, const BasicBigInteger &rhs) { return lhs *= rhs;\
    \ }\n\n    friend bool operator==(const BasicBigInteger &a, const BasicBigInteger\
    \ &b) { return compare(a, b) == 0; }\n    friend bool operator!=(const BasicBigInteger\
    \ &a, const BasicBigInteger &b) { return compare(a, b) != 0; }\n    friend bool\
    \ operator<(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a,\
    \ b) < 0; }\n    friend bool operator<=(const BasicBigInteger &a, const BasicBigInteger\
    \ &b) { return compare(a, b) <= 0; }\n    friend bool operator>(const BasicBigInteger\
    \ &a, const BasicBigInteger &b) { return compare(a, b) > 0; }\n    friend bool\
    \ operator>=(const BasicBigInteger &a, const BasicBigInteger &b) { return compare(a,\
    \ b) >= 0; }\n\n    static pair<BasicBigInteger, BasicBigInteger> divmod(const\
    \ BasicBigInteger &a,\n                                                      \
    \   const BasicBigInteger &b) {\n        assert(!b.is_zero());\n        auto result\
    \ = divmod_abs(a.abs(), b.abs());\n        if (!result.first.is_zero()) result.first.negative\
    \ = a.negative != b.negative;\n        if (!result.second.is_zero()) result.second.negative\
    \ = a.negative;\n        return result;\n    }\n\n    static pair<BasicBigInteger,\
    \ BasicBigInteger> floor_divmod(const BasicBigInteger &a,\n                  \
    \                                             const BasicBigInteger &b) {\n  \
    \      auto result = divmod(a, b);\n        if (!result.second.is_zero() && a.negative\
    \ != b.negative) {\n            result.first -= 1;\n            result.second\
    \ += b;\n        }\n        return result;\n    }\n\n    friend pair<BasicBigInteger,\
    \ BasicBigInteger> divmod(const BasicBigInteger &a,\n                        \
    \                                 const BasicBigInteger &b) {\n        return\
    \ BasicBigInteger::divmod(a, b);\n    }\n\n    friend pair<BasicBigInteger, BasicBigInteger>\
    \ floor_divmod(const BasicBigInteger &a,\n                                   \
    \                            const BasicBigInteger &b) {\n        return BasicBigInteger::floor_divmod(a,\
    \ b);\n    }\n\n    BasicBigInteger &operator/=(const BasicBigInteger &other)\
    \ {\n        *this = divmod(*this, other).first;\n        return *this;\n    }\n\
    \n    BasicBigInteger &operator%=(const BasicBigInteger &other) {\n        *this\
    \ = divmod(*this, other).second;\n        return *this;\n    }\n\n    BasicBigInteger\
    \ &operator<<=(int bits) {\n        assert(bits >= 0);\n        if (is_zero()\
    \ || bits == 0) return *this;\n        auto chunk = shift_chunk();\n        while\
    \ (bits) {\n            int take = min(bits, chunk.first);\n            mul_small_abs(1ULL\
    \ << take);\n            bits -= take;\n        }\n        return *this;\n   \
    \ }\n\n    BasicBigInteger &operator>>=(int bits) {\n        assert(bits >= 0);\n\
    \        if (is_zero() || bits == 0) return *this;\n        bool was_negative\
    \ = negative;\n        bool discarded = false;\n        auto chunk = shift_chunk();\n\
    \        while (bits && !is_zero()) {\n            int take = min(bits, chunk.first);\n\
    \            discarded |= div_small_abs(1ULL << take) != 0;\n            bits\
    \ -= take;\n        }\n        if (was_negative && discarded) {\n            add_small_abs(1);\n\
    \            negative = true;\n        }\n        normalize();\n        return\
    \ *this;\n    }\n\n    friend BasicBigInteger operator/(BasicBigInteger lhs, const\
    \ BasicBigInteger &rhs) { return lhs /= rhs; }\n    friend BasicBigInteger operator%(BasicBigInteger\
    \ lhs, const BasicBigInteger &rhs) { return lhs %= rhs; }\n    friend BasicBigInteger\
    \ operator<<(BasicBigInteger lhs, int bits) { return lhs <<= bits; }\n    friend\
    \ BasicBigInteger operator>>(BasicBigInteger lhs, int bits) { return lhs >>= bits;\
    \ }\n};\n\nusing BigInteger = BasicBigInteger<BigIntegerDetail::DecimalRadix>;\n\
    using HexBigInteger = BasicBigInteger<BigIntegerDetail::HexRadix>;\n\n\n\n/**\n\
    \ * @brief \u591A\u500D\u9577\u6574\u6570(BigInteger)\n */\n#line 15 \"test/yosupo_multiplication_of_hex_big_integers.test.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n    auto to_upper_hex = [](string\
    \ s) {\n        for (char &c : s) {\n            if ('a' <= c && c <= 'f') c =\
    \ char(c - 'a' + 'A');\n        }\n        return s;\n    };\n    int t;\n   \
    \ sc.read(t);\n    while (t--) {\n        HexBigInteger x, y;\n        sc.read(x,\
    \ y);\n        pr.println(to_upper_hex((x * y).to_string(16)));\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/multiplication_of_hex_big_integers\"\
    \n\n#include <cassert>\n#include <algorithm>\n#include <cstdio>\n#include <cstring>\n\
    #include <string>\n#include <utility>\n#include <type_traits>\n#include <vector>\n\
    \n#include <charconv>\n#include \"../util/fastio.cpp\"\n#include \"../util/biginteger.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n    auto to_upper_hex = [](string\
    \ s) {\n        for (char &c : s) {\n            if ('a' <= c && c <= 'f') c =\
    \ char(c - 'a' + 'A');\n        }\n        return s;\n    };\n    int t;\n   \
    \ sc.read(t);\n    while (t--) {\n        HexBigInteger x, y;\n        sc.read(x,\
    \ y);\n        pr.println(to_upper_hex((x * y).to_string(16)));\n    }\n    return\
    \ 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - util/biginteger.cpp
  - math/integer_convolution.cpp
  isVerificationFile: true
  path: test/yosupo_multiplication_of_hex_big_integers.test.cpp
  requiredBy: []
  timestamp: '2026-08-02 21:15:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_multiplication_of_hex_big_integers.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_multiplication_of_hex_big_integers.test.cpp
- /verify/test/yosupo_multiplication_of_hex_big_integers.test.cpp.html
title: test/yosupo_multiplication_of_hex_big_integers.test.cpp
---
