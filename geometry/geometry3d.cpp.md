---
category: "\u5E7E\u4F55"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "3\u6B21\u5143\u5E7E\u4F55"
    links: []
  bundledCode: "#line 1 \"geometry/geometry3d.cpp\"\nusing Real3 = double;\nstatic\
    \ constexpr Real3 EPS3 = 1e-10;\n\nstruct Point3 {\n    Real3 x, y, z;\n\n   \
    \ Point3 &operator+=(const Point3 &a) {\n        x += a.x;\n        y += a.y;\n\
    \        z += a.z;\n        return *this;\n    }\n\n    Point3 &operator-=(const\
    \ Point3 &a) {\n        x -= a.x;\n        y -= a.y;\n        z -= a.z;\n    \
    \    return *this;\n    }\n\n    Point3 &operator*=(Real3 k) {\n        x *= k;\n\
    \        y *= k;\n        z *= k;\n        return *this;\n    }\n\n    Point3\
    \ &operator/=(Real3 k) {\n        x /= k;\n        y /= k;\n        z /= k;\n\
    \        return *this;\n    }\n\n    Point3 operator+(const Point3 &a) const {\
    \ return Point3(*this) += a; }\n    Point3 operator-(const Point3 &a) const {\
    \ return Point3(*this) -= a; }\n    Point3 operator*(Real3 k) const { return Point3(*this)\
    \ *= k; }\n    Point3 operator/(Real3 k) const { return Point3(*this) /= k; }\n\
    \n    Point3(Real3 x = 0, Real3 y = 0, Real3 z = 0) : x(x), y(y), z(z) {}\n};\n\
    \ninline Real3 dot(Point3 a, Point3 b) {\n    return a.x * b.x + a.y * b.y + a.z\
    \ * b.z;\n}\n\ninline Real3 norm(Point3 a) {\n    return dot(a, a);\n}\n\ninline\
    \ Real3 abs(Point3 a) {\n    return std::sqrt(norm(a));\n}\n\ninline Point3 cross(Point3\
    \ a, Point3 b) {\n    return {\n        a.y * b.z - a.z * b.y,\n        a.z *\
    \ b.x - a.x * b.z,\n        a.x * b.y - a.y * b.x,\n    };\n}\n\nstd::istream\
    \ &operator>>(std::istream &s, Point3 &p) {\n    s >> p.x >> p.y >> p.z;\n   \
    \ return s;\n}\n\nstruct Plane {\n    Real3 a, b, c, d;\n\n    Plane(Real3 a,\
    \ Real3 b, Real3 c, Real3 d) : a(a), b(b), c(c), d(d) {}\n\n    Plane(Point3 p,\
    \ Point3 q, Point3 r) {\n        Point3 n = cross(q - p, r - p);\n        a =\
    \ n.x;\n        b = n.y;\n        c = n.z;\n        d = -dot(n, p);\n    }\n};\n\
    \ninline Real3 eval(Plane p, Point3 x) {\n    return p.a * x.x + p.b * x.y + p.c\
    \ * x.z + p.d;\n}\n\ninline Point3 crossPoint(Point3 s, Point3 t, Plane p) {\n\
    \    Point3 dir = t - s;\n    Real3 den = p.a * dir.x + p.b * dir.y + p.c * dir.z;\n\
    \    Real3 num = eval(p, s);\n    return s - dir * (num / den);\n}\n\n/**\n *\
    \ @brief 3\u6B21\u5143\u5E7E\u4F55\n */\n"
  code: "using Real3 = double;\nstatic constexpr Real3 EPS3 = 1e-10;\n\nstruct Point3\
    \ {\n    Real3 x, y, z;\n\n    Point3 &operator+=(const Point3 &a) {\n       \
    \ x += a.x;\n        y += a.y;\n        z += a.z;\n        return *this;\n   \
    \ }\n\n    Point3 &operator-=(const Point3 &a) {\n        x -= a.x;\n        y\
    \ -= a.y;\n        z -= a.z;\n        return *this;\n    }\n\n    Point3 &operator*=(Real3\
    \ k) {\n        x *= k;\n        y *= k;\n        z *= k;\n        return *this;\n\
    \    }\n\n    Point3 &operator/=(Real3 k) {\n        x /= k;\n        y /= k;\n\
    \        z /= k;\n        return *this;\n    }\n\n    Point3 operator+(const Point3\
    \ &a) const { return Point3(*this) += a; }\n    Point3 operator-(const Point3\
    \ &a) const { return Point3(*this) -= a; }\n    Point3 operator*(Real3 k) const\
    \ { return Point3(*this) *= k; }\n    Point3 operator/(Real3 k) const { return\
    \ Point3(*this) /= k; }\n\n    Point3(Real3 x = 0, Real3 y = 0, Real3 z = 0) :\
    \ x(x), y(y), z(z) {}\n};\n\ninline Real3 dot(Point3 a, Point3 b) {\n    return\
    \ a.x * b.x + a.y * b.y + a.z * b.z;\n}\n\ninline Real3 norm(Point3 a) {\n   \
    \ return dot(a, a);\n}\n\ninline Real3 abs(Point3 a) {\n    return std::sqrt(norm(a));\n\
    }\n\ninline Point3 cross(Point3 a, Point3 b) {\n    return {\n        a.y * b.z\
    \ - a.z * b.y,\n        a.z * b.x - a.x * b.z,\n        a.x * b.y - a.y * b.x,\n\
    \    };\n}\n\nstd::istream &operator>>(std::istream &s, Point3 &p) {\n    s >>\
    \ p.x >> p.y >> p.z;\n    return s;\n}\n\nstruct Plane {\n    Real3 a, b, c, d;\n\
    \n    Plane(Real3 a, Real3 b, Real3 c, Real3 d) : a(a), b(b), c(c), d(d) {}\n\n\
    \    Plane(Point3 p, Point3 q, Point3 r) {\n        Point3 n = cross(q - p, r\
    \ - p);\n        a = n.x;\n        b = n.y;\n        c = n.z;\n        d = -dot(n,\
    \ p);\n    }\n};\n\ninline Real3 eval(Plane p, Point3 x) {\n    return p.a * x.x\
    \ + p.b * x.y + p.c * x.z + p.d;\n}\n\ninline Point3 crossPoint(Point3 s, Point3\
    \ t, Plane p) {\n    Point3 dir = t - s;\n    Real3 den = p.a * dir.x + p.b *\
    \ dir.y + p.c * dir.z;\n    Real3 num = eval(p, s);\n    return s - dir * (num\
    \ / den);\n}\n\n/**\n * @brief 3\u6B21\u5143\u5E7E\u4F55\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: geometry/geometry3d.cpp
  requiredBy: []
  timestamp: '2026-03-23 22:54:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
