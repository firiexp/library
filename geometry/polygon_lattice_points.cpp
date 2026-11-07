#ifndef FIRIEXP_LIBRARY_GEOMETRY_POLYGON_LATTICE_POINTS_CPP
#define FIRIEXP_LIBRARY_GEOMETRY_POLYGON_LATTICE_POINTS_CPP

#include "int_point.cpp"

struct LatticePointCount {
    long long interior, boundary;
};

LatticePointCount polygon_lattice_points(const vector<IntPoint> &polygon) {
    assert(polygon.size() >= 3);
    __int128 area2 = 0, boundary = 0;
    int n = polygon.size();
    for (int i = 0; i < n; ++i) {
        auto a = polygon[i], b = polygon[(i + 1) % n];
        area2 += __int128(a.x) * b.y - __int128(a.y) * b.x;
        __int128 dx = __int128(b.x) - a.x, dy = __int128(b.y) - a.y;
        if (dx < 0) dx = -dx;
        if (dy < 0) dy = -dy;
        while (dy != 0) {
            __int128 remainder = dx % dy;
            dx = dy;
            dy = remainder;
        }
        boundary += dx;
    }
    assert(area2 != 0);
    if (area2 < 0) area2 = -area2;
    __int128 interior = (area2 - boundary + 2) / 2;
    assert(interior <= LLONG_MAX && boundary <= LLONG_MAX);
    return {static_cast<long long>(interior), static_cast<long long>(boundary)};
}

#endif

/**
 * @brief 多角形の格子点数
 */
