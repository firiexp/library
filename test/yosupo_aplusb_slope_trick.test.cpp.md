---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/slope_trick.cpp
    title: Slope Trick
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
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"test/yosupo_aplusb_slope_trick.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\nusing\
    \ namespace std;\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\nextern\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"datastructure/slope_trick.cpp\"\
    \ntemplate<class T>\nstruct SlopeTrick {\n    static constexpr T INF = numeric_limits<T>::max()\
    \ / 4;\n    static constexpr bool raw_eval_cache = is_integral<T>::value && sizeof(T)\
    \ <= 8;\n    using EvalSum = conditional_t<raw_eval_cache, __int128, T>;\n\n \
    \   T min_f = 0;\n    priority_queue<T> L;\n    priority_queue<T, vector<T>, greater<T>>\
    \ R;\n    T add_l = 0, add_r = 0;\n    mutable bool eval_cache_valid = false;\n\
    \    mutable vector<T> eval_l, eval_r;\n    mutable vector<EvalSum> eval_l_sum,\
    \ eval_r_sum;\n\n    struct Query {\n        T lx, rx, min_f;\n    };\n\nprivate:\n\
    \    void push_L(T a) { L.push(a - add_l); }\n    void push_R(T a) { R.push(a\
    \ - add_r); }\n    T top_L() const { return L.empty() ? -INF : L.top() + add_l;\
    \ }\n    T top_R() const { return R.empty() ? INF : R.top() + add_r; }\n    T\
    \ pop_L() {\n        invalidate_eval_cache();\n        T x = top_L();\n      \
    \  if (!L.empty()) L.pop();\n        return x;\n    }\n    T pop_R() {\n     \
    \   invalidate_eval_cache();\n        T x = top_R();\n        if (!R.empty())\
    \ R.pop();\n        return x;\n    }\n    size_t size() const { return L.size()\
    \ + R.size(); }\n    void invalidate_eval_cache() {\n        eval_cache_valid\
    \ = false;\n    }\n    void build_eval_cache() const {\n        if (eval_cache_valid)\
    \ return;\n\n        auto lq = L;\n        auto rq = R;\n        eval_l.clear();\n\
    \        eval_r.clear();\n        eval_l.reserve(lq.size());\n        eval_r.reserve(rq.size());\n\
    \        while (!lq.empty()) {\n            if constexpr (raw_eval_cache) eval_l.emplace_back(lq.top());\n\
    \            else eval_l.emplace_back(lq.top() + add_l);\n            lq.pop();\n\
    \        }\n        reverse(eval_l.begin(), eval_l.end());\n        while (!rq.empty())\
    \ {\n            if constexpr (raw_eval_cache) eval_r.emplace_back(rq.top());\n\
    \            else eval_r.emplace_back(rq.top() + add_r);\n            rq.pop();\n\
    \        }\n\n        eval_l_sum.assign(eval_l.size() + 1, 0);\n        for (int\
    \ i = 0; i < (int)eval_l.size(); ++i) {\n            eval_l_sum[i + 1] = eval_l_sum[i]\
    \ + eval_l[i];\n        }\n        eval_r_sum.assign(eval_r.size() + 1, 0);\n\
    \        for (int i = 0; i < (int)eval_r.size(); ++i) {\n            eval_r_sum[i\
    \ + 1] = eval_r_sum[i] + eval_r[i];\n        }\n        eval_cache_valid = true;\n\
    \    }\n\npublic:\n    Query query() const {\n        return {top_L(), top_R(),\
    \ min_f};\n    }\n\n    void add_all(T a) {\n        min_f += a;\n    }\n\n  \
    \  void add_a_minus_x(T a) {\n        invalidate_eval_cache();\n        min_f\
    \ += max<T>(0, a - top_R());\n        push_R(a);\n        push_L(pop_R());\n \
    \   }\n\n    void add_x_minus_a(T a) {\n        invalidate_eval_cache();\n   \
    \     min_f += max<T>(0, top_L() - a);\n        push_L(a);\n        push_R(pop_L());\n\
    \    }\n\n    void add_abs(T a) {\n        add_a_minus_x(a);\n        add_x_minus_a(a);\n\
    \    }\n\n    void clear_right() {\n        decltype(R){}.swap(R);\n        invalidate_eval_cache();\n\
    \    }\n\n    void clear_left() {\n        decltype(L){}.swap(L);\n        invalidate_eval_cache();\n\
    \    }\n\n    void shift(T a, T b) {\n        assert(a <= b);\n        add_l +=\
    \ a;\n        add_r += b;\n        if constexpr (!raw_eval_cache) invalidate_eval_cache();\n\
    \    }\n\n    void shift(T a) {\n        shift(a, a);\n    }\n\n    T eval(T x)\
    \ const {\n        build_eval_cache();\n        EvalSum lx = x, rx = x;\n    \
    \    if constexpr (raw_eval_cache) {\n            lx -= static_cast<EvalSum>(add_l);\n\
    \            rx -= static_cast<EvalSum>(add_r);\n        }\n        EvalSum res\
    \ = min_f;\n        int li = upper_bound(eval_l.begin(), eval_l.end(), lx) - eval_l.begin();\n\
    \        res += eval_l_sum.back() - eval_l_sum[li] - lx * static_cast<EvalSum>(eval_l.size()\
    \ - li);\n        int ri = lower_bound(eval_r.begin(), eval_r.end(), rx) - eval_r.begin();\n\
    \        res += rx * static_cast<EvalSum>(ri) - eval_r_sum[ri];\n        return\
    \ static_cast<T>(res);\n    }\n\n    void merge(SlopeTrick &st) {\n        if\
    \ (st.size() > size()) swap(*this, st);\n        while (!st.L.empty()) add_a_minus_x(st.pop_L());\n\
    \        while (!st.R.empty()) add_x_minus_a(st.pop_R());\n        min_f += st.min_f;\n\
    \    }\n};\n\n/**\n * @brief Slope Trick\n */\n#line 7 \"test/yosupo_aplusb_slope_trick.test.cpp\"\
    \n\ntemplate<class T>\nvoid verify(const SlopeTrick<T> &st, T x) {\n    using\
    \ Wide = conditional_t<is_integral<T>::value, __int128, long double>;\n    Wide\
    \ expected = st.min_f;\n    auto l = st.L;\n    auto r = st.R;\n    while (!l.empty())\
    \ {\n        expected += max<Wide>(0, Wide(l.top()) + st.add_l - x);\n       \
    \ l.pop();\n    }\n    while (!r.empty()) {\n        expected += max<Wide>(0,\
    \ Wide(x) - r.top() - st.add_r);\n        r.pop();\n    }\n    if constexpr (is_integral<T>::value)\
    \ assert(st.eval(x) == expected);\n    else assert(fabsl(st.eval(x) - expected)\
    \ <= 1e-9L);\n}\n\ntemplate<class T>\nvoid random_check() {\n    mt19937 rng(117);\n\
    \    for (int tc = 0; tc < 1000; ++tc) {\n        SlopeTrick<T> st;\n        verify(st,\
    \ T(0));\n        for (int step = 0; step < 200; ++step) {\n            T a =\
    \ T((int(rng() % 101) - 50) * 0.5);\n            switch (rng() % 10) {\n     \
    \           case 0: st.add_abs(a); break;\n                case 1: st.add_a_minus_x(a);\
    \ break;\n                case 2: st.add_x_minus_a(a); break;\n              \
    \  case 3: st.add_all(a); break;\n                case 4: st.shift(a); break;\n\
    \                case 5: st.shift(a, a + int(rng() % 11)); break;\n          \
    \      case 6: st.clear_left(); break;\n                case 7: st.clear_right();\
    \ break;\n                case 8: {\n                    SlopeTrick<T> other;\n\
    \                    for (int i = 0; i < 8; ++i) other.add_abs(T(int(rng() % 101)\
    \ - 50));\n                    other.shift(-3, 7);\n                    verify(other,\
    \ a);\n                    st.merge(other);\n                    verify(other,\
    \ a);\n                    break;\n                }\n                default:\
    \ break;\n            }\n            for (int i = 0; i < 5; ++i) verify(st, T(int(rng()\
    \ % 1001) - 500));\n        }\n    }\n}\n\nvoid cache_check() {\n    SlopeTrick<long\
    \ long> st;\n    st.add_abs(-4);\n    st.add_abs(7);\n    verify(st, 0LL);\n \
    \   auto l = st.eval_l, r = st.eval_r;\n    for (int i = 0; i < 100; ++i) {\n\
    \        st.shift(-1, 2);\n        st.add_all(-3);\n        assert(st.eval_cache_valid);\n\
    \        verify(st, (long long)i);\n        assert(st.eval_l == l && st.eval_r\
    \ == r);\n    }\n    SlopeTrick<double> real_st;\n    real_st.add_abs(0.25);\n\
    \    verify(real_st, 0.5);\n    real_st.shift(-0.5, 1.25);\n    assert(!real_st.eval_cache_valid);\n\
    \    verify(real_st, 0.75);\n    for (long long offset : {-9000000000000000000LL,\
    \ 9000000000000000000LL}) {\n        for (int n = 1; n <= 4; ++n) {\n        \
    \    SlopeTrick<long long> huge;\n            huge.shift(offset);\n          \
    \  for (int i = 0; i < n; ++i) huge.add_abs(0);\n            verify(huge, 0LL);\n\
    \            verify(huge, -1000000000000000000LL);\n            verify(huge, 1000000000000000000LL);\n\
    \            huge.shift(-1, 1);\n            verify(huge, 0LL);\n            verify(huge,\
    \ -1000000000000000000LL);\n            verify(huge, 1000000000000000000LL);\n\
    \        }\n    }\n}\n\nint main() {\n    random_check<long long>();\n    random_check<int>();\n\
    \    random_check<double>();\n    cache_check();\n    Scanner sc;\n    Printer\
    \ pr;\n    int a, b;\n    sc.read(a, b);\n    pr.println(a + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n#include \"../util/fastio.cpp\"\n#include \"../datastructure/slope_trick.cpp\"\
    \n\ntemplate<class T>\nvoid verify(const SlopeTrick<T> &st, T x) {\n    using\
    \ Wide = conditional_t<is_integral<T>::value, __int128, long double>;\n    Wide\
    \ expected = st.min_f;\n    auto l = st.L;\n    auto r = st.R;\n    while (!l.empty())\
    \ {\n        expected += max<Wide>(0, Wide(l.top()) + st.add_l - x);\n       \
    \ l.pop();\n    }\n    while (!r.empty()) {\n        expected += max<Wide>(0,\
    \ Wide(x) - r.top() - st.add_r);\n        r.pop();\n    }\n    if constexpr (is_integral<T>::value)\
    \ assert(st.eval(x) == expected);\n    else assert(fabsl(st.eval(x) - expected)\
    \ <= 1e-9L);\n}\n\ntemplate<class T>\nvoid random_check() {\n    mt19937 rng(117);\n\
    \    for (int tc = 0; tc < 1000; ++tc) {\n        SlopeTrick<T> st;\n        verify(st,\
    \ T(0));\n        for (int step = 0; step < 200; ++step) {\n            T a =\
    \ T((int(rng() % 101) - 50) * 0.5);\n            switch (rng() % 10) {\n     \
    \           case 0: st.add_abs(a); break;\n                case 1: st.add_a_minus_x(a);\
    \ break;\n                case 2: st.add_x_minus_a(a); break;\n              \
    \  case 3: st.add_all(a); break;\n                case 4: st.shift(a); break;\n\
    \                case 5: st.shift(a, a + int(rng() % 11)); break;\n          \
    \      case 6: st.clear_left(); break;\n                case 7: st.clear_right();\
    \ break;\n                case 8: {\n                    SlopeTrick<T> other;\n\
    \                    for (int i = 0; i < 8; ++i) other.add_abs(T(int(rng() % 101)\
    \ - 50));\n                    other.shift(-3, 7);\n                    verify(other,\
    \ a);\n                    st.merge(other);\n                    verify(other,\
    \ a);\n                    break;\n                }\n                default:\
    \ break;\n            }\n            for (int i = 0; i < 5; ++i) verify(st, T(int(rng()\
    \ % 1001) - 500));\n        }\n    }\n}\n\nvoid cache_check() {\n    SlopeTrick<long\
    \ long> st;\n    st.add_abs(-4);\n    st.add_abs(7);\n    verify(st, 0LL);\n \
    \   auto l = st.eval_l, r = st.eval_r;\n    for (int i = 0; i < 100; ++i) {\n\
    \        st.shift(-1, 2);\n        st.add_all(-3);\n        assert(st.eval_cache_valid);\n\
    \        verify(st, (long long)i);\n        assert(st.eval_l == l && st.eval_r\
    \ == r);\n    }\n    SlopeTrick<double> real_st;\n    real_st.add_abs(0.25);\n\
    \    verify(real_st, 0.5);\n    real_st.shift(-0.5, 1.25);\n    assert(!real_st.eval_cache_valid);\n\
    \    verify(real_st, 0.75);\n    for (long long offset : {-9000000000000000000LL,\
    \ 9000000000000000000LL}) {\n        for (int n = 1; n <= 4; ++n) {\n        \
    \    SlopeTrick<long long> huge;\n            huge.shift(offset);\n          \
    \  for (int i = 0; i < n; ++i) huge.add_abs(0);\n            verify(huge, 0LL);\n\
    \            verify(huge, -1000000000000000000LL);\n            verify(huge, 1000000000000000000LL);\n\
    \            huge.shift(-1, 1);\n            verify(huge, 0LL);\n            verify(huge,\
    \ -1000000000000000000LL);\n            verify(huge, 1000000000000000000LL);\n\
    \        }\n    }\n}\n\nint main() {\n    random_check<long long>();\n    random_check<int>();\n\
    \    random_check<double>();\n    cache_check();\n    Scanner sc;\n    Printer\
    \ pr;\n    int a, b;\n    sc.read(a, b);\n    pr.println(a + b);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/slope_trick.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_slope_trick.test.cpp
  requiredBy: []
  timestamp: '2026-10-09 00:41:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_slope_trick.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_slope_trick.test.cpp
- /verify/test/yosupo_aplusb_slope_trick.test.cpp.html
title: test/yosupo_aplusb_slope_trick.test.cpp
---
