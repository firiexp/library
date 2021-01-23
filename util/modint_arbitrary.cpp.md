---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0422.test.cpp
    title: test/aoj0422.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"util/modint_arbitrary.cpp\"\nclass modint {\n    static\
    \ u32 &mod() { static u32 mod_ = 0; return mod_; }\npublic:\n    u32 val;\n  \
    \  modint(const u32 x = 0) : val(x % M()) {}\n    u32 &value() noexcept { return\
    \ val; }\n    const u32 &value() const noexcept { return val; }\n    modint operator+(const\
    \ modint b) const { return modint(*this) += b; }\n    modint operator-(const modint\
    \ b) const { return modint(*this) -= b; }\n    modint operator*(const modint b)\
    \ const { return modint(*this) *= b; }\n    modint operator/(const modint b) const\
    \ { return modint(*this) /= b; }\n    modint &operator+=(const modint b) { val\
    \ += b.val; if (val >= M()) val -= M(); return *this; }\n    modint &operator-=(const\
    \ modint b) { if (val < b.val) val += M(); val -= b.val; return *this; }\n   \
    \ modint &operator*=(const modint b) { val = (u64)val * b.val % M(); return *this;\
    \ }\n    modint pow(ll n) const { modint x = *this, r = 1; while(n){ if(n&1) r\
    \ *= x; x *= x; n >>= 1; } return r; }\n    modint &operator/=(modint b) { return\
    \ *this *= b.pow(M()-2); }\n    static void set_mod(const u32 x) { mod() = x;\
    \ }\n    static int M() { return mod(); }\n};\nusing mint = modint;\n"
  code: "class modint {\n    static u32 &mod() { static u32 mod_ = 0; return mod_;\
    \ }\npublic:\n    u32 val;\n    modint(const u32 x = 0) : val(x % M()) {}\n  \
    \  u32 &value() noexcept { return val; }\n    const u32 &value() const noexcept\
    \ { return val; }\n    modint operator+(const modint b) const { return modint(*this)\
    \ += b; }\n    modint operator-(const modint b) const { return modint(*this) -=\
    \ b; }\n    modint operator*(const modint b) const { return modint(*this) *= b;\
    \ }\n    modint operator/(const modint b) const { return modint(*this) /= b; }\n\
    \    modint &operator+=(const modint b) { val += b.val; if (val >= M()) val -=\
    \ M(); return *this; }\n    modint &operator-=(const modint b) { if (val < b.val)\
    \ val += M(); val -= b.val; return *this; }\n    modint &operator*=(const modint\
    \ b) { val = (u64)val * b.val % M(); return *this; }\n    modint pow(ll n) const\
    \ { modint x = *this, r = 1; while(n){ if(n&1) r *= x; x *= x; n >>= 1; } return\
    \ r; }\n    modint &operator/=(modint b) { return *this *= b.pow(M()-2); }\n \
    \   static void set_mod(const u32 x) { mod() = x; }\n    static int M() { return\
    \ mod(); }\n};\nusing mint = modint;"
  dependsOn: []
  isVerificationFile: false
  path: util/modint_arbitrary.cpp
  requiredBy: []
  timestamp: '2020-10-17 18:59:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0422.test.cpp
documentation_of: util/modint_arbitrary.cpp
layout: document
redirect_from:
- /library/util/modint_arbitrary.cpp
- /library/util/modint_arbitrary.cpp.html
title: util/modint_arbitrary.cpp
---
