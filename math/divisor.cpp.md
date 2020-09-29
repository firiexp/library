---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/divisor.cpp\"\ntemplate<class T>\nvector<T> divisor(T\
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
  path: math/divisor.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/divisor.cpp
layout: document
redirect_from:
- /library/math/divisor.cpp
- /library/math/divisor.cpp.html
title: math/divisor.cpp
---
