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

int main() {
    constexpr int n = 100000, q = 100000, stride = 10007;
    constexpr uint64_t mod = Affine::mod;
    mt19937 rng(8200);
    vector<int> keys(n);
    for (int i = 0; i < n; ++i) keys[i] = i * stride;
    shuffle(keys.begin(), keys.end(), rng);
    vector<Affine::T> values(n);
    for (int i = 0; i < n; ++i) values[i] = {2, uint32_t(keys[i] % mod)};
    vector<uint64_t> power(n + 1, 1), forward(n + 1), backward(n + 1);
    for (int i = 0; i < n; ++i) {
        power[i + 1] = power[i] * 2 % mod;
        forward[i + 1] = (forward[i] * 2 + i * stride) % mod;
        backward[i + 1] = (backward[i] * 2 + (n - 1 - i) * stride) % mod;
    }
    SortableSegmentTree<Affine> seg(keys, values);
    bool descending = false;
    for (int i = 0; i < q; ++i) {
        if (i % 2 == 0) {
            descending = i % 4 == 0;
            if (descending) seg.sort_descending(0, n);
            else seg.sort_ascending(0, n);
        } else {
            int l = rng() % (n + 1), r = rng() % (n + 1);
            if (l > r) swap(l, r);
            const auto &prefix = descending ? backward : forward;
            Affine::T expected{uint32_t(power[r - l]),
                uint32_t((prefix[r] + mod - prefix[l] * power[r - l] % mod) % mod)};
            assert(seg.fold(l, r) == expected);
        }
    }
    for (int i = 0; i < n; ++i) {
        int key = (descending ? n - 1 - i : i) * stride;
        auto item = seg.get(i);
        assert(item.first == key);
        assert((item.second == Affine::T{2, uint32_t(key % mod)}));
    }
    auto stats = seg.node_stats();
    assert(stats.allocations > stats.slots);
    assert(stats.releases > 0 && stats.live == stats.allocations - stats.releases);
    assert(stats.peak_live == size_t(32) * n && stats.slots == stats.peak_live);
    cerr << "allocations=" << stats.allocations << " releases=" << stats.releases
         << " live=" << stats.live << " peak_live=" << stats.peak_live
         << " slots=" << stats.slots << '\n';
}
