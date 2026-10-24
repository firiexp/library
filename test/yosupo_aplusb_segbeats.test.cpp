#define STANDALONE
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

void aligned_boundaries() {
    mt19937 rng(247);
    for (int n : {0, 1, 2, 7, 8, 9, 31, 32, 33, 127, 128, 129}) {
        for (int mode = 0; mode < 4; ++mode) {
            vector<ll> a(n);
            for (int i = 0; i < n; ++i) {
                a[i] = mode == 0 ? i : mode == 1 ? -i : mode == 2 ? (i % 2 ? -n : n) : 0;
            }
            SegmentTreeBeats<ll> seg(a);
            for (int step = 0; step < 1000; ++step) {
                int width = 1 << (rng() % 8);
                int l = min(n, int(rng() % (n / width + 1)) * width);
                int r = min(n, l + width);
                if (step % 4 == 0) l = 0, r = n;
                if (step % 7 == 0) r = l;
                ll x = step % 5 == 0 ? n - step : int(rng() % 101) - 50;
                if (step % 3 == 0) {
                    seg.chmin(l, r, x);
                    for (int i = l; i < r; ++i) a[i] = min(a[i], x);
                } else if (step % 3 == 1) {
                    seg.chmax(l, r, x);
                    for (int i = l; i < r; ++i) a[i] = max(a[i], x);
                } else {
                    seg.add(l, r, x);
                    for (int i = l; i < r; ++i) a[i] += x;
                }
                assert(seg.sum(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
                assert(seg.sum(0, n) == accumulate(a.begin(), a.end(), 0LL));
                l = rng() % (n + 1), r = rng() % (n + 1);
                if (l > r) swap(l, r);
                assert(seg.sum(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
            }
            for (int i = 0; i < n; ++i) assert(seg.sum(i, i + 1) == a[i]);
        }
    }
}

int main() {
    self_check();
    aligned_boundaries();
}
