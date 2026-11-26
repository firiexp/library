#define PROBLEM "https://judge.yosupo.jp/problem/counting_c4"

#include <bits/stdc++.h>
using namespace std;

#include "../util/fastio.cpp"
#include "../graph/count_c4.cpp"

int main() {
    Scanner in;
    Printer out;
    int n, m;
    in.read(n, m);
    vector<pair<int, int>> edges(m);
    in.read(edges);
    for (auto &[u, v] : edges) if (u > v) swap(u, v);
    vector<int> order(m), group(m);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return edges[a] < edges[b]; });
    vector<pair<int, int>> simple;
    vector<long long> multiplicity;
    for (int i : order) {
        if (simple.empty() || simple.back() != edges[i]) {
            simple.push_back(edges[i]);
            multiplicity.push_back(0);
        }
        group[i] = (int)simple.size() - 1;
        ++multiplicity.back();
    }

    vector<long long> per_edge(simple.size()), paths(n);
    vector<int> last_root(n, -1);
    count_c4_detail::for_each_root(n, simple, [&](int root, auto visit_paths) {
        visit_paths([&](int w, int first, int second) {
            if (last_root[w] != root) {
                last_root[w] = root;
                paths[w] = 0;
            }
            paths[w] += multiplicity[first] * multiplicity[second];
        });
        visit_paths([&](int w, int first, int second) {
            long long others = paths[w] - multiplicity[first] * multiplicity[second];
            per_edge[first] += others * multiplicity[second];
            per_edge[second] += others * multiplicity[first];
        });
    });
    if ((int)simple.size() == m) {
        __int128 sum = accumulate(per_edge.begin(), per_edge.end(), (__int128)0);
        if (sum != (__int128)4 * count_c4(n, edges)) return 1;
    }
    vector<long long> answer(m);
    for (int i = 0; i < m; ++i) answer[i] = per_edge[group[i]];
    out.println(answer);
}
