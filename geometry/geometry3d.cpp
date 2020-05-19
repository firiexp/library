using real = double;
static constexpr real EPS = 1e-10;
struct Point3 {
    real x, y, z;
    Point3& operator+=(const Point3 a) { x += a.x; y += a.y; z += a.z;  return *this; }
    Point3& operator-=(const Point3 a) { x -= a.x; y -= a.y; z -= a.z; return *this; }
    Point3& operator*=(const real k) { x *= k; y *= k; z *= k;  return *this; }
    Point3& operator/=(const real k) { x /= k; y /= k; z /= k; return *this; }
    Point3 operator+(const Point3 a) const {return Point3(*this) += a; }
    Point3 operator-(const Point3 a) const {return Point3(*this) -= a; }
    Point3 operator*(const real k) const {return Point3(*this) *= k; }
    Point3 operator/(const real k) const {return Point3(*this) /= k; }
    Point3 (real a = 0, real b = 0, real c = 0) : x(a), y(b), z(c) {};
};

inline real dot(Point3 a, Point3 b){ return a.x*b.x + a.y*b.y + a.z*b.z; }
inline real abs(Point3 a){ return sqrt(dot(a, a)); }
inline Point3 cross(Point3 a, Point3 b){ return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};  }

istream& operator>> (istream& s, Point3& P){
    s >> P.x >> P.y >> P.z;
    return s;
}

struct Plane{
    real a, b, c, d;
    Plane(real a, real b, real c, real d) : a(a), b(b), c(c), d(d){};
    Plane(Point3 P, Point3 Q, Point3 R){
        auto X = cross(Q-P, R-P);
        a = X.x, b = X.y, c = X.z;
        d = -(P.x*a+P.y*b+P.z*c);
    }
};

Point3 crossPoint(Point3 X, Point3 Y, Plane P){
    Y -= X;
    double t = -(Y.x*P.a+Y.y*P.b+Y.z*P.c)/(X.x*P.a+X.y*P.b+X.z*P.c+P.d);
    return X + Y*t;
}