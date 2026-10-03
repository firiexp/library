---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/segmenttree/dualsegtree.cpp
    title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Dual Segment Tree)"
  - icon: ':heavy_check_mark:'
    path: datastructure/segmenttree/lazysegtree.cpp
    title: "\u9045\u5EF6\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Lazy Segment Tree)"
  - icon: ':heavy_check_mark:'
    path: datastructure/segmenttree/segtree.cpp
    title: Segment Tree
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_segmenttree_boundaries.test.cpp\"\n#define\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"datastructure/segmenttree/segtree.cpp\"\
    \ntemplate <class M>\nstruct SegmentTree{\n    using T = typename M::T;\n    int\
    \ sz, n, height{};\n    vector<T> seg;\n    explicit SegmentTree(int n) : n(n)\
    \ {\n        sz = 1; while(sz < n) sz <<= 1, height++;\n        seg.assign(2*sz,\
    \ M::e());\n    }\n\n    void set(int k, const T &x){ seg[k + sz] = x; }\n\n \
    \   void build(){\n        for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[2*i],\
    \ seg[2*i+1]);\n    }\n\n    void update(int k, const T &x){\n        k += sz;\n\
    \        seg[k] = x;\n        while (k >>= 1) seg[k] = M::f(seg[2*k], seg[2*k+1]);\n\
    \    }\n\n    T query(int a, int b){\n        T l = M::e(), r = M::e();\n    \
    \    for(a += sz, b += sz; a < b; a >>=1, b>>=1){\n            if(a & 1) l = M::f(l,\
    \ seg[a++]);\n            if(b & 1) r = M::f(seg[--b], r);\n        }\n      \
    \  return M::f(l, r);\n    }\n\n    template<class F>\n    int search_right(int\
    \ l, F cond){\n        if(l == n) return n;\n        T val = M::e();\n       \
    \ l += sz;\n        do {\n            while(!(l&1)) l >>= 1;\n            if(!cond(M::f(val,\
    \ seg[l]))){\n                while(l < sz) {\n                    l <<= 1;\n\
    \                    if (cond(M::f(val, seg[l]))){\n                        val\
    \ = M::f(val, seg[l]);\n                        l++;\n                    }\n\
    \                }\n                return l - sz;\n            }\n          \
    \  val = M::f(val, seg[l]);\n            l++;\n        } while((l & -l) != l);\n\
    \        return n;\n    }\n\n    template<class F>\n    int search_left(int r,\
    \ F cond){\n        if(r == 0) return 0;\n        T val = M::e();\n        r +=\
    \ sz;\n        do {\n            r--;\n            while(r > 1 && (r & 1)) r >>=\
    \ 1;\n            if(!cond(M::f(seg[r], val))){\n                while(r < sz)\
    \ {\n                    r = ((r << 1)|1);\n                    if (cond(M::f(seg[r],\
    \ val))){\n                        val = M::f(seg[r], val);\n                \
    \        r--;\n                    }\n                }\n                return\
    \ r + 1 - sz;\n            }\n            val = M::f(seg[r], val);\n        }\
    \ while((r & -r) != r);\n        return 0;\n    }\n    T operator[](const int\
    \ &k) const { return seg[k + sz]; }\n};\n\n\n/*\nstruct Monoid{\n    using T =\
    \ array<mint, 2>;\n    static T f(T a, T b) { return {a[0]*b[0], a[1]*b[0]+b[1]};\
    \ }\n    static T e() { return {1, 0}; }\n};\n*/\n\n/**\n * @brief Segment Tree\n\
    \ */\n#line 1 \"datastructure/segmenttree/lazysegtree.cpp\"\ntemplate <class M>\n\
    struct LazySegmentTree{\n    using T = typename M::T;\n    using L = typename\
    \ M::L;\n    int sz, n, height{};\n    vector<T> seg; vector<L> lazy;\n    explicit\
    \ LazySegmentTree(int n) : n(n) {\n        sz = 1; while(sz < n) sz <<= 1, height++;\n\
    \        seg.assign(2*sz, M::e());\n        lazy.assign(2*sz, M::l());\n    }\n\
    \n    void set(int k, const T &x){ seg[k + sz] = x; }\n\n    void build(){\n \
    \       for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[i<<1], seg[(i<<1)|1]);\n\
    \    }\n\n    T reflect(int k){ return lazy[k] == M::l() ? seg[k] : M::g(seg[k],\
    \ lazy[k]); }\n\n    void eval(int k){\n        if(lazy[k] == M::l()) return;\n\
    \        if(k < sz){\n            lazy[(k<<1)|0] = M::h(lazy[(k<<1)|0], lazy[k]);\n\
    \            lazy[(k<<1)|1] = M::h(lazy[(k<<1)|1], lazy[k]);\n        }\n    \
    \    seg[k] = reflect(k);\n        lazy[k] = M::l();\n    }\n    void thrust(int\
    \ k){ for (int i = height; i; --i) eval(k>>i); }\n    void recalc(int k) { while(k\
    \ >>= 1) seg[k] = M::f(reflect((k<<1)|0), reflect((k<<1)|1));}\n\n    void update(int\
    \ a, const T &x){\n        thrust(a += sz);\n        seg[a] = x;\n        lazy[a]\
    \ = M::l();\n        recalc(a);\n    }\n\n    void update(int a, int b, const\
    \ L &x){\n        if(a == b) return;\n        thrust(a += sz); thrust(b += sz-1);\n\
    \        for (int l = a, r = b+1;l < r; l >>=1, r >>= 1) {\n            if(l&1)\
    \ lazy[l] = M::h(lazy[l], x), l++;\n            if(r&1) --r, lazy[r] = M::h(lazy[r],\
    \ x);\n        }\n        recalc(a);\n        recalc(b);\n    }\n\n    T query(int\
    \ a, int b){ // [l, r)\n        if(a == b) return M::e();\n        thrust(a +=\
    \ sz);\n        thrust(b += sz-1);\n        T ll = M::e(), rr = M::e();\n    \
    \    for(int l = a, r = b+1; l < r; l >>=1, r>>=1) {\n            if (l & 1) ll\
    \ = M::f(ll, reflect(l++));\n            if (r & 1) rr = M::f(reflect(--r), rr);\n\
    \        }\n        return M::f(ll, rr);\n    }\n\n    template<class F>\n   \
    \ int search_right(int l, F cond){\n        if(l == n) return n;\n        thrust(l\
    \ += sz);\n        T val = M::e();\n        do {\n            while(!(l&1)) l\
    \ >>= 1;\n            if(!cond(M::f(val, reflect(l)))){\n                while(l\
    \ < sz) {\n                    eval(l); l <<= 1;\n                    if (cond(M::f(val,\
    \ reflect(l)))){\n                        val = M::f(val, reflect(l++));\n   \
    \                 }\n                }\n                return l - sz;\n     \
    \       }\n            val = M::f(val, reflect(l++));\n        } while((l & -l)\
    \ != l);\n        return n;\n    }\n\n    template<class F>\n    int search_left(int\
    \ r, F cond){\n        if(r <= 0) return 0;\n        thrust((r += sz)-1);\n  \
    \      T val = M::e();\n        do {\n            r--;\n            while(r >\
    \ 1 && r&1) r >>= 1;\n            if(!cond(M::f(reflect(r), val))){\n        \
    \        while(r < sz) {\n                    eval(r);\n                    r\
    \ = ((r << 1)|1);\n                    if (cond(M::f(reflect(r), val))){\n   \
    \                     val = M::f(reflect(r--), val);\n                    }\n\
    \                }\n                return r + 1 - sz;\n            }\n      \
    \      val = M::f(reflect(r), val);\n        } while((r & -r) != r);\n       \
    \ return 0;\n    }\n};\n\n/*\nstruct Monoid{\n    using T = array<mint, 2>;\n\
    \    using L = array<mint, 2>;\n    static T f(T a, T b) { return {a[0]+b[0],\
    \ a[1]+b[1]}; }\n    static T g(T a, L b) {\n        return {a[0] * b[0] + a[1]\
    \ * b[1], a[1]};\n    }\n    static L h(L a, L b) {\n        return {a[0]*b[0],\
    \ a[1]*b[0]+b[1]};\n    }\n    static T e() { return {0, 0}; }\n    static L l()\
    \ { return {1, 0}; }\n};\n*/\n\n/**\n * @brief \u9045\u5EF6\u30BB\u30B0\u30E1\u30F3\
    \u30C8\u6728(Lazy Segment Tree)\n */\n#line 1 \"datastructure/segmenttree/dualsegtree.cpp\"\
    \ntemplate <class M>\nstruct DualSegmentTree{\n    using T = typename M::T;\n\
    \    int sz, height{};\n    vector<T> lazy;\n    explicit DualSegmentTree(int\
    \ n) {\n        sz = 1; while(sz < n) sz <<= 1, height++;\n        lazy.assign(2*sz,\
    \ M::e());\n    }\n\n    void eval(int k){\n        if(lazy[k] == M::e()) return;\n\
    \        lazy[(k<<1)|0] = M::f(lazy[(k<<1)|0], lazy[k]);\n        lazy[(k<<1)|1]\
    \ = M::f(lazy[(k<<1)|1], lazy[k]);\n        lazy[k] = M::e();\n    }\n    void\
    \ thrust(int k){ for (int i = height; i; --i) eval(k>>i); }\n    void update(int\
    \ a, int b, const T &x){\n        if(a == b) return;\n        thrust(a += sz);\
    \ thrust(b += sz-1);\n        for (int l = a, r = b+1;l < r; l >>=1, r >>= 1)\
    \ {\n            if(l&1) lazy[l] = M::f(lazy[l], x), l++;\n            if(r&1)\
    \ --r, lazy[r] = M::f(lazy[r], x);\n        }\n    }\n\n    T operator[](int k){\n\
    \        thrust(k += sz);\n        return lazy[k];\n    }\n};\n/*\nstruct Monoid{\n\
    \    using T = ll;\n    static T f(T a, T b) { return a+b; }\n    static T e()\
    \ { return 0; }\n};\n*/\n\n/**\n * @brief \u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\
    \u30C8\u6728(Dual Segment Tree)\n */\n#line 9 \"test/yosupo_aplusb_segmenttree_boundaries.test.cpp\"\
    \n\nstruct Sum {\n    using T = long long;\n    static T e() { return 0; }\n \
    \   static T f(T a, T b) { return a + b; }\n};\n\nstruct SumAffine {\n    using\
    \ T = pair<long long, int>;\n    using L = pair<long long, long long>;\n    static\
    \ T e() { return {0, 0}; }\n    static L l() { return {1, 0}; }\n    static T\
    \ f(T a, T b) { return {a.first + b.first, a.second + b.second}; }\n    static\
    \ T g(T a, L b) { return {a.first * b.first + a.second * b.second, a.second};\
    \ }\n    static L h(L a, L b) { return {a.first * b.first, a.second * b.first\
    \ + b.second}; }\n};\n\nstruct Affine {\n    using T = SumAffine::L;\n    static\
    \ T e() { return SumAffine::l(); }\n    static T f(T a, T b) { return SumAffine::h(a,\
    \ b); }\n};\n\nstruct Concat {\n    using T = string;\n    static T e() { return\
    \ \"\"; }\n    static T f(const T &a, const T &b) { return a + b; }\n};\n\nvoid\
    \ minimal_check() {\n    SegmentTree<Sum> plain(1);\n    plain.set(0, 1);\n  \
    \  plain.build();\n    assert(plain.search_left(1, [](auto x) { return x < 1;\
    \ }) == 1);\n\n    LazySegmentTree<SumAffine> lazy(1);\n    lazy.set(0, {0, 1});\n\
    \    lazy.build();\n    lazy.update(0, 1, {1, 5});\n    assert(lazy.search_right(0,\
    \ [](auto x) { return x.first < 1; }) == 0);\n    lazy.update(0, SumAffine::T{2,\
    \ 1});\n    assert(lazy.query(0, 1).first == 2);\n    lazy.update(1, 1, {1, 5});\n\
    \    assert(lazy.query(0, 1).first == 2);\n\n    DualSegmentTree<Sum> dual(2);\n\
    \    dual.update(0, 1, 7);\n    dual.update(2, 2, 5);\n    assert(dual[0] == 7\
    \ && dual[1] == 0);\n}\n\nvoid exhaustive_search_check() {\n    // Includes singleton\
    \ and power-of-two right boundaries.\n    for (int n = 0, count = 1; n <= 7; ++n,\
    \ count *= 3) {\n        for (int mask = 0; mask < count; ++mask) {\n        \
    \    vector<int> a(n);\n            SegmentTree<Sum> seg(n);\n            int\
    \ digits = mask;\n            for (int i = 0; i < n; ++i, digits /= 3) seg.set(i,\
    \ a[i] = digits % 3);\n            seg.build();\n            for (int end = 0;\
    \ end <= n; ++end) {\n                for (int limit = 0; limit <= 2 * n + 1;\
    \ ++limit) {\n                    auto cond = [&](auto x) { return x <= limit;\
    \ };\n                    int left = end, right = end, sum = 0;\n            \
    \        while (left > 0 && sum + a[left - 1] <= limit) sum += a[--left];\n  \
    \                  sum = 0;\n                    while (right < n && sum + a[right]\
    \ <= limit) sum += a[right++];\n                    assert(seg.search_left(end,\
    \ cond) == left);\n                    assert(seg.search_right(end, cond) == right);\n\
    \                }\n            }\n        }\n    }\n}\n\nvoid mixed_update_check()\
    \ {\n    mt19937 rng(20261003);\n    for (int n = 0; n <= 65; ++n) {\n       \
    \ LazySegmentTree<SumAffine> lazy(n);\n        DualSegmentTree<Affine> dual(n);\n\
    \        SegmentTree<Sum> plain(n);\n        vector<long long> a(n), b(n);\n \
    \       for (int i = 0; i < n; ++i) lazy.set(i, {0, 1});\n        lazy.build();\n\
    \        plain.build();\n        for (int step = 0; step < 500; ++step) {\n  \
    \          int l = rng() % (n + 1), r = rng() % (n + 1);\n            if (l >\
    \ r) swap(l, r);\n            // Assignment and addition are noncommutative affine\
    \ actions.\n            Affine::T op = {rng() % 2, rng() % 8};\n            lazy.update(l,\
    \ r, op);\n            dual.update(l, r, op);\n            for (int i = l; i <\
    \ r; ++i) {\n                a[i] = a[i] * op.first + op.second;\n           \
    \     b[i] = b[i] * op.first + op.second;\n                plain.update(i, a[i]);\n\
    \            }\n            if (n && step % 3 == 0) {\n                int i =\
    \ rng() % n;\n                a[i] = rng() % 20;\n                lazy.update(i,\
    \ SumAffine::T{a[i], 1});\n                plain.update(i, a[i]);\n          \
    \  }\n            for (int end : {0, n / 2, n}) {\n                lazy.update(end,\
    \ end, {0, 99});\n                dual.update(end, end, {0, 99});\n          \
    \      assert(lazy.query(end, end) == SumAffine::e());\n            }\n      \
    \      long long limit = rng() % 100;\n            int end = rng() % (n + 1),\
    \ left = end, right = end;\n            long long sum = 0;\n            while\
    \ (left > 0 && sum + a[left - 1] <= limit) sum += a[--left];\n            sum\
    \ = 0;\n            while (right < n && sum + a[right] <= limit) sum += a[right++];\n\
    \            auto cond = [&](auto x) { return x.first <= limit; };\n         \
    \   assert(lazy.search_left(end, cond) == left);\n            assert(lazy.search_right(end,\
    \ cond) == right);\n            assert(plain.search_left(end, [&](auto x) { return\
    \ x <= limit; }) == left);\n            assert(plain.search_right(end, [&](auto\
    \ x) { return x <= limit; }) == right);\n            assert(lazy.query(l, r).first\
    \ == accumulate(a.begin() + l, a.begin() + r, 0LL));\n            assert(plain.query(l,\
    \ r) == lazy.query(l, r).first);\n            for (int i = 0; i < n; ++i) {\n\
    \                assert(lazy.query(i, i + 1).first == a[i]);\n               \
    \ assert(dual[i].second == b[i]); // Apply the composed action to zero.\n    \
    \        }\n        }\n    }\n}\n\nvoid noncommutative_search_check() {\n    mt19937\
    \ rng(67);\n    for (int n = 0; n <= 32; ++n) {\n        SegmentTree<Concat> seg(n);\n\
    \        string s(n, 'a');\n        for (int i = 0; i < n; ++i) seg.set(i, string(1,\
    \ s[i] = 'a' + rng() % 3));\n        seg.build();\n        for (int step = 0;\
    \ step < 100; ++step) {\n            if (n) {\n                int i = rng() %\
    \ n;\n                seg.update(i, string(1, s[i] = 'a' + rng() % 3));\n    \
    \        }\n            int limit = rng() % (n + 1);\n            auto cond =\
    \ [&](const string &x) {\n                return int(x.size()) <= limit && x.find(\"\
    ab\") == string::npos;\n            };\n            for (int end = 0; end <= n;\
    \ ++end) {\n                int left = end, right = end;\n                while\
    \ (left > 0 && cond(s.substr(left - 1, end - left + 1))) --left;\n           \
    \     while (right < n && cond(s.substr(end, right - end + 1))) ++right;\n   \
    \             assert(seg.search_left(end, cond) == left);\n                assert(seg.search_right(end,\
    \ cond) == right);\n                assert(seg.query(left, right) == s.substr(left,\
    \ right - left));\n            }\n        }\n    }\n}\n\nint main() {\n    minimal_check();\n\
    \    exhaustive_search_check();\n    mixed_update_check();\n    noncommutative_search_check();\n\
    \    Scanner sc;\n    Printer pr;\n    int a, b;\n    sc.read(a, b);\n    pr.println(a\
    \ + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n#include \"../util/fastio.cpp\"\n#include \"../datastructure/segmenttree/segtree.cpp\"\
    \n#include \"../datastructure/segmenttree/lazysegtree.cpp\"\n#include \"../datastructure/segmenttree/dualsegtree.cpp\"\
    \n\nstruct Sum {\n    using T = long long;\n    static T e() { return 0; }\n \
    \   static T f(T a, T b) { return a + b; }\n};\n\nstruct SumAffine {\n    using\
    \ T = pair<long long, int>;\n    using L = pair<long long, long long>;\n    static\
    \ T e() { return {0, 0}; }\n    static L l() { return {1, 0}; }\n    static T\
    \ f(T a, T b) { return {a.first + b.first, a.second + b.second}; }\n    static\
    \ T g(T a, L b) { return {a.first * b.first + a.second * b.second, a.second};\
    \ }\n    static L h(L a, L b) { return {a.first * b.first, a.second * b.first\
    \ + b.second}; }\n};\n\nstruct Affine {\n    using T = SumAffine::L;\n    static\
    \ T e() { return SumAffine::l(); }\n    static T f(T a, T b) { return SumAffine::h(a,\
    \ b); }\n};\n\nstruct Concat {\n    using T = string;\n    static T e() { return\
    \ \"\"; }\n    static T f(const T &a, const T &b) { return a + b; }\n};\n\nvoid\
    \ minimal_check() {\n    SegmentTree<Sum> plain(1);\n    plain.set(0, 1);\n  \
    \  plain.build();\n    assert(plain.search_left(1, [](auto x) { return x < 1;\
    \ }) == 1);\n\n    LazySegmentTree<SumAffine> lazy(1);\n    lazy.set(0, {0, 1});\n\
    \    lazy.build();\n    lazy.update(0, 1, {1, 5});\n    assert(lazy.search_right(0,\
    \ [](auto x) { return x.first < 1; }) == 0);\n    lazy.update(0, SumAffine::T{2,\
    \ 1});\n    assert(lazy.query(0, 1).first == 2);\n    lazy.update(1, 1, {1, 5});\n\
    \    assert(lazy.query(0, 1).first == 2);\n\n    DualSegmentTree<Sum> dual(2);\n\
    \    dual.update(0, 1, 7);\n    dual.update(2, 2, 5);\n    assert(dual[0] == 7\
    \ && dual[1] == 0);\n}\n\nvoid exhaustive_search_check() {\n    // Includes singleton\
    \ and power-of-two right boundaries.\n    for (int n = 0, count = 1; n <= 7; ++n,\
    \ count *= 3) {\n        for (int mask = 0; mask < count; ++mask) {\n        \
    \    vector<int> a(n);\n            SegmentTree<Sum> seg(n);\n            int\
    \ digits = mask;\n            for (int i = 0; i < n; ++i, digits /= 3) seg.set(i,\
    \ a[i] = digits % 3);\n            seg.build();\n            for (int end = 0;\
    \ end <= n; ++end) {\n                for (int limit = 0; limit <= 2 * n + 1;\
    \ ++limit) {\n                    auto cond = [&](auto x) { return x <= limit;\
    \ };\n                    int left = end, right = end, sum = 0;\n            \
    \        while (left > 0 && sum + a[left - 1] <= limit) sum += a[--left];\n  \
    \                  sum = 0;\n                    while (right < n && sum + a[right]\
    \ <= limit) sum += a[right++];\n                    assert(seg.search_left(end,\
    \ cond) == left);\n                    assert(seg.search_right(end, cond) == right);\n\
    \                }\n            }\n        }\n    }\n}\n\nvoid mixed_update_check()\
    \ {\n    mt19937 rng(20261003);\n    for (int n = 0; n <= 65; ++n) {\n       \
    \ LazySegmentTree<SumAffine> lazy(n);\n        DualSegmentTree<Affine> dual(n);\n\
    \        SegmentTree<Sum> plain(n);\n        vector<long long> a(n), b(n);\n \
    \       for (int i = 0; i < n; ++i) lazy.set(i, {0, 1});\n        lazy.build();\n\
    \        plain.build();\n        for (int step = 0; step < 500; ++step) {\n  \
    \          int l = rng() % (n + 1), r = rng() % (n + 1);\n            if (l >\
    \ r) swap(l, r);\n            // Assignment and addition are noncommutative affine\
    \ actions.\n            Affine::T op = {rng() % 2, rng() % 8};\n            lazy.update(l,\
    \ r, op);\n            dual.update(l, r, op);\n            for (int i = l; i <\
    \ r; ++i) {\n                a[i] = a[i] * op.first + op.second;\n           \
    \     b[i] = b[i] * op.first + op.second;\n                plain.update(i, a[i]);\n\
    \            }\n            if (n && step % 3 == 0) {\n                int i =\
    \ rng() % n;\n                a[i] = rng() % 20;\n                lazy.update(i,\
    \ SumAffine::T{a[i], 1});\n                plain.update(i, a[i]);\n          \
    \  }\n            for (int end : {0, n / 2, n}) {\n                lazy.update(end,\
    \ end, {0, 99});\n                dual.update(end, end, {0, 99});\n          \
    \      assert(lazy.query(end, end) == SumAffine::e());\n            }\n      \
    \      long long limit = rng() % 100;\n            int end = rng() % (n + 1),\
    \ left = end, right = end;\n            long long sum = 0;\n            while\
    \ (left > 0 && sum + a[left - 1] <= limit) sum += a[--left];\n            sum\
    \ = 0;\n            while (right < n && sum + a[right] <= limit) sum += a[right++];\n\
    \            auto cond = [&](auto x) { return x.first <= limit; };\n         \
    \   assert(lazy.search_left(end, cond) == left);\n            assert(lazy.search_right(end,\
    \ cond) == right);\n            assert(plain.search_left(end, [&](auto x) { return\
    \ x <= limit; }) == left);\n            assert(plain.search_right(end, [&](auto\
    \ x) { return x <= limit; }) == right);\n            assert(lazy.query(l, r).first\
    \ == accumulate(a.begin() + l, a.begin() + r, 0LL));\n            assert(plain.query(l,\
    \ r) == lazy.query(l, r).first);\n            for (int i = 0; i < n; ++i) {\n\
    \                assert(lazy.query(i, i + 1).first == a[i]);\n               \
    \ assert(dual[i].second == b[i]); // Apply the composed action to zero.\n    \
    \        }\n        }\n    }\n}\n\nvoid noncommutative_search_check() {\n    mt19937\
    \ rng(67);\n    for (int n = 0; n <= 32; ++n) {\n        SegmentTree<Concat> seg(n);\n\
    \        string s(n, 'a');\n        for (int i = 0; i < n; ++i) seg.set(i, string(1,\
    \ s[i] = 'a' + rng() % 3));\n        seg.build();\n        for (int step = 0;\
    \ step < 100; ++step) {\n            if (n) {\n                int i = rng() %\
    \ n;\n                seg.update(i, string(1, s[i] = 'a' + rng() % 3));\n    \
    \        }\n            int limit = rng() % (n + 1);\n            auto cond =\
    \ [&](const string &x) {\n                return int(x.size()) <= limit && x.find(\"\
    ab\") == string::npos;\n            };\n            for (int end = 0; end <= n;\
    \ ++end) {\n                int left = end, right = end;\n                while\
    \ (left > 0 && cond(s.substr(left - 1, end - left + 1))) --left;\n           \
    \     while (right < n && cond(s.substr(end, right - end + 1))) ++right;\n   \
    \             assert(seg.search_left(end, cond) == left);\n                assert(seg.search_right(end,\
    \ cond) == right);\n                assert(seg.query(left, right) == s.substr(left,\
    \ right - left));\n            }\n        }\n    }\n}\n\nint main() {\n    minimal_check();\n\
    \    exhaustive_search_check();\n    mixed_update_check();\n    noncommutative_search_check();\n\
    \    Scanner sc;\n    Printer pr;\n    int a, b;\n    sc.read(a, b);\n    pr.println(a\
    \ + b);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/segmenttree/segtree.cpp
  - datastructure/segmenttree/lazysegtree.cpp
  - datastructure/segmenttree/dualsegtree.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_segmenttree_boundaries.test.cpp
  requiredBy: []
  timestamp: '2026-10-03 12:23:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_segmenttree_boundaries.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_segmenttree_boundaries.test.cpp
- /verify/test/yosupo_aplusb_segmenttree_boundaries.test.cpp.html
title: test/yosupo_aplusb_segmenttree_boundaries.test.cpp
---
