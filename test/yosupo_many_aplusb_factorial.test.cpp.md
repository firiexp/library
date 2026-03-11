---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/factorial.cpp
    title: "\u968E\u4E57\u30FB\u4E8C\u9805\u4FC2\u6570(Factorial)"
  - icon: ':heavy_check_mark:'
    path: util/fastio.cpp
    title: Fast IO
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
    PROBLEM: https://judge.yosupo.jp/problem/many_aplusb
    links:
    - https://judge.yosupo.jp/problem/many_aplusb
  bundledCode: "#line 1 \"test/yosupo_many_aplusb_factorial.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include <vector>\nusing\
    \ namespace std;\n\nusing ll = long long;\nusing uint = unsigned;\nusing ull =\
    \ unsigned long long;\n\nstatic constexpr int MOD = 998244353;\n\n#line 1 \"util/fastio.cpp\"\
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
    \    }\n};\n\n/**\n * @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n */\n#line\
    \ 1 \"math/factorial.cpp\"\n\n#line 1 \"util/modint.cpp\"\n\n\n\ntemplate <uint\
    \ M>\nstruct modint {\n    uint val;\npublic:\n    static modint raw(int v) {\
    \ modint x; x.val = v; return x; }\n    static constexpr uint get_mod() { return\
    \ M; }\n    modint() : val(0) {}\n    template <class T>\n    modint(T v) { ll\
    \ x = (ll)(v%(ll)(M)); if (x < 0) x += M; val = uint(x); }\n    modint(bool v)\
    \ { val = ((unsigned int)(v) % M); }\n    modint& operator++() { val++; if (val\
    \ == M) val = 0; return *this; }\n    modint& operator--() { if (val == 0) val\
    \ = M; val--; return *this; }\n    modint operator++(int) { modint result = *this;\
    \ ++*this; return result; }\n    modint operator--(int) { modint result = *this;\
    \ --*this; return result; }\n    modint& operator+=(const modint& b) { val +=\
    \ b.val; if (val >= M) val -= M; return *this; }\n    modint& operator-=(const\
    \ modint& b) { val -= b.val; if (val >= M) val += M; return *this; }\n    modint&\
    \ operator*=(const modint& b) { ull z = val; z *= b.val; val = (uint)(z % M);\
    \ return *this; }\n    modint& operator/=(const modint& b) { return *this = *this\
    \ * b.inv(); }\n    modint operator+() const { return *this; }\n    modint operator-()\
    \ const { return modint() - *this; }\n    modint pow(long long n) const { modint\
    \ x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r;\
    \ }\n    modint inv() const { return pow(M-2); }\n    friend modint operator+(const\
    \ modint& a, const modint& b) { return modint(a) += b; }\n    friend modint operator-(const\
    \ modint& a, const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    #define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\n/**\n * @brief modint(\u56FA\u5B9A\
    MOD)\n */\n\n\n#line 3 \"math/factorial.cpp\"\n#endif\n\ntemplate <class Mint\
    \ = mint>\nclass Factorial {\n    inline static vector<Mint> facts, factinv, invs;\n\
    \n    static void init() {\n        if (!facts.empty()) return;\n        facts.push_back(Mint(1));\n\
    \        factinv.push_back(Mint(1));\n        invs.push_back(Mint(0));\n     \
    \   invs.push_back(Mint(1));\n    }\n\n    static void expand(int n) {\n     \
    \   init();\n        if (n < (int)facts.size()) return;\n        int old = facts.size();\n\
    \        int mod = Mint::get_mod();\n        facts.resize(n + 1);\n        factinv.resize(n\
    \ + 1);\n        invs.resize(n + 1);\n        for (int i = max(2, old); i <= n;\
    \ ++i) {\n            invs[i] = -Mint(mod / i) * invs[mod % i];\n        }\n \
    \       for (int i = old; i <= n; ++i) {\n            facts[i] = facts[i - 1]\
    \ * Mint(i);\n            factinv[i] = factinv[i - 1] * invs[i];\n        }\n\
    \    }\npublic:\n    explicit Factorial(int n = 0) {\n        expand(n);\n   \
    \ }\n    void ensure(int n) const {\n        if (n >= 0) expand(n);\n    }\n \
    \   int max_n() const {\n        init();\n        return (int)facts.size() - 1;\n\
    \    }\n    Mint fact(int k) const {\n        if (k < 0) return inv_fact(-k);\n\
    \        expand(k);\n        return facts[k];\n    }\n    Mint inv_fact(int k)\
    \ const {\n        if (k < 0) return 0;\n        expand(k);\n        return factinv[k];\n\
    \    }\n    Mint inv(int k) const {\n        if (k < 0) return 0;\n        expand(k);\n\
    \        return invs[k];\n    }\n    Mint operator[](int k) const {\n        return\
    \ k >= 0 ? fact(k) : inv_fact(-k);\n    }\n    Mint C(int n, int k) const {\n\
    \        if (n < 0 || k < 0 || n < k) return 0;\n        expand(n);\n        return\
    \ facts[n] * factinv[k] * factinv[n - k];\n    }\n    Mint P(int n, int k) const\
    \ {\n        if (n < 0 || k < 0 || n < k) return 0;\n        expand(n);\n    \
    \    return facts[n] * factinv[n - k];\n    }\n    Mint H(int n, int k) const\
    \ {\n        if (n < 0 || k < 0) return 0;\n        if (k == 0) return 1;\n  \
    \      if (n == 0) return 0;\n        return C(n + k - 1, k);\n    }\n};\n\n/**\n\
    \ * @brief \u968E\u4E57\u30FB\u4E8C\u9805\u4FC2\u6570(Factorial)\n */\n#line 14\
    \ \"test/yosupo_many_aplusb_factorial.test.cpp\"\n\nvector<vector<mint>> build_comb(int\
    \ n) {\n    vector<vector<mint>> comb(n + 1, vector<mint>(n + 1));\n    comb[0][0]\
    \ = 1;\n    for (int i = 0; i < n; ++i) {\n        for (int j = 0; j <= i; ++j)\
    \ {\n            comb[i + 1][j] += comb[i][j];\n            comb[i + 1][j + 1]\
    \ += comb[i][j];\n        }\n    }\n    return comb;\n}\n\nmint brute_perm(int\
    \ n, int k) {\n    if (n < 0 || k < 0 || n < k) return 0;\n    mint res = 1;\n\
    \    for (int i = 0; i < k; ++i) res *= n - i;\n    return res;\n}\n\nmint brute_homo(const\
    \ vector<vector<mint>> &comb, int n, int k) {\n    if (n < 0 || k < 0) return\
    \ 0;\n    if (k == 0) return 1;\n    if (n == 0) return 0;\n    return comb[n\
    \ + k - 1][k];\n}\n\nint main() {\n    {\n        Factorial f;\n        Factorial\
    \ g;\n        auto comb = build_comb(80);\n        if (f.max_n() != 0) return\
    \ 1;\n        if (g.max_n() != 0) return 1;\n        if (f.fact(0) != 1 || f.inv_fact(0)\
    \ != 1 || f[0] != 1) return 1;\n        for (int n = 0; n <= 30; ++n) {\n    \
    \        if (n > 0 && f.inv(n) * mint(n) != 1) return 1;\n            if (f.fact(n)\
    \ * f.inv_fact(n) != 1) return 1;\n            if (f[-n] != f.inv_fact(n)) return\
    \ 1;\n            if (f.max_n() < n) return 1;\n            for (int k = 0; k\
    \ <= 30; ++k) {\n                mint want_c = (k <= n ? comb[n][k] : mint(0));\n\
    \                if (f.C(n, k) != want_c) return 1;\n                if (f.P(n,\
    \ k) != brute_perm(n, k)) return 1;\n                if (f.H(n, k) != brute_homo(comb,\
    \ n, k)) return 1;\n            }\n        }\n        if (f.C(-1, 0) != 0 || f.C(3,\
    \ -1) != 0 || f.C(3, 4) != 0) return 1;\n        if (f.P(-1, 0) != 0 || f.P(3,\
    \ -1) != 0 || f.P(3, 4) != 0) return 1;\n        if (f.H(-1, 0) != 0 || f.H(3,\
    \ -1) != 0 || f.H(0, 3) != 0) return 1;\n        if (f.inv(-1) != 0) return 1;\n\
    \        if (f.inv_fact(-1) != 0) return 1;\n        f.ensure(100);\n        if\
    \ (f.max_n() < 100) return 1;\n        if (g.max_n() < 100) return 1;\n    }\n\
    \n    Scanner sc;\n    Printer pr;\n    int t;\n    sc.read(t);\n    while (t--)\
    \ {\n        ll a, b;\n        sc.read(a, b);\n        pr.writeln(a + b);\n  \
    \  }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb\"\n\n#include\
    \ <vector>\nusing namespace std;\n\nusing ll = long long;\nusing uint = unsigned;\n\
    using ull = unsigned long long;\n\nstatic constexpr int MOD = 998244353;\n\n#include\
    \ \"../util/fastio.cpp\"\n#include \"../math/factorial.cpp\"\n\nvector<vector<mint>>\
    \ build_comb(int n) {\n    vector<vector<mint>> comb(n + 1, vector<mint>(n + 1));\n\
    \    comb[0][0] = 1;\n    for (int i = 0; i < n; ++i) {\n        for (int j =\
    \ 0; j <= i; ++j) {\n            comb[i + 1][j] += comb[i][j];\n            comb[i\
    \ + 1][j + 1] += comb[i][j];\n        }\n    }\n    return comb;\n}\n\nmint brute_perm(int\
    \ n, int k) {\n    if (n < 0 || k < 0 || n < k) return 0;\n    mint res = 1;\n\
    \    for (int i = 0; i < k; ++i) res *= n - i;\n    return res;\n}\n\nmint brute_homo(const\
    \ vector<vector<mint>> &comb, int n, int k) {\n    if (n < 0 || k < 0) return\
    \ 0;\n    if (k == 0) return 1;\n    if (n == 0) return 0;\n    return comb[n\
    \ + k - 1][k];\n}\n\nint main() {\n    {\n        Factorial f;\n        Factorial\
    \ g;\n        auto comb = build_comb(80);\n        if (f.max_n() != 0) return\
    \ 1;\n        if (g.max_n() != 0) return 1;\n        if (f.fact(0) != 1 || f.inv_fact(0)\
    \ != 1 || f[0] != 1) return 1;\n        for (int n = 0; n <= 30; ++n) {\n    \
    \        if (n > 0 && f.inv(n) * mint(n) != 1) return 1;\n            if (f.fact(n)\
    \ * f.inv_fact(n) != 1) return 1;\n            if (f[-n] != f.inv_fact(n)) return\
    \ 1;\n            if (f.max_n() < n) return 1;\n            for (int k = 0; k\
    \ <= 30; ++k) {\n                mint want_c = (k <= n ? comb[n][k] : mint(0));\n\
    \                if (f.C(n, k) != want_c) return 1;\n                if (f.P(n,\
    \ k) != brute_perm(n, k)) return 1;\n                if (f.H(n, k) != brute_homo(comb,\
    \ n, k)) return 1;\n            }\n        }\n        if (f.C(-1, 0) != 0 || f.C(3,\
    \ -1) != 0 || f.C(3, 4) != 0) return 1;\n        if (f.P(-1, 0) != 0 || f.P(3,\
    \ -1) != 0 || f.P(3, 4) != 0) return 1;\n        if (f.H(-1, 0) != 0 || f.H(3,\
    \ -1) != 0 || f.H(0, 3) != 0) return 1;\n        if (f.inv(-1) != 0) return 1;\n\
    \        if (f.inv_fact(-1) != 0) return 1;\n        f.ensure(100);\n        if\
    \ (f.max_n() < 100) return 1;\n        if (g.max_n() < 100) return 1;\n    }\n\
    \n    Scanner sc;\n    Printer pr;\n    int t;\n    sc.read(t);\n    while (t--)\
    \ {\n        ll a, b;\n        sc.read(a, b);\n        pr.writeln(a + b);\n  \
    \  }\n    return 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - math/factorial.cpp
  - util/modint.cpp
  isVerificationFile: true
  path: test/yosupo_many_aplusb_factorial.test.cpp
  requiredBy: []
  timestamp: '2026-03-11 21:27:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_many_aplusb_factorial.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_many_aplusb_factorial.test.cpp
- /verify/test/yosupo_many_aplusb_factorial.test.cpp.html
title: test/yosupo_many_aplusb_factorial.test.cpp
---
