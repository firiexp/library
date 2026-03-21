#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <random>
#include <vector>
using namespace std;

using ll = long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../datastructure/top_kth.cpp"

template<bool Largest>
ll brute_sum_k(const vector<ll>& a, int k) {
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
void verify_one(const vector<ll>& cur, const TopKTreap<ll, ll, Largest>& ds) {
    assert(ds.size() == (int)cur.size());
    assert(ds.empty() == cur.empty());
    assert(ds.total_sum() == accumulate(cur.begin(), cur.end(), 0LL));
    for (ll x = -8; x <= 8; ++x) {
        int cnt = 0;
        for (ll y : cur) cnt += x == y;
        assert(ds.count(x) == cnt);
        assert(ds.contains(x) == (cnt > 0));
    }
    for (int k = 0; k <= (int)cur.size() + 2; ++k) {
        assert(ds.sum_k(k) == brute_sum_k<Largest>(cur, k));
    }
    if (!cur.empty()) {
        for (int k = 1; k <= (int)cur.size(); ++k) {
            assert(ds.kth(k) == brute_kth<Largest>(cur, k));
        }
    }
    if (ds.has_kth()) {
        assert(ds.kth() == brute_kth<Largest>(cur, ds.k()));
    } else {
        assert(ds.k() <= 0 || ds.k() > (int)cur.size());
    }
    assert(ds.sum_topk() == brute_sum_k<Largest>(cur, ds.k()));
}

void self_check() {
    mt19937 rng(0);
    for (int tc = 0; tc < 300; ++tc) {
        TopKTreap<ll, ll, true> largest(0, rng());
        TopKTreap<ll, ll, false> smallest(0, rng());
        largest.reserve(256);
        smallest.reserve(256);
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

int main() {
    self_check();

    Scanner sc;
    Printer pr;
    ll a, b;
    sc.read(a, b);
    pr.writeln(a + b);
    return 0;
}
