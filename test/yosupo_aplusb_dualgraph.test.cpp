#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../geometry/dualgraph.cpp"

void check(const Polygon &points, const vector<pair<int, int>> &edges) {
    int n = points.size(), m = edges.size();
    DualGraph dual(points);
    for (auto [u, v] : edges) dual.add_edge(u, v);
    vector<vector<int>> previous;
    vector<vector<pair<double, double>>> previous_faces;
    for (int build = 0; build < 2; ++build) {
        dual.build();
        for (int u = 0; u < n; ++u) {
            const auto &adj = dual.G_[u];
            for (int j = 0; j < (int)adj.size(); ++j) {
                const auto &e = adj[j];
                assert(e.nxt == (j + 1) % (int)adj.size());
                assert(dual.G_[e.to][e.rev].to == u);
                assert(dual.G_[e.to][e.rev].id == e.id);
                if (j) assert(arg(points[adj[j - 1].to] - points[u]) <= arg(points[e.to] - points[u]));
            }
        }
        assert((int)dual.A.size() == m - n + 2);
        assert(dual.G.size() == dual.A.size());
        int boundary_size = 0;
        for (const auto &face : dual.A) boundary_size += face.size();
        assert(boundary_size == 2 * m);
        vector<vector<int>> sides(m);
        for (const auto &neighbors : dual.G_) for (const auto &e : neighbors) {
            assert(1 <= e.id2 && e.id2 <= (int)dual.A.size());
            sides[e.id].push_back(e.id2 - 1);
        }
        vector<vector<int>> expected(dual.A.size());
        for (int id = 0; id < m; ++id) {
            assert(sides[id].size() == 2);
            vector<vector<int>> g(n);
            for (int j = 0; j < m; ++j) if (j != id) {
                auto [u, v] = edges[j];
                g[u].push_back(v);
                g[v].push_back(u);
            }
            vector<int> seen(n), order{edges[id].first};
            seen[order[0]] = 1;
            for (int i = 0; i < (int)order.size(); ++i) for (int v : g[order[i]]) if (!seen[v]) {
                seen[v] = 1;
                order.push_back(v);
            }
            bool bridge = !seen[edges[id].second];
            assert((sides[id][0] == sides[id][1]) == bridge);
            expected[sides[id][0]].push_back(sides[id][1]);
            expected[sides[id][1]].push_back(sides[id][0]);
        }
        for (int f = 0; f < (int)expected.size(); ++f) {
            sort(expected[f].begin(), expected[f].end());
            auto actual = dual.G[f];
            sort(actual.begin(), actual.end());
            assert(actual == expected[f]);
        }
        if (build) assert(dual.G == previous);
        previous = dual.G;
        vector<vector<pair<double, double>>> faces;
        for (const auto &face : dual.A) {
            faces.emplace_back();
            for (Point p : face) faces.back().emplace_back(p.x, p.y);
        }
        if (build) assert(faces == previous_faces);
        previous_faces = faces;
    }
}

void self_check() {
    check({Point(0, 0), Point(1, 0), Point(-1, 0)}, {{0, 1}, {0, 2}});
    check({Point(0, 0), Point(1, 0), Point(-1, 0), Point(0, 1), Point(0, -1)},
          {{0, 1}, {0, 2}, {0, 3}, {0, 4}});
    check({Point(0, 0), Point(2, 0), Point(0, 2)}, {{0, 1}, {1, 2}, {2, 0}});
    check({Point(0, 0), Point(2, 0), Point(0, 2), Point(-1, 0)},
          {{0, 1}, {1, 2}, {2, 0}, {0, 3}});
    mt19937 rng(15);
    for (int degree : {3, 14, 15, 16, 17, 32, 64}) {
        Polygon points{Point(0, 0)};
        vector<pair<int, int>> spokes, wheel;
        for (int i = 0; i < degree; ++i) {
            double angle = 2 * pi * i / degree;
            points.emplace_back(cos(angle), sin(angle));
            spokes.emplace_back(0, i + 1);
        }
        wheel = spokes;
        for (int i = 0; i < degree; ++i) wheel.emplace_back(i + 1, (i + 1) % degree + 1);
        for (int repeat = 0; repeat < 8; ++repeat) {
            shuffle(spokes.begin(), spokes.end(), rng);
            shuffle(wheel.begin(), wheel.end(), rng);
            check(points, spokes);
            check(points, wheel);
        }
    }
    for (int h = 1; h <= 6; ++h) for (int w = 1; w <= 6; ++w) {
        if (h * w < 2) continue;
        Polygon points;
        vector<pair<int, int>> edges;
        for (int y = 0; y < h; ++y) for (int x = 0; x < w; ++x) {
            int v = y * w + x;
            points.emplace_back(x, y);
            if (x) edges.emplace_back(v - 1, v);
            if (y && (x == 0 || rng() % 2)) edges.emplace_back(v - w, v);
            if (x && y && rng() % 2) edges.emplace_back(v - w - 1, v);
        }
        check(points, edges);
    }
}

int main() {
    self_check();
}
