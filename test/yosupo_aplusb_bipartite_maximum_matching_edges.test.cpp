#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../graph/matching/bipartite_maximum_matching_edges.cpp"

void check(int l, int r, const vector<pair<int, int>> &edges) {
    vector<vector<int>> adjacent(l);
    for(int id = 0; id < int(edges.size()); ++id) adjacent[edges[id].first].push_back(id);
    vector<int> count(edges.size()), chosen;
    vector<bool> used(r);
    int total = 0, best = -1;
    auto enumerate = [&](auto &&self, int u) -> void {
        if(u == l) {
            int size = chosen.size();
            if(size < best) return;
            if(size > best) {
                best = size;
                total = 0;
                fill(count.begin(), count.end(), 0);
            }
            ++total;
            for(int id : chosen) ++count[id];
            return;
        }
        self(self, u + 1);
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
    auto [size, result] = bipartite_maximum_matching_edges(l, r, edges);
    assert(size == best);
    assert(result.size() == edges.size());
    for(int id = 0; id < int(edges.size()); ++id) {
        int expected = count[id] == 0 ? 0 : count[id] == total ? 2 : 1;
        assert(result[id] == expected);
    }
}

int main() {
    for(int l = 0; l <= 4; ++l) {
        for(int r = 0; r <= 4; ++r) {
            for(int mask = 0; mask < (1 << (l * r)); ++mask) {
                vector<pair<int, int>> edges;
                for(int u = 0; u < l; ++u)
                    for(int v = 0; v < r; ++v)
                        if(mask >> (u * r + v) & 1) edges.emplace_back(u, v);
                check(l, r, edges);
            }
        }
    }
    check(1, 1, {{0, 0}, {0, 0}, {0, 0}});
    check(3, 3, {{0, 0}, {1, 1}, {1, 1}, {2, 2}, {0, 1}});
    check(4, 4, {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 2}, {3, 3}, {2, 3}});
    check(5, 4, {{0, 0}, {1, 0}, {1, 1}, {2, 2}, {2, 3}, {3, 3}, {4, 3}});
    for(int n : {2, 10, 10000}) {
        vector<pair<int, int>> edges;
        for(int u = 0; u < n; ++u) edges.emplace_back(u, u);
        for(int u = 0; u + 1 < n; ++u) edges.emplace_back(u, u + 1);
        auto [size, result] = bipartite_maximum_matching_edges(n, n, edges);
        assert(size == n);
        for(int id = 0; id < int(edges.size()); ++id) assert(result[id] == (id < n ? 2 : 0));
        edges.emplace_back(n - 1, 0);
        result = bipartite_maximum_matching_edges(n, n, edges).second;
        assert(result == vector<int>(edges.size(), 1));
        edges.pop_back();
        edges.emplace_back(n / 2, n / 2);
        result = bipartite_maximum_matching_edges(n, n, edges).second;
        for(int id = 0; id < int(edges.size()); ++id)
            assert(result[id] == (id == n / 2 || id == int(edges.size()) - 1 ? 1 : id < n ? 2 : 0));
        edges.pop_back();
        edges.emplace_back(n, 0);
        auto left_free = bipartite_maximum_matching_edges(n + 1, n, edges);
        assert(left_free.first == n && left_free.second == vector<int>(edges.size(), 1));
        edges.back() = {n - 1, n};
        auto right_free = bipartite_maximum_matching_edges(n, n + 1, edges);
        assert(right_free.first == n && right_free.second == vector<int>(edges.size(), 1));
    }
    mt19937 rng(344);
    for(int tc = 0; tc < 3000; ++tc) {
        int l = 1 + rng() % 6, r = 1 + rng() % 6;
        vector<pair<int, int>> edges;
        for(int i = rng() % 20; i > 0; --i) edges.emplace_back(rng() % l, rng() % r);
        check(l, r, edges);
        shuffle(edges.begin(), edges.end(), rng);
        check(l, r, edges);
    }
}
