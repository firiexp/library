class modint {
    static uint &mod() { static uint mod_ = 0; return mod_; }
public:
    uint val;
    modint(const uint x = 0) : val(x % M()) {}
    uint &value() noexcept { return val; }
    const uint &value() const noexcept { return val; }
    modint operator+(const modint b) const { return modint(*this) += b; }
    modint operator-(const modint b) const { return modint(*this) -= b; }
    modint operator*(const modint b) const { return modint(*this) *= b; }
    modint operator/(const modint b) const { return modint(*this) /= b; }
    modint &operator+=(const modint b) { val += b.val; if (val >= M()) val -= M(); return *this; }
    modint &operator-=(const modint b) { if (val < b.val) val += M(); val -= b.val; return *this; }
    modint &operator*=(const modint b) { val = (ull)val * b.val % M(); return *this; }
    modint pow(ll n) const { modint x = *this, r = 1; while(n){ if(n&1) r *= x; x *= x; n >>= 1; } return r; }
    modint &operator/=(modint b) { return *this *= b.pow(M()-2); }
    static void set_mod(const uint x) { mod() = x; }
    static int M() { return mod(); }
};
using mint = modint;