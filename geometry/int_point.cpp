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
};

__int128 cross(IntPoint a, IntPoint b, IntPoint c) {
    __int128 bx = static_cast<__int128>(b.x) - a.x;
    __int128 by = static_cast<__int128>(b.y) - a.y;
    __int128 cx = static_cast<__int128>(c.x) - a.x;
    __int128 cy = static_cast<__int128>(c.y) - a.y;
    return bx * cy - by * cx;
}

#endif

/**
 * @brief 整数座標点
 */
