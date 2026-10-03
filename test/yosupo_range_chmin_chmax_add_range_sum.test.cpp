#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"
#include <limits>
#include <vector>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <random>

using ll = long long;
using namespace std;

template<class T> constexpr T INF = ::numeric_limits<T>::max()/32*15+208;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include <charconv>
#include "../util/fastio.cpp"
#include "../datastructure/segmenttree/segbeats.cpp"

void self_check() {
    mt19937 rng(36);
    for (int n : {0, 1, 2, 3, 5, 6, 7, 8, 9, 15, 16, 17, 31, 32, 33}) {
        vector<ll> a(n);
        for (auto &x : a) x = int(rng() % 101) - 50;
        SegmentTreeBeats<ll> seg(a);
        for (int i = n; i < seg.n; ++i) {
            const auto &leaf = seg.seg[seg.n + i];
            assert(leaf.sum == 0 && leaf.len == 0 && leaf.mnc == 0 && leaf.mxc == 0);
            assert(leaf.mn == INF<ll> && leaf.mn2 == INF<ll>);
            assert(leaf.mx == -INF<ll> && leaf.mx2 == -INF<ll> && leaf.add == 0);
        }
        for (int step = 0; step < 500; ++step) {
            assert(seg.sum(0, n) == accumulate(a.begin(), a.end(), 0LL));
            assert(seg.seg[1].len == n);
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            assert(seg.sum(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
            ll value = int(rng() % 101) - 50;
            switch (step % 3) {
                case 0:
                    seg.chmin(l, r, value);
                    for (int i = l; i < r; ++i) a[i] = min(a[i], value);
                    break;
                case 1:
                    seg.chmax(l, r, value);
                    for (int i = l; i < r; ++i) a[i] = max(a[i], value);
                    break;
                case 2:
                    seg.add(l, r, value);
                    for (int i = l; i < r; ++i) a[i] += value;
            }
        }
        for (int l = 0; l <= n; ++l) for (int r = l; r <= n; ++r)
            assert(seg.sum(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
    }
}

int main() {
    self_check();
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);
    vector<ll> v(n);
    for (auto &&i : v) sc.read(i);
    SegmentTreeBeats<ll> seg(v);
    while(q--){
        int t;
        sc.read(t);
        if(t == 0){
            int l, r;
            ll b;
            sc.read(l, r, b);
            seg.chmin(l, r, b);
        }else if(t == 1){
            int l, r;
            ll b;
            sc.read(l, r, b);
            seg.chmax(l, r, b);
        }else if(t == 2){
            int l, r;
            ll b;
            sc.read(l, r, b);
            seg.add(l, r, b);
        }else {
            int l, r;
            sc.read(l, r);
            pr.println(seg.sum(l, r));
        }
    }
    return 0;
}
