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

void check_truncated(const vector<poly>& factors, int limit) {
    vector<mint> expected(limit);
    if (limit) expected[0] = 1;
    for (const auto& factor : factors) {
        vector<mint> next(limit);
        for (int i = 0; i < limit; ++i) {
            for (int j = 0; j < factor.size() && i + j < limit; ++j) {
                next[i + j] += expected[i] * factor[j];
            }
        }
        expected = move(next);
    }
    while (!expected.empty() && expected.back() == mint(0)) expected.pop_back();
    auto original = factors;
    assert(product_polynomials(factors, limit).v == expected);
    for (int i = 0; i < (int)factors.size(); ++i) assert(factors[i].v == original[i].v);
    reverse(original.begin(), original.end());
    assert(product_polynomials(move(original), limit).v == expected);
}

int main() {
    for (int limit : {0, 1, 2, 3, 4, 5, 16, 63, 64, 65, 127, 128, 129}) {
        check_truncated({}, limit);
        check_truncated({poly()}, limit);
        check_truncated({poly(vector<mint>{0, 0, 0})}, limit);
        check_truncated({poly(vector<mint>{2}), poly(vector<mint>{3})}, limit);
        check_truncated({poly(vector<mint>{0, 2}), poly(vector<mint>{0, 0, 3})}, limit);
        check_truncated({poly(vector<mint>{1, 1}), poly(vector<mint>{1, -1})}, limit);
        check_truncated(vector<poly>(128, poly(vector<mint>{1, 2, 3})), limit);
        check_truncated({poly(vector<mint>(1025, mint(3))), poly(vector<mint>{0, 0, 4, 5})}, limit);
    }
    vector<mint> high_degree((1 << 23) + 1);
    high_degree[0] = 2;
    high_degree.back() = 3;
    assert(product_polynomials({poly(move(high_degree))}, 2).v == vector<mint>{2});
    check({});
    check({poly()});
    check({poly(vector<mint>{0, 0, 0})});
    check({poly(vector<mint>{1, 2, 0, 0})});
    check({poly(vector<mint>{3}), poly(vector<mint>{5}), poly(vector<mint>{7})});
    check({poly(vector<mint>{3}), poly(), poly(vector<mint>{1, 2})});
    check({poly(vector<mint>{0, 0, 3, 0, 0})});
    check({poly(vector<mint>{0, 2}), poly(vector<mint>{0, 0, 3}), poly(vector<mint>{5})});
    check({poly(vector<mint>{0, 2, 3}), poly(vector<mint>{0, 0, 4, 5})});
    check({poly(vector<mint>{0, 0, 3}), poly(vector<mint>{0, 0})});
    vector<poly> shifted;
    for (int degree : {1, 63, 64, 65, 127, 1024}) {
        vector<mint> coefficients(degree + 3);
        coefficients[degree] = degree;
        coefficients[degree + 1] = degree + 1;
        shifted.emplace_back(move(coefficients));
    }
    check(shifted);
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
            if (!factor.v.empty() && trial % 3 == 0) {
                int zeros = rng() % (factor.size() + 1);
                fill(factor.v.begin(), factor.v.begin() + zeros, mint(0));
            }
        }
        check(factors);
        check_truncated(factors, rng() % 80);
    }
}
