---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash.cpp
    title: string/rolling_hash.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0355.test.cpp
    title: test/aoj0355.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"util/xorshift.cpp\"\n#include <chrono>\nclass xor_shift\
    \ {\n    uint32_t x, y, z, w;\npublic:\n    xor_shift() : x(static_cast<uint32_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL\
    \ << 32)-1))),\n    y(1068246329), z(321908594), w(1234567890) {};\n\n    uint32_t\
    \ urand(){\n        uint32_t t;\n        t = x ^ (x << 11);\n        x = y; y\
    \ = z; z = w;\n        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n        return w;\n\
    \    };\n\n    int rand(int n){\n        if(n < 0) return -rand(-n);\n       \
    \ uint32_t t = numeric_limits<uint32_t>::max()/(n+1)*(n+1);\n        uint32_t\
    \ e = urand();\n        while(e >= t) e = urand();\n        return static_cast<int>(e%(n+1));\n\
    \    }\n\n    int rand(int a, int b){\n        if(a > b) swap(a, b);\n       \
    \ return a+rand(b-a);\n    }\n};\n\n"
  code: "#include <chrono>\nclass xor_shift {\n    uint32_t x, y, z, w;\npublic:\n\
    \    xor_shift() : x(static_cast<uint32_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL\
    \ << 32)-1))),\n    y(1068246329), z(321908594), w(1234567890) {};\n\n    uint32_t\
    \ urand(){\n        uint32_t t;\n        t = x ^ (x << 11);\n        x = y; y\
    \ = z; z = w;\n        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n        return w;\n\
    \    };\n\n    int rand(int n){\n        if(n < 0) return -rand(-n);\n       \
    \ uint32_t t = numeric_limits<uint32_t>::max()/(n+1)*(n+1);\n        uint32_t\
    \ e = urand();\n        while(e >= t) e = urand();\n        return static_cast<int>(e%(n+1));\n\
    \    }\n\n    int rand(int a, int b){\n        if(a > b) swap(a, b);\n       \
    \ return a+rand(b-a);\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: util/xorshift.cpp
  requiredBy:
  - string/rolling_hash.cpp
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0355.test.cpp
documentation_of: util/xorshift.cpp
layout: document
redirect_from:
- /library/util/xorshift.cpp
- /library/util/xorshift.cpp.html
title: util/xorshift.cpp
---
