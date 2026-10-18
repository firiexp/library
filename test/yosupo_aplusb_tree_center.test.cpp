#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../tree/tree_center.cpp"

void check(const vector<vector<int>> &g) {
    auto original = g;
    auto [radius, centers] = tree_center(g);
    assert(g == original);
    int n = g.size();
    if (n == 0) {
        assert(radius == 0 && centers.empty());
        return;
    }
    vector<vector<int>> dist(n, vector<int>(n, -1));
    vector<int> eccentricity(n);
    for (int s = 0; s < n; ++s) {
        queue<int> q;
        dist[s][s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : g[v]) if (dist[s][to] == -1) {
                dist[s][to] = dist[s][v] + 1;
                q.push(to);
            }
        }
        eccentricity[s] = *max_element(dist[s].begin(), dist[s].end());
    }
    int expected_radius = *min_element(eccentricity.begin(), eccentricity.end());
    vector<int> expected;
    for (int v = 0; v < n; ++v) if (eccentricity[v] == expected_radius) expected.push_back(v);
    sort(expected.begin(), expected.end(), [&](int u, int v) { return dist[0][u] > dist[0][v]; });
    assert(radius == expected_radius && centers == expected);
}

int main() {
    mt19937 rng(183);
    for (int n = 0; n <= 80; ++n) {
        vector<int> labels(n);
        iota(labels.begin(), labels.end(), 0);
        for (int shape = 0; shape < 13; ++shape) {
            shuffle(labels.begin(), labels.end(), rng);
            vector<vector<int>> g(n);
            for (int v = 1; v < n; ++v) {
                int p = shape == 0 ? v - 1 : shape == 1 ? 0 : shape == 2 ? (v - 1) / 2 : rng() % v;
                g[labels[v]].push_back(labels[p]);
                g[labels[p]].push_back(labels[v]);
            }
            check(g);
            auto expected = tree_center(g);
            for (auto &adj : g) shuffle(adj.begin(), adj.end(), rng);
            assert(tree_center(g) == expected);
        }
    }
}
