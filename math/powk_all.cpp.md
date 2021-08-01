---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: math/get_min_factor.cpp
    title: math/get_min_factor.cpp
  - icon: ':question:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"util/modint.cpp\"\ntemplate <uint M>\nstruct modint {\n\
    \    uint val;\npublic:\n    static modint raw(int v) { modint x; x.val = v; return\
    \ x; }\n    modint() : val(0) {}\n    template <class T>\n    modint(T v) { ll\
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
    \n/**\n * @brief modint(\u56FA\u5B9AMOD)\n * @docs _md/modint.md\n */\n#line 2\
    \ \"math/powk_all.cpp\"\n\n#line 1 \"math/get_min_factor.cpp\"\nvector<int> get_min_factor(int\
    \ n) {\n    if(n <= 1) return vector<int>{0, 1};\n    vector<bool> prime(n+1,\
    \ true);\n    vector<int> min_factor(n+1, 0);\n    min_factor[0] = 0, min_factor[1]\
    \ = 1;\n    prime[0] = false; prime[1] = false;\n    for(ll i = 2; i <= n; i++){\n\
    \        if(prime[i]) {\n            min_factor[i] = i;\n            for(ll j\
    \ = i << 1; j <= n; j += i) {\n                prime[j] = false;\n           \
    \     if(min_factor[j] == 0) min_factor[j] = i;\n            }\n        }\n  \
    \  }\n    return min_factor;\n}\n#line 4 \"math/powk_all.cpp\"\nvector<mint> powk_all(int\
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
  isVerificationFile: false
  path: math/powk_all.cpp
  requiredBy: []
  timestamp: '2021-07-05 13:06:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/powk_all.cpp
layout: document
redirect_from:
- /library/math/powk_all.cpp
- /library/math/powk_all.cpp.html
title: math/powk_all.cpp
---
