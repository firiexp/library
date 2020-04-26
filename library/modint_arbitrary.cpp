struct modint {
    ll val;
    static ll &mod(){
        static ll mod_ = 0;
        return mod_;
    }

    static void set_mod(const ll x) { mod() = x; }
    static ll M() {return mod(); }

    modint(const ll x) : val(x) {
        val = x%M();
        while(val < 0) val += M();
    }

    modint operator+(const modint a) const { return modint(*this) += a; }
    modint operator-(const modint a) const { return modint(*this) -= a; }
    modint operator*(const modint a) const { return modint(*this) *= a; }
    modint operator/(const modint a) const { return modint(*this) /= a; }
    modint operator-() const { return {M()-val}; }
    modint inv() const {
        ll u = 1, v = 0, s = 0, t = 1, m = M(), x = val;
        while (x) {ll q = M()/x; swap(s -= q*u, u); swap(t -= q*v, v); swap(m -= q*x, x); }
        if(s < 0) s += M();
        return modint(s);
    }
    modint pow(ll n){
        ll u = 1, xx = val;
        while (n > 0){ if (n&1) u = u * xx % M(); xx = xx * xx % M(); n >>= 1; }
        return modint(u);
    }
    modint& operator+=(const modint a){ val += a.val; if(val >= M()) val -= M(); return *this; }
    modint& operator-=(const modint a){ val += a.val; if(val < 0) val += M(); return *this; }
    modint& operator*=(const modint a){ val = val * a.val % M(); return *this; }
    modint& operator/=(const modint a){ val = val * a.inv().val % M(); return *this;}

    modint& operator=(const int& x){
        val = x%M();
        while(val < 0) val += M();
        return *this;
    }
};
using mint = modint;
