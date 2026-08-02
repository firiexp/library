---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/order_statistic_tree.cpp
    title: "\u9806\u5E8F\u6728(Order Statistic Tree)"
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_order_statistic_tree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <numeric>\n#include <random>\n#include <set>\n#include\
    \ <utility>\n#include <vector>\nusing namespace std;\n\n#include <ext/pb_ds/assoc_container.hpp>\n\
    #include <ext/pb_ds/tree_policy.hpp>\nusing namespace __gnu_pbds;\n\nusing ll\
    \ = long long;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n#include\
    \ <type_traits>\n\n#include <charconv>\n#line 1 \"util/fastio.cpp\"\nusing namespace\
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
    }\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line 1 \"datastructure/order_statistic_tree.cpp\"\
    \ntemplate<class T, class Compare = less<T>>\nclass OrderStatisticTree {\nprivate:\n\
    \    struct Node {\n        T key;\n        int cnt;\n        int sz;\n      \
    \  uint32_t pri;\n        int l;\n        int r;\n\n        Node(const T& key_,\
    \ uint32_t pri_)\n            : key(key_), cnt(1), sz(1), pri(pri_), l(-1), r(-1)\
    \ {}\n    };\n\n    int root_ = -1;\n    uint32_t rng_ = 2463534242u;\n    vector<Node>\
    \ nodes_;\n    vector<int> free_nodes_;\n    Compare comp_;\n\n    int size(int\
    \ t) const {\n        return t == -1 ? 0 : nodes_[t].sz;\n    }\n\n    bool equal_key(const\
    \ T& a, const T& b) const {\n        return !comp_(a, b) && !comp_(b, a);\n  \
    \  }\n\n    void pull(int t) {\n        if (t == -1) return;\n        Node& node\
    \ = nodes_[t];\n        node.sz = node.cnt + size(node.l) + size(node.r);\n  \
    \  }\n\n    uint32_t next_rand() {\n        uint32_t x = rng_;\n        x ^= x\
    \ << 13;\n        x ^= x >> 17;\n        x ^= x << 5;\n        rng_ = x;\n   \
    \     return x;\n    }\n\n    int make_node(const T& x) {\n        uint32_t pri\
    \ = next_rand();\n        if (!free_nodes_.empty()) {\n            int idx = free_nodes_.back();\n\
    \            free_nodes_.pop_back();\n            nodes_[idx] = Node(x, pri);\n\
    \            return idx;\n        }\n        nodes_.emplace_back(x, pri);\n  \
    \      return (int)nodes_.size() - 1;\n    }\n\n    void recycle_node(int t) {\n\
    \        if (t != -1) free_nodes_.push_back(t);\n    }\n\n    void rotate_left(int&\
    \ t) {\n        int r = nodes_[t].r;\n        nodes_[t].r = nodes_[r].l;\n   \
    \     nodes_[r].l = t;\n        pull(t);\n        pull(r);\n        t = r;\n \
    \   }\n\n    void rotate_right(int& t) {\n        int l = nodes_[t].l;\n     \
    \   nodes_[t].l = nodes_[l].r;\n        nodes_[l].r = t;\n        pull(t);\n \
    \       pull(l);\n        t = l;\n    }\n\n    void insert(int& t, const T& x)\
    \ {\n        if (t == -1) {\n            t = make_node(x);\n            return;\n\
    \        }\n\n        if (equal_key(x, nodes_[t].key)) {\n            ++nodes_[t].cnt;\n\
    \            pull(t);\n            return;\n        }\n\n        if (comp_(x,\
    \ nodes_[t].key)) {\n            int child = nodes_[t].l;\n            insert(child,\
    \ x);\n            nodes_[t].l = child;\n            if (nodes_[nodes_[t].l].pri\
    \ > nodes_[t].pri) rotate_right(t);\n        } else {\n            int child =\
    \ nodes_[t].r;\n            insert(child, x);\n            nodes_[t].r = child;\n\
    \            if (nodes_[nodes_[t].r].pri > nodes_[t].pri) rotate_left(t);\n  \
    \      }\n        pull(t);\n    }\n\n    bool erase_one(int& t, const T& x) {\n\
    \        if (t == -1) return false;\n\n        bool ok = false;\n        if (comp_(x,\
    \ nodes_[t].key)) {\n            int child = nodes_[t].l;\n            ok = erase_one(child,\
    \ x);\n            nodes_[t].l = child;\n        } else if (comp_(nodes_[t].key,\
    \ x)) {\n            int child = nodes_[t].r;\n            ok = erase_one(child,\
    \ x);\n            nodes_[t].r = child;\n        } else {\n            ok = true;\n\
    \            if (nodes_[t].cnt > 1) {\n                --nodes_[t].cnt;\n    \
    \            pull(t);\n                return true;\n            }\n         \
    \   if (nodes_[t].l == -1 || nodes_[t].r == -1) {\n                int old = t;\n\
    \                t = nodes_[old].l != -1 ? nodes_[old].l : nodes_[old].r;\n  \
    \              recycle_node(old);\n                return true;\n            }\n\
    \            if (nodes_[nodes_[t].l].pri > nodes_[nodes_[t].r].pri) {\n      \
    \          rotate_right(t);\n                int child = nodes_[t].r;\n      \
    \          ok = erase_one(child, x);\n                nodes_[t].r = child;\n \
    \           } else {\n                rotate_left(t);\n                int child\
    \ = nodes_[t].l;\n                ok = erase_one(child, x);\n                nodes_[t].l\
    \ = child;\n            }\n        }\n\n        if (t != -1) pull(t);\n      \
    \  return ok;\n    }\n\npublic:\n    explicit OrderStatisticTree(uint32_t seed\
    \ = 2463534242u, Compare comp = Compare())\n        : root_(-1), rng_(seed), comp_(comp)\
    \ {\n        if (rng_ == 0) rng_ = 2463534242u;\n    }\n\n    void reserve(int\
    \ capacity) {\n        assert(capacity >= 0);\n        nodes_.reserve(capacity);\n\
    \        free_nodes_.reserve(capacity);\n    }\n\n    int size() const {\n   \
    \     return size(root_);\n    }\n\n    bool empty() const {\n        return root_\
    \ == -1;\n    }\n\n    void insert(const T& x) {\n        insert(root_, x);\n\
    \    }\n\n    bool erase_one(const T& x) {\n        return erase_one(root_, x);\n\
    \    }\n\n    int count(const T& x) const {\n        int t = root_;\n        while\
    \ (t != -1) {\n            const Node& node = nodes_[t];\n            if (equal_key(x,\
    \ node.key)) return node.cnt;\n            t = comp_(x, node.key) ? node.l : node.r;\n\
    \        }\n        return 0;\n    }\n\n    bool contains(const T& x) const {\n\
    \        return count(x) > 0;\n    }\n\n    T find_by_order(int k) const {\n \
    \       assert(0 <= k && k < size());\n\n        int t = root_;\n        while\
    \ (true) {\n            const Node& node = nodes_[t];\n            int left_sz\
    \ = size(node.l);\n            if (k < left_sz) {\n                t = node.l;\n\
    \            } else if (k < left_sz + node.cnt) {\n                return node.key;\n\
    \            } else {\n                k -= left_sz + node.cnt;\n            \
    \    t = node.r;\n            }\n        }\n    }\n\n    int order_of_key(const\
    \ T& x) const {\n        int res = 0;\n        int t = root_;\n        while (t\
    \ != -1) {\n            const Node& node = nodes_[t];\n            if (comp_(node.key,\
    \ x)) {\n                res += size(node.l) + node.cnt;\n                t =\
    \ node.r;\n            } else {\n                t = node.l;\n            }\n\
    \        }\n        return res;\n    }\n};\n\n/**\n * @brief \u9806\u5E8F\u6728\
    (Order Statistic Tree)\n */\n#line 26 \"test/yosupo_aplusb_order_statistic_tree.test.cpp\"\
    \n\ntemplate<class Compare>\nvector<int> sorted_values(vector<int> a, Compare\
    \ comp) {\n    sort(a.begin(), a.end(), comp);\n    return a;\n}\n\ntemplate<class\
    \ Compare>\nint brute_order_of_key(const vector<int>& a, int x, Compare comp)\
    \ {\n    int res = 0;\n    for (int y : a) {\n        if (comp(y, x)) ++res;\n\
    \    }\n    return res;\n}\n\ntemplate<class Compare>\nvoid verify_multiset_state(const\
    \ OrderStatisticTree<int, Compare>& st, const vector<int>& cur, Compare comp)\
    \ {\n    vector<int> ord = sorted_values(cur, comp);\n    assert(st.size() ==\
    \ (int)cur.size());\n    assert(st.empty() == cur.empty());\n\n    for (int x\
    \ = -20; x <= 20; ++x) {\n        int cnt = count(cur.begin(), cur.end(), x);\n\
    \        assert(st.count(x) == cnt);\n        assert(st.contains(x) == (cnt >\
    \ 0));\n        assert(st.order_of_key(x) == brute_order_of_key(cur, x, comp));\n\
    \    }\n    for (int k = 0; k < (int)ord.size(); ++k) {\n        assert(st.find_by_order(k)\
    \ == ord[k]);\n    }\n}\n\nvoid self_check_multiset() {\n    mt19937 rng(0);\n\
    \    for (int tc = 0; tc < 300; ++tc) {\n        OrderStatisticTree<int> asc(rng());\n\
    \        OrderStatisticTree<int, greater<int>> desc(rng());\n        asc.reserve(256);\n\
    \        desc.reserve(256);\n        vector<int> cur;\n\n        for (int step\
    \ = 0; step < 200; ++step) {\n            int op = rng() % 3;\n            int\
    \ x = (int)(rng() % 31) - 15;\n            if (op <= 1) {\n                asc.insert(x);\n\
    \                desc.insert(x);\n                cur.push_back(x);\n        \
    \    } else {\n                bool ok1 = asc.erase_one(x);\n                bool\
    \ ok2 = desc.erase_one(x);\n                auto it = find(cur.begin(), cur.end(),\
    \ x);\n                bool ok3 = it != cur.end();\n                if (ok3) cur.erase(it);\n\
    \                assert(ok1 == ok2);\n                assert(ok2 == ok3);\n  \
    \          }\n\n            verify_multiset_state(asc, cur, less<int>());\n  \
    \          verify_multiset_state(desc, cur, greater<int>());\n        }\n    }\n\
    }\n\nvoid self_check_pbds_like_unique_keys() {\n    mt19937 rng(1);\n    using\
    \ Key = pair<int, int>;\n    using PbdsTree = tree<Key, null_type, less<Key>,\
    \ rb_tree_tag, tree_order_statistics_node_update>;\n\n    OrderStatisticTree<Key>\
    \ st;\n    PbdsTree pbds;\n    st.reserve(1000);\n    vector<Key> live;\n\n  \
    \  for (int step = 0; step < 1000; ++step) {\n        int op = rng() % 4;\n  \
    \      if (op <= 1 || live.empty()) {\n            Key key((int)(rng() % 101)\
    \ - 50, step);\n            st.insert(key);\n            pbds.insert(key);\n \
    \           live.push_back(key);\n        } else {\n            int idx = rng()\
    \ % live.size();\n            Key key = live[idx];\n            assert(st.erase_one(key));\n\
    \            assert(pbds.erase(key) == 1);\n            live.erase(live.begin()\
    \ + idx);\n        }\n\n        assert(st.size() == (int)pbds.size());\n     \
    \   for (int k = 0; k < st.size(); ++k) {\n            assert(st.find_by_order(k)\
    \ == *pbds.find_by_order(k));\n        }\n        for (int rep = 0; rep < 16;\
    \ ++rep) {\n            Key key((int)(rng() % 111) - 55, (int)(rng() % 1200));\n\
    \            assert(st.order_of_key(key) == (int)pbds.order_of_key(key));\n  \
    \      }\n    }\n}\n\nint main() {\n    self_check_multiset();\n    self_check_pbds_like_unique_keys();\n\
    \n    Scanner sc;\n    Printer pr;\n    ll a, b;\n    sc.read(a, b);\n    pr.println(a\
    \ + b);\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <numeric>\n#include <random>\n#include <set>\n#include\
    \ <utility>\n#include <vector>\nusing namespace std;\n\n#include <ext/pb_ds/assoc_container.hpp>\n\
    #include <ext/pb_ds/tree_policy.hpp>\nusing namespace __gnu_pbds;\n\nusing ll\
    \ = long long;\n\n#include <cstdio>\n#include <cstring>\n#include <string>\n#include\
    \ <type_traits>\n\n#include <charconv>\n#include \"../util/fastio.cpp\"\n#include\
    \ \"../datastructure/order_statistic_tree.cpp\"\n\ntemplate<class Compare>\nvector<int>\
    \ sorted_values(vector<int> a, Compare comp) {\n    sort(a.begin(), a.end(), comp);\n\
    \    return a;\n}\n\ntemplate<class Compare>\nint brute_order_of_key(const vector<int>&\
    \ a, int x, Compare comp) {\n    int res = 0;\n    for (int y : a) {\n       \
    \ if (comp(y, x)) ++res;\n    }\n    return res;\n}\n\ntemplate<class Compare>\n\
    void verify_multiset_state(const OrderStatisticTree<int, Compare>& st, const vector<int>&\
    \ cur, Compare comp) {\n    vector<int> ord = sorted_values(cur, comp);\n    assert(st.size()\
    \ == (int)cur.size());\n    assert(st.empty() == cur.empty());\n\n    for (int\
    \ x = -20; x <= 20; ++x) {\n        int cnt = count(cur.begin(), cur.end(), x);\n\
    \        assert(st.count(x) == cnt);\n        assert(st.contains(x) == (cnt >\
    \ 0));\n        assert(st.order_of_key(x) == brute_order_of_key(cur, x, comp));\n\
    \    }\n    for (int k = 0; k < (int)ord.size(); ++k) {\n        assert(st.find_by_order(k)\
    \ == ord[k]);\n    }\n}\n\nvoid self_check_multiset() {\n    mt19937 rng(0);\n\
    \    for (int tc = 0; tc < 300; ++tc) {\n        OrderStatisticTree<int> asc(rng());\n\
    \        OrderStatisticTree<int, greater<int>> desc(rng());\n        asc.reserve(256);\n\
    \        desc.reserve(256);\n        vector<int> cur;\n\n        for (int step\
    \ = 0; step < 200; ++step) {\n            int op = rng() % 3;\n            int\
    \ x = (int)(rng() % 31) - 15;\n            if (op <= 1) {\n                asc.insert(x);\n\
    \                desc.insert(x);\n                cur.push_back(x);\n        \
    \    } else {\n                bool ok1 = asc.erase_one(x);\n                bool\
    \ ok2 = desc.erase_one(x);\n                auto it = find(cur.begin(), cur.end(),\
    \ x);\n                bool ok3 = it != cur.end();\n                if (ok3) cur.erase(it);\n\
    \                assert(ok1 == ok2);\n                assert(ok2 == ok3);\n  \
    \          }\n\n            verify_multiset_state(asc, cur, less<int>());\n  \
    \          verify_multiset_state(desc, cur, greater<int>());\n        }\n    }\n\
    }\n\nvoid self_check_pbds_like_unique_keys() {\n    mt19937 rng(1);\n    using\
    \ Key = pair<int, int>;\n    using PbdsTree = tree<Key, null_type, less<Key>,\
    \ rb_tree_tag, tree_order_statistics_node_update>;\n\n    OrderStatisticTree<Key>\
    \ st;\n    PbdsTree pbds;\n    st.reserve(1000);\n    vector<Key> live;\n\n  \
    \  for (int step = 0; step < 1000; ++step) {\n        int op = rng() % 4;\n  \
    \      if (op <= 1 || live.empty()) {\n            Key key((int)(rng() % 101)\
    \ - 50, step);\n            st.insert(key);\n            pbds.insert(key);\n \
    \           live.push_back(key);\n        } else {\n            int idx = rng()\
    \ % live.size();\n            Key key = live[idx];\n            assert(st.erase_one(key));\n\
    \            assert(pbds.erase(key) == 1);\n            live.erase(live.begin()\
    \ + idx);\n        }\n\n        assert(st.size() == (int)pbds.size());\n     \
    \   for (int k = 0; k < st.size(); ++k) {\n            assert(st.find_by_order(k)\
    \ == *pbds.find_by_order(k));\n        }\n        for (int rep = 0; rep < 16;\
    \ ++rep) {\n            Key key((int)(rng() % 111) - 55, (int)(rng() % 1200));\n\
    \            assert(st.order_of_key(key) == (int)pbds.order_of_key(key));\n  \
    \      }\n    }\n}\n\nint main() {\n    self_check_multiset();\n    self_check_pbds_like_unique_keys();\n\
    \n    Scanner sc;\n    Printer pr;\n    ll a, b;\n    sc.read(a, b);\n    pr.println(a\
    \ + b);\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/order_statistic_tree.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_order_statistic_tree.test.cpp
  requiredBy: []
  timestamp: '2026-08-02 21:15:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_order_statistic_tree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_order_statistic_tree.test.cpp
- /verify/test/yosupo_aplusb_order_statistic_tree.test.cpp.html
title: test/yosupo_aplusb_order_statistic_tree.test.cpp
---
