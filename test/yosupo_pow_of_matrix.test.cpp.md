---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/squarematrix_mint.cpp
    title: "\u56FA\u5B9A\u9577\u6B63\u65B9\u884C\u5217(mint\u5C02\u7528)"
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  - icon: ':heavy_check_mark:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/pow_of_matrix
    links:
    - https://judge.yosupo.jp/problem/pow_of_matrix
  bundledCode: "#line 1 \"test/yosupo_pow_of_matrix.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/pow_of_matrix\"\n\n#include <algorithm>\n#include\
    \ <array>\n#include <vector>\nusing namespace std;\n\nstatic const int MOD = 998244353;\n\
    using ll = long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\n\
    \n#include <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\
    #include <utility>\n\n#line 1 \"util/fastio.cpp\"\nusing namespace std;\n\nextern\
    \ \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\ntemplate<class T,\
    \ class = void>\nstruct is_fastio_range : false_type {};\n\ntemplate<class T>\n\
    struct is_fastio_range<T, void_t<decltype(declval<T &>().begin()), decltype(declval<T\
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
    \ */\n#line 1 \"util/modint.cpp\"\n\n\n\ntemplate <uint Mod>\nstruct modint {\n\
    \    uint val;\npublic:\n    static modint raw(int v) { modint x; x.val = v; return\
    \ x; }\n    static constexpr uint get_mod() { return Mod; }\n    static constexpr\
    \ uint M() { return Mod; }\n    modint() : val(0) {}\n    template <class T>\n\
    \    modint(T v) { ll x = (ll)(v % (ll)(Mod)); if (x < 0) x += Mod; val = uint(x);\
    \ }\n    modint(bool v) { val = ((unsigned int)(v) % Mod); }\n    uint &value()\
    \ noexcept { return val; }\n    const uint &value() const noexcept { return val;\
    \ }\n    modint& operator++() { val++; if (val == Mod) val = 0; return *this;\
    \ }\n    modint& operator--() { if (val == 0) val = Mod; val--; return *this;\
    \ }\n    modint operator++(int) { modint result = *this; ++*this; return result;\
    \ }\n    modint operator--(int) { modint result = *this; --*this; return result;\
    \ }\n    modint& operator+=(const modint& b) { val += b.val; if (val >= Mod) val\
    \ -= Mod; return *this; }\n    modint& operator-=(const modint& b) { val -= b.val;\
    \ if (val >= Mod) val += Mod; return *this; }\n    modint& operator*=(const modint&\
    \ b) { ull z = val; z *= b.val; val = (uint)(z % Mod); return *this; }\n    modint&\
    \ operator/=(const modint& b) { return *this = *this * b.inv(); }\n    modint\
    \ operator+() const { return *this; }\n    modint operator-() const { return modint()\
    \ - *this; }\n    modint pow(long long n) const { modint x = *this, r = 1; while\
    \ (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n    modint inv() const\
    \ { return pow(Mod - 2); }\n    friend modint operator+(const modint& a, const\
    \ modint& b) { return modint(a) += b; }\n    friend modint operator-(const modint&\
    \ a, const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    #define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\n/**\n * @brief modint(\u56FA\u5B9A\
    MOD)\n */\n\n\n#line 2 \"math/squarematrix_mint.cpp\"\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n#include <immintrin.h>\n#endif\n\nnamespace squarematrix_mint_detail\
    \ {\nconstexpr ull mul_max_term = (ull)(MOD - 1) * (MOD - 1);\nconstexpr size_t\
    \ mul_block_size = mul_max_term == 0 ? 1 : size_t(~0ULL / mul_max_term);\nconstexpr\
    \ size_t mul_unroll_size = mul_block_size < 16 ? mul_block_size : 16;\n\nstruct\
    \ DotProductPair {\n    uint first;\n    uint second;\n};\n\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n__attribute__((target(\"avx2\"))) inline ull avx2_hsum_u64x4(__m256i\
    \ v) {\n    alignas(32) ull buf[4];\n    _mm256_store_si256((__m256i *)buf, v);\n\
    \    return buf[0] + buf[1] + buf[2] + buf[3];\n}\n\n__attribute__((target(\"\
    avx2\"))) ull dot_product_raw_avx2(const uint *row, const uint *col, size_t n,\
    \ uint mod) {\n    ull sum = 0;\n    size_t k = 0;\n    for (; k + mul_block_size\
    \ - 1 < n; k += mul_block_size) {\n        ull acc = 0;\n        size_t t = 0;\n\
    \        __m256i acc_even = _mm256_setzero_si256();\n        __m256i acc_odd =\
    \ _mm256_setzero_si256();\n        for (; t + 8 <= mul_block_size; t += 8) {\n\
    \            const __m256i rowv = _mm256_loadu_si256((const __m256i *)(row + k\
    \ + t));\n            const __m256i colv = _mm256_loadu_si256((const __m256i *)(col\
    \ + k + t));\n            acc_even = _mm256_add_epi64(acc_even, _mm256_mul_epu32(rowv,\
    \ colv));\n            const __m256i row_hi = _mm256_srli_epi64(rowv, 32);\n \
    \           const __m256i col_hi = _mm256_srli_epi64(colv, 32);\n            acc_odd\
    \ = _mm256_add_epi64(acc_odd, _mm256_mul_epu32(row_hi, col_hi));\n        }\n\
    \        acc += avx2_hsum_u64x4(acc_even) + avx2_hsum_u64x4(acc_odd);\n      \
    \  for (; t < mul_block_size; ++t) acc += (ull)row[k + t] * col[k + t];\n    \
    \    sum += acc % mod;\n        if (sum >= mod) sum -= mod;\n    }\n    ull acc\
    \ = 0;\n    for (; k < n; ++k) acc += (ull)row[k] * col[k];\n    sum += acc %\
    \ mod;\n    if (sum >= mod) sum -= mod;\n    return uint(sum);\n}\n\n__attribute__((target(\"\
    avx2\"))) DotProductPair dot_product_raw2_avx2(const uint *row, const uint *col0,\
    \ const uint *col1, size_t n, uint mod) {\n    ull sum0 = 0, sum1 = 0;\n    size_t\
    \ k = 0;\n    for (; k + mul_block_size - 1 < n; k += mul_block_size) {\n    \
    \    ull acc0 = 0, acc1 = 0;\n        size_t t = 0;\n        __m256i acc0_even\
    \ = _mm256_setzero_si256();\n        __m256i acc0_odd = _mm256_setzero_si256();\n\
    \        __m256i acc1_even = _mm256_setzero_si256();\n        __m256i acc1_odd\
    \ = _mm256_setzero_si256();\n        for (; t + 8 <= mul_block_size; t += 8) {\n\
    \            const __m256i rowv = _mm256_loadu_si256((const __m256i *)(row + k\
    \ + t));\n            const __m256i col0v = _mm256_loadu_si256((const __m256i\
    \ *)(col0 + k + t));\n            const __m256i col1v = _mm256_loadu_si256((const\
    \ __m256i *)(col1 + k + t));\n            acc0_even = _mm256_add_epi64(acc0_even,\
    \ _mm256_mul_epu32(rowv, col0v));\n            acc1_even = _mm256_add_epi64(acc1_even,\
    \ _mm256_mul_epu32(rowv, col1v));\n            const __m256i row_hi = _mm256_srli_epi64(rowv,\
    \ 32);\n            const __m256i col0_hi = _mm256_srli_epi64(col0v, 32);\n  \
    \          const __m256i col1_hi = _mm256_srli_epi64(col1v, 32);\n           \
    \ acc0_odd = _mm256_add_epi64(acc0_odd, _mm256_mul_epu32(row_hi, col0_hi));\n\
    \            acc1_odd = _mm256_add_epi64(acc1_odd, _mm256_mul_epu32(row_hi, col1_hi));\n\
    \        }\n        acc0 += avx2_hsum_u64x4(acc0_even) + avx2_hsum_u64x4(acc0_odd);\n\
    \        acc1 += avx2_hsum_u64x4(acc1_even) + avx2_hsum_u64x4(acc1_odd);\n   \
    \     for (; t < mul_block_size; ++t) {\n            const ull x = row[k + t];\n\
    \            acc0 += x * col0[k + t];\n            acc1 += x * col1[k + t];\n\
    \        }\n        sum0 += acc0 % mod;\n        if (sum0 >= mod) sum0 -= mod;\n\
    \        sum1 += acc1 % mod;\n        if (sum1 >= mod) sum1 -= mod;\n    }\n \
    \   ull acc0 = 0, acc1 = 0;\n    for (; k < n; ++k) {\n        const ull x = row[k];\n\
    \        acc0 += x * col0[k];\n        acc1 += x * col1[k];\n    }\n    sum0 +=\
    \ acc0 % mod;\n    if (sum0 >= mod) sum0 -= mod;\n    sum1 += acc1 % mod;\n  \
    \  if (sum1 >= mod) sum1 -= mod;\n    return {uint(sum0), uint(sum1)};\n}\n\n\
    inline bool has_avx2() {\n    static const bool cached = __builtin_cpu_supports(\"\
    avx2\");\n    return cached;\n}\n#endif\n\nuint dot_product_raw(const uint *row,\
    \ const uint *col, size_t n, uint mod) {\n#if defined(__x86_64__) || defined(_M_X64)\n\
    \    if (mul_block_size >= 8 && has_avx2()) return dot_product_raw_avx2(row, col,\
    \ n, mod);\n#endif\n    ull sum = 0;\n    size_t k = 0;\n    for (; k + mul_block_size\
    \ - 1 < n; k += mul_block_size) {\n        ull acc = 0;\n        if constexpr\
    \ (mul_unroll_size >= 1) acc += (ull)row[k + 0] * col[k + 0];\n        if constexpr\
    \ (mul_unroll_size >= 2) acc += (ull)row[k + 1] * col[k + 1];\n        if constexpr\
    \ (mul_unroll_size >= 3) acc += (ull)row[k + 2] * col[k + 2];\n        if constexpr\
    \ (mul_unroll_size >= 4) acc += (ull)row[k + 3] * col[k + 3];\n        if constexpr\
    \ (mul_unroll_size >= 5) acc += (ull)row[k + 4] * col[k + 4];\n        if constexpr\
    \ (mul_unroll_size >= 6) acc += (ull)row[k + 5] * col[k + 5];\n        if constexpr\
    \ (mul_unroll_size >= 7) acc += (ull)row[k + 6] * col[k + 6];\n        if constexpr\
    \ (mul_unroll_size >= 8) acc += (ull)row[k + 7] * col[k + 7];\n        if constexpr\
    \ (mul_unroll_size >= 9) acc += (ull)row[k + 8] * col[k + 8];\n        if constexpr\
    \ (mul_unroll_size >= 10) acc += (ull)row[k + 9] * col[k + 9];\n        if constexpr\
    \ (mul_unroll_size >= 11) acc += (ull)row[k + 10] * col[k + 10];\n        if constexpr\
    \ (mul_unroll_size >= 12) acc += (ull)row[k + 11] * col[k + 11];\n        if constexpr\
    \ (mul_unroll_size >= 13) acc += (ull)row[k + 12] * col[k + 12];\n        if constexpr\
    \ (mul_unroll_size >= 14) acc += (ull)row[k + 13] * col[k + 13];\n        if constexpr\
    \ (mul_unroll_size >= 15) acc += (ull)row[k + 14] * col[k + 14];\n        if constexpr\
    \ (mul_unroll_size >= 16) acc += (ull)row[k + 15] * col[k + 15];\n        for\
    \ (size_t t = mul_unroll_size; t < mul_block_size; ++t) {\n            acc +=\
    \ (ull)row[k + t] * col[k + t];\n        }\n        sum += acc % mod;\n      \
    \  if (sum >= mod) sum -= mod;\n    }\n    ull acc = 0;\n    for (; k < n; ++k)\
    \ acc += (ull)row[k] * col[k];\n    sum += acc % mod;\n    if (sum >= mod) sum\
    \ -= mod;\n    return uint(sum);\n}\n\nDotProductPair dot_product_raw2(const uint\
    \ *row, const uint *col0, const uint *col1, size_t n, uint mod) {\n#if defined(__x86_64__)\
    \ || defined(_M_X64)\n    if (mul_block_size >= 8 && has_avx2()) return dot_product_raw2_avx2(row,\
    \ col0, col1, n, mod);\n#endif\n    ull sum0 = 0, sum1 = 0;\n    size_t k = 0;\n\
    \    for (; k + mul_block_size - 1 < n; k += mul_block_size) {\n        ull acc0\
    \ = 0, acc1 = 0;\n        if constexpr (mul_unroll_size >= 1) {\n            const\
    \ ull x = row[k + 0];\n            acc0 += x * col0[k + 0];\n            acc1\
    \ += x * col1[k + 0];\n        }\n        if constexpr (mul_unroll_size >= 2)\
    \ {\n            const ull x = row[k + 1];\n            acc0 += x * col0[k + 1];\n\
    \            acc1 += x * col1[k + 1];\n        }\n        if constexpr (mul_unroll_size\
    \ >= 3) {\n            const ull x = row[k + 2];\n            acc0 += x * col0[k\
    \ + 2];\n            acc1 += x * col1[k + 2];\n        }\n        if constexpr\
    \ (mul_unroll_size >= 4) {\n            const ull x = row[k + 3];\n          \
    \  acc0 += x * col0[k + 3];\n            acc1 += x * col1[k + 3];\n        }\n\
    \        if constexpr (mul_unroll_size >= 5) {\n            const ull x = row[k\
    \ + 4];\n            acc0 += x * col0[k + 4];\n            acc1 += x * col1[k\
    \ + 4];\n        }\n        if constexpr (mul_unroll_size >= 6) {\n          \
    \  const ull x = row[k + 5];\n            acc0 += x * col0[k + 5];\n         \
    \   acc1 += x * col1[k + 5];\n        }\n        if constexpr (mul_unroll_size\
    \ >= 7) {\n            const ull x = row[k + 6];\n            acc0 += x * col0[k\
    \ + 6];\n            acc1 += x * col1[k + 6];\n        }\n        if constexpr\
    \ (mul_unroll_size >= 8) {\n            const ull x = row[k + 7];\n          \
    \  acc0 += x * col0[k + 7];\n            acc1 += x * col1[k + 7];\n        }\n\
    \        if constexpr (mul_unroll_size >= 9) {\n            const ull x = row[k\
    \ + 8];\n            acc0 += x * col0[k + 8];\n            acc1 += x * col1[k\
    \ + 8];\n        }\n        if constexpr (mul_unroll_size >= 10) {\n         \
    \   const ull x = row[k + 9];\n            acc0 += x * col0[k + 9];\n        \
    \    acc1 += x * col1[k + 9];\n        }\n        if constexpr (mul_unroll_size\
    \ >= 11) {\n            const ull x = row[k + 10];\n            acc0 += x * col0[k\
    \ + 10];\n            acc1 += x * col1[k + 10];\n        }\n        if constexpr\
    \ (mul_unroll_size >= 12) {\n            const ull x = row[k + 11];\n        \
    \    acc0 += x * col0[k + 11];\n            acc1 += x * col1[k + 11];\n      \
    \  }\n        if constexpr (mul_unroll_size >= 13) {\n            const ull x\
    \ = row[k + 12];\n            acc0 += x * col0[k + 12];\n            acc1 += x\
    \ * col1[k + 12];\n        }\n        if constexpr (mul_unroll_size >= 14) {\n\
    \            const ull x = row[k + 13];\n            acc0 += x * col0[k + 13];\n\
    \            acc1 += x * col1[k + 13];\n        }\n        if constexpr (mul_unroll_size\
    \ >= 15) {\n            const ull x = row[k + 14];\n            acc0 += x * col0[k\
    \ + 14];\n            acc1 += x * col1[k + 14];\n        }\n        if constexpr\
    \ (mul_unroll_size >= 16) {\n            const ull x = row[k + 15];\n        \
    \    acc0 += x * col0[k + 15];\n            acc1 += x * col1[k + 15];\n      \
    \  }\n        for (size_t t = mul_unroll_size; t < mul_block_size; ++t) {\n  \
    \          const ull x = row[k + t];\n            acc0 += x * col0[k + t];\n \
    \           acc1 += x * col1[k + t];\n        }\n        sum0 += acc0 % mod;\n\
    \        if (sum0 >= mod) sum0 -= mod;\n        sum1 += acc1 % mod;\n        if\
    \ (sum1 >= mod) sum1 -= mod;\n    }\n    ull acc0 = 0, acc1 = 0;\n    for (; k\
    \ < n; ++k) {\n        const ull x = row[k];\n        acc0 += x * col0[k];\n \
    \       acc1 += x * col1[k];\n    }\n    sum0 += acc0 % mod;\n    if (sum0 >=\
    \ mod) sum0 -= mod;\n    sum1 += acc1 % mod;\n    if (sum1 >= mod) sum1 -= mod;\n\
    \    return {uint(sum0), uint(sum1)};\n}\n\ntemplate<class Rows>\nvoid transpose_raw(const\
    \ Rows &rows, uint *dst, size_t row_count, size_t col_count, size_t stride) {\n\
    \    for (size_t k = 0; k < row_count; ++k) {\n        const auto *row = rows[k].data();\n\
    \        uint *col = dst + k;\n        for (size_t j = 0; j < col_count; ++j)\
    \ {\n            *col = row[j].value();\n            col += stride;\n        }\n\
    \    }\n}\n} // namespace squarematrix_mint_detail\n\ntemplate<size_t SIZE>\n\
    struct SquareMatrixMint {\n    using T = mint;\n    using ar = array<T, SIZE>;\n\
    \    using mat = array<ar, SIZE>;\n    struct PreparedMul {\n        array<uint,\
    \ SIZE * SIZE> BT;\n    };\n\n    struct MatrixMulScratch : PreparedMul {\n  \
    \      array<uint, SIZE> row;\n    };\n\n    struct VecMulScratch : PreparedMul\
    \ {\n        array<uint, SIZE> res;\n    };\n\n    mat A;\nprivate:\n    void\
    \ mul_assign_prepared_impl(const PreparedMul &prepared, MatrixMulScratch &scratch,\
    \ size_t n, bool clear_unused) {\n        const uint mod = mint::get_mod();\n\
    \        for (size_t i = 0; i < n; ++i) {\n            T *row = A[i].data();\n\
    \            for (size_t j = 0; j < n; ++j) scratch.row[j] = row[j].value();\n\
    \            const uint *col = prepared.BT.data();\n            size_t j = 0;\n\
    \            for (; j + 1 < n; j += 2) {\n                auto dots = squarematrix_mint_detail::dot_product_raw2(scratch.row.data(),\
    \ col, col + SIZE, n, mod);\n                row[j].value() = dots.first;\n  \
    \              row[j + 1].value() = dots.second;\n                col += SIZE\
    \ * 2;\n            }\n            if (j < n) {\n                row[j].value()\
    \ = squarematrix_mint_detail::dot_product_raw(scratch.row.data(), col, n, mod);\n\
    \            }\n            if (clear_unused) {\n                for (size_t j\
    \ = n; j < SIZE; ++j) row[j].value() = 0;\n            }\n        }\n        if\
    \ (clear_unused) {\n            for (size_t i = n; i < SIZE; ++i) {\n        \
    \        for (size_t j = 0; j < SIZE; ++j) A[i][j].value() = 0;\n            }\n\
    \        }\n    }\n\npublic:\n    SquareMatrixMint() {\n        for (size_t i\
    \ = 0; i < SIZE; ++i) {\n            for (size_t j = 0; j < SIZE; ++j) {\n   \
    \             A[i][j] = 0;\n            }\n        }\n    }\n    static SquareMatrixMint\
    \ I(size_t n = SIZE) {\n        SquareMatrixMint X;\n        for (size_t i = 0;\
    \ i < n; ++i) X[i][i] = 1;\n        return X;\n    }\n\n    friend ar &operator*=(ar\
    \ &x, const SquareMatrixMint &Y) {\n        return Y.mul_vec_assign(x);\n    }\n\
    \    friend ar operator*(ar x, const SquareMatrixMint &Y) { return x *= Y; }\n\
    \n    void prepare_mul(PreparedMul &prepared, size_t n = SIZE) const {\n     \
    \   squarematrix_mint_detail::transpose_raw(A, prepared.BT.data(), n, n, SIZE);\n\
    \    }\n\n    void prepare_vec_mul(PreparedMul &prepared, size_t n = SIZE) const\
    \ {\n        prepare_mul(prepared, n);\n    }\n\n    ar &mul_vec_assign(ar &x,\
    \ size_t n = SIZE) const {\n        VecMulScratch scratch;\n        prepare_vec_mul(scratch,\
    \ n);\n        return mul_vec_assign_prepared_impl(x, scratch, n, scratch);\n\
    \    }\n    ar mul_vec(ar x, size_t n = SIZE) const { return mul_vec_assign(x,\
    \ n); }\n    ar &mul_vec_assign(ar &x, VecMulScratch &scratch, size_t n) const\
    \ {\n        prepare_vec_mul(scratch, n);\n        return mul_vec_assign_prepared_impl(x,\
    \ scratch, n, scratch);\n    }\n    ar mul_vec(ar x, VecMulScratch &scratch, size_t\
    \ n) const { return mul_vec_assign(x, scratch, n); }\n    ar &mul_vec_assign_prepared(ar\
    \ &x, VecMulScratch &scratch, size_t n) const {\n        return mul_vec_assign_prepared(x,\
    \ static_cast<const PreparedMul &>(scratch), scratch, n);\n    }\n    ar mul_vec_prepared(ar\
    \ x, VecMulScratch &scratch, size_t n) const {\n        return mul_vec_assign_prepared(x,\
    \ scratch, n);\n    }\n    ar &mul_vec_assign_prepared(ar &x, const PreparedMul\
    \ &prepared, VecMulScratch &scratch, size_t n) const {\n        return mul_vec_assign_prepared_impl(x,\
    \ prepared, n, scratch);\n    }\n    ar mul_vec_prepared(ar x, const PreparedMul\
    \ &prepared, VecMulScratch &scratch, size_t n) const {\n        return mul_vec_assign_prepared(x,\
    \ prepared, scratch, n);\n    }\n\nprivate:\n    ar &mul_vec_assign_prepared_impl(ar\
    \ &x, const PreparedMul &prepared, size_t n, VecMulScratch &scratch) const {\n\
    \        const uint mod = mint::get_mod();\n        for (size_t j = 0; j < n;\
    \ ++j) scratch.res[j] = x[j].value();\n        const uint *col = prepared.BT.data();\n\
    \        size_t j = 0;\n        for (; j + 1 < n; j += 2) {\n            auto\
    \ dots = squarematrix_mint_detail::dot_product_raw2(scratch.res.data(), col, col\
    \ + SIZE, n, mod);\n            x[j].value() = dots.first;\n            x[j +\
    \ 1].value() = dots.second;\n            col += SIZE * 2;\n        }\n       \
    \ if (j < n) {\n            x[j].value() = squarematrix_mint_detail::dot_product_raw(scratch.res.data(),\
    \ col, n, mod);\n        }\n        for (size_t j = n; j < SIZE; ++j) x[j].value()\
    \ = 0;\n        return x;\n    }\n\npublic:\n\n    inline const ar &operator[](int\
    \ k) const { return A.at(k); }\n    inline ar &operator[](int k) { return A.at(k);\
    \ }\n\n    SquareMatrixMint &operator+=(const SquareMatrixMint &B) {\n       \
    \ for (size_t i = 0; i < SIZE; ++i) {\n            for (size_t j = 0; j < SIZE;\
    \ ++j) {\n                A[i][j] += B.A[i][j];\n            }\n        }\n  \
    \      return *this;\n    }\n\n    SquareMatrixMint &operator-=(const SquareMatrixMint\
    \ &B) {\n        for (size_t i = 0; i < SIZE; ++i) {\n            for (size_t\
    \ j = 0; j < SIZE; ++j) {\n                A[i][j] -= B.A[i][j];\n           \
    \ }\n        }\n        return *this;\n    }\n\n    SquareMatrixMint &mul_assign(const\
    \ SquareMatrixMint &B, size_t n = SIZE) {\n        MatrixMulScratch scratch;\n\
    \        return mul_assign(B, scratch, n);\n    }\n    SquareMatrixMint &mul_assign(const\
    \ SquareMatrixMint &B, MatrixMulScratch &scratch, size_t n) {\n        B.prepare_mul(scratch,\
    \ n);\n        return mul_assign_prepared(scratch, n);\n    }\n    SquareMatrixMint\
    \ &mul_assign_prepared(MatrixMulScratch &scratch, size_t n, bool clear_unused\
    \ = true) {\n        return mul_assign_prepared(static_cast<const PreparedMul\
    \ &>(scratch), scratch, n, clear_unused);\n    }\n    SquareMatrixMint &mul_assign_prepared(const\
    \ PreparedMul &prepared, MatrixMulScratch &scratch, size_t n, bool clear_unused\
    \ = true) {\n        mul_assign_prepared_impl(prepared, scratch, n, clear_unused);\n\
    \        return *this;\n    }\n    SquareMatrixMint &operator*=(const SquareMatrixMint\
    \ &B) { return mul_assign(B); }\n\n    SquareMatrixMint pow(ll n, size_t dim =\
    \ SIZE) const {\n        if (n == 0) return I(dim);\n        const ull exp = (ull)n;\n\
    \        MatrixMulScratch scratch;\n        auto binary_pow = [&](ull m) {\n \
    \           SquareMatrixMint a = *this, res = I(dim);\n            while (m >\
    \ 1) {\n                a.prepare_mul(scratch, dim);\n                if (m &\
    \ 1) res.mul_assign_prepared(scratch, dim, false);\n                a.mul_assign_prepared(scratch,\
    \ dim, false);\n                m >>= 1;\n            }\n            a.prepare_mul(scratch,\
    \ dim);\n            res.mul_assign_prepared(scratch, dim, false);\n         \
    \   return res;\n        };\n        if (exp < 8) return binary_pow(exp);\n\n\
    \        constexpr int window_bits = 3;\n        constexpr size_t window_size\
    \ = size_t(1) << (window_bits - 1);\n        struct PowEntry {\n            SquareMatrixMint\
    \ mat;\n            PreparedMul prepared;\n        };\n        array<PowEntry,\
    \ window_size> odd;\n        odd[0].mat = *this;\n        odd[0].mat.prepare_mul(odd[0].prepared,\
    \ dim);\n        if constexpr (window_size > 1) {\n            SquareMatrixMint\
    \ base2 = *this;\n            base2.mul_assign(*this, scratch, dim);\n       \
    \     base2.prepare_mul(scratch, dim);\n            for (size_t i = 1; i < window_size;\
    \ ++i) {\n                odd[i].mat = odd[i - 1].mat;\n                odd[i].mat.mul_assign_prepared(scratch,\
    \ dim, false);\n                odd[i].mat.prepare_mul(odd[i].prepared, dim);\n\
    \            }\n        }\n\n        SquareMatrixMint res;\n        bool started\
    \ = false;\n        for (int bit = 63 - __builtin_clzll(exp); bit >= 0;) {\n \
    \           if (((exp >> bit) & 1ULL) == 0) {\n                if (started) {\n\
    \                    res.prepare_mul(scratch, dim);\n                    res.mul_assign_prepared(scratch,\
    \ dim, false);\n                }\n                --bit;\n                continue;\n\
    \            }\n            int low = bit - (window_bits - 1);\n            if\
    \ (low < 0) low = 0;\n            while (((exp >> low) & 1ULL) == 0) ++low;\n\
    \            uint value = 0;\n            for (int k = bit; k >= low; --k) value\
    \ = (value << 1) | uint((exp >> k) & 1ULL);\n            const uint idx = value\
    \ >> 1;\n            if (!started) {\n                res = odd[idx].mat;\n  \
    \              started = true;\n            } else {\n                for (int\
    \ k = low; k <= bit; ++k) {\n                    res.prepare_mul(scratch, dim);\n\
    \                    res.mul_assign_prepared(scratch, dim, false);\n         \
    \       }\n                res.mul_assign_prepared(odd[idx].prepared, scratch,\
    \ dim, false);\n            }\n            bit = low - 1;\n        }\n       \
    \ return res;\n    }\n    SquareMatrixMint operator+(const SquareMatrixMint &B)\
    \ const { return SquareMatrixMint(*this) += B; }\n    SquareMatrixMint operator-(const\
    \ SquareMatrixMint &B) const { return SquareMatrixMint(*this) -= B; }\n    SquareMatrixMint\
    \ operator*(const SquareMatrixMint &B) const { return SquareMatrixMint(*this)\
    \ *= B; }\n};\n\n/**\n * @brief \u56FA\u5B9A\u9577\u6B63\u65B9\u884C\u5217(mint\u5C02\
    \u7528)\n */\n#line 21 \"test/yosupo_pow_of_matrix.test.cpp\"\n\nusing mat = SquareMatrixMint<200>;\n\
    \nstatic_assert(is_same_v<decltype(declval<mat::ar &>() *= declval<const mat &>()),\
    \ mat::ar &>);\n\n[[maybe_unused]] static void squarematrix_mint_api_smoke_test()\
    \ {\n    mat A;\n    mat::PreparedMul prepared;\n    mat::MatrixMulScratch matrix_scratch;\n\
    \    mat::VecMulScratch vec_scratch;\n    mat::ar x{};\n    A.prepare_mul(prepared,\
    \ 0);\n    A.mul_assign_prepared(prepared, matrix_scratch, 0);\n    A.mul_vec_assign_prepared(x,\
    \ prepared, vec_scratch, 0);\n}\n\nint main() {\n    Scanner sc;\n    Printer\
    \ pr;\n\n    int n;\n    ll k;\n    sc.read(n, k);\n    mat A;\n    for (int i\
    \ = 0; i < n; ++i) {\n        for (int j = 0; j < n; ++j) {\n            int x;\n\
    \            sc.read(x);\n            A[i][j] = x;\n        }\n    }\n\n    auto\
    \ B = A.pow(k, n);\n    for (int i = 0; i < n; ++i) {\n        for (int j = 0;\
    \ j < n; ++j) {\n            pr.print(B[i][j].val);\n            pr.print(j +\
    \ 1 == n ? '\\n' : ' ');\n        }\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/pow_of_matrix\"\n\n#include\
    \ <algorithm>\n#include <array>\n#include <vector>\nusing namespace std;\n\nstatic\
    \ const int MOD = 998244353;\nusing ll = long long;\nusing uint = unsigned;\n\
    using ull = unsigned long long;\n\n#include <cstdio>\n#include <cstring>\n#include\
    \ <string>\n#include <type_traits>\n#include <utility>\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../math/squarematrix_mint.cpp\"\n\nusing mat = SquareMatrixMint<200>;\n\
    \nstatic_assert(is_same_v<decltype(declval<mat::ar &>() *= declval<const mat &>()),\
    \ mat::ar &>);\n\n[[maybe_unused]] static void squarematrix_mint_api_smoke_test()\
    \ {\n    mat A;\n    mat::PreparedMul prepared;\n    mat::MatrixMulScratch matrix_scratch;\n\
    \    mat::VecMulScratch vec_scratch;\n    mat::ar x{};\n    A.prepare_mul(prepared,\
    \ 0);\n    A.mul_assign_prepared(prepared, matrix_scratch, 0);\n    A.mul_vec_assign_prepared(x,\
    \ prepared, vec_scratch, 0);\n}\n\nint main() {\n    Scanner sc;\n    Printer\
    \ pr;\n\n    int n;\n    ll k;\n    sc.read(n, k);\n    mat A;\n    for (int i\
    \ = 0; i < n; ++i) {\n        for (int j = 0; j < n; ++j) {\n            int x;\n\
    \            sc.read(x);\n            A[i][j] = x;\n        }\n    }\n\n    auto\
    \ B = A.pow(k, n);\n    for (int i = 0; i < n; ++i) {\n        for (int j = 0;\
    \ j < n; ++j) {\n            pr.print(B[i][j].val);\n            pr.print(j +\
    \ 1 == n ? '\\n' : ' ');\n        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - math/squarematrix_mint.cpp
  - util/modint.cpp
  isVerificationFile: true
  path: test/yosupo_pow_of_matrix.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 13:47:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_pow_of_matrix.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_pow_of_matrix.test.cpp
- /verify/test/yosupo_pow_of_matrix.test.cpp.html
title: test/yosupo_pow_of_matrix.test.cpp
---
