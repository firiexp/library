#include "multipoint_evaluation.cpp"

poly polynomial_interpolation(const vector<mint> &xs, const vector<mint> &ys) {
    int n = (int)xs.size();
    assert(n == (int)ys.size());
    if (n == 0) return poly();
    if (n == 1) return poly(vector<mint>{ys[0]});
    int sz = 1;
    while (sz < n) sz <<= 1;
    vector<poly> prod(2 * sz);
    for (int i = 0; i < n; ++i) prod[sz + i] = poly(vector<mint>{-xs[i], mint(1)});
    for (int i = n; i < sz; ++i) prod[sz + i] = poly(vector<mint>{mint(1)});
    for (int i = sz - 1; i >= 1; --i) prod[i] = prod[i << 1] * prod[i << 1 | 1];

    poly derivative = prod[1].diff();
    vector<mint> w = 1LL * derivative.size() * n <= 4096
        ? derivative.multipoint_eval(xs)
        : multipoint_evaluation_detail::evaluate(derivative, prod, n);
    vector<mint> prefix(n + 1, mint(1));
    for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] * w[i];
    mint inverse = prefix[n].inv();
    for (int i = n - 1; i >= 0; --i) {
        mint next = inverse * w[i];
        w[i] = ys[i] * prefix[i] * inverse;
        inverse = next;
    }
    auto interpolate = [&](auto &&self, int i) -> poly {
        if (i >= sz) return i - sz < n ? poly(vector<mint>{w[i - sz]}) : poly();
        poly left = self(self, i << 1);
        poly right = self(self, i << 1 | 1);
        return left * prod[i << 1 | 1] + right * prod[i << 1];
    };
    poly result = interpolate(interpolate, 1);
    result.shrink();
    if (result.size() < n) result.v.resize(n);
    return result;
}

/**
 * @brief 多項式補間(Polynomial Interpolation)
 */
