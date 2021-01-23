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
  bundledCode: "#line 1 \"util/is_palindrome.cpp\"\nbool is_parindrome(const string\
    \ &s, char c = '?'){\n    auto n = s.length();\n    for (int i = 0; i < (n+1)/2;\
    \ ++i) {\n        if(s[i] == c || s[n-i-1] == c) continue;\n        if(s[i] !=\
    \ s[n-i-1]) return false;\n    }\n    return true;\n}\n"
  code: "bool is_parindrome(const string &s, char c = '?'){\n    auto n = s.length();\n\
    \    for (int i = 0; i < (n+1)/2; ++i) {\n        if(s[i] == c || s[n-i-1] ==\
    \ c) continue;\n        if(s[i] != s[n-i-1]) return false;\n    }\n    return\
    \ true;\n}"
  dependsOn: []
  isVerificationFile: false
  path: util/is_palindrome.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: util/is_palindrome.cpp
layout: document
redirect_from:
- /library/util/is_palindrome.cpp
- /library/util/is_palindrome.cpp.html
title: util/is_palindrome.cpp
---
