#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../tree/centroid/nearest_active_vertex.cpp"

void check(const vector<vector<int>> &g, mt19937 &rng) {
    int n = g.size();
    NearestActiveVertex nearest(g);
    vector<vector<int>> distance(n, vector<int>(n, -1));
    for(int start = 0; start < n; ++start) {
        queue<int> q;
        q.push(start);
        distance[start][start] = 0;
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            for(int u : g[v]) if(distance[start][u] == -1) {
                distance[start][u] = distance[start][v] + 1;
                q.push(u);
            }
        }
        assert(nearest.nearest(start) == make_pair(-1, -1));
    }
    vector<bool> active(n);
    auto validate = [&]() {
        const auto &view = nearest;
        for(int v = 0; v < n; ++v) {
            optional<pair<int, int>> expected;
            for(int u = 0; u < n; ++u) if(active[u]) {
                pair<int, int> candidate{distance[v][u], u};
                if(!expected || candidate < *expected) expected = candidate;
            }
            assert(view.nearest(v) == expected.value_or(make_pair(-1, -1)));
        }
    };
    if(n == 0) return;
    for(int step = 0; step < 500; ++step) {
        int v = rng() % n;
        bool enabled = rng() % 2;
        nearest.set_active(v, enabled);
        nearest.set_active(v, enabled);
        active[v] = enabled;
        validate();
    }
    for(int v = 0; v < n; ++v) nearest.set_active(v, false);
    fill(active.begin(), active.end(), false);
    validate();
    for(int v = 0; v < n; ++v) {
        nearest.set_active(v, true);
        active[v] = true;
        validate();
    }
    for(int v = 0; v < n; ++v) {
        nearest.set_active(v, false);
        active[v] = false;
        validate();
    }
}

int main() {
    mt19937 rng(338);
    check({}, rng);
    check({{}}, rng);
    for(int tc = 0; tc < 240; ++tc) {
        int n = 2 + rng() % 35;
        vector<vector<int>> g(n);
        for(int v = 1; v < n; ++v) {
            int p = tc % 3 == 0 ? v - 1 : tc % 3 == 1 ? 0 : rng() % v;
            g[p].push_back(v);
            g[v].push_back(p);
        }
        check(g, rng);
    }
}
