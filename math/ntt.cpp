#ifndef FIRIEXP_LIBRARY_MATH_NTT_CPP
#define FIRIEXP_LIBRARY_MATH_NTT_CPP

constexpr int ntt_mod = 998244353, ntt_root = 3;
#ifndef NTT_NAIVE_MUL_THRESHOLD
#define NTT_NAIVE_MUL_THRESHOLD 3072
#endif
#ifndef NTT_NAIVE_MUL_MIN_DIM
#define NTT_NAIVE_MUL_MIN_DIM 48
#endif
// 1012924417 -> 5, 924844033 -> 5
// 998244353  -> 3, 897581057 -> 3
// 645922817  -> 3;
template <uint M>
struct modint {
    uint val;
public:
    static modint raw(int v) { modint x; x.val = v; return x; }
    static constexpr uint get_mod() { return M; }
    modint() : val(0) {}
    template <class T>
    modint(T v) { ll x = (ll)(v%(ll)(M)); if (x < 0) x += M; val = uint(x); }
    modint(bool v) { val = ((unsigned int)(v) % M); }
    modint& operator++() { val++; if (val == M) val = 0; return *this; }
    modint& operator--() { if (val == 0) val = M; val--; return *this; }
    modint operator++(int) { modint result = *this; ++*this; return result; }
    modint operator--(int) { modint result = *this; --*this; return result; }
    modint& operator+=(const modint& rhs) { val += rhs.val; if (val >= M) val -= M; return *this; }
    modint& operator-=(const modint& rhs) { val -= rhs.val; if (val >= M) val += M; return *this; }
    modint& operator*=(const modint& rhs) { ull z = val; z *= rhs.val; val = (uint)(z % M); return *this; }
    modint& operator/=(const modint& rhs) { return *this = *this * rhs.inv(); }
    modint operator+() const { return *this; }
    modint operator-() const { return modint() - *this; }
    modint pow(long long n) const { modint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }
    modint inv() const { return pow(M-2); }
    friend modint operator+(const modint& lhs, const modint& rhs) { return modint(lhs) += rhs; }
    friend modint operator-(const modint& lhs, const modint& rhs) { return modint(lhs) -= rhs; }
    friend modint operator*(const modint& lhs, const modint& rhs) { return modint(lhs) *= rhs; }
    friend modint operator/(const modint& lhs, const modint& rhs) { return modint(lhs) /= rhs; }
    friend bool operator==(const modint& lhs, const modint& rhs) { return lhs.val == rhs.val; }
    friend bool operator!=(const modint& lhs, const modint& rhs) { return lhs.val != rhs.val; }
};
using mint = modint<998244353>;
#define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED

