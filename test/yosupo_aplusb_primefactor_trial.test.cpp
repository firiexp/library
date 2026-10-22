#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using uint = unsigned;

#include "../math/prime/primefactor.cpp"

vector<uint> trial_factor(uint n) {
    vector<uint> result;
    for (uint p = 2; p <= n / p; ++p) {
        while (n % p == 0) {
            result.push_back(p);
            n /= p;
        }
    }
    if (n != 1) result.push_back(n);
    return result;
}

void check(uint n) {
    const auto expected = trial_factor(n);
    assert(prime_factor(n) == expected);
    assert(prime_factor(static_cast<int>(n)) == vector<int>(expected.begin(), expected.end()));
    assert(prime_factor(static_cast<long long>(n)) == vector<long long>(expected.begin(), expected.end()));
    unsigned long long product = 1;
    for (uint p : expected) product *= p;
    assert(product == n);
}

int main() {
    assert(prime_factor(1).empty());
    for (uint n = 1; n <= 100000; ++n) check(n);
    for (uint n = 1; n <= (1U << 29); n *= 2) check(n);
    for (uint n : {3U, 17U, 30030U, 59049U, 387420489U, 1000000000U, 1000000007U,
                   2U * 499999993U, 31991U * 31991U, 31991U * 31981U, 32000U * 32000U}) {
        check(n);
    }
    mt19937 random(271);
    for (int tc = 0; tc < 3000; ++tc) check(1 + random() % (32000U * 32000U));
}
