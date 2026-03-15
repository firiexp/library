---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: math/get_min_factor.cpp
    title: Get Min Factor
  - icon: ':heavy_check_mark:'
    path: math/linear_sieve.cpp
    title: "\u7DDA\u5F62\u7BE9(Linear Sieve)"
  - icon: ':heavy_check_mark:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"util/modint.cpp\"\n\n\n\ntemplate <uint Mod>\nstruct modint\
    \ {\n    uint val;\npublic:\n    static modint raw(int v) { modint x; x.val =\
    \ v; return x; }\n    static constexpr uint get_mod() { return Mod; }\n    static\
    \ constexpr uint M() { return Mod; }\n    modint() : val(0) {}\n    template <class\
    \ T>\n    modint(T v) { ll x = (ll)(v % (ll)(Mod)); if (x < 0) x += Mod; val =\
    \ uint(x); }\n    modint(bool v) { val = ((unsigned int)(v) % Mod); }\n    uint\
    \ &value() noexcept { return val; }\n    const uint &value() const noexcept {\
    \ return val; }\n    modint& operator++() { val++; if (val == Mod) val = 0; return\
    \ *this; }\n    modint& operator--() { if (val == 0) val = Mod; val--; return\
    \ *this; }\n    modint operator++(int) { modint result = *this; ++*this; return\
    \ result; }\n    modint operator--(int) { modint result = *this; --*this; return\
    \ result; }\n    modint& operator+=(const modint& b) { val += b.val; if (val >=\
    \ Mod) val -= Mod; return *this; }\n    modint& operator-=(const modint& b) {\
    \ val -= b.val; if (val >= Mod) val += Mod; return *this; }\n    modint& operator*=(const\
    \ modint& b) { ull z = val; z *= b.val; val = (uint)(z % Mod); return *this; }\n\
    \    modint& operator/=(const modint& b) { return *this = *this * b.inv(); }\n\
    \    modint operator+() const { return *this; }\n    modint operator-() const\
    \ { return modint() - *this; }\n    modint pow(long long n) const { modint x =\
    \ *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }\n\
    \    modint inv() const { return pow(Mod - 2); }\n    friend modint operator+(const\
    \ modint& a, const modint& b) { return modint(a) += b; }\n    friend modint operator-(const\
    \ modint& a, const modint& b) { return modint(a) -= b; }\n    friend modint operator*(const\
    \ modint& a, const modint& b) { return modint(a) *= b; }\n    friend modint operator/(const\
    \ modint& a, const modint& b) { return modint(a) /= b; }\n    friend bool operator==(const\
    \ modint& a, const modint& b) { return a.val == b.val; }\n    friend bool operator!=(const\
    \ modint& a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    #define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\n/**\n * @brief modint(\u56FA\u5B9A\
    MOD)\n */\n\n\n#line 2 \"math/powk_all.cpp\"\n\n#line 1 \"math/linear_sieve.cpp\"\
    \n\n\n\nstruct LinearSieve {\n    int n;\n    vector<int> primes;\n    vector<int>\
    \ min_factor;\n    vector<int> phi;\n    vector<int> mobius;\n    vector<bool>\
    \ prime_table;\n\n    explicit LinearSieve(int n, bool need_min_factor = false,\
    \ bool need_phi = false, bool need_mobius = false)\n        : n(n < 0 ? 0 : n),\n\
    \          min_factor(need_min_factor ? this->n + 1 : 0),\n          phi(need_phi\
    \ ? this->n + 1 : 0),\n          mobius(need_mobius ? this->n + 1 : 0),\n    \
    \      prime_table(need_min_factor ? 0 : this->n + 1, true) {\n        if (!prime_table.empty())\
    \ {\n            prime_table[0] = false;\n            if (this->n >= 1) prime_table[1]\
    \ = false;\n        }\n        if (!min_factor.empty() && this->n >= 1) min_factor[1]\
    \ = 1;\n        if (!phi.empty()) {\n            phi[0] = 0;\n            if (this->n\
    \ >= 1) phi[1] = 1;\n        }\n        if (!mobius.empty()) {\n            mobius[0]\
    \ = 0;\n            if (this->n >= 1) mobius[1] = 1;\n        }\n        for (int\
    \ i = 2; i <= this->n; ++i) {\n            bool prime = min_factor.empty() ? prime_table[i]\
    \ : min_factor[i] == 0;\n            if (prime) {\n                if (!min_factor.empty())\
    \ min_factor[i] = i;\n                if (!phi.empty()) phi[i] = i - 1;\n    \
    \            if (!mobius.empty()) mobius[i] = -1;\n                primes.emplace_back(i);\n\
    \            }\n            for (auto &&p : primes) {\n                long long\
    \ x = 1LL * i * p;\n                if (x > this->n) break;\n                if\
    \ (!prime_table.empty()) prime_table[x] = false;\n                if (!min_factor.empty())\
    \ min_factor[x] = p;\n                bool same = i % p == 0;\n              \
    \  if (!phi.empty()) phi[x] = same ? phi[i] * p : phi[i] * (p - 1);\n        \
    \        if (!mobius.empty()) mobius[x] = same ? 0 : -mobius[i];\n           \
    \     if (same) break;\n            }\n        }\n    }\n\n    bool is_prime(int\
    \ x) const {\n        if (x < 2 || x > n) return false;\n        if (!min_factor.empty())\
    \ return min_factor[x] == x;\n        return prime_table[x];\n    }\n};\n\n/**\n\
    \ * @brief \u7DDA\u5F62\u7BE9(Linear Sieve)\n */\n\n\n#line 2 \"math/get_min_factor.cpp\"\
    \n\nvector<int> get_min_factor(int n) {\n    return LinearSieve(n, true).min_factor;\n\
    }\n\n/**\n * @brief \u6700\u5C0F\u7D20\u56E0\u6570\u30C6\u30FC\u30D6\u30EB(Min\
    \ Factor Table)\n */\n#line 4 \"math/powk_all.cpp\"\nvector<mint> powk_all(int\
    \ n, ll k) {\n    auto min_factor = get_min_factor(n);\n    vector<mint> res(n+1);\n\
    \    res[1] = 1;\n    for (int i = 2; i <= n; ++i) {\n        if(min_factor[i]\
    \ == i) res[i] = mint(i).pow(k);\n        else res[i] = res[i/min_factor[i]]*res[min_factor[i]];\n\
    \    }\n    return res;\n}\n"
  code: "#include \"../util/modint.cpp\"\n\n#include \"./get_min_factor.cpp\"\nvector<mint>\
    \ powk_all(int n, ll k) {\n    auto min_factor = get_min_factor(n);\n    vector<mint>\
    \ res(n+1);\n    res[1] = 1;\n    for (int i = 2; i <= n; ++i) {\n        if(min_factor[i]\
    \ == i) res[i] = mint(i).pow(k);\n        else res[i] = res[i/min_factor[i]]*res[min_factor[i]];\n\
    \    }\n    return res;\n}"
  dependsOn:
  - util/modint.cpp
  - math/get_min_factor.cpp
  - math/linear_sieve.cpp
  isVerificationFile: false
  path: math/powk_all.cpp
  requiredBy: []
  timestamp: '2026-03-14 20:56:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/powk_all.cpp
layout: document
redirect_from:
- /library/math/powk_all.cpp
- /library/math/powk_all.cpp.html
title: math/powk_all.cpp
---
