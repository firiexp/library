#ifndef FIRIEXP_LIBRARY_UTIL_MODINT_ARBITRARY_CPP
#define FIRIEXP_LIBRARY_UTIL_MODINT_ARBITRARY_CPP

class modint {
    static uint &mod() { static uint mod_ = 0; return mod_; }
public:
    uint val;
    static modint raw(int v) { modint x; x.val = v; return x; }
    modint() : val(0) {}
    template <class T>
    modint(T v) { ll x = (ll)(v % (ll)(M())); if (x < 0) x += M(); val = uint(x); }
    modint(bool v) { val = ((unsigned int)(v) % M()); }
    static uint get_mod() { return M(); }
    static uint M() { return mod(); }
    static void set_mod(uint x) { mod() = x; }
    uint &value() noexcept { return val; }
    const uint &value() const noexcept { return val; }
    modint &operator++() { val++; if (val == M()) val = 0; return *this; }
    modint &operator--() { if (val == 0) val = M(); val--; return *this; }
    modint operator++(int) { modint result = *this; ++*this; return result; }
    modint operator--(int) { modint result = *this; --*this; return result; }
    modint &operator+=(const modint &b) { val += b.val; if (val >= M()) val -= M(); return *this; }
    modint &operator-=(const modint &b) { val -= b.val; if (val >= M()) val += M(); return *this; }
    modint &operator*=(const modint &b) { val = (ull)val * b.val % M(); return *this; }
    modint &operator/=(const modint &b) { return *this = *this * b.inv(); }
    modint operator+() const { return *this; }
    modint operator-() const { return modint() - *this; }
    modint pow(long long n) const { modint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1; } return r; }
    modint inv() const { return pow(M() - 2); }
    friend modint operator+(const modint &a, const modint &b) { return modint(a) += b; }
    friend modint operator-(const modint &a, const modint &b) { return modint(a) -= b; }
    friend modint operator*(const modint &a, const modint &b) { return modint(a) *= b; }
    friend modint operator/(const modint &a, const modint &b) { return modint(a) /= b; }
    friend bool operator==(const modint &a, const modint &b) { return a.val == b.val; }
    friend bool operator!=(const modint &a, const modint &b) { return a.val != b.val; }
};
using mint = modint;
#define FIRIEXP_LIBRARY_MINT_ALIAS_DEFINED

/**
 * @brief modint(任意MOD)
 */

#endif
