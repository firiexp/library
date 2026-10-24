#include "int_point.cpp"

struct MinimumEnclosingCircleResult {
    struct Center {
        long double x, y;
    };
    Center center;
    long double radius;
    vector<int> boundary_indices;
};

namespace minimum_enclosing_circle_detail {
using Wide = __int128_t;

inline Wide cross(const IntPoint &a, const IntPoint &b, const IntPoint &c) {
    return (Wide(b.x) - a.x) * (Wide(c.y) - a.y)
        - (Wide(b.y) - a.y) * (Wide(c.x) - a.x);
}

struct Disk {
    int size = 0;
    IntPoint a, b, c;

    int side(const IntPoint &p) const {
        if (!size) return 1;
        Wide x = Wide(p.x) - a.x, y = Wide(p.y) - a.y;
        Wide value = x * x + y * y;
        if (size == 2) {
            value = x * (Wide(p.x) - b.x) + y * (Wide(p.y) - b.y);
        } else if (size == 3) {
            Wide ux = Wide(b.x) - a.x, uy = Wide(b.y) - a.y;
            Wide vx = Wide(c.x) - a.x, vy = Wide(c.y) - a.y;
            value = (ux * ux + uy * uy) * (vx * y - vy * x)
                - (vx * vx + vy * vy) * (ux * y - uy * x)
                + value * (ux * vy - uy * vx);
        }
        return (value > 0) - (value < 0);
    }
};

inline Disk through_three(IntPoint a, IntPoint b, IntPoint c) {
    Wide orientation = cross(a, b, c);
    if (orientation == 0) {
        if (b < a) swap(a, b);
        if (c < a) swap(a, c);
        if (b < c) swap(b, c);
        return {2, a, b, {}};
    }
    if (orientation < 0) swap(b, c);
    return {3, a, b, c};
}
}

optional<MinimumEnclosingCircleResult> minimum_enclosing_circle(
    const vector<IntPoint> &points, uint64_t seed = random_device{}()) {
    using namespace minimum_enclosing_circle_detail;
    int n = points.size();
    if (n == 0) return nullopt;
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    mt19937_64 rng(seed);
    shuffle(order.begin(), order.end(), rng);
    Disk disk;
    for (int i = 0; i < n; ++i) {
        const auto &a = points[order[i]];
        if (disk.side(a) <= 0) continue;
        disk = {1, a, {}, {}};
        for (int j = 0; j < i; ++j) {
            const auto &b = points[order[j]];
            if (disk.side(b) <= 0) continue;
            disk = {2, a, b, {}};
            for (int k = 0; k < j; ++k) {
                const auto &c = points[order[k]];
                if (disk.side(c) > 0) disk = through_three(a, b, c);
            }
        }
    }
    long double x = 0, y = 0;
    if (disk.size == 2) {
        x = (Wide(disk.b.x) - disk.a.x) / 2.0L;
        y = (Wide(disk.b.y) - disk.a.y) / 2.0L;
    } else if (disk.size == 3) {
        Wide ux = Wide(disk.b.x) - disk.a.x, uy = Wide(disk.b.y) - disk.a.y;
        Wide vx = Wide(disk.c.x) - disk.a.x, vy = Wide(disk.c.y) - disk.a.y;
        Wide u2 = ux * ux + uy * uy, v2 = vx * vx + vy * vy;
        long double denominator = 2 * (ux * vy - uy * vx);
        x = (u2 * vy - v2 * uy) / denominator;
        y = (v2 * ux - u2 * vx) / denominator;
    }
    MinimumEnclosingCircleResult result{{disk.a.x + x, disk.a.y + y}, hypotl(x, y), {}};
    for (int i = 0; i < n; ++i) {
        if (disk.side(points[i]) == 0) result.boundary_indices.push_back(i);
    }
    return result;
}

/**
 * @brief 最小包含円
 */
