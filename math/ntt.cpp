constexpr int ntt_mod = 998244353, ntt_root = 3;
// 1012924417 -> 5, 924844033 -> 5
// 998244353  -> 3, 897581057 -> 3
// 645922817  -> 3;
template<u32 M = 1000000007>
struct modint{
    u32 val;
    modint(): val(0){}
    template<typename T>
    modint(T t){t %= (T)M; if(t < 0) t += (T)M; val = t;}

    modint pow(ll k) const {
        modint res(1), x(val);
        while(k){
            if(k&1) res *= x;
            x *= x;
            k >>= 1;
        }
        return res;
    }
    template<typename T>
    modint& operator=(T t){t %= (T)M; if(t < 0) t += (T)M; val = t; return *this; }
    modint inv() const {return pow(M-2);}
    modint& operator+=(const modint& a){ val += a.val; if(val >= M) val -= M; return *this;}
    modint& operator-=(const modint& a){ if(val < a.val) val += M-a.val; else val -= a.val; return *this;}
    modint& operator*=(const modint& a){ val = ((u64)val*a.val)%M; return *this;}
    modint& operator/=(const modint& a){ return (*this) *= a.inv();}
    modint operator+(modint& a) const {return modint(val) +=a;}
    modint operator-(modint& a) const {return modint(val) -=a;}
    modint operator*(modint& a) const {return modint(val) *=a;}
    modint operator/(modint& a) const {return modint(val) /=a;}
    modint operator-(){ return modint(M-val);}
    bool operator==(const modint &a) const {return val == a.val;}
    bool operator!=(const modint &a) const {return val != a.val;}
    bool operator<(const modint &a) const {return val < a.val;}
};

using mint = modint<ntt_mod>;

class NTT {
    static constexpr int max_base = 20, maxN = 1 << max_base; // N <= 524288 * 2
    mint sum_e[30], sum_ie[30];
public:
    NTT() {
        mint es[30], ies[30];
        int cnt2 = __builtin_ctz(ntt_mod-1);
        mint e = mint(ntt_root).pow((ntt_mod-1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 2; i--){
            es[i-2] = e;
            ies[i-2] = ie;
            e *= e;
            ie *= ie;
        }
        mint now = 1, nowi = 1;
        for (int i = 0; i < cnt2 - 2; i++) {
            sum_e[i] = es[i] * now;
            now *= ies[i];
            sum_ie[i] = ies[i] * nowi;
            nowi *= es[i];
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
                        a[i+offset] = l+r;
                        a[i+offset+p] = l-r;
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
                        a[i+offset] = l+r;
                        a[i+offset+p] = (l-r)*inow;
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
        int k = 1;
        while(k < n){
            k *= 2;
            poly ff(k);
            for (int i = 0; i < min(k, n); ++i) {
                ff[i] = this->v[i];
            }
            poly nr = (r*r*ff).cut(k);
            for (int i = 0; i < k/2; ++i) {
                nr[i] = (r[i]+r[i]-nr[i]);
                nr[i+k/2] = -nr[i+k/2];
            }
            r = nr;
        }
        r.v.resize(n);
        return r;
    }
};