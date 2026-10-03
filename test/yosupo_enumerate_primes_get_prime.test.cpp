#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/prime/get_prime_wheel.cpp"
#include "../math/prime/get_prime.cpp"
#include "../math/prime/linear_sieve.cpp"

void self_check() {
    vector<bool> sieve(100001, true);
    sieve[0] = sieve[1] = false;
    for (int p = 2; p * p <= 100000; ++p) if (sieve[p])
        for (int x = p * p; x <= 100000; x += p) sieve[x] = false;
    vector<int> expected;
    for (int n = 0; n <= 100000; ++n) {
        if (sieve[n]) expected.push_back(n);
        if (n <= 10000 || n % 30 <= 1 || n % 30 == 29) assert(get_prime(n) == expected);
    }
    assert(get_prime(-1).empty());
    assert(get_prime(INT_MIN).empty());
    assert(LinearSieve(10000).primes == get_prime(10000));
    for (int p = 7; p <= 313; ++p) if (sieve[p]) {
        for (int n = p * p - 1; n <= p * p + 1; ++n) {
            vector<int> prefix;
            for (int x = 2; x <= n; ++x) if (sieve[x]) prefix.push_back(x);
            assert(get_prime(n) == prefix);
        }
    }
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int n, a, b;
    sc.read(n, a, b);
    auto primes = get_prime(n);
    vector<int> picked;
    for (int i = b; i < (int)primes.size(); i += a) picked.push_back(primes[i]);
    pr.println(primes.size(), picked.size());
    pr.println(picked);
}
