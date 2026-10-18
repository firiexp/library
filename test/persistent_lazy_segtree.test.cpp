#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../datastructure/segmenttree/persistent_lazy_segtree.cpp"
#include "../datastructure/segmenttree/persistent_lazy_segtree.cpp"

struct AffineSum {
    static constexpr long long mod = 998244353;
    using T = array<long long, 2>;
    struct L { long long mul, add; };
    static T f(T a, T b) { return {(a[0] + b[0]) % mod, a[1] + b[1]}; }
    static T g(T value, L op) { return {(value[0] * op.mul + value[1] * op.add) % mod, value[1]}; }
    static L h(L a, L b) { return {a.mul * b.mul % mod, (a.add * b.mul + b.add) % mod}; }
    static T e() { return {0, 0}; }
    static L l() { return {1, 0}; }
};

struct CharacterMap {
    using T = string;
    using L = array<int, 4>;
    static T f(const T &a, const T &b) { return a + b; }
    static T g(T value, const L &op) {
        for (char &c : value) c = 'a' + op[c - 'a'];
        return value;
    }
    static L h(L a, const L &b) {
        for (int &x : a) x = b[x];
        return a;
    }
    static T e() { return {}; }
    static L l() { return {0, 1, 2, 3}; }
};

template<class M, class Operation>
void exercise(vector<typename M::T> initial, Operation operation, mt19937 &rng) {
    using T = typename M::T;
    int n = initial.size(), height = 0;
    while ((1 << height) < n) ++height;
    PersistentLazySegmentTree<M> seg(initial);
    assert(seg.versions() == 1 && seg.latest_version() == 0);
    assert(seg.node.size() == (n ? 2 * (size_t)n - 1 : 0));
    vector<vector<T>> model{initial};
    auto check = [&](int t, int l, int r) {
        T expected = M::e();
        for (int i = l; i < r; ++i) expected = M::f(expected, model[t][i]);
        const auto &immutable = seg;
        size_t size = seg.node.size(), capacity = seg.node.capacity();
        assert(immutable.query(t, l, r) == expected);
        assert(seg.node.size() == size && seg.node.capacity() == capacity);
        assert(seg.versions() == (int)model.size());
    };
    auto update = [&](int t, int l, int r, const typename M::L &op) {
        auto values = model[t];
        for (int i = l; i < r; ++i) values[i] = M::g(values[i], op);
        size_t before = seg.node.size();
        int id = seg.update(t, l, r, op);
        assert(id == (int)model.size());
        model.push_back(std::move(values));
        assert(seg.node.size() - before <= (size_t)(8 * height + 1));
        if (l == r) assert(seg.node.size() == before);
        return id;
    };
    auto copy = [&](int dst, int src, int l, int r) {
        auto values = model[dst];
        for (int i = l; i < r; ++i) values[i] = model[src][i];
        size_t before = seg.node.size();
        int id = seg.copy_range(dst, src, l, r);
        assert(id == (int)model.size());
        model.push_back(std::move(values));
        assert(seg.node.size() - before <= (size_t)(8 * height + 1));
        if (l == r || dst == src || (l == 0 && r == n)) assert(seg.node.size() == before);
        return id;
    };
    int a = update(0, 0, n, operation()), b = update(a, 0, n, operation());
    int c = update(0, 0, n, operation());
    int d = copy(b, c, n / 3, n - n / 3);
    int e = copy(c, b, n / 4, n - n / 4);
    copy(d, e, 0, n);
    copy(b, b, 0, n);
    for (int step = 0; step < 300; ++step) {
        int t = rng() % model.size(), src = rng() % model.size();
        int l = rng() % (n + 1), r = rng() % (n + 1);
        if (l > r) swap(l, r);
        if (step % 2) update(t, l, r, operation());
        else copy(t, src, l, r);
        assert(seg.latest_version() == (int)model.size() - 1);
        check(seg.latest_version(), 0, n);
        for (int i = 0; i < 8; ++i) {
            t = rng() % model.size();
            l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            check(t, l, r);
        }
    }
    for (int t = 0; t < (int)model.size(); ++t) {
        check(t, 0, n);
        for (int i = 0; i < n; ++i) check(t, i, i + 1);
    }
}

int main() {
    for (unsigned seed : {39u, 2026u, 998244353u}) {
        mt19937 rng(seed);
        for (int trial = 0; trial < 40; ++trial) {
            int n = trial < 10 ? trial : rng() % 41;
            vector<AffineSum::T> numbers(n);
            vector<string> characters(n);
            for (int i = 0; i < n; ++i) {
                numbers[i] = {(long long)(rng() % AffineSum::mod), 1};
                characters[i] = string(1, 'a' + rng() % 4);
            }
            exercise<AffineSum>(numbers, [&] {
                return AffineSum::L{(long long)(rng() % 10), (long long)(rng() % 100)};
            }, rng);
            exercise<CharacterMap>(characters, [&] {
                CharacterMap::L op;
                for (int &x : op) x = rng() % 4;
                return op;
            }, rng);
        }
    }
}
