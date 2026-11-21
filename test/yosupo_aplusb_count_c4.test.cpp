#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../graph/count_c4.cpp"

long long brute_force(int n, const vector<pair<int, int>> &edges) {
    vector<vector<bool>> adj(n, vector<bool>(n));
    for (auto [u, v] : edges) adj[u][v] = adj[v][u] = true;
    long long total = 0;
    for (int a = 0; a < n; ++a) {
        for (int b = a + 1; b < n; ++b) {
            for (int c = b + 1; c < n; ++c) {
                for (int d = c + 1; d < n; ++d) {
                    total += adj[a][b] && adj[b][c] && adj[c][d] && adj[d][a];
                    total += adj[a][b] && adj[b][d] && adj[d][c] && adj[c][a];
                    total += adj[a][c] && adj[c][b] && adj[b][d] && adj[d][a];
                }
            }
        }
    }
    return total;
}

int main() {
    for (int n = 0; n <= 6; ++n) {
        vector<pair<int, int>> all;
        for (int u = 0; u < n; ++u)
            for (int v = 0; v < u; ++v) all.emplace_back(u, v);
        for (int mask = 0; mask < (1 << all.size()); ++mask) {
            vector<pair<int, int>> edges;
            for (int i = 0; i < (int)all.size(); ++i)
                if (mask >> i & 1) edges.push_back(all[i]);
            assert(count_c4(n, edges) == brute_force(n, edges));
        }
    }
    mt19937 rng(558);
    for (int trial = 0; trial < 1000; ++trial) {
        int n = rng() % 15, density = rng() % 101;
        vector<pair<int, int>> edges;
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < u; ++v) {
                if ((int)(rng() % 100) < density) edges.emplace_back(u, v);
            }
        }
        shuffle(edges.begin(), edges.end(), rng);
        for (auto &[u, v] : edges) if (rng() & 1) swap(u, v);
        assert(count_c4(n, edges) == brute_force(n, edges));
    }
    int leaves = 100000;
    vector<pair<int, int>> bipartite;
    for (int i = 0; i < leaves; ++i) {
        bipartite.emplace_back(0, i + 2);
        bipartite.emplace_back(1, i + 2);
    }
    assert(count_c4(leaves + 2, bipartite) == 1LL * leaves * (leaves - 1) / 2);
}
