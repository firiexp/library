template<class T>
vector<T> berlekamp_massey(const vector<T> &s) {
    vector<T> c(1, T(1)), b(1, T(1));
    int l = 0, m = 1;
    T y = T(1);
    for (int n = 0; n < (int)s.size(); ++n) {
        T d = T(0);
        for (int i = 0; i <= l; ++i) d += c[i] * s[n - i];
        if (d == T(0)) {
            ++m;
            continue;
        }
        auto t = c;
        T coef = d / y;
        if ((int)c.size() < (int)b.size() + m) c.resize((int)b.size() + m, T(0));
        for (int i = 0; i < (int)b.size(); ++i) c[i + m] -= coef * b[i];
        if (2 * l <= n) {
            l = n + 1 - l;
            b = t;
            y = d;
            m = 1;
        } else {
            ++m;
        }
    }
    c.erase(c.begin());
    for (auto &x : c) x = -x;
    return c;
}

/**
 * @brief Berlekamp-Massey algorithm
 * @docs _md/berlekamp_massey.md
 */
