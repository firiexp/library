#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
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
    for (int tc = 0; tc < 300; ++tc) {
        int n = rng() % 60 + 1;
        vector<ll> a(n);
        for (ll &x : a) x = (int)(rng() % 21) - 10;

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
        }
    }
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
