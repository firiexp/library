#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <random>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

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

int main() {
    deterministic_check();
    random_check();

    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
    return 0;
}
