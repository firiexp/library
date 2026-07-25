#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <random>
#include <string>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

#include <cstdio>
#include <cstring>
#include <type_traits>

#include "../datastructure/dynamic_weighted_wavelet_matrix.cpp"
#include "../util/fastio.cpp"

struct BruteResult {
    int count;
    ll sum;
};

BruteResult brute_less(const vector<int> &a, const vector<ll> &w, int l, int r, int x, bool equal) {
    BruteResult res{0, 0};
    for (int i = l; i < r; ++i) {
        if (a[i] < x || (equal && a[i] == x)) {
            ++res.count;
            res.sum += w[i];
        }
    }
    return res;
}

BruteResult brute_equal(const vector<int> &a, const vector<ll> &w, int l, int r, int x) {
    BruteResult res{0, 0};
    for (int i = l; i < r; ++i) {
        if (a[i] == x) {
            ++res.count;
            res.sum += w[i];
        }
    }
    return res;
}

BruteResult brute_range(const vector<int> &a, const vector<ll> &w, int l, int r, int lower, int upper) {
    BruteResult res{0, 0};
    for (int i = l; i < r; ++i) {
        if (lower <= a[i] && a[i] < upper) {
            ++res.count;
            res.sum += w[i];
        }
    }
    return res;
}

void check_queries(const DynamicWeightedWaveletMatrix<int, ll> &wm,
                   const vector<int> &a, const vector<ll> &w, mt19937 &rng) {
    int n = (int)a.size();
    int l = rng() % (n + 1);
    int r = rng() % (n + 1);
    if (l > r) swap(l, r);
    int x = (int)(rng() % 25) - 12;

    BruteResult less = brute_less(a, w, l, r, x, false);
    auto got_less = wm.count_sum_less(l, r, x);
    assert(got_less.count == less.count && got_less.sum == less.sum);
    assert(wm.count_less(l, r, x) == less.count);
    assert(wm.sum_less(l, r, x) == less.sum);

    BruteResult less_equal = brute_less(a, w, l, r, x, true);
    auto got_less_equal = wm.count_sum_less_equal(l, r, x);
    assert(got_less_equal.count == less_equal.count && got_less_equal.sum == less_equal.sum);
    assert(wm.count_less_equal(l, r, x) == less_equal.count);
    assert(wm.sum_less_equal(l, r, x) == less_equal.sum);

    BruteResult equal = brute_equal(a, w, l, r, x);
    auto got_equal = wm.count_sum_equal(l, r, x);
    assert(got_equal.count == equal.count && got_equal.sum == equal.sum);
    assert(wm.freq(l, r, x) == equal.count);
    assert(wm.sum_equal(l, r, x) == equal.sum);

    int lower = (int)(rng() % 25) - 12;
    int upper = (int)(rng() % 25) - 12;
    if (lower > upper) swap(lower, upper);
    BruteResult range = brute_range(a, w, l, r, lower, upper);
    auto got_range = wm.range_count_sum(l, r, lower, upper);
    assert(got_range.count == range.count && got_range.sum == range.sum);
    assert(wm.range_freq(l, r, lower, upper) == range.count);
    assert(wm.range_sum(l, r, lower, upper) == range.sum);

    int xi = (int)(rng() % (wm.vals.size() + 3)) - 1;
    BruteResult index_less{0, 0};
    if (xi >= (int)wm.vals.size()) {
        index_less = brute_less(a, w, l, r, 1000000000, false);
    }
    else if (xi > 0) {
        index_less = brute_less(a, w, l, r, wm.vals[xi], false);
    }
    auto got_index = wm.count_sum_less_index(l, r, xi);
    assert(got_index.count == index_less.count && got_index.sum == index_less.sum);
}

void self_check_random() {
    mt19937 rng(0);
    for (int tc = 0; tc < 200; ++tc) {
        int n = rng() % 31;
        vector<vector<int>> candidates(n);
        vector<int> a(n);
        vector<ll> w(n);
        DynamicWeightedWaveletMatrix<int, ll> wm(n);

        for (int i = 0; i < n; ++i) {
            int count = rng() % 6 + 1;
            for (int j = 0; j < count; ++j) candidates[i].push_back((int)(rng() % 17) - 8);
            sort(candidates[i].begin(), candidates[i].end());
            candidates[i].erase(unique(candidates[i].begin(), candidates[i].end()), candidates[i].end());
            a[i] = candidates[i][rng() % candidates[i].size()];
            w[i] = (int)(rng() % 41) - 20;
            for (int x : candidates[i]) wm.add_value_candidate(i, x);
            wm.add_value_candidate(i, a[i]);
        }
        wm.build(a, w);

        for (int i = 0; i < n; ++i) {
            assert(wm.get_value(i) == a[i]);
            assert(wm.get_weight(i) == w[i]);
        }
        for (int step = 0; step < 200; ++step) {
            if (n != 0) {
                int k = rng() % n;
                int op = rng() % 6;
                if (op == 0) {
                    int x = candidates[k][rng() % candidates[k].size()];
                    assert(wm.set_value(k, x));
                    a[k] = x;
                }
                else if (op == 1) {
                    ll next = (int)(rng() % 81) - 40;
                    wm.set_weight(k, next);
                    w[k] = next;
                }
                else if (op == 2) {
                    ll delta = (int)(rng() % 21) - 10;
                    wm.add_weight(k, delta);
                    w[k] += delta;
                }
                else if (op == 3) {
                    int x = candidates[k][rng() % candidates[k].size()];
                    ll next = (int)(rng() % 81) - 40;
                    assert(wm.set(k, x, next));
                    a[k] = x;
                    w[k] = next;
                }
                else if (op == 4) {
                    int old_a = a[k];
                    ll old_w = w[k];
                    assert(!wm.set_value(k, 1000000 + k));
                    assert(wm.get_value(k) == old_a && wm.get_weight(k) == old_w);
                }
                else {
                    int old_a = a[k];
                    ll old_w = w[k];
                    assert(!wm.set(k, 2000000 + k, old_w + 1));
                    assert(wm.get_value(k) == old_a && wm.get_weight(k) == old_w);
                }
                assert(wm.get_value(k) == a[k]);
                assert(wm.get_weight(k) == w[k]);
            }
            check_queries(wm, a, w, rng);
        }
    }
}

void self_check_generic_value() {
    vector<string> values{"bb", "aa", "cc"};
    vector<ll> weights{3, -2, 5};
    DynamicWeightedWaveletMatrix<string, ll> wm(3);
    wm.add_value_candidate(0, "dd");
    wm.add_value_candidate(0, "bb");
    wm.add_value_candidate(1, "ab");
    wm.build(values, weights);

    assert(wm.sum_less(0, 3, string("cc")) == 1);
    assert(wm.set_value(0, "dd"));
    assert(wm.freq(0, 3, string("dd")) == 1);
    assert(!wm.set_value(2, "dd"));
    assert(wm.get_value(2) == "cc");
}

int main() {
    self_check_random();
    self_check_generic_value();

    Scanner sc;
    Printer pr;
    ll a, b;
    sc.read(a, b);
    pr.println(a + b);
    return 0;
}
