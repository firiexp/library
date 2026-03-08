---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/CRT.cpp
    title: math/CRT.cpp
  - icon: ':heavy_check_mark:'
    path: math/binom_mod_prime_power.cpp
    title: "\u4E8C\u9805\u4FC2\u6570 mod p^q"
  - icon: ':heavy_check_mark:'
    path: math/extgcd.cpp
    title: math/extgcd.cpp
  - icon: ':heavy_check_mark:'
    path: math/modinv.cpp
    title: math/modinv.cpp
  - icon: ':heavy_check_mark:'
    path: math/primefactor2.cpp
    title: math/primefactor2.cpp
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
    PROBLEM: https://judge.yosupo.jp/problem/binomial_coefficient
    links:
    - https://judge.yosupo.jp/problem/binomial_coefficient
  bundledCode: "#line 1 \"test/yosupo_binomial_coefficient.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/binomial_coefficient\"\n\n#include <cstdint>\n\
    #include <map>\n#include <numeric>\n#include <vector>\nusing namespace std;\n\
    using ll = long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\n\
    \n#line 1 \"util/fastio.cpp\"\n#include <cstdio>\n#include <cstring>\n#include\
    \ <string>\n#include <type_traits>\nusing namespace std;\n\nstruct FastIoDigitTable\
    \ {\n    char num[40000];\n\n    constexpr FastIoDigitTable() : num() {\n    \
    \    for (int i = 0; i < 10000; ++i) {\n            int x = i;\n            for\
    \ (int j = 3; j >= 0; --j) {\n                num[i * 4 + j] = char('0' + x %\
    \ 10);\n                x /= 10;\n            }\n        }\n    }\n};\n\nstruct\
    \ Scanner {\n    static constexpr int BUFSIZE = 1 << 17;\n    static constexpr\
    \ int OFFSET = 64;\n    char buf[BUFSIZE + 1];\n    int idx, size;\n\n    Scanner()\
    \ : idx(0), size(0) {}\n\n    inline void load() {\n        int len = size - idx;\n\
    \        memmove(buf, buf + idx, len);\n        size = len + (int)fread(buf +\
    \ len, 1, BUFSIZE - len, stdin);\n        idx = 0;\n        buf[size] = 0;\n \
    \   }\n\n    inline void ensure() {\n        if (idx + OFFSET > size) load();\n\
    \    }\n\n    inline char skip() {\n        ensure();\n        while (buf[idx]\
    \ && buf[idx] <= ' ') {\n            ++idx;\n            ensure();\n        }\n\
    \        return buf[idx++];\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value,\
    \ int>::type = 0>\n    void read(T &x) {\n        char c = skip();\n        bool\
    \ neg = false;\n        if constexpr (is_signed<T>::value) {\n            if (c\
    \ == '-') {\n                neg = true;\n                c = buf[idx++];\n  \
    \          }\n        }\n        x = 0;\n        while (c >= '0') {\n        \
    \    x = x * 10 + (c & 15);\n            c = buf[idx++];\n        }\n        if\
    \ constexpr (is_signed<T>::value) {\n            if (neg) x = -x;\n        }\n\
    \    }\n\n    template<class Head, class... Tail>\n    void read(Head &head, Tail\
    \ &...tail) {\n        read(head);\n        (read(tail), ...);\n    }\n\n    void\
    \ read(char &c) {\n        c = skip();\n    }\n\n    void read(string &s) {\n\
    \        s.clear();\n        ensure();\n        while (buf[idx] && buf[idx] <=\
    \ ' ') {\n            ++idx;\n            ensure();\n        }\n        while\
    \ (true) {\n            int start = idx;\n            while (buf[idx] > ' ') ++idx;\n\
    \            s.append(buf + start, idx - start);\n            if (buf[idx] <=\
    \ ' ') break;\n            load();\n        }\n        ++idx;\n    }\n};\n\nstruct\
    \ Printer {\n    static constexpr int BUFSIZE = 1 << 17;\n    static constexpr\
    \ int OFFSET = 64;\n    char buf[BUFSIZE];\n    int idx;\n    inline static constexpr\
    \ FastIoDigitTable table{};\n\n    Printer() : idx(0) {}\n    ~Printer() { flush();\
    \ }\n\n    inline void flush() {\n        if (idx) {\n            fwrite(buf,\
    \ 1, idx, stdout);\n            idx = 0;\n        }\n    }\n\n    inline void\
    \ pc(char c) {\n        if (idx > BUFSIZE - OFFSET) flush();\n        buf[idx++]\
    \ = c;\n    }\n\n    inline void write_range(const char *s, size_t n) {\n    \
    \    size_t pos = 0;\n        while (pos < n) {\n            if (idx == BUFSIZE)\
    \ flush();\n            size_t chunk = min(n - pos, (size_t)(BUFSIZE - idx));\n\
    \            memcpy(buf + idx, s + pos, chunk);\n            idx += (int)chunk;\n\
    \            pos += chunk;\n        }\n    }\n\n    void write(const char *s)\
    \ {\n        write_range(s, strlen(s));\n    }\n\n    void write(const string\
    \ &s) {\n        write_range(s.data(), s.size());\n    }\n\n    void write(char\
    \ c) {\n        pc(c);\n    }\n\n    void write(bool b) {\n        pc(char('0'\
    \ + (b ? 1 : 0)));\n    }\n\n    template<class T, typename enable_if<is_integral<T>::value\
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
    \    }\n};\n#line 1 \"math/extgcd.cpp\"\ntemplate<typename T>\nT extgcd(T a, T\
    \ b, T &x ,T &y){\n    for (T u = y = 1, v = x = 0; a; ) {\n        ll q = b/a;\n\
    \        swap(x -= q*u, u);\n        swap(y -= q*v, v);\n        swap(b -= q*a,\
    \ a);\n    }\n    return b;\n}\n \n#line 2 \"math/CRT.cpp\"\n\npair<ll, ll> CRT(const\
    \ vector<pair<ll, ll>> &a){\n    ll R = 0, M = 1;\n    for (auto &&i : a) {\n\
    \        ll r = (i.first+i.second)%i.second, m = i.second;\n        if(m < M)\
    \ swap(r, R), swap(m, M);\n        if(M%m == 0){\n            if(R % m != r) return\
    \ {};\n            continue;\n        }\n        ll p, q;\n        ll g = extgcd(M,\
    \ m, p, q); // p = inv(M') mod m'\n        ll mm = m/g;\n        if((r-R)%g) return\
    \ {0, 0};\n        ll x = (r-R)/g % mm * p % mm;\n        R += x*M;\n        M\
    \ *= mm;\n        if(R < 0) R += M;\n    }\n    return {R, M};\n}\n#line 1 \"\
    math/primefactor2.cpp\"\nusing uint = uint32_t;\n\ntemplate<typename T>\nstruct\
    \ ExactDiv {\n    T t, i, val;\n    ExactDiv() {}\n    ExactDiv(T n) : t(T(-1)\
    \ / n), i(mul_inv(n)) , val(n) {};\n    T mul_inv(T n) {\n        T x = n;\n \
    \       for (int i = 0; i < 5; ++i) x *= 2 - n * x;\n        return x;\n    }\n\
    \    bool divide(T n) const {\n        if(val == 2) return !(n & 1);\n       \
    \ return n * this->i <= this->t;\n    }\n};\n\nvector<ExactDiv<uint>> get_prime(int\
    \ n){\n    if(n <= 1) return vector<ExactDiv<uint>>();\n    vector<bool> is_prime(n+1,\
    \ true);\n    vector<ExactDiv<uint>> prime;\n    is_prime[0] = is_prime[1] = false;\n\
    \    for (int i = 2; i <= n; ++i) {\n        if(is_prime[i]) prime.emplace_back(i);\n\
    \        for (auto &&j : prime){\n            if(i*j.val > n) break;\n       \
    \     is_prime[i*j.val] = false;\n            if(j.divide(i)) break;\n       \
    \ }\n    }\n    return prime;\n}\nconst auto primes = get_prime(32000);\n\ntemplate<class\
    \ T>\nvector<T> prime_factor(T n){\n    vector<T> res;\n    for (auto &&i : primes)\
    \ {\n        while (i.divide(n)){\n            res.emplace_back(i.val);\n    \
    \        n /= i.val;\n        }\n    }\n    if(n != 1) res.emplace_back(n);\n\
    \    return res;\n}\n#line 1 \"math/modinv.cpp\"\ntemplate<typename T>  \nT mod_inv(T\
    \ x, T M){  \n   T u = 1, t = 1, v = 0, s = 0, m = M;  \n   while (x) { T q =\
    \ m/x; swap(s -= q*u, u); swap(t -= q*v, v); swap(m -= q*x, x); }  \n   if(s <\
    \ 0) s += M;  \n   return s;  \n}\n#line 2 \"math/binom_mod_prime_power.cpp\"\n\
    \nstruct BinomModPrimePower {\n    ll p, mod;\n    int q;\n    ll block_prod;\n\
    \    vector<ll> ppow;\n    vector<int> prod;\n\n    explicit BinomModPrimePower(ll\
    \ prime, int exponent) : p(prime), mod(1), q(exponent), ppow(exponent + 1, 1)\
    \ {\n        for (int i = 0; i < q; ++i) {\n            mod *= p;\n          \
    \  ppow[i + 1] = mod;\n        }\n        block_prod = (p == 2 && q >= 3 ? 1 :\
    \ mod - 1);\n        prod.assign(mod + 1, 1);\n        for (int i = 1; i <= mod;\
    \ ++i) {\n            prod[i] = prod[i - 1];\n            if (i % p != 0) prod[i]\
    \ = (ull)prod[i] * i % mod;\n        }\n    }\n\n    pair<ll, ll> factorial(ll\
    \ n) const {\n        ll x = 1, e = 0;\n        while (n) {\n            if (block_prod\
    \ != 1 && (n / mod) & 1) x = mod - x;\n            x = (ull)x * prod[n % mod]\
    \ % mod;\n            n /= p;\n            e += n;\n        }\n        return\
    \ {x, e};\n    }\n\n    ll C(ll n, ll k) const {\n        if (k < 0 || k > n)\
    \ return 0;\n        auto [a, ea] = factorial(n);\n        auto [b, eb] = factorial(k);\n\
    \        auto [c, ec] = factorial(n - k);\n        ll e = ea - eb - ec;\n    \
    \    if (e >= q) return 0;\n        ll x = (ull)b * c % mod;\n        return (ull)a\
    \ * mod_inv(x, mod) % mod * ppow[e] % mod;\n    }\n\n    ll modulus() const {\n\
    \        return mod;\n    }\n};\n\n/**\n * @brief \u4E8C\u9805\u4FC2\u6570 mod\
    \ p^q\n * @docs _md/binom_mod_prime_power.md\n */\n#line 16 \"test/yosupo_binomial_coefficient.test.cpp\"\
    \n\nll brute(ll n, ll k, ll mod) {\n    if (k < 0 || k > n) return 0;\n    vector<vector<ll>>\
    \ dp(n + 1, vector<ll>(k + 1));\n    dp[0][0] = 1 % mod;\n    for (ll i = 0; i\
    \ < n; ++i) {\n        for (ll j = 0; j <= min(i, k); ++j) {\n            dp[i\
    \ + 1][j] += dp[i][j];\n            dp[i + 1][j] %= mod;\n            if (j !=\
    \ k) {\n                dp[i + 1][j + 1] += dp[i][j];\n                dp[i +\
    \ 1][j + 1] %= mod;\n            }\n        }\n    }\n    return dp[n][k];\n}\n\
    \nint main() {\n    {\n        map<ll, BinomModPrimePower> cache;\n        for\
    \ (int mod = 2; mod <= 120; ++mod) {\n            auto pf = prime_factor<ll>(mod);\n\
    \            vector<pair<ll, int>> fac;\n            for (ll p : pf) {\n     \
    \           if (fac.empty() || fac.back().first != p) fac.emplace_back(p, 1);\n\
    \                else fac.back().second++;\n            }\n            for (int\
    \ n = 0; n <= 20; ++n) {\n                for (int k = 0; k <= n; ++k) {\n   \
    \                 vector<pair<ll, ll>> rem;\n                    for (auto [p,\
    \ e] : fac) {\n                        ll pe = 1;\n                        for\
    \ (int i = 0; i < e; ++i) pe *= p;\n                        auto it = cache.find(pe);\n\
    \                        if (it == cache.end()) it = cache.emplace(pe, BinomModPrimePower(p,\
    \ e)).first;\n                        rem.emplace_back(it->second.C(n, k), pe);\n\
    \                    }\n                    if (CRT(rem).first != brute(n, k,\
    \ mod)) return 1;\n                }\n            }\n        }\n    }\n\n    Scanner\
    \ sc;\n    Printer pr;\n    int t;\n    ll mod;\n    sc.read(t, mod);\n    auto\
    \ pf = prime_factor<ll>(mod);\n    vector<pair<ll, int>> fac;\n    for (ll p :\
    \ pf) {\n        if (fac.empty() || fac.back().first != p) fac.emplace_back(p,\
    \ 1);\n        else fac.back().second++;\n    }\n    vector<BinomModPrimePower>\
    \ binoms;\n    vector<ll> mods;\n    for (auto [p, e] : fac) {\n        binoms.emplace_back(p,\
    \ e);\n        mods.emplace_back(binoms.back().modulus());\n    }\n    while (t--)\
    \ {\n        ll n, k;\n        sc.read(n, k);\n        vector<pair<ll, ll>> rem;\n\
    \        for (int i = 0; i < (int)binoms.size(); ++i) {\n            rem.emplace_back(binoms[i].C(n,\
    \ k), mods[i]);\n        }\n        pr.writeln(CRT(rem).first);\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient\"\n\
    \n#include <cstdint>\n#include <map>\n#include <numeric>\n#include <vector>\n\
    using namespace std;\nusing ll = long long;\nusing uint = unsigned;\nusing ull\
    \ = unsigned long long;\n\n#include \"../util/fastio.cpp\"\n#include \"../math/CRT.cpp\"\
    \n#include \"../math/primefactor2.cpp\"\n#include \"../math/binom_mod_prime_power.cpp\"\
    \n\nll brute(ll n, ll k, ll mod) {\n    if (k < 0 || k > n) return 0;\n    vector<vector<ll>>\
    \ dp(n + 1, vector<ll>(k + 1));\n    dp[0][0] = 1 % mod;\n    for (ll i = 0; i\
    \ < n; ++i) {\n        for (ll j = 0; j <= min(i, k); ++j) {\n            dp[i\
    \ + 1][j] += dp[i][j];\n            dp[i + 1][j] %= mod;\n            if (j !=\
    \ k) {\n                dp[i + 1][j + 1] += dp[i][j];\n                dp[i +\
    \ 1][j + 1] %= mod;\n            }\n        }\n    }\n    return dp[n][k];\n}\n\
    \nint main() {\n    {\n        map<ll, BinomModPrimePower> cache;\n        for\
    \ (int mod = 2; mod <= 120; ++mod) {\n            auto pf = prime_factor<ll>(mod);\n\
    \            vector<pair<ll, int>> fac;\n            for (ll p : pf) {\n     \
    \           if (fac.empty() || fac.back().first != p) fac.emplace_back(p, 1);\n\
    \                else fac.back().second++;\n            }\n            for (int\
    \ n = 0; n <= 20; ++n) {\n                for (int k = 0; k <= n; ++k) {\n   \
    \                 vector<pair<ll, ll>> rem;\n                    for (auto [p,\
    \ e] : fac) {\n                        ll pe = 1;\n                        for\
    \ (int i = 0; i < e; ++i) pe *= p;\n                        auto it = cache.find(pe);\n\
    \                        if (it == cache.end()) it = cache.emplace(pe, BinomModPrimePower(p,\
    \ e)).first;\n                        rem.emplace_back(it->second.C(n, k), pe);\n\
    \                    }\n                    if (CRT(rem).first != brute(n, k,\
    \ mod)) return 1;\n                }\n            }\n        }\n    }\n\n    Scanner\
    \ sc;\n    Printer pr;\n    int t;\n    ll mod;\n    sc.read(t, mod);\n    auto\
    \ pf = prime_factor<ll>(mod);\n    vector<pair<ll, int>> fac;\n    for (ll p :\
    \ pf) {\n        if (fac.empty() || fac.back().first != p) fac.emplace_back(p,\
    \ 1);\n        else fac.back().second++;\n    }\n    vector<BinomModPrimePower>\
    \ binoms;\n    vector<ll> mods;\n    for (auto [p, e] : fac) {\n        binoms.emplace_back(p,\
    \ e);\n        mods.emplace_back(binoms.back().modulus());\n    }\n    while (t--)\
    \ {\n        ll n, k;\n        sc.read(n, k);\n        vector<pair<ll, ll>> rem;\n\
    \        for (int i = 0; i < (int)binoms.size(); ++i) {\n            rem.emplace_back(binoms[i].C(n,\
    \ k), mods[i]);\n        }\n        pr.writeln(CRT(rem).first);\n    }\n    return\
    \ 0;\n}\n"
  dependsOn:
  - util/fastio.cpp
  - math/CRT.cpp
  - math/extgcd.cpp
  - math/primefactor2.cpp
  - math/binom_mod_prime_power.cpp
  - math/modinv.cpp
  isVerificationFile: true
  path: test/yosupo_binomial_coefficient.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 19:09:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo_binomial_coefficient.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo_binomial_coefficient.test.cpp
- /verify/test/yosupo_binomial_coefficient.test.cpp.html
title: test/yosupo_binomial_coefficient.test.cpp
---
