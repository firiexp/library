---
category: "\u6570\u5B66"
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: util/modint.cpp
    title: "modint(\u56FA\u5B9AMOD)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aoj0452.test.cpp
    title: test/aoj0452.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "\u968E\u4E57\u30FB\u4E8C\u9805\u4FC2\u6570(Factorial)"
    links: []
  bundledCode: "#line 1 \"math/factorial.cpp\"\n\n#line 1 \"util/modint.cpp\"\n\n\n\
    \ntemplate <uint Mod>\nstruct modint {\n    uint val;\npublic:\n    static modint\
    \ raw(int v) { modint x; x.val = v; return x; }\n    static constexpr uint get_mod()\
    \ { return Mod; }\n    static constexpr uint M() { return Mod; }\n    modint()\
    \ : val(0) {}\n    template <class T>\n    modint(T v) { ll x = (ll)(v % (ll)(Mod));\
    \ if (x < 0) x += Mod; val = uint(x); }\n    modint(bool v) { val = ((unsigned\
    \ int)(v) % Mod); }\n    uint &value() noexcept { return val; }\n    const uint\
    \ &value() const noexcept { return val; }\n    modint& operator++() { val++; if\
    \ (val == Mod) val = 0; return *this; }\n    modint& operator--() { if (val ==\
    \ 0) val = Mod; val--; return *this; }\n    modint operator++(int) { modint result\
    \ = *this; ++*this; return result; }\n    modint operator--(int) { modint result\
    \ = *this; --*this; return result; }\n    modint& operator+=(const modint& b)\
    \ { val += b.val; if (val >= Mod) val -= Mod; return *this; }\n    modint& operator-=(const\
    \ modint& b) { val -= b.val; if (val >= Mod) val += Mod; return *this; }\n   \
    \ modint& operator*=(const modint& b) { ull z = val; z *= b.val; val = (uint)(z\
    \ % Mod); return *this; }\n    modint& operator/=(const modint& b) { return *this\
    \ = *this * b.inv(); }\n    modint operator+() const { return *this; }\n    modint\
    \ operator-() const { return modint() - *this; }\n    modint pow(long long n)\
    \ const { modint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>=\
    \ 1; } return r; }\n    modint inv() const { return pow(Mod - 2); }\n    friend\
    \ modint operator+(const modint& a, const modint& b) { return modint(a) += b;\
    \ }\n    friend modint operator-(const modint& a, const modint& b) { return modint(a)\
    \ -= b; }\n    friend modint operator*(const modint& a, const modint& b) { return\
    \ modint(a) *= b; }\n    friend modint operator/(const modint& a, const modint&\
    \ b) { return modint(a) /= b; }\n    friend bool operator==(const modint& a, const\
    \ modint& b) { return a.val == b.val; }\n    friend bool operator!=(const modint&\
    \ a, const modint& b) { return a.val != b.val; }\n};\nusing mint = modint<MOD>;\n\
    #define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n\n/**\n * @brief modint(\u56FA\u5B9A\
    MOD)\n */\n\n\n#line 3 \"math/factorial.cpp\"\n#endif\n\ntemplate <class Mint\
    \ = mint>\nclass Factorial {\n    inline static vector<Mint> facts, factinv, invs;\n\
    \n    static void init() {\n        if (!facts.empty()) return;\n        facts.push_back(Mint(1));\n\
    \        factinv.push_back(Mint(1));\n        invs.push_back(Mint(0));\n     \
    \   invs.push_back(Mint(1));\n    }\n\n    static void expand(int n) {\n     \
    \   init();\n        if (n < (int)facts.size()) return;\n        int old = facts.size();\n\
    \        int mod = Mint::get_mod();\n        facts.resize(n + 1);\n        factinv.resize(n\
    \ + 1);\n        invs.resize(n + 1);\n        for (int i = max(2, old); i <= n;\
    \ ++i) {\n            invs[i] = -Mint(mod / i) * invs[mod % i];\n        }\n \
    \       for (int i = old; i <= n; ++i) {\n            facts[i] = facts[i - 1]\
    \ * Mint(i);\n            factinv[i] = factinv[i - 1] * invs[i];\n        }\n\
    \    }\npublic:\n    explicit Factorial(int n = 0) {\n        expand(n);\n   \
    \ }\n    void ensure(int n) const {\n        if (n >= 0) expand(n);\n    }\n \
    \   int max_n() const {\n        init();\n        return (int)facts.size() - 1;\n\
    \    }\n    Mint fact(int k) const {\n        if (k < 0) return inv_fact(-k);\n\
    \        expand(k);\n        return facts[k];\n    }\n    Mint inv_fact(int k)\
    \ const {\n        if (k < 0) return 0;\n        expand(k);\n        return factinv[k];\n\
    \    }\n    Mint inv(int k) const {\n        if (k < 0) return 0;\n        expand(k);\n\
    \        return invs[k];\n    }\n    Mint operator[](int k) const {\n        return\
    \ k >= 0 ? fact(k) : inv_fact(-k);\n    }\n    Mint C(int n, int k) const {\n\
    \        if (n < 0 || k < 0 || n < k) return 0;\n        expand(n);\n        return\
    \ facts[n] * factinv[k] * factinv[n - k];\n    }\n    Mint P(int n, int k) const\
    \ {\n        if (n < 0 || k < 0 || n < k) return 0;\n        expand(n);\n    \
    \    return facts[n] * factinv[n - k];\n    }\n    Mint H(int n, int k) const\
    \ {\n        if (n < 0 || k < 0) return 0;\n        if (k == 0) return 1;\n  \
    \      if (n == 0) return 0;\n        return C(n + k - 1, k);\n    }\n};\n\n/**\n\
    \ * @brief \u968E\u4E57\u30FB\u4E8C\u9805\u4FC2\u6570(Factorial)\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED\n#include \"../util/modint.cpp\"\
    \n#endif\n\ntemplate <class Mint = mint>\nclass Factorial {\n    inline static\
    \ vector<Mint> facts, factinv, invs;\n\n    static void init() {\n        if (!facts.empty())\
    \ return;\n        facts.push_back(Mint(1));\n        factinv.push_back(Mint(1));\n\
    \        invs.push_back(Mint(0));\n        invs.push_back(Mint(1));\n    }\n\n\
    \    static void expand(int n) {\n        init();\n        if (n < (int)facts.size())\
    \ return;\n        int old = facts.size();\n        int mod = Mint::get_mod();\n\
    \        facts.resize(n + 1);\n        factinv.resize(n + 1);\n        invs.resize(n\
    \ + 1);\n        for (int i = max(2, old); i <= n; ++i) {\n            invs[i]\
    \ = -Mint(mod / i) * invs[mod % i];\n        }\n        for (int i = old; i <=\
    \ n; ++i) {\n            facts[i] = facts[i - 1] * Mint(i);\n            factinv[i]\
    \ = factinv[i - 1] * invs[i];\n        }\n    }\npublic:\n    explicit Factorial(int\
    \ n = 0) {\n        expand(n);\n    }\n    void ensure(int n) const {\n      \
    \  if (n >= 0) expand(n);\n    }\n    int max_n() const {\n        init();\n \
    \       return (int)facts.size() - 1;\n    }\n    Mint fact(int k) const {\n \
    \       if (k < 0) return inv_fact(-k);\n        expand(k);\n        return facts[k];\n\
    \    }\n    Mint inv_fact(int k) const {\n        if (k < 0) return 0;\n     \
    \   expand(k);\n        return factinv[k];\n    }\n    Mint inv(int k) const {\n\
    \        if (k < 0) return 0;\n        expand(k);\n        return invs[k];\n \
    \   }\n    Mint operator[](int k) const {\n        return k >= 0 ? fact(k) : inv_fact(-k);\n\
    \    }\n    Mint C(int n, int k) const {\n        if (n < 0 || k < 0 || n < k)\
    \ return 0;\n        expand(n);\n        return facts[n] * factinv[k] * factinv[n\
    \ - k];\n    }\n    Mint P(int n, int k) const {\n        if (n < 0 || k < 0 ||\
    \ n < k) return 0;\n        expand(n);\n        return facts[n] * factinv[n -\
    \ k];\n    }\n    Mint H(int n, int k) const {\n        if (n < 0 || k < 0) return\
    \ 0;\n        if (k == 0) return 1;\n        if (n == 0) return 0;\n        return\
    \ C(n + k - 1, k);\n    }\n};\n\n/**\n * @brief \u968E\u4E57\u30FB\u4E8C\u9805\
    \u4FC2\u6570(Factorial)\n */\n"
  dependsOn:
  - util/modint.cpp
  isVerificationFile: false
  path: math/factorial.cpp
  requiredBy: []
  timestamp: '2026-03-14 20:56:35+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/aoj0452.test.cpp
