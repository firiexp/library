#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../math/combinatorics/stirling_second_row.cpp"

int main() {
    const int limit = 180;
    vector<mint> expected(limit + 21);
    expected[0] = 1;
    mt19937 rng(359);
    for (int n = 0; n <= limit; ++n) {
        for (int k : {0, 1, 2, max(0, n - 1), n, n + 1, n + 20, int(rng() % (limit + 1))}) {
            auto actual = stirling_second_row(n, k);
            assert(actual == vector<mint>(expected.begin(), expected.begin() + k + 1));
        }
        for (int k = limit + 20; k >= 1; --k) expected[k] = expected[k] * mint(k) + expected[k - 1];
        expected[0] = 0;
    }
    for (ll n : {1LL, 2LL, 998244352LL, 998244353LL, 998244354LL, LLONG_MAX - 1, LLONG_MAX}) {
        assert(stirling_second_row(n, 0) == vector<mint>({0}));
        auto row = stirling_second_row(n, 20);
        assert(row[0] == mint(0) && row[1] == mint(1));
        assert(row[2] == mint(2).pow(n - 1) - mint(1));
        Factorial<> factorial(20);
        for (int k = 0; k <= 20; ++k) {
            mint sum = 0;
            for (int j = 0; j <= k; ++j) {
                mint term = factorial.C(k, j) * mint(j).pow(n);
                sum += (k - j) % 2 ? -term : term;
            }
            assert(row[k] == sum * factorial.inv_fact(k));
        }
    }
    assert(stirling_second_row(4, 6) == vector<mint>({0, 1, 7, 6, 1, 0, 0}));
}
