#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using uint = unsigned;

#include "../math/prime/primefactor_ll.cpp"
#include "../math/prime/primefactor.cpp"
#include "../math/convolution/gcd_transform.cpp"
#include "../math/prime/get_prime2.cpp"
#include "../math/prime/get_prime.cpp"

int main() {
    assert(get_prime(10) == vector<int>({2, 3, 5, 7}));
    assert(get_prime_exact_div(10).size() == 4);
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
