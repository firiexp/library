---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/convex_hull.cpp
    title: "\u51F8\u5305(Convex Hull)"
  - icon: ':heavy_check_mark:'
    path: geometry/int_point.cpp
    title: "\u6574\u6570\u5EA7\u6A19\u70B9"
  - icon: ':heavy_check_mark:'
    path: geometry/polygon_integral.cpp
    title: "\u591A\u89D2\u5F62\u306E\u533A\u9593\u9762\u7A4D\u3068\u91CD\u5FC3"
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
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"test/yosupo_aplusb_polygon_integral.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\n\
    extern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\ntemplate<class\
    \ T, class = void>\nstruct is_fastio_range : false_type {};\n\ntemplate<class\
    \ T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()), decltype(declval<T\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"geometry/polygon_integral.cpp\"\
    \n\n\n\n#line 1 \"geometry/int_point.cpp\"\n\n\n\nstruct IntPoint {\n    long\
    \ long x = 0, y = 0;\n\n    IntPoint() = default;\n    IntPoint(long long x, long\
    \ long y) : x(x), y(y) {}\n\n    bool operator<(const IntPoint &p) const { return\
    \ x < p.x || (!(p.x < x) && y < p.y); }\n    bool operator==(const IntPoint &p)\
    \ const { return x == p.x && y == p.y; }\n    bool operator!=(const IntPoint &p)\
    \ const { return !(*this == p); }\n    IntPoint &operator+=(const IntPoint &p)\
    \ { x += p.x; y += p.y; return *this; }\n    IntPoint &operator-=(const IntPoint\
    \ &p) { x -= p.x; y -= p.y; return *this; }\n    IntPoint operator+(const IntPoint\
    \ &p) const { return IntPoint(*this) += p; }\n    IntPoint operator-(const IntPoint\
    \ &p) const { return IntPoint(*this) -= p; }\n};\n\n\n\n/**\n * @brief \u6574\u6570\
    \u5EA7\u6A19\u70B9\n */\n#line 5 \"geometry/polygon_integral.cpp\"\n\nclass PolygonIntegral\
    \ {\npublic:\n    struct RationalPoint {\n        __int128 x_num, y_num, den;\n\
    \    };\n\n    class Result {\n        friend class PolygonIntegral;\n\n     \
    \   __int128 area2_ = 0, x_sum = 0, y_sum = 0;\n\n        Result(__int128 area2,\
    \ __int128 x, __int128 y) : area2_(area2), x_sum(x), y_sum(y) {}\n\n    public:\n\
    \        Result() = default;\n\n        __int128 area2() const { return area2_;\
    \ }\n\n        optional<RationalPoint> centroid() const {\n            if (area2_\
    \ == 0) return nullopt;\n            __int128 x = x_sum, y = y_sum, d = area2_;\n\
    \            if (d < 0) {\n                x = -x;\n                y = -y;\n\
    \                d = -d;\n            }\n            return RationalPoint{x, y,\
    \ 3 * d};\n        }\n    };\n\nprivate:\n    vector<IntPoint> points;\n    vector<Result>\
    \ prefix;\n\n    static Result edge(IntPoint a, IntPoint b) {\n        __int128\
    \ d = (__int128)a.x * b.y - (__int128)a.y * b.x;\n        return {d, ((__int128)a.x\
    \ + b.x) * d, ((__int128)a.y + b.y) * d};\n    }\n\n    static Result add(Result\
    \ a, const Result &b) {\n        a.area2_ += b.area2_;\n        a.x_sum += b.x_sum;\n\
    \        a.y_sum += b.y_sum;\n        return a;\n    }\n\npublic:\n    explicit\
    \ PolygonIntegral(const vector<IntPoint> &input) : points(input), prefix(input.size()\
    \ + 1) {\n        int n = points.size();\n        for (int i = 0; i < n; ++i)\n\
    \            prefix[i + 1] = add(prefix[i], edge(points[i], points[(i + 1) % n]));\n\
    \    }\n\n    Result whole() const { return prefix.back(); }\n\n    Result query(int\
    \ u, int v) const {\n        int n = points.size();\n        assert(0 <= u &&\
    \ u < n && 0 <= v && v < n);\n        if (u == v) return {};\n        Result result{prefix[v].area2_\
    \ - prefix[u].area2_,\n                      prefix[v].x_sum - prefix[u].x_sum,\n\
    \                      prefix[v].y_sum - prefix[u].y_sum};\n        if (u > v)\
    \ result = add(result, prefix.back());\n        return add(result, edge(points[v],\
    \ points[u]));\n    }\n};\n\n\n\n/**\n * @brief \u591A\u89D2\u5F62\u306E\u533A\
    \u9593\u9762\u7A4D\u3068\u91CD\u5FC3\n */\n#line 1 \"geometry/convex_hull.cpp\"\
    \n\n\n\n#line 5 \"geometry/convex_hull.cpp\"\n\n__int128 cross(IntPoint a, IntPoint\
    \ b, IntPoint c) {\n    __int128 bx = static_cast<__int128>(b.x) - a.x;\n    __int128\
    \ by = static_cast<__int128>(b.y) - a.y;\n    __int128 cx = static_cast<__int128>(c.x)\
    \ - a.x;\n    __int128 cy = static_cast<__int128>(c.y) - a.y;\n    return bx *\
    \ cy - by * cx;\n}\n\nvector<IntPoint> convex_hull(vector<IntPoint> ps) {\n  \
    \  sort(ps.begin(), ps.end());\n    ps.erase(unique(ps.begin(), ps.end()), ps.end());\n\
    \    int n = ps.size();\n    if (n <= 2) return ps;\n\n    vector<IntPoint> ch(2\
    \ * n);\n    int k = 0;\n    for (int i = 0; i < n; ++i) {\n        while (k >=\
    \ 2 && cross(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;\n        ch[k++] = ps[i];\n\
    \    }\n    for (int i = n - 2, t = k + 1; i >= 0; --i) {\n        while (k >=\
    \ t && cross(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;\n        ch[k++] = ps[i];\n\
    \    }\n    ch.resize(k - 1);\n    return ch;\n}\n\n\n\n/**\n * @brief \u51F8\u5305\
    (Convex Hull)\n */\n#line 9 \"test/yosupo_aplusb_polygon_integral.test.cpp\"\n\
    \nvoid same(PolygonIntegral::RationalPoint a, PolygonIntegral::RationalPoint b)\
    \ {\n    assert(a.x_num == b.x_num && a.y_num == b.y_num && a.den == b.den);\n\
    }\n\nvoid check_result(const PolygonIntegral::Result &actual, const vector<IntPoint>\
    \ &polygon) {\n    __int128 d = 0, x = 0, y = 0;\n    int n = polygon.size();\n\
    \    for (int i = 1; i + 1 < n; ++i) {\n        auto a = polygon[0], b = polygon[i],\
    \ c = polygon[i + 1];\n        __int128 bx = (__int128)b.x - a.x, by = (__int128)b.y\
    \ - a.y;\n        __int128 cx = (__int128)c.x - a.x, cy = (__int128)c.y - a.y;\n\
    \        __int128 area2 = bx * cy - by * cx;\n        d += area2;\n        x +=\
    \ ((__int128)a.x + b.x + c.x) * area2;\n        y += ((__int128)a.y + b.y + c.y)\
    \ * area2;\n    }\n    assert(actual.area2() == d);\n    auto centroid = actual.centroid();\n\
    \    assert(centroid.has_value() == (d != 0));\n    if (centroid) {\n        assert(centroid->den\
    \ > 0);\n        assert(centroid->den == 3 * (d < 0 ? -d : d));\n        assert(centroid->x_num\
    \ == (d < 0 ? -x : x));\n        assert(centroid->y_num == (d < 0 ? -y : y));\n\
    \    }\n}\n\nvoid check(const vector<IntPoint> &points) {\n    auto input = points;\n\
    \    const PolygonIntegral index(input);\n    assert(input == points);\n    input.clear();\n\
    \    check_result(index.whole(), points);\n    int n = points.size();\n    auto\
    \ reversed = points;\n    reverse(reversed.begin(), reversed.end());\n    const\
    \ PolygonIntegral reverse_index(reversed);\n    for (int u = 0; u < n; ++u) for\
    \ (int v = 0; v < n; ++v) {\n        vector<IntPoint> cut{points[u]};\n      \
    \  for (int i = u; i != v;) {\n            i = (i + 1) % n;\n            cut.push_back(points[i]);\n\
    \        }\n        auto result = index.query(u, v);\n        check_result(result,\
    \ cut);\n        auto backward = reverse_index.query(n - 1 - v, n - 1 - u);\n\
    \        assert(backward.area2() == -result.area2());\n        assert(backward.centroid().has_value()\
    \ == result.centroid().has_value());\n        if (result.centroid()) {\n     \
    \       same(*result.centroid(), *backward.centroid());\n        }\n        if\
    \ (u != v) {\n            auto complement = index.query(v, u);\n            assert(result.area2()\
    \ + complement.area2() == index.whole().area2());\n        }\n    }\n}\n\nvoid\
    \ transform_check(const vector<IntPoint> &points) {\n    const PolygonIntegral\
    \ original(points);\n    vector<IntPoint> transformed;\n    for (auto p : points)\
    \ transformed.emplace_back(-3 * p.x + 7, -3 * p.y - 11);\n    const PolygonIntegral\
    \ moved(transformed);\n    int n = points.size();\n    for (int u = 0; u < n;\
    \ ++u) for (int v = 0; v < n; ++v) {\n        auto a = original.query(u, v), b\
    \ = moved.query(u, v);\n        assert(b.area2() == 9 * a.area2());\n        if\
    \ (a.centroid()) {\n            auto p = *a.centroid(), q = *b.centroid();\n \
    \           assert(q.x_num * p.den == (-3 * p.x_num + 7 * p.den) * q.den);\n \
    \           assert(q.y_num * p.den == (-3 * p.y_num - 11 * p.den) * q.den);\n\
    \        } else assert(!b.centroid());\n    }\n    check(transformed);\n}\n\n\
    void self_check() {\n    check({});\n    check({{7, 9}});\n    check({{7, 9},\
    \ {-3, 2}});\n    check({{0, 0}, {1, 1}, {2, 2}, {3, 3}});\n    check({{0, 0},\
    \ {2, 0}, {4, 0}, {4, 2}, {0, 2}});\n    vector<IntPoint> triangle{{0, 0}, {1,\
    \ 0}, {0, 1}};\n    check(triangle);\n    auto small = PolygonIntegral(triangle).whole();\n\
    \    assert(small.area2() == 1);\n    same(*small.centroid(), {1, 1, 3});\n  \
    \  vector<IntPoint> rectangle{{0, 0}, {4, 0}, {4, 2}, {0, 2}};\n    check(rectangle);\n\
    \    const PolygonIntegral index(rectangle);\n    assert(index.whole().area2()\
    \ == 16);\n    same(*index.whole().centroid(), {96, 48, 48});\n    same(*index.query(0,\
    \ 2).centroid(), {64, 16, 24});\n    same(*index.query(2, 0).centroid(), {32,\
    \ 32, 24});\n    auto center = *index.whole().centroid();\n    assert(center.x_num\
    \ == 2 * center.den);\n    assert(center.x_num % center.den == 0);\n    for (long\
    \ long k : {LLONG_MAX - 4, LLONG_MIN + 4}) {\n        check({{k, 0}, {k + 1, 0},\
    \ {k + 1, 1}});\n        check({{0, k}, {0, k + 1}, {1, k + 1}});\n        auto\
    \ wide = PolygonIntegral({{k, 0}, {k + 1, 0}, {k + 1, 1}}).whole();\n        same(*wide.centroid(),\
    \ {(__int128)3 * k + 2, 1, 3});\n    }\n    check({{-1000000000, -1000000000},\
    \ {1000000000, -1000000000},\n           {1000000000, 1000000000}, {-1000000000,\
    \ 1000000000}});\n    mt19937_64 rng(236);\n    for (int tc = 0; tc < 500; ++tc)\
    \ {\n        vector<IntPoint> points(1 + rng() % 30);\n        for (auto &p :\
    \ points) p = {int(rng() % 41) - 20, int(rng() % 41) - 20};\n        points =\
    \ convex_hull(points);\n        check(points);\n        transform_check(points);\n\
    \        reverse(points.begin(), points.end());\n        check(points);\n    }\n\
    }\n\nint main() {\n    self_check();\n    Scanner in;\n    Printer out;\n    int\
    \ a, b;\n    in.read(a, b);\n    out.println(a + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\n#include \"../util/fastio.cpp\"\n#include \"../geometry/polygon_integral.cpp\"\
    \n#include \"../geometry/convex_hull.cpp\"\n\nvoid same(PolygonIntegral::RationalPoint\
    \ a, PolygonIntegral::RationalPoint b) {\n    assert(a.x_num == b.x_num && a.y_num\
    \ == b.y_num && a.den == b.den);\n}\n\nvoid check_result(const PolygonIntegral::Result\
    \ &actual, const vector<IntPoint> &polygon) {\n    __int128 d = 0, x = 0, y =\
    \ 0;\n    int n = polygon.size();\n    for (int i = 1; i + 1 < n; ++i) {\n   \
    \     auto a = polygon[0], b = polygon[i], c = polygon[i + 1];\n        __int128\
    \ bx = (__int128)b.x - a.x, by = (__int128)b.y - a.y;\n        __int128 cx = (__int128)c.x\
    \ - a.x, cy = (__int128)c.y - a.y;\n        __int128 area2 = bx * cy - by * cx;\n\
    \        d += area2;\n        x += ((__int128)a.x + b.x + c.x) * area2;\n    \
    \    y += ((__int128)a.y + b.y + c.y) * area2;\n    }\n    assert(actual.area2()\
    \ == d);\n    auto centroid = actual.centroid();\n    assert(centroid.has_value()\
    \ == (d != 0));\n    if (centroid) {\n        assert(centroid->den > 0);\n   \
    \     assert(centroid->den == 3 * (d < 0 ? -d : d));\n        assert(centroid->x_num\
    \ == (d < 0 ? -x : x));\n        assert(centroid->y_num == (d < 0 ? -y : y));\n\
    \    }\n}\n\nvoid check(const vector<IntPoint> &points) {\n    auto input = points;\n\
    \    const PolygonIntegral index(input);\n    assert(input == points);\n    input.clear();\n\
    \    check_result(index.whole(), points);\n    int n = points.size();\n    auto\
    \ reversed = points;\n    reverse(reversed.begin(), reversed.end());\n    const\
    \ PolygonIntegral reverse_index(reversed);\n    for (int u = 0; u < n; ++u) for\
    \ (int v = 0; v < n; ++v) {\n        vector<IntPoint> cut{points[u]};\n      \
    \  for (int i = u; i != v;) {\n            i = (i + 1) % n;\n            cut.push_back(points[i]);\n\
    \        }\n        auto result = index.query(u, v);\n        check_result(result,\
    \ cut);\n        auto backward = reverse_index.query(n - 1 - v, n - 1 - u);\n\
    \        assert(backward.area2() == -result.area2());\n        assert(backward.centroid().has_value()\
    \ == result.centroid().has_value());\n        if (result.centroid()) {\n     \
    \       same(*result.centroid(), *backward.centroid());\n        }\n        if\
    \ (u != v) {\n            auto complement = index.query(v, u);\n            assert(result.area2()\
    \ + complement.area2() == index.whole().area2());\n        }\n    }\n}\n\nvoid\
    \ transform_check(const vector<IntPoint> &points) {\n    const PolygonIntegral\
    \ original(points);\n    vector<IntPoint> transformed;\n    for (auto p : points)\
    \ transformed.emplace_back(-3 * p.x + 7, -3 * p.y - 11);\n    const PolygonIntegral\
    \ moved(transformed);\n    int n = points.size();\n    for (int u = 0; u < n;\
    \ ++u) for (int v = 0; v < n; ++v) {\n        auto a = original.query(u, v), b\
    \ = moved.query(u, v);\n        assert(b.area2() == 9 * a.area2());\n        if\
    \ (a.centroid()) {\n            auto p = *a.centroid(), q = *b.centroid();\n \
    \           assert(q.x_num * p.den == (-3 * p.x_num + 7 * p.den) * q.den);\n \
    \           assert(q.y_num * p.den == (-3 * p.y_num - 11 * p.den) * q.den);\n\
    \        } else assert(!b.centroid());\n    }\n    check(transformed);\n}\n\n\
    void self_check() {\n    check({});\n    check({{7, 9}});\n    check({{7, 9},\
    \ {-3, 2}});\n    check({{0, 0}, {1, 1}, {2, 2}, {3, 3}});\n    check({{0, 0},\
    \ {2, 0}, {4, 0}, {4, 2}, {0, 2}});\n    vector<IntPoint> triangle{{0, 0}, {1,\
    \ 0}, {0, 1}};\n    check(triangle);\n    auto small = PolygonIntegral(triangle).whole();\n\
    \    assert(small.area2() == 1);\n    same(*small.centroid(), {1, 1, 3});\n  \
    \  vector<IntPoint> rectangle{{0, 0}, {4, 0}, {4, 2}, {0, 2}};\n    check(rectangle);\n\
    \    const PolygonIntegral index(rectangle);\n    assert(index.whole().area2()\
    \ == 16);\n    same(*index.whole().centroid(), {96, 48, 48});\n    same(*index.query(0,\
    \ 2).centroid(), {64, 16, 24});\n    same(*index.query(2, 0).centroid(), {32,\
    \ 32, 24});\n    auto center = *index.whole().centroid();\n    assert(center.x_num\
    \ == 2 * center.den);\n    assert(center.x_num % center.den == 0);\n    for (long\
    \ long k : {LLONG_MAX - 4, LLONG_MIN + 4}) {\n        check({{k, 0}, {k + 1, 0},\
    \ {k + 1, 1}});\n        check({{0, k}, {0, k + 1}, {1, k + 1}});\n        auto\
    \ wide = PolygonIntegral({{k, 0}, {k + 1, 0}, {k + 1, 1}}).whole();\n        same(*wide.centroid(),\
    \ {(__int128)3 * k + 2, 1, 3});\n    }\n    check({{-1000000000, -1000000000},\
    \ {1000000000, -1000000000},\n           {1000000000, 1000000000}, {-1000000000,\
    \ 1000000000}});\n    mt19937_64 rng(236);\n    for (int tc = 0; tc < 500; ++tc)\
    \ {\n        vector<IntPoint> points(1 + rng() % 30);\n        for (auto &p :\
    \ points) p = {int(rng() % 41) - 20, int(rng() % 41) - 20};\n        points =\
    \ convex_hull(points);\n        check(points);\n        transform_check(points);\n\
    \        reverse(points.begin(), points.end());\n        check(points);\n    }\n\
    }\n\nint main() {\n    self_check();\n    Scanner in;\n    Printer out;\n    int\
    \ a, b;\n    in.read(a, b);\n    out.println(a + b);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - geometry/polygon_integral.cpp
  - geometry/int_point.cpp
  - geometry/convex_hull.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_polygon_integral.test.cpp
  requiredBy: []
  timestamp: '2026-10-18 01:50:56+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_polygon_integral.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_polygon_integral.test.cpp
- /verify/test/yosupo_aplusb_polygon_integral.test.cpp.html
title: test/yosupo_aplusb_polygon_integral.test.cpp
---
