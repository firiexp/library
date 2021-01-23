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
  bundledCode: "#line 1 \"geometry/geometry3d.cpp\"\nusing real = double;\nstatic\
    \ constexpr real EPS = 1e-10;\nstruct Point3 {\n    real x, y, z;\n    Point3&\
    \ operator+=(const Point3 a) { x += a.x; y += a.y; z += a.z;  return *this; }\n\
    \    Point3& operator-=(const Point3 a) { x -= a.x; y -= a.y; z -= a.z; return\
    \ *this; }\n    Point3& operator*=(const real k) { x *= k; y *= k; z *= k;  return\
    \ *this; }\n    Point3& operator/=(const real k) { x /= k; y /= k; z /= k; return\
    \ *this; }\n    Point3 operator+(const Point3 a) const {return Point3(*this) +=\
    \ a; }\n    Point3 operator-(const Point3 a) const {return Point3(*this) -= a;\
    \ }\n    Point3 operator*(const real k) const {return Point3(*this) *= k; }\n\
    \    Point3 operator/(const real k) const {return Point3(*this) /= k; }\n    Point3\
    \ (real a = 0, real b = 0, real c = 0) : x(a), y(b), z(c) {};\n};\n\ninline real\
    \ dot(Point3 a, Point3 b){ return a.x*b.x + a.y*b.y + a.z*b.z; }\ninline real\
    \ abs(Point3 a){ return sqrt(dot(a, a)); }\ninline Point3 cross(Point3 a, Point3\
    \ b){ return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};  }\n\nistream&\
    \ operator>> (istream& s, Point3& P){\n    s >> P.x >> P.y >> P.z;\n    return\
    \ s;\n}\n\nstruct Plane{\n    real a, b, c, d;\n    Plane(real a, real b, real\
    \ c, real d) : a(a), b(b), c(c), d(d){};\n    Plane(Point3 P, Point3 Q, Point3\
    \ R){\n        auto X = cross(Q-P, R-P);\n        a = X.x, b = X.y, c = X.z;\n\
    \        d = -(P.x*a+P.y*b+P.z*c);\n    }\n};\n\nPoint3 crossPoint(Point3 X, Point3\
    \ Y, Plane P){\n    Y -= X;\n    double t = -(Y.x*P.a+Y.y*P.b+Y.z*P.c)/(X.x*P.a+X.y*P.b+X.z*P.c+P.d);\n\
    \    return X + Y*t;\n}\n"
  code: "using real = double;\nstatic constexpr real EPS = 1e-10;\nstruct Point3 {\n\
    \    real x, y, z;\n    Point3& operator+=(const Point3 a) { x += a.x; y += a.y;\
    \ z += a.z;  return *this; }\n    Point3& operator-=(const Point3 a) { x -= a.x;\
    \ y -= a.y; z -= a.z; return *this; }\n    Point3& operator*=(const real k) {\
    \ x *= k; y *= k; z *= k;  return *this; }\n    Point3& operator/=(const real\
    \ k) { x /= k; y /= k; z /= k; return *this; }\n    Point3 operator+(const Point3\
    \ a) const {return Point3(*this) += a; }\n    Point3 operator-(const Point3 a)\
    \ const {return Point3(*this) -= a; }\n    Point3 operator*(const real k) const\
    \ {return Point3(*this) *= k; }\n    Point3 operator/(const real k) const {return\
    \ Point3(*this) /= k; }\n    Point3 (real a = 0, real b = 0, real c = 0) : x(a),\
    \ y(b), z(c) {};\n};\n\ninline real dot(Point3 a, Point3 b){ return a.x*b.x +\
    \ a.y*b.y + a.z*b.z; }\ninline real abs(Point3 a){ return sqrt(dot(a, a)); }\n\
    inline Point3 cross(Point3 a, Point3 b){ return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z,\
    \ a.x*b.y-a.y*b.x};  }\n\nistream& operator>> (istream& s, Point3& P){\n    s\
    \ >> P.x >> P.y >> P.z;\n    return s;\n}\n\nstruct Plane{\n    real a, b, c,\
    \ d;\n    Plane(real a, real b, real c, real d) : a(a), b(b), c(c), d(d){};\n\
    \    Plane(Point3 P, Point3 Q, Point3 R){\n        auto X = cross(Q-P, R-P);\n\
    \        a = X.x, b = X.y, c = X.z;\n        d = -(P.x*a+P.y*b+P.z*c);\n    }\n\
    };\n\nPoint3 crossPoint(Point3 X, Point3 Y, Plane P){\n    Y -= X;\n    double\
    \ t = -(Y.x*P.a+Y.y*P.b+Y.z*P.c)/(X.x*P.a+X.y*P.b+X.z*P.c+P.d);\n    return X\
    \ + Y*t;\n}"
  dependsOn: []
  isVerificationFile: false
  path: geometry/geometry3d.cpp
  requiredBy: []
  timestamp: '2020-05-19 17:07:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: geometry/geometry3d.cpp
layout: document
redirect_from:
- /library/geometry/geometry3d.cpp
- /library/geometry/geometry3d.cpp.html
title: geometry/geometry3d.cpp
---
