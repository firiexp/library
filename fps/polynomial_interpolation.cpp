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

    vector<mint> w = prod[1].diff().multipoint_eval(xs);
    vector<poly> cur(2 * sz);
    for (int i = 0; i < n; ++i) cur[sz + i] = poly(vector<mint>{ys[i] / w[i]});
    for (int i = sz - 1; i >= 1; --i) {
        cur[i] = cur[i << 1] * prod[i << 1 | 1] + cur[i << 1 | 1] * prod[i << 1];
    }
    cur[1].shrink();
    if (cur[1].size() < n) cur[1].v.resize(n);
    return cur[1];
}

/**
 * @brief polynomial interpolation
 * @docs _md/polynomial_interpolation.md
 */
