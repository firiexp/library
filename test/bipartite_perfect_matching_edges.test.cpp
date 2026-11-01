#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../graph/matching/bipartite_perfect_matching_edges.cpp"

void check(int n, const vector<pair<int, int>> &edges) {
    vector<vector<int>> adjacent(n);
    for(int id = 0; id < int(edges.size()); ++id) adjacent[edges[id].first].push_back(id);
    vector<int> count(edges.size()), chosen;
    vector<bool> used(n);
    int total = 0;
    auto enumerate = [&](auto &&self, int u) -> void {
        if(u == n) {
            ++total;
            for(int id : chosen) ++count[id];
            return;
        }
        for(int id : adjacent[u]) {
            int v = edges[id].second;
            if(used[v]) continue;
            used[v] = true;
            chosen.push_back(id);
            self(self, u + 1);
            chosen.pop_back();
            used[v] = false;
        }
    };
    enumerate(enumerate, 0);
    auto result = bipartite_perfect_matching_edges(n, edges);
    if(total == 0) {
        assert(result.empty());
        return;
    }
    assert(result.size() == edges.size());
    for(int id = 0; id < int(edges.size()); ++id) {
        int expected = count[id] == 0 ? 0 : count[id] == total ? 2 : 1;
        assert(result[id] == expected);
    }
}

int main() {
    for(int n = 0; n <= 4; ++n) {
        for(int mask = 0; mask < (1 << (n * n)); ++mask) {
            vector<pair<int, int>> edges;
            for(int u = 0; u < n; ++u)
                for(int v = 0; v < n; ++v)
                    if(mask >> (u * n + v) & 1) edges.emplace_back(u, v);
            check(n, edges);
        }
    }
    check(1, {{0, 0}, {0, 0}, {0, 0}});
    check(3, {{0, 0}, {1, 1}, {1, 1}, {2, 2}, {0, 1}});
    check(4, {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 2}, {3, 3}, {2, 3}});
    mt19937 rng(344);
    for(int tc = 0; tc < 3000; ++tc) {
        int n = 1 + rng() % 6;
        vector<pair<int, int>> edges;
        for(int i = rng() % 20; i > 0; --i) edges.emplace_back(rng() % n, rng() % n);
        check(n, edges);
        shuffle(edges.begin(), edges.end(), rng);
        check(n, edges);
    }
}
