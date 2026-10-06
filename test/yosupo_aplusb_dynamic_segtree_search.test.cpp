#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "../util/fastio.cpp"
#include "../datastructure/segmenttree/dynamic_segtree.cpp"

struct Sum {
    using T = ll;
    static T e() { return 0; }
    static T f(T a, T b) { return a + b; }
};

struct Concat {
    using T = string;
    static T e() { return ""; }
    static T f(const T &a, const T &b) { return a + b; }
};

void sum_check() {
    mt19937 rng(113);
    for (int n = 0; n <= 65; ++n) {
        DynamicSegmentTree<Sum> seg(n);
        const auto &view = seg;
        vector<ll> a(n);
        for (int step = 0; step < 300; ++step) {
            if (n && step % 3) {
                int k = rng() % n;
                ll x = rng() % 20;
                if (step % 2) {
                    seg.add(k, x);
                    a[k] += x;
                } else {
                    seg.update(k, x);
                    a[k] = x;
                }
            }
            size_t nodes = seg.node.size();
            for (int end : {0, int(rng() % (n + 1)), n}) {
                ll limit = rng() % 200, sum = 0;
                int left = end, right = end;
                while (left && sum + a[left - 1] <= limit) sum += a[--left];
                sum = 0;
                while (right < n && sum + a[right] <= limit) sum += a[right++];
                auto cond = [&](ll x) { return x <= limit; };
                assert(view.search_left(end, cond) == left);
                assert(view.search_right(end, cond) == right);
                assert(view.query(left, right) == accumulate(a.begin() + left, a.begin() + right, 0LL));
            }
            assert(seg.node.size() == nodes);
        }
    }
}

void noncommutative_check() {
    mt19937 rng(114);
    for (int n = 0; n <= 32; ++n) {
        DynamicSegmentTree<Concat> seg(n);
        vector<string> a(n);
        for (int step = 0; step < 100; ++step) {
            if (n) {
                int k = rng() % n;
                a[k] = rng() % 3 ? string(1, 'a' + rng() % 3) : "";
                seg.update(k, a[k]);
            }
            int limit = rng() % (n + 1);
            auto cond = [&](const string &x) {
                return int(x.size()) <= limit && x.find("ab") == string::npos;
            };
            size_t nodes = seg.node.size();
            for (int end = 0; end <= n; ++end) {
                int left = end, right = end;
                string acc;
                while (left && cond(a[left - 1] + acc)) acc = a[--left] + acc;
                acc.clear();
                while (right < n && cond(acc + a[right])) acc += a[right++];
                assert(seg.search_left(end, cond) == left);
                assert(seg.search_right(end, cond) == right);
            }
            assert(seg.node.size() == nodes);
        }
    }
}

void sparse_check() {
    for (ll n : {1LL, 1000000000000LL, LLONG_MAX}) {
        DynamicSegmentTree<Sum> seg(n);
        auto zero = [](ll x) { return x == 0; };
        for (ll end : {0LL, n / 2, n}) {
            assert(seg.search_left(end, zero) == 0);
            assert(seg.search_right(end, zero) == n);
        }
        assert(seg.node.empty());
        seg.update(n - 1, 1);
        assert(seg.search_right(0, zero) == n - 1);
        assert(seg.search_left(n, zero) == n);
        assert(seg.search_left(n - 1, zero) == 0);
        assert(seg.search_right(n, zero) == n);
        seg.update(0, 1);
        assert(seg.search_right(0, zero) == 0);
        assert(seg.search_left(n, [](ll x) { return x <= 2; }) == 0);
        assert(seg.search_right(0, [](ll x) { return x <= 2; }) == n);
    }
}

int main() {
    sum_check();
    noncommutative_check();
    sparse_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
