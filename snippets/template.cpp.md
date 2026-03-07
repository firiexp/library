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
  bundledCode: "#line 1 \"snippets/template.cpp\"\n#include <algorithm>\n#include\
    \ <array>\n#include <bitset>\n#include <cmath>\n#include <iostream>\n#include\
    \ <limits>\n#include <map>\n#include <numeric>\n#include <queue>\n#include <set>\n\
    #include <stack>\n#include <unordered_map>\n#include <vector>\n\nstatic const\
    \ int MOD = 1000000007;\nusing ll = long long;\nusing uint = unsigned;\nusing\
    \ ull = unsigned long long;\nusing namespace std;\n\ntemplate<class T>\nconstexpr\
    \ T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\ntemplate<class T>\nT\
    \ ifloor(T x, T y){\n    return x/y-(x%y ? (x < 0)^(y < 0) : 0);\n}\n\ntemplate<class\
    \ T>\ninline T iceil(T x, T y){\n    return x/y+(x%y ? (x >= 0)^(y < 0) : 0);\n\
    }\n\ntemplate<class T>\ninline bool chmax(T& a, T b) {\n    if (a < b) {\n   \
    \     a = b;\n        return true;\n    }\n    return false;\n}\n\ntemplate<class\
    \ T>\ninline bool chmin(T& a, T b) {\n    if (a > b) {\n        a = b;\n     \
    \   return true;\n    }\n    return false;\n}\n\ntemplate <typename T>\nusing\
    \ GPQ = priority_queue<T, vector<T>, greater<T>>;\n\ntemplate<class T>\nvector<pair<T,\
    \ int>> RLE(const vector<T> &a){\n    vector<pair<T, int>> p;\n    if(a.empty())\
    \ return p;\n    p.emplace_back(a[0], 1);\n    for (int j = 1; j < (int)a.size();\
    \ ++j) {\n        if(p.back().first == a[j]) p.back().second++;\n        else\
    \ p.emplace_back(a[j], 1);\n    }\n    return p;\n}\n\nint main() {\n    return\
    \ 0;\n}\n"
  code: "#include <algorithm>\n#include <array>\n#include <bitset>\n#include <cmath>\n\
    #include <iostream>\n#include <limits>\n#include <map>\n#include <numeric>\n#include\
    \ <queue>\n#include <set>\n#include <stack>\n#include <unordered_map>\n#include\
    \ <vector>\n\nstatic const int MOD = 1000000007;\nusing ll = long long;\nusing\
    \ uint = unsigned;\nusing ull = unsigned long long;\nusing namespace std;\n\n\
    template<class T>\nconstexpr T INF = ::numeric_limits<T>::max() / 32 * 15 + 208;\n\
    \ntemplate<class T>\nT ifloor(T x, T y){\n    return x/y-(x%y ? (x < 0)^(y < 0)\
    \ : 0);\n}\n\ntemplate<class T>\ninline T iceil(T x, T y){\n    return x/y+(x%y\
    \ ? (x >= 0)^(y < 0) : 0);\n}\n\ntemplate<class T>\ninline bool chmax(T& a, T\
    \ b) {\n    if (a < b) {\n        a = b;\n        return true;\n    }\n    return\
    \ false;\n}\n\ntemplate<class T>\ninline bool chmin(T& a, T b) {\n    if (a >\
    \ b) {\n        a = b;\n        return true;\n    }\n    return false;\n}\n\n\
    template <typename T>\nusing GPQ = priority_queue<T, vector<T>, greater<T>>;\n\
    \ntemplate<class T>\nvector<pair<T, int>> RLE(const vector<T> &a){\n    vector<pair<T,\
    \ int>> p;\n    if(a.empty()) return p;\n    p.emplace_back(a[0], 1);\n    for\
    \ (int j = 1; j < (int)a.size(); ++j) {\n        if(p.back().first == a[j]) p.back().second++;\n\
    \        else p.emplace_back(a[j], 1);\n    }\n    return p;\n}\n\nint main()\
    \ {\n    return 0;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: snippets/template.cpp
  requiredBy: []
  timestamp: '2026-03-07 20:03:13+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: snippets/template.cpp
layout: document
redirect_from:
- /library/snippets/template.cpp
- /library/snippets/template.cpp.html
title: snippets/template.cpp
---
