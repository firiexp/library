#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../math/prime/totient_mobius_sum.cpp"

int main() {
    const int limit = 1025;
    vector<int> phi(limit + 1), mobius(limit + 1);
    mobius[1] = 1;
    for (int x = 1; x <= limit; ++x) {
        for (int i = 1; i <= x; ++i) phi[x] += gcd(i, x) == 1;
        for (int j = 2 * x; j <= limit; j += x) mobius[j] -= mobius[x];
    }
    partial_sum(phi.begin(), phi.end(), phi.begin());
    partial_sum(mobius.begin(), mobius.end(), mobius.begin());
    for (int n = 0; n <= limit; ++n) {
        int root = (int)sqrt(n);
        for (int b = root; b <= n; ++b) {
            if (n > 100 && b != root && b != root + 1 && b != n) continue;
            TotientMobiusSum sums(n, b);
            auto check = [&](int x) {
                auto [phi_x, mobius_x] = sums.get(x);
                assert(phi_x == phi[x] && mobius_x == mobius[x]);
            };
            for (int x = 0; x <= b; ++x) check(x);
            for (int i = 1; i <= n / (b + 1); ++i) check(n / i);
        }
    }

    const long long n = 10000000000LL;
    TotientMobiusSum sums(n, 1000000);
    auto [phi_n, mobius_n] = sums.get(n);
    assert(phi_n == (__int128)3039635509 * n + 2886216366LL);
    assert(mobius_n == -33722);
}
