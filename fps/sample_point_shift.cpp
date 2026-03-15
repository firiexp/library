#include "../math/ntt.cpp"

vector<mint> sample_point_shift(const vector<mint> &ys, mint c, int m = -1) {
    int n = ys.size();
    if (m == -1) m = n;
    if (m <= 0) return {};
    if (n == 0) return vector<mint>(m, mint(0));

    int k = n - 1;
    long long t = c.val;
    if (t <= k) {
        vector<mint> res;
        res.reserve(m);
        for (long long x = t; x <= k && (int)res.size() < m; ++x) res.push_back(ys[x]);
        if ((int)res.size() < m) {
            vector<mint> suf = sample_point_shift(ys, mint(k + 1), m - (int)res.size());
            res.insert(res.end(), suf.begin(), suf.end());
        }
        return res;
    }
    if (t + m > ntt_mod) {
        vector<mint> pref = sample_point_shift(ys, mint(t), ntt_mod - t);
        vector<mint> suf = sample_point_shift(ys, mint(0), m - (int)pref.size());
        pref.insert(pref.end(), suf.begin(), suf.end());
        return pref;
    }

    static vector<mint> fact = {mint(1)}, ifact = {mint(1)};
    auto ensure_fact = [&](int lim) {
        if ((int)fact.size() > lim) return;
        int old = fact.size();
        int next = max(old * 2, lim + 1);
        fact.resize(next);
        for (int i = old; i < next; ++i) fact[i] = fact[i - 1] * mint::raw(i);
        ifact.resize(next);
        ifact[next - 1] = fact[next - 1].inv();
        for (int i = next - 1; i > old; --i) ifact[i - 1] = ifact[i] * mint::raw(i);
    };
    ensure_fact(k);

    vector<mint> a(n), b(n + m - 1);
    for (int i = 0; i < n; ++i) {
        a[i] = ys[i] * ifact[i] * ifact[k - i];
        if ((k - i) & 1) a[i] = -a[i];
    }
    mint start = c - mint(k);
    b[0] = start;
    for (int i = 1; i < n + m - 1; ++i) {
        b[i] = b[i - 1] * (start + mint(i));
    }
    mint coef = b[k];
    mint inv_all = b.back().inv();
    for (int i = n + m - 2; i >= 1; --i) {
        b[i] = b[i - 1] * inv_all;
        inv_all *= start + mint(i);
    }
    b[0] = inv_all;
    poly pa(a), pb(b);
    vector<mint> conv = (pa * pb).v;

    vector<mint> res(m);
    for (int i = 0; i < m; ++i) {
        res[i] = conv[k + i] * coef;
        coef *= c + mint(i + 1);
        coef *= b[i];
    }
    return res;
}

/**
 * @brief 標本点シフト(Sample Point Shift)
 */
