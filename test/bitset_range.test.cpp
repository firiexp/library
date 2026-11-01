#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../datastructure/bitset/dynamic_bitset.cpp"
#include "../datastructure/bitset/static_bitset.cpp"

template<class B>
void check_bits(const B &bits, const vector<int> &a) {
    int n = a.size(), count = 0, first = -1, last = -1;
    assert(bits.size() == n);
    for (int i = 0; i < n; ++i) {
        assert(bits.test(i) == bool(a[i]));
        if (a[i]) {
            ++count;
            if (first == -1) first = i;
            last = i;
        }
    }
    assert(bits.count() == count);
    assert(bits.any() == (count != 0) && bits.none() == (count == 0));
    assert(bits.all() == (count == n));
    assert(bits.find_first() == first && bits.find_last() == last);
}

template<class B>
void update(B &bits, vector<int> &a, int l, int r, int op) {
    if (op == 0) bits.set(l, r);
    if (op == 1) bits.reset(l, r);
    if (op == 2) bits.flip(l, r);
    for (int i = l; i < r; ++i) a[i] = op == 0 ? 1 : op == 1 ? 0 : a[i] ^ 1;
}

template<class B>
void check(B bits) {
    int n = bits.size();
    mt19937 rng(326 + n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rng() & 1;
        bits.assign(i, a[i]);
    }
    if (n <= 129) {
        for (int l = 0; l <= n; ++l) for (int r = l; r <= n; ++r) {
            for (int op = 0; op < 3; ++op) {
                auto copy = bits;
                auto expected = a;
                update(copy, expected, l, r, op);
                check_bits(copy, expected);
            }
        }
    }
    for (int step = 0; step < 2000; ++step) {
        int l = rng() % (n + 1), r = rng() % (n + 1);
        if (l > r) swap(l, r);
        int op = rng() % 13;
        if (op < 3) update(bits, a, l, r, op);
        else if (op < 7) {
            int shift = rng() % (n + 2);
            if (op == 3) bits <<= shift;
            if (op == 4) bits >>= shift;
            if (op == 5) bits.or_shift_left(shift);
            if (op == 6) bits.or_shift_right(shift);
            auto before = a;
            for (int i = 0; i < n; ++i) {
                int src = (op & 1) ? i - shift : i + shift;
                int value = 0 <= src && src < n ? before[src] : 0;
                a[i] = op < 5 ? value : before[i] | value;
            }
        } else if (op < 10) {
            auto other = bits;
            for (int i = 0; i < n; ++i) {
                int x = rng() & 1;
                other.assign(i, x);
                if (op == 7) a[i] &= x;
                if (op == 8) a[i] |= x;
                if (op == 9) a[i] ^= x;
            }
            if (op == 7) bits &= other;
            if (op == 8) bits |= other;
            if (op == 9) bits ^= other;
        } else {
            if (op == 10) bits.set();
            if (op == 11) bits.reset();
            if (op == 12) bits.flip();
            for (int &x : a) x = op == 10 ? 1 : op == 11 ? 0 : x ^ 1;
        }
        check_bits(bits, a);
    }
    bits.set(0, n);
    check_bits(bits, vector<int>(n, 1));
    bits.flip(0, n);
    check_bits(bits, vector<int>(n, 0));
    bits.reset(0, n);
    check_bits(bits, vector<int>(n, 0));
}

template<int N>
void check_size() {
    check(DynamicBitset(N));
    check(StaticBitset<N>());
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
    check_size<511>();
    check_size<512>();
    check_size<513>();
    check_size<4097>();
}
