#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../math/batch_inverse.cpp"

template<class Mint>
void check(const vector<Mint>& a) {
    auto original = a;
    auto result = batch_inverse(a);
    assert(a == original && result.size() == a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        assert(result[i] == a[i].inv());
        assert(a[i] * result[i] == Mint(1));
    }
}

template<unsigned Mod>
void check_mod() {
    using Mint = modint<Mod>;
    check(vector<Mint>{});
    check(vector<Mint>{1});
    check(vector<Mint>{Mod - 1});
    check(vector<Mint>(1000, Mod - 1));
    vector<Mint> all;
    for (unsigned i = 1; i < min(Mod, 100U); ++i) all.push_back(i);
    check(all);
    mt19937 rng(Mod);
    for (int trial = 0; trial < 300; ++trial) {
        vector<Mint> a(rng() % 101);
        for (auto& x : a) x = 1 + rng() % (Mod - 1);
        check(a);
    }
}

int main() {
    check_mod<2>();
    check_mod<3>();
    check_mod<17>();
    check_mod<998244353>();
    check_mod<1000000007>();
}
