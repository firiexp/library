#define STANDALONE

#include <cassert>
#include <cstdint>
#include <random>
#include <vector>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include "../util/modint_arbitrary.cpp"

void check_pair(uint a, uint b, uint mod) {
    mint x(a), y(b);
    assert((x * y).val == (ull)a * b % mod);
    mint square = x;
    square *= square;
    assert(square.val == (ull)a * a % mod);
    if (mod > (1U << 31)) return;
    assert(mint::raw(a).val == a);
    assert((x + y).val == ((ull)a + b) % mod);
    assert((x - y).val == ((ull)a + mod - b) % mod);
    assert((-x).val == (a == 0 ? 0 : mod - a));
    assert((++x).val == ((ull)a + 1) % mod);
    assert((--x).val == a);
    assert(mint(-(ll)a).val == (a == 0 ? 0 : mod - a));
    ull power = 1 % mod;
    for (int i = 0; i < 11; ++i) power = power * a % mod;
    assert(x.pow(11).val == power);
    assert(x.pow(0).val == 1 % mod);
}

int main() {
    mt19937_64 rng(215);
    vector<uint> mods{1, 2, 3, 4, 17, 255, 256, 257, 65535, 65536, 65537,
                      998244353, 1000000007, 2147483646, 2147483647, 2147483648U,
                      4294967291U, 4294967295U};
    for (int i = 0; i < 100; ++i) mods.push_back(1 + rng() % (1ULL << 31));
    for (uint mod : mods) {
        mint::set_mod(mod);
        assert(mint::M() == mod && mint::get_mod() == mod);
        vector<uint> edge{0, mod - 1, mod / 2, 1 % mod};
        for (uint a : edge) for (uint b : edge) check_pair(a, b, mod);
        for (int i = 0; i < 10000; ++i) check_pair(rng() % mod, rng() % mod, mod);
    }
    for (int i = 0; i < 10000; ++i) {
        uint mod = mods[rng() % mods.size()];
        mint::set_mod(mod);
        check_pair(rng() % mod, rng() % mod, mod);
    }
    for (uint mod : {2U, 17U, 998244353U, 1000000007U, 2147483647U}) {
        mint::set_mod(mod);
        for (int i = 0; i < 1000; ++i) {
            mint a(1 + rng() % (mod - 1)), b(rng() % mod);
            assert((a * a.inv()).val == 1);
            assert(b / a * a == b);
        }
    }
}
