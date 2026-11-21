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
                auto [big_phi_x, big_mobius_x] = sums.get_big(x);
                assert(big_phi_x == phi[x] && big_mobius_x == mobius[x]);
            };
            for (int x = 0; x <= b; ++x) check(x);
            for (int i = 1; i <= n / (b + 1); ++i) check(n / i);
        }
    }

    const long long n = 10000000000LL;
    TotientMobiusSum sums(2 * n, 1000000);
    static_assert(is_same_v<decltype(sums.get(n)), pair<long long, long long>>);
    static_assert(is_same_v<decltype(sums.get_big(n)), pair<__int128, long long>>);
    auto [phi_n, mobius_n] = sums.get_big(n);
    assert(phi_n == (__int128)3039635509 * n + 2886216366LL);
    assert(mobius_n == -33722);
    auto [phi_half, mobius_half] = sums.get(n / 2);
    auto [big_phi_half, big_mobius_half] = sums.get_big(n / 2);
    assert(big_phi_half > INT_MAX && phi_half == big_phi_half && mobius_half == big_mobius_half);
}
