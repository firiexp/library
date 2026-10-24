#define STANDALONE

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

vector<mint> naive_power(const vector<mint> &f, int k, int deg) {
    vector<mint> g(deg);
    if (deg == 0) return g;
    g[0] = 1;
    for (int e = 0; e < k; ++e) {
        vector<mint> next(deg);
        for (int i = 0; i < deg; ++i) {
            for (int j = 0; j < (int)f.size() && i + j < deg; ++j) next[i + j] += g[i] * f[j];
        }
        g = std::move(next);
    }
    return g;
}

void check_power() {
    mt19937 random(212);
    for (int n : {0, 1, 2, 8, 17, 33, 65}) {
        for (int form = 0; form < 5; ++form) {
            poly f(n);
            for (int i = 0; i < n; ++i) {
                if (form == 1 && i >= n / 2) continue;
                if (form == 2 && i < n / 2) continue;
                if (form == 3 && i != n / 2) continue;
                if (form == 4) continue;
                f[i] = 1 + random() % (ntt_mod - 1);
            }
            auto original = f.v;
            for (int k : {0, 1, 2, 8, 64, 65}) {
                for (int deg : {0, 1, n / 2, n, n + 1, 2 * n + 1}) {
                    assert(f.pow(k, deg).v == naive_power(f.v, k, deg));
                }
                assert(f.pow(k).v == naive_power(f.v, k, n));
            }
            assert(f.v == original);
        }
    }
    poly short_input(vector<mint>{1, 2, 3, 4, 5, 6, 7, 8});
    poly padded = short_input.pre(1 << 18);
    for (int k : {1, 2, 8, 64, 65}) {
        auto expected = naive_power(short_input.v, k, 7 * k + 1);
        expected.resize(1 << 17);
        assert(short_input.pow(k, 1 << 17).v == expected);
        assert(padded.pow(k, 1 << 17).v == expected);
    }
    poly shifted(1 << 17);
    shifted[1 << 16] = 3;
    assert(shifted.pow(2).v == vector<mint>(shifted.size()));
    assert(shifted.pow(LLONG_MAX).v == vector<mint>(shifted.size()));
    assert(poly(vector<mint>{0, 3}).pow(LLONG_MAX, 2).v == vector<mint>(2));
}

void check_sqrt() {
    mt19937 rng(259);
    for (int tc = 0; tc < 160; ++tc) {
        int shift = tc % 10, length = 1 + rng() % 32;
        vector<mint> root(shift + length);
        for (int i = shift; i < (int)root.size(); ++i) root[i] = 1 + rng() % (ntt_mod - 1);
        int n = 2 * root.size() - 1;
        poly f(naive_power(root, 2, n));
        auto original = f.v;
        for (int deg : {0, 1, 2, shift, shift + 1, n / 2, n, n + 1, 2 * n + 1}) {
            auto g = f.sqrt(deg);
            assert(g.size() == deg);
            auto expected = root;
            expected.resize(deg);
            if (shift < deg && g[shift] == -root[shift]) {
                for (auto &x : expected) x = -x;
            }
            assert(g.v == expected);
            assert(naive_power(g.v, 2, deg) == f.pre(deg).v);
        }
        assert(f.sqrt().v == f.sqrt(n).v);
        assert(f.v == original);
    }
    for (int n : {0, 1, 2, 65, 4097}) {
        poly zero(n);
        for (int deg : {0, 1, n, n + 1}) assert(zero.sqrt(deg).v == vector<mint>(deg));
    }
    for (int lead : {0, 1, 2, 63, 64, 65, 4096, 4097}) {
        poly f(lead + 1);
        for (int value : {1, 3, 4}) {
            f[lead] = value;
            for (int deg : {1, 2, 64}) {
                auto g = f.sqrt(deg);
                if ((lead & 1) || value == 3) assert(g.size() == 0);
                else {
                    assert(g.size() == deg);
                    assert(naive_power(g.v, 2, deg) == f.pre(deg).v);
                }
            }
            assert(f.sqrt(0).size() == 0);
        }
    }
    poly long_input(1 << 20);
    for (auto &x : long_input.v) x = rng() % ntt_mod;
    long_input[0] = 1;
    auto original = long_input.v;
    for (int deg : {1, 2, 63, 64, 65, 129}) {
        auto g = long_input.sqrt(deg);
        assert(g.v == long_input.pre(deg).sqrt(deg).v);
        assert(naive_power(g.v, 2, deg) == long_input.pre(deg).v);
    }
    assert(long_input.v == original);
}

void self_check() {
    check_power();
    check_sqrt();
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
}
