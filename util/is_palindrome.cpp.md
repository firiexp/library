---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_is_palindrome.test.cpp
    title: test/yosupo_aplusb_is_palindrome.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"util/is_palindrome.cpp\"\nbool is_palindrome(const string\
    \ &s, char c = '?'){\n    auto n = s.length();\n    for (int i = 0; i < (n+1)/2;\
    \ ++i) {\n        if(s[i] == c || s[n-i-1] == c) continue;\n        if(s[i] !=\
    \ s[n-i-1]) return false;\n    }\n    return true;\n}\n"
  code: "bool is_palindrome(const string &s, char c = '?'){\n    auto n = s.length();\n\
    \    for (int i = 0; i < (n+1)/2; ++i) {\n        if(s[i] == c || s[n-i-1] ==\
    \ c) continue;\n        if(s[i] != s[n-i-1]) return false;\n    }\n    return\
    \ true;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: util/is_palindrome.cpp
  requiredBy: []
  timestamp: '2026-10-03 12:02:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_is_palindrome.test.cpp
documentation_of: util/is_palindrome.cpp
layout: document
redirect_from:
- /library/util/is_palindrome.cpp
- /library/util/is_palindrome.cpp.html
title: util/is_palindrome.cpp
---
