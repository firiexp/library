#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
#include "../fps/product_polynomials.cpp"

void check(const vector<poly>& factors) {
    vector<mint> expected{1};
    for (const auto& factor : factors) {
        if (expected.empty() || factor.v.empty()) {
            expected.clear();
            continue;
        }
        vector<mint> next(expected.size() + factor.size() - 1);
        for (int i = 0; i < (int)expected.size(); ++i) {
            for (int j = 0; j < factor.size(); ++j) next[i + j] += expected[i] * factor[j];
        }
        expected = move(next);
    }
    while (!expected.empty() && expected.back() == mint(0)) expected.pop_back();
    auto original = factors;
    assert(product_polynomials(factors).v == expected);
    for (int i = 0; i < (int)factors.size(); ++i) assert(factors[i].v == original[i].v);
    reverse(original.begin(), original.end());
    assert(product_polynomials(move(original)).v == expected);
}

int main() {
    check({});
    check({poly()});
    check({poly(vector<mint>{0, 0, 0})});
    check({poly(vector<mint>{1, 2, 0, 0})});
    check({poly(vector<mint>{3}), poly(vector<mint>{5}), poly(vector<mint>{7})});
    check({poly(vector<mint>{3}), poly(), poly(vector<mint>{1, 2})});
    check(vector<poly>(1000, poly(vector<mint>{2})));
    vector<poly> linear(128, poly(vector<mint>{1, 1}));
    check(linear);
    linear.insert(linear.begin(), poly(vector<mint>(1025, mint(3))));
    linear.emplace_back(vector<mint>(257, mint(5)));
    check(linear);
    mt19937 rng(355);
    for (int trial = 0; trial < 600; ++trial) {
        vector<poly> factors(rng() % 16);
        for (auto& factor : factors) {
            factor.v.resize(trial % 5 ? 1 + rng() % 20 : rng() % 8);
            for (auto& x : factor.v) x = int(rng() % 15) - 7;
            if (!factor.v.empty() && trial % 7 == 0) factor.v.back() = 0;
        }
        check(factors);
    }
}
