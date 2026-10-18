#define STANDALONE

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

template <class T>
void check_cursor_tree(const WeightedWaveletMatrix<T, ll> &wm,
                       typename WeightedWaveletMatrix<T, ll>::Cursor cur,
                       const vector<pair<T, ll>> &items) {
    ll sum = 0;
    for (const auto &item : items) sum += item.second;
    assert(cur.count() == (int)items.size());
    assert(cur.sum() == sum);
    assert(cur.info().count == cur.count() && cur.info().sum == sum);
    assert(cur.empty() == items.empty());
    if (cur.is_leaf()) {
        for (const auto &item : items) assert(item.first == cur.value());
        return;
    }
    auto children = wm.split(cur);
    auto again = wm.split(cur);
    assert(again.low.count() == children.low.count());
    assert(again.high.sum() == children.high.sum());
    int split = children.low.count();
    check_cursor_tree(wm, children.low, vector<pair<T, ll>>(items.begin(), items.begin() + split));
    check_cursor_tree(wm, children.high, vector<pair<T, ll>>(items.begin() + split, items.end()));
    assert(cur.count() == (int)items.size() && cur.sum() == sum);
}

void check_two_ranges(const WeightedWaveletMatrix<ll, ll> &wm,
                      const vector<ll> &values, const vector<ll> &weights,
                      int l1, int r1, int l2, int r2, int k) {
    vector<ll> sorted;
    for (auto [l, r] : {pair{l1, r1}, pair{l2, r2}}) {
        for (int i = l; i < r; ++i) sorted.push_back(values[i]);
    }
    sort(sorted.begin(), sorted.end());
    if (sorted.empty()) return;
    ll expected = sorted[k];
    ll expected_sum = brute_less(values, weights, l1, r1, expected, false).sum
                    + brute_less(values, weights, l2, r2, expected, false).sum;
    auto a = wm.range_cursor(l1, r1), b = wm.range_cursor(l2, r2);
    ll sum = 0;
    while (!a.is_leaf()) {
        auto x = wm.split(a), y = wm.split(b);
        int low = x.low.count() + y.low.count();
        if (k < low) {
            a = x.low;
            b = y.low;
        } else {
            k -= low;
            sum += x.low.sum() + y.low.sum();
            a = x.high;
            b = y.high;
        }
    }
    assert((a.empty() ? b.value() : a.value()) == expected);
    assert(sum == expected_sum);
}

void check_random() {
    mt19937_64 rng(0);
    for (int tc = 0; tc < 1000; ++tc) {
        const int sizes[] = {0, 1, 2, 3, 63, 64, 65, 127, 128, 129};
        int n = tc < 10 ? sizes[tc] : rng() % 258;
        vector<ll> values(n), weights(n);
        for (int i = 0; i < n; ++i) {
            if (tc % 11 == 0) values[i] = -7;
            else if (tc % 3 == 0) values[i] = (int)(rng() % 21) - 10;
            else values[i] = (ll)rng();
            weights[i] = (int)(rng() % 101) - 50;
        }
        if (n && tc % 7 == 0 && tc % 11 != 0) {
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
        size_t sum_size = 0;
        for (int mid : wm.mid) sum_size += mid + 1;
        assert(wm.zero_sum.size() == sum_size);
        assert(wm_index.zero_sum.size() == sum_size);

        vector<pair<ll, ll>> items;
        for (int i = 0; i < n; ++i) items.emplace_back(values[i], weights[i]);
        sort(items.begin(), items.end());
        check_cursor_tree(wm, wm.range_cursor(0, n), items);
        check_cursor_tree(wm_index, wm_index.range_cursor(n, n), {});

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
            if (step < 20) {
                int l2 = rng() % (n + 1), r2 = rng() % (n + 1);
                if (l2 > r2) swap(l2, r2);
                int count = r - l + r2 - l2;
                int k = count ? rng() % count : 0;
                check_two_ranges(wm, values, weights, l, r, l2, r2, k);
                check_two_ranges(wm_index, values, weights, l, r, l2, r2, k);
            }
        }
        wm.build({}, {});
        assert(wm.zero_sum.empty());
        assert(wm.count_sum_less(0, 0, 0).sum == 0);
        wm.build(values, weights);
        assert(wm.zero_sum.size() == sum_size);
        assert(wm.count_sum_less_index(0, n, sorted_values.size()).sum == wm_index.base_sum[n]);
    }
}

void check_generic_value() {
    vector<string> values{"bb", "aa", "cc", "aa"};
    vector<ll> weights{3, -2, 5, 7};
    WeightedWaveletMatrix<string, ll> wm(values, weights);
    assert(wm.count_less(0, 4, string("bb")) == 2);
    assert(wm.sum_less_equal(1, 4, string("bb")) == 5);
    check_cursor_tree(wm, wm.range_cursor(1, 4), {{"aa", -2}, {"aa", 7}, {"cc", 5}});
}

void check_integral_widths() {
    vector<signed char> values{-128, 127, 0, -1, 0};
    vector<int> weights{1, 2, 4, 8, 16};
    WeightedWaveletMatrix<signed char, int> wm(values, weights);
    assert(wm.count_less(0, 5, (signed char)1) == 4);
    assert(wm.sum_less_equal(0, 5, (signed char)0) == 29);
}

int main() {
    WeightedWaveletMatrix<ll, ll> empty;
    check_cursor_tree(empty, empty.range_cursor(0, 0), {});
    check_random();
    check_generic_value();
    check_integral_widths();

}
