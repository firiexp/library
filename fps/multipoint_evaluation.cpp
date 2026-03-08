#include "../math/ntt.cpp"

vector<mint> poly::multipoint_eval(const vector<mint> &xs) const {
    int m = (int)xs.size();
    if (m == 0) return {};
    if (size() == 0) return vector<mint>(m, mint(0));
    if (1LL * size() * m <= 4096) {
        vector<mint> ys(m);
        for (int i = 0; i < m; ++i) ys[i] = eval(xs[i]);
        return ys;
    }
    int n = 1;
    while (n < m) n <<= 1;
    vector<poly> prod(2 * n);
    for (int i = 0; i < m; ++i) prod[n + i] = poly(vector<mint>{-xs[i], mint(1)});
    for (int i = m; i < n; ++i) prod[n + i] = poly(vector<mint>{mint(1)});
    for (int i = n - 1; i >= 1; --i) prod[i] = prod[i << 1] * prod[i << 1 | 1];

    vector<poly> rem(2 * n);
    rem[1] = mod(prod[1]);
    for (int i = 1; i < n; ++i) {
        rem[i << 1] = rem[i].mod(prod[i << 1]);
        rem[i << 1 | 1] = rem[i].mod(prod[i << 1 | 1]);
    }
    vector<mint> ys(m);
    for (int i = 0; i < m; ++i) ys[i] = rem[n + i].v.empty() ? mint(0) : rem[n + i][0];
    return ys;
}

/**
 * @brief 多点評価(Multipoint Evaluation)
 * @docs _md/multipoint_evaluation.md
 */
