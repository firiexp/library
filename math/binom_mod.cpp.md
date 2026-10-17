---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/binom_mod_prime_power.cpp
    title: "\u4E8C\u9805\u4FC2\u6570(mod p^q)"
  - icon: ':heavy_check_mark:'
    path: math/modinv.cpp
    title: math/modinv.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_binom_mod.test.cpp
    title: test/yosupo_aplusb_binom_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_binomial_coefficient.test.cpp
    title: test/yosupo_binomial_coefficient.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E8C\u9805\u4FC2\u6570\uFF08\u5408\u6210\u6570mod\uFF09"
    links: []
  bundledCode: "#line 1 \"math/binom_mod.cpp\"\n\n\n\n#line 1 \"math/modinv.cpp\"\n\
    template<typename T>  \nT mod_inv(T x, T M){  \n   T u = 1, t = 1, v = 0, s =\
    \ 0, m = M;  \n   while (x) { T q = m/x; swap(s -= q*u, u); swap(t -= q*v, v);\
    \ swap(m -= q*x, x); }  \n   if(s < 0) s += M;  \n   return s;  \n}\n#line 2 \"\
    math/binom_mod_prime_power.cpp\"\n\nstruct BinomModPrimePower {\n    ll p, mod;\n\
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
    \ @brief \u4E8C\u9805\u4FC2\u6570(mod p^q)\n */\n#line 5 \"math/binom_mod.cpp\"\
    \n\nclass BinomMod {\n    ll mod;\n    vector<BinomModPrimePower> binoms;\n  \
    \  vector<ll> coefficients;\n\npublic:\n    explicit BinomMod(ll modulus) : mod(modulus)\
    \ {\n        assert(1 <= mod && mod <= 1000000);\n        ll remaining = mod;\n\
    \        for (ll p = 2; p * p <= remaining; ++p) {\n            if (remaining\
    \ % p != 0) continue;\n            int exponent = 0;\n            do {\n     \
    \           remaining /= p;\n                ++exponent;\n            } while\
    \ (remaining % p == 0);\n            binoms.emplace_back(p, exponent);\n     \
    \   }\n        if (remaining > 1) binoms.emplace_back(remaining, 1);\n       \
    \ for (const auto &binom : binoms) {\n            ll power = binom.modulus(),\
    \ cofactor = mod / power;\n            coefficients.push_back(cofactor * mod_inv(cofactor\
    \ % power, power) % mod);\n        }\n    }\n\n    ll C(ll n, ll k) const {\n\
    \        if (mod == 1 || k < 0 || k > n) return 0;\n        ll result = 0;\n \
    \       for (int i = 0; i < (int)binoms.size(); ++i)\n            result = (result\
    \ + binoms[i].C(n, k) * coefficients[i]) % mod;\n        return result;\n    }\n\
    \n    ll modulus() const { return mod; }\n};\n\n\n\n/**\n * @brief \u4E8C\u9805\
    \u4FC2\u6570\uFF08\u5408\u6210\u6570mod\uFF09\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_MATH_BINOM_MOD_CPP\n#define FIRIEXP_LIBRARY_MATH_BINOM_MOD_CPP\n\
    \n#include \"binom_mod_prime_power.cpp\"\n\nclass BinomMod {\n    ll mod;\n  \
    \  vector<BinomModPrimePower> binoms;\n    vector<ll> coefficients;\n\npublic:\n\
    \    explicit BinomMod(ll modulus) : mod(modulus) {\n        assert(1 <= mod &&\
    \ mod <= 1000000);\n        ll remaining = mod;\n        for (ll p = 2; p * p\
    \ <= remaining; ++p) {\n            if (remaining % p != 0) continue;\n      \
    \      int exponent = 0;\n            do {\n                remaining /= p;\n\
    \                ++exponent;\n            } while (remaining % p == 0);\n    \
    \        binoms.emplace_back(p, exponent);\n        }\n        if (remaining >\
    \ 1) binoms.emplace_back(remaining, 1);\n        for (const auto &binom : binoms)\
    \ {\n            ll power = binom.modulus(), cofactor = mod / power;\n       \
    \     coefficients.push_back(cofactor * mod_inv(cofactor % power, power) % mod);\n\
    \        }\n    }\n\n    ll C(ll n, ll k) const {\n        if (mod == 1 || k <\
    \ 0 || k > n) return 0;\n        ll result = 0;\n        for (int i = 0; i < (int)binoms.size();\
    \ ++i)\n            result = (result + binoms[i].C(n, k) * coefficients[i]) %\
    \ mod;\n        return result;\n    }\n\n    ll modulus() const { return mod;\
    \ }\n};\n\n#endif\n\n/**\n * @brief \u4E8C\u9805\u4FC2\u6570\uFF08\u5408\u6210\
    \u6570mod\uFF09\n */\n"
  dependsOn:
  - math/binom_mod_prime_power.cpp
  - math/modinv.cpp
  isVerificationFile: false
  path: math/binom_mod.cpp
  requiredBy: []
  timestamp: '2026-10-14 20:39:08+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_binomial_coefficient.test.cpp
  - test/yosupo_aplusb_binom_mod.test.cpp
documentation_of: math/binom_mod.cpp
layout: document
title: "\u4E8C\u9805\u4FC2\u6570\uFF08\u5408\u6210\u6570mod\uFF09"
---

## 説明
二項係数 $\binom{n}{k}\bmod m$ を求める。法 $m$ を素因数分解し、素数冪ごとのテーブルと CRT の併合係数を前計算する。
$1\le m\le10^6$、$0\le n\le10^{18}$ を扱う。

## できること
- `BinomMod(m)`：法 $m$ 用のテーブルを構築する
- `ll C(ll n, ll k) const`：$\binom{n}{k}\bmod m$ を返す。$m=1$、$k<0$、$k>n$ なら $0$
- `ll modulus() const`：法を返す

## 使い方
```cpp
BinomMod binom(12);
auto value = binom.C(10, 3);
```

この例の結果は $0$。素数冪だけを扱う場合は `BinomModPrimePower` も引き続き使える。

## 実装上の補足
$m=\prod_i p_i^{q_i}$ として、構築時間は $O(\sqrt m+\sum_i p_i^{q_i})$、保持領域は $O(1+\sum_i p_i^{q_i})$。
1クエリは $O(1+\sum_i(\log_{p_i}(n)+\log(p_i^{q_i})))$。
CRT 用の配列確保や併合係数の逆数計算はクエリ中に行わない。素数冪ごとの階乗比の逆数計算は必要。
