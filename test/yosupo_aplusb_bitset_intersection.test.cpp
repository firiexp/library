#define STANDALONE

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <new>
#include <random>
#include <vector>
using namespace std;

#include "../datastructure/static_bitset.cpp"
#include "../datastructure/dynamic_bitset.cpp"

size_t allocations = 0;

void *operator new(size_t n) {
    ++allocations;
    if (void *p = malloc(n ? n : 1)) return p;
    throw bad_alloc();
}

void *operator new[](size_t n) { return ::operator new(n); }
void operator delete(void *p) noexcept { free(p); }
void operator delete[](void *p) noexcept { free(p); }
void operator delete(void *p, size_t) noexcept { free(p); }
void operator delete[](void *p, size_t) noexcept { free(p); }

template<class T>
void check_pair(const T &a, const T &b, const vector<bool> &va, const vector<bool> &vb) {
    int expected = 0, count_a = 0;
    for (int i = 0; i < a.size(); ++i) {
        expected += va[i] && vb[i];
        count_a += va[i];
    }
    size_t before = allocations;
    assert(a.count_and(b) == expected);
    assert(b.count_and(a) == expected);
    assert(a.intersects(b) == (expected != 0));
    assert(b.intersects(a) == (expected != 0));
    assert(a.count_and(a) == count_a);
    assert(a.intersects(a) == (count_a != 0));
    assert(allocations == before);
    assert(a.count_and(b) == (a & b).count());
    assert(a.intersects(b) == (a & b).any());
    for (int i = 0; i < a.size(); ++i) {
        assert(a.test(i) == va[i]);
        assert(b.test(i) == vb[i]);
    }
}

template<int N>
void check_size() {
    mt19937 rng(N + 205);
    for (int shape = 0; shape < 8; ++shape) {
        DynamicBitset a(N), b(N);
        StaticBitset<N> sa, sb;
        vector<bool> va(N), vb(N);
        for (int i = 0; i < N; ++i) {
            bool x = shape == 0 ? false : shape < 3 ? true : shape == 3 ? i % 2 : rng() & 1;
            bool y = shape == 1 ? true : shape < 3 ? false : shape == 3 ? !(i % 2) : rng() & 1;
            if (shape == 4 || shape == 5) {
                x = true;
                y = i == (shape == 4 ? 0 : N - 1);
            }
            if (shape == 7) y = x;
            a.assign(i, x);
            sa.assign(i, x);
            va[i] = x;
            b.assign(i, y);
            sb.assign(i, y);
            vb[i] = y;
        }
        check_pair(a, b, va, vb);
        check_pair(sa, sb, va, vb);
        for (int step = 0; step < 20; ++step) {
            if constexpr (N > 0) {
                int k = rng() % N;
                a.flip(k);
                sa.flip(k);
                va[k] = !va[k];
                k = rng() % N;
                b.flip(k);
                sb.flip(k);
                vb[k] = !vb[k];
            }
            check_pair(a, b, va, vb);
            check_pair(sa, sb, va, vb);
        }
        a.set();
        sa.set();
        b.set();
        sb.set();
        fill(va.begin(), va.end(), true);
        fill(vb.begin(), vb.end(), true);
        check_pair(a, b, va, vb);
        check_pair(sa, sb, va, vb);
    }
}

void check_kernels() {
#if defined(__x86_64__) || defined(_M_X64)
    bool avx2 = __builtin_cpu_supports("avx2");
    bool popcnt = __builtin_cpu_supports("popcnt");
    bool avx512 = avx2 && popcnt && __builtin_cpu_supports("avx512f") && __builtin_cpu_supports("avx512vpopcntdq");
    mt19937_64 rng(205);
    for (int n = 0; n <= 257; ++n) {
        for (int offset = 0; offset < 4; ++offset) {
            vector<unsigned long long> a(n + offset), b(n + offset);
            for (int shape = 0; shape < 4; ++shape) {
                int expected = 0;
                for (int i = offset; i < n + offset; ++i) {
                    a[i] = rng();
                    b[i] = ~a[i];
                    if (shape == 1 && i == offset) b[i] = ~0ULL;
                    if (shape == 2 && i == n + offset - 1) b[i] = ~0ULL;
                    if (shape == 3) b[i] = rng();
                    for (auto x = a[i] & b[i]; x; x &= x - 1) ++expected;
                }
                const auto *p = n ? a.data() + offset : nullptr;
                const auto *q = n ? b.data() + offset : nullptr;
                if (avx2) assert(bitset_count_detail::intersects_avx2(p, q, n) == (expected != 0));
                if (avx2 && popcnt) assert(bitset_count_detail::count_avx2<true>(p, n, q) == expected);
                if (avx512) assert(bitset_count_detail::count_avx512<true>(p, n, q) == expected);
            }
        }
    }
#endif
}

int main() {
    check_size<0>();
    check_size<1>();
    check_size<63>();
    check_size<64>();
    check_size<65>();
    check_size<127>();
    check_size<128>();
    check_size<129>();
    check_size<448>();
    check_size<449>();
    check_size<511>();
    check_size<512>();
    check_size<513>();
    check_size<8128>();
    check_size<8129>();
    check_size<8191>();
    check_size<8192>();
    check_size<8193>();
    check_size<1048577>();
    check_kernels();
}
