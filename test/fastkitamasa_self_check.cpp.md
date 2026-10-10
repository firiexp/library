---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_fastkitamasa_fft.test.cpp
    title: test/yosupo_aplusb_fastkitamasa_fft.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_kth_term_of_linearly_recurrent_sequence_fastkitamasa.test.cpp
    title: test/yosupo_kth_term_of_linearly_recurrent_sequence_fastkitamasa.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"test/fastkitamasa_self_check.cpp\"\nnamespace fastkitamasa_test\
    \ {\n\nvector<mint> multiply(const vector<mint> &a, const vector<mint> &b, const\
    \ vector<mint> &f) {\n    int n = (int)f.size() - 1;\n    vector<mint> result(2\
    \ * n - 1);\n    for (int i = 0; i < (int)a.size(); ++i)\n        for (int j =\
    \ 0; j < (int)b.size(); ++j) result[i + j] += a[i] * b[j];\n    mint inverse =\
    \ f.back().inv();\n    for (int i = 2 * n - 2; i >= n; --i) {\n        mint q\
    \ = result[i] * inverse;\n        for (int j = 0; j <= n; ++j) result[i - n +\
    \ j] -= q * f[j];\n    }\n    result.resize(n);\n    return result;\n}\n\nvector<mint>\
    \ power(const vector<mint> &f, long long exponent) {\n    int n = (int)f.size()\
    \ - 1;\n    vector<mint> result(n), x(n);\n    result[0] = 1;\n    if (n == 1)\
    \ x[0] = -f[0] / f[1];\n    else x[1] = 1;\n    while (exponent) {\n        if\
    \ (exponent & 1) result = multiply(result, x, f);\n        x = multiply(x, x,\
    \ f);\n        exponent >>= 1;\n    }\n    return result;\n}\n\nvoid self_check()\
    \ {\n    vector<int> fibonacci{-1, -1, 1};\n    Fast_Kitamasa legacy(fibonacci,\
    \ mint::get_mod());\n    assert((legacy.kitamasa(10).v == vector<mint>{34, 55}));\n\
    \    assert((fibonacci == vector<int>{-1, -1, 1}));\n    mt19937 rng(60);\n  \
    \  for (int n : {1, 2, 3, 4, 5, 7, 8, 9, 15, 16, 17, 63, 64, 65}) {\n        for\
    \ (int tc = 0; tc < 8; ++tc) {\n            vector<mint> f(n + 1);\n         \
    \   for (auto &x : f) x = int(rng() % 21) - 10;\n            f[n] = 1 + rng()\
    \ % 7;\n            if (tc == 0) fill(f.begin(), f.begin() + n, mint(0));\n  \
    \          if (tc == 1) f[0] = 0;\n            const Fast_Kitamasa solver(f);\n\
    \            auto original = f;\n            for (long long exponent : {0LL, 1LL,\
    \ (long long)n - 1, (long long)n, (long long)n + 1, (long long)(rng() % 1000),\
    \ LLONG_MAX}) {\n                auto actual = solver.kitamasa(exponent);\n  \
    \              assert(actual.size() == n && actual.v == power(f, exponent));\n\
    \                assert(f == original);\n            }\n            vector<mint>\
    \ a(n), b(n);\n            for (auto &x : a) x = rng();\n            for (auto\
    \ &x : b) x = rng();\n            poly value(a);\n            solver.multiply_mod(value,\
    \ poly(b));\n            assert(value.v == multiply(a, b, f));\n            value\
    \ = poly(a);\n            solver.multiply_mod(value, value);\n            assert(value.v\
    \ == multiply(a, a, f));\n            value = poly();\n            solver.multiply_mod(value,\
    \ poly(b));\n            assert(value.v == vector<mint>(n));\n        }\n    }\n\
    \    for (int n = 1; n <= 12; ++n) {\n        vector<mint> f(n + 1);\n       \
    \ f[n] = 1;\n        for (int i = 0; i < n; ++i) f[i] = int(rng() % 11) - 5;\n\
    \        Fast_Kitamasa solver(f);\n        vector<mint> expected(n);\n       \
    \ expected[0] = 1;\n        for (int exponent = 0; exponent < 100; ++exponent)\
    \ {\n            assert(solver.kitamasa(exponent).v == expected);\n          \
    \  mint leading = expected.back();\n            for (int i = n - 1; i > 0; --i)\
    \ expected[i] = expected[i - 1];\n            expected[0] = 0;\n            for\
    \ (int i = 0; i < n; ++i) expected[i] -= leading * f[i];\n        }\n    }\n}\n\
    \n}\n"
  code: "namespace fastkitamasa_test {\n\nvector<mint> multiply(const vector<mint>\
    \ &a, const vector<mint> &b, const vector<mint> &f) {\n    int n = (int)f.size()\
    \ - 1;\n    vector<mint> result(2 * n - 1);\n    for (int i = 0; i < (int)a.size();\
    \ ++i)\n        for (int j = 0; j < (int)b.size(); ++j) result[i + j] += a[i]\
    \ * b[j];\n    mint inverse = f.back().inv();\n    for (int i = 2 * n - 2; i >=\
    \ n; --i) {\n        mint q = result[i] * inverse;\n        for (int j = 0; j\
    \ <= n; ++j) result[i - n + j] -= q * f[j];\n    }\n    result.resize(n);\n  \
    \  return result;\n}\n\nvector<mint> power(const vector<mint> &f, long long exponent)\
    \ {\n    int n = (int)f.size() - 1;\n    vector<mint> result(n), x(n);\n    result[0]\
    \ = 1;\n    if (n == 1) x[0] = -f[0] / f[1];\n    else x[1] = 1;\n    while (exponent)\
    \ {\n        if (exponent & 1) result = multiply(result, x, f);\n        x = multiply(x,\
    \ x, f);\n        exponent >>= 1;\n    }\n    return result;\n}\n\nvoid self_check()\
    \ {\n    vector<int> fibonacci{-1, -1, 1};\n    Fast_Kitamasa legacy(fibonacci,\
    \ mint::get_mod());\n    assert((legacy.kitamasa(10).v == vector<mint>{34, 55}));\n\
    \    assert((fibonacci == vector<int>{-1, -1, 1}));\n    mt19937 rng(60);\n  \
    \  for (int n : {1, 2, 3, 4, 5, 7, 8, 9, 15, 16, 17, 63, 64, 65}) {\n        for\
    \ (int tc = 0; tc < 8; ++tc) {\n            vector<mint> f(n + 1);\n         \
    \   for (auto &x : f) x = int(rng() % 21) - 10;\n            f[n] = 1 + rng()\
    \ % 7;\n            if (tc == 0) fill(f.begin(), f.begin() + n, mint(0));\n  \
    \          if (tc == 1) f[0] = 0;\n            const Fast_Kitamasa solver(f);\n\
    \            auto original = f;\n            for (long long exponent : {0LL, 1LL,\
    \ (long long)n - 1, (long long)n, (long long)n + 1, (long long)(rng() % 1000),\
    \ LLONG_MAX}) {\n                auto actual = solver.kitamasa(exponent);\n  \
    \              assert(actual.size() == n && actual.v == power(f, exponent));\n\
    \                assert(f == original);\n            }\n            vector<mint>\
    \ a(n), b(n);\n            for (auto &x : a) x = rng();\n            for (auto\
    \ &x : b) x = rng();\n            poly value(a);\n            solver.multiply_mod(value,\
    \ poly(b));\n            assert(value.v == multiply(a, b, f));\n            value\
    \ = poly(a);\n            solver.multiply_mod(value, value);\n            assert(value.v\
    \ == multiply(a, a, f));\n            value = poly();\n            solver.multiply_mod(value,\
    \ poly(b));\n            assert(value.v == vector<mint>(n));\n        }\n    }\n\
    \    for (int n = 1; n <= 12; ++n) {\n        vector<mint> f(n + 1);\n       \
    \ f[n] = 1;\n        for (int i = 0; i < n; ++i) f[i] = int(rng() % 11) - 5;\n\
    \        Fast_Kitamasa solver(f);\n        vector<mint> expected(n);\n       \
    \ expected[0] = 1;\n        for (int exponent = 0; exponent < 100; ++exponent)\
    \ {\n            assert(solver.kitamasa(exponent).v == expected);\n          \
    \  mint leading = expected.back();\n            for (int i = n - 1; i > 0; --i)\
    \ expected[i] = expected[i - 1];\n            expected[0] = 0;\n            for\
    \ (int i = 0; i < n; ++i) expected[i] -= leading * f[i];\n        }\n    }\n}\n\
    \n}\n"
  dependsOn: []
  isVerificationFile: false
  path: test/fastkitamasa_self_check.cpp
  requiredBy: []
  timestamp: '2026-10-10 16:31:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_kth_term_of_linearly_recurrent_sequence_fastkitamasa.test.cpp
  - test/yosupo_aplusb_fastkitamasa_fft.test.cpp
documentation_of: test/fastkitamasa_self_check.cpp
layout: document
redirect_from:
- /library/test/fastkitamasa_self_check.cpp
- /library/test/fastkitamasa_self_check.cpp.html
title: test/fastkitamasa_self_check.cpp
---
