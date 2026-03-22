---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/dynamic_bitset.cpp
    title: Dynamic Bitset
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B
  bundledCode: "#line 1 \"test/aoj_alds1_14_b_dynamic_bitset.test.cpp\"\n#define PROBLEM\
    \ \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B\"\n\n#include <algorithm>\n\
    #include <string>\n#include <vector>\nusing namespace std;\nusing ull = unsigned\
    \ long long;\n\n#include <cstdio>\n#include <cstring>\n#line 12 \"test/aoj_alds1_14_b_dynamic_bitset.test.cpp\"\
    \n#include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\
    \nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\ntemplate<class\
    \ T, class = void>\nstruct is_fastio_range : false_type {};\n\ntemplate<class\
    \ T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()), decltype(declval<T\
    \ &>().end())>> : true_type {};\n\ntemplate<class T, class = void>\nstruct has_fastio_value\
    \ : false_type {};\n\ntemplate<class T>\nstruct has_fastio_value<T, void_t<decltype(declval<const\
    \ T &>().value())>> : true_type {};\n\nstruct FastIoDigitTable {\n    char num[40000];\n\
    \n    constexpr FastIoDigitTable() : num() {\n        for (int i = 0; i < 10000;\
    \ ++i) {\n            int x = i;\n            for (int j = 3; j >= 0; --j) {\n\
    \                num[i * 4 + j] = char('0' + x % 10);\n                x /= 10;\n\
    \            }\n        }\n    }\n};\n\nstruct Scanner {\n    static constexpr\
    \ int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE\
    \ + 1];\n    int idx, size;\n    bool interactive;\n\n    Scanner() : idx(0),\
    \ size(0), interactive(isatty(fileno(stdin))) {}\n\n    inline void load() {\n\
    \        int len = size - idx;\n        memmove(buf, buf + idx, len);\n      \
    \  if (interactive) {\n            if (fgets(buf + len, BUFSIZE + 1 - len, stdin))\
    \ size = len + (int)strlen(buf + len);\n            else size = len;\n       \
    \ } else {\n            size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n\
    \        }\n        idx = 0;\n        buf[size] = 0;\n    }\n\n    inline void\
    \ ensure() {\n        if (idx + OFFSET > size) load();\n    }\n\n    inline void\
    \ ensure_interactive() {\n        if (idx == size) load();\n    }\n\n    inline\
    \ char skip() {\n        if (interactive) {\n            ensure_interactive();\n\
    \            while (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n \
    \               ensure_interactive();\n            }\n            return buf[idx++];\n\
    \        }\n        ensure();\n        while (buf[idx] && buf[idx] <= ' ') {\n\
    \            ++idx;\n            ensure();\n        }\n        return buf[idx++];\n\
    \    }\n\n    template<class T, typename enable_if<is_integral<T>::value, int>::type\
    \ = 0>\n    void read(T &x) {\n        if (interactive) {\n            char c\
    \ = skip();\n            bool neg = false;\n            if constexpr (is_signed<T>::value)\
    \ {\n                if (c == '-') {\n                    neg = true;\n      \
    \              ensure_interactive();\n                    c = buf[idx++];\n  \
    \              }\n            }\n            x = 0;\n            while (c >= '0')\
    \ {\n                x = x * 10 + (c & 15);\n                ensure_interactive();\n\
    \                c = buf[idx++];\n            }\n            if constexpr (is_signed<T>::value)\
    \ {\n                if (neg) x = -x;\n            }\n            return;\n  \
    \      }\n        char c = skip();\n        bool neg = false;\n        if constexpr\
    \ (is_signed<T>::value) {\n            if (c == '-') {\n                neg =\
    \ true;\n                c = buf[idx++];\n            }\n        }\n        x\
    \ = 0;\n        while (c >= '0') {\n            x = x * 10 + (c & 15);\n     \
    \       c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class T, typename\
    \ enable_if<!is_integral<T>::value && !is_fastio_range<T>::value && !is_same<typename\
    \ decay<T>::type, string>::value && has_fastio_value<T>::value, int>::type = 0>\n\
    \    void read(T &x) {\n        long long v;\n        read(v);\n        x = T(v);\n\
    \    }\n\n    template<class Head, class Next, class... Tail>\n    void read(Head\
    \ &head, Next &next, Tail &...tail) {\n        read(head);\n        read(next,\
    \ tail...);\n    }\n\n    template<class T, class U>\n    void read(pair<T, U>\
    \ &p) {\n        read(p.first, p.second);\n    }\n\n    template<class T, typename\
    \ enable_if<is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value,\
    \ int>::type = 0>\n    void read(T &a) {\n        for (auto &x : a) read(x);\n\
    \    }\n\n    void read(char &c) {\n        c = skip();\n    }\n\n    void read(string\
    \ &s) {\n        s.clear();\n        if (interactive) {\n            ensure_interactive();\n\
    \            while (buf[idx] && buf[idx] <= ' ') {\n                ++idx;\n \
    \               ensure_interactive();\n            }\n            while (true)\
    \ {\n                int start = idx;\n                while (idx < size && buf[idx]\
    \ > ' ') ++idx;\n                s.append(buf + start, idx - start);\n       \
    \         if (idx < size) break;\n                load();\n                if\
    \ (size == 0) break;\n            }\n            if (idx < size) ++idx;\n    \
    \        return;\n        }\n        ensure();\n        while (buf[idx] && buf[idx]\
    \ <= ' ') {\n            ++idx;\n            ensure();\n        }\n        while\
    \ (true) {\n            int start = idx;\n            while (idx < size && buf[idx]\
    \ > ' ') ++idx;\n            s.append(buf + start, idx - start);\n           \
    \ if (idx < size) break;\n            load();\n        }\n        if (idx < size)\
    \ ++idx;\n    }\n};\n\nstruct Printer {\n    static constexpr int BUFSIZE = 1\
    \ << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE];\n    int\
    \ idx;\n    bool interactive;\n    inline static constexpr FastIoDigitTable table{};\n\
    \n    Printer() : idx(0), interactive(isatty(fileno(stdout))) {}\n    ~Printer()\
    \ { flush(); }\n\n    inline void flush() {\n        if (idx) {\n            fwrite(buf,\
    \ 1, idx, stdout);\n            idx = 0;\n        }\n    }\n\n    inline void\
    \ pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++]\
    \ = c;\n        if (interactive && c == '\\n') flush();\n    }\n\n    inline void\
    \ print_range(const char *s, size_t n) {\n        size_t pos = 0;\n        while\
    \ (pos < n) {\n            if (idx == BUFSIZE) flush();\n            size_t chunk\
    \ = min(n - pos, (size_t)(BUFSIZE - idx));\n            memcpy(buf + idx, s +\
    \ pos, chunk);\n            idx += (int)chunk;\n            pos += chunk;\n  \
    \      }\n    }\n\n    void print(const char *s) {\n        print_range(s, strlen(s));\n\
    \    }\n\n    void print(const string &s) {\n        print_range(s.data(), s.size());\n\
    \    }\n\n    void print(char c) {\n        pc(c);\n    }\n\n    void print(bool\
    \ b) {\n        pc(char('0' + (b ? 1 : 0)));\n    }\n\n    template<class T, typename\
    \ enable_if<is_integral<T>::value && !is_same<T, bool>::value, int>::type = 0>\n\
    \    void print(T x) {\n        if (idx > BUFSIZE - 100) flush();\n        using\
    \ U = typename make_unsigned<T>::type;\n        U y;\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (x < 0) {\n                buf[idx++] = '-';\n           \
    \     y = U(0) - static_cast<U>(x);\n            } else {\n                y =\
    \ static_cast<U>(x);\n            }\n        } else {\n            y = x;\n  \
    \      }\n        if (y == 0) {\n            buf[idx++] = '0';\n            return;\n\
    \        }\n        static constexpr int TMP_SIZE = sizeof(U) * 10 / 4;\n    \
    \    char tmp[TMP_SIZE];\n        int pos = TMP_SIZE;\n        while (y >= 10000)\
    \ {\n            pos -= 4;\n            memcpy(tmp + pos, table.num + (y % 10000)\
    \ * 4, 4);\n            y /= 10000;\n        }\n        if (y >= 1000) {\n   \
    \         memcpy(buf + idx, table.num + (y << 2), 4);\n            idx += 4;\n\
    \        } else if (y >= 100) {\n            memcpy(buf + idx, table.num + (y\
    \ << 2) + 1, 3);\n            idx += 3;\n        } else if (y >= 10) {\n     \
    \       unsigned q = (unsigned(y) * 205) >> 11;\n            buf[idx] = char('0'\
    \ + q);\n            buf[idx + 1] = char('0' + (unsigned(y) - q * 10));\n    \
    \        idx += 2;\n        } else {\n            buf[idx++] = char('0' + y);\n\
    \        }\n        memcpy(buf + idx, tmp + pos, TMP_SIZE - pos);\n        idx\
    \ += TMP_SIZE - pos;\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && has_fastio_value<T>::value, int>::type = 0>\n    void print(const T &x) {\n\
    \        print(x.value());\n    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value\
    \ && !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
    \ print(const T &a) {\n        bool first = true;\n        for (auto &&x : a)\
    \ {\n            if (!first) pc(' ');\n            first = false;\n          \
    \  print(x);\n        }\n    }\n\n    template<class T>\n    void println(const\
    \ T &x) {\n        print(x);\n        pc('\\n');\n    }\n\n    template<class\
    \ Head, class... Tail>\n    void println(const Head &head, const Tail &...tail)\
    \ {\n        print(head);\n        ((pc(' '), print(tail)), ...);\n        pc('\\\
    n');\n    }\n\n    void println() {\n        pc('\\n');\n    }\n};\n\ntemplate<class\
    \ T>\nScanner &operator>>(Scanner &in, T &x) {\n    in.read(x);\n    return in;\n\
    }\n\ntemplate<class T>\nPrinter &operator<<(Printer &out, const T &x) {\n    out.print(x);\n\
    \    return out;\n}\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n\
    \ */\n#line 1 \"datastructure/dynamic_bitset.cpp\"\n#if defined(__x86_64__) ||\
    \ defined(_M_X64)\n#include <immintrin.h>\n#endif\n\nusing namespace std;\n\n\
    namespace dynamic_bitset_detail {\nusing Word = unsigned long long;\nconstexpr\
    \ int avx2_threshold_words = 8;\n\n#if defined(__x86_64__) || defined(_M_X64)\n\
    __attribute__((target(\"avx2\"))) inline void and_assign_avx2(Word *dst, const\
    \ Word *src, int m) {\n    int i = 0;\n    for (; i + 4 <= m; i += 4) {\n    \
    \    __m256i x = _mm256_loadu_si256((const __m256i *)(dst + i));\n        __m256i\
    \ y = _mm256_loadu_si256((const __m256i *)(src + i));\n        _mm256_storeu_si256((__m256i\
    \ *)(dst + i), _mm256_and_si256(x, y));\n    }\n    for (; i < m; ++i) dst[i]\
    \ &= src[i];\n}\n\n__attribute__((target(\"avx2\"))) inline void or_assign_avx2(Word\
    \ *dst, const Word *src, int m) {\n    int i = 0;\n    for (; i + 4 <= m; i +=\
    \ 4) {\n        __m256i x = _mm256_loadu_si256((const __m256i *)(dst + i));\n\
    \        __m256i y = _mm256_loadu_si256((const __m256i *)(src + i));\n       \
    \ _mm256_storeu_si256((__m256i *)(dst + i), _mm256_or_si256(x, y));\n    }\n \
    \   for (; i < m; ++i) dst[i] |= src[i];\n}\n\n__attribute__((target(\"avx2\"\
    ))) inline void xor_assign_avx2(Word *dst, const Word *src, int m) {\n    int\
    \ i = 0;\n    for (; i + 4 <= m; i += 4) {\n        __m256i x = _mm256_loadu_si256((const\
    \ __m256i *)(dst + i));\n        __m256i y = _mm256_loadu_si256((const __m256i\
    \ *)(src + i));\n        _mm256_storeu_si256((__m256i *)(dst + i), _mm256_xor_si256(x,\
    \ y));\n    }\n    for (; i < m; ++i) dst[i] ^= src[i];\n}\n\n__attribute__((target(\"\
    avx2\"))) inline bool any_avx2(const Word *src, int m) {\n    __m256i acc = _mm256_setzero_si256();\n\
    \    int i = 0;\n    for (; i + 4 <= m; i += 4) {\n        acc = _mm256_or_si256(acc,\
    \ _mm256_loadu_si256((const __m256i *)(src + i)));\n    }\n    if (!_mm256_testz_si256(acc,\
    \ acc)) return true;\n    for (; i < m; ++i) {\n        if (src[i]) return true;\n\
    \    }\n    return false;\n}\n\n__attribute__((target(\"avx2\"))) inline bool\
    \ all_full_words_avx2(const Word *src, int m) {\n    const __m256i ones = _mm256_set1_epi64x(-1);\n\
    \    int i = 0;\n    for (; i + 4 <= m; i += 4) {\n        __m256i x = _mm256_loadu_si256((const\
    \ __m256i *)(src + i));\n        __m256i eq = _mm256_cmpeq_epi64(x, ones);\n \
    \       if (_mm256_movemask_epi8(eq) != -1) return false;\n    }\n    for (; i\
    \ < m; ++i) {\n        if (src[i] != ~0ULL) return false;\n    }\n    return true;\n\
    }\n\ninline bool has_avx2() {\n    static const bool cached = __builtin_cpu_supports(\"\
    avx2\");\n    return cached;\n}\n#endif\n}  // namespace dynamic_bitset_detail\n\
    \nclass DynamicBitset {\n    static constexpr int B = 64;\n    using Word = unsigned\
    \ long long;\n\n    int n;\n    vector<Word> a;\n\n    static int popcount(Word\
    \ x) {\n        return __builtin_popcountll(x);\n    }\n    static int ctz(Word\
    \ x) {\n        return __builtin_ctzll(x);\n    }\n    static int clz(Word x)\
    \ {\n        return __builtin_clzll(x);\n    }\n\n    Word tail_mask() const {\n\
    \        int rem = n & (B - 1);\n        return rem ? ((1ULL << rem) - 1) : ~0ULL;\n\
    \    }\n\n    void normalize() {\n        if (!a.empty()) a.back() &= tail_mask();\n\
    \    }\n\npublic:\n    DynamicBitset() : n(0) {}\n    explicit DynamicBitset(int\
    \ n, bool x = false) : n(n), a((n + B - 1) >> 6, x ? ~0ULL : 0ULL) {\n       \
    \ normalize();\n    }\n\n    int size() const { return n; }\n    bool empty()\
    \ const { return n == 0; }\n\n    void reset() {\n        fill(a.begin(), a.end(),\
    \ 0);\n    }\n    void set() {\n        fill(a.begin(), a.end(), ~0ULL);\n   \
    \     normalize();\n    }\n    void flip() {\n        Word *p = a.data();\n  \
    \      int m = (int)a.size();\n        for (int i = 0; i < m; ++i) p[i] = ~p[i];\n\
    \        normalize();\n    }\n\n    bool test(int k) const {\n        return (a[k\
    \ >> 6] >> (k & 63)) & 1ULL;\n    }\n    void set(int k) {\n        a[k >> 6]\
    \ |= 1ULL << (k & 63);\n    }\n    void reset(int k) {\n        a[k >> 6] &= ~(1ULL\
    \ << (k & 63));\n    }\n    void flip(int k) {\n        a[k >> 6] ^= 1ULL << (k\
    \ & 63);\n    }\n    void assign(int k, bool x) {\n        if (x) set(k);\n  \
    \      else reset(k);\n    }\n\n    bool any() const {\n        int m = (int)a.size();\n\
    \        const Word *p = a.data();\n#if defined(__x86_64__) || defined(_M_X64)\n\
    \        if (m >= dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2())\
    \ {\n            return dynamic_bitset_detail::any_avx2(p, m);\n        }\n#endif\n\
    \        for (int i = 0; i < m; ++i) {\n            if (p[i]) return true;\n \
    \       }\n        return false;\n    }\n    bool none() const { return !any();\
    \ }\n    bool all() const {\n        int m = (int)a.size();\n        if (m ==\
    \ 0) return true;\n        const Word *p = a.data();\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n        if (m > 1 + dynamic_bitset_detail::avx2_threshold_words\
    \ && dynamic_bitset_detail::has_avx2()) {\n            if (!dynamic_bitset_detail::all_full_words_avx2(p,\
    \ m - 1)) return false;\n        } else\n#endif\n        {\n            for (int\
    \ i = 0; i + 1 < m; ++i) {\n                if (p[i] != ~0ULL) return false;\n\
    \            }\n        }\n        return p[m - 1] == tail_mask();\n    }\n  \
    \  int count() const {\n        const Word *p = a.data();\n        int m = (int)a.size();\n\
    \        int res = 0;\n        int i = 0;\n        for (; i + 4 <= m; i += 4)\
    \ {\n            res += popcount(p[i + 0]) + popcount(p[i + 1]) + popcount(p[i\
    \ + 2]) + popcount(p[i + 3]);\n        }\n        for (; i < m; ++i) res += popcount(p[i]);\n\
    \        return res;\n    }\n\n    int find_first() const {\n        int m = (int)a.size();\n\
    \        const Word *p = a.data();\n        for (int i = 0; i < m; ++i) {\n  \
    \          if (p[i]) return (i << 6) + ctz(p[i]);\n        }\n        return -1;\n\
    \    }\n    int find_last() const {\n        const Word *p = a.data();\n     \
    \   for (int i = (int)a.size() - 1; i >= 0; --i) {\n            if (p[i]) return\
    \ (i << 6) + (B - 1 - clz(p[i]));\n        }\n        return -1;\n    }\n    int\
    \ find_next(int k) const {\n        ++k;\n        if (k >= n) return -1;\n   \
    \     const Word *p = a.data();\n        int i = k >> 6;\n        Word x = p[i]\
    \ & (~0ULL << (k & 63));\n        if (x) return (i << 6) + ctz(x);\n        int\
    \ m = (int)a.size();\n        for (++i; i < m; ++i) {\n            if (p[i]) return\
    \ (i << 6) + ctz(p[i]);\n        }\n        return -1;\n    }\n    int find_prev(int\
    \ k) const {\n        --k;\n        if (k < 0) return -1;\n        const Word\
    \ *p = a.data();\n        int i = k >> 6;\n        int rem = k & 63;\n       \
    \ Word mask = rem == B - 1 ? ~0ULL : ((1ULL << (rem + 1)) - 1);\n        Word\
    \ x = p[i] & mask;\n        if (x) return (i << 6) + (B - 1 - clz(x));\n     \
    \   for (--i; i >= 0; --i) {\n            if (p[i]) return (i << 6) + (B - 1 -\
    \ clz(p[i]));\n        }\n        return -1;\n    }\n\n    DynamicBitset &operator&=(const\
    \ DynamicBitset &r) {\n        Word *p = a.data();\n        const Word *q = r.a.data();\n\
    \        int m = (int)a.size();\n#if defined(__x86_64__) || defined(_M_X64)\n\
    \        if (m >= dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2())\
    \ {\n            dynamic_bitset_detail::and_assign_avx2(p, q, m);\n          \
    \  return *this;\n        }\n#endif\n        for (int i = 0; i < m; ++i) p[i]\
    \ &= q[i];\n        return *this;\n    }\n    DynamicBitset &operator|=(const\
    \ DynamicBitset &r) {\n        Word *p = a.data();\n        const Word *q = r.a.data();\n\
    \        int m = (int)a.size();\n#if defined(__x86_64__) || defined(_M_X64)\n\
    \        if (m >= dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2())\
    \ {\n            dynamic_bitset_detail::or_assign_avx2(p, q, m);\n           \
    \ return *this;\n        }\n#endif\n        for (int i = 0; i < m; ++i) p[i] |=\
    \ q[i];\n        return *this;\n    }\n    DynamicBitset &operator^=(const DynamicBitset\
    \ &r) {\n        Word *p = a.data();\n        const Word *q = r.a.data();\n  \
    \      int m = (int)a.size();\n#if defined(__x86_64__) || defined(_M_X64)\n  \
    \      if (m >= dynamic_bitset_detail::avx2_threshold_words && dynamic_bitset_detail::has_avx2())\
    \ {\n            dynamic_bitset_detail::xor_assign_avx2(p, q, m);\n          \
    \  normalize();\n            return *this;\n        }\n#endif\n        for (int\
    \ i = 0; i < m; ++i) p[i] ^= q[i];\n        normalize();\n        return *this;\n\
    \    }\n\n    friend DynamicBitset operator&(DynamicBitset l, const DynamicBitset\
    \ &r) { return l &= r; }\n    friend DynamicBitset operator|(DynamicBitset l,\
    \ const DynamicBitset &r) { return l |= r; }\n    friend DynamicBitset operator^(DynamicBitset\
    \ l, const DynamicBitset &r) { return l ^= r; }\n\n    DynamicBitset &operator<<=(int\
    \ s) {\n        if (s <= 0 || n == 0) return *this;\n        if (s >= n) {\n \
    \           reset();\n            return *this;\n        }\n        if (s == 1)\
    \ {\n            Word carry = 0;\n            for (int i = 0; i < (int)a.size();\
    \ ++i) {\n                Word next = a[i] >> (B - 1);\n                a[i] =\
    \ (a[i] << 1) | carry;\n                carry = next;\n            }\n       \
    \     normalize();\n            return *this;\n        }\n        int m = (int)a.size();\n\
    \        int block = s >> 6;\n        int rem = s & 63;\n        if (rem == 0)\
    \ {\n            memmove(a.data() + block, a.data(), sizeof(Word) * (m - block));\n\
    \        } else {\n            for (int i = m - 1; i > block; --i) {\n       \
    \         a[i] = (a[i - block] << rem) | (a[i - block - 1] >> (B - rem));\n  \
    \          }\n            a[block] = a[0] << rem;\n        }\n        fill(a.begin(),\
    \ a.begin() + block, 0);\n        normalize();\n        return *this;\n    }\n\
    \    DynamicBitset &operator>>=(int s) {\n        if (s <= 0 || n == 0) return\
    \ *this;\n        if (s >= n) {\n            reset();\n            return *this;\n\
    \        }\n        if (s == 1) {\n            int m = (int)a.size();\n      \
    \      for (int i = 0; i < m; ++i) {\n                Word next = i + 1 < m ?\
    \ (a[i + 1] << (B - 1)) : 0;\n                a[i] = (a[i] >> 1) | next;\n   \
    \         }\n            normalize();\n            return *this;\n        }\n\
    \        int m = (int)a.size();\n        int block = s >> 6;\n        int rem\
    \ = s & 63;\n        if (rem == 0) {\n            memmove(a.data(), a.data() +\
    \ block, sizeof(Word) * (m - block));\n        } else {\n            int last\
    \ = m - block - 1;\n            for (int i = 0; i < last; ++i) {\n           \
    \     a[i] = (a[i + block] >> rem) | (a[i + block + 1] << (B - rem));\n      \
    \      }\n            a[last] = a[m - 1] >> rem;\n        }\n        fill(a.begin()\
    \ + (m - block), a.end(), 0);\n        normalize();\n        return *this;\n \
    \   }\n\n    friend DynamicBitset operator<<(DynamicBitset l, int s) { return\
    \ l <<= s; }\n    friend DynamicBitset operator>>(DynamicBitset l, int s) { return\
    \ l >>= s; }\n};\n\n/**\n * @brief \u52D5\u7684bitset(Dynamic Bitset)\n */\n#line\
    \ 16 \"test/aoj_alds1_14_b_dynamic_bitset.test.cpp\"\n\nint main() {\n    Scanner\
    \ sc;\n    Printer pr;\n\n    string text, pattern;\n    sc.read(text, pattern);\n\
    \n    int m = pattern.size();\n    if (m == 0) {\n        for (int i = 0; i <=\
    \ (int)text.size(); ++i) pr.println(i);\n        return 0;\n    }\n\n    vector<DynamicBitset>\
    \ mask(256, DynamicBitset(m));\n    for (int i = 0; i < m; ++i) mask[(unsigned\
    \ char)pattern[i]].set(i);\n\n    DynamicBitset cur(m), head(m);\n    head.set(0);\n\
    \    for (int i = 0; i < (int)text.size(); ++i) {\n        cur <<= 1;\n      \
    \  cur |= head;\n        cur &= mask[(unsigned char)text[i]];\n        if (cur.test(m\
    \ - 1)) pr.println(i - m + 1);\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B\"\n\
    \n#include <algorithm>\n#include <string>\n#include <vector>\nusing namespace\
    \ std;\nusing ull = unsigned long long;\n\n#include <cstdio>\n#include <cstring>\n\
    #include <string>\n#include <type_traits>\n\n#include \"../util/fastio.cpp\"\n\
    #include \"../datastructure/dynamic_bitset.cpp\"\n\nint main() {\n    Scanner\
    \ sc;\n    Printer pr;\n\n    string text, pattern;\n    sc.read(text, pattern);\n\
    \n    int m = pattern.size();\n    if (m == 0) {\n        for (int i = 0; i <=\
    \ (int)text.size(); ++i) pr.println(i);\n        return 0;\n    }\n\n    vector<DynamicBitset>\
    \ mask(256, DynamicBitset(m));\n    for (int i = 0; i < m; ++i) mask[(unsigned\
    \ char)pattern[i]].set(i);\n\n    DynamicBitset cur(m), head(m);\n    head.set(0);\n\
    \    for (int i = 0; i < (int)text.size(); ++i) {\n        cur <<= 1;\n      \
    \  cur |= head;\n        cur &= mask[(unsigned char)text[i]];\n        if (cur.test(m\
    \ - 1)) pr.println(i - m + 1);\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/dynamic_bitset.cpp
  isVerificationFile: true
  path: test/aoj_alds1_14_b_dynamic_bitset.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 13:44:11+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj_alds1_14_b_dynamic_bitset.test.cpp
layout: document
redirect_from:
- /verify/test/aoj_alds1_14_b_dynamic_bitset.test.cpp
- /verify/test/aoj_alds1_14_b_dynamic_bitset.test.cpp.html
title: test/aoj_alds1_14_b_dynamic_bitset.test.cpp
---
