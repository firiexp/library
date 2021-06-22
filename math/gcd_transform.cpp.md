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
  bundledCode: "#line 1 \"math/gcd_transform.cpp\"\ntemplate<class T>\nvoid gcd_transform(vector<T>\
    \ &v){\n    vector<bool> sieve(v.size());\n    for (int i = 2; i <= r; ++i) {\n\
    \        if(!sieve[i]){\n            for (int j = r/i; j != 0; --j) {\n      \
    \          if(j != 1) sieve[j*i] = true;\n                dp[j] += dp[j*i];\n\
    \            }\n        }\n    }\n}\n\ntemplate<class T>\nvoid gcd_itransform(vector<T>\
    \ &v){\n    vector<bool> sieve(v.size());\n    for (int i = 2; i <= r; ++i) {\n\
    \        if(!sieve[i]){\n            for (int j = 1; j*i <= r; ++j) {\n      \
    \          if(j != 1) sieve[j*i] = true;\n                dp[j] -= dp[j*i];\n\
    \            }\n        }\n    }\n}\n"
  code: "template<class T>\nvoid gcd_transform(vector<T> &v){\n    vector<bool> sieve(v.size());\n\
    \    for (int i = 2; i <= r; ++i) {\n        if(!sieve[i]){\n            for (int\
    \ j = r/i; j != 0; --j) {\n                if(j != 1) sieve[j*i] = true;\n   \
    \             dp[j] += dp[j*i];\n            }\n        }\n    }\n}\n\ntemplate<class\
    \ T>\nvoid gcd_itransform(vector<T> &v){\n    vector<bool> sieve(v.size());\n\
    \    for (int i = 2; i <= r; ++i) {\n        if(!sieve[i]){\n            for (int\
    \ j = 1; j*i <= r; ++j) {\n                if(j != 1) sieve[j*i] = true;\n   \
    \             dp[j] -= dp[j*i];\n            }\n        }\n    }\n}"
  dependsOn: []
  isVerificationFile: false
  path: math/gcd_transform.cpp
  requiredBy: []
  timestamp: '2021-06-22 23:26:58+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/gcd_transform.cpp
layout: document
redirect_from:
- /library/math/gcd_transform.cpp
- /library/math/gcd_transform.cpp.html
title: math/gcd_transform.cpp
---
