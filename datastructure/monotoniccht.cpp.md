---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/monotoniccht.cpp\"\ntemplate<class T, bool\
    \ get_max>\nclass CHT {\n    using P = pair<T, T>;\n    deque<P> lines;\npublic:\n\
    \    CHT() = default;\n    int sgn(T x) { return x == 0 ? 0 : (x > 0 ? 1 : -1);\
    \ }\n    bool check(P l1, P l2, P l3){\n        if(l1.second == l2.second || l2.second\
    \ == l3.second){\n            return sgn(l1.first - l2.first)*sgn(l2.second -\
    \ l3.second)\n                >= sgn(l2.first - l3.first)*sgn(l1.second - l2.second);\n\
    \        }else {\n            return (l1.first - l2.first)*sgn(l2.second - l3.second)/\
    \ static_cast<long double>(abs(l1.second - l2.second))\n                   >=\
    \ (l2.first - l3.first)*sgn(l1.second - l2.second)/ static_cast<long double>(abs(l2.second\
    \ - l3.second));\n        }\n    }\n\n    void add_line(T a, T b) { // add ax\
    \ + b\n        if(get_max) a = -a, b = -b;\n        P L(a, b);\n        if(lines.empty()){\n\
    \            lines.emplace_back(L);\n            return;\n        }\n        if(lines.front().first\
    \ <= a){\n            if(lines.front().first == a){\n                if(lines.front().second\
    \ <= b) return;\n                else lines.pop_front();\n            }\n    \
    \        while(lines.size() >= 2 && check(L, lines.front(), lines[1])) lines.pop_front();\n\
    \            lines.emplace_front(L);\n        }else {\n            if(lines.back().first\
    \ == a){\n                if(lines.back().second <= b) return;\n             \
    \   else lines.pop_back();\n            }\n            while(lines.size() >= 2\
    \ && check(lines[lines.size()-2], lines.back(), L)) lines.pop_back();\n      \
    \      lines.emplace_back(L);\n        }\n    }\n\n    T val(const P &L, const\
    \ T &x) { return L.first * x + L.second; }\n    T query(T x){\n        int l =\
    \ -1, r = lines.size() - 1;\n        while(r - l > 1){\n            int mid =\
    \ (l+r) >> 1;\n            if(val(lines[mid], x) >= val(lines[mid+1], x)) l =\
    \ mid;\n            else r = mid;\n        }\n        return get_max ? -val(lines[r],\
    \ x) : val(lines[r], x);\n    }\n\n    T query_increase(T x){\n        while(lines.size()\
    \ >= 2 && val(lines.front(), x) >= val(lines[1], x)) lines.pop_front();\n    \
    \    return get_max ? -val(lines.front(), x) : val(lines.front(), x);\n    }\n\
    \n    T query_decrease(T x){\n        while(lines.size() >= 2 && val(lines.back(),\
    \ x) >= val(lines[lines.size() - 2], x)) lines.pop_back();\n        return get_max\
    \ ? -val(lines.back(), x) : val(lines.back(), x);\n    }\n};\n"
  code: "template<class T, bool get_max>\nclass CHT {\n    using P = pair<T, T>;\n\
    \    deque<P> lines;\npublic:\n    CHT() = default;\n    int sgn(T x) { return\
    \ x == 0 ? 0 : (x > 0 ? 1 : -1); }\n    bool check(P l1, P l2, P l3){\n      \
    \  if(l1.second == l2.second || l2.second == l3.second){\n            return sgn(l1.first\
    \ - l2.first)*sgn(l2.second - l3.second)\n                >= sgn(l2.first - l3.first)*sgn(l1.second\
    \ - l2.second);\n        }else {\n            return (l1.first - l2.first)*sgn(l2.second\
    \ - l3.second)/ static_cast<long double>(abs(l1.second - l2.second))\n       \
    \            >= (l2.first - l3.first)*sgn(l1.second - l2.second)/ static_cast<long\
    \ double>(abs(l2.second - l3.second));\n        }\n    }\n\n    void add_line(T\
    \ a, T b) { // add ax + b\n        if(get_max) a = -a, b = -b;\n        P L(a,\
    \ b);\n        if(lines.empty()){\n            lines.emplace_back(L);\n      \
    \      return;\n        }\n        if(lines.front().first <= a){\n           \
    \ if(lines.front().first == a){\n                if(lines.front().second <= b)\
    \ return;\n                else lines.pop_front();\n            }\n          \
    \  while(lines.size() >= 2 && check(L, lines.front(), lines[1])) lines.pop_front();\n\
    \            lines.emplace_front(L);\n        }else {\n            if(lines.back().first\
    \ == a){\n                if(lines.back().second <= b) return;\n             \
    \   else lines.pop_back();\n            }\n            while(lines.size() >= 2\
    \ && check(lines[lines.size()-2], lines.back(), L)) lines.pop_back();\n      \
    \      lines.emplace_back(L);\n        }\n    }\n\n    T val(const P &L, const\
    \ T &x) { return L.first * x + L.second; }\n    T query(T x){\n        int l =\
    \ -1, r = lines.size() - 1;\n        while(r - l > 1){\n            int mid =\
    \ (l+r) >> 1;\n            if(val(lines[mid], x) >= val(lines[mid+1], x)) l =\
    \ mid;\n            else r = mid;\n        }\n        return get_max ? -val(lines[r],\
    \ x) : val(lines[r], x);\n    }\n\n    T query_increase(T x){\n        while(lines.size()\
    \ >= 2 && val(lines.front(), x) >= val(lines[1], x)) lines.pop_front();\n    \
    \    return get_max ? -val(lines.front(), x) : val(lines.front(), x);\n    }\n\
    \n    T query_decrease(T x){\n        while(lines.size() >= 2 && val(lines.back(),\
    \ x) >= val(lines[lines.size() - 2], x)) lines.pop_back();\n        return get_max\
    \ ? -val(lines.back(), x) : val(lines.back(), x);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/monotoniccht.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: datastructure/monotoniccht.cpp
layout: document
redirect_from:
- /library/datastructure/monotoniccht.cpp
- /library/datastructure/monotoniccht.cpp.html
title: datastructure/monotoniccht.cpp
---
