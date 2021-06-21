---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/primefactor_ll2.cpp\"\n#include <random>\n\nusing ull\
    \ = unsigned long long;\nusing u128 = __uint128_t;\n\ntemplate< class T>\nT pow_\
    \ (T x, ull n, ull M){\n    T u = 1;\n    if(n > 0){\n        u = pow_(x, n/2,\
    \ M);\n        if (n % 2 == 0) u = (u*u) % M;\n        else u = (((u * u)% M)\
    \ * x) % M;\n    }\n    return u;\n};\n\nbool suspect(__uint128_t a, ull s, ull\
    \ d, ull n){\n    __uint128_t x = pow_(a, d, n);\n    if (x == 1) return true;\n\
    \    for (int r = 0; r < s; ++r) {\n        if(x == n-1) return true;\n      \
    \  x = x * x % n;\n    }\n    return false;\n}\n\ntemplate<class T>\nbool miller_rabin(T\
    \ m){\n    ull n = m;\n    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;\n\
    \    ull d = n - 1, s = 0;\n    while (!(d&1)) {++s; d >>= 1;}\n    vector<ull>\
    \ v = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};\n    if(n <= 4759123141LL)\
    \ v = {2, 7, 61};\n    for (auto &&p : v) {\n        if(p >= n) break;\n     \
    \   if(!suspect(p, s, d, n)) return false;\n    }\n    return true;\n}\n\n\ntemplate<typename\
    \ T>\nstruct ExactDiv {\n    T t, i, val;\n    ExactDiv() {}\n    ExactDiv(T n)\
    \ : t(T(-1) / n), i(mul_inv(n)) , val(n) {};\n    T mul_inv(T n) {\n        T\
    \ x = n;\n        for (int i = 0; i < 5; ++i) x *= 2 - n * x;\n        return\
    \ x;\n    }\n    bool divide(T n) const {\n        if(val == 2) return !(n & 1);\n\
    \        return n * this->i <= this->t;\n    }\n};\n\nvector<ExactDiv<ull>> get_prime(int\
    \ n){\n    if(n <= 1) return vector<ExactDiv<ull>>();\n    vector<bool> is_prime(n+1,\
    \ true);\n    vector<ExactDiv<ull>> prime;\n    is_prime[0] = is_prime[1] = false;\n\
    \    for (int i = 2; i <= n; ++i) {\n        if(is_prime[i]) prime.emplace_back(i);\n\
    \        for (auto &&j : prime){\n            if(i*j.val > n) break;\n       \
    \     is_prime[i*j.val] = false;\n            if(j.divide(i)) break;\n       \
    \ }\n    }\n    return prime;\n}\nconst auto primes = get_prime(50000);\n\nrandom_device\
    \ rng;\n\nstruct mod64 {\n    ull n;\n    static ull mod, inv, r2;\n    mod64()\
    \ : n(0) {}\n    mod64(ull x) : n(init(x)) {}\n    static ull init(ull w) { return\
    \ reduce(u128(w) * r2); }\n    static void set_mod(ull m) {\n        mod = inv\
    \ = m;\n        for (int i = 0; i < 5; ++i) inv *= 2 - inv * m;\n        r2 =\
    \ -u128(m) % m;\n    }\n    static ull reduce(u128 x) {\n        ull y = ull(x\
    \ >> 64) - ull((u128(ull(x) * inv) * mod) >> 64);\n        return ll(y) < 0 ?\
    \ y + mod : y;\n    };\n    mod64& operator+=(mod64 x) { n += x.n - mod; if(ll(n)\
    \ < 0) n += mod; return *this; }\n    mod64 operator+(mod64 x) const { return\
    \ mod64(*this) += x; }\n    mod64& operator*=(mod64 x) { n = reduce(u128(n) *\
    \ x.n);  return *this; }\n    mod64 operator*(mod64 x) const { return mod64(*this)\
    \ *= x; }\n    ull val() const { return reduce(n); }\n};\n\null mod64::mod, mod64::inv,\
    \ mod64::r2;\n\ntemplate<class T>\nT pollard_rho2(T n) {\n    uniform_int_distribution<T>\
    \ ra(1, n-1);\n    mod64::set_mod(n);\n    while(true){\n        ull c_ = ra(rng),\
    \ g = 1, r = 1, m = 500;\n        while(c_ == n-2) c_ = ra(rng);\n        mod64\
    \ y(ra(rng)), xx(0), c(c_), ys(0), q(1);\n        while(g == 1){\n           \
    \ xx.n = y.n;\n            for (int i = 1; i <= r; ++i) {\n                y *=\
    \ y; y += c;\n            }\n            T k = 0; g = 1;\n            while(k\
    \ < r && g == 1){\n                for (int i = 1; i <= (m > (r-k) ? (r-k) : m);\
    \ ++i) {\n                    ys.n = y.n;\n                    y *= y; y += c;\n\
    \                    ull xxx = xx.val(), yyy = y.val();\n                    q\
    \ *= mod64(xxx > yyy ? xxx - yyy : yyy - xxx);\n                }\n          \
    \      g = __gcd<ll>(q.val(), n);\n                k += m;\n            }\n  \
    \          r *= 2;\n        }\n        if(g == n) g = 1;\n        while (g ==\
    \ 1){\n            ys *= ys; ys += c;\n            ull xxx = xx.val(), yyy = ys.val();\n\
    \            g = __gcd<ll>(xxx > yyy ? xxx - yyy : yyy - xxx, n);\n        }\n\
    \        if (g != n && miller_rabin(g)) return g;\n    }\n}\n\ntemplate<class\
    \ T>\nvector<T> prime_factor(T n, int d = 0){\n    vector<T> a, res;\n    if(!d)\
    \ for (auto &&i : primes) {\n            while (i.divide(n)){\n              \
    \  res.emplace_back(i.val);\n                n /= i.val;\n            }\n    \
    \    }\n    while(n != 1){\n        if(miller_rabin(n)){\n            a.emplace_back(n);\n\
    \            break;\n        }\n        T x = pollard_rho2(n);\n        n /= x;\n\
    \        a.emplace_back(x);\n    }\n    for (auto &&i : a) {\n        if (miller_rabin(i))\
    \ {\n            res.emplace_back(i);\n        } else {\n            vector<T>\
    \ b = prime_factor(i, d + 1);\n            for (auto &&j : b) res.emplace_back(j);\n\
    \        }\n    }\n    sort(res.begin(),res.end());\n    return res;\n}\n"
  code: "#include <random>\n\nusing ull = unsigned long long;\nusing u128 = __uint128_t;\n\
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
    \      g = __gcd<ll>(q.val(), n);\n                k += m;\n            }\n  \
    \          r *= 2;\n        }\n        if(g == n) g = 1;\n        while (g ==\
    \ 1){\n            ys *= ys; ys += c;\n            ull xxx = xx.val(), yyy = ys.val();\n\
    \            g = __gcd<ll>(xxx > yyy ? xxx - yyy : yyy - xxx, n);\n        }\n\
    \        if (g != n && miller_rabin(g)) return g;\n    }\n}\n\ntemplate<class\
    \ T>\nvector<T> prime_factor(T n, int d = 0){\n    vector<T> a, res;\n    if(!d)\
    \ for (auto &&i : primes) {\n            while (i.divide(n)){\n              \
    \  res.emplace_back(i.val);\n                n /= i.val;\n            }\n    \
    \    }\n    while(n != 1){\n        if(miller_rabin(n)){\n            a.emplace_back(n);\n\
    \            break;\n        }\n        T x = pollard_rho2(n);\n        n /= x;\n\
    \        a.emplace_back(x);\n    }\n    for (auto &&i : a) {\n        if (miller_rabin(i))\
    \ {\n            res.emplace_back(i);\n        } else {\n            vector<T>\
    \ b = prime_factor(i, d + 1);\n            for (auto &&j : b) res.emplace_back(j);\n\
    \        }\n    }\n    sort(res.begin(),res.end());\n    return res;\n}"
  dependsOn: []
  isVerificationFile: false
  path: math/primefactor_ll2.cpp
  requiredBy: []
  timestamp: '2021-06-21 15:24:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/primefactor_ll2.cpp
layout: document
redirect_from:
- /library/math/primefactor_ll2.cpp
- /library/math/primefactor_ll2.cpp.html
title: math/primefactor_ll2.cpp
---
