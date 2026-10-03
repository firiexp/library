---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: flow/dinic.cpp
    title: "Dinic\u6CD5(Dinic)"
  - icon: ':heavy_check_mark:'
    path: flow/project_selection_problem.cpp
    title: Project Selection Problem
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_project_selection_pair_profit.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing ll = long long;\ntemplate<class T> constexpr T INF\
    \ = numeric_limits<T>::max() / 32 * 15 + 208;\n#line 1 \"util/fastio.cpp\"\nusing\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"flow/dinic.cpp\"\
    \ntemplate<class T, bool directed>\nclass Dinic {\n    void bfs(int s){\n    \
    \    fill(level.begin(),level.end(), -1);\n        queue<int> Q;\n        level[s]\
    \ = 0;\n        Q.emplace(s);\n        while(!Q.empty()){\n            int v =\
    \ Q.front(); Q.pop();\n            for (auto &&e : G[v]){\n                if(e.cap\
    \ > 0 && level[e.to] < 0){\n                    level[e.to] = level[v] + 1;\n\
    \                    Q.emplace(e.to);\n                }\n            }\n    \
    \    }\n    }\n \n    T dfs(int v, int t, T f){\n        if(v == t) return f;\n\
    \        for(int &i = iter[v]; i < G[v].size(); i++){\n            edge &e = G[v][i];\n\
    \            if(e.cap > 0 && level[v] < level[e.to]){\n                T d = dfs(e.to,\
    \ t, min(f,  e.cap));\n                if(d == 0) continue;\n                e.cap\
    \ -= d;\n                G[e.to][e.rev].cap += d;\n                return d;\n\
    \            }\n        }\n        return 0;\n    }\npublic:\n    struct edge\
    \ {\n        int to{}; T cap; int rev{};\n        edge() = default;\n        edge(int\
    \ to, T cap, int rev) : to(to), cap(cap), rev(rev) {}\n    };\n \n    vector<vector<edge>>\
    \ G;\n    vector<int> level, iter;\n    Dinic() = default;\n    explicit Dinic(int\
    \ n) : G(n), level(n), iter(n) {}\n \n    void add_edge(int from, int to, T cap){\n\
    \        int from_id = G[from].size(), to_id = G[to].size();\n        if(from\
    \ == to) ++to_id;\n        G[from].emplace_back(to, cap, to_id);\n        G[to].emplace_back(from,\
    \ directed ? 0 : cap, from_id);\n    }\n \n \n    T flow(int s, int t, T lim =\
    \ INF<T>){\n        T ret = 0;\n        while(true) {\n            bfs(s);\n \
    \           if(level[t] < 0 || lim == 0) break;\n            fill(iter.begin(),iter.end(),\
    \ 0);\n            while(true){\n                T f = dfs(s, t, lim);\n     \
    \           if(f == 0) break;\n                ret += f;\n                lim\
    \ -= f;\n            }\n        }\n        return ret;\n    }\n};\n\n/**\n * @brief\
    \ Dinic\u6CD5(Dinic)\n */\n#line 2 \"flow/project_selection_problem.cpp\"\n\n\
    template<class T>\nclass ProjectSelectionProblem {\n    int n;\n    T base_score{};\n\
    \    vector<T> weight;\n    vector<tuple<int, int, T>> penalty;\n    vector<char>\
    \ forced_true, forced_false;\n    vector<int> selected;\n\npublic:\n    ProjectSelectionProblem()\
    \ : n(0) {}\n    explicit ProjectSelectionProblem(int n)\n        : n(n), base_score(0),\
    \ weight(n, 0), forced_true(n, false), forced_false(n, false), selected(n, 0)\
    \ {}\n\n    int add_vertex() {\n        weight.emplace_back(0);\n        forced_true.emplace_back(false);\n\
    \        forced_false.emplace_back(false);\n        selected.emplace_back(0);\n\
    \        return n++;\n    }\n\n    int size() const {\n        return n;\n   \
    \ }\n\n    void add_true_profit(int v, T x) {\n        weight[v] += x;\n    }\n\
    \n    void add_false_profit(int v, T x) {\n        base_score += x;\n        weight[v]\
    \ -= x;\n    }\n\n    void add_penalty(int x, int y, T cost) {\n        penalty.emplace_back(x,\
    \ y, cost);\n    }\n\n    void add_pair_profit(int u, int v, T p00, T p01, T p10,\
    \ T p11) {\n        assert(p00 + p11 >= p01 + p10);\n        T cost = p00 + p11\
    \ - p01 - p10;\n        base_score += p00;\n        add_true_profit(u, p11 - p01);\n\
    \        add_true_profit(v, p01 - p00);\n        add_penalty(u, v, cost);\n  \
    \  }\n\n    void add_if_then(int x, int y) {\n        add_penalty(x, y, INF<T>);\n\
    \    }\n\n    void force_true(int v) {\n        forced_true[v] = true;\n    }\n\
    \n    void force_false(int v) {\n        forced_false[v] = true;\n    }\n\n  \
    \  T solve() {\n        int s = n, t = n + 1;\n        Dinic<T, true> mf(n + 2);\n\
    \        T offset = base_score;\n        for (int v = 0; v < n; ++v) {\n     \
    \       if (weight[v] >= 0) {\n                offset += weight[v];\n        \
    \        mf.add_edge(s, v, weight[v]);\n            } else {\n               \
    \ mf.add_edge(v, t, -weight[v]);\n            }\n            if (forced_true[v])\
    \ mf.add_edge(s, v, INF<T>);\n            if (forced_false[v]) mf.add_edge(v,\
    \ t, INF<T>);\n        }\n        for (auto&& [x, y, cost] : penalty) {\n    \
    \        mf.add_edge(x, y, cost);\n        }\n        T cut = mf.flow(s, t);\n\
    \n        fill(selected.begin(), selected.end(), 0);\n        queue<int> q;\n\
    \        q.emplace(s);\n        vector<int> vis(n + 2, 0);\n        vis[s] = 1;\n\
    \        while (!q.empty()) {\n            int v = q.front();\n            q.pop();\n\
    \            for (auto&& e : mf.G[v]) {\n                if (e.cap <= 0 || vis[e.to])\
    \ continue;\n                vis[e.to] = 1;\n                q.emplace(e.to);\n\
    \            }\n        }\n        for (int v = 0; v < n; ++v) {\n           \
    \ selected[v] = vis[v];\n        }\n        return offset - cut;\n    }\n\n  \
    \  const vector<int>& get_selected() const {\n        return selected;\n    }\n\
    };\n\n/**\n * @brief Project Selection Problem\n */\n#line 9 \"test/yosupo_aplusb_project_selection_pair_profit.test.cpp\"\
    \n\ntemplate<class Score>\nvoid check(ProjectSelectionProblem<ll> &psp, Score\
    \ score, int fixed = -1) {\n    int n = psp.size();\n    ll best = LLONG_MIN;\n\
    \    for (int mask = 0; mask < (1 << n); ++mask)\n        if (fixed == -1 || mask\
    \ == fixed) best = max(best, score(mask));\n    for (int repeat = 0; repeat <\
    \ 2; ++repeat) {\n        assert(psp.solve() == best);\n        const auto &selected\
    \ = psp.get_selected();\n        int mask = 0;\n        for (int i = 0; i < n;\
    \ ++i) mask |= selected[i] << i;\n        assert(fixed == -1 || mask == fixed);\n\
    \        assert(score(mask) == best);\n    }\n}\n\nvoid self_check() {\n    for\
    \ (ll a = -2; a <= 2; ++a) for (ll b = -2; b <= 2; ++b)\n    for (ll c = -2; c\
    \ <= 2; ++c) for (ll d = -2; d <= 2; ++d) {\n        if (a + d < b + c) continue;\n\
    \        array<ll, 4> table{a, b, c, d};\n        for (int fixed = -1; fixed <\
    \ 4; ++fixed) {\n            ProjectSelectionProblem<ll> psp(2);\n           \
    \ psp.add_pair_profit(0, 1, a, b, c, d);\n            if (fixed != -1) for (int\
    \ v = 0; v < 2; ++v) {\n                if ((fixed >> v) & 1) psp.force_true(v);\n\
    \                else psp.force_false(v);\n            }\n            check(psp,\
    \ [&](int mask) { return table[2 * (mask & 1) + ((mask >> 1) & 1)]; }, fixed);\n\
    \        }\n        ProjectSelectionProblem<ll> same(1);\n        same.add_pair_profit(0,\
    \ 0, a, b, c, d);\n        check(same, [&](int mask) { return mask ? d : a; });\n\
    \    }\n    mt19937 rng(66);\n    for (int tc = 0; tc < 2000; ++tc) {\n      \
    \  int n = 1 + rng() % 6;\n        ProjectSelectionProblem<ll> psp(n);\n     \
    \   vector<ll> yes(n), no(n);\n        for (int i = 0; i < n; ++i) {\n       \
    \     yes[i] = int(rng() % 11) - 5;\n            no[i] = int(rng() % 11) - 5;\n\
    \            psp.add_true_profit(i, yes[i]);\n            psp.add_false_profit(i,\
    \ no[i]);\n        }\n        vector<tuple<int, int, array<ll, 4>>> terms;\n \
    \       auto score = [&](int mask) {\n            ll sum = 0;\n            for\
    \ (int i = 0; i < n; ++i) sum += (mask >> i) & 1 ? yes[i] : no[i];\n         \
    \   for (auto [u, v, p] : terms) sum += p[2 * ((mask >> u) & 1) + ((mask >> v)\
    \ & 1)];\n            return sum;\n        };\n        for (int i = 0; i < 8;\
    \ ++i) {\n            int u = rng() % n, v = rng() % n;\n            array<ll,\
    \ 4> p;\n            for (auto &x : p) x = int(rng() % 11) - 5;\n            p[3]\
    \ = max(p[3], p[1] + p[2] - p[0]);\n            psp.add_pair_profit(u, v, p[0],\
    \ p[1], p[2], p[3]);\n            terms.emplace_back(u, v, p);\n            if\
    \ (i == 3 || i == 7) check(psp, score);\n        }\n    }\n}\n\nint main() {\n\
    \    self_check();\n    Scanner sc;\n    Printer pr;\n    int a, b;\n    sc.read(a,\
    \ b);\n    pr.println(a + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing ll = long long;\ntemplate<class T> constexpr T INF\
    \ = numeric_limits<T>::max() / 32 * 15 + 208;\n#include \"../util/fastio.cpp\"\
    \n#include \"../flow/project_selection_problem.cpp\"\n\ntemplate<class Score>\n\
    void check(ProjectSelectionProblem<ll> &psp, Score score, int fixed = -1) {\n\
    \    int n = psp.size();\n    ll best = LLONG_MIN;\n    for (int mask = 0; mask\
    \ < (1 << n); ++mask)\n        if (fixed == -1 || mask == fixed) best = max(best,\
    \ score(mask));\n    for (int repeat = 0; repeat < 2; ++repeat) {\n        assert(psp.solve()\
    \ == best);\n        const auto &selected = psp.get_selected();\n        int mask\
    \ = 0;\n        for (int i = 0; i < n; ++i) mask |= selected[i] << i;\n      \
    \  assert(fixed == -1 || mask == fixed);\n        assert(score(mask) == best);\n\
    \    }\n}\n\nvoid self_check() {\n    for (ll a = -2; a <= 2; ++a) for (ll b =\
    \ -2; b <= 2; ++b)\n    for (ll c = -2; c <= 2; ++c) for (ll d = -2; d <= 2; ++d)\
    \ {\n        if (a + d < b + c) continue;\n        array<ll, 4> table{a, b, c,\
    \ d};\n        for (int fixed = -1; fixed < 4; ++fixed) {\n            ProjectSelectionProblem<ll>\
    \ psp(2);\n            psp.add_pair_profit(0, 1, a, b, c, d);\n            if\
    \ (fixed != -1) for (int v = 0; v < 2; ++v) {\n                if ((fixed >> v)\
    \ & 1) psp.force_true(v);\n                else psp.force_false(v);\n        \
    \    }\n            check(psp, [&](int mask) { return table[2 * (mask & 1) + ((mask\
    \ >> 1) & 1)]; }, fixed);\n        }\n        ProjectSelectionProblem<ll> same(1);\n\
    \        same.add_pair_profit(0, 0, a, b, c, d);\n        check(same, [&](int\
    \ mask) { return mask ? d : a; });\n    }\n    mt19937 rng(66);\n    for (int\
    \ tc = 0; tc < 2000; ++tc) {\n        int n = 1 + rng() % 6;\n        ProjectSelectionProblem<ll>\
    \ psp(n);\n        vector<ll> yes(n), no(n);\n        for (int i = 0; i < n; ++i)\
    \ {\n            yes[i] = int(rng() % 11) - 5;\n            no[i] = int(rng()\
    \ % 11) - 5;\n            psp.add_true_profit(i, yes[i]);\n            psp.add_false_profit(i,\
    \ no[i]);\n        }\n        vector<tuple<int, int, array<ll, 4>>> terms;\n \
    \       auto score = [&](int mask) {\n            ll sum = 0;\n            for\
    \ (int i = 0; i < n; ++i) sum += (mask >> i) & 1 ? yes[i] : no[i];\n         \
    \   for (auto [u, v, p] : terms) sum += p[2 * ((mask >> u) & 1) + ((mask >> v)\
    \ & 1)];\n            return sum;\n        };\n        for (int i = 0; i < 8;\
    \ ++i) {\n            int u = rng() % n, v = rng() % n;\n            array<ll,\
    \ 4> p;\n            for (auto &x : p) x = int(rng() % 11) - 5;\n            p[3]\
    \ = max(p[3], p[1] + p[2] - p[0]);\n            psp.add_pair_profit(u, v, p[0],\
    \ p[1], p[2], p[3]);\n            terms.emplace_back(u, v, p);\n            if\
    \ (i == 3 || i == 7) check(psp, score);\n        }\n    }\n}\n\nint main() {\n\
    \    self_check();\n    Scanner sc;\n    Printer pr;\n    int a, b;\n    sc.read(a,\
    \ b);\n    pr.println(a + b);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - flow/project_selection_problem.cpp
  - flow/dinic.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_project_selection_pair_profit.test.cpp
  requiredBy: []
  timestamp: '2026-10-03 16:38:16+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_project_selection_pair_profit.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_project_selection_pair_profit.test.cpp
- /verify/test/yosupo_aplusb_project_selection_pair_profit.test.cpp.html
title: test/yosupo_aplusb_project_selection_pair_profit.test.cpp
---
