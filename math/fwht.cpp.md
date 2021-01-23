---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0402.test.cpp
    title: test/aoj0402.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/fwht.cpp\"\ntemplate<class T>\nvoid fwht(vector<T>\
    \ &v){\n    int sz = 1;\n    while(sz < v.size()) sz <<= 1;\n    v.resize(sz);\n\
    \    for (int i = 1; i < sz; i <<= 1) {\n        for (int j = 0; j < sz; j +=\
    \ (i<<1)) {\n            for (int k = 0; k < i; ++k) {\n                T x =\
    \ v[j+k], y = v[j+k+i];\n                v[j+k] = (x+y), v[j+k+i] = (x-y);\n \
    \           }\n        }\n    }\n}\n\ntemplate<class T>\nvoid ifwht(vector<T>\
    \ &v){\n    int sz = 1;\n    while(sz < v.size()) sz <<= 1;\n    v.resize(sz);\n\
    \    for (int i = 1; i < sz; i <<= 1) {\n        for (int j = 0; j < sz; j +=\
    \ (i<<1)) {\n            for (int k = 0; k < i; ++k) {\n                T x =\
    \ v[j+k], y = v[j+k+i];\n                v[j+k] = (x+y)>>1, v[j+k+i] = (x-y)>>1;\n\
    \            }\n        }\n    }\n}\n"
  code: "template<class T>\nvoid fwht(vector<T> &v){\n    int sz = 1;\n    while(sz\
    \ < v.size()) sz <<= 1;\n    v.resize(sz);\n    for (int i = 1; i < sz; i <<=\
    \ 1) {\n        for (int j = 0; j < sz; j += (i<<1)) {\n            for (int k\
    \ = 0; k < i; ++k) {\n                T x = v[j+k], y = v[j+k+i];\n          \
    \      v[j+k] = (x+y), v[j+k+i] = (x-y);\n            }\n        }\n    }\n}\n\
    \ntemplate<class T>\nvoid ifwht(vector<T> &v){\n    int sz = 1;\n    while(sz\
    \ < v.size()) sz <<= 1;\n    v.resize(sz);\n    for (int i = 1; i < sz; i <<=\
    \ 1) {\n        for (int j = 0; j < sz; j += (i<<1)) {\n            for (int k\
    \ = 0; k < i; ++k) {\n                T x = v[j+k], y = v[j+k+i];\n          \
    \      v[j+k] = (x+y)>>1, v[j+k+i] = (x-y)>>1;\n            }\n        }\n   \
    \ }\n}"
  dependsOn: []
  isVerificationFile: false
  path: math/fwht.cpp
  requiredBy: []
  timestamp: '2020-10-15 21:07:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0402.test.cpp
documentation_of: math/fwht.cpp
layout: document
redirect_from:
- /library/math/fwht.cpp
- /library/math/fwht.cpp.html
title: math/fwht.cpp
---
