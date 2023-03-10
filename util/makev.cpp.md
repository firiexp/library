---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0274.test.cpp
    title: test/aoj0274.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj0335.test.cpp
    title: test/aoj0335.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj0422.test.cpp
    title: test/aoj0422.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj0438.test.cpp
    title: test/aoj0438.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/makev.md
    document_title: make_v, chmin, chmax
    links: []
  bundledCode: "#line 1 \"util/makev.cpp\"\ntemplate <class T, class U>\nvector<T>\
    \ make_v(U size, const T& init){ return vector<T>(static_cast<size_t>(size), init);\
    \ }\n\ntemplate<class... Ts, class U>\nauto make_v(U size, Ts... rest) { return\
    \ vector<decltype(make_v(rest...))>(static_cast<size_t>(size), make_v(rest...));\
    \ }\n\ntemplate<class T> void chmin(T &a, const T &b){ a = (a < b ? a : b); }\n\
    template<class T> void chmax(T &a, const T &b){ a = (a > b ? a : b); }\n\n/**\n\
    \ * @brief make_v, chmin, chmax\n * @docs _md/makev.md\n */\n"
  code: "template <class T, class U>\nvector<T> make_v(U size, const T& init){ return\
    \ vector<T>(static_cast<size_t>(size), init); }\n\ntemplate<class... Ts, class\
    \ U>\nauto make_v(U size, Ts... rest) { return vector<decltype(make_v(rest...))>(static_cast<size_t>(size),\
    \ make_v(rest...)); }\n\ntemplate<class T> void chmin(T &a, const T &b){ a = (a\
    \ < b ? a : b); }\ntemplate<class T> void chmax(T &a, const T &b){ a = (a > b\
    \ ? a : b); }\n\n/**\n * @brief make_v, chmin, chmax\n * @docs _md/makev.md\n\
    \ */"
  dependsOn: []
  isVerificationFile: false
  path: util/makev.cpp
  requiredBy: []
  timestamp: '2020-04-28 18:50:16+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0422.test.cpp
  - test/aoj0438.test.cpp
  - test/aoj0274.test.cpp
  - test/aoj0335.test.cpp
documentation_of: util/makev.cpp
layout: document
redirect_from:
- /library/util/makev.cpp
- /library/util/makev.cpp.html
title: make_v, chmin, chmax
---
## 説明
vector<vector\<int\>>とか書かなくていいようにするやつ。

## できること
- make_v : 多次元vectorの作成
- chmin(x, y) : x = min(x, y)
- chmax(x, y) : x = max(x, y) 