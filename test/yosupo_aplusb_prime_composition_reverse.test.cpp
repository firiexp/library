#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using uint = unsigned;

const vector<int> primes{2, 3, 5, 7};

#include "../math/prime/primefactor_ll.cpp"
#include "../math/prime/primefactor_ll.cpp"
#include "../math/prime/miller_rabin.cpp"
#include "../math/prime/primefactor.cpp"
#include "../math/convolution/gcd_transform.cpp"
#include "../math/prime/get_prime2.cpp"
#include "../math/prime/get_prime2.cpp"
#include "../math/prime/linear_sieve.cpp"
#include "../math/prime/get_prime.cpp"

int main() {
    assert(get_prime(10) == primes);
    auto divisors = get_prime_exact_div(10);
    assert(divisors.size() == primes.size());
    for (size_t i = 0; i < primes.size(); ++i) {
        assert(divisors[i].val == (uint)primes[i]);
        assert(divisors[i].divide(21) == (21 % primes[i] == 0));
    }
    assert(prime_factor(1).empty());
    assert(prime_factor_trial(1).empty());
    for (int n = 2; n <= 1000; ++n) {
        assert(prime_factor_trial(n) == prime_factor(n));
    }
    assert(prime_factor(1000000007LL * 1000000009LL)
           == vector<long long>({1000000007LL, 1000000009LL}));
    vector<int> multiples{0, 1, 2, 3, 4};
    gcd_transform(multiples);
    assert(multiples == vector<int>({0, 10, 6, 3, 4}));
    gcd_itransform(multiples);
    assert(multiples == vector<int>({0, 1, 2, 3, 4}));
}
