---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aoj0399.test.cpp
    title: test/aoj0399.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/squarematrix.cpp\"\ntemplate<class H, size_t SIZE>\n\
    struct SquareMatrix {\n    using T = typename H::T;\n    using ar = array<T, SIZE>;\n\
    \    using mat = array<ar, SIZE>;\n    mat A;\n    SquareMatrix() {\n        for\
    \ (int i = 0; i < SIZE; ++i) {\n            for (int j = 0; j < SIZE; ++j) {\n\
    \                A[i][j] = H::zero();\n            }\n        }\n    }\n    static\
    \ SquareMatrix I(){\n        SquareMatrix X;\n        for (int i = 0; i < SIZE;\
    \ ++i) {\n            for (int j = 0; j < SIZE; ++j) {\n                if(i ==\
    \ j) X[i][j] = H::one();\n                else X[i][j] = H::zero();\n        \
    \    }\n        }\n        return X;\n    }\n\n    friend ar operator*=(ar &x,\
    \ const SquareMatrix &Y) {\n        ar ans;\n        fill(begin(ans), end(ans),\
    \ mint(0));\n        for (int i = 0; i < SIZE; ++i) {\n            for (int j\
    \ = 0; j < SIZE; ++j) {\n                 H::add(ans[j], H::mul(x[i], Y[i][j]));\n\
    \            }\n        }\n        x.swap(ans);\n        return x;\n    }\n  \
    \  friend ar operator*(ar x, const SquareMatrix &Y) { return x *= Y; }\n\n   \
    \ inline const ar &operator[](int k) const{ return (A.at(k)); }\n    inline ar\
    \ &operator[](int k) { return (A.at(k)); }\n    SquareMatrix &operator+= (const\
    \ SquareMatrix &B){\n        for (int i = 0; i < SIZE; ++i) {\n            for\
    \ (int j = 0; j < SIZE; ++j) {\n                H::add((*this)[i][j], B[i][j]);\n\
    \            }\n        }\n        return (*this);\n    }\n\n    SquareMatrix\
    \ &operator-= (const SquareMatrix &B){\n        for (int i = 0; i < SIZE; ++i)\
    \ {\n            for (int j = 0; j < SIZE; ++j) {\n                H::add((*this)[i][j],\
    \ -B[i][j]);\n            }\n        }\n        return (*this);\n    }\n\n   \
    \ SquareMatrix &operator*=(const SquareMatrix &B) {\n        SquareMatrix C{};\n\
    \        for (int i = 0; i < SIZE; ++i) {\n            for (int k = 0; k < SIZE;\
    \ ++k) {\n                for (int j = 0; j < SIZE; ++j) {\n                 \
    \   H::add(C[i][j],  H::mul((*this)[i][k], B[k][j]));\n                }\n   \
    \         }\n        }\n        A.swap(C.A);\n        return (*this);\n    }\n\
    \n    SquareMatrix pow(ll n) const {\n        SquareMatrix a = (*this), res =\
    \ I();\n\n        while(n > 0){\n            if(n & 1) res *= a;\n           \
    \ a *= a;\n            n >>= 1;\n        }\n        return res;\n    }\n    SquareMatrix\
    \ operator+(const SquareMatrix &B) const {return SquareMatrix(*this) += B;}\n\
    \    SquareMatrix operator-(const SquareMatrix &B) const {return SquareMatrix(*this)\
    \ -= B;}\n    SquareMatrix operator*(const SquareMatrix &B) const {return SquareMatrix(*this)\
    \ *= B;}\n};\n\nstruct SemiRing {\n    using T = mint;\n    static inline T mul(T\
    \ x, T y){ return x * y; }\n    static inline void add(T &x, T y){ x += y; }\n\
    \    static inline T one(){ return 1; }\n    static inline T zero(){ return 0;\
    \ }\n};\n\nusing ar = array<SemiRing::T, 64>;\nusing mat = SquareMatrix<SemiRing,\
    \ 64>;\n"
  code: "template<class H, size_t SIZE>\nstruct SquareMatrix {\n    using T = typename\
    \ H::T;\n    using ar = array<T, SIZE>;\n    using mat = array<ar, SIZE>;\n  \
    \  mat A;\n    SquareMatrix() {\n        for (int i = 0; i < SIZE; ++i) {\n  \
    \          for (int j = 0; j < SIZE; ++j) {\n                A[i][j] = H::zero();\n\
    \            }\n        }\n    }\n    static SquareMatrix I(){\n        SquareMatrix\
    \ X;\n        for (int i = 0; i < SIZE; ++i) {\n            for (int j = 0; j\
    \ < SIZE; ++j) {\n                if(i == j) X[i][j] = H::one();\n           \
    \     else X[i][j] = H::zero();\n            }\n        }\n        return X;\n\
    \    }\n\n    friend ar operator*=(ar &x, const SquareMatrix &Y) {\n        ar\
    \ ans;\n        fill(begin(ans), end(ans), mint(0));\n        for (int i = 0;\
    \ i < SIZE; ++i) {\n            for (int j = 0; j < SIZE; ++j) {\n           \
    \      H::add(ans[j], H::mul(x[i], Y[i][j]));\n            }\n        }\n    \
    \    x.swap(ans);\n        return x;\n    }\n    friend ar operator*(ar x, const\
    \ SquareMatrix &Y) { return x *= Y; }\n\n    inline const ar &operator[](int k)\
    \ const{ return (A.at(k)); }\n    inline ar &operator[](int k) { return (A.at(k));\
    \ }\n    SquareMatrix &operator+= (const SquareMatrix &B){\n        for (int i\
    \ = 0; i < SIZE; ++i) {\n            for (int j = 0; j < SIZE; ++j) {\n      \
    \          H::add((*this)[i][j], B[i][j]);\n            }\n        }\n       \
    \ return (*this);\n    }\n\n    SquareMatrix &operator-= (const SquareMatrix &B){\n\
    \        for (int i = 0; i < SIZE; ++i) {\n            for (int j = 0; j < SIZE;\
    \ ++j) {\n                H::add((*this)[i][j], -B[i][j]);\n            }\n  \
    \      }\n        return (*this);\n    }\n\n    SquareMatrix &operator*=(const\
    \ SquareMatrix &B) {\n        SquareMatrix C{};\n        for (int i = 0; i < SIZE;\
    \ ++i) {\n            for (int k = 0; k < SIZE; ++k) {\n                for (int\
    \ j = 0; j < SIZE; ++j) {\n                    H::add(C[i][j],  H::mul((*this)[i][k],\
    \ B[k][j]));\n                }\n            }\n        }\n        A.swap(C.A);\n\
    \        return (*this);\n    }\n\n    SquareMatrix pow(ll n) const {\n      \
    \  SquareMatrix a = (*this), res = I();\n\n        while(n > 0){\n           \
    \ if(n & 1) res *= a;\n            a *= a;\n            n >>= 1;\n        }\n\
    \        return res;\n    }\n    SquareMatrix operator+(const SquareMatrix &B)\
    \ const {return SquareMatrix(*this) += B;}\n    SquareMatrix operator-(const SquareMatrix\
    \ &B) const {return SquareMatrix(*this) -= B;}\n    SquareMatrix operator*(const\
    \ SquareMatrix &B) const {return SquareMatrix(*this) *= B;}\n};\n\nstruct SemiRing\
    \ {\n    using T = mint;\n    static inline T mul(T x, T y){ return x * y; }\n\
    \    static inline void add(T &x, T y){ x += y; }\n    static inline T one(){\
    \ return 1; }\n    static inline T zero(){ return 0; }\n};\n\nusing ar = array<SemiRing::T,\
    \ 64>;\nusing mat = SquareMatrix<SemiRing, 64>;\n"
  dependsOn: []
  isVerificationFile: false
  path: math/squarematrix.cpp
  requiredBy: []
  timestamp: '2021-06-06 22:51:17+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/aoj0399.test.cpp
documentation_of: math/squarematrix.cpp
layout: document
redirect_from:
- /library/math/squarematrix.cpp
- /library/math/squarematrix.cpp.html
title: math/squarematrix.cpp
---
