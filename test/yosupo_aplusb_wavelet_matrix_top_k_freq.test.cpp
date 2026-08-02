#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <limits>
#include <map>
#include <random>
#include <vector>
using namespace std;

using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../datastructure/wavelet_matrix.cpp"
#include <charconv>
#include "../util/fastio.cpp"

vector<pair<int, ll>> brute_top_k_freq(const vector<ll> &a, int l, int r, int k) {
    map<ll, int> cnt;
    for (int i = l; i < r; ++i) ++cnt[a[i]];
    vector<pair<int, ll>> res;
    for (const auto &[x, c] : cnt) res.push_back({c, x});
    sort(res.begin(), res.end(), [](const pair<int, ll> &x, const pair<int, ll> &y) {
        if (x.first != y.first) return x.first > y.first;
        return x.second < y.second;
    });
    if ((int)res.size() > k) res.resize(k);
    return res;
}

vector<pair<int, int>> brute_top_k_freq_index(const vector<int> &idx, int l, int r, int k) {
    map<int, int> cnt;
    for (int i = l; i < r; ++i) ++cnt[idx[i]];
    vector<pair<int, int>> res;
    for (const auto &[x, c] : cnt) res.push_back({c, x});
    sort(res.begin(), res.end(), [](const pair<int, int> &x, const pair<int, int> &y) {
        if (x.first != y.first) return x.first > y.first;
        return x.second < y.second;
    });
    if ((int)res.size() > k) res.resize(k);
    return res;
}

void self_check() {
    mt19937 rng(0);
    const vector<int> edge_sizes = {1, 7, 8, 15, 16, 63, 64, 65, 127, 128, 129};
    for (int tc = 0; tc < 300 + (int)edge_sizes.size(); ++tc) {
        int n = tc < 300 ? rng() % 60 + 1 : edge_sizes[tc - 300];
        vector<ll> a(n);
        if (tc < 300) {
            for (ll &x : a) x = (int)(rng() % 21) - 10;
        }
        else {
            for (int i = 0; i < n; ++i) {
                if (i % 17 == 0) a[i] = numeric_limits<ll>::min();
                else if (i % 19 == 0) a[i] = numeric_limits<ll>::max();
                else if (i % 5 == 0) a[i] = 7;
                else a[i] = (ll)((unsigned long long)rng() << 32 | rng());
            }
        }

        WaveletMatrix<ll> wm(a);
        vector<ll> vals = a;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        vector<int> idx(n);
        for (int i = 0; i < n; ++i) idx[i] = (int)(lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin());

        WaveletMatrix<ll> wm_index;
        wm_index.build_from_index(idx, vals);

        for (int step = 0; step < 200; ++step) {
            int l = rng() % (n + 1);
            int r = rng() % (n + 1);
            if (l > r) swap(l, r);
            int k = rng() % (n + 3);

            auto got = wm.top_k_freq(l, r, k);
            auto want = brute_top_k_freq(a, l, r, k);
            assert(got == want);

            auto got_idx = wm_index.top_k_freq_index(l, r, k);
            auto want_idx = brute_top_k_freq_index(idx, l, r, k);
            assert(got_idx == want_idx);

            vector<ll> part(a.begin() + l, a.begin() + r);
            sort(part.begin(), part.end());
            ll x;
            if (step % 17 == 0) x = numeric_limits<ll>::min();
            else if (step % 19 == 0) x = numeric_limits<ll>::max();
            else if (step % 3 == 0) x = a[rng() % n];
            else x = (int)(rng() % 31) - 15;
            ll y = step % 7 == 0 ? x : (int)(rng() % 31) - 15;
            ll lower = min(x, y), upper = max(x, y);

            int less = (int)(lower_bound(part.begin(), part.end(), x) - part.begin());
            int equal = (int)(upper_bound(part.begin(), part.end(), x)
                              - lower_bound(part.begin(), part.end(), x));
            int in_range = (int)(lower_bound(part.begin(), part.end(), upper)
                                 - lower_bound(part.begin(), part.end(), lower));
            assert(wm.count_less(l, r, x) == less);
            assert(wm.freq(l, r, x) == equal);
            assert(wm.range_freq(l, r, lower, upper) == in_range);
            assert(wm_index.count_less(l, r, x) == less);
            assert(wm_index.freq(l, r, x) == equal);

            int xi = (int)(rng() % (vals.size() + 3)) - 1;
            int less_idx = 0, equal_idx = 0;
            for (int i = l; i < r; ++i) {
                less_idx += idx[i] < xi;
                equal_idx += idx[i] == xi;
            }
            assert(wm_index.count_less_index(l, r, xi) == less_idx);
            assert(wm_index.count_equal_index(l, r, xi) == equal_idx);

            if (!part.empty()) {
                int order = rng() % part.size();
                assert(wm.kth_smallest(l, r, order) == part[order]);
                assert(wm.kth_largest(l, r, order) == part[part.size() - 1 - order]);
                assert(wm_index.kth_smallest(l, r, order) == part[order]);
            }

            ll got_value = 0;
            auto prev_it = lower_bound(part.begin(), part.end(), x);
            bool has_prev = prev_it != part.begin();
            assert(wm.prev_value(l, r, x, got_value) == has_prev);
            if (has_prev) {
                --prev_it;
                assert(got_value == *prev_it);
            }
            auto next_it = lower_bound(part.begin(), part.end(), x);
            bool has_next = next_it != part.end();
            assert(wm.next_value(l, r, x, got_value) == has_next);
            if (has_next) assert(got_value == *next_it);
        }
    }

    vector<ll> same(128, -3);
    WaveletMatrix<ll> same_wm(same);
    assert(same_wm.count_less(0, 128, -2) == 128);
    assert(same_wm.freq(0, 128, -3) == 128);
    assert(same_wm.kth_smallest(0, 128, 127) == -3);

    vector<signed char> bytes = {-128, 127, 0, -1, 0, 127, -128};
    WaveletMatrix<signed char> byte_wm(bytes);
    assert(byte_wm.kth_smallest(0, (int)bytes.size(), 0) == -128);
    assert(byte_wm.kth_largest(0, (int)bytes.size(), 0) == 127);

    vector<string> words = {"z", "a", "m", "a", "zz"};
    WaveletMatrix<string> string_wm(words);
    assert(string_wm.count_less(0, 5, string("n")) == 3);
    string value;
    assert(string_wm.prev_value(0, 5, string("m"), value) && value == "a");
    assert(string_wm.next_value(0, 5, string("m"), value) && value == "m");

    WaveletMatrix<int> empty(vector<int>{});
    int value_int = 0;
    assert(empty.count_less(0, 0, 1) == 0);
    assert(!empty.prev_value(0, 0, 1, value_int));
    assert(!empty.next_value(0, 0, 1, value_int));
}

int main() {
    self_check();

    Scanner sc;
    Printer pr;
    ll a, b;
    sc.read(a, b);
    pr.println(a + b);
    return 0;
}