date: 2026-03-12
documentation_of: geometry/geometry3d.cpp
layout: document
tags: "\u5E7E\u4F55"
title: "3\u6B21\u5143\u5E7E\u4F55(Geometry 3D)"
---

## 説明
3 次元ベクトル演算と、3 点から決まる平面、直線と平面の交点を扱う最小限の補助である。
凸包や球、距離計算などはまだ持たない。

## できること
- `Point3(x, y, z)`
  3 次元点・ベクトルを作る
- `a + b`, `a - b`, `a * k`, `a / k`
  ベクトル演算をする
- `Real3 dot(Point3 a, Point3 b)`
  内積を返す
- `Real3 norm(Point3 a)`
  二乗ノルムを返す
- `Real3 abs(Point3 a)`
  ノルムを返す
- `Point3 cross(Point3 a, Point3 b)`
  外積を返す
- `Plane(a, b, c, d)`
  平面 $ax + by + cz + d = 0$ を作る
- `Plane(p, q, r)`
  3 点を通る平面を作る。3 点が同一直線上なら法線が 0 になる
- `Real3 eval(Plane p, Point3 x)`
  点 `x` を平面式へ代入した値を返す
- `Point3 crossPoint(Point3 s, Point3 t, Plane p)`
  直線 `s` - `t` と平面 `p` の交点を返す。平行なときは使えない

## 使い方
`Point3` をベクトルとして扱い、`Plane` は係数指定か 3 点指定で作る。
直線と平面の交点は `crossPoint` を使う。

```cpp
Point3 a(0, 0, 0), b(1, 0, 0), c(0, 1, 0);
Plane p(a, b, c);
Point3 s(0, 0, 1), t(0, 0, -1);
Point3 x = crossPoint(s, t, p);
```

## 実装上の補足
`Real3` は `double` で、許容誤差として `EPS3` を置いている。
`crossPoint` は分母が 0 に近いと不安定なので、必要なら `abs(den) < EPS3` 相当の判定を呼び出し側で入れる。
