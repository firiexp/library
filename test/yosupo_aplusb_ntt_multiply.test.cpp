#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/ntt.cpp"

vector<mint> naive_product(const vector<mint> &a, const vector<mint> &b) {
    if (a.empty() || b.empty()) return {};
    vector<mint> result(a.size() + b.size() - 1);
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = 0; j < (int)b.size(); ++j) result[i + j] += a[i] * b[j];
    }
    return result;
}

void check_product(const poly &f, const poly &g) {
    auto expected = naive_product(f.v, g.v);
    auto left = f, right = g;
    left *= g;
    right *= f;
    assert(left.v == expected && right.v == expected);
    assert((f * g).v == expected && (g * f).v == expected);
}

void self_check() {
    mt19937 random(20);
    auto make_poly = [&](int n) {
        poly f(n);
        for (auto &x : f.v) x = random() % ntt_mod;
        return f;
    };
    for (int n = 0; n <= 64; ++n) {
        for (int m = 0; m <= 64; ++m) check_product(make_poly(n), make_poly(m));
    }
    // Result lengths on both sides of powers of two, and both naive thresholds.
    for (int power = 128; power <= 4096; power *= 2) {
        for (int m : {1, 2, 15, 16, 17, 31, 32, 33, 47, 48, 49, 64, 65}) {
            for (int offset : {-1, 0, 1}) {
                check_product(make_poly(power - m + 1 + offset), make_poly(m));
            }
        }
    }
    for (int n : {0, 1, 2, 16, 17, 48, 49, 64, 65, 127, 128, 129, 1024}) {
        auto f = make_poly(n), original = f;
        auto expected = naive_product(f.v, f.v);
        f *= f;
        assert(f.v == expected);
        assert((original * original).v == expected);
        check_product(original, poly(vector<mint>{0}));
        check_product(original, poly(vector<mint>{1}));
        check_product(original, poly(vector<mint>{ntt_mod - 1}));
        check_product(original, poly(17));
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
