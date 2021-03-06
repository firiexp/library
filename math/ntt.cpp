constexpr int ntt_mod = 998244353, ntt_root = 3;
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
    poly& operator-=(const poly &a) {
        this->v.resize(max(size(), a.size()));
        for (int i = 0; i < a.size(); ++i) this->v[i] -= a.v[i];
        return *this;
    }
    poly& operator*=(poly a) {
        int N = size()+a.size()-1;
        int sz = 1;
        while(sz < N) sz <<= 1;
        this->v.resize(sz); a.v.resize(sz);
        ntt.transform(this->v, 0); ntt.transform(a.v, 0);
        for(int i = 0; i < sz; ++i) this->v[i] *= a.v[i];
        ntt.transform(this->v, 1);
        this->v.resize(N);
        mint iz = mint(sz).inv();
        for (int i = 0; i < N; i++) this->v[i] *= iz;
        return *this;
    }
    poly& operator/=(const poly &a){ return (*this *= a.inv()); }
    poly operator+(const poly &a) const { return poly(*this) += a; }
    poly operator-(const poly &a) const { return poly(*this) -= a; }
    poly operator*(const poly &a) const { return poly(*this) *= a; }

    poly inv() const {
        int n = size();
        poly r(1);
        r[0] = (this->v[0]).inv();
        for (int k = 1; k < n; k <<= 1) {
            poly ff(2*k);
            for (int i = 0; i < min(k*2, n); ++i) ff[i] = this->v[i];
            poly nr = (r*r*ff).cut(k*2);
            for (int i = 0; i < k; ++i) {
                nr[i] = (r[i]+r[i]-nr[i]);
                nr[i+k] = -nr[i+k];
            }
            r = nr;
        }
        r.v.resize(n);
        return r;
    }
};