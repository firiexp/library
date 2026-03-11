using Real3 = double;
static constexpr Real3 EPS3 = 1e-10;

struct Point3 {
    Real3 x, y, z;

    Point3 &operator+=(const Point3 &a) {
        x += a.x;
        y += a.y;
        z += a.z;
        return *this;
    }

    Point3 &operator-=(const Point3 &a) {
        x -= a.x;
        y -= a.y;
        z -= a.z;
        return *this;
    }

    Point3 &operator*=(Real3 k) {
        x *= k;
        y *= k;
        z *= k;
        return *this;
    }

    Point3 &operator/=(Real3 k) {
        x /= k;
        y /= k;
        z /= k;
        return *this;
    }

    Point3 operator+(const Point3 &a) const { return Point3(*this) += a; }
    Point3 operator-(const Point3 &a) const { return Point3(*this) -= a; }
    Point3 operator*(Real3 k) const { return Point3(*this) *= k; }
    Point3 operator/(Real3 k) const { return Point3(*this) /= k; }

    Point3(Real3 x = 0, Real3 y = 0, Real3 z = 0) : x(x), y(y), z(z) {}
};

inline Real3 dot(Point3 a, Point3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Real3 norm(Point3 a) {
    return dot(a, a);
}

inline Real3 abs(Point3 a) {
    return std::sqrt(norm(a));
}

inline Point3 cross(Point3 a, Point3 b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x,
    };
}

std::istream &operator>>(std::istream &s, Point3 &p) {
    s >> p.x >> p.y >> p.z;
    return s;
}

struct Plane {
    Real3 a, b, c, d;

    Plane(Real3 a, Real3 b, Real3 c, Real3 d) : a(a), b(b), c(c), d(d) {}

    Plane(Point3 p, Point3 q, Point3 r) {
        Point3 n = cross(q - p, r - p);
        a = n.x;
        b = n.y;
        c = n.z;
        d = -dot(n, p);
    }
};

inline Real3 eval(Plane p, Point3 x) {
    return p.a * x.x + p.b * x.y + p.c * x.z + p.d;
}

inline Point3 crossPoint(Point3 s, Point3 t, Plane p) {
    Point3 dir = t - s;
    Real3 den = p.a * dir.x + p.b * dir.y + p.c * dir.z;
    Real3 num = eval(p, s);
    return s - dir * (num / den);
}

/**
 * @brief 3次元幾何(Geometry 3D)
 */
