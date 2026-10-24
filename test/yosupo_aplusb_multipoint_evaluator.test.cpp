#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include "../fps/multipoint_evaluation.cpp"
#include "../fps/polynomial_interpolation.cpp"

int main() {
    mt19937 rng(261);
    for (int m : {0, 1, 2, 15, 16, 17, 63, 64, 65, 129, 257}) {
        vector<mint> xs(m);
        for (int i = 0; i < m; ++i) xs[i] = i + 7;
        shuffle(xs.begin(), xs.end(), rng);
        auto original_xs = xs;
        MultipointEvaluator evaluator(xs);
        fill(xs.begin(), xs.end(), mint(0));
        vector<mint> saved_values, original_values;
        poly saved_polynomial, original_polynomial;
        for (int rep = 0; rep < 30; ++rep) {
            int k = rep % 3 == 0 ? m : rng() % (2 * m + 100);
            poly f(k);
            for (auto &c : f.v) c = rng() % ntt_mod;
            if (rep % 5 == 0) fill(f.v.begin(), f.v.end(), mint(0));
            auto original_f = f.v;
            vector<mint> expected(m);
            for (int i = 0; i < m; ++i) expected[i] = f.eval(original_xs[i]);
            assert(evaluator.eval(f) == expected);
            assert(f.v == original_f);
            if (k == m) {
                auto original_expected = expected;
                auto restored = evaluator.interpolate(expected);
                assert(restored.v == original_f);
                assert(expected == original_expected);
                assert(evaluator.eval(restored) == expected);
                if (rep == 0) {
                    saved_values = original_values = expected;
                    saved_polynomial = original_polynomial = restored;
                }
            }
            assert(saved_values == original_values);
            assert(saved_polynomial.v == original_polynomial.v);
        }
    }
    for (int m : {1, 17, 65, 513}) {
        vector<mint> xs(m);
        for (int i = 0; i < m; ++i) xs[i] = i % 7;
        const MultipointEvaluator evaluator(xs);
        for (int k : {0, 1, 16, 17, 257, 1025}) {
            poly f(k);
            for (auto &c : f.v) c = rng() % ntt_mod;
            vector<mint> expected(m);
            for (int i = 0; i < m; ++i) expected[i] = f.eval(xs[i]);
            assert(evaluator.eval(f) == expected);
        }
    }
    auto temporary = []() {
        return MultipointEvaluator(vector<mint>{2, 3});
    }();
    assert(temporary.interpolate({5, 7}).v == vector<mint>({1, 2}));
}
