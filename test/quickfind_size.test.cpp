#define STANDALONE

#include <bits/stdc++.h>
using namespace std;
#include "../datastructure/unionfind/quickfind.cpp"

int main() {
    QuickFind empty(0);
    mt19937 rng(331);
    for (int n = 1; n <= 60; ++n) {
        for (int tc = 0; tc < 20; ++tc) {
            QuickFind uf(n);
            vector<int> component(n);
            iota(component.begin(), component.end(), 0);
            auto verify = [&]() {
                for (int v = 0; v < n; ++v) {
                    vector<int> expected;
                    for (int u = 0; u < n; ++u) {
                        if (component[u] == component[v]) expected.push_back(u);
                    }
                    assert(uf.size(v) == expected.size());
                    assert(uf.size(v) == uf.components(v).size());
                    auto actual = uf.components(v);
                    sort(actual.begin(), actual.end());
                    assert(actual == expected);
                }
            };
            verify();
            for (int step = 0; step < 100; ++step) {
                int u = rng() % n, v = rng() % n;
                if (n >= 4 && step == 0) u = 1, v = 2;
                if (n >= 4 && step == 1) u = 0, v = 2;
                if (n >= 4 && step == 2) u = 1, v = 3;
                int from = component[v], to = component[u];
                assert(uf.unite(u, v) == (from != to));
                for (int &c : component) if (c == from) c = to;
                verify();
                assert(!uf.unite(v, u));
                verify();
            }
        }
    }
}
