#ifndef FIRIEXP_LIBRARY_FPS_MULTIPOINT_EVALUATION_GEOMETRIC_CPP
#define FIRIEXP_LIBRARY_FPS_MULTIPOINT_EVALUATION_GEOMETRIC_CPP

#include "ntt.cpp"

vector<mint> multipoint_evaluation_geometric(const poly& f, mint a, mint r, int m) {
    assert(m >= 0);
    int n = f.size();
    vector<mint> result(m);
    if (m == 0 || n == 0) return result;
    if (a == mint(0)) {
        fill(result.begin(), result.end(), f[0]);
        return result;
    }
    if (r == mint(0)) {
        fill(result.begin(), result.end(), f[0]);
        result[0] = f.eval(a);
        return result;
    }
    if (r == mint(1)) {
        fill(result.begin(), result.end(), f.eval(a));
        return result;
    }
    if (min(n, m) <= 32) {
        for (int i = 0; i < m; ++i) {
            result[i] = f.eval(a);
            a *= r;
        }
        return result;
    }
    vector<mint> inverse_chirp(max(n, m));
    mint inverse_r = r.inv(), power = 1, value = 1;
    for (auto& x : inverse_chirp) {
        x = value;
        value *= power;
        power *= inverse_r;
    }
    poly left(n), right(n + m - 1);
    power = 1;
    for (int i = 0; i < n; ++i) {
        left[n - 1 - i] = f[i] * power * inverse_chirp[i];
        power *= a;
    }
    power = value = 1;
    for (auto& x : right.v) {
        x = value;
        value *= power;
        power *= r;
    }
    left *= right;
    for (int i = 0; i < m; ++i) result[i] = left[n - 1 + i] * inverse_chirp[i];
    return result;
}

#endif

/**
 * @brief 等比数列上の多点評価
 */
