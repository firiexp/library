#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
constexpr int MOD = 998244353;

#include "../math/modular/modint.cpp"
#include "../datastructure/segmenttree/range_add_range_sum_bit.cpp"

template<class T>
void check_all(RangeAddRangeSumBIT<T> &bit, const vector<T> &a) {
    int n = a.size();
    for (int l = 0; l <= n; ++l) {
        T expected = 0;
        for (int r = l; r <= n; ++r) {
            assert(bit.sum(l, r) == expected);
            if (l == 0) assert(bit.sum(r) == expected);
            if (r < n) expected += a[r];
        }
    }
}

template<class T>
void run() {
    for (int n = 0; n <= 6; ++n) {
        for (int l = 0; l <= n; ++l) {
            for (int r = l; r <= n; ++r) {
                for (int slope = -3; slope <= 3; ++slope) {
                    for (int intercept = -3; intercept <= 3; ++intercept) {
                        vector<T> a(n);
                        for (int i = 0; i < n; ++i) a[i] = T(i * i - 5);
                        RangeAddRangeSumBIT<T> bit(a);
                        bit.add(l, r, T(slope), T(intercept));
                        for (int i = l; i < r; ++i) a[i] += T(slope * i + intercept);
                        check_all(bit, a);
                    }
                }
            }
        }
    }
    mt19937 rng(322);
    for (int n : {0, 1, 2, 3, 7, 8, 9, 31, 32, 33, 65}) {
        vector<T> a(n);
        for (auto &x : a) x = T((int)(rng() % 2001) - 1000);
        RangeAddRangeSumBIT<T> bit(a), zero(n);
        check_all(bit, a);
        check_all(zero, vector<T>(n));
        for (int i = 0; i < n; ++i) zero.add(i, i + 1, a[i]);
        check_all(zero, a);
        for (int t = 0; t < 1000; ++t) {
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            if (t % 10 == 0) l = 0, r = n;
            T x = T((int)(rng() % 2001) - 1000);
            if (t % 3 == 0) {
                bit.add(l, r, x);
                for (int i = l; i < r; ++i) a[i] += x;
            } else {
                T slope = T((int)(rng() % 2001) - 1000);
                bit.add(l, r, slope, x);
                for (int i = l; i < r; ++i) a[i] += slope * i + x;
            }
            if (t % 50 == 0) check_all(bit, a);
            l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            assert(bit.sum(l, r) == accumulate(a.begin() + l, a.begin() + r, T(0)));
        }
        check_all(bit, a);
    }
    int n = 200000;
    vector<T> a(n);
    RangeAddRangeSumBIT<T> bit(n);
    for (auto [l, r, slope, intercept] : vector<array<int, 4>>{
             {0, n, 17, -9}, {70000, 190000, -1000000, 123456789},
             {n - 1, n, 5, -3}, {n, n, 2, 1}}) {
        bit.add(l, r, T(slope), T(intercept));
        for (int i = l; i < r; ++i) a[i] += T(1LL * slope * i + intercept);
    }
    vector<T> prefix(n + 1);
    for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + a[i];
    assert(bit.sum(n) == prefix[n]);
    for (int t = 0; t < 1000; ++t) {
        int l = rng() % (n + 1), r = rng() % (n + 1);
        if (l > r) swap(l, r);
        assert(bit.sum(l, r) == prefix[r] - prefix[l]);
    }
}

int main() {
    run<ll>();
    run<mint>();
    run<modint<8>>();
}
