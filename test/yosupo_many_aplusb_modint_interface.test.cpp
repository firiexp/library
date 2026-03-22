#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include "../util/fastio.cpp"

namespace fixed_modint_test {
static constexpr uint MOD = 998244353;
#include "../util/modint.cpp"
}

namespace dynamic_modint_test {
#include "../util/modint_arbitrary.cpp"
}

template <class Mint>
void common_check() {
    assert(Mint::get_mod() == 998244353);
    assert(Mint::M() == 998244353);

    Mint zero;
    assert(zero.value() == 0);
    assert(zero.val == 0);

    Mint a = -1;
    Mint b = Mint::raw(5);
    assert(a.value() == 998244352);
    assert(b.value() == 5);

    assert((+b).value() == 5);
    assert((-b).value() == 998244348);
    assert((Mint(true) + Mint(false)).value() == 1);
    assert((a + b).value() == 4);
    assert((a - b).value() == 998244347);
    assert((Mint(3) * Mint(7)).value() == 21);
    assert((Mint(21) / Mint(7)).value() == 3);
    assert(Mint(3).pow(5).value() == 243);
    assert((Mint(5) * Mint(5).inv()).value() == 1);

    Mint c = Mint::raw(998244352);
    assert((++c).value() == 0);
    assert((c++).value() == 0);
    assert(c.value() == 1);
    assert((--c).value() == 0);
    assert((c--).value() == 0);
    assert(c.value() == 998244352);

    assert(Mint(42) == Mint(42));
    assert(Mint(42) != Mint(24));
}

int main() {
    dynamic_modint_test::mint::set_mod(998244353);
    common_check<fixed_modint_test::mint>();
    common_check<dynamic_modint_test::mint>();

    Scanner in;
    Printer out;
    int t;
    in.read(t);
    while (t--) {
        ll a, b;
        in.read(a, b);
        out.println(a + b);
    }
    return 0;
}
