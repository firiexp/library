#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include "../math/combinatorics/many_factorials.cpp"
#include "../fps/sample_point_shift.cpp"

int main() {
    const int direct_limit = 2 * (ntt_mod / 512);
    vector<mint> fact(direct_limit + 2, mint(1));
    for (int i = 1; i < (int)fact.size(); ++i) fact[i] = fact[i - 1] * mint(i);
    auto check = [&](const vector<ll> &ns) {
        auto saved = ns;
        auto result = many_factorials(ns);
        assert(result.size() == ns.size());
        for (int i = 0; i < (int)ns.size(); ++i) {
            mint expected = ns[i] >= ntt_mod ? mint(0) : fact[ns[i]];
            assert(result[i] == expected);
        }
        assert(ns == saved);
    };
    check({});
    check({ntt_mod, ntt_mod + 1LL, LLONG_MAX});
    for (int n : {0, 100, 99, 1000, 5, 999999, 1000000, 1, 1000001, 1000003, 20}) {
        check({n, ntt_mod, n, 0, LLONG_MAX});
    }
    check({direct_limit - 1, direct_limit, direct_limit - 1});
    check({direct_limit + 1, direct_limit, direct_limit - 1, direct_limit + 1});
    mt19937 rng(262);
    for (int rep = 0; rep < 1000; ++rep) {
        vector<ll> ns(rng() % 100);
        for (auto &n : ns) n = rng() % 5 == 0 ? ntt_mod + ll(rng()) : rng() % fact.size();
        check(ns);
    }
    for (int rep = 0; rep < 3; ++rep) {
        auto answer = many_factorials({ntt_mod - 1, 100, ntt_mod - 2, ntt_mod - 3, 100, ntt_mod});
        assert(answer == vector<mint>({-1, fact[100], 1, -mint(2).inv(), fact[100], 0}));
        check({0, 1, 1000000, 999999, 1000001});
    }
    vector<ll> ns;
    vector<mint> expected;
    for (int k : {513, 0, 255, 256, 257, 511, 512, 1, 255, 1025}) {
        ns.push_back(ntt_mod - 1 - k);
        expected.push_back((k % 2 ? mint(1) : mint(-1)) / fact[k]);
    }
    assert(many_factorials(ns) == expected);
}
