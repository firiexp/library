#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../datastructure/unionfind/unionfind.cpp"

int main() {
    UnionFind empty(0);
    assert(empty.size() == 0);
    UnionFind fixed(6);
    auto check_merge = [&](int a, int b, int keep, int absorbed, int size, int components) {
        auto result = fixed.unite(a, b);
        assert(result.keep == keep && result.absorbed == absorbed);
        assert(bool(result) == (absorbed != -1));
        assert(fixed.root(a) == keep && fixed.root(b) == keep);
        assert(fixed.size(a) == size && fixed.size() == components);
    };
    check_merge(0, 0, 0, -1, 1, 6);
    check_merge(0, 1, 0, 1, 2, 5);
    check_merge(2, 3, 2, 3, 2, 4);
    check_merge(4, 2, 2, 4, 3, 3);
    check_merge(0, 4, 2, 0, 5, 2);
    check_merge(1, 3, 2, -1, 5, 2);
    check_merge(5, 0, 2, 5, 6, 1);
    check_merge(0, 5, 2, -1, 6, 1);

    mt19937 rng(414);
    for (int tc = 0; tc < 250; ++tc) {
        int n = 1 + rng() % 40;
        UnionFind uf(n);
        vector<int> label(n);
        iota(label.begin(), label.end(), 0);
        vector<long long> weight(n), sum(n);
        for (auto& x : weight) x = int(rng() % 2001) - 1000;
        sum = weight;
        for (int step = 0; step < 200; ++step) {
            int a = rng() % n, b = rng() % n;
            int ra = uf.root(a), rb = uf.root(b);
            bool same = label[a] == label[b];
            int keep = uf.size(a) >= uf.size(b) ? ra : rb;
            int absorbed = same ? -1 : (keep == ra ? rb : ra);
            auto result = uf.unite(a, b);
            assert(result.keep == keep && result.absorbed == absorbed);
            assert(bool(result) == !same);
            assert(uf.root(a) == keep && uf.root(b) == keep);
            if (result) sum[result.keep] += sum[result.absorbed];
            int old_label = label[b], new_label = label[a];
            for (int& value : label) if (value == old_label) value = new_label;
            set<int> components(label.begin(), label.end());
            assert(uf.size() == (int)components.size());
            for (int v = 0; v < n; ++v) {
                long long expected = 0;
                int size = 0;
                for (int u = 0; u < n; ++u) {
                    if (label[u] == label[v]) expected += weight[u], ++size;
                }
                assert(sum[uf.root(v)] == expected);
                assert(uf.size(v) == size);
                assert(uf.same(a, v) == (label[a] == label[v]));
            }
        }
    }
}
