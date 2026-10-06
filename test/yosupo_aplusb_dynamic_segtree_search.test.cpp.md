---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/segmenttree/dynamic_segtree.cpp
    title: Dynamic Segment Tree
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_dynamic_segtree_search.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing ll = long long;\n#line 1 \"util/fastio.cpp\"\nusing\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"datastructure/segmenttree/dynamic_segtree.cpp\"\
    \ntemplate <class M>\nstruct DynamicSegmentTree{\n    using T = typename M::T;\n\
    \    struct Node{\n        T val;\n        int l, r;\n    };\n\n    long long\
    \ n{};\n    vector<Node> node;\n    int root;\n\n    explicit DynamicSegmentTree(long\
    \ long n): n(n), root(-1) {}\n\n    void reserve(size_t sz){\n        node.reserve(sz);\n\
    \    }\n\n    void update(long long k, const T &x){\n        if(n == 0) return;\n\
    \        update_(root, k, x, 0, n);\n    }\n\n    void add(long long k, const\
    \ T &x){\n        if(n == 0) return;\n        add_(root, k, x, 0, n);\n    }\n\
    \n    T query(long long a, long long b) const {\n        if(n == 0 || b <= a)\
    \ return M::e();\n        return query_(root, a, b, 0, n);\n    }\n\n    T get(long\
    \ long k) const { return query(k, k+1); }\n    T operator[](const long long &k)\
    \ const { return get(k); }\n\n    template<class F>\n    long long search_right(long\
    \ long l, F cond) const {\n        T acc = M::e();\n        return search_right_(root,\
    \ l, 0, n, acc, cond);\n    }\n\n    template<class F>\n    long long search_left(long\
    \ long r, F cond) const {\n        T acc = M::e();\n        return search_left_(root,\
    \ r, 0, n, acc, cond);\n    }\n\nprivate:\n    template<class F>\n    long long\
    \ search_right_(int id, long long a, long long l, long long r, T &acc, F &cond)\
    \ const {\n        if(id == -1 || r <= a) return n;\n        if(a <= l){\n   \
    \         T next = M::f(acc, node[id].val);\n            if(cond(next)){\n   \
    \             acc = move(next);\n                return n;\n            }\n  \
    \          if(r-l == 1) return l;\n        }\n        long long m = l + ((r-l)>>1);\n\
    \        long long result = search_right_(node[id].l, a, l, m, acc, cond);\n \
    \       if(result != n) return result;\n        return search_right_(node[id].r,\
    \ a, m, r, acc, cond);\n    }\n\n    template<class F>\n    long long search_left_(int\
    \ id, long long a, long long l, long long r, T &acc, F &cond) const {\n      \
    \  if(id == -1 || a <= l) return 0;\n        if(r <= a){\n            T next =\
    \ M::f(node[id].val, acc);\n            if(cond(next)){\n                acc =\
    \ move(next);\n                return 0;\n            }\n            if(r-l ==\
    \ 1) return r;\n        }\n        long long m = l + ((r-l)>>1);\n        long\
    \ long result = search_left_(node[id].r, a, m, r, acc, cond);\n        if(result\
    \ != 0) return result;\n        return search_left_(node[id].l, a, l, m, acc,\
    \ cond);\n    }\n\n    int make_node(const T &v, int l, int r){\n        node.push_back({v,\
    \ l, r});\n        return (int)node.size()-1;\n    }\n\n    void update_(int &id,\
    \ long long k, const T &x, long long l, long long r){\n        if(id == -1) id\
    \ = make_node(M::e(), -1, -1);\n        if(l+1 == r){\n            node[id].val\
    \ = x;\n            return;\n        }\n        long long m = l + ((r-l)>>1);\n\
    \        if(k < m){\n            int child = node[id].l;\n            update_(child,\
    \ k, x, l, m);\n            node[id].l = child;\n        }else{\n            int\
    \ child = node[id].r;\n            update_(child, k, x, m, r);\n            node[id].r\
    \ = child;\n        }\n        node[id].val = M::f(value(node[id].l), value(node[id].r));\n\
    \    }\n\n    void add_(int &id, long long k, const T &x, long long l, long long\
    \ r){\n        if(id == -1) id = make_node(M::e(), -1, -1);\n        if(l+1 ==\
    \ r){\n            node[id].val = M::f(node[id].val, x);\n            return;\n\
    \        }\n        long long m = l + ((r-l)>>1);\n        if(k < m){\n      \
    \      int child = node[id].l;\n            add_(child, k, x, l, m);\n       \
    \     node[id].l = child;\n        }else{\n            int child = node[id].r;\n\
    \            add_(child, k, x, m, r);\n            node[id].r = child;\n     \
    \   }\n        node[id].val = M::f(value(node[id].l), value(node[id].r));\n  \
    \  }\n\n    T query_(int id, long long a, long long b, long long l, long long\
    \ r) const {\n        if(id == -1 || r <= a || b <= l) return M::e();\n      \
    \  if(a <= l && r <= b) return node[id].val;\n        long long m = l + ((r-l)>>1);\n\
    \        return M::f(query_(node[id].l, a, b, l, m), query_(node[id].r, a, b,\
    \ m, r));\n    }\n\n    T value(int id) const {\n        return id == -1 ? M::e()\
    \ : node[id].val;\n    }\n};\n\n/*\nstruct Monoid{\n    using T = long long;\n\
    \    static T f(T a, T b) { return a + b; }\n    static T e() { return 0; }\n\
    };\n*/\n\n/**\n * @brief Dynamic Segment Tree\n */\n#line 8 \"test/yosupo_aplusb_dynamic_segtree_search.test.cpp\"\
    \n\nstruct Sum {\n    using T = ll;\n    static T e() { return 0; }\n    static\
    \ T f(T a, T b) { return a + b; }\n};\n\nstruct Concat {\n    using T = string;\n\
    \    static T e() { return \"\"; }\n    static T f(const T &a, const T &b) { return\
    \ a + b; }\n};\n\nvoid sum_check() {\n    mt19937 rng(113);\n    for (int n =\
    \ 0; n <= 65; ++n) {\n        DynamicSegmentTree<Sum> seg(n);\n        const auto\
    \ &view = seg;\n        vector<ll> a(n);\n        for (int step = 0; step < 300;\
    \ ++step) {\n            if (n && step % 3) {\n                int k = rng() %\
    \ n;\n                ll x = rng() % 20;\n                if (step % 2) {\n  \
    \                  seg.add(k, x);\n                    a[k] += x;\n          \
    \      } else {\n                    seg.update(k, x);\n                    a[k]\
    \ = x;\n                }\n            }\n            size_t nodes = seg.node.size();\n\
    \            for (int end : {0, int(rng() % (n + 1)), n}) {\n                ll\
    \ limit = rng() % 200, sum = 0;\n                int left = end, right = end;\n\
    \                while (left && sum + a[left - 1] <= limit) sum += a[--left];\n\
    \                sum = 0;\n                while (right < n && sum + a[right]\
    \ <= limit) sum += a[right++];\n                auto cond = [&](ll x) { return\
    \ x <= limit; };\n                assert(view.search_left(end, cond) == left);\n\
    \                assert(view.search_right(end, cond) == right);\n            \
    \    assert(view.query(left, right) == accumulate(a.begin() + left, a.begin()\
    \ + right, 0LL));\n            }\n            assert(seg.node.size() == nodes);\n\
    \        }\n    }\n}\n\nvoid noncommutative_check() {\n    mt19937 rng(114);\n\
    \    for (int n = 0; n <= 32; ++n) {\n        DynamicSegmentTree<Concat> seg(n);\n\
    \        vector<string> a(n);\n        for (int step = 0; step < 100; ++step)\
    \ {\n            if (n) {\n                int k = rng() % n;\n              \
    \  a[k] = rng() % 3 ? string(1, 'a' + rng() % 3) : \"\";\n                seg.update(k,\
    \ a[k]);\n            }\n            int limit = rng() % (n + 1);\n          \
    \  auto cond = [&](const string &x) {\n                return int(x.size()) <=\
    \ limit && x.find(\"ab\") == string::npos;\n            };\n            size_t\
    \ nodes = seg.node.size();\n            for (int end = 0; end <= n; ++end) {\n\
    \                int left = end, right = end;\n                string acc;\n \
    \               while (left && cond(a[left - 1] + acc)) acc = a[--left] + acc;\n\
    \                acc.clear();\n                while (right < n && cond(acc +\
    \ a[right])) acc += a[right++];\n                assert(seg.search_left(end, cond)\
    \ == left);\n                assert(seg.search_right(end, cond) == right);\n \
    \           }\n            assert(seg.node.size() == nodes);\n        }\n    }\n\
    }\n\nvoid sparse_check() {\n    for (ll n : {1LL, 1000000000000LL, LLONG_MAX})\
    \ {\n        DynamicSegmentTree<Sum> seg(n);\n        auto zero = [](ll x) { return\
    \ x == 0; };\n        for (ll end : {0LL, n / 2, n}) {\n            assert(seg.search_left(end,\
    \ zero) == 0);\n            assert(seg.search_right(end, zero) == n);\n      \
    \  }\n        assert(seg.node.empty());\n        seg.update(n - 1, 1);\n     \
    \   assert(seg.search_right(0, zero) == n - 1);\n        assert(seg.search_left(n,\
    \ zero) == n);\n        assert(seg.search_left(n - 1, zero) == 0);\n        assert(seg.search_right(n,\
    \ zero) == n);\n        seg.update(0, 1);\n        assert(seg.search_right(0,\
    \ zero) == 0);\n        assert(seg.search_left(n, [](ll x) { return x <= 2; })\
    \ == 0);\n        assert(seg.search_right(0, [](ll x) { return x <= 2; }) == n);\n\
    \    }\n}\n\nint main() {\n    sum_check();\n    noncommutative_check();\n   \
    \ sparse_check();\n    Scanner sc;\n    Printer pr;\n    int a, b;\n    sc.read(a,\
    \ b);\n    pr.println(a + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing ll = long long;\n#include \"../util/fastio.cpp\"\n\
    #include \"../datastructure/segmenttree/dynamic_segtree.cpp\"\n\nstruct Sum {\n\
    \    using T = ll;\n    static T e() { return 0; }\n    static T f(T a, T b) {\
    \ return a + b; }\n};\n\nstruct Concat {\n    using T = string;\n    static T\
    \ e() { return \"\"; }\n    static T f(const T &a, const T &b) { return a + b;\
    \ }\n};\n\nvoid sum_check() {\n    mt19937 rng(113);\n    for (int n = 0; n <=\
    \ 65; ++n) {\n        DynamicSegmentTree<Sum> seg(n);\n        const auto &view\
    \ = seg;\n        vector<ll> a(n);\n        for (int step = 0; step < 300; ++step)\
    \ {\n            if (n && step % 3) {\n                int k = rng() % n;\n  \
    \              ll x = rng() % 20;\n                if (step % 2) {\n         \
    \           seg.add(k, x);\n                    a[k] += x;\n                }\
    \ else {\n                    seg.update(k, x);\n                    a[k] = x;\n\
    \                }\n            }\n            size_t nodes = seg.node.size();\n\
    \            for (int end : {0, int(rng() % (n + 1)), n}) {\n                ll\
    \ limit = rng() % 200, sum = 0;\n                int left = end, right = end;\n\
    \                while (left && sum + a[left - 1] <= limit) sum += a[--left];\n\
    \                sum = 0;\n                while (right < n && sum + a[right]\
    \ <= limit) sum += a[right++];\n                auto cond = [&](ll x) { return\
    \ x <= limit; };\n                assert(view.search_left(end, cond) == left);\n\
    \                assert(view.search_right(end, cond) == right);\n            \
    \    assert(view.query(left, right) == accumulate(a.begin() + left, a.begin()\
    \ + right, 0LL));\n            }\n            assert(seg.node.size() == nodes);\n\
    \        }\n    }\n}\n\nvoid noncommutative_check() {\n    mt19937 rng(114);\n\
    \    for (int n = 0; n <= 32; ++n) {\n        DynamicSegmentTree<Concat> seg(n);\n\
    \        vector<string> a(n);\n        for (int step = 0; step < 100; ++step)\
    \ {\n            if (n) {\n                int k = rng() % n;\n              \
    \  a[k] = rng() % 3 ? string(1, 'a' + rng() % 3) : \"\";\n                seg.update(k,\
    \ a[k]);\n            }\n            int limit = rng() % (n + 1);\n          \
    \  auto cond = [&](const string &x) {\n                return int(x.size()) <=\
    \ limit && x.find(\"ab\") == string::npos;\n            };\n            size_t\
    \ nodes = seg.node.size();\n            for (int end = 0; end <= n; ++end) {\n\
    \                int left = end, right = end;\n                string acc;\n \
    \               while (left && cond(a[left - 1] + acc)) acc = a[--left] + acc;\n\
    \                acc.clear();\n                while (right < n && cond(acc +\
    \ a[right])) acc += a[right++];\n                assert(seg.search_left(end, cond)\
    \ == left);\n                assert(seg.search_right(end, cond) == right);\n \
    \           }\n            assert(seg.node.size() == nodes);\n        }\n    }\n\
    }\n\nvoid sparse_check() {\n    for (ll n : {1LL, 1000000000000LL, LLONG_MAX})\
    \ {\n        DynamicSegmentTree<Sum> seg(n);\n        auto zero = [](ll x) { return\
    \ x == 0; };\n        for (ll end : {0LL, n / 2, n}) {\n            assert(seg.search_left(end,\
    \ zero) == 0);\n            assert(seg.search_right(end, zero) == n);\n      \
    \  }\n        assert(seg.node.empty());\n        seg.update(n - 1, 1);\n     \
    \   assert(seg.search_right(0, zero) == n - 1);\n        assert(seg.search_left(n,\
    \ zero) == n);\n        assert(seg.search_left(n - 1, zero) == 0);\n        assert(seg.search_right(n,\
    \ zero) == n);\n        seg.update(0, 1);\n        assert(seg.search_right(0,\
    \ zero) == 0);\n        assert(seg.search_left(n, [](ll x) { return x <= 2; })\
    \ == 0);\n        assert(seg.search_right(0, [](ll x) { return x <= 2; }) == n);\n\
    \    }\n}\n\nint main() {\n    sum_check();\n    noncommutative_check();\n   \
    \ sparse_check();\n    Scanner sc;\n    Printer pr;\n    int a, b;\n    sc.read(a,\
    \ b);\n    pr.println(a + b);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/segmenttree/dynamic_segtree.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_dynamic_segtree_search.test.cpp
  requiredBy: []
  timestamp: '2026-10-07 00:49:22+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_dynamic_segtree_search.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_dynamic_segtree_search.test.cpp
- /verify/test/yosupo_aplusb_dynamic_segtree_search.test.cpp.html
title: test/yosupo_aplusb_dynamic_segtree_search.test.cpp
---
