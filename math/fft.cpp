#ifndef FIRIEXP_LIBRARY_MATH_FFT_CPP
#define FIRIEXP_LIBRARY_MATH_FFT_CPP

#include "./integer_convolution.cpp"
#include "../util/modint.cpp"

namespace ArbitraryConvolution {
    constexpr int naive_mod_threshold = 128;

    vector<unsigned int> convolution_mod(const vector<unsigned int> &a, const vector<unsigned int> &b) {
        if (a.empty() || b.empty()) return {};
        if (min(a.size(), b.size()) <= naive_mod_threshold) {
            const auto &x = a.size() < b.size() ? b : a;
            const auto &y = a.size() < b.size() ? a : b;
            vector<unsigned int> res(x.size() + y.size() - 1);
            for (size_t i = 0; i < y.size(); ++i)
                for (size_t j = 0; j < x.size(); ++j)
                    res[i + j] = (1ULL * y[i] * x[j] + res[i + j]) % MOD;
            return res;
        }
        static const NTT1 ntt1;
        static const NTT2 ntt2;
        static const NTT3 ntt3;
        auto c1 = ntt1.convolution(a, b);
        auto c2 = ntt2.convolution(a, b);
        auto c3 = ntt3.convolution(a, b);
        vector<unsigned int> res(c1.size());
        for (int i = 0; i < (int)res.size(); ++i) {
            res[i] = internal::combine_mod<MOD>(c1[i], c2[i], c3[i]);
        }
        return res;
    }
}

struct poly {
    vector<mint> v;
    poly() = default;
    explicit poly(int n) : v(n) {}
    explicit poly(vector<mint> vv) : v(std::move(vv)) {}
    int size() const { return (int)v.size(); }
    poly cut(int len) {
        if (len < (int)v.size()) v.resize((size_t)len);
        return *this;
    }
    mint& operator[](int i) { return v[i]; }
    const mint& operator[](int i) const { return v[i]; }
    poly& operator+=(const poly &a) {
        v.resize(max(size(), a.size()));
        for (int i = 0; i < a.size(); ++i) v[i] += a.v[i];
        return *this;
    }
    poly& operator-=(const poly &a) {
        v.resize(max(size(), a.size()));
        for (int i = 0; i < a.size(); ++i) v[i] -= a.v[i];
        return *this;
    }
    poly& operator*=(const poly &a) {
        int n = size(), m = a.size();
        if (n == 0 || m == 0) {
            v.clear();
            return *this;
        }
        if (n == 1 || m == 1) {
            mint scalar = m == 1 ? a.v[0] : v[0];
            if (n == 1 && m > 1) v = a.v;
            for (auto &x : v) x *= scalar;
            return *this;
        }
        if (min(n, m) <= ArbitraryConvolution::naive_mod_threshold) {
            const auto &x = n < m ? a.v : v;
            const auto &y = n < m ? v : a.v;
            vector<mint> res(n + m - 1);
            for (size_t i = 0; i < y.size(); ++i)
                for (size_t j = 0; j < x.size(); ++j)
                    res[i + j].val = (1ULL * y[i].val * x[j].val + res[i + j].val) % MOD;
            v = std::move(res);
            return *this;
        }
        vector<unsigned int> x(n), y(m);
        for (int i = 0; i < n; ++i) x[i] = v[i].val;
        for (int i = 0; i < m; ++i) y[i] = a.v[i].val;
        auto z = ArbitraryConvolution::convolution_mod(x, y);
        v.resize(z.size());
        for (int i = 0; i < (int)z.size(); ++i) v[i] = z[i];
        return *this;
    }
    poly& operator/=(const poly &a) { return (*this) *= a.inv(); }
    poly operator+(const poly &a) const { return poly(*this) += a; }
    poly operator-(const poly &a) const { return poly(*this) -= a; }
    poly operator*(const poly &a) const { return poly(*this) *= a; }

    poly inv() const {
        int n = size();
        poly r(1);
        r[0] = v[0].inv();
        int k = 1;
        while (k < n) {
            k <<= 1;
            poly f(k);
            for (int i = 0; i < min(k, n); ++i) f[i] = v[i];
            poly nr = (r * r * f).cut(k);
            for (int i = 0; i < k / 2; ++i) {
                nr[i] = r[i] + r[i] - nr[i];
                nr[i + k / 2] = -nr[i + k / 2];
            }
            r = nr;
        }
        r.v.resize(n);
        return r;
    }
};

/**
 * @brief 任意MOD畳み込み(3 NTT + Garner)
 */

#endif
