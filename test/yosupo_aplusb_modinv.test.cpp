#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../math/modular/modinv.cpp"

int main() {
    assert(mod_inv(-1LL, 7LL) == 6);
    assert(mod_inv(-4LL, 7LL) == 5);
    assert(mod_inv(1LL, 1LL) == 0);
    for (int m = 1; m <= 100; ++m) {
        for (int x = -2 * m; x <= 2 * m; ++x) {
            if (gcd(x, m) != 1) continue;
            int r = mod_inv(x, m);
            assert(0 <= r && r < m);
            assert((r * x - 1) % m == 0);
        }
    }
    assert(mod_inv(LLONG_MIN, LLONG_MAX) == LLONG_MAX - 1);
    assert(mod_inv(2LL, LLONG_MAX) == LLONG_MAX / 2 + 1);
    assert(mod_inv(ULLONG_MAX - 1, ULLONG_MAX) == ULLONG_MAX - 1);
    assert(mod_inv(2ULL, ULLONG_MAX) == ULLONG_MAX / 2 + 1);
}
