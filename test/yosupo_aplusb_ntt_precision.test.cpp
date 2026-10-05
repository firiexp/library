#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/ntt.cpp"

vector<mint> naive_inverse(const vector<mint> &f, int deg) {
    vector<mint> g(deg);
    if (deg == 0) return g;
    g[0] = f[0].inv();
    for (int i = 1; i < deg; ++i) {
        for (int j = 1; j <= i && j < (int)f.size(); ++j) g[i] -= f[j] * g[i - j];
        g[i] *= g[0];
    }
    return g;
}

vector<mint> naive_log(const vector<mint> &f, int deg) {
    // f * (log f)' = f': solve coefficients without using poly operations.
    vector<mint> g(deg);
    for (int i = 1; i < deg; ++i) {
        mint coefficient = i < (int)f.size() ? mint(i) * f[i] : mint(0);
        for (int j = 1; j < i && j < (int)f.size(); ++j) {
            coefficient -= f[j] * mint(i - j) * g[i - j];
        }
        g[i] = coefficient / mint(i);
    }
    return g;
}

void self_check() {
    mt19937 random(19);
    const int sizes[] = {1, 2, 3, 7, 16, 31, 32, 33, 63, 64, 65, 127, 128, 129};
    for (int n : sizes) {
        poly f(n);
        for (auto &x : f.v) x = random() % ntt_mod;
        f[0] = 1 + random() % (ntt_mod - 1);
        const vector<int> degrees = {0, 1, 2, n / 2, n, n + 1, 2 * n + 1};
        auto original = f.v;
        for (int deg : degrees) assert(f.inv(deg).v == naive_inverse(f.v, deg));
        assert(f.inv().v == naive_inverse(f.v, n));
        assert(f.v == original);
        f[0] = 1;
        original = f.v;
        for (int deg : degrees) assert(f.log(deg).v == naive_log(f.v, deg));
        assert(f.log().v == naive_log(f.v, n));
        assert(f.v == original);
    }
    poly one(vector<mint>{1});
    for (int deg : {0, 1, 2, 65}) {
        assert(one.inv(deg).v == naive_inverse(one.v, deg));
        assert(one.log(deg).v == vector<mint>(deg));
    }
    poly long_input(1 << 18);
    for (auto &x : long_input.v) x = random() % ntt_mod;
    long_input[0] = 1;
    auto original = long_input.v;
    for (int deg : {0, 1, 64, 1024}) {
        auto prefix = long_input.pre(max(1, deg));
        assert(long_input.inv(deg).v == naive_inverse(prefix.v, deg));
        assert(long_input.log(deg).v == naive_log(prefix.v, deg));
        assert(long_input.log(deg).v == prefix.log(deg).v);
    }
    assert(long_input.v == original);
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
