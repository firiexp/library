#define STANDALONE

#include <algorithm>
#include <cassert>
#include <bitset>
#include <limits>
#include <random>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../datastructure/static_bitset.cpp"

template<int N>
vector<int> to_vec(const StaticBitset<N> &bs) {
    vector<int> res(N);
    for (int i = 0; i < N; ++i) res[i] = bs.test(i);
    return res;
}

int brute_find_first(const vector<int> &a) {
    for (int i = 0; i < (int)a.size(); ++i) if (a[i]) return i;
    return -1;
}

int brute_find_last(const vector<int> &a) {
    for (int i = (int)a.size() - 1; i >= 0; --i) if (a[i]) return i;
    return -1;
}

int brute_find_next(const vector<int> &a, int k) {
    for (int i = k + 1; i < (int)a.size(); ++i) if (a[i]) return i;
    return -1;
}

int brute_find_prev(const vector<int> &a, int k) {
    for (int i = k - 1; i >= 0; --i) if (a[i]) return i;
    return -1;
}

vector<int> shifted_left(const vector<int> &a, int s) {
    vector<int> res(a.size());
    if (s >= (int)a.size()) return res;
    for (int i = 0; i + s < (int)a.size(); ++i) res[i + s] = a[i];
    return res;
}

vector<int> shifted_right(const vector<int> &a, int s) {
    vector<int> res(a.size());
    if (s >= (int)a.size()) return res;
    for (int i = s; i < (int)a.size(); ++i) res[i - s] = a[i];
    return res;
}

template<int N>
void verify_state(const StaticBitset<N> &bs, const vector<int> &a) {
    assert(bs.size() == (int)a.size());
    assert(bs.empty() == a.empty());
    assert(to_vec(bs) == a);

    int cnt = 0;
    for (int x : a) cnt += x;
    assert(bs.count() == cnt);
    assert(bs.any() == (cnt != 0));
    assert(bs.none() == (cnt == 0));
    assert(bs.all() == (cnt == (int)a.size()));
    assert(bs.find_first() == brute_find_first(a));
    assert(bs.find_last() == brute_find_last(a));
    for (int i = 0; i <= (int)a.size(); ++i) {
        assert(bs.find_next(i - 1) == brute_find_next(a, i - 1));
        assert(bs.find_prev(i) == brute_find_prev(a, i));
    }
}

template<int N>
void deterministic_check_size() {
    StaticBitset<N> zero, one(true);
    verify_state(zero, vector<int>(N, 0));
    verify_state(one, vector<int>(N, 1));

    vector<int> base(N);
    for (int i = 0; i < N; ++i) base[i] = (i % 3) == 1;
    StaticBitset<N> bs;
    for (int i = 0; i < N; ++i) if (base[i]) bs.set(i);
    verify_state(bs, base);

    StaticBitset<N> flipped = bs;
    flipped.flip();
    vector<int> flip_base = base;
    for (int &x : flip_base) x ^= 1;
    verify_state(flipped, flip_base);

    vector<int> shifts = {0, 1, 2, 31, 32, 63, 64, 65, max(0, N - 1), N, N + 7};
    for (int s : shifts) {
        StaticBitset<N> left = bs;
        left <<= s;
        verify_state(left, shifted_left(base, s));

        StaticBitset<N> right = bs;
        right >>= s;
        verify_state(right, shifted_right(base, s));
    }

    StaticBitset<N> all(true);
    StaticBitset<N> x = bs & all;
    verify_state(x, base);

    StaticBitset<N> y = bs | all;
    verify_state(y, vector<int>(N, 1));

    StaticBitset<N> z = bs ^ all;
    vector<int> xor_base = base;
    for (int &v : xor_base) v ^= 1;
    verify_state(z, xor_base);
}

template<int N>
void random_check_size() {
    mt19937 rng(N + 17);
    for (int tc = 0; tc < 60; ++tc) {
        StaticBitset<N> bs, other;
        vector<int> a(N, 0), b(N, 0);
        for (int step = 0; step < 120; ++step) {
            int op = rng() % 12;
            if (op == 0 && N > 0) {
                int k = rng() % N;
                bs.set(k);
                a[k] = 1;
            } else if (op == 1 && N > 0) {
                int k = rng() % N;
                bs.reset(k);
                a[k] = 0;
            } else if (op == 2 && N > 0) {
                int k = rng() % N;
                bs.flip(k);
                a[k] ^= 1;
            } else if (op == 3 && N > 0) {
                int k = rng() % N;
                int x = rng() & 1;
                bs.assign(k, x);
                a[k] = x;
            } else if (op == 4) {
                bs.reset();
                fill(a.begin(), a.end(), 0);
            } else if (op == 5) {
                bs.set();
                fill(a.begin(), a.end(), 1);
            } else if (op == 6) {
                bs.flip();
                for (int &x : a) x ^= 1;
            } else if (op == 7) {
                for (int i = 0; i < N; ++i) {
                    int x = (rng() >> (i & 7)) & 1;
                    other.assign(i, x);
                    b[i] = x;
                }
            } else if (op == 8) {
                StaticBitset<N> cur = bs;
                cur &= other;
                vector<int> expect(N);
                for (int i = 0; i < N; ++i) expect[i] = a[i] & b[i];
                verify_state(cur, expect);
            } else if (op == 9) {
                StaticBitset<N> cur = bs;
                cur |= other;
                vector<int> expect(N);
                for (int i = 0; i < N; ++i) expect[i] = a[i] | b[i];
                verify_state(cur, expect);
            } else if (op == 10) {
                StaticBitset<N> cur = bs;
                cur ^= other;
                vector<int> expect(N);
                for (int i = 0; i < N; ++i) expect[i] = a[i] ^ b[i];
                verify_state(cur, expect);
            } else {
                int s = N == 0 ? 0 : rng() % (N + 8);
                if (rng() & 1) {
                    bs <<= s;
                    a = shifted_left(a, s);
                } else {
                    bs >>= s;
                    a = shifted_right(a, s);
                }
            }
            verify_state(bs, a);
            verify_state(other, b);
        }
    }
}

