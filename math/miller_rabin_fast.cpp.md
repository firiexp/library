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
  bundledCode: "#line 1 \"math/miller_rabin_fast.cpp\"\nusing u128 = __uint128_t;\n\
    \nstruct mod64 {\n    u64 n;\n    static u64 mod, inv, r2;\n    mod64() : n(0)\
    \ {}\n    mod64(u64 x) : n(init(x)) {}\n    static u64 init(u64 w) { return reduce(u128(w)\
    \ * r2); }\n    static void set_mod(u64 m) {\n        mod = inv = m;\n       \
    \ for (int i = 0; i < 5; ++i) inv *= 2 - inv * m;\n        r2 = -u128(m) % m;\n\
    \    }\n    static u64 reduce(u128 x) {\n        u64 y = u64(x >> 64) - u64((u128(u64(x)\
    \ * inv) * mod) >> 64);\n        return ll(y) < 0 ? y + mod : y;\n    };\n   \
    \ mod64& operator+=(mod64 x) { n += x.n - mod; if(ll(n) < 0) n += mod; return\
    \ *this; }\n    mod64 operator+(mod64 x) const { return mod64(*this) += x; }\n\
    \    mod64& operator*=(mod64 x) { n = reduce(u128(n) * x.n);  return *this; }\n\
    \    mod64 operator*(mod64 x) const { return mod64(*this) *= x; }\n    u64 val()\
    \ const { return reduce(n); }\n};\n\nu64 mod64::mod, mod64::inv, mod64::r2;\n\n\
    bool suspect(u64 a, u64 s, u64 d, u64 n){\n    if(mod64::mod != n) mod64::set_mod(n);\n\
    \    mod64 x(1), xx(a), one(x), minusone(n-1);\n    while(d > 0){\n        if(d&1)\
    \ x = x * xx;\n        xx = xx * xx;\n        d >>= 1;\n    }\n    if (x.n ==\
    \ one.n) return true;\n    for (int r = 0; r < s; ++r) {\n        if(x.n == minusone.n)\
    \ return true;\n        x = x * x;\n    }\n    return false;\n}\n\ntemplate<class\
    \ T>\nbool miller_rabin(T n){\n    if (n <= 1 || (n > 2 && n % 2 == 0)) return\
    \ false;\n    u64 d = n - 1, s = 0;\n    while (!(d&1)) {++s; d >>= 1;}\n    vector<uint64_t>\
    \ v = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};\n    if(n < 4759123141LL)\
    \ v = {2, 7, 61};\n    for (auto &&p : v) {\n        if(p >= n) break;\n     \
    \   if(!suspect(p, s, d, n)) return false;\n    }\n    return true;\n}\n"
  code: "using u128 = __uint128_t;\n\nstruct mod64 {\n    u64 n;\n    static u64 mod,\
    \ inv, r2;\n    mod64() : n(0) {}\n    mod64(u64 x) : n(init(x)) {}\n    static\
    \ u64 init(u64 w) { return reduce(u128(w) * r2); }\n    static void set_mod(u64\
    \ m) {\n        mod = inv = m;\n        for (int i = 0; i < 5; ++i) inv *= 2 -\
    \ inv * m;\n        r2 = -u128(m) % m;\n    }\n    static u64 reduce(u128 x) {\n\
    \        u64 y = u64(x >> 64) - u64((u128(u64(x) * inv) * mod) >> 64);\n     \
    \   return ll(y) < 0 ? y + mod : y;\n    };\n    mod64& operator+=(mod64 x) {\
    \ n += x.n - mod; if(ll(n) < 0) n += mod; return *this; }\n    mod64 operator+(mod64\
    \ x) const { return mod64(*this) += x; }\n    mod64& operator*=(mod64 x) { n =\
    \ reduce(u128(n) * x.n);  return *this; }\n    mod64 operator*(mod64 x) const\
    \ { return mod64(*this) *= x; }\n    u64 val() const { return reduce(n); }\n};\n\
    \nu64 mod64::mod, mod64::inv, mod64::r2;\n\nbool suspect(u64 a, u64 s, u64 d,\
    \ u64 n){\n    if(mod64::mod != n) mod64::set_mod(n);\n    mod64 x(1), xx(a),\
    \ one(x), minusone(n-1);\n    while(d > 0){\n        if(d&1) x = x * xx;\n   \
    \     xx = xx * xx;\n        d >>= 1;\n    }\n    if (x.n == one.n) return true;\n\
    \    for (int r = 0; r < s; ++r) {\n        if(x.n == minusone.n) return true;\n\
    \        x = x * x;\n    }\n    return false;\n}\n\ntemplate<class T>\nbool miller_rabin(T\
    \ n){\n    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;\n    u64 d = n -\
    \ 1, s = 0;\n    while (!(d&1)) {++s; d >>= 1;}\n    vector<uint64_t> v = {2,\
    \ 325, 9375, 28178, 450775, 9780504, 1795265022};\n    if(n < 4759123141LL) v\
    \ = {2, 7, 61};\n    for (auto &&p : v) {\n        if(p >= n) break;\n       \
    \ if(!suspect(p, s, d, n)) return false;\n    }\n    return true;\n}"
  dependsOn: []
  isVerificationFile: false
  path: math/miller_rabin_fast.cpp
  requiredBy: []
  timestamp: '2021-03-26 19:39:30+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/miller_rabin_fast.cpp
layout: document
redirect_from:
- /library/math/miller_rabin_fast.cpp
- /library/math/miller_rabin_fast.cpp.html
title: math/miller_rabin_fast.cpp
---