date: 2026-03-11
documentation_of: math/factorial.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u968E\u4E57\u30FB\u4E8C\u9805\u4FC2\u6570(Factorial)"
---

## 説明
階乗 `n!`、逆元 `n^{-1}`、階乗逆元 `(n!)^{-1}` を必要になったところまで遅延計算する。
`C(n, k)`、`P(n, k)`、`H(n, k)` を $O(1)$ で返す。


## できること
- `Factorial<Mint = mint> f(int n = 0)`
  `0` から `n` まで前計算して作る
- `void ensure(int n)`
  `n` まで前計算を広げる
- `int max_n()`
  現在前計算済みの最大添字を返す
- `mint fact(int k)`
  `k >= 0` なら `k!`、`k < 0` なら `(-k)!^{-1}` を返す
- `mint inv(int k)`
  `k^{-1}` を返す。`k < 0` なら `0`
- `mint inv_fact(int k)`
  `(k!)^{-1}` を返す。`k < 0` なら `0`
- `mint operator[](int k)`
  `k >= 0` なら `k!`、`k < 0` なら `(-k)!^{-1}` を返す
- `mint C(int n, int k)`
  二項係数を返す。
- `mint P(int n, int k)`
  順列数を返す。
- `mint H(int n, int k)`
  重複組合せを返す。
