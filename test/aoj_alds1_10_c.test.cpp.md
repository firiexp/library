---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/lcs_bit.cpp
    title: string/lcs_bit.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_10_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_10_C
  bundledCode: "#line 1 \"test/aoj_alds1_10_c.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_10_C\"\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing\
    \ uint = unsigned;\nusing ull = unsigned long long;\nusing namespace std;\n\n\
    template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\
    \n#line 1 \"string/lcs_bit.cpp\"\nint LCS_bit(string &s, string &t){\n    const\
    \ int n = s.size(), m = t.size(), bit_sz = (m+63)>>6;\n    vector<vector<ull>>\
    \ p(256, vector<ull>(bit_sz, 0));\n    for (int i = 0; i < m; ++i) {\n       \
    \ p[t[i]][i>>6] |= (1ULL << (i&63));\n    }\n    vector<ull> dp(bit_sz);\n   \
    \ for (int i = 0; i < m; ++i) {\n        if(s[0] == t[i]) {\n            dp[i>>6]\
    \ |= (1ULL << (i&63));\n            break;\n        }\n    }\n    for (int i =\
    \ 1; i < n; ++i) {\n        ull shift = 1, sub = 0, tmp_sub = 0;\n        for\
    \ (int j = 0; j < bit_sz; ++j) {\n            ull x = dp[j] | p[s[i]][j], y =\
    \ (dp[j] << 1)|shift, z = x;\n            shift = dp[j] >> 63;\n            tmp_sub\
    \ = z < sub;\n            z -= sub;\n            sub = tmp_sub;\n            sub\
    \ += z < y;\n            z -= y;\n            dp[j] = (z^x)&x;\n        }\n  \
    \      dp[m>>6] &= (1LLU << (m&63))-1;\n    }\n    int ans = 0;\n    for (int\
    \ i = 0; i < bit_sz; ++i) {\n        ans += __builtin_popcountll(dp[i]);\n   \
    \ }\n    return ans;\n}\n#line 21 \"test/aoj_alds1_10_c.test.cpp\"\n\nint main()\
    \ {\n    int n;\n    cin >> n;\n    while(n--){\n        string s, t;\n      \
    \  cin >> s >> t;\n        cout << LCS_bit(s, t) << \"\\n\";\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_10_C\"\n\
    #include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n#include\
    \ <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\
    \nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\n\
    using ull = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\n#include \"../string/lcs_bit.cpp\"\
    \n\nint main() {\n    int n;\n    cin >> n;\n    while(n--){\n        string s,\
    \ t;\n        cin >> s >> t;\n        cout << LCS_bit(s, t) << \"\\n\";\n    }\n\
    \    return 0;\n}\n"
  dependsOn:
  - string/lcs_bit.cpp
  isVerificationFile: true
  path: test/aoj_alds1_10_c.test.cpp
  requiredBy: []
  timestamp: '2021-06-21 16:27:34+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj_alds1_10_c.test.cpp
layout: document
redirect_from:
- /verify/test/aoj_alds1_10_c.test.cpp
- /verify/test/aoj_alds1_10_c.test.cpp.html
title: test/aoj_alds1_10_c.test.cpp
---
