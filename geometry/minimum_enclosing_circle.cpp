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

struct Disk {
    int size = 0;
    IntPoint a, b, c;
    Wide quadratic = 1, linear_x = 0, linear_y = 0;

    Disk() = default;

    Disk(int size, IntPoint a, IntPoint b, IntPoint c) : size(size), a(a), b(b), c(c) {
        if (size != 3) return;
        Wide ux = Wide(b.x) - a.x, uy = Wide(b.y) - a.y;
        Wide vx = Wide(c.x) - a.x, vy = Wide(c.y) - a.y;
        Wide u2 = ux * ux + uy * uy, v2 = vx * vx + vy * vy;
        quadratic = ux * vy - uy * vx;
        linear_x = v2 * uy - u2 * vy;
        linear_y = u2 * vx - v2 * ux;
    }

    int side(const IntPoint &p) const {
        if (!size) return 1;
        long long x = p.x - a.x, y = p.y - a.y;
        Wide value = Wide(x) * x + Wide(y) * y;
        if (size == 2) {
            value = Wide(x) * (p.x - b.x) + Wide(y) * (p.y - b.y);
        } else if (size == 3) {
            value = quadratic * value + linear_x * x + linear_y * y;
        }
        return (value > 0) - (value < 0);
    }
};

inline Disk through_three(IntPoint a, IntPoint b, IntPoint c) {
    Wide orientation = cross_i128(a, b, c);
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
        disk.size = 1;
        disk.a = a;
        for (int j = 0; j < i; ++j) {
            const auto &b = points[order[j]];
            if (disk.side(b) <= 0) continue;
            disk.size = 2;
            disk.a = a;
            disk.b = b;
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
        long double denominator = 2 * disk.quadratic;
        x = -disk.linear_x / denominator;
        y = -disk.linear_y / denominator;
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