class NTT {
    static constexpr int max_base = 23, maxN = 1 << max_base; // 998244353 supports up to 2^23-th roots
    mint root[30], iroot[30], rate2[30], irate2[30], rate3[30], irate3[30];
public:
    NTT() {
        int cnt2 = __builtin_ctz(ntt_mod-1);
        mint e = mint(ntt_root).pow((ntt_mod-1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 0; i--){
            root[i] = e;
            iroot[i] = ie;
            e *= e; ie *= ie;
        }
        mint prod = 1, iprod = 1;
        for (int i = 0; i <= cnt2 - 2; i++) {
            rate2[i] = root[i + 2] * prod;
            irate2[i] = iroot[i + 2] * iprod;
            prod *= iroot[i + 2];
            iprod *= root[i + 2];
        }
        prod = 1, iprod = 1;
        for (int i = 0; i <= cnt2 - 3; i++) {
            rate3[i] = root[i + 3] * prod;
            irate3[i] = iroot[i + 3] * iprod;
            prod *= iroot[i + 3];
            iprod *= root[i + 3];
        }
    }

    mint root_pow2(int k) const { return root[k]; }
    mint iroot_pow2(int k) const { return iroot[k]; }

    void transform(vector<mint> &a, int sign){
        const int n = a.size();
        assert(n > 0);
        assert((n & (n - 1)) == 0);
        assert(n <= maxN);
        int h = 0;
        while ((1U << h) < (unsigned int)(n)) h++;
        if(!sign){ // fft
            int len = 0;
            while (len < h) {
                if (h - len == 1) {
                    int p = 1 << (h - len - 1);
                    mint rot = 1;
                    for (int s = 0; s < (1 << len); s++) {
                        int offset = s << (h - len);
                        for (int i = 0; i < p; i++) {
                            auto l = a[i + offset];
                            auto r = a[i + offset + p] * rot;
                            a[i + offset] = l + r;
                            a[i + offset + p] = l - r;
                        }
                        if (s + 1 != (1 << len)) {
                            rot *= rate2[__builtin_ctz(~(unsigned int)(s))];
                        }
                    }
                    len++;
                } else {
                    int p = 1 << (h - len - 2);
                    mint rot = 1, imag = root[2];
                    for (int s = 0; s < (1 << len); s++) {
                        mint rot2 = rot * rot;
                        mint rot3 = rot2 * rot;
                        int offset = s << (h - len);
                        for (int i = 0; i < p; i++) {
                            ull mod2 = 1ULL * ntt_mod * ntt_mod;
                            ull a0 = a[i + offset].val;
                            ull a1 = 1ULL * a[i + offset + p].val * rot.val;
                            ull a2 = 1ULL * a[i + offset + 2 * p].val * rot2.val;
                            ull a3 = 1ULL * a[i + offset + 3 * p].val * rot3.val;
                            ull a1na3imag = 1ULL * mint(a1 + mod2 - a3).val * imag.val;
                            ull na2 = mod2 - a2;
                            a[i + offset] = mint(a0 + a2 + a1 + a3);
                            a[i + offset + p] = mint(a0 + a2 + (2 * mod2 - (a1 + a3)));
                            a[i + offset + 2 * p] = mint(a0 + na2 + a1na3imag);
                            a[i + offset + 3 * p] = mint(a0 + na2 + (mod2 - a1na3imag));
                        }
                        if (s + 1 != (1 << len)) {
                            rot *= rate3[__builtin_ctz(~(unsigned int)(s))];
                        }
                    }
                    len += 2;
                }
            }
        }else { // ifft
            int len = h;
            while (len) {
                if (len == 1) {
                    int p = 1 << (h - len);
                    mint irot = 1;
                    for (int s = 0; s < (1 << (len - 1)); s++) {
                        int offset = s << (h - len + 1);
                        for (int i = 0; i < p; i++) {
                            auto l = a[i + offset];
                            auto r = a[i + offset + p];
                            a[i + offset] = l + r;
                            a[i + offset + p] = mint(1ULL * (ntt_mod + l.val - r.val) * irot.val);
                        }
                        if (s + 1 != (1 << (len - 1))) {
                            irot *= irate2[__builtin_ctz(~(unsigned int)(s))];
                        }
                    }
                    len--;
                } else {
                    int p = 1 << (h - len);
                    mint irot = 1, iimag = iroot[2];
                    for (int s = 0; s < (1 << (len - 2)); s++) {
                        mint irot2 = irot * irot;
                        mint irot3 = irot2 * irot;
                        int offset = s << (h - len + 2);
                        for (int i = 0; i < p; i++) {
                            ull a0 = a[i + offset].val;
                            ull a1 = a[i + offset + p].val;
                            ull a2 = a[i + offset + 2 * p].val;
                            ull a3 = a[i + offset + 3 * p].val;
                            ull a2na3iimag = 1ULL * mint(1ULL * (ntt_mod + a2 - a3) * iimag.val).val;
                            a[i + offset] = mint(a0 + a1 + a2 + a3);
                            a[i + offset + p] = mint(a0 + (ntt_mod - a1) + a2na3iimag) * irot;
                            a[i + offset + 2 * p] = mint(a0 + a1 + (ntt_mod - a2) + (ntt_mod - a3)) * irot2;
                            a[i + offset + 3 * p] = mint(a0 + (ntt_mod - a1) + (ntt_mod - a2na3iimag)) * irot3;
                        }
                        if (s + 1 != (1 << (len - 2))) {
                            irot *= irate3[__builtin_ctz(~(unsigned int)(s))];
                        }
                    }
                    len -= 2;
                }
            }
        }
    }
};

NTT ntt;

void ntt_ifft(vector<mint>& a) {
    ntt.transform(a, 1);
    static vector<mint> inv_pow2 = []() {
        vector<mint> t(31, mint(1));
        mint inv2 = mint(2).inv();
        for (int i = 1; i < (int)t.size(); ++i) t[i] = t[i - 1] * inv2;
        return t;
    }();
    mint iz = inv_pow2[__builtin_ctz((unsigned)a.size())];
    for (auto& x : a) x *= iz;
}

mint ntt_inv_size(int n) {
    static vector<mint> inv_pow2 = []() {
        vector<mint> t(31, mint(1));
        mint inv2 = mint(2).inv();
        for (int i = 1; i < (int)t.size(); ++i) t[i] = t[i - 1] * inv2;
        return t;
    }();
    return inv_pow2[__builtin_ctz((unsigned)n)];
}

bool mod_sqrt(mint a, mint &x) {
    if (a == mint(0)) {
        x = mint(0);
        return true;
    }
    if (a.pow((ntt_mod - 1) >> 1) != mint(1)) return false;
    if (ntt_mod % 4 == 3) {
        x = a.pow((ntt_mod + 1) >> 2);
        return true;
    }
    int s = 0;
    int q = ntt_mod - 1;
    while ((q & 1) == 0) {
        ++s;
        q >>= 1;
    }
    mint z = 2;
    while (z.pow((ntt_mod - 1) >> 1) == mint(1)) ++z;
    mint c = z.pow(q);
    mint t = a.pow(q);
    mint r = a.pow((q + 1) >> 1);
    int m = s;
    while (t != mint(1)) {
        int i = 1;
        mint tt = t * t;
        while (i < m && tt != mint(1)) {
            tt *= tt;
            ++i;
        }
        mint b = c.pow(1LL << (m - i - 1));
        r *= b;
        c = b * b;
        t *= c;
        m = i;
    }
    x = r;
    return true;
}

struct poly {
    vector<mint> v;
    poly() = default;
    explicit poly(int n) : v(n) {};
    explicit poly(vector<mint> vv) : v(std::move(vv)) {};
    int size() const {return (int)v.size(); }
    void shrink() {
        while (!v.empty() && v.back() == mint(0)) v.pop_back();
    }
    poly cut(int len){
        if (len < (int)v.size()) v.resize(static_cast<unsigned long>(len));
        return *this;
    }
    inline mint& operator[] (int i) {return v[i]; }
    inline const mint& operator[] (int i) const {return v[i]; }
    poly& operator+=(const poly &a) {
        this->v.resize(max(size(), a.size()));
        for (int i = 0; i < a.size(); ++i) this->v[i] += a.v[i];
        return *this;
    }
    poly &operator+=(const mint &r) {
        if (v.empty()) v.resize(1);
        v[0] += r;
        return *this;
    }
    poly& operator-=(const poly &a) {
        this->v.resize(max(size(), a.size()));
        for (int i = 0; i < a.size(); ++i) this->v[i] -= a.v[i];
        return *this;
    }
    poly& operator*=(const poly &a) {
        const int n = size();
        const int m = a.size();
        if (n == 0 || m == 0) {
            v.clear();
            return *this;
        }
        if (1LL * n * m <= NTT_NAIVE_MUL_THRESHOLD && min(n, m) <= NTT_NAIVE_MUL_MIN_DIM) {
            vector<mint> res(n + m - 1);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    res[i + j] += v[i] * a.v[j];
                }
            }
            v = std::move(res);
            return *this;
        }
        int N = n + m - 1;
        int sz = 1;
        while(sz < N) sz <<= 1;
        this->v.resize(sz);
        ntt.transform(this->v, 0);
        if (this == &a) {
            for (int i = 0; i < sz; ++i) this->v[i] *= this->v[i];
        } else {
            static thread_local vector<mint> b;
            b.assign(a.v.begin(), a.v.end());
            b.resize(sz);
            ntt.transform(b, 0);
            for(int i = 0; i < sz; ++i) this->v[i] *= b[i];
        }
        ntt.transform(this->v, 1);
        this->v.resize(N);
        mint iz = ntt_inv_size(sz);
        for (int i = 0; i < N; i++) this->v[i] *= iz;
        return *this;
    }
    poly& operator/=(const poly &a){ return (*this *= a.inv()); }
    poly operator+(const poly &a) const { return poly(*this) += a; }
    poly operator+(const mint &v) const { return poly(*this) += v; }
    poly operator-(const poly &a) const { return poly(*this) -= a; }
    poly operator*(const poly &a) const { return poly(*this) *= a; }
    poly rev(int deg = -1) const {
        poly ret(*this);
        if (deg != -1) ret.v.resize(deg);
        reverse(ret.v.begin(), ret.v.end());
        return ret;
    }

    pair<poly, poly> divmod(const poly &a) const {
        poly f(*this), g(a);
        f.shrink();
        g.shrink();
        assert(!g.v.empty());
        if (f.size() < g.size()) return {poly(), f};
        int need = f.size() - g.size() + 1;
        poly q = (f.rev().pre(need) * g.rev().inv(need)).pre(need).rev();
        poly r = f - g * q;
        r = r.pre(g.size() - 1);
        r.shrink();
        return {q, r};
    }

    poly mod(const poly &a) const {
        return divmod(a).second;
    }

    mint eval(mint x) const {
        mint y = 0;
        for (int i = size() - 1; i >= 0; --i) y = y * x + v[i];
        return y;
    }

    poly pre(int sz) const {
        poly ret(sz);
        for (int i = 0; i < min<int>(sz, v.size()); ++i) {
            ret[i] = v[i];
        }
        return ret;
    }

    poly diff() const {
        const int n = (int)this->size();
        poly ret(max(0, n - 1));
        mint one(1), coeff(1);
        for (int i = 1; i < n; i++) {
            ret[i - 1] = v[i] * coeff;
            coeff += one;
        }
        return ret;
    }

    poly integral() const {
        const int n = (int)this->size();
        poly ret(n + 1);
        ret[0] = mint(0);
        static vector<mint> invs = {mint(0), mint(1)};
        if ((int)invs.size() <= n) {
            int old = (int)invs.size();
            invs.resize(n + 1);
            for (int i = old; i <= n; ++i) invs[i] = mint(ntt_mod - ntt_mod / i) * invs[ntt_mod % i];
        }
        for (int i = 0; i < n; i++) ret[i + 1] = v[i] * invs[i + 1];
        return ret;
    }

    poly inv(int deg = -1) const {
        assert(!v.empty() && v[0] != mint(0));
        if (deg == -1) deg = size();
        poly res(deg);
        res[0] = v[0].inv();
        for (int d = 1; d < deg; d <<= 1) {
            vector<mint> f(2 * d), g(2 * d);
            for (int i = 0; i < min(size(), 2 * d); ++i) f[i] = v[i];
            for (int i = 0; i < d; ++i) g[i] = res[i];
            ntt.transform(f, 0);
            ntt.transform(g, 0);
            for (int i = 0; i < 2 * d; ++i) f[i] *= g[i];
            ntt_ifft(f);
            fill(f.begin(), f.begin() + d, mint(0));
            ntt.transform(f, 0);
            for (int i = 0; i < 2 * d; ++i) f[i] *= g[i];
            ntt_ifft(f);
            for (int i = d; i < min(2 * d, deg); ++i) res[i] = -f[i];
        }
        return res.pre(deg);
    }

    poly log(int deg = -1) const {
        assert(!v.empty() && v[0] == mint(1));
        if (deg == -1) deg = (int)this->size();
        return (this->diff() * this->inv(deg)).pre(deg - 1).integral();
    }

    poly exp(int deg = -1) const {
        assert(v.size() == 0 || v[0] == mint(0));
        if (deg == -1) deg = v.size();
        static vector<mint> invs = {mint(0), mint(1)};
        auto ensure_invs = [&](int n) {
            if ((int)invs.size() <= n) {
                int old = (int)invs.size();
                invs.resize(n + 1);
                for (int i = old; i <= n; ++i) invs[i] = mint(ntt_mod - ntt_mod / i) * invs[ntt_mod % i];
            }
        };
        auto inplace_integral = [&](poly& f) {
            int n = f.size();
            ensure_invs(n);
            f.v.insert(f.v.begin(), mint(0));
            for (int i = 1; i <= n; ++i) f[i] *= invs[i];
        };
        poly b(vector<mint>{mint(1), (1 < size() ? v[1] : mint(0))});
        poly c(vector<mint>{mint(1)}), z1, z2(vector<mint>{mint(1), mint(1)});
        for (int m = 2; m < deg; m <<= 1) {
            poly y = b;
            y.v.resize(2 * m);
            ntt.transform(y.v, 0);
            z1 = z2;
            poly z(m);
            for (int i = 0; i < m; ++i) z[i] = y[i] * z1[i];
            ntt_ifft(z.v);
            fill(z.v.begin(), z.v.begin() + m / 2, mint(0));
            ntt.transform(z.v, 0);
            for (int i = 0; i < m; ++i) z[i] *= -z1[i];
            ntt_ifft(z.v);
            c.v.insert(c.v.end(), z.v.begin() + m / 2, z.v.end());
            z2 = c;
            z2.v.resize(2 * m);
            ntt.transform(z2.v, 0);

            poly x(m);
            for (int i = 0; i + 1 < m && i + 1 < size(); ++i) x[i] = v[i + 1] * mint(i + 1);
            x[m - 1] = mint(0);
            ntt.transform(x.v, 0);
            for (int i = 0; i < m; ++i) x[i] *= y[i];
            ntt_ifft(x.v);
            for (int i = 0; i + 1 < m; ++i) x[i] -= b[i + 1] * mint(i + 1);
            x.v.resize(2 * m);
            for (int i = 0; i + 1 < m; ++i) {
                x[m + i] = x[i];
                x[i] = mint(0);
            }
            ntt.transform(x.v, 0);
            for (int i = 0; i < 2 * m; ++i) x[i] *= z2[i];
            ntt_ifft(x.v);
            x.v.pop_back();
            inplace_integral(x);
            for (int i = m; i < min(size(), 2 * m); ++i) x[i] += v[i];
            fill(x.v.begin(), x.v.begin() + m, mint(0));
            ntt.transform(x.v, 0);
            for (int i = 0; i < 2 * m; ++i) x[i] *= y[i];
            ntt_ifft(x.v);
            b.v.insert(b.v.end(), x.v.begin() + m, x.v.end());
        }
        return b.pre(deg);
    }

    poly pow(long long k, int deg = -1) const {
        if (deg == -1) deg = size();
        poly ret(max(0, deg));
        if (deg <= 0) return ret;
        if (k == 0) {
            ret[0] = 1;
            return ret;
        }
        if (0 < k && k <= 64) {
            poly base = pre(deg);
            poly ans(1);
            ans[0] = 1;
            long long e = k;
            while (e > 0) {
                if (e & 1) {
                    ans *= base;
                    ans = ans.pre(deg);
                }
                e >>= 1;
                if (e == 0) break;
                base *= base;
                base = base.pre(deg);
            }
            ans = ans.pre(deg);
            if (ans.size() < deg) ans.v.resize(deg);
            return ans;
        }
        int lead = 0;
        while (lead < size() && v[lead] == mint(0)) lead++;
        if (lead == size()) return ret;
        long long shift_ll = 0;
        if (lead > 0) {
            if (k > (deg - 1) / lead) return ret;
            shift_ll = 1LL * lead * k;
        }
        poly f(size() - lead);
        mint inv_lead = v[lead].inv();
        for (int i = lead; i < size(); ++i) f[i - lead] = v[i] * inv_lead;
        int shift = static_cast<int>(shift_ll);
        int rem_deg = deg - shift;
        poly g = f.log(rem_deg);
        mint k_mint = mint(k);
        for (int i = 0; i < g.size(); ++i) g[i] *= k_mint;
        g = g.exp(rem_deg);
        mint coeff = v[lead].pow(k);
        for (int i = 0; i < g.size(); ++i) g[i] *= coeff;
        for (int i = 0; i < g.size(); ++i) ret[i + shift] = g[i];
        return ret;
    }

    poly sqrt(int deg = -1) const {
        if (deg == -1) deg = size();
        poly ret(max(0, deg));
        if (deg <= 0) return ret;
        int lead = 0;
        while (lead < size() && v[lead] == mint(0)) lead++;
        if (lead == size()) return ret;
        if (lead & 1) return poly();
        mint sq0;
        if (!mod_sqrt(v[lead], sq0)) return poly();
        int shift = lead >> 1;
        if (shift >= deg) return ret;
        int rem_deg = deg - shift;
        poly f(size() - lead);
        mint inv_lead = v[lead].inv();
        for (int i = lead; i < size(); ++i) f[i - lead] = v[i] * inv_lead;
        poly s(1);
        s[0] = 1;
        mint inv2 = mint(2).inv();
        for (int k = 1; k < rem_deg; k <<= 1) {
            poly ns = (s + (f.pre(k << 1) * s.inv(k << 1)).pre(k << 1)).pre(k << 1);
            for (int i = 0; i < ns.size(); ++i) ns[i] *= inv2;
            s = ns;
        }
        s = s.pre(rem_deg);
        for (int i = 0; i < s.size(); ++i) ret[i + shift] = s[i] * sq0;
        return ret;
    }

    vector<mint> multipoint_eval(const vector<mint> &xs) const;
};

/**
 * @brief NTT・形式的冪級数(NTT/FPS)
 */

#endif
