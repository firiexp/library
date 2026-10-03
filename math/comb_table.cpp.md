---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_comb_table.test.cpp
    title: test/yosupo_aplusb_comb_table.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/comb_table.cpp\"\nvector<vector<mint>> comb_table(int\
    \ n, int m){\n    vector<vector<mint>> res(n+1, vector<mint>(m+1, 0));\n    for\
    \ (int i = 0; i <= n; ++i){\n        res[i][0] = 1;\n        for(int j = 1; j\
    \ <= min(i, m); j ++){\n            res[i][j] = res[i-1][j-1] + res[i-1][j];\n\
    \        }\n    }\n    return res;\n}\n"
  code: "vector<vector<mint>> comb_table(int n, int m){\n    vector<vector<mint>>\
    \ res(n+1, vector<mint>(m+1, 0));\n    for (int i = 0; i <= n; ++i){\n       \
    \ res[i][0] = 1;\n        for(int j = 1; j <= min(i, m); j ++){\n            res[i][j]\
    \ = res[i-1][j-1] + res[i-1][j];\n        }\n    }\n    return res;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: math/comb_table.cpp
  requiredBy: []
  timestamp: '2026-10-03 12:24:08+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_comb_table.test.cpp
documentation_of: math/comb_table.cpp
layout: document
redirect_from:
- /library/math/comb_table.cpp
- /library/math/comb_table.cpp.html
title: math/comb_table.cpp
---
