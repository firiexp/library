---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_alds1_10_c.test.cpp
    title: test/aoj_alds1_10_c.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/lcs_bit.md
    document_title: LCS(bitset)
    links: []
  bundledCode: "#line 1 \"string/lcs_bit.cpp\"\nint LCS_bit(string &s, string &t){\n\
    \    const int n = s.size(), m = t.size(), bit_sz = (m+63)>>6;\n    if(n == 0\
    \ || m == 0) return 0;\n    vector<vector<ull>> p(256, vector<ull>(bit_sz, 0));\n\
    \    for (int i = 0; i < m; ++i) {\n        p[(unsigned char)t[i]][i>>6] |= (1ULL\
    \ << (i&63));\n    }\n    vector<ull> dp(bit_sz);\n    for (int i = 0; i < m;\
    \ ++i) {\n        if(s[0] == t[i]) {\n            dp[i>>6] |= (1ULL << (i&63));\n\
    \            break;\n        }\n    }\n    for (int i = 1; i < n; ++i) {\n   \
    \     ull shift = 1, sub = 0, tmp_sub = 0;\n        for (int j = 0; j < bit_sz;\
    \ ++j) {\n            ull x = dp[j] | p[(unsigned char)s[i]][j], y = (dp[j] <<\
    \ 1)|shift, z = x;\n            shift = dp[j] >> 63;\n            tmp_sub = z\
    \ < sub;\n            z -= sub;\n            sub = tmp_sub;\n            sub +=\
    \ z < y;\n            z -= y;\n            dp[j] = (z^x)&x;\n        }\n     \
    \   if(m & 63) dp.back() &= (1ULL << (m & 63)) - 1;\n    }\n    int ans = 0;\n\
    \    for (int i = 0; i < bit_sz; ++i) {\n        ans += __builtin_popcountll(dp[i]);\n\
    \    }\n    return ans;\n}\n\n/**\n * @brief LCS(bitset)\n * @docs _md/lcs_bit.md\n\
    \ */\n"
  code: "int LCS_bit(string &s, string &t){\n    const int n = s.size(), m = t.size(),\
    \ bit_sz = (m+63)>>6;\n    if(n == 0 || m == 0) return 0;\n    vector<vector<ull>>\
    \ p(256, vector<ull>(bit_sz, 0));\n    for (int i = 0; i < m; ++i) {\n       \
    \ p[(unsigned char)t[i]][i>>6] |= (1ULL << (i&63));\n    }\n    vector<ull> dp(bit_sz);\n\
    \    for (int i = 0; i < m; ++i) {\n        if(s[0] == t[i]) {\n            dp[i>>6]\
    \ |= (1ULL << (i&63));\n            break;\n        }\n    }\n    for (int i =\
    \ 1; i < n; ++i) {\n        ull shift = 1, sub = 0, tmp_sub = 0;\n        for\
    \ (int j = 0; j < bit_sz; ++j) {\n            ull x = dp[j] | p[(unsigned char)s[i]][j],\
    \ y = (dp[j] << 1)|shift, z = x;\n            shift = dp[j] >> 63;\n         \
    \   tmp_sub = z < sub;\n            z -= sub;\n            sub = tmp_sub;\n  \
    \          sub += z < y;\n            z -= y;\n            dp[j] = (z^x)&x;\n\
    \        }\n        if(m & 63) dp.back() &= (1ULL << (m & 63)) - 1;\n    }\n \
    \   int ans = 0;\n    for (int i = 0; i < bit_sz; ++i) {\n        ans += __builtin_popcountll(dp[i]);\n\
    \    }\n    return ans;\n}\n\n/**\n * @brief LCS(bitset)\n * @docs _md/lcs_bit.md\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: string/lcs_bit.cpp
  requiredBy: []
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj_alds1_10_c.test.cpp
documentation_of: string/lcs_bit.cpp
layout: document
redirect_from:
- /library/string/lcs_bit.cpp
- /library/string/lcs_bit.cpp.html
title: LCS(bitset)
---
## 説明
bitset を使って 2 文字列の LCS 長を求める。
文字列長を `N`, `M` とすると計算量は `O(256 * ceil(M / 64) + N * ceil(M / 64))`。

## できること
- `int LCS_bit(string& s, string& t)`
  `s` と `t` の最長共通部分列の長さを返す。空文字列を含んでも `0` を返す

## 使い方
```cpp
string s, t;
int len = LCS_bit(s, t);
```

## 実装上の補足
ASCII 相当の 256 文字を前提にしている。
復元は行わず、長さだけを返す。
