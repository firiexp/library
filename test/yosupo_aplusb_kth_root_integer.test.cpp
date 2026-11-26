#define STANDALONE

#include <cassert>
#include <climits>
#include <initializer_list>
using ull = unsigned long long;
#include "../math/kth_root_integer.cpp"

__uint128_t power(ull base, int k) {
    __uint128_t value = 1;
    for (int i = 0; i < k; ++i) {
        value *= base;
        if (value > ULLONG_MAX) break;
    }
    return value;
}

void check_boundary(ull base, int k) {
    __uint128_t value = power(base, k);
    if (value > ULLONG_MAX) return;
    ull a = value;
    assert(kth_root_integer(a - 1, k) == base - 1);
    assert(kth_root_integer(a, k) == base);
    if (a < ULLONG_MAX) assert(kth_root_integer(a + 1, k) == base + (k == 1));
}

int main() {
    for (int k = 1; k <= 64; ++k) {
        assert(kth_root_integer(0, k) == 0);
        assert(kth_root_integer(1, k) == 1);
        assert(kth_root_integer(2, k) == (k == 1 ? 2ULL : 1ULL));

        ull last = kth_root_integer(ULLONG_MAX, k);
        assert(power(last, k) <= ULLONG_MAX);
        if (last < ULLONG_MAX) assert(power(last + 1, k) > ULLONG_MAX);
        for (ull base = 1; base <= 64; ++base) check_boundary(base, k);
        if (last > 1) check_boundary(last - 1, k);
        check_boundary(last, k);
    }
    for (ull k : {65ULL, 1000000000ULL, (1ULL << 32) + 1, 1ULL << 63, ULLONG_MAX}) {
        assert(kth_root_integer(0, k) == 0);
        assert(kth_root_integer(1, k) == 1);
        assert(kth_root_integer(2, k) == 1);
        assert(kth_root_integer(ULLONG_MAX, k) == 1);
    }
}
