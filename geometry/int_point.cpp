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

inline long long cross_ll(IntPoint a, IntPoint b, IntPoint c) {
    long long bx = b.x - a.x, by = b.y - a.y;
    long long cx = c.x - a.x, cy = c.y - a.y;
    return bx * cy - by * cx;
}

inline __int128 cross_i128(IntPoint a, IntPoint b, IntPoint c) {
    __int128 bx = __int128(b.x) - a.x, by = __int128(b.y) - a.y;
    __int128 cx = __int128(c.x) - a.x, cy = __int128(c.y) - a.y;
    return bx * cy - by * cx;
}

#endif

/**
 * @brief 整数座標点
 */
