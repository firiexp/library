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
  bundledCode: "#line 1 \"util/rle.cpp\"\ntemplate<class T>\nvector<pair<T, int>>\
    \ RLE(vector<T> &a){\n    vector<pair<int, int>> p;\n    p.emplace_back(a[0],\
    \ 1);\n    for (int j = 1; j < a.size(); ++j) {\n        if(p.back().first ==\
    \ a[j]) p.back().second++;\n        else p.emplace_back(a[j], 1);\n    }\n   \
    \ return p;\n}\n"
  code: "template<class T>\nvector<pair<T, int>> RLE(vector<T> &a){\n    vector<pair<int,\
    \ int>> p;\n    p.emplace_back(a[0], 1);\n    for (int j = 1; j < a.size(); ++j)\
    \ {\n        if(p.back().first == a[j]) p.back().second++;\n        else p.emplace_back(a[j],\
    \ 1);\n    }\n    return p;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: util/rle.cpp
  requiredBy: []
  timestamp: '2021-03-20 13:19:40+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: util/rle.cpp
layout: document
redirect_from:
- /library/util/rle.cpp
- /library/util/rle.cpp.html
title: util/rle.cpp
---
