#include "convex_hull.cpp"

pair<int, int> furthest_pair(const vector<pair<long long, long long>> &points) {
    assert(points.size() >= 2);
    auto hull = convex_hull(points);
    int n = hull.size();
    if (n == 1) return {0, 1};
    auto distance_squared = [&](int i, int j) {
        __int128 dx = static_cast<__int128>(hull[i].first) - hull[j].first;
        __int128 dy = static_cast<__int128>(hull[i].second) - hull[j].second;
        return dx * dx + dy * dy;
    };
    pair<int, int> best = {0, 1};
    __int128 best_distance = distance_squared(0, 1);
    auto update = [&](int i, int j) {
        __int128 d = distance_squared(i, j);
        if (d > best_distance) {
            best_distance = d;
            best = {i, j};
        }
    };
    if (n > 2) {
        int j = 1;
        for (int i = 0; i < n; ++i) {
            int next_i = (i + 1) % n;
            auto height = [&](int v) { return cross(hull[i], hull[next_i], hull[v]); };
            while (height((j + 1) % n) > height(j)) j = (j + 1) % n;
            update(i, j);
            update(next_i, j);
            int next_j = (j + 1) % n;
            if (height(next_j) == height(j)) {
                update(i, next_j);
                update(next_i, next_j);
            }
        }
    }
    pair<int, int> result = {-1, -1};
    for (int i = 0; i < int(points.size()); ++i) {
        if (points[i] == hull[best.first]) result.first = i;
        if (points[i] == hull[best.second]) result.second = i;
        if (result.first != -1 && result.second != -1) break;
    }
    return result;
}

/**
 * @brief 最遠点対
 */
