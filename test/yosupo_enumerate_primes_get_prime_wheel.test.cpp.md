---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/prime/get_prime_wheel.cpp
    title: get_prime_wheel
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
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_primes
    links:
    - https://judge.yosupo.jp/problem/enumerate_primes
  bundledCode: "#line 1 \"test/yosupo_enumerate_primes_get_prime_wheel.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_primes\"\n\n#include\
    \ <algorithm>\n#include <cmath>\n#include <vector>\n#include <array>\nusing namespace\
    \ std;\nusing ll = long long;\nusing ull = unsigned long long;\n\n#include <cstdio>\n\
    #include <cstring>\n#include <string>\n#include <type_traits>\n\n#line 1 \"util/fastio.cpp\"\
    \nusing namespace std;\n\nextern \"C\" int fileno(FILE *);\nextern \"C\" int isatty(int);\n\
    \ntemplate<class T, class = void>\nstruct is_fastio_range : false_type {};\n\n\
    template<class T>\nstruct is_fastio_range<T, void_t<decltype(declval<T &>().begin()),\
    \ decltype(declval<T &>().end())>> : true_type {};\n\ntemplate<class T, class\
    \ = void>\nstruct has_fastio_value : false_type {};\n\ntemplate<class T>\nstruct\
    \ has_fastio_value<T, void_t<decltype(declval<const T &>().value())>> : true_type\
    \ {};\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr FastIoDigitTable()\
    \ : num() {\n        for (int i = 0; i < 10000; ++i) {\n            int x = i;\n\
    \            for (int j = 3; j >= 0; --j) {\n                num[i * 4 + j] =\
    \ char('0' + x % 10);\n                x /= 10;\n            }\n        }\n  \
    \  }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE = 1 << 17;\n  \
    \  static constexpr int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n    int idx,\
    \ size;\n    bool interactive;\n\n    Scanner() : idx(0), size(0), interactive(isatty(fileno(stdin)))\
    \ {}\n\n    inline void load() {\n        int len = size - idx;\n        memmove(buf,\
    \ buf + idx, len);\n        if (interactive) {\n            if (fgets(buf + len,\
    \ BUFSIZE + 1 - len, stdin)) size = len + (int)strlen(buf + len);\n          \
    \  else size = len;\n        } else {\n            size = len + (int)fread(buf\
    \ + len, 1, BUFSIZE - len, stdin);\n        }\n        idx = 0;\n        buf[size]\
    \ = 0;\n    }\n\n    inline void ensure() {\n        if (idx + OFFSET > size)\
    \ load();\n    }\n\n    inline void ensure_interactive() {\n        if (idx ==\
    \ size) load();\n    }\n\n    inline char skip() {\n        if (interactive) {\n\
    \            ensure_interactive();\n            while (buf[idx] && buf[idx] <=\
    \ ' ') {\n                ++idx;\n                ensure_interactive();\n    \
    \        }\n            return buf[idx++];\n        }\n        ensure();\n   \
    \     while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n            ensure();\n\
    \        }\n        return buf[idx++];\n    }\n\n    template<class T, typename\
    \ enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T &x) {\n  \
    \      if (interactive) {\n            char c = skip();\n            bool neg\
    \ = false;\n            if constexpr (is_signed<T>::value) {\n               \
    \ if (c == '-') {\n                    neg = true;\n                    ensure_interactive();\n\
    \                    c = buf[idx++];\n                }\n            }\n     \
    \       x = 0;\n            while (c >= '0') {\n                x = x * 10 + (c\
    \ & 15);\n                ensure_interactive();\n                c = buf[idx++];\n\
    \            }\n            if constexpr (is_signed<T>::value) {\n           \
    \     if (neg) x = -x;\n            }\n            return;\n        }\n      \
    \  char c = skip();\n        bool neg = false;\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (c == '-') {\n                neg = true;\n              \
    \  c = buf[idx++];\n            }\n        }\n        x = 0;\n        while (c\
    \ >= '0') {\n            x = x * 10 + (c & 15);\n            c = buf[idx++];\n\
    \        }\n        if constexpr (is_signed<T>::value) {\n            if (neg)\
    \ x = -x;\n        }\n    }\n\n    template<class T, typename enable_if<!is_integral<T>::value\
    \ && !is_fastio_range<T>::value && !is_same<typename decay<T>::type, string>::value\
    \ && has_fastio_value<T>::value, int>::type = 0>\n    void read(T &x) {\n    \
    \    long long v;\n        read(v);\n        x = T(v);\n    }\n\n    template<class\
    \ Head, class Next, class... Tail>\n    void read(Head &head, Next &next, Tail\
    \ &...tail) {\n        read(head);\n        read(next, tail...);\n    }\n\n  \
    \  template<class T, class U>\n    void read(pair<T, U> &p) {\n        read(p.first,\
    \ p.second);\n    }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value\
    \ && !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
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
    \ 64;\n    char buf[BUFSIZE];\n    int idx;\n    bool interactive;\n    inline\
    \ static constexpr FastIoDigitTable table{};\n\n    Printer() : idx(0), interactive(isatty(fileno(stdout)))\
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
    \ 1 : 0)));\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value\
    \ && !is_same<T, bool>::value, int>::type = 0>\n    void print(T x) {\n      \
    \  if (idx > BUFSIZE - 100) flush();\n        using U = typename make_unsigned<T>::type;\n\
    \        U y;\n        if constexpr (is_signed<T>::value) {\n            if (x\
    \ < 0) {\n                buf[idx++] = '-';\n                y = U(0) - static_cast<U>(x);\n\
    \            } else {\n                y = static_cast<U>(x);\n            }\n\
    \        } else {\n            y = x;\n        }\n        if (y == 0) {\n    \
    \        buf[idx++] = '0';\n            return;\n        }\n        static constexpr\
    \ int TMP_SIZE = sizeof(U) * 10 / 4;\n        char tmp[TMP_SIZE];\n        int\
    \ pos = TMP_SIZE;\n        while (y >= 10000) {\n            pos -= 4;\n     \
    \       memcpy(tmp + pos, table.num + (y % 10000) * 4, 4);\n            y /= 10000;\n\
    \        }\n        if (y >= 1000) {\n            memcpy(buf + idx, table.num\
    \ + (y << 2), 4);\n            idx += 4;\n        } else if (y >= 100) {\n   \
    \         memcpy(buf + idx, table.num + (y << 2) + 1, 3);\n            idx +=\
    \ 3;\n        } else if (y >= 10) {\n            unsigned q = (unsigned(y) * 205)\
    \ >> 11;\n            buf[idx] = char('0' + q);\n            buf[idx + 1] = char('0'\
    \ + (unsigned(y) - q * 10));\n            idx += 2;\n        } else {\n      \
    \      buf[idx++] = char('0' + y);\n        }\n        memcpy(buf + idx, tmp +\
    \ pos, TMP_SIZE - pos);\n        idx += TMP_SIZE - pos;\n    }\n\n    template<class\
    \ T, typename enable_if<!is_integral<T>::value && !is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value && has_fastio_value<T>::value,\
    \ int>::type = 0>\n    void print(const T &x) {\n        print(x.value());\n \
    \   }\n\n    template<class T, typename enable_if<is_fastio_range<T>::value &&\
    \ !is_same<typename decay<T>::type, string>::value, int>::type = 0>\n    void\
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
    \ */\n#line 1 \"math/prime/get_prime_wheel.cpp\"\nstruct Prime {\n    static constexpr\
    \ int wheel[8]  = {4, 2, 4, 2, 4, 6, 2, 6};\n    static constexpr int wheel2[8]\
    \ = {7, 11, 13, 17, 19, 23, 29, 31};\n    static constexpr int wheel_sum[30] =\
    \ {\n        0, 0, 0, 0, 0, 0, 1, 1, 1, 1,\n        2, 2, 3, 3, 3, 3, 4, 4, 5,\
    \ 5,\n        5, 5, 6, 6, 6, 6, 6, 6, 7, 7\n    };\n    static constexpr int off64[64]\
    \ = {\n          0,  4,  6, 10, 12, 16, 22, 24,\n         30, 34, 36, 40, 42,\
    \ 46, 52, 54,\n         60, 64, 66, 70, 72, 76, 82, 84,\n         90, 94, 96,100,102,106,112,114,\n\
    \        120,124,126,130,132,136,142,144,\n        150,154,156,160,162,166,172,174,\n\
    \        180,184,186,190,192,196,202,204,\n        210,214,216,220,222,226,232,234\n\
    \    };\n\n    // old 1-based\n    static inline int f(int n) { return (n - 1)\
    \ / 30 * 8 + wheel_sum[(n - 1) % 30]; }\n    static inline int g(int n) { return\
    \ ((n - 1) >> 3) * 30 + wheel2[(n - 1) & 7]; }\n\n    // internal 0-based\n  \
    \  static inline int f0(int n) { return f(n) - 1; }\n    static inline int g0(int\
    \ n) { return (n >> 3) * 30 + wheel2[n & 7]; }\n\n    int count = 0;\n    vector<int>\
    \ primes;\n    vector<int> picked;\n\nprivate:\n    static void build_sieve(int\
    \ M, vector<ull>& sieve, int& n0) {\n        if (M < 7) {\n            n0 = -1;\n\
    \            sieve.clear();\n            return;\n        }\n\n        n0 = f0(M);\n\
    \        int sq = (int)std::sqrt((double)M);\n        int k0 = (sq >= 7 ? f0(sq)\
    \ : -1);\n\n        int num = n0 + 1;\n        sieve.assign((num + 63) >> 6, ~0ULL);\n\
    \        if (num & 63) sieve.back() &= (1ULL << (num & 63)) - 1;\n\n        auto*\
    \ sv = sieve.data();\n        array<int, 8> delta{};\n\n        for (int i = 0;\
    \ i <= k0; ++i) {\n            if (((sv[i >> 6] >> (i & 63)) & 1ULL) == 0) continue;\n\
    \n            int p = g0(i);\n            int phase0 = i & 7;\n\n            long\
    \ long cur = 1LL * p * p;\n            int idx = f0((int)cur);\n\n           \
    \ for (int t = 0; t < 8; ++t) {\n                long long nxt = cur + 1LL * wheel[(phase0\
    \ + t) & 7] * p;\n                delta[t] = f((int)nxt) - f((int)cur);\n    \
    \            cur = nxt;\n            }\n\n            const int d0 = delta[0];\n\
    \            const int d1 = delta[1];\n            const int d2 = delta[2];\n\
    \            const int d3 = delta[3];\n            const int d4 = delta[4];\n\
    \            const int d5 = delta[5];\n            const int d6 = delta[6];\n\
    \            const int d7 = delta[7];\n\n            while (idx <= n0) {\n   \
    \             sv[idx >> 6] &= ~(1ULL << (idx & 63));\n                idx += d0;\n\
    \                if (idx > n0) break;\n                sv[idx >> 6] &= ~(1ULL\
    \ << (idx & 63));\n                idx += d1;\n                if (idx > n0) break;\n\
    \                sv[idx >> 6] &= ~(1ULL << (idx & 63));\n                idx +=\
    \ d2;\n                if (idx > n0) break;\n                sv[idx >> 6] &= ~(1ULL\
    \ << (idx & 63));\n                idx += d3;\n                if (idx > n0) break;\n\
    \                sv[idx >> 6] &= ~(1ULL << (idx & 63));\n                idx +=\
    \ d4;\n                if (idx > n0) break;\n                sv[idx >> 6] &= ~(1ULL\
    \ << (idx & 63));\n                idx += d5;\n                if (idx > n0) break;\n\
    \                sv[idx >> 6] &= ~(1ULL << (idx & 63));\n                idx +=\
    \ d6;\n                if (idx > n0) break;\n                sv[idx >> 6] &= ~(1ULL\
    \ << (idx & 63));\n                idx += d7;\n            }\n        }\n    }\n\
    \npublic:\n    Prime(int M) {\n        if (M >= 17) {\n            primes.reserve(max(0,\
    \ (int)(M / (log((double)M) - 1.12))));\n        }\n\n        if (M >= 2) primes.push_back(2),\
    \ ++count;\n        if (M >= 3) primes.push_back(3), ++count;\n        if (M >=\
    \ 5) primes.push_back(5), ++count;\n        if (M < 7) return;\n\n        vector<ull>\
    \ sieve;\n        int n0;\n        build_sieve(M, sieve, n0);\n\n        int words\
    \ = (n0 + 64) >> 6;\n        for (int w = 0; w < words; ++w) {\n            ull\
    \ bits = sieve[w];\n            int base = 240 * w + 7; // 64 candidates = 8 cycles\
    \ = 240 numbers\n            while (bits) {\n                int t = __builtin_ctzll(bits);\n\
    \                primes.push_back(base + off64[t]);\n                ++count;\n\
    \                bits &= bits - 1;\n            }\n        }\n    }\n\n    Prime(int\
    \ M, int a, int b) {\n        int next_pick = b;\n\n        auto add_small = [&](int\
    \ p) {\n            if (count == next_pick) {\n                picked.push_back(p);\n\
    \                next_pick += a;\n            }\n            ++count;\n      \
    \  };\n\n        if (M >= 2) add_small(2);\n        if (M >= 3) add_small(3);\n\
    \        if (M >= 5) add_small(5);\n        if (M < 7) return;\n\n        vector<ull>\
    \ sieve;\n        int n0;\n        build_sieve(M, sieve, n0);\n\n        int words\
    \ = (n0 + 64) >> 6;\n        for (int w = 0; w < words; ++w) {\n            ull\
    \ bits = sieve[w];\n            int pc = __builtin_popcountll(bits);\n\n     \
    \       if (next_pick >= count + pc) {\n                count += pc;\n       \
    \         continue;\n            }\n\n            int base = 240 * w + 7;\n  \
    \          while (bits) {\n                int t = __builtin_ctzll(bits);\n  \
    \              if (count == next_pick) {\n                    picked.push_back(base\
    \ + off64[t]);\n                    next_pick += a;\n                }\n     \
    \           ++count;\n                bits &= bits - 1;\n            }\n     \
    \   }\n    }\n};\n\nconstexpr int Prime::wheel[8];\nconstexpr int Prime::wheel2[8];\n\
    constexpr int Prime::wheel_sum[30];\nconstexpr int Prime::off64[64];\n#line 18\
    \ \"test/yosupo_enumerate_primes_get_prime_wheel.test.cpp\"\n\nint main() {\n\
    \    Scanner sc;\n    Printer pr;\n\n    int n, a, b;\n    sc.read(n, a, b);\n\
    \n    Prime prime(n, a, b);\n\n    pr.print(prime.count);\n    pr.print(' ');\n\
    \    pr.println((prime.count <= b ? 0 : (prime.count - b + a - 1) / a));\n\n \
    \   pr.println(prime.picked);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_primes\"\n\n\
    #include <algorithm>\n#include <cmath>\n#include <vector>\n#include <array>\n\
    using namespace std;\nusing ll = long long;\nusing ull = unsigned long long;\n\
    \n#include <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\
    \n#include \"../util/fastio.cpp\"\n#include \"../math/prime/get_prime_wheel.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n\n    int n, a, b;\n    sc.read(n,\
    \ a, b);\n\n    Prime prime(n, a, b);\n\n    pr.print(prime.count);\n    pr.print('\
    \ ');\n    pr.println((prime.count <= b ? 0 : (prime.count - b + a - 1) / a));\n\
    \n    pr.println(prime.picked);\n}\n"
  dependsOn:
  - util/fastio.cpp
  - math/prime/get_prime_wheel.cpp
  isVerificationFile: true
  path: test/yosupo_enumerate_primes_get_prime_wheel.test.cpp
  requiredBy: []
  timestamp: '2026-03-22 19:39:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_enumerate_primes_get_prime_wheel.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_enumerate_primes_get_prime_wheel.test.cpp
- /verify/test/yosupo_enumerate_primes_get_prime_wheel.test.cpp.html
title: test/yosupo_enumerate_primes_get_prime_wheel.test.cpp
---
