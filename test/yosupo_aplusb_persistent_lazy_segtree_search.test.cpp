#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../datastructure/segmenttree/persistent_lazy_segtree.cpp"

struct CharacterAffine {
    using T = string;
    struct L { int mul, add; };
    static T e() { return {}; }
    static L l() { return {1, 0}; }
    static T f(const T &a, const T &b) { return a + b; }
    static T g(T value, L op) {
        for (char &c : value) c = 'a' + ((c - 'a') * op.mul + op.add) % 5;
        return value;
    }
    static L h(L a, L b) { return {a.mul * b.mul % 5, (a.add * b.mul + b.add) % 5}; }
};

template<class M, class F>
void check_search(const PersistentLazySegmentTree<M> &seg, int t,
                  const vector<typename M::T> &values, int end, F cond) {
    int left = end, right = end;
    auto acc = M::e();
    while (left && cond(M::f(values[left - 1], acc))) acc = M::f(values[--left], acc);
    acc = M::e();
    while (right < (int)values.size() && cond(M::f(acc, values[right]))) acc = M::f(acc, values[right++]);
    size_t nodes = seg.node.size(), capacity = seg.node.capacity();
    auto roots = seg.root;
    assert(seg.search_left(t, end, cond) == left);
    assert(seg.search_right(t, end, cond) == right);
    assert(seg.node.size() == nodes && seg.node.capacity() == capacity && seg.root == roots);
}

void character_check() {
    using M = CharacterAffine;
    for (unsigned seed : {258u, 2026u, 998244353u}) {
        mt19937 rng(seed);
        for (int n = 0; n <= 44; ++n) {
            vector<string> initial(n);
            for (auto &v : initial) v = string(1, 'a' + rng() % 5);
            PersistentLazySegmentTree<M> seg(initial);
            vector<vector<string>> model{initial};
            auto update = [&](int t, int l, int r, M::L op) {
                auto values = model[t];
                for (int i = l; i < r; ++i) values[i] = M::g(values[i], op);
                int version = seg.update(t, l, r, op);
                assert(version == (int)model.size());
                model.push_back(std::move(values));
                return version;
            };
            auto copy = [&](int dst, int src, int l, int r) {
                auto values = model[dst];
                for (int i = l; i < r; ++i) values[i] = model[src][i];
                int version = seg.copy_range(dst, src, l, r);
                assert(version == (int)model.size());
                model.push_back(std::move(values));
                return version;
            };
            int a = update(0, 0, n, {2, 1});
            int b = update(a, 0, n, {3, 2});
            int c = update(0, 0, n, {4, 3});
            copy(b, c, n / 3, n - n / 3);
            update(b, n / 2, n / 2, {0, 0});
            copy(c, b, n / 2, n / 2);
            auto check = [&](int t, int end, int limit) {
                auto cond = [&](const string &value) {
                    return (int)value.size() <= limit && value.find("ab") == string::npos;
                };
                check_search(seg, t, model[t], end, cond);
            };
            for (int step = 0; step < 200; ++step) {
                int t = rng() % model.size(), src = rng() % model.size();
                int l = rng() % (n + 1), r = rng() % (n + 1);
                if (l > r) swap(l, r);
                if (step % 2) update(t, l, r, {int(rng() % 5), int(rng() % 5)});
                else copy(t, src, l, r);
                for (int q = 0; q < 6; ++q) {
                    int v = q == 0 ? seg.latest_version() : q == 1 ? t : q == 2 ? src : rng() % model.size();
                    int end = q == 0 ? 0 : q == 1 ? n : rng() % (n + 1);
                    check(v, end, q == 0 ? 0 : q == 1 ? n : rng() % (n + 1));
                }
            }
            for (int t = 0; t < (int)model.size(); ++t) {
                string expected;
                for (const auto &value : model[t]) expected += value;
                assert(seg.query(t, 0, n) == expected);
                for (int end : {0, n / 2, n}) {
                    check(t, end, 0);
                    check(t, end, n);
                    check_search(seg, t, model[t], end, [](const string &) { return true; });
                }
            }
        }
    }
}

struct NonnegativeSum {
    using T = array<long long, 2>;
    struct L { long long mul, add; };
    static inline int calls = 0;
    static T e() { return {0, 0}; }
    static L l() { return {1, 0}; }
    static T f(T a, T b) { ++calls; return {a[0] + b[0], a[1] + b[1]}; }
    static T g(T value, L op) { ++calls; return {value[0] * op.mul + value[1] * op.add, value[1]}; }
    static L h(L a, L b) { ++calls; return {a.mul * b.mul, a.add * b.mul + b.add}; }
};

void sum_check() {
    using M = NonnegativeSum;
    int n = 100003;
    PersistentLazySegmentTree<M> seg(vector<M::T>(n, {1, 1}));
    int a = seg.update(0, 0, n, {0, 4});
    int b = seg.update(a, 0, n, {1, 3});
    int c = seg.update(0, 0, n, {0, 2});
    int d = seg.copy_range(b, c, n / 3, 2 * n / 3);
    vector<long long> prefix(n + 1);
    for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + (n / 3 <= i && i < 2 * n / 3 ? 2 : 7);
    mt19937 rng(258);
    const auto &view = seg;
    size_t nodes = seg.node.size(), capacity = seg.node.capacity();
    auto roots = seg.root;
    for (int q = 0; q < 3000; ++q) {
        int end = q % 3 == 0 ? 0 : q % 3 == 1 ? n : rng() % (n + 1);
        long long limit = q % 5 == 0 ? 0 : q % 5 == 1 ? prefix[n] : rng() % prefix[n];
        auto cond = [&](M::T value) { return value[0] <= limit; };
        int right = upper_bound(prefix.begin(), prefix.end(), prefix[end] + limit) - prefix.begin() - 1;
        int left = lower_bound(prefix.begin(), prefix.end(), prefix[end] - limit) - prefix.begin();
        M::calls = 0;
        assert(view.search_right(d, end, cond) == right);
        assert(M::calls <= 12 * 18);
        M::calls = 0;
        assert(view.search_left(d, end, cond) == left);
        assert(M::calls <= 12 * 18);
    }
    assert(seg.node.size() == nodes && seg.node.capacity() == capacity && seg.root == roots);
    assert(seg.query(0, 0, n)[0] == n && seg.query(a, 0, n)[0] == 4LL * n);
    assert(seg.query(b, 0, n)[0] == 7LL * n && seg.query(c, 0, n)[0] == 2LL * n);
}

int main() {
    character_check();
    sum_check();
}
