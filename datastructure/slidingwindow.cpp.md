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
  bundledCode: "#line 1 \"datastructure/slidingwindow.cpp\"\ntemplate<class T, class\
    \ F>\nclass sliding_window {\n    vector<T> v;\n    deque<T> Q;\n    F f;\npublic:\n\
    \    int l, r;\n    explicit sliding_window(vector<T> &v, F f) : v(v), f(f), l(0),\
    \ r(0) {};\n    void set(vector<T> &u){\n        v = u;\n        Q.clear();\n\
    \        l = 0; r = 0;\n    }\n    void reset(){\n        Q.clear();\n       \
    \ l = 0, r = 0;\n    }\n    void slideL(){\n        if(Q.front() == l++) Q.pop_front();\n\
    \    }\n    void slideR(){\n        while(!Q.empty() && !f(v[Q.back()], v[r]))\
    \ Q.pop_back();\n        Q.push_back(r++);\n    }\n    T get_index()  {\n    \
    \    if(l == r) return 0;\n        return Q.front();\n    }\n    T value()  {\n\
    \        if(l == r) return 0;\n        return v[Q.front()];\n    }\n};\n"
  code: "template<class T, class F>\nclass sliding_window {\n    vector<T> v;\n  \
    \  deque<T> Q;\n    F f;\npublic:\n    int l, r;\n    explicit sliding_window(vector<T>\
    \ &v, F f) : v(v), f(f), l(0), r(0) {};\n    void set(vector<T> &u){\n       \
    \ v = u;\n        Q.clear();\n        l = 0; r = 0;\n    }\n    void reset(){\n\
    \        Q.clear();\n        l = 0, r = 0;\n    }\n    void slideL(){\n      \
    \  if(Q.front() == l++) Q.pop_front();\n    }\n    void slideR(){\n        while(!Q.empty()\
    \ && !f(v[Q.back()], v[r])) Q.pop_back();\n        Q.push_back(r++);\n    }\n\
    \    T get_index()  {\n        if(l == r) return 0;\n        return Q.front();\n\
    \    }\n    T value()  {\n        if(l == r) return 0;\n        return v[Q.front()];\n\
    \    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/slidingwindow.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: datastructure/slidingwindow.cpp
layout: document
redirect_from:
- /library/datastructure/slidingwindow.cpp
- /library/datastructure/slidingwindow.cpp.html
title: datastructure/slidingwindow.cpp
---
