class modint {
    static u32 &mod() { static u32 mod_ = 0; return mod_; }
public:
    u32 val;
    modint(const u32 x = 0) : val(x % M()) {}
    u32 &value() noexcept { return val; }
    const u32 &value() const noexcept { return val; }
    modint operator+(const modint b) const { return modint(*this) += b; }
    modint operator-(const modint b) const { return modint(*this) -= b; }
    modint operator*(const modint b) const { return modint(*this) *= b; }
    modint operator/(const modint b) const { return modint(*this) /= b; }
    modint &operator+=(const modint b) { val += b.val; if (val >= M()) val -= M(); return *this; }
    modint &operator-=(const modint b) { if (val < b.val) val += M(); val -= b.val; return *this; }
    modint &operator*=(const modint b) { val = (u64)val * b.val % M(); return *this; }
    modint pow(ll n) const { modint x = *this, r = 1; while(n){ if(n&1) r *= x; x *= x; n >>= 1; } return r; }
    modint &operator/=(modint b) { return *this *= b.pow(M()-2); }
    static void set_mod(const u32 x) { mod() = x; }
    static int M() { return mod(); }
};
using mint = modint;