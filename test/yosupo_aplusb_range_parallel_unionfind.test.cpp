#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../datastructure/range_parallel_unionfind.cpp"

void check(int n, mt19937& rng) {
    RangeParallelUnionFind uf(n), without_callback(n);
    vector<int> label(n);
    iota(label.begin(), label.end(), 0);
    vector<long long> weights(n), sum(n);
    for (int i = 0; i < n; ++i) sum[i] = weights[i] = (int)(rng() % 21) - 10;
    int count = n, total_callbacks = 0;
    long long answer = 0;
    array<int, 3> previous{0, 0, 0};
    for (int step = 0; step < 120; ++step) {
        int k = rng() % (n + 1);
        int a = rng() % (n - k + 1), b = rng() % (n - k + 1);
        if (step % 7 == 0) tie(a, b, k) = tie(previous[0], previous[1], previous[2]);
        previous = {a, b, k};
        int callbacks = 0;
        int merged = uf.unite_range(a, b, k, [&](int keep, int absorbed) {
            assert(uf.root(keep) == keep && uf.root(absorbed) == absorbed);
            assert(!uf.same(keep, absorbed));
            long long s = 0, t = 0;
            for (int v = 0; v < n; ++v) {
                if (uf.same(v, keep)) s += weights[v];
                if (uf.same(v, absorbed)) t += weights[v];
            }
            assert(sum[keep] == s && sum[absorbed] == t);
            answer += sum[keep] * sum[absorbed];
            sum[keep] += sum[absorbed];
            ++callbacks;
        });
        int expected_merges = 0;
        for (int i = 0; i < k; ++i) {
            int keep = label[a + i], absorbed = label[b + i];
            if (keep == absorbed) continue;
            for (int& x : label) if (x == absorbed) x = keep;
            ++expected_merges;
        }
        assert(merged == expected_merges && callbacks == merged);
        assert(without_callback.unite_range(a, b, k) == merged);
        count -= merged;
        total_callbacks += callbacks;
        assert(uf.count() == count && without_callback.count() == count);
        assert(total_callbacks <= max(0, n - 1));
        long long expected_answer = 0;
        for (int v = 0; v < n; ++v) {
            assert(uf.root(uf.root(v)) == uf.root(v));
            int size = 0;
            for (int u = 0; u < n; ++u) {
                bool same = label[u] == label[v];
                assert(uf.same(u, v) == same && without_callback.same(u, v) == same);
                size += same;
                if (u < v && same) expected_answer += weights[u] * weights[v];
            }
            assert(uf.size(v) == size && without_callback.size(v) == size);
        }
        assert(answer == expected_answer);
    }
}

int main() {
    mt19937 rng(128);
    for (int n = 0; n <= 65; ++n) check(n, rng);
    for (int tc = 0; tc < 150; ++tc) check(rng() % 66, rng);
    RangeParallelUnionFind uf(65);
    assert(uf.unite_range(0, 65, 0) == 0);
    assert(uf.unite_range(0, 0, 65) == 0);
    assert(uf.unite_range(0, 1, 64) == 64);
    assert(uf.count() == 1 && uf.size(64) == 65);
    for (int k = 0; k <= 64; ++k) assert(uf.unite_range(0, 65 - k, k) == 0);
}
