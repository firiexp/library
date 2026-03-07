#include <cassert>

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

class NTT {
    static constexpr int max_base = 20, maxN = 1 << max_base; // N <= 524288 * 2
    mint sum_e[30], sum_ie[30];
public:
    mint es[30], ies[30];
    NTT() {
        int cnt2 = __builtin_ctz(ntt_mod-1);
        mint e = mint(ntt_root).pow((ntt_mod-1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 0; i--){
            es[i] = e; ies[i] = ie;
            e *= e; ie *= ie;
        }
        mint now = 1, nowi = 1;
        for (int i = 0; i < cnt2 - 2; i++) {
            sum_e[i] = es[i+2] * now; now *= ies[i+2];
            sum_ie[i] = ies[i+2] * nowi; nowi *= es[i+2];
        }
    }

    void transform(vector<mint> &a, int sign){
        const int n = a.size();
        int h = 0;
        while ((1U << h) < (unsigned int)(n)) h++;
        if(!sign){ // fft
            for (int ph = 1; ph <= h; ph++) {
                int w = 1 << (ph-1), p = 1 << (h-ph);
                mint now = 1;
                for (int s = 0; s < w; s++) {
                    int offset = s << (h-ph+1);
                    for (int i = 0; i < p; i++) {
                        auto l = a[i+offset], r = a[i+offset+p]*now;
                        a[i+offset] = l+r, a[i+offset+p] = l-r;
                    }
                    now *= sum_e[__builtin_ctz(~(unsigned int)(s))];
                }
            }
        }else { // ifft
            for (int ph = h; ph >= 1; ph--) {
                int w = 1 << (ph-1), p = 1 << (h-ph);
                mint inow = 1;
                for (int s = 0; s < w; s++) {
                    int offset = s << (h-ph+1);
                    for (int i = 0; i < p; i++) {
                        auto l = a[i+offset], r = a[i+offset+p];
                        a[i+offset] = l+r, a[i+offset+p] = (l-r)*inow;
                    }
                    inow *= sum_ie[__builtin_ctz(~(unsigned int)(s))];
                }
            }
        }
    }
};

NTT ntt;

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
    poly cut(int len){
        if(len < v.size()) v.resize(static_cast<unsigned long>(len));
        return *this;
    }
    inline mint& operator[] (int i) {return v[i]; }
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
            vector<mint> b = a.v;
            b.resize(sz);
            ntt.transform(b, 0);
            for(int i = 0; i < sz; ++i) this->v[i] *= b[i];
        }
        ntt.transform(this->v, 1);
        this->v.resize(N);
        static vector<mint> inv_pow2 = []() {
            vector<mint> t(31, mint(1));
            mint inv2 = mint(2).inv();
            for (int i = 1; i < (int)t.size(); ++i) t[i] = t[i - 1] * inv2;
            return t;
        }();
        mint iz = inv_pow2[__builtin_ctz((unsigned)sz)];
        for (int i = 0; i < N; i++) this->v[i] *= iz;
        return *this;
    }
    poly& operator/=(const poly &a){ return (*this *= a.inv()); }
    poly operator+(const poly &a) const { return poly(*this) += a; }
    poly operator+(const mint &v) const { return poly(*this) += v; }
    poly operator-(const poly &a) const { return poly(*this) -= a; }
    poly operator*(const poly &a) const { return poly(*this) *= a; }

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
        int n = size();
        if(deg == -1) deg = v.size();
        poly r(1);
        r[0] = (this->v[0]).inv();
        for (int k = 1; k < deg; k <<= 1) {
            poly ff(2*k);
            for (int i = 0; i < min(k*2, n); ++i) ff[i] = this->v[i];
            poly nr = (r*r*ff).cut(k*2);
            for (int i = 0; i < k; ++i) {
                nr[i] = (r[i]+r[i]-nr[i]);
                nr[i+k] = -nr[i+k];
            }
            r = nr;
        }
        return r.pre(deg);
    }

    poly log(int deg = -1) const {
        assert(!v.empty() && v[0] == mint(1));
        if (deg == -1) deg = (int)this->size();
        return (this->diff() * this->inv(deg)).pre(deg - 1).integral();
    }

    poly exp(int deg = -1) const {
        assert(v.size() == 0 || v[0] == mint(0));
        if (deg == -1) deg = v.size();
        poly ret(1); ret[0] = 1;
        for (int i = 1; i < deg; i <<= 1) {
            ret = (ret * (pre(i << 1) + mint(1) - ret.log(i << 1))).pre(i << 1);
        }
        return ret.pre(deg);
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
};
