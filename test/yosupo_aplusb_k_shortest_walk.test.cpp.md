---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/edge.cpp
    title: graph/edge.cpp
  - icon: ':heavy_check_mark:'
    path: graph/k_shortest_walk.cpp
    title: "K\u756A\u76EE\u306E\u6700\u77ED\u30A6\u30A9\u30FC\u30AF"
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_k_shortest_walk.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\nusing\
    \ namespace std;\nusing ll = long long;\n\n#line 1 \"util/fastio.cpp\"\nusing\
    \ namespace std;\n\nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"graph/k_shortest_walk.cpp\"\
    \n\n\n\n#line 1 \"graph/edge.cpp\"\n\n\n\ntemplate <typename T>\nstruct edge {\n\
    \    int from, to;\n    T cost;\n\n    edge(int to, T cost) : from(-1), to(to),\
    \ cost(cost) {}\n    edge(int from, int to, T cost) : from(from), to(to), cost(cost)\
    \ {}\n\n    explicit operator int() const { return to; }\n};\n\n\n#line 5 \"graph/k_shortest_walk.cpp\"\
    \n\ntemplate <class T>\nvector<T> k_shortest_walk(int s, int t, int k, const vector<vector<edge<T>>>\
    \ &g) {\n    int n = (int)g.size();\n    assert(0 <= s && s < n && 0 <= t && t\
    \ < n && k >= 0);\n    if (k == 0) return {};\n    vector<vector<pair<int, int>>>\
    \ reverse_graph(n);\n    size_t m = 0;\n    for (int v = 0; v < n; ++v) {\n  \
    \      m += g[v].size();\n        for (int i = 0; i < (int)g[v].size(); ++i) {\n\
    \            const auto &e = g[v][i];\n            assert(0 <= e.to && e.to <\
    \ n && e.cost >= 0);\n            reverse_graph[e.to].emplace_back(v, i);\n  \
    \      }\n    }\n    vector<T> dist(n);\n    vector<char> reached(n);\n    vector<int>\
    \ parent_edge(n, -1), order;\n    priority_queue<pair<T, int>, vector<pair<T,\
    \ int>>, greater<>> queue;\n    reached[t] = true;\n    queue.emplace(T(0), t);\n\
    \    while (!queue.empty()) {\n        auto [value, v] = queue.top();\n      \
    \  queue.pop();\n        if (value != dist[v]) continue;\n        order.push_back(v);\n\
    \        for (auto [u, i] : reverse_graph[v]) {\n            T next = value +\
    \ g[u][i].cost;\n            if (reached[u] && dist[u] <= next) continue;\n  \
    \          reached[u] = true;\n            dist[u] = next;\n            parent_edge[u]\
    \ = i;\n            queue.emplace(next, u);\n        }\n    }\n    if (!reached[s])\
    \ return {};\n    vector<T> result{dist[s]};\n    if (k == 1) return result;\n\
    \n    struct Node { T delta; int to, left, right, rank; };\n    vector<Node> nodes{\
    \ { T(0), -1, 0, 0, 0 } };\n    nodes.reserve(m + 1);\n    auto meld = [&](auto\
    \ &&self, int a, int b, bool persistent) -> int {\n        if (!a) return b;\n\
    \        if (!b) return a;\n        if (nodes[b].delta < nodes[a].delta) swap(a,\
    \ b);\n        if (persistent) {\n            Node copy = nodes[a];\n        \
    \    a = (int)nodes.size();\n            nodes.push_back(copy);\n        }\n \
    \       int right = self(self, nodes[a].right, b, persistent);\n        nodes[a].right\
    \ = right;\n        if (nodes[nodes[a].left].rank < nodes[right].rank) swap(nodes[a].left,\
    \ nodes[a].right);\n        nodes[a].rank = nodes[nodes[a].right].rank + 1;\n\
    \        return a;\n    };\n    vector<int> roots(n);\n    for (int v : order)\
    \ {\n        int heap = 0;\n        for (int i = 0; i < (int)g[v].size(); ++i)\
    \ {\n            const auto &e = g[v][i];\n            if (i == parent_edge[v]\
    \ || !reached[e.to]) continue;\n            int id = (int)nodes.size();\n    \
    \        nodes.push_back({e.cost + dist[e.to] - dist[v], e.to, 0, 0, 1});\n  \
    \          heap = meld(meld, heap, id, false);\n        }\n        if (parent_edge[v]\
    \ != -1) {\n            int parent = g[v][parent_edge[v]].to;\n            heap\
    \ = meld(meld, heap, roots[parent], true);\n        }\n        roots[v] = heap;\n\
    \    }\n    if (roots[s]) queue.emplace(dist[s] + nodes[roots[s]].delta, roots[s]);\n\
    \    while (!queue.empty() && (int)result.size() < k) {\n        auto [value,\
    \ id] = queue.top();\n        queue.pop();\n        result.push_back(value);\n\
    \        if ((int)result.size() == k) break;\n        const auto &node = nodes[id];\n\
    \        for (int child : {node.left, node.right}) {\n            if (child) queue.emplace(value\
    \ - node.delta + nodes[child].delta, child);\n        }\n        int next = roots[node.to];\n\
    \        if (next) queue.emplace(value + nodes[next].delta, next);\n    }\n  \
    \  return result;\n}\n\n\n\n/**\n * @brief K\u756A\u76EE\u306E\u6700\u77ED\u30A6\
    \u30A9\u30FC\u30AF\n */\n#line 9 \"test/yosupo_aplusb_k_shortest_walk.test.cpp\"\
    \n\nvector<ll> naive(int s, int t, int k, const vector<vector<edge<ll>>> &g) {\n\
    \    vector<int> count(g.size());\n    vector<ll> result;\n    priority_queue<pair<ll,\
    \ int>, vector<pair<ll, int>>, greater<>> queue;\n    queue.emplace(0, s);\n \
    \   while (!queue.empty() && (int)result.size() < k) {\n        auto [cost, v]\
    \ = queue.top();\n        queue.pop();\n        if (count[v] == k) continue;\n\
    \        ++count[v];\n        if (v == t) result.push_back(cost);\n        for\
    \ (const auto &e : g[v]) {\n            if (count[e.to] < k) queue.emplace(cost\
    \ + e.cost, e.to);\n        }\n    }\n    return result;\n}\n\nvoid check(const\
    \ vector<vector<edge<ll>>> &g, int s, int t, int k) {\n    auto copy = g;\n  \
    \  assert(k_shortest_walk(s, t, k, g) == naive(s, t, k, g));\n    for (int v =\
    \ 0; v < (int)g.size(); ++v) {\n        assert(copy[v].size() == g[v].size());\n\
    \        for (int i = 0; i < (int)g[v].size(); ++i) {\n            assert(copy[v][i].from\
    \ == g[v][i].from);\n            assert(copy[v][i].to == g[v][i].to);\n      \
    \      assert(copy[v][i].cost == g[v][i].cost);\n        }\n    }\n}\n\nvoid self_check()\
    \ {\n    for (int mask = 0; mask < 81; ++mask) {\n        vector<vector<edge<ll>>>\
    \ g(2);\n        int state = mask;\n        for (int u = 0; u < 2; ++u) for (int\
    \ v = 0; v < 2; ++v) {\n            int kind = state % 3;\n            state /=\
    \ 3;\n            if (kind) g[u].emplace_back(u, v, kind == 1 ? 0 : 3);\n    \
    \    }\n        for (int s = 0; s < 2; ++s) for (int t = 0; t < 2; ++t) check(g,\
    \ s, t, 8);\n    }\n    vector<vector<edge<ll>>> g(4);\n    g[0].emplace_back(1,\
    \ 0);\n    g[0].emplace_back(1, 0);\n    g[1].emplace_back(0, 0);\n    g[1].emplace_back(2,\
    \ 5);\n    g[2].emplace_back(1, 0);\n    g[3].emplace_back(3, 0);\n    for (int\
    \ s = 0; s < 4; ++s) for (int t = 0; t < 4; ++t) {\n        check(g, s, t, 0);\n\
    \        check(g, s, t, 1);\n        check(g, s, t, 30);\n    }\n    vector<vector<edge<ll>>>\
    \ large_cost(3);\n    large_cost[0].emplace_back(1, 3000000000LL);\n    large_cost[0].emplace_back(1,\
    \ 3000000000LL);\n    large_cost[1].emplace_back(2, 4000000000LL);\n    check(large_cost,\
    \ 0, 2, 10);\n    large_cost[0].clear();\n    large_cost[1].clear();\n    large_cost[0].emplace_back(2,\
    \ LLONG_MAX);\n    large_cost[0].emplace_back(2, LLONG_MAX - 1);\n    check(large_cost,\
    \ 0, 2, 5);\n    mt19937 rng(84);\n    for (int tc = 0; tc < 10000; ++tc) {\n\
    \        int n = 1 + rng() % 8, m = rng() % 25;\n        vector<vector<edge<ll>>>\
    \ graph(n);\n        for (int i = 0; i < m; ++i) graph[rng() % n].emplace_back(rng()\
    \ % n, rng() % 10);\n        check(graph, rng() % n, rng() % n, rng() % 25);\n\
    \    }\n    vector<vector<edge<int>>> path(20000);\n    for (int i = 0; i < 19999;\
    \ ++i) path[i].emplace_back(i + 1, 1);\n    assert(k_shortest_walk(0, 19999, 20,\
    \ path) == vector<int>{19999});\n    path.back().emplace_back(19999, 7);\n   \
    \ auto costs = k_shortest_walk(0, 19999, 20, path);\n    assert(costs.size() ==\
    \ 20);\n    for (int i = 0; i < 20; ++i) assert(costs[i] == 19999 + 7 * i);\n\
    }\n\nint main() {\n    self_check();\n    Scanner in;\n    Printer out;\n    int\
    \ a, b;\n    in.read(a, b);\n    out.println(a + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing ll = long long;\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../graph/k_shortest_walk.cpp\"\n\nvector<ll> naive(int s, int t,\
    \ int k, const vector<vector<edge<ll>>> &g) {\n    vector<int> count(g.size());\n\
    \    vector<ll> result;\n    priority_queue<pair<ll, int>, vector<pair<ll, int>>,\
    \ greater<>> queue;\n    queue.emplace(0, s);\n    while (!queue.empty() && (int)result.size()\
    \ < k) {\n        auto [cost, v] = queue.top();\n        queue.pop();\n      \
    \  if (count[v] == k) continue;\n        ++count[v];\n        if (v == t) result.push_back(cost);\n\
    \        for (const auto &e : g[v]) {\n            if (count[e.to] < k) queue.emplace(cost\
    \ + e.cost, e.to);\n        }\n    }\n    return result;\n}\n\nvoid check(const\
    \ vector<vector<edge<ll>>> &g, int s, int t, int k) {\n    auto copy = g;\n  \
    \  assert(k_shortest_walk(s, t, k, g) == naive(s, t, k, g));\n    for (int v =\
    \ 0; v < (int)g.size(); ++v) {\n        assert(copy[v].size() == g[v].size());\n\
    \        for (int i = 0; i < (int)g[v].size(); ++i) {\n            assert(copy[v][i].from\
    \ == g[v][i].from);\n            assert(copy[v][i].to == g[v][i].to);\n      \
    \      assert(copy[v][i].cost == g[v][i].cost);\n        }\n    }\n}\n\nvoid self_check()\
    \ {\n    for (int mask = 0; mask < 81; ++mask) {\n        vector<vector<edge<ll>>>\
    \ g(2);\n        int state = mask;\n        for (int u = 0; u < 2; ++u) for (int\
    \ v = 0; v < 2; ++v) {\n            int kind = state % 3;\n            state /=\
    \ 3;\n            if (kind) g[u].emplace_back(u, v, kind == 1 ? 0 : 3);\n    \
    \    }\n        for (int s = 0; s < 2; ++s) for (int t = 0; t < 2; ++t) check(g,\
    \ s, t, 8);\n    }\n    vector<vector<edge<ll>>> g(4);\n    g[0].emplace_back(1,\
    \ 0);\n    g[0].emplace_back(1, 0);\n    g[1].emplace_back(0, 0);\n    g[1].emplace_back(2,\
    \ 5);\n    g[2].emplace_back(1, 0);\n    g[3].emplace_back(3, 0);\n    for (int\
    \ s = 0; s < 4; ++s) for (int t = 0; t < 4; ++t) {\n        check(g, s, t, 0);\n\
    \        check(g, s, t, 1);\n        check(g, s, t, 30);\n    }\n    vector<vector<edge<ll>>>\
    \ large_cost(3);\n    large_cost[0].emplace_back(1, 3000000000LL);\n    large_cost[0].emplace_back(1,\
    \ 3000000000LL);\n    large_cost[1].emplace_back(2, 4000000000LL);\n    check(large_cost,\
    \ 0, 2, 10);\n    large_cost[0].clear();\n    large_cost[1].clear();\n    large_cost[0].emplace_back(2,\
    \ LLONG_MAX);\n    large_cost[0].emplace_back(2, LLONG_MAX - 1);\n    check(large_cost,\
    \ 0, 2, 5);\n    mt19937 rng(84);\n    for (int tc = 0; tc < 10000; ++tc) {\n\
    \        int n = 1 + rng() % 8, m = rng() % 25;\n        vector<vector<edge<ll>>>\
    \ graph(n);\n        for (int i = 0; i < m; ++i) graph[rng() % n].emplace_back(rng()\
    \ % n, rng() % 10);\n        check(graph, rng() % n, rng() % n, rng() % 25);\n\
    \    }\n    vector<vector<edge<int>>> path(20000);\n    for (int i = 0; i < 19999;\
    \ ++i) path[i].emplace_back(i + 1, 1);\n    assert(k_shortest_walk(0, 19999, 20,\
    \ path) == vector<int>{19999});\n    path.back().emplace_back(19999, 7);\n   \
    \ auto costs = k_shortest_walk(0, 19999, 20, path);\n    assert(costs.size() ==\
    \ 20);\n    for (int i = 0; i < 20; ++i) assert(costs[i] == 19999 + 7 * i);\n\
    }\n\nint main() {\n    self_check();\n    Scanner in;\n    Printer out;\n    int\
    \ a, b;\n    in.read(a, b);\n    out.println(a + b);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - graph/k_shortest_walk.cpp
  - graph/edge.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_k_shortest_walk.test.cpp
  requiredBy: []
  timestamp: '2026-10-17 02:52:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_k_shortest_walk.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_k_shortest_walk.test.cpp
- /verify/test/yosupo_aplusb_k_shortest_walk.test.cpp.html
title: test/yosupo_aplusb_k_shortest_walk.test.cpp
---
