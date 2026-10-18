#define STANDALONE

#include <algorithm>
#include <array>
#include <cassert>
#include <numeric>
#include <random>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

#include "../datastructure/implicit_treap.cpp"

struct SumAffine {
    using T = array<long long, 2>;
    using L = array<long long, 2>;
    static T f(T a, T b) { return {a[0] + b[0], a[1] + b[1]}; }
    static T g(T a, L x) { return {a[0] * x[0] + a[1] * x[1], a[1]}; }
    static L h(L a, L b) { return {a[0] * b[0], a[1] * b[0] + b[1]}; }
    static T e() { return {0, 0}; }
    static L l() { return {1, 0}; }
};

void sum_queries() {
    mt19937 rng(207);
    for (int initial = 0; initial <= 60; ++initial) {
        vector<long long> expected(initial);
        vector<SumAffine::T> values;
        for (auto &x : expected) {
            x = rng() % 10;
            values.push_back({x, 1});
        }
        ImplicitTreap<SumAffine> tr(values);
        for (int step = 0; step < 600; ++step) {
            int n = expected.size();
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            int op = rng() % 6;
            long long x = rng() % 10;
            if (op == 0 && n < 80) {
                tr.insert(l, {x, 1});
                expected.insert(expected.begin() + l, x);
            } else if (op == 1 && n) {
                int k = rng() % n;
                assert(tr.erase(k)[0] == expected[k]);
                expected.erase(expected.begin() + k);
            } else if (op == 2 && n) {
                int k = rng() % n;
                tr.set(k, {x, 1});
                expected[k] = x;
            } else if (op == 3) {
                tr.reverse(l, r);
                reverse(expected.begin() + l, expected.begin() + r);
            } else {
                if (op == 5) l = 0, r = n;
                long long a = rng() % 2;
                tr.apply(l, r, {a, x});
                for (int i = l; i < r; ++i) expected[i] = a * expected[i] + x;
            }
            n = expected.size();
            long long total = accumulate(expected.begin(), expected.end(), 0LL);
            auto count = tr.nodes.size(), capacity = tr.nodes.capacity(), free_count = tr.free_nodes.size();
            int root = tr.root;
            for (long long limit : {0LL, (long long)(rng() % 200), total}) {
                auto cond = [&](SumAffine::T x) { return x[0] <= limit; };
                for (int k : {0, int(rng() % (n + 1)), n}) {
                    int right = k, left = k;
                    long long sum = 0;
                    while (right < n && sum + expected[right] <= limit) sum += expected[right++];
                    sum = 0;
                    while (left > 0 && expected[left - 1] + sum <= limit) sum += expected[--left];
                    assert(tr.search_right(k, cond) == right);
                    assert(tr.search_left(k, cond) == left);
                }
            }
            assert(tr.nodes.size() == count && tr.nodes.capacity() == capacity);
            assert(tr.free_nodes.size() == free_count && tr.root == root);
            assert(tr.size() == n && tr.all_fold()[0] == total);
            if (step % 71 == 0) {
                for (int i = 0; i < n; ++i) assert(tr.get(i)[0] == expected[i]);
            }
        }
    }
}

struct StringMap {
    using T = string;
    using L = array<int, 3>;
    static T f(const T &a, const T &b) { return a + b; }
    static T g(T a, L x) {
        for (char &c : a) c = 'a' + x[c - 'a'];
        return a;
    }
    static L h(L a, L b) { return {b[a[0]], b[a[1]], b[a[2]]}; }
    static T e() { return ""; }
    static L l() { return {0, 1, 2}; }
};

void noncommutative_queries() {
    mt19937 rng(208);
    for (int initial = 0; initial <= 40; ++initial) {
        string expected(initial, 'a');
        vector<string> values;
        for (char &c : expected) {
            c += rng() % 3;
            values.emplace_back(1, c);
        }
        ImplicitTreap<StringMap> tr(values);
        for (int step = 0; step < 500; ++step) {
            int n = expected.size();
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            int op = rng() % 6;
            char c = 'a' + rng() % 3;
            if (op == 0 && n < 60) {
                tr.insert(l, string(1, c));
                expected.insert(expected.begin() + l, c);
            } else if (op == 1 && n) {
                int k = rng() % n;
                assert(tr.erase(k) == expected.substr(k, 1));
                expected.erase(k, 1);
            } else if (op == 2 && n) {
                int k = rng() % n;
                tr.set(k, string(1, c));
                expected[k] = c;
            } else if (op == 3) {
                tr.reverse(l, r);
                reverse(expected.begin() + l, expected.begin() + r);
            } else {
                if (op == 5) l = 0, r = n;
                StringMap::L map{int(rng() % 3), int(rng() % 3), int(rng() % 3)};
                tr.apply(l, r, map);
                for (int i = l; i < r; ++i) expected[i] = 'a' + map[expected[i] - 'a'];
            }
            n = expected.size();
            string forbidden(2, 'a');
            for (char &x : forbidden) x += rng() % 3;
            int limit = rng() % (n + 1);
            auto cond = [&](const string &s) {
                return (int)s.size() <= limit && s.find(forbidden) == string::npos;
            };
            auto count = tr.nodes.size();
            for (int k = 0; k <= n; ++k) {
                int right = k, left = k;
                while (right < n && cond(expected.substr(k, right + 1 - k))) ++right;
                while (left > 0 && cond(expected.substr(left - 1, k - left + 1))) --left;
                assert(tr.search_right(k, cond) == right);
                assert(tr.search_left(k, cond) == left);
            }
            assert(tr.nodes.size() == count);
            assert(tr.all_fold() == expected);
        }
    }
}

void whole_ranges() {
    constexpr int n = 100000;
    ImplicitTreap<SumAffine> tr(vector<SumAffine::T>(n, {1, 1}));
    tr.apply(0, n, {0, 7});
    tr.reverse(0, n);
    int calls = 0;
    auto all = [&](SumAffine::T x) { ++calls; return x[0] <= 7LL * n; };
    assert(tr.search_right(0, all) == n && calls == 1);
    calls = 0;
    assert(tr.search_left(n, all) == 0 && calls == 1);
    calls = 0;
    assert(tr.search_right(n, all) == n && calls == 0);
    assert(tr.search_left(0, all) == 0 && calls == 0);
    auto empty_only = [](SumAffine::T x) { return x[0] == 0; };
    for (int k : {0, 1, n / 2, n - 1, n}) {
        assert(tr.search_right(k, empty_only) == k);
        assert(tr.search_left(k, empty_only) == k);
    }
}

int main() {
    sum_queries();
    noncommutative_queries();
    whole_ranges();
}
