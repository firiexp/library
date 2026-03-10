#include "../util/modint.cpp"

#include <algorithm>
#include <cassert>

namespace ArbitraryConvolution {
    template<uint M>
    struct StaticModInt {
        uint val;
        StaticModInt() : val(0) {}
        template<class T>
        StaticModInt(T v) {
            long long x = (long long)(v % (long long)M);
            if (x < 0) x += M;
            val = (uint)x;
        }
        static StaticModInt raw(uint v) {
            StaticModInt x;
            x.val = v;
            return x;
        }
        StaticModInt& operator+=(const StaticModInt& rhs) {
            val += rhs.val;
            if (val >= M) val -= M;
            return *this;
        }
        StaticModInt& operator-=(const StaticModInt& rhs) {
            val -= rhs.val;
            if (val >= M) val += M;
            return *this;
        }
        StaticModInt& operator*=(const StaticModInt& rhs) {
            val = (uint)((unsigned long long)val * rhs.val % M);
            return *this;
        }
        StaticModInt pow(long long n) const {
            StaticModInt x = *this, r = 1;
            while (n) {
                if (n & 1) r *= x;
                x *= x;
                n >>= 1;
            }
            return r;
        }
        StaticModInt inv() const { return pow(M - 2); }
        friend StaticModInt operator+(StaticModInt lhs, const StaticModInt& rhs) { return lhs += rhs; }
        friend StaticModInt operator-(StaticModInt lhs, const StaticModInt& rhs) { return lhs -= rhs; }
        friend StaticModInt operator*(StaticModInt lhs, const StaticModInt& rhs) { return lhs *= rhs; }
        friend bool operator==(const StaticModInt& lhs, const StaticModInt& rhs) { return lhs.val == rhs.val; }
        friend bool operator!=(const StaticModInt& lhs, const StaticModInt& rhs) { return lhs.val != rhs.val; }
    };

    template<uint MOD_, uint PRIMITIVE_ROOT_>
    struct NTT {
        using mint = StaticModInt<MOD_>;
        static constexpr uint MODV = MOD_;
        static constexpr uint G = PRIMITIVE_ROOT_;

        void ntt(vector<mint> &a, bool invert) const {
            int n = (int)a.size();
            for (int i = 1, j = 0; i < n; ++i) {
                int bit = n >> 1;
                for (; j & bit; bit >>= 1) j ^= bit;
                j ^= bit;
                if (i < j) swap(a[i], a[j]);
            }
            for (int len = 2; len <= n; len <<= 1) {
                mint wlen = mint(G).pow((MODV - 1) / len);
                if (invert) wlen = wlen.inv();
                for (int i = 0; i < n; i += len) {
                    mint w = 1;
                    for (int j = 0; j < len / 2; ++j) {
                        mint u = a[i + j];
                        mint v = a[i + j + len / 2] * w;
                        a[i + j] = u + v;
                        a[i + j + len / 2] = u - v;
                        w *= wlen;
                    }
                }
            }
            if (invert) {
                mint inv_n = mint(n).inv();
                for (auto &x : a) x *= inv_n;
            }
        }

        vector<uint> convolution(const vector<uint> &a, const vector<uint> &b) const {
            if (a.empty() || b.empty()) return {};
            int need = (int)a.size() + (int)b.size() - 1;
            int n = 1;
            while (n < need) n <<= 1;
            vector<mint> fa(n), fb(n);
            for (int i = 0; i < (int)a.size(); ++i) fa[i] = a[i];
            for (int i = 0; i < (int)b.size(); ++i) fb[i] = b[i];
            ntt(fa, false);
            ntt(fb, false);
            for (int i = 0; i < n; ++i) fa[i] *= fb[i];
            ntt(fa, true);
            vector<uint> res(need);
            for (int i = 0; i < need; ++i) res[i] = fa[i].val;
            return res;
        }
    };

    using NTT1 = NTT<167772161, 3>;
    using NTT2 = NTT<469762049, 3>;
    using NTT3 = NTT<1224736769, 3>;

    vector<uint> convolution_mod(const vector<uint> &a, const vector<uint> &b) {
        if (a.empty() || b.empty()) return {};
        static const NTT1 ntt1;
        static const NTT2 ntt2;
        static const NTT3 ntt3;
        static const long long m1 = 167772161LL;
        static const long long m2 = 469762049LL;
        static const long long m3 = 1224736769LL;
        static const long long m1_inv_m2 = StaticModInt<469762049>(m1).inv().val;
        static const long long m12_mod_m3 = (m1 % m3) * (m2 % m3) % m3;
        static const long long m12_inv_m3 = StaticModInt<1224736769>((long long)m12_mod_m3).inv().val;
        static const unsigned long long m12 = (unsigned long long)m1 * (unsigned long long)m2;
        static const long long m1_mod = m1 % MOD;
        static const long long m12_mod = m12 % MOD;

        auto c1 = ntt1.convolution(a, b);
        auto c2 = ntt2.convolution(a, b);
        auto c3 = ntt3.convolution(a, b);
        vector<uint> res(c1.size());
        for (int i = 0; i < (int)res.size(); ++i) {
            long long x1 = c1[i];
            long long x2 = c2[i];
            long long x3 = c3[i];
            long long t = (x2 - x1) % m2;
            if (t < 0) t += m2;
            t = t * m1_inv_m2 % m2;
            long long x12 = (long long)(((__int128)x1 + (__int128)m1 * t) % m3);
            long long u = (x3 - x12) % m3;
            if (u < 0) u += m3;
            u = u * m12_inv_m3 % m3;
            __int128 value = x1 % MOD;
            value += (__int128)m1_mod * t;
            value += (__int128)m12_mod * u;
            res[i] = (uint)(value % MOD);
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
        vector<uint> x(size()), y(a.size());
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
