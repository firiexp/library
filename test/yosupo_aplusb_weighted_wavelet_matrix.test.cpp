#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <limits>
#include <random>
#include <string>
#include <type_traits>
#include <vector>
using namespace std;

#include "../datastructure/weighted_wavelet_matrix.cpp"

#include <cstdio>
#include <cstring>

#include <charconv>
#include "../util/fastio.cpp"

using ll = long long;

struct BruteResult {
    int count;
    ll sum;
};

BruteResult brute_less(const vector<ll> &values, const vector<ll> &weights,
                       int l, int r, ll x, bool equal) {
    BruteResult res{0, 0};
    for (int i = l; i < r; ++i) {
        if (values[i] < x || (equal && values[i] == x)) {
            ++res.count;
            res.sum += weights[i];
        }
    }
    return res;
}

void check_random() {
    mt19937_64 rng(0);
    for (int tc = 0; tc < 200; ++tc) {
        int n = rng() % 51;
        vector<ll> values(n), weights(n);
        for (int i = 0; i < n; ++i) {
            if (tc % 3 == 0) values[i] = (int)(rng() % 21) - 10;
            else values[i] = (ll)rng();
            weights[i] = (int)(rng() % 101) - 50;
        }
        if (n && tc % 7 == 0) {
            values[0] = numeric_limits<ll>::min();
            values[n - 1] = numeric_limits<ll>::max();
        }

        WeightedWaveletMatrix<ll, ll> wm(values, weights);
        vector<ll> sorted_values = values;
        sort(sorted_values.begin(), sorted_values.end());
        sorted_values.erase(unique(sorted_values.begin(), sorted_values.end()), sorted_values.end());
        assert(wm.vals == sorted_values);

        vector<int> index(n);
        for (int i = 0; i < n; ++i) {
            index[i] = lower_bound(sorted_values.begin(), sorted_values.end(), values[i]) - sorted_values.begin();
        }
        WeightedWaveletMatrix<ll, ll> wm_index;
        wm_index.build_from_index(index, sorted_values, weights);

        for (int step = 0; step < 200; ++step) {
            int l = rng() % (n + 1);
            int r = rng() % (n + 1);
            if (l > r) swap(l, r);
            ll x = step % 17 == 0 ? numeric_limits<ll>::min()
                                  : step % 19 == 0 ? numeric_limits<ll>::max()
                                                    : (ll)rng();

            BruteResult less = brute_less(values, weights, l, r, x, false);
            auto got_less = wm.count_sum_less(l, r, x);
            assert(got_less.count == less.count && got_less.sum == less.sum);
            assert(wm.count_less(l, r, x) == less.count);
            assert(wm.sum_less(l, r, x) == less.sum);

            BruteResult less_equal = brute_less(values, weights, l, r, x, true);
            auto got_less_equal = wm.count_sum_less_equal(l, r, x);
            assert(got_less_equal.count == less_equal.count && got_less_equal.sum == less_equal.sum);
            assert(wm.count_less_equal(l, r, x) == less_equal.count);
            assert(wm.sum_less_equal(l, r, x) == less_equal.sum);

            int xi = (int)(rng() % (sorted_values.size() + 5)) - 2;
            BruteResult index_less{0, 0};
            for (int i = l; i < r; ++i) {
                if (index[i] < xi) {
                    ++index_less.count;
                    index_less.sum += weights[i];
                }
            }
            auto got_index = wm_index.count_sum_less_index(l, r, xi);
            assert(got_index.count == index_less.count && got_index.sum == index_less.sum);
            assert(wm_index.count_less_index(l, r, xi) == index_less.count);
        }
    }
}

void check_generic_value() {
    vector<string> values{"bb", "aa", "cc", "aa"};
    vector<ll> weights{3, -2, 5, 7};
    WeightedWaveletMatrix<string, ll> wm(values, weights);
    assert(wm.count_less(0, 4, string("bb")) == 2);
    assert(wm.sum_less_equal(1, 4, string("bb")) == 5);
}

void check_integral_widths() {
    vector<signed char> values{-128, 127, 0, -1, 0};
    vector<int> weights{1, 2, 4, 8, 16};
    WeightedWaveletMatrix<signed char, int> wm(values, weights);
    assert(wm.count_less(0, 5, (signed char)1) == 4);
    assert(wm.sum_less_equal(0, 5, (signed char)0) == 29);
}

int main() {
    check_random();
    check_generic_value();
    check_integral_widths();

    Scanner in;
    Printer out;
    ll a, b;
    in.read(a, b);
    out.println(a + b);
    return 0;
}
