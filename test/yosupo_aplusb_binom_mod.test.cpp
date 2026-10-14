#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/binom_mod.cpp"
#include "../math/binom_mod.cpp"

int main() {
    vector<int> moduli;
    for (int m = 1; m <= 500; ++m) moduli.push_back(m);
    for (int m : {1024, 6561, 65536, 510510, 531441, 999983, 1000000}) moduli.push_back(m);
    for (int m : moduli) {
        const BinomMod binom(m);
        assert(binom.modulus() == m);
        vector<ll> row(102);
        row[0] = 1 % m;
        for (int n = 0; n <= 100; ++n) {
            assert(binom.C(n, -1) == 0);
            assert(binom.C(n, n + 1) == 0);
            for (int k = 0; k <= n; ++k) assert(binom.C(n, k) == row[k]);
            for (int k = n + 1; k > 0; --k) row[k] = (row[k] + row[k - 1]) % m;
        }
        for (ll n : {1000000000000000000LL, 999999999999999999LL}) {
            assert(binom.C(n, 0) == 1 % m);
            assert(binom.C(n, n) == 1 % m);
            assert(binom.C(n, 1) == n % m);
            assert(binom.C(n, n - 1) == n % m);
            ll pairs = (__int128)n * (n - 1) / 2 % m;
            assert(binom.C(n, 2) == pairs);
            assert(binom.C(n, n - 2) == pairs);
            for (ll k : {37, 100, 10000}) {
                assert(binom.C(n, k) == binom.C(n, n - k));
                assert(binom.C(n, k) == (binom.C(n - 1, k - 1) + binom.C(n - 1, k)) % m);
            }
        }
    }
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
