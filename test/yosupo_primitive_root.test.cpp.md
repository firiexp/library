---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: math/primefactor_ll2.cpp
    title: math/primefactor_ll2.cpp
  - icon: ':x:'
    path: math/primitive_root.cpp
    title: "\u539F\u59CB\u6839(Primitive Root)"
  - icon: ':question:'
    path: util/fastio.cpp
    title: "\u9AD8\u901F\u5165\u51FA\u529B(Fast IO)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/primitive_root
    links:
    - https://judge.yosupo.jp/problem/primitive_root
  bundledCode: "#line 1 \"test/yosupo_primitive_root.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/primitive_root\"\n\n#include <cstdint>\n\nstatic\
    \ const int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\n\
    using ull = unsigned long long;\n\n#line 1 \"util/fastio.cpp\"\n#include <cstdio>\n\
    #include <cstring>\n#include <string>\n#include <type_traits>\nusing namespace\
    \ std;\n\nstruct FastIoDigitTable {\n    char num[40000];\n\n    constexpr FastIoDigitTable()\
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
    n');\n    }\n\n    void writeln() {\n        pc('\\n');\n    }\n};\n\n/**\n *\
    \ @brief \u9AD8\u901F\u5165\u51FA\u529B(Fast IO)\n * @docs _md/fastio.md\n */\n\
    #line 1 \"math/primefactor_ll2.cpp\"\n#include <algorithm>\n#include <numeric>\n\
    #include <random>\n\nusing ull = unsigned long long;\nusing u128 = __uint128_t;\n\
    \ntemplate< class T>\nT pow_ (T x, ull n, ull M){\n    T u = 1;\n    if(n > 0){\n\
    \        u = pow_(x, n/2, M);\n        if (n % 2 == 0) u = (u*u) % M;\n      \
    \  else u = (((u * u)% M) * x) % M;\n    }\n    return u;\n};\n\nbool suspect(__uint128_t\
    \ a, ull s, ull d, ull n){\n    __uint128_t x = pow_(a, d, n);\n    if (x == 1)\
    \ return true;\n    for (int r = 0; r < s; ++r) {\n        if(x == n-1) return\
    \ true;\n        x = x * x % n;\n    }\n    return false;\n}\n\ntemplate<class\
    \ T>\nbool miller_rabin(T m){\n    ull n = m;\n    if (n <= 1 || (n > 2 && n %\
    \ 2 == 0)) return false;\n    ull d = n - 1, s = 0;\n    while (!(d&1)) {++s;\
    \ d >>= 1;}\n    vector<ull> v = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};\n\
    \    if(n <= 4759123141LL) v = {2, 7, 61};\n    for (auto &&p : v) {\n       \
    \ if(p >= n) break;\n        if(!suspect(p, s, d, n)) return false;\n    }\n \
    \   return true;\n}\n\n\ntemplate<typename T>\nstruct ExactDiv {\n    T t, i,\
    \ val;\n    ExactDiv() {}\n    ExactDiv(T n) : t(T(-1) / n), i(mul_inv(n)) , val(n)\
    \ {};\n    T mul_inv(T n) {\n        T x = n;\n        for (int i = 0; i < 5;\
    \ ++i) x *= 2 - n * x;\n        return x;\n    }\n    bool divide(T n) const {\n\
    \        if(val == 2) return !(n & 1);\n        return n * this->i <= this->t;\n\
    \    }\n};\n\nvector<ExactDiv<ull>> get_prime(int n){\n    if(n <= 1) return vector<ExactDiv<ull>>();\n\
    \    vector<bool> is_prime(n+1, true);\n    vector<ExactDiv<ull>> prime;\n   \
    \ is_prime[0] = is_prime[1] = false;\n    for (int i = 2; i <= n; ++i) {\n   \
    \     if(is_prime[i]) prime.emplace_back(i);\n        for (auto &&j : prime){\n\
    \            if(i*j.val > n) break;\n            is_prime[i*j.val] = false;\n\
    \            if(j.divide(i)) break;\n        }\n    }\n    return prime;\n}\n\
    const auto primes = get_prime(50000);\n\nrandom_device rng;\n\nstruct mod64 {\n\
    \    ull n;\n    static ull mod, inv, r2;\n    mod64() : n(0) {}\n    mod64(ull\
    \ x) : n(init(x)) {}\n    static ull init(ull w) { return reduce(u128(w) * r2);\
    \ }\n    static void set_mod(ull m) {\n        mod = inv = m;\n        for (int\
    \ i = 0; i < 5; ++i) inv *= 2 - inv * m;\n        r2 = -u128(m) % m;\n    }\n\
    \    static ull reduce(u128 x) {\n        ull y = ull(x >> 64) - ull((u128(ull(x)\
    \ * inv) * mod) >> 64);\n        return ll(y) < 0 ? y + mod : y;\n    };\n   \
    \ mod64& operator+=(mod64 x) { n += x.n - mod; if(ll(n) < 0) n += mod; return\
    \ *this; }\n    mod64 operator+(mod64 x) const { return mod64(*this) += x; }\n\
    \    mod64& operator*=(mod64 x) { n = reduce(u128(n) * x.n);  return *this; }\n\
    \    mod64 operator*(mod64 x) const { return mod64(*this) *= x; }\n    ull val()\
    \ const { return reduce(n); }\n};\n\null mod64::mod, mod64::inv, mod64::r2;\n\n\
    template<class T>\nT pollard_rho2(T n) {\n    uniform_int_distribution<T> ra(1,\
    \ n-1);\n    mod64::set_mod(n);\n    while(true){\n        ull c_ = ra(rng), g\
    \ = 1, r = 1, m = 500;\n        while(c_ == n-2) c_ = ra(rng);\n        mod64\
    \ y(ra(rng)), xx(0), c(c_), ys(0), q(1);\n        while(g == 1){\n           \
    \ xx.n = y.n;\n            for (int i = 1; i <= r; ++i) {\n                y *=\
    \ y; y += c;\n            }\n            T k = 0; g = 1;\n            while(k\
    \ < r && g == 1){\n                for (int i = 1; i <= (m > (r-k) ? (r-k) : m);\
    \ ++i) {\n                    ys.n = y.n;\n                    y *= y; y += c;\n\
    \                    ull xxx = xx.val(), yyy = y.val();\n                    q\
    \ *= mod64(xxx > yyy ? xxx - yyy : yyy - xxx);\n                }\n          \
    \      g = gcd<ull>(q.val(), (ull)n);\n                k += m;\n            }\n\
    \            r *= 2;\n        }\n        if(g == n) g = 1;\n        while (g ==\
    \ 1){\n            ys *= ys; ys += c;\n            ull xxx = xx.val(), yyy = ys.val();\n\
    \            g = gcd<ull>(xxx > yyy ? xxx - yyy : yyy - xxx, (ull)n);\n      \
    \  }\n        if (g != n && miller_rabin(g)) return g;\n    }\n}\n\ntemplate<class\
    \ T>\nvector<T> prime_factor(T n, int d = 0){\n    vector<T> a, res;\n    if(!d)\
    \ for (auto &&i : primes) {\n            while (i.divide(n)){\n              \
    \  res.emplace_back(i.val);\n                n /= i.val;\n            }\n    \
    \    }\n    while(n != 1){\n        if(miller_rabin(n)){\n            a.emplace_back(n);\n\
    \            break;\n        }\n        T x = pollard_rho2(n);\n        n /= x;\n\
    \        a.emplace_back(x);\n    }\n    for (auto &&i : a) {\n        if (miller_rabin(i))\
    \ {\n            res.emplace_back(i);\n        } else {\n            vector<T>\
    \ b = prime_factor(i, d + 1);\n            for (auto &&j : b) res.emplace_back(j);\n\
    \        }\n    }\n    sort(res.begin(),res.end());\n    return res;\n}\n#line\
    \ 2 \"math/primitive_root.cpp\"\nll primitive_root(ll m) {\n    if (m == 2) return\
    \ 1;\n    auto divs = prime_factor(m - 1);\n    divs.erase(unique(divs.begin(),\
    \ divs.end()), divs.end());\n    auto mod_pow = [&](ll x, ll n) {\n        ull\
    \ a = x, r = 1, mod = m;\n        while (n > 0) {\n            if (n & 1) r =\
    \ (u128)r * a % mod;\n            a = (u128)a * a % mod;\n            n >>= 1;\n\
    \        }\n        return (ll)r;\n    };\n    for (ll g = 2;; g++) {\n      \
    \  bool ok = true;\n        for (auto &&d : divs) {\n            if (mod_pow(g,\
    \ (m - 1) / d) == 1) {\n                ok = false;\n                break;\n\
    \            }\n        }\n        if (ok) return g;\n    }\n}\n\n/**\n * @brief\
    \ \u539F\u59CB\u6839(Primitive Root)\n * @docs _md/primitive_root.md\n */\n#line\
    \ 12 \"test/yosupo_primitive_root.test.cpp\"\n\nint main() {\n    Scanner in;\n\
    \    Printer out;\n    int q;\n    in.read(q);\n    while (q--) {\n        ll\
    \ p;\n        in.read(p);\n        out.writeln(primitive_root(p));\n    }\n  \
    \  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/primitive_root\"\n\n#include\
    \ <cstdint>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing\
    \ uint = unsigned;\nusing ull = unsigned long long;\n\n#include \"../util/fastio.cpp\"\
    \n#include \"../math/primitive_root.cpp\"\n\nint main() {\n    Scanner in;\n \
    \   Printer out;\n    int q;\n    in.read(q);\n    while (q--) {\n        ll p;\n\
    \        in.read(p);\n        out.writeln(primitive_root(p));\n    }\n    return\
    \ 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - math/primitive_root.cpp
  - math/primefactor_ll2.cpp
  isVerificationFile: true
  path: test/yosupo_primitive_root.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/yosupo_primitive_root.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_primitive_root.test.cpp
- /verify/test/yosupo_primitive_root.test.cpp.html
title: test/yosupo_primitive_root.test.cpp
---
