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
    modint& operator+=(modint a){ val += a.val; if(val >= M) val -= M; return *this;}
    modint& operator-=(modint a){ if(val < a.val) val += M-a.val; else val -= a.val; return *this;}
    modint& operator*=(modint a){ val = (u64)val*a.val%M; return *this;}
    modint& operator/=(modint a){ return (*this) *= a.inv();}
    modint operator+(modint a) const {return modint(val) +=a;}
    modint operator-(modint a) const {return modint(val) -=a;}
    modint operator*(modint a) const {return modint(val) *=a;}
    modint operator/(modint a) const {return modint(val) /=a;}
    modint operator-(){ return modint(M-val);}
    bool operator==(const modint a) const {return val == a.val;}
    bool operator!=(const modint a) const {return val != a.val;}
    bool operator<(const modint a) const {return val < a.val;}
};

using mint = modint<ntt_mod>;

class NTT {
    static constexpr int max_base = 20, maxN = 1 << max_base; // N <= 524288 * 2
    mint roots[maxN << 1], iroots[maxN << 1];
public:
    NTT() {
        for (int i = 0; i <= max_base; ++i) {
            const int offset = (1 << i) - 1;
            const mint g = mint(ntt_root).pow((ntt_mod)/(1 << i)), ginv = g.inv();
            mint x = 1, y = 1;
            for (int j = 0; j < 1 << i; ++j) {
                roots[offset+j] = x;
                x *= g;
                iroots[offset+j] = y;
                y *= ginv;
            }
        }
    }

    void transform(vector<mint> &a, int sign){
        const int n = a.size();
        if(!sign){ // fft
            for(int k = n >> 1; k >= 1; k >>= 1){
                for (int i = 0; i < n; i += k << 1) {
                    for (int j = 0; j < k; ++j) {
                        const mint tmp = a[i+j]-a[i+j+k];
                        a[i+j] += a[i+j+k];
                        a[i+j+k] = tmp*roots[(k << 1)-1+j];
                    }
                }
            }
        }else { // ifft
            for(int k = 1; k <= (n >> 1); k <<= 1){
                for (int i = 0; i < n; i += k << 1) {
                    for (int j = 0; j < k; ++j) {
                        a[i+j+k] *= iroots[(k << 1)-1+j];
                        const mint tmp = a[i+j]-a[i+j+k];
                        a[i+j] += a[i+j+k];
                        a[i+j+k] = tmp;
                    }
                }
            }
            const mint x = mint(n).inv();
            for (auto &&i : a) i *= x;
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