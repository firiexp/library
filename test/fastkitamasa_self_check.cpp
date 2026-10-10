namespace fastkitamasa_test {

vector<mint> multiply(const vector<mint> &a, const vector<mint> &b, const vector<mint> &f) {
    int n = (int)f.size() - 1;
    vector<mint> result(2 * n - 1);
    for (int i = 0; i < (int)a.size(); ++i)
        for (int j = 0; j < (int)b.size(); ++j) result[i + j] += a[i] * b[j];
    mint inverse = f.back().inv();
    for (int i = 2 * n - 2; i >= n; --i) {
        mint q = result[i] * inverse;
        for (int j = 0; j <= n; ++j) result[i - n + j] -= q * f[j];
    }
    result.resize(n);
    return result;
}

vector<mint> power(const vector<mint> &f, long long exponent) {
    int n = (int)f.size() - 1;
    vector<mint> result(n), x(n);
    result[0] = 1;
    if (n == 1) x[0] = -f[0] / f[1];
    else x[1] = 1;
    while (exponent) {
        if (exponent & 1) result = multiply(result, x, f);
        x = multiply(x, x, f);
        exponent >>= 1;
    }
    return result;
}

void self_check() {
    vector<int> fibonacci{-1, -1, 1};
    Fast_Kitamasa legacy(fibonacci, mint::get_mod());
    assert((legacy.kitamasa(10).v == vector<mint>{34, 55}));
    assert((fibonacci == vector<int>{-1, -1, 1}));
    mt19937 rng(60);
    for (int n : {1, 2, 3, 4, 5, 7, 8, 9, 15, 16, 17, 63, 64, 65}) {
        for (int tc = 0; tc < 8; ++tc) {
            vector<mint> f(n + 1);
            for (auto &x : f) x = int(rng() % 21) - 10;
            f[n] = 1 + rng() % 7;
            if (tc == 0) fill(f.begin(), f.begin() + n, mint(0));
            if (tc == 1) f[0] = 0;
            const Fast_Kitamasa solver(f);
            auto original = f;
            for (long long exponent : {0LL, 1LL, (long long)n - 1, (long long)n, (long long)n + 1, (long long)(rng() % 1000), LLONG_MAX}) {
                auto actual = solver.kitamasa(exponent);
                assert(actual.size() == n && actual.v == power(f, exponent));
                assert(f == original);
            }
            vector<mint> a(n), b(n);
            for (auto &x : a) x = rng();
            for (auto &x : b) x = rng();
            poly value(a);
            solver.multiply_mod(value, poly(b));
            assert(value.v == multiply(a, b, f));
            value = poly(a);
            solver.multiply_mod(value, value);
            assert(value.v == multiply(a, a, f));
            value = poly();
            solver.multiply_mod(value, poly(b));
            assert(value.v == vector<mint>(n));
        }
    }
    for (int n = 1; n <= 12; ++n) {
        vector<mint> f(n + 1);
        f[n] = 1;
        for (int i = 0; i < n; ++i) f[i] = int(rng() % 11) - 5;
        Fast_Kitamasa solver(f);
        vector<mint> expected(n);
        expected[0] = 1;
        for (int exponent = 0; exponent < 100; ++exponent) {
            assert(solver.kitamasa(exponent).v == expected);
            mint leading = expected.back();
            for (int i = n - 1; i > 0; --i) expected[i] = expected[i - 1];
            expected[0] = 0;
            for (int i = 0; i < n; ++i) expected[i] -= leading * f[i];
        }
    }
}

}
