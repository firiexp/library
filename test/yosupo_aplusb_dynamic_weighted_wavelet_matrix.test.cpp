#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <limits>
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

ll brute_sum_k_smallest(const vector<int> &a, const vector<ll> &w, int l, int r, int k) {
    vector<int> ord(r - l);
    for (int i = l; i < r; ++i) ord[i - l] = i;
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        if (a[i] != a[j]) return a[i] < a[j];
        return i < j;
    });
    ll res = 0;
    for (int i = 0; i < k; ++i) res += w[ord[i]];
    return res;
}

void check_cursor(const DynamicWeightedWaveletMatrix<int, ll> &wm,
                  const vector<int> &a, const vector<ll> &w, int l, int r) {
    auto root = wm.range_cursor(l, r);
    ll total = 0;
    for (int i = l; i < r; ++i) total += w[i];
    assert(root.count() == r - l && root.sum() == total);
    assert(root.info().count == root.count() && root.info().sum == root.sum());
    assert(root.empty() == (l == r));

    vector<pair<int, BruteResult>> got;
    auto visit = [&](auto &&self, const auto &cur) -> void {
        if (cur.empty()) return;
        if (cur.is_leaf()) {
            got.push_back({cur.value(), {cur.count(), cur.sum()}});
            return;
        }
        auto children = wm.split(cur);
        assert(children.low.count() + children.high.count() == cur.count());
        assert(children.low.sum() + children.high.sum() == cur.sum());
        self(self, children.low);
        self(self, children.high);
    };
    visit(visit, root);

    vector<pair<int, BruteResult>> expected;
    for (int x : wm.vals) {
        BruteResult res = brute_equal(a, w, l, r, x);
        if (res.count != 0) expected.push_back({x, res});
    }
    assert(got.size() == expected.size());
    for (int i = 0; i < (int)got.size(); ++i) {
        assert(got[i].first == expected[i].first);
        assert(got[i].second.count == expected[i].second.count);
        assert(got[i].second.sum == expected[i].second.sum);
    }
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

    int k = rng() % (r - l + 1);
    assert(wm.sum_k_smallest(l, r, k) == brute_sum_k_smallest(a, w, l, r, k));
    check_cursor(wm, a, w, l, r);

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

    auto cur = wm.range_cursor(0, 3);
    while (!cur.is_leaf()) {
        auto children = wm.split(cur);
        cur = children.high.empty() ? children.low : children.high;
    }
    assert(cur.value() == "dd");
}

void self_check_sum_k_smallest() {
    vector<int> values{2, 1, 1, 3, 1};
    vector<ll> weights{5, 10, 20, -4, 30};
    DynamicWeightedWaveletMatrix<int, ll> wm(5);
    wm.add_value_candidate(0, 1);
    wm.add_value_candidate(3, 1);
    wm.build(values, weights);

    assert(wm.sum_k_smallest(0, 5, 0) == 0);
    assert(wm.sum_k_smallest(0, 5, 1) == 10);
    assert(wm.sum_k_smallest(0, 5, 2) == 30);
    assert(wm.sum_k_smallest(0, 5, 3) == 60);
    assert(wm.sum_k_smallest(0, 5, 4) == 65);
    assert(wm.sum_k_smallest(0, 5, 5) == 61);
    assert(wm.sum_k_smallest(2, 5, 2) == 50);

    assert(wm.set_value(0, 1));
    assert(wm.sum_k_smallest(0, 5, 1) == 5);
    wm.set_weight(0, -7);
    assert(wm.sum_k_smallest(0, 5, 2) == 3);
    assert(wm.set(3, 1, 40));
    assert(wm.sum_k_smallest(0, 5, 4) == 63);
    assert(wm.sum_k_smallest(0, 5, 5) == 93);
}

void self_check_fixed_values() {
    vector<int> values{2, -3, 2, 7, 0, -3};
    vector<ll> weights{5, 10, -4, 8, 3, 20};
    DynamicWeightedWaveletMatrix<int, ll> wm(values, weights);
    mt19937 rng(1);

    for (int step = 0; step < 200; ++step) {
        int k = rng() % values.size();
        ll delta = (int)(rng() % 21) - 10;
        wm.add_weight(k, delta);
        weights[k] += delta;
        check_queries(wm, values, weights, rng);
    }
    assert(wm.set_value(0, values[0]));
    assert(!wm.set_value(0, 1000000));
}

void self_check_integral_boundaries() {
    ll low = numeric_limits<ll>::min();
    ll high = numeric_limits<ll>::max();
    vector<ll> values{high, 0, low, -1};
    vector<ll> weights{1, 2, 4, 8};
    DynamicWeightedWaveletMatrix<ll, ll> wm(4);
    wm.add_value_candidate(0, low);
    wm.add_value_candidate(0, high);
    wm.add_value_candidate(2, high);
    wm.build(values, weights);

    assert((wm.vals == vector<ll>{low, -1, 0, high}));
    assert(wm.count_less(0, 4, 0) == 2);
    assert(wm.sum_less_equal(0, 4, 0) == 14);
    assert(wm.set_value(0, low));
    assert(wm.freq(0, 4, low) == 2);
    assert(wm.set(2, high, -5));
    assert(wm.sum_equal(0, 4, high) == -5);
}

int main() {
    self_check_random();
    self_check_generic_value();
    self_check_sum_k_smallest();
    self_check_fixed_values();
    self_check_integral_boundaries();

    Scanner sc;
    Printer pr;
    ll a, b;
    sc.read(a, b);
    pr.println(a + b);
    return 0;
}
