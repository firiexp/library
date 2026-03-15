#ifndef FIRIEXP_LIBRARY_MATH_FFT_CORE_CPP
#define FIRIEXP_LIBRARY_MATH_FFT_CORE_CPP

#ifndef FIRIEXP_LIBRARY_ARBITRARY_CONVOLUTION_U64_NAIVE_THRESHOLD
#define FIRIEXP_LIBRARY_ARBITRARY_CONVOLUTION_U64_NAIVE_THRESHOLD 8192
#endif

#ifndef FIRIEXP_LIBRARY_ARBITRARY_SQUARE_U64_NAIVE_THRESHOLD
#define FIRIEXP_LIBRARY_ARBITRARY_SQUARE_U64_NAIVE_THRESHOLD 32768
#endif

namespace ArbitraryConvolution {
    template<unsigned int M>
    struct StaticModInt {
        unsigned int val;
        StaticModInt() : val(0) {}
        template<class T>
        StaticModInt(T v) {
            long long x = (long long)(v % (long long)M);
            if (x < 0) x += M;
            val = (unsigned int)x;
        }
        static StaticModInt raw(unsigned int v) {
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
            val = (unsigned int)((unsigned long long)val * rhs.val % M);
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

    template<unsigned int MOD_, unsigned int PRIMITIVE_ROOT_>
    struct NTT {
        using mint = StaticModInt<MOD_>;
        static constexpr unsigned int MODV = MOD_;
        static constexpr unsigned int G = PRIMITIVE_ROOT_;
        mint root[30], iroot[30], rate2[30], irate2[30], rate3[30], irate3[30], inv_pow2[30];
        int max_base;

        NTT() : max_base(__builtin_ctz(MODV - 1)) {
            mint e = mint(G).pow((MODV - 1) >> max_base), ie = e.inv();
            for (int i = max_base; i >= 0; --i) {
                root[i] = e;
                iroot[i] = ie;
                e *= e;
                ie *= ie;
            }
            mint prod = 1, iprod = 1;
            for (int i = 0; i <= max_base - 2; ++i) {
                rate2[i] = root[i + 2] * prod;
                irate2[i] = iroot[i + 2] * iprod;
                prod *= iroot[i + 2];
                iprod *= root[i + 2];
            }
            prod = 1;
            iprod = 1;
            for (int i = 0; i <= max_base - 3; ++i) {
                rate3[i] = root[i + 3] * prod;
                irate3[i] = iroot[i + 3] * iprod;
                prod *= iroot[i + 3];
                iprod *= root[i + 3];
            }
            inv_pow2[0] = 1;
            mint inv2 = mint(2).inv();
            for (int i = 1; i < 30; ++i) inv_pow2[i] = inv_pow2[i - 1] * inv2;
        }

        mint inv_size(int n) const {
            return inv_pow2[__builtin_ctz((unsigned int)n)];
        }

        void ntt(vector<mint> &a, bool invert) const {
            int n = (int)a.size();
            assert(n > 0);
            assert((n & (n - 1)) == 0);
            assert(__builtin_ctz((unsigned int)n) <= max_base);
            int h = __builtin_ctz((unsigned int)n);
            if (!invert) {
                int len = 0;
                while (len < h) {
                    if (h - len == 1) {
                        int p = 1 << (h - len - 1);
                        mint rot = 1;
                        for (int s = 0; s < (1 << len); ++s) {
                            int offset = s << (h - len);
                            for (int i = 0; i < p; ++i) {
                                mint l = a[i + offset];
                                mint r = a[i + offset + p] * rot;
                                a[i + offset] = l + r;
                                a[i + offset + p] = l - r;
                            }
                            if (s + 1 != (1 << len)) {
                                rot *= rate2[__builtin_ctz(~(unsigned int)s)];
                            }
                        }
                        ++len;
                    } else {
                        int p = 1 << (h - len - 2);
                        mint rot = 1, imag = root[2];
                        for (int s = 0; s < (1 << len); ++s) {
                            mint rot2 = rot * rot;
                            mint rot3 = rot2 * rot;
                            int offset = s << (h - len);
                            unsigned long long mod2 = 1ULL * MODV * MODV;
                            for (int i = 0; i < p; ++i) {
                                unsigned long long a0 = a[i + offset].val;
                                unsigned long long a1 = 1ULL * a[i + offset + p].val * rot.val;
                                unsigned long long a2 = 1ULL * a[i + offset + 2 * p].val * rot2.val;
                                unsigned long long a3 = 1ULL * a[i + offset + 3 * p].val * rot3.val;
                                unsigned long long a1na3imag = 1ULL * mint(a1 + mod2 - a3).val * imag.val;
                                unsigned long long na2 = mod2 - a2;
                                a[i + offset] = mint(a0 + a2 + a1 + a3);
                                a[i + offset + p] = mint(a0 + a2 + (2 * mod2 - (a1 + a3)));
                                a[i + offset + 2 * p] = mint(a0 + na2 + a1na3imag);
                                a[i + offset + 3 * p] = mint(a0 + na2 + (mod2 - a1na3imag));
                            }
                            if (s + 1 != (1 << len)) {
                                rot *= rate3[__builtin_ctz(~(unsigned int)s)];
                            }
                        }
                        len += 2;
                    }
                }
            } else {
                int len = h;
                while (len) {
                    if (len == 1) {
                        int p = 1 << (h - len);
                        mint irot = 1;
                        for (int s = 0; s < (1 << (len - 1)); ++s) {
                            int offset = s << (h - len + 1);
                            for (int i = 0; i < p; ++i) {
                                mint l = a[i + offset];
                                mint r = a[i + offset + p];
                                a[i + offset] = l + r;
                                a[i + offset + p] = mint(1ULL * (MODV + l.val - r.val) * irot.val);
                            }
                            if (s + 1 != (1 << (len - 1))) {
                                irot *= irate2[__builtin_ctz(~(unsigned int)s)];
                            }
                        }
                        --len;
                    } else {
                        int p = 1 << (h - len);
                        mint irot = 1, iimag = iroot[2];
                        for (int s = 0; s < (1 << (len - 2)); ++s) {
                            mint irot2 = irot * irot;
                            mint irot3 = irot2 * irot;
                            int offset = s << (h - len + 2);
                            for (int i = 0; i < p; ++i) {
                                unsigned long long a0 = a[i + offset].val;
                                unsigned long long a1 = a[i + offset + p].val;
                                unsigned long long a2 = a[i + offset + 2 * p].val;
                                unsigned long long a3 = a[i + offset + 3 * p].val;
                                unsigned long long a2na3iimag = 1ULL * mint(1ULL * (MODV + a2 - a3) * iimag.val).val;
                                a[i + offset] = mint(a0 + a1 + a2 + a3);
                                a[i + offset + p] = mint(a0 + (MODV - a1) + a2na3iimag) * irot;
                                a[i + offset + 2 * p] = mint(a0 + a1 + (MODV - a2) + (MODV - a3)) * irot2;
                                a[i + offset + 3 * p] = mint(a0 + (MODV - a1) + (MODV - a2na3iimag)) * irot3;
                            }
                            if (s + 1 != (1 << (len - 2))) {
                                irot *= irate3[__builtin_ctz(~(unsigned int)s)];
                            }
                        }
                        len -= 2;
                    }
                }
            }
        }

        vector<unsigned int> convolution(const vector<unsigned int> &a, const vector<unsigned int> &b) const {
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
            mint iz = inv_size(n);
            vector<unsigned int> res(need);
            for (int i = 0; i < need; ++i) res[i] = (fa[i] * iz).val;
            return res;
        }

        vector<unsigned int> square(const vector<unsigned int> &a) const {
            if (a.empty()) return {};
            int need = (int)a.size() * 2 - 1;
            int n = 1;
            while (n < need) n <<= 1;
            vector<mint> fa(n);
            for (int i = 0; i < (int)a.size(); ++i) fa[i] = a[i];
            ntt(fa, false);
            for (int i = 0; i < n; ++i) fa[i] *= fa[i];
            ntt(fa, true);
            mint iz = inv_size(n);
            vector<unsigned int> res(need);
            for (int i = 0; i < need; ++i) res[i] = (fa[i] * iz).val;
            return res;
        }
    };

    using NTT1 = NTT<167772161, 3>;
    using NTT2 = NTT<469762049, 3>;
    using NTT3 = NTT<1224736769, 3>;

    namespace internal {
        static constexpr int CONVOLUTION_U64_NAIVE_THRESHOLD = FIRIEXP_LIBRARY_ARBITRARY_CONVOLUTION_U64_NAIVE_THRESHOLD;
        static constexpr int SQUARE_U64_NAIVE_THRESHOLD = FIRIEXP_LIBRARY_ARBITRARY_SQUARE_U64_NAIVE_THRESHOLD;

        inline const NTT1& ntt1() {
            static const NTT1 value;
            return value;
        }

        inline const NTT2& ntt2() {
            static const NTT2 value;
            return value;
        }

        inline const NTT3& ntt3() {
            static const NTT3 value;
            return value;
        }

        inline unsigned long long combine_u64(unsigned int x1, unsigned int x2, unsigned int x3) {
            static const unsigned long long m1 = 167772161ULL;
            static const unsigned long long m2 = 469762049ULL;
            static const unsigned long long m3 = 1224736769ULL;
            static const unsigned long long m1_inv_m2 = StaticModInt<469762049>(m1).inv().val;
            static const unsigned long long m12_mod_m3 = (m1 % m3) * (m2 % m3) % m3;
            static const unsigned long long m12_inv_m3 = StaticModInt<1224736769>(m12_mod_m3).inv().val;
            static const unsigned long long m12 = m1 * m2;

            unsigned long long t = (x2 + m2 - x1 % m2) % m2;
            t = t * m1_inv_m2 % m2;
            unsigned long long x12 = (x1 + (__uint128_t)m1 * t) % m3;
            unsigned long long u = (x3 + m3 - x12) % m3;
            u = u * m12_inv_m3 % m3;
            return (unsigned long long)((__uint128_t)x1 + (__uint128_t)m1 * t + (__uint128_t)m12 * u);
        }

        template<unsigned int TARGET_MOD>
        inline unsigned int combine_mod(unsigned int x1, unsigned int x2, unsigned int x3) {
            static const long long m1 = 167772161LL;
            static const long long m2 = 469762049LL;
            static const long long m3 = 1224736769LL;
            static const long long m1_inv_m2 = StaticModInt<469762049>(m1).inv().val;
            static const long long m12_mod_m3 = (m1 % m3) * (m2 % m3) % m3;
            static const long long m12_inv_m3 = StaticModInt<1224736769>(m12_mod_m3).inv().val;
            static const unsigned long long m12 = (unsigned long long)m1 * (unsigned long long)m2;
            static const long long m1_mod = m1 % TARGET_MOD;
            static const long long m12_mod = m12 % TARGET_MOD;

            long long t = ((long long)x2 - (long long)x1) % m2;
            if (t < 0) t += m2;
            t = t * m1_inv_m2 % m2;
            long long x12 = (long long)(((__int128)x1 + (__int128)m1 * t) % m3);
            long long u = ((long long)x3 - x12) % m3;
            if (u < 0) u += m3;
            u = u * m12_inv_m3 % m3;
            __int128 value = x1 % TARGET_MOD;
            value += (__int128)m1_mod * t;
            value += (__int128)m12_mod * u;
            return (unsigned int)(value % TARGET_MOD);
        }
    }  // namespace internal

    vector<unsigned long long> convolution_u64(const vector<unsigned int> &a, const vector<unsigned int> &b) {
        if (a.empty() || b.empty()) return {};
        if (1LL * (int)a.size() * (int)b.size() <= internal::CONVOLUTION_U64_NAIVE_THRESHOLD) {
            vector<unsigned long long> res(a.size() + b.size() - 1);
            for (int i = 0; i < (int)a.size(); ++i) {
                for (int j = 0; j < (int)b.size(); ++j) {
                    res[i + j] += (unsigned long long)a[i] * b[j];
                }
            }
            return res;
        }

        auto c1 = internal::ntt1().convolution(a, b);
        auto c2 = internal::ntt2().convolution(a, b);
        auto c3 = internal::ntt3().convolution(a, b);
        vector<unsigned long long> res(c1.size());
        for (int i = 0; i < (int)res.size(); ++i) {
            res[i] = internal::combine_u64(c1[i], c2[i], c3[i]);
        }
        return res;
    }

    vector<unsigned long long> square_u64(const vector<unsigned int> &a) {
        if (a.empty()) return {};
        if (1LL * (int)a.size() * (int)a.size() <= internal::SQUARE_U64_NAIVE_THRESHOLD) {
            vector<unsigned long long> res(a.size() * 2 - 1);
            for (int i = 0; i < (int)a.size(); ++i) {
                res[i + i] += (unsigned long long)a[i] * a[i];
                for (int j = i + 1; j < (int)a.size(); ++j) {
                    res[i + j] += 2ULL * (unsigned long long)a[i] * a[j];
                }
            }
            return res;
        }

        auto c1 = internal::ntt1().square(a);
        auto c2 = internal::ntt2().square(a);
        auto c3 = internal::ntt3().square(a);
        vector<unsigned long long> res(c1.size());
        for (int i = 0; i < (int)res.size(); ++i) {
            res[i] = internal::combine_u64(c1[i], c2[i], c3[i]);
        }
        return res;
    }
}

#endif

#ifndef FIRIEXP_LIBRARY_FFT_EXACT_ONLY
#ifndef FIRIEXP_LIBRARY_MATH_FFT_POLY_CPP
#define FIRIEXP_LIBRARY_MATH_FFT_POLY_CPP

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
#endif
