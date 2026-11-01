#ifndef FIRIEXP_LIBRARY_GEOMETRY_SEGMENT_INTERSECTION_CPP
#define FIRIEXP_LIBRARY_GEOMETRY_SEGMENT_INTERSECTION_CPP

#include "int_point.cpp"

bool segments_intersect(IntPoint a, IntPoint b, IntPoint c, IntPoint d) {
    if (max(a.x, b.x) < min(c.x, d.x) || max(c.x, d.x) < min(a.x, b.x) ||
        max(a.y, b.y) < min(c.y, d.y) || max(c.y, d.y) < min(a.y, b.y)) return false;
    auto opposite = [](__int128 x, __int128 y) {
        return x == 0 || y == 0 || (x < 0) != (y < 0);
    };
    return opposite(IntPoint::cross(a, b, c), IntPoint::cross(a, b, d)) &&
           opposite(IntPoint::cross(c, d, a), IntPoint::cross(c, d, b));
}

#endif

/**
 * @brief 整数座標の線分交差判定
 */
