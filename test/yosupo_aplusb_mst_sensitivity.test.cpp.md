---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/kruskal.cpp
    title: "\u6700\u5C0F\u5168\u57DF\u6728(Kruskal\u6CD5)"
  - icon: ':heavy_check_mark:'
    path: graph/kruskal.cpp
    title: "\u6700\u5C0F\u5168\u57DF\u6728(Kruskal\u6CD5)"
  - icon: ':heavy_check_mark:'
    path: graph/mst_sensitivity.cpp
    title: "\u6700\u5C0F\u5168\u57DF\u6728\u306E\u8FBA\u5225\u5236\u7D04\u30B3\u30B9\
      \u30C8"
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_mst_sensitivity.test.cpp\"\n#define PROBLEM\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"graph/kruskal.cpp\"\
    \n\n\n\ntemplate <class T>\nstruct edge {\n    int from, to, idx;\n    T cost;\n\
    \n    edge(int from, int to, T cost, int idx = -1) : from(from), to(to), idx(idx),\
    \ cost(cost) {}\n};\n\nclass KruskalUnionFind {\n    vector<int> p;\n\npublic:\n\
    \    explicit KruskalUnionFind(int n) : p(n, -1) {}\n\n    int root(int x) {\n\
    \        if (p[x] < 0) return x;\n        return p[x] = root(p[x]);\n    }\n\n\
    \    bool unite(int a, int b) {\n        a = root(a);\n        b = root(b);\n\
    \        if (a == b) return false;\n        if (p[a] > p[b]) swap(a, b);\n   \
    \     p[a] += p[b];\n        p[b] = a;\n        return true;\n    }\n};\n\ntemplate\
    \ <class T>\nstruct KruskalResult {\n    bool exists;\n    T cost;\n    vector<int>\
    \ edge_id;\n};\n\ntemplate <class T>\nKruskalResult<T> kruskal(vector<edge<T>>\
    \ edges, int n) {\n    for (int i = 0; i < (int)edges.size(); ++i) {\n       \
    \ if (edges[i].idx == -1) edges[i].idx = i;\n    }\n    sort(edges.begin(), edges.end(),\
    \ [](const edge<T> &a, const edge<T> &b) {\n        if (a.cost != b.cost) return\
    \ a.cost < b.cost;\n        return a.idx < b.idx;\n    });\n\n    KruskalUnionFind\
    \ uf(n);\n    T cost = T(0);\n    vector<int> edge_id;\n    edge_id.reserve(max(0,\
    \ n - 1));\n    for (auto &&e : edges) {\n        if (!uf.unite(e.from, e.to))\
    \ continue;\n        cost += e.cost;\n        edge_id.push_back(e.idx);\n    }\n\
    \    if ((int)edge_id.size() != max(0, n - 1)) return {false, T(0), {}};\n   \
    \ return {true, cost, std::move(edge_id)};\n}\n\n\n\n/**\n * @brief \u6700\u5C0F\
    \u5168\u57DF\u6728(Kruskal\u6CD5)\n */\n#line 1 \"graph/mst_sensitivity.cpp\"\n\
    \n\n\n#line 5 \"graph/mst_sensitivity.cpp\"\n\nstruct MSTSensitivityResult {\n\
    \    bool exists;\n    long long cost;\n    vector<optional<long long>> forced,\
    \ forbidden;\n};\n\nMSTSensitivityResult mst_sensitivity(int n, const vector<edge<long\
    \ long>> &edges) {\n    assert(n >= 1);\n    int m = (int)edges.size();\n    auto\
    \ indexed = edges;\n    for (int i = 0; i < m; ++i) indexed[i].idx = i;\n    auto\
    \ mst = kruskal(std::move(indexed), n);\n    MSTSensitivityResult result{mst.exists,\
    \ mst.cost,\n                                vector<optional<long long>>(m), vector<optional<long\
    \ long>>(m)};\n    if (!mst.exists) return result;\n    vector<char> in_tree(m);\n\
    \    vector<vector<pair<int, int>>> tree(n);\n    for (int id : mst.edge_id) {\n\
    \        in_tree[id] = 1;\n        result.forced[id] = mst.cost;\n        const\
    \ auto &e = edges[id];\n        tree[e.from].emplace_back(e.to, id);\n       \
    \ tree[e.to].emplace_back(e.from, id);\n    }\n    int height = 1;\n    while\
    \ ((1LL << height) <= n) ++height;\n    vector<vector<int>> parent(height, vector<int>(n));\n\
    \    vector<vector<long long>> maximum(height, vector<long long>(n, LLONG_MIN));\n\
    \    vector<int> depth(n), parent_edge(n, -1), order{0};\n    for (int i = 0;\
    \ i < (int)order.size(); ++i) {\n        int v = order[i];\n        for (auto\
    \ [u, id] : tree[v]) {\n            if (u == parent[0][v]) continue;\n       \
    \     parent[0][u] = v;\n            parent_edge[u] = id;\n            maximum[0][u]\
    \ = edges[id].cost;\n            depth[u] = depth[v] + 1;\n            order.push_back(u);\n\
    \        }\n    }\n    for (int k = 1; k < height; ++k) {\n        for (int v\
    \ = 0; v < n; ++v) {\n            int u = parent[k - 1][v];\n            parent[k][v]\
    \ = parent[k - 1][u];\n            maximum[k][v] = max(maximum[k - 1][v], maximum[k\
    \ - 1][u]);\n        }\n    }\n    auto path = [&](int u, int v) {\n        long\
    \ long weight = LLONG_MIN;\n        if (depth[u] < depth[v]) swap(u, v);\n   \
    \     int difference = depth[u] - depth[v];\n        for (int k = 0; k < height;\
    \ ++k) {\n            if ((difference >> k) & 1) {\n                weight = max(weight,\
    \ maximum[k][u]);\n                u = parent[k][u];\n            }\n        }\n\
    \        if (u == v) return make_pair(u, weight);\n        for (int k = height\
    \ - 1; k >= 0; --k) {\n            if (parent[k][u] == parent[k][v]) continue;\n\
    \            weight = max({weight, maximum[k][u], maximum[k][v]});\n         \
    \   u = parent[k][u];\n            v = parent[k][v];\n        }\n        return\
    \ make_pair(parent[0][u], max({weight, maximum[0][u], maximum[0][v]}));\n    };\n\
    \    vector<int> non_tree;\n    for (int i = 0; i < m; ++i) {\n        if (in_tree[i])\
    \ continue;\n        result.forbidden[i] = mst.cost;\n        if (edges[i].from\
    \ != edges[i].to) non_tree.push_back(i);\n    }\n    sort(non_tree.begin(), non_tree.end(),\
    \ [&](int a, int b) { return edges[a].cost < edges[b].cost; });\n    KruskalUnionFind\
    \ skip(n);\n    vector<int> top(n);\n    iota(top.begin(), top.end(), 0);\n  \
    \  auto replace = [&](int v, int ancestor, long long weight) {\n        int representative\
    \ = skip.root(v), x = top[representative];\n        while (depth[x] > depth[ancestor])\
    \ {\n            int id = parent_edge[x];\n            result.forbidden[id] =\
    \ mst.cost + weight - edges[id].cost;\n            int highest = top[skip.root(parent[0][x])];\n\
    \            skip.unite(representative, parent[0][x]);\n            representative\
    \ = skip.root(representative);\n            top[representative] = highest;\n \
    \           x = highest;\n        }\n    };\n    for (int id : non_tree) {\n \
    \       const auto &e = edges[id];\n        auto [ancestor, weight] = path(e.from,\
    \ e.to);\n        result.forced[id] = mst.cost + e.cost - weight;\n        replace(e.from,\
    \ ancestor, e.cost);\n        replace(e.to, ancestor, e.cost);\n    }\n    return\
    \ result;\n}\n\n\n\n/**\n * @brief \u6700\u5C0F\u5168\u57DF\u6728\u306E\u8FBA\u5225\
    \u5236\u7D04\u30B3\u30B9\u30C8\n */\n#line 8 \"test/yosupo_aplusb_mst_sensitivity.test.cpp\"\
    \n\nvoid check(int n, vector<edge<long long>> edges) {\n    int m = (int)edges.size();\n\
    \    for (int i = 0; i < m; ++i) edges[i].idx = i % 3 == 0 ? -1 : 1000 - i % 3;\n\
    \    auto original = edges;\n    auto result = mst_sensitivity(n, edges);\n  \
    \  optional<long long> best;\n    vector<optional<long long>> forced(m), forbidden(m);\n\
    \    auto minimize = [](optional<long long> &a, long long b) {\n        if (!a\
    \ || b < *a) a = b;\n    };\n    for (int mask = 0; mask < (1 << m); ++mask) {\n\
    \        if (__builtin_popcount((unsigned)mask) != n - 1) continue;\n        vector<int>\
    \ component(n);\n        iota(component.begin(), component.end(), 0);\n      \
    \  bool valid = true;\n        long long cost = 0;\n        for (int i = 0; i\
    \ < m; ++i) {\n            if (!((mask >> i) & 1)) continue;\n            const\
    \ auto &e = edges[i];\n            int a = component[e.from], b = component[e.to];\n\
    \            if (a == b) { valid = false; break; }\n            for (int &c :\
    \ component) if (c == b) c = a;\n            cost += e.cost;\n        }\n    \
    \    if (!valid) continue;\n        minimize(best, cost);\n        for (int i\
    \ = 0; i < m; ++i) minimize((mask >> i) & 1 ? forced[i] : forbidden[i], cost);\n\
    \    }\n    assert(result.exists == best.has_value());\n    assert(result.cost\
    \ == best.value_or(0));\n    assert(result.forced == forced && result.forbidden\
    \ == forbidden);\n    for (int i = 0; i < m; ++i) {\n        const auto &a = edges[i],\
    \ &b = original[i];\n        assert(tie(a.from, a.to, a.cost, a.idx) == tie(b.from,\
    \ b.to, b.cost, b.idx));\n    }\n}\n\nint main() {\n    check(1, {});\n    long\
    \ long large = 1000000000000LL;\n    check(1, {{0, 0, -large}, {0, 0, large}});\n\
    \    check(2, {{0, 1, -large}, {0, 1, -large + 1}});\n    check(2, {{0, 1, large\
    \ - 1}, {0, 1, large}});\n    check(3, {{0, 1, -large + 10}, {1, 2, large - 5},\
    \ {0, 2, 0}});\n    for (int n = 1; n <= 4; ++n) {\n        vector<pair<int, int>>\
    \ pairs;\n        for (int u = 0; u < n; ++u) for (int v = u + 1; v < n; ++v)\
    \ pairs.emplace_back(u, v);\n        int combinations = 1 << (2 * pairs.size());\n\
    \        for (int state = 0; state < combinations; ++state) {\n            int\
    \ code = state;\n            vector<edge<long long>> edges;\n            for (auto\
    \ [u, v] : pairs) {\n                int choice = code % 4;\n                code\
    \ /= 4;\n                if (choice) edges.emplace_back(u, v, choice - 2);\n \
    \           }\n            check(n, edges);\n        }\n    }\n    mt19937 rng(139);\n\
    \    for (int tc = 0; tc < 5000; ++tc) {\n        int n = 1 + rng() % 8, m = rng()\
    \ % 13;\n        vector<edge<long long>> edges;\n        for (int i = 0; i < m;\
    \ ++i) edges.emplace_back(rng() % n, rng() % n, (int)(rng() % 21) - 10);\n   \
    \     check(n, edges);\n    }\n    int n = 100000;\n    for (bool star : {false,\
    \ true}) {\n        vector<edge<long long>> edges;\n        for (int v = 1; v\
    \ < n; ++v) edges.emplace_back(star ? 0 : v - 1, v, 1);\n        auto bridges\
    \ = mst_sensitivity(n, edges);\n        assert(bridges.exists && bridges.cost\
    \ == n - 1);\n        for (int i = 0; i < n - 1; ++i) {\n            assert(bridges.forced[i]\
    \ == n - 1 && !bridges.forbidden[i]);\n        }\n        if (star) {\n      \
    \      for (int v = 1; v < n; ++v) edges.emplace_back(v, v == n - 1 ? 1 : v +\
    \ 1, 2);\n        } else {\n            for (int v = 2; v < n; ++v) edges.emplace_back(0,\
    \ v, 2);\n        }\n        auto result = mst_sensitivity(n, edges);\n      \
    \  assert(result.exists && result.cost == n - 1);\n        for (int i = 0; i <\
    \ (int)edges.size(); ++i) {\n            assert(result.forced[i] == (i < n - 1\
    \ ? n - 1 : n));\n            assert(result.forbidden[i] == (i < n - 1 ? n : n\
    \ - 1));\n        }\n    }\n    Scanner sc;\n    Printer pr;\n    int a, b;\n\
    \    sc.read(a, b);\n    pr.println(a + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n#include \"../util/fastio.cpp\"\n#include \"../graph/kruskal.cpp\"\
    \n#include \"../graph/mst_sensitivity.cpp\"\n\nvoid check(int n, vector<edge<long\
    \ long>> edges) {\n    int m = (int)edges.size();\n    for (int i = 0; i < m;\
    \ ++i) edges[i].idx = i % 3 == 0 ? -1 : 1000 - i % 3;\n    auto original = edges;\n\
    \    auto result = mst_sensitivity(n, edges);\n    optional<long long> best;\n\
    \    vector<optional<long long>> forced(m), forbidden(m);\n    auto minimize =\
    \ [](optional<long long> &a, long long b) {\n        if (!a || b < *a) a = b;\n\
    \    };\n    for (int mask = 0; mask < (1 << m); ++mask) {\n        if (__builtin_popcount((unsigned)mask)\
    \ != n - 1) continue;\n        vector<int> component(n);\n        iota(component.begin(),\
    \ component.end(), 0);\n        bool valid = true;\n        long long cost = 0;\n\
    \        for (int i = 0; i < m; ++i) {\n            if (!((mask >> i) & 1)) continue;\n\
    \            const auto &e = edges[i];\n            int a = component[e.from],\
    \ b = component[e.to];\n            if (a == b) { valid = false; break; }\n  \
    \          for (int &c : component) if (c == b) c = a;\n            cost += e.cost;\n\
    \        }\n        if (!valid) continue;\n        minimize(best, cost);\n   \
    \     for (int i = 0; i < m; ++i) minimize((mask >> i) & 1 ? forced[i] : forbidden[i],\
    \ cost);\n    }\n    assert(result.exists == best.has_value());\n    assert(result.cost\
    \ == best.value_or(0));\n    assert(result.forced == forced && result.forbidden\
    \ == forbidden);\n    for (int i = 0; i < m; ++i) {\n        const auto &a = edges[i],\
    \ &b = original[i];\n        assert(tie(a.from, a.to, a.cost, a.idx) == tie(b.from,\
    \ b.to, b.cost, b.idx));\n    }\n}\n\nint main() {\n    check(1, {});\n    long\
    \ long large = 1000000000000LL;\n    check(1, {{0, 0, -large}, {0, 0, large}});\n\
    \    check(2, {{0, 1, -large}, {0, 1, -large + 1}});\n    check(2, {{0, 1, large\
    \ - 1}, {0, 1, large}});\n    check(3, {{0, 1, -large + 10}, {1, 2, large - 5},\
    \ {0, 2, 0}});\n    for (int n = 1; n <= 4; ++n) {\n        vector<pair<int, int>>\
    \ pairs;\n        for (int u = 0; u < n; ++u) for (int v = u + 1; v < n; ++v)\
    \ pairs.emplace_back(u, v);\n        int combinations = 1 << (2 * pairs.size());\n\
    \        for (int state = 0; state < combinations; ++state) {\n            int\
    \ code = state;\n            vector<edge<long long>> edges;\n            for (auto\
    \ [u, v] : pairs) {\n                int choice = code % 4;\n                code\
    \ /= 4;\n                if (choice) edges.emplace_back(u, v, choice - 2);\n \
    \           }\n            check(n, edges);\n        }\n    }\n    mt19937 rng(139);\n\
    \    for (int tc = 0; tc < 5000; ++tc) {\n        int n = 1 + rng() % 8, m = rng()\
    \ % 13;\n        vector<edge<long long>> edges;\n        for (int i = 0; i < m;\
    \ ++i) edges.emplace_back(rng() % n, rng() % n, (int)(rng() % 21) - 10);\n   \
    \     check(n, edges);\n    }\n    int n = 100000;\n    for (bool star : {false,\
    \ true}) {\n        vector<edge<long long>> edges;\n        for (int v = 1; v\
    \ < n; ++v) edges.emplace_back(star ? 0 : v - 1, v, 1);\n        auto bridges\
    \ = mst_sensitivity(n, edges);\n        assert(bridges.exists && bridges.cost\
    \ == n - 1);\n        for (int i = 0; i < n - 1; ++i) {\n            assert(bridges.forced[i]\
    \ == n - 1 && !bridges.forbidden[i]);\n        }\n        if (star) {\n      \
    \      for (int v = 1; v < n; ++v) edges.emplace_back(v, v == n - 1 ? 1 : v +\
    \ 1, 2);\n        } else {\n            for (int v = 2; v < n; ++v) edges.emplace_back(0,\
    \ v, 2);\n        }\n        auto result = mst_sensitivity(n, edges);\n      \
    \  assert(result.exists && result.cost == n - 1);\n        for (int i = 0; i <\
    \ (int)edges.size(); ++i) {\n            assert(result.forced[i] == (i < n - 1\
    \ ? n - 1 : n));\n            assert(result.forbidden[i] == (i < n - 1 ? n : n\
    \ - 1));\n        }\n    }\n    Scanner sc;\n    Printer pr;\n    int a, b;\n\
    \    sc.read(a, b);\n    pr.println(a + b);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - graph/kruskal.cpp
  - graph/mst_sensitivity.cpp
  - graph/kruskal.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_mst_sensitivity.test.cpp
  requiredBy: []
  timestamp: '2026-10-15 00:51:41+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_mst_sensitivity.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_mst_sensitivity.test.cpp
- /verify/test/yosupo_aplusb_mst_sensitivity.test.cpp.html
title: test/yosupo_aplusb_mst_sensitivity.test.cpp
---
