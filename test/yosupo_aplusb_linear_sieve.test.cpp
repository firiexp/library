#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../math/prime/linear_sieve.cpp"
#include "../math/prime/get_min_factor.cpp"
#include "../math/prime/eulerphi_all.cpp"
#include "../math/prime/mobius_all.cpp"

void self_check() {
    const int limit = 4096;
    vector<int> factors(limit + 1), phi(limit + 1), mu(limit + 1);
    factors[1] = phi[1] = mu[1] = 1;
    for (int x = 2; x <= limit; ++x) {
        int rest = x, count = 0;
        bool square = false;
        phi[x] = x;
        for (int p = 2; p <= rest; ++p) if (rest % p == 0) {
            if (factors[x] == 0) factors[x] = p;
            phi[x] -= phi[x] / p;
            rest /= p;
            ++count;
            if (rest % p == 0) square = true;
            while (rest % p == 0) rest /= p;
        }
        mu[x] = square ? 0 : count % 2 ? -1 : 1;
    }
    vector<int> sizes{INT_MIN, -1, 997, 1000, limit};
    for (int n = 0; n <= 128; ++n) sizes.push_back(n);
    for (int input : sizes) {
        int n = max(input, 0);
        vector<int> primes;
        for (int x = 2; x <= n; ++x) if (factors[x] == x) primes.push_back(x);
        for (int options = 0; options < 8; ++options) {
            LinearSieve sieve(input, options & 1, options & 2, options & 4);
            assert(sieve.n == n && sieve.primes == primes);
            assert(sieve.min_factor == (options & 1 ? vector<int>(factors.begin(), factors.begin() + n + 1) : vector<int>{}));
            assert(sieve.phi == (options & 2 ? vector<int>(phi.begin(), phi.begin() + n + 1) : vector<int>{}));
            assert(sieve.mobius == (options & 4 ? vector<int>(mu.begin(), mu.begin() + n + 1) : vector<int>{}));
            if (!(options & 1)) assert(sieve.min_factor.capacity() == 0);
            if (!(options & 2)) assert(sieve.phi.capacity() == 0);
            if (!(options & 4)) assert(sieve.mobius.capacity() == 0);
            if (options & 1) assert(sieve.prime_table.empty() && sieve.prime_table.capacity() == 0);
            else {
                assert(sieve.prime_table.size() == size_t(n + 1));
                for (int x = 0; x <= n; ++x) assert(sieve.prime_table[x] == (x >= 2 && factors[x] == x));
            }
            for (int x = -1; x <= n + 1; ++x) {
                bool prime = x >= 2 && x <= n && factors[x] == x;
                assert(sieve.is_prime(x) == prime);
            }
        }
        assert(get_min_factor(input) == vector<int>(factors.begin(), factors.begin() + n + 1));
        assert(eulerphi_all(n + 1) == vector<int>(phi.begin(), phi.begin() + n + 1));
        assert(mobius_all(n + 1) == vector<int>(mu.begin(), mu.begin() + n + 1));
    }
    assert(eulerphi_all(0).empty() && eulerphi_all(-1).empty());
    assert(mobius_all(0).empty() && mobius_all(-1).empty());
}

int main() {
    self_check();
}
