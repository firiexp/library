---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/minimum_cost_b_flow.cpp
    title: "\u6700\u5C0F\u8CBB\u7528b-flow(Min-Cost b-Flow)"
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_min_cost_b_flow.test.cpp\"\n#define PROBLEM\
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
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    static constexpr int DEFAULT_DOUBLE_PRECISION = 15;\n    char buf[BUFSIZE];\n\
    \    int idx;\n    bool interactive;\n    string number_buf;\n    inline static\
    \ constexpr FastIoDigitTable table{};\n\n    Printer() : idx(0), interactive(isatty(fileno(stdout)))\
    \ {}\n    ~Printer() { flush(); }\n\n    inline void flush() {\n        if (idx)\
    \ {\n            fwrite(buf, 1, idx, stdout);\n            idx = 0;\n        }\n\
    \    }\n\n    inline void pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n\
    \        buf[idx++] = c;\n        if (interactive && c == '\\n') flush();\n  \
    \  }\n\n    inline void print_range(const char *s, size_t n) {\n        size_t\
    \ pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n\
    \            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n         \
    \   memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n     \
    \       pos += chunk;\n        }\n    }\n\n    void print(const char *s) {\n \
    \       print_range(s, strlen(s));\n    }\n\n    void print(const string &s) {\n\
    \        print_range(s.data(), s.size());\n    }\n\n    void print(char c) {\n\
    \        pc(c);\n    }\n\n    void print(bool b) {\n        pc(char('0' + (b ?\
    \ 1 : 0)));\n    }\n\n    inline char *write_top(char *out, unsigned x) {\n  \
    \      if (x >= 1000) {\n            memcpy(out, table.num + (x << 2), 4);\n \
    \           return out + 4;\n        }\n        if (x >= 100) {\n            memcpy(out,\
    \ table.num + (x << 2) + 1, 3);\n            return out + 3;\n        }\n    \
    \    if (x >= 10) {\n            unsigned q = (x * 205) >> 11;\n            out[0]\
    \ = char('0' + q);\n            out[1] = char('0' + (x - q * 10));\n         \
    \   return out + 2;\n        }\n        *out = char('0' + x);\n        return\
    \ out + 1;\n    }\n\n    inline void write_four(char *out, unsigned x) {\n   \
    \     memcpy(out, table.num + (x << 2), 4);\n    }\n\n    inline void write_eight(char\
    \ *out, unsigned x) {\n        unsigned hi = x / 10000;\n        unsigned lo =\
    \ x - hi * 10000;\n        write_four(out, hi);\n        write_four(out + 4, lo);\n\
    \    }\n\n    inline char *write_u32(char *out, unsigned x) {\n        if (x >=\
    \ 100000000) {\n            unsigned hi = x / 100000000;\n            unsigned\
    \ lo = x - hi * 100000000;\n            out = write_top(out, hi);\n          \
    \  write_eight(out, lo);\n            return out + 8;\n        }\n        if (x\
    \ >= 10000) {\n            unsigned hi = x / 10000;\n            unsigned lo =\
    \ x - hi * 10000;\n            out = write_top(out, hi);\n            write_four(out,\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"graph/minimum_cost_b_flow.cpp\"\
    \ntemplate<class Flow, class Cost>\nstruct MinimumCostBFlow {\n    using Sum =\
    \ __int128_t;\n    struct Edge {\n        int from, to, rev;\n        Flow flow,\
    \ cap;\n        Cost cost;\n\n        Flow residual_cap() const {\n          \
    \  return cap - flow;\n        }\n    };\n\n    struct EdgeRef {\n        int\
    \ from, idx;\n    };\n\n    int n;\n    vector<vector<Edge>> g;\n    vector<Flow>\
    \ b;\n    vector<EdgeRef> edges;\n    vector<Cost> potential;\n    bool potential_valid\
    \ = false;\n\n    explicit MinimumCostBFlow(int n) : n(n), g(n), b(n, 0), potential(n,\
    \ 0) {}\n\n    void add_supply(int v, Flow x) {\n        potential_valid = false;\n\
    \        b[v] += x;\n    }\n\n    void add_demand(int v, Flow x) {\n        potential_valid\
    \ = false;\n        b[v] -= x;\n    }\n\n    int add_edge(int from, int to, Flow\
    \ lower, Flow upper, Cost cost) {\n        assert(lower <= upper);\n        potential_valid\
    \ = false;\n        int idx = (int)g[from].size();\n        int rev = from ==\
    \ to ? idx + 1 : (int)g[to].size();\n        g[from].push_back({from, to, rev,\
    \ 0, upper, cost});\n        g[to].push_back({to, from, idx, 0, -lower, -cost});\n\
    \        edges.push_back({from, idx});\n        return (int)edges.size() - 1;\n\
    \    }\n\n    Edge& rev_edge(const Edge& e) {\n        return g[e.to][e.rev];\n\
    \    }\n\n    const Edge& get_edge(int i) const {\n        return g[edges[i].from][edges[i].idx];\n\
    \    }\n\n    vector<Flow> get_flows() const {\n        vector<Flow> ret(edges.size());\n\
    \        for (int i = 0; i < (int)edges.size(); ++i) ret[i] = get_edge(i).flow;\n\
    \        return ret;\n    }\n\n    vector<Cost> get_potential() const {\n    \
    \    if (potential_valid) return potential;\n        vector<Cost> ret(n, 0);\n\
    \        for (int iter = 0; iter < n; ++iter) {\n            bool updated = false;\n\
    \            for (int v = 0; v < n; ++v) {\n                for (auto&& e : g[v])\
    \ {\n                    if(e.residual_cap() <= 0) continue;\n               \
    \     if(ret[e.to] > ret[e.from] + e.cost) {\n                        ret[e.to]\
    \ = ret[e.from] + e.cost;\n                        updated = true;\n         \
    \           }\n                }\n            }\n            if(!updated) break;\n\
    \        }\n        return ret;\n    }\n\n    pair<bool, Sum> solve() {\n    \
    \    potential_valid = false;\n        const Cost unreachable = numeric_limits<Cost>::max();\n\
    \        vector<Cost> dist(n);\n        vector<Edge*> parent(n);\n        vector<int>\
    \ excess, deficit;\n        priority_queue<pair<Cost, int>, vector<pair<Cost,\
    \ int>>, greater<pair<Cost, int>>> pq;\n        Cost farthest = 0;\n\n       \
    \ auto push = [&](Edge& e, Flow amount) {\n            e.flow += amount;\n   \
    \         rev_edge(e).flow -= amount;\n        };\n        auto residual_cost\
    \ = [&](const Edge& e) {\n            return e.cost + potential[e.from] - potential[e.to];\n\
    \        };\n\n        auto saturate_negative = [&](Flow delta) {\n          \
    \  excess.clear();\n            deficit.clear();\n            for (auto&& es :\
    \ g) {\n                for (auto&& e : es) {\n                    Flow rcap =\
    \ e.residual_cap();\n                    if(rcap < delta) continue;\n        \
    \            if(residual_cost(e) < 0) {\n                        push(e, rcap);\n\
    \                        b[e.from] -= rcap;\n                        b[e.to] +=\
    \ rcap;\n                    }\n                }\n            }\n           \
    \ for (int v = 0; v < n; ++v) {\n                if(b[v] > 0) excess.push_back(v);\n\
    \                if(b[v] < 0) deficit.push_back(v);\n            }\n        };\n\
    \n        auto dual = [&](Flow delta) {\n            fill(dist.begin(), dist.end(),\
    \ unreachable);\n            fill(parent.begin(), parent.end(), nullptr);\n\n\
    \            excess.erase(remove_if(excess.begin(), excess.end(), [&](int v) {\n\
    \                return b[v] < delta;\n            }), excess.end());\n      \
    \      deficit.erase(remove_if(deficit.begin(), deficit.end(), [&](int v) {\n\
    \                return b[v] > -delta;\n            }), deficit.end());\n\n  \
    \          while(!pq.empty()) pq.pop();\n            for (int v : excess) {\n\
    \                dist[v] = 0;\n                pq.emplace(0, v);\n           \
    \ }\n\n            farthest = 0;\n            int reached = 0;\n            while(!pq.empty())\
    \ {\n                auto [d, v] = pq.top();\n                pq.pop();\n    \
    \            if(dist[v] != d) continue;\n                farthest = d;\n     \
    \           if(b[v] <= -delta) ++reached;\n                if(reached >= (int)deficit.size())\
    \ break;\n                for (auto&& e : g[v]) {\n                    if(e.residual_cap()\
    \ < delta) continue;\n                    Cost nd = d + residual_cost(e);\n  \
    \                  if(nd >= dist[e.to]) continue;\n                    dist[e.to]\
    \ = nd;\n                    parent[e.to] = &e;\n                    pq.emplace(nd,\
    \ e.to);\n                }\n            }\n\n            for (int v = 0; v <\
    \ n; ++v) {\n                potential[v] += min(dist[v], farthest);\n       \
    \     }\n            return reached > 0;\n        };\n\n        auto primal =\
    \ [&](Flow delta) {\n            for (int t : deficit) {\n                if(dist[t]\
    \ > farthest) continue;\n                Flow f = -b[t];\n                int\
    \ v = t;\n                while(parent[v] != nullptr && f >= delta) {\n      \
    \              f = min(f, parent[v]->residual_cap());\n                    v =\
    \ parent[v]->from;\n                }\n                f = min(f, b[v]);\n   \
    \             if(f < delta) continue;\n                v = t;\n              \
    \  while(parent[v] != nullptr) {\n                    Edge& e = *parent[v];\n\
    \                    push(e, f);\n                    int u = e.from;\n      \
    \              parent[v] = nullptr;\n                    v = u;\n            \
    \    }\n                b[t] += f;\n                b[v] -= f;\n            }\n\
    \        };\n\n        for (auto&& es : g) {\n            for (auto&& e : es)\
    \ {\n                Flow rcap = e.residual_cap();\n                if(rcap <\
    \ 0) {\n                    push(e, rcap);\n                    b[e.from] -= rcap;\n\
    \                    b[e.to] += rcap;\n                }\n            }\n    \
    \    }\n\n        Flow max_cap = 1;\n        for (auto&& es : g) {\n         \
    \   for (auto&& e : es) {\n                max_cap = max(max_cap, e.residual_cap());\n\
    \            }\n        }\n        Flow delta = 1;\n        while(delta <= max_cap\
    \ / 2) delta <<= 1;\n        for (; delta > 0; delta >>= 1) {\n            saturate_negative(delta);\n\
    \            while(dual(delta)) primal(delta);\n        }\n\n        Sum value\
    \ = 0;\n        bool ok = true;\n        for (int v = 0; v < n; ++v) {\n     \
    \       if(b[v] != 0) ok = false;\n        }\n        for (int i = 0; i < (int)edges.size();\
    \ ++i) {\n            auto&& e = get_edge(i);\n            value += (Sum)e.flow\
    \ * (Sum)e.cost;\n        }\n        potential_valid = ok;\n        return {ok,\
    \ value};\n    }\n};\n\n/**\n * @brief \u6700\u5C0F\u8CBB\u7528b-flow(Min-Cost\
    \ b-Flow)\n */\n#line 8 \"test/yosupo_aplusb_min_cost_b_flow.test.cpp\"\n\nstruct\
    \ InputEdge { int from, to, lower, upper, cost; };\n\nvoid check_dual(const MinimumCostBFlow<ll,\
    \ ll> &g) {\n    auto potential = g.get_potential();\n    assert((int)potential.size()\
    \ == g.n);\n    for (const auto &es : g.g) for (const auto &e : es)\n        if\
    \ (e.residual_cap() > 0) assert(e.cost + potential[e.from] - potential[e.to] >=\
    \ 0);\n}\n\nvoid check(const vector<ll> &supply, const vector<InputEdge> &edges)\
    \ {\n    int n = supply.size();\n    MinimumCostBFlow<ll, ll> g(n);\n    for (int\
    \ v = 0; v < n; ++v) g.add_supply(v, supply[v]);\n    for (auto e : edges) g.add_edge(e.from,\
    \ e.to, e.lower, e.upper, e.cost);\n    ll best = LLONG_MAX;\n    vector<ll> balance(n);\n\
    \    auto enumerate = [&](auto &&self, int i, ll cost) -> void {\n        if (i\
    \ == (int)edges.size()) {\n            if (balance == supply) best = min(best,\
    \ cost);\n            return;\n        }\n        auto e = edges[i];\n       \
    \ for (int f = e.lower; f <= e.upper; ++f) {\n            balance[e.from] += f;\n\
    \            balance[e.to] -= f;\n            self(self, i + 1, cost + f * e.cost);\n\
    \            balance[e.from] -= f;\n            balance[e.to] += f;\n        }\n\
    \    };\n    enumerate(enumerate, 0, 0);\n    for (int repeat = 0; repeat < 2;\
    \ ++repeat) {\n        auto [ok, cost] = g.solve();\n        assert(ok == (best\
    \ != LLONG_MAX));\n        if (!ok) break;\n        assert(cost == best);\n  \
    \      auto flow = g.get_flows();\n        assert(flow.size() == edges.size());\n\
    \        fill(balance.begin(), balance.end(), 0);\n        ll actual = 0;\n  \
    \      for (int i = 0; i < (int)edges.size(); ++i) {\n            auto e = edges[i];\n\
    \            assert(e.lower <= flow[i] && flow[i] <= e.upper);\n            balance[e.from]\
    \ += flow[i];\n            balance[e.to] -= flow[i];\n            actual += flow[i]\
    \ * e.cost;\n        }\n        assert(balance == supply && actual == best);\n\
    \        auto before = g.get_flows();\n        check_dual(g);\n        check_dual(g);\n\
    \        assert(g.get_flows() == before);\n    }\n}\n\nvoid self_check() {\n \
    \   check({1, -1}, {{0, 1, 0, 1, 7}});\n    check({0, 0}, {{0, 1, 0, 1, -1}, {1,\
    \ 0, 0, 1, 0}});\n    check({}, {});\n    check({0}, {});\n    check({1}, {});\n\
    \    check({2, -2}, {{0, 1, 2, 2, 3}});\n    check({0}, {{0, 0, -2, 1, -4}});\n\
    \    check({-1, 1}, {{0, 1, -2, -1, 3}});\n    check({2, -2}, {{0, 1, 0, 1, -1}});\n\
    \    MinimumCostBFlow<ll, ll> g(3);\n    g.add_edge(0, 1, 0, 1, 7);\n    check_dual(g);\n\
    \    g.add_supply(0, 1);\n    g.add_demand(1, 1);\n    assert(g.solve() == make_pair(true,\
    \ (__int128_t)7));\n    check_dual(g);\n    g.add_edge(0, 2, 0, 1, -9);\n    check_dual(g);\n\
    \    assert(g.solve() == make_pair(true, (__int128_t)7));\n    g.add_supply(0,\
    \ 1);\n    check_dual(g);\n    assert(!g.solve().first);\n    check_dual(g);\n\
    \    g.add_demand(2, 1);\n    check_dual(g);\n    assert(g.solve() == make_pair(true,\
    \ (__int128_t)-2));\n    check_dual(g);\n    g.add_edge(1, 0, 0, 1, -10);\n  \
    \  assert(g.solve() == make_pair(true, (__int128_t)-2));\n    check_dual(g);\n\
    \n    mt19937 random(20261002);\n    for (int tc = 0; tc < 100000; ++tc) {\n \
    \       int n = 1 + random() % 5, m = random() % 8;\n        vector<ll> supply(n);\n\
    \        vector<InputEdge> edges;\n        for (int i = 0; i < m; ++i) {\n   \
    \         int u = random() % n, v = random() % n;\n            int lower = int(random()\
    \ % 5) - 2, upper = lower + random() % 4;\n            edges.push_back({u, v,\
    \ lower, upper, int(random() % 9) - 4});\n            int f = lower + random()\
    \ % (upper - lower + 1);\n            supply[u] += f;\n            supply[v] -=\
    \ f;\n        }\n        if (tc % 3 == 0) {\n            ++supply[random() % n];\n\
    \            --supply[random() % n];\n        }\n        if (tc % 7 == 0) ++supply[random()\
    \ % n];\n        check(supply, edges);\n    }\n}\n\nint main() {\n    self_check();\n\
    \    Scanner sc;\n    Printer pr;\n    int a, b;\n    sc.read(a, b);\n    pr.println(a\
    \ + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing ll = long long;\n#include \"../util/fastio.cpp\"\n\
    #include \"../graph/minimum_cost_b_flow.cpp\"\n\nstruct InputEdge { int from,\
    \ to, lower, upper, cost; };\n\nvoid check_dual(const MinimumCostBFlow<ll, ll>\
    \ &g) {\n    auto potential = g.get_potential();\n    assert((int)potential.size()\
    \ == g.n);\n    for (const auto &es : g.g) for (const auto &e : es)\n        if\
    \ (e.residual_cap() > 0) assert(e.cost + potential[e.from] - potential[e.to] >=\
    \ 0);\n}\n\nvoid check(const vector<ll> &supply, const vector<InputEdge> &edges)\
    \ {\n    int n = supply.size();\n    MinimumCostBFlow<ll, ll> g(n);\n    for (int\
    \ v = 0; v < n; ++v) g.add_supply(v, supply[v]);\n    for (auto e : edges) g.add_edge(e.from,\
    \ e.to, e.lower, e.upper, e.cost);\n    ll best = LLONG_MAX;\n    vector<ll> balance(n);\n\
    \    auto enumerate = [&](auto &&self, int i, ll cost) -> void {\n        if (i\
    \ == (int)edges.size()) {\n            if (balance == supply) best = min(best,\
    \ cost);\n            return;\n        }\n        auto e = edges[i];\n       \
    \ for (int f = e.lower; f <= e.upper; ++f) {\n            balance[e.from] += f;\n\
    \            balance[e.to] -= f;\n            self(self, i + 1, cost + f * e.cost);\n\
    \            balance[e.from] -= f;\n            balance[e.to] += f;\n        }\n\
    \    };\n    enumerate(enumerate, 0, 0);\n    for (int repeat = 0; repeat < 2;\
    \ ++repeat) {\n        auto [ok, cost] = g.solve();\n        assert(ok == (best\
    \ != LLONG_MAX));\n        if (!ok) break;\n        assert(cost == best);\n  \
    \      auto flow = g.get_flows();\n        assert(flow.size() == edges.size());\n\
    \        fill(balance.begin(), balance.end(), 0);\n        ll actual = 0;\n  \
    \      for (int i = 0; i < (int)edges.size(); ++i) {\n            auto e = edges[i];\n\
    \            assert(e.lower <= flow[i] && flow[i] <= e.upper);\n            balance[e.from]\
    \ += flow[i];\n            balance[e.to] -= flow[i];\n            actual += flow[i]\
    \ * e.cost;\n        }\n        assert(balance == supply && actual == best);\n\
    \        auto before = g.get_flows();\n        check_dual(g);\n        check_dual(g);\n\
    \        assert(g.get_flows() == before);\n    }\n}\n\nvoid self_check() {\n \
    \   check({1, -1}, {{0, 1, 0, 1, 7}});\n    check({0, 0}, {{0, 1, 0, 1, -1}, {1,\
    \ 0, 0, 1, 0}});\n    check({}, {});\n    check({0}, {});\n    check({1}, {});\n\
    \    check({2, -2}, {{0, 1, 2, 2, 3}});\n    check({0}, {{0, 0, -2, 1, -4}});\n\
    \    check({-1, 1}, {{0, 1, -2, -1, 3}});\n    check({2, -2}, {{0, 1, 0, 1, -1}});\n\
    \    MinimumCostBFlow<ll, ll> g(3);\n    g.add_edge(0, 1, 0, 1, 7);\n    check_dual(g);\n\
    \    g.add_supply(0, 1);\n    g.add_demand(1, 1);\n    assert(g.solve() == make_pair(true,\
    \ (__int128_t)7));\n    check_dual(g);\n    g.add_edge(0, 2, 0, 1, -9);\n    check_dual(g);\n\
    \    assert(g.solve() == make_pair(true, (__int128_t)7));\n    g.add_supply(0,\
    \ 1);\n    check_dual(g);\n    assert(!g.solve().first);\n    check_dual(g);\n\
    \    g.add_demand(2, 1);\n    check_dual(g);\n    assert(g.solve() == make_pair(true,\
    \ (__int128_t)-2));\n    check_dual(g);\n    g.add_edge(1, 0, 0, 1, -10);\n  \
    \  assert(g.solve() == make_pair(true, (__int128_t)-2));\n    check_dual(g);\n\
    \n    mt19937 random(20261002);\n    for (int tc = 0; tc < 100000; ++tc) {\n \
    \       int n = 1 + random() % 5, m = random() % 8;\n        vector<ll> supply(n);\n\
    \        vector<InputEdge> edges;\n        for (int i = 0; i < m; ++i) {\n   \
    \         int u = random() % n, v = random() % n;\n            int lower = int(random()\
    \ % 5) - 2, upper = lower + random() % 4;\n            edges.push_back({u, v,\
    \ lower, upper, int(random() % 9) - 4});\n            int f = lower + random()\
    \ % (upper - lower + 1);\n            supply[u] += f;\n            supply[v] -=\
    \ f;\n        }\n        if (tc % 3 == 0) {\n            ++supply[random() % n];\n\
    \            --supply[random() % n];\n        }\n        if (tc % 7 == 0) ++supply[random()\
    \ % n];\n        check(supply, edges);\n    }\n}\n\nint main() {\n    self_check();\n\
    \    Scanner sc;\n    Printer pr;\n    int a, b;\n    sc.read(a, b);\n    pr.println(a\
    \ + b);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - graph/minimum_cost_b_flow.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_min_cost_b_flow.test.cpp
  requiredBy: []
  timestamp: '2026-10-03 16:59:05+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_min_cost_b_flow.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_min_cost_b_flow.test.cpp
- /verify/test/yosupo_aplusb_min_cost_b_flow.test.cpp.html
title: test/yosupo_aplusb_min_cost_b_flow.test.cpp
---
