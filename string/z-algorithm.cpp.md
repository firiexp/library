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
  bundledCode: "#line 1 \"string/z-algorithm.cpp\"\nvector<int> Z_algorithm(const\
    \ string &s){\n    vector<int> res(s.size());\n    res.front() = s.size();\n \
    \   for (int i = 1, j = 0; i < s.size(); ++i) {\n        if(i + res[i-j] < j +\
    \ res[j]) res[i] = res[i-j];\n        else {\n            int k = max(0, j + res[j]-i);\n\
    \            while(i + k < s.size() && s[k] == s[i+k]) ++k;\n            res[i]\
    \ = k;\n            j = i;\n        }\n    }\n    return res;\n}\n"
  code: "vector<int> Z_algorithm(const string &s){\n    vector<int> res(s.size());\n\
    \    res.front() = s.size();\n    for (int i = 1, j = 0; i < s.size(); ++i) {\n\
    \        if(i + res[i-j] < j + res[j]) res[i] = res[i-j];\n        else {\n  \
    \          int k = max(0, j + res[j]-i);\n            while(i + k < s.size() &&\
    \ s[k] == s[i+k]) ++k;\n            res[i] = k;\n            j = i;\n        }\n\
    \    }\n    return res;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: string/z-algorithm.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: string/z-algorithm.cpp
layout: document
redirect_from:
- /library/string/z-algorithm.cpp
- /library/string/z-algorithm.cpp.html
title: string/z-algorithm.cpp
---
