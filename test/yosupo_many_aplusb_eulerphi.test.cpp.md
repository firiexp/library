---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/eulerphi.cpp
    title: "\u30AA\u30A4\u30E9\u30FC\u306E\u03C6\u95A2\u6570(Euler Phi)"
  - icon: ':heavy_check_mark:'
    path: math/eulerphi_all.cpp
    title: "\u30AA\u30A4\u30E9\u30FC\u306E\u03C6\u95A2\u6570\u30C6\u30FC\u30D6\u30EB\
      (Euler Phi Table)"
  - icon: ':heavy_check_mark:'
    path: math/get_min_factor.cpp
    title: "\u6700\u5C0F\u7D20\u56E0\u6570\u30C6\u30FC\u30D6\u30EB(Min Factor Table)"
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
    PROBLEM: https://judge.yosupo.jp/problem/many_aplusb
    links:
    - https://judge.yosupo.jp/problem/many_aplusb
  bundledCode: "#line 1 \"test/yosupo_many_aplusb_eulerphi.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include <algorithm>\n#include\
    \ <numeric>\n#include <random>\n#include <vector>\nusing namespace std;\nusing\
    \ ll = long long;\n\n#line 1 \"util/fastio.cpp\"\n#include <cstdio>\n#include\
    \ <cstring>\n#include <string>\n#include <type_traits>\nusing namespace std;\n\
    \nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr FastIoDigitTable()\
    \ : num() {\n        for (int i = 0; i < 10000; ++i) {\n            int x = i;\n\
    \            for (int j = 3; j >= 0; --j) {\n                num[i * 4 + j] =\
    \ char('0' + x % 10);\n                x /= 10;\n            }\n        }\n  \
    \  }\n};\n\nstruct Scanner {\n    static constexpr int BUFSIZE = 1 << 17;\n  \
    \  static constexpr int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n    int idx,\
    \ size;\n\n    Scanner() : idx(0), size(0) {}\n\n    inline void load() {\n  \
    \      int len = size - idx;\n        memmove(buf, buf + idx, len);\n        size\
    \ = len + (int)fread(buf + len, 1, BUFSIZE - len, stdin);\n        idx = 0;\n\
    \        buf[size] = 0;\n    }\n\n    inline void ensure() {\n        if (idx\
    \ + OFFSET > size) load();\n    }\n\n    inline char skip() {\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        return buf[idx++];\n    }\n\n    template<class\
    \ T, typename enable_if<is_integral<T>::value, int>::type = 0>\n    void read(T\
    \ &x) {\n        char c = skip();\n        bool neg = false;\n        if constexpr\
    \ (is_signed<T>::value) {\n            if (c == '-') {\n                neg =\
    \ true;\n                c = buf[idx++];\n            }\n        }\n        x\
    \ = 0;\n        while (c >= '0') {\n            x = x * 10 + (c & 15);\n     \
    \       c = buf[idx++];\n        }\n        if constexpr (is_signed<T>::value)\
    \ {\n            if (neg) x = -x;\n        }\n    }\n\n    template<class Head,\
    \ class... Tail>\n    void read(Head &head, Tail &...tail) {\n        read(head);\n\
    \        (read(tail), ...);\n    }\n\n    void read(char &c) {\n        c = skip();\n\
    \    }\n\n    void read(string &s) {\n        s.clear();\n        ensure();\n\
    \        while (buf[idx] && buf[idx] <= ' ') {\n            ++idx;\n         \
    \   ensure();\n        }\n        while (true) {\n            int start = idx;\n\
    \            while (idx < size && buf[idx] > ' ') ++idx;\n            s.append(buf\
    \ + start, idx - start);\n            if (idx < size) break;\n            load();\n\
    \        }\n        if (idx < size) ++idx;\n    }\n};\n\nstruct Printer {\n  \
    \  static constexpr int BUFSIZE = 1 << 17;\n    static constexpr int OFFSET =\
    \ 64;\n    char buf[BUFSIZE];\n    int idx;\n    inline static constexpr FastIoDigitTable\
    \ table{};\n\n    Printer() : idx(0) {}\n    ~Printer() { flush(); }\n\n    inline\
    \ void flush() {\n        if (idx) {\n            fwrite(buf, 1, idx, stdout);\n\
    \            idx = 0;\n        }\n    }\n\n    inline void pc(char c) {\n    \
    \    if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++] = c;\n    }\n\n\
    \    inline void write_range(const char *s, size_t n) {\n        size_t pos =\
    \ 0;\n        while (pos < n) {\n            if (idx == BUFSIZE) flush();\n  \
    \          size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n           \
    \ memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n       \
    \     pos += chunk;\n        }\n    }\n\n    void write(const char *s) {\n   \
    \     write_range(s, strlen(s));\n    }\n\n    void write(const string &s) {\n\
    \        write_range(s.data(), s.size());\n    }\n\n    void write(char c) {\n\
    \        pc(c);\n    }\n\n    void write(bool b) {\n        pc(char('0' + (b ?\
    \ 1 : 0)));\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value\
    \ && !is_same<T, bool>::value, int>::type = 0>\n    void write(T x) {\n      \
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
    \ T>\n    void writeln(const T &x) {\n        write(x);\n        pc('\\n');\n\
    \    }\n\n    template<class Head, class... Tail>\n    void writeln(const Head\
    \ &head, const Tail &...tail) {\n        write(head);\n        ((pc(' '), write(tail)),\
    \ ...);\n        pc('\\n');\n    }\n\n    void writeln() {\n        pc('\\n');\n\
    \    }\n};\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n * @docs\
    \ _md/fastio.md\n */\n#line 1 \"math/eulerphi.cpp\"\nint eulerphi(int x){\n  \
    \  int phi = x, xx = x;\n    for (int i = 2; i * i <= x; ++i) {\n        if (xx\
    \ % i == 0) {\n            phi -= phi / i;\n            while(xx % i == 0) xx\
    \ /= i;\n        }\n    }\n    if(xx > 1) phi -= phi/xx;\n    return phi;\n}\n\
    \n/**\n * @brief \u30AA\u30A4\u30E9\u30FC\u306E\u03C6\u95A2\u6570(Euler Phi)\n\
    \ * @docs _md/eulerphi.md\n */\n#line 1 \"math/eulerphi_all.cpp\"\nvector<int>\
    \ eulerphi_all(int M){\n    vector<int> phi(M);\n    vector<bool> isprime(M);\n\
    \    for (int i = 0; i < M; ++i) {\n        phi[i] = i;\n        isprime[i] =\
    \ 1;\n    }\n    for (int i = 2; i < M; ++i) {\n        if(isprime[i]){\n    \
    \        for (int j = i; j < M; j += i) {\n                phi[j] -= phi[j]/i;\n\
    \                isprime[j] = 0;\n            }\n            isprime[i] = 1;\n\
    \        }\n    }\n    return phi;\n}\n\n/**\n * @brief \u30AA\u30A4\u30E9\u30FC\
    \u306E\u03C6\u95A2\u6570\u30C6\u30FC\u30D6\u30EB(Euler Phi Table)\n * @docs _md/eulerphi_all.md\n\
    \ */\n#line 1 \"math/get_min_factor.cpp\"\nvector<int> get_min_factor(int n) {\n\
    \    if(n <= 1) return vector<int>{0, 1};\n    vector<bool> prime(n+1, true);\n\
    \    vector<int> min_factor(n+1, 0);\n    min_factor[0] = 0, min_factor[1] = 1;\n\
    \    prime[0] = false; prime[1] = false;\n    for(ll i = 2; i <= n; i++){\n  \
    \      if(prime[i]) {\n            min_factor[i] = i;\n            for(ll j =\
    \ i << 1; j <= n; j += i) {\n                prime[j] = false;\n             \
    \   if(min_factor[j] == 0) min_factor[j] = i;\n            }\n        }\n    }\n\
    \    return min_factor;\n}\n\n/**\n * @brief \u6700\u5C0F\u7D20\u56E0\u6570\u30C6\
    \u30FC\u30D6\u30EB(Min Factor Table)\n * @docs _md/get_min_factor.md\n */\n#line\
    \ 14 \"test/yosupo_many_aplusb_eulerphi.test.cpp\"\n\nint brute_phi(int x) {\n\
    \    int res = 0;\n    for (int i = 1; i <= x; ++i) {\n        if (gcd(i, x) ==\
    \ 1) ++res;\n    }\n    return res;\n}\n\nint brute_min_factor(int x) {\n    if\
    \ (x == 0) return 0;\n    if (x == 1) return 1;\n    for (int p = 2; p <= x; ++p)\
    \ {\n        if (x % p == 0) return p;\n    }\n    return x;\n}\n\nint main()\
    \ {\n    {\n        for (int n = 1; n <= 300; ++n) {\n            if (eulerphi(n)\
    \ != brute_phi(n)) return 1;\n        }\n\n        for (int m = 1; m <= 300; ++m)\
    \ {\n            auto phi = eulerphi_all(m);\n            if ((int)phi.size()\
    \ != m) return 1;\n            for (int i = 0; i < m; ++i) {\n               \
    \ if (phi[i] != (i == 0 ? 0 : brute_phi(i))) return 1;\n            }\n      \
    \  }\n\n        for (int n = 0; n <= 300; ++n) {\n            auto min_factor\
    \ = get_min_factor(n);\n            if ((int)min_factor.size() != max(2, n + 1))\
    \ return 1;\n            for (int i = 0; i <= n; ++i) {\n                if (min_factor[i]\
    \ != brute_min_factor(i)) return 1;\n            }\n        }\n\n        mt19937\
    \ rng(123456789);\n        for (int trial = 0; trial < 1000; ++trial) {\n    \
    \        int n = uniform_int_distribution<int>(1, 10000)(rng);\n            if\
    \ (eulerphi(n) != brute_phi(n)) return 1;\n        }\n    }\n\n    Scanner sc;\n\
    \    Printer pr;\n    int t;\n    sc.read(t);\n    while (t--) {\n        long\
    \ long a, b;\n        sc.read(a, b);\n        pr.writeln(a + b);\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include\
    \ <algorithm>\n#include <numeric>\n#include <random>\n#include <vector>\nusing\
    \ namespace std;\nusing ll = long long;\n\n#include \"../util/fastio.cpp\"\n#include\
    \ \"../math/eulerphi.cpp\"\n#include \"../math/eulerphi_all.cpp\"\n#include \"\
    ../math/get_min_factor.cpp\"\n\nint brute_phi(int x) {\n    int res = 0;\n   \
    \ for (int i = 1; i <= x; ++i) {\n        if (gcd(i, x) == 1) ++res;\n    }\n\
    \    return res;\n}\n\nint brute_min_factor(int x) {\n    if (x == 0) return 0;\n\
    \    if (x == 1) return 1;\n    for (int p = 2; p <= x; ++p) {\n        if (x\
    \ % p == 0) return p;\n    }\n    return x;\n}\n\nint main() {\n    {\n      \
    \  for (int n = 1; n <= 300; ++n) {\n            if (eulerphi(n) != brute_phi(n))\
    \ return 1;\n        }\n\n        for (int m = 1; m <= 300; ++m) {\n         \
    \   auto phi = eulerphi_all(m);\n            if ((int)phi.size() != m) return\
    \ 1;\n            for (int i = 0; i < m; ++i) {\n                if (phi[i] !=\
    \ (i == 0 ? 0 : brute_phi(i))) return 1;\n            }\n        }\n\n       \
    \ for (int n = 0; n <= 300; ++n) {\n            auto min_factor = get_min_factor(n);\n\
    \            if ((int)min_factor.size() != max(2, n + 1)) return 1;\n        \
    \    for (int i = 0; i <= n; ++i) {\n                if (min_factor[i] != brute_min_factor(i))\
    \ return 1;\n            }\n        }\n\n        mt19937 rng(123456789);\n   \
    \     for (int trial = 0; trial < 1000; ++trial) {\n            int n = uniform_int_distribution<int>(1,\
    \ 10000)(rng);\n            if (eulerphi(n) != brute_phi(n)) return 1;\n     \
    \   }\n    }\n\n    Scanner sc;\n    Printer pr;\n    int t;\n    sc.read(t);\n\
    \    while (t--) {\n        long long a, b;\n        sc.read(a, b);\n        pr.writeln(a\
    \ + b);\n    }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - math/eulerphi.cpp
  - math/eulerphi_all.cpp
  - math/get_min_factor.cpp
  isVerificationFile: true
  path: test/yosupo_many_aplusb_eulerphi.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 21:12:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_many_aplusb_eulerphi.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_many_aplusb_eulerphi.test.cpp
- /verify/test/yosupo_many_aplusb_eulerphi.test.cpp.html
title: test/yosupo_many_aplusb_eulerphi.test.cpp
---
