#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_D"

#include <algorithm>
#include <cassert>
#include <climits>
#include <random>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../math/prime/eulerphi.cpp"
#include "../math/prime/divisor.cpp"

void self_check() {
    // Factor using a sieve, then enumerate divisors and apply inclusion-exclusion.
    vector<bool> composite(46341);
    vector<int> primes;
    for (int p = 2; p <= 46340; ++p) {
        if (composite[p]) continue;
        primes.push_back(p);
        for (int k = p + p; k <= 46340; k += p) composite[k] = true;
    }
    vector<int> cases;
    for (int n = 1; n <= 10000; ++n) cases.push_back(n);
    for (int n : {46340 * 46340 - 1, 46340 * 46340, 46340 * 46340 + 1,
                  INT_MAX - 1, INT_MAX}) cases.push_back(n);
    mt19937 rng(71);
    for (int i = 0; i < 64; ++i) cases.push_back(INT_MAX - int(rng() % 100000));
    for (int n : cases) {
        int remaining = n;
        vector<pair<int, int>> factors;
        for (int p : primes) {
            if (1LL * p * p > remaining) break;
            if (remaining % p != 0) continue;
            int exponent = 0;
            do {
                remaining /= p;
                ++exponent;
            } while (remaining % p == 0);
            factors.emplace_back(p, exponent);
        }
        if (remaining > 1) factors.emplace_back(remaining, 1);

        vector<int> expected_divisors{1};
        for (auto [p, exponent] : factors) {
            int size = expected_divisors.size();
            long long power = 1;
            for (int e = 1; e <= exponent; ++e) {
                power *= p;
                for (int i = 0; i < size; ++i) {
                    expected_divisors.push_back(expected_divisors[i] * power);
                }
            }
        }
        sort(expected_divisors.begin(), expected_divisors.end());
        assert(divisor(n) == expected_divisors);
        auto wide_divisors = divisor(static_cast<long long>(n));
        assert(vector<long long>(expected_divisors.begin(), expected_divisors.end()) == wide_divisors);

        long long expected_phi = 0;
        for (int mask = 0; mask < (1 << factors.size()); ++mask) {
            long long product = 1;
            int sign = 1;
            for (int i = 0; i < (int)factors.size(); ++i) {
                if ((mask >> i) & 1) {
                    product *= factors[i].first;
                    sign = -sign;
                }
            }
            expected_phi += sign * (n / product);
        }
        assert(eulerphi(n) == expected_phi);
    }
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;

    int n;
    sc.read(n);
    pr.println(eulerphi(n));
    return 0;
}
