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
  bundledCode: "#line 1 \"math/comb_table.cpp\"\nvector<vector<mint>> comb_table(int\
    \ n, int m){\n    vector<vector<mint>> res(n+1, vector<mint>(m+1, 0));\n    for\
    \ (int i = 0; i <= n; ++i){\n        res[i][0] = 1;\n        for(int j = 1; j\
    \ <= i; j ++){\n\t\t\tres[i][j] = res[i-1][j-1] + res[i-1][j];\n        }\n  \
    \  }\n    return res;\n}\n"
  code: "vector<vector<mint>> comb_table(int n, int m){\n    vector<vector<mint>>\
    \ res(n+1, vector<mint>(m+1, 0));\n    for (int i = 0; i <= n; ++i){\n       \
    \ res[i][0] = 1;\n        for(int j = 1; j <= i; j ++){\n\t\t\tres[i][j] = res[i-1][j-1]\
    \ + res[i-1][j];\n        }\n    }\n    return res;\n}"
  dependsOn: []
  isVerificationFile: false
  path: math/comb_table.cpp
  requiredBy: []
  timestamp: '2021-06-22 23:51:14+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/comb_table.cpp
layout: document
redirect_from:
- /library/math/comb_table.cpp
- /library/math/comb_table.cpp.html
title: math/comb_table.cpp
---
