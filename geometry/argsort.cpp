#include "int_point.cpp"

namespace geometry_argsort_detail {
template <class Wide, class T>
int compare(T ax, T ay, T bx, T by) {
    auto half = [](T x, T y) { return y ? (y < 0 ? -1 : 1) : int(x < 0); };
    int a = half(ax, ay), b = half(bx, by);
    if (a != b) return a < b ? -1 : 1;
    Wide lhs = Wide(ax) * by, rhs = Wide(ay) * bx;
    return lhs > rhs ? -1 : lhs < rhs ? 1 : 0;
}
}

using Ar2 = array<int, 2>;

void argsort(vector<Ar2> &v) {
    sort(v.begin(), v.end(), [](const Ar2 &a, const Ar2 &b) {
        return geometry_argsort_detail::compare<long long>(a[0], a[1], b[0], b[1]) < 0;
    });
}

void argsort(vector<IntPoint> &v) {
    sort(v.begin(), v.end(), [](const IntPoint &a, const IntPoint &b) {
        return geometry_argsort_detail::compare<__int128>(a.x, a.y, b.x, b.y) < 0;
    });
}

vector<int> arg_sort_indices(const vector<IntPoint> &v) {
    vector<int> order(v.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) {
        int c = geometry_argsort_detail::compare<__int128>(v[i].x, v[i].y, v[j].x, v[j].y);
        return c < 0 || (c == 0 && i < j);
    });
    return order;
}

/**
 * @brief 偏角ソート(Argument Sort)
 */
