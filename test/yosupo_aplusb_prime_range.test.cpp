#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/prime/primefactor_ll.cpp"

ull power(ull a, ull k, ull n) {
    ull result = 1;
    for (; k; k >>= 1, a = (__uint128_t)a * a % n)
        if (k & 1) result = (__uint128_t)result * a % n;
    return result;
}

bool reference(ull n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    ull d = n - 1;
    int s = 0;
    while (d % 2 == 0) d /= 2, ++s;
    for (ull a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (a % n == 0) continue;
        ull x = power(a % n, d, n);
        if (x == 1 || x == n - 1) continue;
        bool passed = false;
        for (int i = 1; i < s; ++i) {
            x = (__uint128_t)x * x % n;
            if (x == n - 1) { passed = true; break; }
        }
        if (!passed) return false;
    }
    return true;
}

void check_factor(ull n) {
    auto factors = prime_factor(n);
    assert(is_sorted(factors.begin(), factors.end()));
    __uint128_t product = 1;
    for (ull p : factors) {
        assert(reference(p));
        product *= p;
    }
    assert(product == n);
    assert(prime_factor((long long)n) == vector<long long>(factors.begin(), factors.end()));
    if (n >= 4 && !reference(n)) {
        ull factor = pollard_rho2(n);
        assert(1 < factor && factor < n && n % factor == 0);
    }
}

void self_check() {
    for (long long n : {LLONG_MIN, -100LL, -1LL, 0LL, 1LL}) assert(!miller_rabin(n));
    for (int n = 0; n <= 10000; ++n) {
        bool prime = n >= 2;
        for (int p = 2; p * p <= n; ++p) if (n % p == 0) prime = false;
        assert(miller_rabin(n) == prime);
        assert(reference(n) == prime);
    }
    for (ull n = LLONG_MAX - 64; n <= (ull)LLONG_MAX; ++n) {
        assert(miller_rabin(n) == reference(n));
        assert(miller_rabin((long long)n) == reference(n));
    }
    for (ull n : {1ULL, 2ULL, 3ULL, 4ULL, 9ULL, 25ULL, 561ULL, 3215031751ULL,
                  1ULL << 62, 3037000493ULL * 3037000493ULL,
                  (ull)LLONG_MAX - 24, (ull)LLONG_MAX}) check_factor(n);
    mt19937_64 random(9);
    for (int i = 0; i < 1000; ++i) {
        ull n = random() >> 1;
        assert(miller_rabin(n) == reference(n));
        if (i < 20) check_factor(max(1ULL, n));
        if (i < 100) check_factor(1 + random() % 1000000000000ULL);
    }
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
