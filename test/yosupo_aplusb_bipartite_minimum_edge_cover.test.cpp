#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../graph/matching/bipartite_minimum_edge_cover.cpp"

void validate(int l, int r, const vector<pair<int, int>> &edges,
              const vector<int> &result) {
    vector<char> left(l), right(r), used(edges.size());
    for (int id : result) {
        assert(0 <= id && id < int(edges.size()));
        assert(!used[id]);
        used[id] = true;
        auto [u, v] = edges[id];
        left[u] = right[v] = true;
    }
    for (bool covered : left) assert(covered);
    for (bool covered : right) assert(covered);
}

void check(int l, int r, const vector<pair<int, int>> &edges) {
    int m = edges.size(), full = (1 << (l + r)) - 1;
    int best = m + 1;
    vector<int> covered(1 << m);
    for (int mask = 0; mask < (1 << m); ++mask) {
        if (mask) {
            int id = __builtin_ctz(unsigned(mask));
            auto [u, v] = edges[id];
            covered[mask] = covered[mask & (mask - 1)] | (1 << u) | (1 << (l + v));
        }
        if (covered[mask] == full) best = min(best, __builtin_popcount(unsigned(mask)));
    }
    auto result = bipartite_minimum_edge_cover(l, r, edges);
    if (best > m) {
        assert(result.empty());
        return;
    }
    assert(int(result.size()) == best);
    validate(l, r, edges, result);
}

int main() {
    for (int l = 0; l <= 4; ++l) {
        for (int r = 0; r <= 4; ++r) {
            for (int mask = 0; mask < (1 << (l * r)); ++mask) {
                vector<pair<int, int>> edges;
                for (int u = 0; u < l; ++u)
                    for (int v = 0; v < r; ++v)
                        if (mask >> (u * r + v) & 1) edges.emplace_back(u, v);
                check(l, r, edges);
            }
        }
    }
    check(2, 3, {{0, 0}, {0, 0}, {0, 1}, {1, 2}, {1, 2}});
    check(3, 2, {{0, 0}, {1, 0}, {1, 0}, {2, 1}});
    check(3, 3, {{0, 0}, {1, 1}, {1, 1}});
    mt19937 rng(418);
    for (int tc = 0; tc < 1000; ++tc) {
        int l = 1 + rng() % 5, r = 1 + rng() % 5;
        vector<pair<int, int>> edges;
        for (int m = rng() % 15; m > 0; --m) edges.emplace_back(rng() % l, rng() % r);
        check(l, r, edges);
        shuffle(edges.begin(), edges.end(), rng);
        check(l, r, edges);
    }
    for (bool transpose : {false, true}) {
        int l = 1, r = 10000;
        vector<pair<int, int>> edges;
        for (int v = 0; v < r; ++v) edges.emplace_back(0, v);
        if (transpose) {
            swap(l, r);
            for (auto &[u, v] : edges) swap(u, v);
        }
        auto result = bipartite_minimum_edge_cover(l, r, edges);
        assert(result.size() == 10000);
        validate(l, r, edges, result);
    }
}
