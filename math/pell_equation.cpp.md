---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/isqrt.cpp
    title: "\u6574\u6570\u5E73\u65B9\u6839(Integer Square Root)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_pell_equation.test.cpp
    title: test/yosupo_aplusb_pell_equation.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/isqrt.cpp\"\null Isqrt(ull const &x){\n    ull ret\
    \ = (ull)sqrtl(x);\n    while(ret > 0 && ret*ret > x) --ret;\n    while(x - ret*ret\
    \ > 2*ret) ++ret;\n    return ret;\n}\n\n/**\n * @brief \u6574\u6570\u5E73\u65B9\
    \u6839(Integer Square Root)\n */\n#line 2 \"math/pell_equation.cpp\"\n\nvector<ll>\
    \ sqrt_fraction(ll n) {\n    ll a0 = Isqrt(n);\n    vector<ll> ret{a0};\n    if\
    \ (a0 * a0 == n) return ret;\n    ll m = 0, d = 1, a = a0;\n    do {\n       \
    \ m = (__int128)d * a - m;\n        d = ((__int128)n - (__int128)m * m) / d;\n\
    \        a = (a0 + m) / d;\n        ret.push_back(a);\n    } while (a != 2 * a0);\n\
    \    return ret;\n}\n\npair<ll, ll> pell_equation(ll d) {\n    auto li = sqrt_fraction(d);\n\
    \    if (li.size() <= 1) return {0, 0};\n    li.pop_back();\n    __int128 p =\
    \ li.back(), q = 1;\n    for (int i = (int)li.size() - 2; i >= 0; --i) {\n   \
    \     swap(p, q);\n        p += q * li[i];\n        assert(p <= LLONG_MAX && q\
    \ <= LLONG_MAX);\n    }\n    if (p * p - d * q * q == -1) {\n        __int128\
    \ x = p * p + d * q * q;\n        q = 2 * p * q;\n        p = x;\n    }\n    assert(p\
    \ <= LLONG_MAX && q <= LLONG_MAX);\n    return {(ll)p, (ll)q};\n}\n"
  code: "#include \"./isqrt.cpp\"\n\nvector<ll> sqrt_fraction(ll n) {\n    ll a0 =\
    \ Isqrt(n);\n    vector<ll> ret{a0};\n    if (a0 * a0 == n) return ret;\n    ll\
    \ m = 0, d = 1, a = a0;\n    do {\n        m = (__int128)d * a - m;\n        d\
    \ = ((__int128)n - (__int128)m * m) / d;\n        a = (a0 + m) / d;\n        ret.push_back(a);\n\
    \    } while (a != 2 * a0);\n    return ret;\n}\n\npair<ll, ll> pell_equation(ll\
    \ d) {\n    auto li = sqrt_fraction(d);\n    if (li.size() <= 1) return {0, 0};\n\
    \    li.pop_back();\n    __int128 p = li.back(), q = 1;\n    for (int i = (int)li.size()\
    \ - 2; i >= 0; --i) {\n        swap(p, q);\n        p += q * li[i];\n        assert(p\
    \ <= LLONG_MAX && q <= LLONG_MAX);\n    }\n    if (p * p - d * q * q == -1) {\n\
    \        __int128 x = p * p + d * q * q;\n        q = 2 * p * q;\n        p =\
    \ x;\n    }\n    assert(p <= LLONG_MAX && q <= LLONG_MAX);\n    return {(ll)p,\
    \ (ll)q};\n}\n"
  dependsOn:
  - math/isqrt.cpp
  isVerificationFile: false
  path: math/pell_equation.cpp
  requiredBy: []
  timestamp: '2026-10-08 14:15:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_pell_equation.test.cpp
documentation_of: math/pell_equation.cpp
layout: document
redirect_from:
- /library/math/pell_equation.cpp
- /library/math/pell_equation.cpp.html
title: math/pell_equation.cpp
---