void deterministic_check() {
    deterministic_check_size<0>();
    deterministic_check_size<1>();
    deterministic_check_size<2>();
    deterministic_check_size<63>();
    deterministic_check_size<64>();
    deterministic_check_size<65>();
    deterministic_check_size<127>();
    deterministic_check_size<128>();
    deterministic_check_size<129>();
}

void random_check() {
    random_check_size<0>();
    random_check_size<1>();
    random_check_size<2>();
    random_check_size<63>();
    random_check_size<64>();
    random_check_size<65>();
    random_check_size<129>();
    random_check_size<257>();
}

void count_kernels_check() {
#if defined(__x86_64__) || defined(_M_X64)
    bool avx2 = __builtin_cpu_supports("avx2") && __builtin_cpu_supports("popcnt");
    bool avx512 = avx2 && __builtin_cpu_supports("avx512f") && __builtin_cpu_supports("avx512vpopcntdq");
    mt19937_64 rng(164);
    for (int n = 0; n <= 257; ++n) {
        for (int offset = 0; offset < 4; ++offset) {
            vector<unsigned long long> data(n + offset);
            for (int shape = 0; shape < 4; ++shape) {
                int expected = 0;
                for (int i = offset; i < n + offset; ++i) {
                    data[i] = shape == 0 ? 0 : shape == 1 ? ~0ULL : shape == 2 ? 0x5555555555555555ULL : rng();
                    for (auto x = data[i]; x; x &= x - 1) ++expected;
                }
                const auto *p = n ? data.data() + offset : nullptr;
                if (avx2) assert(bitset_count_detail::count_avx2(p, n) == expected);
                if (avx512) assert(bitset_count_detail::count_avx512(p, n) == expected);
            }
        }
    }
#endif
}

template<int N>
void count_check_size() {
    mt19937 rng(N + 164);
    for (int shape = 0; shape < 4; ++shape) {
        StaticBitset<N> actual;
        bitset<N> expected;
        for (int i = 0; i < N; ++i) {
            bool bit = shape == 0 ? false : shape == 1 ? true : shape == 2 ? i % 2 : rng() & 1;
            actual.assign(i, bit);
            expected[i] = bit;
        }
        assert(actual.count() == (int)expected.count());
        actual.flip();
        expected.flip();
        assert(actual.count() == (int)expected.count());
        actual <<= 1;
        expected <<= 1;
        assert(actual.count() == (int)expected.count());
        actual >>= 63;
        expected >>= 63;
        assert(actual.count() == (int)expected.count());
    }
}

template<int N>
void shift_or_check() {
    mt19937 rng(N + 211);
    vector<int> shifts = {numeric_limits<int>::min(), -1, 0, 1, 2, 63, 64, 65,
                         127, 128, 129, N - 1, N, N + 1, numeric_limits<int>::max()};
    for (int shape = 0; shape < 4; ++shape) {
        StaticBitset<N> bs;
        bitset<N> expected;
        for (int i = 0; i < N; ++i) {
            bool bit = shape == 0 ? false : shape == 1 ? true : shape == 2 ? i % 67 == 0 : rng() & 1;
            bs.assign(i, bit);
            expected[i] = bit;
        }
        for (int step = 0; step < 500; ++step) {
            if constexpr (N > 0) {
                int k = rng() % N;
                bs.flip(k);
                expected.flip(k);
            }
            int s = step < (int)shifts.size() * 2 ? shifts[step / 2] : int(rng() % (N + 130)) - 65;
            bool left = step % 2 == 0;
            auto reference = bs | (left ? bs << s : bs >> s);
            if (s > 0 && s < N) expected |= left ? expected << s : expected >> s;
            auto &result = left ? bs.or_shift_left(s) : bs.or_shift_right(s);
            assert(&result == &bs);
            assert(bs.count() == (int)expected.count());
            for (int i = 0; i < N; ++i) {
                assert(bs.test(i) == expected[i]);
                assert(bs.test(i) == reference.test(i));
            }
        }
    }
}

void subset_sum_check() {
    constexpr int N = 8193;
    StaticBitset<N> bs;
    vector<bool> possible(N);
    bs.set(0);
    possible[0] = true;
    mt19937 rng(211);
    for (int step = 0; step < 200; ++step) {
        int w = rng() % 300;
        bs.or_shift_left(w);
        for (int i = N - 1; i >= w; --i) possible[i] = possible[i] || possible[i - w];
        for (int i = 0; i < N; ++i) assert(bs.test(i) == possible[i]);
    }
}

int main() {
    shift_or_check<0>();
    shift_or_check<1>();
    shift_or_check<63>();
    shift_or_check<64>();
    shift_or_check<65>();
    shift_or_check<127>();
    shift_or_check<128>();
    shift_or_check<129>();
    shift_or_check<8193>();
    subset_sum_check();
    deterministic_check();
    random_check();
    count_kernels_check();
    count_check_size<8128>();
    count_check_size<8129>();
    count_check_size<8191>();
    count_check_size<8192>();
    count_check_size<8193>();
    count_check_size<65536>();
    count_check_size<65537>();
    count_check_size<1048577>();

}
