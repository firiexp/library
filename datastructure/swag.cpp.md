---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_queue_operate_all_composite.test.cpp
    title: test/yosupo_queue_operate_all_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/swag.cpp\"\ntemplate<class G>\nclass SWAG\
    \ {\n    using T = typename G::T;\n    vector<T> in, out, insum, outsum;\npublic:\n\
    \    SWAG() : in(0), out(0), insum(1, G::e()), outsum(1, G::e()) {}\n\n    void\
    \ push(const T& v){\n        insum.push_back(G::f(insum.back(), v));\n       \
    \ in.push_back(v);\n    }\n\n    void pop(){\n        if(out.empty()){\n     \
    \       do {\n                out.emplace_back(in.back());\n                outsum.emplace_back(G::f(in.back(),\
    \ outsum.back()));\n                in.pop_back(); insum.pop_back();\n       \
    \     }while(!in.empty());\n        }\n        out.pop_back(); outsum.pop_back();\n\
    \    }\n\n    T fold(){\n        return G::f(outsum.back(), insum.back());\n \
    \   }\n};\n/*\nstruct Monoid {\n    using T = int;\n    static T f(T a, T b) {\
    \ return a+b; }\n    static T e() { return 0; }\n};\n*/\n"
  code: "template<class G>\nclass SWAG {\n    using T = typename G::T;\n    vector<T>\
    \ in, out, insum, outsum;\npublic:\n    SWAG() : in(0), out(0), insum(1, G::e()),\
    \ outsum(1, G::e()) {}\n\n    void push(const T& v){\n        insum.push_back(G::f(insum.back(),\
    \ v));\n        in.push_back(v);\n    }\n\n    void pop(){\n        if(out.empty()){\n\
    \            do {\n                out.emplace_back(in.back());\n            \
    \    outsum.emplace_back(G::f(in.back(), outsum.back()));\n                in.pop_back();\
    \ insum.pop_back();\n            }while(!in.empty());\n        }\n        out.pop_back();\
    \ outsum.pop_back();\n    }\n\n    T fold(){\n        return G::f(outsum.back(),\
    \ insum.back());\n    }\n};\n/*\nstruct Monoid {\n    using T = int;\n    static\
    \ T f(T a, T b) { return a+b; }\n    static T e() { return 0; }\n};\n*/"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/swag.cpp
  requiredBy: []
  timestamp: '2020-10-27 21:25:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_queue_operate_all_composite.test.cpp
documentation_of: datastructure/swag.cpp
layout: document
redirect_from:
- /library/datastructure/swag.cpp
- /library/datastructure/swag.cpp.html
title: datastructure/swag.cpp
---
