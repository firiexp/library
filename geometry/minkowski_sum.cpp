#include "convex_hull.cpp"

vector<IntPoint> minkowski_sum(const vector<IntPoint> &a, const vector<IntPoint> &b) {
    if (a.empty() || b.empty()) return {};
    int n = a.size(), m = b.size();
    int p = min_element(a.begin(), a.end()) - a.begin();
    int q = min_element(b.begin(), b.end()) - b.begin();
    vector<IntPoint> result;
    result.reserve(n + m);
    if (n == 1 || m == 1) {
        for (int k = 0; k < max(n, m); ++k) {
            const auto &u = a[(p + k) % n];
            const auto &v = b[(q + k) % m];
            result.emplace_back(u.x + v.x, u.y + v.y);
        }
        return result;
    }
    for (int i = 0, j = 0; i < n || j < m;) {
        result.emplace_back(a[p].x + b[q].x, a[p].y + b[q].y);
        int next_p = (p + 1) % n, next_q = (q + 1) % m;
        int order;
        if (i == n) order = 1;
        else if (j == m) order = -1;
        else {
            __int128 ax = static_cast<__int128>(a[next_p].x) - a[p].x;
            __int128 ay = static_cast<__int128>(a[next_p].y) - a[p].y;
            __int128 bx = static_cast<__int128>(b[next_q].x) - b[q].x;
            __int128 by = static_cast<__int128>(b[next_q].y) - b[q].y;
            bool half_a = ax < 0 || (ax == 0 && ay < 0);
            bool half_b = bx < 0 || (bx == 0 && by < 0);
            __int128 turn = ax * by - ay * bx;
            order = half_a != half_b ? (half_a ? 1 : -1) : turn > 0 ? -1 : turn < 0 ? 1 : 0;
        }
        if (order <= 0) {
            p = next_p;
            ++i;
        }
        if (order >= 0) {
            q = next_q;
            ++j;
        }
    }
    return result;
}

/**
 * @brief 整数凸多角形のミンコフスキー和
 */
