---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/static_bitset.cpp
    title: "\u56FA\u5B9A\u9577bitset(Static Bitset)"
  - icon: ':question:'
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
  bundledCode: "#line 1 \"test/yosupo_aplusb_static_bitset.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <random>\n#include <vector>\nusing namespace std;\n\n#include\
    \ <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\n\
    #line 1 \"util/fastio.cpp\"\nusing namespace std;\n\nextern \"C\" int fileno(FILE\
    \ *);\nextern \"C\" int isatty(int);\n\ntemplate<class T, class = void>\nstruct\
    \ is_fastio_range : false_type {};\n\ntemplate<class T>\nstruct is_fastio_range<T,\
    \ void_t<decltype(declval<T &>().begin()), decltype(declval<T &>().end())>> :\
    \ true_type {};\n\ntemplate<class T, class = void>\nstruct has_fastio_value :\
    \ false_type {};\n\ntemplate<class T>\nstruct has_fastio_value<T, void_t<decltype(declval<const\
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
    \ */\n#line 1 \"datastructure/static_bitset.cpp\"\n#if defined(__x86_64__) ||\
    \ defined(_M_X64)\n#include <immintrin.h>\n#endif\n\nusing namespace std;\n\n\
    namespace static_bitset_detail {\nusing Word = unsigned long long;\nconstexpr\
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
    avx2\");\n    return cached;\n}\n#endif\n}  // namespace static_bitset_detail\n\
    \ntemplate<int N>\nclass StaticBitset {\n    static_assert(N >= 0);\n    static\
    \ constexpr int B = 64;\n    static constexpr int M = (N + B - 1) >> 6;\n    using\
    \ Word = unsigned long long;\n\n    Word a[M > 0 ? M : 1];\n\n    static int popcount(Word\
    \ x) {\n        return __builtin_popcountll(x);\n    }\n    static int ctz(Word\
    \ x) {\n        return __builtin_ctzll(x);\n    }\n    static int clz(Word x)\
    \ {\n        return __builtin_clzll(x);\n    }\n    static constexpr Word tail_mask()\
    \ {\n        return N % B ? ((1ULL << (N % B)) - 1) : ~0ULL;\n    }\n    void\
    \ normalize() {\n        if constexpr (M > 0) a[M - 1] &= tail_mask();\n    }\n\
    \npublic:\n    explicit StaticBitset(bool x = false) : a{} {\n        if (x) set();\n\
    \    }\n\n    int size() const { return N; }\n    bool empty() const { return\
    \ N == 0; }\n\n    void reset() {\n        fill(a, a + M, 0);\n    }\n    void\
    \ set() {\n        fill(a, a + M, ~0ULL);\n        normalize();\n    }\n    void\
    \ flip() {\n        for (Word &x : a) x = ~x;\n        normalize();\n    }\n\n\
    \    bool test(int k) const {\n        return (a[k >> 6] >> (k & 63)) & 1ULL;\n\
    \    }\n    void set(int k) {\n        a[k >> 6] |= 1ULL << (k & 63);\n    }\n\
    \    void reset(int k) {\n        a[k >> 6] &= ~(1ULL << (k & 63));\n    }\n \
    \   void flip(int k) {\n        a[k >> 6] ^= 1ULL << (k & 63);\n    }\n    void\
    \ assign(int k, bool x) {\n        if (x) set(k);\n        else reset(k);\n  \
    \  }\n\n    bool any() const {\n        const Word *p = a;\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n        if constexpr (M >= static_bitset_detail::avx2_threshold_words)\
    \ {\n            if (static_bitset_detail::has_avx2()) return static_bitset_detail::any_avx2(p,\
    \ M);\n        }\n#endif\n        for (int i = 0; i < M; ++i) {\n            if\
    \ (p[i]) return true;\n        }\n        return false;\n    }\n    bool none()\
    \ const { return !any(); }\n    bool all() const {\n        if constexpr (M ==\
    \ 0) return true;\n        const Word *p = a;\n#if defined(__x86_64__) || defined(_M_X64)\n\
    \        if constexpr (M > 1 + static_bitset_detail::avx2_threshold_words) {\n\
    \            if (static_bitset_detail::has_avx2()) {\n                if (!static_bitset_detail::all_full_words_avx2(p,\
    \ M - 1)) return false;\n                return p[M - 1] == tail_mask();\n   \
    \         }\n        }\n#endif\n        for (int i = 0; i + 1 < M; ++i) {\n  \
    \          if (p[i] != ~0ULL) return false;\n        }\n        return p[M - 1]\
    \ == tail_mask();\n    }\n    int count() const {\n        const Word *p = a;\n\
    \        int res = 0;\n        int i = 0;\n        for (; i + 4 <= M; i += 4)\
    \ {\n            res += popcount(p[i + 0]) + popcount(p[i + 1]) + popcount(p[i\
    \ + 2]) + popcount(p[i + 3]);\n        }\n        for (; i < M; ++i) res += popcount(p[i]);\n\
    \        return res;\n    }\n\n    int find_first() const {\n        const Word\
    \ *p = a;\n        for (int i = 0; i < M; ++i) {\n            if (p[i]) return\
    \ (i << 6) + ctz(p[i]);\n        }\n        return -1;\n    }\n    int find_last()\
    \ const {\n        const Word *p = a;\n        for (int i = M - 1; i >= 0; --i)\
    \ {\n            if (p[i]) return (i << 6) + (B - 1 - clz(p[i]));\n        }\n\
    \        return -1;\n    }\n    int find_next(int k) const {\n        ++k;\n \
    \       if (k >= N) return -1;\n        const Word *p = a;\n        int i = k\
    \ >> 6;\n        Word x = p[i] & (~0ULL << (k & 63));\n        if (x) return (i\
    \ << 6) + ctz(x);\n        for (++i; i < M; ++i) {\n            if (p[i]) return\
    \ (i << 6) + ctz(p[i]);\n        }\n        return -1;\n    }\n    int find_prev(int\
    \ k) const {\n        --k;\n        if (k < 0) return -1;\n        const Word\
    \ *p = a;\n        int i = k >> 6;\n        int rem = k & 63;\n        Word mask\
    \ = rem == B - 1 ? ~0ULL : ((1ULL << (rem + 1)) - 1);\n        Word x = p[i] &\
    \ mask;\n        if (x) return (i << 6) + (B - 1 - clz(x));\n        for (--i;\
    \ i >= 0; --i) {\n            if (p[i]) return (i << 6) + (B - 1 - clz(p[i]));\n\
    \        }\n        return -1;\n    }\n\n    StaticBitset &operator&=(const StaticBitset\
    \ &r) {\n        Word *p = a;\n        const Word *q = r.a;\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n        if constexpr (M >= static_bitset_detail::avx2_threshold_words)\
    \ {\n            if (static_bitset_detail::has_avx2()) {\n                static_bitset_detail::and_assign_avx2(p,\
    \ q, M);\n                return *this;\n            }\n        }\n#endif\n  \
    \      for (int i = 0; i < M; ++i) p[i] &= q[i];\n        return *this;\n    }\n\
    \    StaticBitset &operator|=(const StaticBitset &r) {\n        Word *p = a;\n\
    \        const Word *q = r.a;\n#if defined(__x86_64__) || defined(_M_X64)\n  \
    \      if constexpr (M >= static_bitset_detail::avx2_threshold_words) {\n    \
    \        if (static_bitset_detail::has_avx2()) {\n                static_bitset_detail::or_assign_avx2(p,\
    \ q, M);\n                return *this;\n            }\n        }\n#endif\n  \
    \      for (int i = 0; i < M; ++i) p[i] |= q[i];\n        return *this;\n    }\n\
    \    StaticBitset &operator^=(const StaticBitset &r) {\n        Word *p = a;\n\
    \        const Word *q = r.a;\n#if defined(__x86_64__) || defined(_M_X64)\n  \
    \      if constexpr (M >= static_bitset_detail::avx2_threshold_words) {\n    \
    \        if (static_bitset_detail::has_avx2()) {\n                static_bitset_detail::xor_assign_avx2(p,\
    \ q, M);\n                normalize();\n                return *this;\n      \
    \      }\n        }\n#endif\n        for (int i = 0; i < M; ++i) p[i] ^= q[i];\n\
    \        normalize();\n        return *this;\n    }\n\n    friend StaticBitset\
    \ operator&(StaticBitset l, const StaticBitset &r) { return l &= r; }\n    friend\
    \ StaticBitset operator|(StaticBitset l, const StaticBitset &r) { return l |=\
    \ r; }\n    friend StaticBitset operator^(StaticBitset l, const StaticBitset &r)\
    \ { return l ^= r; }\n\n    StaticBitset &operator<<=(int s) {\n        if (s\
    \ <= 0 || N == 0) return *this;\n        if (s >= N) {\n            reset();\n\
    \            return *this;\n        }\n        if (s == 1) {\n            Word\
    \ carry = 0;\n            for (int i = 0; i < M; ++i) {\n                Word\
    \ next = a[i] >> (B - 1);\n                a[i] = (a[i] << 1) | carry;\n     \
    \           carry = next;\n            }\n            normalize();\n         \
    \   return *this;\n        }\n        int block = s >> 6;\n        int rem = s\
    \ & 63;\n        if (rem == 0) {\n            memmove(a + block, a, sizeof(Word)\
    \ * (M - block));\n        } else {\n            for (int i = M - 1; i > block;\
    \ --i) {\n                a[i] = (a[i - block] << rem) | (a[i - block - 1] >>\
    \ (B - rem));\n            }\n            a[block] = a[0] << rem;\n        }\n\
    \        fill(a, a + block, 0);\n        normalize();\n        return *this;\n\
    \    }\n    StaticBitset &operator>>=(int s) {\n        if (s <= 0 || N == 0)\
    \ return *this;\n        if (s >= N) {\n            reset();\n            return\
    \ *this;\n        }\n        if (s == 1) {\n            for (int i = 0; i < M;\
    \ ++i) {\n                Word next = i + 1 < M ? (a[i + 1] << (B - 1)) : 0;\n\
    \                a[i] = (a[i] >> 1) | next;\n            }\n            normalize();\n\
    \            return *this;\n        }\n        int block = s >> 6;\n        int\
    \ rem = s & 63;\n        if (rem == 0) {\n            memmove(a, a + block, sizeof(Word)\
    \ * (M - block));\n        } else {\n            int last = M - block - 1;\n \
    \           for (int i = 0; i < last; ++i) {\n                a[i] = (a[i + block]\
    \ >> rem) | (a[i + block + 1] << (B - rem));\n            }\n            a[last]\
    \ = a[M - 1] >> rem;\n        }\n        fill(a + (M - block), a + M, 0);\n  \
    \      normalize();\n        return *this;\n    }\n\n    friend StaticBitset operator<<(StaticBitset\
    \ l, int s) { return l <<= s; }\n    friend StaticBitset operator>>(StaticBitset\
    \ l, int s) { return l >>= s; }\n};\n\n/**\n * @brief \u56FA\u5B9A\u9577bitset(Static\
    \ Bitset)\n */\n#line 16 \"test/yosupo_aplusb_static_bitset.test.cpp\"\n\ntemplate<int\
    \ N>\nvector<int> to_vec(const StaticBitset<N> &bs) {\n    vector<int> res(N);\n\
    \    for (int i = 0; i < N; ++i) res[i] = bs.test(i);\n    return res;\n}\n\n\
    int brute_find_first(const vector<int> &a) {\n    for (int i = 0; i < (int)a.size();\
    \ ++i) if (a[i]) return i;\n    return -1;\n}\n\nint brute_find_last(const vector<int>\
    \ &a) {\n    for (int i = (int)a.size() - 1; i >= 0; --i) if (a[i]) return i;\n\
    \    return -1;\n}\n\nint brute_find_next(const vector<int> &a, int k) {\n   \
    \ for (int i = k + 1; i < (int)a.size(); ++i) if (a[i]) return i;\n    return\
    \ -1;\n}\n\nint brute_find_prev(const vector<int> &a, int k) {\n    for (int i\
    \ = k - 1; i >= 0; --i) if (a[i]) return i;\n    return -1;\n}\n\nvector<int>\
    \ shifted_left(const vector<int> &a, int s) {\n    vector<int> res(a.size());\n\
    \    if (s >= (int)a.size()) return res;\n    for (int i = 0; i + s < (int)a.size();\
    \ ++i) res[i + s] = a[i];\n    return res;\n}\n\nvector<int> shifted_right(const\
    \ vector<int> &a, int s) {\n    vector<int> res(a.size());\n    if (s >= (int)a.size())\
    \ return res;\n    for (int i = s; i < (int)a.size(); ++i) res[i - s] = a[i];\n\
    \    return res;\n}\n\ntemplate<int N>\nvoid verify_state(const StaticBitset<N>\
    \ &bs, const vector<int> &a) {\n    assert(bs.size() == (int)a.size());\n    assert(bs.empty()\
    \ == a.empty());\n    assert(to_vec(bs) == a);\n\n    int cnt = 0;\n    for (int\
    \ x : a) cnt += x;\n    assert(bs.count() == cnt);\n    assert(bs.any() == (cnt\
    \ != 0));\n    assert(bs.none() == (cnt == 0));\n    assert(bs.all() == (cnt ==\
    \ (int)a.size()));\n    assert(bs.find_first() == brute_find_first(a));\n    assert(bs.find_last()\
    \ == brute_find_last(a));\n    for (int i = 0; i <= (int)a.size(); ++i) {\n  \
    \      assert(bs.find_next(i - 1) == brute_find_next(a, i - 1));\n        assert(bs.find_prev(i)\
    \ == brute_find_prev(a, i));\n    }\n}\n\ntemplate<int N>\nvoid deterministic_check_size()\
    \ {\n    StaticBitset<N> zero, one(true);\n    verify_state(zero, vector<int>(N,\
    \ 0));\n    verify_state(one, vector<int>(N, 1));\n\n    vector<int> base(N);\n\
    \    for (int i = 0; i < N; ++i) base[i] = (i % 3) == 1;\n    StaticBitset<N>\
    \ bs;\n    for (int i = 0; i < N; ++i) if (base[i]) bs.set(i);\n    verify_state(bs,\
    \ base);\n\n    StaticBitset<N> flipped = bs;\n    flipped.flip();\n    vector<int>\
    \ flip_base = base;\n    for (int &x : flip_base) x ^= 1;\n    verify_state(flipped,\
    \ flip_base);\n\n    vector<int> shifts = {0, 1, 2, 31, 32, 63, 64, 65, max(0,\
    \ N - 1), N, N + 7};\n    for (int s : shifts) {\n        StaticBitset<N> left\
    \ = bs;\n        left <<= s;\n        verify_state(left, shifted_left(base, s));\n\
    \n        StaticBitset<N> right = bs;\n        right >>= s;\n        verify_state(right,\
    \ shifted_right(base, s));\n    }\n\n    StaticBitset<N> all(true);\n    StaticBitset<N>\
    \ x = bs & all;\n    verify_state(x, base);\n\n    StaticBitset<N> y = bs | all;\n\
    \    verify_state(y, vector<int>(N, 1));\n\n    StaticBitset<N> z = bs ^ all;\n\
    \    vector<int> xor_base = base;\n    for (int &v : xor_base) v ^= 1;\n    verify_state(z,\
    \ xor_base);\n}\n\ntemplate<int N>\nvoid random_check_size() {\n    mt19937 rng(N\
    \ + 17);\n    for (int tc = 0; tc < 60; ++tc) {\n        StaticBitset<N> bs, other;\n\
    \        vector<int> a(N, 0), b(N, 0);\n        for (int step = 0; step < 120;\
    \ ++step) {\n            int op = rng() % 12;\n            if (op == 0 && N >\
    \ 0) {\n                int k = rng() % N;\n                bs.set(k);\n     \
    \           a[k] = 1;\n            } else if (op == 1 && N > 0) {\n          \
    \      int k = rng() % N;\n                bs.reset(k);\n                a[k]\
    \ = 0;\n            } else if (op == 2 && N > 0) {\n                int k = rng()\
    \ % N;\n                bs.flip(k);\n                a[k] ^= 1;\n            }\
    \ else if (op == 3 && N > 0) {\n                int k = rng() % N;\n         \
    \       int x = rng() & 1;\n                bs.assign(k, x);\n               \
    \ a[k] = x;\n            } else if (op == 4) {\n                bs.reset();\n\
    \                fill(a.begin(), a.end(), 0);\n            } else if (op == 5)\
    \ {\n                bs.set();\n                fill(a.begin(), a.end(), 1);\n\
    \            } else if (op == 6) {\n                bs.flip();\n             \
    \   for (int &x : a) x ^= 1;\n            } else if (op == 7) {\n            \
    \    for (int i = 0; i < N; ++i) {\n                    int x = (rng() >> (i &\
    \ 7)) & 1;\n                    other.assign(i, x);\n                    b[i]\
    \ = x;\n                }\n            } else if (op == 8) {\n               \
    \ StaticBitset<N> cur = bs;\n                cur &= other;\n                vector<int>\
    \ expect(N);\n                for (int i = 0; i < N; ++i) expect[i] = a[i] & b[i];\n\
    \                verify_state(cur, expect);\n            } else if (op == 9) {\n\
    \                StaticBitset<N> cur = bs;\n                cur |= other;\n  \
    \              vector<int> expect(N);\n                for (int i = 0; i < N;\
    \ ++i) expect[i] = a[i] | b[i];\n                verify_state(cur, expect);\n\
    \            } else if (op == 10) {\n                StaticBitset<N> cur = bs;\n\
    \                cur ^= other;\n                vector<int> expect(N);\n     \
    \           for (int i = 0; i < N; ++i) expect[i] = a[i] ^ b[i];\n           \
    \     verify_state(cur, expect);\n            } else {\n                int s\
    \ = N == 0 ? 0 : rng() % (N + 8);\n                if (rng() & 1) {\n        \
    \            bs <<= s;\n                    a = shifted_left(a, s);\n        \
    \        } else {\n                    bs >>= s;\n                    a = shifted_right(a,\
    \ s);\n                }\n            }\n            verify_state(bs, a);\n  \
    \          verify_state(other, b);\n        }\n    }\n}\n\nvoid deterministic_check()\
    \ {\n    deterministic_check_size<0>();\n    deterministic_check_size<1>();\n\
    \    deterministic_check_size<2>();\n    deterministic_check_size<63>();\n   \
    \ deterministic_check_size<64>();\n    deterministic_check_size<65>();\n    deterministic_check_size<127>();\n\
    \    deterministic_check_size<128>();\n    deterministic_check_size<129>();\n\
    }\n\nvoid random_check() {\n    random_check_size<0>();\n    random_check_size<1>();\n\
    \    random_check_size<2>();\n    random_check_size<63>();\n    random_check_size<64>();\n\
    \    random_check_size<65>();\n    random_check_size<129>();\n    random_check_size<257>();\n\
    }\n\nint main() {\n    deterministic_check();\n    random_check();\n\n    Scanner\
    \ sc;\n    Printer pr;\n    int a, b;\n    sc.read(a, b);\n    pr.println(a +\
    \ b);\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <random>\n#include <vector>\nusing namespace std;\n\
    \n#include <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\
    \n#include \"../util/fastio.cpp\"\n#include \"../datastructure/static_bitset.cpp\"\
    \n\ntemplate<int N>\nvector<int> to_vec(const StaticBitset<N> &bs) {\n    vector<int>\
    \ res(N);\n    for (int i = 0; i < N; ++i) res[i] = bs.test(i);\n    return res;\n\
    }\n\nint brute_find_first(const vector<int> &a) {\n    for (int i = 0; i < (int)a.size();\
    \ ++i) if (a[i]) return i;\n    return -1;\n}\n\nint brute_find_last(const vector<int>\
    \ &a) {\n    for (int i = (int)a.size() - 1; i >= 0; --i) if (a[i]) return i;\n\
    \    return -1;\n}\n\nint brute_find_next(const vector<int> &a, int k) {\n   \
    \ for (int i = k + 1; i < (int)a.size(); ++i) if (a[i]) return i;\n    return\
    \ -1;\n}\n\nint brute_find_prev(const vector<int> &a, int k) {\n    for (int i\
    \ = k - 1; i >= 0; --i) if (a[i]) return i;\n    return -1;\n}\n\nvector<int>\
    \ shifted_left(const vector<int> &a, int s) {\n    vector<int> res(a.size());\n\
    \    if (s >= (int)a.size()) return res;\n    for (int i = 0; i + s < (int)a.size();\
    \ ++i) res[i + s] = a[i];\n    return res;\n}\n\nvector<int> shifted_right(const\
    \ vector<int> &a, int s) {\n    vector<int> res(a.size());\n    if (s >= (int)a.size())\
    \ return res;\n    for (int i = s; i < (int)a.size(); ++i) res[i - s] = a[i];\n\
    \    return res;\n}\n\ntemplate<int N>\nvoid verify_state(const StaticBitset<N>\
    \ &bs, const vector<int> &a) {\n    assert(bs.size() == (int)a.size());\n    assert(bs.empty()\
    \ == a.empty());\n    assert(to_vec(bs) == a);\n\n    int cnt = 0;\n    for (int\
    \ x : a) cnt += x;\n    assert(bs.count() == cnt);\n    assert(bs.any() == (cnt\
    \ != 0));\n    assert(bs.none() == (cnt == 0));\n    assert(bs.all() == (cnt ==\
    \ (int)a.size()));\n    assert(bs.find_first() == brute_find_first(a));\n    assert(bs.find_last()\
    \ == brute_find_last(a));\n    for (int i = 0; i <= (int)a.size(); ++i) {\n  \
    \      assert(bs.find_next(i - 1) == brute_find_next(a, i - 1));\n        assert(bs.find_prev(i)\
    \ == brute_find_prev(a, i));\n    }\n}\n\ntemplate<int N>\nvoid deterministic_check_size()\
    \ {\n    StaticBitset<N> zero, one(true);\n    verify_state(zero, vector<int>(N,\
    \ 0));\n    verify_state(one, vector<int>(N, 1));\n\n    vector<int> base(N);\n\
    \    for (int i = 0; i < N; ++i) base[i] = (i % 3) == 1;\n    StaticBitset<N>\
    \ bs;\n    for (int i = 0; i < N; ++i) if (base[i]) bs.set(i);\n    verify_state(bs,\
    \ base);\n\n    StaticBitset<N> flipped = bs;\n    flipped.flip();\n    vector<int>\
    \ flip_base = base;\n    for (int &x : flip_base) x ^= 1;\n    verify_state(flipped,\
    \ flip_base);\n\n    vector<int> shifts = {0, 1, 2, 31, 32, 63, 64, 65, max(0,\
    \ N - 1), N, N + 7};\n    for (int s : shifts) {\n        StaticBitset<N> left\
    \ = bs;\n        left <<= s;\n        verify_state(left, shifted_left(base, s));\n\
    \n        StaticBitset<N> right = bs;\n        right >>= s;\n        verify_state(right,\
    \ shifted_right(base, s));\n    }\n\n    StaticBitset<N> all(true);\n    StaticBitset<N>\
    \ x = bs & all;\n    verify_state(x, base);\n\n    StaticBitset<N> y = bs | all;\n\
    \    verify_state(y, vector<int>(N, 1));\n\n    StaticBitset<N> z = bs ^ all;\n\
    \    vector<int> xor_base = base;\n    for (int &v : xor_base) v ^= 1;\n    verify_state(z,\
    \ xor_base);\n}\n\ntemplate<int N>\nvoid random_check_size() {\n    mt19937 rng(N\
    \ + 17);\n    for (int tc = 0; tc < 60; ++tc) {\n        StaticBitset<N> bs, other;\n\
    \        vector<int> a(N, 0), b(N, 0);\n        for (int step = 0; step < 120;\
    \ ++step) {\n            int op = rng() % 12;\n            if (op == 0 && N >\
    \ 0) {\n                int k = rng() % N;\n                bs.set(k);\n     \
    \           a[k] = 1;\n            } else if (op == 1 && N > 0) {\n          \
    \      int k = rng() % N;\n                bs.reset(k);\n                a[k]\
    \ = 0;\n            } else if (op == 2 && N > 0) {\n                int k = rng()\
    \ % N;\n                bs.flip(k);\n                a[k] ^= 1;\n            }\
    \ else if (op == 3 && N > 0) {\n                int k = rng() % N;\n         \
    \       int x = rng() & 1;\n                bs.assign(k, x);\n               \
    \ a[k] = x;\n            } else if (op == 4) {\n                bs.reset();\n\
    \                fill(a.begin(), a.end(), 0);\n            } else if (op == 5)\
    \ {\n                bs.set();\n                fill(a.begin(), a.end(), 1);\n\
    \            } else if (op == 6) {\n                bs.flip();\n             \
    \   for (int &x : a) x ^= 1;\n            } else if (op == 7) {\n            \
    \    for (int i = 0; i < N; ++i) {\n                    int x = (rng() >> (i &\
    \ 7)) & 1;\n                    other.assign(i, x);\n                    b[i]\
    \ = x;\n                }\n            } else if (op == 8) {\n               \
    \ StaticBitset<N> cur = bs;\n                cur &= other;\n                vector<int>\
    \ expect(N);\n                for (int i = 0; i < N; ++i) expect[i] = a[i] & b[i];\n\
    \                verify_state(cur, expect);\n            } else if (op == 9) {\n\
    \                StaticBitset<N> cur = bs;\n                cur |= other;\n  \
    \              vector<int> expect(N);\n                for (int i = 0; i < N;\
    \ ++i) expect[i] = a[i] | b[i];\n                verify_state(cur, expect);\n\
    \            } else if (op == 10) {\n                StaticBitset<N> cur = bs;\n\
    \                cur ^= other;\n                vector<int> expect(N);\n     \
    \           for (int i = 0; i < N; ++i) expect[i] = a[i] ^ b[i];\n           \
    \     verify_state(cur, expect);\n            } else {\n                int s\
    \ = N == 0 ? 0 : rng() % (N + 8);\n                if (rng() & 1) {\n        \
    \            bs <<= s;\n                    a = shifted_left(a, s);\n        \
    \        } else {\n                    bs >>= s;\n                    a = shifted_right(a,\
    \ s);\n                }\n            }\n            verify_state(bs, a);\n  \
    \          verify_state(other, b);\n        }\n    }\n}\n\nvoid deterministic_check()\
    \ {\n    deterministic_check_size<0>();\n    deterministic_check_size<1>();\n\
    \    deterministic_check_size<2>();\n    deterministic_check_size<63>();\n   \
    \ deterministic_check_size<64>();\n    deterministic_check_size<65>();\n    deterministic_check_size<127>();\n\
    \    deterministic_check_size<128>();\n    deterministic_check_size<129>();\n\
    }\n\nvoid random_check() {\n    random_check_size<0>();\n    random_check_size<1>();\n\
    \    random_check_size<2>();\n    random_check_size<63>();\n    random_check_size<64>();\n\
    \    random_check_size<65>();\n    random_check_size<129>();\n    random_check_size<257>();\n\
    }\n\nint main() {\n    deterministic_check();\n    random_check();\n\n    Scanner\
    \ sc;\n    Printer pr;\n    int a, b;\n    sc.read(a, b);\n    pr.println(a +\
    \ b);\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - datastructure/static_bitset.cpp
  isVerificationFile: true
  path: test/yosupo_aplusb_static_bitset.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 13:44:11+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_aplusb_static_bitset.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_aplusb_static_bitset.test.cpp
- /verify/test/yosupo_aplusb_static_bitset.test.cpp.html
title: test/yosupo_aplusb_static_bitset.test.cpp
---
