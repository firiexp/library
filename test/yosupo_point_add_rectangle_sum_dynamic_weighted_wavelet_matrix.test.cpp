#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "../datastructure/dynamic_weighted_wavelet_matrix.cpp"
#include "../util/fastio.cpp"

int main() {
    Scanner sc;
    Printer pr;
    int n, q;
    sc.read(n, q);

    struct Point {
        int x, y;
        long long weight;
        bool initially_active;
    };
    struct Query {
        int type;
        int a, b, c, d;
        long long weight;
    };

    vector<Point> points;
    points.reserve(n + q);
    for (int i = 0; i < n; ++i) {
        int x, y;
        long long weight;
        sc.read(x, y, weight);
        points.push_back({x, y, weight, true});
    }

    vector<Query> queries;
    queries.reserve(q);
    for (int i = 0; i < q; ++i) {
        int type;
        sc.read(type);
        if (type == 0) {
            int x, y;
            long long weight;
            sc.read(x, y, weight);
            int id = (int)points.size();
            points.push_back({x, y, weight, false});
            queries.push_back({type, id, 0, 0, 0, weight});
        }
        else {
            int l, d, r, u;
            sc.read(l, d, r, u);
            queries.push_back({type, l, d, r, u, 0});
        }
    }

    int m = (int)points.size();
    vector<int> ord(m);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        if (points[a].x != points[b].x) return points[a].x < points[b].x;
        return a < b;
    });

    vector<int> position(m), xs(m), values(m);
    vector<long long> weights(m, 0);
    for (int i = 0; i < m; ++i) {
        int id = ord[i];
        position[id] = i;
        xs[i] = points[id].x;
        values[i] = points[id].y;
        if (points[id].initially_active) weights[i] = points[id].weight;
    }

    DynamicWeightedWaveletMatrix<int, long long> wm(values, weights);
    for (const Query &query : queries) {
        if (query.type == 0) {
            wm.add_weight(position[query.a], query.weight);
        }
        else {
            int l = (int)(lower_bound(xs.begin(), xs.end(), query.a) - xs.begin());
            int r = (int)(lower_bound(xs.begin(), xs.end(), query.c) - xs.begin());
            pr.println(wm.range_sum(l, r, query.b, query.d));
        }
    }
    return 0;
}
