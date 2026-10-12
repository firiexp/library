---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/sparsetable.cpp
    title: Sparse Table
  - icon: ':heavy_check_mark:'
    path: string/enumerate_runs.cpp
    title: "\u6587\u5B57\u5217\u306Erun\u5217\u6319"
  - icon: ':heavy_check_mark:'
    path: string/suffix_array.cpp
    title: Suffix Array
  - icon: ':heavy_check_mark:'
    path: string/suffix_array_query.cpp
    title: "\u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E\u30FB\u90E8\u5206\u6587\u5B57\
      \u5217\u306E\u8F9E\u66F8\u9806\u6BD4\u8F03"
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
    PROBLEM: https://judge.yosupo.jp/problem/runenumerate
    links:
    - https://judge.yosupo.jp/problem/runenumerate
  bundledCode: "#line 1 \"test/yosupo_runenumerate.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/runenumerate\"\n\n#include <bits/stdc++.h>\nusing\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"string/enumerate_runs.cpp\"\
    \n\n\n\n#line 1 \"string/suffix_array_query.cpp\"\n\n\n\n#line 1 \"string/suffix_array.cpp\"\
    \n\n\n\nvector<int> convert(string const& s){\n    int n = s.size();\n    std::vector<int>\
    \ s2(n);\n    for (int i = 0; i < n; i++) s2[i] = static_cast<unsigned char>(s[i]);\n\
    \    return s2;\n}\n\nvector<int> suffix_array(const vector<int> &s, int upper){\n\
    \    int n = s.size();\n    if (n <= 1) return vector<int>(n, 0);\n    if (n ==\
    \ 2) return s[0] < s[1] ? vector<int>{0, 1} : vector<int>{1, 0};\n    vector<int>\
    \ sa(n);\n    vector<bool> ls(n);\n    for (int i = n-2; i >= 0; --i) ls[i] =\
    \ (s[i] == s[i+1]) ? ls[i+1] : (s[i] < s[i+1]);\n    vector<int> sum_l(upper+1),\
    \ sum_s(upper+1);\n    for (int i = 0; i < n; ++i) (ls[i] ? sum_l[s[i]+1] : sum_s[s[i]])++;\n\
    \    for (int i = 0; i <= upper; ++i) {\n        sum_s[i] += sum_l[i];\n     \
    \   if(i < upper) sum_l[i+1] += sum_s[i];\n    }\n\n    auto induce = [&](vector<int>\
    \ const& lms){\n        fill(sa.begin(),sa.end(), -1);\n        vector<int> buf(upper+1);\n\
    \        copy(sum_s.begin(),sum_s.end(), buf.begin());\n        for (auto &&i\
    \ : lms) if(i != n) sa[buf[s[i]]++] = i;\n        copy(sum_l.begin(),sum_l.end(),\
    \ buf.begin());\n        sa[buf[s.back()]++] = n-1;\n        for (int i = 0; i\
    \ < n; ++i) {\n            int v = sa[i];\n            if(v >= 1 && !ls[v-1])\
    \ sa[buf[s[v-1]]++] = v-1;\n        }\n        copy(sum_l.begin(),sum_l.end(),\
    \ buf.begin());\n        for (int i = n - 1; i >= 0; --i) {\n            int v\
    \ = sa[i];\n            if(v >= 1 && ls[v-1]) sa[--buf[s[v-1]+1]] = v-1;\n   \
    \     }\n    };\n    vector<int> lms_map(n+1, -1);\n    int m = 0;\n    for (int\
    \ i = 1; i < n; ++i) if(!ls[i-1] && ls[i]) lms_map[i] = m++;\n    vector<int>\
    \ lms;\n    lms.reserve(m);\n    for (int i = 1; i < n; ++i) if(!ls[i-1] && ls[i])\
    \ lms.emplace_back(i);\n    induce(lms);\n    if(m){\n        vector<int> sorted_lms;\n\
    \        sorted_lms.reserve(m);\n        for (auto &&i : sa) if(~lms_map[i]) sorted_lms.emplace_back(i);\n\
    \        vector<int> rec_s(m);\n        int rec_upper = 0;\n        rec_s[lms_map[sorted_lms.front()]]\
    \ = 0;\n        for (int i = 1; i < m; ++i) {\n            int l = sorted_lms[i-1],\
    \ r = sorted_lms[i];\n            int end_l = (lms_map[l]+1) < m ? lms[lms_map[l]+1]\
    \ : n;\n            int end_r = (lms_map[r]+1) < m ? lms[lms_map[r]+1] : n;\n\
    \            bool same = true;\n            if(end_l-l != end_r-r) same = false;\n\
    \            else {\n                while(l < end_l && s[l] == s[r]) l++, r++;\n\
    \                if(l == n || s[l] != s[r]) same = false;\n            }\n   \
    \         rec_upper += !same;\n            rec_s[lms_map[sorted_lms[i]]] = rec_upper;\n\
    \        }\n        auto rec_sa = suffix_array(rec_s, rec_upper);\n        for\
    \ (int i = 0; i < m; ++i) sorted_lms[i] = lms[rec_sa[i]];\n        induce(sorted_lms);\n\
    \    }\n    return sa;\n}\n\ntemplate<class T> vector<int> suffix_array(vector<T>\
    \ const& s){\n    int n = s.size();\n    vector<int> idx(n);\n    iota(idx.begin(),idx.end(),\
    \ 0);\n    sort(idx.begin(),idx.end(), [&](int l, int r){ return s[l] < s[r];\
    \ });\n    vector<int> z(n);\n    int now = 0;\n    for (int i = 0; i < n; ++i)\
    \ {\n        if(i && s[idx[i-1]] != s[idx[i]]) now++;\n        z[idx[i]] = now;\n\
    \    }\n    return suffix_array(z, now);\n}\n\nvector<int> suffix_array(const\
    \ string& s){\n    return suffix_array(convert(s), 255);\n}\n\ntemplate<class\
    \ T>\nvector<int> lcp(const vector<T> &s, const vector<int> &sa){\n    int n =\
    \ s.size();\n    if (n <= 1) return {};\n    vector<int> sa_inv(n);\n    for (int\
    \ i = 0; i < n; ++i) sa_inv[sa[i]] = i;\n    vector<int> lcp(n-1);\n    int h\
    \ = 0;\n    for (int i = 0; i < n; ++i) {\n        if(h > 0) h--;\n        if(!sa_inv[i])\
    \ continue;\n        int j = sa[sa_inv[i]-1];\n        while(j+h < n && i+h <\
    \ n && s[j+h] == s[i+h]) h++;\n        lcp[sa_inv[i]-1] = h;\n    }\n    return\
    \ lcp;\n}\n\nvector<int> lcp(string const& s, vector<int> const& sa){\n    return\
    \ lcp(convert(s), sa);\n}\n\n/**\n * @brief Suffix Array\n */\n\n\n#line 1 \"\
    datastructure/sparsetable.cpp\"\n\n\n\ntemplate <class F>\nstruct SparseTable\
    \ {\n    using T = typename F::T;\n    vector<vector<T>> table;\n    vector<int>\
    \ u;\n    SparseTable() = default;\n    explicit SparseTable(const vector<T> &v){\
    \ build(v); }\n \n    void build(const vector<T> &v){\n        int n = v.size(),\
    \ m = 1;\n        while((1<<m) <= n) m++;\n        table.assign(m, vector<T>(n));\n\
    \        u.assign(n+1, 0);\n        for (int i = 2; i <= n; ++i) {\n         \
    \   u[i] = u[i>>1] + 1;\n        }\n        for (int i = 0; i < n; ++i) {\n  \
    \          table[0][i] = v[i];\n        }\n        for (int i = 1; i < m; ++i)\
    \ {\n            int x = (1<<(i-1));\n            for (int j = 0; j < n; ++j)\
    \ {\n                table[i][j] = F::f(table[i-1][j], table[i-1][min(j+x, n-1)]);\n\
    \            }\n        }\n    }\n \n    T query(int a, int b) const {\n     \
    \   int l = b-a;\n        return F::f(table[u[l]][a], table[u[l]][b-(1<<u[l])]);\n\
    \    }\n};\n\n/**\n * @brief Sparse Table\n */\n\n\n#line 6 \"string/suffix_array_query.cpp\"\
    \n\nclass SuffixArrayQuery {\n    struct Minimum {\n        using T = int;\n \
    \       static int f(int a, int b) { return min(a, b); }\n    };\n    int n;\n\
    \    vector<int> rank;\n    SparseTable<Minimum> rmq;\n\n    template<class Sequence>\n\
    \    void initialize(const Sequence& s) {\n        n = (int)s.size();\n      \
    \  auto sa = suffix_array(s);\n        rank.resize(n);\n        for (int i = 0;\
    \ i < n; ++i) rank[sa[i]] = i;\n        rmq.build(lcp(s, sa));\n    }\n\npublic:\n\
    \    explicit SuffixArrayQuery(const string& s) { initialize(s); }\n\n    template<class\
    \ T>\n    explicit SuffixArrayQuery(const vector<T>& s) { initialize(s); }\n\n\
    \    int suffix_rank(int i) const { return rank[i]; }\n\n    int lce(int i, int\
    \ j) const {\n        if (i == j) return n - i;\n        if (i == n || j == n)\
    \ return 0;\n        int a = rank[i], b = rank[j];\n        if (a > b) swap(a,\
    \ b);\n        return rmq.query(a, b);\n    }\n\n    int compare(int l1, int r1,\
    \ int l2, int r2) const {\n        int len1 = r1 - l1, len2 = r2 - l2;\n     \
    \   if (lce(l1, l2) >= min(len1, len2))\n            return (len1 > len2) - (len1\
    \ < len2);\n        return rank[l1] < rank[l2] ? -1 : 1;\n    }\n};\n\n\n\n/**\n\
    \ * @brief \u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E\u30FB\u90E8\u5206\u6587\u5B57\
    \u5217\u306E\u8F9E\u66F8\u9806\u6BD4\u8F03\n */\n#line 5 \"string/enumerate_runs.cpp\"\
    \n\nstruct Run {\n    int period, l, r;\n};\n\nvector<Run> enumerate_runs(const\
    \ string& s) {\n    int n = (int)s.size();\n    if (n <= 1) return {};\n    SuffixArrayQuery\
    \ forward(s), backward(string(s.rbegin(), s.rend()));\n    vector<Run> result;\n\
    \    vector<int> values = convert(s), rank(n), stack;\n    stack.reserve(n);\n\
    \    for (int order = 0; order < 2; ++order) {\n        if (order == 0) {\n  \
    \          for (int i = 0; i < n; ++i) rank[i] = forward.suffix_rank(i);\n   \
    \     } else {\n            auto sa = suffix_array(values, 255);\n           \
    \ for (int i = 0; i < n; ++i) rank[sa[i]] = i;\n        }\n        stack.clear();\n\
    \        for (int i = n - 1; i >= 0; --i) {\n            while (!stack.empty()\
    \ && rank[i] < rank[stack.back()]) stack.pop_back();\n            int j = stack.empty()\
    \ ? n : stack.back();\n            int period = j - i;\n            int left =\
    \ backward.lce(n - i, n - j);\n            int right = forward.lce(i, j);\n  \
    \          if (left + right >= period) result.push_back({period, i - left, j +\
    \ right});\n            stack.push_back(i);\n        }\n        for (int& c :\
    \ values) c = 255 - c;\n    }\n    sort(result.begin(), result.end(), [](const\
    \ Run& a, const Run& b) {\n        return tie(a.period, a.l, a.r) < tie(b.period,\
    \ b.l, b.r);\n    });\n    result.erase(unique(result.begin(), result.end(), [](const\
    \ Run& a, const Run& b) {\n        return tie(a.period, a.l, a.r) == tie(b.period,\
    \ b.l, b.r);\n    }), result.end());\n    return result;\n}\n\n\n\n/**\n * @brief\
    \ \u6587\u5B57\u5217\u306Erun\u5217\u6319\n */\n#line 7 \"test/yosupo_runenumerate.test.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n    string s;\n    sc.read(s);\n\
    \    auto runs = enumerate_runs(s);\n    pr.println(runs.size());\n    for (auto\
    \ [period, l, r] : runs) pr.println(period, l, r);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/runenumerate\"\n\n#include\
    \ <bits/stdc++.h>\nusing namespace std;\n#include \"../util/fastio.cpp\"\n#include\
    \ \"../string/enumerate_runs.cpp\"\n\nint main() {\n    Scanner sc;\n    Printer\
    \ pr;\n    string s;\n    sc.read(s);\n    auto runs = enumerate_runs(s);\n  \
    \  pr.println(runs.size());\n    for (auto [period, l, r] : runs) pr.println(period,\
    \ l, r);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - string/enumerate_runs.cpp
  - string/suffix_array_query.cpp
  - string/suffix_array.cpp
  - datastructure/sparsetable.cpp
  isVerificationFile: true
  path: test/yosupo_runenumerate.test.cpp
  requiredBy: []
  timestamp: '2026-10-12 10:35:08+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_runenumerate.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_runenumerate.test.cpp
- /verify/test/yosupo_runenumerate.test.cpp.html
title: test/yosupo_runenumerate.test.cpp
---
