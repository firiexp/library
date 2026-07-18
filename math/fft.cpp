#ifndef FIRIEXP_LIBRARY_MATH_FFT_CPP
#define FIRIEXP_LIBRARY_MATH_FFT_CPP

#include "./integer_convolution.cpp"
#include "../util/modint.cpp"

namespace ArbitraryConvolution {
    vector<unsigned int> convolution_mod(const vector<unsigned int> &a, const vector<unsigned int> &b) {
        if (a.empty() || b.empty()) return {};
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
        if (size() == 0 || a.size() == 0) {
            v.clear();
            return *this;
        }
        vector<unsigned int> x(size()), y(a.size());
        for (int i = 0; i < size(); ++i) x[i] = v[i].val;
        for (int i = 0; i < a.size(); ++i) y[i] = a.v[i].val;
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
