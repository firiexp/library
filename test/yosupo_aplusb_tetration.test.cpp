#define STANDALONE

#include <cassert>
#include <climits>
#include <type_traits>
#include <vector>
using std::vector;
using ll = long long;
using ull = unsigned long long;

#include "../math/modular/tetration.cpp"

void check(ll a, ll n, ll mod, ll residue, bool reaches_mod) {
    assert(tetration(a, n, mod) == residue);
    bool large = !reaches_mod;
    ull lifted = tetration(a, n, mod, large);
    assert(large == reaches_mod);
    assert(lifted == static_cast<ull>(residue) + (reaches_mod ? mod : 0));
}

int main() {
    for (ll a = 0; a <= 15; ++a) {
        ll power = 1;
        for (ll i = 0; i < a; ++i) power *= a;
        for (ll mod = 1; mod <= 160; ++mod) {
            check(a, 0, mod, 1 % mod, 1 >= mod);
            check(a, 1, mod, a % mod, a >= mod);
            check(a, 2, mod, power % mod, power >= mod);
        }
    }
    for (ll mod = 65535; mod <= 65537; ++mod) {
        check(2, 4, mod, 65536 % mod, 65536 >= mod);
    }
    check(1LL << 32, 2, 998244353, 122371506, true);
    check(5000000000LL, 2, 10, 0, true);
    check(LLONG_MAX, 1, LLONG_MAX - 1, 1, true);
    check(LLONG_MAX, 2, LLONG_MAX - 24, 86762353606963200LL, true);
    check(31, 3, LLONG_MAX, 8732241942972972063LL, true);
    check(49, 3, LLONG_MAX, 5920772039431037537LL, true);
    check(3, 4, 1LL << 62, 2487664236534860091LL, true);
    check(0, LLONG_MAX, 1, 0, false);
    check(0, LLONG_MAX - 1, 1, 0, true);
    check(1, LLONG_MAX, LLONG_MAX, 1, false);
    check(2, LLONG_MAX, 1LL << 62, 0, true);
    check(LLONG_MAX - 1, LLONG_MAX, LLONG_MAX, 1, true);
}
