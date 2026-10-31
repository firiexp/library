#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../tree/centroid/frequency_table_of_tree_distance.cpp"

vector<vector<int>> make_tree(const vector<int>& parent) {
    vector<vector<int>> g(parent.size() + 1);
    for (int v = 1; v < (int)g.size(); ++v) {
        g[v].push_back(parent[v - 1]);
        g[parent[v - 1]].push_back(v);
    }
    return g;
}

void check(const vector<vector<int>>& g, vector<long long> expected = {}) {
    int n = g.size();
    if (expected.empty()) {
        expected.resize(n);
        for (int s = 0; s < n; ++s) {
            vector<int> distance(n, -1), pending{s};
            distance[s] = 0;
            for (int i = 0; i < n; ++i) {
                int v = pending[i];
                for (int to : g[v]) if (distance[to] == -1) {
                    distance[to] = distance[v] + 1;
                    pending.push_back(to);
                }
            }
            for (int v = s + 1; v < n; ++v) ++expected[distance[v]];
        }
    }
    auto actual = frequency_table_of_tree_distance(g);
    assert(actual == expected);
    assert((int)actual.size() == n);
    assert(n == 0 || actual[0] == 0);
    assert(accumulate(actual.begin(), actual.end(), 0LL) == 1LL * n * (n - 1) / 2);
    if (n > 0) assert(all_of(actual.begin(), actual.end(), [](long long x) { return x >= 0; }));
}

int main() {
    check({});
    check(make_tree({}));
    check(make_tree({0}));
    check(make_tree({0, 0, 1, 1, 2, 5, 5}));
    for (int n : {3, 4, 5, 7, 8, 9, 127, 128, 129, 255, 256, 257,
                  511, 512, 513, 1023, 1024, 1025, 4097}) {
        vector<int> parent(n - 1);
        iota(parent.begin(), parent.end(), 0);
        vector<long long> expected(n);
        for (int d = 1; d < n; ++d) expected[d] = n - d;
        check(make_tree(parent), expected);
    }
    int n = 100000;
    vector<long long> star(n);
    star[1] = n - 1;
    star[2] = 1LL * (n - 1) * (n - 2) / 2;
    check(make_tree(vector<int>(n - 1)), star);
    mt19937 rng(244);
    for (int tc = 0; tc < 1200; ++tc) {
        int size = 1 + rng() % 100;
        vector<int> parent(size - 1);
        for (int v = 1; v < size; ++v) parent[v - 1] = rng() % v;
        auto g = make_tree(parent);
        for (auto& neighbors : g) shuffle(neighbors.begin(), neighbors.end(), rng);
        check(g);
    }
}
