---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/lyndon_factorization.cpp
    title: "Lyndon\u5206\u89E3(Lyndon Factorization)"
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash.cpp
    title: Rolling Hash
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash_ull.cpp
    title: Rolling Hash(mod 2^61-1)
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  - icon: ':heavy_check_mark:'
    path: util/xorshift.cpp
    title: Xor-Shift
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_string_bytes.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\nusing\
    \ namespace std;\nusing ll = long long;\nusing ull = unsigned long long;\n#line\
    \ 1 \"util/fastio.cpp\"\nusing namespace std;\n\nextern \"C\" int fileno(FILE\
    \ *);\nextern \"C\" int isatty(int);\n\ntemplate<class T, class = void>\nstruct\
    \ is_fastio_range : false_type {};\n\ntemplate<class T>\nstruct is_fastio_range<T,\
    \ void_t<decltype(declval<T &>().begin()), decltype(declval<T &>().end())>> :\
    \ true_type {};\n\ntemplate<class T, class = void>\nstruct has_fastio_value :\
    \ false_type {};\n\ntemplate<class T>\nstruct has_fastio_value<T, void_t<decltype(declval<const\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"util/xorshift.cpp\"\
    \nclass xor_shift {\n    uint32_t x, y, z, w;\npublic:\n    xor_shift() : x(static_cast<uint32_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL\
    \ << 32)-1))),\n    y(1068246329), z(321908594), w(1234567890) {};\n\n    uint32_t\
    \ urand(){\n        uint32_t t;\n        t = x ^ (x << 11);\n        x = y; y\
    \ = z; z = w;\n        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n        return w;\n\
    \    };\n\n    int rand(int n){\n        return rand(0, n);\n    }\n\n    int\
    \ rand(int a, int b){\n        if(a > b) swap(a, b);\n        uint64_t width =\
    \ int64_t(b) - int64_t(a) + 1;\n        uint64_t limit = (uint64_t(1) << 32) /\
    \ width * width;\n        uint64_t e = urand();\n        while(e >= limit) e =\
    \ urand();\n        return static_cast<int>(int64_t(a) + int64_t(e % width));\n\
    \    }\n};\n#line 2 \"string/rolling_hash.cpp\"\nxor_shift rd;\n\ntemplate<int\
    \ M>\nstruct rolling_hash {\n\n    static ll &B() {\n        static ll B_ = rd.rand(2,\
    \ M-1);\n        return B_;\n    }\n    static vector<ll> &p() {\n        static\
    \ vector<ll> p_{1, B()};\n        return p_;\n    }\n\n    vector<ll> hash;\n\
    \    explicit rolling_hash(const string &s) {\n        if(p().size() <= s.size()){\n\
    \            int l = p().size();\n            p().resize(s.size()+1);\n      \
    \      for (int i = l; i < p().size(); ++i) {\n                p()[i] = (p()[i-1]*p()[1])%M;\n\
    \            }\n        }\n        hash.resize(s.size()+1, 0);\n        for (int\
    \ i = 0; i < s.size(); ++i) {\n            hash[i+1] = (hash[i]*B() + (unsigned\
    \ char)s[i]) % M;\n        }\n    };\n\n    ll get(int l, int r){\n        ll\
    \ res = hash[r]+M-hash[l]*p()[r-l]%M;\n        return res >= M ? res-M : res;\n\
    \    }\n};\n\n/**\n * @brief Rolling Hash\n */\n#line 1 \"string/rolling_hash_ull.cpp\"\
    \nconstexpr ull M = (1UL << 61) - 1;\nconstexpr ull POSITIVISER = M * 4; // mul\
    \ returns an unreduced value below 4*M.\nconstexpr ull MASK30 = (1UL << 30) -\
    \ 1;\nconstexpr ull MASK31 = (1UL << 31) - 1;\n\nclass rolling_hash_ull {\n  \
    \  static ull get_base(){\n        ull z = (static_cast<uint64_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL\
    \ << 32)-1)))+0x9e3779b97f4a7c15;\n        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n\
    \        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;\n        return z;\n    }\n\
    \n    static inline ull calc_mod(ull val){\n        val = (val & M) + (val >>\
    \ 61);\n        if(val >= M) val -= M;\n        return val;\n    }\npublic:\n\
    \    vector<ull> hash;\n\n    static ull &B() {\n        static ull B_ = (get_base())%(M-2)+2;\n\
    \        return B_;\n    }\n\n    static vector<ull> &p() {\n        static vector<ull>\
    \ p_{1, B()};\n        return p_;\n    }\n\n    static inline ull mul(ull x, ull\
    \ y){\n        ull a = x >> 31, b = x & MASK31, c = y >> 31, d = y & MASK31, e\
    \ = b*c+a*d;\n        return (a*c << 1) + b*d + ((e & MASK30) << 31) + (e >> 30);\n\
    \    }\n\n    rolling_hash_ull(const string &s) {\n        if(p().size() <= s.size()){\n\
    \            int l = p().size();\n            p().resize(s.size()+1);\n      \
    \      for (int i = l; i < p().size(); ++i) {\n                p()[i] = calc_mod(mul(p()[i-1],\
    \ p()[1]));\n            }\n        }\n        hash.resize(s.size()+1, 0);\n \
    \       for (int i = 0; i < s.size(); ++i) {\n            hash[i+1] = calc_mod(mul(hash[i],B())\
    \ + (unsigned char)s[i]);\n        }\n    };\n\n    rolling_hash_ull(const int&\
    \ n){\n        int l = p().size();\n        if(n < l) return;\n        p().resize(n+1);\n\
    \        for (int i = l; i < p().size(); ++i) {\n            p()[i] = calc_mod(mul(p()[i-1],\
    \ p()[1]));\n        }\n    }\n\n    ull get(int l, int r){\n        return calc_mod(hash[r]\
    \ + POSITIVISER - mul(hash[l], p()[r-l]));\n    }\n\n    static ull val(string\
    \ &s){\n        if(p().size() <= s.size()){\n            int l = p().size();\n\
    \            p().resize(s.size()+1);\n            for (int i = l; i < p().size();\
    \ ++i) {\n                p()[i] = calc_mod(mul(p()[i-1], p()[1]));\n        \
    \    }\n        }\n        ull ret = 0;\n        for (int i = 0; i < s.size();\
    \ ++i) {\n            ret = calc_mod(mul(ret, B()) + (unsigned char)s[i]);\n \
    \       }\n        return ret;\n    }\n};\n\n/**\n * @brief Rolling Hash(mod 2^61-1)\n\
    \ */\n#line 1 \"string/lyndon_factorization.cpp\"\nusing namespace std;\n\nvector<pair<int,\
    \ int>> lyndon_factorization(const string &s) {\n    int n = (int)s.size();\n\
    \    vector<pair<int, int>> res;\n    for (int i = 0; i < n;) {\n        int j\
    \ = i + 1, k = i;\n        while (j < n && (unsigned char)s[k] <= (unsigned char)s[j])\
    \ {\n            if ((unsigned char)s[k] < (unsigned char)s[j]) k = i;\n     \
    \       else ++k;\n            ++j;\n        }\n        int len = j - k;\n   \
    \     while (i <= k) {\n            res.emplace_back(i, i + len);\n          \
    \  i += len;\n        }\n    }\n    return res;\n}\n\n/**\n * @brief Lyndon\u5206\
    \u89E3(Lyndon Factorization)\n */\n#line 11 \"test/yosupo_aplusb_string_bytes.test.cpp\"\
    \n\nconstexpr int MOD = 1000000007;\n\nvoid hash_check(const string &s) {\n  \
    \  rolling_hash<MOD> small(s);\n    rolling_hash_ull large(s);\n    for (int l\
    \ = 0; l <= int(s.size()); ++l) {\n        ull expected_small = 0, expected_large\
    \ = 0;\n        for (int r = l; r <= int(s.size()); ++r) {\n            if (r\
    \ > l) {\n                unsigned char byte = s[r - 1];\n                expected_small\
    \ = (expected_small * 127 + byte) % MOD;\n                expected_large = ((__uint128_t)expected_large\
    \ * 127 + byte) % M;\n            }\n            string sub = s.substr(l, r -\
    \ l);\n            rolling_hash<MOD> small_sub(sub);\n            rolling_hash_ull\
    \ large_sub(sub);\n            assert(small.get(l, r) == ll(expected_small));\n\
    \            assert(small_sub.get(0, sub.size()) == ll(expected_small));\n   \
    \         assert(large.get(l, r) == expected_large);\n            assert(large_sub.get(0,\
    \ sub.size()) == expected_large);\n            assert(rolling_hash_ull::val(sub)\
    \ == expected_large);\n        }\n    }\n}\n\nvoid lyndon_check(const string &s)\
    \ {\n    auto factors = lyndon_factorization(s);\n    int end = 0;\n    string\
    \ previous;\n    for (auto [l, r] : factors) {\n        assert(l == end && l <\
    \ r && r <= int(s.size()));\n        string word = s.substr(l, r - l);\n     \
    \   for (int i = 1; i < int(word.size()); ++i) assert(word < word.substr(i));\n\
    \        if (l > 0) assert(previous >= word);\n        previous = word;\n    \
    \    end = r;\n    }\n    assert(end == int(s.size()));\n}\n\nvoid shared_powers_check()\
    \ {\n    string s(64, 'a');\n    rolling_hash_ull original(s);\n    ull expected\
    \ = rolling_hash_ull::val(s);\n    size_t size = rolling_hash_ull::p().size();\n\
    \    for (int n : {0, 1, 0, 32}) {\n        rolling_hash_ull precompute(n);\n\
    \        assert(rolling_hash_ull::p().size() == size);\n        assert(original.get(0,\
    \ s.size()) == expected);\n        assert(original.get(1, 2) == 'a');\n    }\n\
    \    rolling_hash_ull grow(200);\n    assert(rolling_hash_ull::p().size() >= 201);\n\
    \    assert(original.get(0, s.size()) == expected);\n    hash_check(\"abc\");\n\
    \    hash_check(string(80, '\\0'));\n}\n\nint main() {\n    rolling_hash<MOD>::B()\
    \ = 127;\n    rolling_hash_ull::B() = 127;\n    shared_powers_check();\n    hash_check(string{char(255),\
    \ char(127), 1, 1, 1, 1, 1});\n    // The unreduced product in get(17, 28) exceeds\
    \ hash[28] + 3*M.\n    string subtraction_case;\n    for (int byte : {52, 238,\
    \ 54, 138, 29, 92, 151, 22, 86, 21, 6, 9, 155, 217, 111, 94,\n               \
    \     133, 220, 239, 101, 237, 127, 15, 83, 108, 190, 213, 198, 175, 154, 9, 95})\n\
    \        subtraction_case += char(byte);\n    hash_check(subtraction_case);\n\
    \    const unsigned char alphabet[] = {0, 127, 128, 255};\n    for (int n = 0,\
    \ count = 1; n <= 6; ++n, count *= 4) {\n        for (int mask = 0; mask < count;\
    \ ++mask) {\n            string s(n, '\\0');\n            int digits = mask;\n\
    \            for (char &c : s) {\n                c = char(alphabet[digits % 4]);\n\
    \                digits /= 4;\n            }\n            lyndon_check(s);\n \
    \           if (n <= 5) hash_check(s);\n        }\n    }\n    mt19937 rng(57);\n\
    \    for (int tc = 0; tc < 100; ++tc) {\n        string s(rng() % 40, '\\0');\n\
    \        for (char &c : s) c = char(rng() % 256);\n        hash_check(s);\n  \
    \      lyndon_check(s);\n    }\n    Scanner sc;\n    Printer pr;\n    int a, b;\n\
    \    sc.read(a, b);\n    pr.println(a + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing ll = long long;\nusing ull = unsigned long long;\n\
    #include \"../util/fastio.cpp\"\n#include \"../string/rolling_hash.cpp\"\n#include\
    \ \"../string/rolling_hash_ull.cpp\"\n#include \"../string/lyndon_factorization.cpp\"\
    \n\nconstexpr int MOD = 1000000007;\n\nvoid hash_check(const string &s) {\n  \
    \  rolling_hash<MOD> small(s);\n    rolling_hash_ull large(s);\n    for (int l\
    \ = 0; l <= int(s.size()); ++l) {\n        ull expected_small = 0, expected_large\
    \ = 0;\n        for (int r = l; r <= int(s.size()); ++r) {\n            if (r\
    \ > l) {\n                unsigned char byte = s[r - 1];\n                expected_small\
    \ = (expected_small * 127 + byte) % MOD;\n                expected_large = ((__uint128_t)expected_large\
    \ * 127 + byte) % M;\n            }\n            string sub = s.substr(l, r -\
    \ l);\n            rolling_hash<MOD> small_sub(sub);\n            rolling_hash_ull\
    \ large_sub(sub);\n            assert(small.get(l, r) == ll(expected_small));\n\
    \            assert(small_sub.get(0, sub.size()) == ll(expected_small));\n   \
    \         assert(large.get(l, r) == expected_large);\n            assert(large_sub.get(0,\
    \ sub.size()) == expected_large);\n            assert(rolling_hash_ull::val(sub)\
    \ == expected_large);\n        }\n    }\n}\n\nvoid lyndon_check(const string &s)\
    \ {\n    auto factors = lyndon_factorization(s);\n    int end = 0;\n    string\
    \ previous;\n    for (auto [l, r] : factors) {\n        assert(l == end && l <\
    \ r && r <= int(s.size()));\n        string word = s.substr(l, r - l);\n     \
    \   for (int i = 1; i < int(word.size()); ++i) assert(word < word.substr(i));\n\
    \        if (l > 0) assert(previous >= word);\n        previous = word;\n    \
    \    end = r;\n    }\n    assert(end == int(s.size()));\n}\n\nvoid shared_powers_check()\
    \ {\n    string s(64, 'a');\n    rolling_hash_ull original(s);\n    ull expected\
    \ = rolling_hash_ull::val(s);\n    size_t size = rolling_hash_ull::p().size();\n\
    \    for (int n : {0, 1, 0, 32}) {\n        rolling_hash_ull precompute(n);\n\
    \        assert(rolling_hash_ull::p().size() == size);\n        assert(original.get(0,\
    \ s.size()) == expected);\n        assert(original.get(1, 2) == 'a');\n    }\n\
    \    rolling_hash_ull grow(200);\n    assert(rolling_hash_ull::p().size() >= 201);\n\
    \    assert(original.get(0, s.size()) == expected);\n    hash_check(\"abc\");\n\
    \    hash_check(string(80, '\\0'));\n}\n\nint main() {\n    rolling_hash<MOD>::B()\
    \ = 127;\n    rolling_hash_ull::B() = 127;\n    shared_powers_check();\n    hash_check(string{char(255),\
    \ char(127), 1, 1, 1, 1, 1});\n    // The unreduced product in get(17, 28) exceeds\
    \ hash[28] + 3*M.\n    string subtraction_case;\n    for (int byte : {52, 238,\
    \ 54, 138, 29, 92, 151, 22, 86, 21, 6, 9, 155, 217, 111, 94,\n               \
    \     133, 220, 239, 101, 237, 127, 15, 83, 108, 190, 213, 198, 175, 154, 9, 95})\n\
    \        subtraction_case += char(byte);\n    hash_check(subtraction_case);\n\
    \    const unsigned char alphabet[] = {0, 127, 128, 255};\n    for (int n = 0,\
    \ count = 1; n <= 6; ++n, count *= 4) {\n        for (int mask = 0; mask < count;\
    \ ++mask) {\n            string s(n, '\\0');\n            int digits = mask;\n\
    \            for (char &c : s) {\n                c = char(alphabet[digits % 4]);\n\
    \                digits /= 4;\n            }\n            lyndon_check(s);\n \
    \           if (n <= 5) hash_check(s);\n        }\n    }\n    mt19937 rng(57);\n\
    \    for (int tc = 0; tc < 100; ++tc) {\n        string s(rng() % 40, '\\0');\n\
    \        for (char &c : s) c = char(rng() % 256);\n        hash_check(s);\n  \
    \      lyndon_check(s);\n    }\n    Scanner sc;\n    Printer pr;\n    int a, b;\n\
    \    sc.read(a, b);\n    pr.println(a + b);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - string/rolling_hash.cpp
  - util/xorshift.cpp
  - string/rolling_hash_ull.cpp
  - string/lyndon_factorization.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_string_bytes.test.cpp
  requiredBy: []
  timestamp: '2026-10-03 16:38:16+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_string_bytes.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_string_bytes.test.cpp
- /verify/test/yosupo_aplusb_string_bytes.test.cpp.html
title: test/yosupo_aplusb_string_bytes.test.cpp
---
