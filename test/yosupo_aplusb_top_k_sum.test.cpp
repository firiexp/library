#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <random>
#include <set>
#include <vector>
using namespace std;

using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/top_k_sum.cpp"

template<bool Largest>
ll brute_sum_topk(const vector<ll>& a, int k) {
    if (k <= 0) return 0;
    vector<ll> b = a;
    sort(b.begin(), b.end());
    if constexpr (Largest) reverse(b.begin(), b.end());
    k = min(k, (int)b.size());
    return accumulate(b.begin(), b.begin() + k, 0LL);
}

template<bool Largest>
ll brute_kth(const vector<ll>& a, int k) {
    vector<ll> b = a;
    sort(b.begin(), b.end());
    if constexpr (Largest) reverse(b.begin(), b.end());
    return b[k - 1];
}

template<bool Largest>
void verify_one(const vector<ll>& cur, const TopKSum<ll, ll, Largest>& ds) {
    assert(ds.size() == (int)cur.size());
    assert(ds.empty() == cur.empty());
    assert(ds.total_sum() == accumulate(cur.begin(), cur.end(), 0LL));
    assert(ds.sum_topk() == brute_sum_topk<Largest>(cur, ds.k()));
    if (ds.has_kth()) {
        assert(ds.kth() == brute_kth<Largest>(cur, ds.k()));
    } else {
        assert(ds.k() <= 0 || ds.k() > (int)cur.size());
    }
}

void random_check() {
    mt19937 rng(0);
    for (int tc = 0; tc < 300; ++tc) {
        TopKSum<ll, ll, true> largest(0);
        TopKSum<ll, ll, false> smallest(0);
        vector<ll> cur;

        for (int step = 0; step < 200; ++step) {
            int op = rng() % 4;
            if (op <= 1) {
                ll x = (int)(rng() % 17) - 8;
                largest.insert(x);
                smallest.insert(x);
                cur.push_back(x);
            } else if (op == 2) {
                ll x = (int)(rng() % 17) - 8;
                bool ok1 = largest.erase_one(x);
                bool ok2 = smallest.erase_one(x);
                auto it = find(cur.begin(), cur.end(), x);
                bool ok3 = it != cur.end();
                if (ok3) cur.erase(it);
                assert(ok1 == ok2);
                assert(ok2 == ok3);
            } else {
                int new_k = rng() % 12;
                largest.set_k(new_k);
                smallest.set_k(new_k);
            }
            verify_one<true>(cur, largest);
            verify_one<false>(cur, smallest);
        }
    }
}

void sliding_window_check() {
    mt19937 rng(1);
    for (int tc = 0; tc < 100; ++tc) {
        int n = rng() % 80 + 1;
        int m = rng() % n + 1;
        int k = rng() % (m + 2);
        vector<ll> a(n);
        for (ll& x : a) x = (int)(rng() % 31) - 15;

        TopKSum<ll, ll, false> ds(k);
        vector<ll> got;
        for (int i = 0; i < n; ++i) {
            ds.insert(a[i]);
            if (i >= m) ds.erase_one(a[i - m]);
            if (i >= m - 1) {
                vector<ll> cur(a.begin() + i - m + 1, a.begin() + i + 1);
                got.push_back(ds.sum_topk());
                assert(got.back() == brute_sum_topk<false>(cur, k));
            }
        }
    }
}

int main() {
    random_check();
    sliding_window_check();

    Scanner sc;
    Printer pr;
    ll a, b;
    sc.read(a, b);
    pr.writeln(a + b);
    return 0;
}
