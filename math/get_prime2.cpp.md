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
  bundledCode: "#line 1 \"math/get_prime2.cpp\"\nusing uint = uint32_t;\n\ntemplate<typename\
    \ T>\nstruct ExactDiv {\n    T t, i, val;\n    ExactDiv() {}\n    ExactDiv(T n)\
    \ : t(T(-1) / n), i(mul_inv(n)) , val(n) {};\n    T mul_inv(T n) {\n        T\
    \ x = n;\n        for (int i = 0; i < 5; ++i) x *= 2 - n * x;\n        return\
    \ x;\n    }\n    bool divide(T n) const {\n        if(val == 2) return !(n & 1);\n\
    \        return n * this->i <= this->t;\n    }\n};\n\nvector<ExactDiv<uint>> get_prime(int\
    \ n){\n    if(n <= 1) return vector<ExactDiv<uint>>();\n    vector<bool> is_prime(n+1,\
    \ true);\n    vector<ExactDiv<uint>> prime;\n    is_prime[0] = is_prime[1] = false;\n\
    \    for (int i = 2; i <= n; ++i) {\n        if(is_prime[i]) prime.emplace_back(i);\n\
    \        for (auto &&j : prime){\n            if(i*j.val > n) break;\n       \
    \     is_prime[i*j.val] = false;\n            if(j.divide(i)) break;\n       \
    \ }\n    }\n    return prime;\n}\nconst auto primes = get_prime(32000);\n"
  code: "using uint = uint32_t;\n\ntemplate<typename T>\nstruct ExactDiv {\n    T\
    \ t, i, val;\n    ExactDiv() {}\n    ExactDiv(T n) : t(T(-1) / n), i(mul_inv(n))\
    \ , val(n) {};\n    T mul_inv(T n) {\n        T x = n;\n        for (int i = 0;\
    \ i < 5; ++i) x *= 2 - n * x;\n        return x;\n    }\n    bool divide(T n)\
    \ const {\n        if(val == 2) return !(n & 1);\n        return n * this->i <=\
    \ this->t;\n    }\n};\n\nvector<ExactDiv<uint>> get_prime(int n){\n    if(n <=\
    \ 1) return vector<ExactDiv<uint>>();\n    vector<bool> is_prime(n+1, true);\n\
    \    vector<ExactDiv<uint>> prime;\n    is_prime[0] = is_prime[1] = false;\n \
    \   for (int i = 2; i <= n; ++i) {\n        if(is_prime[i]) prime.emplace_back(i);\n\
    \        for (auto &&j : prime){\n            if(i*j.val > n) break;\n       \
    \     is_prime[i*j.val] = false;\n            if(j.divide(i)) break;\n       \
    \ }\n    }\n    return prime;\n}\nconst auto primes = get_prime(32000);\n"
  dependsOn: []
  isVerificationFile: false
  path: math/get_prime2.cpp
  requiredBy: []
  timestamp: '2021-06-21 15:24:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/get_prime2.cpp
layout: document
redirect_from:
- /library/math/get_prime2.cpp
- /library/math/get_prime2.cpp.html
title: math/get_prime2.cpp
---
