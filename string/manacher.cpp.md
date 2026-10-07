---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_palindrome_radii.test.cpp
    title: test/yosupo_aplusb_palindrome_radii.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_enumerate_palindromes_manacher.test.cpp
    title: test/yosupo_enumerate_palindromes_manacher.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/manacher.cpp\"\nvector<int> manacher(const string\
    \ &s){\n    vector<int> res(s.size());\n    int i = 0, j = 0;\n    while(i < s.size()){\n\
    \        while(i >= j && i + j < s.size() && s[i-j] == s[i+j]) ++j;\n        res[i]\
    \ = j;\n        int k = 1;\n        while(i >= k && i + k < s.size() && k + res[i-k]\
    \ < j) res[i+k] = res[i-k], ++k;\n        i += k; j -= k;\n    }\n    return res;\n\
    }\n\nstruct PalindromeRadii {\n    vector<int> odd, even;\n\n    explicit PalindromeRadii(const\
    \ string &s): odd(manacher(s)), even(s.size()) {\n        int n = s.size(), l\
    \ = 0, r = -1;\n        for (int i = 0; i < n; ++i) {\n            int k = i >\
    \ r ? 0 : min(even[l + r - i + 1], r - i + 1);\n            while (i - k - 1 >=\
    \ 0 && i + k < n && s[i - k - 1] == s[i + k]) ++k;\n            even[i] = k;\n\
    \            if (i + k - 1 > r) {\n                l = i - k;\n              \
    \  r = i + k - 1;\n            }\n        }\n    }\n\n    bool is_palindrome(int\
    \ l, int r) const {\n        int length = r - l;\n        if (!length) return\
    \ true;\n        int center = l + length / 2;\n        return length & 1 ? odd[center]\
    \ >= length / 2 + 1 : even[center] >= length / 2;\n    }\n};\n"
  code: "vector<int> manacher(const string &s){\n    vector<int> res(s.size());\n\
    \    int i = 0, j = 0;\n    while(i < s.size()){\n        while(i >= j && i +\
    \ j < s.size() && s[i-j] == s[i+j]) ++j;\n        res[i] = j;\n        int k =\
    \ 1;\n        while(i >= k && i + k < s.size() && k + res[i-k] < j) res[i+k] =\
    \ res[i-k], ++k;\n        i += k; j -= k;\n    }\n    return res;\n}\n\nstruct\
    \ PalindromeRadii {\n    vector<int> odd, even;\n\n    explicit PalindromeRadii(const\
    \ string &s): odd(manacher(s)), even(s.size()) {\n        int n = s.size(), l\
    \ = 0, r = -1;\n        for (int i = 0; i < n; ++i) {\n            int k = i >\
    \ r ? 0 : min(even[l + r - i + 1], r - i + 1);\n            while (i - k - 1 >=\
    \ 0 && i + k < n && s[i - k - 1] == s[i + k]) ++k;\n            even[i] = k;\n\
    \            if (i + k - 1 > r) {\n                l = i - k;\n              \
    \  r = i + k - 1;\n            }\n        }\n    }\n\n    bool is_palindrome(int\
    \ l, int r) const {\n        int length = r - l;\n        if (!length) return\
    \ true;\n        int center = l + length / 2;\n        return length & 1 ? odd[center]\
    \ >= length / 2 + 1 : even[center] >= length / 2;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: string/manacher.cpp
  requiredBy: []
  timestamp: '2026-10-07 22:14:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_palindrome_radii.test.cpp
  - test/yosupo_enumerate_palindromes_manacher.test.cpp
documentation_of: string/manacher.cpp
layout: document
redirect_from:
- /library/string/manacher.cpp
- /library/string/manacher.cpp.html
title: string/manacher.cpp
---
