#define STANDALONE

#include <bits/stdc++.h>
using namespace std;

#include "../graph/topological_sort.cpp"

vector<int> brute(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> order(n), position(n);
    iota(order.begin(), order.end(), 0);
    do {
        for (int i = 0; i < n; ++i) position[order[i]] = i;
        bool valid = true;
        for (int v = 0; v < n && valid; ++v) {
            for (int to : g[v]) {
                if (position[v] >= position[to]) {
                    valid = false;
                    break;
                }
            }
        }
        if (valid) return order;
    } while (next_permutation(order.begin(), order.end()));
    return {};
}

int main() {
    for (int n = 0; n <= 4; ++n) {
        for (int mask = 0; mask < (1 << (n * n)); ++mask) {
            vector<vector<int>> g(n);
            for (int v = 0; v < n; ++v) {
                for (int to = 0; to < n; ++to) {
                    if (mask >> (v * n + to) & 1) g[v].push_back(to);
                }
            }
            assert(topological_sort_lexmin(g) == brute(g));
        }
    }
    vector<vector<int>> g{{}, {0, 0}, {0}, {}};
    assert((topological_sort_lexmin(g) == vector<int>{1, 2, 0, 3}));
    mt19937 rng(345);
    for (int t = 0; t < 500; ++t) {
        int n = 1 + rng() % 8;
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        shuffle(order.begin(), order.end(), rng);
        g.assign(n, {});
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((t % 2 == 0 || i < j) && rng() % 4 == 0) {
                    g[order[i]].push_back(order[j]);
                    if (rng() % 3 == 0) g[order[i]].push_back(order[j]);
                }
            }
        }
        assert(topological_sort_lexmin(g) == brute(g));
    }
    int n = 200000;
    g.assign(n, {});
    vector<int> expected(n);
    iota(expected.begin(), expected.end(), 0);
    assert(topological_sort_lexmin(g) == expected);
    for (int i = 0; i + 1 < n; ++i) g[i].push_back(i + 1);
    assert(topological_sort_lexmin(g) == expected);
    g.back().push_back(0);
    assert(topological_sort_lexmin(g).empty());
}
