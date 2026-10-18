---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/bipartite_matching.cpp
    title: "\u4E8C\u90E8\u30B0\u30E9\u30D5\u6700\u5927\u30DE\u30C3\u30C1\u30F3\u30B0\
      (Bipartite Matching)"
  - icon: ':heavy_check_mark:'
    path: graph/bipartite_matching_lexmin.cpp
    title: "\u8F9E\u66F8\u9806\u6700\u5C0F\u4E8C\u90E8\u30DE\u30C3\u30C1\u30F3\u30B0\
      (Lexicographically Minimum Bipartite Matching)"
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_bipartite_matching_lexmin.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"graph/bipartite_matching.cpp\"\
    \nclass Bipartite_Matching {\nprotected:\n    vector<vector<int>> G;\n    vector<int>\
    \ used, alive;\n    int t;\n    int l, r;\n\npublic:\n    vector<int> match;\n\
    \n    explicit Bipartite_Matching(int l, int r)\n        : G(l), used(l, 0), alive(l\
    \ + r, -1), t(0), l(l), r(r), match(l + r, -1) {}\n\n    void add_edge(int a,\
    \ int b) {\n        G[a].push_back(b);\n    }\n\n    bool dfs(int x) {\n     \
    \   used[x] = t;\n        for (int y : G[x]) {\n            int ry = y + l;\n\
    \            if (alive[ry] == 0) continue;\n            int w = match[ry];\n \
    \           if (w != -1 && (alive[w] == 0 || used[w] == t || !dfs(w))) continue;\n\
    \            match[x] = ry;\n            match[ry] = x;\n            return true;\n\
    \        }\n        return false;\n    }\n\n    int matching() {\n        int\
    \ ans = 0;\n        for (int i = 0; i < l; ++i) {\n            if (alive[i] ==\
    \ 0 || match[i] != -1) continue;\n            ++t;\n            ans += dfs(i);\n\
    \        }\n        return ans;\n    }\n\n    vector<pair<int, int>> get_pairs()\
    \ const {\n        vector<pair<int, int>> res;\n        for (int i = 0; i < l;\
    \ ++i) {\n            if (match[i] == -1) continue;\n            res.emplace_back(i,\
    \ match[i] - l);\n        }\n        return res;\n    }\n};\n\n/**\n * @brief\
    \ \u4E8C\u90E8\u30B0\u30E9\u30D5\u6700\u5927\u30DE\u30C3\u30C1\u30F3\u30B0(Bipartite\
    \ Matching)\n */\n#line 2 \"graph/bipartite_matching_lexmin.cpp\"\nclass Bipartite_Matching_LexMin\
    \ : public Bipartite_Matching {\npublic:\n    using Bipartite_Matching::Bipartite_Matching;\n\
    \n    int solve_LexMin() {\n        matching();\n        int res = 0;\n      \
    \  for (int i = 0; i < l; ++i) res += match[i] != -1;\n        int source = l\
    \ + r, sink = source + 1;\n        vector<vector<int>> reverse(sink + 1);\n  \
    \      vector<int> next(sink + 1), queue;\n        vector<pair<int, int>> added;\n\
    \        for (int i = 0; i < l; ++i) {\n            if (match[i] == -1) continue;\n\
    \            for (auto &edges : reverse) edges.clear();\n            auto edge\
    \ = [&](int u, int v) { reverse[v].push_back(u); };\n            for (int u =\
    \ i; u < l; ++u) {\n                if (match[u] == -1) edge(source, u);\n   \
    \             else edge(u, source);\n                for (int v : G[u]) {\n  \
    \                  int w = l + v;\n                    if (match[u] == w) edge(w,\
    \ u);\n                    else edge(u, w);\n                }\n            }\n\
    \            for (int v = l; v < l + r; ++v) {\n                if (match[v] ==\
    \ -1) edge(v, sink);\n                else edge(sink, v);\n            }\n   \
    \         next.assign(sink + 1, -1);\n            next[i] = i;\n            queue.clear();\n\
    \            queue.push_back(i);\n            for (int k = 0; k < (int)queue.size();\
    \ ++k) {\n                int v = queue[k];\n                for (int u : reverse[v])\
    \ {\n                    if (next[u] != -1) continue;\n                    next[u]\
    \ = v;\n                    queue.push_back(u);\n                }\n         \
    \   }\n            int chosen = source;\n            if (next[source] == -1) {\n\
    \                chosen = match[i];\n                for (int v : G[i]) {\n  \
    \                  int w = l + v;\n                    if (w < chosen && next[w]\
    \ != -1) chosen = w;\n                }\n            }\n            if (chosen\
    \ == match[i]) continue;\n            added.clear();\n            int u = i, v\
    \ = chosen;\n            do {\n                if (u < l && l <= v && v < source)\
    \ added.emplace_back(u, v);\n                if (l <= u && u < source && v < l)\
    \ match[u] = match[v] = -1;\n                u = v;\n                v = next[u];\n\
    \            } while (u != i);\n            for (auto [a, b] : added) {\n    \
    \            match[a] = b;\n                match[b] = a;\n            }\n   \
    \     }\n        return res;\n    }\n};\n\n/**\n * @brief \u8F9E\u66F8\u9806\u6700\
    \u5C0F\u4E8C\u90E8\u30DE\u30C3\u30C1\u30F3\u30B0(Lexicographically Minimum Bipartite\
    \ Matching)\n */\n#line 8 \"test/yosupo_aplusb_bipartite_matching_lexmin.test.cpp\"\
    \n\nvoid check(int l, int r, const vector<pair<int, int>> &edges) {\n    Bipartite_Matching_LexMin\
    \ solver(l, r);\n    vector<vector<int>> g(l);\n    for (auto [u, v] : edges)\
    \ {\n        solver.add_edge(u, v);\n        g[u].push_back(v);\n    }\n    vector<int>\
    \ current(l, -1), best;\n    int size = -1;\n    auto enumerate = [&](auto &&self,\
    \ int u, int used, int count) -> void {\n        if (u == l) {\n            if\
    \ (count > size || (count == size && current < best)) {\n                size\
    \ = count;\n                best = current;\n            }\n            return;\n\
    \        }\n        current[u] = -1;\n        self(self, u + 1, used, count);\n\
    \        for (int v : g[u]) {\n            if (used >> v & 1) continue;\n    \
    \        current[u] = v;\n            self(self, u + 1, used | (1 << v), count\
    \ + 1);\n        }\n    };\n    enumerate(enumerate, 0, 0, 0);\n    assert(solver.solve_LexMin()\
    \ == size);\n    for (int u = 0; u < l; ++u) {\n        assert(solver.match[u]\
    \ == (best[u] == -1 ? -1 : l + best[u]));\n        if (best[u] != -1) assert(solver.match[l\
    \ + best[u]] == u);\n    }\n    auto match = solver.match;\n    assert(solver.solve_LexMin()\
    \ == size && solver.match == match);\n}\n\nint main() {\n    check(3, 2, {{0,\
    \ 0}, {0, 1}, {1, 0}, {2, 1}});\n    for (int mask = 0; mask < (1 << 16); ++mask)\
    \ {\n        vector<pair<int, int>> edges;\n        for (int u = 0; u < 4; ++u)\n\
    \            for (int v = 0; v < 4; ++v)\n                if (mask >> (4 * u +\
    \ v) & 1) edges.emplace_back(u, v);\n        check(4, 4, edges);\n    }\n    mt19937\
    \ rng(20261010);\n    for (int tc = 0; tc < 2000; ++tc) {\n        int l = rng()\
    \ % 7, r = rng() % 7;\n        vector<pair<int, int>> edges;\n        for (int\
    \ u = 0; u < l; ++u)\n            for (int v = 0; v < r; ++v)\n              \
    \  if (rng() % 3 == 0) edges.emplace_back(u, v);\n        shuffle(edges.begin(),\
    \ edges.end(), rng);\n        check(l, r, edges);\n    }\n    Scanner in;\n  \
    \  Printer out;\n    int a, b;\n    in.read(a, b);\n    out.println(a + b);\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\n#include \"../util/fastio.cpp\"\n#include \"../graph/bipartite_matching_lexmin.cpp\"\
    \n\nvoid check(int l, int r, const vector<pair<int, int>> &edges) {\n    Bipartite_Matching_LexMin\
    \ solver(l, r);\n    vector<vector<int>> g(l);\n    for (auto [u, v] : edges)\
    \ {\n        solver.add_edge(u, v);\n        g[u].push_back(v);\n    }\n    vector<int>\
    \ current(l, -1), best;\n    int size = -1;\n    auto enumerate = [&](auto &&self,\
    \ int u, int used, int count) -> void {\n        if (u == l) {\n            if\
    \ (count > size || (count == size && current < best)) {\n                size\
    \ = count;\n                best = current;\n            }\n            return;\n\
    \        }\n        current[u] = -1;\n        self(self, u + 1, used, count);\n\
    \        for (int v : g[u]) {\n            if (used >> v & 1) continue;\n    \
    \        current[u] = v;\n            self(self, u + 1, used | (1 << v), count\
    \ + 1);\n        }\n    };\n    enumerate(enumerate, 0, 0, 0);\n    assert(solver.solve_LexMin()\
    \ == size);\n    for (int u = 0; u < l; ++u) {\n        assert(solver.match[u]\
    \ == (best[u] == -1 ? -1 : l + best[u]));\n        if (best[u] != -1) assert(solver.match[l\
    \ + best[u]] == u);\n    }\n    auto match = solver.match;\n    assert(solver.solve_LexMin()\
    \ == size && solver.match == match);\n}\n\nint main() {\n    check(3, 2, {{0,\
    \ 0}, {0, 1}, {1, 0}, {2, 1}});\n    for (int mask = 0; mask < (1 << 16); ++mask)\
    \ {\n        vector<pair<int, int>> edges;\n        for (int u = 0; u < 4; ++u)\n\
    \            for (int v = 0; v < 4; ++v)\n                if (mask >> (4 * u +\
    \ v) & 1) edges.emplace_back(u, v);\n        check(4, 4, edges);\n    }\n    mt19937\
    \ rng(20261010);\n    for (int tc = 0; tc < 2000; ++tc) {\n        int l = rng()\
    \ % 7, r = rng() % 7;\n        vector<pair<int, int>> edges;\n        for (int\
    \ u = 0; u < l; ++u)\n            for (int v = 0; v < r; ++v)\n              \
    \  if (rng() % 3 == 0) edges.emplace_back(u, v);\n        shuffle(edges.begin(),\
    \ edges.end(), rng);\n        check(l, r, edges);\n    }\n    Scanner in;\n  \
    \  Printer out;\n    int a, b;\n    in.read(a, b);\n    out.println(a + b);\n\
    }\n"
  dependsOn:
  - util/fastio.cpp
  - graph/bipartite_matching_lexmin.cpp
  - graph/bipartite_matching.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_bipartite_matching_lexmin.test.cpp
  requiredBy: []
  timestamp: '2026-10-10 19:44:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_bipartite_matching_lexmin.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_bipartite_matching_lexmin.test.cpp
- /verify/test/yosupo_aplusb_bipartite_matching_lexmin.test.cpp.html
title: test/yosupo_aplusb_bipartite_matching_lexmin.test.cpp
---
