---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/manacher.cpp\"\nvector<int> manacher(const string\
    \ &s){\n    vector<int> res(s.size());\n    int i = 0, j = 0;\n    while(i < s.size()){\n\
    \        while(i >= j && i + j < s.size() && s[i-j] == s[i+j]) ++j;\n        res[i]\
    \ = j;\n        int k = 1;\n        while(i >= k && i + k < s.size() && k + res[i-k]\
    \ < j) res[i+k] = res[i-k], ++k;\n        i += k; j -= k;\n    }\n    return res;\n\
    }\n"
  code: "vector<int> manacher(const string &s){\n    vector<int> res(s.size());\n\
    \    int i = 0, j = 0;\n    while(i < s.size()){\n        while(i >= j && i +\
    \ j < s.size() && s[i-j] == s[i+j]) ++j;\n        res[i] = j;\n        int k =\
    \ 1;\n        while(i >= k && i + k < s.size() && k + res[i-k] < j) res[i+k] =\
    \ res[i-k], ++k;\n        i += k; j -= k;\n    }\n    return res;\n}"
  dependsOn: []
  isVerificationFile: false
  path: string/manacher.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: string/manacher.cpp
layout: document
redirect_from:
- /library/string/manacher.cpp
- /library/string/manacher.cpp.html
title: string/manacher.cpp
---
