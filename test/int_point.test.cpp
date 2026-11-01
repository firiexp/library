#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../geometry/int_point.cpp"

static_assert(is_same_v<decltype(cross_i128({}, {}, {})), __int128>);
static_assert(is_same_v<decltype(cross_ll({}, {}, {})), long long>);

int main() {
    const IntPoint a{1, 1}, b{3, 1}, c{1, 4};
    assert(cross_ll(a, b, c) == 6);
    assert(cross_ll(a, c, b) == -6);
    assert(cross_ll(a, a, c) == 0);
    assert(cross_i128(a, a, c) == 0);
    mt19937_64 rng(306);
    for (int trial = 0; trial < 10000; ++trial) {
        IntPoint p[3];
        for (auto &point : p) {
            point.x = static_cast<long long>(rng() % 2000000001) - 1000000000;
            point.y = static_cast<long long>(rng() % 2000000001) - 1000000000;
        }
        __int128 expected = __int128(p[0].x) * (p[1].y - p[2].y) +
                            __int128(p[1].x) * (p[2].y - p[0].y) +
                            __int128(p[2].x) * (p[0].y - p[1].y);
        assert(cross_i128(p[0], p[1], p[2]) == expected);
        assert(cross_ll(p[0], p[1], p[2]) == expected);
    }
    const long long m = 1000000000000000000LL;
    assert(cross_i128({-m, -m}, {m, -m}, {-m, m}) == __int128(4) * m * m);
    assert(cross_i128({-m, -m}, {-m, m}, {m, -m}) == -__int128(4) * m * m);
}
