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
  bundledCode: "#line 1 \"util/template.cpp\"\n#include <iostream>\n#include <algorithm>\n\
    #include <map>\n#include <set>\n#include <queue>\n#include <stack>\n#include <numeric>\n\
    #include <bitset>\n#include <cmath>\n#include <limits>\n#include <array>\n#include\
    \ <unordered_map>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\n\
    using uint = unsigned;\nusing ull = unsigned long long;\nusing namespace std;\n\
    \ntemplate<class T> constexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\
    \ntemplate<class T>T ifloor(T x, T y){\n    return x/y-(x%y ? (x < 0)^(y < 0)\
    \ : 0);\n}\n\ntemplate<class T>inline T iceil(T x, T y){\n    return x/y+(x%y\
    \ ? (x >= 0)^(y < 0) : 0);\n}\n\ntemplate<class T> inline bool chmax(T& a, T b)\
    \ { if (a < b) { a = b; return 1; } return 0; }\ntemplate<class T> inline bool\
    \ chmin(T& a, T b) { if (a > b) { a = b; return 1; } return 0; }\n\ntemplate <typename\
    \ T>\nusing GPQ = priority_queue<T, vector<T>, greater<T>>;\n\ntemplate<class\
    \ T>\nvector<pair<T, int>> RLE(vector<T> &a){\n    vector<pair<int, int>> p;\n\
    \    p.emplace_back(a[0], 1);\n    for (int j = 1; j < a.size(); ++j) {\n    \
    \    if(p.back().first == a[j]) p.back().second++;\n        else p.emplace_back(a[j],\
    \ 1);\n    }\n    return p;\n}\n\nint main() {\n    \n    return 0;\n}\n"
  code: "#include <iostream>\n#include <algorithm>\n#include <map>\n#include <set>\n\
    #include <queue>\n#include <stack>\n#include <numeric>\n#include <bitset>\n#include\
    \ <cmath>\n#include <limits>\n#include <array>\n#include <unordered_map>\n\nstatic\
    \ const int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\n\
    using ull = unsigned long long;\nusing namespace std;\n\ntemplate<class T> constexpr\
    \ T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\ntemplate<class T>T ifloor(T\
    \ x, T y){\n    return x/y-(x%y ? (x < 0)^(y < 0) : 0);\n}\n\ntemplate<class T>inline\
    \ T iceil(T x, T y){\n    return x/y+(x%y ? (x >= 0)^(y < 0) : 0);\n}\n\ntemplate<class\
    \ T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return 1; } return 0;\
    \ }\ntemplate<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return\
    \ 1; } return 0; }\n\ntemplate <typename T>\nusing GPQ = priority_queue<T, vector<T>,\
    \ greater<T>>;\n\ntemplate<class T>\nvector<pair<T, int>> RLE(vector<T> &a){\n\
    \    vector<pair<int, int>> p;\n    p.emplace_back(a[0], 1);\n    for (int j =\
    \ 1; j < a.size(); ++j) {\n        if(p.back().first == a[j]) p.back().second++;\n\
    \        else p.emplace_back(a[j], 1);\n    }\n    return p;\n}\n\nint main()\
    \ {\n    \n    return 0;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: util/template.cpp
  requiredBy: []
  timestamp: '2026-02-23 16:52:08+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: util/template.cpp
layout: document
redirect_from:
- /library/util/template.cpp
- /library/util/template.cpp.html
title: util/template.cpp
---
