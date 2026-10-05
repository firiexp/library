#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/ntt.cpp"

void check_sum_difference(const poly &f, const poly &g) {
    auto original_f = f.v, original_g = g.v;
    vector<mint> sum(max(f.size(), g.size())), difference(sum.size());
    for (int i = 0; i < (int)sum.size(); ++i) {
        mint a = i < f.size() ? f[i] : mint(0);
        mint b = i < g.size() ? g[i] : mint(0);
        sum[i] = a + b;
        difference[i] = a - b;
    }
    assert((f + g).v == sum);
    assert((f - g).v == difference);
    assert(f.v == original_f && g.v == original_g);
    for (mint scalar : {mint(0), mint(1), mint(ntt_mod - 1)}) {
        auto expected = f.v;
        if (expected.empty()) expected.resize(1);
        expected[0] += scalar;
        assert((f + scalar).v == expected);
        assert(f.v == original_f);
    }
    if (f.size()) {
        auto expected = f.v;
        expected[0] += f[0];
        assert((f + f[0]).v == expected);
        assert(f.v == original_f);
    }
}

void self_check() {
    mt19937 random(21);
    const int sizes[] = {0, 1, 2, 16, 17, 48, 49, 64, 65, 4096};
    for (int n : sizes) {
        poly f(n);
        for (auto &x : f.v) x = random() % ntt_mod;
        check_sum_difference(f, f);
        for (int m : sizes) {
            poly g(m);
            for (auto &x : g.v) x = random() % ntt_mod;
            check_sum_difference(f, g);
        }
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
