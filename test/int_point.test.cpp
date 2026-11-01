#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../geometry/int_point.cpp"

static_assert(is_same_v<decltype(IntPoint::cross({}, {}, {})), __int128>);
static_assert(is_same_v<decltype(IntPoint::cross<long long>({}, {}, {})), long long>);
static_assert(is_same_v<decltype(IntPoint::cross<int>({}, {}, {})), int>);

int main() {
    const IntPoint a{1, 1}, b{3, 1}, c{1, 4};
    assert(IntPoint::cross<long long>(a, b, c) == 6);
    assert(IntPoint::cross<int>(a, c, b) == -6);
    assert(IntPoint::cross(a, a, c) == 0);
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
        assert(IntPoint::cross(p[0], p[1], p[2]) == expected);
        assert(IntPoint::cross<long long>(p[0], p[1], p[2]) == expected);
    }
    const long long m = 1000000000000000000LL;
    assert(IntPoint::cross({-m, -m}, {m, -m}, {-m, m}) == __int128(4) * m * m);
    assert(IntPoint::cross({-m, -m}, {-m, m}, {m, -m}) == -__int128(4) * m * m);
}
