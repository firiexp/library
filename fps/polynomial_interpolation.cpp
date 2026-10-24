#ifndef FIRIEXP_LIBRARY_FPS_POLYNOMIAL_INTERPOLATION_CPP
#define FIRIEXP_LIBRARY_FPS_POLYNOMIAL_INTERPOLATION_CPP

#include "multipoint_evaluation.cpp"

poly MultipointEvaluator::interpolate(const vector<mint> &ys) {
    int m = (int)xs.size();
    assert(m == (int)ys.size());
    if (m == 0) return poly();
    if (m == 1) return poly(vector<mint>{ys[0]});
    if (inverse_weights.empty()) {
        vector<mint> w = eval(prod[1].diff());
        vector<mint> prefix(m + 1, mint(1));
        for (int i = 0; i < m; ++i) prefix[i + 1] = prefix[i] * w[i];
        assert(prefix[m] != mint(0));
        mint inverse = prefix[m].inv();
        inverse_weights.resize(m);
        for (int i = m - 1; i >= 0; --i) {
            inverse_weights[i] = prefix[i] * inverse;
            inverse *= w[i];
        }
    }
    auto interpolate = [&](auto &&self, int i) -> poly {
        if (i >= n) return i - n < m
            ? poly(vector<mint>{ys[i - n] * inverse_weights[i - n]}) : poly();
        poly left = self(self, i << 1);
        poly right = self(self, i << 1 | 1);
        return left * prod[i << 1 | 1] + right * prod[i << 1];
    };
    poly result = interpolate(interpolate, 1);
    result.shrink();
    if (result.size() < m) result.v.resize(m);
    return result;
}

poly polynomial_interpolation(const vector<mint> &xs, const vector<mint> &ys) {
    return MultipointEvaluator(xs).interpolate(ys);
}

#endif

/**
 * @brief 多項式補間(Polynomial Interpolation)
 */
