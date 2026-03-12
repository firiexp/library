#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

#include <algorithm>
#include <array>
#include <cassert>
#include <random>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

static const int MOD = 998244353;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../util/fastio.cpp"
#include "../util/modint.cpp"
#include "../datastructure/implicit_treap.cpp"

struct AffineSumMonoid {
    using T = array<mint, 2>;
    using L = array<mint, 2>;
    static T f(T a, T b) { return {a[0] + b[0], a[1] + b[1]}; }
    static T g(T a, L b) { return {a[0] * b[0] + a[1] * b[1], a[1]}; }
    static L h(L a, L b) { return {a[0] * b[0], a[1] * b[0] + b[1]}; }
    static T e() { return {0, 0}; }
    static L l() { return {1, 0}; }
};

struct RangeAddSumMonoid {
    using T = array<ll, 2>;
    using L = ll;
    static T f(T a, T b) { return {a[0] + b[0], a[1] + b[1]}; }
    static T g(T a, L b) { return {a[0] + a[1] * b, a[1]}; }
    static L h(L a, L b) { return a + b; }
    static T e() { return {0, 0}; }
    static L l() { return 0; }
};

struct StringMonoid {
    using T = string;
    using L = int;
    static T f(const T &a, const T &b) { return a + b; }
    static T g(const T &a, L) { return a; }
    static L h(L, L) { return 0; }
    static T e() { return ""; }
    static L l() { return 0; }
};

void self_check_sum() {
    mt19937 rng(0);
    for (int tc = 0; tc < 200; ++tc) {
        vector<ll> brute;
        ImplicitTreap<RangeAddSumMonoid> tr;
        int init_n = rng() % 8;
        for (int i = 0; i < init_n; ++i) {
            ll x = (int)(rng() % 21) - 10;
            brute.push_back(x);
            tr.push_back({x, 1});
        }
        for (int step = 0; step < 200; ++step) {
            int op = rng() % 7;
            if (brute.empty()) op = 0;
            if (op == 0) {
                int pos = rng() % (brute.size() + 1);
                ll x = (int)(rng() % 21) - 10;
                brute.insert(brute.begin() + pos, x);
                tr.insert(pos, {x, 1});
            } else if (op == 1) {
                int pos = rng() % brute.size();
                ll got = tr.erase(pos)[0];
                assert(got == brute[pos]);
                brute.erase(brute.begin() + pos);
            } else if (op == 2) {
                int pos = rng() % brute.size();
                ll x = (int)(rng() % 21) - 10;
                brute[pos] = x;
                tr.set(pos, {x, 1});
            } else if (op == 3) {
                int l = rng() % brute.size();
                int r = rng() % brute.size();
                if (l > r) swap(l, r);
                ++r;
                ll add = (int)(rng() % 21) - 10;
                for (int i = l; i < r; ++i) brute[i] += add;
                tr.apply(l, r, add);
            } else if (op == 4) {
                int l = rng() % brute.size();
                int r = rng() % brute.size();
                if (l > r) swap(l, r);
                ++r;
                reverse(brute.begin() + l, brute.begin() + r);
                tr.reverse(l, r);
            } else if (op == 5) {
                int l = rng() % brute.size();
                int r = rng() % brute.size();
                if (l > r) swap(l, r);
                ++r;
                ll sum = 0;
                for (int i = l; i < r; ++i) sum += brute[i];
                assert(tr.fold(l, r)[0] == sum);
            } else {
                int pos = rng() % brute.size();
                assert(tr.get(pos)[0] == brute[pos]);
            }
            assert(tr.size() == (int)brute.size());
            ll total = 0;
            for (ll x : brute) total += x;
            assert(tr.all_fold()[0] == total);
        }
    }
}

void self_check_order() {
    mt19937 rng(1);
    for (int tc = 0; tc < 200; ++tc) {
        vector<string> brute;
        ImplicitTreap<StringMonoid> tr;
        int init_n = rng() % 8;
        for (int i = 0; i < init_n; ++i) {
            string s(1, char('a' + rng() % 3));
            brute.push_back(s);
            tr.push_back(s);
        }
        for (int step = 0; step < 200; ++step) {
            int op = rng() % 6;
            if (brute.empty()) op = 0;
            if (op == 0) {
                int pos = rng() % (brute.size() + 1);
                string s(1, char('a' + rng() % 3));
                brute.insert(brute.begin() + pos, s);
                tr.insert(pos, s);
            } else if (op == 1) {
                int pos = rng() % brute.size();
                assert(tr.erase(pos) == brute[pos]);
                brute.erase(brute.begin() + pos);
            } else if (op == 2) {
                int pos = rng() % brute.size();
                string s(1, char('a' + rng() % 3));
                brute[pos] = s;
                tr.set(pos, s);
            } else if (op == 3) {
                int l = rng() % brute.size();
                int r = rng() % brute.size();
                if (l > r) swap(l, r);
                ++r;
                reverse(brute.begin() + l, brute.begin() + r);
                tr.reverse(l, r);
            } else if (op == 4) {
                int l = rng() % brute.size();
                int r = rng() % brute.size();
                if (l > r) swap(l, r);
                ++r;
                string s;
                for (int i = l; i < r; ++i) s += brute[i];
                assert(tr.fold(l, r) == s);
            } else {
                int pos = rng() % brute.size();
                assert(tr.get(pos) == brute[pos]);
            }
            string all;
            for (const auto &s : brute) all += s;
            assert(tr.all_fold() == all);
        }
    }
}

int main() {
    self_check_sum();
    self_check_order();

    Scanner sc;
    Printer pr;

    int n, q;
    sc.read(n, q);
    vector<array<mint, 2>> init(n);
    for (int i = 0; i < n; ++i) {
        int a;
        sc.read(a);
        init[i] = {a, 1};
    }

    ImplicitTreap<AffineSumMonoid> tr(init);
    while (q--) {
        int t;
        sc.read(t);
        if (t == 0) {
            int pos, x;
            sc.read(pos, x);
            tr.insert(pos, {x, 1});
        } else if (t == 1) {
            int pos;
            sc.read(pos);
            tr.erase(pos);
        } else if (t == 2) {
            int l, r;
            sc.read(l, r);
            tr.reverse(l, r);
        } else if (t == 3) {
            int l, r, b, c;
            sc.read(l, r, b, c);
            tr.apply(l, r, {b, c});
        } else {
            int l, r;
            sc.read(l, r);
            pr.writeln(tr.fold(l, r)[0].val);
        }
    }
    return 0;
}
