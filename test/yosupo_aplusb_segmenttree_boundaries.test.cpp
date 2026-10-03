#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/segmenttree/segtree.cpp"
#include "../datastructure/segmenttree/lazysegtree.cpp"
#include "../datastructure/segmenttree/dualsegtree.cpp"

struct Sum {
    using T = long long;
    static T e() { return 0; }
    static T f(T a, T b) { return a + b; }
};

struct SumAffine {
    using T = pair<long long, int>;
    using L = pair<long long, long long>;
    static T e() { return {0, 0}; }
    static L l() { return {1, 0}; }
    static T f(T a, T b) { return {a.first + b.first, a.second + b.second}; }
    static T g(T a, L b) { return {a.first * b.first + a.second * b.second, a.second}; }
    static L h(L a, L b) { return {a.first * b.first, a.second * b.first + b.second}; }
};

struct Affine {
    using T = SumAffine::L;
    static T e() { return SumAffine::l(); }
    static T f(T a, T b) { return SumAffine::h(a, b); }
};

struct Concat {
    using T = string;
    static T e() { return ""; }
    static T f(const T &a, const T &b) { return a + b; }
};

void minimal_check() {
    SegmentTree<Sum> plain(1);
    plain.set(0, 1);
    plain.build();
    assert(plain.search_left(1, [](auto x) { return x < 1; }) == 1);

    LazySegmentTree<SumAffine> lazy(1);
    lazy.set(0, {0, 1});
    lazy.build();
    lazy.update(0, 1, {1, 5});
    assert(lazy.search_right(0, [](auto x) { return x.first < 1; }) == 0);
    lazy.update(0, SumAffine::T{2, 1});
    assert(lazy.query(0, 1).first == 2);
    lazy.update(1, 1, {1, 5});
    assert(lazy.query(0, 1).first == 2);

    DualSegmentTree<Sum> dual(2);
    dual.update(0, 1, 7);
    dual.update(2, 2, 5);
    assert(dual[0] == 7 && dual[1] == 0);
}

void exhaustive_search_check() {
    // Includes singleton and power-of-two right boundaries.
    for (int n = 0, count = 1; n <= 7; ++n, count *= 3) {
        for (int mask = 0; mask < count; ++mask) {
            vector<int> a(n);
            SegmentTree<Sum> seg(n);
            int digits = mask;
            for (int i = 0; i < n; ++i, digits /= 3) seg.set(i, a[i] = digits % 3);
            seg.build();
            for (int end = 0; end <= n; ++end) {
                for (int limit = 0; limit <= 2 * n + 1; ++limit) {
                    auto cond = [&](auto x) { return x <= limit; };
                    int left = end, right = end, sum = 0;
                    while (left > 0 && sum + a[left - 1] <= limit) sum += a[--left];
                    sum = 0;
                    while (right < n && sum + a[right] <= limit) sum += a[right++];
                    assert(seg.search_left(end, cond) == left);
                    assert(seg.search_right(end, cond) == right);
                }
            }
        }
    }
}

void mixed_update_check() {
    mt19937 rng(20261003);
    for (int n = 0; n <= 65; ++n) {
        LazySegmentTree<SumAffine> lazy(n);
        DualSegmentTree<Affine> dual(n);
        SegmentTree<Sum> plain(n);
        vector<long long> a(n), b(n);
        for (int i = 0; i < n; ++i) lazy.set(i, {0, 1});
        lazy.build();
        plain.build();
        for (int step = 0; step < 500; ++step) {
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            // Assignment and addition are noncommutative affine actions.
            Affine::T op = {rng() % 2, rng() % 8};
            lazy.update(l, r, op);
            dual.update(l, r, op);
            for (int i = l; i < r; ++i) {
                a[i] = a[i] * op.first + op.second;
                b[i] = b[i] * op.first + op.second;
                plain.update(i, a[i]);
            }
            if (n && step % 3 == 0) {
                int i = rng() % n;
                a[i] = rng() % 20;
                lazy.update(i, SumAffine::T{a[i], 1});
                plain.update(i, a[i]);
            }
            for (int end : {0, n / 2, n}) {
                lazy.update(end, end, {0, 99});
                dual.update(end, end, {0, 99});
                assert(lazy.query(end, end) == SumAffine::e());
            }
            long long limit = rng() % 100;
            int end = rng() % (n + 1), left = end, right = end;
            long long sum = 0;
            while (left > 0 && sum + a[left - 1] <= limit) sum += a[--left];
            sum = 0;
            while (right < n && sum + a[right] <= limit) sum += a[right++];
            auto cond = [&](auto x) { return x.first <= limit; };
            assert(lazy.search_left(end, cond) == left);
            assert(lazy.search_right(end, cond) == right);
            assert(plain.search_left(end, [&](auto x) { return x <= limit; }) == left);
            assert(plain.search_right(end, [&](auto x) { return x <= limit; }) == right);
            assert(lazy.query(l, r).first == accumulate(a.begin() + l, a.begin() + r, 0LL));
            assert(plain.query(l, r) == lazy.query(l, r).first);
            for (int i = 0; i < n; ++i) {
                assert(lazy.query(i, i + 1).first == a[i]);
                assert(dual[i].second == b[i]); // Apply the composed action to zero.
            }
        }
    }
}

void noncommutative_search_check() {
    mt19937 rng(67);
    for (int n = 0; n <= 32; ++n) {
        SegmentTree<Concat> seg(n);
        string s(n, 'a');
        for (int i = 0; i < n; ++i) seg.set(i, string(1, s[i] = 'a' + rng() % 3));
        seg.build();
        for (int step = 0; step < 100; ++step) {
            if (n) {
                int i = rng() % n;
                seg.update(i, string(1, s[i] = 'a' + rng() % 3));
            }
            int limit = rng() % (n + 1);
            auto cond = [&](const string &x) {
                return int(x.size()) <= limit && x.find("ab") == string::npos;
            };
            for (int end = 0; end <= n; ++end) {
                int left = end, right = end;
                while (left > 0 && cond(s.substr(left - 1, end - left + 1))) --left;
                while (right < n && cond(s.substr(end, right - end + 1))) ++right;
                assert(seg.search_left(end, cond) == left);
                assert(seg.search_right(end, cond) == right);
                assert(seg.query(left, right) == s.substr(left, right - left));
            }
        }
    }
}

int main() {
    minimal_check();
    exhaustive_search_check();
    mixed_update_check();
    noncommutative_search_check();
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
