#ifndef FIRIEXP_LIBRARY_GEOMETRY_INT_POINT_CPP
#define FIRIEXP_LIBRARY_GEOMETRY_INT_POINT_CPP

struct IntPoint {
    long long x = 0, y = 0;

    IntPoint() = default;
    IntPoint(long long x, long long y) : x(x), y(y) {}

    bool operator<(const IntPoint &p) const { return x < p.x || (!(p.x < x) && y < p.y); }
    bool operator==(const IntPoint &p) const { return x == p.x && y == p.y; }
    bool operator!=(const IntPoint &p) const { return !(*this == p); }
    IntPoint &operator+=(const IntPoint &p) { x += p.x; y += p.y; return *this; }
    IntPoint &operator-=(const IntPoint &p) { x -= p.x; y -= p.y; return *this; }
    IntPoint operator+(const IntPoint &p) const { return IntPoint(*this) += p; }
    IntPoint operator-(const IntPoint &p) const { return IntPoint(*this) -= p; }

    template<class T = __int128>
    static T cross(IntPoint a, IntPoint b, IntPoint c) {
        T bx = T(b.x) - T(a.x), by = T(b.y) - T(a.y);
        T cx = T(c.x) - T(a.x), cy = T(c.y) - T(a.y);
        return bx * cy - by * cx;
    }
};

#endif

/**
 * @brief 整数座標点
 */
