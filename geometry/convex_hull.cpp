#ifndef FIRIEXP_LIBRARY_GEOMETRY_CONVEX_HULL_CPP
#define FIRIEXP_LIBRARY_GEOMETRY_CONVEX_HULL_CPP

#include "int_point.cpp"

__int128 cross(IntPoint a, IntPoint b, IntPoint c) {
    __int128 bx = static_cast<__int128>(b.x) - a.x;
    __int128 by = static_cast<__int128>(b.y) - a.y;
    __int128 cx = static_cast<__int128>(c.x) - a.x;
    __int128 cy = static_cast<__int128>(c.y) - a.y;
    return bx * cy - by * cx;
}

vector<IntPoint> convex_hull(vector<IntPoint> ps) {
    sort(ps.begin(), ps.end());
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    int n = ps.size();
    if (n <= 2) return ps;

    vector<IntPoint> ch(2 * n);
    int k = 0;
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;
        ch[k++] = ps[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; --i) {
        while (k >= t && cross(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;
        ch[k++] = ps[i];
    }
    ch.resize(k - 1);
    return ch;
}

int contains_convex(const vector<IntPoint> &hull, IntPoint p) {
    int n = hull.size();
    if (n == 0) return 0;
    if (n == 1) return hull[0] == p ? 1 : 0;
    auto on_segment = [&](IntPoint a, IntPoint b) {
        return cross(a, b, p) == 0 &&
               min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
               min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
    };
    if (n == 2) return on_segment(hull[0], hull[1]) ? 1 : 0;
    __int128 left = cross(hull[0], hull[1], p);
    __int128 right = cross(hull[0], hull[n - 1], p);
    if (left < 0 || right > 0) return 0;
    if (left == 0) return on_segment(hull[0], hull[1]) ? 1 : 0;
    if (right == 0) return on_segment(hull[0], hull[n - 1]) ? 1 : 0;
    int l = 1, r = n - 1;
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (cross(hull[0], hull[m], p) >= 0) l = m;
        else r = m;
    }
    __int128 side = cross(hull[l], hull[r], p);
    return side < 0 ? 0 : side == 0 ? 1 : 2;
}

#endif

/**
 * @brief 凸包(Convex Hull)
 */
