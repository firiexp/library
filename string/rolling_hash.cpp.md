---
category: "\u6587\u5B57\u5217"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: util/xorshift.cpp
    title: Xor-Shift
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0355.test.cpp
    title: test/aoj0355.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_string_bytes.test.cpp
    title: test/yosupo_aplusb_string_bytes.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Rolling Hash
    links: []
  bundledCode: "#line 1 \"util/xorshift.cpp\"\nclass xor_shift {\n    uint32_t x,\
    \ y, z, w;\npublic:\n    xor_shift() : x(static_cast<uint32_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL\
    \ << 32)-1))),\n    y(1068246329), z(321908594), w(1234567890) {};\n\n    uint32_t\
    \ urand(){\n        uint32_t t;\n        t = x ^ (x << 11);\n        x = y; y\
    \ = z; z = w;\n        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n        return w;\n\
    \    };\n\n    int rand(int n){\n        return rand(0, n);\n    }\n\n    int\
    \ rand(int a, int b){\n        if(a > b) swap(a, b);\n        uint64_t width =\
    \ int64_t(b) - int64_t(a) + 1;\n        uint64_t limit = (uint64_t(1) << 32) /\
    \ width * width;\n        uint64_t e = urand();\n        while(e >= limit) e =\
    \ urand();\n        return static_cast<int>(int64_t(a) + int64_t(e % width));\n\
    \    }\n};\n#line 2 \"string/rolling_hash.cpp\"\nxor_shift rd;\n\ntemplate<int\
    \ M>\nstruct rolling_hash {\n\n    static ll &B() {\n        static ll B_ = rd.rand(2,\
    \ M-1);\n        return B_;\n    }\n    static vector<ll> &p() {\n        static\
    \ vector<ll> p_{1, B()};\n        return p_;\n    }\n\n    vector<ll> hash;\n\
    \    explicit rolling_hash(const string &s) {\n        if(p().size() <= s.size()){\n\
    \            int l = p().size();\n            p().resize(s.size()+1);\n      \
    \      for (int i = l; i < p().size(); ++i) {\n                p()[i] = (p()[i-1]*p()[1])%M;\n\
    \            }\n        }\n        hash.resize(s.size()+1, 0);\n        for (int\
    \ i = 0; i < s.size(); ++i) {\n            hash[i+1] = (hash[i]*B() + (unsigned\
    \ char)s[i]) % M;\n        }\n    };\n\n    ll get(int l, int r){\n        ll\
    \ res = hash[r]+M-hash[l]*p()[r-l]%M;\n        return res >= M ? res-M : res;\n\
    \    }\n};\n\n/**\n * @brief Rolling Hash\n */\n"
  code: "#include \"../util/xorshift.cpp\"\nxor_shift rd;\n\ntemplate<int M>\nstruct\
    \ rolling_hash {\n\n    static ll &B() {\n        static ll B_ = rd.rand(2, M-1);\n\
    \        return B_;\n    }\n    static vector<ll> &p() {\n        static vector<ll>\
    \ p_{1, B()};\n        return p_;\n    }\n\n    vector<ll> hash;\n    explicit\
    \ rolling_hash(const string &s) {\n        if(p().size() <= s.size()){\n     \
    \       int l = p().size();\n            p().resize(s.size()+1);\n           \
    \ for (int i = l; i < p().size(); ++i) {\n                p()[i] = (p()[i-1]*p()[1])%M;\n\
    \            }\n        }\n        hash.resize(s.size()+1, 0);\n        for (int\
    \ i = 0; i < s.size(); ++i) {\n            hash[i+1] = (hash[i]*B() + (unsigned\
    \ char)s[i]) % M;\n        }\n    };\n\n    ll get(int l, int r){\n        ll\
    \ res = hash[r]+M-hash[l]*p()[r-l]%M;\n        return res >= M ? res-M : res;\n\
    \    }\n};\n\n/**\n * @brief Rolling Hash\n */\n"
  dependsOn:
  - util/xorshift.cpp
  isVerificationFile: false
  path: string/rolling_hash.cpp
  requiredBy: []
  timestamp: '2026-10-03 16:38:16+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0355.test.cpp
  - test/yosupo_aplusb_string_bytes.test.cpp
date: 2019-09-16
documentation_of: string/rolling_hash.cpp
layout: document
tags: "\u6587\u5B57\u5217"
title: Rolling Hash
---

## 説明

