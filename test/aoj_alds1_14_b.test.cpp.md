---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/kmp.cpp
    title: KMP
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B
  bundledCode: "#line 1 \"test/aoj_alds1_14_b.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B\"\
    \n#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing\
    \ uint = unsigned;\nusing ull = unsigned long long;\nusing namespace std;\n\n\
    template<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\
    \n#line 1 \"string/kmp.cpp\"\nvector<int> kmp_table(const string &s){\n    int\
    \ n = s.size();\n    vector<int> table(n + 1);\n    table[0] = -1;\n    for (int\
    \ i = 0, j = -1; i < n;) {\n        while(j >= 0 && s[i] != s[j]) j = table[j];\n\
    \        i++, j++;\n        table[i] = j;\n    }\n    return table;\n}\n\nvector<int>\
    \ kmp_search(const string &text, const string &pattern){\n    int n = text.size(),\
    \ m = pattern.size();\n    vector<int> res;\n    if(pattern.empty()){\n      \
    \  res.resize(n + 1);\n        iota(res.begin(), res.end(), 0);\n        return\
    \ res;\n    }\n    auto table = kmp_table(pattern);\n    for (int i = 0, j = 0;\
    \ i < n;) {\n        while(j >= 0 && text[i] != pattern[j]) j = table[j];\n  \
    \      i++, j++;\n        if(j == m){\n            res.emplace_back(i - j);\n\
    \            j = table[j];\n        }\n    }\n    return res;\n}\n\n/**\n * @brief\
    \ KMP\u6CD5\n */\n#line 21 \"test/aoj_alds1_14_b.test.cpp\"\n\nint main() {\n\
    \    string text, pattern;\n    cin >> text >> pattern;\n    auto res = kmp_search(text,\
    \ pattern);\n    for (auto &&i : res) {\n        cout << i << \"\\n\";\n    }\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B\"\n\
    #include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n#include\
    \ <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include <cmath>\n\
    \nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\n\
    using ull = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\n#include \"../string/kmp.cpp\"\
    \n\nint main() {\n    string text, pattern;\n    cin >> text >> pattern;\n   \
    \ auto res = kmp_search(text, pattern);\n    for (auto &&i : res) {\n        cout\
    \ << i << \"\\n\";\n    }\n    return 0;\n}\n"
  dependsOn:
  - string/kmp.cpp
  isVerificationFile: true
  path: test/aoj_alds1_14_b.test.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj_alds1_14_b.test.cpp
layout: document
redirect_from:
- /verify/test/aoj_alds1_14_b.test.cpp
- /verify/test/aoj_alds1_14_b.test.cpp.html
title: test/aoj_alds1_14_b.test.cpp
---
