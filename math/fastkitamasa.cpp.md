---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/fastkitamasa.cpp\"\nclass Fast_Kitamasa {\n    poly\
    \ c, b, ic;\n    int k;\n    int mod;\npublic:\n    explicit Fast_Kitamasa(vector<int>\
    \ &c, int mod) : c(c), mod(mod){\n        k = static_cast<int>(c.size() - 1);\n\
    \        calc_ic();\n    }\n    void multiply_mod(poly &a, poly x){\n        auto\
    \ beta = a*x;\n        auto q = beta*ic;\n        q.cut(k-1);\n        auto result\
    \ = c*q;\n        for (int i = k-1; i <= 2*k-2; ++i) {\n            (result[i]\
    \ += beta[i]) %= mod;\n        }\n        a = poly(vector<int>(result.v.begin()+k-1,\
    \ result.v.begin()+2*k-1));\n    }\n\n    void calc_ic() {\n        ic = poly(vector<int>(1,\
    \ 1));\n        int t = 1;\n        while(t <= k){\n            t = min(2*t, k+1);\n\
    \            auto cc = poly(vector<int>(c.v.begin(), c.v.begin()+t));\n      \
    \      auto current = cc*ic;\n            (current[0] += 2) %= mod;\n        \
    \    ic = ic*current;\n        }\n        ic.cut(t);\n    }\n\n    poly kitamasa(int\
    \ n){\n        b = poly(vector<int>(k, 0));\n        auto x = poly(vector<int>(k,\
    \ 0));\n        b[k-1] = 1;\n        x[k-2] = 1;\n        while (n != 0){\n  \
    \          if ((n & 1) == 1){\n                multiply_mod(b, x);\n         \
    \   }\n            n /= 2;\n            multiply_mod(x, x);\n        }\n     \
    \   return b;\n    }\n};\n"
  code: "class Fast_Kitamasa {\n    poly c, b, ic;\n    int k;\n    int mod;\npublic:\n\
    \    explicit Fast_Kitamasa(vector<int> &c, int mod) : c(c), mod(mod){\n     \
    \   k = static_cast<int>(c.size() - 1);\n        calc_ic();\n    }\n    void multiply_mod(poly\
    \ &a, poly x){\n        auto beta = a*x;\n        auto q = beta*ic;\n        q.cut(k-1);\n\
    \        auto result = c*q;\n        for (int i = k-1; i <= 2*k-2; ++i) {\n  \
    \          (result[i] += beta[i]) %= mod;\n        }\n        a = poly(vector<int>(result.v.begin()+k-1,\
    \ result.v.begin()+2*k-1));\n    }\n\n    void calc_ic() {\n        ic = poly(vector<int>(1,\
    \ 1));\n        int t = 1;\n        while(t <= k){\n            t = min(2*t, k+1);\n\
    \            auto cc = poly(vector<int>(c.v.begin(), c.v.begin()+t));\n      \
    \      auto current = cc*ic;\n            (current[0] += 2) %= mod;\n        \
    \    ic = ic*current;\n        }\n        ic.cut(t);\n    }\n\n    poly kitamasa(int\
    \ n){\n        b = poly(vector<int>(k, 0));\n        auto x = poly(vector<int>(k,\
    \ 0));\n        b[k-1] = 1;\n        x[k-2] = 1;\n        while (n != 0){\n  \
    \          if ((n & 1) == 1){\n                multiply_mod(b, x);\n         \
    \   }\n            n /= 2;\n            multiply_mod(x, x);\n        }\n     \
    \   return b;\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: math/fastkitamasa.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/fastkitamasa.cpp
layout: document
redirect_from:
- /library/math/fastkitamasa.cpp
- /library/math/fastkitamasa.cpp.html
title: math/fastkitamasa.cpp
---
