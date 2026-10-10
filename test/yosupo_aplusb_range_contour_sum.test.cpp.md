---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/binaryindexedtree.cpp
    title: Binary Indexed Tree(BIT)
  - icon: ':heavy_check_mark:'
    path: tree/centroid_decomposition_query_helper.cpp
    title: "\u91CD\u5FC3\u5206\u89E3\u30AF\u30A8\u30EA\u88DC\u52A9(Centroid Query\
      \ Helper)"
  - icon: ':heavy_check_mark:'
    path: tree/range_contour_sum.cpp
    title: "\u6728\u306E\u9802\u70B9\u52A0\u7B97\u30FB\u8DDD\u96E2\u533A\u9593\u548C"
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_range_contour_sum.test.cpp\"\n#define\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"tree/centroid_decomposition_query_helper.cpp\"\
    \nusing namespace std;\n\nstruct CentroidDecompositionQueryHelper {\n    int n,\
    \ root;\n    vector<vector<int>> G, tree, path, dist;\n    vector<int> sz, parent,\
    \ depth;\n    vector<char> used;\n\n    explicit CentroidDecompositionQueryHelper(int\
    \ n)\n        : n(n), root(-1), G(n), tree(n), path(n), dist(n), sz(n), parent(n,\
    \ -1), depth(n), used(n, 0) {}\n\n    void add_edge(int u, int v) {\n        G[u].push_back(v);\n\
    \        G[v].push_back(u);\n    }\n\n    int build(int start = 0) {\n       \
    \ tree.assign(n, {});\n        path.assign(n, {});\n        dist.assign(n, {});\n\
    \        fill(parent.begin(), parent.end(), -1);\n        fill(depth.begin(),\
    \ depth.end(), 0);\n        fill(used.begin(), used.end(), 0);\n        dfs_parent.resize(n);\n\
    \        order.reserve(n);\n        if (n == 0) return root = -1;\n        return\
    \ root = decompose(start, -1, 0);\n    }\n\nprivate:\n    vector<int> dfs_parent,\
    \ order;\n\n    int dfs_size(int v, int p) {\n        order.clear();\n       \
    \ order.push_back(v);\n        dfs_parent[v] = p;\n        for (int i = 0; i <\
    \ (int)order.size(); ++i) {\n            int x = order[i];\n            sz[x]\
    \ = 1;\n            for (int u : G[x]) {\n                if (u == dfs_parent[x]\
    \ || used[u]) continue;\n                dfs_parent[u] = x;\n                order.push_back(u);\n\
    \            }\n        }\n        for (int i = (int)order.size() - 1; i > 0;\
    \ --i)\n            sz[dfs_parent[order[i]]] += sz[order[i]];\n        return\
    \ sz[v];\n    }\n\n    int find_centroid(int v, int p, int half) {\n        while\
    \ (true) {\n            int next = -1;\n            for (int u : G[v]) {\n   \
    \             if (u != p && !used[u] && sz[u] > half) {\n                    next\
    \ = u;\n                    break;\n                }\n            }\n       \
    \     if (next == -1) return v;\n            p = v;\n            v = next;\n \
    \       }\n    }\n\n    void collect(int v, int p, int d, vector<pair<int, int>>\
    \ &buf) {\n        buf.emplace_back(v, d);\n        dfs_parent[v] = p;\n     \
    \   for (int i = 0; i < (int)buf.size(); ++i) {\n            auto [x, distance]\
    \ = buf[i];\n            for (int u : G[x]) {\n                if (u == dfs_parent[x]\
    \ || used[u]) continue;\n                dfs_parent[u] = x;\n                buf.emplace_back(u,\
    \ distance + 1);\n            }\n        }\n    }\n\n    int decompose(int start,\
    \ int p, int dep) {\n        int centroid = find_centroid(start, -1, dfs_size(start,\
    \ -1) / 2);\n        used[centroid] = 1;\n        parent[centroid] = p;\n    \
    \    depth[centroid] = dep;\n        path[centroid].push_back(centroid);\n   \
    \     dist[centroid].push_back(0);\n        for (auto &&u : G[centroid]) {\n \
    \           if (used[u]) continue;\n            vector<pair<int, int>> buf;\n\
    \            collect(u, centroid, 1, buf);\n            int child = decompose(u,\
    \ centroid, dep + 1);\n            tree[centroid].push_back(child);\n        \
    \    for (auto &&[v, d] : buf) {\n                path[v].push_back(centroid);\n\
    \                dist[v].push_back(d);\n            }\n        }\n        return\
    \ centroid;\n    }\n};\n\n/**\n * @brief \u91CD\u5FC3\u5206\u89E3\u30AF\u30A8\u30EA\
    \u88DC\u52A9(Centroid Query Helper)\n */\n#line 1 \"datastructure/binaryindexedtree.cpp\"\
    \n\n\n\ntemplate<class T>\nclass BIT {\n    vector<T> bit;\n    int m, n;\npublic:\n\
    \    BIT(int n): bit(n), m(1), n(n) {\n        while (m < n) m <<= 1;\n    }\n\
    \n    explicit BIT(const vector<T> &values): bit(values), m(1), n(values.size())\
    \ {\n        while (m < n) m <<= 1;\n        for (int i = 1; i <= n; ++i) {\n\
    \            int parent = i + (i & -i);\n            if (parent <= n) bit[parent\
    \ - 1] += bit[i - 1];\n        }\n    }\n\n    T sum(int k){\n        T ret =\
    \ 0;\n        for (; k > 0; k -= (k & -k)) ret += bit[k - 1];\n        return\
    \ ret;\n    }\n\n    void add(int k, T x){\n        for (k++; k <= n; k += (k\
    \ & -k)) bit[k - 1] += x;\n    }\n\n    int lower_bound(T x) {\n        if (x\
    \ <= 0) return 0;\n        int i = 0;\n        for (int j = m; j; j >>= 1) {\n\
    \            if (i + j <= n && bit[i + j - 1] < x) x -= bit[i + j - 1], i += j;\n\
    \        }\n        return min(i + 1, n);\n    }\n};\n\n/**\n * @brief Binary\
    \ Indexed Tree(BIT)\n */\n\n\n#line 3 \"tree/range_contour_sum.cpp\"\n\nclass\
    \ RangeContourSum {\n    CentroidDecompositionQueryHelper cd;\n    vector<BIT<long\
    \ long>> all, branch;\n    vector<int> all_size, branch_size;\n\n    long long\
    \ sum(BIT<long long> &bit, int size, long long l, long long r) {\n        int\
    \ left = (int)max(0LL, min((long long)size, l));\n        int right = (int)max(0LL,\
    \ min((long long)size, r));\n        return bit.sum(right) - bit.sum(left);\n\
    \    }\n\npublic:\n    RangeContourSum(const vector<vector<int>> &g, const vector<long\
    \ long> &values)\n        : cd((int)g.size()), all_size(g.size()), branch_size(g.size())\
    \ {\n        cd.G = g;\n        cd.build();\n        int n = g.size();\n     \
    \   vector<vector<long long>> a(n), b(n);\n        for (int v = 0; v < n; ++v)\
    \ {\n            for (int i = 0; i < (int)cd.path[v].size(); ++i) {\n        \
    \        int c = cd.path[v][i], d = cd.dist[v][i];\n                if ((int)a[c].size()\
    \ <= d) a[c].resize(d + 1);\n                a[c][d] += values[v];\n         \
    \       if (i == 0) continue;\n                int child = cd.path[v][i - 1];\n\
    \                if ((int)b[child].size() <= d) b[child].resize(d + 1);\n    \
    \            b[child][d] += values[v];\n            }\n        }\n        all.reserve(n);\n\
    \        branch.reserve(n);\n        for (int c = 0; c < n; ++c) {\n         \
    \   all_size[c] = a[c].size();\n            branch_size[c] = b[c].size();\n  \
    \          all.emplace_back(a[c]);\n            branch.emplace_back(b[c]);\n \
    \       }\n    }\n\n    void add(int v, long long x) {\n        for (int i = 0;\
    \ i < (int)cd.path[v].size(); ++i) {\n            all[cd.path[v][i]].add(cd.dist[v][i],\
    \ x);\n            if (i > 0) branch[cd.path[v][i - 1]].add(cd.dist[v][i], x);\n\
    \        }\n    }\n\n    long long query(int v, int l, int r) {\n        if (l\
    \ >= r) return 0;\n        long long answer = 0;\n        for (int i = 0; i <\
    \ (int)cd.path[v].size(); ++i) {\n            int c = cd.path[v][i], d = cd.dist[v][i];\n\
    \            answer += sum(all[c], all_size[c], (long long)l - d, (long long)r\
    \ - d);\n            if (i == 0) continue;\n            int child = cd.path[v][i\
    \ - 1];\n            answer -= sum(branch[child], branch_size[child], (long long)l\
    \ - d, (long long)r - d);\n        }\n        return answer;\n    }\n};\n\n/**\n\
    \ * @brief \u6728\u306E\u9802\u70B9\u52A0\u7B97\u30FB\u8DDD\u96E2\u533A\u9593\u548C\
    \n */\n#line 8 \"test/yosupo_aplusb_range_contour_sum.test.cpp\"\n\nvoid check(int\
    \ n, int mode, mt19937 &rng) {\n    vector<vector<int>> g(n), distance(n, vector<int>(n,\
    \ -1));\n    for (int i = 1; i < n; ++i) {\n        int p = mode == 0 ? i - 1\
    \ : mode == 1 ? 0 : rng() % i;\n        g[p].push_back(i);\n        g[i].push_back(p);\n\
    \    }\n    for (int v = 0; v < n; ++v) {\n        vector<int> queue{v};\n   \
    \     distance[v][v] = 0;\n        for (int i = 0; i < (int)queue.size(); ++i)\
    \ {\n            int x = queue[i];\n            for (int u : g[x]) {\n       \
    \         if (distance[v][u] != -1) continue;\n                distance[v][u]\
    \ = distance[v][x] + 1;\n                queue.push_back(u);\n            }\n\
    \        }\n    }\n    CentroidDecompositionQueryHelper helper(n);\n    helper.G\
    \ = g;\n    helper.build();\n    auto path = helper.path, dist = helper.dist;\n\
    \    helper.build();\n    assert(path == helper.path && dist == helper.dist);\n\
    \    for (int v = 0; v < n; ++v) {\n        assert(path[v].front() == v && path[v].back()\
    \ == helper.root);\n        for (int i = 0; i < (int)path[v].size(); ++i) {\n\
    \            assert(dist[v][i] == distance[v][path[v][i]]);\n            if (i\
    \ > 0) assert(helper.parent[path[v][i - 1]] == path[v][i]);\n        }\n    }\n\
    \    vector<long long> values(n);\n    for (auto &x : values) x = (int)(rng()\
    \ % 21) - 10;\n    RangeContourSum solver(g, values);\n    for (int step = 0;\
    \ step < 200; ++step) {\n        int v = rng() % n;\n        if (step % 3 == 0)\
    \ {\n            long long x = (int)(rng() % 21) - 10;\n            solver.add(v,\
    \ x);\n            values[v] += x;\n        }\n        int l = (int)(rng() % (n\
    \ + 10)) - 5;\n        int r = (int)(rng() % (n + 10)) - 5;\n        if (step\
    \ % 20 == 0) l = INT_MIN, r = INT_MAX;\n        long long expected = 0;\n    \
    \    for (int u = 0; u < n; ++u)\n            if (l <= distance[v][u] && distance[v][u]\
    \ < r) expected += values[u];\n        assert(solver.query(v, l, r) == expected);\n\
    \        assert(solver.query(v, 0, 1) == values[v]);\n    }\n}\n\nint main() {\n\
    \    RangeContourSum empty({}, {});\n    mt19937 rng(20261010);\n    for (int\
    \ n : {1, 2, 3, 63, 64, 65, 100})\n        for (int mode = 0; mode < 3; ++mode)\
    \ check(n, mode, rng);\n    for (int tc = 0; tc < 500; ++tc) check(1 + rng() %\
    \ 50, 2, rng);\n    Scanner in;\n    Printer out;\n    int a, b;\n    in.read(a,\
    \ b);\n    out.println(a + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\n#include \"../util/fastio.cpp\"\n#include \"../tree/range_contour_sum.cpp\"\
    \n\nvoid check(int n, int mode, mt19937 &rng) {\n    vector<vector<int>> g(n),\
    \ distance(n, vector<int>(n, -1));\n    for (int i = 1; i < n; ++i) {\n      \
    \  int p = mode == 0 ? i - 1 : mode == 1 ? 0 : rng() % i;\n        g[p].push_back(i);\n\
    \        g[i].push_back(p);\n    }\n    for (int v = 0; v < n; ++v) {\n      \
    \  vector<int> queue{v};\n        distance[v][v] = 0;\n        for (int i = 0;\
    \ i < (int)queue.size(); ++i) {\n            int x = queue[i];\n            for\
    \ (int u : g[x]) {\n                if (distance[v][u] != -1) continue;\n    \
    \            distance[v][u] = distance[v][x] + 1;\n                queue.push_back(u);\n\
    \            }\n        }\n    }\n    CentroidDecompositionQueryHelper helper(n);\n\
    \    helper.G = g;\n    helper.build();\n    auto path = helper.path, dist = helper.dist;\n\
    \    helper.build();\n    assert(path == helper.path && dist == helper.dist);\n\
    \    for (int v = 0; v < n; ++v) {\n        assert(path[v].front() == v && path[v].back()\
    \ == helper.root);\n        for (int i = 0; i < (int)path[v].size(); ++i) {\n\
    \            assert(dist[v][i] == distance[v][path[v][i]]);\n            if (i\
    \ > 0) assert(helper.parent[path[v][i - 1]] == path[v][i]);\n        }\n    }\n\
    \    vector<long long> values(n);\n    for (auto &x : values) x = (int)(rng()\
    \ % 21) - 10;\n    RangeContourSum solver(g, values);\n    for (int step = 0;\
    \ step < 200; ++step) {\n        int v = rng() % n;\n        if (step % 3 == 0)\
    \ {\n            long long x = (int)(rng() % 21) - 10;\n            solver.add(v,\
    \ x);\n            values[v] += x;\n        }\n        int l = (int)(rng() % (n\
    \ + 10)) - 5;\n        int r = (int)(rng() % (n + 10)) - 5;\n        if (step\
    \ % 20 == 0) l = INT_MIN, r = INT_MAX;\n        long long expected = 0;\n    \
    \    for (int u = 0; u < n; ++u)\n            if (l <= distance[v][u] && distance[v][u]\
    \ < r) expected += values[u];\n        assert(solver.query(v, l, r) == expected);\n\
    \        assert(solver.query(v, 0, 1) == values[v]);\n    }\n}\n\nint main() {\n\
    \    RangeContourSum empty({}, {});\n    mt19937 rng(20261010);\n    for (int\
    \ n : {1, 2, 3, 63, 64, 65, 100})\n        for (int mode = 0; mode < 3; ++mode)\
    \ check(n, mode, rng);\n    for (int tc = 0; tc < 500; ++tc) check(1 + rng() %\
    \ 50, 2, rng);\n    Scanner in;\n    Printer out;\n    int a, b;\n    in.read(a,\
    \ b);\n    out.println(a + b);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - tree/range_contour_sum.cpp
  - tree/centroid_decomposition_query_helper.cpp
  - datastructure/binaryindexedtree.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_range_contour_sum.test.cpp
  requiredBy: []
  timestamp: '2026-10-10 19:50:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_range_contour_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_range_contour_sum.test.cpp
- /verify/test/yosupo_aplusb_range_contour_sum.test.cpp.html
title: test/yosupo_aplusb_range_contour_sum.test.cpp
---
