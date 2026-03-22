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
#include "../datastructure/dynamic_bitset.cpp"

vector<int> to_vec(const DynamicBitset &bs) {
    vector<int> res(bs.size());
    for (int i = 0; i < bs.size(); ++i) res[i] = bs.test(i);
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

void verify_state(const DynamicBitset &bs, const vector<int> &a) {
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

void deterministic_check() {
    vector<int> sizes = {0, 1, 2, 63, 64, 65, 127, 128, 129};
    for (int n : sizes) {
        DynamicBitset zero(n), one(n, true);
        verify_state(zero, vector<int>(n, 0));
        verify_state(one, vector<int>(n, 1));

        vector<int> base(n);
        for (int i = 0; i < n; ++i) base[i] = (i % 3) == 1;
        DynamicBitset bs(n);
        for (int i = 0; i < n; ++i) if (base[i]) bs.set(i);
        verify_state(bs, base);

        DynamicBitset flipped = bs;
        flipped.flip();
        vector<int> flip_base = base;
        for (int &x : flip_base) x ^= 1;
        verify_state(flipped, flip_base);

        vector<int> shifts = {0, 1, 2, 31, 32, 63, 64, 65, max(0, n - 1), n, n + 7};
        for (int s : shifts) {
            DynamicBitset left = bs;
            left <<= s;
            verify_state(left, shifted_left(base, s));

            DynamicBitset right = bs;
            right >>= s;
            verify_state(right, shifted_right(base, s));
        }

        DynamicBitset all(n, true);
        DynamicBitset mix = bs;
        DynamicBitset x = mix & all;
        verify_state(x, base);

        DynamicBitset y = mix | all;
        verify_state(y, vector<int>(n, 1));

        DynamicBitset z = mix ^ all;
        vector<int> xor_base = base;
        for (int &v : xor_base) v ^= 1;
        verify_state(z, xor_base);
    }
}

void random_check() {
    mt19937 rng(0);
    for (int tc = 0; tc < 400; ++tc) {
        int n = rng() % 260;
        DynamicBitset bs(n), other(n);
        vector<int> a(n, 0), b(n, 0);
        for (int step = 0; step < 200; ++step) {
            int op = rng() % 12;
            if (op == 0 && n > 0) {
                int k = rng() % n;
                bs.set(k);
                a[k] = 1;
            } else if (op == 1 && n > 0) {
                int k = rng() % n;
                bs.reset(k);
                a[k] = 0;
            } else if (op == 2 && n > 0) {
                int k = rng() % n;
                bs.flip(k);
                a[k] ^= 1;
            } else if (op == 3 && n > 0) {
                int k = rng() % n;
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
                for (int i = 0; i < n; ++i) {
                    int x = (rng() >> (i & 7)) & 1;
                    other.assign(i, x);
                    b[i] = x;
                }
            } else if (op == 8) {
                DynamicBitset cur = bs;
                cur &= other;
                vector<int> expect(n);
                for (int i = 0; i < n; ++i) expect[i] = a[i] & b[i];
                verify_state(cur, expect);
            } else if (op == 9) {
                DynamicBitset cur = bs;
                cur |= other;
                vector<int> expect(n);
                for (int i = 0; i < n; ++i) expect[i] = a[i] | b[i];
                verify_state(cur, expect);
            } else if (op == 10) {
                DynamicBitset cur = bs;
                cur ^= other;
                vector<int> expect(n);
                for (int i = 0; i < n; ++i) expect[i] = a[i] ^ b[i];
                verify_state(cur, expect);
            } else {
                int s = n == 0 ? 0 : rng() % (n + 8);
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
