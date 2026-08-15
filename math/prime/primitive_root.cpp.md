---
category: "\u6570\u5B66"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/prime/miller_rabin.cpp
    title: "Miller-Rabin\u7D20\u6570\u5224\u5B9A"
  - icon: ':heavy_check_mark:'
    path: math/prime/primefactor_ll.cpp
    title: "\u7D20\u56E0\u6570\u5206\u89E3(Pollard Rho)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_primitive_root.test.cpp
    title: test/yosupo_primitive_root.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u539F\u59CB\u6839(Primitive Root)"
    links: []
  bundledCode: "#line 1 \"math/prime/miller_rabin.cpp\"\nusing u128 = __uint128_t;\n\
    \nstruct mod64 {\n    unsigned long long n;\n    static unsigned long long mod,\
    \ inv, r2;\n    mod64() : n(0) {}\n    mod64(unsigned long long x) : n(init(x))\
    \ {}\n    static unsigned long long init(unsigned long long w) {\n        return\
    \ reduce(u128(w) * r2);\n    }\n    static void set_mod(unsigned long long m)\
    \ {\n        mod = inv = m;\n        for (int i = 0; i < 5; ++i) inv *= 2 - inv\
    \ * m;\n        r2 = -u128(m) % m;\n    }\n    static unsigned long long reduce(u128\
    \ x) {\n        unsigned long long y =\n            static_cast<unsigned long\
    \ long>(x >> 64)\n            - static_cast<unsigned long long>((u128(static_cast<unsigned\
    \ long long>(x) * inv) * mod) >> 64);\n        return (long long)y < 0 ? y + mod\
    \ : y;\n    }\n    mod64& operator*=(mod64 x) {\n        n = reduce(u128(n) *\
    \ x.n);\n        return *this;\n    }\n    mod64 operator*(mod64 x) const {\n\
    \        return mod64(*this) *= x;\n    }\n    mod64& operator+=(mod64 x) {\n\
    \        n += x.n - mod;\n        if((long long)n < 0) n += mod;\n        return\
    \ *this;\n    }\n    mod64 operator+(mod64 x) const {\n        return mod64(*this)\
    \ += x;\n    }\n    unsigned long long val() const {\n        return reduce(n);\n\
    \    }\n};\n\nunsigned long long mod64::mod, mod64::inv, mod64::r2;\n\nbool suspect(unsigned\
    \ long long a, unsigned long long s, unsigned long long d, unsigned long long\
    \ n){\n    if(mod64::mod != n) mod64::set_mod(n);\n    mod64 x(1), xx(a), one(1),\
    \ minusone(n - 1);\n    while(d > 0){\n        if(d & 1) x *= xx;\n        xx\
    \ *= xx;\n        d >>= 1;\n    }\n    if (x.n == one.n) return true;\n    for\
    \ (unsigned long long r = 0; r < s; ++r) {\n        if(x.n == minusone.n) return\
    \ true;\n        x *= x;\n    }\n    return false;\n}\n\ntemplate<class T>\nbool\
    \ miller_rabin(T m){\n    unsigned long long n = m;\n    if (n <= 1 || (n > 2\
    \ && n % 2 == 0)) return false;\n    if (n == 2 || n == 3 || n == 5 || n == 7)\
    \ return true;\n    if (n % 3 == 0 || n % 5 == 0 || n % 7 == 0) return false;\n\
    \    unsigned long long d = n - 1, s = 0;\n    while (!(d & 1)) { ++s; d >>= 1;\
    \ }\n    static constexpr unsigned long long small[] = {2, 7, 61};\n    static\
    \ constexpr unsigned long long large[] = {2, 325, 9375, 28178, 450775, 9780504,\
    \ 1795265022};\n    if(n < 4759123141ULL) {\n        for (auto p : small) {\n\
    \            if(p >= n) break;\n            if(!suspect(p, s, d, n)) return false;\n\
    \        }\n    } else {\n        for (auto p : large) {\n            if(p >=\
    \ n) break;\n            if(!suspect(p, s, d, n)) return false;\n        }\n \
    \   }\n    return true;\n}\n\n/**\n * @brief Miller-Rabin\u7D20\u6570\u5224\u5B9A\
    \n */\n#line 2 \"math/prime/primefactor_ll.cpp\"\n\ntemplate<typename T>\nstruct\
    \ ExactDiv {\n    T t, i, val;\n    ExactDiv() {}\n    ExactDiv(T n) : t(T(-1)\
    \ / n), i(mul_inv(n)) , val(n) {};\n    T mul_inv(T n) {\n        T x = n;\n \
    \       for (int i = 0; i < 5; ++i) x *= 2 - n * x;\n        return x;\n    }\n\
    \    bool divide(T n) const {\n        if(val == 2) return !(n & 1);\n       \
    \ return n * this->i <= this->t;\n    }\n};\n\nvector<ExactDiv<ull>> get_prime(int\
    \ n){\n    if(n <= 1) return vector<ExactDiv<ull>>();\n    vector<bool> is_prime(n+1,\
    \ true);\n    vector<ExactDiv<ull>> prime;\n    is_prime[0] = is_prime[1] = false;\n\
    \    for (int i = 2; i <= n; ++i) {\n        if(is_prime[i]) prime.emplace_back(i);\n\
    \        for (auto &&j : prime){\n            ull v = (ull)i * j.val;\n      \
    \      if(v > (ull)n) break;\n            is_prime[v] = false;\n            if(j.divide(i))\
    \ break;\n        }\n    }\n    return prime;\n}\n\nconstexpr int pollard_pm1_bound\
    \ = 3000;\nconst auto primes = get_prime(pollard_pm1_bound);\n\nconstexpr ull\
    \ pollard_batch_size = 208;\nconstexpr ull pollard_pm1_trigger = 2048;\nconstexpr\
    \ ull pollard_pm1_mod_threshold = 500000000000000000ULL;\nconstexpr ull pollard_lazy_mod_limit\
    \ = 1ULL << 61;\n\n// REDC \u306E\u7D50\u679C\u3092\u6B63\u898F\u5316\u3057\u306A\
    \u3044\u3002mod < 2^61 \u306A\u3089 rho \u5185\u306E\u5024\u306F 4 * mod \u672A\
    \u6E80\u306B\u53CE\u307E\u308B\u3002\nstruct mod64_lazy {\n    ull n;\n    static\
    \ ull mod, inv, r2;\n    mod64_lazy() : n(0) {}\n    mod64_lazy(ull x) : n(init(x))\
    \ {}\n    static void set_mod(ull m) {\n        mod = inv = m;\n        for (int\
    \ i = 0; i < 5; ++i) inv *= 2 - inv * m;\n        inv = -inv;\n        r2 = -u128(m)\
    \ % m;\n    }\n    static ull reduce(u128 x) {\n        ull q = (ull)x * inv;\n\
    \        return (x + u128(q) * mod) >> 64;\n    }\n    static ull init(ull x)\
    \ {\n        ull y = reduce(u128(x) * r2);\n        return y >= mod ? y - mod\
    \ : y;\n    }\n    mod64_lazy& operator*=(mod64_lazy x) {\n        n = reduce(u128(n)\
    \ * x.n);\n        return *this;\n    }\n    mod64_lazy& operator+=(mod64_lazy\
    \ x) {\n        n += x.n;\n        return *this;\n    }\n};\n\null mod64_lazy::mod,\
    \ mod64_lazy::inv, mod64_lazy::r2;\n\nvector<ull> get_pollard_pm1_exponents()\
    \ {\n    vector<ull> res;\n    ull product = 1;\n    for (auto &&p : primes) {\n\
    \        if (p.val > pollard_pm1_bound) break;\n        ull power = p.val;\n \
    \       while (power <= pollard_pm1_bound / p.val) power *= p.val;\n        if\
    \ (product > ull(-1) / power) {\n            res.emplace_back(product);\n    \
    \        product = 1;\n        }\n        product *= power;\n    }\n    res.emplace_back(product);\n\
    \    return res;\n}\n\nconst auto pollard_pm1_exponents = get_pollard_pm1_exponents();\n\
    \nmt19937_64 rng(0x8a5cd789635d2dffULL);\n\nmod64_lazy pow_mod64_lazy(mod64_lazy\
    \ x, ull exponent) {\n    mod64_lazy res = x;\n    for (int bit = 62 - __builtin_clzll(exponent);\
    \ bit >= 0; --bit) {\n        res *= res;\n        if ((exponent >> bit) & 1)\
    \ res *= x;\n    }\n    return res;\n}\n\null pollard_pm1(ull n) {\n    mod64_lazy::set_mod(n);\n\
    \    mod64_lazy x(2), one(1);\n    for (ull exponent : pollard_pm1_exponents)\
    \ {\n        x = pow_mod64_lazy(x, exponent);\n    }\n    ull diff = x.n > one.n\
    \ ? x.n - one.n : one.n - x.n;\n    ull g = gcd(diff, n);\n    return g != 1 &&\
    \ g != n ? g : 0;\n}\n\ntemplate<class Mint>\null pollard_rho_impl(ull nn, bool\
    \ use_pm1) {\n    uniform_int_distribution<ull> ra(1, nn - 1);\n    Mint::set_mod(nn);\n\
    \    bool pm1_done = !use_pm1;\n    while(true){\n        ull c_ = ra(rng), g\
    \ = 1, r = 1;\n        while(c_ == nn - 2) c_ = ra(rng);\n        Mint y(ra(rng)),\
    \ xx(0), c(c_), ys(0), q(1);\n        while(g == 1){\n            xx.n = y.n;\n\
    \            for (ull i = 0; i < r; ++i) {\n                y *= y; y += c;\n\
    \            }\n            ull k = 0; g = 1;\n            while(k < r && g ==\
    \ 1){\n                ull lim = min(pollard_batch_size, r - k);\n           \
    \     for (ull i = 0; i < lim; ++i) {\n                    ys.n = y.n;\n     \
    \               y *= y; y += c;\n                    Mint diff;\n            \
    \        diff.n = xx.n > y.n ? xx.n - y.n : y.n - xx.n;\n                    q\
    \ *= diff;\n                }\n                g = gcd<ull>(q.n, nn);\n      \
    \          k += pollard_batch_size;\n            }\n            r *= 2;\n    \
    \        if (!pm1_done && r == pollard_pm1_trigger) {\n                ull factor\
    \ = pollard_pm1(nn);\n                if (factor != 0) return factor;\n      \
    \          pm1_done = true;\n            }\n        }\n        if(g == nn) g =\
    \ 1;\n        while (g == 1){\n            ys *= ys; ys += c;\n            ull\
    \ diff = xx.n > ys.n ? xx.n - ys.n : ys.n - xx.n;\n            g = gcd<ull>(diff,\
    \ nn);\n        }\n        if (g != nn) return g;\n    }\n}\n\ntemplate<class\
    \ T>\nT pollard_rho2(T n) {\n    ull nn = n;\n    if ((nn & 1) == 0) return 2;\n\
    \    if (nn < pollard_lazy_mod_limit) {\n        return (T)pollard_rho_impl<mod64_lazy>(nn,\
    \ nn >= pollard_pm1_mod_threshold);\n    }\n    return (T)pollard_rho_impl<mod64>(nn,\
    \ false);\n}\n\ntemplate<class T>\nvoid prime_factor_impl(T n, vector<T> &res,\
    \ bool trial){\n    if(trial) {\n        for (auto &&i : primes) {\n         \
    \   while (i.divide(n)){\n                res.emplace_back(i.val);\n         \
    \       n /= i.val;\n            }\n        }\n    }\n    if(n == 1) return;\n\
    \    if(miller_rabin(n)) {\n        res.emplace_back(n);\n        return;\n  \
    \  }\n    ull root = __builtin_sqrtl((long double)n);\n    while ((u128)(root\
    \ + 1) * (root + 1) <= (ull)n) ++root;\n    while ((u128)root * root > (ull)n)\
    \ --root;\n    if ((u128)root * root == (ull)n) {\n        prime_factor_impl((T)root,\
    \ res, false);\n        prime_factor_impl((T)root, res, false);\n        return;\n\
    \    }\n    T x = pollard_rho2(n);\n    prime_factor_impl(x, res, false);\n  \
    \  prime_factor_impl(n / x, res, false);\n}\n\ntemplate<class T>\nvector<T> prime_factor(T\
    \ n){\n    vector<T> res;\n    prime_factor_impl(n, res, true);\n    sort(res.begin(),res.end());\n\
    \    return res;\n}\n\n/**\n * @brief \u7D20\u56E0\u6570\u5206\u89E3(Pollard Rho)\n\
    \ */\n#line 2 \"math/prime/primitive_root.cpp\"\nll primitive_root(ll m) {\n \
    \   if (m == 2) return 1;\n    auto divs = prime_factor(m - 1);\n    divs.erase(unique(divs.begin(),\
    \ divs.end()), divs.end());\n    auto mod_pow = [&](ll x, ll n) {\n        ull\
    \ a = x, r = 1, mod = m;\n        while (n > 0) {\n            if (n & 1) r =\
    \ (u128)r * a % mod;\n            a = (u128)a * a % mod;\n            n >>= 1;\n\
    \        }\n        return (ll)r;\n    };\n    for (ll g = 2;; g++) {\n      \
    \  bool ok = true;\n        for (auto &&d : divs) {\n            if (mod_pow(g,\
    \ (m - 1) / d) == 1) {\n                ok = false;\n                break;\n\
    \            }\n        }\n        if (ok) return g;\n    }\n}\n\n/**\n * @brief\
    \ \u539F\u59CB\u6839(Primitive Root)\n */\n"
  code: "#include \"primefactor_ll.cpp\"\nll primitive_root(ll m) {\n    if (m ==\
    \ 2) return 1;\n    auto divs = prime_factor(m - 1);\n    divs.erase(unique(divs.begin(),\
    \ divs.end()), divs.end());\n    auto mod_pow = [&](ll x, ll n) {\n        ull\
    \ a = x, r = 1, mod = m;\n        while (n > 0) {\n            if (n & 1) r =\
    \ (u128)r * a % mod;\n            a = (u128)a * a % mod;\n            n >>= 1;\n\
    \        }\n        return (ll)r;\n    };\n    for (ll g = 2;; g++) {\n      \
    \  bool ok = true;\n        for (auto &&d : divs) {\n            if (mod_pow(g,\
    \ (m - 1) / d) == 1) {\n                ok = false;\n                break;\n\
    \            }\n        }\n        if (ok) return g;\n    }\n}\n\n/**\n * @brief\
    \ \u539F\u59CB\u6839(Primitive Root)\n */\n"
  dependsOn:
  - math/prime/primefactor_ll.cpp
  - math/prime/miller_rabin.cpp
  isVerificationFile: false
  path: math/prime/primitive_root.cpp
  requiredBy: []
  timestamp: '2026-08-11 13:43:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_primitive_root.test.cpp
date: 2026-03-08
documentation_of: math/prime/primitive_root.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u539F\u59CB\u6839(Primitive Root)"
---

## 説明
素数 `p` に対する原始根を 1 つ返す。
`p - 1` の素因数を使って候補を判定する。
計算量はおおむね $O(sqrt(p) + k log p)$。

## できること
- `ll primitive_root(ll p)`
  素数 `p` に対する原始根を 1 つ返す

## 使い方
`p` は素数を仮定する。
返る値は最小とは限らないが、`mod p` の乗法群を生成する。
