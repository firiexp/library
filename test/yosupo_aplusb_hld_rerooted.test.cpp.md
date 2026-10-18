---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/segmenttree/lazysegtree.cpp
    title: "\u9045\u5EF6\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Lazy Segment Tree)"
  - icon: ':heavy_check_mark:'
    path: tree/hld.cpp
    title: "HL\u5206\u89E3(HL Decomposition)"
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_hld_rerooted.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\nusing\
    \ namespace std;\nusing ll = long long;\n#line 1 \"util/fastio.cpp\"\nusing namespace\
    \ std;\n\nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\n\
    template<class T, class = void>\nstruct is_fastio_range : false_type {};\n\ntemplate<class\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"tree/hld.cpp\"\
    \n\n\n\nclass HeavyLightDecomposition {\n    void dfs_sz(int root, vector<int>\
    \ &order){\n        order.clear();\n        order.push_back(root);\n        for\
    \ (int i = 0; i < (int)order.size(); ++i) {\n            int v = order[i];\n \
    \           for (int u : G[v]) {\n                if (u == par[v]) continue;\n\
    \                par[u] = v;\n                dep[u] = dep[v] + 1;\n         \
    \       order.push_back(u);\n            }\n        }\n        for (int i = (int)order.size()\
    \ - 1; i >= 0; --i) {\n            int v = order[i], heavy = -1;\n           \
    \ for (int u : G[v]) {\n                if (u == par[v]) continue;\n         \
    \       sub_size[v] += sub_size[u];\n                if (heavy == -1 || sub_size[u]\
    \ > sub_size[heavy]) heavy = u;\n            }\n            if (heavy != -1 &&\
    \ G[v][0] != heavy) {\n                for (auto &u : G[v]) {\n              \
    \      if (u == heavy) {\n                        swap(u, G[v][0]);\n        \
    \                break;\n                    }\n                }\n          \
    \  }\n        }\n    }\n    void dfs_hld(int root, int c, int &pos, vector<int>\
    \ &stack){\n        stack.clear();\n        stack.push_back(root);\n        while\
    \ (!stack.empty()) {\n            int v = stack.back();\n            stack.pop_back();\n\
    \            id[v] = pos++;\n            id_inv[id[v]] = v;\n            tree_id[v]\
    \ = c;\n            for (int i = (int)G[v].size() - 1; i >= 0; --i) {\n      \
    \          int u = G[v][i];\n                if (u == par[v]) continue;\n    \
    \            head[u] = (u == G[v][0] ? head[v] : u);\n                stack.push_back(u);\n\
    \            }\n        }\n    }\npublic:\n    int n;\n    vector<vector<int>>\
    \ G;\n    vector<int> par, dep, sub_size, id, id_inv, tree_id, head;\n    explicit\
    \ HeavyLightDecomposition(int n) : n(n), G(n), par(n), dep(n), sub_size(n, 1),\
    \ id(n), id_inv(n), tree_id(n), head(n){}\n    explicit HeavyLightDecomposition(vector<vector<int>>\
    \ &G) : n(G.size()), G(G), par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n),\
    \ head(n) {}\n\n    void add_edge(int u, int v){\n        G[u].emplace_back(v);\n\
    \        G[v].emplace_back(u);\n    }\n\n    void build(vector<int> roots = {0}){\n\
    \        if (n == 0) return;\n        fill(par.begin(), par.end(), -1);\n    \
    \    fill(dep.begin(), dep.end(), 0);\n        fill(sub_size.begin(), sub_size.end(),\
    \ 1);\n        int c = 0, pos = 0;\n        vector<int> order;\n        for (auto\
    \ &&i : roots) {\n            dfs_sz(i, order);\n            head[i] = i;\n  \
    \          dfs_hld(i, c++, pos, order);\n        }\n    }\n\n    int lca(int u,\
    \ int v) const {\n        while(true){\n            if(id[u] > id[v]) swap(u,\
    \ v);\n            if(head[u] == head[v]) return u;\n            v = par[head[v]];\n\
    \        }\n    }\n\n    int parent(int v) const {\n        return par[v];\n \
    \   }\n\n    int ancestor(int v, int k) const {\n        if(dep[v] < k) return\
    \ -1;\n        while(true) {\n            int u = head[v];\n            if(id[v]\
    \ - k >= id[u]) return id_inv[id[v] - k];\n            k -= id[v]-id[u]+1;\n \
    \           v = par[u];\n        }\n    }\n\n    int distance(int u, int v){ return\
    \ dep[u] + dep[v] - 2*dep[lca(u, v)]; }\n\n    pair<int, int> subtree(int v, bool\
    \ edge = false) const {\n        return {id[v] + edge, id[v] + sub_size[v]};\n\
    \    }\n\n    int rerooted_lca(int u, int v, int root) const {\n        int answer\
    \ = lca(u, v);\n        int a = lca(u, root), b = lca(v, root);\n        if (dep[a]\
    \ > dep[answer]) answer = a;\n        if (dep[b] > dep[answer]) answer = b;\n\
    \        return answer;\n    }\n\n    template<typename F>\n    void rerooted_subtree(int\
    \ v, int root, const F& f) const {\n        auto [l, r] = subtree(v);\n      \
    \  if (id[root] < l || r <= id[root]) {\n            f(l, r);\n            return;\n\
    \        }\n        auto [begin, end] = subtree(ancestor(v, dep[v]));\n      \
    \  if (v == root) {\n            f(begin, end);\n            return;\n       \
    \ }\n        int child = ancestor(root, dep[root] - dep[v] - 1);\n        auto\
    \ [cl, cr] = subtree(child);\n        if (begin < cl) f(begin, cl);\n        if\
    \ (cr < end) f(cr, end);\n    }\n\n    template<typename F>\n    void add(int\
    \ u, int v, const F &f, bool edge){\n        while (head[u] != head[v]){\n   \
    \         if(id[u] > id[v]) swap(u, v);\n            f(id[head[v]], id[v]+1);\n\
    \            v = par[head[v]];\n        }\n        if(id[u] > id[v]) swap(u, v);\n\
    \        f(id[u]+edge, id[v]+1);\n    }\n\n    template<typename F>\n    void\
    \ path(int u, int v, const F &f, bool edge = false){\n        add(u, v, f, edge);\n\
    \    }\n\n    template<typename F>\n    void path_ordered(int u, int v, const\
    \ F &f, bool edge = false) const {\n        struct Interval { int l, r; };\n \
    \       Interval pending[numeric_limits<unsigned>::digits];\n        int size\
    \ = 0;\n        while (head[u] != head[v]) {\n            if (id[u] > id[v]) {\n\
    \                f(id[head[u]], id[u] + 1, true);\n                u = par[head[u]];\n\
    \            } else {\n                pending[size++] = {id[head[v]], id[v] +\
    \ 1};\n                v = par[head[v]];\n            }\n        }\n        if\
    \ (id[u] <= id[v]) {\n            if (id[u] + edge <= id[v]) f(id[u] + edge, id[v]\
    \ + 1, false);\n        } else {\n            f(id[v] + edge, id[u] + 1, true);\n\
    \        }\n        while (size) {\n            auto [l, r] = pending[--size];\n\
    \            f(l, r, false);\n        }\n    }\n\n    template<typename F>\n \
    \   void apply_subtree(int v, const F &f, bool edge = false){\n        auto [l,\
    \ r] = subtree(v, edge);\n        f(l, r);\n    }\n\n    template<typename T,\
    \ typename Q, typename F>\n    T query(int u, int v, const T &e, const Q &q, const\
    \ F &f, bool edge){\n        T l = e, r = e;\n        while(head[u] != head[v]){\n\
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
    \u89E3(HL Decomposition)\n */\n\n\n#line 1 \"datastructure/segmenttree/lazysegtree.cpp\"\
    \ntemplate <class M>\nstruct LazySegmentTree{\n    using T = typename M::T;\n\
    \    using L = typename M::L;\n    int sz, n, height{};\n    vector<T> seg; vector<L>\
    \ lazy;\n    explicit LazySegmentTree(int n) : n(n) {\n        sz = 1; while(sz\
    \ < n) sz <<= 1, height++;\n        seg.assign(2*sz, M::e());\n        lazy.assign(2*sz,\
    \ M::l());\n    }\n\n    void set(int k, const T &x){ seg[k + sz] = x; }\n\n \
    \   void build(){\n        for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[i<<1],\
    \ seg[(i<<1)|1]);\n    }\n\n    T reflect(int k){ return lazy[k] == M::l() ? seg[k]\
    \ : M::g(seg[k], lazy[k]); }\n\n    void eval(int k){\n        if(lazy[k] == M::l())\
    \ return;\n        if(k < sz){\n            lazy[(k<<1)|0] = M::h(lazy[(k<<1)|0],\
    \ lazy[k]);\n            lazy[(k<<1)|1] = M::h(lazy[(k<<1)|1], lazy[k]);\n   \
    \     }\n        seg[k] = reflect(k);\n        lazy[k] = M::l();\n    }\n    void\
    \ thrust(int k){ for (int i = height; i; --i) eval(k>>i); }\n    void recalc(int\
    \ k) { while(k >>= 1) seg[k] = M::f(reflect((k<<1)|0), reflect((k<<1)|1));}\n\n\
    \    void update(int a, const T &x){\n        thrust(a += sz);\n        seg[a]\
    \ = x;\n        lazy[a] = M::l();\n        recalc(a);\n    }\n\n    void update(int\
    \ a, int b, const L &x){\n        if(a == b) return;\n        a += sz; b += sz;\n\
    \        int ha = __builtin_ctz(a), hb = __builtin_ctz(b);\n        for(int i\
    \ = height; i > ha; --i) eval(a >> i);\n        for(int i = height; i > hb; --i)\
    \ eval((b-1) >> i);\n        for (int l = a, r = b; l < r; l >>=1, r >>= 1) {\n\
    \            if(l&1) lazy[l] = M::h(lazy[l], x), l++;\n            if(r&1) --r,\
    \ lazy[r] = M::h(lazy[r], x);\n        }\n        recalc(a >> ha);\n        recalc((b-1)\
    \ >> hb);\n    }\n\n    T query(int a, int b){ // [l, r)\n        if(a == b) return\
    \ M::e();\n        a += sz; b += sz;\n        int ha = __builtin_ctz(a), hb =\
    \ __builtin_ctz(b);\n        for(int i = height; i > ha; --i) eval(a >> i);\n\
    \        for(int i = height; i > hb; --i) eval((b-1) >> i);\n        T ll = M::e(),\
    \ rr = M::e();\n        for(int l = a, r = b; l < r; l >>=1, r>>=1) {\n      \
    \      if (l & 1) ll = M::f(ll, reflect(l++));\n            if (r & 1) rr = M::f(reflect(--r),\
    \ rr);\n        }\n        return M::f(ll, rr);\n    }\n\n    template<class F>\n\
    \    int search_right(int l, F cond){\n        if(l == n) return n;\n        thrust(l\
    \ += sz);\n        T val = M::e();\n        do {\n            while(!(l&1)) l\
    \ >>= 1;\n            T next = M::f(val, reflect(l));\n            if(!cond(next)){\n\
    \                while(l < sz) {\n                    eval(l); l <<= 1;\n    \
    \                next = M::f(val, reflect(l));\n                    if (cond(next)){\n\
    \                        val = move(next);\n                        l++;\n   \
    \                 }\n                }\n                return l - sz;\n     \
    \       }\n            val = move(next);\n            l++;\n        } while((l\
    \ & -l) != l);\n        return n;\n    }\n\n    template<class F>\n    int search_left(int\
    \ r, F cond){\n        if(r <= 0) return 0;\n        thrust((r += sz)-1);\n  \
    \      T val = M::e();\n        do {\n            r--;\n            while(r >\
    \ 1 && r&1) r >>= 1;\n            T next = M::f(reflect(r), val);\n          \
    \  if(!cond(next)){\n                while(r < sz) {\n                    eval(r);\n\
    \                    r = ((r << 1)|1);\n                    next = M::f(reflect(r),\
    \ val);\n                    if (cond(next)){\n                        val = move(next);\n\
    \                        r--;\n                    }\n                }\n    \
    \            return r + 1 - sz;\n            }\n            val = move(next);\n\
    \        } while((r & -r) != r);\n        return 0;\n    }\n};\n\n/*\nstruct Monoid{\n\
    \    using T = array<mint, 2>;\n    using L = array<mint, 2>;\n    static T f(T\
    \ a, T b) { return {a[0]+b[0], a[1]+b[1]}; }\n    static T g(T a, L b) {\n   \
    \     return {a[0] * b[0] + a[1] * b[1], a[1]};\n    }\n    static L h(L a, L\
    \ b) {\n        return {a[0]*b[0], a[1]*b[0]+b[1]};\n    }\n    static T e() {\
    \ return {0, 0}; }\n    static L l() { return {1, 0}; }\n};\n*/\n\n/**\n * @brief\
    \ \u9045\u5EF6\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Lazy Segment Tree)\n */\n#line\
    \ 9 \"test/yosupo_aplusb_hld_rerooted.test.cpp\"\n\nstruct SumAdd {\n    using\
    \ T = array<ll, 2>;\n    using L = ll;\n    static T f(T a, T b) { return {a[0]\
    \ + b[0], a[1] + b[1]}; }\n    static T g(T a, L x) { return {a[0] + a[1] * x,\
    \ a[1]}; }\n    static L h(L a, L b) { return a + b; }\n    static T e() { return\
    \ {0, 0}; }\n    static L l() { return 0; }\n};\n\nvoid self_check() {\n    mt19937\
    \ rng(155);\n    for (int tc = 0; tc < 350; ++tc) {\n        int n = 1 + rng()\
    \ % 28;\n        HeavyLightDecomposition hld(n);\n        vector<vector<int>>\
    \ g(n);\n        for (int v = 1; v < n; ++v) {\n            if (tc % 2 && rng()\
    \ % 4 == 0) continue;\n            int p = tc % 5 == 0 ? v - 1 : tc % 5 == 1 ?\
    \ 0 : rng() % v;\n            hld.add_edge(p, v);\n            g[p].push_back(v);\n\
    \            g[v].push_back(p);\n        }\n        vector<int> seen(n), roots;\n\
    \        for (int v = 0; v < n; ++v) if (!seen[v]) {\n            vector<int>\
    \ component{v};\n            seen[v] = 1;\n            for (int i = 0; i < (int)component.size();\
    \ ++i) {\n                for (int u : g[component[i]]) if (!seen[u]) {\n    \
    \                seen[u] = 1;\n                    component.push_back(u);\n \
    \               }\n            }\n            roots.push_back(component[rng()\
    \ % component.size()]);\n        }\n        shuffle(roots.begin(), roots.end(),\
    \ rng);\n        hld.build(roots);\n        auto ids = hld.id, parents = hld.par,\
    \ depths = hld.dep;\n        const auto& index = hld;\n        vector<ll> values(n);\n\
    \        LazySegmentTree<SumAdd> seg(n);\n        for (int v = 0; v < n; ++v)\
    \ seg.set(hld.id[v], {0, 1});\n        seg.build();\n        for (int root = 0;\
    \ root < n; ++root) {\n            vector<int> parent(n, -2), depth(n), order{root};\n\
    \            parent[root] = -1;\n            for (int i = 0; i < (int)order.size();\
    \ ++i) {\n                int v = order[i];\n                for (int u : g[v])\
    \ if (u != parent[v]) {\n                    parent[u] = v;\n                \
    \    depth[u] = depth[v] + 1;\n                    order.push_back(u);\n     \
    \           }\n            }\n            for (int v : order) {\n            \
    \    vector<int> expected, actual;\n                for (int u : order) {\n  \
    \                  int x = u;\n                    while (x != -1 && x != v) x\
    \ = parent[x];\n                    if (x == v) expected.push_back(u);\n     \
    \           }\n                int calls = 0, previous = -1;\n               \
    \ index.rerooted_subtree(v, root, [&](int l, int r) {\n                    assert(0\
    \ <= l && l < r && r <= n && previous <= l);\n                    previous = r;\n\
    \                    ++calls;\n                    for (int i = l; i < r; ++i)\
    \ actual.push_back(hld.id_inv[i]);\n                });\n                sort(expected.begin(),\
    \ expected.end());\n                sort(actual.begin(), actual.end());\n    \
    \            assert(actual == expected && 1 <= calls && calls <= 2);\n       \
    \         ll add = int(rng() % 11) - 5;\n                index.rerooted_subtree(v,\
    \ root, [&](int l, int r) { seg.update(l, r, add); });\n                for (int\
    \ u : expected) values[u] += add;\n                ll sum = 0, oracle = 0;\n \
    \               index.rerooted_subtree(v, root, [&](int l, int r) { sum += seg.query(l,\
    \ r)[0]; });\n                for (int u : expected) oracle += values[u];\n  \
    \              assert(sum == oracle);\n                for (int u : order) {\n\
    \                    int a = u, b = v;\n                    while (depth[a] >\
    \ depth[b]) a = parent[a];\n                    while (depth[b] > depth[a]) b\
    \ = parent[b];\n                    while (a != b) { a = parent[a]; b = parent[b];\
    \ }\n                    assert(index.rerooted_lca(u, v, root) == a);\n      \
    \          }\n            }\n        }\n        assert(hld.id == ids && hld.par\
    \ == parents && hld.dep == depths);\n        for (int v = 0; v < n; ++v) assert(seg.query(hld.id[v],\
    \ hld.id[v] + 1)[0] == values[v]);\n    }\n}\n\nint main() {\n    self_check();\n\
    \    Scanner in;\n    Printer out;\n    int a, b;\n    in.read(a, b);\n    out.println(a\
    \ + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing ll = long long;\n#include \"../util/fastio.cpp\"\n\
    #include \"../tree/hld.cpp\"\n#include \"../datastructure/segmenttree/lazysegtree.cpp\"\
    \n\nstruct SumAdd {\n    using T = array<ll, 2>;\n    using L = ll;\n    static\
    \ T f(T a, T b) { return {a[0] + b[0], a[1] + b[1]}; }\n    static T g(T a, L\
    \ x) { return {a[0] + a[1] * x, a[1]}; }\n    static L h(L a, L b) { return a\
    \ + b; }\n    static T e() { return {0, 0}; }\n    static L l() { return 0; }\n\
    };\n\nvoid self_check() {\n    mt19937 rng(155);\n    for (int tc = 0; tc < 350;\
    \ ++tc) {\n        int n = 1 + rng() % 28;\n        HeavyLightDecomposition hld(n);\n\
    \        vector<vector<int>> g(n);\n        for (int v = 1; v < n; ++v) {\n  \
    \          if (tc % 2 && rng() % 4 == 0) continue;\n            int p = tc % 5\
    \ == 0 ? v - 1 : tc % 5 == 1 ? 0 : rng() % v;\n            hld.add_edge(p, v);\n\
    \            g[p].push_back(v);\n            g[v].push_back(p);\n        }\n \
    \       vector<int> seen(n), roots;\n        for (int v = 0; v < n; ++v) if (!seen[v])\
    \ {\n            vector<int> component{v};\n            seen[v] = 1;\n       \
    \     for (int i = 0; i < (int)component.size(); ++i) {\n                for (int\
    \ u : g[component[i]]) if (!seen[u]) {\n                    seen[u] = 1;\n   \
    \                 component.push_back(u);\n                }\n            }\n\
    \            roots.push_back(component[rng() % component.size()]);\n        }\n\
    \        shuffle(roots.begin(), roots.end(), rng);\n        hld.build(roots);\n\
    \        auto ids = hld.id, parents = hld.par, depths = hld.dep;\n        const\
    \ auto& index = hld;\n        vector<ll> values(n);\n        LazySegmentTree<SumAdd>\
    \ seg(n);\n        for (int v = 0; v < n; ++v) seg.set(hld.id[v], {0, 1});\n \
    \       seg.build();\n        for (int root = 0; root < n; ++root) {\n       \
    \     vector<int> parent(n, -2), depth(n), order{root};\n            parent[root]\
    \ = -1;\n            for (int i = 0; i < (int)order.size(); ++i) {\n         \
    \       int v = order[i];\n                for (int u : g[v]) if (u != parent[v])\
    \ {\n                    parent[u] = v;\n                    depth[u] = depth[v]\
    \ + 1;\n                    order.push_back(u);\n                }\n         \
    \   }\n            for (int v : order) {\n                vector<int> expected,\
    \ actual;\n                for (int u : order) {\n                    int x =\
    \ u;\n                    while (x != -1 && x != v) x = parent[x];\n         \
    \           if (x == v) expected.push_back(u);\n                }\n          \
    \      int calls = 0, previous = -1;\n                index.rerooted_subtree(v,\
    \ root, [&](int l, int r) {\n                    assert(0 <= l && l < r && r <=\
    \ n && previous <= l);\n                    previous = r;\n                  \
    \  ++calls;\n                    for (int i = l; i < r; ++i) actual.push_back(hld.id_inv[i]);\n\
    \                });\n                sort(expected.begin(), expected.end());\n\
    \                sort(actual.begin(), actual.end());\n                assert(actual\
    \ == expected && 1 <= calls && calls <= 2);\n                ll add = int(rng()\
    \ % 11) - 5;\n                index.rerooted_subtree(v, root, [&](int l, int r)\
    \ { seg.update(l, r, add); });\n                for (int u : expected) values[u]\
    \ += add;\n                ll sum = 0, oracle = 0;\n                index.rerooted_subtree(v,\
    \ root, [&](int l, int r) { sum += seg.query(l, r)[0]; });\n                for\
    \ (int u : expected) oracle += values[u];\n                assert(sum == oracle);\n\
    \                for (int u : order) {\n                    int a = u, b = v;\n\
    \                    while (depth[a] > depth[b]) a = parent[a];\n            \
    \        while (depth[b] > depth[a]) b = parent[b];\n                    while\
    \ (a != b) { a = parent[a]; b = parent[b]; }\n                    assert(index.rerooted_lca(u,\
    \ v, root) == a);\n                }\n            }\n        }\n        assert(hld.id\
    \ == ids && hld.par == parents && hld.dep == depths);\n        for (int v = 0;\
    \ v < n; ++v) assert(seg.query(hld.id[v], hld.id[v] + 1)[0] == values[v]);\n \
    \   }\n}\n\nint main() {\n    self_check();\n    Scanner in;\n    Printer out;\n\
    \    int a, b;\n    in.read(a, b);\n    out.println(a + b);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - tree/hld.cpp
  - datastructure/segmenttree/lazysegtree.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_hld_rerooted.test.cpp
  requiredBy: []
  timestamp: '2026-10-18 09:37:05+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_hld_rerooted.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_hld_rerooted.test.cpp
- /verify/test/yosupo_aplusb_hld_rerooted.test.cpp.html
title: test/yosupo_aplusb_hld_rerooted.test.cpp
---
