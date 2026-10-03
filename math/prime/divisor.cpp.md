---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_ntl_1_d_eulerphi.test.cpp
    title: test/aoj_ntl_1_d_eulerphi.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/prime/divisor.cpp\"\ntemplate<class T>\nvector<T> divisor(T\
    \ n){\n    vector<T> ret;\n    for(T i = 1; i <= n / i; i++) {\n        if(n %\
    \ i == 0) {\n            ret.push_back(i);\n            if(i * i != n) ret.push_back(n\
    \ / i);\n        }\n    }\n    sort(begin(ret), end(ret));\n    return(ret);\n\
    }\n"
  code: "template<class T>\nvector<T> divisor(T n){\n    vector<T> ret;\n    for(T\
    \ i = 1; i <= n / i; i++) {\n        if(n % i == 0) {\n            ret.push_back(i);\n\
    \            if(i * i != n) ret.push_back(n / i);\n        }\n    }\n    sort(begin(ret),\
    \ end(ret));\n    return(ret);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: math/prime/divisor.cpp
  requiredBy: []
  timestamp: '2026-10-03 11:59:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj_ntl_1_d_eulerphi.test.cpp
documentation_of: math/prime/divisor.cpp
layout: document
redirect_from:
- /library/math/prime/divisor.cpp
- /library/math/prime/divisor.cpp.html
title: math/prime/divisor.cpp
---
