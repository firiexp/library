---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0438.test.cpp
    title: test/aoj0438.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/rolling_hash_ull.cpp\"\n#include <chrono>\nconstexpr\
    \ ull M = (1UL << 61) - 1;\nconstexpr ull POSITIVISER = M * 3;\nconstexpr ull\
    \ MASK30 = (1UL << 30) - 1;\nconstexpr ull MASK31 = (1UL << 31) - 1;\n\nclass\
    \ rolling_hash_ull {\n    static ull get_base(){\n        ull z = (static_cast<uint64_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL\
    \ << 32)-1)))+0x9e3779b97f4a7c15;\n        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n\
    \        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;\n        return z;\n    }\n\
    \n    static inline ull calc_mod(ull val){\n        val = (val & M) + (val >>\
    \ 61);\n        if(val > M) val -= M;\n        return val;\n    }\npublic:\n \
    \   vector<ull> hash;\n\n    static ull &B() {\n        static ull B_ = (get_base())%(M-2)+2;\n\
    \        return B_;\n    }\n\n    static vector<ull> &p() {\n        static vector<ull>\
    \ p_{1, B()};\n        return p_;\n    }\n\n    static inline ull mul(ull x, ull\
    \ y){\n        ull a = x >> 31, b = x & MASK31, c = y >> 31, d = y & MASK31, e\
    \ = b*c+a*d;\n        return (a*c << 1) + b*d + ((e & MASK30) << 31) + (e >> 30);\n\
    \    }\n\n    rolling_hash_ull(const string &s) {\n        if(p().size() <= s.size()){\n\
    \            int l = p().size();\n            p().resize(s.size()+1);\n      \
    \      for (int i = l; i < p().size(); ++i) {\n                p()[i] = calc_mod(mul(p()[i-1],\
    \ p()[1]));\n            }\n        }\n        hash.resize(s.size()+1, 0);\n \
    \       for (int i = 0; i < s.size(); ++i) {\n            hash[i+1] = calc_mod(mul(hash[i],B())\
    \ + s[i]);\n        }\n    };\n\n    rolling_hash_ull(const int& n){\n       \
    \ int l = p().size();\n        p().resize(n+1);\n        for (int i = l; i < p().size();\
    \ ++i) {\n            p()[i] = calc_mod(mul(p()[i-1], p()[1]));\n        }\n \
    \   }\n\n    ull get(int l, int r){\n        return calc_mod(hash[r] + POSITIVISER\
    \ - mul(hash[l], p()[r-l]));\n    }\n\n    static ull val(string &s){\n      \
    \  if(p().size() <= s.size()){\n            int l = p().size();\n            p().resize(s.size()+1);\n\
    \            for (int i = l; i < p().size(); ++i) {\n                p()[i] =\
    \ calc_mod(mul(p()[i-1], p()[1]));\n            }\n        }\n        ull ret\
    \ = 0;\n        for (int i = 0; i < s.size(); ++i) {\n            ret = calc_mod(mul(ret,\
    \ B()) + s[i]);\n        }\n        return ret;\n    }\n};\n"
  code: "#include <chrono>\nconstexpr ull M = (1UL << 61) - 1;\nconstexpr ull POSITIVISER\
    \ = M * 3;\nconstexpr ull MASK30 = (1UL << 30) - 1;\nconstexpr ull MASK31 = (1UL\
    \ << 31) - 1;\n\nclass rolling_hash_ull {\n    static ull get_base(){\n      \
    \  ull z = (static_cast<uint64_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL\
    \ << 32)-1)))+0x9e3779b97f4a7c15;\n        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n\
    \        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;\n        return z;\n    }\n\
    \n    static inline ull calc_mod(ull val){\n        val = (val & M) + (val >>\
    \ 61);\n        if(val > M) val -= M;\n        return val;\n    }\npublic:\n \
    \   vector<ull> hash;\n\n    static ull &B() {\n        static ull B_ = (get_base())%(M-2)+2;\n\
    \        return B_;\n    }\n\n    static vector<ull> &p() {\n        static vector<ull>\
    \ p_{1, B()};\n        return p_;\n    }\n\n    static inline ull mul(ull x, ull\
    \ y){\n        ull a = x >> 31, b = x & MASK31, c = y >> 31, d = y & MASK31, e\
    \ = b*c+a*d;\n        return (a*c << 1) + b*d + ((e & MASK30) << 31) + (e >> 30);\n\
    \    }\n\n    rolling_hash_ull(const string &s) {\n        if(p().size() <= s.size()){\n\
    \            int l = p().size();\n            p().resize(s.size()+1);\n      \
    \      for (int i = l; i < p().size(); ++i) {\n                p()[i] = calc_mod(mul(p()[i-1],\
    \ p()[1]));\n            }\n        }\n        hash.resize(s.size()+1, 0);\n \
    \       for (int i = 0; i < s.size(); ++i) {\n            hash[i+1] = calc_mod(mul(hash[i],B())\
    \ + s[i]);\n        }\n    };\n\n    rolling_hash_ull(const int& n){\n       \
    \ int l = p().size();\n        p().resize(n+1);\n        for (int i = l; i < p().size();\
    \ ++i) {\n            p()[i] = calc_mod(mul(p()[i-1], p()[1]));\n        }\n \
    \   }\n\n    ull get(int l, int r){\n        return calc_mod(hash[r] + POSITIVISER\
    \ - mul(hash[l], p()[r-l]));\n    }\n\n    static ull val(string &s){\n      \
    \  if(p().size() <= s.size()){\n            int l = p().size();\n            p().resize(s.size()+1);\n\
    \            for (int i = l; i < p().size(); ++i) {\n                p()[i] =\
    \ calc_mod(mul(p()[i-1], p()[1]));\n            }\n        }\n        ull ret\
    \ = 0;\n        for (int i = 0; i < s.size(); ++i) {\n            ret = calc_mod(mul(ret,\
    \ B()) + s[i]);\n        }\n        return ret;\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: string/rolling_hash_ull.cpp
  requiredBy: []
  timestamp: '2021-06-21 15:51:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0438.test.cpp
documentation_of: string/rolling_hash_ull.cpp
layout: document
redirect_from:
- /library/string/rolling_hash_ull.cpp
- /library/string/rolling_hash_ull.cpp.html
title: string/rolling_hash_ull.cpp
---
