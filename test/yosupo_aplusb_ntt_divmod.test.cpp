#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../util/fastio.cpp"
#include "../math/ntt.cpp"

void check(poly f, poly g) {
    auto original_f = f.v, original_g = g.v;
    auto [q, r] = f.divmod(g);
    assert(f.v == original_f && g.v == original_g);
    f.shrink();
    g.shrink();
    assert(q.size() == max(0, f.size() - g.size() + 1));
    assert(r.size() < g.size());
    assert(r.v.empty() || r.v.back() != mint(0));
    vector<mint> restored(max(f.size(), r.size()));
    for (int i = 0; i < q.size(); ++i)
        for (int j = 0; j < g.size(); ++j) restored[i + j] += q[i] * g[j];
    for (int i = 0; i < r.size(); ++i) restored[i] += r[i];
    assert(restored == f.v);
    assert(f.mod(g).v == r.v);
}

int main() {
    mt19937 rng(95);
    for (int m : {1, 2, 15, 16, 17, 31, 63, 64, 65, 127, 128, 129}) {
        for (int k : {0, 1, 2, 15, 16, 17, 31, 63, 64, 65, 127, 128, 129}) {
            for (int mode = 0; mode < 3; ++mode) {
                poly f(m + k - 1), g(m);
                for (auto &x : f.v) x = rng() % ntt_mod;
                for (auto &x : g.v) x = rng() % ntt_mod;
                g[m - 1] = mode ? mint(1) : mint(2 + rng() % (ntt_mod - 2));
                if (mode == 2) {
                    f.v.resize(f.size() + 3);
                    g.v.resize(g.size() + 2);
                }
                check(f, g);
            }
        }
    }
    check(poly(), poly(vector<mint>{3}));
    check(poly(20), poly(vector<mint>{1, 2, 0}));
    for (int tc = 0; tc < 500; ++tc) {
        poly f(rng() % 300), g(1 + rng() % 150);
        for (auto &x : f.v) x = rng() % ntt_mod;
        for (auto &x : g.v) x = 1 + rng() % (ntt_mod - 1);
        check(f, g);
    }
}
