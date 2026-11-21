#define STANDALONE

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include <charconv>
#include "../util/fastio.cpp"
#include "../math/extgcd.cpp"

namespace fixed_modint_test {
static constexpr uint MOD = 998244353;
#include "../math/modular/modint.cpp"
}

namespace dynamic_modint_test {
#include "../math/modular/modint_arbitrary.cpp"
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

template<class Mint>
void check_division(uint a, uint b, uint inverse) {
    Mint divisor = b;
    assert(divisor.inv().value() == inverse);
    uint expected = (ull)a * inverse % Mint::M();
    assert((Mint(a) / divisor).value() == expected);
    Mint quotient = a;
    quotient /= divisor;
    assert(quotient.value() == expected);
    divisor /= divisor;
    assert(divisor == Mint(1));
}

template<uint Mod>
void check_both(uint a, uint b, uint inverse) {
    dynamic_modint_test::mint::set_mod(Mod);
    check_division<fixed_modint_test::modint<Mod>>(a, b, inverse);
    check_division<dynamic_modint_test::mint>(a, b, inverse);
}

template<uint Mod>
void check_small_moduli() {
    for (uint b = 0; b < Mod; ++b) {
        uint inverse = 0;
        while (inverse < Mod && b * inverse % Mod != 1 % Mod) ++inverse;
        if (inverse == Mod) continue;
        for (uint a = 0; a < Mod; ++a) check_both<Mod>(a, b, inverse);
    }
    if constexpr (Mod > 1) check_small_moduli<Mod - 1>();
}

int main() {
    dynamic_modint_test::mint::set_mod(998244353);
    common_check<fixed_modint_test::mint>();
    common_check<dynamic_modint_test::mint>();
    check_small_moduli<32>();
    check_both<1000000000>(999999998, 3, 666666667);
    check_both<1U << 31>(2147483646, 2147483647, 2147483647);
    check_both<4294967295U>(4294967294U, 2, 2147483648U);
}
