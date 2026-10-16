---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/digit_dfa.cpp
    title: "\u6570\u5B57\u5217\u306E\u6761\u4EF6\u3092\u8868\u3059\u6709\u9650\u30AA\
      \u30FC\u30C8\u30DE\u30C8\u30F3"
  - icon: ':heavy_check_mark:'
    path: string/dfa.cpp
    title: "\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u3068\u6761\u4EF6\u306E\
      \u5408\u6210"
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_dfa.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n#include <bits/stdc++.h>\nusing namespace std;\n\n#line 1 \"math/digit_dfa.cpp\"\
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
    \n\n\n/**\n * @brief \u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\u3068\u6761\
    \u4EF6\u306E\u5408\u6210\n */\n#line 5 \"math/digit_dfa.cpp\"\n\nDFA<10> digit_value_mod(int\
    \ m, int r = 0) {\n    assert(m > 0 && 0 <= r && r < m);\n    DFA<10> a{vector<array<int,\
    \ 10>>(m), vector<char>(m), 0};\n    a.accept[r] = true;\n    for (int v = 0;\
    \ v < m; ++v) {\n        for (int d = 0; d < 10; ++d) a.next[v][d] = (10LL * v\
    \ + d) % m;\n    }\n    return a;\n}\n\nDFA<10> digit_sum_mod(int m, int r = 0)\
    \ {\n    assert(m > 0 && 0 <= r && r < m);\n    DFA<10> a{vector<array<int, 10>>(m),\
    \ vector<char>(m), 0};\n    a.accept[r] = true;\n    for (int v = 0; v < m; ++v)\
    \ {\n        for (int d = 0; d < 10; ++d) a.next[v][d] = (v + (long long)d) %\
    \ m;\n    }\n    return a;\n}\n\nDFA<10> digit_sum_exact(int k) {\n    assert(0\
    \ <= k && k < numeric_limits<int>::max());\n    DFA<10> a{vector<array<int, 10>>(k\
    \ + 1), vector<char>(k + 1), 0};\n    a.accept[k] = true;\n    for (int v = 0;\
    \ v <= k; ++v) {\n        for (int d = 0; d < 10; ++d) a.next[v][d] = d <= k -\
    \ v ? v + d : -1;\n    }\n    return a;\n}\n\nDFA<10> no_equal_adjacent() {\n\
    \    DFA<10> a{vector<array<int, 10>>(11), vector<char>(11, true), 10};\n    for\
    \ (int v = 0; v <= 10; ++v) {\n        for (int d = 0; d < 10; ++d) a.next[v][d]\
    \ = v == d ? -1 : d;\n    }\n    return a;\n}\n\nDFA<10> required_digits(int mask)\
    \ {\n    assert(0 <= mask && mask < (1 << 10));\n    array<int, 10> bit{};\n \
    \   int n = 1;\n    for (int d = 0; d < 10; ++d) {\n        if (mask >> d & 1)\
    \ bit[d] = n, n *= 2;\n    }\n    DFA<10> a{vector<array<int, 10>>(n), vector<char>(n),\
    \ 0};\n    a.accept[n - 1] = true;\n    for (int v = 0; v < n; ++v) {\n      \
    \  for (int d = 0; d < 10; ++d) a.next[v][d] = v | bit[d];\n    }\n    return\
    \ a;\n}\n\n\n\n/**\n * @brief \u6570\u5B57\u5217\u306E\u6761\u4EF6\u3092\u8868\
    \u3059\u6709\u9650\u30AA\u30FC\u30C8\u30DE\u30C8\u30F3\n */\n#line 1 \"util/fastio.cpp\"\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 7 \"test/yosupo_aplusb_dfa.test.cpp\"\
    \n\ntemplate<int W>\nbool accepts(const DFA<W>& a, const string& s, char start)\
    \ {\n    int v = a.initial;\n    for (char c : s) {\n        if (v == -1) return\
    \ false;\n        v = a.next[v][c - start];\n    }\n    return v != -1 && a.accept[v];\n\
    }\n\ntemplate<int W>\nvoid check_reachable(const DFA<W>& a) {\n    assert(a.accept.size()\
    \ == a.next.size());\n    if (a.initial == -1) {\n        assert(a.next.empty());\n\
    \        return;\n    }\n    vector<char> seen(a.next.size());\n    vector<int>\
    \ q{a.initial};\n    seen[a.initial] = true;\n    for (size_t i = 0; i < q.size();\
    \ ++i) {\n        for (int v : a.next[q[i]]) {\n            assert(-1 <= v &&\
    \ v < (int)a.next.size());\n            if (v != -1 && !seen[v]) seen[v] = true,\
    \ q.push_back(v);\n        }\n    }\n    assert(q.size() == a.next.size());\n\
    }\n\nvoid self_check() {\n    mt19937 rng(149);\n    for (int tc = 0; tc < 300;\
    \ ++tc) {\n        auto random_dfa = [&]() {\n            int n = 1 + rng() %\
    \ 8;\n            DFA<2> a{vector<array<int, 2>>(n), vector<char>(n), int(rng()\
    \ % (n + 1)) - 1};\n            for (int v = 0; v < n; ++v) {\n              \
    \  a.accept[v] = rng() % 2;\n                for (int& to : a.next[v]) to = int(rng()\
    \ % (n + 1)) - 1;\n            }\n            return a;\n        };\n        auto\
    \ a = random_dfa(), b = random_dfa();\n        auto c = intersect(a, b);\n   \
    \     check_reachable(c);\n        for (int n = 0; n <= 8; ++n) {\n          \
    \  for (int mask = 0; mask < (1 << n); ++mask) {\n                string s(n,\
    \ 'a');\n                for (int i = 0; i < n; ++i) s[i] += mask >> i & 1;\n\
    \                assert(accepts(c, s, 'a') == (accepts(a, s, 'a') && accepts(b,\
    \ s, 'a')));\n            }\n        }\n    }\n    assert(intersect(digit_value_mod(2),\
    \ digit_value_mod(4)).next.size() == 4);\n    assert(intersect(DFA<10>{}, digit_value_mod(1)).initial\
    \ == -1);\n    for (int m = 1; m <= 12; ++m) {\n        for (int r = 0; r < m;\
    \ ++r) {\n            auto value = digit_value_mod(m, r), sum = digit_sum_mod(m,\
    \ r);\n            for (int x = 0; x <= 2000; ++x) {\n                string s\
    \ = to_string(x);\n                int total = 0;\n                for (char c\
    \ : s) total += c - '0';\n                assert(accepts(value, s, '0') == (x\
    \ % m == r));\n                assert(accepts(sum, s, '0') == (total % m == r));\n\
    \                assert(accepts(value, \"00\" + s, '0') == (x % m == r));\n  \
    \          }\n        }\n    }\n    for (int k = 0; k <= 30; ++k) {\n        auto\
    \ exact = digit_sum_exact(k);\n        for (int x = 0; x <= 2000; ++x) {\n   \
    \         string s = to_string(x);\n            int total = 0;\n            for\
    \ (char c : s) total += c - '0';\n            assert(accepts(exact, s, '0') ==\
    \ (total == k));\n        }\n    }\n    for (int mask = 0; mask < 1024; ++mask)\
    \ {\n        auto a = required_digits(mask);\n        assert(a.next.size() ==\
    \ size_t(1 << __builtin_popcount(unsigned(mask))));\n        assert(accepts(a,\
    \ \"\", '0') == (mask == 0));\n        for (int x = 0; x <= 2000; ++x) {\n   \
    \         string s = to_string(x);\n            int seen = 0;\n            for\
    \ (char c : s) seen |= 1 << (c - '0');\n            assert(accepts(a, s, '0')\
    \ == ((seen & mask) == mask));\n        }\n    }\n    auto adjacent = no_equal_adjacent();\n\
    \    for (int x = 0; x <= 2000; ++x) {\n        string s = to_string(x);\n   \
    \     assert(accepts(adjacent, s, '0') == (adjacent_find(s.begin(), s.end()) ==\
    \ s.end()));\n    }\n    assert(accepts(adjacent, \"\", '0'));\n    assert(!accepts(adjacent,\
    \ \"00\", '0'));\n    assert(accepts(digit_sum_exact(0), \"\", '0'));\n    assert(!accepts(digit_sum_exact(1),\
    \ \"\", '0'));\n}\n\nint main() {\n    self_check();\n    Scanner sc;\n    Printer\
    \ pr;\n    int a, b;\n    sc.read(a, b);\n    pr.println(a + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n#include <bits/stdc++.h>\n\
    using namespace std;\n\n#include \"../math/digit_dfa.cpp\"\n#include \"../util/fastio.cpp\"\
    \n\ntemplate<int W>\nbool accepts(const DFA<W>& a, const string& s, char start)\
    \ {\n    int v = a.initial;\n    for (char c : s) {\n        if (v == -1) return\
    \ false;\n        v = a.next[v][c - start];\n    }\n    return v != -1 && a.accept[v];\n\
    }\n\ntemplate<int W>\nvoid check_reachable(const DFA<W>& a) {\n    assert(a.accept.size()\
    \ == a.next.size());\n    if (a.initial == -1) {\n        assert(a.next.empty());\n\
    \        return;\n    }\n    vector<char> seen(a.next.size());\n    vector<int>\
    \ q{a.initial};\n    seen[a.initial] = true;\n    for (size_t i = 0; i < q.size();\
    \ ++i) {\n        for (int v : a.next[q[i]]) {\n            assert(-1 <= v &&\
    \ v < (int)a.next.size());\n            if (v != -1 && !seen[v]) seen[v] = true,\
    \ q.push_back(v);\n        }\n    }\n    assert(q.size() == a.next.size());\n\
    }\n\nvoid self_check() {\n    mt19937 rng(149);\n    for (int tc = 0; tc < 300;\
    \ ++tc) {\n        auto random_dfa = [&]() {\n            int n = 1 + rng() %\
    \ 8;\n            DFA<2> a{vector<array<int, 2>>(n), vector<char>(n), int(rng()\
    \ % (n + 1)) - 1};\n            for (int v = 0; v < n; ++v) {\n              \
    \  a.accept[v] = rng() % 2;\n                for (int& to : a.next[v]) to = int(rng()\
    \ % (n + 1)) - 1;\n            }\n            return a;\n        };\n        auto\
    \ a = random_dfa(), b = random_dfa();\n        auto c = intersect(a, b);\n   \
    \     check_reachable(c);\n        for (int n = 0; n <= 8; ++n) {\n          \
    \  for (int mask = 0; mask < (1 << n); ++mask) {\n                string s(n,\
    \ 'a');\n                for (int i = 0; i < n; ++i) s[i] += mask >> i & 1;\n\
    \                assert(accepts(c, s, 'a') == (accepts(a, s, 'a') && accepts(b,\
    \ s, 'a')));\n            }\n        }\n    }\n    assert(intersect(digit_value_mod(2),\
    \ digit_value_mod(4)).next.size() == 4);\n    assert(intersect(DFA<10>{}, digit_value_mod(1)).initial\
    \ == -1);\n    for (int m = 1; m <= 12; ++m) {\n        for (int r = 0; r < m;\
    \ ++r) {\n            auto value = digit_value_mod(m, r), sum = digit_sum_mod(m,\
    \ r);\n            for (int x = 0; x <= 2000; ++x) {\n                string s\
    \ = to_string(x);\n                int total = 0;\n                for (char c\
    \ : s) total += c - '0';\n                assert(accepts(value, s, '0') == (x\
    \ % m == r));\n                assert(accepts(sum, s, '0') == (total % m == r));\n\
    \                assert(accepts(value, \"00\" + s, '0') == (x % m == r));\n  \
    \          }\n        }\n    }\n    for (int k = 0; k <= 30; ++k) {\n        auto\
    \ exact = digit_sum_exact(k);\n        for (int x = 0; x <= 2000; ++x) {\n   \
    \         string s = to_string(x);\n            int total = 0;\n            for\
    \ (char c : s) total += c - '0';\n            assert(accepts(exact, s, '0') ==\
    \ (total == k));\n        }\n    }\n    for (int mask = 0; mask < 1024; ++mask)\
    \ {\n        auto a = required_digits(mask);\n        assert(a.next.size() ==\
    \ size_t(1 << __builtin_popcount(unsigned(mask))));\n        assert(accepts(a,\
    \ \"\", '0') == (mask == 0));\n        for (int x = 0; x <= 2000; ++x) {\n   \
    \         string s = to_string(x);\n            int seen = 0;\n            for\
    \ (char c : s) seen |= 1 << (c - '0');\n            assert(accepts(a, s, '0')\
    \ == ((seen & mask) == mask));\n        }\n    }\n    auto adjacent = no_equal_adjacent();\n\
    \    for (int x = 0; x <= 2000; ++x) {\n        string s = to_string(x);\n   \
    \     assert(accepts(adjacent, s, '0') == (adjacent_find(s.begin(), s.end()) ==\
    \ s.end()));\n    }\n    assert(accepts(adjacent, \"\", '0'));\n    assert(!accepts(adjacent,\
    \ \"00\", '0'));\n    assert(accepts(digit_sum_exact(0), \"\", '0'));\n    assert(!accepts(digit_sum_exact(1),\
    \ \"\", '0'));\n}\n\nint main() {\n    self_check();\n    Scanner sc;\n    Printer\
    \ pr;\n    int a, b;\n    sc.read(a, b);\n    pr.println(a + b);\n}\n"
  dependsOn:
  - math/digit_dfa.cpp
  - string/dfa.cpp
  - util/fastio.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_dfa.test.cpp
  requiredBy: []
  timestamp: '2026-10-16 22:08:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_dfa.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_dfa.test.cpp
- /verify/test/yosupo_aplusb_dfa.test.cpp.html
title: test/yosupo_aplusb_dfa.test.cpp
---
