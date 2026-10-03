#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;
#include "../util/fastio.cpp"
#include "../tree/hld_edge.cpp"

int main() {
    mt19937 rng(20261003);
    for (int n = 1; n <= 70; ++n) {
        HeavyLightDecompositionEdge edge(n);
        vector<int> parent(n, -1);
        for (int v = 1; v < n; ++v) {
            parent[v] = rng() % v;
            edge.add_edge(parent[v], v);
        }
        edge.build();
        auto &hld = edge.hld;
        vector<int> at(n);
        for (int v = 0; v < n; ++v) at[hld.id[v]] = v;
        auto collect = [&](int l, int r) { return vector<int>(at.begin() + l, at.begin() + r); };
        auto count = [](int l, int r) { return r - l; };
        for (int root = 0; root < n; ++root) {
            vector<int> expected;
            for (int v = 0; v < n; ++v) {
                int u = v;
                while (u != -1 && u != root) u = parent[u];
                if (u == root) expected.push_back(v);
            }
            auto actual = hld.subtree_query(root, collect);
            static_assert(is_same_v<decltype(actual), vector<int>>);
            sort(actual.begin(), actual.end());
            assert(actual == expected);
            assert(hld.subtree_query(root, count) == int(expected.size()));
            expected.erase(find(expected.begin(), expected.end(), root));
            actual = edge.subtree_query(root, collect);
            sort(actual.begin(), actual.end());
            assert(actual == expected);
            assert(edge.subtree_query(root, count) == int(expected.size()));
            assert(hld.subtree_query(root, collect, true) == edge.subtree_query(root, collect));
        }
        auto ref = [&](int, int) -> const vector<int> & { return at; };
        static_assert(is_same_v<decltype(hld.subtree_query(0, ref)), const vector<int> &>);
        static_assert(is_same_v<decltype(edge.subtree_query(0, ref)), const vector<int> &>);
        assert(&hld.subtree_query(0, ref) == &at);
        assert(&edge.subtree_query(0, ref) == &at);
    }
    Scanner sc;
    Printer pr;
    int a, b;
    sc.read(a, b);
    pr.println(a + b);
}
