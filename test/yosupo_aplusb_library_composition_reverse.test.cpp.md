---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/sparsetable.cpp
    title: Sparse Table
  - icon: ':heavy_check_mark:'
    path: graph/SCC.cpp
    title: "\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3(SCC)"
  - icon: ':heavy_check_mark:'
    path: graph/bellman_ford.cpp
    title: "Bellman-Ford\u6CD5"
  - icon: ':heavy_check_mark:'
    path: graph/bfs01.cpp
    title: 01-BFS
  - icon: ':heavy_check_mark:'
    path: graph/biconnected_components.cpp
    title: "\u4E8C\u91CD\u9023\u7D50\u6210\u5206\u5206\u89E3(Biconnected Components)"
  - icon: ':heavy_check_mark:'
    path: graph/biconnected_components.cpp
    title: "\u4E8C\u91CD\u9023\u7D50\u6210\u5206\u5206\u89E3(Biconnected Components)"
  - icon: ':heavy_check_mark:'
    path: graph/block_cut_tree.cpp
    title: "\u30D6\u30ED\u30C3\u30AF\u30AB\u30C3\u30C8\u6728(Block-Cut Tree)"
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.cpp
    title: "Dijkstra\u6CD5"
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra_common.cpp
    title: graph/dijkstra_common.cpp
  - icon: ':heavy_check_mark:'
    path: graph/edge.cpp
    title: graph/edge.cpp
  - icon: ':heavy_check_mark:'
    path: graph/twosat.cpp
    title: 2-SAT
  - icon: ':heavy_check_mark:'
    path: tree/auxtree.cpp
    title: "\u88DC\u52A9\u6728(Aux Tree)"
  - icon: ':heavy_check_mark:'
    path: tree/auxtree.cpp
    title: "\u88DC\u52A9\u6728(Aux Tree)"
  - icon: ':heavy_check_mark:'
    path: tree/hld.cpp
    title: "HL\u5206\u89E3(HL Decomposition)"
  - icon: ':heavy_check_mark:'
    path: tree/hld.cpp
    title: "HL\u5206\u89E3(HL Decomposition)"
  - icon: ':heavy_check_mark:'
    path: tree/hld_edge.cpp
    title: "HL\u5206\u89E3(\u8FBA\u30AF\u30A8\u30EA)"
  - icon: ':heavy_check_mark:'
    path: tree/virtual_tree_helper.cpp
    title: Virtual Tree Helper
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_library_composition_reverse.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\ntemplate<class T> constexpr T INF = numeric_limits<T>::max()\
    \ / 32 * 15 + 208;\nusing ll = long long;\nusing uint = unsigned;\nusing ull =\
    \ unsigned long long;\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\n\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 12 \"\
    test/yosupo_aplusb_library_composition_reverse.test.cpp\"\n\n#line 1 \"graph/edge.cpp\"\
    \n\n\n\ntemplate <typename T>\nstruct edge {\n    int from, to;\n    T cost;\n\
    \n    edge(int to, T cost) : from(-1), to(to), cost(cost) {}\n    edge(int from,\
    \ int to, T cost) : from(from), to(to), cost(cost) {}\n\n    explicit operator\
    \ int() const { return to; }\n};\n\n\n#line 2 \"graph/bellman_ford.cpp\"\n\ntemplate\
    \ <typename T>\nvector<T> bellman_ford(int s, int V,vector<edge<T> > &G){\n  \
    \  const T INF = numeric_limits<T>::max();\n    vector<T> d(V, INF);\n    d[s]\
    \ = 0;\n    for (int i = 0; i < V - 1; ++i) {\n        bool updated = false;\n\
    \        for (auto &&e : G) {\n            if (d[e.from] == INF) continue;\n \
    \           if (d[e.from] + e.cost < d[e.to]) {\n                d[e.to] = d[e.from]\
    \ + e.cost;\n                updated = true;\n            }\n        }\n     \
    \   if (!updated) return d;\n    }\n    for (auto &&e : G) {\n        if(d[e.from]\
    \ == INF) continue;\n        if(d[e.from] + e.cost < d[e.to]) return vector<T>\
    \ ();\n    }\n    return d;\n}\n\n/**\n * @brief Bellman-Ford\u6CD5\n */\n#line\
    \ 2 \"graph/bfs01.cpp\"\n\ntemplate <typename T>\nvector<T> bfs01(int s, vector<vector<edge<T>>>\
    \ &G) {\n    int n = G.size();\n    vector<T> d(n, INF<T>);\n    deque<int> q;\n\
    \    d[s] = 0;\n    q.push_front(s);\n    while (!q.empty()) {\n        int v\
    \ = q.front();\n        q.pop_front();\n        for (auto &&e : G[v]) {\n    \
    \        T nd = d[v] + e.cost;\n            if (d[e.to] <= nd) continue;\n   \
    \         d[e.to] = nd;\n            if (e.cost == T(0)) {\n                q.push_front(e.to);\n\
    \            } else {\n                assert(e.cost == T(1));\n             \
    \   q.push_back(e.to);\n            }\n        }\n    }\n    return d;\n}\n\n\
    /**\n * @brief 01-BFS\n */\n#line 1 \"graph/dijkstra_common.cpp\"\n\n\n\n#line\
    \ 5 \"graph/dijkstra_common.cpp\"\n\ntemplate <typename T>\nstruct DijkstraPriorityQueue\
    \ {\n    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;\n\n\
    \    bool empty() const { return q.empty(); }\n\n    void push(T cost, int v)\
    \ {\n        q.emplace(cost, v);\n    }\n\n    pair<T, int> pop() {\n        auto\
    \ res = q.top();\n        q.pop();\n        return res;\n    }\n};\n\ntemplate\
    \ <typename T, class Queue, class OnRelax>\nvector<T> dijkstra_internal(int s,\
    \ const vector<vector<edge<T>>> &G, Queue &Q, OnRelax on_relax) {\n    int n =\
    \ (int)G.size();\n    vector<T> dist(n, INF<T>);\n    dist[s] = 0;\n    Q.push(T(0),\
    \ s);\n    while (!Q.empty()) {\n        auto [cost, v] = Q.pop();\n        if\
    \ (dist[v] < cost) continue;\n        for (auto &&e : G[v]) {\n            T nxt\
    \ = cost + e.cost;\n            if (dist[e.to] <= nxt) continue;\n           \
    \ dist[e.to] = nxt;\n            on_relax(v, e);\n            Q.push(nxt, e.to);\n\
    \        }\n    }\n    return dist;\n}\n\ntemplate <typename T, class Queue>\n\
    vector<T> dijkstra_internal(int s, const vector<vector<edge<T>>> &G, Queue &Q)\
    \ {\n    return dijkstra_internal(s, G, Q, [](int, const edge<T> &) {});\n}\n\n\
    \n#line 2 \"graph/dijkstra.cpp\"\n\ntemplate <typename T>\nvector<T> dijkstra(int\
    \ s, const vector<vector<edge<T>>> &G) {\n    DijkstraPriorityQueue<T> Q;\n  \
    \  return dijkstra_internal(s, G, Q);\n}\n\n/**\n * @brief Dijkstra\u6CD5\n */\n\
    #line 16 \"test/yosupo_aplusb_library_composition_reverse.test.cpp\"\n\n#line\
    \ 1 \"graph/twosat.cpp\"\nstruct TwoSAT {\n    struct SCC {\n        struct CSR\
    \ {\n            vector<int> start, elist;\n\n            CSR() = default;\n\n\
    \            CSR(int n, const vector<pair<int, int>> &edges, bool rev) : start(n\
    \ + 1), elist(edges.size()) {\n                for (auto &&[a, b] : edges) {\n\
    \                    ++start[(rev ? b : a) + 1];\n                }\n        \
    \        for (int i = 0; i < n; ++i) start[i + 1] += start[i];\n             \
    \   auto counter = start;\n                for (auto &&[a, b] : edges) {\n   \
    \                 int from = rev ? b : a;\n                    int to = rev ?\
    \ a : b;\n                    elist[counter[from]++] = to;\n                }\n\
    \            }\n        };\n\n        int n = 0;\n        vector<pair<int, int>>\
    \ edges;\n        vector<int> vs, used, cmp;\n        SCC() = default;\n     \
    \   explicit SCC(int n) : n(n), used(n), cmp(n) {}\n\n        void add_edge(int\
    \ a, int b){\n            edges.emplace_back(a, b);\n        }\n\n        int\
    \ build() {\n            CSR G(n, edges, false), G_r(n, edges, true);\n      \
    \      vs.clear();\n            vs.reserve(n);\n            fill(used.begin(),\
    \ used.end(), 0);\n            auto dfs = [&](auto &&self, int v) -> void {\n\
    \                used[v] = 1;\n                for (int ei = G.start[v]; ei <\
    \ G.start[v + 1]; ++ei) {\n                    int u = G.elist[ei];\n        \
    \            if(!used[u]) self(self, u);\n                }\n                vs.emplace_back(v);\n\
    \            };\n            for (int i = 0; i < n; ++i) {\n                if(!used[i])\
    \ dfs(dfs, i);\n            }\n            fill(used.begin(),used.end(), 0);\n\
    \            int k = 0;\n            auto dfs_r = [&](auto &&self, int v, int\
    \ c) -> void {\n                used[v] = 1;\n                cmp[v] = c;\n  \
    \              for (int ei = G_r.start[v]; ei < G_r.start[v + 1]; ++ei) {\n  \
    \                  int u = G_r.elist[ei];\n                    if(!used[u]) self(self,\
    \ u, c);\n                }\n            };\n            for (int i = n - 1; i\
    \ >= 0; --i) {\n                if(!used[vs[i]]){\n                    dfs_r(dfs_r,\
    \ vs[i], k++);\n                }\n            }\n            return k;\n    \
    \    }\n\n        int operator[](int k) const { return cmp[k]; }\n    };\n\n \
    \   int n;\n    SCC scc;\n    explicit TwoSAT(int n) : n(n), scc(n*2) {};\n  \
    \  int negate(int v){\n        int ret = n+v;\n        if(ret >= n*2) ret -= n*2;\n\
    \        return ret;\n    }\n\n    vector<int> build() {\n        scc.build();\n\
    \        vector<int> res(n);\n        for (int i = 0; i < n; ++i) {\n        \
    \    if(scc[i] == scc[n+i]) return {};\n            res[i] = scc[i] > scc[n+i];\n\
    \        }\n        return res;\n    }\n\n    void add_if(int u, int v){ // u\
    \ -> v\n        scc.add_edge(u, v);\n        scc.add_edge(negate(v), negate(u));\n\
    \    }\n\n    void add_or(int u, int v){ // u || v\n        add_if(negate(u),\
    \ v);\n    }\n};\n\n/**\n * @brief 2-SAT\n */\n#line 1 \"graph/SCC.cpp\"\nclass\
    \ SCC {\n    struct CSR {\n        vector<int> start, elist;\n\n        CSR()\
    \ = default;\n\n        CSR(int n, const vector<pair<int, int>> &edges, bool rev)\
    \ : start(n + 1), elist(edges.size()) {\n            for (auto &&[a, b] : edges)\
    \ {\n                ++start[(rev ? b : a) + 1];\n            }\n            for\
    \ (int i = 0; i < n; ++i) start[i + 1] += start[i];\n            auto counter\
    \ = start;\n            for (auto &&[a, b] : edges) {\n                int from\
    \ = rev ? b : a;\n                int to = rev ? a : b;\n                elist[counter[from]++]\
    \ = to;\n            }\n        }\n    };\n\n    int n = 0;\n    vector<pair<int,\
    \ int>> edges;\n\npublic:\n    vector<vector<int>> G_out;\n    vector<int> vs,\
    \ used, cmp, sz;\n    SCC() = default;\n    explicit SCC(int n) : n(n), used(n),\
    \ cmp(n), sz(n) {}\n\n    void add_edge(int a, int b){\n        edges.emplace_back(a,\
    \ b);\n    }\n\n    int build() {\n        CSR G(n, edges, false), G_r(n, edges,\
    \ true);\n        vs.clear();\n        vs.reserve(n);\n        fill(used.begin(),\
    \ used.end(), 0);\n        auto dfs = [&](auto &&self, int v) -> void {\n    \
    \        used[v] = 1;\n            for (int ei = G.start[v]; ei < G.start[v +\
    \ 1]; ++ei) {\n                int u = G.elist[ei];\n                if(!used[u])\
    \ self(self, u);\n            }\n            vs.emplace_back(v);\n        };\n\
    \        for (int i = 0; i < n; ++i) {\n            if(!used[i]) dfs(dfs, i);\n\
    \        }\n        fill(used.begin(), used.end(), 0);\n        sz.resize(n);\n\
    \        fill(sz.begin(), sz.end(), 0);\n        int k = 0;\n        auto dfs_r\
    \ = [&](auto &&self, int v, int c) -> void {\n            used[v] = 1;\n     \
    \       cmp[v] = c;\n            sz[c]++;\n            for (int ei = G_r.start[v];\
    \ ei < G_r.start[v + 1]; ++ei) {\n                int u = G_r.elist[ei];\n   \
    \             if(!used[u]) self(self, u, c);\n            }\n        };\n    \
    \    for (int i = n - 1; i >= 0; --i) {\n            if(!used[vs[i]]){\n     \
    \           dfs_r(dfs_r, vs[i], k++);\n            }\n        }\n        G_out.assign(k,\
    \ {});\n        sz.resize(k);\n        if (k <= 1) return k;\n        vector<int>\
    \ head(k, -1), next(n), seen(k, -1);\n        for (int v = 0; v < n; ++v) {\n\
    \            next[v] = head[cmp[v]];\n            head[cmp[v]] = v;\n        }\n\
    \        for (int to = 0; to < k; ++to) {\n            for (int v = head[to];\
    \ v != -1; v = next[v]) {\n                for (int ei = G_r.start[v]; ei < G_r.start[v\
    \ + 1]; ++ei) {\n                    int from = cmp[G_r.elist[ei]];\n        \
    \            if (from == to || seen[from] == to) continue;\n                 \
    \   seen[from] = to;\n                    G_out[from].push_back(to);\n       \
    \         }\n            }\n        }\n        return k;\n    }\n\n    int operator[](int\
    \ k) const { return cmp[k]; }\n};\n\n/**\n * @brief \u5F37\u9023\u7D50\u6210\u5206\
    \u5206\u89E3(SCC)\n */\n#line 19 \"test/yosupo_aplusb_library_composition_reverse.test.cpp\"\
    \n\n#line 1 \"graph/block_cut_tree.cpp\"\nusing namespace std;\n\n#line 1 \"graph/biconnected_components.cpp\"\
    \n\n\n\nclass BiconnectedComponents {\n    struct CSR {\n        vector<int> start,\
    \ elist;\n\n        CSR() = default;\n\n        CSR(int n, const vector<pair<int,\
    \ int>> &edges) : start(n + 1), elist(edges.size() * 2) {\n            for (auto\
    \ &&[u, v] : edges) {\n                ++start[u + 1];\n                ++start[v\
    \ + 1];\n            }\n            for (int i = 0; i < n; ++i) start[i + 1] +=\
    \ start[i];\n            auto counter = start;\n            for (int id = 0; id\
    \ < (int)edges.size(); ++id) {\n                auto &&[u, v] = edges[id];\n \
    \               elist[counter[u]++] = id;\n                elist[counter[v]++]\
    \ = id;\n            }\n        }\n    };\n\n    int n = 0;\n    vector<int> st;\n\
    \n    int other(int id, int v) const {\n        return edges[id].first ^ edges[id].second\
    \ ^ v;\n    }\n\n    void dfs(int i, int pe, const CSR &G, int &pos){\n      \
    \  ord[i] = low[i] = pos++;\n        for (int ei = G.start[i]; ei < G.start[i\
    \ + 1]; ++ei) {\n            int id = G.elist[ei];\n            if(id == pe) continue;\n\
    \            int j = other(id, i);\n            if(ord[j] < ord[i]) st.emplace_back(id);\n\
    \            if(~ord[j]){\n                low[i] = min(low[i], ord[j]);\n   \
    \             continue;\n            }\n            par[j] = i;\n            dfs(j,\
    \ id, G, pos);\n            low[i] = min(low[i], low[j]);\n            if(ord[i]\
    \ <= low[j]){\n                bcc_edges.emplace_back();\n                while(true){\n\
    \                    int k = st.back();\n                    st.pop_back();\n\
    \                    bcc_edges.back().emplace_back(min(edges[k].first, edges[k].second),\
    \ max(edges[k].first, edges[k].second));\n                    if(k == id) break;\n\
    \                }\n            }\n        }\n    }\npublic:\n    vector<int>\
    \ ord, low, par;\n    vector<pair<int, int>> edges;\n    vector<vector<pair<int,\
    \ int>>> bcc_edges;\n    vector<vector<int>> bcc_vertices;\n    explicit BiconnectedComponents(int\
    \ n): n(n), ord(n, -1), low(n), par(n, -1){}\n\n    void add_edge(int u, int v){\n\
    \        if(u == v) return;\n        edges.emplace_back(u, v);\n    }\n\n    int\
    \ build(){\n        CSR G(n, edges);\n        int pos = 0;\n        fill(ord.begin(),\
    \ ord.end(), -1);\n        fill(par.begin(), par.end(), -1);\n        bcc_edges.clear();\n\
    \        bcc_vertices.clear();\n        st.clear();\n        for (int i = 0; i\
    \ < n; ++i) {\n            if(ord[i] < 0) dfs(i, -1, G, pos);\n        }\n   \
    \     vector<int> seen(n, -1);\n        bcc_vertices.reserve(bcc_edges.size());\n\
    \        for (int i = 0; i < (int)bcc_edges.size(); ++i) {\n            vector<int>\
    \ now;\n            for (auto &&e : bcc_edges[i]) {\n                if(seen[e.first]\
    \ != i){\n                    seen[e.first] = i;\n                    now.emplace_back(e.first);\n\
    \                }\n                if(seen[e.second] != i){\n               \
    \     seen[e.second] = i;\n                    now.emplace_back(e.second);\n \
    \               }\n            }\n            bcc_vertices.emplace_back(std::move(now));\n\
    \        }\n        for (int i = 0; i < n; ++i) {\n            if(G.start[i] ==\
    \ G.start[i + 1]){\n                bcc_edges.emplace_back();\n              \
    \  bcc_vertices.push_back({i});\n            }\n        }\n        return bcc_vertices.size();\n\
    \    }\n};\n\n/**\n * @brief \u4E8C\u91CD\u9023\u7D50\u6210\u5206\u5206\u89E3\
    (Biconnected Components)\n */\n\n\n#line 4 \"graph/block_cut_tree.cpp\"\n\nstruct\
    \ BlockCutTree {\n    int n, block_count;\n    BiconnectedComponents bcc;\n  \
    \  vector<vector<int>> tree, nodes;\n    vector<int> id, rev;\n    vector<char>\
    \ is_articulation;\n\n    explicit BlockCutTree(int n) : n(n), block_count(0),\
    \ bcc(n), id(n, -1), is_articulation(n, 0) {}\n\n    void add_edge(int u, int\
    \ v) {\n        bcc.add_edge(u, v);\n    }\n\n    int build() {\n        block_count\
    \ = bcc.build();\n        vector<int> cnt(n);\n        for (auto &&vs : bcc.bcc_vertices)\
    \ {\n            for (auto &&v : vs) ++cnt[v];\n        }\n\n        int m = block_count;\n\
    \        id.assign(n, -1);\n        is_articulation.assign(n, 0);\n        for\
    \ (int v = 0; v < n; ++v) {\n            if (cnt[v] > 1) {\n                is_articulation[v]\
    \ = 1;\n                id[v] = m++;\n            }\n        }\n\n        tree.assign(m,\
    \ {});\n        nodes.assign(m, {});\n        rev.assign(m, -1);\n        for\
    \ (int i = 0; i < block_count; ++i) {\n            nodes[i] = bcc.bcc_vertices[i];\n\
    \            for (auto &&v : bcc.bcc_vertices[i]) {\n                if (cnt[v]\
    \ > 1) {\n                    tree[i].push_back(id[v]);\n                    tree[id[v]].push_back(i);\n\
    \                } else {\n                    id[v] = i;\n                }\n\
    \            }\n        }\n        for (int v = 0; v < n; ++v) {\n           \
    \ if (is_articulation[v]) {\n                nodes[id[v]].push_back(v);\n    \
    \            rev[id[v]] = v;\n            }\n        }\n        return m;\n  \
    \  }\n};\n\n/**\n * @brief \u30D6\u30ED\u30C3\u30AF\u30AB\u30C3\u30C8\u6728(Block-Cut\
    \ Tree)\n */\n#line 22 \"test/yosupo_aplusb_library_composition_reverse.test.cpp\"\
    \n\n#line 1 \"tree/auxtree.cpp\"\n\n\n\n#line 1 \"datastructure/sparsetable.cpp\"\
    \n\n\n\ntemplate <class F>\nstruct SparseTable {\n    using T = typename F::T;\n\
    \    vector<vector<T>> table;\n    vector<int> u;\n    SparseTable() = default;\n\
    \    explicit SparseTable(const vector<T> &v){ build(v); }\n \n    void build(const\
    \ vector<T> &v){\n        int n = v.size(), m = 1;\n        while((1<<m) <= n)\
    \ m++;\n        table.assign(m, vector<T>(n));\n        u.assign(n+1, 0);\n  \
    \      for (int i = 2; i <= n; ++i) {\n            u[i] = u[i>>1] + 1;\n     \
    \   }\n        for (int i = 0; i < n; ++i) {\n            table[0][i] = v[i];\n\
    \        }\n        for (int i = 1; i < m; ++i) {\n            int x = (1<<(i-1));\n\
    \            for (int j = 0; j < n; ++j) {\n                table[i][j] = F::f(table[i-1][j],\
    \ table[i-1][min(j+x, n-1)]);\n            }\n        }\n    }\n \n    T query(int\
    \ a, int b){\n        int l = b-a;\n        return F::f(table[u[l]][a], table[u[l]][b-(1<<u[l])]);\n\
    \    }\n};\n\n/**\n * @brief Sparse Table\n */\n\n\n#line 5 \"tree/auxtree.cpp\"\
    \n\nstruct F {\n    using T = pair<int, int>;\n    static T f(T a, T b) { return\
    \ min(a, b); }\n    static T e() { return T{INF<int>, -1}; }\n};\n\nclass AuxTree\
    \ {\n    SparseTable<F> table;\n    void dfs_euler(int v, int p, int d, int &k,\
    \ int &l){\n        id[v] = k;\n        vs[k] = v;\n        depth[k++] = d;\n\
    \        dep[v] = d;\n        fi[v] = l++;\n        for (auto &&u : G[v]) {\n\
    \            if(u != p){\n                dfs_euler(u, v, d+1, k, l);\n      \
    \          vs[k] = v;\n                depth[k++] = d;\n            }\n      \
    \  }\n    }\npublic:\n    int n;\n    vector<vector<int>> G, out;\n    vector<int>\
    \ vs, depth, dep, id, fi;\n    explicit AuxTree(int n) : table(), n(n), G(n),\
    \ out(n), vs(2*n-1), depth(2*n-1), dep(n), id(n), fi(n) {};\n    void add_edge(int\
    \ a, int b){\n        G[a].emplace_back(b);\n        G[b].emplace_back(a);\n \
    \   }\n\n    void eulertour(int root) {\n        int k = 0, l = 0;\n        dfs_euler(root,\
    \ -1, 0, k, l);\n    }\n\n    void buildLCA(int root = 0){\n        eulertour(root);\n\
    \        vector<pair<int, int>> v(2*n-1);\n        for (int i = 0; i < 2*n-1;\
    \ ++i) {\n            v[i] = make_pair(depth[i], vs[i]);\n        }\n        table.build(v);\n\
    \    }\n\n    void make(vector<int> &v){\n        if(v.empty()) return;\n    \
    \    sort(v.begin(),v.end(), [&](int a, int b){ return fi[a] < fi[b]; });\n  \
    \      v.erase(unique(v.begin(), v.end()), v.end());\n        int k = v.size();\n\
    \        stack<int> s;\n        s.emplace(v.front());\n        for (int i = 0;\
    \ i+1 < k; ++i) {\n            int w = LCA(v[i], v[i+1]);\n            if(w !=\
    \ v[i]){\n                int u = s.top(); s.pop();\n                while(!s.empty()\
    \ && dep[w] < dep[s.top()]){\n                    out[s.top()].emplace_back(u);\n\
    \                    out[u].emplace_back(s.top());\n                    u = s.top();\
    \ s.pop();\n                }\n                if(s.empty() || s.top() != w){\n\
    \                    s.emplace(w);\n                    v.emplace_back(w);\n \
    \               }\n                out[w].emplace_back(u);\n                out[u].emplace_back(w);\n\
    \            }\n            s.emplace(v[i+1]);\n        }\n        while(s.size()\
    \ > 1){\n            int u = s.top(); s.pop();\n            out[s.top()].emplace_back(u);\n\
    \            out[u].emplace_back(s.top());\n        }\n    }\n\n    void clear(vector<int>\
    \ &v){\n        for (auto &&i : v) {\n            out[i].clear();\n        }\n\
    \    }\n\n    int LCA(int u, int v){\n        if(id[u] > id[v]) swap(u, v);\n\
    \        return table.query(id[u], id[v]+1).second;\n    }\n\n    int distance(int\
    \ u, int v){\n        return dep[u]+dep[v]-2*dep[LCA(u, v)];\n    }\n};\n\n/**\n\
    \ * @brief \u88DC\u52A9\u6728(Aux Tree)\n */\n\n\n#line 2 \"tree/virtual_tree_helper.cpp\"\
    \n\nstruct VirtualTree {\n    int root;\n    vector<int> vertices;\n    vector<int>\
    \ parent;\n};\n\nclass VirtualTreeHelper {\n    AuxTree aux;\n    vector<int>\
    \ mark, parent_buf;\n    int stamp = 0;\n\npublic:\n    explicit VirtualTreeHelper(int\
    \ n) : aux(n), mark(n, 0), parent_buf(n, -1) {}\n\n    void add_edge(int u, int\
    \ v) {\n        aux.add_edge(u, v);\n    }\n\n    void build(int root = 0) {\n\
    \        aux.buildLCA(root);\n    }\n\n    int lca(int u, int v) {\n        return\
    \ aux.LCA(u, v);\n    }\n\n    int distance(int u, int v) {\n        return aux.distance(u,\
    \ v);\n    }\n\n    VirtualTree make(vector<int> vertices) {\n        if (vertices.empty())\
    \ return {-1, {}, {}};\n        aux.make(vertices);\n        sort(vertices.begin(),\
    \ vertices.end(), [&](int a, int b) { return aux.fi[a] < aux.fi[b]; });\n    \
    \    vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());\n\
    \n        VirtualTree res;\n        res.root = vertices.front();\n        ++stamp;\n\
    \        vector<int> st = {res.root};\n        mark[res.root] = stamp;\n     \
    \   parent_buf[res.root] = -1;\n\n        while (!st.empty()) {\n            int\
    \ v = st.back();\n            st.pop_back();\n            res.vertices.emplace_back(v);\n\
    \            res.parent.emplace_back(parent_buf[v]);\n            for (auto &&u\
    \ : aux.out[v]) {\n                if (mark[u] == stamp) continue;\n         \
    \       mark[u] = stamp;\n                parent_buf[u] = v;\n               \
    \ st.emplace_back(u);\n            }\n        }\n\n        aux.clear(vertices);\n\
    \        return res;\n    }\n};\n\n/**\n * @brief Virtual Tree Helper\n */\n#line\
    \ 1 \"tree/hld.cpp\"\n\n\n\nclass HeavyLightDecomposition {\n    void dfs_sz(int\
    \ v){\n        int heavy = -1;\n        for (auto &&u : G[v]) {\n            if(u\
    \ == par[v]) continue;\n            par[u] = v; dep[u] = dep[v] + 1;\n       \
    \     dfs_sz(u);\n            sub_size[v] += sub_size[u];\n            if(heavy\
    \ == -1 || sub_size[u] > sub_size[heavy]) heavy = u;\n        }\n        if (heavy\
    \ != -1 && G[v][0] != heavy) {\n            for (auto &&u : G[v]) {\n        \
    \        if (u == heavy) {\n                    swap(u, G[v][0]);\n          \
    \          break;\n                }\n            }\n        }\n    }\n    void\
    \ dfs_hld(int v, int c, int &pos){\n        id[v] = pos++;\n        id_inv[id[v]]=\
    \ v;\n        tree_id[v] = c;\n        for (auto &&u : G[v]) {\n            if(u\
    \ == par[v]) continue;\n            head[u] = (u == G[v][0] ? head[v] : u);\n\
    \            dfs_hld(u, c, pos);\n        }\n    }\npublic:\n    int n;\n    vector<vector<int>>\
    \ G;\n    vector<int> par, dep, sub_size, id, id_inv, tree_id, head;\n    explicit\
    \ HeavyLightDecomposition(int n) : n(n), G(n), par(n), dep(n), sub_size(n, 1),\
    \ id(n), id_inv(n), tree_id(n), head(n){}\n    explicit HeavyLightDecomposition(vector<vector<int>>\
    \ &G) : n(G.size()), G(G), par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n),\
    \ head(n) {}\n\n    void add_edge(int u, int v){\n        G[u].emplace_back(v);\n\
    \        G[v].emplace_back(u);\n    }\n\n    void build(vector<int> roots = {0}){\n\
    \        fill(par.begin(), par.end(), -1);\n        fill(dep.begin(), dep.end(),\
    \ 0);\n        fill(sub_size.begin(), sub_size.end(), 1);\n        int c = 0,\
    \ pos = 0;\n        for (auto &&i : roots) {\n            dfs_sz(i);\n       \
    \     head[i] = i;\n            dfs_hld(i, c++, pos);\n        }\n    }\n\n  \
    \  int lca(int u, int v){\n        while(true){\n            if(id[u] > id[v])\
    \ swap(u, v);\n            if(head[u] == head[v]) return u;\n            v = par[head[v]];\n\
    \        }\n    }\n\n    int parent(int v) const {\n        return par[v];\n \
    \   }\n\n    int ancestor(int v, int k) {\n        if(dep[v] < k) return -1;\n\
    \        while(true) {\n            int u = head[v];\n            if(id[v] - k\
    \ >= id[u]) return id_inv[id[v] - k];\n            k -= id[v]-id[u]+1;\n     \
    \       v = par[u];\n        }\n    }\n\n    int distance(int u, int v){ return\
    \ dep[u] + dep[v] - 2*dep[lca(u, v)]; }\n\n    pair<int, int> subtree(int v, bool\
    \ edge = false) const {\n        return {id[v] + edge, id[v] + sub_size[v]};\n\
    \    }\n\n    template<typename F>\n    void add(int u, int v, const F &f, bool\
    \ edge){\n        while (head[u] != head[v]){\n            if(id[u] > id[v]) swap(u,\
    \ v);\n            f(id[head[v]], id[v]+1);\n            v = par[head[v]];\n \
    \       }\n        if(id[u] > id[v]) swap(u, v);\n        f(id[u]+edge, id[v]+1);\n\
    \    }\n\n    template<typename F>\n    void path(int u, int v, const F &f, bool\
    \ edge = false){\n        add(u, v, f, edge);\n    }\n\n    template<typename\
    \ F>\n    void apply_subtree(int v, const F &f, bool edge = false){\n        auto\
    \ [l, r] = subtree(v, edge);\n        f(l, r);\n    }\n\n    template<typename\
    \ T, typename Q, typename F>\n    T query(int u, int v, const T &e, const Q &q,\
    \ const F &f, bool edge){\n        T l = e, r = e;\n        while(head[u] != head[v]){\n\
    \            if(id[u] > id[v]) swap(u, v), swap(l, r);\n            l = f(l, q(id[head[v]],\
    \ id[v]+1));\n            v = par[head[v]];\n        }\n        if(id[u] > id[v])\
    \ swap(u, v), swap(l, r);\n        return f(q(id[u]+edge, id[v]+1), f(l, r));\n\
    \    }\n\n    template<typename T, typename Q, typename F>\n    T path_query(int\
    \ u, int v, const T &e, const Q &q, const F &f, bool edge = false){\n        return\
    \ query(u, v, e, q, f, edge);\n    }\n\n    template<typename T, typename QL,\
    \ typename QR, typename F>\n    T query_order(int u, int v, const T &e, const\
    \ QL &ql, const QR &qr, const F &f, bool edge){\n        T l = e, r = e;\n   \
    \     while(head[u] != head[v]){\n            if(id[u] > id[v]) {\n          \
    \      l = f(l, qr(id[head[u]], id[u]+1));\n                u = par[head[u]];\n\
    \            }else {\n                r = f(ql(id[head[v]], id[v]+1), r);\n  \
    \              v = par[head[v]];\n            }\n        }\n        T mid = (id[u]\
    \ > id[v] ? qr(id[v]+edge, id[u]+1) : ql(id[u]+edge, id[v]+1));\n        return\
    \ f(f(l, mid), r);\n    }\n\n    template<typename T, typename QL, typename QR,\
    \ typename F>\n    T path_query_ordered(int u, int v, const T &e, const QL &ql,\
    \ const QR &qr, const F &f, bool edge = false){\n        return query_order(u,\
    \ v, e, ql, qr, f, edge);\n    }\n\n    template<typename Q>\n    decltype(auto)\
    \ subtree_query(int v, const Q &q, bool edge = false){\n        auto [l, r] =\
    \ subtree(v, edge);\n        return q(l, r);\n    }\n};\n\n/**\n * @brief HL\u5206\
    \u89E3(HL Decomposition)\n */\n\n\n#line 2 \"tree/hld_edge.cpp\"\n\nstruct HeavyLightDecompositionEdge\
    \ {\n    HeavyLightDecomposition hld;\n\n    explicit HeavyLightDecompositionEdge(int\
    \ n) : hld(n) {}\n    explicit HeavyLightDecompositionEdge(vector<vector<int>>\
    \ &g) : hld(g) {}\n\n    void add_edge(int u, int v) {\n        hld.add_edge(u,\
    \ v);\n    }\n\n    void build(vector<int> roots = {0}) {\n        hld.build(roots);\n\
    \    }\n\n    int lca(int u, int v) {\n        return hld.lca(u, v);\n    }\n\n\
    \    int parent(int v) const {\n        return hld.parent(v);\n    }\n\n    int\
    \ ancestor(int v, int k) {\n        return hld.ancestor(v, k);\n    }\n\n    int\
    \ distance(int u, int v) {\n        return hld.distance(u, v);\n    }\n\n    int\
    \ edge_index(int v) const {\n        if (hld.par[v] == -1) return -1;\n      \
    \  return hld.id[v];\n    }\n\n    pair<int, int> subtree(int v) const {\n   \
    \     return hld.subtree(v, true);\n    }\n\n    template<typename F>\n    void\
    \ path(int u, int v, const F &f) {\n        hld.path(u, v, f, true);\n    }\n\n\
    \    template<typename F>\n    void apply_subtree(int v, const F &f) {\n     \
    \   hld.apply_subtree(v, f, true);\n    }\n\n    template<typename T, typename\
    \ Q, typename F>\n    T path_query(int u, int v, const T &e, const Q &q, const\
    \ F &f) {\n        return hld.path_query(u, v, e, q, f, true);\n    }\n\n    template<typename\
    \ T, typename QL, typename QR, typename F>\n    T path_query_ordered(int u, int\
    \ v, const T &e, const QL &ql, const QR &qr, const F &f) {\n        return hld.path_query_ordered(u,\
    \ v, e, ql, qr, f, true);\n    }\n\n    template<typename Q>\n    decltype(auto)\
    \ subtree_query(int v, const Q &q) {\n        return hld.subtree_query(v, q, true);\n\
    \    }\n};\n\n/**\n * @brief HL\u5206\u89E3(\u8FBA\u30AF\u30A8\u30EA)\n */\n#line\
    \ 27 \"test/yosupo_aplusb_library_composition_reverse.test.cpp\"\n\nint main()\
    \ {\n    Scanner in;\n    Printer out;\n    ll a, b;\n    in.read(a, b);\n   \
    \ out.println(a + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\ntemplate<class T> constexpr T INF = numeric_limits<T>::max()\
    \ / 32 * 15 + 208;\nusing ll = long long;\nusing uint = unsigned;\nusing ull =\
    \ unsigned long long;\n\n#include \"../util/fastio.cpp\"\n\n#include \"../graph/bellman_ford.cpp\"\
    \n#include \"../graph/bfs01.cpp\"\n#include \"../graph/dijkstra.cpp\"\n\n#include\
    \ \"../graph/twosat.cpp\"\n#include \"../graph/SCC.cpp\"\n\n#include \"../graph/block_cut_tree.cpp\"\
    \n#include \"../graph/biconnected_components.cpp\"\n\n#include \"../tree/virtual_tree_helper.cpp\"\
    \n#include \"../tree/auxtree.cpp\"\n#include \"../tree/hld_edge.cpp\"\n#include\
    \ \"../tree/hld.cpp\"\n\nint main() {\n    Scanner in;\n    Printer out;\n   \
    \ ll a, b;\n    in.read(a, b);\n    out.println(a + b);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - graph/bellman_ford.cpp
  - graph/edge.cpp
  - graph/bfs01.cpp
  - graph/dijkstra.cpp
  - graph/dijkstra_common.cpp
  - graph/twosat.cpp
  - graph/SCC.cpp
  - graph/block_cut_tree.cpp
  - graph/biconnected_components.cpp
  - graph/biconnected_components.cpp
  - tree/virtual_tree_helper.cpp
  - tree/auxtree.cpp
  - datastructure/sparsetable.cpp
  - tree/auxtree.cpp
  - tree/hld_edge.cpp
  - tree/hld.cpp
  - tree/hld.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_library_composition_reverse.test.cpp
  requiredBy: []
  timestamp: '2026-10-06 23:06:10+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_library_composition_reverse.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_library_composition_reverse.test.cpp
- /verify/test/yosupo_aplusb_library_composition_reverse.test.cpp.html
title: test/yosupo_aplusb_library_composition_reverse.test.cpp
---
