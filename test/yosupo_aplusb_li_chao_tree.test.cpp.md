---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/li_chao_tree.cpp
    title: Li Chao Tree
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_li_chao_tree.test.cpp\"\n#define PROBLEM\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"datastructure/li_chao_tree.cpp\"\
    \ntemplate<class T, bool get_max = false>\nstruct LiChaoTree {\n    struct Line\
    \ {\n        T a, b;\n        int id;\n        Line(T a = 0, T b = inf(), int\
    \ id = -1) : a(a), b(b), id(id) {}\n        T get(T x) const { return a * x +\
    \ b; }\n        bool better(const Line &other, T x) const {\n            return\
    \ make_pair(get(x), id) < make_pair(other.get(x), other.id);\n        }\n    };\n\
    \n    vector<T> xs;\n    vector<Line> seg;\n    int n;\n    int next_id = 0;\n\
    \n    explicit LiChaoTree(vector<T> xs) : xs(xs) {\n        sort(this->xs.begin(),\
    \ this->xs.end());\n        this->xs.erase(unique(this->xs.begin(), this->xs.end()),\
    \ this->xs.end());\n        n = (int)this->xs.size();\n        seg.assign(max(1,\
    \ 4 * n), Line());\n    }\n\n    int add_line(T a, T b) {\n        int id = next_id++;\n\
    \        if (n == 0) return id;\n        if (get_max) a = -a, b = -b;\n      \
    \  add_line_node(1, 0, n, Line(a, b, id));\n        return id;\n    }\n\n    int\
    \ add_segment(T a, T b, T l, T r) {\n        int id = next_id++;\n        if (n\
    \ == 0 || l >= r) return id;\n        if (get_max) a = -a, b = -b;\n        int\
    \ L = lower_bound(xs.begin(), xs.end(), l) - xs.begin();\n        int R = lower_bound(xs.begin(),\
    \ xs.end(), r) - xs.begin();\n        if (L >= R) return id;\n        add_segment_node(1,\
    \ 0, n, L, R, Line(a, b, id));\n        return id;\n    }\n\n    T query(T x)\
    \ const {\n        auto ret = query_with_id(x);\n        return ret ? ret->first\
    \ : (get_max ? -inf() : inf());\n    }\n\n    optional<pair<T, int>> query_with_id(T\
    \ x) const {\n        if (n == 0) return nullopt;\n        int i = lower_bound(xs.begin(),\
    \ xs.end(), x) - xs.begin();\n        if (i == n || xs[i] != x) return nullopt;\n\
    \        auto ret = query_node(1, 0, n, i, x);\n        if (ret && get_max) ret->first\
    \ = -ret->first;\n        return ret;\n    }\n\nprivate:\n    static constexpr\
    \ T inf() {\n        return numeric_limits<T>::max() / 4;\n    }\n\n    void add_line_node(int\
    \ k, int l, int r, Line x) {\n        if (seg[k].id == -1) {\n            seg[k]\
    \ = x;\n            return;\n        }\n        int m = (l + r) / 2;\n       \
    \ bool lef = x.better(seg[k], xs[l]);\n        bool mid = x.better(seg[k], xs[m]);\n\
    \        if (mid) swap(seg[k], x);\n        if (r - l == 1) return;\n        if\
    \ (lef != mid) add_line_node(k * 2, l, m, x);\n        else add_line_node(k *\
    \ 2 + 1, m, r, x);\n    }\n\n    void add_segment_node(int k, int l, int r, int\
    \ a, int b, Line x) {\n        if (r <= a || b <= l) return;\n        if (a <=\
    \ l && r <= b) {\n            add_line_node(k, l, r, x);\n            return;\n\
    \        }\n        int m = (l + r) / 2;\n        add_segment_node(k * 2, l, m,\
    \ a, b, x);\n        add_segment_node(k * 2 + 1, m, r, a, b, x);\n    }\n\n  \
    \  optional<pair<T, int>> query_node(int k, int l, int r, int i, T x) const {\n\
    \        optional<pair<T, int>> ret;\n        if (seg[k].id != -1) ret = make_pair(seg[k].get(x),\
    \ seg[k].id);\n        if (r - l == 1) return ret;\n        int m = (l + r) /\
    \ 2;\n        auto child = i < m ? query_node(k * 2, l, m, i, x)\n           \
    \               : query_node(k * 2 + 1, m, r, i, x);\n        if (child && (!ret\
    \ || *child < *ret)) ret = child;\n        return ret;\n    }\n};\n\ntemplate<class\
    \ T, bool get_max = false>\nstruct OnlineLiChaoTree {\n    struct Line {\n   \
    \     T a, b;\n        int id;\n        Line(T a = 0, T b = inf(), int id = -1)\
    \ : a(a), b(b), id(id) {}\n        T get(T x) const { return a * x + b; }\n  \
    \      bool better(const Line &other, T x) const {\n            return make_pair(get(x),\
    \ id) < make_pair(other.get(x), other.id);\n        }\n    };\n\n    struct Node\
    \ {\n        Line line;\n        int l, r;\n        explicit Node(const Line &line)\
    \ : line(line), l(-1), r(-1) {}\n    };\n\n    T low, high;\n    int root;\n \
    \   int next_id = 0;\n    deque<Node> nodes;\n\n    explicit OnlineLiChaoTree(T\
    \ low, T high) : low(low), high(high), root(-1) {}\n\n    int add_line(T a, T\
    \ b) {\n        int id = next_id++;\n        if (get_max) a = -a, b = -b;\n  \
    \      add_line(root, low, high, Line(a, b, id));\n        return id;\n    }\n\
    \n    int add_segment(T a, T b, T l, T r) {\n        int id = next_id++;\n   \
    \     if (l >= r) return id;\n        if (get_max) a = -a, b = -b;\n        add_segment(root,\
    \ low, high, l, r, Line(a, b, id));\n        return id;\n    }\n\n    T query(T\
    \ x) const {\n        auto ret = query_with_id(x);\n        return ret ? ret->first\
    \ : (get_max ? -inf() : inf());\n    }\n\n    optional<pair<T, int>> query_with_id(T\
    \ x) const {\n        auto ret = query(root, low, high, x);\n        if (ret &&\
    \ get_max) ret->first = -ret->first;\n        return ret;\n    }\n\nprivate:\n\
    \    static constexpr T inf() {\n        return numeric_limits<T>::max() / 4;\n\
    \    }\n\n    int new_node(const Line &line) {\n        nodes.emplace_back(line);\n\
    \        return (int)nodes.size() - 1;\n    }\n\n    void add_line(int &t, T l,\
    \ T r, Line x) {\n        if (t == -1) {\n            t = new_node(x);\n     \
    \       return;\n        }\n        Node &node = nodes[t];\n        if (node.line.id\
    \ == -1) {\n            node.line = x;\n            return;\n        }\n     \
    \   T m = l + (r - l) / 2;\n        bool lef = x.better(node.line, l);\n     \
    \   bool mid = x.better(node.line, m);\n        if (mid) swap(node.line, x);\n\
    \        if (r - l == 1) return;\n        if (lef != mid) add_line(node.l, l,\
    \ m, x);\n        else if (x.better(node.line, r - 1)) add_line(node.r, m, r,\
    \ x);\n    }\n\n    void add_segment(int &t, T l, T r, T a, T b, Line x) {\n \
    \       if (r <= a || b <= l) return;\n        if (a <= l && r <= b) {\n     \
    \       add_line(t, l, r, x);\n            return;\n        }\n        if (t ==\
    \ -1) t = new_node(Line());\n        Node &node = nodes[t];\n        T m = l +\
    \ (r - l) / 2;\n        if (a < m) add_segment(node.l, l, m, a, b, x);\n     \
    \   if (m < b) add_segment(node.r, m, r, a, b, x);\n    }\n\n    optional<pair<T,\
    \ int>> query(int t, T l, T r, T x) const {\n        optional<pair<T, int>> ret;\n\
    \        while (t != -1) {\n            const Node &node = nodes[t];\n       \
    \     if (node.line.id != -1) {\n                auto value = make_pair(node.line.get(x),\
    \ node.line.id);\n                if (!ret || value < *ret) ret = value;\n   \
    \         }\n            if (r - l == 1) break;\n            T m = l + (r - l)\
    \ / 2;\n            if (x < m) {\n                t = node.l;\n              \
    \  r = m;\n            } else {\n                t = node.r;\n               \
    \ l = m;\n            }\n        }\n        return ret;\n    }\n};\n\n/**\n *\
    \ @brief Li Chao Tree\n */\n#line 9 \"test/yosupo_aplusb_li_chao_tree.test.cpp\"\
    \n\ntemplate<bool get_max>\nvoid check_limits() {\n    const ll inf = numeric_limits<ll>::max()\
    \ / 4;\n    const ll empty = get_max ? -inf : inf;\n    for (ll value : {0LL,\
    \ inf, -inf, inf + 1, -inf - 1,\n                     3000000000000000000LL, -3000000000000000000LL,\n\
    \                     LLONG_MAX, -LLONG_MAX}) {\n        LiChaoTree<ll, get_max>\
    \ offline({-2, 0, 2});\n        OnlineLiChaoTree<ll, get_max> online(-2, 3);\n\
    \        assert(offline.query(0) == empty && online.query(0) == empty);\n    \
    \    assert(!offline.query_with_id(0) && !online.query_with_id(0));\n        assert(offline.add_segment(0,\
    \ value, 0, 1) == 0);\n        assert(online.add_segment(0, value, 0, 1) == 0);\n\
    \        assert(offline.query(0) == value && online.query(0) == value);\n    \
    \    assert(offline.query_with_id(0) == make_pair(value, 0));\n        assert(online.query_with_id(0)\
    \ == make_pair(value, 0));\n        for (ll x : {-2LL, 2LL}) {\n            assert(offline.query(x)\
    \ == empty && online.query(x) == empty);\n            assert(!offline.query_with_id(x)\
    \ && !online.query_with_id(x));\n        }\n        assert(offline.add_line(0,\
    \ value) == 1);\n        assert(online.add_line(0, value) == 1);\n        for\
    \ (ll x : {-2LL, 0LL, 2LL}) {\n            assert(offline.query(x) == value &&\
    \ online.query(x) == value);\n            auto expected = make_pair(value, x ==\
    \ 0 ? 0 : 1);\n            assert(offline.query_with_id(x) == expected && online.query_with_id(x)\
    \ == expected);\n        }\n    }\n    LiChaoTree<ll, get_max> empty_tree({});\n\
    \    assert(empty_tree.add_line(0, 1) == 0);\n    assert(empty_tree.add_segment(1,\
    \ 0, -2, 2) == 1);\n    assert(empty_tree.query(0) == empty);\n    assert(!empty_tree.query_with_id(0));\n\
    \    LiChaoTree<ll, get_max> single({0, 0});\n    OnlineLiChaoTree<ll, get_max>\
    \ single_online(0, 1);\n    assert(single.add_segment(0, 0, 0, 0) == 0);\n   \
    \ assert(single_online.add_segment(0, 0, 0, 0) == 0);\n    assert(single.query(0)\
    \ == empty && single_online.query(0) == empty);\n    assert(single.add_line(0,\
    \ 7) == 1);\n    assert(single_online.add_line(0, 7) == 1);\n    assert(single.query(0)\
    \ == 7 && single_online.query(0) == 7);\n    assert(single.query_with_id(0) ==\
    \ make_pair(7LL, 1));\n    assert(single_online.query_with_id(0) == make_pair(7LL,\
    \ 1));\n    assert(single.query(1) == empty);\n    assert(!single.query_with_id(1));\n\
    \    if constexpr (!get_max) {\n        single.add_line(0, LLONG_MIN);\n     \
    \   single_online.add_line(0, LLONG_MIN);\n        assert(single.query_with_id(0)\
    \ == make_pair(LLONG_MIN, 2));\n        assert(single_online.query_with_id(0)\
    \ == make_pair(LLONG_MIN, 2));\n    }\n}\n\ntemplate<bool get_max>\nvoid check_ties()\
    \ {\n    const vector<array<ll, 4>> lines = {\n        {0, 0, -4, 5}, {1, 0, -4,\
    \ 5}, {-1, 0, -4, 5},\n        {0, 0, -4, 5}, {0, 0, 0, 1}, {1, -1, 1, 5}\n  \
    \  };\n    vector<int> order = {0, 1, 2, 3, 4, 5};\n    do {\n        LiChaoTree<ll,\
    \ get_max> offline({-4, -3, -2, -1, 0, 1, 2, 3, 4});\n        OnlineLiChaoTree<ll,\
    \ get_max> online(-4, 5);\n        for (int id = 0; id < 6; ++id) {\n        \
    \    auto [a, b, l, r] = lines[order[id]];\n            if (order[id] < 4) {\n\
    \                assert(offline.add_line(a, b) == id);\n                assert(online.add_line(a,\
    \ b) == id);\n            } else {\n                assert(offline.add_segment(a,\
    \ b, l, r) == id);\n                assert(online.add_segment(a, b, l, r) == id);\n\
    \            }\n            for (ll x = -4; x <= 4; ++x) {\n                optional<pair<ll,\
    \ int>> expected;\n                for (int j = 0; j <= id; ++j) {\n         \
    \           auto [a, b, l, r] = lines[order[j]];\n                    if (x <\
    \ l || r <= x) continue;\n                    ll value = a * x + b;\n        \
    \            if (!expected || (get_max ? value > expected->first : value < expected->first))\
    \ {\n                        expected = make_pair(value, j);\n               \
    \     }\n                }\n                assert(offline.query_with_id(x) ==\
    \ expected && online.query_with_id(x) == expected);\n            }\n        }\n\
    \    } while (next_permutation(order.begin(), order.end()));\n}\n\ntemplate<bool\
    \ get_max>\nvoid check_pruning() {\n    const ll sign = get_max ? -1 : 1;\n  \
    \  OnlineLiChaoTree<ll, get_max> dominated(-1000000000LL, 1000000001LL);\n   \
    \ dominated.add_line(0, 0);\n    for (int i = 0; i < 1000; ++i) {\n        dominated.add_line(0,\
    \ 0);\n        dominated.add_line(sign * (i % 7), sign * (10000000000LL + i));\n\
    \        dominated.add_segment(0, sign, -1000000000LL, 1000000001LL);\n    }\n\
    \    assert(dominated.nodes.size() == 1);\n    dominated.add_line(0, -sign);\n\
    \    assert(dominated.nodes.size() == 1);\n    for (ll x : {-1000000000LL, 0LL,\
    \ 1000000000LL}) assert(dominated.query(x) == -sign);\n    OnlineLiChaoTree<ll,\
    \ get_max> crossing(0, 1001);\n    for (ll i = 0; i <= 1000; ++i) crossing.add_line(sign\
    \ * (-2 * i), sign * i * i);\n    for (ll x = 0; x <= 1000; ++x) assert(crossing.query(x)\
    \ == -sign * x * x);\n    OnlineLiChaoTree<ll, get_max> endpoint(0, 9);\n    endpoint.add_line(0,\
    \ 0);\n    endpoint.add_line(-sign, 7 * sign);\n    assert(endpoint.query(0) ==\
    \ 0 && endpoint.query(8) == -sign);\n}\n\ntemplate<bool get_max>\nvoid check_random()\
    \ {\n    struct Line {\n        ll a, b, l, r;\n    };\n    const ll inf = numeric_limits<ll>::max()\
    \ / 4;\n    mt19937 rng(100 + get_max);\n    for (int tc = 0; tc < 200; ++tc)\
    \ {\n        vector<ll> xs;\n        for (ll x = -16; x <= 16; ++x)\n        \
    \    if (rng() % 3 != 0) xs.push_back(x);\n        shuffle(xs.begin(), xs.end(),\
    \ rng);\n        if (!xs.empty()) xs.push_back(xs[0]);\n        LiChaoTree<ll,\
    \ get_max> offline(xs);\n        OnlineLiChaoTree<ll, get_max> online(-16, 17);\n\
    \        vector<Line> lines;\n        for (int op = 0; op < 100; ++op) {\n   \
    \         ll a = int(rng() % 17) - 8;\n            ll b = int(rng() % 101) - 50;\n\
    \            if (op % 3 == 0) b += 3000000000000000000LL;\n            if (op\
    \ % 3 == 1) b -= 3000000000000000000LL;\n            ll l = int(rng() % 41) -\
    \ 20, r = int(rng() % 41) - 20;\n            if (rng() % 3 == 0) {\n         \
    \       l = -16;\n                r = 17;\n                assert(offline.add_line(a,\
    \ b) == op);\n                assert(online.add_line(a, b) == op);\n         \
    \   } else {\n                assert(offline.add_segment(a, b, l, r) == op);\n\
    \                assert(online.add_segment(a, b, l, r) == op);\n            }\n\
    \            lines.push_back({a, b, l, r});\n            for (ll x = -16; x <=\
    \ 16; ++x) {\n                optional<pair<ll, int>> expected;\n            \
    \    for (int id = 0; id <= op; ++id) {\n                    const auto &line\
    \ = lines[id];\n                    if (x < line.l || line.r <= x) continue;\n\
    \                    ll y = line.a * x + line.b;\n                    if (!expected\
    \ || (get_max ? y > expected->first : y < expected->first)) {\n              \
    \          expected = make_pair(y, id);\n                    }\n             \
    \   }\n                ll value = expected ? expected->first : (get_max ? -inf\
    \ : inf);\n                assert(online.query(x) == value);\n               \
    \ assert(online.query_with_id(x) == expected);\n                if (find(xs.begin(),\
    \ xs.end(), x) == xs.end()) {\n                    value = get_max ? -inf : inf;\n\
    \                    expected = nullopt;\n                }\n                assert(offline.query(x)\
    \ == value);\n                assert(offline.query_with_id(x) == expected);\n\
    \            }\n        }\n    }\n}\n\nint main() {\n    check_limits<false>();\n\
    \    check_limits<true>();\n    check_ties<false>();\n    check_ties<true>();\n\
    \    check_pruning<false>();\n    check_pruning<true>();\n    check_random<false>();\n\
    \    check_random<true>();\n    Scanner in;\n    Printer out;\n    int a, b;\n\
    \    in.read(a, b);\n    out.println(a + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing ll = long long;\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../datastructure/li_chao_tree.cpp\"\n\ntemplate<bool get_max>\nvoid\
    \ check_limits() {\n    const ll inf = numeric_limits<ll>::max() / 4;\n    const\
    \ ll empty = get_max ? -inf : inf;\n    for (ll value : {0LL, inf, -inf, inf +\
    \ 1, -inf - 1,\n                     3000000000000000000LL, -3000000000000000000LL,\n\
    \                     LLONG_MAX, -LLONG_MAX}) {\n        LiChaoTree<ll, get_max>\
    \ offline({-2, 0, 2});\n        OnlineLiChaoTree<ll, get_max> online(-2, 3);\n\
    \        assert(offline.query(0) == empty && online.query(0) == empty);\n    \
    \    assert(!offline.query_with_id(0) && !online.query_with_id(0));\n        assert(offline.add_segment(0,\
    \ value, 0, 1) == 0);\n        assert(online.add_segment(0, value, 0, 1) == 0);\n\
    \        assert(offline.query(0) == value && online.query(0) == value);\n    \
    \    assert(offline.query_with_id(0) == make_pair(value, 0));\n        assert(online.query_with_id(0)\
    \ == make_pair(value, 0));\n        for (ll x : {-2LL, 2LL}) {\n            assert(offline.query(x)\
    \ == empty && online.query(x) == empty);\n            assert(!offline.query_with_id(x)\
    \ && !online.query_with_id(x));\n        }\n        assert(offline.add_line(0,\
    \ value) == 1);\n        assert(online.add_line(0, value) == 1);\n        for\
    \ (ll x : {-2LL, 0LL, 2LL}) {\n            assert(offline.query(x) == value &&\
    \ online.query(x) == value);\n            auto expected = make_pair(value, x ==\
    \ 0 ? 0 : 1);\n            assert(offline.query_with_id(x) == expected && online.query_with_id(x)\
    \ == expected);\n        }\n    }\n    LiChaoTree<ll, get_max> empty_tree({});\n\
    \    assert(empty_tree.add_line(0, 1) == 0);\n    assert(empty_tree.add_segment(1,\
    \ 0, -2, 2) == 1);\n    assert(empty_tree.query(0) == empty);\n    assert(!empty_tree.query_with_id(0));\n\
    \    LiChaoTree<ll, get_max> single({0, 0});\n    OnlineLiChaoTree<ll, get_max>\
    \ single_online(0, 1);\n    assert(single.add_segment(0, 0, 0, 0) == 0);\n   \
    \ assert(single_online.add_segment(0, 0, 0, 0) == 0);\n    assert(single.query(0)\
    \ == empty && single_online.query(0) == empty);\n    assert(single.add_line(0,\
    \ 7) == 1);\n    assert(single_online.add_line(0, 7) == 1);\n    assert(single.query(0)\
    \ == 7 && single_online.query(0) == 7);\n    assert(single.query_with_id(0) ==\
    \ make_pair(7LL, 1));\n    assert(single_online.query_with_id(0) == make_pair(7LL,\
    \ 1));\n    assert(single.query(1) == empty);\n    assert(!single.query_with_id(1));\n\
    \    if constexpr (!get_max) {\n        single.add_line(0, LLONG_MIN);\n     \
    \   single_online.add_line(0, LLONG_MIN);\n        assert(single.query_with_id(0)\
    \ == make_pair(LLONG_MIN, 2));\n        assert(single_online.query_with_id(0)\
    \ == make_pair(LLONG_MIN, 2));\n    }\n}\n\ntemplate<bool get_max>\nvoid check_ties()\
    \ {\n    const vector<array<ll, 4>> lines = {\n        {0, 0, -4, 5}, {1, 0, -4,\
    \ 5}, {-1, 0, -4, 5},\n        {0, 0, -4, 5}, {0, 0, 0, 1}, {1, -1, 1, 5}\n  \
    \  };\n    vector<int> order = {0, 1, 2, 3, 4, 5};\n    do {\n        LiChaoTree<ll,\
    \ get_max> offline({-4, -3, -2, -1, 0, 1, 2, 3, 4});\n        OnlineLiChaoTree<ll,\
    \ get_max> online(-4, 5);\n        for (int id = 0; id < 6; ++id) {\n        \
    \    auto [a, b, l, r] = lines[order[id]];\n            if (order[id] < 4) {\n\
    \                assert(offline.add_line(a, b) == id);\n                assert(online.add_line(a,\
    \ b) == id);\n            } else {\n                assert(offline.add_segment(a,\
    \ b, l, r) == id);\n                assert(online.add_segment(a, b, l, r) == id);\n\
    \            }\n            for (ll x = -4; x <= 4; ++x) {\n                optional<pair<ll,\
    \ int>> expected;\n                for (int j = 0; j <= id; ++j) {\n         \
    \           auto [a, b, l, r] = lines[order[j]];\n                    if (x <\
    \ l || r <= x) continue;\n                    ll value = a * x + b;\n        \
    \            if (!expected || (get_max ? value > expected->first : value < expected->first))\
    \ {\n                        expected = make_pair(value, j);\n               \
    \     }\n                }\n                assert(offline.query_with_id(x) ==\
    \ expected && online.query_with_id(x) == expected);\n            }\n        }\n\
    \    } while (next_permutation(order.begin(), order.end()));\n}\n\ntemplate<bool\
    \ get_max>\nvoid check_pruning() {\n    const ll sign = get_max ? -1 : 1;\n  \
    \  OnlineLiChaoTree<ll, get_max> dominated(-1000000000LL, 1000000001LL);\n   \
    \ dominated.add_line(0, 0);\n    for (int i = 0; i < 1000; ++i) {\n        dominated.add_line(0,\
    \ 0);\n        dominated.add_line(sign * (i % 7), sign * (10000000000LL + i));\n\
    \        dominated.add_segment(0, sign, -1000000000LL, 1000000001LL);\n    }\n\
    \    assert(dominated.nodes.size() == 1);\n    dominated.add_line(0, -sign);\n\
    \    assert(dominated.nodes.size() == 1);\n    for (ll x : {-1000000000LL, 0LL,\
    \ 1000000000LL}) assert(dominated.query(x) == -sign);\n    OnlineLiChaoTree<ll,\
    \ get_max> crossing(0, 1001);\n    for (ll i = 0; i <= 1000; ++i) crossing.add_line(sign\
    \ * (-2 * i), sign * i * i);\n    for (ll x = 0; x <= 1000; ++x) assert(crossing.query(x)\
    \ == -sign * x * x);\n    OnlineLiChaoTree<ll, get_max> endpoint(0, 9);\n    endpoint.add_line(0,\
    \ 0);\n    endpoint.add_line(-sign, 7 * sign);\n    assert(endpoint.query(0) ==\
    \ 0 && endpoint.query(8) == -sign);\n}\n\ntemplate<bool get_max>\nvoid check_random()\
    \ {\n    struct Line {\n        ll a, b, l, r;\n    };\n    const ll inf = numeric_limits<ll>::max()\
    \ / 4;\n    mt19937 rng(100 + get_max);\n    for (int tc = 0; tc < 200; ++tc)\
    \ {\n        vector<ll> xs;\n        for (ll x = -16; x <= 16; ++x)\n        \
    \    if (rng() % 3 != 0) xs.push_back(x);\n        shuffle(xs.begin(), xs.end(),\
    \ rng);\n        if (!xs.empty()) xs.push_back(xs[0]);\n        LiChaoTree<ll,\
    \ get_max> offline(xs);\n        OnlineLiChaoTree<ll, get_max> online(-16, 17);\n\
    \        vector<Line> lines;\n        for (int op = 0; op < 100; ++op) {\n   \
    \         ll a = int(rng() % 17) - 8;\n            ll b = int(rng() % 101) - 50;\n\
    \            if (op % 3 == 0) b += 3000000000000000000LL;\n            if (op\
    \ % 3 == 1) b -= 3000000000000000000LL;\n            ll l = int(rng() % 41) -\
    \ 20, r = int(rng() % 41) - 20;\n            if (rng() % 3 == 0) {\n         \
    \       l = -16;\n                r = 17;\n                assert(offline.add_line(a,\
    \ b) == op);\n                assert(online.add_line(a, b) == op);\n         \
    \   } else {\n                assert(offline.add_segment(a, b, l, r) == op);\n\
    \                assert(online.add_segment(a, b, l, r) == op);\n            }\n\
    \            lines.push_back({a, b, l, r});\n            for (ll x = -16; x <=\
    \ 16; ++x) {\n                optional<pair<ll, int>> expected;\n            \
    \    for (int id = 0; id <= op; ++id) {\n                    const auto &line\
    \ = lines[id];\n                    if (x < line.l || line.r <= x) continue;\n\
    \                    ll y = line.a * x + line.b;\n                    if (!expected\
    \ || (get_max ? y > expected->first : y < expected->first)) {\n              \
    \          expected = make_pair(y, id);\n                    }\n             \
    \   }\n                ll value = expected ? expected->first : (get_max ? -inf\
    \ : inf);\n                assert(online.query(x) == value);\n               \
    \ assert(online.query_with_id(x) == expected);\n                if (find(xs.begin(),\
    \ xs.end(), x) == xs.end()) {\n                    value = get_max ? -inf : inf;\n\
    \                    expected = nullopt;\n                }\n                assert(offline.query(x)\
    \ == value);\n                assert(offline.query_with_id(x) == expected);\n\
    \            }\n        }\n    }\n}\n\nint main() {\n    check_limits<false>();\n\
    \    check_limits<true>();\n    check_ties<false>();\n    check_ties<true>();\n\
    \    check_pruning<false>();\n    check_pruning<true>();\n    check_random<false>();\n\
    \    check_random<true>();\n    Scanner in;\n    Printer out;\n    int a, b;\n\
    \    in.read(a, b);\n    out.println(a + b);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/li_chao_tree.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_li_chao_tree.test.cpp
  requiredBy: []
  timestamp: '2026-10-06 23:51:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_li_chao_tree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_li_chao_tree.test.cpp
- /verify/test/yosupo_aplusb_li_chao_tree.test.cpp.html
title: test/yosupo_aplusb_li_chao_tree.test.cpp
---
