#ifndef FIRIEXP_LIBRARY_UTIL_MODINT_CPP
#define FIRIEXP_LIBRARY_UTIL_MODINT_CPP

template <uint Mod>
struct modint {
    uint val;
public:
    static modint raw(int v) { modint x; x.val = v; return x; }
    static constexpr uint get_mod() { return Mod; }
    static constexpr uint M() { return Mod; }
    modint() : val(0) {}
    template <class T>
    modint(T v) { ll x = (ll)(v % (ll)(Mod)); if (x < 0) x += Mod; val = uint(x); }
    modint(bool v) { val = ((unsigned int)(v) % Mod); }
    uint &value() noexcept { return val; }
    const uint &value() const noexcept { return val; }
    modint& operator++() { val++; if (val == Mod) val = 0; return *this; }
    modint& operator--() { if (val == 0) val = Mod; val--; return *this; }
    modint operator++(int) { modint result = *this; ++*this; return result; }
    modint operator--(int) { modint result = *this; --*this; return result; }
    modint& operator+=(const modint& b) { val += b.val; if (val >= Mod) val -= Mod; return *this; }
    modint& operator-=(const modint& b) { val -= b.val; if (val >= Mod) val += Mod; return *this; }
    modint& operator*=(const modint& b) { ull z = val; z *= b.val; val = (uint)(z % Mod); return *this; }
    modint& operator/=(const modint& b) { return *this = *this * b.inv(); }
    modint operator+() const { return *this; }
    modint operator-() const { return modint() - *this; }
    modint pow(long long n) const { modint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }
    modint inv() const { return pow(Mod - 2); }
    friend modint operator+(const modint& a, const modint& b) { return modint(a) += b; }
    friend modint operator-(const modint& a, const modint& b) { return modint(a) -= b; }
    friend modint operator*(const modint& a, const modint& b) { return modint(a) *= b; }
    friend modint operator/(const modint& a, const modint& b) { return modint(a) /= b; }
    friend bool operator==(const modint& a, const modint& b) { return a.val == b.val; }
    friend bool operator!=(const modint& a, const modint& b) { return a.val != b.val; }
};
using mint = modint<MOD>;
#define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED

/**
 * @brief modint(固定MOD)
 */

#endif
