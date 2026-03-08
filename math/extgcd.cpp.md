---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/CRT.cpp
    title: "\u4E2D\u56FD\u5270\u4F59\u5B9A\u7406(CRT)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_binomial_coefficient.test.cpp
    title: test/yosupo_binomial_coefficient.test.cpp
  - icon: ':x:'
    path: test/yuki1358.test.cpp
    title: test/yuki1358.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':question:'
  attributes:
    _deprecated_at_docs: _md/extgcd.md
    document_title: "\u62E1\u5F35\u30E6\u30FC\u30AF\u30EA\u30C3\u30C9\u4E92\u9664\u6CD5\
      (Extended GCD)"
    links: []
  bundledCode: "#line 1 \"math/extgcd.cpp\"\ntemplate<typename T>\nT extgcd(T a, T\
    \ b, T &x ,T &y){\n    for (T u = y = 1, v = x = 0; a; ) {\n        ll q = b/a;\n\
    \        swap(x -= q*u, u);\n        swap(y -= q*v, v);\n        swap(b -= q*a,\
    \ a);\n    }\n    return b;\n}\n \n\n/**\n * @brief \u62E1\u5F35\u30E6\u30FC\u30AF\
    \u30EA\u30C3\u30C9\u4E92\u9664\u6CD5(Extended GCD)\n * @docs _md/extgcd.md\n */\n"
  code: "template<typename T>\nT extgcd(T a, T b, T &x ,T &y){\n    for (T u = y =\
    \ 1, v = x = 0; a; ) {\n        ll q = b/a;\n        swap(x -= q*u, u);\n    \
    \    swap(y -= q*v, v);\n        swap(b -= q*a, a);\n    }\n    return b;\n}\n\
    \ \n\n/**\n * @brief \u62E1\u5F35\u30E6\u30FC\u30AF\u30EA\u30C3\u30C9\u4E92\u9664\
    \u6CD5(Extended GCD)\n * @docs _md/extgcd.md\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/extgcd.cpp
  requiredBy:
  - math/CRT.cpp
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/yosupo_binomial_coefficient.test.cpp
  - test/yuki1358.test.cpp
documentation_of: math/extgcd.cpp
layout: document
redirect_from:
- /library/math/extgcd.cpp
- /library/math/extgcd.cpp.html
title: "\u62E1\u5F35\u30E6\u30FC\u30AF\u30EA\u30C3\u30C9\u4E92\u9664\u6CD5(Extended\
  \ GCD)"
---
---
layout: post
title: 拡張ユークリッド互除法
date: 2018-04-28
category: 数学
tags: 整数論
---

## 説明
$a, b$が与えられる時、$ax+by= \gcd (a, b)$を満たす$x, y$を計算する。返り値は$\gcd (a, b)$である。
