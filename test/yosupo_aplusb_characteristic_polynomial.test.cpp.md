---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/characteristic_polynomial.cpp
    title: "\u7279\u6027\u591A\u9805\u5F0F"
  - icon: ':heavy_check_mark:'
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_characteristic_polynomial.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing ll = long long;\nusing ull = unsigned long long;\n\
    using uint = unsigned;\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\n\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"util/modint_base.cpp\"\
    \n\n\n\ntemplate <uint Mod>\nstruct modint {\n    uint val;\npublic:\n    static\
    \ modint raw(int v) { modint x; x.val = v; return x; }\n    static constexpr uint\
    \ get_mod() { return Mod; }\n    static constexpr uint M() { return Mod; }\n \
    \   modint() : val(0) {}\n    template <class T>\n    modint(T v) { ll x = (ll)(v\
    \ % (ll)(Mod)); if (x < 0) x += Mod; val = uint(x); }\n    modint(bool v) { val\
    \ = ((unsigned int)(v) % Mod); }\n    uint &value() noexcept { return val; }\n\
    \    const uint &value() const noexcept { return val; }\n    modint& operator++()\
    \ { val++; if (val == Mod) val = 0; return *this; }\n    modint& operator--()\
    \ { if (val == 0) val = Mod; val--; return *this; }\n    modint operator++(int)\
    \ { modint result = *this; ++*this; return result; }\n    modint operator--(int)\
    \ { modint result = *this; --*this; return result; }\n    modint& operator+=(const\
    \ modint& b) { val += b.val; if (val >= Mod) val -= Mod; return *this; }\n   \
    \ modint& operator-=(const modint& b) { val -= b.val; if (val >= Mod) val += Mod;\
    \ return *this; }\n    modint& operator*=(const modint& b) { ull z = val; z *=\
    \ b.val; val = (uint)(z % Mod); return *this; }\n    modint& operator/=(const\
    \ modint& b) { return *this = *this * b.inv(); }\n    modint operator+() const\
    \ { return *this; }\n    modint operator-() const { return modint() - *this; }\n\
    \    modint pow(long long n) const { modint x = *this, r = 1; while (n) { if (n\
    \ & 1) r *= x; x *= x; n >>= 1; } return r; }\n    modint inv() const { return\
    \ pow(Mod - 2); }\n    friend modint operator+(const modint& a, const modint&\
    \ b) { return modint(a) += b; }\n    friend modint operator-(const modint& a,\
    \ const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\n\n\n#line 1 \"math/characteristic_polynomial.cpp\"\
    \ntemplate<class T>\nvector<T> characteristic_polynomial(vector<vector<T>> a)\
    \ {\n    int n = (int)a.size();\n    for (int k = 0; k + 2 < n; ++k) {\n     \
    \   int pivot = k + 1;\n        while (pivot < n && a[pivot][k] == T(0)) ++pivot;\n\
    \        if (pivot == n) continue;\n        if (pivot != k + 1) {\n          \
    \  swap(a[pivot], a[k + 1]);\n            for (auto& row : a) swap(row[pivot],\
    \ row[k + 1]);\n        }\n        T inv = T(1) / a[k + 1][k];\n        for (int\
    \ i = k + 2; i < n; ++i) {\n            if (a[i][k] == T(0)) continue;\n     \
    \       T factor = a[i][k] * inv;\n            a[i][k] = 0;\n            for (int\
    \ j = k + 1; j < n; ++j) a[i][j] -= factor * a[k + 1][j];\n            for (int\
    \ j = 0; j < n; ++j) a[j][k + 1] += factor * a[j][i];\n        }\n    }\n    vector<vector<T>>\
    \ p(n + 1);\n    p[0] = {T(1)};\n    for (int i = 0; i < n; ++i) {\n        p[i\
    \ + 1].resize(i + 2);\n        for (int j = 0; j <= i; ++j) {\n            p[i\
    \ + 1][j + 1] += p[i][j];\n            p[i + 1][j] -= a[i][i] * p[i][j];\n   \
    \     }\n        T product = 1;\n        for (int k = i - 1; k >= 0; --k) {\n\
    \            if (a[k + 1][k] == T(0)) break;\n            product *= a[k + 1][k];\n\
    \            T factor = product * a[k][i];\n            for (int j = 0; j <= k;\
    \ ++j) p[i + 1][j] -= factor * p[k][j];\n        }\n    }\n    return p[n];\n\
    }\n\n/**\n * @brief \u7279\u6027\u591A\u9805\u5F0F\n */\n#line 11 \"test/yosupo_aplusb_characteristic_polynomial.test.cpp\"\
    \n\ntemplate<class T>\nvector<T> determinant_polynomial(const vector<vector<T>>&\
    \ a) {\n    int n = (int)a.size();\n    vector<int> perm(n);\n    iota(perm.begin(),\
    \ perm.end(), 0);\n    vector<T> result(n + 1);\n    do {\n        int inversions\
    \ = 0;\n        for (int i = 0; i < n; ++i) for (int j = 0; j < i; ++j)\n    \
    \        inversions += perm[j] > perm[i];\n        vector<T> term = {T(inversions\
    \ % 2 ? -1 : 1)};\n        for (int i = 0; i < n; ++i) {\n            vector<T>\
    \ next(term.size() + 1);\n            for (int j = 0; j < (int)term.size(); ++j)\
    \ {\n                next[j] -= a[i][perm[i]] * term[j];\n                if (perm[i]\
    \ == i) next[j + 1] += term[j];\n            }\n            term = std::move(next);\n\
    \        }\n        for (int j = 0; j <= n; ++j) result[j] += term[j];\n    }\
    \ while (next_permutation(perm.begin(), perm.end()));\n    return result;\n}\n\
    \ntemplate<class T>\nvoid check(const vector<vector<T>>& a) {\n    auto original\
    \ = a;\n    auto p = characteristic_polynomial(a);\n    assert(a == original);\n\
    \    assert(p == determinant_polynomial(a));\n    assert(p.size() == a.size()\
    \ + 1 && p.back() == T(1));\n    if (!a.empty()) {\n        T trace = 0;\n   \
    \     for (int i = 0; i < (int)a.size(); ++i) trace += a[i][i];\n        assert(p[a.size()\
    \ - 1] == -trace);\n    }\n}\n\ntemplate<unsigned Mod>\nvoid check_field() {\n\
    \    using T = modint<Mod>;\n    check<T>({});\n    check<T>({{1, 2}, {3, 4}});\n\
    \    assert(characteristic_polynomial<T>({{1, 2}, {3, 4}}) == vector<T>({-2, -5,\
    \ 1}));\n    check<T>({{0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}, {1, 0, 0, 0}});\n\
    \    mt19937 rng(Mod);\n    for (int n = 0; n <= 6; ++n) {\n        vector<vector<T>>\
    \ a(n, vector<T>(n));\n        check(a);\n        for (int i = 0; i < n; ++i)\
    \ a[i][i] = 1;\n        check(a);\n        for (int i = 0; i + 1 < n; ++i) a[i][i\
    \ + 1] = 1;\n        check(a);\n        for (int tc = 0; tc < 70; ++tc) {\n  \
    \          for (auto& row : a) for (auto& x : row) x = rng();\n            check(a);\n\
    \        }\n        for (int split = 1; split < n; ++split) {\n            for\
    \ (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)\n                a[i][j]\
    \ = j + 1 >= i ? T(rng()) : T(0);\n            a[split][split - 1] = 0;\n    \
    \        check(a);\n        }\n    }\n    vector<vector<T>> triangle(30, vector<T>(30));\n\
    \    vector<T> expected = {T(1)};\n    for (int i = 0; i < 30; ++i) {\n      \
    \  for (int j = i; j < 30; ++j) triangle[i][j] = rng();\n        vector<T> next(expected.size()\
    \ + 1);\n        for (int j = 0; j < (int)expected.size(); ++j) {\n          \
    \  next[j + 1] += expected[j];\n            next[j] -= triangle[i][i] * expected[j];\n\
    \        }\n        expected = std::move(next);\n    }\n    assert(characteristic_polynomial(triangle)\
    \ == expected);\n    for (int i = 0; i < 30; ++i) for (int j = 0; j < i; ++j)\n\
    \        swap(triangle[i][j], triangle[j][i]);\n    assert(characteristic_polynomial(triangle)\
    \ == expected);\n}\n\nint main() {\n    check_field<2>();\n    check_field<3>();\n\
    \    check_field<5>();\n    check_field<998244353>();\n    for (int mask = 0;\
    \ mask < 512; ++mask) {\n        vector<vector<modint<2>>> a(3, vector<modint<2>>(3));\n\
    \        for (int i = 0; i < 9; ++i) a[i / 3][i % 3] = mask >> i & 1;\n      \
    \  check(a);\n    }\n    Scanner sc;\n    Printer pr;\n    long long a, b;\n \
    \   sc.read(a, b);\n    pr.println(a + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing ll = long long;\nusing ull = unsigned long long;\n\
    using uint = unsigned;\n#include \"../util/fastio.cpp\"\n#include \"../util/modint_base.cpp\"\
    \n#include \"../math/characteristic_polynomial.cpp\"\n\ntemplate<class T>\nvector<T>\
    \ determinant_polynomial(const vector<vector<T>>& a) {\n    int n = (int)a.size();\n\
    \    vector<int> perm(n);\n    iota(perm.begin(), perm.end(), 0);\n    vector<T>\
    \ result(n + 1);\n    do {\n        int inversions = 0;\n        for (int i =\
    \ 0; i < n; ++i) for (int j = 0; j < i; ++j)\n            inversions += perm[j]\
    \ > perm[i];\n        vector<T> term = {T(inversions % 2 ? -1 : 1)};\n       \
    \ for (int i = 0; i < n; ++i) {\n            vector<T> next(term.size() + 1);\n\
    \            for (int j = 0; j < (int)term.size(); ++j) {\n                next[j]\
    \ -= a[i][perm[i]] * term[j];\n                if (perm[i] == i) next[j + 1] +=\
    \ term[j];\n            }\n            term = std::move(next);\n        }\n  \
    \      for (int j = 0; j <= n; ++j) result[j] += term[j];\n    } while (next_permutation(perm.begin(),\
    \ perm.end()));\n    return result;\n}\n\ntemplate<class T>\nvoid check(const\
    \ vector<vector<T>>& a) {\n    auto original = a;\n    auto p = characteristic_polynomial(a);\n\
    \    assert(a == original);\n    assert(p == determinant_polynomial(a));\n   \
    \ assert(p.size() == a.size() + 1 && p.back() == T(1));\n    if (!a.empty()) {\n\
    \        T trace = 0;\n        for (int i = 0; i < (int)a.size(); ++i) trace +=\
    \ a[i][i];\n        assert(p[a.size() - 1] == -trace);\n    }\n}\n\ntemplate<unsigned\
    \ Mod>\nvoid check_field() {\n    using T = modint<Mod>;\n    check<T>({});\n\
    \    check<T>({{1, 2}, {3, 4}});\n    assert(characteristic_polynomial<T>({{1,\
    \ 2}, {3, 4}}) == vector<T>({-2, -5, 1}));\n    check<T>({{0, 1, 0, 0}, {0, 0,\
    \ 1, 0}, {0, 0, 0, 1}, {1, 0, 0, 0}});\n    mt19937 rng(Mod);\n    for (int n\
    \ = 0; n <= 6; ++n) {\n        vector<vector<T>> a(n, vector<T>(n));\n       \
    \ check(a);\n        for (int i = 0; i < n; ++i) a[i][i] = 1;\n        check(a);\n\
    \        for (int i = 0; i + 1 < n; ++i) a[i][i + 1] = 1;\n        check(a);\n\
    \        for (int tc = 0; tc < 70; ++tc) {\n            for (auto& row : a) for\
    \ (auto& x : row) x = rng();\n            check(a);\n        }\n        for (int\
    \ split = 1; split < n; ++split) {\n            for (int i = 0; i < n; ++i) for\
    \ (int j = 0; j < n; ++j)\n                a[i][j] = j + 1 >= i ? T(rng()) : T(0);\n\
    \            a[split][split - 1] = 0;\n            check(a);\n        }\n    }\n\
    \    vector<vector<T>> triangle(30, vector<T>(30));\n    vector<T> expected =\
    \ {T(1)};\n    for (int i = 0; i < 30; ++i) {\n        for (int j = i; j < 30;\
    \ ++j) triangle[i][j] = rng();\n        vector<T> next(expected.size() + 1);\n\
    \        for (int j = 0; j < (int)expected.size(); ++j) {\n            next[j\
    \ + 1] += expected[j];\n            next[j] -= triangle[i][i] * expected[j];\n\
    \        }\n        expected = std::move(next);\n    }\n    assert(characteristic_polynomial(triangle)\
    \ == expected);\n    for (int i = 0; i < 30; ++i) for (int j = 0; j < i; ++j)\n\
    \        swap(triangle[i][j], triangle[j][i]);\n    assert(characteristic_polynomial(triangle)\
    \ == expected);\n}\n\nint main() {\n    check_field<2>();\n    check_field<3>();\n\
    \    check_field<5>();\n    check_field<998244353>();\n    for (int mask = 0;\
    \ mask < 512; ++mask) {\n        vector<vector<modint<2>>> a(3, vector<modint<2>>(3));\n\
    \        for (int i = 0; i < 9; ++i) a[i / 3][i % 3] = mask >> i & 1;\n      \
    \  check(a);\n    }\n    Scanner sc;\n    Printer pr;\n    long long a, b;\n \
    \   sc.read(a, b);\n    pr.println(a + b);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - util/modint_base.cpp
  - math/characteristic_polynomial.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_characteristic_polynomial.test.cpp
  requiredBy: []
  timestamp: '2026-10-12 10:35:15+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_characteristic_polynomial.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_characteristic_polynomial.test.cpp
- /verify/test/yosupo_aplusb_characteristic_polynomial.test.cpp.html
title: test/yosupo_aplusb_characteristic_polynomial.test.cpp
---
