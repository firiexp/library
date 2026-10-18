#define STANDALONE

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <optional>
#include <random>
#include <vector>
using namespace std;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../math/xor_basis.cpp"

vector<uint16_t> enumerate(const vector<uint16_t> &values) {
    vector<uint16_t> result{0};
    for (uint16_t x : values) {
        int n = result.size();
        for (int i = 0; i < n; ++i) result.push_back(result[i] ^ x);
        sort(result.begin(), result.end());
        result.erase(unique(result.begin(), result.end()), result.end());
    }
    return result;
}

void check_order(const XorBasis<uint16_t> &basis, const vector<uint16_t> &values) {
    for (int k = 0; k < (int)values.size(); ++k) assert(basis.kth(k) == values[k]);
    assert(!basis.kth(values.size()));
    assert(!basis.kth(numeric_limits<uint16_t>::max()));
    for (int x = 0; x <= 256; ++x) {
        auto count = lower_bound(values.begin(), values.end(), x) - values.begin();
        assert(basis.order_of_key(x) == count);
    }
}

template<class T>
void wide_order_check() {
    using U = make_unsigned_t<T>;
    constexpr int B = numeric_limits<U>::digits;
    const U high = U(1) << (B - 1), maximum = numeric_limits<U>::max();
    XorBasis<T> basis;
    assert(basis.kth(0) == T(0));
    assert(!basis.kth(1));
    assert(basis.order_of_key(0) == 0);
    assert(basis.order_of_key(static_cast<T>(maximum)) == 1);
    basis.add(static_cast<T>(maximum));
    assert(basis.kth(1) == static_cast<T>(maximum));
    assert(!basis.kth(2));
    assert(basis.order_of_key(static_cast<T>(high)) == 1);
    assert(basis.order_of_key(static_cast<T>(maximum)) == 1);
    for (int i = B - 1; i >= 0; --i) basis.add(static_cast<T>(U(1) << i));
    assert(basis.size() == B);
    for (U x : {U(0), U(1), U(high - 1), high, U(maximum - 1), maximum}) {
        assert(basis.kth(x) == static_cast<T>(x));
        assert(basis.order_of_key(static_cast<T>(x)) == x);
    }
    mt19937_64 rng(220);
    for (int i = 0; i < 1000; ++i) {
        U x = static_cast<U>(rng());
        assert(basis.kth(x) == static_cast<T>(x));
        assert(basis.order_of_key(static_cast<T>(x)) == x);
    }
    XorBasis<T> even;
    for (int i = 1; i < B; ++i) even.add(static_cast<T>((U(1) << i) | 1));
    assert(even.size() == B - 1);
    assert(!even.kth(high));
    assert(!even.kth(maximum));
    for (int i = 0; i < 1000; ++i) {
        U x = i == 0 ? maximum : static_cast<U>(rng());
        U k = x >> 1;
        int parity = __builtin_popcountll(k) & 1;
        U value = (k << 1) | parity;
        assert(even.kth(k) == static_cast<T>(value));
        assert(even.order_of_key(static_cast<T>(x)) == k + ((x & 1) && !parity));
    }
}

void order_check() {
    XorBasis<uint16_t> example;
    example.add(3);
    check_order(example, {0, 3});
    mt19937 rng(220);
    for (int tc = 0; tc < 500; ++tc) {
        vector<uint16_t> a(rng() % 9), b(rng() % 9);
        XorBasis<uint16_t> left, right;
        for (auto &x : a) {
            x = rng() % 256;
            left.add(x);
            assert(!left.add(x));
        }
        for (auto &x : b) {
            x = rng() % 256;
            right.add(x);
        }
        assert(!left.add(0));
        auto va = enumerate(a), vb = enumerate(b);
        check_order(left, va);
        check_order(right, vb);
        vector<uint16_t> common;
        for (uint16_t x : va) if (binary_search(vb.begin(), vb.end(), x)) common.push_back(x);
        check_order(left.intersection(right), common);
        auto merged = left;
        merged.merge(right);
        a.insert(a.end(), b.begin(), b.end());
        check_order(merged, enumerate(a));
        check_order(left, va);
    }
    wide_order_check<uint8_t>();
    wide_order_check<int8_t>();
    wide_order_check<uint32_t>();
    wide_order_check<int32_t>();
    wide_order_check<uint64_t>();
    wide_order_check<int64_t>();
}

bool brute(const vector<int> &a) {
    int n = a.size();
    for (int mask = 1; mask < (1 << n) - 1; ++mask) {
        int xb = 0;
        int xc = 0;
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) xb ^= a[i];
            else xc ^= a[i];
        }
        if (xb == 0 && xc == 0) return true;
    }
    return false;
}

void self_check() {
    {
        for (int n = 2; n <= 12; ++n) {
            for (int mask = 0; mask < (1 << n); ++mask) {
                vector<int> a(n);
                for (int i = 0; i < n; ++i) a[i] = (mask >> i) & 1;
                XorBasis<int> xb;
                int total = 0;
                for (int x : a) {
                    xb.add(x);
                    total ^= x;
                }
                bool ok = total == 0 && xb.size() < n - 1;
                assert(ok == brute(a));
            }
        }
    }
    {
        mt19937 rng(0);
        for (int tc = 0; tc < 1000; ++tc) {
            int n = rng() % 14 + 2;
            vector<int> a(n);
            for (int i = 0; i < n; ++i) a[i] = rng() % 16;
            XorBasis<int> xb;
            int total = 0;
            for (int x : a) {
                xb.add(x);
                total ^= x;
            }
            bool ok = total == 0 && xb.size() < n - 1;
            assert(ok == brute(a));
        }
    }
}

int main() {
    order_check();
    self_check();
}
