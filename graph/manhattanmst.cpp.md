---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0403.test.cpp
    title: test/aoj0403.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/manhattanmst.cpp\"\ntemplate<typename T>\nvector<pair<int,\
    \ int>> manhattanMST(vector<T> xs, vector<T> ys) {\n    using P = pair<int, int>;\n\
    \    vector<P> es;\n    vector<int> ord(xs.size());\n    for (int s = 0; s < 4;\
    \ s++) {\n        iota(ord.begin(), ord.end(), 0);\n        auto cmp = [&](int\
    \ i, int j) -> bool {\n            if (xs[i]+ys[i] != xs[j]+ys[j]) return xs[i]+ys[i]\
    \ < xs[j]+ys[j];\n            return (s>>1) ^ (i > j);\n        };\n        sort(ord.begin(),\
    \ ord.end(), cmp);\n        map<pair<T, int>, int> idx;\n        for (auto &&i\
    \ : ord) {\n            pair<T, int> p = {-ys[i], (s == 3)?i:-i};\n          \
    \  for (auto it = idx.lower_bound(p); it != idx.end(); it = idx.erase(it)) {\n\
    \                if (xs[i] - xs[it->second] < ys[i] - ys[it->second]) break;\n\
    \                es.emplace_back(i, it->second);\n            }\n            idx[p]\
    \ = i;\n        }\n        swap(xs, ys);\n        if(s&1) for(auto &&i : xs) i\
    \ = -i;\n    }\n    return es;\n}\n"
  code: "template<typename T>\nvector<pair<int, int>> manhattanMST(vector<T> xs, vector<T>\
    \ ys) {\n    using P = pair<int, int>;\n    vector<P> es;\n    vector<int> ord(xs.size());\n\
    \    for (int s = 0; s < 4; s++) {\n        iota(ord.begin(), ord.end(), 0);\n\
    \        auto cmp = [&](int i, int j) -> bool {\n            if (xs[i]+ys[i] !=\
    \ xs[j]+ys[j]) return xs[i]+ys[i] < xs[j]+ys[j];\n            return (s>>1) ^\
    \ (i > j);\n        };\n        sort(ord.begin(), ord.end(), cmp);\n        map<pair<T,\
    \ int>, int> idx;\n        for (auto &&i : ord) {\n            pair<T, int> p\
    \ = {-ys[i], (s == 3)?i:-i};\n            for (auto it = idx.lower_bound(p); it\
    \ != idx.end(); it = idx.erase(it)) {\n                if (xs[i] - xs[it->second]\
    \ < ys[i] - ys[it->second]) break;\n                es.emplace_back(i, it->second);\n\
    \            }\n            idx[p] = i;\n        }\n        swap(xs, ys);\n  \
    \      if(s&1) for(auto &&i : xs) i = -i;\n    }\n    return es;\n}"
  dependsOn: []
  isVerificationFile: false
  path: graph/manhattanmst.cpp
  requiredBy: []
  timestamp: '2020-11-06 00:00:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0403.test.cpp
documentation_of: graph/manhattanmst.cpp
layout: document
redirect_from:
- /library/graph/manhattanmst.cpp
- /library/graph/manhattanmst.cpp.html
title: graph/manhattanmst.cpp
---
