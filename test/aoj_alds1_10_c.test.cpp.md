---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/lcs_bit.cpp
    title: LCS(bitset)
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
    \ <cmath>\n#include <cassert>\n#include <random>\n\nstatic const int MOD = 1000000007;\n\
    using ll = long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\n\
    using namespace std;\n\ntemplate<class T> constexpr T INF = ::numeric_limits<T>::max()\
    \ / 32 * 15 + 208;\n\n#line 1 \"string/lcs_bit.cpp\"\nint LCS_bit(string &a, string\
    \ &b){\n    const string &s = a.size() >= b.size() ? a : b;\n    const string\
    \ &t = a.size() >= b.size() ? b : a;\n    const int n = s.size(), m = t.size(),\
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
    \    }\n    return ans;\n}\n\n/**\n * @brief LCS(bitset)\n */\n#line 23 \"test/aoj_alds1_10_c.test.cpp\"\
    \n\nvoid self_check() {\n    mt19937 rng(54);\n    const vector<int> sizes{0,\
    \ 1, 63, 64, 65, 127, 128, 129};\n    for (int tc = 0; tc < 400; ++tc) {\n   \
    \     string a(sizes[tc % sizes.size()], '\\0');\n        string b(sizes[(tc /\
    \ sizes.size()) % sizes.size()], '\\0');\n        for (char &c : a) c = char(rng()\
    \ % (tc % 2 ? 256 : 3));\n        for (char &c : b) c = char(rng() % (tc % 2 ?\
    \ 256 : 3));\n        vector<vector<int>> dp(a.size() + 1, vector<int>(b.size()\
    \ + 1));\n        for (int i = 0; i < (int)a.size(); ++i) for (int j = 0; j <\
    \ (int)b.size(); ++j)\n            dp[i + 1][j + 1] = a[i] == b[j] ? dp[i][j]\
    \ + 1 : max(dp[i][j + 1], dp[i + 1][j]);\n        auto original_a = a, original_b\
    \ = b;\n        assert(LCS_bit(a, b) == dp.back().back());\n        assert(LCS_bit(b,\
    \ a) == dp.back().back());\n        assert(a == original_a && b == original_b);\n\
    \    }\n}\n\nint main() {\n    self_check();\n    int n;\n    cin >> n;\n    while(n--){\n\
    \        string s, t;\n        cin >> s >> t;\n        cout << LCS_bit(s, t) <<\
    \ \"\\n\";\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_10_C\"\n\
    #include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n#include\
    \ <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\
    #include <cassert>\n#include <random>\n\nstatic const int MOD = 1000000007;\n\
    using ll = long long;\nusing uint = unsigned;\nusing ull = unsigned long long;\n\
    using namespace std;\n\ntemplate<class T> constexpr T INF = ::numeric_limits<T>::max()\
    \ / 32 * 15 + 208;\n\n#include \"../string/lcs_bit.cpp\"\n\nvoid self_check()\
    \ {\n    mt19937 rng(54);\n    const vector<int> sizes{0, 1, 63, 64, 65, 127,\
    \ 128, 129};\n    for (int tc = 0; tc < 400; ++tc) {\n        string a(sizes[tc\
    \ % sizes.size()], '\\0');\n        string b(sizes[(tc / sizes.size()) % sizes.size()],\
    \ '\\0');\n        for (char &c : a) c = char(rng() % (tc % 2 ? 256 : 3));\n \
    \       for (char &c : b) c = char(rng() % (tc % 2 ? 256 : 3));\n        vector<vector<int>>\
    \ dp(a.size() + 1, vector<int>(b.size() + 1));\n        for (int i = 0; i < (int)a.size();\
    \ ++i) for (int j = 0; j < (int)b.size(); ++j)\n            dp[i + 1][j + 1] =\
    \ a[i] == b[j] ? dp[i][j] + 1 : max(dp[i][j + 1], dp[i + 1][j]);\n        auto\
    \ original_a = a, original_b = b;\n        assert(LCS_bit(a, b) == dp.back().back());\n\
    \        assert(LCS_bit(b, a) == dp.back().back());\n        assert(a == original_a\
    \ && b == original_b);\n    }\n}\n\nint main() {\n    self_check();\n    int n;\n\
    \    cin >> n;\n    while(n--){\n        string s, t;\n        cin >> s >> t;\n\
    \        cout << LCS_bit(s, t) << \"\\n\";\n    }\n    return 0;\n}\n"
  dependsOn:
  - string/lcs_bit.cpp
  isVerificationFile: true
  path: test/aoj_alds1_10_c.test.cpp
  requiredBy: []
  timestamp: '2026-10-03 16:22:52+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj_alds1_10_c.test.cpp
layout: document
redirect_from:
- /verify/test/aoj_alds1_10_c.test.cpp
- /verify/test/aoj_alds1_10_c.test.cpp.html
title: test/aoj_alds1_10_c.test.cpp
---
