#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../fps/ntt.cpp"

void check(poly f, int deg) {
    auto copy = f.v;
    auto g = f.inv(deg);
    assert(g.size() == deg && f.v == copy);
    for (int i = 0; i < deg; ++i) {
        mint sum = 0;
        for (int d = 0; d <= i && d < f.size(); ++d) sum += f[d] * g[i - d];
        assert(sum == mint(i == 0));
    }
    f[0] = 0;
    copy = f.v;
    auto e = f.exp(deg);
    assert(e.size() == deg && f.v == copy);
    if (deg) assert(e[0] == mint(1));
    for (int i = 1; i < deg; ++i) {
        mint sum = 0;
        for (int d = 1; d <= i && d < f.size(); ++d) sum += mint(d) * f[d] * e[i - d];
        assert(mint(i) * e[i] == sum);
    }
}

int main() {
    assert(poly().exp(0).size() == 0);
    assert(poly().exp(8).v == poly(vector<mint>{1}).pre(8).v);
    mt19937 rng(267);
    for (int trial = 0; trial < 600; ++trial) {
        int n = 1 + rng() % 150;
        poly f(n);
        f[0] = 1 + rng() % (ntt_mod - 1);
        for (int k = rng() % 40; k > 0 && n > 1; --k) f[1 + rng() % (n - 1)] = rng() % ntt_mod;
        for (int deg : {0, 1, n / 2, n, n + 37}) check(f, deg);
        assert(f.inv().v == f.inv(n).v);
        f[0] = 0;
        assert(f.exp().v == f.exp(n).v);
    }
    for (int k : {0, 1, 15, 16, 17, 31, 32, 33}) {
        poly f(300);
        f[0] = 3;
        for (int j = 1; j <= k; ++j) f[j * 7] = ntt_mod - 1;
        for (int deg : {0, 1, 2, 64, 127, 300, 350}) check(f, deg);
    }
    poly high(1000000);
    high[0] = 5;
    high[500000] = 7;
    high[999999] = 11;
    check(high, 17);
    int n = 1 << 17;
    poly f(vector<mint>{3, 7});
    auto g = f.inv(n);
    for (int i = 1; i < n; ++i) assert(mint(3) * g[i] + mint(7) * g[i - 1] == mint(0));
    f[0] = 0;
    auto e = f.exp(n);
    for (int i = 1; i < n; ++i) assert(mint(i) * e[i] == mint(7) * e[i - 1]);
}
