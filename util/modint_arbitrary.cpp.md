---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"util/modint_arbitrary.cpp\"\nstruct modint {\n    ll val;\n\
    \    static ll &mod(){\n        static ll mod_ = 0;\n        return mod_;\n  \
    \  }\n\n    static void set_mod(const ll x) { mod() = x; }\n    static ll M()\
    \ {return mod(); }\n\n    modint(const ll x) : val(x) {\n        val = x%M();\n\
    \        while(val < 0) val += M();\n    }\n\n    modint operator+(const modint\
    \ a) const { return modint(*this) += a; }\n    modint operator-(const modint a)\
    \ const { return modint(*this) -= a; }\n    modint operator*(const modint a) const\
    \ { return modint(*this) *= a; }\n    modint operator/(const modint a) const {\
    \ return modint(*this) /= a; }\n    modint operator-() const { return {M()-val};\
    \ }\n    modint inv() const {\n        ll u = 1, v = 0, s = 0, t = 1, m = M(),\
    \ x = val;\n        while (x) {ll q = M()/x; swap(s -= q*u, u); swap(t -= q*v,\
    \ v); swap(m -= q*x, x); }\n        if(s < 0) s += M();\n        return modint(s);\n\
    \    }\n    modint pow(ll n){\n        ll u = 1, xx = val;\n        while (n >\
    \ 0){ if (n&1) u = u * xx % M(); xx = xx * xx % M(); n >>= 1; }\n        return\
    \ modint(u);\n    }\n    modint& operator+=(const modint a){ val += a.val; if(val\
    \ >= M()) val -= M(); return *this; }\n    modint& operator-=(const modint a){\
    \ val += a.val; if(val < 0) val += M(); return *this; }\n    modint& operator*=(const\
    \ modint a){ val = val * a.val % M(); return *this; }\n    modint& operator/=(const\
    \ modint a){ val = val * a.inv().val % M(); return *this;}\n\n    modint& operator=(const\
    \ int& x){\n        val = x%M();\n        while(val < 0) val += M();\n       \
    \ return *this;\n    }\n};\nusing mint = modint;\n"
  code: "struct modint {\n    ll val;\n    static ll &mod(){\n        static ll mod_\
    \ = 0;\n        return mod_;\n    }\n\n    static void set_mod(const ll x) { mod()\
    \ = x; }\n    static ll M() {return mod(); }\n\n    modint(const ll x) : val(x)\
    \ {\n        val = x%M();\n        while(val < 0) val += M();\n    }\n\n    modint\
    \ operator+(const modint a) const { return modint(*this) += a; }\n    modint operator-(const\
    \ modint a) const { return modint(*this) -= a; }\n    modint operator*(const modint\
    \ a) const { return modint(*this) *= a; }\n    modint operator/(const modint a)\
    \ const { return modint(*this) /= a; }\n    modint operator-() const { return\
    \ {M()-val}; }\n    modint inv() const {\n        ll u = 1, v = 0, s = 0, t =\
    \ 1, m = M(), x = val;\n        while (x) {ll q = M()/x; swap(s -= q*u, u); swap(t\
    \ -= q*v, v); swap(m -= q*x, x); }\n        if(s < 0) s += M();\n        return\
    \ modint(s);\n    }\n    modint pow(ll n){\n        ll u = 1, xx = val;\n    \
    \    while (n > 0){ if (n&1) u = u * xx % M(); xx = xx * xx % M(); n >>= 1; }\n\
    \        return modint(u);\n    }\n    modint& operator+=(const modint a){ val\
    \ += a.val; if(val >= M()) val -= M(); return *this; }\n    modint& operator-=(const\
    \ modint a){ val += a.val; if(val < 0) val += M(); return *this; }\n    modint&\
    \ operator*=(const modint a){ val = val * a.val % M(); return *this; }\n    modint&\
    \ operator/=(const modint a){ val = val * a.inv().val % M(); return *this;}\n\n\
    \    modint& operator=(const int& x){\n        val = x%M();\n        while(val\
    \ < 0) val += M();\n        return *this;\n    }\n};\nusing mint = modint;\n"
  dependsOn: []
  isVerificationFile: false
  path: util/modint_arbitrary.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: util/modint_arbitrary.cpp
layout: document
redirect_from:
- /library/util/modint_arbitrary.cpp
- /library/util/modint_arbitrary.cpp.html
title: util/modint_arbitrary.cpp
---
