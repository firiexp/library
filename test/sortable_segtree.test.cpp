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
typename M::T read_fold(SortableSegmentTree<M> &seg, int l, int r) {
    auto before = seg.node_stats();
    auto value = seg.fold(l, r);
    auto after = seg.node_stats();
    assert(before.allocations == after.allocations && before.releases == after.releases);
    assert(before.live == after.live && before.peak_live == after.peak_live && before.slots == after.slots);
    return value;
}

template<class M>
void check(uint64_t upper, mt19937_64 &rng, int n = -1) {
    using T = typename M::T;
    uint64_t key_count = min(upper, uint64_t(INT_MAX) + 1);
    if (n == -1) n = rng() % (min<uint64_t>(upper, 35) + 1);
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
        int key = rng() % key_count;
        if (!present.insert(key).second) continue;
        keys.push_back(key);
        values.push_back(value());
        expected.emplace_back(key, values.back());
    }
    SortableSegmentTree<M> seg(keys, values, upper);
    assert(seg.size() == n);
    int height = 0;
    for (uint64_t width = upper; width > 1; width = width / 2 + width % 2) ++height;
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
            int key = step % 3 == 0 ? old_key : int(rng() % key_count);
            while (present.count(key)) key = rng() % key_count;
            present.insert(key);
            T v = value();
            expected[i] = {key, v};
            seg.set(i, key, v);
        } else {
            T result = M::e();
            for (int i = l; i < r; ++i) result = M::f(result, expected[i].second);
            assert(read_fold(seg, l, r) == result);
        }
        if (step % 31 == 0) {
            for (int i = 0; i < n; ++i) assert(seg.get(i) == expected[i]);
            for (int a = 0; a <= n; ++a) {
                T result = M::e();
                for (int b = a; b <= n; ++b) {
                    assert(read_fold(seg, a, b) == result);
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
    check<Affine>(1, rng, 1);
    for (uint64_t upper : {1ULL, 2ULL, 3ULL, 7ULL, 16ULL, 99ULL, 1ULL << 31}) {
        for (int tc = 0; tc < 12; ++tc) {
            check<Affine>(upper, rng);
            check<Matrix>(upper, rng);
        }
    }
    for (int n : {0, 1, 63, 64, 65, 127, 128, 129}) check<Affine>(1ULL << 31, rng, n);
    for (uint64_t upper : {uint64_t(1) << 32, UINT64_MAX}) {
        check<Affine>(upper, rng, 8);
        SortableSegmentTree<Affine> wide({INT_MAX, 0}, {{2, 3}, {5, 7}}, upper);
        wide.sort_ascending(0, 2);
        assert(wide.get(0).first == 0 && wide.get(1).first == INT_MAX);
        wide.set(1, INT_MAX - 1, {11, 13});
        wide.sort_descending(0, 2);
        assert(wide.get(0).first == INT_MAX - 1);
        assert(wide.fold(0, 2) == Affine::f({11, 13}, {5, 7}));
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
