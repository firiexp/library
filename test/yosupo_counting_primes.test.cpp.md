---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/counting_primes.cpp
    title: math/counting_primes.cpp
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: util/fastio.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/counting_primes
    links:
    - https://judge.yosupo.jp/problem/counting_primes
  bundledCode: "#line 1 \"test/yosupo_counting_primes.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/counting_primes\"\n\n#line 1 \"util/fastio.cpp\"\
    \n#include <cstdio>\n#include <cstring>\n#include <string>\n#include <type_traits>\n\
    using namespace std;\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n  \
    \  constexpr FastIoDigitTable() : num() {\n        for (int i = 0; i < 10000;\
    \ ++i) {\n            int x = i;\n            for (int j = 3; j >= 0; --j) {\n\
    \                num[i * 4 + j] = char('0' + x % 10);\n                x /= 10;\n\
    \            }\n        }\n    }\n};\n\nstruct Scanner {\n    static constexpr\
    \ int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE\
    \ + 1];\n    int idx, size;\n\n    Scanner() : idx(0), size(0) {}\n\n    inline\
    \ void load() {\n        int len = size - idx;\n        memmove(buf, buf + idx,\
    \ len);\n        size = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n\
    \        idx = 0;\n        buf[size] = 0;\n    }\n\n    inline void ensure() {\n\
    \        if (idx + OFFSET > size) load();\n    }\n\n    inline char skip() {\n\
    \        ensure();\n        while (buf[idx] && buf[idx] <= ' ') {\n          \
    \  ++idx;\n            ensure();\n        }\n        return buf[idx++];\n    }\n\
    \n    template<class T, typename enable_if<is_integral<T>::value, int>::type =\
    \ 0>\n    void read(T &x) {\n        char c = skip();\n        bool neg = false;\n\
    \        if constexpr (is_signed<T>::value) {\n            if (c == '-') {\n \
    \               neg = true;\n                c = buf[idx++];\n            }\n\
    \        }\n        x = 0;\n        while (c >= '0') {\n            x = x * 10\
    \ + (c & 15);\n            c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class Head,\
    \ class... Tail>\n    void read(Head &head, Tail &...tail) {\n        read(head);\n\
    \        (read(tail), ...);\n    }\n\n    void read(char &c) {\n        c = skip();\n\
    \    }\n\n    void read(string &s) {\n        s.clear();\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (buf[idx] > ' ') ++idx;\n            s.append(buf + start,\
    \ idx - start);\n            if (buf[idx] <= ' ') break;\n            load();\n\
    \        }\n        ++idx;\n    }\n};\n\nstruct Printer {\n    static constexpr\
    \ int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET = 64;\n    char buf[BUFSIZE];\n\
    \    int idx;\n    inline static constexpr FastIoDigitTable table{};\n\n    Printer()\
    \ : idx(0) {}\n    ~Printer() { flush(); }\n\n    inline void flush() {\n    \
    \    if (idx) {\n            fwrite(buf, 1, idx, stdout);\n            idx = 0;\n\
    \        }\n    }\n\n    inline void pc(char c) {\n        if (idx > BUFSIZE -\
    \ OFFSET) flush();\n        buf[idx++] = c;\n    }\n\n    inline void write_range(const\
    \ char *s, size_t n) {\n        size_t pos = 0;\n        while (pos < n) {\n \
    \           if (idx == BUFSIZE) flush();\n            size_t chunk = min(n - pos,\
    \ (size_t)(BUFSIZE - idx));\n            memcpy(buf + idx, s + pos, chunk);\n\
    \            idx += (int)chunk;\n            pos += chunk;\n        }\n    }\n\
    \n    void write(const char *s) {\n        write_range(s, strlen(s));\n    }\n\
    \n    void write(const string &s) {\n        write_range(s.data(), s.size());\n\
    \    }\n\n    void write(char c) {\n        pc(c);\n    }\n\n    void write(bool\
    \ b) {\n        pc(char('0' + (b ? 1 : 0)));\n    }\n\n    template<class T, typename\
    \ enable_if<is_integral<T>::value && !is_same<T, bool>::value, int>::type = 0>\n\
    \    void write(T x) {\n        if (idx > BUFSIZE - 100) flush();\n        using\
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
    \ += TMP_SIZE - pos;\n    }\n\n    template<class T>\n    void writeln(const T\
    \ &x) {\n        write(x);\n        pc('\\n');\n    }\n\n    template<class Head,\
    \ class... Tail>\n    void writeln(const Head &head, const Tail &...tail) {\n\
    \        write(head);\n        ((pc(' '), write(tail)), ...);\n        pc('\\\
    n');\n    }\n\n    void writeln() {\n        pc('\\n');\n    }\n};\n#line 1 \"\
    math/counting_primes.cpp\"\n#include <cmath>\n#include <cstdint>\n#include <vector>\n\
    using namespace std;\n\nnamespace counting_primes_internal {\n\nusing ll = long\
    \ long;\n\nconstexpr int MAX = 5000000;\nconstexpr int PHI_N = 100000;\nconstexpr\
    \ int PHI_S = 100;\n\nbool initialized = false;\nvector<int> primes;\nvector<int>\
    \ prime_pi;\nint phi_dp[PHI_S + 1][PHI_N + 1];\n\nll isqrt(ll x) {\n    ll r =\
    \ sqrtl((long double)x);\n    while ((r + 1) * (r + 1) <= x) ++r;\n    while (r\
    \ * r > x) --r;\n    return r;\n}\n\nll icbrt(ll x) {\n    ll r = powl((long double)x,\
    \ 1.0L / 3.0L);\n    while ((__int128)(r + 1) * (r + 1) * (r + 1) <= x) ++r;\n\
    \    while ((__int128)r * r * r > x) --r;\n    return r;\n}\n\nll iroot4(ll x)\
    \ {\n    return isqrt(isqrt(x));\n}\n\nvoid init() {\n    if (initialized) return;\n\
    \    initialized = true;\n\n    vector<int> min_factor(MAX + 1);\n    prime_pi.assign(MAX\
    \ + 1, 0);\n    for (int i = 2; i <= MAX; ++i) {\n        if (min_factor[i] ==\
    \ 0) {\n            min_factor[i] = i;\n            primes.push_back(i);\n   \
    \     }\n        for (int p : primes) {\n            ll v = 1LL * i * p;\n   \
    \         if (v > MAX || p > min_factor[i]) break;\n            min_factor[v]\
    \ = p;\n        }\n        prime_pi[i] = prime_pi[i - 1] + (min_factor[i] == i);\n\
    \    }\n\n    for (int n = 0; n <= PHI_N; ++n) phi_dp[0][n] = n;\n    for (int\
    \ s = 1; s <= PHI_S; ++s) {\n        int p = primes[s - 1];\n        for (int\
    \ n = 0; n <= PHI_N; ++n) {\n            phi_dp[s][n] = phi_dp[s - 1][n] - phi_dp[s\
    \ - 1][n / p];\n        }\n    }\n}\n\nll phi(ll x, int s) {\n    if (s == 0)\
    \ return x;\n    if (s <= PHI_S && x <= PHI_N) return phi_dp[s][x];\n    if (s\
    \ == 1) return x - x / 2;\n    return phi(x, s - 1) - phi(x / primes[s - 1], s\
    \ - 1);\n}\n\nll lehmer_pi(ll x) {\n    if (x <= MAX) return prime_pi[x];\n\n\
    \    ll a = lehmer_pi(iroot4(x));\n    ll b = lehmer_pi(isqrt(x));\n    ll c =\
    \ lehmer_pi(icbrt(x));\n\n    ll sum = phi(x, (int)a) + (b + a - 2) * (b - a +\
    \ 1) / 2;\n    for (ll i = a + 1; i <= b; ++i) {\n        ll w = x / primes[i\
    \ - 1];\n        sum -= lehmer_pi(w);\n        if (i <= c) {\n            ll lim\
    \ = lehmer_pi(isqrt(w));\n            for (ll j = i; j <= lim; ++j) {\n      \
    \          sum -= lehmer_pi(w / primes[j - 1]) - (j - 1);\n            }\n   \
    \     }\n    }\n    return sum;\n}\n\n}  // namespace counting_primes_internal\n\
    \nlong long counting_primes(long long n) {\n    counting_primes_internal::init();\n\
    \    return counting_primes_internal::lehmer_pi(n);\n}\n#line 5 \"test/yosupo_counting_primes.test.cpp\"\
    \n\nint main() {\n    Scanner sc;\n    Printer pr;\n    long long n;\n    sc.read(n);\n\
    \    pr.writeln(counting_primes(n));\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/counting_primes\"\n\n#include\
    \ \"../util/fastio.cpp\"\n#include \"../math/counting_primes.cpp\"\n\nint main()\
    \ {\n    Scanner sc;\n    Printer pr;\n    long long n;\n    sc.read(n);\n   \
    \ pr.writeln(counting_primes(n));\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - math/counting_primes.cpp
  isVerificationFile: true
  path: test/yosupo_counting_primes.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 17:13:05+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_counting_primes.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_counting_primes.test.cpp
- /verify/test/yosupo_counting_primes.test.cpp.html
title: test/yosupo_counting_primes.test.cpp
---
