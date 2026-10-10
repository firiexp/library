#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/dynamic_graph_vertex_add_component_sum.cpp"

void check(int n, int q, int mode, mt19937 &rng) {
    vector<long long> values(n);
    for (auto &x : values) x = (int)(rng() % 21) - 10;
    DynamicGraphVertexAddComponentSum solver(values, q);
    vector<vector<char>> edges(n, vector<char>(n));
    vector<long long> expected;
    for (int t = 0; t < q; ++t) {
        int u = rng() % n, v = rng() % n;
        int type = rng() % 4;
        if (mode == 1) type = 2;
        if (mode == 2) type = 3;
        if (mode == 3) {
            type = t % 2 ? 2 : 0;
            u = 0;
            v = n - 1;
        }
        if (mode == 4) {
            type = 0;
            u = 0;
            v = n - 1;
        }
        if (type < 2 && u == v) type = 3;
        if (mode != 1 && t == q - 1) type = 3;
        if (type < 2) {
            if (edges[u][v]) solver.erase_edge(u, v);
            else solver.add_edge(u, v);
            edges[u][v] = edges[v][u] = !edges[u][v];
        } else if (type == 2) {
            long long x = (int)(rng() % 21) - 10;
            solver.add_vertex(u, x);
            values[u] += x;
        } else {
            solver.add_component_query(u);
            vector<int> queue{u};
            vector<char> seen(n);
            seen[u] = 1;
            long long sum = 0;
            for (int i = 0; i < (int)queue.size(); ++i) {
                int a = queue[i];
                sum += values[a];
                for (int b = 0; b < n; ++b) {
                    if (!edges[a][b] || seen[b]) continue;
                    seen[b] = 1;
                    queue.push_back(b);
                }
            }
            expected.push_back(sum);
        }
    }
    assert(solver.solve() == expected);
    assert(solver.solve() == expected);
}

int main() {
    mt19937 rng(20261010);
    for (int q : {0, 1, 2, 3, 7, 8, 9, 127, 128, 129})
        for (int mode = 0; mode < 5; ++mode)
            for (int n : {1, 2, 10}) check(n, q, mode, rng);
    for (int tc = 0; tc < 2000; ++tc) check(1 + rng() % 12, rng() % 200, 0, rng);
    DynamicGraphVertexAddComponentSum path(vector<long long>(1000, 1), 1001);
    for (int i = 0; i < 999; ++i) path.add_edge(i, i + 1);
    path.add_vertex(0, -1000);
    path.add_component_query(999);
    assert(path.solve() == vector<long long>{0});
    Scanner in;
    Printer out;
    int a, b;
    in.read(a, b);
    out.println(a + b);
}
