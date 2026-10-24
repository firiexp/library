#define STANDALONE
#include <bits/stdc++.h>
using namespace std;

#include "../datastructure/segmenttree/sortable_segtree.cpp"

struct Affine {
    using T = array<uint32_t, 2>;
    static constexpr uint32_t mod = 998244353;
    static T f(T a, T b) {
        return {uint32_t(uint64_t(a[0]) * b[0] % mod),
                uint32_t((uint64_t(a[1]) * b[0] + b[1]) % mod)};
    }
    static T e() { return {1, 0}; }
};

struct Matrix {
    using T = array<uint32_t, 4>;
    static constexpr uint32_t mod = 998244353;
    static T f(T a, T b) {
        T result{};
        for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) {
            uint64_t value = 0;
            for (int k = 0; k < 2; ++k) value += uint64_t(a[i * 2 + k]) * b[k * 2 + j];
            result[i * 2 + j] = value % mod;
        }
        return result;
    }
    static T e() { return {1, 0, 0, 1}; }
};

template<class M>
void check(uint64_t upper, mt19937_64 &rng) {
    using T = typename M::T;
    int n = rng() % (min<uint64_t>(upper, 35) + 1);
    auto value = [&]() {
        T result;
        for (auto &x : result) x = rng() % M::mod;
        return result;
    };
    vector<int> keys;
    vector<T> values;
    std::set<int> present;
    vector<pair<int, T>> expected;
    while ((int)keys.size() < n) {
        int key = rng() % upper;
        if (!present.insert(key).second) continue;
        keys.push_back(key);
        values.push_back(value());
        expected.emplace_back(key, values.back());
    }
    SortableSegmentTree<M> seg(keys, values, upper);
    assert(seg.size() == n);
    int height = 0;
    for (uint64_t width = 1; width < upper; width <<= 1) ++height;
    for (int step = 0; step < 700; ++step) {
        int l = rng() % (n + 1), r = rng() % (n + 1);
        if (l > r) swap(l, r);
        if (step % 9 < 2) l = 0, r = n;
        int type = step % 9 < 2 ? step % 9 : rng() % 4;
        if (type < 2) {
            if (type == 0) seg.sort_ascending(l, r);
            else seg.sort_descending(l, r);
            sort(expected.begin() + l, expected.begin() + r, [&](const auto &a, const auto &b) {
                return type == 0 ? a.first < b.first : a.first > b.first;
            });
        } else if (type == 2 && n) {
            int i = rng() % n;
            int old_key = expected[i].first;
            present.erase(old_key);
            int key = step % 3 == 0 ? old_key : int(rng() % upper);
            while (present.count(key)) key = rng() % upper;
            present.insert(key);
            T v = value();
            expected[i] = {key, v};
            seg.set(i, key, v);
        } else {
            T result = M::e();
            for (int i = l; i < r; ++i) result = M::f(result, expected[i].second);
            assert(seg.fold(l, r) == result);
        }
        if (step % 31 == 0) {
            for (int i = 0; i < n; ++i) assert(seg.get(i) == expected[i]);
            for (int a = 0; a <= n; ++a) {
                T result = M::e();
                for (int b = a; b <= n; ++b) {
                    assert(seg.fold(a, b) == result);
                    if (b < n) result = M::f(result, expected[b].second);
                }
            }
        }
        auto stats = seg.node_stats();
        assert(stats.live == stats.allocations - stats.releases);
        assert(stats.live <= stats.peak_live && stats.peak_live <= stats.slots);
        assert(stats.slots <= size_t(n) * (height + 1));
    }
}

int main() {
    mt19937_64 rng(82);
    for (uint64_t upper : {1ULL, 2ULL, 3ULL, 7ULL, 16ULL, 99ULL, 1ULL << 31}) {
        for (int tc = 0; tc < 12; ++tc) {
            check<Affine>(upper, rng);
            check<Matrix>(upper, rng);
        }
    }
    SortableSegmentTree<Affine> seg({0, INT_MAX, 1}, {{2, 3}, {5, 7}, {11, 13}});
    seg.sort_descending(0, 3);
    assert(seg.get(0).first == INT_MAX);
    seg.set(1, 1000000007, {17, 19});
    seg.set(2, 1, {23, 29});
    seg.set(0, 0, {31, 37});
    seg.sort_ascending(0, 3);
    assert(seg.get(0).first == 0 && seg.get(1).first == 1 && seg.get(2).first == 1000000007);
    assert(seg.fold(0, 3) == Affine::f(Affine::f({31, 37}, {23, 29}), {17, 19}));
}
