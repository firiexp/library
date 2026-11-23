#include "int_point.cpp"

namespace closest_pair_detail {
inline long long square_difference(int a, int b) {
    long long d = (long long)a - b;
    return d * d;
}

inline __uint128_t square_difference(long long a, long long b) {
    uint64_t d = a < b ? uint64_t(b) - uint64_t(a) : uint64_t(a) - uint64_t(b);
    return __uint128_t(d) * d;
}

inline long long sum_squares(long long x, long long y) {
    return x + y;
}

inline pair<bool, __uint128_t> sum_squares(__uint128_t x, __uint128_t y) {
    __uint128_t low = x + y;
    return {low < x, low};
}

template<class Coord>
pair<int, int> solve(const vector<IntPoint> &points, IntPoint origin) {
    struct Point {
        Coord x, y;
        int index;
    };
    int n = points.size();
    vector<Point> ps;
    ps.reserve(n);
    for (int i = 0; i < n; ++i) {
        ps.push_back({Coord(points[i].x - origin.x), Coord(points[i].y - origin.y), i});
    }
    sort(ps.begin(), ps.end(), [](const Point &a, const Point &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    });
    for (int i = 1; i < n; ++i) {
        if (ps[i - 1].x == ps[i].x && ps[i - 1].y == ps[i].y) {
            return {ps[i - 1].index, ps[i].index};
        }
    }

    auto distance = [](const Point &a, const Point &b) {
        return sum_squares(square_difference(a.x, b.x), square_difference(a.y, b.y));
    };
    auto best = distance(ps[0], ps[1]);
    pair<int, int> answer{ps[0].index, ps[1].index};
    auto update = [&](const Point &a, const Point &b) {
        auto d = distance(a, b);
        if (d < best) {
            best = d;
            answer = {a.index, b.index};
        }
    };

    auto by_y = [](const Point &a, const Point &b) { return a.y < b.y; };
    if (is_sorted(ps.begin(), ps.end(), by_y) || is_sorted(ps.rbegin(), ps.rend(), by_y)) {
        for (int i = 2; i < n; ++i) update(ps[i - 1], ps[i]);
        return answer;
    }

    vector<Point> scratch(n);
    auto dfs = [&](auto &&self, int l, int r) -> void {
        if (r - l <= 8) {
            for (int i = l; i < r; ++i) {
                for (int j = i + 1; j < r; ++j) update(ps[i], ps[j]);
            }
            sort(ps.begin() + l, ps.begin() + r, by_y);
            return;
        }
        int m = l + (r - l) / 2;
        Coord mid_x = ps[m].x;
        self(self, l, m);
        self(self, m, r);
        merge(ps.begin() + l, ps.begin() + m, ps.begin() + m, ps.begin() + r, scratch.begin(), by_y);
        copy_n(scratch.begin(), r - l, ps.begin() + l);
        int count = 0;
        for (int i = l; i < r; ++i) {
            if (sum_squares(square_difference(ps[i].x, mid_x), 0) >= best) continue;
            for (int j = count - 1; j >= 0; --j) {
                if (sum_squares(square_difference(ps[i].y, scratch[j].y), 0) >= best) break;
                update(ps[i], scratch[j]);
            }
            scratch[count++] = ps[i];
        }
    };
    dfs(dfs, 0, n);
    return answer;
}
}

pair<int, int> closest_pair(const vector<IntPoint> &points) {
    assert(points.size() >= 2);
    if (points.size() == 2) return {0, 1};
    IntPoint lo = points[0], hi = points[0];
    for (const auto &p : points) {
        lo.x = min(lo.x, p.x);
        lo.y = min(lo.y, p.y);
        hi.x = max(hi.x, p.x);
        hi.y = max(hi.y, p.y);
    }
    if (__int128_t(hi.x) - lo.x <= INT32_MAX && __int128_t(hi.y) - lo.y <= INT32_MAX) {
        return closest_pair_detail::solve<int>(points, lo);
    }
    return closest_pair_detail::solve<long long>(points, {0, 0});
}

/**
 * @brief Closest Pair
 */
