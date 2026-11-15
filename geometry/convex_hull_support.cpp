#include "int_point.cpp"

class ConvexHullSupport {
    struct Direction {
        __int128 x, y;
    };

    vector<IntPoint> hull;
    int first = 0;

    static bool angle_less(Direction a, Direction b) {
        bool lower_a = a.y < 0 || (a.y == 0 && a.x < 0);
        bool lower_b = b.y < 0 || (b.y == 0 && b.x < 0);
        if (lower_a != lower_b) return lower_a < lower_b;
        return a.x * b.y - a.y * b.x > 0;
    }

    Direction edge(int i) const {
        int j = i + 1 == (int)hull.size() ? 0 : i + 1;
        return {__int128(hull[j].x) - hull[i].x, __int128(hull[j].y) - hull[i].y};
    }

    __int128 dot(int i, IntPoint direction) const {
        return __int128(hull[i].x) * direction.x + __int128(hull[i].y) * direction.y;
    }

public:
    explicit ConvexHullSupport(vector<IntPoint> polygon) : hull(move(polygon)) {
        if (hull.size() <= 2) return;
        for (int i = 1; i < (int)hull.size(); ++i)
            if (angle_less(edge(i), edge(first))) first = i;
    }

    optional<pair<__int128, int>> max_dot(IntPoint direction) const {
        int n = (int)hull.size();
        if (n == 0) return nullopt;
        if (direction.x == 0 && direction.y == 0) return make_pair(__int128(0), 0);
        if (n <= 2) {
            int i = n == 2 && dot(1, direction) > dot(0, direction) ? 1 : 0;
            return make_pair(dot(i, direction), i);
        }
        Direction target{-__int128(direction.y), __int128(direction.x)};
        int l = 0, r = n;
        while (l < r) {
            int m = l + (r - l) / 2;
            int i = first + m;
            if (i >= n) i -= n;
            if (angle_less(edge(i), target)) l = m + 1;
            else r = m;
        }
        int i = first + l;
        if (i >= n) i -= n;
        return make_pair(dot(i, direction), i);
    }
};

/**
 * @brief 凸多角形の最大内積
 */
