#ifndef FIRIEXP_LIBRARY_FPS_MULTIPOINT_EVALUATION_CPP
#define FIRIEXP_LIBRARY_FPS_MULTIPOINT_EVALUATION_CPP

#include "ntt.cpp"

namespace multipoint_evaluation_detail {
bool use_horner(int coefficients, int points) {
    return coefficients <= 16 || points <= 16 || 1LL * coefficients * points <= 4096;
}

vector<mint> evaluate(const poly &f, const vector<poly> &prod, const vector<mint> &xs) {
    int n = (int)prod.size() / 2;
    int m = (int)xs.size();
    vector<mint> ys(m);
    if (use_horner(f.size(), m)) {
        for (int i = 0; i < m; ++i) ys[i] = f.eval(xs[i]);
        return ys;
    }
    auto visit = [&](auto &&self, int i, int l, int r, const poly &rem) -> void {
        if (l >= m) return;
        if (rem.size() <= 16 || r - l <= 16) {
            for (int j = l; j < min(r, m); ++j) ys[j] = rem.eval(xs[j]);
            return;
        }
        int mid = (l + r) / 2;
        self(self, i << 1, l, mid, rem.mod(prod[i << 1]));
        if (mid < m) self(self, i << 1 | 1, mid, r, rem.mod(prod[i << 1 | 1]));
    };
    visit(visit, 1, 0, n, f.mod(prod[1]));
    return ys;
}
}

class MultipointEvaluator {
    vector<mint> xs, inverse_weights;
    vector<poly> prod;
    int n = 1;

public:
    explicit MultipointEvaluator(const vector<mint> &points) : xs(points) {
        int m = (int)xs.size();
        while (n < m) n <<= 1;
        prod.resize(2 * n);
        for (int i = 0; i < m; ++i) prod[n + i] = poly(vector<mint>{-xs[i], mint(1)});
        for (int i = m; i < n; ++i) prod[n + i] = poly(vector<mint>{mint(1)});
        for (int i = n - 1; i >= 1; --i) prod[i] = prod[i << 1] * prod[i << 1 | 1];
    }

    vector<mint> eval(const poly &f) const {
        return multipoint_evaluation_detail::evaluate(f, prod, xs);
    }

    poly interpolate(const vector<mint> &ys);
};

vector<mint> poly::multipoint_eval(const vector<mint> &xs) const {
    int m = (int)xs.size();
    if (m == 0) return {};
    if (size() == 0) return vector<mint>(m, mint(0));
    if (multipoint_evaluation_detail::use_horner(size(), m)) {
        vector<mint> ys(m);
        for (int i = 0; i < m; ++i) ys[i] = eval(xs[i]);
        return ys;
    }
    return MultipointEvaluator(xs).eval(*this);
}

#endif

/**
 * @brief 多点評価(Multipoint Evaluation)
 */
