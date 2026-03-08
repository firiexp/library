#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <cmath>
#include <limits>
#include <random>
using namespace std;
using ull = unsigned long long;

#include "../util/fastio.cpp"
#include "../math/isqrt.cpp"

bool check_isqrt(ull x) {
    ull y = Isqrt(x);
    __uint128_t yy = (__uint128_t)y * y;
    __uint128_t zz = (__uint128_t)(y + 1) * (y + 1);
    return yy <= x && x < zz;
}

int main() {
    {
        vector<ull> xs = {
            0, 1, 2, 3, 4, 7, 8, 9, 10,
            (1ULL << 32) - 1,
            1ULL << 32,
            (1ULL << 32) + 1,
            4294967295ULL * 4294967295ULL,
            numeric_limits<ull>::max() - 1,
            numeric_limits<ull>::max()
        };
        for (ull x : xs) {
            if (!check_isqrt(x)) return 1;
        }

        for (ull y : {0ULL, 1ULL, 2ULL, 3ULL, 10ULL, 1000ULL, 65535ULL, 123456789ULL, 4294967295ULL}) {
            ull sq = y * y;
            if (!check_isqrt(sq)) return 1;
            if (sq > 0 && !check_isqrt(sq - 1)) return 1;
            if (sq != numeric_limits<ull>::max() && !check_isqrt(sq + 1)) return 1;
        }

        mt19937_64 rng(123456789);
        for (int trial = 0; trial < 200000; ++trial) {
            ull x = rng();
            if (!check_isqrt(x)) return 1;
        }
    }

    Scanner sc;
    Printer pr;
    int t;
    sc.read(t);
    while (t--) {
        long long a, b;
        sc.read(a, b);
        pr.writeln(a + b);
    }
    return 0;
}
