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
  bundledCode: "#line 1 \"math/prime/divisor.cpp\"\ntemplate<class T>\nvector<T> divisor(T\
    \ n){\n    vector<T> ret;\n    for(T i = 1; i * i <= n; i++) {\n        if(n %\
    \ i == 0) {\n            ret.push_back(i);\n            if(i * i != n) ret.push_back(n\
    \ / i);\n        }\n    }\n    sort(begin(ret), end(ret));\n    return(ret);\n\
    }\n"
  code: "template<class T>\nvector<T> divisor(T n){\n    vector<T> ret;\n    for(T\
    \ i = 1; i * i <= n; i++) {\n        if(n % i == 0) {\n            ret.push_back(i);\n\
    \            if(i * i != n) ret.push_back(n / i);\n        }\n    }\n    sort(begin(ret),\
    \ end(ret));\n    return(ret);\n}"
  dependsOn: []
  isVerificationFile: false
  path: math/prime/divisor.cpp
  requiredBy: []
  timestamp: '2026-03-22 19:39:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/prime/divisor.cpp
layout: document
redirect_from:
- /library/math/prime/divisor.cpp
- /library/math/prime/divisor.cpp.html
title: math/prime/divisor.cpp
---
