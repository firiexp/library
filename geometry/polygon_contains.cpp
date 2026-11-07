#ifndef FIRIEXP_LIBRARY_GEOMETRY_POLYGON_CONTAINS_CPP
#define FIRIEXP_LIBRARY_GEOMETRY_POLYGON_CONTAINS_CPP

#include "int_point.cpp"

int contains_polygon(const vector<IntPoint> &polygon, IntPoint p) {
    bool inside = false;
    int n = polygon.size();
    for (int i = 0; i < n; ++i) {
        auto a = polygon[i], b = polygon[(i + 1) % n];
        auto side = cross_i128(a, b, p);
        if (side == 0 && min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
                         min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y)) return 1;
        if ((a.y > p.y) != (b.y > p.y) && (side > 0) == (b.y > a.y))
            inside = !inside;
    }
    return inside ? 2 : 0;
}

#endif

/**
 * @brief 整数多角形の包含判定
 */
