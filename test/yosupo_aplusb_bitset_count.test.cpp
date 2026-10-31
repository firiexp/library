#define STANDALONE

#include <algorithm>
#include <cassert>
#include <cstring>
#include <random>
#include <vector>
using namespace std;

#include "../datastructure/bitset/dynamic_bitset.cpp"
#include "../datastructure/bitset/static_bitset.cpp"
#include "../datastructure/bitset/dynamic_bitset.cpp"
#include "../datastructure/bitset/static_bitset.cpp"

template<int N>
void check() {
    mt19937 rng(N + 210);
    for (int shape = 0; shape < 4; ++shape) {
        DynamicBitset dynamic(N);
        StaticBitset<N> fixed;
        vector<bool> expected(N);
        int count = 0;
        for (int i = 0; i < N; ++i) {
            bool bit = shape == 0 ? false : shape == 1 ? true : shape == 2 ? i % 2 : rng() & 1;
            dynamic.assign(i, bit);
            fixed.assign(i, bit);
            expected[i] = bit;
            count += bit;
        }
        assert(dynamic.count() == count);
        assert(fixed.count() == count);
        for (int step = 0; step < 100; ++step) {
            if constexpr (N > 0) {
                int k = rng() % N;
                count += expected[k] ? -1 : 1;
                expected[k] = !expected[k];
                dynamic.flip(k);
                fixed.flip(k);
            }
            assert(dynamic.count() == count);
            assert(fixed.count() == count);
        }
        dynamic.flip();
        fixed.flip();
        assert(dynamic.count() == N - count);
        assert(fixed.count() == N - count);
        dynamic <<= 1;
        fixed <<= 1;
        if constexpr (N > 0) count += !expected[N - 1];
        assert(dynamic.count() == N - count);
        assert(fixed.count() == N - count);
        dynamic.set();
        fixed.set();
        assert(dynamic.count() == N);
        assert(fixed.count() == N);
        dynamic.reset();
        fixed.reset();
        assert(dynamic.count() == 0);
        assert(fixed.count() == 0);
    }
}

int main() {
    check<0>();
    check<1>();
    check<63>();
    check<64>();
    check<65>();
    check<127>();
    check<128>();
    check<129>();
    check<8128>();
    check<8129>();
    check<8191>();
    check<8192>();
    check<8193>();
    check<1048577>();
}
