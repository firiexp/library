---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/weightedunionfind.cpp
    title: "\u91CD\u307F\u4ED8\u304DUnionFind(Weighted Union Find)"
  - icon: ':heavy_check_mark:'
    path: tree/rerooting.cpp
    title: "ReRooting(\u5168\u65B9\u4F4D\u6728DP)"
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_noncommutative_tree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\nextern\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"datastructure/weightedunionfind.cpp\"\
    \ntemplate <class G>\nclass WeightedUnionFind {\n    using T = typename G::T;\n\
    \    vector<int> uni;\n    vector<T> weights;\n\npublic:\n    explicit WeightedUnionFind(int\
    \ n) : uni(n, -1), weights(n, G::e()) {}\n\n    int root(int a) {\n        if\
    \ (uni[a] < 0) return a;\n        int p = uni[a];\n        int r = root(p);\n\
    \        weights[a] = G::op(weights[p], weights[a]);\n        return uni[a] =\
    \ r;\n    }\n\n    T weight(int a) {\n        root(a);\n        return weights[a];\n\
    \    }\n\n    bool same(int a, int b) {\n        return root(a) == root(b);\n\
    \    }\n\n    bool unite(int a, int b, T w) {\n        w = G::op(weight(a), G::op(w,\
    \ G::inv(weight(b))));\n        a = root(a);\n        b = root(b);\n        if\
    \ (a == b) return false;\n        if (uni[a] > uni[b]) {\n            swap(a,\
    \ b);\n            w = G::inv(w);\n        }\n        uni[a] += uni[b];\n    \
    \    uni[b] = a;\n        weights[b] = w;\n        return true;\n    }\n\n   \
    \ int size(int a) {\n        return -uni[root(a)];\n    }\n\n    T diff(int x,\
    \ int y) {\n        return G::op(G::inv(weight(x)), weight(y));\n    }\n};\n\n\
    /*\nstruct Group {\n    using T = long long;\n    static T op(T a, T b) { return\
    \ a + b; }\n    static T inv(T a) { return -a; }\n    static T e() { return 0;\
    \ }\n};\n*/\n\n/**\n * @brief \u91CD\u307F\u4ED8\u304DUnionFind(Weighted Union\
    \ Find)\n */\n#line 1 \"tree/rerooting.cpp\"\nusing namespace std;\n\ntemplate\
    \ <typename M>\nclass ReRooting {\npublic:\n    using T = typename M::T;\n   \
    \ using U = typename M::U;\n\n    struct Node {\n        int to, rev;\n      \
    \  U val;\n\n        Node(int to, int rev, U val) : to(to), rev(rev), val(val)\
    \ {}\n    };\n\n    int n;\n    vector<vector<Node>> G;\n    vector<vector<T>>\
    \ dpl, dpr;\n    vector<int> l, r;\n\n    explicit ReRooting(int n) : n(n), G(n),\
    \ dpl(n), dpr(n), l(n), r(n) {}\n\n    void add_edge(int u, int v, const U &x)\
    \ {\n        G[u].emplace_back(v, (int)G[v].size(), x);\n        G[v].emplace_back(u,\
    \ (int)G[u].size() - 1, x);\n    }\n\n    void add_edge(int u, int v, const U\
    \ &x, const U &y) {\n        G[u].emplace_back(v, (int)G[v].size(), x);\n    \
    \    G[v].emplace_back(u, (int)G[u].size() - 1, y);\n    }\n\n    T dfs(int i,\
    \ int par) {\n        while (l[i] != par && l[i] < (int)G[i].size()) {\n     \
    \       auto &e = G[i][l[i]];\n            dpl[i][l[i] + 1] = M::f(dpl[i][l[i]],\
    \ M::g(dfs(e.to, e.rev), e.val));\n            ++l[i];\n        }\n        while\
    \ (r[i] != par && r[i] >= 0) {\n            auto &e = G[i][r[i]];\n          \
    \  dpr[i][r[i]] = M::f(M::g(dfs(e.to, e.rev), e.val), dpr[i][r[i] + 1]);\n   \
    \         --r[i];\n        }\n        if (par < 0) return dpr[i].front();\n  \
    \      return M::f(dpl[i][par], dpr[i][par + 1]);\n    }\n\n    vector<T> solve()\
    \ {\n        for (int i = 0; i < n; ++i) {\n            dpl[i].assign(G[i].size()\
    \ + 1, M::e());\n            dpr[i].assign(G[i].size() + 1, M::e());\n       \
    \     l[i] = 0;\n            r[i] = (int)G[i].size() - 1;\n        }\n       \
    \ vector<T> ans(n);\n        for (int i = 0; i < n; ++i) ans[i] = dfs(i, -1);\n\
    \        return ans;\n    }\n};\n\n/**\n * @brief ReRooting(\u5168\u65B9\u4F4D\
    \u6728DP)\n */\n#line 8 \"test/yosupo_aplusb_noncommutative_tree.test.cpp\"\n\n\
    struct Permutations {\n    using T = array<int, 4>;\n    static T e() { return\
    \ {0, 1, 2, 3}; }\n    static T op(T a, T b) {\n        T c;\n        for (int\
    \ i = 0; i < 4; ++i) c[i] = a[b[i]];\n        return c;\n    }\n    static T inv(T\
    \ a) {\n        T b;\n        for (int i = 0; i < 4; ++i) b[a[i]] = i;\n     \
    \   return b;\n    }\n};\n\nvoid unionfind_check() {\n    using G = Permutations;\n\
    \    WeightedUnionFind<G> minimal(4);\n    G::T b{1, 0, 2, 3}, c{0, 2, 1, 3};\n\
    \    minimal.unite(0, 1, G::e());\n    minimal.unite(2, 3, b);\n    minimal.unite(0,\
    \ 2, c);\n    assert(minimal.diff(0, 3) == G::op(c, b));\n    assert(minimal.diff(2,\
    \ 3) == b);\n    mt19937 rng(28);\n    for (int n = 1; n <= 40; ++n) {\n     \
    \   vector<G::T> potential(n, G::e());\n        for (auto &p : potential) shuffle(p.begin(),\
    \ p.end(), rng);\n        vector<int> component(n);\n        iota(component.begin(),\
    \ component.end(), 0);\n        WeightedUnionFind<G> uf(n);\n        auto difference\
    \ = [&](int u, int v) {\n            return G::op(G::inv(potential[u]), potential[v]);\n\
    \        };\n        for (int step = 0; step < 100; ++step) {\n            //\
    \ Force the single-vertex component to join a larger one.\n            int u =\
    \ rng() % n, v = rng() % n;\n            if (n >= 3 && step == 0) u = 1, v = 2;\n\
    \            if (n >= 3 && step == 1) u = 0, v = 1;\n            bool distinct\
    \ = component[u] != component[v];\n            assert(uf.unite(u, v, difference(u,\
    \ v)) == distinct);\n            int from = component[v], to = component[u];\n\
    \            for (int &id : component) if (id == from) id = to;\n            for\
    \ (int a = 0; a < n; ++a) {\n                assert(uf.size(a) == count(component.begin(),\
    \ component.end(), component[a]));\n                uf.root(a);\n            \
    \    uf.root(a);\n                for (int b = 0; b < n; ++b) {\n            \
    \        assert(uf.same(a, b) == (component[a] == component[b]));\n          \
    \          if (uf.same(a, b)) assert(uf.diff(a, b) == difference(a, b));\n   \
    \             }\n            }\n        }\n    }\n}\n\nstruct OrderedTree {\n\
    \    using T = string;\n    using U = string;\n    static T e() { return \"\"\
    ; }\n    static T f(const T &a, const T &b) { return a + b; }\n    static T g(const\
    \ T &a, const U &edge) { return edge + \"(\" + a + \")\"; }\n};\n\nvoid rerooting_check()\
    \ {\n    ReRooting<OrderedTree> star(4);\n    star.add_edge(0, 1, \"a\");\n  \
    \  star.add_edge(0, 2, \"b\");\n    star.add_edge(0, 3, \"c\");\n    assert(star.solve()[0]\
    \ == \"a()b()c()\");\n    assert(star.solve()[2] == \"b(a()c())\");\n    mt19937\
    \ rng(44);\n    for (int n = 0; n <= 29; ++n) {\n        for (int tc = 0; tc <\
    \ 20; ++tc) {\n            vector<pair<int, int>> edges;\n            for (int\
    \ v = 1; v < n; ++v) edges.emplace_back(rng() % v, v);\n            shuffle(edges.begin(),\
    \ edges.end(), rng);\n            ReRooting<OrderedTree> tree(n);\n          \
    \  vector<vector<pair<int, string>>> adj(n);\n            for (auto [u, v] : edges)\
    \ {\n                string x = to_string(u) + \":\" + to_string(v);\n       \
    \         string y = to_string(v) + \":\" + to_string(u);\n                tree.add_edge(u,\
    \ v, x, y);\n                adj[u].emplace_back(v, x);\n                adj[v].emplace_back(u,\
    \ y);\n            }\n            auto dfs = [&](auto &&self, int v, int parent)\
    \ -> string {\n                string result;\n                for (auto [to,\
    \ label] : adj[v])\n                    if (to != parent) result += label + \"\
    (\" + self(self, to, v) + \")\";\n                return result;\n           \
    \ };\n            vector<string> expected;\n            for (int root = 0; root\
    \ < n; ++root) expected.push_back(dfs(dfs, root, -1));\n            assert(tree.solve()\
    \ == expected);\n            assert(tree.solve() == expected);\n        }\n  \
    \  }\n}\n\nint main() {\n    unionfind_check();\n    rerooting_check();\n    Scanner\
    \ sc;\n    Printer pr;\n    int a, b;\n    sc.read(a, b);\n    pr.println(a +\
    \ b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n#include \"../util/fastio.cpp\"\n#include \"../datastructure/weightedunionfind.cpp\"\
    \n#include \"../tree/rerooting.cpp\"\n\nstruct Permutations {\n    using T = array<int,\
    \ 4>;\n    static T e() { return {0, 1, 2, 3}; }\n    static T op(T a, T b) {\n\
    \        T c;\n        for (int i = 0; i < 4; ++i) c[i] = a[b[i]];\n        return\
    \ c;\n    }\n    static T inv(T a) {\n        T b;\n        for (int i = 0; i\
    \ < 4; ++i) b[a[i]] = i;\n        return b;\n    }\n};\n\nvoid unionfind_check()\
    \ {\n    using G = Permutations;\n    WeightedUnionFind<G> minimal(4);\n    G::T\
    \ b{1, 0, 2, 3}, c{0, 2, 1, 3};\n    minimal.unite(0, 1, G::e());\n    minimal.unite(2,\
    \ 3, b);\n    minimal.unite(0, 2, c);\n    assert(minimal.diff(0, 3) == G::op(c,\
    \ b));\n    assert(minimal.diff(2, 3) == b);\n    mt19937 rng(28);\n    for (int\
    \ n = 1; n <= 40; ++n) {\n        vector<G::T> potential(n, G::e());\n       \
    \ for (auto &p : potential) shuffle(p.begin(), p.end(), rng);\n        vector<int>\
    \ component(n);\n        iota(component.begin(), component.end(), 0);\n      \
    \  WeightedUnionFind<G> uf(n);\n        auto difference = [&](int u, int v) {\n\
    \            return G::op(G::inv(potential[u]), potential[v]);\n        };\n \
    \       for (int step = 0; step < 100; ++step) {\n            // Force the single-vertex\
    \ component to join a larger one.\n            int u = rng() % n, v = rng() %\
    \ n;\n            if (n >= 3 && step == 0) u = 1, v = 2;\n            if (n >=\
    \ 3 && step == 1) u = 0, v = 1;\n            bool distinct = component[u] != component[v];\n\
    \            assert(uf.unite(u, v, difference(u, v)) == distinct);\n         \
    \   int from = component[v], to = component[u];\n            for (int &id : component)\
    \ if (id == from) id = to;\n            for (int a = 0; a < n; ++a) {\n      \
    \          assert(uf.size(a) == count(component.begin(), component.end(), component[a]));\n\
    \                uf.root(a);\n                uf.root(a);\n                for\
    \ (int b = 0; b < n; ++b) {\n                    assert(uf.same(a, b) == (component[a]\
    \ == component[b]));\n                    if (uf.same(a, b)) assert(uf.diff(a,\
    \ b) == difference(a, b));\n                }\n            }\n        }\n    }\n\
    }\n\nstruct OrderedTree {\n    using T = string;\n    using U = string;\n    static\
    \ T e() { return \"\"; }\n    static T f(const T &a, const T &b) { return a +\
    \ b; }\n    static T g(const T &a, const U &edge) { return edge + \"(\" + a +\
    \ \")\"; }\n};\n\nvoid rerooting_check() {\n    ReRooting<OrderedTree> star(4);\n\
    \    star.add_edge(0, 1, \"a\");\n    star.add_edge(0, 2, \"b\");\n    star.add_edge(0,\
    \ 3, \"c\");\n    assert(star.solve()[0] == \"a()b()c()\");\n    assert(star.solve()[2]\
    \ == \"b(a()c())\");\n    mt19937 rng(44);\n    for (int n = 0; n <= 29; ++n)\
    \ {\n        for (int tc = 0; tc < 20; ++tc) {\n            vector<pair<int, int>>\
    \ edges;\n            for (int v = 1; v < n; ++v) edges.emplace_back(rng() % v,\
    \ v);\n            shuffle(edges.begin(), edges.end(), rng);\n            ReRooting<OrderedTree>\
    \ tree(n);\n            vector<vector<pair<int, string>>> adj(n);\n          \
    \  for (auto [u, v] : edges) {\n                string x = to_string(u) + \":\"\
    \ + to_string(v);\n                string y = to_string(v) + \":\" + to_string(u);\n\
    \                tree.add_edge(u, v, x, y);\n                adj[u].emplace_back(v,\
    \ x);\n                adj[v].emplace_back(u, y);\n            }\n           \
    \ auto dfs = [&](auto &&self, int v, int parent) -> string {\n               \
    \ string result;\n                for (auto [to, label] : adj[v])\n          \
    \          if (to != parent) result += label + \"(\" + self(self, to, v) + \"\
    )\";\n                return result;\n            };\n            vector<string>\
    \ expected;\n            for (int root = 0; root < n; ++root) expected.push_back(dfs(dfs,\
    \ root, -1));\n            assert(tree.solve() == expected);\n            assert(tree.solve()\
    \ == expected);\n        }\n    }\n}\n\nint main() {\n    unionfind_check();\n\
    \    rerooting_check();\n    Scanner sc;\n    Printer pr;\n    int a, b;\n   \
    \ sc.read(a, b);\n    pr.println(a + b);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/weightedunionfind.cpp
  - tree/rerooting.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_noncommutative_tree.test.cpp
  requiredBy: []
  timestamp: '2026-10-05 22:58:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_noncommutative_tree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_noncommutative_tree.test.cpp
- /verify/test/yosupo_aplusb_noncommutative_tree.test.cpp.html
title: test/yosupo_aplusb_noncommutative_tree.test.cpp
---
