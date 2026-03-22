---
category: "\u6570\u5B66"
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: math/modinv.cpp
    title: math/modinv.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_binomial_coefficient.test.cpp
    title: test/yosupo_binomial_coefficient.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "\u4E8C\u9805\u4FC2\u6570(mod p^q)"
    links: []
  bundledCode: "#line 1 \"math/modinv.cpp\"\ntemplate<typename T>  \nT mod_inv(T x,\
    \ T M){  \n   T u = 1, t = 1, v = 0, s = 0, m = M;  \n   while (x) { T q = m/x;\
    \ swap(s -= q*u, u); swap(t -= q*v, v); swap(m -= q*x, x); }  \n   if(s < 0) s\
    \ += M;  \n   return s;  \n}\n#line 2 \"math/binom_mod_prime_power.cpp\"\n\nstruct\
    \ BinomModPrimePower {\n    ll p, mod;\n    int q;\n    ll block_prod;\n    vector<ll>\
    \ ppow;\n    vector<int> prod;\n\n    explicit BinomModPrimePower(ll prime, int\
    \ exponent) : p(prime), mod(1), q(exponent), ppow(exponent + 1, 1) {\n       \
    \ for (int i = 0; i < q; ++i) {\n            mod *= p;\n            ppow[i + 1]\
    \ = mod;\n        }\n        block_prod = (p == 2 && q >= 3 ? 1 : mod - 1);\n\
    \        prod.assign(mod + 1, 1);\n        for (int i = 1; i <= mod; ++i) {\n\
    \            prod[i] = prod[i - 1];\n            if (i % p != 0) prod[i] = (ull)prod[i]\
    \ * i % mod;\n        }\n    }\n\n    pair<ll, ll> factorial(ll n) const {\n \
    \       ll x = 1, e = 0;\n        while (n) {\n            if (block_prod != 1\
    \ && (n / mod) & 1) x = mod - x;\n            x = (ull)x * prod[n % mod] % mod;\n\
    \            n /= p;\n            e += n;\n        }\n        return {x, e};\n\
    \    }\n\n    ll C(ll n, ll k) const {\n        if (k < 0 || k > n) return 0;\n\
    \        auto [a, ea] = factorial(n);\n        auto [b, eb] = factorial(k);\n\
    \        auto [c, ec] = factorial(n - k);\n        ll e = ea - eb - ec;\n    \
    \    if (e >= q) return 0;\n        ll x = (ull)b * c % mod;\n        return (ull)a\
    \ * mod_inv(x, mod) % mod * ppow[e] % mod;\n    }\n\n    ll modulus() const {\n\
    \        return mod;\n    }\n};\n\n/**\n * @brief \u4E8C\u9805\u4FC2\u6570(mod\
    \ p^q)\n */\n"
  code: "#include \"modinv.cpp\"\n\nstruct BinomModPrimePower {\n    ll p, mod;\n\
    \    int q;\n    ll block_prod;\n    vector<ll> ppow;\n    vector<int> prod;\n\
    \n    explicit BinomModPrimePower(ll prime, int exponent) : p(prime), mod(1),\
    \ q(exponent), ppow(exponent + 1, 1) {\n        for (int i = 0; i < q; ++i) {\n\
    \            mod *= p;\n            ppow[i + 1] = mod;\n        }\n        block_prod\
    \ = (p == 2 && q >= 3 ? 1 : mod - 1);\n        prod.assign(mod + 1, 1);\n    \
    \    for (int i = 1; i <= mod; ++i) {\n            prod[i] = prod[i - 1];\n  \
    \          if (i % p != 0) prod[i] = (ull)prod[i] * i % mod;\n        }\n    }\n\
    \n    pair<ll, ll> factorial(ll n) const {\n        ll x = 1, e = 0;\n       \
    \ while (n) {\n            if (block_prod != 1 && (n / mod) & 1) x = mod - x;\n\
    \            x = (ull)x * prod[n % mod] % mod;\n            n /= p;\n        \
    \    e += n;\n        }\n        return {x, e};\n    }\n\n    ll C(ll n, ll k)\
    \ const {\n        if (k < 0 || k > n) return 0;\n        auto [a, ea] = factorial(n);\n\
    \        auto [b, eb] = factorial(k);\n        auto [c, ec] = factorial(n - k);\n\
    \        ll e = ea - eb - ec;\n        if (e >= q) return 0;\n        ll x = (ull)b\
    \ * c % mod;\n        return (ull)a * mod_inv(x, mod) % mod * ppow[e] % mod;\n\
    \    }\n\n    ll modulus() const {\n        return mod;\n    }\n};\n\n/**\n *\
    \ @brief \u4E8C\u9805\u4FC2\u6570(mod p^q)\n */\n"
  dependsOn:
  - math/modinv.cpp
  isVerificationFile: false
  path: math/binom_mod_prime_power.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_binomial_coefficient.test.cpp
date: 2026-03-08
documentation_of: math/binom_mod_prime_power.cpp
layout: document
tags: "\u6570\u5B66"
title: binom_mod_prime_power
---

## 説明
素数冪 `p^q` を法とする二項係数 `C(n, k)` を扱う。
前計算 $O(p^q)$、各クエリ $O(log_p n)$。

## できること
- `BinomModPrimePower(ll p, int q)`
  法 `p^q` 用のテーブルを作る
- `ll C(ll n, ll k)`
  `C(n, k) mod p^q` を返す。`k < 0` または `k > n` なら `0`
- `ll modulus()`
  法 `p^q` を返す

## 使い方
`BinomModPrimePower binom(p, q);` を作り、`binom.C(n, k)` を呼ぶ。
一般の合成数 mod `m` で使いたいときは、`m` を素因数分解して各 `p^q` ごとに値を出し、CRT で併合する。

## 実装上の補足
`n!` の `p` を除いた部分と `p` の指数を再帰的に分けて計算する。
メモリは $O(p^q)$ 使うので、法が大きすぎる場合には向かない。
